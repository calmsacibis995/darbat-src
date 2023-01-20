/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#include <IOKit/IOLib.h>
#include <IOKit/IOPlatformExpert.h>
#include "Apple8259PIC.h"
#include "PICShared.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define super IOInterruptController

OSDefineMetaClassAndStructors( Apple8259PICInterruptController,
                               IOInterruptController )

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef L4IOKIT
#include <l4/kdebug.h>
extern "C" {
#include <iguana/hardware.h>
};
void Apple8259PIC::printBadState(IOPICState prevState, IOPICState nextState)
{
	const char *states[] = {
		"kIOPICNotRegistered",
		"kIOPICRegistered",
		"kIOPICEnabled",
		"kIOPICDisabled"
	};

	IOLog("Apple8259PIC::printBadState: bad state transition prevState %s "
	   "requested state %s\n", states[prevState], states[nextState]);
}

bool Apple8259PIC::isState(long irq, IOPICState state)
{
	return _interruptState[irq] == state;
}

void Apple8259PIC::setState(long irq, IOPICState state)
{
	// change the state, as well as do some sanity checks.
	switch (state) {
		case kIOPICNotRegistered:
			// I am guessing that this must either be in
			// disabled state or in Registered state.
			if (_interruptState[irq] != kIOPICRegistered &&
			    _interruptState[irq] != kIOPICDisabled)
				printBadState(_interruptState[irq], state);
			break;
		case kIOPICRegistered:
			if (_interruptState[irq] != kIOPICNotRegistered)
				printBadState(_interruptState[irq], state);
			break;
		case kIOPICEnabled:
			// can only reach enable state if it was previously
			// in registered state or disabled state.
			if (_interruptState[irq] != kIOPICDisabled && 
			    _interruptState[irq] != kIOPICRegistered &&
			    _interruptState[irq] != kIOPICInInterrupt &&
			    _interruptState[irq] != kIOPICQueued) 
				printBadState(_interruptState[irq], state);
			break;
		case kIOPICDisabled:
			// should only be able to reach this if it was 
			// previously enabled.  I wonder if it is possible
			// to call registerInterrupt() and then call 
			// diableVectorHard() to disable the interrupt???
			// if so then we need to change this
			if (_interruptState[irq] != kIOPICEnabled)
				printBadState(_interruptState[irq], state);
			break;
		case kIOPICInInterrupt:
			// should only be in this state if prev state
			// is enabled.
			if (_interruptState[irq] != kIOPICEnabled)
				printBadState(_interruptState[irq], state);
			break;
		case kIOPICQueued:
			// we can get into this state if we were delivered
			// an interrupt which we could not service because
			// the interrupts were in kIOPICDisabled state.
			if (_interruptState[irq] != kIOPICDisabled)
				printBadState(_interruptState[irq], state);
			break;
		default:
			IOLog("setState: unknown state %d\n", state);
			break;
	}

	_interruptState[irq] = state;
}

// register hook
IOReturn Apple8259PIC::registerInterrupt(IOService *nub, int source,
                                     void *target,
                                     IOInterruptHandler handler,
                                     void *refCon)
{
	IOReturn	res;
	IOInterruptSource *interruptSources;
	long              vectorNumber;
	OSData            *vectorData;
	IOInterruptState state;

	interruptSources = nub->_interruptSources;
	vectorData = interruptSources[source].vectorData;
	vectorNumber = *(long *)vectorData->getBytesNoCopy();

	res = super::registerInterrupt(nub, source, target, handler, refCon);
	if (res)
		return (res);

	// XXX: need to lock?

	state = IOSimpleLockLockDisableInterrupt( _interruptLock );

	if (_interruptState[vectorNumber] == kIOPICNotRegistered) {
		// note that we should only do this once, if it has
		// previously been registered we should not
		// set this to register state
		setState(vectorNumber, kIOPICRegistered);
	}

	IOSimpleLockUnlockEnableInterrupt( _interruptLock , state);

	return (res);
}

// unregister hook
IOReturn Apple8259PIC::unregisterInterrupt(IOService *nub, int source)
{
	IOReturn	res;
	IOInterruptSource *interruptSources;
	long              vectorNumber;
	OSData            *vectorData;
	IOInterruptState   state; 

	interruptSources = nub->_interruptSources;
	vectorData = interruptSources[source].vectorData;
	vectorNumber = *(long *)vectorData->getBytesNoCopy();

	res = super::unregisterInterrupt(nub, source);
	if (res)
		return (res);

	// XXX: need to lock?
	state = IOSimpleLockLockDisableInterrupt( _interruptLock );
	setState(vectorNumber, kIOPICNotRegistered);	
	IOSimpleLockUnlockEnableInterrupt( _interruptLock , state);

	return (res);
}

#endif

bool Apple8259PIC::start( IOService * provider )
{
    IOInterruptAction handler;
    const OSSymbol *  name;


#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start starting\n");
    //L4_KDB_Enter("blah");
#endif
#ifndef L4IOKIT
    if ( super::start(provider) == false ) return false;
#else
    if ( super::start(provider) == false ) {
	//IOLog("Apple8259PIC::start super::start(provider) returns false!\n");
	//L4_KDB_Enter("oops");
	return false;
    }
#endif	/* L4IOKIT */

    _handleSleepWakeFunction = OSSymbol::withCString(
                               kHandleSleepWakeFunction );
#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start _handleSleepWakeFunction %x\n",
//	_handleSleepWakeFunction);
    //L4_KDB_Enter("blah");
#endif
    if (!_handleSleepWakeFunction) return false;

    _interruptLock = IOSimpleLockAlloc();
#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start _interruptLock %p\n", _interruptLock);
    //L4_KDB_Enter("blah");
#endif
    if (!_interruptLock) return false;

    // Allocate the memory for the vectors

    vectors = IONew( IOInterruptVector, kNumVectors );
#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start vectors %p\n", vectors);
    //L4_KDB_Enter("blah");
#endif
    if ( 0 == vectors ) return false;

    bzero( vectors, sizeof(IOInterruptVector) * kNumVectors );

    // Allocate locks for the vectors

    for ( int cnt = 0; cnt < kNumVectors; cnt++ )
    {
        vectors[cnt].interruptLock = IOLockAlloc();
#ifdef L4IOKIT
	//IOLog("Apple8259PIC::start vectors[%d].interruptLock %p\n", cnt, 
	//	vectors[cnt].interruptLock);
	//L4_KDB_Enter("blah");
#endif
        if ( 0 == vectors[cnt].interruptLock )
            return false;
    }

    // Mask all interrupts except for the cascade line

    _interruptMasks = 0xffff & ~(1 << kPICSlaveID);

    // Initialize master PIC

    initializePIC( kPIC1BasePort,
      /* ICW1 */   kPIC_ICW1_IC4,
      /* ICW2 */   kBaseIOInterruptVectors,
      /* ICW3 */   (1 << kPICSlaveID),
      /* ICW4 */   kPIC_ICW4_uPM );

    // Write to OCW1, OCW3, OCW2
    // The priority order is changed to (highest to lowest)
    // 3 4 5 6 7 0 1 2
    // The default priority after initialization is (highest to lowest)
    // 0 1 2 3 4 5 6 7

#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC1BasePort), _interruptMasks & 0xff );
    outb( kPIC_OCW3(kPIC1BasePort), kPIC_OCW3_MBO | kPIC_OCW3_RR );
    outb( kPIC_OCW2(kPIC1BasePort), kPIC_OCW2_R   |
                                    kPIC_OCW2_SL  |
                                    kPIC_OCW2_LEVEL(2) );
#endif
    
    // Initialize slave PIC

    initializePIC( kPIC2BasePort,
      /* ICW1 */   kPIC_ICW1_IC4,
      /* ICW2 */   kBaseIOInterruptVectors + 8,
      /* ICW3 */   kPICSlaveID,
      /* ICW4 */   kPIC_ICW4_uPM );

    // Write to OCW1, and OCW3

#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC2BasePort), _interruptMasks >> 8 );
    outb( kPIC_OCW3(kPIC2BasePort), kPIC_OCW3_MBO | kPIC_OCW3_RR );
#endif
    // Save the trigger type register setup by the BIOS

#ifdef L4IOKIT
    // Is this OK?  To do an inb like this?
#endif
#ifndef L4IOKIT
    _interruptTriggerTypes = inb( kPIC1TriggerTypePort ) |
                           ( inb( kPIC2TriggerTypePort ) << 8 );
#endif

    // Platform driver may wait on the PIC

#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start registering service\n");
    //L4_KDB_Enter("blah");
#endif
    registerService();

    // Primary interrupt controller

#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start setCPUInterruptProperties\n");
    //L4_KDB_Enter("blah");
#endif
    getPlatform()->setCPUInterruptProperties( provider );

    // Register the interrupt handler function so it can service interrupts.

    handler = getInterruptHandlerAddress();
#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start handler is %p\n", handler);
    //L4_KDB_Enter("blah");
#endif
    if ( provider->registerInterrupt(0, this, handler, 0) != kIOReturnSuccess )
#ifdef L4IOKIT
    {
	//IOLog("8259-PIC: registerInterrupt failed\n");
	//L4_KDB_Enter("oops");
#endif
        IOPanic("8259-PIC: registerInterrupt failed");
#ifdef L4IOKIT
    }
#endif

#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start enabling cpu interrupts\n");
    //L4_KDB_Enter("blah");
#endif
#ifndef L4IOKIT	// nope: that is the timer source.
    provider->enableInterrupt(0);
#endif

    // Register this interrupt controller so clients can find it.
    // Get the interrupt controller name from the provider's properties.

    name = OSSymbol::withString( (OSString *)
                     provider->getProperty(kInterruptControllerNameKey) );
    if ( 0 == name )
    {
        IOLog("8259-PIC: no interrupt controller name\n");
#ifdef L4IOKIT
	//L4_KDB_Enter("badness");
#endif
        return false;
    }

    getPlatform()->registerInterruptController( (OSSymbol *) name, this );
    name->release();

#ifdef L4IOKIT
    //IOLog("Apple8259PIC::start returned ok!\n");
    //L4_KDB_Enter("blah");
#endif
    return true;
}

//---------------------------------------------------------------------------
// Free the interrupt controller object. Deallocate all resources.

void Apple8259PIC::free( void )
{
    if ( vectors )
    {
        for ( int cnt = 0; cnt < kNumVectors; cnt++ )
        {
            if (vectors[cnt].interruptLock)
                IOLockFree(vectors[cnt].interruptLock);
        }
        IODelete( vectors, IOInterruptVector, kNumVectors );
        vectors = 0;
    }

    if ( _handleSleepWakeFunction )
    {
        _handleSleepWakeFunction->release();
        _handleSleepWakeFunction = 0;
    }

    if ( _interruptLock )
    {
        IOSimpleLockFree( _interruptLock );
        _interruptLock = 0;
    }

    super::free();
}

//---------------------------------------------------------------------------
// Initialize the PIC by sending the Initialization Command Words (ICW).

void Apple8259PIC::initializePIC( UInt16 port,
                                  UInt8  icw1, UInt8 icw2,
                                  UInt8  icw3, UInt8 icw4 )
{
    // Initialize 8259's. Start the initialization sequence by
    // issuing ICW1 (Initialization Command Word 1).
    // Bit 4 must be set.

#ifndef L4IOKIT
    outb( kPIC_ICW1(port), kPIC_ICW1_MBO | icw1 );

    // ICW2
    // Upper 5 bits of the interrupt vector address. The lower three
    // bits are set according to the interrupt level serviced.

    outb( kPIC_ICW2(port), icw2 );

    // ICW3 (Master Device)
    // Set a 1 bit for each IR line that has a slave.

    outb( kPIC_ICW3(port), icw3 );

    // ICW4

    outb( kPIC_ICW4(port), icw4 );
#endif
}

//---------------------------------------------------------------------------
// Report whether the interrupt line is edge or level triggered.

int Apple8259PIC::getVectorType( long vectorNumber,
                                 IOInterruptVector * vector )
{
#ifndef L4IOKIT
    if (_interruptTriggerTypes & (1 << vectorNumber))
        return kIOInterruptTypeLevel;
    else
        return kIOInterruptTypeEdge;
#else	/* XXX l4iokit: all the world's at level! */
        return kIOInterruptTypeLevel;
#endif
}

IOReturn Apple8259PIC::getInterruptType( IOService * nub,
                                         int         source,
                                         int *       interruptType )
{
    IOInterruptSource * interruptSources;
    OSData            * vectorData;
  
    if (!nub || !interruptType)
    {
        return kIOReturnBadArgument;
    }

    interruptSources = nub->_interruptSources;
    vectorData = interruptSources[source].vectorData;

    if (vectorData->getLength() < sizeof(UInt64))
    {
        // On legacy platforms, report the default trigger type
        // configured by the BIOS.

        UInt32 vectorNumber = DATA_TO_VECTOR(vectorData);
        *interruptType = getVectorType(vectorNumber, 0);
    }
    else
    {
        // On ACPI platforms, report the proposed interrupt trigger
        // type configured by the platform driver, which has not yet
        // been applied to the hardware. The latter will happen when
        // the interrupt is registered and our initVector() function
        // is called. IOInterruptEventSource will grab the interrupt
        // type first and then register an interrupt handler.

        UInt32 vectorFlags = DATA_TO_FLAGS(vectorData);
        *interruptType = ((vectorFlags & kInterruptTriggerModeMask) ==
                           kInterruptTriggerModeEdge) ?
                         kIOInterruptTypeEdge : kIOInterruptTypeLevel;
    }

    APIC_LOG("PIC: %s( %s, %d ) = %s (vector %ld)\n",
             __FUNCTION__,
             nub->getName(), source,
             *interruptType == kIOInterruptTypeLevel ? "level" : "edge",
             DATA_TO_VECTOR(vectorData));

    return kIOReturnSuccess;
}

//---------------------------------------------------------------------------

IOReturn Apple8259PIC::setVectorType( long vectorNumber, long vectorType )
{
    IOInterruptState state;

    if ( vectorNumber >= kNumVectors || vectorNumber == kPICSlaveID ||
         ( vectorType != kIOInterruptTypeLevel &&
           vectorType != kIOInterruptTypeEdge ) )
    {
        return kIOReturnBadArgument;
    }

    state = IOSimpleLockLockDisableInterrupt( _interruptLock );

    if ( vectorType == kIOInterruptTypeLevel )
        _interruptTriggerTypes |= ( 1 << vectorNumber );
    else
        _interruptTriggerTypes &= ~( 1 << vectorNumber );        

#ifdef L4IOKIT
    // Err, no.  No outb like this.
#endif
#ifndef L4IOKIT
    outb( kPIC1TriggerTypePort, (UInt8) _interruptTriggerTypes );
    outb( kPIC2TriggerTypePort, (UInt8)(_interruptTriggerTypes >> 8));
#endif

    IOSimpleLockUnlockEnableInterrupt( _interruptLock, state );

    return kIOReturnSuccess;
}

//---------------------------------------------------------------------------

IOInterruptAction Apple8259PIC::getInterruptHandlerAddress( void )
{
#ifndef L4IOKIT
    return (IOInterruptAction) &Apple8259PIC::handleInterrupt;
#else
    return OSMemberFunctionCast(IOInterruptAction, this,
	&Apple8259PIC::handleInterrupt);
#endif
}

//---------------------------------------------------------------------------
// Handle an interrupt by servicing the 8259, and dispatch the
// handler associated with the interrupt vector.

IOReturn Apple8259PIC::handleInterrupt( void *      savedState,
                                        IOService * nub,
                                        int         source )
{
    IOInterruptVector * vector;
    long                vectorNumber;
    long                level;
    void *              refCon;

#ifdef L4IOKIT
    vectorNumber = source;
#else
    vectorNumber = source - kBaseIOInterruptVectors;
#endif


#ifdef L4IOKIT
    //IOLog("Apple8259PIC::handleInterrupt savedState %p nub %p source %d\n",
	//savedState, nub, source);
#endif

    if (vectorNumber < 0 || vectorNumber >= kNumVectors)
        return kIOReturnSuccess;

#ifndef L4IOKIT
    level = (_interruptTriggerTypes & (1 << vectorNumber));
#else
    level = 1;	// hack
#endif
    if (0 == level) ackInterrupt( vectorNumber );

    vector = &vectors[ vectorNumber ];

    // AppleIntelClock needs interrupt state.
    refCon = ((vectorNumber == 0) ? savedState : vector->refCon);

    vector->interruptActive = 1;

#ifdef L4IOKIT
    //IOLog("Apple8259PIC::handleInterrupt %d %d\n",
//	vector->interruptDisabledSoft, vector->interruptRegistered);
#endif
    if ( !vector->interruptDisabledSoft && vector->interruptRegistered )
    {
#ifdef L4IOKIT
#if 0
	IOLog("Apple8259PIC::handleInterrupt %p %p %p %p %x\n",
		vector->handler, vector->target, refCon, vector->nub, 
		vector->source);
#endif
#endif
        vector->handler( vector->target, refCon,
                         vector->nub,    vector->source );

        // interruptDisabledSoft flag may be set by the
        // vector handler to indicate that the interrupt
        // should now be disabled.

        if ( vector->interruptDisabledSoft )
        {
            vector->interruptDisabledHard = 1;
            disableVectorHard( vectorNumber, vector );
        }
    }
    else
    {
        vector->interruptDisabledHard = 1;
        disableVectorHard( vectorNumber, vector );
    }

    if (level) ackInterrupt( vectorNumber );

    vector->interruptActive = 0;
        
    return kIOReturnSuccess;
}

//---------------------------------------------------------------------------

bool Apple8259PIC::vectorCanBeShared( long vectorNumber,
                                      IOInterruptVector * vector )
{
    if (getVectorType(vectorNumber, vector) == kIOInterruptTypeLevel)
        return true;   // level-triggered
    else
        return false;  // edge-triggered
}

//---------------------------------------------------------------------------

void Apple8259PIC::initVector( long vectorNumber,
                               IOInterruptVector * vector )
{
    IOInterruptSource * interruptSources;
    UInt32              vectorFlags;
    OSData *            vectorData;

    // Get the vector flags assigned by the platform driver.
    // Unlike the APIC driver, the PIC driver can be loaded
    // on a non-ACPI platform driver, which does not report
    // any vector flags.

    interruptSources = vector->nub->_interruptSources;
    vectorData = interruptSources[vector->source].vectorData;
    if (vectorData->getLength() >= sizeof(UInt64))
    {
        vectorFlags = DATA_TO_FLAGS( vectorData );

        if ((vectorFlags & kInterruptTriggerModeMask) ==
             kInterruptTriggerModeEdge)
            setVectorType(vectorNumber, kIOInterruptTypeEdge);
        else
            setVectorType(vectorNumber, kIOInterruptTypeLevel);
    }
}

//---------------------------------------------------------------------------

void Apple8259PIC::disableVectorHard( long vectorNumber,
                                      IOInterruptVector * vector )
{
    IOInterruptState state;

    // cacade/slave interrupt line cannot be disable
    if ( vectorNumber == kPICSlaveID ) return;

    state = IOSimpleLockLockDisableInterrupt( _interruptLock );
    disableInterrupt( vectorNumber );
    IOSimpleLockUnlockEnableInterrupt( _interruptLock, state );
}

//---------------------------------------------------------------------------

void Apple8259PIC::enableVector( long vectorNumber,
                                 IOInterruptVector * vector )
{
    IOInterruptState state;
    state = IOSimpleLockLockDisableInterrupt( _interruptLock );
    enableInterrupt( vectorNumber );
    IOSimpleLockUnlockEnableInterrupt( _interruptLock, state );
}

//---------------------------------------------------------------------------

void Apple8259PIC::prepareForSleep( void )
{
    // Mask all interrupts. Don't assume that the IRQ lines will remain
    // masked on wake. See comment in resumeFromSleep().
#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC2BasePort), 0xff );
    outb( kPIC_OCW1(kPIC1BasePort), 0xff );
#endif
}

//---------------------------------------------------------------------------

void Apple8259PIC::resumeFromSleep( void )
{
    // Masking all interrupts again on wake is not simply paranoia,
    // it is absolutely required for some machines such as Dell C610.
    // Observed that all IRQ lines came up unmasked on wake (BIOS ?).
    // IRQ 0 and IRQ 1 (Timer, PS/2 Keyboard) interrupts still comes
    // through,  but no other interrupts are dispatched for service,
    // including SCI at IRQ 9, IRQ 14/15, and PCI at IRQ 11. Masking
    // all lines again seems to reset the interrupt trigger logic.
#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC2BasePort), 0xff );
    outb( kPIC_OCW1(kPIC1BasePort), 0xff );

    // Restore trigger type registers.

    outb( kPIC1TriggerTypePort, (UInt8) _interruptTriggerTypes );
    outb( kPIC2TriggerTypePort, (UInt8)(_interruptTriggerTypes >> 8));
#endif
    // Initialize master PIC.

    initializePIC( kPIC1BasePort,
      /* ICW1 */   kPIC_ICW1_IC4,
      /* ICW2 */   kBaseIOInterruptVectors,
      /* ICW3 */   (1 << kPICSlaveID),
      /* ICW4 */   kPIC_ICW4_uPM );

    // Write to OCW1, OCW3, OCW2.
    // The priority order is changed to (highest to lowest)
    // 3 4 5 6 7 0 1 2
    // The default priority after initialization is (highest to lowest)
    // 0 1 2 3 4 5 6 7
#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC1BasePort), _interruptMasks & 0xff );
    outb( kPIC_OCW3(kPIC1BasePort), kPIC_OCW3_MBO | kPIC_OCW3_RR );
    outb( kPIC_OCW2(kPIC1BasePort), kPIC_OCW2_R   |
                                    kPIC_OCW2_SL  |
                                    kPIC_OCW2_LEVEL(2) );
#endif
    
    // Initialize slave PIC.

    initializePIC( kPIC2BasePort,
      /* ICW1 */   kPIC_ICW1_IC4,
      /* ICW2 */   kBaseIOInterruptVectors + 8,
      /* ICW3 */   kPICSlaveID,
      /* ICW4 */   kPIC_ICW4_uPM );

    // Write to OCW1, and OCW3.

#ifndef L4IOKIT
    outb( kPIC_OCW1(kPIC2BasePort), _interruptMasks >> 8 );
    outb( kPIC_OCW3(kPIC2BasePort), kPIC_OCW3_MBO | kPIC_OCW3_RR );
#endif
}

//---------------------------------------------------------------------------

IOReturn Apple8259PIC::callPlatformFunction( const OSSymbol * function,
                                             bool   waitForFunction,
                                             void * param1, void * param2,
                                             void * param3, void * param4 )
{
    if ( function == _handleSleepWakeFunction )
    {
        if ( param1 )
            prepareForSleep();   /* prior to system sleep */
        else
            resumeFromSleep();   /* after system wake */

        return kIOReturnSuccess;
    }

    return super::callPlatformFunction( function, waitForFunction,
                                        param1, param2, param3, param4 );
}

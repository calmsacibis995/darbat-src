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

#ifndef _IOKIT_APPLE8259PIC_H
#define _IOKIT_APPLE8259PIC_H

#ifdef L4IOKIT
#include <l4/kdebug.h>
#include <l4/ipc.h>		/* ackInterrupt L4 glue */
#include <xnucompat.h>
#endif

#include <IOKit/IOInterrupts.h>
#include <IOKit/IOInterruptController.h>
#include <libkern/c++/OSContainers.h>

#define kClockIRQ              0

#define kPIC1BasePort          0x20
#define kPIC2BasePort          0xa0

#define kPIC1TriggerTypePort   0x4d0
#define kPIC2TriggerTypePort   0x4d1

#define kPICCmdPortOffset      0
#define kPICDataPortOffset     1

#define kEOICommand            0x20

#define kPICSlaveID            2       // Slave ID for second PIC

#ifdef L4IOKIT
// should be sync'ed with kSystemIRQCount!!  fuckers
#define kNumVectors		24
#else
#define kNumVectors            16
#endif

#define IS_SLAVE_VECTOR(x)     ((x) & 8)

// ICW1
//
#define kPIC_ICW1(x)           ((x) + kPICCmdPortOffset)
#define kPIC_ICW1_MBO          0x10    // must be one
#define kPIC_ICW1_LTIM         0x08    // level/edge triggered mode
#define kPIC_ICW1_ADI          0x04    // 4/8 byte call address interval
#define kPIC_ICW1_SNGL         0x02    // single/cascade mode
#define kPIC_ICW1_IC4          0x01    // ICW4 needed/not needed

// ICW2 - Interrupt vector address (bits 7 - 3).
//
#define kPIC_ICW2(x)           ((x) + kPICDataPortOffset)

// ICW3 - Slave device.
//
#define kPIC_ICW3(x)           ((x) + kPICDataPortOffset)

// ICW4
//
#define kPIC_ICW4(x)           ((x) + kPICDataPortOffset)
#define kPIC_ICW4_SFNM         0x10    // special fully nested mode
#define kPIC_ICW4_BUF          0x08    // buffered mode
#define kPIC_ICW4_MS           0x04    // master/slave
#define kPIC_ICW4_AEOI         0x02    // automatic end of interrupt mode
#define kPIC_ICW4_uPM          0x01    // 8088 (vs. 8085) operation

// OCW1 - Interrupt mask.
//
#define kPIC_OCW1(x)           ((x) + kPICDataPortOffset)

// OCW2 - Bit 4 must be zero.
//
#define kPIC_OCW2(x)           ((x) + kPICCmdPortOffset)
#define kPIC_OCW2_R            0x80    // rotation
#define kPIC_OCW2_SL           0x40    // specific
#define kPIC_OCW2_EOI          0x20
#define kPIC_OCW2_LEVEL(x)     ((x) & 0x07)

// OCW3 - Bit 4 must be zero.
//
#define kPIC_OCW3(x)           ((x) + kPICCmdPortOffset)
#define kPIC_OCW3_ESMM         0x40    // special mask mode
#define kPIC_OCW3_SMM          0x20
#define kPIC_OCW3_MBO          0x08    // must be one
#define kPIC_OCW3_P            0x04    // poll
#define kPIC_OCW3_RR           0x02
#define kPIC_OCW3_RIS          0x01

static __inline__ UInt8 inb( UInt16 port )
{
    UInt8 data;
    __asm__ volatile ( "inb %1, %0"
                     : "=a" (data)
                     : "d" (port));
    return data;
}

static __inline__ void outb( UInt16 port, UInt8 data )
{
    __asm__ volatile ( "outb %1, %0"
                     : /* no output */
                     : "d" (port), "a" (data));
}

#define Apple8259PIC Apple8259PICInterruptController

#ifdef L4IOKIT
// Each interrupt line can be in 4 states.  The states are exclusive and
// a line cannot be in more than one state at a time.  Each line starts off
// as kIOPICNotRegistered.  This means that the interrupt is not registered
// with anything.  When the kIOPICRegister bit is set, it means that someone
// has requested that this interrupt be registered with the I/O Kit.  The
// kIOPICEnable happens when the enableVector() method is called.  For
// an L4 emulation PIC, this basically means calling AssociateInterrupt(),
// that is, registering the interrupt with the kernel and unmasking it
// all in one go.  Since L4 will mask off the interrupt when the interrupt
// is delivered, this probably best resembles level-triggered interrupts.
// As such, the L4 emulation PIC pretends all interrupts are level-triggered,
// even though they are not.  This has the nice advantage that the interrupts
// will be disabled by the I/O Kit automatically.  (Since for level, the 
// interrupt line is held until it is reset by say, reading the status
// register on the interrupting device.
//
// After this step, the state will alternate between
// kIOPICEnabled, kIOPICInInterrupt, KIOPICDisabled and kIOPICQueued.
//
// the interrupt may be disabled by calling disableVectorHard().  If
// the disableVectorHard() method was called because an interrupt was
// raised, it transitions into the kIPICInInterrupt state.  Otherwise,
// it transitions into the kIOPICDisabled state.  A subsequent enabling
// of the interrupt with enableVector() is handled as follows.  If the
// state is previously kIOPICDisabled, then the enabled state is set 
// without acknowledging the interrupt.  If it was enabled again due
// to a previous disable that was due to an interrupt, then it transitions
// from the kIOInInterrupt state into the kIOEnable state and sends
// a reply ack to L4.
//
// a kIOPICQueued is the same as a disabled, except there is a pending
// interrupt which needs to be acked, because the interrupt cannot
// be serviced while it has been disabled.
//
// the unregisterInterrupt() function will unregister it and reset it
// back to the initial state.  (XXX: should be does not happen now, since
// you cannot unregister interrupts in Iguana.  How miserable.)
//
// things  to think about: the disable() must wait for the completion
// of the hardware interrupt handler before it can disable() it, or
// alternatively if the handler is not running it will prevent the
// handler from running again.   Do we model this correctly?
//
// ml_set_interrupts_enabled() may need fixing.  This diasbles interrupts
// on the local processor.  This means things like thread callouts probably
// won't run (since that relies on the timer tick).  We may end up not
// having to worry about this too much since this only disables interrupts
// on the local processor meaning that if the other processor takes the
// tick this could would be unreliable anyway.

typedef enum {
	kIOPICNotRegistered = 0,
	kIOPICRegistered,
	kIOPICEnabled,
	kIOPICDisabled,
	kIOPICQueued,
	kIOPICInInterrupt
} IOPICState;

#ifdef __cplusplus
extern "C" { 
#include <iguana/hardware.h> 
};
#endif
#endif

class Apple8259PIC : public IOInterruptController
{
    OSDeclareDefaultStructors( Apple8259PICInterruptController );

protected:
#ifdef L4IOKIT
    // XXX: could probably be more compact.
    IOPICState		_interruptState[244];
#endif
    UInt16           _interruptMasks;
    UInt16           _interruptTriggerTypes;
    IOSimpleLock *   _interruptLock;
    const OSSymbol * _handleSleepWakeFunction;
    const OSSymbol * _setVectorTypeFunction;

    inline void writeInterruptMask( long irq )
    {
#ifndef L4IOKIT
        if ( IS_SLAVE_VECTOR(irq) )
            outb( kPIC_OCW1(kPIC2BasePort), _interruptMasks >> 8 );
        else
            outb( kPIC_OCW1(kPIC1BasePort), _interruptMasks & 0xff );
#endif
    }

    inline void disableInterrupt( long irq )
    {
        _interruptMasks |= (1 << irq);
        writeInterruptMask(irq);
#ifdef L4IOKIT
	// the interrupt could be disabled for a number of reasons.
	// but we only want to mark it as in interrupt if we are currently
	// servicing an interrupt.  Otherwise it goes into the disabled
	// state.  This is necessary for things like shared interrupt
	// controllers where the interrupt may be disabled even if there
	// is no interrupt coming in.
	if (vectors[irq].interruptActive)
		setState(irq, kIOPICInInterrupt);
	else
		setState(irq, kIOPICDisabled);
#endif

    }

    inline void enableInterrupt( long irq )
    {
        _interruptMasks &= ~(1 << irq);
        writeInterruptMask(irq);
#ifdef L4IOKIT
	// no need for locking: enableVector() locks for us.
	if (isState(irq, kIOPICRegistered)) {
		// it is registered, and we want to enable it for the first
		// time.  Set the state to enabled and tell the Iguana 
		// server to proxy it for us.
		if (1 != hardware_register_interrupt(l4intrgettid(), irq))
			IOLog("%s: shit: hardware_register_interrupt() "
			    "failed irq %d\n", __func__, (int)irq);
		setState(irq, kIOPICEnabled);
	} else if (isState(irq, kIOPICDisabled)) {
		// was in disabled state.  Simply set the enable bit.
		setState(irq, kIOPICEnabled);
	} else if (isState(irq, kIOPICInInterrupt) ||
	    isState(irq, kIOPICQueued)) {
		// was serving the interrupt.  set the state back to 
		// enable and ack the interrupt.
		//
		// if queued, then we simply ack.  For edge triggered 
		// interrupts we will miss it while for level it will
		// be redelivered which seems to correspond to what
		// the I/O Kit wants us to to do.
		ackL4Interrupt(irq);
		setState(irq, kIOPICEnabled);
	} else {
		// what the hell?
		printBadState(_interruptState[irq], kIOPICEnabled);
	}
#endif
    }

#ifdef L4IOKIT
    inline void ackL4Interrupt( long irq )
    {
	L4_MsgTag_t	tag;
	L4_Msg_t	msg;

	L4_MsgClear(&msg);
	L4_Set_Propagation(&msg.tag);
	L4_MsgLoad(&msg);
	L4_Set_VirtualSender(l4intrgettid());
	tag = L4_Reply(L4_GlobalId((L4_Word_t) irq, 1));
	if (L4_IpcFailed(tag))
		IOLog("Apple8259PIC::enableInterrupt(%d) failed "
		    "code = 0x%lx!\n", (int)irq,(unsigned long)L4_ErrorCode());
    }
#endif

    inline void ackInterrupt( long irq )
    {
#ifndef L4IOKIT
        if ( IS_SLAVE_VECTOR(irq) )
            outb( kPIC_OCW2(kPIC2BasePort), kEOICommand );
        outb( kPIC_OCW2(kPIC1BasePort), kEOICommand );
#endif
#ifdef L4IOKIT
	// we could either be in 3 states if this is called:
	// the enabled state, in which case the interrupt was never
	// supposed to be disabled so we tell the kernel that this is so,
	// or we could be in the disabled state because the disableVectorHard()
	// method was called because we asked for a disable, or we could
	// be in the KIOPICQueued state because it was already disabled but
	// we were delivered an interrupt (which could happen on a 
	// explicit disabling of the interrupt line).  In the latter two
	// cases we can do nothing.
	if (isState(irq, kIOPICEnabled)) {
		// still enabled.  Unmask and tell L4 to go on with processing
		// here.
		// otherwise if this conditional is false then this is a no-op
		ackL4Interrupt(irq);
	}
#endif
    }

    virtual void     initializePIC( UInt16 port,
                                    UInt8 icw1, UInt8 icw2,
                                    UInt8 icw3, UInt8 icw4 );

    virtual void     prepareForSleep( void );

    virtual void     resumeFromSleep( void );

    virtual IOReturn setVectorType( long vectorNumber, long type );

    virtual void     free( void );

public:
#ifdef L4IOKIT
  virtual IOReturn registerInterrupt(IOService *nub, int source,
                                     void *target,
                                     IOInterruptHandler handler,
                                     void *refCon);
  virtual IOReturn unregisterInterrupt(IOService *nub, int source);
// XXX: maybe we should return the previous state????
// XXX: the state functions should probably be private??
   virtual void setState(long irq, IOPICState state);
   virtual bool isState(long irq, IOPICState state);
   virtual void printBadState(IOPICState prevState, IOPICState nextState);
#endif
    virtual bool     start( IOService * provider );

    virtual IOReturn getInterruptType( IOService * nub,
                                       int   source,
                                       int * interruptType );

    virtual int      getVectorType( long vectorNumber,
                                    IOInterruptVector * vector);

    virtual IOInterruptAction getInterruptHandlerAddress( void );

    virtual IOReturn handleInterrupt( void * refCon,
                                      IOService * nub,
                                      int source );

    virtual bool     vectorCanBeShared( long vectorNumber,
                                        IOInterruptVector * vector );

    virtual void     initVector( long vectorNumber,
                                 IOInterruptVector * vector );

    virtual void     disableVectorHard( long vectorNumber,
                                        IOInterruptVector * vector );

    virtual void     enableVector( long vectorNumber,
                                   IOInterruptVector * vector );

    virtual IOReturn callPlatformFunction( const OSSymbol * function,
                                           bool waitForFunction,
                                           void * param1, void * param2,
                                           void * param3, void * param4 );
};

#endif /* !_IOKIT_APPLE8259PIC_H */

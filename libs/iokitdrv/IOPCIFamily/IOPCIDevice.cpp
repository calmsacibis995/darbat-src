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
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved. 
 *
 * HISTORY
 * 23 Nov 98 sdouglas created from objc version.
 */

#include <IOKit/system.h>

#include <IOKit/pci/IOPCIBridge.h>
#include <IOKit/pci/IOPCIPrivate.h>
#include <IOKit/pci/IOAGPDevice.h>
#include <IOKit/IOPlatformExpert.h>

#include <IOKit/IOLib.h>
#include <IOKit/assert.h>

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

#include <libkern/c++/OSContainers.h>

#define	PMsleepEnabled		reserved->PMsleepEnabled
#define	PMcontrolStatus		reserved->PMcontrolStatus
#define	sleepControlBits	reserved->sleepControlBits

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define super IOService

OSDefineMetaClassAndStructors(IOPCIDevice, IOService)
OSMetaClassDefineReservedUnused(IOPCIDevice,  3);
OSMetaClassDefineReservedUnused(IOPCIDevice,  4);
OSMetaClassDefineReservedUnused(IOPCIDevice,  5);
OSMetaClassDefineReservedUnused(IOPCIDevice,  6);
OSMetaClassDefineReservedUnused(IOPCIDevice,  7);
OSMetaClassDefineReservedUnused(IOPCIDevice,  8);
OSMetaClassDefineReservedUnused(IOPCIDevice,  9);
OSMetaClassDefineReservedUnused(IOPCIDevice, 10);
OSMetaClassDefineReservedUnused(IOPCIDevice, 11);
OSMetaClassDefineReservedUnused(IOPCIDevice, 12);
OSMetaClassDefineReservedUnused(IOPCIDevice, 13);
OSMetaClassDefineReservedUnused(IOPCIDevice, 14);
OSMetaClassDefineReservedUnused(IOPCIDevice, 15);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static IOPMPowerState powerStates[ kIOPCIDevicePowerStateCount ] = {
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, IOPMSoftSleep, IOPMSoftSleep, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, IOPMPowerOn, IOPMPowerOn, 0, 0, 0, 0, 0, 0, 0, 0 }
        };


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// attach
//
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool IOPCIDevice::attach( IOService * provider )
{
    // initialize superclass variables
    PMinit();
    // register as controlling driver
    registerPowerDriver( this, (IOPMPowerState *) powerStates,
                         kIOPCIDevicePowerStateCount );
    // join the tree
    provider->joinPMtree( this);

#if 0
    // clamp power on if this is a slot device
    slotNameProperty = provider->getProperty ("AAPL,slot-name");
    if (slotNameProperty != NULL)
        changePowerStateToPriv (1);
#endif

    return super::attach(provider);
}

void IOPCIDevice::detach( IOService * provider )
{
    PMstop();
    return super::detach(provider);
}

bool 
IOPCIDevice::init(OSDictionary * propTable)
{
    if (!super::init(propTable))  return false;
    
    // allocate our expansion data
    if (!reserved)
    {
	reserved = IONew(ExpansionData, 1);
	if (!reserved)
	    return false;
	bzero(reserved, sizeof(ExpansionData));
    }
    
    return true;
}


bool IOPCIDevice::init( IORegistryEntry * from, const IORegistryPlane * inPlane )
{
    if (!super::init(from, inPlane))  return false;

    // allocate our expansion data
    if (!reserved)
    {
	reserved = IONew(ExpansionData, 1);
	if (!reserved)
	    return false;
	bzero(reserved, sizeof(ExpansionData));
    }
    
    return true;
}


void IOPCIDevice::free()
{
    if (savedConfig)
    {
	IODelete(savedConfig, UInt32, kIOPCIConfigShadowSize);
	savedConfig = 0;
    }
    //  This needs to be the LAST thing we do, as it disposes of our "fake" member
    //  variables.
    //
    if (reserved)
	IODelete(reserved, ExpansionData, 1);

    super::free();
}

#define DEBUG_PCI_PWR_MGMT 0

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// setPowerState
//
// Saves and restores PCI config space if power is going down or up.
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOReturn IOPCIDevice::setPowerState( unsigned long powerState,
                                     IOService * whatDevice )
{
#if DEBUG_PCI_PWR_MGMT
    IOLog("%s[%p]::setPowerState(%d, %p)\n", getName(), this, (int)powerState, whatDevice);
#endif
    
    switch (powerState) {
	case kIOPCIDeviceOffState:
	    parent->setDevicePowerState( this, 0 );
	    if (PMsleepEnabled && PMcontrolStatus && sleepControlBits)
	    {
#if DEBUG_PCI_PWR_MGMT
		IOLog("%s[%p]::setPowerState(OFF) - setting PMCS to %x\n", getName(), this, sleepControlBits);
#endif
		configWrite16(PMcontrolStatus, sleepControlBits);
	    }
	    break;
	    
	case kIOPCIDeviceDozeState:
	    if (PMsleepEnabled && PMcontrolStatus && sleepControlBits)
	    {
		if ((configRead16(PMcontrolStatus) & kPCIPMCSPowerStateMask) != kPCIPMCSPowerStateD0)
		{
#if DEBUG_PCI_PWR_MGMT
		    IOLog("%s[%p]::setPowerState(DOZE) - moving PMCS from %x to D0 and restoring registers\n", getName(), this, configRead16(PMcontrolStatus));
#endif
		    configWrite16(PMcontrolStatus, kPCIPMCSPMEStatus | kPCIPMCSPowerStateD0);
		    parent->setDevicePowerState( this, 1 );
		}
		else
		{
#if DEBUG_PCI_PWR_MGMT
		    IOLog("%s[%p]::setPowerState(DOZE) - PMCS already at D0 (%x)\n", getName(), this, configRead16(PMcontrolStatus));
#endif
		}
	    }
	    break;
	    
	case kIOPCIDeviceOnState:
	    if (PMsleepEnabled && PMcontrolStatus && sleepControlBits)
		if ((configRead16(PMcontrolStatus) & kPCIPMCSPowerStateMask) != kPCIPMCSPowerStateD0)
		{
#if DEBUG_PCI_PWR_MGMT
		    IOLog("%s[%p]::setPowerState(ON) - moving PMCS from %x to D0\n", getName(), this, configRead16(PMcontrolStatus));
#endif
		    configWrite16(PMcontrolStatus, kPCIPMCSPMEStatus | kPCIPMCSPowerStateD0);
		}
		else
		{
#if DEBUG_PCI_PWR_MGMT
		    IOLog("%s[%p]::setPowerState(ON) - PMCS already at D0 (%x)\n", getName(), this, configRead16(PMcontrolStatus));
#endif
		    configWrite16(PMcontrolStatus, kPCIPMCSPMEStatus);
		}
	    parent->setDevicePowerState( this, 1 );
	    break;
	    
    }
    
    return IOPMAckImplied;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool IOPCIDevice::matchPropertyTable( OSDictionary * table, SInt32 * score )
{
    return (parent->matchNubWithPropertyTable(this, table, score));
}

bool IOPCIDevice::compareName( OSString * name, OSString ** matched ) const
{
    return (parent->compareNubName(this, name, matched));
}

IOReturn IOPCIDevice::getResources( void )
{
    return (parent->getNubResources(this));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

UInt32 IOPCIDevice::configRead32( IOPCIAddressSpace _space,
                                  UInt8 offset )
{
    return (parent->configRead32(_space, offset));
}

void IOPCIDevice::configWrite32( IOPCIAddressSpace _space,
                                 UInt8 offset, UInt32 data )
{
    parent->configWrite32( _space, offset, data );
}

UInt16 IOPCIDevice::configRead16( IOPCIAddressSpace _space,
                                  UInt8 offset )
{
    return (parent->configRead16(_space, offset));
}

void IOPCIDevice::configWrite16( IOPCIAddressSpace _space,
                                 UInt8 offset, UInt16 data )
{
    parent->configWrite16( _space, offset, data );
}

UInt8 IOPCIDevice::configRead8( IOPCIAddressSpace _space,
                                UInt8 offset )
{
    return (parent->configRead8(_space, offset));
}

void IOPCIDevice::configWrite8( IOPCIAddressSpace _space,
                                UInt8 offset, UInt8 data )
{
    parent->configWrite8( _space, offset, data );
}

UInt32 IOPCIDevice::configRead32( UInt8 offset )
{
    return (parent->configRead32(space, offset));
}

void IOPCIDevice::configWrite32( UInt8 offset, UInt32 data )
{
    parent->configWrite32( space, offset, data );
}

UInt16 IOPCIDevice::configRead16( UInt8 offset )
{
    return (parent->configRead16(space, offset));
}

void IOPCIDevice::configWrite16( UInt8 offset, UInt16 data )
{
    parent->configWrite16( space, offset, data );
}

UInt8 IOPCIDevice::configRead8( UInt8 offset )
{
    return (parent->configRead8(space, offset));
}

void IOPCIDevice::configWrite8( UInt8 offset, UInt8 data )
{
    parent->configWrite8( space, offset, data );
}

// --

UInt32 IOPCIDevice::extendedConfigRead32( IOByteCount offset )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    return (configRead32(_space, offset));
}

void IOPCIDevice::extendedConfigWrite32( IOByteCount offset, UInt32 data )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    configWrite32(_space, offset, data);
}

UInt16 IOPCIDevice::extendedConfigRead16( IOByteCount offset )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    return (configRead16(_space, offset));
}

void IOPCIDevice::extendedConfigWrite16( IOByteCount offset, UInt16 data )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    configWrite16(_space, offset, data);
}

UInt8 IOPCIDevice::extendedConfigRead8( IOByteCount offset )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    return (configRead8(space, offset));
}

void IOPCIDevice::extendedConfigWrite8( IOByteCount offset, UInt8 data )
{
    IOPCIAddressSpace _space = space;
    _space.es.registerNumExtended = (offset >> 8);

    configWrite8(_space, offset, data);
}

// --

IOReturn IOPCIDevice::saveDeviceState( IOOptionBits options )
{
    return (parent->saveDeviceState(this, options));
}

IOReturn IOPCIDevice::restoreDeviceState( IOOptionBits options )
{
    return (parent->restoreDeviceState(this, options));
}

UInt32 IOPCIDevice::findPCICapability( UInt8 capabilityID, UInt8 * offset )
{
    return (parent->findPCICapability(space, capabilityID, offset));
}

UInt32 IOPCIDevice::extendedFindPCICapability( UInt32 capabilityID, IOByteCount * offset )
{
    return (parent->extendedFindPCICapability(space, capabilityID, offset));
}

UInt32 IOPCIDevice::setConfigBits( UInt8 reg, UInt32 mask, UInt32 value )
{
    UInt32	was;
    UInt32	bits;

    bits = configRead32( reg );
    was = (bits & mask);
    bits &= ~mask;
    bits |= (value & mask);
    configWrite32( reg, bits );

    return (was);
}

bool IOPCIDevice::setBusMasterEnable( bool enable )
{
    return (0 != setConfigBits(kIOPCIConfigCommand, kIOPCICommandBusMaster,
                               enable ? kIOPCICommandBusMaster : 0));
}

bool IOPCIDevice::setMemoryEnable( bool enable )
{
    return (0 != setConfigBits(kIOPCIConfigCommand, kIOPCICommandMemorySpace,
                               enable ? kIOPCICommandMemorySpace : 0));
}

bool IOPCIDevice::setIOEnable( bool enable, bool /* exclusive = false */ )
{
    // exclusive is TODO.
    return (0 != setConfigBits(kIOPCIConfigCommand, kIOPCICommandIOSpace,
                               enable ? kIOPCICommandIOSpace : 0));
}

UInt8 IOPCIDevice::getBusNumber( void )
{
    return (space.s.busNum);
}

UInt8 IOPCIDevice::getDeviceNumber( void )
{
    return (space.s.deviceNum);
}

UInt8 IOPCIDevice::getFunctionNumber( void )
{
    return (space.s.functionNum);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IODeviceMemory * IOPCIDevice::getDeviceMemoryWithRegister( UInt8 reg )
{
    OSArray *		array;
    IODeviceMemory *	range;
    unsigned int	i = 0;

    array = (OSArray *) getProperty( gIODeviceMemoryKey);
#ifdef L4IOKIT
#if 0
    IOLog("IOPCIDevice::getDeviceMemoryWithRegister reg = 0x%lx "
	"array = 0x%lx\n", reg, array);
#endif
#endif
    if (0 == array)
        return (0);

    while ((range = (IODeviceMemory *) array->getObject(i++)))
    {
        if (reg == (range->getTag() & 0xff))
            break;
    }

    return (range);
}

IOMemoryMap * IOPCIDevice:: mapDeviceMemoryWithRegister( UInt8 reg,
        IOOptionBits options )
{
    IODeviceMemory *	range;
    IOMemoryMap *	map;

    range = getDeviceMemoryWithRegister( reg );
#ifdef L4IOKIT
#if 0
    IOLog("IOPCIDevice::mapDeviceMemoryWithRegister reg = 0x%lx "
	"options = 0x%lx result range = 0x%lx\n", reg, options, range);
#endif
#endif
    if (range)
        map = range->map( options );
    else
        map = 0;

    return (map);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IODeviceMemory * IOPCIDevice::ioDeviceMemory( void )
{
    return (parent->ioDeviceMemory());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOService * IOPCIDevice::matchLocation( IOService * /* client */ )
{
    return (this);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSMetaClassDefineReservedUsed(IOPCIDevice,  0);
bool IOPCIDevice::hasPCIPowerManagement(IOOptionBits state)
{
    UInt8	pciPMCapOffset;
    UInt16	pciPMCapReg;
    OSObject	*anObject;
    OSData	*aString;

    sleepControlBits = 0;		// on a new query, we reset the proper sleep control bits
    if (!PMcontrolStatus)
    {
	// need to find out if there is a Pwr Mgmt control/status register
	findPCICapability(kIOPCIPowerManagementCapability, &pciPMCapOffset);
	if (pciPMCapOffset > 0x3f)					// must be > 3f, section 3.1
	{
#if DEBUG_PCI_PWR_MGMT
	    IOLog("%s[%p]::hasPCIPwrMgmt found pciPMCapOffset %d\n", getName(), this, pciPMCapOffset);
#endif
	    pciPMCapReg = configRead16(pciPMCapOffset+2);
#if DEBUG_PCI_PWR_MGMT
	    IOLog("%s[%p]::hasPCIPwrMgmt found pciPMCapReg %x\n", getName(), this, pciPMCapReg);
#endif
	    PMcontrolStatus = pciPMCapOffset+4;
	}
    }
    if (PMcontrolStatus)
    {
	if (state)
	{
	    switch (state) {
		case kPCIPMCPMESupportFromD3Cold:
		case kPCIPMCPMESupportFromD3Hot:
		    sleepControlBits = (kPCIPMCSPMEStatus | kPCIPMCSPMEEnable | kPCIPMCSPowerStateD3);
		    break;
		case kPCIPMCPMESupportFromD2:
		    sleepControlBits = (kPCIPMCSPMEStatus | kPCIPMCSPMEEnable | kPCIPMCSPowerStateD2);
		    break;
		case kPCIPMCPMESupportFromD1:
		    sleepControlBits = (kPCIPMCSPMEStatus | kPCIPMCSPMEEnable | kPCIPMCSPowerStateD1);
		    break;
		case kPCIPMCD3Support:
			sleepControlBits = kPCIPMCSPowerStateD3;
			break;
		default:
		    break;
	    }
	}
	else
	{
	    anObject = getProperty("sleep-power-state");
	    aString = OSDynamicCast(OSData, anObject);
	    if (aString)
	    {
#if DEBUG_PCI_PWR_MGMT
		IOLog("%s[%p]::hasPCIPwrMgmt found sleep-power-state string %p\n", getName(), this, aString);
#endif
    
		if (aString->isEqualTo("D3cold", 6))
		{
		    sleepControlBits = (kPCIPMCSPMEStatus | kPCIPMCSPMEEnable | kPCIPMCSPowerStateD3);
		}
		else if (aString->isEqualTo("D3Hot", 5))
		{
		    sleepControlBits = (kPCIPMCSPMEStatus | kPCIPMCSPMEEnable | kPCIPMCSPowerStateD3);
		}
	    }
	}
	
    }
    return sleepControlBits ? true : false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSMetaClassDefineReservedUsed(IOPCIDevice,  1);
IOReturn IOPCIDevice::enablePCIPowerManagement(IOOptionBits state)
{
    IOReturn	ret = kIOReturnSuccess;
    
    if (!PMcontrolStatus)
	{
		ret = kIOReturnBadArgument;
		return ret;
	}
	
	if ( state == kPCIPMCSPowerStateD0 )
	{
		sleepControlBits = 0;
		PMsleepEnabled = false;
		return ret;
	}
    
    else
	{
		
		UInt32	oldBits = sleepControlBits;
		
		sleepControlBits = state & kPCIPMCSPowerStateMask;
		
		if ( oldBits & kPCIPMCSPMEStatus )
			sleepControlBits |= kPCIPMCSPMEStatus;
		
		if ( oldBits & kPCIPMCSPMEEnable )
			sleepControlBits |= kPCIPMCSPMEEnable;
		
		if (!sleepControlBits)
		{
			
		#if DEBUG_PCI_PWR_MGMT
			IOLog("%s[%p] - enablePCIPwrMgmt - no sleep control bits - not enabling", getName(), this);
		#endif
			ret = kIOReturnBadArgument;
			
		}
		else
		{
		
		#if DEBUG_PCI_PWR_MGMT
			IOLog("%s[%p] - enablePCIPwrMgmt, enabling", getName(), this);
		#endif
			
			PMsleepEnabled = true;
			
		}
		
	}
    return ret;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#undef super
#define super IOPCIDevice

OSDefineMetaClassAndStructors(IOAGPDevice, IOPCIDevice)
OSMetaClassDefineReservedUnused(IOAGPDevice,  0);
OSMetaClassDefineReservedUnused(IOAGPDevice,  1);
OSMetaClassDefineReservedUnused(IOAGPDevice,  2);
OSMetaClassDefineReservedUnused(IOAGPDevice,  3);
OSMetaClassDefineReservedUnused(IOAGPDevice,  4);
OSMetaClassDefineReservedUnused(IOAGPDevice,  5);
OSMetaClassDefineReservedUnused(IOAGPDevice,  6);
OSMetaClassDefineReservedUnused(IOAGPDevice,  7);
OSMetaClassDefineReservedUnused(IOAGPDevice,  8);
OSMetaClassDefineReservedUnused(IOAGPDevice,  9);
OSMetaClassDefineReservedUnused(IOAGPDevice, 10);
OSMetaClassDefineReservedUnused(IOAGPDevice, 11);
OSMetaClassDefineReservedUnused(IOAGPDevice, 12);
OSMetaClassDefineReservedUnused(IOAGPDevice, 13);
OSMetaClassDefineReservedUnused(IOAGPDevice, 14);
OSMetaClassDefineReservedUnused(IOAGPDevice, 15);
OSMetaClassDefineReservedUnused(IOAGPDevice, 16);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOReturn IOAGPDevice::createAGPSpace( IOOptionBits options,
                                      IOPhysicalAddress * address,
                                      IOPhysicalLength * length )
{
    return (parent->createAGPSpace(this, options, address, length));
}

IOReturn IOAGPDevice::destroyAGPSpace( void )
{
    return (parent->destroyAGPSpace(this));
}

IORangeAllocator * IOAGPDevice::getAGPRangeAllocator( void )
{
    return (parent->getAGPRangeAllocator(this));
}

IOOptionBits IOAGPDevice::getAGPStatus( IOOptionBits options )
{
    return (parent->getAGPStatus(this, options));
}

IOReturn IOAGPDevice::resetAGP( IOOptionBits options )
{
    return (parent->resetAGPDevice(this, options));
}

IOReturn IOAGPDevice::getAGPSpace( IOPhysicalAddress * address,
                                   IOPhysicalLength * length )
{
    return (parent->getAGPSpace(this, address, length));
}

IOReturn IOAGPDevice::commitAGPMemory(  IOMemoryDescriptor * memory,
                                        IOByteCount agpOffset,
                                        IOOptionBits options )
{
    return (parent->commitAGPMemory(this, memory, agpOffset, options));
}

IOReturn IOAGPDevice::releaseAGPMemory( IOMemoryDescriptor * memory,
                                        IOByteCount agpOffset,
                                        IOOptionBits options )
{
    return (parent->releaseAGPMemory(this, memory, agpOffset, options));
}


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
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
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
 * L4PCIBridge.cpp
 *
 * Implements PCI Bridge proxying
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */


#include <IOKit/IOLib.h>

#include "L4PCIBridge.h"

#define super IOPCIBridge

UInt32 L4PCIBridge::proxyCall(
	L4_Word_t fn, IOPCIAddressSpace space, UInt8 offset, UInt32 data)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;

	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, fn);
	L4_MsgAppendWord(&msg, space.bits);
	L4_MsgAppendWord(&msg, offset);
	L4_MsgAppendWord(&msg, data);
	L4_MsgLoad(&msg);

	tag = L4_Call(pciBridgeTid);

	assert(L4_IpcSucceeded(tag));

	return L4_MsgWord(&msg, 0);
}

bool L4PCIBridge::init(OSDictionary *propTable)
{
	super::init(propTable);

	do 
		pciBridgeTid.raw = naming_lookup("iokit_tid");
	while (pciBridgeTid.raw == 0);

	return (true);
}

IOReturn L4PCIBridge::setDevicePowerState(
	IOPCIDevice *device, unsigned long whatToDo)
{
	/*
	 * XXX:
	 *
	 * We do not handle any power saving features, for now
	 * anyway.
	 *
	 * I think the right way to do this would be to only let
	 * the device itself change its power state.  Right??
	 */
	assert(device == this);
	return kIOReturnSuccess;
}

bool L4PCIBridge::matchNubWithPropertyTable(
	IOService *nub, OSDictionary *table, SInt32 *score)
{

	return true;
}

#if 0
bool L4PCIBridge::compareNubName (
	IOService *nub, OSString *name, OSString ** matched = 0 )
	const
{
	/*
	 * This is what is in IOPCIBridge.  Do we need to proxy this?
	 *
	 */
	return IODTCompareNubName(this, name, matched);
}
#endif

#if 0
IOReturn L4PCIBridge::getNubResources(IOService *service)
{
	IOPCIDevice	*nub = (IOPCIDevice *)service;
	IOReturn	err;

	/*
	 * Copied from IOPCIBridge.cpp
	 *
	 */
	IOLog("L4PCIBridge::getNubResources called\n");

	if (service->getDeviceMemory())
		return kIOReturnSuccess;

	/*
	 * XXX Proxy this??
	 * 
	 * Though, I think it pobably belongs here or in IOPCIDevice
	 * more than on the bridge.
	 */
	return getNubAddressing(nub);
}

IOReturn L4PCIBridge::getNubAddressing(IOPCIDevice *nub)
{
    OSArray *		array;
    OSData *		assignedProp;
    IOPhysicalAddress	phys;
    IOPhysicalLength	len;
    UInt32		save, value;
    IOPCIAddressSpace	reg;
    UInt8		regNum;
    UInt8       headerType;
    bool		memEna, ioEna;
    boolean_t		s;

    value = nub->configRead32( kIOPCIConfigVendorID );
    if (0x0003106b == value)		// control doesn't play well
        return (kIOReturnSuccess);

    // headers type 0 and 2
    headerType = nub->configRead8( kIOPCIConfigHeaderType ) & 0x7f;
    if (headerType != 0 && headerType != 2)
        return (kIOReturnSuccess);

    array = OSArray::withCapacity( 1 );
    if (0 == array)
        return (kIOReturnNoMemory);
    assignedProp = OSData::withCapacity( 3 * sizeof(IOPCIPhysicalAddress) );
    if (0 == assignedProp)
        return (kIOReturnNoMemory);

    for (regNum = 0x10; regNum < 0x28; regNum += 4)
    {
        // Only look at CardBus socket BAR
        if ( (2 == headerType) && (regNum > 0x10) )
            break;

        // begin scary
        s = ml_set_interrupts_enabled(FALSE);
        memEna = nub->setMemoryEnable( false );
        ioEna = nub->setIOEnable( false );

        save = nub->configRead32( regNum );

        nub->configWrite32( regNum, 0xffffffff );
        value = nub->configRead32( regNum );

        nub->configWrite32( regNum, save );
        nub->setMemoryEnable( memEna );
        nub->setIOEnable( ioEna );
        ml_set_interrupts_enabled( s );
        // end scary

        if (0 == value)
            continue;

        reg = nub->space;
        reg.s.registerNum = regNum;

        if (value & 1)
        {
            reg.s.space = kIOPCIIOSpace;

            // If the upper 16 bits for I/O space
            // are all 0, then we should ignore them.
            if ((value & 0xFFFF0000) == 0)
            {
                value = value | 0xFFFF0000;
            }
        }
        else
        {
            reg.s.prefetch = (0 != (value & 8));

            switch (value & 6)
            {
                case 2: /* below 1Mb */
                    reg.s.t = 1;
                    /* fall thru */
                case 0: /* 32-bit mem */
                case 6:	/* reserved */
                    reg.s.space = kIOPCI32BitMemorySpace;
                    break;

                case 4: /* 64-bit mem */
                    reg.s.space = kIOPCI64BitMemorySpace;
                    regNum += 4;
                    break;
            }
        }

        value &= 0xfffffff0;
        phys = IOPhysical32( 0, save & value );
        len = IOPhysical32( 0, -value );

        if (assignedProp)
        {
            IOPCIPhysicalAddress assigned;
            assigned.physHi = reg;
            assigned.physMid = 0;
            assigned.physLo = phys;
            assigned.lengthHi = 0;
            assigned.lengthLo = len;

            assignedProp->appendBytes( &assigned, sizeof(assigned) );
        }

        if (1 & gIOPCIDebug)
            IOLog("Space %08lx : %08lx, %08lx\n", reg.bits, phys, len);

        constructRange( &reg, phys, len, array );
    }

    if (array->getCount())
        nub->setProperty( gIODeviceMemoryKey, array);
    array->release();

    if (assignedProp->getLength())
        nub->setProperty( "assigned-addresses", assignedProp );
    assignedProp->release();

    return (kIOReturnSuccess);
}
#endif

#if 0
bool IOPCIBridge::matchKeys( IOPCIDevice * nub, const char * keys,
                             UInt32 defaultMask, UInt8 regNum )
{
    const char *	next;
    UInt32		mask, value, reg;
    bool		found = false;

    do
    {
        value = strtoul( keys, (char **) &next, 16);
#ifdef L4IOKIT
	//IOLog("%s::%s value = 0x%lx keys = %s\n", getName(), __FUNCTION__, 
	//	value, keys);
	//L4_KDB_Enter("X");
#endif
        if (next == keys)
            break;

        while ((*next) == ' ')
            next++;

        if ((*next) == '&')
            mask = strtoul( next + 1, (char **) &next, 16);
        else
            mask = defaultMask;

#ifdef L4IOKIT
	//IOLog("%s::%s: reg = 0x%lx mask = 0x%lx\n", 
	//    getName(), __FUNCTION__, reg, mask);
	//L4_KDB_Enter("X");
#endif
        reg = nub->savedConfig[ regNum >> 2 ];
        found = ((value & mask) == (reg & mask));
        keys = next;
    }
    while (!found);

    return (found);
}


bool IOPCIBridge::pciMatchNub( IOPCIDevice * nub,
                               OSDictionary * table,
                               SInt32 * score )
{
    OSString *		prop;
    const char *	keys;
    bool		match = true;
    UInt8		regNum;
    int			i;

#ifdef L4IOKIT
    //IOLog("IOPCIBridge::pciMatchNub\n");
    //L4_KDB_Enter("XXXX");
#endif


}
#endif
/*
 * XXX:
 *
 * could optimize these to do it in its own pd?
 * but if they are not called that often, then it doesn't make sense
 * These would be easy to implement in one's own AS
 */
UInt32 L4PCIBridge::configRead32(IOPCIAddressSpace space, UInt8 offset)
{

	return proxyCall(CONFIGREAD32, space, offset, 0);
}

UInt16 L4PCIBridge::configRead16(IOPCIAddressSpace space, UInt8 offset)
{

	return proxyCall(CONFIGREAD16, space, offset, 0);
}

UInt8 L4PCIBridge::configRead8(IOPCIAddressSpace space, UInt8 offset)
{

	return proxyCall(CONFIGREAD8, space, offset, 0);
}

void L4PCIBridge::configWrite32(
	IOPCIAddressSpace space, UInt8 offset, UInt32 data )
{

	(void)proxyCall(CONFIGWRITE32, space, offset, data);
}

void L4PCIBridge::configWrite16(
	IOPCIAddressSpace space, UInt8 offset, UInt16 data )
{

	(void)proxyCall(CONFIGWRITE16, space, offset, data);
}

void L4PCIBridge::configWrite8 (
	IOPCIAddressSpace space, UInt8 offset, UInt8 data)
{

	(void)proxyCall(CONFIGWRITE8, space, offset, data);
}


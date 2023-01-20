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
 * L4PCIBridge.h
 *
 * Geoffrey Lee <glee at cse.unsw.edu.au>
 */


#include <IOKit/pci/IOPCIBridge.h>

#include <l4/ipc.h>
//#include <naming/naming.h>	c++ bullshit
extern "C" uintptr_t naming_lookup(const char *);

#define CONFIGREAD32	0
#define CONFIGWRITE32	1
#define CONFIGREAD16	2
#define CONFIGWRITE16	3
#define CONFIGREAD8	4
#define CONFIGWRITE8	5

/*
 * This is empty.  It does not implement anything new, but implements a 
 * proxying device (for now, only implement what we * need) to proxy 
 * back to the IOPCIBridge that lives in another pd.
 */
class L4PCIBridge : public IOPCIBridge {

	OSDeclareDefaultStructors(L4PCIBridge)
public:

    virtual UInt32 configRead32( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite32( IOPCIAddressSpace space,
                                        UInt8 offset, UInt32 data );
    virtual UInt16 configRead16( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite16( IOPCIAddressSpace space,
                                        UInt8 offset, UInt16 data );
    virtual UInt8 configRead8( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite8( IOPCIAddressSpace space,
                                        UInt8 offset, UInt8 data );

    bool init(OSDictionary *propTable);
    IOReturn L4PCIBridge::setDevicePowerState(
        IOPCIDevice *device, unsigned long whatToDo);

    UInt32 proxyCall(
		L4_Word_t fn, 
		IOPCIAddressSpace space, 
		UInt8 offset, 
		UInt32 data);

    bool L4PCIBridge::matchNubWithPropertyTable(
        IOService *nub, OSDictionary *table, SInt32 *score);

private:
	L4_ThreadId_t		pciBridgeTid;


};


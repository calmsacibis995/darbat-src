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
 * Copyright (c) 1998 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 *
 */

#ifndef _IOKIT_IODEVICETREE_H
#define _IOKIT_IODEVICETREE_H

#include <IOKit/IORegistryEntry.h>
#include <libkern/c++/OSData.h>

class IODeviceMemory;
class IOService;

extern const IORegistryPlane *	gIODTPlane;

extern const OSSymbol *		gIODTCompatibleKey;
extern const OSSymbol * 	gIODTTypeKey;
extern const OSSymbol * 	gIODTModelKey;

extern const OSSymbol *		gIODTAAPLInterruptsKey;
extern const OSSymbol *		gIODTDefaultInterruptController;
extern const OSSymbol *		gIODTNWInterruptMappingKey;

IORegistryEntry * IODeviceTreeAlloc( void * dtTop );


bool IODTMatchNubWithKeys( IORegistryEntry * nub,
                                    const char * keys );

bool IODTCompareNubName( const IORegistryEntry * regEntry,
			 OSString * name, OSString ** matchingName );

enum {
    kIODTRecursive	= 0x00000001,
    kIODTExclusive	= 0x00000002
};

OSCollectionIterator * IODTFindMatchingEntries( IORegistryEntry * from,
			IOOptionBits options, const char * keys );

typedef SInt32 (*IODTCompareAddressCellFunc)
	(UInt32 cellCount, UInt32 left[], UInt32 right[]);
typedef void (*IODTNVLocationFunc)
	(IORegistryEntry * entry,
	UInt8 * busNum, UInt8 * deviceNum, UInt8 * functionNum );

void IODTSetResolving( IORegistryEntry * 	regEntry,
		IODTCompareAddressCellFunc	compareFunc,
		IODTNVLocationFunc		locationFunc );

bool IODTResolveAddressCell( IORegistryEntry * regEntry,
                             UInt32 cellsIn[],
                             IOPhysicalAddress * phys, IOPhysicalLength * len );

OSArray * IODTResolveAddressing( IORegistryEntry * regEntry,
			const char * addressPropertyName,
			IODeviceMemory * parent );

#pragma options align=mac68k

struct IONVRAMDescriptor {
    unsigned int format:4;
    unsigned int marker:1;
    unsigned int bridgeCount:3;
    unsigned int busNum:2;
    unsigned int bridgeDevices:6 * 5;
    unsigned int functionNum:3;
    unsigned int deviceNum:5;
};

#pragma options align=reset

IOReturn IODTMakeNVDescriptor( IORegistryEntry * regEntry,
				IONVRAMDescriptor * hdr );

OSData * IODTFindSlotName( IORegistryEntry * regEntry, UInt32 deviceNumber );

const OSSymbol * IODTInterruptControllerName(
			IORegistryEntry * regEntry );

bool IODTMapInterrupts( IORegistryEntry * regEntry );

enum {
    kIODTInterruptShared = 0x00000001
};
IOReturn IODTGetInterruptOptions( IORegistryEntry * regEntry, int source, IOOptionBits * options );

#ifdef __cplusplus
extern "C" {
#endif

IOReturn IONDRVLibrariesInitialize( IOService * provider );

#ifdef __cplusplus
}
#endif

#endif /* _IOKIT_IODEVICETREE_H */


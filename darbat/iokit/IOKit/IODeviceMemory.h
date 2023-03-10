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

#ifndef _IOKIT_IODEVICEMEMORY_H
#define _IOKIT_IODEVICEMEMORY_H

#include <IOKit/IOMemoryDescriptor.h>

/*! @class IODeviceMemory
    @abstract An IOMemoryDescriptor used for device physical memory ranges.
    @discussion The IODeviceMemory class is a simple subclass of IOMemoryDescriptor that uses its methods to describe a single range of physical memory on a device. IODeviceMemory objects are usually looked up with IOService or IOPCIDevice accessors, and are created by memory-mapped bus families. IODeviceMemory implements only some factory methods in addition to the methods of IOMemoryDescriptor. 
*/

class IODeviceMemory : public IOMemoryDescriptor
{
    OSDeclareDefaultStructors(IODeviceMemory)

public:

/*! @struct InitElement
    @field start First physical address in the range.
    @field length Length of the range.
    @field tag 32-bit value not interpreted by IODeviceMemory or IOMemoryDescriptor, for use by the bus family. */

    struct InitElement {
        IOPhysicalAddress	start;
        IOPhysicalLength	length;
        IOOptionBits 		tag;
    };

/*! @function arrayFromList
    @abstract Constructs an OSArray of IODeviceMemory instances, each describing one physical range, and a tag value.
    @discussion This method creates IODeviceMemory instances for each physical range passed in an IODeviceMemory::InitElement array. Each element consists of a physical address, length and tag value for the IODeviceMemory. The instances are returned as a created OSArray.
    @param list An array of IODeviceMemory::InitElement structures.
    @param count The number of elements in the list.
    @result Returns a created OSArray of IODeviceMemory objects, to be released by the caller, or zero on failure. */

    static OSArray *		arrayFromList(
	InitElement		list[],
	IOItemCount		count );

/*! @function withRange
    @abstract Constructs an IODeviceMemory instance, describing one physical range.
    @discussion This method creates an IODeviceMemory instance for one physical range passed as a physical address and length. It just calls IOMemoryDescriptor::withPhysicalAddress.
    @param address The physical address of the first byte in the memory.
    @param withLength The length of memory.
    @result Returns the created IODeviceMemory on success, to be released by the caller, or zero on failure. */

    static IODeviceMemory *	withRange( 
	IOPhysicalAddress	start,
	IOPhysicalLength	length );

/*! @function withSubRange
    @abstract Constructs an IODeviceMemory instance, describing a subset of an existing IODeviceMemory range.
    @discussion This method creates an IODeviceMemory instance for a subset of an existing IODeviceMemory range, passed as a physical address offset and length. It just calls IOMemoryDescriptor::withSubRange.
    @param of The parent IODeviceMemory of which a subrange is to be used for the new descriptor, which will be retained by the subrange IODeviceMemory.
    @param offset A byte offset into the parent's memory.
    @param length The length of the subrange.
    @result Returns the created IODeviceMemory on success, to be released by the caller, or zero on failure. */

    static IODeviceMemory *	withSubRange( 
	IODeviceMemory *	of,
	IOPhysicalAddress	offset,
	IOPhysicalLength	length );
};

#endif /* ! _IOKIT_IODEVICEMEMORY_H */

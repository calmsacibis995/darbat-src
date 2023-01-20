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
cc idtest.c -o /tmp/idtest -Wall -framework IOKit -framework CoreFoundation
 */

#include <assert.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOKitKeys.h>

int main(int argc, char **argv)
{
    io_registry_entry_t	   service;
    io_connect_t	   connect;
    SInt32		   id1, id2, id3;
    kern_return_t          status;

    service = IORegistryEntryFromPath(kIOMasterPortDefault, 
				    kIOServicePlane ":/IOResources/IODisplayWrangler");
    assert(service);
    if (service) 
    {
        status = IOServiceOpen(service, mach_task_self(), 0, &connect);
	IOObjectRelease(service);
	assert(kIOReturnSuccess == status);

    }

    enum { kAlloc, kFree };
enum {
    kIOAccelSpecificID		= 0x00000001
};


    status = IOConnectMethodScalarIScalarO(connect, kAlloc, 2, 1, kNilOptions, 0, &id1);
    assert(kIOReturnSuccess == status);
    printf("ID: %x\n", id1);
    status = IOConnectMethodScalarIScalarO(connect, kFree, 2, 0, kNilOptions, id1);
    assert(kIOReturnSuccess == status);
    status = IOConnectMethodScalarIScalarO(connect, kAlloc, 2, 1, kNilOptions, 0, &id1);
    assert(kIOReturnSuccess == status);
    printf("ID: %x\n", id1);


    status = IOConnectMethodScalarIScalarO(connect, kAlloc, 2, 1, kIOAccelSpecificID, 53, &id2);
    assert(kIOReturnSuccess == status);
    printf("ID: %x\n", id2);


    status = IOConnectMethodScalarIScalarO(connect, kFree, 2, 0, kNilOptions, id1);
    assert(kIOReturnSuccess == status);
    printf("free ID: %d\n", id1);

    status = IOConnectMethodScalarIScalarO(connect, kFree, 2, 0, kNilOptions, id2);
    assert(kIOReturnSuccess == status);
    printf("free ID: %d\n", id2);

    exit(0);	
}



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
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#include <IOKit/IOLib.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/storage/IOBlockStorageDevice.h>

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

#define	super	IOService
OSDefineMetaClassAndAbstractStructors(IOBlockStorageDevice,IOService)

bool
IOBlockStorageDevice::init(OSDictionary * properties)
{
    bool result;

    result = super::init(properties);
    if (result) {
        result = setProperty(kIOBlockStorageDeviceTypeKey,
                             kIOBlockStorageDeviceTypeGeneric);
    }
   
#ifdef L4IOKIT
    //IOLog("IOBlockStorageDevice::init got result %d\n", result);
    //L4_KDB_Enter("X");
#endif 
    return(result);
}

/* Route a user-client getter request.  We should make a full-
 * fledged user-client for IOBlockStorageDevice at some point.
 */
OSObject *
IOBlockStorageDevice::getProperty(const OSSymbol * key) const
{
    OSObject *obj = NULL;

    if (key->isEqualTo(kIOBlockStorageDeviceWriteCacheStateKey)) {
        bool enabled;
        IOReturn result;

        result = ((IOBlockStorageDevice *)this)->getWriteCacheState(&enabled);
        if (result == kIOReturnSuccess) {
            obj = (enabled) ? kOSBooleanTrue : kOSBooleanFalse;
        }
/*  } else if (key->isEqualTo(...)) {
 *      obj = ...;
 */
    } else {
        obj = super::getProperty(key);
    }

    return(obj);
}

/* Route a user-client setter request.  We should make a full-
 * fledged user-client for IOBlockStorageDevice at some point.
 */
IOReturn
IOBlockStorageDevice::setProperties(OSObject * properties)
{
    OSDictionary *dict;
    OSObject *obj;
    IOReturn result;

    result = super::setProperties(properties);
    if (result != kIOReturnUnsupported) {
        return(result);
    }

    result = IOUserClient::clientHasPrivilege(current_task(),kIOClientPrivilegeAdministrator);
    if (result != kIOReturnSuccess) {
        return(result);
    }

    dict = OSDynamicCast(OSDictionary,properties);
    if (!dict) {
        return(kIOReturnBadArgument);
    }

    obj = dict->getObject(kIOBlockStorageDeviceWriteCacheStateKey);
    if (obj) {
        if (OSDynamicCast(OSBoolean,obj)) {
            result = setWriteCacheState((obj == kOSBooleanTrue));
        } else {
            result = kIOReturnBadArgument;
        }
        return(result);
    }

/*  obj = dict->getObject(...);
 *  if (obj) {
 *      result = ...;
 *      return(result);
 *  }
 */

    return(kIOReturnUnsupported);
}

/* DEPRECATED */ IOReturn
/* DEPRECATED */ IOBlockStorageDevice::doSyncReadWrite(IOMemoryDescriptor *buffer,
/* DEPRECATED */                                       UInt32 block,UInt32 nblks)
/* DEPRECATED */ {
/* DEPRECATED */    return(kIOReturnUnsupported);
/* DEPRECATED */ }

IOReturn
IOBlockStorageDevice::doAsyncReadWrite(IOMemoryDescriptor *buffer,
                                       UInt64 block,UInt64 nblks,
                                       IOStorageCompletion completion)
{
    if ((block >> 32) || (nblks >> 32)) {
        return(kIOReturnUnsupported);
    } else {
        return(doAsyncReadWrite(buffer,(UInt32)block,(UInt32)nblks,completion));
    }
}

OSMetaClassDefineReservedUsed(IOBlockStorageDevice, 0);

IOReturn
IOBlockStorageDevice::getWriteCacheState(bool *enabled)
{
    return(kIOReturnUnsupported);
}

OSMetaClassDefineReservedUsed(IOBlockStorageDevice, 1);

IOReturn
IOBlockStorageDevice::setWriteCacheState(bool enabled)
{
    return(kIOReturnUnsupported);
}

OSMetaClassDefineReservedUsed(IOBlockStorageDevice, 2);

OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  3);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  4);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  5);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  6);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  7);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  8);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice,  9);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 10);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 11);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 12);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 13);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 14);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 15);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 16);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 17);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 18);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 19);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 20);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 21);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 22);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 23);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 24);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 25);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 26);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 27);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 28);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 29);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 30);
OSMetaClassDefineReservedUnused(IOBlockStorageDevice, 31);

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
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
#include "IOHITabletPointer.h"

OSDefineMetaClassAndStructors(IOHITabletPointer, IOHIDevice)

UInt16 IOHITabletPointer::generateDeviceID()
{
    static UInt16 _nextDeviceID = 0;
    return _nextDeviceID++;
}

bool IOHITabletPointer::init( OSDictionary *propTable )
{
    if (!IOHIDevice::init(propTable)) {
        return false;
    }

    _deviceID = generateDeviceID();
    setProperty(kIOHITabletPointerDeviceID, (unsigned long long)_deviceID, 16);

    return true;
}

bool IOHITabletPointer::attach( IOService * provider )
{
    if (!IOHIDevice::attach(provider)) {
        return false;
    }

    _tablet = OSDynamicCast(IOHITablet, provider);

    return true;
}

void IOHITabletPointer::dispatchTabletEvent(NXEventData *tabletEvent,
                                            AbsoluteTime ts)
{
    if (_tablet) {
        _tablet->dispatchTabletEvent(tabletEvent, ts);
    }
}

void IOHITabletPointer::dispatchProximityEvent(NXEventData *proximityEvent,
                                               AbsoluteTime ts)
{
    if (_tablet) {
        _tablet->dispatchProximityEvent(proximityEvent, ts);
    }
}

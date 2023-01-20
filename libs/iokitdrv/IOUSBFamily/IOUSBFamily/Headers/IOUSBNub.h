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
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_IOUSBNUB_H
#define _IOKIT_IOUSBNUB_H

#include <IOKit/IOService.h>
#include <libkern/c++/OSData.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/usb/USB.h>

class IOUSBController;
class IOUSBPipe;

class IOUSBNub : public IOService
{
    OSDeclareDefaultStructors(IOUSBNub)

public:
    virtual bool    USBCompareProperty(OSDictionary   * matching,
                                    const char     * key );
    
    bool            IsWildCardMatch( OSDictionary   * matching, const char     * key );
    bool	    USBComparePropertyWithMask( OSDictionary *matching, const char *key, const char * maskKey );
};

#ifdef __cplusplus
extern "C" {
#endif

void printDescriptor(const IOUSBDescriptorHeader *desc);
void printDeviceDescriptor(const IOUSBDeviceDescriptor *desc);
void printConfigDescriptor(const IOUSBConfigurationDescriptor *cd);
void printEndpointDescriptor(const IOUSBEndpointDescriptor *ed);
void printInterfaceDescriptor(const IOUSBInterfaceDescriptor *id);

#ifdef __cplusplus
}
#endif

#endif /* _IOKIT_IOUSBNUB_H */

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

#ifndef _IOKIT_APPLEUSBOPTICALMOUSE_H
#define _IOKIT_APPLEUSBOPTICALMOUSE_H

#ifndef L4IOKIT
#include "IOUSBHIDDriver.h"
#else
#include <IOKit/usb/IOUSBHIDDriver.h>
#endif

#define kMouseRetryCount	3

class AppleUSBOpticalMouse : public IOUSBHIDDriver
{
    OSDeclareDefaultStructors(AppleUSBOpticalMouse)

private:
    IONotifier * 		_notifier;
    bool			_switchTo800dpiFlag;
    bool			_switchTo2000fpsFlag;
    
    // IOKit methods
    bool		willTerminate(IOService * provider, IOOptionBits options);
   
#ifdef L4IOKIT
    virtual bool start(IOService *provider);
#endif
 
    // IOUSBHIDDriver methods
    virtual IOReturn	StartFinalProcessing(void);
    
    // leaf class methods
    static IOReturn 	PowerDownHandler(void *target, void *refCon, UInt32 messageType, IOService *service,
                                      void *messageArgument, vm_size_t argSize);
};

#endif _IOKIT_APPLEUSBOPTICALMOUSE_H

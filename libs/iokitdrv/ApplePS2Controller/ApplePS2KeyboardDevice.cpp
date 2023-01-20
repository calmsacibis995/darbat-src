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

#include <IOKit/assert.h>
#include <IOKit/ps2/ApplePS2KeyboardDevice.h>
#include "ApplePS2Controller.h"

// =============================================================================
// ApplePS2KeyboardDevice Class Implementation
//

#define super IOService
OSDefineMetaClassAndStructors(ApplePS2KeyboardDevice, IOService);

bool ApplePS2KeyboardDevice::attach( IOService * provider )
{
  if( !super::attach(provider) )  return false;

  assert(_controller == 0);
  _controller = (ApplePS2Controller *)provider;
  _controller->retain();

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::detach( IOService * provider )
{
  assert(_controller == provider);
  _controller->release();
  _controller = 0;

  super::detach(provider);
}

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::installInterruptAction(OSObject *         target,
                                                    PS2InterruptAction action)
{
#ifdef L4IOKIT
  IOLog("ApplePS2KeyboardDevice::installInterruptAction installing!\n");
#endif
  _controller->installInterruptAction(kDT_Keyboard, target, action);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::uninstallInterruptAction()
{
  _controller->uninstallInterruptAction(kDT_Keyboard);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::installPowerControlAction(
                                                OSObject *            target,
                                                PS2PowerControlAction action)
{
  _controller->installPowerControlAction(kDT_Keyboard, target, action);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::uninstallPowerControlAction()
{
  _controller->uninstallPowerControlAction(kDT_Keyboard);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

PS2Request * ApplePS2KeyboardDevice::allocateRequest()
{
  return _controller->allocateRequest();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::freeRequest(PS2Request * request)
{
  _controller->freeRequest(request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool ApplePS2KeyboardDevice::submitRequest(PS2Request * request)
{
  return _controller->submitRequest(request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ApplePS2KeyboardDevice::submitRequestAndBlock(PS2Request * request)
{
  _controller->submitRequestAndBlock(request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 0);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 1);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 2);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 3);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 4);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 5);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 6);
OSMetaClassDefineReservedUnused(ApplePS2KeyboardDevice, 7);

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

#ifndef _APPLEPS2MOUSEDEVICE_H
#define _APPLEPS2MOUSEDEVICE_H

#include <IOKit/ps2/ApplePS2Device.h>

class ApplePS2Controller;

class ApplePS2MouseDevice : public IOService
{
  OSDeclareDefaultStructors(ApplePS2MouseDevice);

private:
  ApplePS2Controller * _controller;

protected:
  struct ExpansionData { /* */ };
  ExpansionData * _expansionData;

public:
  virtual bool attach(IOService * provider);
  virtual void detach(IOService * provider);

  // Interrupt Handling Routines

  virtual void installInterruptAction(OSObject *, PS2InterruptAction);
  virtual void uninstallInterruptAction();

  // Request Submission Routines

  virtual PS2Request * allocateRequest();
  virtual void         freeRequest(PS2Request * request);
  virtual bool         submitRequest(PS2Request * request);
  virtual void         submitRequestAndBlock(PS2Request * request);

  // Power Control Handling Routines

  virtual void installPowerControlAction(OSObject *, PS2PowerControlAction);
  virtual void uninstallPowerControlAction();

  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 0);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 1);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 2);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 3);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 4);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 5);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 6);
  OSMetaClassDeclareReservedUnused(ApplePS2MouseDevice, 7);
};

#endif /* !_APPLEPS2MOUSEDEVICE_H */

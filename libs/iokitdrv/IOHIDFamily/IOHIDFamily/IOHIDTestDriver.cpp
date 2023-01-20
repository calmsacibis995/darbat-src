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
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
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

#include <IOKit/IOBufferMemoryDescriptor.h>
#include "IOHIDEventQueue.h"
#include "IOHIDTestDriver.h"

#undef  super
#define super IOHIDDevice
OSDefineMetaClassAndStructors( IOHIDTestDriver, IOHIDDevice )

void IOHIDTestDriver::free()
{
    if ( _timerSource )
    {
        _timerSource->cancelTimeout();
        _timerSource->release();
        _timerSource = 0;
    }

    if ( _workLoop )
    {
        _workLoop->release();
        _workLoop = 0;
    }

    super::free();
}

static void generateFakeReport(OSObject * owner, IOTimerEventSource * sender)
{
    ((IOHIDTestDriver *) owner)->issueFakeReport();

    sender->setTimeoutMS(1000);
}

void IOHIDTestDriver::handleStop( IOService * provider )
{
    if ( _timerSource ) _timerSource->cancelTimeout();
    
    super::handleStop(provider);
}

bool IOHIDTestDriver::handleStart( IOService * provider )
{
    if ( super::handleStart(provider) == false )
        return false;

    _workLoop = IOWorkLoop::workLoop();
    if ( _workLoop == 0 )
        return false;
        
    _timerSource = IOTimerEventSource::timerEventSource(
                     this, 
                     (IOTimerEventSource::Action) &generateFakeReport );
    if ( _timerSource == 0)
        return false;
    
    if ( _workLoop->addEventSource( _timerSource ) != kIOReturnSuccess )
        return false;

    _timerSource->setTimeoutMS(1000);

    return true;
}

//---------------------------------------------------------------------------
// Report fake report descriptor and report data.

IOReturn IOHIDTestDriver::newReportDescriptor(IOMemoryDescriptor ** desc) const
{
#if 0
    // Keyboard
    char report[] = { 0x05, 0x01,
                      0x09, 0x06,
                      0xA1, 0x01,
                      0x05, 0x07,
                      0x19, 0xE0,
                      0x29, 0xE7,
                      0x15, 0x00,
                      0x25, 0x01,
                      0x75, 0x01,
                      0x95, 0x08,
                      0x81, 0x02,
                      0x95, 0x01,
                      0x75, 0x08,
                      0x81, 0x01,
                      0x95, 0x05,
                      0x75, 0x01,
                      0x05, 0x08,
                      0x19, 0x01,
                      0x29, 0x05,
                      0x91, 0x02,
                      0x95, 0x01,
                      0x75, 0x03,
                      0x91, 0x01,
                      0x95, 0x06,
                      0x75, 0x08,
                      0x15, 0x00,
                      0x25, 0x65,
                      0x05, 0x07,
                      0x19, 0x00,
                      0x29, 0x65,
                      0x81, 0x00, 0xC0 };

    // macally joystick
    char report[] = {
        0x05, 0x01, 0x09, 0x04, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
        0x15, 0x00, 0x25, 0x7F, 0x35, 0x00, 0x46, 0xFF,
        0x00, 0x66, 0x00, 0x00, 0x75, 0x08, 0x95, 0x02,
        0x81, 0x02, 0x75, 0x08, 0x95, 0x01, 0x81, 0x01,
        0x09, 0x39, 0x15, 0x01, 0x25, 0x08, 0x36, 0x00,
        0x00, 0x46, 0x3B, 0x01, 0x65, 0x14, 0x75, 0x08,
        0x95, 0x01, 0x81, 0x02, 0x05, 0x09, 0x19, 0x01,
        0x29, 0x04, 0x15, 0x00, 0x25, 0x01, 0x35, 0x00,
        0x45, 0x01, 0x75, 0x01, 0x95, 0x04, 0x81, 0x02,
        0x95, 0x01, 0x75, 0x04, 0x81, 0x01, 0xC0, 0x05,
        0x01, 0x09, 0x36, 0x15, 0x00, 0x26, 0xFF, 0x00,
        0x35, 0x00, 0x46, 0xFF, 0x00, 0x75, 0x08, 0x66,
        0x00, 0x00, 0x95, 0x01, 0x81, 0x02, 0xC0, 0x00,
        0x00, 0x00
    };

    // macally gamepad
    char report[] = {
        0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
        0x09, 0x35, 0x09, 0x36, 0x15, 0x00, 0x25, 0x7F,
        0x35, 0x00, 0x46, 0xFF, 0x00, 0x65, 0x00, 0x75,
        0x08, 0x95, 0x04, 0x81, 0x02, 0x05, 0x09, 0x19,
        0x01, 0x29, 0x14, 0x15, 0x00, 0x25, 0x01, 0x35,
        0x00, 0x45, 0x01, 0x75, 0x01, 0x95, 0x14, 0x81,
        0x02, 0x75, 0x01, 0x95, 0x04, 0x81, 0x01, 0xC0,
        0xC0
    };

    // gravis gamepad
    char report[] = {
        0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x05, 0x01,
        0x09, 0x01, 0xA1, 0x00, 0x09, 0x30, 0x09, 0x31,
        0x15, 0x00, 0x26, 0xFF, 0x00, 0x75, 0x08, 0x95,
        0x02, 0x81, 0x02, 0xC0, 0x05, 0x09, 0x19, 0x01,
        0x29, 0x0A, 0x15, 0x00, 0x25, 0x01, 0x75, 0x01,
        0x95, 0x0A, 0x81, 0x02, 0x95, 0x01, 0x75, 0x06,
        0x81, 0x01, 0xC0 
    };
    
    // sidewinder gamepad
    char report[] = {
        0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
        0x15, 0x00, 0x25, 0x7F, 0x35, 0x00, 0x45, 0x7F,
        0x66, 0x00, 0x00, 0x75, 0x08, 0x95, 0x02, 0x81,
        0x02, 0xC0, 0x05, 0x09, 0x19, 0x01, 0x29, 0x06,
        0x15, 0x00, 0x25, 0x01, 0x35, 0x00, 0x45, 0x01,
        0x75, 0x01, 0x95, 0x06, 0x81, 0x02, 0x95, 0x02,
        0x81, 0x01, 0xC0
    };

    // Xterminator
    char report[] = {
        0x05, 0x01, 0x09, 0x04, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
        0x15, 0x00, 0x26, 0xFF, 0x00, 0x75, 0x08, 0x95,
        0x02, 0x81, 0x02, 0xC0, 0x05, 0x01, 0x09, 0x35,
        0x15, 0x00, 0x26, 0xFF, 0x00, 0x35, 0x00, 0x46,
        0xFF, 0x00, 0x75, 0x08, 0x95, 0x01, 0x81, 0x02,
        0x09, 0x37, 0x15, 0x00, 0x26, 0xFF, 0x00, 0x35,
        0x00, 0x46, 0xFF, 0x00, 0x75, 0x08, 0x95, 0x01,
        0x81, 0x02, 0x09, 0x32, 0x15, 0x00, 0x26, 0xFF,
        0x00, 0x35, 0x00, 0x46, 0xFF, 0x00, 0x75, 0x08,
        0x95, 0x01, 0x81, 0x02, 0x05, 0x01, 0x09, 0x39,
        0x15, 0x01, 0x25, 0x08, 0x75, 0x08, 0x95, 0x01,
        0x81, 0x42, 0x05, 0x09, 0x19, 0x01, 0x29, 0x09,
        0x15, 0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x09,
        0x81, 0x02, 0x75, 0x01, 0x95, 0x07, 0x81, 0x01,
        0xC0
    };

    // Thrustmaster
    char report[] = {
        0x05, 0x01, 0x09, 0x04, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x09, 0x30, 0x09, 0x31, 0x15, 0x80,
        0x25, 0x7F, 0x35, 0x00, 0x46, 0xFF, 0x00, 0x75,
        0x08, 0x95, 0x02, 0x81, 0x02, 0xC0, 0x09, 0x39, 
        0x15, 0x01, 0x25, 0x08, 0x35, 0x00, 0x46, 0x3B,
        0x01, 0x66, 0x14, 0x00, 0x75, 0x04, 0x95, 0x01,
        0x81, 0x42, 0x05, 0x09, 0x15, 0x00, 0x25, 0x01,
        0x35, 0x00, 0x45, 0x01, 0x19, 0x01, 0x29, 0x04,
        0x75, 0x01, 0x95, 0x04, 0x81, 0x02, 0x75, 0x08,
        0x95, 0x01, 0x81, 0x01, 0xC0
    };

    // macally gamepad
    char report[] = {
        0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x09, 0x01,
        0xA1, 0x00, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
        0x09, 0x35, 0x09, 0x36, 0x15, 0x00, 0x25, 0x7F,
        0x35, 0x00, 0x46, 0xFF, 0x00, 0x65, 0x00, 0x75,
        0x08, 0x95, 0x04, 0x81, 0x02, 0x05, 0x09, 0x19,
        0x01, 0x29, 0x14, 0x15, 0x00, 0x25, 0x01, 0x35,
        0x00, 0x45, 0x01, 0x75, 0x01, 0x95, 0x14, 0x81,
        0x02, 0x75, 0x01, 0x95, 0x04, 0x81, 0x01, 0xC0,
        0xC0
    };
#endif

    // EIZO HID-controllable monitors
    char report[] = {
        0x05, 0x80, 0x09, 0x01, 0xA1, 0x01, 0x75, 0x08, 0x95, 0x80, 0x15, 0x00, 0x26, 0xFF, 0x00, 0x85,
        0x01, 0x09, 0x02, 0xB2, 0x02, 0x01, 0x05, 0x82, 0x75, 0x10, 0x95, 0x01, 0x25, 0x78, 0x85, 0x20,
        0x09, 0x12, 0x81, 0x02, 0x09, 0x12, 0xB1, 0x02, 0x26, 0xC8, 0x00, 0x85, 0x21, 0x09, 0x10, 0x81,
        0x02, 0x09, 0x10, 0xB1, 0x02, 0x26, 0xFF, 0x00, 0x85, 0x22, 0x09, 0x16, 0x81, 0x02, 0x09, 0x16,
        0xB1, 0x02, 0x85, 0x23, 0x09, 0x18, 0x81, 0x02, 0x09, 0x18, 0xB1, 0x02, 0x85, 0x24, 0x09, 0x1A,
        0x81, 0x02, 0x09, 0x1A, 0xB1, 0x02, 0x26, 0xFF, 0x01, 0x85, 0x30, 0x09, 0x20, 0x81, 0x02, 0x09,
        0x20, 0xB1, 0x02, 0x26, 0xFF, 0x00, 0x85, 0x38, 0x09, 0x30, 0x81, 0x02, 0x09, 0x30, 0xB1, 0x02,
        0x75, 0x20, 0x27, 0x40, 0x0D, 0x03, 0x00, 0x85, 0x10, 0x09, 0xAC, 0x81, 0x02, 0x09, 0xAC, 0xB1,
        0x02, 0x75, 0x10, 0x26, 0x20, 0x4E, 0x09, 0xAE, 0x81, 0x02, 0x09, 0xAE, 0xB1, 0x02, 0x75, 0x02,
        0x15, 0x01, 0x25, 0x02, 0x85, 0x02, 0x09, 0x60, 0xA1, 0x02, 0x05, 0x81, 0x09, 0x01, 0x09, 0x02,
        0x81, 0x00, 0xC0, 0x75, 0x06, 0x81, 0x03, 0x05, 0x82, 0x75, 0x02, 0x09, 0x60, 0xA1, 0x02, 0x05,
        0x81, 0x09, 0x01, 0x09, 0x02, 0xB1, 0x00, 0xC0, 0x75, 0x06, 0xB1, 0x03, 0x05, 0x82, 0x75, 0x02,
        0x85, 0x18, 0x09, 0xB0, 0xA1, 0x02, 0x05, 0x81, 0x09, 0x01, 0x09, 0x02, 0xB1, 0x00, 0xC0, 0x75,
        0x06, 0xB1, 0x03, 0x06, 0x00, 0xFF, 0x75, 0x10, 0x95, 0x01, 0x15, 0x00, 0x27, 0xFF, 0xFF, 0x00,
        0x00, 0x85, 0x50, 0x09, 0x09, 0x81, 0x02, 0x09, 0x09, 0xB1, 0x02, 0x85, 0x51, 0x09, 0x30, 0xB1,
        0x02, 0x85, 0x52, 0x09, 0x31, 0xB1, 0x02, 0x75, 0x20, 0x27, 0xFF, 0xFF, 0xFF, 0x00, 0x85, 0x53,
        0x09, 0x32, 0xB1, 0x02, 0x75, 0x08, 0x26, 0xFF, 0x00, 0x85, 0x54, 0x09, 0x33, 0xB1, 0x02, 0x95,
        0x80, 0x85, 0x55, 0x09, 0x34, 0xB2, 0x02, 0x01, 0x75, 0x10, 0x95, 0x01, 0x25, 0x06, 0x85, 0x56,
        0x09, 0xBC, 0x81, 0x02, 0x09, 0xBC, 0xB1, 0x02, 0x75, 0x08, 0x95, 0x10, 0x26, 0xFF, 0x00, 0x85,
        0x57, 0x09, 0x35, 0xB2, 0x02, 0x01, 0x95, 0x03, 0x85, 0x58, 0x09, 0x37, 0xB1, 0x02, 0x95, 0x11,
        0x85, 0x59, 0x09, 0x36, 0xB2, 0x02, 0x01, 0x95, 0x21, 0x85, 0x5A, 0x09, 0x38, 0xB2, 0x02, 0x01,
        0x85, 0x5B, 0x09, 0x39, 0xB2, 0x02, 0x01, 0x85, 0x5C, 0x09, 0x3A, 0xB2, 0x02, 0x01, 0x95, 0x11,
        0x85, 0x5D, 0x09, 0x3B, 0xB2, 0x02, 0x01, 0x95, 0x01, 0x25, 0x01, 0x85, 0x5E, 0x09, 0xBF, 0xB1,
        0x02, 0x85, 0x5F, 0x09, 0xBD, 0xB1, 0x02, 0x95, 0x04, 0x26, 0xFF, 0x00, 0x85, 0x60, 0x09, 0xBE,
        0xB1, 0x02, 0x95, 0x01, 0x25, 0x01, 0x85, 0x61, 0x09, 0xB8, 0x81, 0x02, 0x09, 0xB8, 0xB1, 0x02,
        0x75, 0x08, 0x25, 0x27, 0x85, 0x62, 0x09, 0x3D, 0xB1, 0x02, 0x75, 0x08, 0x95, 0x80, 0x26, 0xFF,
        0x00, 0x85, 0x63, 0x09, 0x3E, 0xB2, 0x02, 0x01, 0x75, 0x10, 0x95, 0x01, 0x25, 0x01, 0x85, 0x81,
        0x09, 0xC1, 0x81, 0x02, 0x09, 0xC1, 0xB1, 0x02, 0x25, 0x1F, 0x85, 0x82, 0x09, 0xC5, 0x81, 0x02,
        0x75, 0x08, 0x95, 0x02, 0x25, 0x40, 0x85, 0x84, 0x09, 0xC7, 0xB1, 0x02, 0x75, 0x10, 0x95, 0x28,
        0x27, 0xFF, 0xFF, 0x00, 0x00, 0x85, 0x85, 0x09, 0xC8, 0xB1, 0x02, 0x95, 0x01, 0x25, 0x77, 0x85,
        0x83, 0x09, 0xC6, 0xB1, 0x02, 0x75, 0x08, 0x25, 0x02, 0x85, 0x86, 0x09, 0xC9, 0xB1, 0x02, 0x75,
        0x10, 0x25, 0x0B, 0x85, 0x90, 0x09, 0xE1, 0xB1, 0x02, 0x75, 0x08, 0x25, 0x01, 0x85, 0x91, 0x09,
        0xE2, 0xB1, 0x02, 0x95, 0x80, 0x26, 0xFF, 0x00, 0x85, 0x92, 0x09, 0xE3, 0xB2, 0x02, 0x01, 0x95,
        0x01, 0x75, 0x10, 0x85, 0xA0, 0x09, 0xA7, 0x81, 0x02, 0x09, 0xA7, 0xB1, 0x02, 0x85, 0xA1, 0x09,
        0x83, 0x81, 0x02, 0x09, 0x83, 0xB1, 0x02, 0x85, 0xA2, 0x09, 0x84, 0x81, 0x02, 0x09, 0x84, 0xB1,
        0x02, 0x85, 0xA3, 0x09, 0x85, 0x81, 0x02, 0x09, 0x85, 0xB1, 0x02, 0x25, 0x3F, 0x85, 0xA4, 0x09,
        0x86, 0x81, 0x02, 0x09, 0x86, 0xB1, 0x02, 0x85, 0xA5, 0x09, 0x87, 0x81, 0x02, 0x09, 0x87, 0xB1,
        0x02, 0x85, 0xA6, 0x09, 0x88, 0x81, 0x02, 0x09, 0x88, 0xB1, 0x02, 0x26, 0xFF, 0x00, 0x85, 0xA7,
        0x09, 0x89, 0x81, 0x02, 0x09, 0x89, 0xB1, 0x02, 0x85, 0xA8, 0x09, 0x8A, 0x81, 0x02, 0x09, 0x8A,
        0xB1, 0x02, 0x85, 0xA9, 0x09, 0x8B, 0x81, 0x02, 0x09, 0x8B, 0xB1, 0x02, 0x85, 0xAA, 0x09, 0x8C,
        0x81, 0x02, 0x09, 0x8C, 0xB1, 0x02, 0x26, 0x00, 0x05, 0x16, 0x40, 0x01, 0x85, 0xB0, 0x09, 0xA2,
        0x81, 0x02, 0x09, 0xA2, 0xB1, 0x02, 0x85, 0xB1, 0x09, 0xCA, 0x81, 0x02, 0x09, 0xCA, 0xB1, 0x02,
        0x26, 0x00, 0x04, 0x16, 0xC8, 0x00, 0x85, 0xB8, 0x09, 0xA3, 0x81, 0x02, 0x09, 0xA3, 0xB1, 0x02,
        0x85, 0xB9, 0x09, 0xCB, 0x81, 0x02, 0x09, 0xCB, 0xB1, 0x02, 0x25, 0x06, 0x15, 0x00, 0x85, 0xC0,
        0x09, 0x10, 0x81, 0x02, 0x09, 0x10, 0xB1, 0x02, 0x16, 0x00, 0x80, 0x26, 0xFF, 0x7F, 0x85, 0xC2,
        0x09, 0x0F, 0x81, 0x02, 0x09, 0x0F, 0xB1, 0x02, 0x15, 0x00, 0x25, 0x07, 0x85, 0xC3, 0x09, 0x15,
        0x81, 0x02, 0x09, 0x15, 0xB1, 0x02, 0x15, 0x00, 0x25, 0x01, 0x85, 0xC4, 0x09, 0xA8, 0x81, 0x02,
        0x09, 0xA8, 0xB1, 0x02, 0x25, 0x17, 0x85, 0xC5, 0x09, 0xAA, 0x81, 0x02, 0x09, 0xAA, 0xB1, 0x02,
        0x25, 0x02, 0x85, 0xC6, 0x09, 0xA5, 0x81, 0x02, 0x09, 0xA5, 0xB1, 0x02, 0x25, 0x04, 0x85, 0xC7,
        0x09, 0xAB, 0x81, 0x02, 0x09, 0xAB, 0xB1, 0x02, 0x25, 0x01, 0x85, 0xCA, 0x09, 0x80, 0x81, 0x02,
        0x09, 0x80, 0xB1, 0x02, 0x26, 0xFE, 0x0F, 0x16, 0x40, 0x01, 0x85, 0xCB, 0x09, 0xA0, 0x81, 0x02,
        0x09, 0xA0, 0xB1, 0x02, 0x25, 0x1F, 0x15, 0x00, 0x85, 0xCC, 0x09, 0xA1, 0x81, 0x02, 0x09, 0xA1,
        0xB1, 0x02, 0x25, 0x07, 0x85, 0xCD, 0x09, 0x81, 0x81, 0x02, 0x09, 0x81, 0xB1, 0x02, 0x26, 0xFF,
        0x00, 0x85, 0xCE, 0x09, 0xC4, 0xB1, 0x02, 0x85, 0xCF, 0x09, 0x82, 0x81, 0x02, 0x09, 0x82, 0xB1,
        0x02, 0x26, 0x10, 0x27, 0x95, 0x02, 0x85, 0xD0, 0x09, 0xAD, 0x81, 0x02, 0x09, 0xAD, 0xB1, 0x02,
        0x85, 0xD1, 0x09, 0xAE, 0x81, 0x02, 0x09, 0xAE, 0xB1, 0x02, 0x85, 0xD2, 0x09, 0xAF, 0x81, 0x02,
        0x09, 0xAF, 0xB1, 0x02, 0x85, 0xD3, 0x09, 0xB0, 0x81, 0x02, 0x09, 0xB0, 0xB1, 0x02, 0x95, 0x01,
        0x26, 0x70, 0x17, 0x85, 0xD5, 0x09, 0xB2, 0x81, 0x02, 0x09, 0xB2, 0xB1, 0x02, 0x25, 0x0F, 0x85,
        0xD6, 0x09, 0x07, 0x81, 0x02, 0x09, 0x07, 0xB1, 0x02, 0x25, 0x20, 0x85, 0xD7, 0x09, 0xB3, 0x81,
        0x02, 0x09, 0xB3, 0xB1, 0x02, 0x85, 0xE8, 0x09, 0x6D, 0x81, 0x02, 0x09, 0x6D, 0xB1, 0x02, 0x85,
        0xE9, 0x09, 0x6E, 0x81, 0x02, 0x09, 0x6E, 0xB1, 0x02, 0x85, 0xEA, 0x09, 0x6F, 0x81, 0x02, 0x09,
        0x6F, 0xB1, 0x02, 0x85, 0xEB, 0x09, 0x70, 0x81, 0x02, 0x09, 0x70, 0xB1, 0x02, 0x85, 0xEC, 0x09,
        0x71, 0x81, 0x02, 0x09, 0x71, 0xB1, 0x02, 0x85, 0xED, 0x09, 0x72, 0x81, 0x02, 0x09, 0x72, 0xB1,
        0x02, 0x25, 0x28, 0x85, 0xD8, 0x09, 0xB4, 0x81, 0x02, 0x09, 0xB4, 0xB1, 0x02, 0x85, 0xE2, 0x09,
        0x67, 0x81, 0x02, 0x09, 0x67, 0xB1, 0x02, 0x85, 0xE3, 0x09, 0x68, 0x81, 0x02, 0x09, 0x68, 0xB1,
        0x02, 0x85, 0xE4, 0x09, 0x69, 0x81, 0x02, 0x09, 0x69, 0xB1, 0x02, 0x85, 0xE5, 0x09, 0x6A, 0x81,
        0x02, 0x09, 0x6A, 0xB1, 0x02, 0x85, 0xE6, 0x09, 0x6B, 0x81, 0x02, 0x09, 0x6B, 0xB1, 0x02, 0x85,
        0xE7, 0x09, 0x6C, 0x81, 0x02, 0x09, 0x6C, 0xB1, 0x02, 0x25, 0x08, 0x85, 0xD4, 0x09, 0x66, 0x81,
        0x02, 0x09, 0x66, 0xB1, 0x02, 0x26, 0xFF, 0x00, 0x85, 0xD9, 0x09, 0xB5, 0x81, 0x02, 0x09, 0xB5,
        0xB1, 0x02, 0x85, 0xDA, 0x09, 0xB6, 0x81, 0x02, 0x09, 0xB6, 0xB1, 0x02, 0x85, 0xDB, 0x09, 0xB7,
        0x81, 0x02, 0x09, 0xB7, 0xB1, 0x02, 0x26, 0x10, 0x27, 0x95, 0x02, 0x85, 0xDE, 0x09, 0x9C, 0x81,
        0x02, 0x09, 0x9C, 0xB1, 0x02, 0x85, 0xDF, 0x09, 0x9D, 0x81, 0x02, 0x09, 0x9D, 0xB1, 0x02, 0x85,
        0xE0, 0x09, 0x9E, 0x81, 0x02, 0x09, 0x9E, 0xB1, 0x02, 0x85, 0xE1, 0x09, 0x9F, 0x81, 0x02, 0x09,
        0x9F, 0xB1, 0x02, 0x75, 0x08, 0x95, 0x07, 0x26, 0xFF, 0x00, 0x85, 0x80, 0x09, 0xC3, 0xB2, 0x02,
        0x01, 0x75, 0x08, 0x95, 0x12, 0x26, 0xFF, 0x00, 0x85, 0xEF, 0x09, 0x3F, 0xB2, 0x02, 0x01, 0x75,
        0x10, 0x95, 0x02, 0x15, 0x00, 0x27, 0xFF, 0xFF, 0x00, 0x00, 0x85, 0x64, 0x09, 0x2F, 0xB1, 0x02,
        0x75, 0x08, 0x95, 0x04, 0x26, 0xFF, 0x00, 0x85, 0x65, 0x09, 0x41, 0xB1, 0x02, 0x96, 0x00, 0x02,
        0x85, 0x66, 0x09, 0x42, 0xB1, 0x02, 0x95, 0x10, 0x85, 0x67, 0x09, 0x43, 0xB1, 0x02, 0x95, 0x02,
        0x85, 0x68, 0x09, 0x48, 0xB1, 0x02, 0xC0
    };

    *desc = IOBufferMemoryDescriptor::withBytes( report,
                                                 sizeof(report),
                                                 kIODirectionNone );

    return kIOReturnSuccess;
}

void IOHIDTestDriver::issueFakeReport()
{
    UInt8 report[][7] = {
    { 0x44, 0x3B, 0x49, 0x43, 0x80, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x20, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x10, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x00, 0x80, 0x00 },
    { 0x44, 0x3B, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x44, 0x36, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x48, 0x19, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x48, 0x15, 0x49, 0x43, 0x00, 0x00, 0x00 },
    { 0x4C, 0x11, 0x49, 0x43, 0x00, 0x00, 0x00 } };

    const  UInt32 reportCount = sizeof(report)/sizeof(report[0]);
    static UInt32 reportIndex = 0;

    IOMemoryDescriptor * desc = IOMemoryDescriptor::withAddress(
                                        report[reportIndex],
                                        sizeof(report[0]),
                                        kIODirectionNone );

    if (desc)
    {
        handleReport( desc );
        desc->release();
    }

    if ( ++reportIndex >= reportCount )
        reportIndex = 0;
}

//---------------------------------------------------------------------------
// Dummy properties.

OSString * IOHIDTestDriver::newTransportString() const
{
    return OSString::withCStringNoCopy("USB");
}

OSString * IOHIDTestDriver::newManufacturerString() const
{
    return OSString::withCStringNoCopy("ACME");
}

OSString * IOHIDTestDriver::newProductString() const
{
    return OSString::withCStringNoCopy("AxisStick");
}

OSNumber * IOHIDTestDriver::newVendorIDNumber() const
{
    return OSNumber::withNumber(64443, 32);
}

OSNumber * IOHIDTestDriver::newProductIDNumber() const
{
    return OSNumber::withNumber(0xffff, 32);
}

OSNumber * IOHIDTestDriver::newVersionNumber() const
{
    return OSNumber::withNumber(256, 32);
}

OSNumber * IOHIDTestDriver::newSerialNumber() const
{
    return OSNumber::withNumber(0x1234, 32);
}

OSNumber * IOHIDTestDriver::newPrimaryUsageNumber() const
{
    return OSNumber::withNumber(4, 32);
}

OSNumber * IOHIDTestDriver::newPrimaryUsagePageNumber() const
{
    return OSNumber::withNumber(1, 32);
}

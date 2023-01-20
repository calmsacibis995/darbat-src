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
/*
 * 07 Jan 2002 		ryepez
 *			This class is based off IOHIPointing and handles
 *			USB HID report based pointing devices
 */

#include <IOKit/IOLib.h>
#include <IOKit/assert.h>
#include <IOKit/hidsystem/IOHIDParameter.h>
#include <IOKit/hidsystem/IOHIDShared.h>
#include <IOKit/hidsystem/IOHIDDescriptorParser.h>

#include "IOHIDPointing.h"
#include "IOHIDKeys.h"
#include "IOHIDElement.h"

#define super IOHITablet
OSDefineMetaClassAndStructors(IOHIDPointing, IOHITablet);

//====================================================================================================
// IOHIDPointing::Pointing
//====================================================================================================
IOHIDPointing * IOHIDPointing::Pointing(
                                UInt32          buttonCount,
                                IOFixed         pointerResolution,
                                IOFixed         scrollResolution,
                                bool            isDispatcher)
{
    IOHIDPointing 	*nub 			= new IOHIDPointing;    
    
    if ((nub == 0) || !nub->initWithMouseProperties(buttonCount, pointerResolution, scrollResolution, isDispatcher) )
    {
        if (nub) nub->release();
        return 0;
    }
        
    return nub;
}


//====================================================================================================
// IOHIDPointing::initWithMouseProperties
//====================================================================================================
bool IOHIDPointing::initWithMouseProperties(
                                UInt32          buttonCount,
                                IOFixed         pointerResolution,
                                IOFixed         scrollResolution,
                                bool            isDispatcher)
{
    if (!super::init(0))  return false;
    
    _numButtons         = (buttonCount > 0) ? buttonCount : 1;
    _resolution         = pointerResolution;
    _scrollResolution   = scrollResolution;
    _isDispatcher       = isDispatcher;
    
    return true;
}

//====================================================================================================
// IOHIDPointing::start
//====================================================================================================
bool IOHIDPointing::start(IOService *provider)
{

	_provider = OSDynamicCast(IOHIDEventService, provider);
	
	if (!_provider)
		return false;
		
    // push up properties from our provider
    setupProperties();
	
    return super::start(provider);
}

//====================================================================================================
// IOHIDPointing::dispatchAbsolutePointerEvent
//====================================================================================================
void IOHIDPointing::dispatchAbsolutePointerEvent(
                                AbsoluteTime                timeStamp,
                                Point *                     newLoc,
                                Bounds *                    bounds,
                                UInt32                      buttonState,
                                bool                        inRange,
                                SInt32                      tipPressure,
                                SInt32                      tipPressureMin,
                                SInt32                      tipPressureMax,
                                IOOptionBits                options)
{
    bool    convertToRelative   = ((options & kHIDDispatchOptionPointerAbsolutToRelative) != 0);
    bool    accelerate          = ((options & kHIDDispatchOptionPointerNoAcceleration) == 0);
    UInt32  pointingMode        = getPointingMode();
    
    if ( (((pointingMode & kAccelMouse) != 0) != accelerate) && (((pointingMode & kAbsoluteConvertMouse) != 0) != convertToRelative))
    {
        if ( accelerate )
            pointingMode |= kAccelMouse;
        else
            pointingMode &= ~kAccelMouse;
            
        if ( convertToRelative )
            pointingMode |= kAbsoluteConvertMouse;
        else
            pointingMode &= ~kAbsoluteConvertMouse;
            
        setPointingMode(pointingMode);
    }

	super::dispatchAbsolutePointerEvent(newLoc, bounds, buttonState, inRange, tipPressure, tipPressureMin, tipPressureMax, 90, timeStamp);
}

//====================================================================================================
// IOHIDPointing::dispatchRelativePointerEvent
//====================================================================================================
void IOHIDPointing::dispatchRelativePointerEvent(
                                AbsoluteTime                timeStamp,
                                SInt32                      dx,
                                SInt32                      dy,
                                UInt32                      buttonState,
                                IOOptionBits                options)
{
    bool    accelerate      = ((options & kHIDDispatchOptionPointerNoAcceleration) == 0);
    UInt32  pointingMode    = getPointingMode();
    
    if ( ((pointingMode & kAccelMouse) != 0) != accelerate)
    {
        if ( accelerate )
            pointingMode |= kAccelMouse;
        else
            pointingMode &= ~kAccelMouse;
            
        setPointingMode(pointingMode);
    }

	super::dispatchRelativePointerEvent(dx, dy, buttonState, timeStamp);
}

//====================================================================================================
// IOHIDPointing::dispatchScrollWheelEvent
//====================================================================================================
void IOHIDPointing::dispatchScrollWheelEvent(
                                AbsoluteTime                timeStamp,
                                SInt32                      deltaAxis1,
                                SInt32                      deltaAxis2,
                                UInt32                      deltaAxis3,
                                IOOptionBits                options)
{
    bool    accelerate      = ((options & kHIDDispatchOptionPointerNoAcceleration) == 0);
    UInt32  pointingMode    = getPointingMode();
    
    if ( ((pointingMode & kAccelScroll) != 0) != accelerate)
    {
        if ( accelerate )
            pointingMode |= kAccelScroll;
        else
            pointingMode &= ~kAccelScroll;
            
        setPointingMode(pointingMode);
    }
    
	super::dispatchScrollWheelEvent(deltaAxis1, deltaAxis2, deltaAxis3, timeStamp);
}

//====================================================================================================
// IOHIDPointing::generateDeviceID
//====================================================================================================
UInt16 IOHIDPointing::generateDeviceID()
{
    static UInt16 sNextDeviceID = 0x8000;
    return sNextDeviceID++;
}
                                
//====================================================================================================
// IOHIDPointing::dispatchTabletPointEvent
//====================================================================================================
void IOHIDPointing::dispatchTabletEvent(
                                    NXEventData *           tabletEvent,
                                    AbsoluteTime            ts)
{
    super::dispatchTabletEvent(tabletEvent, ts);
}

//====================================================================================================
// IOHIDPointing::dispatchTabletProximityEvent
//====================================================================================================
void IOHIDPointing::dispatchProximityEvent(
                                    NXEventData *           proximityEvent,
                                    AbsoluteTime            ts)
{
    super::dispatchProximityEvent(proximityEvent, ts);
}


// subclasses override

//====================================================================================================
// IOHIDPointing::buttonCount
//====================================================================================================
IOItemCount IOHIDPointing::buttonCount()
{
    return _numButtons;
}

//====================================================================================================
// IOHIDPointing::resolution
//====================================================================================================
IOFixed IOHIDPointing::resolution()
{
    return _resolution;
}


//====================================================================================================
// IOHIDPointing::setupProperties
//====================================================================================================
void IOHIDPointing::setupProperties()
{
    OSNumber *  number  = NULL;
    
	// Store the scroll resolution
    if ( number = OSDynamicCast(OSNumber, _provider->getProperty(kIOHIDScrollResolutionKey)) )
    {
        _scrollResolution = number->unsigned32BitValue();
        setProperty(kIOHIDScrollResolutionKey, number);
    }
    else if ( _scrollResolution )
    {
        setProperty(kIOHIDScrollResolutionKey, _scrollResolution, 32);
    }
    
    if ( _isDispatcher )
        setProperty(kIOHIDVirtualHIDevice, kOSBooleanTrue);

    setProperty(kIOHIDScrollAccelerationTypeKey, _provider->getProperty( kIOHIDScrollAccelerationTypeKey ));
    setProperty(kIOHIDPointerAccelerationTypeKey, _provider->getProperty( kIOHIDPointerAccelerationTypeKey ));
        
    setProperty(kIOHIDPointerAccelerationTableKey, _provider->getProperty( kIOHIDPointerAccelerationTableKey ));
    setProperty(kIOHIDScrollAccelerationTableKey, _provider->getProperty( kIOHIDScrollAccelerationTableKey ));
    
    setProperty(kIOHIDPointerResolutionKey, _provider->getProperty( kIOHIDPointerResolutionKey ));

    setProperty( kIOHIDScrollMouseButtonKey, _provider->getProperty( kIOHIDScrollMouseButtonKey ));
}

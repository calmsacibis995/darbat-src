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

#include "IOHIDInterface.h"
#include "IOHIDDevice.h"
#include "IOHIDElementPrivate.h"

#ifdef L4IOKIT
#include <IOKit/IOLib.h>
#endif

//===========================================================================
// IOHIDInterface class

#define super IOService

OSDefineMetaClassAndStructors( IOHIDInterface, super )

//---------------------------------------------------------------------------
// IOHIDInterface::free

void IOHIDInterface::free()
{
	if ( _elementArray )
	{
		_elementArray->release();
		_elementArray = 0;
	}

    super::free();
}

//---------------------------------------------------------------------------
// IOHIDInterface::init

bool IOHIDInterface::init( OSDictionary * dictionary )
{
    if ( !super::init(dictionary) )
        return false;
        
    bzero(_maxReportSize, sizeof(IOByteCount) * kIOHIDReportTypeCount);
        
    return true;
}

IOHIDInterface * IOHIDInterface::withElements( OSArray * elements )
{
    IOHIDInterface * nub = new IOHIDInterface;
    
    if ((nub == 0) || !nub->init() || !elements)
    {
        if (nub) nub->release();
        return 0;
    }
    
    nub->_elementArray  = elements;
    nub->_elementArray->retain();
	
    return nub;
}


//---------------------------------------------------------------------------
// IOHIDInterface::start

bool IOHIDInterface::start( IOService * provider )
{
    OSNumber * number;
    
    if ( !super::start(provider) )
        return false;
		
	_owner = OSDynamicCast( IOHIDDevice, provider );
	
	if ( !_owner )
		return false;
            
    _transportString    = OSDynamicCast(OSString, getProperty(kIOHIDTransportKey));
    _manufacturerString = OSDynamicCast(OSString, getProperty(kIOHIDManufacturerKey));
    _productString        = OSDynamicCast(OSString, getProperty(kIOHIDProductKey));
    _serialNumberString = OSDynamicCast(OSString, getProperty(kIOHIDSerialNumberKey));
    
    number = OSDynamicCast(OSNumber, getProperty(kIOHIDLocationIDKey));
    if ( number ) _locationID = number->unsigned32BitValue();
    
    number = OSDynamicCast(OSNumber, getProperty(kIOHIDVendorIDKey));
    if ( number ) _vendorID = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, getProperty(kIOHIDVendorIDSourceKey));
    if ( number ) _vendorIDSource = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, getProperty(kIOHIDProductIDKey));
    if ( number ) _productID = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, getProperty(kIOHIDVersionNumberKey));
    if ( number ) _version = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, getProperty(kIOHIDCountryCodeKey));
    if ( number ) _countryCode = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, _owner->getProperty(kIOHIDMaxInputReportSizeKey));
    if ( number ) _maxReportSize[kIOHIDReportTypeInput] = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, _owner->getProperty(kIOHIDMaxOutputReportSizeKey));
    if ( number ) _maxReportSize[kIOHIDReportTypeOutput] = number->unsigned32BitValue();

    number = OSDynamicCast(OSNumber, _owner->getProperty(kIOHIDMaxFeatureReportSizeKey));
    if ( number ) _maxReportSize[kIOHIDReportTypeFeature] = number->unsigned32BitValue();
    
    registerService();
    
    return true;
}
    
//---------------------------------------------------------------------------
// IOHIDInterface::matchPropertyTable

bool IOHIDInterface::matchPropertyTable(
                                OSDictionary *              table, 
                                SInt32 *                    score)
{
    if ( !super::matchPropertyTable(table, score) )
        return false;
        
    return _owner->matchPropertyTable(table, score);
}

//---------------------------------------------------------------------------
// IOHIDInterface::open

bool IOHIDInterface::open (
                                IOService *                 client,
                                IOOptionBits                options,
                                InterruptReportAction       action,
                                void *                      refCon)
{
    if ( !super::open(client, options) )
        return false;
        
    if ( !_owner->IOService::open(client, options) )
    {
        super::close(client, options);
        return false;
    }
    
    // Do something with action and refcon here
    _interruptTarget = client;
    _interruptAction = action;
    _interruptRefCon = refCon;
    
    return true;
}

void IOHIDInterface::close(  
								IOService *					client,
								IOOptionBits				options)
{
    _owner->close(client, options);
    
    super::close(client, options);
    
    _interruptTarget = NULL;
    _interruptAction = NULL;
    _interruptRefCon = NULL;    
    
}

OSString * IOHIDInterface::getTransport ()
{
    return _transportString;
}

OSString * IOHIDInterface::getManufacturer ()
{
    return _manufacturerString;
}

OSString * IOHIDInterface::getProduct ()
{
    return _productString;
}

OSString * IOHIDInterface::getSerialNumber ()
{
    return _serialNumberString;
}

UInt32 IOHIDInterface::getLocationID ()
{
    return _locationID;
}

UInt32 IOHIDInterface::getVendorID ()
{
    return _vendorID;
}

UInt32 IOHIDInterface::getVendorIDSource ()
{
    return _vendorIDSource;
}

UInt32 IOHIDInterface::getProductID ()
{
    return _productID;
}

UInt32 IOHIDInterface::getVersion ()
{
    return _version;
}

UInt32 IOHIDInterface::getCountryCode ()
{
    return _countryCode;
}

IOByteCount IOHIDInterface::getMaxReportSize (IOHIDReportType type)
{
    return _maxReportSize[type];
}


OSArray * IOHIDInterface::createMatchingElements (
                                OSDictionary *              matching, 
                                IOOptionBits                options)
{
    UInt32                    count        = _elementArray->getCount();
    IOHIDElementPrivate *   element        = NULL;
    OSArray *                elements    = NULL;

    if ( count )
    {
        if ( matching )
        {
            elements = OSArray::withCapacity(count - 1);

            // Start at index 1 to avoid virtual collection element
            for ( UInt32 i = 1; i < count; i ++)
            {
                // Compare properties.
                if (( element = (IOHIDElementPrivate *)_elementArray->getObject(i) )
                        && element->matchProperties(matching))
                {
                    elements->setObject(element);
                }
            }
        }
        else
        {
            elements = OSArray::withArray(_elementArray);

            // remove the virtual collection
            if (elements)
                elements->removeObject(0);
        }
    }

    return elements;
}

void IOHIDInterface::handleReport ( 
                                AbsoluteTime                timestamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options)
{
    if ( !_interruptAction )
        return;
    
#ifdef L4IOKIT
#if 0
    IOLog("_interruptAction %p %p timestamp (fixme) report %p "
	"report type %d report id %d refCon %p\n",
	_interruptAction, _interruptTarget, 
	report, reportType, reportID, _interruptRefCon);
#endif
#endif
    (*_interruptAction)(_interruptTarget, timestamp, report, reportType, reportID, _interruptRefCon);
}

    
IOReturn IOHIDInterface::setReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options)
{
    return _owner->setReport(report, reportType, (reportID | (options << 8)));
}

IOReturn IOHIDInterface::getReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options)
{
    return _owner->getReport(report, reportType, (reportID | (options << 8)));
}


IOReturn IOHIDInterface::setReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options,
                                UInt32                      completionTimeout,
                                CompletionAction *          completion)
{
    return kIOReturnUnsupported;
}
    

IOReturn IOHIDInterface::getReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options,
                                UInt32                      completionTimeout,
                                CompletionAction *          completion)
{
    return kIOReturnUnsupported;
}


OSMetaClassDefineReservedUnused(IOHIDInterface,  0);
OSMetaClassDefineReservedUnused(IOHIDInterface,  1);
OSMetaClassDefineReservedUnused(IOHIDInterface,  2);
OSMetaClassDefineReservedUnused(IOHIDInterface,  3);
OSMetaClassDefineReservedUnused(IOHIDInterface,  4);
OSMetaClassDefineReservedUnused(IOHIDInterface,  5);
OSMetaClassDefineReservedUnused(IOHIDInterface,  6);
OSMetaClassDefineReservedUnused(IOHIDInterface,  7);
OSMetaClassDefineReservedUnused(IOHIDInterface,  8);
OSMetaClassDefineReservedUnused(IOHIDInterface,  9);
OSMetaClassDefineReservedUnused(IOHIDInterface, 10);
OSMetaClassDefineReservedUnused(IOHIDInterface, 11);
OSMetaClassDefineReservedUnused(IOHIDInterface, 12);
OSMetaClassDefineReservedUnused(IOHIDInterface, 13);
OSMetaClassDefineReservedUnused(IOHIDInterface, 14);
OSMetaClassDefineReservedUnused(IOHIDInterface, 15);
OSMetaClassDefineReservedUnused(IOHIDInterface, 16);
OSMetaClassDefineReservedUnused(IOHIDInterface, 17);
OSMetaClassDefineReservedUnused(IOHIDInterface, 18);
OSMetaClassDefineReservedUnused(IOHIDInterface, 19);
OSMetaClassDefineReservedUnused(IOHIDInterface, 20);
OSMetaClassDefineReservedUnused(IOHIDInterface, 21);
OSMetaClassDefineReservedUnused(IOHIDInterface, 22);
OSMetaClassDefineReservedUnused(IOHIDInterface, 23);
OSMetaClassDefineReservedUnused(IOHIDInterface, 24);
OSMetaClassDefineReservedUnused(IOHIDInterface, 25);
OSMetaClassDefineReservedUnused(IOHIDInterface, 26);
OSMetaClassDefineReservedUnused(IOHIDInterface, 27);
OSMetaClassDefineReservedUnused(IOHIDInterface, 28);
OSMetaClassDefineReservedUnused(IOHIDInterface, 29);
OSMetaClassDefineReservedUnused(IOHIDInterface, 30);
OSMetaClassDefineReservedUnused(IOHIDInterface, 31);

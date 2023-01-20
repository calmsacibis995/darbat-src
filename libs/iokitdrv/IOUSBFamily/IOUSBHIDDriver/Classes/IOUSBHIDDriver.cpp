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


//================================================================================================
//
//   Headers
//
//================================================================================================
//
#include <libkern/OSByteOrder.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOMessage.h>

#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/usb/IOUSBInterface.h>
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/usb/IOUSBHIDDriver.h>

//================================================================================================
//
//   Local Definitions
//
//================================================================================================
//
#define super IOHIDDevice

#define _workLoop			_usbHIDExpansionData->_workLoop
#define _handleReportThread             _usbHIDExpansionData->_handleReportThread
#define _rootDomain			_usbHIDExpansionData->_rootDomain
#define _wakeUpTime			_usbHIDExpansionData->_wakeUpTime
#define _completionWithTimeStamp	_usbHIDExpansionData->_completionWithTimeStamp
#define _checkForTimeStamp		_usbHIDExpansionData->_checkForTimeStamp
#define _msToIgnoreTransactionsAfterWake	_usbHIDExpansionData->_msToIgnoreTransactionsAfterWake

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

//================================================================================================
//
//   IOUSBHIDDriver Methods
//
//================================================================================================
//
OSDefineMetaClassAndStructors(IOUSBHIDDriver, IOHIDDevice)


#pragma mark �������� IOService Methods ���������
//================================================================================================
//
//  init
//
//  Do what is necessary to start device before probe is called.
//
//================================================================================================
//
bool 
IOUSBHIDDriver::init(OSDictionary *properties)
{
#ifdef L4IOKIT
    IOLog("IOUSBHIDDriver init \n");
#endif
    if (!super::init(properties))
    {
        return false;
    }

    // Allocate our expansion data
    //
    if (!_usbHIDExpansionData)
    {
        _usbHIDExpansionData = (IOUSBHIDDriverExpansionData *)IOMalloc(sizeof(IOUSBHIDDriverExpansionData));
        if (!_usbHIDExpansionData)
            return false;
        bzero(_usbHIDExpansionData, sizeof(IOUSBHIDDriverExpansionData));
    }
    _retryCount = kHIDDriverRetryCount;
    _maxReportSize = kMaxHIDReportSize;

#ifdef L4IOKIT
    IOLog("IOUSBHIDDriver init retruns true\n");
#endif
    return true;
}

//================================================================================================
//
//  free
//
//================================================================================================
//
void
IOUSBHIDDriver::free()
{
    if (_gate)
    {
        if (_workLoop)
        {
            _workLoop->removeEventSource(_gate);
            _workLoop->release();
            _workLoop = NULL;
        }

        _gate->release();
        _gate = NULL;
    }

    //  This needs to be the LAST thing we do, as it disposes of our "fake" member
    //  variables.
    //
    if (_usbHIDExpansionData)
    {
        IOFree(_usbHIDExpansionData, sizeof(IOUSBHIDDriverExpansionData));
        _usbHIDExpansionData = NULL;
    }

super::free();
}


//=============================================================================================
//
//  start
//
//=============================================================================================
//
bool
IOUSBHIDDriver::start(IOService *provider)
{
    IOReturn			err = kIOReturnSuccess;
    IOWorkLoop	*		workLoop = NULL;
    IOCommandGate *		commandGate = NULL;
    OSNumber *			locationIDProperty;
    UInt32			locationID = 0;
    IOUSBFindEndpointRequest	request;
    bool			addEventSourceSuccess = false;
    UInt32			maxInputReportSize = 0;
    OSNumber * 			inputReportSize = NULL;
    
    USBLog(7, "%s[%p]::start", getName(), this);
    IncrementOutstandingIO();			// make sure that once we open we don't close until start is finished

#ifdef L4IOKIT
    IOLog("IOUSBHIDDriver::start called\n");
#endif
    if (!super::start(provider))
    {
        USBError(1, "%s[%p]::start - super::start returned false!", getName(), this);
        goto ErrorExit;
    }

    // Attempt to create a command gate for our driver
    //
    commandGate = IOCommandGate::commandGate(this);

    if (!commandGate)
    {
        USBError(1, "%s[%p]::start - could not get a command gate", getName(), this);
        goto ErrorExit;
    }

    workLoop = getWorkLoop();
    if ( !workLoop)
    {
        USBError(1, "%s[%p]::start - unable to find my workloop", getName(), this);
        goto ErrorExit;
    }

    // Hold on to the workloop in cause we're being unplugged at the same time
    //
    workLoop->retain();

    if (workLoop->addEventSource(commandGate) != kIOReturnSuccess)
    {
        USBError(1, "%s[%p]::start - unable to add gate to work loop", getName(), this);
        goto ErrorExit;
    }

    addEventSourceSuccess = true;

    // Now, find our interrupt out pipe and interrupt in pipes
    //
    request.type = kUSBInterrupt;
    request.direction = kUSBOut;
    _interruptOutPipe = _interface->FindNextPipe(NULL, &request);

    request.type = kUSBInterrupt;
    request.direction = kUSBIn;
    _interruptPipe = _interface->FindNextPipe(NULL, &request);

    if (!_interruptPipe)
    {
        USBError(1, "%s[%p]::start - unable to get interrupt pipe", getName(), this);
        goto ErrorExit;
    }

    // The HID spec specifies that only input reports should come thru the interrupt pipe.  Thus,
    // set the buffer size to the Max Input Report Size that has been decoded by the HID Mgr.
    //
    inputReportSize = (OSNumber *)getProperty(kIOHIDMaxInputReportSizeKey);
    if ( inputReportSize )
        maxInputReportSize = inputReportSize->unsigned32BitValue();

    if (maxInputReportSize == 0)
        maxInputReportSize = _interruptPipe->GetMaxPacketSize();

    if ( maxInputReportSize > 0 )
    {
        _buffer = IOBufferMemoryDescriptor::withCapacity(maxInputReportSize, kIODirectionIn);
        if ( !_buffer )
        {
            USBError(1, "%s[%p]::start - unable to get create buffer", getName(), this);
            goto ErrorExit;
        }
    }
    else
    {
        USBLog(5, "%s[%p]::start - Device reports maxInputReportSize of 0", getName(), this);
        _buffer = NULL;
    }
    
    // Errata for ALL Saitek devices.  Do a SET_IDLE 0 call
    //
    if ( (_device->GetVendorID()) == 0x06a3 )
        SetIdleMillisecs(0);

    // For Keyboards, set the idle millecs to 24 or to 0 if from Apple
    //
    if ( (_interface->GetInterfaceClass() == kUSBHIDClass) &&
         (_interface->GetInterfaceSubClass() == kUSBHIDBootInterfaceSubClass) &&
         (_interface->GetInterfaceProtocol() == kHIDKeyboardInterfaceProtocol) )
    {
        if (_device->GetVendorID() == kIOUSBVendorIDAppleComputer)
        {
            SetIdleMillisecs(0);
        }
        else
        {
            SetIdleMillisecs(24);
        }
    }

    // Set the device into Report Protocol if it's a bootInterface subClass interface
    //
    if (_interface->GetInterfaceSubClass() == kUSBHIDBootInterfaceSubClass)
        err = SetProtocol( kHIDReportProtocolValue );
    
    // allocate a thread_call structure to see if our device is "dead" or not. We need to do this on a separate thread
    // to allow it to run without holding up the show
    //
    _deviceDeadCheckThread = thread_call_allocate((thread_call_func_t)CheckForDeadDeviceEntry, (thread_call_param_t)this);
    _clearFeatureEndpointHaltThread = thread_call_allocate((thread_call_func_t)ClearFeatureEndpointHaltEntry, (thread_call_param_t)this);
    _handleReportThread = thread_call_allocate((thread_call_func_t)HandleReportEntry, (thread_call_param_t)this);
    
    if ( !_deviceDeadCheckThread || !_clearFeatureEndpointHaltThread || !_handleReportThread )
    {
        USBError(1, "[%s]%p: could not allocate all thread functions", getName(), this);
        goto ErrorExit;
    }
    
    
    // Get our locationID as an unsigned 32 bit number so we can
    locationIDProperty = (OSNumber *) provider->getProperty(kUSBDevicePropertyLocationID);
    if ( locationIDProperty )
    {
        locationID = locationIDProperty->unsigned32BitValue();
    }
    // Do the final processing for the "start" method.  This allows subclasses to get called right before we return from
    // the start
    //
    err = StartFinalProcessing();
    if (err != kIOReturnSuccess)
    {
        USBError(1, "%s[%p]::start - err (%x) in StartFinalProcessing", getName(), this, err);
        goto ErrorExit;
    }

    USBLog(1, "[%p]::start -  USB HID Interface #%d of device %s @ %d (0x%x)",this, _interface->GetInterfaceNumber(), _device->getName(), _device->GetAddress(), locationID );

    // Now that we have succesfully added our gate to the workloop, set our member variables
    //
    _gate = commandGate;
    _workLoop = workLoop;

    DecrementOutstandingIO();		// release the hold we put on at the beginning
#ifdef L4IOKIT
    IOLog("IOUSBHIDDriver::start returns true\n");
#endif
    return true;

ErrorExit:

        USBError(1, "%s[%p]::start - aborting startup", getName(), this);

    if ( commandGate != NULL )
    {
        if ( addEventSourceSuccess )
            workLoop->removeEventSource(commandGate);

        commandGate->release();
        commandGate = NULL;
    }

    if ( workLoop != NULL )
    {
        workLoop->release();
        workLoop = NULL;
    }

    if (_deviceDeadCheckThread)
        thread_call_free(_deviceDeadCheckThread);

    if (_clearFeatureEndpointHaltThread)
        thread_call_free(_clearFeatureEndpointHaltThread);

    if (_handleReportThread)
        thread_call_free(_handleReportThread);

    if (_interface)
        _interface->close(this);

    DecrementOutstandingIO();		// release the hold we put on at the beginning
    return false;
}


//=============================================================================================
//
//  message
//
//=============================================================================================
//
IOReturn
IOUSBHIDDriver::message( UInt32 type, IOService * provider,  void * argument )
{
    IOReturn	err;

    // Call our superclass to the handle the message first
    //
    err = super::message (type, provider, argument);

    switch ( type )
    {
        case kIOUSBMessagePortHasBeenReset:
            
            USBLog(3, "%s[%p]: received kIOUSBMessagePortHasBeenReset", getName(), this);
            
            _retryCount = kHIDDriverRetryCount;
            _deviceIsDead = FALSE;
            _deviceHasBeenDisconnected = FALSE;

            err = RearmInterruptRead();

            break;

        default:
            break;
    }

    return err;
}


//=============================================================================================
//
//  willTerminate
//
//=============================================================================================
//
bool
IOUSBHIDDriver::willTerminate( IOService * provider, IOOptionBits options )
{
    // this method is intended to be used to stop any pending I/O and to make sure that
    // we have begun getting our callbacks in order. by the time we get here, the
    // isInactive flag is set, so we really are marked as being done. we will do in here
    // what we used to do in the message method (this happens first)
    //
    USBLog(3, "%s[%p]::willTerminate isInactive = %d", getName(), this, isInactive());
    
    if (_interruptPipe)
    {
        _interruptPipe->Abort();
    }

    return super::willTerminate(provider, options);
}



//=============================================================================================
//
//  didTerminate
//
//=============================================================================================
//
bool
IOUSBHIDDriver::didTerminate( IOService * provider, IOOptionBits options, bool * defer )
{
    // this method comes at the end of the termination sequence. Hopefully, all of our outstanding IO is complete
    // in which case we can just close our provider and IOKit will take care of the rest. Otherwise, we need to
    // hold on to the device and IOKit will terminate us when we close it later
    //
    USBLog(3, "%s[%p]::didTerminate isInactive = %d, outstandingIO = %d", getName(), this, isInactive(), _outstandingIO);
    
    if (!_outstandingIO)
        _interface->close(this);
    else
        _needToClose = true;

    return super::didTerminate(provider, options, defer);
}



#pragma mark �������� IOHIDDevice Methods ���������
//================================================================================================
//
//  handleStart
//
//  Note: handleStart is not an IOKit thing, but is a IOHIDDevice thing. It is called from 
//  IOHIDDevice::start after some initialization by that method, but before it calls registerService
//  this method needs to open the provider, and make sure to have enough state (basically _interface
//  and _device) to be able to get information from the device. we do NOT need to start the interrupt read
//  yet, however
//
//================================================================================================
//
bool 
IOUSBHIDDriver::handleStart(IOService * provider)
{
    USBLog(7, "%s[%p]::handleStart", getName(), this);

    if ( !super::handleStart(provider))
    {
        return false;
    }

    // Open our provider so that nobody else an gain access to it
    //
    if( !provider->open(this))
    {
        USBError(1, "%s[%p]::handleStart - unable to open provider. returning false", getName(), this);
        return (false);
    }

    _interface = OSDynamicCast(IOUSBInterface, provider);
    if (!_interface)
    {
        USBError(1, "%s[%p]::handleStart - Our provider is not an IOUSBInterface!!", getName(), this);
        return false;
    }

    _device = _interface->GetDevice();
    if (!_device)
    {
        USBError(1, "%s[%p]::handleStart - Cannot get our provider's USB device.  This is bad.", getName(), this);
        return false;
    }

    return true;
}


//================================================================================================
//
//  handleStop
//
//  Note: handleStop is not an IOKit thing, but is a IOHIDDevice thing.
//
//================================================================================================
//
void
IOUSBHIDDriver::handleStop(IOService * provider)
{
    USBLog(7, "%s[%p]::handleStop", getName(), this);

    if (_buffer)
    {
        _buffer->release();
        _buffer = NULL;
    }

    if (_deviceDeadCheckThread)
    {
        thread_call_cancel(_deviceDeadCheckThread);
        thread_call_free(_deviceDeadCheckThread);
    }

    if (_clearFeatureEndpointHaltThread)
    {
        thread_call_cancel(_clearFeatureEndpointHaltThread);
        thread_call_free(_clearFeatureEndpointHaltThread);
    }
    if (_handleReportThread)
    {
        thread_call_cancel(_handleReportThread);
        thread_call_free(_handleReportThread);
    }
    
super::handleStop(provider);
}


//================================================================================================
//
//  getReport
//
//================================================================================================
//
IOReturn 
IOUSBHIDDriver::getReport(	IOMemoryDescriptor * report,
                                IOHIDReportType      reportType,
                                IOOptionBits         options )
{
    UInt8		reportID;
    IOReturn		ret;
    UInt8		usbReportType;
    IOUSBDevRequestDesc requestPB;

    // The following should really be an errata bit.  We will need to add that later.  For now
    // hardcode the check.  Some Logitech devices do not respond well to a GET_REPORT, so we need
    // to return unsupported for them.
    //
    if ( _device->GetVendorID() == 0x046d )
    {
        UInt16	prodID = _device->GetProductID();

        if ( (prodID == 0xc202) || (prodID == 0xc207) || (prodID == 0xc208) ||
             (prodID == 0xc209) || (prodID == 0xc20a) || (prodID == 0xc212) || 
             (prodID == 0xc285) || (prodID == 0xc293) || (prodID == 0xc294) ||
             (prodID == 0xc295) || (prodID == 0xc283) )
        {
            return kIOReturnUnsupported;
        }
    }
    
    IncrementOutstandingIO();

    // Get the reportID from the lower 8 bits of options
    //
    reportID = (UInt8) ( options & 0x000000ff);

    // And now save the report type
    //
    usbReportType = HIDMGR2USBREPORTTYPE(reportType);

#if ENABLE_HIDREPORT_LOGGING
    USBLog(3, "%s[%p]::getReport (%d, %p)", getName(), this, reportID, usbReportType);
#endif
    //--- Fill out device request form
    //
    requestPB.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBClass, kUSBInterface);
    requestPB.bRequest = kHIDRqGetReport;
    requestPB.wValue = (usbReportType << 8) | reportID;
    requestPB.wIndex = _interface->GetInterfaceNumber();
    requestPB.wLength = report->getLength();
    requestPB.pData = report;
    requestPB.wLenDone = 0;
    
    ret = _device->DeviceRequest(&requestPB);
    if ( ret != kIOReturnSuccess )
            USBLog(3, "%s[%p]::getReport request failed; err = 0x%x)", getName(), this, ret);
           
    DecrementOutstandingIO();
#if ENABLE_HIDREPORT_LOGGING
    USBLog(3, "%s[%p]::getReport returning", getName(), this);
#endif
    return ret;
}


//=============================================================================================
//
//  setReport
//
//=============================================================================================
//
IOReturn 
IOUSBHIDDriver::setReport( IOMemoryDescriptor * 	report,
                            IOHIDReportType      	reportType,
                            IOOptionBits         	options)
{
    UInt8		reportID;
    IOReturn		ret;
    UInt8		usbReportType;
    IOUSBDevRequestDesc requestPB;
    
    IncrementOutstandingIO();
    
    // Get the reportID from the lower 8 bits of options
    //
    reportID = (UInt8) ( options & 0x000000ff);

    // And now save the report type
    //
    usbReportType = HIDMGR2USBREPORTTYPE(reportType);
    
    // If we have an interrupt out pipe, try to use it for output type of reports.
    if ( kHIDOutputReport == usbReportType && _interruptOutPipe )
    {
        #if ENABLE_HIDREPORT_LOGGING
            USBLog(3, "%s[%p]::setReport sending out interrupt out pipe buffer (%p,%d):", getName(), this, report, report->getLength() );
            LogMemReport(report);
        #endif
        ret = _interruptOutPipe->Write(report);
        if (ret == kIOReturnSuccess)
        {       
            DecrementOutstandingIO();
            return ret;
        }
        else
        {
            USBLog(3, "%s[%p]::setReport _interruptOutPipe->Write failed; err = 0x%x)", getName(), this, ret);
        }
    }
        
    // If we did not succeed using the interrupt out pipe, we may still be able to use the control pipe.
    // We'll let the family check whether it's a disjoint descriptor or not (but right now it doesn't do it)
    //
    #if ENABLE_HIDREPORT_LOGGING
        USBLog(3, "%s[%p]::SetReport sending out control pipe:", getName(), this);
        LogMemReport( report);
    #endif

    //--- Fill out device request form
    requestPB.bmRequestType = USBmakebmRequestType(kUSBOut, kUSBClass, kUSBInterface);
    requestPB.bRequest = kHIDRqSetReport;
    requestPB.wValue = (usbReportType << 8) | reportID;
    requestPB.wIndex = _interface->GetInterfaceNumber();
    requestPB.wLength = report->getLength();
    requestPB.pData = report;
    requestPB.wLenDone = 0;
    
    ret = _device->DeviceRequest(&requestPB);
    if (ret != kIOReturnSuccess)
            USBLog(3, "%s[%p]::setReport request failed; err = 0x%x)", getName(), this, ret);
        
    DecrementOutstandingIO();
#if ENABLE_HIDREPORT_LOGGING
    USBLog(3, "%s[%p]::setReport returning", getName(), this);
#endif
    return ret;
}


//=============================================================================================
//
//  newLocationIDNumber
//
//=============================================================================================
//
OSNumber *
IOUSBHIDDriver::newLocationIDNumber() const
{
    OSNumber * newLocationID = NULL;

    if (_interface != NULL)
    {
        OSNumber * locationID = (OSNumber *)_interface->getProperty(kUSBDevicePropertyLocationID);
        if ( locationID )
            // I should be able to just duplicate locationID, but no OSObject::clone() or such.
            newLocationID = OSNumber::withNumber(locationID->unsigned32BitValue(), 32);
    }

    return newLocationID;
}


//=============================================================================================
//
//  newManufacturerString
//
//=============================================================================================
//
OSString *
IOUSBHIDDriver::newManufacturerString() const
{
    char 	manufacturerString[256];
    UInt32 	strSize;
    UInt8 	index;
    IOReturn	err;

    manufacturerString[0] = 0;

    index = _device->GetManufacturerStringIndex();
    strSize = sizeof(manufacturerString);

    err = GetIndexedString(index, (UInt8 *)manufacturerString, &strSize);

    if ( err == kIOReturnSuccess )
        return OSString::withCString(manufacturerString);
    else
        return NULL;
}


//=============================================================================================
//
//  newProductIDNumber
//
//=============================================================================================
//
OSNumber *
IOUSBHIDDriver::newProductIDNumber() const
{
    UInt16 productID = 0;

    if (_device != NULL)
        productID = _device->GetProductID();

    return OSNumber::withNumber(productID, 16);
}


//=============================================================================================
//
//  newProductString
//
//=============================================================================================
//
OSString *
IOUSBHIDDriver::newProductString() const
{
    char 	productString[256];
    UInt32 	strSize;
    UInt8 	index;
    IOReturn	err;

    productString[0] = 0;

    index = _device->GetProductStringIndex();
    strSize = sizeof(productString);

    err = GetIndexedString(index, (UInt8 *)productString, &strSize);

    if ( err == kIOReturnSuccess )
        return OSString::withCString(productString);
    else
        return NULL;
}


//=============================================================================================
//
//  newReportDescriptor
//
//=============================================================================================
//
IOReturn
IOUSBHIDDriver::newReportDescriptor(IOMemoryDescriptor ** desc) const
{
    IOBufferMemoryDescriptor * 	bufferDesc = NULL;
    IOReturn ret = 		kIOReturnNoMemory;
    IOUSBHIDDriver * 		me = (IOUSBHIDDriver *) this;

    // Get the proper HID report descriptor size.
    //
    UInt32 inOutSize = 0;
    ret = me->GetHIDDescriptor(kUSBReportDesc, 0, NULL, &inOutSize);

    if ( ret == kIOReturnSuccess && inOutSize != 0)
    {
        bufferDesc = IOBufferMemoryDescriptor::withCapacity(inOutSize, kIODirectionOutIn);
    }

    if (bufferDesc)
    {
        ret = me->GetHIDDescriptor(kUSBReportDesc, 0, (UInt8 *)bufferDesc->getBytesNoCopy(), &inOutSize);

        if ( ret != kIOReturnSuccess )
        {
            bufferDesc->release();
            bufferDesc = NULL;
        }
    }

    *desc = bufferDesc;

    return ret;
}


//=============================================================================================
//
//  newSerialNumberString
//
//=============================================================================================
//
OSString * 
IOUSBHIDDriver::newSerialNumberString() const
{
    char 	serialNumberString[256];
    UInt32 	strSize;
    UInt8 	index;
    IOReturn	err;
    
    serialNumberString[0] = 0;

    index = _device->GetSerialNumberStringIndex();
    strSize = sizeof(serialNumberString);
    
    err = GetIndexedString(index, (UInt8 *)serialNumberString, &strSize);
    
    if ( err == kIOReturnSuccess )
        return OSString::withCString(serialNumberString);
    else
        return NULL;
}


//=============================================================================================
//
//  newTransportString
//
//=============================================================================================
//
OSString *
IOUSBHIDDriver::newTransportString() const
{
    return OSString::withCString("USB");
}

//=============================================================================================
//
//  newVendorIDNumber
//
//=============================================================================================
//
OSNumber *
IOUSBHIDDriver::newVendorIDNumber() const
{
    UInt16 vendorID = 0;

    if (_device != NULL)
        vendorID = _device->GetVendorID();

    return OSNumber::withNumber(vendorID, 16);
}


//=============================================================================================
//
//  newVersionNumber
//
//=============================================================================================
//
OSNumber *
IOUSBHIDDriver::newVersionNumber() const
{
    UInt16 releaseNum = 0;

    if (_device != NULL)
        releaseNum = _device->GetDeviceRelease();

    return OSNumber::withNumber(releaseNum, 16);
}


//=============================================================================================
//
//  newCountryCodeNumber
//
//=============================================================================================
//
OSNumber *
IOUSBHIDDriver::newCountryCodeNumber() const
{
    IOUSBHIDDescriptor 		*theHIDDesc;
    
    if (!_interface)
    {
        USBLog(2, "%s[%p]::newCountryCodeNumber - no _interface", getName(), this);
        return NULL;
    }
    
    // From the interface descriptor, get the HID descriptor.
    theHIDDesc = (IOUSBHIDDescriptor *)_interface->FindNextAssociatedDescriptor(NULL, kUSBHIDDesc);
    
    if (theHIDDesc == NULL)
    {
        USBLog(2, "%s[%p]::newCountryCodeNumber - FindNextAssociatedDescriptor(NULL, kUSBHIDDesc) failed", getName(), this);
        return NULL;
    }
    
    return OSNumber::withNumber((unsigned long long)theHIDDesc->hidCountryCode, 8);
}


#pragma mark �������� Static Methods ���������
//=============================================================================================
//
//  InterruptReadHandlerEntry is called to process any data coming in through our interrupt pipe
//
//=============================================================================================
//
void 
IOUSBHIDDriver::InterruptReadHandlerEntry(OSObject *target, void *param, IOReturn status, UInt32 bufferSizeRemaining)
{
    IOUSBHIDDriver *	me = OSDynamicCast(IOUSBHIDDriver, target);
    AbsoluteTime        timeStamp;
    
    if (!me)
        return;
    
    clock_get_uptime(&timeStamp);
    me->InterruptReadHandler(status, bufferSizeRemaining, timeStamp);
    me->DecrementOutstandingIO();
}

void 
IOUSBHIDDriver::InterruptReadHandlerWithTimeStampEntry(OSObject *target, void *param, IOReturn status, UInt32 bufferSizeRemaining, AbsoluteTime timeStamp)
{
    IOUSBHIDDriver *	me = OSDynamicCast(IOUSBHIDDriver, target);
    
    if (!me)
        return;
    
    me->InterruptReadHandler(status, bufferSizeRemaining, timeStamp);
    me->DecrementOutstandingIO();
}


void 
IOUSBHIDDriver::InterruptReadHandler(IOReturn status, UInt32 bufferSizeRemaining, AbsoluteTime timeStamp)
{
    bool			queueAnother = false;					// make the default to not queue another - since the callout threads usually do
    IOReturn		err = kIOReturnSuccess;
    UInt64			timeElapsed;
    AbsoluteTime	timeStop;
    
    // Calculate the # of milliseconds since we woke up.  If this is <= the amount specified in _msToIgnoreTransactionsAfterWake, then
    // we will ignore the transaction.
    //clock_get_uptime(&timeStop);
    //SUB_ABSOLUTETIME(&timeStop, &timeStamp);
    //absolutetime_to_nanoseconds(timeStop, &timeElapsed);
	//
    // USBLog(5,"%s[%p]::InterruptReadHandler:  microsecs since filter interrupt:  %qd", getName(), this, timeElapsed / 1000);
    // USBLog(5,"%s[%p]::InterruptReadHandler:  time.hi 0x%x time.lo 0x%x", getName(), this, timeStamp.hi, timeStamp.lo);
    // kprintf("%s[%p]::InterruptReadHandler:  time.hi 0x%x time.lo 0x%x\n", getName(), this, timeStamp.hi, timeStamp.lo);

    switch (status)
    {
        case kIOReturnOverrun:
#ifdef L4IOKIT
#if 0
            IOLog("%s[%p]::InterruptReadHandler kIOReturnOverrun error\n", getName(), this);
#endif
#endif
            USBLog(3, "%s[%p]::InterruptReadHandler kIOReturnOverrun error", getName(), this);
            // This is an interesting error, as we have the data that we wanted and more...  We will use this
            // data but first we need to clear the stall and reset the data toggle on the device. We then just 
            // fall through to the kIOReturnSuccess case.
            // 01-18-02 JRH If we are inactive, then ignore this
			if (!isInactive())
            {
                //
                // First, clear the halted bit in the controller
                //
                _interruptPipe->ClearStall();
				
                // And call the device to reset the endpoint as well
                //
                IncrementOutstandingIO();
                thread_call_enter(_clearFeatureEndpointHaltThread);
            }
            // Fall through to process the data.
            
        case kIOReturnSuccess:
            // Reset the retry count, since we had a successful read
            //
            _retryCount = kHIDDriverRetryCount;
			
            // Handle the data.  We do this on a callout thread so that we don't block all
            // of USB I/O if the HID system is blocked
            //
            IncrementOutstandingIO();
#ifdef L4IOKIT
#if 0
	    IOLog("scheduling _handleReportThread\n");
#endif
#endif
            thread_call_enter1(_handleReportThread, (thread_call_param_t) &timeStamp);
            break;
			
        case kIOReturnNotResponding:
            USBLog(3, "%s[%p]::InterruptReadHandler kIOReturnNotResponding error", getName(), this);
            // If our device has been disconnected or we're already processing a
            // terminate message, just go ahead and close the device (i.e. don't
            // queue another read.  Otherwise, go check to see if the device is
            // around or not. 
            //
            if ( !_deviceHasBeenDisconnected && !isInactive() )
			{
				USBLog(3, "%s[%p]::InterruptReadHandler Checking to see if HID device is still connected", getName(), this);
				IncrementOutstandingIO();
				thread_call_enter(_deviceDeadCheckThread );
				
				// Before requeueing, we need to clear the stall
				//
				_interruptPipe->ClearStall();
				queueAnother = true;						// if the device is really dead, this request will get aborted
			}
			break;
            
		case kIOReturnAborted:
			// This generally means that we are done, because we were unplugged, but not always
            //
            if (!isInactive() && !_deviceIsDead )
            {
                USBLog(3, "%s[%p]::InterruptReadHandler error kIOReturnAborted. Try again.", getName(), this);
				queueAnother = true;
            }
			break;
            
        case kIOReturnUnderrun:
        case kIOUSBPipeStalled:
        case kIOUSBLinkErr:
        case kIOUSBNotSent2Err:
        case kIOUSBNotSent1Err:
        case kIOUSBBufferUnderrunErr:
        case kIOUSBBufferOverrunErr:
        case kIOUSBWrongPIDErr:
        case kIOUSBPIDCheckErr:
        case kIOUSBDataToggleErr:
        case kIOUSBBitstufErr:
        case kIOUSBCRCErr:
		case kIOUSBHighSpeedSplitError:
            // These errors will halt the endpoint, so before we requeue the interrupt read, we have
            // to clear the stall at the controller and at the device.
            
            USBLog(3, "%s[%p]::InterruptReadHandler OHCI error (0x%x) reading interrupt pipe", getName(), this, status);
            // 01-18-02 JRH If we are inactive, then ignore this
			if (!isInactive())
            {
                // First, clear the halted bit in the controller
                //
                _interruptPipe->ClearStall();
				
                // And call the device to reset the endpoint as well
                //
                IncrementOutstandingIO();
                thread_call_enter(_clearFeatureEndpointHaltThread);					// this will rearm the request when it is done
            }
			break;
			
        default:
            // We should handle other errors more intelligently, but
            // for now just return and assume the error is recoverable.
            USBLog(3, "%s[%p]::InterruptReadHandler Unknown error (0x%x) reading interrupt pipe", getName(), this, status);
			if ( !isInactive() )
                _interruptPipe->ClearStall();
			queueAnother = true;													// no callout to go to - rearm it now
			
			break;
    }

    if ( queueAnother )
    {
        // Queue up another one before we leave.
        //
        (void) RearmInterruptRead();
    }
}


//=============================================================================================
//
//  CheckForDeadDevice
//
//  Is called when we get a kIODeviceNotResponding error in our interrupt pipe.
//  This can mean that (1) the device was unplugged, or (2) we lost contact
//  with our hub.  In case (1), we just need to close the driver and go.  In
//  case (2), we need to ask if we are still attached.  If we are, then we update 
//  our retry count.  Once our retry count (3 from the 9 sources) are exhausted, then we
//  issue a DeviceReset to our provider, with the understanding that we will go
//  away (as an interface).
//
//=============================================================================================
//
void 
IOUSBHIDDriver::CheckForDeadDeviceEntry(OSObject *target)
{
    IOUSBHIDDriver *	me = OSDynamicCast(IOUSBHIDDriver, target);
    
    if (!me)
        return;
        
    me->CheckForDeadDevice();
    me->DecrementOutstandingIO();
}

void 
IOUSBHIDDriver::CheckForDeadDevice()
{
    IOReturn			err = kIOReturnSuccess;

    if ( _deviceDeadThreadActive )
    {
        USBLog(3, "%s[%p]::CheckForDeadDevice already active, returning", getName(), this);
        return;
    }
    
    _deviceDeadThreadActive = TRUE;

    // Are we still connected?
    //
    if ( _interface && _device )
    {
        err = _device->message(kIOUSBMessageHubIsDeviceConnected, NULL, 0);
    
        if ( kIOReturnSuccess == err )
        {
            // Looks like the device is still plugged in.  Have we reached our retry count limit?
            //
            if ( --_retryCount == 0 )
            {
                _deviceIsDead = TRUE;
                USBLog(3, "%s[%p]: Detected an kIONotResponding error but still connected.  Resetting port", getName(), this);
                
                if (_interruptPipe)
                {
                    _interruptPipe->Abort();  // This will end up closing the interface as well.
                }
                
                // OK, let 'er rip.  Let's do the reset thing
                //
                _device->ResetDevice();
                    
            }
        }
        else
        {
            // Device is not connected -- our device has gone away.
            //
            _deviceHasBeenDisconnected = TRUE;

            USBLog(5, "%s[%p]: CheckForDeadDevice: device %s has been unplugged", getName(), this, _device->getName() );
        }
    }
    _deviceDeadThreadActive = FALSE;
}


//=============================================================================================
//
//  ClearFeatureEndpointHaltEntry is called when we get an OHCI error from our interrupt read
//  (except for kIOReturnNotResponding  which will check for a dead device).  In these cases
//  we need to clear the halted bit in the controller AND we need to reset the data toggle on the
//  device.
//
//=============================================================================================
//
void
IOUSBHIDDriver::ClearFeatureEndpointHaltEntry(OSObject *target)
{
    IOUSBHIDDriver *	me = OSDynamicCast(IOUSBHIDDriver, target);

    if (!me)
        return;

    me->ClearFeatureEndpointHalt();
    me->DecrementOutstandingIO();
}

void
IOUSBHIDDriver::ClearFeatureEndpointHalt( )
{
    IOReturn			status;
    IOUSBDevRequest		request;
    UInt32			retries = 2;
    
    // Clear out the structure for the request
    //
    bzero( &request, sizeof(IOUSBDevRequest));
    
    while ( retries > 0 )
    {
        retries--;
        
        // Build the USB command to clear the ENDPOINT_HALT feature for our interrupt endpoint
        //
        request.bmRequestType 	= USBmakebmRequestType(kUSBNone, kUSBStandard, kUSBEndpoint);
        request.bRequest 		= kUSBRqClearFeature;
        request.wValue		= 0;	// Zero is ENDPOINT_HALT
        request.wIndex		= _interruptPipe->GetEndpointNumber() | 0x80 ; // bit 7 sets the direction of the endpoint to IN
        request.wLength		= 0;
        request.pData 		= NULL;
        
        // Send the command over the control endpoint
        //
        status = _device->DeviceRequest(&request, 5000, 0);
        
        if ( status != kIOReturnSuccess )
        {
            USBLog(3, "%s[%p]::ClearFeatureEndpointHalt -  DeviceRequest returned: 0x%x, retries = %d", getName(), this, status, retries);
            IOSleep(100);
        }
        else
            break;
    }
    
    // Now that we've sent the ENDPOINT_HALT clear feature, we need to requeue the interrupt read.  Note
    // that we are doing this even if we get an error from the DeviceRequest.
    //
    (void) RearmInterruptRead();
}

//=============================================================================================
//
//  HandleReportEntry 
//
//  Calls the HID System to handle the report we got.  Note that we are relying on the fact
//  that the _buffer data will not be overwritten.  We can assume this because we are not 
//  rearming the Read until after we are done with handleReport
//=============================================================================================
//
void
IOUSBHIDDriver::HandleReportEntry(OSObject *target, thread_call_param_t timeStamp)
{
    IOUSBHIDDriver *	me = OSDynamicCast(IOUSBHIDDriver, target);
    AbsoluteTime		theTime;
	
    if (!me)
        return;
    
	// Make a copy  of the timeStamp parameter, since it can be overwritten by the next transaction
	//
	theTime = * (AbsoluteTime *)timeStamp;
    me->HandleReport( theTime );
    me->DecrementOutstandingIO();
}

void
IOUSBHIDDriver::HandleReport(AbsoluteTime timeStamp)
{
    IOReturn			status;
    IOUSBDevRequest		request;
   
#ifdef L4IOKIT 
#if 0
    IOLog("%s[%p]::HandleReport report came in:\n", getName(), this);
#endif
#endif
#if ENABLE_HIDREPORT_LOGGING 
    USBLog(6, "%s[%p]::HandleReport report came in:", getName(), this);
    LogMemReport(_buffer);
#endif
	//status = handleReportWithTime(timeStamp, _buffer);
	status = handleReport(_buffer);
	if ( status != kIOReturnSuccess)
	{
		USBLog(1, "%s[%p]::HandleReport handleReportWithTime returned 0x%x:", getName(), this, status);
    }
	
    if ( !isInactive() )
    {
        // Rearm the interrupt read
        //
        (void) RearmInterruptRead();
    }
}

#pragma mark �������� HID Driver Methods ���������
//=============================================================================================
//
//  getMaxReportSize
//
//  Looks at both the input and feature report sizes and returns the maximum
//
//=============================================================================================
//
UInt32
IOUSBHIDDriver::getMaxReportSize()
{
    UInt32	maxInputReportSize = 0;
    UInt32	maxFeatureReportSize = 0;

    OSNumber * inputReportSize = (OSNumber *)getProperty(kIOHIDMaxInputReportSizeKey);
    if ( inputReportSize )
        maxInputReportSize = inputReportSize->unsigned32BitValue();

    OSNumber * featureReportSize = (OSNumber *)getProperty(kIOHIDMaxFeatureReportSizeKey);
    if ( featureReportSize )
        maxFeatureReportSize = featureReportSize->unsigned32BitValue();

    return ( (maxInputReportSize > maxFeatureReportSize) ? maxInputReportSize : maxFeatureReportSize);

}


//=============================================================================================
//
//  GetHIDDescriptor
//
// HIDGetHIDDescriptor is used to get a specific HID descriptor from a HID device
// (such as a report descriptor).
//
//=============================================================================================
//
IOReturn
IOUSBHIDDriver::GetHIDDescriptor(UInt8 inDescriptorType, UInt8 inDescriptorIndex, UInt8 *vOutBuf, UInt32 *vOutSize)
{
    IOUSBDevRequest 		requestPB;
    IOUSBHIDDescriptor 		*theHIDDesc;
    IOUSBHIDReportDesc 		*hidTypeSizePtr;	// For checking owned descriptors.
    UInt8 			*descPtr;
    UInt32 			providedBufferSize;
    UInt16 			descSize;
    UInt8 			descType;
    UInt8 			typeIndex;
    UInt8 			numberOwnedDesc;
    IOReturn 		err = kIOReturnSuccess;
    Boolean			foundIt;

    if (!vOutSize)
        return  kIOReturnBadArgument;

    if (!_interface)
    {
        USBLog(2, "%s[%p]::GetHIDDescriptor - no _interface", getName(), this);
        return kIOReturnNotFound;
    }

    // From the interface descriptor, get the HID descriptor.
    theHIDDesc = (IOUSBHIDDescriptor *)_interface->FindNextAssociatedDescriptor(NULL, kUSBHIDDesc);

    if (theHIDDesc == NULL)
    {
        USBLog(2, "%s[%p]::GetHIDDescriptor - FindNextAssociatedDescriptor(NULL, kUSBHIDDesc) failed", getName(), this);
        return kIOReturnNotFound;
    }

    // Remember the provided buffer size
    providedBufferSize = *vOutSize;
    // Are we looking for just the main HID descriptor?
    if (inDescriptorType == kUSBHIDDesc || (inDescriptorType == 0 && inDescriptorIndex == 0))
    {
        descSize = theHIDDesc->descLen;
        descPtr = (UInt8 *)theHIDDesc;

        // No matter what, set the return size to the actual size of the data.
        *vOutSize = descSize;

        // If the provided size is 0, they are just asking for the size, so don't return an error.
        if (providedBufferSize == 0)
            err = kIOReturnSuccess;
        // Otherwise, if the buffer too small, return buffer too small error.
        else if (descSize > providedBufferSize)
            err = kIOReturnNoSpace;
        // Otherwise, if the buffer nil, return that error.
        else if (vOutBuf == NULL)
            err = kIOReturnBadArgument;
        // Otherwise, looks good, so copy the deiscriptor.
        else
        {
            //IOLog("  Copying HIDDesc w/ vOutBuf = 0x%x, descPtr = 0x%x, and descSize = 0x%x.\n", vOutBuf, descPtr, descSize);
            memcpy(vOutBuf, descPtr, descSize);
        }
    }
    else
    {	// Looking for a particular type of descriptor.
      // The HID descriptor tells how many endpoint and report descriptors it contains.
        numberOwnedDesc = ((IOUSBHIDDescriptor *)theHIDDesc)->hidNumDescriptors;
        hidTypeSizePtr = (IOUSBHIDReportDesc *)&((IOUSBHIDDescriptor *)theHIDDesc)->hidDescriptorType;
        //IOLog("     %d owned descriptors start at %08x\n", numberOwnedDesc, (unsigned int)hidTypeSizePtr);

        typeIndex = 0;
        foundIt = false;
        err = kIOReturnNotFound;
        for (UInt8 i = 0; i < numberOwnedDesc; i++)
        {
            descType = hidTypeSizePtr->hidDescriptorType;

            // Are we indexing for a specific type?
            if (inDescriptorType != 0)
            {
                if (inDescriptorType == descType)
                {
                    if (inDescriptorIndex == typeIndex)
                    {
                        foundIt = true;
                    }
                    else
                    {
                        typeIndex++;
                    }
                }
            }
            // Otherwise indexing across descriptors in general.
            // (If looking for any type, index must be 1 based or we'll get HID descriptor.)
            else if (inDescriptorIndex == i + 1)
            {
                //IOLog("  said we found it because inDescriptorIndex = 0x%x.\n", inDescriptorIndex);
                typeIndex = i;
                foundIt = true;
            }

            if (foundIt)
            {
                err = kIOReturnSuccess;		// Maybe
                                         //IOLog("     Found the requested owned descriptor, %d.\n", i);
                descSize = (hidTypeSizePtr->hidDescriptorLengthHi << 8) + hidTypeSizePtr->hidDescriptorLengthLo;

                // Did we just want the size or the whole descriptor?
                // No matter what, set the return size to the actual size of the data.
                *vOutSize = descSize;	// OSX: Won't get back if we return an error!

                // If the provided size is 0, they are just asking for the size, so don't return an error.
                if (providedBufferSize == 0)
                    err = kIOReturnSuccess;
                // Otherwise, if the buffer too small, return buffer too small error.
                else if (descSize > providedBufferSize)
                    err = kIOReturnNoSpace;
                // Otherwise, if the buffer nil, return that error.
                else if (vOutBuf == NULL)
                    err = kIOReturnBadArgument;
                // Otherwise, looks good, so copy the descriptor.
                else
                {
                    if (!_device)
                    {
                        USBLog(2, "%s[%p]::GetHIDDescriptor - no _device", getName(), this);
                        return kIOReturnNotFound;
                    }

                    //IOLog("  Requesting new desscriptor.\n");
                    requestPB.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBInterface);
                    requestPB.bRequest = kUSBRqGetDescriptor;
                    requestPB.wValue = (inDescriptorType << 8) + typeIndex;		// type and index
                    requestPB.wIndex = _interface->GetInterfaceNumber();
                    requestPB.wLength = descSize;
                    requestPB.pData = vOutBuf;						// So we don't have to do any allocation here.
                    err = _device->DeviceRequest(&requestPB, 5000, 0);
                    if (err != kIOReturnSuccess)
                    {
                        USBLog(3, "%s[%p]::GetHIDDescriptor Final request failed; err = 0x%x", getName(), this, err);
                        return err;
                    }
                }
                break;	// out of for i loop.
            }
            // Make sure we add 3 bytes not 4 regardless of struct alignment.
            hidTypeSizePtr = (IOUSBHIDReportDesc *)(((UInt8 *)hidTypeSizePtr) + 3);
        }
    }
    return err;
}


//=============================================================================================
//
//  GetIndexedString
//
//=============================================================================================
//
IOReturn
IOUSBHIDDriver::GetIndexedString(UInt8 index, UInt8 *vOutBuf, UInt32 *vOutSize, UInt16 lang) const
{
    char 	strBuf[256];
    UInt16 	strLen = sizeof(strBuf) - 1;	// GetStringDescriptor MaxLen = 255
    UInt32 	outSize = *vOutSize;
    IOReturn 	err;

    // Valid string index?
    if (index == 0)
    {
        return kIOReturnBadArgument;
    }

    // Valid language?
    if (lang == 0)
    {
        lang = 0x409;	// Default is US English.
    }

    err = _device->GetStringDescriptor((UInt8)index, strBuf, strLen, (UInt16)lang);
    
    // When string is returned, it has been converted from Unicode and is null terminated!

    if (err != kIOReturnSuccess)
    {
        return err;
    }

    // We return the length of the string plus the null terminator,
    // but don't say a null string is 1 byte long.
    //
    strLen = (strBuf[0] == 0) ? 0 : strlen(strBuf) + 1;

    if (outSize == 0)
    {
        *vOutSize = strLen;
        return kIOReturnSuccess;
    }
    else if (outSize < strLen)
    {
        return kIOReturnMessageTooLarge;
    }

    strcpy((char *)vOutBuf, strBuf);
    *vOutSize = strLen;
    return kIOReturnSuccess;
}

//=============================================================================================
//
//  newIndexedString
//
//=============================================================================================
//
OSString *
IOUSBHIDDriver::newIndexedString(UInt8 index) const
{
    char string[256];
    UInt32 strSize;
    IOReturn	err = kIOReturnSuccess;

    string[0] = 0;
    strSize = sizeof(string);

    err = GetIndexedString(index, (UInt8 *)string, &strSize );

    if ( err == kIOReturnSuccess )
        return OSString::withCString(string);
    else
        return NULL;
}

//================================================================================================
//
//  StartFinalProcessing
//
//  This method may have a confusing name. This is not talking about Final Processing of the driver (as in
//  the driver is going away or something like that. It is talking about FinalProcessing of the start method.
//  It is called as the very last thing in the start method, and by default it issues a read on the interrupt
//  pipe.
//
//================================================================================================
//
IOReturn
IOUSBHIDDriver::StartFinalProcessing(void)
{
    IOReturn	err = kIOReturnSuccess;

    _completionWithTimeStamp.target = (void *)this;
    _completionWithTimeStamp.action = (IOUSBCompletionActionWithTimeStamp) &IOUSBHIDDriver::InterruptReadHandlerWithTimeStampEntry;
    _completionWithTimeStamp.parameter = (void *)0;
    
    _completion.target = (void *)this;
    _completion.action = (IOUSBCompletionAction) &IOUSBHIDDriver::InterruptReadHandlerEntry;
    _completion.parameter = (void *)0;
    
    err = RearmInterruptRead();

    return err;
}


//================================================================================================
//
//  SetIdleMillisecs
//
//================================================================================================
//
IOReturn
IOUSBHIDDriver::SetIdleMillisecs(UInt16 msecs)
{
    IOReturn    		err = kIOReturnSuccess;
    IOUSBDevRequest		request;

    request.bmRequestType = USBmakebmRequestType(kUSBOut, kUSBClass, kUSBInterface);
    request.bRequest = kHIDRqSetIdle;  //See USBSpec.h
    request.wValue = (msecs/4) << 8;
    request.wIndex = _interface->GetInterfaceNumber();
    request.wLength = 0;
    request.pData = NULL;

    err = _device->DeviceRequest(&request, 5000, 0);
    if (err != kIOReturnSuccess)
    {
        USBLog(3, "%s[%p]::SetIdleMillisecs returned error 0x%x",getName(), this, err);
    }

    return err;

}

//================================================================================================
//
//  SetIdleMillisecs
//
//================================================================================================
//
IOReturn
IOUSBHIDDriver::SetProtocol(UInt32 protocol)
{
    IOReturn    		err = kIOReturnSuccess;
    IOUSBDevRequest		request;

    request.bmRequestType = USBmakebmRequestType(kUSBOut, kUSBClass, kUSBInterface);
    request.bRequest = kHIDRqSetProtocol;  //See USBSpec.h
    request.wValue = protocol;
    request.wIndex = _interface->GetInterfaceNumber();
    request.wLength = 0;
    request.pData = NULL;

    err = _device->DeviceRequest(&request, 5000, 0);
    if (err != kIOReturnSuccess)
    {
        USBLog(3, "%s[%p]:::SetProtocol returned error 0x%x",getName(), this, err);
    }

    return err;

}

#pragma mark �������� Bookkeeping Methods ���������
//================================================================================================
//
//   ChangeOutstandingIO function
//
//================================================================================================
//
IOReturn
IOUSBHIDDriver::ChangeOutstandingIO(OSObject *target, void *param1, void *param2, void *param3, void *param4)
{
    IOUSBHIDDriver *me = OSDynamicCast(IOUSBHIDDriver, target);
    UInt32	direction = (UInt32)param1;
    
    if (!me)
    {
	USBLog(1, "IOUSBHIDDriver::ChangeOutstandingIO - invalid target");
	return kIOReturnSuccess;
    }
    switch (direction)
    {
	case 1:
	    me->_outstandingIO++;
	    break;
	    
	case -1:
	    if (!--me->_outstandingIO && me->_needToClose)
	    {
		USBLog(3, "%s[%p]::ChangeOutstandingIO isInactive = %d, outstandingIO = %d - closing device", me->getName(), me, me->isInactive(), me->_outstandingIO);
		me->_interface->close(me);
	    }
	    break;
	    
	default:
	    USBLog(1, "%s[%p]::ChangeOutstandingIO - invalid direction", me->getName(), me);
    }
    return kIOReturnSuccess;
}


//================================================================================================
//
//   DecrementOutstandingIO function
//
//================================================================================================
//
void
IOUSBHIDDriver::DecrementOutstandingIO(void)
{
    if (!_gate)
    {
	if (!--_outstandingIO && _needToClose)
	{
	    USBLog(3, "%s[%p]::DecrementOutstandingIO isInactive = %d, outstandingIO = %d - closing device", getName(), this, isInactive(), _outstandingIO);
	    _interface->close(this);
	}
	return;
    }
    _gate->runAction(ChangeOutstandingIO, (void*)-1);
}


//================================================================================================
//
//   IncrementOutstandingIO function
//
//================================================================================================
//
void
IOUSBHIDDriver::IncrementOutstandingIO(void)
{
    if (!_gate)
    {
	_outstandingIO++;
	return;
    }
    _gate->runAction(ChangeOutstandingIO, (void*)1);
}



#pragma mark �������� Debug Methods ���������
#if ENABLE_HIDREPORT_LOGGING
void 
IOUSBHIDDriver::LogMemReport(IOMemoryDescriptor * reportBuffer)
{
    IOByteCount reportSize;
    char outBuffer[1024];
    char in[1024];
    char *out;
    char inChar;
    
    out = (char *)&outBuffer;
    reportSize = reportBuffer->getLength();
    reportBuffer->readBytes(0, in, reportSize );
    if (reportSize > 256) reportSize = 256;
    
    for (unsigned int i = 0; i < reportSize; i++)
    {
        inChar = in[i];
        *out++ = ' ';
        *out++ = GetHexChar(inChar >> 4);
        *out++ = GetHexChar(inChar & 0x0F);
    }
    
    *out = 0;
    
    USBLog(6, outBuffer);
	// kprintf("IOUSBHIDDriver::handleReport %s\n",outBuffer);
}

char 
IOUSBHIDDriver::GetHexChar(char hexChar)
{
    char hexChars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    return hexChars[0x0F & hexChar];
}
#endif


#pragma mark �������� Obsolete Methods ���������
//================================================================================================
//
//   Obsolete methods
//
//================================================================================================
//
void
IOUSBHIDDriver::processPacket(void *data, UInt32 size)
{
    return;
}

IOReturn
IOUSBHIDDriver::GetReport(UInt8 inReportType, UInt8 inReportID, UInt8 *vInBuf, UInt32 *vInSize)
{
    return kIOReturnSuccess;
}

IOReturn
IOUSBHIDDriver::SetReport(UInt8 outReportType, UInt8 outReportID, UInt8 *vOutBuf, UInt32 vOutSize)
{
    return kIOReturnSuccess;
}

#pragma mark �������� Padding Methods ���������
OSMetaClassDefineReservedUsed(IOUSBHIDDriver,  0);
IOReturn
IOUSBHIDDriver::RearmInterruptRead()
{
    IOReturn    err = kIOReturnSuccess;
    
    if ( _buffer == NULL )
        return err;
    
    // Queue up another one before we leave.
    //
    IncrementOutstandingIO();
    err = _interruptPipe->Read(_buffer, 0, 0, _buffer->getLength(), &_completionWithTimeStamp);
    if ( err != kIOReturnSuccess)
    {
        // If we get an unsupported error, try to read w/out the completionWithTimeStamp
        //
        if ( err == kIOReturnUnsupported )
        {
            err = _interruptPipe->Read(_buffer, 0, 0, _buffer->getLength(), &_completion);
            
            if ( err != kIOReturnSuccess)
            {
                // This is bad.  We probably shouldn't continue on from here.
                //
                USBError(1, "%s[%p]::InterruptReadHandler immediate error 0x%x queueing read\n", getName(), this, err);
                DecrementOutstandingIO();
            }
        }
    }
    
    return err;
}

OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  1);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  2);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  3);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  4);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  5);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  6);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  7);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  8);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver,  9);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 10);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 11);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 12);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 13);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 14);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 15);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 16);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 17);
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 18); 
OSMetaClassDefineReservedUnused(IOUSBHIDDriver, 19);


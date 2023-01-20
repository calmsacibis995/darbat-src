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
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
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


//�����������������������������������������������������������������������������
//	Includes
//�����������������������������������������������������������������������������

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

// General OS Services header files
#include <libkern/OSByteOrder.h>

// This class' header file
#include "IOUSBMassStorageClass.h"

#include "Debugging.h"

#include <IOKit/scsi-commands/IOSCSIPeripheralDeviceNub.h>

//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

// Macros for printing debugging information
#if (USB_MASS_STORAGE_DEBUG == 1)
#define PANIC_NOW(x)	IOPanic x
// Override the debug level for USBLog to make sure our logs make it out and then import
// the logging header.
#define DEBUG_LEVEL		1
#include <IOKit/usb/IOUSBLog.h>
#define STATUS_LOG(x)	USBLog x
#else
#define STATUS_LOG(x)
#define PANIC_NOW(x)
#endif

#define DEBUGGING_LEVEL 0
#define DEBUGLOG kprintf

#define super IOSCSIProtocolServices

OSDefineMetaClassAndStructors( IOUSBMassStorageClass, IOSCSIProtocolServices )

//�����������������������������������������������������������������������������
//	� init - Called at initialization time							   [PUBLIC]
//�����������������������������������������������������������������������������

bool 
IOUSBMassStorageClass::init( OSDictionary * propTable )
{
#ifdef L4IOKIT
    IOLog("IOUSBMassStorageClass::%s called\n", __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    if( super::init( propTable ) == false)
    {
		return false;
    }

    return true;
}


//�����������������������������������������������������������������������������
//	� start - Called at services start time	(after successful matching)
//																	   [PUBLIC]
//�����������������������������������������������������������������������������

bool 
IOUSBMassStorageClass::start( IOService * provider )
{
    IOUSBFindEndpointRequest 	request;
	OSDictionary * 				characterDict 	= NULL;
	OSObject *					obj				= NULL;

#ifdef L4IOKIT
    IOLog("IOUSBMassStorageClass::%s called\n", __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    
    if( super::start( provider ) == false )
    {
    	STATUS_LOG((1, "%s: superclass start failure.", getName()));
        return false;
    }
	
	// Allocate data for our expansion data.
	reserved = ( ExpansionData * ) IOMalloc ( sizeof ( ExpansionData ) );
	bzero ( reserved, sizeof ( ExpansionData ) );
	
    // Save the reference to the interface on the device that will be
    // the provider for this object.
    SetInterfaceReference( OSDynamicCast( IOUSBInterface, provider) );
    if ( GetInterfaceReference() == NULL )
    {
    	STATUS_LOG((1, "%s: the provider is not an IOUSBInterface object",
    				getName()));
    	// If our provider is not a IOUSBInterface object, return false
    	// to indicate that the object could not be correctly 
		// instantiated.
    	// The USB Mass Storage Class specification requires that all 
		// devices be a composite device with a Mass Storage interface
		// so this object will always be an interface driver.
        return false;
    }

    STATUS_LOG((6, "%s: USB Mass Storage @ %d", 
    			getName(),
                GetInterfaceReference()->GetDevice()->GetAddress()));

    if ( GetInterfaceReference()->open( this ) == false) 
    {
    	STATUS_LOG((1, "%s: could not open the interface", getName()));
   		return false;
    }

	// Set the IOUSBPipe object pointers to NULL so that the driver can 
	// release these objects if instantition is not successful.
    fBulkInPipe 	= NULL;
    fBulkOutPipe	= NULL;
    fInterruptPipe	= NULL;
	
	// Default is to have no clients
	fClients		= NULL;
	
	// Default is to have a max lun of 0.
	SetMaxLogicalUnitNumber( 0 );
	
	// Initialize all Bulk Only related member variables to their default 	
	// states.
	fBulkOnlyCommandTag = 0;
	fBulkOnlyCommandStructInUse = false;
	
	// Initialize all CBI related member variables to their default 	
	// states.
	fCBICommandStructInUse = false;

	// Check if the personality for this device specifies a preferred protocol
	if ( getProperty( kIOUSBMassStorageCharacteristics ) == NULL )
	{
		// This device does not specify a preferred protocol, use the protocol
		// defined in the descriptor.
		fPreferredProtocol = GetInterfaceReference()->GetInterfaceProtocol();
		fPreferredSubclass = GetInterfaceReference()->GetInterfaceSubClass();
	}
	else
	{
		OSDictionary * characterDict;
		
		characterDict = OSDynamicCast( OSDictionary, 
							getProperty( kIOUSBMassStorageCharacteristics ));
		
		// Check if the personality for this device specifies a preferred
		// protocol
		if ( characterDict->getObject( kIOUSBMassStoragePreferredProtocol ) 
				== NULL )
		{
			// This device does not specify a preferred protocol, use the
			// protocol defined in the interface descriptor.
			fPreferredProtocol = 
					GetInterfaceReference()->GetInterfaceProtocol();
		}
		else
		{
	    	OSNumber *	preferredProtocol;
			
			preferredProtocol = OSDynamicCast( OSNumber, 
				characterDict->getObject( kIOUSBMassStoragePreferredProtocol ));
			
			// This device has a preferred protocol, use that.
			fPreferredProtocol = preferredProtocol->unsigned32BitValue();
		}
		
		// Check if the personality for this device specifies a preferred 
		// subclass
		if ( characterDict->getObject( kIOUSBMassStoragePreferredSubclass ) == NULL )
		{
			// This device does not specify a preferred subclass, use the 
			// subclass defined in the interface descriptor.
			fPreferredSubclass = 
					GetInterfaceReference()->GetInterfaceSubClass();
		}
		else
		{
	    	OSNumber *	preferredSubclass;
			
			preferredSubclass = OSDynamicCast( OSNumber, characterDict->getObject( kIOUSBMassStoragePreferredSubclass ));
			
			// This device has a preferred protocol, use that.
			fPreferredSubclass = preferredSubclass->unsigned32BitValue();
		}
	}
		
	STATUS_LOG((6, "%s: Preferred Protocol is: %d", getName(), fPreferredProtocol));
    STATUS_LOG((6, "%s: Preferred Subclass is: %d", getName(), fPreferredSubclass));

	// Verify that the device has a supported interface type and configure that
	// Interrupt pipe if the protocol requires one.
    STATUS_LOG((7, "%s: Configure the Storage interface", getName()));
    switch ( GetInterfaceProtocol() )
    {
    	case kProtocolControlBulkInterrupt:
    	{
	         // Find the interrupt pipe for the device
	        request.type = kUSBInterrupt;
	        request.direction = kUSBIn;
 			fInterruptPipe = GetInterfaceReference()->FindNextPipe(NULL, &request);

	        STATUS_LOG((7, "%s: find interrupt pipe", getName()));
	        if(( GetInterfaceProtocol() == kProtocolControlBulkInterrupt) 
	        		&& (fInterruptPipe == 0))
	        {
	            // This is a CBI device and must have an interrupt pipe, 
	            // halt configuration since one could not be found
	            STATUS_LOG((1, "%s: No interrupt pipe for CBI, abort", getName()));
	            goto abortStart;
	        }
	    }
    	break;
    	
    	case kProtocolControlBulk:
    	// Since all the CB devices I have seen do not use the interrupt
    	// endpoint, even if it exists, ignore it if present.
    	case kProtocolBulkOnly:
    	{
	        STATUS_LOG((7, "%s: Bulk Only - skip interrupt pipe",
	        		 	getName()));
	        // Since this is a Bulk Only device, do not look for
	        // interrupt and set the pipe object to NULL so that the
	        // driver can not try to use it.
	        fInterruptPipe 	= NULL;
	    }
	    break;
	    
	    default:
	    {
	    	// The device has a protocol that the driver does not
	    	// support. Return false to indicate that instantiation was
	    	// not successful.
    		goto abortStart;
	    }
	    break;
    }

	// Find the Bulk In pipe for the device
    STATUS_LOG((7, "%s: find bulk in pipe", getName()));
	request.type = kUSBBulk;
	request.direction = kUSBIn;
	fBulkInPipe = GetInterfaceReference()->FindNextPipe(NULL, &request);
	if ( fBulkInPipe == NULL )
	{
		// We could not find the bulk in pipe, not much a bulk transfer
		// device can do without this, so fail the configuration.
    	STATUS_LOG((1, "%s: No bulk in pipe found, aborting",
    				getName()));
    	goto abortStart;
	}
	
	// Find the Bulk Out pipe for the device
    STATUS_LOG((7, "%s: find bulk out pipe", getName()));
	request.type = kUSBBulk;
	request.direction = kUSBOut;
	fBulkOutPipe = GetInterfaceReference()->FindNextPipe(NULL, &request);
	if ( fBulkOutPipe == NULL )
	{
		// We could not find the bulk out pipe, not much a bulk transfer
		// device can do without this, so fail the configuration.
    	STATUS_LOG((1, "%s: No bulk out pipe found, aborting",
    			 	getName()));
    	goto abortStart;
	}
	
	// Build the Protocol Charactersitics dictionary since not all devices will have a 
	// SCSI Peripheral Device Nub to guarantee its existance.
	characterDict = OSDynamicCast ( OSDictionary, getProperty ( kIOPropertyProtocolCharacteristicsKey ) );
	if ( characterDict == NULL )
	{
		characterDict = OSDictionary::withCapacity ( 1 );
	}
	
	else
	{
		characterDict->retain ( );
	}
	
	obj = getProperty ( kIOPropertyPhysicalInterconnectTypeKey );
	if ( obj != NULL )
	{
		characterDict->setObject ( kIOPropertyPhysicalInterconnectTypeKey, obj );
	}
	
	obj = getProperty ( kIOPropertyPhysicalInterconnectLocationKey );
	if ( obj != NULL )
	{
		characterDict->setObject ( kIOPropertyPhysicalInterconnectLocationKey, obj );
	}
	
	obj = getProperty ( kIOPropertyReadTimeOutDurationKey );	
	if ( obj != NULL );
	{
		characterDict->setObject ( kIOPropertyReadTimeOutDurationKey, obj );
	}
	
	obj = getProperty ( kIOPropertyWriteTimeOutDurationKey );	
	if ( obj != NULL );
	{
		characterDict->setObject ( kIOPropertyWriteTimeOutDurationKey, obj );
	}
	
	setProperty ( kIOPropertyProtocolCharacteristicsKey, characterDict );
	
	characterDict->release ( );

   	STATUS_LOG((6, "%s: successfully configured", getName()));

	InitializePowerManagement( GetInterfaceReference() );
	BeginProvidedServices();       

#ifdef L4IOKIT
    IOLog("IOUSBMassStorageClass::%s returns true\n", __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    
    return true;

abortStart:
    STATUS_LOG((1, "%s: aborting startup.  Stop the provider.", getName() ));

	// Call the stop method to clean up any allocated resources.
    stop( provider );
    
    return false;
}


//�����������������������������������������������������������������������������
//	� stop - Called at stop time								   [PUBLIC]
//�����������������������������������������������������������������������������

void 
IOUSBMassStorageClass::stop(IOService * provider)
{
	// I am logging this as a 1 because if anything is logging after this we want to know about it.
	// This should be the last message we see.
    STATUS_LOG((1, "%s: Bye bye!", getName()));

	EndProvidedServices();

	// Tell the interface object to close all pipes since the driver is 
	// going away.
   	fBulkInPipe 	= NULL;
   	fBulkOutPipe 	= NULL;
   	fInterruptPipe 	= NULL;

    super::stop(provider);
}


//�����������������������������������������������������������������������������
//	� free - Called by IOKit to free any resources.					   [PUBLIC]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::free ( void )
{
	
	if ( reserved != NULL )
	{
		
		// Since fClients is defined as reserved->fClients we don't want
		// to dereference it unless reserved is non-NULL.
		if ( fClients != NULL )
		{
			
			fClients->release();
			fClients = NULL;
			
		}
		
		IOFree ( reserved, sizeof ( ExpansionData ) );
		reserved = NULL;
		
	}
	
	super::free ( );
	
}


//�����������������������������������������������������������������������������
//	� message - Called by IOKit to deliver messages.				   [PUBLIC]
//�����������������������������������������������������������������������������

IOReturn
IOUSBMassStorageClass::message( UInt32 type, IOService * provider, void * argument )
{
	IOReturn	result;
	
	STATUS_LOG ( (4, "%s: message = %lx called", getName(), type ) );
	switch( type )
	{
		case kIOMessageServiceIsTerminated:
		{
			IOUSBInterface * currentInterface;
			
			STATUS_LOG((2, "%s: message  kIOMessageServiceIsTerminated.", getName() ));
			
			currentInterface = GetInterfaceReference();
			if ( currentInterface != NULL )
			{				
				STATUS_LOG((2, "%s: message  kIOMessageServiceIsTerminated interface is non NULL.", getName() ));
				
				SetInterfaceReference( NULL );
				
				// Close our interface
			    currentInterface->close(this);
				
				// Let the clients know that the device is gone.
				SendNotification_DeviceRemoved( );
			}
			
			result = kIOReturnSuccess;
		}
		break;

		case kIOMessageServiceIsRequestingClose:
		{
			IOUSBInterface * currentInterface;

    		STATUS_LOG((2, "%s: message  kIOMessageServiceIsRequestingClose.", getName() ));
			
			// Let the clients know that the device is gone.
			SendNotification_DeviceRemoved( );

			currentInterface = GetInterfaceReference();
			if ( currentInterface != NULL )
			{				
				SetInterfaceReference( NULL );

				// Close our interface
			    currentInterface->close(this);
			}
			
			result = kIOReturnSuccess;
		}
		break;
					
		default:
		{
			result = super::message( type, provider, argument );
		}
	}
	
	return result;
}


//�����������������������������������������������������������������������������
//	� BeginProvidedServices											[PROTECTED]
//�����������������������������������������������������������������������������

bool	
IOUSBMassStorageClass::BeginProvidedServices( void )
{
 	// If this is a BO device that supports multiple LUNs, we will need 
	// to spawn off a nub for each valid LUN.  If this is a CBI/CB
	// device or a BO device that only supports LUN 0, this object can
	// register itself as the nub.  
    STATUS_LOG((7, "%s: Determine the maximum LUN", getName()));
	
  	if( GetInterfaceProtocol() == kProtocolBulkOnly )
    {
    	IOReturn	status;
    	bool		maxLUNDetermined = false;
		
		// Before we issue the GetMaxLUN call let's check if this device
		// specifies a MaxLogicalUnitNumber as part of its personality.
		if( getProperty( kIOUSBMassStorageCharacteristics ) != NULL )
		{
			OSDictionary * characterDict = OSDynamicCast( OSDictionary, 
														  getProperty( kIOUSBMassStorageCharacteristics ));
			
			// Check if this device is known to have problems when waking from sleep
			if( characterDict->getObject( kIOUSBMassStorageMaxLogicalUnitNumber ) != NULL )
			{
				OSNumber *	maxLUN = OSDynamicCast( OSNumber,
													characterDict->getObject( kIOUSBMassStorageMaxLogicalUnitNumber ) );
				if( maxLUN != NULL )
				{
					SetMaxLogicalUnitNumber( maxLUN->unsigned8BitValue() );
					STATUS_LOG((4, "%s: Number of LUNs %u.", getName(), maxLUN->unsigned8BitValue() ));
					maxLUNDetermined = true;
				}
			}
		}
		
		if( maxLUNDetermined == false )
		{
			// The device is a Bulk Only transport device, issue the
			// GetMaxLUN call to determine what the maximum value is.
			bool		triedReset = false;
			UInt8		clearPipeAttempts = 0;		

			// We want to loop until we get a satisfactory response to GetMaxLUN, either an answer or failure.
			while ( status != kIOReturnSuccess )
			{
				
				// Build the USB command
				fUSBDeviceRequest.bmRequestType 	= USBmakebmRequestType(kUSBIn, kUSBClass, kUSBInterface);
				fUSBDeviceRequest.bRequest 			= 0xFE;
				fUSBDeviceRequest.wValue			= 0;
				fUSBDeviceRequest.wIndex			= GetInterfaceReference()->GetInterfaceNumber();
				fUSBDeviceRequest.wLength			= 1;
				fUSBDeviceRequest.pData				= &fMaxLogicalUnitNumber;
				
				STATUS_LOG((4, "%s: Issuing device request to find max LUN", getName() ));
				
				// Send the command over the control endpoint
				status = GetInterfaceReference()->DeviceRequest( &fUSBDeviceRequest );
				
				STATUS_LOG((4, "%s: DeviceRequest returned status = %x", getName(), status ));
				
				if ( status != kIOReturnSuccess )
				{
					
					SetMaxLogicalUnitNumber( 0 );
					if( ( status == kIOUSBPipeStalled ) && ( clearPipeAttempts < 3 ) )
					{
						UInt8		eStatus[2];
						
						STATUS_LOG((4, "%s: calling GetStatusEndpointStatus to clear stall", getName()));
						
						// Throw in an extra Get Status to clear up devices that stall the
						// control pipe like the early Iomega devices.
						GetStatusEndpointStatus( GetControlPipe(), &eStatus[0], NULL);
						
						clearPipeAttempts++;
					}
					else if ( ( status == kIOReturnNotResponding ) && ( triedReset == false ) )
					{
						// The device isn't responding. Let us reset the device, and try again.
						
						// We need to retain ourselves so we stick around after the bus reset.
						retain();
				
						// The endpoint status could not be retrieved meaning that the device has
						// stopped responding. Or this could be a device we know needs a reset.
						// Begin the device reset sequence.
						
						STATUS_LOG((4, "%s: BeginProvidedServices: device not responding, reseting.", getName() ));
						
						// Reset the device on its own thread so we don't deadlock.
						fResetInProgress = true;
						
						IOCreateThread( IOUSBMassStorageClass::sResetDevice, this );
						fCommandGate->runAction ( ( IOCommandGate::Action ) &IOUSBMassStorageClass::sWaitForReset );
						
						triedReset = true;
					}
					else
					{
						break;
					}
					
				}
					
			}
		}
			
    }
    else
    {
    	// CBI and CB protocols do not support LUNs so for these the 
    	// maximum LUN will always be zero.
        SetMaxLogicalUnitNumber( 0 );
    }
    

    STATUS_LOG((5, "%s: Maximum supported LUN is: %d", 
    			getName(), 
    			GetMaxLogicalUnitNumber() ));
	
   	STATUS_LOG((7, "%s: successfully configured", getName()));

 	// If this is a BO device that supports multiple LUNs, we will need 
	// to spawn off a nub for each valid LUN.  If this is a CBI/CB
	// device or a BO device that only supports LUN 0, this object can
	// register itself as the nub.  
 	if ( GetMaxLogicalUnitNumber() == 0 )
 	{    
		registerService(kIOServiceAsynchronous);
		
		fClients = NULL;
    }
    else
    {
		// Allocate space for our set that will keep track of the LUNs.
		fClients = OSSet::withCapacity( GetMaxLogicalUnitNumber() + 1 );
	
        for( int loopLUN = 0; loopLUN <= GetMaxLogicalUnitNumber(); loopLUN++ )
        {
		    STATUS_LOG((6,  "IOUSBMassStorageClass::CreatePeripheralDeviceNubForLUN entering." ));

			IOSCSILogicalUnitNub * 	nub = OSTypeAlloc( IOSCSILogicalUnitNub );
			
			if( nub == NULL )
			{
				PANIC_NOW(( "IOUSBMassStorageClass::CreatePeripheralDeviceNubForLUN failed" ));
				return false;
			}
			
			nub->init( 0 );
			
			if( nub->attach( this ) == false )
			{
				if( isInactive() == false )
				{
					// panic since the nub can't attach and we are active
					PANIC_NOW(( "IOUSBMassStorageClass::CreatePeripheralDeviceNubForLUN unable to attach nub" ));
				}
				
				// Release our nub before we return so we don't leak...
				nub->release();
				// We didn't attach so we should return false.
				return false;
			}
						
			nub->SetLogicalUnitNumber( loopLUN );
			if( nub->start( this ) == false )
			{
				nub->detach( this );
			}
			else
			{
				nub->registerService( kIOServiceAsynchronous );
			}

			nub->release();
			
			STATUS_LOG((6, "IOUSBMassStorageClass::CreatePeripheralDeviceNubForLUN exiting." ));
		}
    }

	return true;
}


//�����������������������������������������������������������������������������
//	� EndProvidedServices											[PROTECTED]
//�����������������������������������������������������������������������������

bool	
IOUSBMassStorageClass::EndProvidedServices( void )
{
	return true;
}


#pragma mark -
#pragma mark *** CDB Transport Methods ***
#pragma mark -


//�����������������������������������������������������������������������������
//	� SendSCSICommand												[PROTECTED]
//�����������������������������������������������������������������������������

bool 
IOUSBMassStorageClass::SendSCSICommand( 	
									SCSITaskIdentifier 			request, 
									SCSIServiceResponse *		serviceResponse,
									SCSITaskStatus *			taskStatus )
{
	IOReturn status;

	// Set the defaults to an error state.		
	*taskStatus = kSCSITaskStatus_No_Status;
	*serviceResponse =  kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
	
   	STATUS_LOG((6, "%s: SendSCSICommand was called", getName()));

	// Temporary work around for 3774063 since it will most likely not be 
	// addressed in time for Tiger release.
	// This work around needs to be removed once 3774063 is fixed.
	if ( isInactive () )
	{	
		return false;
	}
	
	// Verify that the SCSI Task to execute is valid.
  	if ( request == NULL )
 	{
 		// An invalid SCSI Task object was passed into here.  Let the client know
 		// by returning the default error for taskStatus and serviceResponse
 		// and true to indicate that the command is completed.
  		STATUS_LOG((1, "%s: SendSCSICommand was called with a NULL CDB", 
					getName()));
		return true;
 	}

	if ( GetInterfaceReference() == NULL )
	{
 		// The USB interface is no longer valid.  Let the client know
 		// by returning the default error for taskStatus and serviceResponse
 		// and true to indicate that the command is completed.
		return true;
	}

#if (USB_MASS_STORAGE_DEBUG == 1)
	SCSICommandDescriptorBlock	cdbData;
	
	STATUS_LOG((4, "%s: SendSCSICommand CDB data: ", getName()));
	GetCommandDescriptorBlock( request, &cdbData );
	
	if ( GetCommandDescriptorBlockSize ( request ) == kSCSICDBSize_6Byte )
		STATUS_LOG((4, "%X : %X : %X : %X : %X : %X",
					cdbData[0], cdbData[1], cdbData[2], cdbData[3],
					cdbData[4], cdbData[5]));
	else if ( GetCommandDescriptorBlockSize ( request ) == kSCSICDBSize_10Byte )
		STATUS_LOG((4, "%X : %X : %X : %X : %X : %X : %X : %X : %X : %X",
					cdbData[0], cdbData[1], cdbData[2], cdbData[3],
					cdbData[4], cdbData[5], cdbData[6], cdbData[7],
					cdbData[8], cdbData[9]));
	else if ( GetCommandDescriptorBlockSize ( request ) == kSCSICDBSize_12Byte )
		STATUS_LOG((4, "%X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X",
					cdbData[0], cdbData[1], cdbData[2], cdbData[3],
					cdbData[4], cdbData[5], cdbData[6], cdbData[7],
					cdbData[8], cdbData[9], cdbData[10], cdbData[11]));
	else if ( GetCommandDescriptorBlockSize ( request ) == kSCSICDBSize_6Byte )
		STATUS_LOG((4, "%X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X : %X",
					cdbData[0], cdbData[1], cdbData[2], cdbData[3],
					cdbData[4], cdbData[5], cdbData[6], cdbData[7],
					cdbData[8], cdbData[9], cdbData[10], cdbData[11],
					cdbData[12], cdbData[13], cdbData[14], cdbData[15]));
#endif
	
   	if( GetInterfaceProtocol() == kProtocolBulkOnly)
	{
		if ( fBulkOnlyCommandStructInUse == true )
		{
			return false;
		}
		
		fBulkOnlyCommandStructInUse = true;
   		STATUS_LOG((6, "%s: SendSCSICommandforBulkOnlyProtocol sent", getName() ));
		status = SendSCSICommandForBulkOnlyProtocol( request );
		if( status != kIOReturnSuccess )
		{
			// If the command fails we want to make sure that we
			// don't hold up other commands.
			fBulkOnlyCommandStructInUse = false;
		}
   		STATUS_LOG((5, "%s: SendSCSICommandforBulkOnlyProtocol returned %x",
   			 		getName(), 
   			 		status));
	}
	else
	{
		if ( fCBICommandStructInUse == true )
		{
			return false;
		}
		
		fCBICommandStructInUse = true;
		status = SendSCSICommandForCBIProtocol( request );
		if( status != kIOReturnSuccess )
		{
			// If the command fails we want to make sure that we
			// don't hold up other commands.
			fCBICommandStructInUse = false;
		}
   		STATUS_LOG((5, "%s: SendSCSICommandforCBIProtocol returned %x", 
   					getName(), 
   					status));
	}

	if ( status == kIOReturnSuccess )
	{	
		*serviceResponse = kSCSIServiceResponse_Request_In_Process;
	}

	return true;
}


//�����������������������������������������������������������������������������
//	� CompleteSCSICommand											[PROTECTED]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::CompleteSCSICommand( SCSITaskIdentifier request, IOReturn status )
{
	fBulkOnlyCommandStructInUse = false;
	fCBICommandStructInUse = false;
		
	if ( status == kIOReturnSuccess )
	{	
		CommandCompleted( request, kSCSIServiceResponse_TASK_COMPLETE, kSCSITaskStatus_GOOD );
	}
	else
	{
		CommandCompleted( request, kSCSIServiceResponse_TASK_COMPLETE, kSCSITaskStatus_CHECK_CONDITION );
	}
}


//�����������������������������������������������������������������������������
//	� AbortSCSICommand												[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOUSBMassStorageClass::AbortSCSICommand( SCSITaskIdentifier abortTask )
{
 	IOReturn	status = kIOReturnSuccess;
 	
  	STATUS_LOG((6, "%s: AbortSCSICommand was called", getName()));
 	if ( abortTask == NULL )
 	{
 		// We were given an invalid SCSI Task object.  Let the client know.
  		STATUS_LOG((1, "%s: AbortSCSICommand was called with a NULL CDB object", 
					getName()));
 		return kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
 	}
	
	if ( GetInterfaceReference() == NULL )
	{
 		// We have an invalid interface, the device has probably been removed.
 		// Nothing else to do except to report an error.
  		STATUS_LOG((1, "%s: AbortSCSICommand was called with a NULL interface", 
					getName()));
 		return kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
	}
	
	if(GetInterfaceReference()->GetInterfaceProtocol() == kProtocolBulkOnly)
	{
		status = AbortSCSICommandForBulkOnlyProtocol( abortTask );
   		STATUS_LOG((5, "%s: abortCDBforBulkOnlyProtocol returned %x", 
					getName(), 
					status));
	}
	else
	{
		status = AbortSCSICommandForCBIProtocol( abortTask );
   		STATUS_LOG((5, "%s: abortCDBforCBIProtocol returned %x", 
   					getName(), 
   					status));
	}

	// Since the driver currently does not support abort, return an error	
	return kSCSIServiceResponse_FUNCTION_REJECTED;
}


//�����������������������������������������������������������������������������
//	� IsProtocolServiceSupported									[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOUSBMassStorageClass::IsProtocolServiceSupported( 
										SCSIProtocolFeature 	feature, 
										void * 					serviceValue )
{
	bool	isSupported;
	
	STATUS_LOG((6,  "IOUSBMassStorageClass::IsProtocolServiceSupported called"));
	
    // all features just return false
	switch( feature )
	{
		case kSCSIProtocolFeature_GetMaximumLogicalUnitNumber:
		{
			*((UInt32 *) serviceValue) = GetMaxLogicalUnitNumber();
			isSupported = true;
		}
		break;
		
		default:
		{
			isSupported = false;
		}
		break;

	}

	return isSupported;
}


//�����������������������������������������������������������������������������
//	� HandleProtocolServiceFeature									[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOUSBMassStorageClass::HandleProtocolServiceFeature( 
										SCSIProtocolFeature 	feature, 
										void * 					serviceValue )
{
	UNUSED( feature );
	UNUSED( serviceValue );

	return false;
}


#pragma mark -
#pragma mark *** Standard USB Command Methods ***
#pragma mark -


//�����������������������������������������������������������������������������
//	� ClearFeatureEndpointStall -	Method to do the CLEAR_FEATURE command for
//									an ENDPOINT_STALL feature.		
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn 
IOUSBMassStorageClass::ClearFeatureEndpointStall( 
								IOUSBPipe *			thePipe,
								IOUSBCompletion	*	completion )
{
	IOReturn			status;
	
	if ( ( GetInterfaceReference() == NULL ) ||
		 ( thePipe == NULL ) )
	{
 		// We have an invalid interface, the device has probably been removed.
 		// Nothing else to do except to report an error.
 		return kIOReturnDeviceError;
	}
	
	// Make sure that the Data Toggles are reset before doing the 
	// Clear Stall.
	thePipe->Reset();

	// Clear out the structure for the request
	bzero( &fUSBDeviceRequest, sizeof(IOUSBDevRequest));
	
	// Build the USB command
	fUSBDeviceRequest.bmRequestType 	= USBmakebmRequestType(kUSBNone, kUSBStandard, kUSBEndpoint);
   	fUSBDeviceRequest.bRequest 			= kUSBRqClearFeature;
   	fUSBDeviceRequest.wValue			= 0;	// Zero is EndpointStall
	fUSBDeviceRequest.wIndex			= thePipe->GetEndpointNumber();
	if ( thePipe == GetBulkInPipe() )
	{
		fUSBDeviceRequest.wIndex		|= 0x80;
	}

	// Send the command over the control endpoint
	status = GetInterfaceReference()->DeviceRequest( &fUSBDeviceRequest, completion );
   	STATUS_LOG((5, "%s: ClearFeatureEndpointStall returned %x", 
   				getName(), 
   				status));
				
	return status;
}


//�����������������������������������������������������������������������������
//	� GetStatusEndpointStatus -	Method to do the GET_STATUS command for the
//								endpoint that the IOUSBPipe is connected to.		
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn 
IOUSBMassStorageClass::GetStatusEndpointStatus( 
								IOUSBPipe *			thePipe,
								void *				endpointStatus,
								IOUSBCompletion	*	completion ) 
{
	IOReturn			status;

	if ( ( GetInterfaceReference() == NULL ) ||
		 ( thePipe == NULL ) )
	{
 		// We have an invalid interface, the device has probably been removed.
 		// Nothing else to do except to report an error.
 		return kIOReturnDeviceError;
	}
	
	// Clear out the structure for the request
	bzero( &fUSBDeviceRequest, sizeof(IOUSBDevRequest));

	// Build the USB command	
    fUSBDeviceRequest.bmRequestType 	= USBmakebmRequestType( kUSBIn, kUSBStandard, kUSBEndpoint);	
   	fUSBDeviceRequest.bRequest 			= kUSBRqGetStatus;
   	fUSBDeviceRequest.wValue			= 0;	// Zero is EndpointStall
	fUSBDeviceRequest.wIndex			= thePipe->GetEndpointNumber();

	if ( thePipe == GetBulkInPipe() )
	{
		fUSBDeviceRequest.wIndex		|= 0x80;
	}
	
	fUSBDeviceRequest.wLength			= 2;
   	fUSBDeviceRequest.pData				= endpointStatus;

	// Send the command over the control endpoint
	status = GetInterfaceReference()->DeviceRequest( &fUSBDeviceRequest, completion );
   	STATUS_LOG((5, "%s: GetStatusEndpointStatus returned %x", 
   				getName(), 
   				status));
	return status;
}

#pragma mark -
#pragma mark *** Accessor Methods For All Protocol Variables ***
#pragma mark -


/* The following methods are for use only by this class */


//�����������������������������������������������������������������������������
//	� GetInterfaceReference -	Method to do the GET_STATUS command for the
//								endpoint that the IOUSBPipe is connected to.		
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOUSBInterface *
IOUSBMassStorageClass::GetInterfaceReference( void )
{
	// Making this a 7 since it gets called A LOT.
   	STATUS_LOG((7, "%s: GetInterfaceReference", getName() ));
   	if ( fInterface == NULL )
   	{
   		STATUS_LOG((2, "%s: GetInterfaceReference - Interface is NULL.", getName() ));
   	}
   	
	return fInterface;
}


//�����������������������������������������������������������������������������
//	� SetInterfaceReference											[PROTECTED]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::SetInterfaceReference( IOUSBInterface * newInterface )
{
	fInterface = newInterface;
}


//�����������������������������������������������������������������������������
//	� GetInterfaceSubClass											[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOUSBMassStorageClass::GetInterfaceSubclass( void )
{
	return fPreferredSubclass;
}


//�����������������������������������������������������������������������������
//	� GetInterfaceProtocol											[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOUSBMassStorageClass::GetInterfaceProtocol( void )
{
	return fPreferredProtocol;
}


//�����������������������������������������������������������������������������
//	� GetControlPipe												[PROTECTED]
//�����������������������������������������������������������������������������

IOUSBPipe *
IOUSBMassStorageClass::GetControlPipe( void )
{
	if ( GetInterfaceReference() == NULL )
	{
		return NULL;
	}
	
	return GetInterfaceReference()->GetDevice()->GetPipeZero();
}


//�����������������������������������������������������������������������������
//	� GetBulkInPipe													[PROTECTED]
//�����������������������������������������������������������������������������

IOUSBPipe *
IOUSBMassStorageClass::GetBulkInPipe( void )
{
	return fBulkInPipe;
}


//�����������������������������������������������������������������������������
//	� GetBulkOutPipe												[PROTECTED]
//�����������������������������������������������������������������������������

IOUSBPipe *
IOUSBMassStorageClass::GetBulkOutPipe( void )
{
	return fBulkOutPipe;
}


//�����������������������������������������������������������������������������
//	� GetInterruptPipe												[PROTECTED]
//�����������������������������������������������������������������������������

IOUSBPipe *
IOUSBMassStorageClass::GetInterruptPipe( void )
{
	return fInterruptPipe;
}


//�����������������������������������������������������������������������������
//	� GetMaxLogicalUnitNumber										[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOUSBMassStorageClass::GetMaxLogicalUnitNumber( void ) const
{
	return fMaxLogicalUnitNumber;
}


//�����������������������������������������������������������������������������
//	� SetMaxLogicalUnitNumber										[PROTECTED]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::SetMaxLogicalUnitNumber( UInt8 maxLUN )
{
	fMaxLogicalUnitNumber = maxLUN;
}


#pragma mark -
#pragma mark *** Accessor Methods For CBI Protocol Variables ***
#pragma mark -


//�����������������������������������������������������������������������������
//	� GetCBIRequestBlock											[PROTECTED]
//�����������������������������������������������������������������������������

CBIRequestBlock *	
IOUSBMassStorageClass::GetCBIRequestBlock( void )
{
	// Return a pointer to the CBIRequestBlock
	return &fCBICommandRequestBlock;
}


//�����������������������������������������������������������������������������
//	� ReleaseCBIRequestBlock										[PROTECTED]
//�����������������������������������������������������������������������������

void	
IOUSBMassStorageClass::ReleaseCBIRequestBlock( CBIRequestBlock * cbiRequestBlock )
{
	// Clear the request and completion to avoid possible double callbacks.
	cbiRequestBlock->request = NULL;

	// Since we only allow one command and the CBIRequestBlock is
	// a member variable, no need to do anything.
	return;
}

#pragma mark -
#pragma mark *** Accessor Methods For Bulk Only Protocol Variables ***
#pragma mark -


//�����������������������������������������������������������������������������
//	� GetBulkOnlyRequestBlock										[PROTECTED]
//�����������������������������������������������������������������������������

BulkOnlyRequestBlock *	
IOUSBMassStorageClass::GetBulkOnlyRequestBlock( void )
{
	// Return a pointer to the BulkOnlyRequestBlock
	return &fBulkOnlyCommandRequestBlock;
}


//�����������������������������������������������������������������������������
//	� ReleaseBulkOnlyRequestBlock									[PROTECTED]
//�����������������������������������������������������������������������������

void	
IOUSBMassStorageClass::ReleaseBulkOnlyRequestBlock( BulkOnlyRequestBlock * boRequestBlock )
{
	// Clear the request and completion to avoid possible double callbacks.
	boRequestBlock->request = NULL;

	// Since we only allow one command and the BulkOnlyRequestBlock is
	// a member variable, no need to do anything.
	return;
}


//�����������������������������������������������������������������������������
//	� GetNextBulkOnlyCommandTag										[PROTECTED]
//�����������������������������������������������������������������������������

UInt32	
IOUSBMassStorageClass::GetNextBulkOnlyCommandTag( void )
{
	fBulkOnlyCommandTag++;
	
	return fBulkOnlyCommandTag;
}


//�����������������������������������������������������������������������������
//	� HandlePowerOn - Will get called when a device has been resumed   [PUBLIC]
//�����������������������������������������������������������������������������

IOReturn
IOUSBMassStorageClass::HandlePowerOn( void )
{
	UInt8	eStatus[2];
	bool	knownResetOnResumeDevice = false;
	
	// The USB hub port that the device is connected to has been resumed,
	// check to see if the device is still responding correctly and if not, 
	// fix it so that it is.
	STATUS_LOG((6, "%s: HandlePowerOn", getName() ));
	
	if ( getProperty( kIOUSBMassStorageCharacteristics ) != NULL )
	{
		OSDictionary * characterDict = OSDynamicCast(
											OSDictionary, 
											getProperty( kIOUSBMassStorageCharacteristics ));
		
		// Check if this device is known to have problems when waking from sleep
		if ( characterDict->getObject( kIOUSBMassStorageResetOnResume ) != NULL )
		{
			STATUS_LOG((4, "%s: knownResetOnResumeDevice", getName() ));
			knownResetOnResumeDevice = true;
		}
	}
	
	if ( ( ( GetStatusEndpointStatus( GetBulkInPipe(), &eStatus[0], NULL) != kIOReturnSuccess ) ||
		 ( knownResetOnResumeDevice == true ) ) &&
		 ( isInactive() == false ) )
	{
		// We call retain here so that the driver will stick around long enough for
		// sResetDevice() to do it's thing in case we are being terminated.  The
		// retain() is balanced with a release in sResetDevice().
		retain();
		
		// The endpoint status could not be retrieved meaning that the device has
		// stopped responding. Or this could be a device we know needs a reset.
		// Begin the device reset sequence.
		
		STATUS_LOG((4, "%s: kIOMessageServiceIsResumed GetStatusEndpointStatus error or knownResetOnResumeDevice.", getName() ));
		
		// Reset the device on its own thread so we don't deadlock.
		fResetInProgress = true;
		
		IOCreateThread( IOUSBMassStorageClass::sResetDevice, this );
		fCommandGate->runAction ( ( IOCommandGate::Action ) &IOUSBMassStorageClass::sWaitForReset );
		
	}
	
	return kIOReturnSuccess;
}


//�����������������������������������������������������������������������������
//	� handleOpen													   [PUBLIC]
//�����������������������������������������������������������������������������

bool
IOUSBMassStorageClass::handleOpen( IOService *		client,
								   IOOptionBits		options,
								   void *			arg )
{
	
	bool	result = false;
	
	// If this is a normal open on a single LUN device.
	if ( GetMaxLogicalUnitNumber() == 0 )
	{
		
		result = super::handleOpen ( client, options, arg );
		goto Exit;
		
	}
	
	// It's an open from a multi-LUN client
	require_nonzero ( fClients, ErrorExit );
	require_nonzero ( OSDynamicCast ( IOSCSILogicalUnitNub, client ), ErrorExit );
	result = fClients->setObject ( client );
	
	
Exit:
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� handleClose													   [PUBLIC]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::handleClose( IOService *		client,
									IOOptionBits	options )
{
		
	if ( GetMaxLogicalUnitNumber() == 0 )
	{
		super::handleClose( client, options );
		return;
	}
	
	require_nonzero ( fClients, Exit );
	
	if ( fClients->containsObject( client ) )
	{
		fClients->removeObject( client );
		
		if ( ( fClients->getCount( ) == 0 ) && isInactive( ) )
		{
			message( kIOMessageServiceIsRequestingClose, getProvider( ), 0 );
		}
	}
	
	
Exit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	� handleIsOpen													   [PUBLIC]
//�����������������������������������������������������������������������������

bool
IOUSBMassStorageClass::handleIsOpen( const IOService * client ) const
{
	
	bool	result = false;
	UInt8	lun = GetMaxLogicalUnitNumber();
	
	require_nonzero ( lun, CallSuperClass );
	require_nonzero ( fClients, CallSuperClass );
	
	// General case (is anybody open)
	if ( ( client == NULL ) && ( fClients->getCount ( ) != 0 ) )
	{
		result = true;
	}
	
	else
	{
		// specific case (is this client open)
		result = fClients->containsObject ( client );
	}
	
	return result;
	
	
CallSuperClass:
	
	
	result = super::handleIsOpen ( client );	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� sWaitForReset											[STATIC][PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOUSBMassStorageClass::sWaitForReset( void * refcon )
{
	
	return (( IOUSBMassStorageClass * ) refcon )->GatedWaitForReset();
	
}


//�����������������������������������������������������������������������������
//	� GatedWaitForReset												[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOUSBMassStorageClass::GatedWaitForReset( void )
{
	
	IOReturn status = kIOReturnSuccess;
	
	if ( fResetInProgress == true )
	{
		status = fCommandGate->commandSleep( &fResetInProgress, THREAD_UNINT );
	}
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� sResetDevice											[STATIC][PROTECTED]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::sResetDevice( void * refcon )
{
	
	IOUSBMassStorageClass *		driver;
	IOReturn					status = kIOReturnSuccess;
	driver = ( IOUSBMassStorageClass * ) refcon;
	
	STATUS_LOG((4, "IOUSBMassStorageClass: sResetDevice" ));
	
	// Check if we should bail out because we are
	// being terminated.
	if ( ( driver->GetInterfaceReference() == NULL ) ||
		 ( driver->isInactive( ) == true ) )
	{
		STATUS_LOG((2,  "IOUSBMassStorageClass: sResetDevice - We are being terminated!" ));
		goto ErrorExit;
	}
	
	status = driver->GetInterfaceReference()->GetDevice()->ResetDevice();
	
	STATUS_LOG((5, "IOUSBMassStorageClass: ResetDevice() returned status = %d", status ));
	
	// We may get terminated during the call to ResetDevice() since it is synchronous.  We should
	// check again whether we should bail or not.
	if ( ( driver->GetInterfaceReference() == NULL ) ||
		 ( driver->isInactive( ) == true ) ||
		 ( status != kIOReturnSuccess ) )
	{
		STATUS_LOG((2, "IOUSBMassStorageClass: sResetDevice - We are being terminated!" ));
		goto ErrorExit;
	}
	
	if ( driver->GetBulkInPipe() != NULL )
	{
		driver->GetBulkInPipe()->Reset();
	}
	
	if ( driver->GetBulkOutPipe() != NULL )
	{
		driver->GetBulkOutPipe()->Reset();
	}
	
	// Once the device has been reset, send notification to the client so that the
	// device can be reconfigured for use.
	driver->SendNotification_VerifyDeviceState();
	
	
ErrorExit:
	
	
	driver->fResetInProgress = false;
	driver->fCommandGate->commandWakeup( &driver->fResetInProgress, false );
	
	// We retained the driver in HandlePowerOn() when
	// we created a thread for sResetDevice()
	driver->release();
	
	STATUS_LOG((6,"IOUSBMassStorageClass: sResetDevice returned" ));
	
	return;
	
}


OSMetaClassDefineReservedUsed( IOUSBMassStorageClass, 1 );


//�����������������������������������������������������������������������������
//	� StartDeviceRecovery - The recovery sequence to restore functionality for
//							devices that stop responding (like many devices
//							after a Suspend/Resume).				[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOUSBMassStorageClass::StartDeviceRecovery( void )
{
	// First check to see if the device is still connected.
	UInt8		eStatus[2];
	IOReturn	status = kIOReturnError;
	
	// The USB hub port that the device is connected to has been resumed,
	// check to see if the device is still responding correctly and if not, 
	// fix it so that it is. 
	STATUS_LOG((5, "%s: StartDeviceRecovery", getName() ));
	
	if( fBulkOnlyCommandStructInUse == true )
	{
		// Set up the IOUSBCompletion structure
		fBulkOnlyCommandRequestBlock.boCompletion.target 		= this;
		fBulkOnlyCommandRequestBlock.boCompletion.action 		= &this->DeviceRecoveryCompletionAction;
		status = GetStatusEndpointStatus( GetBulkInPipe(), &eStatus[0], &fBulkOnlyCommandRequestBlock.boCompletion);
	}
	else if( fCBICommandStructInUse == true )
	{
		// Set up the IOUSBCompletion structure
		fCBICommandRequestBlock.cbiCompletion.target 		= this;
		fCBICommandRequestBlock.cbiCompletion.action 		= &this->DeviceRecoveryCompletionAction;
		status = GetStatusEndpointStatus( GetBulkInPipe(), &eStatus[0], &fCBICommandRequestBlock.cbiCompletion);
   	}
	
	return status;
}

OSMetaClassDefineReservedUsed( IOUSBMassStorageClass, 2 );


//�����������������������������������������������������������������������������
//	� FinishDeviceRecovery											[PROTECTED]
//�����������������������������������������������������������������������������

void
IOUSBMassStorageClass::FinishDeviceRecovery( IOReturn status )
{
	
	SCSITaskIdentifier	tempTask = NULL;
	
	if ( status != kIOReturnSuccess)
	{
		// The endpoint status could not be retrieved meaning that the device has
		// stopped responding.  Begin the device reset sequence.
		
		STATUS_LOG((4, "%s: StartDeviceRecovery GetStatusEndpointStatus error. status = %d", getName(), status ));
		
		if ( GetInterfaceReference() == NULL )
		{
			// We are being terminated.  We should clean up and bail...
			if( fBulkOnlyCommandStructInUse == true )
			{
				tempTask = fBulkOnlyCommandRequestBlock.request;
			}
			else if ( fCBICommandStructInUse == true )
			{
				tempTask = fCBICommandRequestBlock.request;
			}
			
			goto ErrorExit;
		}
		
		status = (GetInterfaceReference()->GetDevice())->ResetDevice();
		
		// Once the device has been reset, send notification to the client so that the
		// device can be reconfigured for use.
		SendNotification_VerifyDeviceState();
	}
	
	// If the device is responding correctly or has been reset, retry the command.
	if( status == kIOReturnSuccess )
	{
		
		if( fBulkOnlyCommandStructInUse == true )
		{
			tempTask = fBulkOnlyCommandRequestBlock.request;
			
	   		STATUS_LOG((6, "%s: FinishDeviceRecovery SendSCSICommandforBulkOnlyProtocol sent", getName() ));
			status = SendSCSICommandForBulkOnlyProtocol( tempTask );
	   		STATUS_LOG((5, "%s: FinishDeviceRecovery SendSCSICommandforBulkOnlyProtocol returned %x",
	   			 		getName(), 
	   			 		status));
			if( status != kIOReturnSuccess)
			{
				STATUS_LOG((6, "%s: FinishDeviceRecovery SendSCSICommandforBulkOnlyProtocol status != kIOReturnSuccess ", getName() ));
				goto ErrorExit;
			}
		}
		else if ( fCBICommandStructInUse == true )
		{
			tempTask = fCBICommandRequestBlock.request;
			
	   		STATUS_LOG((6, "%s: FinishDeviceRecovery SendSCSICommandforCBIProtocol sent", getName() ));
			status = SendSCSICommandForCBIProtocol( tempTask );
	   		STATUS_LOG((5, "%s: FinishDeviceRecovery SendSCSICommandforCBIProtocol returned %x",
	   					getName(),
	   					status));
			if( status != kIOReturnSuccess )
			{
				goto ErrorExit;
			}
	   	}
	}
	
	return;
	
	
ErrorExit:
	
	
	if ( tempTask != NULL )
	{
		RejectTask( tempTask );
	}
	
}


//�����������������������������������������������������������������������������
//	� DeviceRecoveryCompletionAction								[PROTECTED]
//�����������������������������������������������������������������������������

void 
IOUSBMassStorageClass::DeviceRecoveryCompletionAction(
					                void *			target,
					                void *			parameter,
					                IOReturn		status,
					                UInt32			bufferSizeRemaining)
{
	UNUSED( parameter );
	UNUSED( bufferSizeRemaining );
	
	IOUSBMassStorageClass *		theMSC;
	
	theMSC = (IOUSBMassStorageClass *) target;
	theMSC->FinishDeviceRecovery( status );
}


// Space reserved for future expansion.
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 3 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 4 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 5 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 6 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 7 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 8 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 9 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 10 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 11 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 12 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 13 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 14 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 15 );
OSMetaClassDefineReservedUnused( IOUSBMassStorageClass, 16 );

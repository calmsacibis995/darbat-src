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

// Libkern includes
#include <libkern/OSByteOrder.h>

// Generic IOKit related headers
#include <IOKit/IOMessage.h>
#include <IOKit/IOKitKeys.h>

// IOKit storage related headers
#include <IOKit/storage/IOStorageDeviceCharacteristics.h>

// SCSI Architecture Model Family includes
#include <IOKit/scsi/SCSICommandOperationCodes.h>

#include "IOSCSIPrimaryCommandsDevice.h"
#include "SCSIPrimaryCommands.h"


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define DEBUG 									0
#define DEBUG_ASSERT_COMPONENT_NAME_STRING		"SPC"

#if DEBUG
#define SCSI_SPC_DEVICE_DEBUGGING_LEVEL			0
#endif


#include "IOSCSIArchitectureModelFamilyDebugging.h"


#if ( SCSI_SPC_DEVICE_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)		IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( SCSI_SPC_DEVICE_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)		IOLog x
#else
#define ERROR_LOG(x)
#endif

#if ( SCSI_SPC_DEVICE_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)		IOLog x
#else
#define STATUS_LOG(x)
#endif


#define super IOSCSIProtocolInterface
OSDefineMetaClass ( IOSCSIPrimaryCommandsDevice, IOSCSIProtocolInterface );
OSDefineAbstractStructors ( IOSCSIPrimaryCommandsDevice, IOSCSIProtocolInterface );


//�����������������������������������������������������������������������������
//	Constants
//�����������������������������������������������������������������������������

enum
{
	kSecondsInAMinute = 60
};

#define	kPowerConditionsModePage					0x1A
#define	kPowerConditionsModePageSize				12
#define kIOPropertyPowerConditionsSupportedKey		"PowerConditionsSupported"
#define kAppleKeySwitchProperty						"AppleKeyswitch"
#define kKeySwitchProperty							"Keyswitch"

// Reserved fields
#define fKeySwitchNotifier							fIOSCSIPrimaryCommandsDeviceReserved->fKeySwitchNotifier
#define fANSIVersion								fIOSCSIPrimaryCommandsDeviceReserved->fANSIVersion
#define fCMDQUE										fIOSCSIPrimaryCommandsDeviceReserved->fCMDQUE
#define	fTaskID										fIOSCSIPrimaryCommandsDeviceReserved->fTaskID
#define	fTaskIDLock									fIOSCSIPrimaryCommandsDeviceReserved->fTaskIDLock

#if 0
#pragma mark -
#pragma mark � Public Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� init - Called by IOKit to initialize us.						   [PUBLIC]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::init ( OSDictionary * propTable )
{
	
	bool	result = false;
	
	require ( super::init ( propTable ), ErrorExit );
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� start - Called by IOKit to start our services.				   [PUBLIC]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::start ( IOService * provider )
{
	
	bool			result			= false;
	bool			supported		= false;
	UInt64			maxByteCount	= 0;
	OSIterator *	iterator		= NULL;
	OSObject *		obj				= NULL;
	OSDictionary *	dict			= NULL;
	OSString *		string			= NULL;
	OSNumber *		value			= NULL;
	
	// Call our super class' start routine so that all inherited
	// behavior is initialized.	
	require ( super::start ( provider ), ErrorExit );
	
	fDeviceAccessEnabled 			= false;
	fDeviceAccessSuspended			= false;
	fDeviceSupportsPowerConditions 	= false;
	fNumCommandsOutstanding 		= 0;
	
	fIOSCSIPrimaryCommandsDeviceReserved = IONew ( IOSCSIPrimaryCommandsDeviceExpansionData, 1 );
	require_nonzero ( fIOSCSIPrimaryCommandsDeviceReserved, ErrorExit );
	
	bzero ( fIOSCSIPrimaryCommandsDeviceReserved,
			sizeof ( IOSCSIPrimaryCommandsDeviceExpansionData ) );
	
	fANSIVersion = kINQUIRY_ANSI_VERSION_NoClaimedConformance;
	
	fTaskIDLock = IOSimpleLockAlloc ( );
	require_nonzero ( fTaskIDLock, FreeReservedMemory );
	
	fProtocolDriver = OSDynamicCast ( IOSCSIProtocolInterface, provider );
	require_nonzero ( fProtocolDriver, FreeTaskIDLock );
	
	fDeviceCharacteristicsDictionary = OSDictionary::withCapacity ( 1 );
	require_nonzero ( fDeviceCharacteristicsDictionary, FreeTaskIDLock );
	
	string = ( OSString * ) GetProtocolDriver ( )->getProperty ( kIOPropertySCSIVendorIdentification );	
	check ( string );
	fDeviceCharacteristicsDictionary->setObject ( kIOPropertyVendorNameKey, string );
	
	string = ( OSString * ) GetProtocolDriver ( )->getProperty ( kIOPropertySCSIProductIdentification );	
	check ( string );
	fDeviceCharacteristicsDictionary->setObject ( kIOPropertyProductNameKey, string );
	
	string = ( OSString * ) GetProtocolDriver ( )->getProperty ( kIOPropertySCSIProductRevisionLevel );	
	check ( string );
	fDeviceCharacteristicsDictionary->setObject ( kIOPropertyProductRevisionLevelKey, string );
	
	value = ( OSNumber * ) GetProtocolDriver ( )->getProperty ( kIOPropertyReadTimeOutDurationKey );	
	if ( value != NULL );
	{
		fDeviceCharacteristicsDictionary->setObject ( kIOPropertyReadTimeOutDurationKey, value );
	}
	
	value = ( OSNumber * ) GetProtocolDriver ( )->getProperty ( kIOPropertyWriteTimeOutDurationKey );	
	if ( value != NULL );
	{
		fDeviceCharacteristicsDictionary->setObject ( kIOPropertyWriteTimeOutDurationKey, value );
	}
	
	// Now create the required command sets used by the class
	require ( CreateCommandSetObjects ( ), FreeDeviceDictionary );
	
	// Open our provider so it can't slip out from under us
	GetProtocolDriver ( )->open ( this );
	
	STATUS_LOG ( ( "%s: Check for the SCSI Device Characteristics property from provider.\n", getName ( ) ) );
	
	// Check if the personality for this device specifies device characteristics.
	if ( ( GetProtocolDriver ( )->getProperty ( kIOPropertySCSIDeviceCharacteristicsKey ) ) == NULL )
	{
		
		STATUS_LOG ( ( "%s: No SCSI Device Characteristics property, set defaults.\n", getName ( ) ) );
		fDefaultInquiryCount = 0;
		
	}
	
	else
	{
		
		OSDictionary * characterDict;
		
		STATUS_LOG ( ( "%s: Get the SCSI Device Characteristics property from provider.\n", getName ( ) ) );
		characterDict = OSDynamicCast ( OSDictionary, ( GetProtocolDriver ( )->getProperty ( kIOPropertySCSIDeviceCharacteristicsKey ) ) );
		
		STATUS_LOG ( ( "%s: set this SCSI Device Characteristics property.\n", getName ( ) ) );
		setProperty ( kIOPropertySCSIDeviceCharacteristicsKey, characterDict );

		// Check if the personality for this device specifies a default Inquiry count
		STATUS_LOG ( ( "%s: check for the Inquiry Length property.\n", getName ( ) ) );
		
		if ( characterDict->getObject ( kIOPropertySCSIInquiryLengthKey ) == NULL )
		{
			
			STATUS_LOG ( ( "%s: No Inquiry Length property, use default.\n", getName ( ) ) );
			fDefaultInquiryCount = 0;
			
		}
		
		else
		{
			
			OSNumber *	defaultInquiry;
			
			STATUS_LOG ( ( "%s: Get Inquiry Length property.\n", getName ( ) ) );
			defaultInquiry = OSDynamicCast ( OSNumber, characterDict->getObject ( kIOPropertySCSIInquiryLengthKey ) );
			
			// This device has a default Inquiry length, use that.
			fDefaultInquiryCount = defaultInquiry->unsigned32BitValue ( );
			
		}
		
	}
	
	fProtocolAccessEnabled = true;
	
	require ( InitializeDeviceSupport ( ), CloseProvider );
	
	iterator = getMatchingServices ( nameMatching ( kAppleKeySwitchProperty ) );
	if ( iterator != NULL )
	{
		
		while ( obj = iterator->getNextObject ( ) )
		{
			
			IOService *		service = ( IOService * ) obj;
			OSBoolean *		boolKey = NULL;
			
			boolKey = OSDynamicCast (
								OSBoolean,
								service->getProperty ( kKeySwitchProperty ) );
			
			dict = GetProtocolCharacteristicsDictionary ( );
			
			OSString *	protocol = OSDynamicCast ( OSString, dict->getObject ( kIOPropertyPhysicalInterconnectTypeKey ) );
			
			if ( ( protocol == NULL ) ||
				 ( protocol->isEqualTo ( kIOPropertyPhysicalInterconnectTypeUSB ) ) ||
				 ( protocol->isEqualTo ( kIOPropertyPhysicalInterconnectTypeFireWire ) ) ||
				 ( protocol->isEqualTo ( kIOPropertyPhysicalInterconnectTypeATAPI ) ) )
			{			
				
				setProperty ( kAppleKeySwitchProperty, boolKey );
				
				// Add a notification for the Apple KeySwitch on the servers.
				fKeySwitchNotifier = addNotification (
						gIOMatchedNotification,
						nameMatching ( kAppleKeySwitchProperty ),
						( IOServiceNotificationHandler ) &IOSCSIPrimaryCommandsDevice::ServerKeyswitchCallback,
						this,
						0 );
				
			}
			
		}
		
		iterator->release ( );
		iterator = NULL;
		
	}
	
	// assume device will use infinite time outs
	fReadTimeoutDuration	= 0;
	fWriteTimeoutDuration	= 0;
	
	// determine the protocol-specific default read/write time out values 
	dict = GetProtocolCharacteristicsDictionary ( );
	if ( dict != NULL )
	{
		
		value = OSDynamicCast ( OSNumber, dict->getObject ( kIOPropertyReadTimeOutDurationKey ) );
		
		if ( value != NULL )
		{
			fReadTimeoutDuration = value->unsigned32BitValue ( );
		}
		
		value = OSDynamicCast ( OSNumber, dict->getObject ( kIOPropertyWriteTimeOutDurationKey ) );
		
		if ( value != NULL )
		{
			fWriteTimeoutDuration = value->unsigned32BitValue ( );
		}
		
	}
	
	// check if we should override the maximum read/write time outs with a device-specific
	dict = GetDeviceCharacteristicsDictionary ( );
	if ( dict != NULL )
	{
		
		value = OSDynamicCast ( OSNumber, dict->getObject ( kIOPropertyReadTimeOutDurationKey ) );
		
		if ( value != NULL )
		{
			fReadTimeoutDuration = value->unsigned32BitValue ( );
		}
		
		value = OSDynamicCast ( OSNumber, dict->getObject ( kIOPropertyWriteTimeOutDurationKey ) );
		
		if ( value != NULL )
		{
			fWriteTimeoutDuration = value->unsigned32BitValue ( );
		}
		
	}
	
	// See if the transport driver wants us to limit the read transfer byte count
	supported = GetProtocolDriver ( )->IsProtocolServiceSupported (
						kSCSIProtocolFeature_MaximumReadTransferByteCount,
						&maxByteCount );	
	
	if ( supported == true )
	{
		setProperty ( kIOMaximumByteCountReadKey, maxByteCount, 64 );
	}
	
	// See if the transport driver wants us to limit the write transfer byte count
	supported = GetProtocolDriver ( )->IsProtocolServiceSupported (
						kSCSIProtocolFeature_MaximumWriteTransferByteCount,
						&maxByteCount );	
	
	if ( supported == true )
	{
		setProperty ( kIOMaximumByteCountWriteKey, maxByteCount, 64 );
	}
	
	fDeviceAccessEnabled = true;
	StartDeviceSupport ( );

	result = true;
	
	return result;
	
	
CloseProvider:
	
	
	GetProtocolDriver ( )->close ( this );
	
	
FreeDeviceDictionary:
	
	
	require_nonzero ( fDeviceCharacteristicsDictionary, FreeTaskIDLock );
	fDeviceCharacteristicsDictionary->release ( );
	fDeviceCharacteristicsDictionary = NULL;
	
	
FreeTaskIDLock:
	
	
	require_nonzero ( fTaskIDLock, FreeReservedMemory );
	IOSimpleLockFree ( fTaskIDLock );
	fTaskIDLock = NULL;
	
	
FreeReservedMemory:
	
	
	require_nonzero ( fIOSCSIPrimaryCommandsDeviceReserved, ErrorExit );
	IODelete ( fIOSCSIPrimaryCommandsDeviceReserved, IOSCSIPrimaryCommandsDeviceExpansionData, 1 );
	fIOSCSIPrimaryCommandsDeviceReserved = NULL;
	

ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� stop - Called by IOKit to stop our services.					   [PUBLIC]
//�����������������������������������������������������������������������������

void 
IOSCSIPrimaryCommandsDevice::stop ( IOService * provider )
{
	
	fProtocolAccessEnabled = false;
	
	// Put some protection from having stop called multiple times
	// GetProtocolDriver is called all over the place in this object
	if ( fDeviceAccessEnabled == true )
	{
		
		fDeviceAccessEnabled = false;
		StopDeviceSupport ( );
		
	}
	
	if ( ( fProtocolDriver != NULL ) && ( fProtocolDriver == provider ) )
	{
		
		fProtocolDriver->close ( this );
		fProtocolDriver = NULL;
		
		super::stop ( provider );
		
	}
	
}


//�����������������������������������������������������������������������������
//	� free - Called by IOKit to free any resources.					   [PUBLIC]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::free ( void )
{
	
	// Free any command set objects created by
	// CreateCommandSetObjects()
	FreeCommandSetObjects ( );
	
	// Free our reserved data
	if ( fIOSCSIPrimaryCommandsDeviceReserved != NULL )
	{
		
		if ( fTaskIDLock != NULL )
		{
			
			IOSimpleLockFree ( fTaskIDLock );
			fTaskIDLock = NULL;
			
		}
		
		IODelete ( fIOSCSIPrimaryCommandsDeviceReserved, IOSCSIPrimaryCommandsDeviceExpansionData, 1 );
		fIOSCSIPrimaryCommandsDeviceReserved = NULL;
		
	}
	
	if ( fDeviceCharacteristicsDictionary != NULL )
	{
		
		fDeviceCharacteristicsDictionary->release ( );
		fDeviceCharacteristicsDictionary = NULL;
		
	}
	
	// Make sure to call our super
	super::free ( );
	
}


//�����������������������������������������������������������������������������
//	� message - Called by IOKit to deliver messages.				   [PUBLIC]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::message (	UInt32 		type,
										IOService *	nub,
										void *		arg )
{
	
	IOReturn status;
	
	switch ( type )
	{
		
		// The device is no longer attached to the bus,
		// close provider so message will continue
		// to propagate up the driver stack.
		case kIOMessageServiceIsRequestingClose:
		{
			
			STATUS_LOG ( ( "%s: kIOMessageServiceIsRequestingClose Received\n", getName ( ) ) );
			
			fProtocolAccessEnabled = false;
			
			if ( fDeviceAccessEnabled == true )
			{
				
				fDeviceAccessEnabled = false;
				StopDeviceSupport ( );
				
			}
			
			if ( fKeySwitchNotifier != NULL )
			{
				
				fKeySwitchNotifier->remove ( );
				fKeySwitchNotifier = NULL;
				
			}
			
			TerminateDeviceSupport ( );
			
			if ( fProtocolDriver != NULL )
			{
				fProtocolDriver->close ( this );
			}
			
			status = kIOReturnSuccess;
			
		}
		break;

		case kSCSIServicesNotification_Suspend:
		{
			
			ERROR_LOG ( ( "type = kSCSIServicesNotification_Suspend, nub = %p\n", nub ) );
			fDeviceAccessSuspended = true;
			SuspendDeviceSupport ( );
			status = kIOReturnSuccess;
			
		}
		break;
		
		case kSCSIServicesNotification_Resume:
		{
			
			ERROR_LOG ( ( "type = kSCSIServicesNotification_Resume, nub = %p\n", nub ) );
			fDeviceAccessSuspended = false;
			ResumeDeviceSupport ( );
			status = kIOReturnSuccess;
			
		}
		break;

		case kSCSIProtocolNotification_VerifyDeviceState:
		{
			
			STATUS_LOG ( ("%s: kSCSIProtocolNotification_VerifyDeviceState Received\n", getName ( ) ) );
			status = VerifyDeviceState ( );
			
		}
		break;

		default:
		{
			status = super::message ( type, nub, arg );
		}
		break;
		
	}
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� VerifyDeviceState - Used to verify that device is in a known state.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::VerifyDeviceState ( void )
{
	return kIOReturnSuccess;
}


//�����������������������������������������������������������������������������
//	� IsProtocolAccessEnabled - Returns whether protocol access is enabled
//								or not.								[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::IsProtocolAccessEnabled ( void )
{
	return fProtocolAccessEnabled;
}


//�����������������������������������������������������������������������������
//	� IsDeviceAccessEnabled - Returns whether device access is enabled or not.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::IsDeviceAccessEnabled ( void )
{
	return fDeviceAccessEnabled;
}


//�����������������������������������������������������������������������������
//	� IsDeviceAccessSuspended - Returns whether device access is suspended
//								or not.								[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::IsDeviceAccessSuspended ( void )
{
	return fDeviceAccessSuspended;
}


#if 0
#pragma mark -
#pragma mark � Power Management Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� setAggressiveness - 	Called by power management to tell us to change
//							the device aggressiveness values.		[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::setAggressiveness ( UInt32 type, UInt32 minutes )
{
	
	UInt32	numStateTransitions = 0;
	
	if ( type == kPMMinutesToSpinDown )
	{
		
		STATUS_LOG ( ( "IOSCSIPrimaryCommandsDevice: setting idle timer to %ld min\n", minutes ) );
		
		numStateTransitions = GetNumberOfPowerStateTransitions ( );
		if ( numStateTransitions != 0 )
		{
			
			// Set the idle timer based on number of power state transitions
			setIdleTimerPeriod ( minutes * ( kSecondsInAMinute / numStateTransitions ) );
			
		}
		
		else
		{
			
			// The device has requested no transitions, don't do any
			// (except System Sleep, which is unavoidable).
			setIdleTimerPeriod ( 0 );
			
		}
		
	}
	
	return ( super::setAggressiveness ( type, minutes ) );
	
}


//�����������������������������������������������������������������������������
//	� ClearPowerOnReset - 	Clears any power-on sense data.			[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::ClearPowerOnReset ( void )
{
	
	SCSI_Sense_Data				senseBuffer		= { 0 };
	IOMemoryDescriptor *		bufferDesc		= NULL;
	SCSITaskIdentifier			request			= NULL;
	bool						driveReady 		= false;
	bool						result 			= true;
	SCSIServiceResponse 		serviceResponse = kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
	
	bufferDesc = IOMemoryDescriptor::withAddress ( ( void * ) &senseBuffer,
													kSenseDefaultSize,
													kIODirectionIn );
	
	request = GetSCSITask ( );
	
	do
	{
		
		if ( TEST_UNIT_READY ( request, 0 ) == true )
		{
			
			// The command was successfully built, now send it
			serviceResponse = SendCommand ( request, kTenSecondTimeoutInMS );
			
		}
		
		else
		{
			PANIC_NOW ( ( "IOSCSIPrimaryCommandsDevice::ClearPowerOnReset malformed command" ) );
		}
		
		if ( serviceResponse == kSCSIServiceResponse_TASK_COMPLETE )
		{
			
			bool validSense = false;
			
			if ( GetTaskStatus ( request ) == kSCSITaskStatus_CHECK_CONDITION )
			{
				
				validSense = GetAutoSenseData ( request, &senseBuffer, sizeof ( senseBuffer ) );
				if ( validSense == false )
				{
					
					if ( REQUEST_SENSE ( request, bufferDesc, kSenseDefaultSize, 0  ) == true )
					{
						
						// The command was successfully built, now send it
						serviceResponse = SendCommand ( request, kTenSecondTimeoutInMS );
						
					}
					
					else
					{
						PANIC_NOW ( ( "IOSCSIPrimaryCommandsDevice::ClearPowerOnReset REQUEST_SENSE malformed command" ) );
					}
					
					if ( serviceResponse == kSCSIServiceResponse_TASK_COMPLETE )
					{
						
						validSense = true;
						
					}
					
					else
					{
						IOSleep ( 200 );
					}
					
				}
				
				if ( validSense == true )
				{
					
					// Make sure we don't get a Unit Attention with power on reset qualifier or
					// medium changed qualifier
					
					if ( ( ( ( senseBuffer.SENSE_KEY & kSENSE_KEY_Mask ) == kSENSE_KEY_UNIT_ATTENTION  ) && 
							( senseBuffer.ADDITIONAL_SENSE_CODE == 0x29 ) &&
							( senseBuffer.ADDITIONAL_SENSE_CODE_QUALIFIER == 0x00 ) ) ||
						 ( ( ( senseBuffer.SENSE_KEY & kSENSE_KEY_Mask ) == kSENSE_KEY_UNIT_ATTENTION  ) && 
							( senseBuffer.ADDITIONAL_SENSE_CODE == 0x28 ) &&
							( senseBuffer.ADDITIONAL_SENSE_CODE_QUALIFIER == 0x00 ) ) )
					{
						
						STATUS_LOG ( ( "%s::drive NOT READY\n", getName ( ) ) );
						driveReady = false;
						IOSleep ( 200 );
						
					}
					
					else
					{
						
						driveReady = true;
						STATUS_LOG ( ( "%s::drive READY\n", getName ( ) ) );
						
					}
					
					STATUS_LOG ( ( "sense data: %01x, %02x, %02x\n",
								( senseBuffer.SENSE_KEY & kSENSE_KEY_Mask ),
								senseBuffer.ADDITIONAL_SENSE_CODE,
								senseBuffer.ADDITIONAL_SENSE_CODE_QUALIFIER ) );
					
				}
				
			}
			
			else
			{
				
				driveReady = true;
			
			}
			
		}
		
		else
		{
			
			// The command failed - perhaps the device was hot unplugged
			// give other threads some time to run.
			IOSleep ( 200 );
			
		}
	
	// Check isInactive() in case device was hot unplugged during sleep
	// and we are in an infinite loop here.
	} while ( ( driveReady == false ) && ( isInactive ( ) == false ) );
	
	bufferDesc->release ( );
	ReleaseSCSITask ( request );
	
	result = isInactive ( ) ? false : true;
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� CheckPowerConditionsModePage - Checks the power conditions mode page.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::CheckPowerConditionsModePage ( void )
{

	UInt8						buffer[kPowerConditionsModePageSize];	
	IOMemoryDescriptor *		bufferDesc;
	IOReturn					status;
	bool						use10Byte = true;
	
	STATUS_LOG ( ( "%s::%s called\n", getName ( ), __FUNCTION__ ) );
	
	bufferDesc = IOMemoryDescriptor::withAddress (  ( void * ) buffer,
													kPowerConditionsModePageSize,
													kIODirectionIn );
	
	if ( bufferDesc != NULL )
	{
	
	
		status = GetModeSense ( bufferDesc,
								kPowerConditionsModePage,
								kPowerConditionsModePageSize,
								&use10Byte );
		if ( status == kIOReturnSuccess )
		{
			
			if ( ( buffer[8] & 0x3F ) == kPowerConditionsModePage )
			{
				
				STATUS_LOG ( ( "Device supports power conditions page\n" ) );
				
				// This device supports the power conditions mode page, so set
				// our flag to true
				fDeviceSupportsPowerConditions = true;
				
			}
			
		}
		
		bufferDesc->release ( );
		
	}
	
	#if ( SCSI_SPC_DEVICE_DEBUGGING_LEVEL > 0 )
		setProperty ( kIOPropertyPowerConditionsSupportedKey, fDeviceSupportsPowerConditions );
	#endif /* SCSI_SPC_DEVICE_DEBUGGING_LEVEL */
	
}


//�����������������������������������������������������������������������������
//	� IncrementOutstandingCommandsCount - 	Called to increment the number of
//											outstanding commands.	[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::IncrementOutstandingCommandsCount ( void )
{
	
	fCommandGate->runAction ( ( IOCommandGate::Action )
		&IOSCSIPrimaryCommandsDevice::sIncrementOutstandingCommandsCount );
	
}


//�����������������������������������������������������������������������������
//	� sIncrementOutstandingCommandsCount - C->C++ glue code.
//															[STATIC][PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::sIncrementOutstandingCommandsCount (
									IOSCSIPrimaryCommandsDevice * self )
{
	
	self->HandleIncrementOutstandingCommandsCount ( );
	
}


//�����������������������������������������������������������������������������
// � HandleIncrementOutstandingCommandsCount - 	Increments number of
//												outstanding commands.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::HandleIncrementOutstandingCommandsCount ( void )
{
	
	fNumCommandsOutstanding++;	
	
}


#if 0
#pragma mark -
#pragma mark ��SCSI Task Get and Release
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � GetSCSITask - 	Gets a SCSITask for use by the caller.			[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaskIdentifier 
IOSCSIPrimaryCommandsDevice::GetSCSITask ( void )
{
	
	SCSITask *	newTask = OSTypeAlloc ( SCSITask );
	
	check ( newTask );
	
	newTask->SetTaskOwner ( this );
	
	// thread safe increment outstanding command count
	IncrementOutstandingCommandsCount ( );
	
	// Make sure the object is not removed if there is a pending
	// command.
	retain ( );
	
	return ( SCSITaskIdentifier ) newTask;
	
}


//�����������������������������������������������������������������������������
// � ReleaseSCSITask - 	Releases a SCSITask.						[PROTECTED]
//�����������������������������������������������������������������������������

void 
IOSCSIPrimaryCommandsDevice::ReleaseSCSITask ( SCSITaskIdentifier request )
{
	
	require_nonzero ( request, Exit );
	
	// decrement outstanding command count
	fNumCommandsOutstanding--;
	
	request->release ( );
	
	// Since the command has been released, let go of the retain on this
	// object.
	release ( );
	
	
Exit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
// � GetUniqueTagID - 	Returns a unique tagged task ID.			[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaggedTaskIdentifier 
IOSCSIPrimaryCommandsDevice::GetUniqueTagID ( void )
{
	
	SCSITaggedTaskIdentifier	taskID = kSCSIUntaggedTaskIdentifier;
	
	IOSimpleLockLock ( fTaskIDLock );
	
	taskID = ++fTaskID;
	
	IOSimpleLockUnlock ( fTaskIDLock );
	
	return taskID;
	
}


#if 0
#pragma mark -
#pragma mark � Supporting Object Accessor Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � GetProtocolDriver - Returns the protocol driver.				[PROTECTED]
//�����������������������������������������������������������������������������

IOSCSIProtocolInterface *
IOSCSIPrimaryCommandsDevice::GetProtocolDriver ( void )
{
	
	check ( fProtocolDriver );
	return fProtocolDriver;
	
}


//�����������������������������������������������������������������������������
// � GetSCSIPrimaryCommandObject - Returns SCSIPrimaryCommands object.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

SCSIPrimaryCommands	*
IOSCSIPrimaryCommandsDevice::GetSCSIPrimaryCommandObject ( void )
{
	
	STATUS_LOG ( ( "%s: getSCSIPrimaryCommandObject called.\n", getName ( ) ) );
	return fSCSIPrimaryCommandObject;
	
}


//�����������������������������������������������������������������������������
// � CreateCommandSetObjects - Called to create command set objects.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::CreateCommandSetObjects ( void )
{
	
	bool	result = false;
	
	fSCSIPrimaryCommandObject =
		SCSIPrimaryCommands::CreateSCSIPrimaryCommandObject ( );
	require_nonzero ( fSCSIPrimaryCommandObject, ErrorExit );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
// � FreeCommandSetObjects - Called to free command set objects.	[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::FreeCommandSetObjects ( void )
{
	
	if ( fSCSIPrimaryCommandObject != NULL )
	{
		
		fSCSIPrimaryCommandObject->release( );
		fSCSIPrimaryCommandObject = NULL;
		
	}
	
}


#if 0
#pragma mark -
#pragma mark � Task Execution Support Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� TaskCallback - Callback method for synchronous commands.		  [PRIVATE]
//�����������������������������������������������������������������������������

void 
IOSCSIPrimaryCommandsDevice::TaskCallback ( SCSITaskIdentifier completedTask )
{
	
	SCSITask *						scsiRequest	= NULL;
	IOSCSIPrimaryCommandsDevice *	owner		= NULL;
	
	scsiRequest = OSDynamicCast ( SCSITask, completedTask );
	require_nonzero ( scsiRequest, ErrorExit );
	
	owner = ( IOSCSIPrimaryCommandsDevice * ) scsiRequest->GetTaskOwner ( );
	require_nonzero ( owner, ErrorExit );
	
	owner->TaskCompletion ( scsiRequest );
	
	
ErrorExit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	� TaskCompletion - Callback method for synchronous commands.	  [PRIVATE]
//�����������������������������������������������������������������������������

void 
IOSCSIPrimaryCommandsDevice::TaskCompletion ( SCSITaskIdentifier completedTask )
{
	
	fCommandGate->commandWakeup ( completedTask, true );
	
}


//�����������������������������������������������������������������������������
// � SendCommand - Called to send a command synchronously.			[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::SendCommand (
					SCSITaskIdentifier	request,
					UInt32				timeoutDuration )
{
	
	SCSIServiceResponse		serviceResponse = kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
	
	require ( IsProtocolAccessEnabled ( ), ProtocolAccessDisabledError );
	
	SetTimeoutDuration ( request, timeoutDuration );
	SetTaskCompletionCallback ( request, &IOSCSIPrimaryCommandsDevice::TaskCallback );
	
	SetAutosenseCommand ( request,
						  kSCSICmd_REQUEST_SENSE,
						  0x00,
						  0x00,
						  0x00,
						  sizeof ( SCSI_Sense_Data ),
						  0x00 );
	
	GetProtocolDriver ( )->ExecuteCommand ( request );
	
	// Wait for the completion routine to get called
	fCommandGate->runAction ( ( IOCommandGate::Action )
							  &IOSCSIPrimaryCommandsDevice::sWaitForTask,
							  request );
	
	serviceResponse = GetServiceResponse ( request );
	
	return serviceResponse;
	
	
ProtocolAccessDisabledError:
	
	
	SetServiceResponse ( request, serviceResponse );
	SetTaskStatus ( request, kSCSITaskStatus_No_Status );
	
	return serviceResponse;
	
}


//�����������������������������������������������������������������������������
// � SendCommand - Called to send a command asynchronously.			[PROTECTED]
//�����������������������������������������������������������������������������

void 
IOSCSIPrimaryCommandsDevice::SendCommand ( 
						SCSITaskIdentifier	request,
						UInt32 				timeoutDuration,
						SCSITaskCompletion 	taskCompletion )
{
	
	SetTaskCompletionCallback ( request, taskCompletion );
	
	require ( IsProtocolAccessEnabled ( ), ProtocolAccessDisabledError );
	
	SetTimeoutDuration ( request, timeoutDuration );
	
	SetAutosenseCommand ( request,
						  kSCSICmd_REQUEST_SENSE,
						  0x00,
						  0x00,
						  0x00,
						  sizeof ( SCSI_Sense_Data ),
						  0x00 );
	
	GetProtocolDriver ( )->ExecuteCommand ( request );
	
	return;
	
	
ProtocolAccessDisabledError:
	
	
	SetServiceResponse ( request,
						 kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE );
	SetTaskStatus ( request, kSCSITaskStatus_No_Status );
	// The task has completed, execute the callback.
	TaskCompletedNotification ( request );
	
	return;
	
}


//�����������������������������������������������������������������������������
// � GatedWaitForTask - Called to wait for a task to complete.		  [PRIVATE]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::GatedWaitForTask ( SCSITaskIdentifier request )
{
	
	SCSITask *		task	= OSDynamicCast ( SCSITask, request );
	IOReturn		result	= kIOReturnBadArgument;
	
	if ( task != NULL )
	{
		
		while ( task->GetTaskState ( ) != kSCSITaskState_ENDED )
		{
			
			result = fCommandGate->commandSleep ( task, THREAD_UNINT );
			
		}
		
	}
	
	if ( result == THREAD_AWAKENED )
		result = kIOReturnSuccess;
	
	return result;
	
}


#if 0
#pragma mark -
#pragma mark � SCSI Task Field Accessors
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � ResetForNewTask - Resets the task.								[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::ResetForNewTask (	
									SCSITaskIdentifier 		request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->ResetForNewTask ( );
	
}


//�����������������������������������������������������������������������������
// � SetTaskAttribute - Sets the SCSITaskAttribute.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTaskAttribute (
									SCSITaskIdentifier	request,
									SCSITaskAttribute	newAttribute )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTaskAttribute ( newAttribute );
	
}


//�����������������������������������������������������������������������������
// � GetTaskAttribute - Gets the SCSITaskAttribute.					[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaskAttribute
IOSCSIPrimaryCommandsDevice::GetTaskAttribute ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetTaskAttribute ( );
	
}


//�����������������������������������������������������������������������������
// � SetTaggedTaskIdentifier - Sets the SCSITaggedTaskIdentifier.	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTaggedTaskIdentifier (
							SCSITaskIdentifier			request,
							SCSITaggedTaskIdentifier	taggedTaskIdentifier )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTaggedTaskIdentifier ( taggedTaskIdentifier );
	
}


//�����������������������������������������������������������������������������
// � GetTaggedTaskIdentifier - Gets the SCSITaggedTaskIdentifier.	[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaggedTaskIdentifier
IOSCSIPrimaryCommandsDevice::GetTaggedTaskIdentifier (
							SCSITaskIdentifier			request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetTaggedTaskIdentifier ( );
	
}


//�����������������������������������������������������������������������������
// � SetTaskState - Sets the SCSITaskState.							[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTaskState ( SCSITaskIdentifier	request,
											SCSITaskState		newTaskState )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTaskState ( newTaskState );
	
}


//�����������������������������������������������������������������������������
// � GetTaskState - Gets the SCSITaskState.							[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaskState
IOSCSIPrimaryCommandsDevice::GetTaskState ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest;

	scsiRequest = OSDynamicCast ( SCSITask, request );
	return scsiRequest->GetTaskState( );
	
}


//�����������������������������������������������������������������������������
// � SetTaskStatus - Sets the SCSITaskStatus.						[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTaskStatus ( SCSITaskIdentifier	request,
											 SCSITaskStatus		newStatus )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTaskStatus ( newStatus );
	
}


//�����������������������������������������������������������������������������
// � GetTaskStatus - Gets the SCSITaskStatus.						[PROTECTED]
//�����������������������������������������������������������������������������

SCSITaskStatus
IOSCSIPrimaryCommandsDevice::GetTaskStatus ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetTaskStatus ( );
	
}


//�����������������������������������������������������������������������������
// � SetCommandDescriptorBlock - Sets 6-byte CDB.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetCommandDescriptorBlock (
									SCSITaskIdentifier 		request,
									UInt8					cdbByte0,
									UInt8					cdbByte1,
									UInt8					cdbByte2,
									UInt8					cdbByte3,
									UInt8					cdbByte4,
									UInt8					cdbByte5 )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetCommandDescriptorBlock (
									cdbByte0,
									cdbByte1,
									cdbByte2,
									cdbByte3,
									cdbByte4,
									cdbByte5 );
	
}


//�����������������������������������������������������������������������������
// � SetCommandDescriptorBlock - Sets 10-byte CDB.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetCommandDescriptorBlock (
									SCSITaskIdentifier 		request,
									UInt8					cdbByte0,
									UInt8					cdbByte1,
									UInt8					cdbByte2,
									UInt8					cdbByte3,
									UInt8					cdbByte4,
									UInt8					cdbByte5,
									UInt8					cdbByte6,
									UInt8					cdbByte7,
									UInt8					cdbByte8,
									UInt8					cdbByte9 )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetCommandDescriptorBlock (
									cdbByte0,
									cdbByte1,
									cdbByte2,
									cdbByte3,
									cdbByte4,
									cdbByte5,
									cdbByte6,
									cdbByte7,
									cdbByte8,
									cdbByte9 );
	
}


//�����������������������������������������������������������������������������
// � SetCommandDescriptorBlock - Sets 12-byte CDB.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetCommandDescriptorBlock ( 
									SCSITaskIdentifier 		request,
									UInt8					cdbByte0,
									UInt8					cdbByte1,
									UInt8					cdbByte2,
									UInt8					cdbByte3,
									UInt8					cdbByte4,
									UInt8					cdbByte5,
									UInt8					cdbByte6,
									UInt8					cdbByte7,
									UInt8					cdbByte8,
									UInt8					cdbByte9,
									UInt8					cdbByte10,
									UInt8					cdbByte11 )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetCommandDescriptorBlock (
									cdbByte0,
									cdbByte1,
									cdbByte2,
									cdbByte3,
									cdbByte4,
									cdbByte5,
									cdbByte6,
									cdbByte7,
									cdbByte8,
									cdbByte9,
									cdbByte10,
									cdbByte11 );
	
}


//�����������������������������������������������������������������������������
// � SetCommandDescriptorBlock - Sets 16-byte CDB.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetCommandDescriptorBlock (
									SCSITaskIdentifier 		request,
									UInt8					cdbByte0,
									UInt8					cdbByte1,
									UInt8					cdbByte2,
									UInt8					cdbByte3,
									UInt8					cdbByte4,
									UInt8					cdbByte5,
									UInt8					cdbByte6,
									UInt8					cdbByte7,
									UInt8					cdbByte8,
									UInt8					cdbByte9,
									UInt8					cdbByte10,
									UInt8					cdbByte11,
									UInt8					cdbByte12,
									UInt8					cdbByte13,
									UInt8					cdbByte14,
									UInt8					cdbByte15 )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetCommandDescriptorBlock (
									cdbByte0,
									cdbByte1,
									cdbByte2,
									cdbByte3,
									cdbByte4,
									cdbByte5,
									cdbByte6,
									cdbByte7,
									cdbByte8,
									cdbByte9,
									cdbByte10,
									cdbByte11,
									cdbByte12,
									cdbByte13,
									cdbByte14,
									cdbByte15 );
	
}


//�����������������������������������������������������������������������������
// � SetDataTransferDirection - Sets the data transfer direction.	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetDataTransferDirection (
									SCSITaskIdentifier	request,
									UInt8				newDirection )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	return scsiRequest->SetDataTransferDirection ( newDirection );
	
}


//�����������������������������������������������������������������������������
// � GetDataTransferDirection - Gets the data transfer direction.	[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOSCSIPrimaryCommandsDevice::GetDataTransferDirection (
										SCSITaskIdentifier	request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetDataTransferDirection ( );
	
}


//�����������������������������������������������������������������������������
// � SetRequestedDataTransferCount - Sets the requested data transfer count.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetRequestedDataTransferCount (
										SCSITaskIdentifier	request,
										UInt64				newRequestedCount )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetRequestedDataTransferCount ( newRequestedCount );
	
}


//�����������������������������������������������������������������������������
// � GetRequestedDataTransferCount - Gets the requested data transfer count.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt64
IOSCSIPrimaryCommandsDevice::GetRequestedDataTransferCount (
										SCSITaskIdentifier	request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetRequestedDataTransferCount ( );
	
}


//�����������������������������������������������������������������������������
// � SetRealizedDataTransferCount - Sets the realized data transfer count.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetRealizedDataTransferCount (
										SCSITaskIdentifier	request,
										UInt64				newRealizedDataCount )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetRealizedDataTransferCount ( newRealizedDataCount );
	
}


//�����������������������������������������������������������������������������
// � GetRealizedDataTransferCount - Gets the realized data transfer count.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt64
IOSCSIPrimaryCommandsDevice::GetRealizedDataTransferCount (
										SCSITaskIdentifier	request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetRealizedDataTransferCount ( );
	
}


//�����������������������������������������������������������������������������
// � SetDataBuffer - Sets the data buffer.							[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetDataBuffer ( SCSITaskIdentifier		request,
											 IOMemoryDescriptor *	newBuffer )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetDataBuffer ( newBuffer );
	
}


//�����������������������������������������������������������������������������
// � GetDataBuffer - Gets the data buffer.							[PROTECTED]
//�����������������������������������������������������������������������������

IOMemoryDescriptor *
IOSCSIPrimaryCommandsDevice::GetDataBuffer ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetDataBuffer ( );
	
}


//�����������������������������������������������������������������������������
// � SetTimeoutDuration - Sets the timeout duration in milliseconds.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTimeoutDuration (
											SCSITaskIdentifier	request,
											UInt32				newTimeout )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTimeoutDuration ( newTimeout );
	
}


//�����������������������������������������������������������������������������
// � GetTimeoutDuration - Gets the timeout duration in milliseconds.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt32
IOSCSIPrimaryCommandsDevice::GetTimeoutDuration ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetTimeoutDuration ( );
	
}


//�����������������������������������������������������������������������������
// � SetTaskCompletionCallback - Sets the completion routine.		[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetTaskCompletionCallback ( 
										SCSITaskIdentifier 		request,
										SCSITaskCompletion 		newCallback )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetTaskCompletionCallback ( newCallback );
	
}


//�����������������������������������������������������������������������������
// � TaskCompletedNotification - Calls the completion routine.		[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::TaskCompletedNotification (  
										SCSITaskIdentifier 		request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->TaskCompletedNotification ( );
	
}


//�����������������������������������������������������������������������������
// � SetServiceResponse - Sets the SCSIServiceResponse.				[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetServiceResponse ( 
										SCSITaskIdentifier 		request,
										SCSIServiceResponse 	serviceResponse )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetServiceResponse ( serviceResponse );
	
}


//�����������������������������������������������������������������������������
// � GetServiceResponse - Gets the SCSIServiceResponse.				[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::GetServiceResponse ( 
										SCSITaskIdentifier 		request )
{
	
	SCSITask *	scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetServiceResponse ( );
	
}


//�����������������������������������������������������������������������������
// � SetAutosenseCommand - Sets the autosense command.				[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetAutosenseCommand (
										SCSITaskIdentifier 		request,
										UInt8					cdbByte0,
										UInt8					cdbByte1,
										UInt8					cdbByte2,
										UInt8					cdbByte3,
										UInt8					cdbByte4,
										UInt8					cdbByte5 )
{
	
	SCSITask *		scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetAutosenseCommand ( cdbByte0, cdbByte1, cdbByte2,
											  cdbByte3, cdbByte4, cdbByte5 );
	
}


//�����������������������������������������������������������������������������
// � GetAutoSenseData - Gets the autosense data.		[DEPRECATED][PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::GetAutoSenseData ( SCSITaskIdentifier	request,
												SCSI_Sense_Data *	senseData )
{
	return GetAutoSenseData ( request, senseData, sizeof ( SCSI_Sense_Data ) );
}


//�����������������������������������������������������������������������������
// � GetAutoSenseData - Gets the autosense data.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::GetAutoSenseData ( SCSITaskIdentifier	request,
												SCSI_Sense_Data *	senseData,
												UInt8				senseDataSize )
{
	
	SCSITask *		scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetAutoSenseData ( senseData, senseDataSize );
	
}


//�����������������������������������������������������������������������������
// � GetAutoSenseDataSize - Gets the autosense data size.			[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOSCSIPrimaryCommandsDevice::GetAutoSenseDataSize ( SCSITaskIdentifier request )
{
	
	SCSITask *		scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetAutoSenseDataSize ( );
	
}


//�����������������������������������������������������������������������������
// � SetApplicationLayerReference - Sets the application layer refcon.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::SetApplicationLayerReference (
									SCSITaskIdentifier	request,
									void *				newReferenceValue )
{
	
	SCSITask *		scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->SetApplicationLayerReference ( newReferenceValue );
	
}


//�����������������������������������������������������������������������������
// � GetApplicationLayerReference - Gets the application layer refcon.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

void *
IOSCSIPrimaryCommandsDevice::GetApplicationLayerReference (
										SCSITaskIdentifier	request )
{
	
	SCSITask *		scsiRequest;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetApplicationLayerReference ( );
	
}


//�����������������������������������������������������������������������������
// � sGetOwnerForTask - Gets the owner for a task			[STATIC][PROTECTED]
//�����������������������������������������������������������������������������

OSObject *
IOSCSIPrimaryCommandsDevice::sGetOwnerForTask ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest = NULL;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	check ( scsiRequest );
	
	return scsiRequest->GetTaskOwner ( );
	
}


#if 0
#pragma mark -
#pragma mark � Device Information Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � GetVendorString - Gets the vendor string.						[PROTECTED]
//�����������������������������������������������������������������������������

char *
IOSCSIPrimaryCommandsDevice::GetVendorString ( void )
{
	
	OSString *		vendorString;
	
	vendorString = ( OSString * ) GetProtocolDriver ( )->getProperty (
										kIOPropertySCSIVendorIdentification );
	if ( vendorString != NULL )
	{
		return ( ( char * ) vendorString->getCStringNoCopy ( ) );
	}
	
	else
	{
		return "NULL STRING";
	}
	
}


//�����������������������������������������������������������������������������
// � GetProductString - Gets the product string.					[PROTECTED]
//�����������������������������������������������������������������������������

char *
IOSCSIPrimaryCommandsDevice::GetProductString ( void )
{
	
	OSString *		productString;
	
	productString = ( OSString * ) GetProtocolDriver ( )->getProperty (
										kIOPropertySCSIProductIdentification );
	if ( productString != NULL )
	{
		return ( ( char * ) productString->getCStringNoCopy ( ) );
	}
	
	else
	{
		return "NULL STRING";
	}
	
}


//�����������������������������������������������������������������������������
// � GetRevisionString - Gets the product revision level string.	[PROTECTED]
//�����������������������������������������������������������������������������

char *
IOSCSIPrimaryCommandsDevice::GetRevisionString ( void )
{
	
	OSString *		revisionString;
	
	STATUS_LOG ( ( "%s::%s\n", getName ( ), __FUNCTION__ ) );
	
	revisionString = ( OSString * ) GetProtocolDriver ( )->getProperty (
										kIOPropertySCSIProductRevisionLevel );
	
	if ( revisionString != NULL )
	{
		return ( ( char * ) revisionString->getCStringNoCopy ( ) );
	}
	
	else
	{
		return "NULL STRING";
	}
	
}


//�����������������������������������������������������������������������������
// � GetProtocolCharacteristicsDictionary - Gets the protocol characteristics
//											dictionary.				[PROTECTED]
//�����������������������������������������������������������������������������

OSDictionary *
IOSCSIPrimaryCommandsDevice::GetProtocolCharacteristicsDictionary ( void )
{
	
	return ( OSDictionary * ) GetProtocolDriver ( )->getProperty (
										kIOPropertyProtocolCharacteristicsKey );
	
}


//�����������������������������������������������������������������������������
// � GetDeviceCharacteristicsDictionary - 	Gets the device characteristics
//											dictionary.				[PROTECTED]
//�����������������������������������������������������������������������������

OSDictionary *
IOSCSIPrimaryCommandsDevice::GetDeviceCharacteristicsDictionary ( void )
{
	
	check ( fDeviceCharacteristicsDictionary );
	return fDeviceCharacteristicsDictionary;
	
}


//�����������������������������������������������������������������������������
// � GetANSIVersion - Gets the ANSI version the device claims conformance to.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt8
IOSCSIPrimaryCommandsDevice::GetANSIVersion ( void )
{
	
	return fANSIVersion;
	
}


//�����������������������������������������������������������������������������
// � SetANSIVersion - Sets the ANSI version the device claims conformance to.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::SetANSIVersion ( UInt8 newVersion )
{
	
	fANSIVersion = newVersion;
	
}


//�����������������������������������������������������������������������������
// � GetCMDQUE - Gets the CMDQUE bit from the INQUIRY data.			[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::GetCMDQUE ( void )
{
	
	return fCMDQUE;
	
}


//�����������������������������������������������������������������������������
// � SetCMDQUE - Sets the CMDQUE bit from the INQUIRY data.			[PROTECTED]
//�����������������������������������������������������������������������������

void
IOSCSIPrimaryCommandsDevice::SetCMDQUE ( bool value )
{
	
	fCMDQUE = value;
	
}


//�����������������������������������������������������������������������������
// � GetModeSense - Called to get mode sense data from the device.	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::GetModeSense ( 
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField6Bit 			PAGE_CODE,
						SCSICmdField2Byte 			ALLOCATION_LENGTH,
						bool *						use10ByteModeSense )
{
	
	SCSIServiceResponse			serviceResponse = kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE;
	SCSITaskIdentifier			request			= NULL;
	SCSICmdField1Bit			DBD				= 0;
	IOReturn					status			= kIOReturnNoResources;
	bool						commandOK		= false;
	
	request = GetSCSITask ( );
	require_nonzero ( request, ErrorExit );
	
OUTERLOOP:
		
		
		DBD = 1;	/* Disable block descriptors */
		
		
	INNERLOOP:
		
		
		if ( *use10ByteModeSense )
		{
			
			commandOK = MODE_SENSE_10 ( request,
										dataBuffer,
										0x00,
										DBD,	
										0x00,
										PAGE_CODE,
										ALLOCATION_LENGTH,
										0 );
			
		}
		
		else
		{
			
			commandOK = MODE_SENSE_6 (	request,
										dataBuffer,
										DBD,	
										0x00,
										PAGE_CODE,
										ALLOCATION_LENGTH & 0xFF,
										0 );
			
		}
		
		if ( commandOK )
		{
			
			// The command was successfully built, now send it
			serviceResponse = SendCommand ( request, kThirtySecondTimeoutInMS );
			
		}
		
		if ( ( serviceResponse == kSCSIServiceResponse_TASK_COMPLETE ) &&
			 ( GetTaskStatus ( request ) == kSCSITaskStatus_GOOD ) )
		{
 			
			if ( GetRealizedDataTransferCount ( request ) == GetRequestedDataTransferCount ( request ) )
			{
				
				status = kIOReturnSuccess;
				
			}
			
			else if ( GetRealizedDataTransferCount ( request ) < GetRequestedDataTransferCount ( request ) )
 			{
 				
				status 	= kIOReturnUnderrun;
				
			}
			
			else
			{
				
				status = kIOReturnIOError;
				
			}
			
		}
		
		else
		{
			
			// Something went wrong. Try again with DBD=0
			if ( DBD == 1 )
			{
				
				ERROR_LOG ( ( "Trying again with DBD=0\n" ) );
				
				DBD = 0;
				goto INNERLOOP;
				
			}
			
			ERROR_LOG ( ( "Modes sense returned error\n" ) );
			
		}
		
		if ( status != kIOReturnSuccess )
		{
			
			// Something went wrong. Try again with use10Byte = false
			if ( *use10ByteModeSense )
			{
				
				ERROR_LOG ( ( "Trying again with MODE_SENSE_6 command\n" ) );
				
				*use10ByteModeSense = false;
				goto OUTERLOOP;
				
			}
			
			ERROR_LOG ( ( "Mode sense returned error\n" ) );
			
		}
	
	ReleaseSCSITask ( request );
	
	
ErrorExit:
	
	
	return status;
	
}


#if 0
#pragma mark -
#pragma mark � SCSI Protocol Interface Implementations
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � ExecuteCommand - 	The ExecuteCommand method will take a SCSI Task and
//						transport it across the physical wire(s) to the device.
//																	[PROTECTED]
//�����������������������������������������������������������������������������


void
IOSCSIPrimaryCommandsDevice::ExecuteCommand ( SCSITaskIdentifier request )
{
	GetProtocolDriver ( )->ExecuteCommand ( request );
}


//�����������������������������������������������������������������������������
// � AbortCommand -	The AbortCommand method is replaced by the AbortTask
//					Management function and should no longer be called.
//														  			[PROTECTED]
// [OBSOLETE - DO NOT USE]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::AbortCommand ( SCSITaskIdentifier request )
{
	return GetProtocolDriver ( )->AbortCommand ( request );
}


//�����������������������������������������������������������������������������
// � AbortTask -	The Task Management function to allow the SCSI Application
// 					Layer client to request that a specific task be aborted.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::AbortTask (
								UInt8						theLogicalUnit,
								SCSITaggedTaskIdentifier	theTag )
{
	return GetProtocolDriver ( )->AbortTask ( theLogicalUnit, theTag );
}


//�����������������������������������������������������������������������������
// � AbortTaskSet -	The Task Management function to allow the SCSI Application
//					Layer client to request that a all tasks currently in the
//					task set be aborted.							[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::AbortTaskSet ( UInt8 theLogicalUnit )
{
	return GetProtocolDriver ( )->AbortTaskSet ( theLogicalUnit );
}


//�����������������������������������������������������������������������������
// � ClearACA -	The Task Management function to allow the SCSI Application
//				Layer client to request that an Auto-Contingent Allegiance
//				be cleared.											[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::ClearACA ( UInt8 theLogicalUnit )
{
	return GetProtocolDriver ( )->ClearACA ( theLogicalUnit );
}


//�����������������������������������������������������������������������������
// � ClearTaskSet -	The Task Management function to allow the SCSI Application
//					Layer client to request that the task set be cleared.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse		
IOSCSIPrimaryCommandsDevice::ClearTaskSet ( UInt8 theLogicalUnit )
{
	return GetProtocolDriver ( )->ClearTaskSet ( theLogicalUnit );
}


//�����������������������������������������������������������������������������
// � LogicalUnitReset -	The Task Management function to allow the SCSI Application
//						Layer client to request that the Logical Unit be reset.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::LogicalUnitReset ( UInt8 theLogicalUnit )
{
	return GetProtocolDriver ( )->LogicalUnitReset ( theLogicalUnit );
}


//�����������������������������������������������������������������������������
// � TargetReset -	The Task Management function to allow the SCSI Application
//					Layer client to request that the Target Device be reset.
//																	[PROTECTED]
//�����������������������������������������������������������������������������

SCSIServiceResponse
IOSCSIPrimaryCommandsDevice::TargetReset ( void )
{
	return GetProtocolDriver ( )->TargetReset ( );
}


//�����������������������������������������������������������������������������
// � IsProtocolServiceSupported -	The IsProtocolServiceSupported will return
//									true if the specified feature is supported
//									by the protocol layer. If the service has
//									a value that must be returned, it will be
//									returned in the serviceValue output
//									parameter.						[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::IsProtocolServiceSupported (
										SCSIProtocolFeature		feature,
										void *					serviceValue )
{
	return GetProtocolDriver ( )->IsProtocolServiceSupported ( feature, serviceValue );
}


//�����������������������������������������������������������������������������
// � HandleProtocolServiceFeature -	The HandleProtocolServiceFeature will
//									return true if the specified feature could
//									be done by the protocol layer. If the
//									service has a value that must be sent, it
//									will be sent in the serviceValue input
//									parameter.						[PROTECTED]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::HandleProtocolServiceFeature (
										SCSIProtocolFeature		feature,
										void *					serviceValue )
{
	return GetProtocolDriver ( )->HandleProtocolServiceFeature ( feature, serviceValue );
}


#if 0
#pragma mark -
#pragma mark � Static Methods C->C++ Glue
#pragma mark -
#endif


//�����������������������������������������������������������������������������
// � ServerKeyswitchCallback -	Called when notifications about the server
//								keyswitch are broadcast.	  [STATIC][PRIVATE]
//�����������������������������������������������������������������������������

bool
IOSCSIPrimaryCommandsDevice::ServerKeyswitchCallback (
									void *			target,
									void * 			refCon,
									IOService * 	newDevice )
{
	
	OSBoolean *						keySwitchLocked	= NULL;
	IOSCSIPrimaryCommandsDevice *	device			= NULL;
	
	device = OSDynamicCast ( IOSCSIPrimaryCommandsDevice, ( OSObject * ) target );
	
	keySwitchLocked = OSDynamicCast (
							OSBoolean,
							newDevice->getProperty ( kKeySwitchProperty ) );
	
	if ( ( keySwitchLocked != NULL )  &&  ( device != NULL ) )
	{
		
		device->setProperty ( kAppleKeySwitchProperty, keySwitchLocked );
		
	}
	
	return true;
	
}


//�����������������������������������������������������������������������������
// � sWaitForTask -	Called to wait for a task until it completes.
//															  [STATIC][PRIVATE]
//�����������������������������������������������������������������������������

IOReturn
IOSCSIPrimaryCommandsDevice::sWaitForTask (
									void * 				object,
									SCSITaskIdentifier 	request )
{
	
	IOSCSIPrimaryCommandsDevice *	device = NULL;
	
	device = OSDynamicCast ( IOSCSIPrimaryCommandsDevice, ( OSObject * ) object );
	
	return device->GatedWaitForTask ( request );
	
}




#if 0
#pragma mark -
#pragma mark � VTable Padding
#pragma mark -
#endif


// Space reserved for future expansion.
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  1 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  2 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  3 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  4 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  5 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  6 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  7 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  8 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice,  9 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 10 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 11 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 12 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 13 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 14 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 15 );
OSMetaClassDefineReservedUnused ( IOSCSIPrimaryCommandsDevice, 16 );
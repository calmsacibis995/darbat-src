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
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Includes
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

// Libkern includes
#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSNumber.h>
#include <libkern/c++/OSString.h>

// Storage Family includes
#include <IOKit/storage/IOStorageProtocolCharacteristics.h>

// SCSI Architecture Model Family includes
#include "SCSITargetDevicePathManager.h"
#include "SCSITaskDefinition.h"


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Macros
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

#define DEBUG 												0
#define DEBUG_ASSERT_COMPONENT_NAME_STRING					"SCSITargetDevicePathManager"

#if DEBUG
#define SCSI_PATH_MANAGER_DEBUGGING_LEVEL					0
#endif


#include "IOSCSIArchitectureModelFamilyDebugging.h"


#if ( SCSI_PATH_MANAGER_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)		IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( SCSI_PATH_MANAGER_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)		IOLog x
#else
#define ERROR_LOG(x)
#endif

#if ( SCSI_PATH_MANAGER_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)		IOLog x; IOSleep(1)
#else
#define STATUS_LOG(x)
#endif

#define super OSObject
OSDefineMetaClassAndStructors ( SCSITargetDevicePath, OSObject );


#define kIOPropertyBytesTransmittedKey		"Bytes Transmitted"
#define kIOPropertyBytesReceivedKey			"Bytes Received"
#define kIOPropertyCommandsProcessedKey		"Commands Processed"


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Create - Create the path object.						   [PUBLIC][STATIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

SCSITargetDevicePath *
SCSITargetDevicePath::Create ( SCSITargetDevicePathManager *	manager,
							   IOSCSIProtocolServices * 		initialPath )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	STATUS_LOG ( ( "SCSITargetDevicePath::Create\n" ) );
	
	path = OSTypeAlloc ( SCSITargetDevicePath );
	require_nonzero ( path, ErrorExit );
	
	require ( path->InitWithObjects ( manager, initialPath ), ReleasePath );
	
	return path;
	
	
ReleasePath:
	
	
	require_nonzero_quiet ( path, ErrorExit );
	path->release ( );
	path = NULL;
	
	
ErrorExit:
	
	
	return path;		
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Create - Create the path object.						   [PUBLIC][STATIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
SCSITargetDevicePath::InitWithObjects (
						SCSITargetDevicePathManager *	manager,
						IOSCSIProtocolServices * 		interface )
{
	
	OSNumber *										number		= NULL;
	OSString *										string		= NULL;
	UInt32											domainID	= 0;
	bool											result 		= false;
	
	STATUS_LOG ( ( "SCSITargetDevicePath::InitWithObjects\n" ) );
	
	super::init ( );
	
	fInterface 		= interface;
	fPathManager	= manager;
	
	fStatistics = OSDictionary::withCapacity ( 4 );
	require_nonzero ( fStatistics, ErrorExit );
	
	fDomainIdentifier = GetInterfaceDomainIdentifier ( interface );
	require_nonzero ( fDomainIdentifier, ReleaseStatistics );
	domainID = fDomainIdentifier->unsigned32BitValue ( );
	fDomainIdentifier = OSNumber::withNumber ( domainID, 32 );
	fStatistics->setObject ( kIOPropertySCSIDomainIdentifierKey, fDomainIdentifier );
	
	number = OSNumber::withNumber ( ( UInt64 ) 0, 64 );
	require_nonzero ( number, ReleaseStatistics );
	fBytesTransmitted = number;
	fStatistics->setObject ( kIOPropertyBytesTransmittedKey, number );
	
	number = OSNumber::withNumber ( ( UInt64 ) 0, 64 );
	require_nonzero ( number, ReleaseStatistics );
	fBytesReceived = number;
	fStatistics->setObject ( kIOPropertyBytesReceivedKey, number );
	
	number = OSNumber::withNumber ( ( UInt64 ) 0, 64 );
	require_nonzero ( number, ReleaseStatistics );
	fCommandsProcessed = number;
	fStatistics->setObject ( kIOPropertyCommandsProcessedKey, number );
	
	fStatus = kIOPropertyPortStatusLinkEstablishedKey;
	string = OSString::withCStringNoCopy ( fStatus );
	require_nonzero ( string, ReleaseStatistics );
	fPathStatus = string;
	fStatistics->setObject ( kIOPropertyPortStatusKey, string );
	
	STATUS_LOG ( ( "stats has %ld entries\n", fStatistics->getCount ( ) ) );
	
	result = true;
	
	return result;
	
	
ReleaseStatistics:
	
	
	require_nonzero_quiet ( fStatistics, ErrorExit );
	fStatistics->release ( );
	fStatistics = NULL;
	
	
ErrorExit:
	
	
	return result;	
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	GetInterfaceDomainIdentifier - Gets Domain ID.			   [PUBLIC][STATIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

OSNumber *
SCSITargetDevicePath::GetInterfaceDomainIdentifier (
					 const IOSCSIProtocolServices * interface )
{
	
	OSDictionary *	dict	= NULL;
	OSNumber *		number	= NULL;
	OSObject *		obj		= NULL;
	
	obj = interface->getProperty ( kIOPropertyProtocolCharacteristicsKey, gIOServicePlane );
	
	dict = OSDynamicCast ( OSDictionary, obj );
	require_nonzero ( dict, ErrorExit );
	
	obj = dict->getObject ( kIOPropertySCSIDomainIdentifierKey );
	number = OSDynamicCast ( OSNumber, obj );
	require_nonzero ( number, ErrorExit );
	
	
ErrorExit:
	
	
	return number;	
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Activate - Changes path status.									   [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePath::Activate ( void )
{
	
	fStatus = kIOPropertyPortStatusLinkEstablishedKey;
	fPathStatus->initWithCStringNoCopy ( fStatus );
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Inactivate - Changes path status.								   [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePath::Inactivate ( void )
{
	
	fStatus = kIOPropertyPortStatusNoLinkEstablishedKey;
	fPathStatus->initWithCStringNoCopy ( fStatus );
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	free - Called to free resources.								   [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePath::free ( void )
{
	
	STATUS_LOG ( ( "+SCSITargetDevicePath::free\n" ) );
	
	if ( fStatistics != NULL )
	{
		
		fStatistics->release ( );
		fStatistics = NULL;
		
	}
	
	if ( fDomainIdentifier != NULL )
	{
		
		fDomainIdentifier->release ( );
		fDomainIdentifier = NULL;
		
	}
	
	if ( fBytesTransmitted != NULL )
	{
		
		fBytesTransmitted->release ( );
		fBytesTransmitted = NULL;
		
	}

	if ( fBytesReceived != NULL )
	{
		
		fBytesReceived->release ( );
		fBytesReceived = NULL;
		
	}

	if ( fCommandsProcessed != NULL )
	{
		
		fCommandsProcessed->release ( );
		fCommandsProcessed = NULL;
		
	}
	
	if ( fPathStatus != NULL )
	{
		
		fPathStatus->release ( );
		fPathStatus = NULL;
		
	}
	
	super::free ( );
	
	STATUS_LOG ( ( "-SCSITargetDevicePath::free\n" ) );
	
}


#undef super
#define super OSObject
OSDefineMetaClass ( SCSITargetDevicePathManager, OSObject );
OSDefineAbstractStructors ( SCSITargetDevicePathManager, OSObject );


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	InitializePathManagerForTarget - Initializes the path manager.  [PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
SCSITargetDevicePathManager::InitializePathManagerForTarget (
									IOSCSITargetDevice * 		target,
									IOSCSIProtocolServices * 	initialPath )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSITargetDevicePathManager::InitializePathManagerForTarget\n" ) );
	
	super::init ( );
	
	fStatistics = OSArray::withCapacity ( 1 );
	require_nonzero ( fStatistics, ErrorExit );
	
	fTarget = target;	
	result 	= true;
	
	return result;
	
	
ReleaseStats:
	
	
	require_nonzero_quiet ( fStatistics, ReleaseStats );
	fStatistics->release ( );
	fStatistics = NULL;
	
	
ErrorExit:
	
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ PathTaskCallback - C-C++ Glue code.					   [PUBLIC][STATIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePathManager::PathTaskCallback ( SCSITaskIdentifier request )
{
	
	SCSITargetDevicePath *			path 	= NULL;
	SCSITargetDevicePathManager *	manager	= NULL;
	IOSCSITargetDevice *			target	= NULL;
	
	STATUS_LOG ( ( "SCSITargetDevicePathManager::PathTaskCallback\n" ) );
	
	path = ( SCSITargetDevicePath * ) GetPathLayerReference ( request );
	require_nonzero_quiet ( path, ErrorExit );
	
	manager = path->GetPathManager ( );
	require_nonzero ( manager, ErrorExit );
	
	// Call path manager hook for task completion.
	manager->TaskCompletion ( request, path );
	
	
ErrorExit:
	
	
	target = ( IOSCSITargetDevice * ) IOSCSITargetDevice::GetTargetLayerReference ( request );
	target->TargetTaskCompletion ( request );
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ TaskCompletion - Called to complete a task.					[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePathManager::TaskCompletion ( SCSITaskIdentifier 		request,
											  SCSITargetDevicePath *	path )
{
	
	UInt64					bytes	= 0;
	IOSCSITargetDevice *	target	= NULL;
	
	STATUS_LOG ( ( "SCSITargetDevicePathManager::TaskCompletion\n" ) );
	
	target = ( IOSCSITargetDevice * ) IOSCSITargetDevice::GetTargetLayerReference ( request );
	
	if ( IsTransmit ( request, target, &bytes ) == true )
	{
		
		STATUS_LOG ( ( "path->AddBytesTransmitted\n" ) );
		path->AddBytesTransmitted ( bytes );
		
	}
	
	else if ( IsReceive ( request, target, &bytes ) == true )
	{
		
		STATUS_LOG ( ( "path->AddBytesReceived\n" ) );
		path->AddBytesReceived ( bytes );
		
	}
	
	STATUS_LOG ( ( "path->IncrementCommandsProcessed\n" ) );
	path->IncrementCommandsProcessed ( );
	
}



//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ IsTransmit -  Figures out if packet was transmission from host and if so,
//					how many bytes were transmitted.				[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
SCSITargetDevicePathManager::IsTransmit ( SCSITaskIdentifier 	request,
										  IOSCSITargetDevice * 	target,
										  UInt64 * 				bytes )
{
	
	bool	result = false;
	
	if ( target->GetDataTransferDirection ( request ) == kSCSIDataTransfer_FromInitiatorToTarget )
	{
		
		result = true;
		*bytes = target->GetRealizedDataTransferCount ( request );
		
	}
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ IsReceive -  Figures out if packet was received from device and if so,
//				   how many bytes were transmitted.					[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
SCSITargetDevicePathManager::IsReceive ( SCSITaskIdentifier 	request,
										 IOSCSITargetDevice * 	target,
										 UInt64 *				bytes )
{
	
	bool	result = false;
	
	if ( target->GetDataTransferDirection ( request ) == kSCSIDataTransfer_FromTargetToInitiator )
	{
		
		result = true;
		*bytes = target->GetRealizedDataTransferCount ( request );
		
	}
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ SetPathLayerReference -  Sets path layer reference value.		[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
SCSITargetDevicePathManager::SetPathLayerReference (
							SCSITaskIdentifier	request,
							void *				newReference )
{
	
	SCSITask *	scsiRequest = NULL;
	bool		result		= NULL;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	if ( scsiRequest != NULL )
	{
		result = scsiRequest->SetPathLayerReference ( newReference );
	}
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ GetPathLayerReference -  Gets path layer reference value.		[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void *
SCSITargetDevicePathManager::GetPathLayerReference ( SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest = NULL;
	void *		result		= NULL;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	if ( scsiRequest != NULL )
	{
		result = scsiRequest->GetPathLayerReference ( );
	}
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ GetRequestedDataTransferCount -  Gets data xfer count.		[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

UInt64
SCSITargetDevicePathManager::GetRequestedDataTransferCount (
										SCSITaskIdentifier request )
{
	
	SCSITask *	scsiRequest = NULL;
	UInt64		result		= NULL;
	
	scsiRequest = OSDynamicCast ( SCSITask, request );
	if ( scsiRequest != NULL )
	{
		result = scsiRequest->GetRequestedDataTransferCount ( );
	}
	
	return result;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ free -  Called to free all resources.							[PROTECTED]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
SCSITargetDevicePathManager::free ( void )
{
	
	STATUS_LOG ( ( "+SCSITargetDevicePathManager::free\n" ) );
	
	if ( fStatistics != NULL )
	{
		
		fStatistics->release ( );
		fStatistics = NULL;
		
	}
	
	super::free ( );
	
	STATUS_LOG ( ( "-SCSITargetDevicePathManager::free\n" ) );
	
}
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


//�����������������������������������������������������������������������������
//	Includes
//�����������������������������������������������������������������������������

// Libkern includes
#include <libkern/c++/OSArray.h>
#include <libkern/c++/OSNumber.h>

// IOKit includes
#include <IOKit/IOLocks.h>

// SCSI Architecture Model Family includes
#include "SCSIPathManagers.h"


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define DEBUG 												0
#define DEBUG_ASSERT_COMPONENT_NAME_STRING					"SCSIPathManagers"

#if DEBUG
#define SCSI_PATH_MANAGERS_DEBUGGING_LEVEL					0
#endif


#include "IOSCSIArchitectureModelFamilyDebugging.h"


#if ( SCSI_PATH_MANAGERS_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)		IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( SCSI_PATH_MANAGERS_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)		IOLog x; IOSleep(1)
#else
#define ERROR_LOG(x)
#endif

#if ( SCSI_PATH_MANAGERS_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)		IOLog x; IOSleep(1)
#else
#define STATUS_LOG(x)
#endif


#define kIOPropertyPathStatisticsKey		"Path Statistics"

#define kPressurePathTableIncrement			16


#if DEBUG_STATS
static thread_call_t	gThread;
#endif	/* DEBUG_STATS */

static SCSIPressurePathManager::PortBandwidthGlobals gSCSIPortBandwidth;


#if 0
#pragma mark � SCSIPathSet implementation
#pragma mark -
#endif


#define super OSArray
OSDefineMetaClassAndStructors ( SCSIPathSet, OSArray );


//�����������������������������������������������������������������������������
//	withCapacity - Allocates a set with desired capacity.			[PROTECTED]
//�����������������������������������������������������������������������������

SCSIPathSet *
SCSIPathSet::withCapacity ( unsigned int capacity )
{
	
	SCSIPathSet *	set 	= NULL;
	bool			result	= false;
	
	STATUS_LOG ( ( "+SCSIPathSet::withCapacity\n" ) );
	
	set = OSTypeAlloc ( SCSIPathSet );
	require_nonzero ( set, ErrorExit );
	
	result = set->initWithCapacity ( capacity );
	require ( result, ReleaseSet );
	
	return set;
	
	
ReleaseSet:
	
	
	require_nonzero_quiet ( set, ErrorExit );
	set->release ( );
	set = NULL;
	
	
ErrorExit:
	
	
	return set;
	
}


//�����������������������������������������������������������������������������
//	setObject - Adds object to set.									[PROTECTED]
//�����������������������������������������������������������������������������

bool
SCSIPathSet::setObject ( const SCSITargetDevicePath * path )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "+SCSIPathSet::setObject\n" ) );
	
	result = member ( path );
	require ( ( result == false ), ErrorExit );
	
	STATUS_LOG ( ( "calling super::setObject()\n" ) );
	
	result = super::setObject ( path );
	
	STATUS_LOG ( ( "-SCSIPathSet::setObject\n" ) );
	
	return result;
	
	
ErrorExit:
	
	
	result = false;
	
	STATUS_LOG ( ( "-SCSIPathSet::setObject\n" ) );
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	member - Checks if object is a member of set.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
SCSIPathSet::member ( const SCSITargetDevicePath * path ) const
{
	
	bool					result 	= false;
	SCSITargetDevicePath *	element	= NULL;
	UInt32					index	= 0;
	
	STATUS_LOG ( ( "+SCSIPathSet::member\n" ) );
	for ( index = 0; index < count; index++ )
	{
		
		element = ( SCSITargetDevicePath * ) array[index];
		if ( element->GetDomainIdentifier ( )->isEqualTo ( path->GetDomainIdentifier ( ) ) )
		{
			
			STATUS_LOG ( ( "path is member\n" ) );
			result = true;
			break;
			
		}
		
	}
	
	STATUS_LOG ( ( "-SCSIPathSet::member\n" ) );
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	member - Checks if object is a member of set.					[PROTECTED]
//�����������������������������������������������������������������������������

bool
SCSIPathSet::member ( const IOSCSIProtocolServices * interface ) const
{
	
	bool					result 		= false;
	OSNumber *				domainID	= NULL;
	SCSITargetDevicePath *	element		= NULL;
	UInt32					index		= 0;
	
	STATUS_LOG ( ( "+SCSIPathSet::member\n" ) );
	
	domainID = SCSITargetDevicePath::GetInterfaceDomainIdentifier ( interface );
	
	for ( index = 0; index < count; index++ )
	{
		
		element = ( SCSITargetDevicePath * ) array[index];
		if ( element->GetDomainIdentifier ( )->isEqualTo ( domainID ) )
		{
			
			STATUS_LOG ( ( "path is member\n" ) );
			result = true;
			break;
			
		}
		
	}
	
	STATUS_LOG ( ( "-SCSIPathSet::member\n" ) );
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	removeObject - Removes object from set.							[PROTECTED]
//�����������������������������������������������������������������������������

void
SCSIPathSet::removeObject ( const IOSCSIProtocolServices * interface )
{
	
	SCSITargetDevicePath *	member		= NULL;
	OSNumber *				domainID	= NULL;
	UInt32					index		= 0;
	
	STATUS_LOG ( ( "+SCSIPathSet::removeObject\n" ) );
	
	domainID = SCSITargetDevicePath::GetInterfaceDomainIdentifier ( interface );
	
	for ( index = 0; index < count; index++ )
	{
		
		member = ( SCSITargetDevicePath * ) array[index];
		if ( member->GetDomainIdentifier ( )->isEqualTo ( domainID ) )
		{
			
			super::removeObject ( index );
			break;
			
		}
		
	}
	
	STATUS_LOG ( ( "-SCSIPathSet::removeObject\n" ) );
	
}


//�����������������������������������������������������������������������������
//	getAnyObject - Gets any available object in the set.			[PROTECTED]
//�����������������������������������������������������������������������������

SCSITargetDevicePath *
SCSIPathSet::getAnyObject ( void ) const
{
	return ( SCSITargetDevicePath * ) super::getObject ( 0 );
}


//�����������������������������������������������������������������������������
//	getObject - Gets any available object in the set.				[PROTECTED]
//�����������������������������������������������������������������������������

SCSITargetDevicePath *
SCSIPathSet::getObject ( unsigned int index ) const
{
	return ( SCSITargetDevicePath * ) super::getObject ( index );
}


//�����������������������������������������������������������������������������
//	getObjectWithInterface - Gets object with an interface equal to
//							 the interface.							[PROTECTED]
//�����������������������������������������������������������������������������

SCSITargetDevicePath *
SCSIPathSet::getObjectWithInterface ( const IOSCSIProtocolServices * interface ) const
{
	
	SCSITargetDevicePath *	element		= NULL;
	SCSITargetDevicePath *	result		= NULL;
	OSNumber *				domainID	= NULL;
	UInt32					index		= 0;
	
	STATUS_LOG ( ( "+SCSIPathSet::getObjectWithInterface\n" ) );
	
	domainID = SCSITargetDevicePath::GetInterfaceDomainIdentifier ( interface );
	
	for ( index = 0; index < count; index++ )
	{
		
		element = ( SCSITargetDevicePath * ) array[index];
		if ( element->GetDomainIdentifier ( )->isEqualTo ( domainID ) )
		{
			
			result = element;
			break;
			
		}
		
	}
	
	return result;
	
}


#if 0
#pragma mark -
#pragma mark � Pressure Path Manager
#pragma mark -
#endif


#undef super
#define super SCSITargetDevicePathManager
OSDefineMetaClassAndStructors ( SCSIPressurePathManager, SCSITargetDevicePathManager );


//�����������������������������������������������������������������������������
//	free - Frees any resources allocated.							[PROTECTED]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::free ( void )
{
	
	STATUS_LOG ( ( "SCSIPressurePathManager::free\n" ) );
	
	if ( fPathSet != NULL )
	{
		
		fPathSet->release ( );
		fPathSet = NULL;
		
	}
	
	if ( fInactivePathSet != NULL )
	{
		
		fInactivePathSet->release ( );
		fInactivePathSet = NULL;
		
	}
	
	if ( fLock != NULL )
	{
		
		IOLockFree ( fLock );
		fLock = NULL;
		
	}
	
	super::free ( );
	
}


//�����������������������������������������������������������������������������
//	Create - Static factory method used to create an instance of
//			 SCSIPressurePathManager.						   [PUBLIC][STATIC]
//�����������������������������������������������������������������������������

SCSIPressurePathManager *
SCSIPressurePathManager::Create ( IOSCSITargetDevice *		target,
								  IOSCSIProtocolServices * 	initialPath )
{
	
	SCSIPressurePathManager *	manager = NULL;
	bool						result	= false;
	
	STATUS_LOG ( ( "+SCSIPressurePathManager::Create\n" ) );
	
	manager = OSTypeAlloc ( SCSIPressurePathManager );
	require_nonzero ( manager, ErrorExit );
	
	result = manager->InitializePathManagerForTarget ( target, initialPath );
	require ( result, ReleasePathManager );
	
	STATUS_LOG ( ( "-SCSIPressurePathManager::Create, manager = %p\n", manager ) );
	
	return manager;
	
	
ReleasePathManager:
	
	
	require_nonzero_quiet ( manager, ErrorExit );
	manager->release ( );
	manager = NULL;
	
	
ErrorExit:
	
	
	STATUS_LOG ( ( "-SCSIPressurePathManager::Create, manager = NULL\n" ) );
	
	return manager;	
	
}


//�����������������������������������������������������������������������������
//	InitializePathManagerForTarget - Initializes the path manager.  [PROTECTED]
//�����������������������������������������������������������������������������

bool
SCSIPressurePathManager::InitializePathManagerForTarget (
							IOSCSITargetDevice * 		target,
							IOSCSIProtocolServices * 	initialPath )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIPressurePathManager::InitializePathManagerForTarget\n" ) );
	
	result = super::InitializePathManagerForTarget ( target, initialPath );
	require ( result, ErrorExit );
	
	STATUS_LOG ( ( "called super\n" ) );
	
	fLock = IOLockAlloc ( );
	require_nonzero ( fLock, ErrorExit );
	
	STATUS_LOG ( ( "allocated lock\n" ) );
	
	fPathSet = SCSIPathSet::withCapacity ( 1 );
	require_nonzero ( fPathSet, FreeLock );
	
	fInactivePathSet = SCSIPathSet::withCapacity ( 1 );
	require_nonzero ( fInactivePathSet, ReleasePathSet );
	
	STATUS_LOG ( ( "allocated path set, adding intial path\n" ) );
	
	result = AddPath ( initialPath );
	require ( result, ReleaseInactivePathSet );
	
	STATUS_LOG ( ( "added intial path, ready to go\n" ) );
	STATUS_LOG ( ( "Called AddPath, fStatistics array has %ld members\n", fStatistics->getCount ( ) ) );
	target->setProperty ( kIOPropertyPathStatisticsKey, fStatistics );	
	
	result = true;
	
	return result;
	
	
ReleaseInactivePathSet:
	
	
	require_nonzero_quiet ( fInactivePathSet, ReleasePathSet );
	fInactivePathSet->release ( );
	fInactivePathSet = NULL;
	
	
ReleasePathSet:
	
	
	require_nonzero_quiet ( fPathSet, FreeLock );
	fPathSet->release ( );
	fPathSet = NULL;
	
	
FreeLock:
	
	
	require_nonzero_quiet ( fLock, ErrorExit );
	IOLockFree ( fLock );
	fLock = NULL;
	
	
ErrorExit:
	
	
	result = false;
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	AddPath - Adds a path to the path manager.						   [PUBLIC]
//�����������������������������������������������������������������������������

bool
SCSIPressurePathManager::AddPath ( IOSCSIProtocolServices * interface )
{
	
	bool							result 	= false;
	SCSITargetDevicePath *			path	= NULL;
	OSDictionary *					dict	= NULL;
	PortBandwidthGlobals *			bw		= NULL;
	
	STATUS_LOG ( ( "SCSIPressurePathManager::AddPath\n" ) );
	
	require_nonzero ( interface, ErrorExit );
	
	path = SCSITargetDevicePath::Create ( this, interface );
	require_nonzero ( path, ErrorExit );
	
	bw = PortBandwidthGlobals::GetSharedInstance ( );
	bw->AddSCSIPort ( path->GetDomainIdentifier ( )->unsigned32BitValue ( ) );
	
	STATUS_LOG ( ( "Registering callback handler\n" ) );
	
	interface->RegisterSCSITaskCompletionRoutine ( &SCSITargetDevicePathManager::PathTaskCallback );
	
	dict = path->GetStatistics ( );
	
	STATUS_LOG ( ( "Got path stats, count = %ld\n", dict->getCount ( ) ) );
	
	fStatistics->setObject ( dict );
	
	STATUS_LOG ( ( "fStatistics array has %ld members\n", fStatistics->getCount ( ) ) );
	
	IOLockLock ( fLock );
	result = fPathSet->setObject ( path );
	IOLockUnlock ( fLock );
	
	path->release ( );
	path = NULL;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	ActivatePath - Activates a path (if its currently inactive).	   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::ActivatePath ( IOSCSIProtocolServices * interface )
{
	
	bool					result 	= false;
	SCSITargetDevicePath *	path	= NULL;
	
	STATUS_LOG ( ( "SCSIPressurePathManager::ActivatePath\n" ) );
	
	require_nonzero ( interface, ErrorExit );
	
	IOLockLock ( fLock );
	
	result = fInactivePathSet->member ( interface );
	if ( result == true )
	{
		
		path = fInactivePathSet->getObjectWithInterface ( interface );
		if ( path != NULL )
		{
			
			path->retain ( );
			path->Activate ( );
			fInactivePathSet->removeObject ( interface );
			fPathSet->setObject ( path );
			path->release ( );
			path = NULL;
			
		}
		
	}
	
	else
	{
		
		result = fPathSet->member ( interface );
		if ( result == false )
		{
			
			IOLockUnlock ( fLock );
			AddPath ( interface );
			goto Exit;
			
		}
		
	}
	
	IOLockUnlock ( fLock );
	
	
ErrorExit:
Exit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	InactivatePath - Moves path to inactive list.					   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::InactivatePath ( IOSCSIProtocolServices * interface )
{
	
	bool					result 	= false;
	SCSITargetDevicePath *	path	= NULL;
	
	STATUS_LOG ( ( "SCSIPressurePathManager::InactivatePath\n" ) );
	
	require_nonzero ( interface, ErrorExit );
	
	IOLockLock ( fLock );
	
	result = fPathSet->member ( interface );
	if ( result == true )
	{
		
		path = fPathSet->getObjectWithInterface ( interface );
		if ( path != NULL )
		{
			
			path->retain ( );
			path->Inactivate ( );
			fPathSet->removeObject ( interface );
			fInactivePathSet->setObject ( path );
			path->release ( );
			path = NULL;
			
		}
		
	}
	
	IOLockUnlock ( fLock );
	
	
ErrorExit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	RemovePath - Removes a path from the path manager.				   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::RemovePath ( IOSCSIProtocolServices * path )
{
	
	STATUS_LOG ( ( "SCSIPressurePathManager::RemovePath\n" ) );
	
	if ( path != NULL )
	{
		
		IOLockLock ( fLock );
		
		// First check if it's on the inactive list (it should since the
		// notification should come before termination).
		
		if ( fInactivePathSet->member ( path ) == true )
		{
			
			SCSITargetDevicePath *			tdp = NULL;
			
			tdp = fInactivePathSet->getObjectWithInterface ( path );
			if ( tdp != NULL )
			{
				
				OSDictionary *	dict = NULL;
				
				dict = tdp->GetStatistics ( );
				
				if ( dict != NULL )
				{
					
					UInt32	count = fStatistics->getCount ( );
					UInt32	index = 0;
					
					for ( index = 0; index < count; index++ )
					{
						
						if ( fStatistics->getObject ( index ) == dict )
						{
							fStatistics->removeObject ( index );
						}
						
					}
					
				}
				
			}

			STATUS_LOG ( ( "Removing path from inactive path set\n" ) );
			fInactivePathSet->removeObject ( path );
			
		}
		
		else
		{
			
			SCSITargetDevicePath *	tdp = NULL;
			
			tdp = fPathSet->getObjectWithInterface ( path );
			if ( tdp != NULL )
			{
				
				OSDictionary *	dict = NULL;
				
				dict = tdp->GetStatistics ( );
				
				if ( dict != NULL )
				{
					
					UInt32	count = fStatistics->getCount ( );
					UInt32	index = 0;
					
					for ( index = 0; index < count; index++ )
					{
						
						if ( fStatistics->getObject ( index ) == dict )
						{
							fStatistics->removeObject ( index );
						}
						
					}
					
				}
				
			}
			
			ERROR_LOG ( ( "Removing path from active path set, no notification came!!!\n" ) );
			fPathSet->removeObject ( path );
			
		}
		
		IOLockUnlock ( fLock );
		
	}
	
}


//�����������������������������������������������������������������������������
//	PathStatusChanged - Notification for when a path status changes.   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PathStatusChanged (
							IOSCSIProtocolServices * 	path,
							UInt32						newStatus )
{
	
	STATUS_LOG ( ( "SCSIPressurePathManager::PathStatusChanged\n" ) );
	
	switch ( newStatus )
	{
		
		case kSCSIPort_StatusOnline:
		{
			
			STATUS_LOG ( ( "kSPIPortStatus_Online\n" ) );
			ActivatePath ( path );
			
		}
		break;
		
		case kSCSIPort_StatusOffline:
		case kSCSIPort_StatusFailure:
		{
			
			STATUS_LOG ( ( "kSPIPortStatus_Offline or kSPIPortStatus_Failure\n" ) );
			InactivatePath ( path );
			
		}
		break;
		
		default:
		{
			STATUS_LOG ( ( "Unknown port status\n" ) );
		}
		break;
		
	}
	
}


//�����������������������������������������������������������������������������
//	ExecuteCommand - Called to execute a SCSITask. 					   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::ExecuteCommand ( SCSITaskIdentifier request )
{
	
	SCSITargetDevicePath *		path		= NULL;
	PortBandwidthGlobals *		bw			= NULL;
	UInt32						numPaths	= 0;
	
	IOLockLock ( fLock );
	
	numPaths = fPathSet->getCount ( );
	
	if ( numPaths == 0 )
	{
		
		IOLockUnlock ( fLock );
		PathTaskCallback ( request );
		return;
		
	}
	
	bw = PortBandwidthGlobals::GetSharedInstance ( );
	path = bw->AllocateBandwidth ( fPathSet, GetRequestedDataTransferCount ( request ) );
	
	IOLockUnlock ( fLock );
	
	SetPathLayerReference ( request, ( void * ) path );
	path->GetInterface ( )->ExecuteCommand ( request );
	
}


//�����������������������������������������������������������������������������
//	TaskCompletion - Called to complete task. 						   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::TaskCompletion ( SCSITaskIdentifier 		request,
										  SCSITargetDevicePath * 	path )
{
	
	PortBandwidthGlobals *	bw = NULL;
	
	bw = PortBandwidthGlobals::GetSharedInstance ( );
	bw->DeallocateBandwidth ( path, GetRequestedDataTransferCount ( request ) );
	
	super::TaskCompletion ( request, path );
	
}



//�����������������������������������������������������������������������������
//	AbortTask - Called to abort a SCSITask. 						   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::AbortTask ( SCSILogicalUnitNumber 		theLogicalUnit,
									 SCSITaggedTaskIdentifier 	theTag )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->AbortTask ( theLogicalUnit, theTag );
	
}


//�����������������������������������������������������������������������������
//	AbortTaskSet - Called to abort a task set. 						   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::AbortTaskSet ( SCSILogicalUnitNumber theLogicalUnit )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->AbortTaskSet ( theLogicalUnit );
	
}


//�����������������������������������������������������������������������������
//	ClearACA - Called to clear an ACA condition. 					   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::ClearACA ( SCSILogicalUnitNumber theLogicalUnit )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->ClearACA ( theLogicalUnit );
	
}


//�����������������������������������������������������������������������������
//	ClearTaskSet - Called to clear a task set. 						   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::ClearTaskSet ( SCSILogicalUnitNumber theLogicalUnit )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->ClearTaskSet ( theLogicalUnit );
	
}


//�����������������������������������������������������������������������������
//	LogicalUnitReset - Called to reset a logical unit. 				   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::LogicalUnitReset ( SCSILogicalUnitNumber theLogicalUnit )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->LogicalUnitReset ( theLogicalUnit );
	
}


//�����������������������������������������������������������������������������
//	TargetReset - Called to reset a target device. 					   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIServiceResponse
SCSIPressurePathManager::TargetReset ( void )
{
	
	SCSITargetDevicePath *	path = NULL;
	
	IOLockLock ( fLock );
	path = fPathSet->getAnyObject ( );
	IOLockUnlock ( fLock );
	
	if ( path == NULL )
		return kSCSIServiceResponse_FUNCTION_REJECTED;
	
	return path->GetInterface ( )->TargetReset ( );
	
}


#pragma mark -
#pragma mark � SCSI Port Bandwidth Globals
#pragma mark -


//�����������������������������������������������������������������������������
//	GetSharedInstance - Gets global bandwidth object.				   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIPressurePathManager::PortBandwidthGlobals *
SCSIPressurePathManager::PortBandwidthGlobals::GetSharedInstance ( void )
{
	return &gSCSIPortBandwidth;
}


//�����������������������������������������������������������������������������
//	Constructor														   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIPressurePathManager::PortBandwidthGlobals::PortBandwidthGlobals ( void )
{
	
	fPathsAllocated	= 0;
	fLock			= IOLockAlloc ( );
	
	// Allocate enough space for kPressurePathTableIncrement ports for now.
	// We can grow the table if we have to...
	fCapacity = sizeof ( UInt64 ) * kPressurePathTableIncrement;
	
	fListHead = ( UInt64 * ) IOMalloc ( fCapacity );
	bzero ( fListHead, fCapacity );

#if DEBUG_STATS	
	
	gThread = thread_call_allocate ( 
						( thread_call_func_t ) PortBandwidthGlobals::sDumpDebugInfo,
						( thread_call_param_t ) this );
	
	SetTimer ( );
	
#endif	/* DEBUG_STATS */
	
}


//�����������������������������������������������������������������������������
//	Destructor														   [PUBLIC]
//�����������������������������������������������������������������������������

SCSIPressurePathManager::PortBandwidthGlobals::~PortBandwidthGlobals ( void )
{
	
	if ( fLock != NULL )
	{
		
		IOLockFree ( fLock );
		fLock = NULL;
		
	}
	
	IOFree ( fListHead, fCapacity );
	fListHead = NULL;
	fCapacity = 0;
	
}


//�����������������������������������������������������������������������������
//	AllocateBandwidth												   [PUBLIC]
//�����������������������������������������������������������������������������

SCSITargetDevicePath *
SCSIPressurePathManager::PortBandwidthGlobals::AllocateBandwidth (
						SCSIPathSet *	pathSet,
						UInt64			bytes )
{
	
	SCSITargetDevicePath *		path		= NULL;
	SCSITargetDevicePath *		result		= NULL;
	UInt32						numPaths	= 0;
	UInt32						index		= 0;
	UInt32						resultIndex	= 0;
	UInt64						bandwidth	= 0xFFFFFFFFFFFFFFFFULL;
	
	STATUS_LOG ( ( "+PortBandwidthGlobals::AllocateBandwidth\n" ) );
	
	// Grab the lock since we'll end up manipulating the table.
	IOLockLock ( fLock );
	
	// Assume we're using the first path.
	result 		= pathSet->getObject ( index );
	numPaths	= pathSet->getCount ( );
	
	// Loop over the passed in possible paths.
	for ( index = 0; index < numPaths; index++ )
	{
		
		UInt32	domainID = 0;
		
		STATUS_LOG ( ( "Getting a path at index = %ld\n", index ) );
		
		path = pathSet->getObject ( index );
		
		domainID = path->GetDomainIdentifier ( )->unsigned32BitValue ( );
		
		// Sanity check
		//check ( domainID < fCapacity );
		
		if ( fListHead[domainID] < bandwidth )
		{
			
			result 		= path;
			bandwidth 	= fListHead[domainID];
			resultIndex	= domainID;
			
		}
		
	}
	
	// Whichever path we chose, charge it with the bandwidth.
	fListHead[resultIndex] += bytes;
	
	// Done manipulating the table. Drop the lock.
	IOLockUnlock ( fLock );
	
	STATUS_LOG ( ( "-PortBandwidthGlobals::AllocateBandwidth\n" ) );
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	DeallocateBandwidth												   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PortBandwidthGlobals::DeallocateBandwidth (
					SCSITargetDevicePath *	path,
					UInt64					bytes )
{
	
	UInt32	domainID = 0;

	domainID = path->GetDomainIdentifier ( )->unsigned32BitValue ( );
	
	STATUS_LOG ( ( "+PortBandwidthGlobals::DeallocateBandwidth\n" ) );
	
	IOLockLock ( fLock );
	
	// Just decrement the bandwidth charged to this port.
	fListHead[domainID] -= bytes;
	
	IOLockUnlock ( fLock );
	
	STATUS_LOG ( ( "-PortBandwidthGlobals::DeallocateBandwidth\n" ) );
	
}


//�����������������������������������������������������������������������������
//	AddSCSIPort														   [PUBLIC]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PortBandwidthGlobals::AddSCSIPort (
													 UInt32 domainID )
{
	
	STATUS_LOG ( ( "+PortBandwidthGlobals::AddSCSIPort\n" ) );
	
	IOLockLock ( fLock );
	
	// ����Assumption that domainID grows monotonically in increments
	// of 1 starting at domainID of zero.
	if ( domainID >= fCapacity )
	{
		
		UInt32		newCapacity = 0;
		UInt64 *	newHead		= NULL;
		
		// We need to grow the table to hold this new port. Add space
		// for another kPressurePathTableIncrement ports.
		newCapacity = fCapacity + ( sizeof ( UInt64 ) * kPressurePathTableIncrement );
		newHead		= ( UInt64 * ) IOMalloc ( newCapacity );
		
		if ( newHead != NULL )
		{
			
			bcopy ( fListHead, newHead, fCapacity );
			bzero ( &newHead[fCapacity], newCapacity - fCapacity );
			
			IOFree ( fListHead, fCapacity );
			
			fListHead = newHead;
			fCapacity = newCapacity;
			
		}
		
	}
	
	IOLockUnlock ( fLock );
	
}


#pragma mark - 
#pragma mark � Debugging Support
#pragma mark - 


#if DEBUG_STATS


//�����������������������������������������������������������������������������
//	SetTimer														  [PRIVATE]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PortBandwidthGlobals::SetTimer ( void )
{
	
	AbsoluteTime	time;
	
	clock_interval_to_deadline ( 3000, kMillisecondScale, &time );
	thread_call_enter_delayed ( gThread, time );
	
}


//�����������������������������������������������������������������������������
//	sDumpDebugInfo - C->C++ glue									  [PRIVATE]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PortBandwidthGlobals::sDumpDebugInfo (
						thread_call_param_t 	param0,
						thread_call_param_t 	param1 )
{

#pragma unused ( param1 )
	
	PortBandwidthGlobals *	globals = ( PortBandwidthGlobals * ) param0;
	globals->DumpDebugInfo ( );
	
}


//�����������������������������������������������������������������������������
//	DumpDebugInfo - Dumps debug info about ports					  [PRIVATE]
//�����������������������������������������������������������������������������

void
SCSIPressurePathManager::PortBandwidthGlobals::DumpDebugInfo ( void )
{

	UInt32	index = 0;
	
	IOLockLock ( fLock );
	
	IOLog ( "fPathsAllocated = %ld\n", fPathsAllocated );
	IOSleep ( 1 );
	
	for ( index = 0; index < fCapacity; index++ )
	{
		
		IOLog ( "[%ld]: bandwidthAllocated = %lld\n", index, fListHead[index] );
		IOSleep ( 1 );
		
	}
	
	SetTimer ( );
	
	IOLockUnlock ( fLock );
	
}


#endif	/* DEBUG_STATS */
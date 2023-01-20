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
 * Copyright (c) 2001-2002 Apple Computer, Inc. All rights reserved.
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

// Private includes
#include "SCSITaskIUnknown.h"
#include "SCSITaskClass.h"
#include "SCSITaskDeviceClass.h"
#include "MMCDeviceUserClientClass.h"


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define SCSI_TASK_IUNKNOWN_DEBUGGING_LEVEL 0

#if ( SCSI_TASK_IUNKNOWN_DEBUGGING_LEVEL > 0 )
#define PRINT(x)	printf x
#else
#define PRINT(x)
#endif


//�����������������������������������������������������������������������������
//	Static variable initialization
//�����������������������������������������������������������������������������

UInt32	SCSITaskIUnknown::sFactoryRefCount = 0;


#if 0
#pragma mark Methods associated with SCSITaskLib factory
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� SCSITaskLibFactory - Factory method. Exported via plist		[PUBLIC]
//�����������������������������������������������������������������������������

void *
SCSITaskLibFactory ( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	
	PRINT ( ( "SCSITaskLibFactory called\n" ) );
	
	if ( CFEqual ( typeID, kIOSCSITaskDeviceUserClientTypeID ) )
		return ( void * ) SCSITaskDeviceClass::alloc ( );
	
	else if ( CFEqual ( typeID, kIOMMCDeviceUserClientTypeID ) )
		return ( void * ) MMCDeviceUserClientClass::alloc ( );
	
	else
		return NULL;
	
}


//�����������������������������������������������������������������������������
//	� sFactoryAddRef - 	Static method to increment the refcount associated with
//						the CFPlugIn factory
//																	[PUBLIC]
//�����������������������������������������������������������������������������

void
SCSITaskIUnknown::sFactoryAddRef ( void )
{
	
	if ( sFactoryRefCount++ == 0 )
	{
		
		CFUUIDRef	factoryID = kIOSCSITaskLibFactoryID;
		
		CFRetain ( factoryID );
		CFPlugInAddInstanceForFactory ( factoryID );
		
	}
	
}


//�����������������������������������������������������������������������������
//	� sFactoryRelease - Static method to decrement the refcount associated with
//						the CFPlugIn factory and release it when the refcount
//						becomes zero.								[PUBLIC]
//�����������������������������������������������������������������������������

void
SCSITaskIUnknown::sFactoryRelease ( void )
{
	
	if ( sFactoryRefCount-- == 1 )
	{
		
		CFUUIDRef	factoryID = kIOSCSITaskLibFactoryID;
		
		CFPlugInRemoveInstanceForFactory ( factoryID );
		CFRelease ( factoryID );
		
	}
	
	else if ( sFactoryRefCount < 0 )
	{
		sFactoryRefCount = 0;
	}
	
}


#if 0
#pragma mark -
#pragma mark Public Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� Constructor. Called by subclasses.							[PUBLIC]
//�����������������������������������������������������������������������������

SCSITaskIUnknown::SCSITaskIUnknown ( void * unknownVTable ) : fRefCount ( 1 )
{
	
	fInterfaceMap.pseudoVTable 	= ( IUnknownVTbl * ) unknownVTable;
	fInterfaceMap.obj 			= this;
	
	sFactoryAddRef ( );
	
}


//�����������������������������������������������������������������������������
//	� Destructor													[PUBLIC]
//�����������������������������������������������������������������������������

SCSITaskIUnknown::~SCSITaskIUnknown ( void )
{
	sFactoryRelease ( );
}


//�����������������������������������������������������������������������������
//	� AddRef	-	Increments refcount associated with the object.	[PUBLIC]
//�����������������������������������������������������������������������������

UInt32
SCSITaskIUnknown::AddRef ( void )
{
	
	PRINT ( ( "AddRef called\n" ) );
	
	fRefCount += 1;
	
	PRINT ( ( "fRefCount = %ld\n", fRefCount ) );
	
	return fRefCount;
	
}


//�����������������������������������������������������������������������������
//	� Release	-	Decrements refcount associated with the object, freeing it
//					when the refcount is zero.						[PUBLIC]
//�����������������������������������������������������������������������������

UInt32
SCSITaskIUnknown::Release ( void )
{
	
	UInt32 returnValue = fRefCount - 1;
	
	PRINT ( ( "Release called\n" ) );
	PRINT ( ( "fRefCount = %ld\n", fRefCount ) );
	
	if ( returnValue > 0 )
	{
		fRefCount = returnValue;
	}
	
	else if ( returnValue == 0 )
	{
		
		PRINT ( ( "deleting object\n" ) );
		
		fRefCount = returnValue;
		delete this;
		
	}
	
	else
	{
		returnValue = 0;
	}
	
	return returnValue;
	
}


#if 0
#pragma mark -
#pragma mark Static C->C++ Glue Functions
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� sQueryInterface - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

HRESULT
SCSITaskIUnknown::sQueryInterface ( void * self, REFIID iid, void **ppv )
{
	
	SCSITaskIUnknown *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->QueryInterface ( iid, ppv );
	
}


//�����������������������������������������������������������������������������
//	� sAddRef - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt32
SCSITaskIUnknown::sAddRef ( void * self )
{
	
	SCSITaskIUnknown *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->AddRef ( );
	
}


//�����������������������������������������������������������������������������
//	� sRelease - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt32
SCSITaskIUnknown::sRelease ( void * self )
{
	
	SCSITaskIUnknown *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->Release ( );
	
}

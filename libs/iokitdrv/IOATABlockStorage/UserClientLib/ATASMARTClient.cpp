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
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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


//�����������������������������������������������������������������������������
//	Includes
//�����������������������������������������������������������������������������

// Private includes
#include "ATASMARTLib.h"
#include "ATASMARTClient.h"
#include "ATASMARTLibPriv.h"

#include <stdio.h>


//�����������������������������������������������������������������������������
//	Constants
//�����������������������������������������������������������������������������


enum
{
	kATASMARTLogDirectoryEntry	= 0x00
};

enum
{
	kATADefaultSectorSize = 512
};


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define ATA_SMART_DEBUGGING_LEVEL 0

#if ( ATA_SMART_DEBUGGING_LEVEL > 0 )
#define PRINT(x)	printf x
#else
#define PRINT(x)
#endif


//�����������������������������������������������������������������������������
//	Static variable initialization
//�����������������������������������������������������������������������������

UInt32	ATASMARTClient::sFactoryRefCount = 0;


IOCFPlugInInterface
ATASMARTClient::sIOCFPlugInInterface = 
{
	0,
	&ATASMARTClient::sQueryInterface,
	&ATASMARTClient::sAddRef,
	&ATASMARTClient::sRelease,
	1, 0, // version/revision
	&ATASMARTClient::sProbe,
	&ATASMARTClient::sStart,
	&ATASMARTClient::sStop
};

IOATASMARTInterface
ATASMARTClient::sATASMARTInterface =
{
	0,
	&ATASMARTClient::sQueryInterface,
	&ATASMARTClient::sAddRef,
	&ATASMARTClient::sRelease,
	1, 0, // version/revision
	&ATASMARTClient::sSMARTEnableDisableOperations,
	&ATASMARTClient::sSMARTEnableDisableAutosave,
	&ATASMARTClient::sSMARTReturnStatus,
	&ATASMARTClient::sSMARTExecuteOffLineImmediate,
	&ATASMARTClient::sSMARTReadData,
	&ATASMARTClient::sSMARTValidateReadData,
	&ATASMARTClient::sSMARTReadDataThresholds,
	&ATASMARTClient::sSMARTReadLogDirectory,
	&ATASMARTClient::sSMARTReadLogAtAddress,
	&ATASMARTClient::sSMARTWriteLogAtAddress,
	&ATASMARTClient::sGetATAIdentifyData
};


#if 0
#pragma mark -
#pragma mark Methods associated with ATASMARTLib factory
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� ATASMARTLibFactory - Factory method. Exported via plist		[PUBLIC]
//�����������������������������������������������������������������������������

void *
ATASMARTLibFactory ( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	
	PRINT ( ( "ATASMARTLibFactory called\n" ) );
	
	if ( CFEqual ( typeID, kIOATASMARTUserClientTypeID ) )
		return ( void * ) ATASMARTClient::alloc ( );
		
	else
		return NULL;
	
}



//�����������������������������������������������������������������������������
//	� alloc - Used to allocate an instance of ATASMARTClient		[PUBLIC]
//�����������������������������������������������������������������������������

IOCFPlugInInterface **
ATASMARTClient::alloc ( void )
{
	
	ATASMARTClient * 			userClient;
	IOCFPlugInInterface ** 		interface = NULL;
	
	PRINT ( ( "ATASMARTClient::alloc called\n" ) );
	
	userClient = new ATASMARTClient;
	if ( userClient != NULL )
	{
		
		interface = ( IOCFPlugInInterface ** ) &userClient->fCFPlugInInterfaceMap.pseudoVTable;
		
	}
	
	return interface;
	
}


//�����������������������������������������������������������������������������
//	� sFactoryAddRef - 	Static method to increment the refcount associated with
//						the CFPlugIn factory
//																	[PUBLIC]
//�����������������������������������������������������������������������������

void
ATASMARTClient::sFactoryAddRef ( void )
{
	
	if ( sFactoryRefCount++ == 0 )
	{
		
		CFUUIDRef	factoryID = kIOATASMARTLibFactoryID;
		
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
ATASMARTClient::sFactoryRelease ( void )
{
	
	if ( sFactoryRefCount-- == 1 )
	{
		
		CFUUIDRef	factoryID = kIOATASMARTLibFactoryID;
		
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

ATASMARTClient::ATASMARTClient ( void ) : fRefCount ( 1 )
{
	
	fCFPlugInInterfaceMap.pseudoVTable 	= ( IUnknownVTbl * ) &sIOCFPlugInInterface;
	fCFPlugInInterfaceMap.obj 			= this;
	
	fATASMARTInterfaceMap.pseudoVTable	= ( IUnknownVTbl * ) &sATASMARTInterface;
	fATASMARTInterfaceMap.obj			= this;
	
	sFactoryAddRef ( );
	
}


//�����������������������������������������������������������������������������
//	� Destructor													[PUBLIC]
//�����������������������������������������������������������������������������

ATASMARTClient::~ATASMARTClient ( void )
{
	sFactoryRelease ( );
}


#if 0
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� QueryInterface - Called to obtain the presence of an interface
//																	[PROTECTED]
//�����������������������������������������������������������������������������

HRESULT
ATASMARTClient::QueryInterface ( REFIID iid, void ** ppv )
{
	
	CFUUIDRef 	uuid 	= CFUUIDCreateFromUUIDBytes ( NULL, iid );
	HRESULT 	result 	= S_OK;
	
	PRINT ( ( "ATASMARTClient : QueryInterface called\n" ) );
	
	if ( CFEqual ( uuid, IUnknownUUID ) ||
		 CFEqual ( uuid, kIOCFPlugInInterfaceID ) ) 
	{
        
		PRINT ( ( "IUnknownUUID | kIOCFPlugInInterfaceID requested\n" ) );
		
		*ppv = &fCFPlugInInterfaceMap;
        AddRef ( );
		
    }
	
	else if ( CFEqual ( uuid, kIOATASMARTInterfaceID ) ) 
	{
		
		PRINT ( ( "kIOATASMARTInterfaceID requested\n" ) );
		
		*ppv = &fATASMARTInterfaceMap;
        AddRef ( );
		
    }
	
    else
	{
		
		PRINT ( ( "unknown interface requested\n" ) );
		*ppv = 0;
		result = E_NOINTERFACE;
		
	}
	
	CFRelease ( uuid );
	
	return result;
	
}


//�����������������������������������������������������������������������������
//	� AddRef	-	Increments refcount associated with the object.	[PUBLIC]
//�����������������������������������������������������������������������������

UInt32
ATASMARTClient::AddRef ( void )
{
	
	fRefCount += 1;
	return fRefCount;
	
}


//�����������������������������������������������������������������������������
//	� Release	-	Decrements refcount associated with the object, freeing it
//					when the refcount is zero.						[PUBLIC]
//�����������������������������������������������������������������������������

UInt32
ATASMARTClient::Release ( void )
{
	
	UInt32 returnValue = fRefCount - 1;
	
	if ( returnValue > 0 )
	{
		fRefCount = returnValue;
	}
	
	else if ( returnValue == 0 )
	{
		
		fRefCount = returnValue;
		delete this;
		
	}
	
	else
	{
		returnValue = 0;
	}
	
	return returnValue;
	
}


//�����������������������������������������������������������������������������
//	� Probe - 	Called by IOKit to ascertain whether we can drive the provided
//				io_service_t										[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::Probe ( CFDictionaryRef propertyTable,
						io_service_t 	inService,
						SInt32 * 		order )
{
	
	CFMutableDictionaryRef	dict	= 0;
	IOReturn				status 	= kIOReturnBadArgument;
	
	PRINT ( ( "ATASMARTClient::Probe called\n" ) );
	
	// Sanity check
	if ( inService == 0 )
	{
		goto Exit;
	}
	
	status = IORegistryEntryCreateCFProperties ( inService, &dict, NULL, 0 );
	if ( status != kIOReturnSuccess )
	{
		goto Exit;
	}
	
	if ( !CFDictionaryContainsKey ( dict, CFSTR ( "IOCFPlugInTypes" ) ) )
	{
		goto Exit;
	}
	
	
	status = kIOReturnSuccess;
	
	
Exit:
	
	
	if ( dict != 0 )
	{
		
		CFRelease ( dict );
		dict = 0;
		
	}
	
	
	return status;
	
}
	

//�����������������������������������������������������������������������������
//	� Start - Called to start providing our services.				[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::Start ( CFDictionaryRef propertyTable, io_service_t service )
{
	
	IOReturn 	status = kIOReturnSuccess;
	
	PRINT ( ( "ATASMARTClient : Start\n" ) );
	
	fService = service;
	status = IOServiceOpen ( fService,
							 mach_task_self ( ), 
							 kIOATASMARTLibConnection,
							 &fConnection );
	
	if ( !fConnection )
		status = kIOReturnNoDevice;
	
	PRINT ( ( "ATASMARTClient : IOServiceOpen status = 0x%08lx, connection = %d\n",
			( UInt32 ) status, fConnection ) );
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� Stop - Called to stop providing our services.					[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::Stop ( void )
{
	
	PRINT ( ( "ATASMARTClient : Stop\n" ) );
		
	if ( fConnection )
	{
		
		PRINT ( ( "ATASMARTClient : IOServiceClose connection = %d\n", fConnection ) );
        IOServiceClose ( fConnection );
        fConnection = MACH_PORT_NULL;
		
	}
	
	return kIOReturnSuccess;
	
}


#if 0
#pragma mark -
#pragma mark SMART Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� SMARTEnableDisableOperations - Enables/Disables SMART operations
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTEnableDisableOperations ( Boolean enable )
{
	
	IOReturn	status 		= kIOReturnSuccess;
	int			selection 	= ( enable == true ) ? 1 : 0;

	PRINT ( ( "ATASMARTClient::SMARTEnableDisableOperations called\n" ) );
	
	status = IOConnectMethodScalarIScalarO ( fConnection,
											 kIOATASMARTEnableDisableOperations,
											 1,
											 0,
											 &selection );

	PRINT ( ( "ATASMARTClient::SMARTEnableDisableOperations status = %d\n", status ) );		

	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTEnableDisableAutosave - Enables/Disables SMART AutoSave
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTEnableDisableAutosave ( Boolean enable )
{
	
	IOReturn	status 		= kIOReturnSuccess;
	int			selection 	= ( enable == true ) ? 1 : 0;
	
	PRINT ( ( "ATASMARTClient::SMARTEnableDisableAutosave called\n" ) );
	
	status = IOConnectMethodScalarIScalarO ( fConnection,
											 kIOATASMARTEnableDisableAutoSave,
											 1,
											 0,
											 &selection );
	
	PRINT ( ( "ATASMARTClient::SMARTEnableDisableAutosave status = %d\n", status ) );		
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTReturnStatus - Returns SMART status
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTReturnStatus ( Boolean * exceededCondition )
{
	
	IOReturn	status 		= kIOReturnSuccess;
	int			condition 	= 0;
	
	PRINT ( ( "ATASMARTClient::SMARTReturnStatus called\n" ) );
	
	status = IOConnectMethodScalarIScalarO ( fConnection,
											 kIOATASMARTReturnStatus,
											 0,
											 1,
											 &condition );
	
	if ( status == kIOReturnSuccess )
	{
		
		*exceededCondition = ( condition != 0 ) ? true : false;
		PRINT ( ( "exceededCondition = %d\n", condition ) );
		
	}
	
	PRINT ( ( "ATASMARTClient::SMARTReturnStatus status = %d\n", status ) );		
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTExecuteOffLineImmediate - Executes an off-line immediate SMART test
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTExecuteOffLineImmediate ( Boolean extendedTest )
{
	
	IOReturn	status 		= kIOReturnSuccess;
	int			selection 	= ( extendedTest == true ) ? 1 : 0;;
	
	PRINT ( ( "ATASMARTClient::SMARTExecuteOffLineImmediate called\n" ) );
	
	status = IOConnectMethodScalarIScalarO ( fConnection,
											 kIOATASMARTExecuteOffLineImmediate,
											 1,
											 0,
											 &selection );
	
	PRINT ( ( "ATASMARTClient::SMARTExecuteOffLineImmediate status = %d\n", status ) );		
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTReadData - Reads the SMART data
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTReadData ( ATASMARTData * data )
{
	
	IOReturn		status;
	
	PRINT ( ( "ATASMARTClient::SMARTReadData called\n" ) );
	
	status = IOConnectMethodScalarIScalarO (	fConnection, 	
												kIOATASMARTReadData, 
												1,
												0,
												( int * ) data );
	
	PRINT ( ( "ATASMARTClient::SMARTReadData status = %d\n", status ) );		
	
	#if 0
	if ( status == kIOReturnSuccess )
	{
		
		UInt8 *		ptr = ( UInt8 * ) data;
		
		printf ( "ATA SMART DATA\n" );
		
		for ( UInt8	index = 0; ( index < sizeof ( ATASMARTData ) ); index += 8 )
		{
			
			printf ( "0x%02x 0x%02x 0x%02x 0x%02x | 0x%02x 0x%02x 0x%02x 0x%02x\n",
					 ptr[index + 0], ptr[index + 1], ptr[index + 2], ptr[index + 3],
					 ptr[index + 4], ptr[index + 5], ptr[index + 6], ptr[index + 7] );
			
		}
		
	}
	#endif
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTReadDataThresholds - Reads the SMART data thresholds
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTReadDataThresholds ( ATASMARTDataThresholds * data )
{
	
	IOReturn		status;
	
	PRINT ( ( "ATASMARTClient::SMARTReadDataThresholds called\n" ) );
	
	status = IOConnectMethodScalarIScalarO (	fConnection, 	
												kIOATASMARTReadDataThresholds, 
												1,
												0,
												( int * ) data );
	
	PRINT ( ( "ATASMARTClient::SMARTReadDataThresholds status = %d\n", status ) );		
	
	#if 0
	if ( status == kIOReturnSuccess )
	{
		
		UInt8 *		ptr = ( UInt8 * ) data;
		
		printf ( "ATA SMART DATA THRESHOLDS\n" );
		
		for ( UInt8	index = 0; ( index < sizeof ( ATASMARTDataThresholds ) ); index += 8 )
		{
			
			printf ( "0x%02x 0x%02x 0x%02x 0x%02x | 0x%02x 0x%02x 0x%02x 0x%02x\n",
					 ptr[index + 0], ptr[index + 1], ptr[index + 2], ptr[index + 3],
					 ptr[index + 4], ptr[index + 5], ptr[index + 6], ptr[index + 7] );
			
		}
		
	}
	#endif
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTReadLogDirectory - Reads the SMART Log Directory
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTReadLogDirectory ( ATASMARTLogDirectory * log )
{
	
	IOReturn		status;
	
	status = SMARTReadLogAtAddress ( kATASMARTLogDirectoryEntry,
									 ( void * ) log,
									 sizeof ( ATASMARTLogDirectory ) );
	
	PRINT ( ( "ATASMARTClient::SMARTReadLogDirectory status = %d\n", status ) );		
	
	#if 0
	if ( status == kIOReturnSuccess )
	{
		
		UInt8 *		ptr = ( UInt8 * ) log;

		printf ( "ATA SMART Log Directory\n" );
		
		for ( UInt8	index = 0; ( index < sizeof ( ATASMARTLogDirectory ) ); index += 8 )
		{
			
			printf ( "0x%02x 0x%02x 0x%02x 0x%02x | 0x%02x 0x%02x 0x%02x 0x%02x\n",
					 ptr[index + 0], ptr[index + 1], ptr[index + 2], ptr[index + 3],
					 ptr[index + 4], ptr[index + 5], ptr[index + 6], ptr[index + 7] );
			
		}
		
	}
	#endif
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTReadLogAtAddress - 	Reads from the SMART Log at specified address
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTReadLogAtAddress ( UInt32		address,
										void *		buffer,
										UInt32		bufferSize )
{
	
	IOReturn				status;
	IOByteCount				byteCount;
	ATASMARTReadLogStruct	params;
	
	PRINT ( ( "ATASMARTClient::SMARTReadLogAtAddress called\n" ) );
		
	if ( ( address > 0xFF ) || ( buffer == NULL ) )
	{
		
		status = kIOReturnBadArgument;
		goto Exit;
		
	}
	
	byteCount = sizeof ( ATASMARTReadLogStruct );
	
	params.numSectors	= bufferSize / kATADefaultSectorSize;
	params.logAddress	= address & 0xFF;
	params.buffer		= buffer;
	params.bufferSize	= bufferSize;
	
	// Can't read or write more than 16 sectors
	if ( params.numSectors > 16 )
	{
		
		status = kIOReturnBadArgument;
		goto Exit;
		
	}
	
	PRINT ( ( "ATASMARTClient::SMARTReadLogAtAddress address = %ld\n", address ) );		
	
	status = IOConnectMethodScalarIStructureI (  fConnection, 	
												 kIOATASMARTReadLogAtAddress, 
												 0,
												 byteCount,
												 ( void * ) &params );
	
	
Exit:
	
	
	PRINT ( ( "ATASMARTClient::SMARTReadLogAtAddress status = %d\n", status ) );		
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� SMARTWriteLogAtAddress - Writes to the SMART Log at specified address
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::SMARTWriteLogAtAddress ( UInt32			address,
										 const void *	buffer,
										 UInt32			bufferSize )
{
	
	IOReturn				status;
	IOByteCount				byteCount;
	ATASMARTWriteLogStruct	params;
	
	PRINT ( ( "ATASMARTClient::SMARTWriteLogAtAddress called\n" ) );
		
	if ( ( address > 0xFF ) || ( buffer == NULL ) )
	{
		
		status = kIOReturnBadArgument;
		goto Exit;
		
	}
	
	byteCount = sizeof ( ATASMARTWriteLogStruct );
	
	params.numSectors	= bufferSize / kATADefaultSectorSize;
	params.logAddress	= address & 0xFF;
	params.buffer		= buffer;
	params.bufferSize	= bufferSize;
	
	// Can't read or write more than 16 sectors
	if ( params.numSectors > 16 )
	{
		
		status = kIOReturnBadArgument;
		goto Exit;
		
	}
	
	PRINT ( ( "ATASMARTClient::SMARTWriteLogAtAddress address = %ld\n", address ) );		
	
	status = IOConnectMethodScalarIStructureI (  fConnection, 	
												 kIOATASMARTWriteLogAtAddress, 
												 0,
												 byteCount,
												 ( void * ) &params );
	
	
Exit:
	
	
	PRINT ( ( "ATASMARTClient::SMARTWriteLogAtAddress status = %d\n", status ) );		
	
	return status;
	
}


#if 0
#pragma mark -
#pragma mark Additional Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//	� GetATAIdentifyData - Gets ATA Identify Data.					[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::GetATAIdentifyData ( void * buffer, UInt32 inSize, UInt32 * outSize )
{
	
	IOReturn					status				= kIOReturnBadArgument;
	IOByteCount					byteCount			= 0;
	ATAGetIdentifyDataStruct	params				= { 0 };
	UInt32						bytesTransferred 	= 0;
	
	if ( ( buffer == NULL ) || ( inSize > 512 ) || ( inSize == 0 ) )
	{
		
		status = kIOReturnBadArgument;
		goto Exit;
		
	}
	
	byteCount = sizeof ( UInt32 );
	
	params.buffer		= buffer;
	params.bufferSize	= inSize;
	
	PRINT ( ( "ATASMARTClient::GetATAIdentifyData\n" ) );		
	
	status = IOConnectMethodStructureIStructureO ( fConnection,
												   kIOATASMARTGetIdentifyData,
												   sizeof ( ATAGetIdentifyDataStruct ),
												   &byteCount,
												   ( void * ) &params,
												   ( void * ) &bytesTransferred );
	
	if ( outSize != NULL )
	{
		*outSize = bytesTransferred;
	}
	
	
Exit:
	
	
	PRINT ( ( "ATASMARTClient::GetATAIdentifyData status = %d\n", status ) );		
	
	return status;
	
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
ATASMARTClient::sQueryInterface ( void * self, REFIID iid, void ** ppv )
{
	
	ATASMARTClient *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->QueryInterface ( iid, ppv );
	
}


//�����������������������������������������������������������������������������
//	� sAddRef - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt32
ATASMARTClient::sAddRef ( void * self )
{
	
	ATASMARTClient *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->AddRef ( );
	
}


//�����������������������������������������������������������������������������
//	� sRelease - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

UInt32
ATASMARTClient::sRelease ( void * self )
{
	
	ATASMARTClient *	obj = ( ( InterfaceMap * ) self )->obj;
	return obj->Release ( );
	
}


//�����������������������������������������������������������������������������
//	� sProbe - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sProbe ( void *				self,
						 CFDictionaryRef	propertyTable, 
						 io_service_t		service,
						 SInt32 *			order )
{
	return getThis ( self )->Probe ( propertyTable, service, order );
}


//�����������������������������������������������������������������������������
//	� sStart - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sStart ( void *				self,
						 CFDictionaryRef	propertyTable,
						 io_service_t		service )
{
	return getThis ( self )->Start ( propertyTable, service );
}


//�����������������������������������������������������������������������������
//	� sStop - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sStop ( void * self )
{
	return getThis ( self )->Stop ( );
}


//�����������������������������������������������������������������������������
//	� sSMARTEnableDisableOperations - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTEnableDisableOperations ( void * self, Boolean enable )
{
	return getThis ( self )->SMARTEnableDisableOperations ( enable );
}


//�����������������������������������������������������������������������������
//	� sSMARTEnableDisableAutosave - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTEnableDisableAutosave ( void * self, Boolean enable )
{
	return getThis ( self )->SMARTEnableDisableAutosave ( enable );
}


//�����������������������������������������������������������������������������
//	� sSMARTReturnStatus - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTReturnStatus ( void * self, Boolean * exceededCondition )
{
	return getThis ( self )->SMARTReturnStatus ( exceededCondition );
}


//�����������������������������������������������������������������������������
//	� sSMARTExecuteOffLineImmediate - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTExecuteOffLineImmediate ( void * self, Boolean extendedTest )
{
	return getThis ( self )->SMARTExecuteOffLineImmediate ( extendedTest );
}


//�����������������������������������������������������������������������������
//	� sSMARTReadData - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTReadData ( void * self, ATASMARTData * data )
{
	return getThis ( self )->SMARTReadData ( data );
}


//�����������������������������������������������������������������������������
//	� sSMARTValidateReadData - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTValidateReadData ( void * self, const ATASMARTData * data )
{
	
	SInt8		checksum 	= 0;
	UInt32		index 		= 0;
	SInt8 *		ptr			= ( SInt8 * ) data;
	IOReturn	status		= kIOReturnError;
	
	PRINT ( ( "sSMARTValidateReadData called\n" ) );

	// Checksum the 511 bytes of the structure;
	for ( index = 0; index < ( sizeof ( ATASMARTData ) - 1 ); index++ )
	{
		
		checksum += ptr[index];
		
	}
	
	PRINT ( ( "Checksum = %d\n", checksum ) );
	PRINT ( ( "ptr[511] = %d\n", ptr[511] ) );
	
	if ( ( checksum + ptr[511] ) == 0 )
	{
		
		PRINT ( ( "Checksum is valid\n" ) );
		status = kIOReturnSuccess;
		
	}
	
	return status;
	
}


//�����������������������������������������������������������������������������
//	� sSMARTReadDataThresholds - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTReadDataThresholds (
							void *						self,
							ATASMARTDataThresholds * 	data )
{
	return getThis ( self )->SMARTReadDataThresholds ( data );
}


//�����������������������������������������������������������������������������
//	� sSMARTReadLogDirectory - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTReadLogDirectory ( void * self, ATASMARTLogDirectory * log )
{
	return getThis ( self )->SMARTReadLogDirectory ( log );
}


//�����������������������������������������������������������������������������
//	� sSMARTReadLogAtAddress - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTReadLogAtAddress ( void *		self,
										 UInt32		address,
										 void *		buffer,
										 UInt32		size )
{
	return getThis ( self )->SMARTReadLogAtAddress ( address, buffer, size );
}


//�����������������������������������������������������������������������������
//	� sSMARTWriteLogAtAddress - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sSMARTWriteLogAtAddress ( void *		self,
										  UInt32		address,
										  const void *	buffer,
										  UInt32		size )
{
	return getThis ( self )->SMARTWriteLogAtAddress ( address, buffer, size );
}


//�����������������������������������������������������������������������������
//	� sGetATAIdentifyData - Static function for C->C++ glue
//																	[PROTECTED]
//�����������������������������������������������������������������������������

IOReturn
ATASMARTClient::sGetATAIdentifyData ( void * self, void * buffer, UInt32 inSize, UInt32 * outSize )
{
	return getThis ( self )->GetATAIdentifyData ( buffer, inSize, outSize );
}
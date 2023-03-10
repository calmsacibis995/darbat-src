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


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Includes
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

// SCSI Architecture Model Family includes
#include "IOSCSIPeripheralDeviceType0E.h"


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Macros
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

#define DEBUG 									0
#define DEBUG_ASSERT_COMPONENT_NAME_STRING		"PDT 0E"

#if DEBUG
#define SCSI_PDT_0E_DEBUGGING_LEVEL				0
#endif


#include "IOSCSIArchitectureModelFamilyDebugging.h"


#if ( SCSI_PDT_0E_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)		IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( SCSI_PDT_0E_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)		IOLog x
#else
#define ERROR_LOG(x)
#endif

#if ( SCSI_PDT_0E_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)		IOLog x
#else
#define STATUS_LOG(x)
#endif


#define super IOSCSIReducedBlockCommandsDevice
OSDefineMetaClassAndStructors ( IOSCSIPeripheralDeviceType0E, IOSCSIReducedBlockCommandsDevice );


#if 0
#pragma mark -
#pragma mark ₯ Public Methods - Methods used by this class and subclasses
#pragma mark -
#endif


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ init - Called at initialization time						       [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
IOSCSIPeripheralDeviceType0E::init ( OSDictionary * propTable )
{
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::init called\n" ) );
	
	if ( super::init ( propTable ) == false )
	{
		
		STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::init exiting false\n" ) );
		return false;
		
	}
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::init exiting true\n" ) );
	
	return true;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ start - Called at services start time	(after successful matching)
//																	   [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

bool
IOSCSIPeripheralDeviceType0E::start ( IOService * provider )
{
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::start called\n" ) );
	
	// Call our superclass' start routine so that all inherited
	// behavior is initialized.    
	if ( !super::start ( provider ) )
    {
		return false;
	}
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::start exiting\n" ) );
	
	return true;
	
}


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	₯ stop - Called at stop start time								   [PUBLIC]
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

void
IOSCSIPeripheralDeviceType0E::stop ( IOService * provider )
{
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::stop called\n" ) );
	
	super::stop ( provider );
	
	STATUS_LOG ( ( "IOSCSIPeripheralDeviceType0E::stop exiting\n" ) );
	
}


#if 0
#pragma mark -
#pragma mark ₯ VTable Padding
#pragma mark -
#endif


// Space reserved for future expansion.
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 1 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 2 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 3 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 4 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 5 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 6 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 7 );
OSMetaClassDefineReservedUnused ( IOSCSIPeripheralDeviceType0E, 8 );
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

#include <IOKit/IOLib.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/storage/IOStorageDeviceCharacteristics.h>
#include <IOKit/IOPlatformExpert.h>

#include "IOATABlockStorageDriver.h"
#include "IOATABlockStorageDevice.h"
#include "ATASMARTLibPriv.h"

#define super IOBlockStorageDevice
OSDefineMetaClassAndStructors ( IOATABlockStorageDevice, IOBlockStorageDevice );

#ifdef L4IOKIT
#define ATA_BLOCK_STORAGE_DEVICE_DEBUGGING_LEVEL	0
//#define ATA_BLOCK_STORAGE_DEVICE_DEBUGGING_LEVEL	4
#endif

#if ( ATA_BLOCK_STORAGE_DEVICE_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)			IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( ATA_BLOCK_STORAGE_DEVICE_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)			IOLog x
#else
#define ERROR_LOG(x)
#endif

#if ( ATA_BLOCK_STORAGE_DEVICE_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)			IOLog x
#else
#define STATUS_LOG(x)
#endif


//---------------------------------------------------------------------------
// attach to provider.

bool
IOATABlockStorageDevice::attach ( IOService * provider )
{
	
	OSDictionary *	dictionary = NULL;

#ifndef L4IOKIT
	if ( !super::attach ( provider ) )
#else
	if ( !super::attach ( provider ) ) {
		IOLog("IOATABlockStorageDevice::%s can't super::attach\n",
		    __FUNCTION__);
#endif
		return false;
#ifdef L4IOKIT
	}
#endif
	
	fProvider = OSDynamicCast ( IOATABlockStorageDriver, provider );
	if ( fProvider == NULL )
	{
		
		ERROR_LOG ( ( "IOATABlockStorageDevice: attach; wrong provider type!\n" ) );
		return false;
		
	}
	
	reserved = IONew ( ExpansionData, 1 );
	if ( reserved == NULL )
	{
		
		ERROR_LOG ( ( "IOATABlockStorageDevice: attach; can't allocate ExpansionData!\n" ) );
		return false;
		
	}
	
	bzero ( reserved, sizeof ( ExpansionData ) );
	
	dictionary = OSDictionary::withCapacity ( 2 );
	if ( dictionary != NULL )
	{
		
		dictionary->setObject ( kIOPropertyPhysicalInterconnectTypeKey, fProvider->getProperty ( kIOPropertyPhysicalInterconnectTypeKey ) );
		dictionary->setObject ( kIOPropertyPhysicalInterconnectLocationKey, fProvider->getProperty ( kIOPropertyPhysicalInterconnectLocationKey ) );
		setProperty ( kIOPropertyProtocolCharacteristicsKey, dictionary );
		
		dictionary->release ( );
		
	}
	
	dictionary = OSDictionary::withCapacity ( 1 );
	if ( dictionary != NULL )
	{
		
		char *		string;
		OSString *	theString;
		OSNumber *	value;
		UInt32		features;
		
		string = getVendorString ( );
		
		theString = OSString::withCString ( string );
		if ( theString != NULL )
		{
			dictionary->setObject ( kIOPropertyVendorNameKey, theString );
			theString->release ( );
		}

		string = getProductString ( );

		theString = OSString::withCString ( string );
		if ( theString != NULL )
		{
			dictionary->setObject ( kIOPropertyProductNameKey, theString );
			theString->release ( );
		}

		string = getRevisionString ( );

		theString = OSString::withCString ( string );
		if ( theString != NULL )
		{
			dictionary->setObject ( kIOPropertyProductRevisionLevelKey, theString );
			theString->release ( );
		}
		
		dictionary->setObject ( kIOATASupportedFeaturesKey, fProvider->getProperty ( kIOATASupportedFeaturesKey ) );
		value = OSDynamicCast ( OSNumber, fProvider->getProperty ( kIOATASupportedFeaturesKey ) );
		if ( value != NULL )
		{
			
			features = value->unsigned32BitValue ( );
			if ( features & kIOATAFeatureSMART )
			{
				
				OSDictionary *	userClientDict = OSDictionary::withCapacity ( 1 );
				OSString *		string1;
				OSString *		string2;
				
				string1 = OSString::withCString ( kATASMARTUserClientTypeIDKey );
				string2 = OSString::withCString ( kATASMARTUserClientLibLocationKey );
				
				userClientDict->setObject ( string1, string2 );
				
				setProperty ( kIOUserClientClassKey, kATASMARTUserClientClassKey );
				setProperty ( kIOCFPlugInTypesKey, userClientDict );
				
				if ( userClientDict != NULL )
				{
					
					userClientDict->release ( );
					userClientDict = NULL;
					
				}
				
				if ( string1 != NULL )
				{
					
					string1->release ( );
					string1 = NULL;
					
				}

				if ( string2 != NULL )
				{
					
					string2->release ( );
					string2 = NULL;
					
				}
				
			}
			
		}
		
		setProperty ( kIOPropertyDeviceCharacteristicsKey, dictionary );
		
		dictionary->release ( );
		
	}

#ifdef L4IOKIT
	//IOLog("IOATABlockStorageDevice::attach returning true\n");
#endif	
	return true;
	
}


//---------------------------------------------------------------------------
// detach from provider.

void
IOATABlockStorageDevice::detach ( IOService * provider )
{
	
	if ( fProvider == provider )
		fProvider = 0;
	
	if ( reserved != NULL )
	{
		
		if ( fClients != NULL )
		{
			
			fClients->release ( );
			fClients = NULL;
			
		}
		
		IODelete ( reserved, ExpansionData, 1 );
		reserved = NULL;
		
	}
	
	super::detach ( provider );
	
}


//---------------------------------------------------------------------------
// handleOpen from client.

bool
IOATABlockStorageDevice::handleOpen ( IOService * client, IOOptionBits options, void * access )
{
	
	// If this isn't a user client, pass through to superclass.
	if ( ( options & kIOATASMARTUserClientAccessMask ) == 0 )
	{
		
		return super::handleOpen ( client, options, access );
		
	}
	
	// It's the user client, so add it to the set
	
	if ( fClients == NULL )
		fClients = OSSet::withCapacity ( 1 );
	
	if ( fClients == NULL )
		return false;
	
	// Check if we already have a user client open
	if ( fClients->getCount ( ) != 0 )
	{
		
		ERROR_LOG ( ( "User client already open\n" ) );
		return false;
	
	}
	
	fClients->setObject ( client );
	
	return true;
	
}


//---------------------------------------------------------------------------
// handleClose from client.

void
IOATABlockStorageDevice::handleClose ( IOService * client, IOOptionBits options )
{
	
	// If this isn't a user client, pass through to superclass.
	if ( ( options & kIOATASMARTUserClientAccessMask ) == 0 )
		super::handleClose ( client, options );
	
	else
	{
		
		STATUS_LOG ( ( "Removing user client\n" ) );
		fClients->removeObject ( client );
		if ( fClients->getCount ( ) != 0 )
		{
			
			ERROR_LOG ( ( "Removed client and still have count = %d\n", fClients->getCount ( ) ) );
			return;
			
		}
		
	}
	
}


//---------------------------------------------------------------------------
// handleIsOpen from client.

bool
IOATABlockStorageDevice::handleIsOpen ( const IOService * client ) const
{
	
	// General case (is anybody open)
	if ( client == NULL )
	{
		
		STATUS_LOG ( ( "IOATABlockStorageDevice::handleIsOpen, client is NULL\n" ) );
		
		if ( ( fClients != NULL ) && ( fClients->getCount ( ) > 0 ) )
			return true;
		
		STATUS_LOG ( ( "calling super\n" ) );
		
		return super::handleIsOpen ( client );
		
	}
	
	STATUS_LOG ( ( "IOATABlockStorageDevice::handleIsOpen, client = %p\n", client ) );
	
	// specific case (is this client open)
	if ( ( fClients != NULL ) && ( fClients->containsObject ( client ) ) )
		return true;
	
	STATUS_LOG ( ( "calling super\n" ) );
	
	return super::handleIsOpen ( client );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::setProperties ( OSObject * properties )
{
	
	OSDictionary *	dict 		= NULL;
	OSNumber *		number 		= NULL;
	IOReturn		status 		= kIOReturnSuccess;
	UInt32			features	= 0;
	boolean_t		success		= false;
	char			modelName[50];
	
	STATUS_LOG ( ( "IOATABlockStorageDevice::setProperties called\n" ) );
	
	status = super::setProperties ( properties );
	if ( status == kIOReturnSuccess )
	{
		return status;
	}
	
	number = ( OSNumber * ) fProvider->getProperty ( kIOATASupportedFeaturesKey );
	features = number->unsigned32BitValue ( );
	
	// Check if the drive supports this feature or not.
	if ( ( features & kIOATAFeatureAdvancedPowerManagement ) == 0 )
	{
		
		ERROR_LOG ( ( "IOATABlockStorageDevice::setProperties called on unsupported drive\n" ) );
		status = kIOReturnUnsupported;
		return status;
		
	}
	
	// Don't send the command to non-powerbooks
	success = PEGetModelName ( modelName, sizeof ( modelName ) );
	if ( success == true )
	{
		
		if ( strncmp ( modelName, "PowerBook", 9 ) != 0 )
		{
			
			ERROR_LOG ( ( "IOATABlockStorageDevice::setProperties called on non-powerbook drive\n" ) );
			status = kIOReturnUnsupported;
			return status;
			
		}
		
	}
	
	else
	{
		
		ERROR_LOG ( ( "IOATABlockStorageDevice::setProperties couldn't get model name\n" ) );
		status = kIOReturnUnsupported;
		return status;
		
	}
	
	dict = OSDynamicCast ( OSDictionary, properties );
	if ( dict != NULL )
	{
		number = OSDynamicCast ( OSNumber, dict->getObject ( "APM Level" ) );
	}
	
	if ( number != NULL )
	{
				
		UInt8	apmLevel = number->unsigned8BitValue ( );
		
		if ( ( apmLevel == 0 ) || ( apmLevel == 0xFF ) )
		{
			
			status = kIOReturnBadArgument;
			return status;
			
		}
		
		STATUS_LOG ( ( "apmLevel = %d\n", apmLevel ) );
		
		status = fProvider->setAdvancedPowerManagementLevel ( apmLevel, true );
		
	}
	
	else
	{
		status = kIOReturnBadArgument;
	}
	
	STATUS_LOG ( ( "IOATABlockStorageDevice::leave setProperties\n" ) );
	
	return status;
	
}




//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::doAsyncReadWrite (
											IOMemoryDescriptor *	buffer,
											UInt32					block,
											UInt32					nblks,
											IOStorageCompletion		completion )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	fProvider->checkPowerState ( );
	return fProvider->doAsyncReadWrite ( buffer, block, nblks, completion );
	
}


//---------------------------------------------------------------------------
//

IOReturn
IOATABlockStorageDevice::doSyncReadWrite (	IOMemoryDescriptor * buffer,
											UInt32 block, UInt32 nblks )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	fProvider->checkPowerState ( );
	return fProvider->doSyncReadWrite ( buffer, block, nblks );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::doEjectMedia ( void )
{
	
	return fProvider->doEjectMedia ( );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::doFormatMedia ( UInt64 byteCapacity )
{
	
	return fProvider->doFormatMedia ( byteCapacity );
	
}


//---------------------------------------------------------------------------
// 

UInt32
IOATABlockStorageDevice::doGetFormatCapacities ( UInt64 * capacities,
												 UInt32   capacitiesMaxCount ) const
{
	
	return fProvider->doGetFormatCapacities ( capacities, capacitiesMaxCount );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::doLockUnlockMedia ( bool doLock )
{
	
	return fProvider->doLockUnlockMedia ( doLock );
	
}


//---------------------------------------------------------------------------
//

IOReturn
IOATABlockStorageDevice::doSynchronizeCache ( void )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	fProvider->checkPowerState ( );
	return fProvider->doSynchronizeCache ( );
	
}


//---------------------------------------------------------------------------
// 

char *
IOATABlockStorageDevice::getVendorString ( void )
{

	return fProvider->getVendorString ( );

}


//---------------------------------------------------------------------------
// 

char *
IOATABlockStorageDevice::getProductString ( void )
{
	
	return fProvider->getProductString ( );
	
}


//---------------------------------------------------------------------------
// 

char *
IOATABlockStorageDevice::getRevisionString ( void )
{
	
	return fProvider->getRevisionString ( );
	
}


//---------------------------------------------------------------------------
// 

char *
IOATABlockStorageDevice::getAdditionalDeviceInfoString ( void )
{
	
	return fProvider->getAdditionalDeviceInfoString ( );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportBlockSize ( UInt64 * blockSize )
{
	
	return fProvider->reportBlockSize ( blockSize );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportEjectability ( bool * isEjectable )
{
	
	return fProvider->reportEjectability ( isEjectable );

}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportLockability ( bool * isLockable )
{
	
	return fProvider->reportLockability ( isLockable );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportPollRequirements ( 	bool * pollIsRequired,
													bool * pollIsExpensive )
{
	
	return fProvider->reportPollRequirements ( pollIsRequired, pollIsExpensive );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportMaxReadTransfer ( UInt64 blockSize,
													UInt64 * max )
{
	
	return fProvider->reportMaxReadTransfer ( blockSize, max );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportMaxValidBlock ( UInt64 * maxBlock )
{

	return fProvider->reportMaxValidBlock ( maxBlock );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportMaxWriteTransfer ( UInt64	blockSize,
												  UInt64 *	max )
{
	
	return fProvider->reportMaxWriteTransfer ( blockSize, max );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportMediaState ( bool * mediaPresent,
											bool * changed )	
{
	
	return fProvider->reportMediaState ( mediaPresent, changed );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportRemovability ( bool * isRemovable )
{
	
	return fProvider->reportRemovability ( isRemovable );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::reportWriteProtection ( bool * isWriteProtected )
{
	
	return fProvider->reportWriteProtection ( isWriteProtected );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::getWriteCacheState ( bool * enabled )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	return fProvider->getWriteCacheState ( enabled );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::setWriteCacheState ( bool enabled )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	return fProvider->setWriteCacheState ( enabled );
	
}


//---------------------------------------------------------------------------
// 

IOReturn
IOATABlockStorageDevice::sendSMARTCommand ( IOATACommand * command )
{
	
	// Block incoming I/O if we have been terminated
	if ( isInactive ( ) != false )
	{
		return kIOReturnNotAttached;
	}
	
	return fProvider->sendSMARTCommand ( command );
	
}


// binary compatibility reserved method space
OSMetaClassDefineReservedUsed ( IOATABlockStorageDevice, 1 );	/* sendSMARTCommand */

OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 2 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 3 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 4 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 5 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 6 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 7 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 8 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 9 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 10 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 11 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 12 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 13 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 14 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 15 );
OSMetaClassDefineReservedUnused ( IOATABlockStorageDevice, 16 );

//--------------------------------------------------------------------------------------
//							End				Of				File
//--------------------------------------------------------------------------------------

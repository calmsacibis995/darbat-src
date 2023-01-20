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
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
* � Copyright 2001-2003 Apple Computer, Inc. All rights reserved.
*
* IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. (�Apple�) in 
* consideration of your agreement to the following terms, and your use, installation, 
* modification or redistribution of this Apple software constitutes acceptance of these
* terms.  If you do not agree with these terms, please do not use, install, modify or 
* redistribute this Apple software.
*
* In consideration of your agreement to abide by the following terms, and subject to these 
* terms, Apple grants you a personal, non exclusive license, under Apple�s copyrights in this 
* original Apple software (the �Apple Software�), to use, reproduce, modify and redistribute 
* the Apple Software, with or without modifications, in source and/or binary forms; provided 
* that if you redistribute the Apple Software in its entirety and without modifications, you 
* must retain this notice and the following text and disclaimers in all such redistributions 
* of the Apple Software.  Neither the name, trademarks, service marks or logos of Apple 
* Computer, Inc. may be used to endorse or promote products derived from the Apple Software 
* without specific prior written permission from Apple. Except as expressly stated in this 
* notice, no other rights or licenses, express or implied, are granted by Apple herein, 
* including but not limited to any patent rights that may be infringed by your derivative 
* works or by other works in which the Apple Software may be incorporated.
* 
* The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, 
* EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-
* INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE 
* SOFTWARE OR ITS USE AND OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS. 
*
* IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
* REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND 
* WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR 
* OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/		


//�����������������������������������������������������������������������������
//	Includes
//�����������������������������������������������������������������������������

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/scsi/SCSITaskLib.h>
#include <IOKit/scsi/SCSITask.h>
#include <IOKit/scsi/SCSICmds_INQUIRY_Definitions.h>
#include <IOKit/scsi/SCSICommandOperationCodes.h>
#include <IOKit/storage/IOCDTypes.h>
#include <IOKit/storage/IODVDTypes.h>
#include <CoreFoundation/CoreFoundation.h>


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define DEBUG	0

#define DEBUG_ASSERT_COMPONENT_NAME_STRING "AuthoringUnitTestUnixTool"

#if DEBUG
#define DEBUG_ASSERT_MESSAGE(componentNameString,	\
							 assertionString,		\
							 exceptionLabelString,	\
							 errorString,			\
							 fileName,				\
							 lineNumber,			\
							 errorCode)				\
DebugAssert(componentNameString,					\
					   assertionString,				\
					   exceptionLabelString,		\
					   errorString,					\
					   fileName,					\
					   lineNumber,					\
					   errorCode)					\

static void
DebugAssert ( const char *	componentNameString,
			  const char *	assertionString,
			  const char *	exceptionLabelString,
			  const char *	errorString,
			  const char *	fileName,
			  long			lineNumber,
			  int			errorCode )
{
	
	if ( ( assertionString != NULL ) && ( *assertionString != '\0' ) )
		printf ( "Assertion failed: %s: %s\n", componentNameString, assertionString );
	else
		printf ( "Check failed: %s:\n", componentNameString );
	if ( exceptionLabelString != NULL )
		printf ( "	 %s\n", exceptionLabelString );
	if ( errorString != NULL )
		printf ( "	 %s\n", errorString );
	if ( fileName != NULL )
		printf ( "	 file: %s\n", fileName );
	if ( lineNumber != 0 )
		printf ( "	 line: %ld\n", lineNumber );
	if ( errorCode != 0 )
		printf ( "	 error: %d\n", errorCode );
	
}

#endif	/* DEBUG */

#include <AssertMacros.h>


//�����������������������������������������������������������������������������
//	Constants
//�����������������������������������������������������������������������������

// Mechanical Capabilities flags
enum
{
	kMechanicalCapabilitiesCDRMask		= 0x01,
	kMechanicalCapabilitiesCDRWMask		= 0x02,
	kMechanicalCapabilitiesDVDROMMask	= 0x08,
	kMechanicalCapabilitiesDVDRMask		= 0x10,
	kMechanicalCapabilitiesDVDRAMMask 	= 0x20,
};

#define kModeSenseParameterHeaderSize 8


//�����������������������������������������������������������������������������
//	Globals
//�����������������������������������������������������������������������������

static IONotificationPortRef	gNotifyPort;
static io_iterator_t			gAppearedIter;
static io_iterator_t			gDisappearedIter;


//�����������������������������������������������������������������������������
//	Prototypes
//�����������������������������������������������������������������������������

static void
PrintSenseString ( SCSI_Sense_Data * sense, Boolean addRawValues );

static void
TestDevice ( io_service_t service );

static void
ExclusiveTestUnitReady ( SCSITaskDeviceInterface ** interface );

static void
ExclusiveInquiry ( SCSITaskDeviceInterface ** interface );

static void
DeviceAppeared ( void * refCon, io_iterator_t iterator );

static void
DeviceDisappeared ( void * refCon, io_iterator_t iterator );

static void
StripWhiteSpace ( char * buffer, SInt32 length );

static void
SignalHandler ( int sigraised );

static void
TestMMCInterface ( MMCDeviceInterface ** interface );

static void
TestSCSITaskDeviceInterface ( SCSITaskDeviceInterface ** interface );

static void
TestUnitReady ( MMCDeviceInterface ** interface );

static void
Inquiry ( MMCDeviceInterface ** interface );

static void
ModeSense10 ( MMCDeviceInterface ** interface );

static void
GetTrayState ( MMCDeviceInterface ** interface );

static void
SetTrayState ( MMCDeviceInterface ** interface, UInt8 trayState );

static void
ReadTableOfContents ( MMCDeviceInterface ** interface );

static void
ReadDiscInformation ( MMCDeviceInterface ** interface );

static void
ReadTrackRZoneInformation ( MMCDeviceInterface ** interface );

static void
ReadDVDStructure ( MMCDeviceInterface ** interface );

static void
SetCDSpeed ( MMCDeviceInterface ** interface );

static void
ReadFormatCapacities ( MMCDeviceInterface ** interface );


//�����������������������������������������������������������������������������
//	�	main - Our main entry point
//�����������������������������������������������������������������������������

int
main ( int argc, const char * argv[] )
{

#pragma unused ( argc )
#pragma unused ( argv )
	
	CFMutableDictionaryRef 	matchingDict	= NULL;
	CFMutableDictionaryRef 	subDict			= NULL;
	CFRunLoopSourceRef		runLoopSource	= NULL;
	IOReturn				error			= kIOReturnSuccess;
	sig_t					oldHandler		= 0;
	
	// Set up a signal handler so we can clean up when we're interrupted from the command line
	// Otherwise we stay in our run loop forever.
	oldHandler = signal ( SIGINT, SignalHandler );
	if ( oldHandler == SIG_ERR )
		printf ( "Could not establish new signal handler" );
	
	// Create the dictionaries
	matchingDict = CFDictionaryCreateMutable ( kCFAllocatorDefault,
											   0,
											   &kCFTypeDictionaryKeyCallBacks,
											   &kCFTypeDictionaryValueCallBacks );
	
	subDict = CFDictionaryCreateMutable ( kCFAllocatorDefault,
										  0,
										  &kCFTypeDictionaryKeyCallBacks,
										  &kCFTypeDictionaryValueCallBacks );
	
	//
	//	Note: We are setting up a matching dictionary which looks like the following:
	//
	//	<dict>
	//		<key>IOPropertyMatch</key>
	//		<dict>
	//			<key>SCSITaskDeviceCategory</key>
	//			<string>SCSITaskAuthoringDevice</string>
	//		</dict>
	// </dict>
	//
	
	// Create a dictionary with the "SCSITaskDeviceCategory" key = "SCSITaskAuthoringDevice"
	CFDictionarySetValue ( 	subDict,
							CFSTR ( kIOPropertySCSITaskDeviceCategory ),
							CFSTR ( kIOPropertySCSITaskAuthoringDevice ) );
	
	// Add the dictionary to the main dictionary with the key "IOPropertyMatch" to
	// narrow the search to the above dictionary.
	CFDictionarySetValue ( 	matchingDict,
							CFSTR ( kIOPropertyMatchKey ),
							subDict );
	
	// Create a notification port and add its run loop event source to our run loop
	// This is how async notifications get set up.
	gNotifyPort 	= IONotificationPortCreate ( kIOMasterPortDefault );
	runLoopSource 	= IONotificationPortGetRunLoopSource ( gNotifyPort );
	
	// Add the runloop source to the current runloop. You must enter the runloop by calling
	// CFRunLoopRun() before any notifications can be delivered.
	CFRunLoopAddSource ( CFRunLoopGetCurrent ( ), runLoopSource, kCFRunLoopDefaultMode );
	
	// Retain a reference since we arm both the appearance and disappearance notifications
	// and the call to IOServiceAddMatchingNotification() consumes a reference each time.
	matchingDict = ( CFMutableDictionaryRef ) CFRetain ( matchingDict );
	
	// Now set up two notifications, one to be called when an authoring device is
	// first matched by I/O Kit, and the other to be called when the device is
	// terminated.
	error = IOServiceAddMatchingNotification ( gNotifyPort,
											   kIOFirstMatchNotification,
											   matchingDict,
											   DeviceAppeared,
											   NULL,
											   &gAppearedIter );
	
	// Iterate once to get already-present devices and arm the notification
	DeviceAppeared ( NULL, gAppearedIter );
	
	error = IOServiceAddMatchingNotification ( gNotifyPort,
											   kIOTerminatedNotification,
											   matchingDict,
											   DeviceDisappeared,
											   NULL,
											   &gDisappearedIter );
	
	// Iterate once to arm the notification
	DeviceDisappeared ( NULL, gDisappearedIter );
	
	// Start the run loop. Now we'll receive notifications.
	CFRunLoopRun ( );
	
	// We should never get here, but this is required.
	return 0;
	
}


//�����������������������������������������������������������������������������
//	�	TestDevice -  Creates a plugin for the device and begins test process
//�����������������������������������������������������������������������������

static void
TestDevice ( io_service_t service )
{
	
	SInt32							score			= 0;
	HRESULT							herr			= S_OK;
	IOReturn						err				= kIOReturnSuccess;
	IOCFPlugInInterface **			plugInInterface = NULL;
	MMCDeviceInterface **			mmcInterface	= NULL;
	SCSITaskDeviceInterface **		interface		= NULL;
	
	// Create the IOCFPlugIn interface so we can query it.
	err = IOCreatePlugInInterfaceForService ( 	service,
												kIOMMCDeviceUserClientTypeID,
												kIOCFPlugInInterfaceID,
												&plugInInterface,
												&score );
	
	require ( ( err == kIOReturnSuccess ), ErrorExit );
	
	// Query the interface for the MMCDeviceInterface.
	herr = ( *plugInInterface )->QueryInterface ( plugInInterface,
										CFUUIDGetUUIDBytes ( kIOMMCDeviceInterfaceID ),
										( LPVOID ) &mmcInterface );
	
	require ( ( herr == S_OK ), DestroyPlugin );
	
	TestMMCInterface ( mmcInterface );
	
	// Get the SCSITaskDeviceInterface so we can send exclusive commands
	interface = ( *mmcInterface )->GetSCSITaskDeviceInterface ( mmcInterface );
	require ( ( interface != NULL ), ReleaseMMCInterface );
	
	// Obtain exclusive access
	err = ( *interface )->ObtainExclusiveAccess ( interface );
	require ( ( err == kIOReturnSuccess ), ReleaseDeviceInterface );
	
	TestSCSITaskDeviceInterface ( interface );
	
	// Make sure we release exclusive access now that we are done with the device.
	( *interface )->ReleaseExclusiveAccess ( interface );
	
	
ReleaseDeviceInterface:
	
	
	require_quiet ( ( interface != NULL ), ReleaseMMCInterface );
	( *interface )->Release ( interface );
	interface = NULL;
	
	
ReleaseMMCInterface:
	
	
	require_quiet ( ( mmcInterface != NULL ), DestroyPlugin );
	( *mmcInterface )->Release ( mmcInterface );
	mmcInterface = NULL;
	
	
DestroyPlugin:
	
	
	require_quiet ( ( plugInInterface != NULL ), ErrorExit );
	IODestroyPlugInInterface ( plugInInterface );
	plugInInterface = NULL;
	
	
ErrorExit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	�	TestMMCInterface - Tests the MMC interface (non-exclusive commands)
//�����������������������������������������������������������������������������

static void
TestMMCInterface ( MMCDeviceInterface ** interface )
{
	
	TestUnitReady ( interface );
	Inquiry ( interface );
	ModeSense10 ( interface );
	GetTrayState ( interface );
	SetTrayState ( interface, kMMCDeviceTrayOpen );
	SetTrayState ( interface, kMMCDeviceTrayClosed );
	ReadTableOfContents ( interface );
	ReadDiscInformation ( interface );
	ReadTrackRZoneInformation ( interface );
	ReadDVDStructure ( interface );
	SetCDSpeed ( interface );
	ReadFormatCapacities ( interface );
	
}


//�����������������������������������������������������������������������������
//	�	TestUnitReady - Calls the TestUnitReady method
//�����������������������������������������������������������������������������

static void
TestUnitReady ( MMCDeviceInterface ** interface )
{
	
	SCSITaskStatus			taskStatus		= kSCSITaskStatus_No_Status;
	IOReturn				err				= kIOReturnSuccess;
	SCSI_Sense_Data			senseBuffer		= { 0 };
	
	printf ( "TestUnitReady: " );
	
	// Issue a TEST_UNIT_READY through the non-exclusive MMCDeviceInterface
	err = ( *interface )->TestUnitReady ( interface, &taskStatus, &senseBuffer );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "TestUnitReady failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		printf ( "Good Status\n" );
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseBuffer, false );
		
	}
	
	else
	{
		printf ( "taskStatus = %d\n", taskStatus );
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	Inquiry - Calls the Inquiry method
//�����������������������������������������������������������������������������

static void
Inquiry ( MMCDeviceInterface ** interface )
{

	SCSICmd_INQUIRY_StandardData	inqBuffer		= { 0 };	
	SCSI_Sense_Data					senseBuffer		= { 0 };
	SCSITaskStatus					taskStatus		= kSCSITaskStatus_No_Status;
	IOReturn						err				= kIOReturnSuccess;
	
	printf ( "Inquiry:" );
	
	// Issue a TEST_UNIT_READY through the non-exclusive MMCDeviceInterface
	err = ( *interface )->Inquiry ( interface, &inqBuffer, sizeof ( inqBuffer ), &taskStatus, &senseBuffer );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "Inquiry failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		char	tmp[kINQUIRY_PRODUCT_IDENTIFICATION_Length + 1];
		
		printf ( "Good Status\n" );
		printf ( "Inquiry Data\n" );
		
		printf ( "Peripheral Device Type = %d\n",
				 inqBuffer.PERIPHERAL_DEVICE_TYPE & kINQUIRY_PERIPHERAL_TYPE_Mask );
		printf ( "Removable Media Bit = %d\n",
				 inqBuffer.RMB & kINQUIRY_PERIPHERAL_RMB_MediumRemovable ? 1 : 0 );
		
		bcopy ( inqBuffer.VENDOR_IDENTIFICATION, tmp, kINQUIRY_VENDOR_IDENTIFICATION_Length );
		tmp[kINQUIRY_VENDOR_IDENTIFICATION_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_VENDOR_IDENTIFICATION_Length );
		printf ( "Vendor Identification = %s\n", tmp );
		
		bcopy ( inqBuffer.PRODUCT_IDENTIFICATION, tmp, kINQUIRY_PRODUCT_IDENTIFICATION_Length );
		tmp[kINQUIRY_PRODUCT_IDENTIFICATION_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_PRODUCT_IDENTIFICATION_Length );		
		printf ( "Product Identification = %s\n", tmp );
		
		bcopy ( inqBuffer.PRODUCT_REVISION_LEVEL, tmp, kINQUIRY_PRODUCT_REVISION_LEVEL_Length );
		tmp[kINQUIRY_PRODUCT_REVISION_LEVEL_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_PRODUCT_REVISION_LEVEL_Length );		
		printf ( "Product Revision Level = %s\n", tmp );
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseBuffer, false );
		
	}
	
	else
	{
		printf ( "taskStatus = %d\n", taskStatus );
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ModeSense10 - Calls the ModeSense10 method
//�����������������������������������������������������������������������������

static void
ModeSense10 ( MMCDeviceInterface ** interface )
{
	
	UInt16				size					= 0;
	IOReturn			err						= kIOReturnSuccess;
	UInt8 *				buffer					= NULL;
	UInt8 * 			mechanicalCapabilities	= NULL;
	SCSITaskStatus		taskStatus				= kSCSITaskStatus_No_Status;
	SCSI_Sense_Data		senseData				= { 0 };
	UInt8				parameterHeader[kModeSenseParameterHeaderSize] = { 0 };
	
	printf ( "ModeSense10: " );
	
	// Issue a MODE_SENSE_10 through the non-exclusive MMCDeviceInterface. Ask it for
	// the Mechanical Capabilities mode page (0x2A). Only ask for 8 bytes to get the real
	// size of the mode page.
	err = ( *interface )->ModeSense10 ( interface,
										0,
										0,
										0,
										0x2A,
										parameterHeader,
										kModeSenseParameterHeaderSize,
										&taskStatus,
										&senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ModeSense10 failed, err = 0x%08x\n", err ) );
	
	printf ( "Mode Sense Data\n" );
	
	// First word of returned data is where the size is stored.
	size = OSReadBigInt16 ( parameterHeader, 0 );
	
	printf ( "Mechanical Capabilities page size = %d\n", size );
	
	// Create a buffer the size the drive returned
	buffer = ( UInt8 * ) malloc ( size );
	require ( ( buffer != NULL ), ErrorExit );
	
	// Issue a MODE_SENSE_10 through the non-exclusive MMCDeviceInterface. Ask it for
	// the Mechanical Capabilities mode page (0x2A). Ask for all the bytes is said it could return.
	err = ( *interface )->ModeSense10 ( interface,
										0,
										0,
										0,
										0x2A,
										buffer,
										size,
										&taskStatus,
										&senseData );
	require_action ( ( err == kIOReturnSuccess ), FreeBuffer, printf ( "ModeSense10 failed, err = 0x%08x\n", err ) );
	
	mechanicalCapabilities = &buffer[kModeSenseParameterHeaderSize + 2];
	
	// Walk the buffer of the mechanical capabilities page. The passed in buffer
	// starts at byte 11 which is where the DVD-ROM capabilities are.
	if ( ( *mechanicalCapabilities & kMechanicalCapabilitiesDVDROMMask ) != 0 )
	{
		
		printf ( "Device supports DVD-ROM\n" );
		
	}

	mechanicalCapabilities++;		

	// Walk the 12th byte now.
	if ( ( *mechanicalCapabilities & kMechanicalCapabilitiesDVDRAMMask ) != 0 )
	{

		printf ( "Device supports DVD-RAM\n" );
		
	}

	if ( ( *mechanicalCapabilities & kMechanicalCapabilitiesDVDRMask ) != 0 )
	{
		
		printf ( "Device supports DVD-R\n" );
		
	}
	
	if ( ( *mechanicalCapabilities & kMechanicalCapabilitiesCDRWMask ) != 0 )
	{
		
		printf ( "Device supports CD-RW\n" );
		
	}
	
	if ( ( *mechanicalCapabilities & kMechanicalCapabilitiesCDRMask ) != 0 )
	{
		
		printf ( "Device supports CD-R\n" );
	
	}
	
	// Since it responded to the CD Mechanical Capabilities Mode Page, it must at
	// least be a CD-ROM...
	printf ( "Device supports CD-ROM\n" );
	
	
FreeBuffer:
	
	
	require_quiet ( ( buffer != NULL ), ErrorExit );
	free ( ( void * ) buffer );
	buffer = NULL;
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	GetTrayState - Calls the GetTrayState method
//�����������������������������������������������������������������������������

static void
GetTrayState ( MMCDeviceInterface ** interface )
{

	UInt8		trayState 	= 0;
	IOReturn	err			= kIOReturnSuccess;
	
	printf ( "GetTrayState: " );
	
	// Ask the device if its tray state is closed or open.
	err = ( *interface )->GetTrayState ( interface, &trayState );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "GetTrayState failed, err = 0x%08x\n", err ) );
	
	if ( trayState == kMMCDeviceTrayOpen )
	{
		printf ( "Tray open\n" );
	}
	
	else if ( trayState == kMMCDeviceTrayClosed )
	{
		printf ( "Tray closed\n" );
	}
	
	else
	{
		printf ( "Unexpected value\n" );
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	SetTrayState - Calls the SetTrayState method
//�����������������������������������������������������������������������������

static void
SetTrayState ( MMCDeviceInterface ** interface, UInt8 trayState )
{

	IOReturn	err	= kIOReturnSuccess;
	
	printf ( "SetTrayState: " );
	
	// Ask the device to open the tray. This will not work if media is
	// in the drive. You must use Carbon FSVolumeUnmountSync/Async in
	// that case.
	err = ( *interface )->SetTrayState ( interface, trayState );
	check ( err == kIOReturnSuccess );
	
	if ( err == kIOReturnSuccess )
	{
		
		if ( trayState == kMMCDeviceTrayOpen )
		{
			printf ( "Tray Opened\n" );
		}
		
		else if ( trayState == kMMCDeviceTrayClosed )
		{
			printf ( "Tray Closed\n" );
		}
		
	}
	
	else if ( err == kIOReturnExclusiveAccess )
	{
		printf ( "Another client has exclusive access!\n" );
	}
	
	else
	{
		printf ( "Error = 0x%08x\n", err );
	}
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ReadTableOfContents - Calls the ReadTableOfContents method
//�����������������������������������������������������������������������������

static void
ReadTableOfContents ( MMCDeviceInterface ** interface )
{
	
	UInt8				tocBuffer[4096] = { 0 };
	SCSI_Sense_Data		senseData		= { 0 };
	SCSITaskStatus		taskStatus		= kSCSITaskStatus_No_Status;
	IOReturn			err				= kIOReturnSuccess;
	UInt16				tocSize			= 0;
	UInt16				requestSize		= 0;
	
	printf ( "ReadTableOfContents: " );
	
	// Issue a READ_TOC_PMA_ATIP command through this call. We are going to ask for TOC format 0x02 (the whole TOC)
	// in one shot. First, request 4 bytes to find out how much TOC data there is.
	err = ( *interface )->ReadTableOfContents ( interface,
												1,
												0x02,
												0x00,
												tocBuffer,
												4,
												&taskStatus,
												&senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadTableOfContents failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		// Find out how much data there is. Add the size of the first word because it isn't counted
		// and then round up to the nearest even value since the spec isn't clear what should happen
		// on ATAPI devices with odd byte requests.
		requestSize = tocSize = OSReadBigInt16 ( tocBuffer, 0 ) + sizeof ( UInt16 );
		if ( tocSize & 1 )
			requestSize += 1;
		
		printf ( "Toc size = %d\n", tocSize );
		err = ( *interface )->ReadTableOfContents ( interface,
													1,
													0x02,
													0x00,
													tocBuffer,
													requestSize,
													&taskStatus,
													&senseData );
		require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadTableOfContents failed, err = 0x%08x\n", err ) );
		
		if ( taskStatus == kSCSITaskStatus_GOOD )
		{
			
			UInt16	index = 0;
			
			// Print the TOC data
			printf ( "TOC Data\n" );
			
			for ( index = 0; index < tocSize; index++ )
			{
				printf ( "0x%02x : ", tocBuffer[index] );
			}
			
			printf ( "\n" );
			
		}
		
		else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
		{
			
			// Something happened. Print the sense string
			PrintSenseString ( &senseData, false );
			
		}
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ReadDiscInformation - Calls the ReadDiscInformation method
//�����������������������������������������������������������������������������

static void
ReadDiscInformation ( MMCDeviceInterface ** interface )
{

	UInt8				discInfoBuffer[4096]	= { 0 };
	SCSI_Sense_Data		senseData				= { 0 };
	SCSITaskStatus		taskStatus				= kSCSITaskStatus_No_Status;
	IOReturn			err						= kIOReturnSuccess;
	UInt8				index					= 0;
	UInt16				discInfoSize			= 0;
	UInt16				requestSize				= 0;
	
	printf ( "ReadDiscInformation: " );
	
	// Issue a READ_DISC_INFORMATION command to the device. Ask for 4 bytes to get the length field.
	err = ( *interface )->ReadDiscInformation ( interface,
												discInfoBuffer,
												4,
												&taskStatus,
												&senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadDiscInformation failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		// The first word contains the size. Add 2 bytes for the first word since it isn't counted
		requestSize = discInfoSize = OSReadBigInt16 ( discInfoBuffer, 0 ) + sizeof ( UInt16 );
		if ( discInfoSize & 1 )
			requestSize += 1;
		
		printf ( "Disc Info size = %d\n", discInfoSize );
		
		// Issue another READ_DISC_INFORMATION command to the device with the correct sized buffer.
		err = ( *interface )->ReadDiscInformation ( interface,
													discInfoBuffer,
													requestSize,
													&taskStatus,
													&senseData );
		require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadDiscInformation failed, err = 0x%08x\n", err ) );
		
		if ( taskStatus == kSCSITaskStatus_GOOD )
		{
			
			// Print the discinfo data
			printf ( "Disc Info Data\n" );
			
			for ( index = 0; index < discInfoSize; index++ )
			{
				printf ( "0x%02x : ", discInfoBuffer[index] );
			}
			
			printf ( "\n" );
			
		}
		
		else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
		{
			
			// Something happened. Print the sense string
			PrintSenseString ( &senseData, false );
			
		}
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ReadTrackRZoneInformation - Calls the ReadTrackInformation method
//�����������������������������������������������������������������������������

static void
ReadTrackRZoneInformation ( MMCDeviceInterface ** interface )
{

	UInt8				trackInfoBuffer[36]		= { 0 };
	SCSI_Sense_Data		senseData				= { 0 };
	SCSITaskStatus		taskStatus				= kSCSITaskStatus_No_Status;
	IOReturn			err						= kIOReturnSuccess;
	UInt8				index					= 0;
	UInt16				trackInfoSize			= 0;
	UInt16				requestSize				= 0;
	
	printf ( "ReadTrackRZoneInformation: " );
	
	// Issue a READ_TRACK_INFORMATION command to the device. Ask for 4 bytes to get the length field.
	// I decided to ask for LBA 32. That was just an arbitrary number.
	err = ( *interface )->ReadTrackInformation ( interface,
												 0x00,
												 32,
												 trackInfoBuffer,
												 4,
												 &taskStatus,
												 &senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadTrackInformation failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		// The first word contains the size. Add 2 bytes for the first word since it isn't counted
		requestSize = trackInfoSize = OSReadBigInt16 ( trackInfoBuffer, 0 ) + sizeof ( UInt16 );
		if ( trackInfoSize & 1 )
			requestSize += 1;
		
		printf ( "Track Info size = %d\n", trackInfoSize );
		
		// Issue a READ_TRACK_INFORMATION command to the device. Ask for the whole buffer this time.
		// I decided to ask for LBA 32. That was just an arbitrary number.
		err = ( *interface )->ReadTrackInformation ( interface,
													 0x00,
													 32,
													 trackInfoBuffer,
													 requestSize,
													 &taskStatus,
													 &senseData );
		require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadTrackInformation failed, err = 0x%08x\n", err ) );
		
		if ( taskStatus == kSCSITaskStatus_GOOD )
		{
			
			// Print the discinfo data
			printf ( "Track/RZone Info Data\n" );
			
			for ( index = 0; index < trackInfoSize; index++ )
			{
				printf ( "0x%02x : ", trackInfoBuffer[index] );
			}
			
			printf ( "\n" );
			
		}
		
		else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
		{
			
			// Something happened. Print the sense string
			PrintSenseString ( &senseData, false );
			
		}
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ReadDVDStructure - Calls the ReadDVDStructure method
//�����������������������������������������������������������������������������

static void
ReadDVDStructure ( MMCDeviceInterface ** interface )
{
	
	DVDPhysicalFormatInfo	physicalFormatInfo	= { { 0 } };
	SCSI_Sense_Data			senseData			= { 0 };
	SCSITaskStatus			taskStatus			= kSCSITaskStatus_No_Status;
	IOReturn				err					= kIOReturnSuccess;
	
	printf ( "ReadDVDStructure: " );
	
	// Issue a READ_DVD_STRUCTURE command to the device. Ask for 8 bytes to get the medium's book type.
	err = ( *interface )->ReadDVDStructure ( interface,
											 0x00,
											 0x00,
											 0x00,
											 &physicalFormatInfo,
											 8,
											 &taskStatus,
											 &senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadDVDStructure failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		printf ( "DVD Structure Data\n" );
		printf ( "Book Type = %d\n", physicalFormatInfo.bookType );
		printf ( "Number of Layers = %d\n", physicalFormatInfo.numberOfLayers + 1 );
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	SetCDSpeed - Calls the SetCDSpeed method
//�����������������������������������������������������������������������������

static void
SetCDSpeed ( MMCDeviceInterface ** interface )
{
	
	SCSI_Sense_Data		senseData	= { 0 };
	SCSITaskStatus		taskStatus	= kSCSITaskStatus_No_Status;
	IOReturn			err			= kIOReturnSuccess;
	
	printf ( "SetCDSpeed: " );
	
	// Issue a SET_CD_SPEED command to the device.
	err = ( *interface )->SetCDSpeed ( interface,
									   0xFFFF,
									   0xFFFF,
									   &taskStatus,
									   &senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "SetCDSpeed failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		printf ( "Set CD Speed successful\n" );
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	ReadFormatCapacities - Calls the ReadFormatCapacities method
//�����������������������������������������������������������������������������

static void
ReadFormatCapacities ( MMCDeviceInterface ** interface )
{
	
	UInt16				index		= 0;
	UInt8				buffer[256] = { 0 };
	SCSI_Sense_Data		senseData	= { 0 };
	SCSITaskStatus		taskStatus	= kSCSITaskStatus_No_Status;
	IOReturn			err			= kIOReturnSuccess;
	
	printf ( "ReadFormatCapacities: " );
	
	// Issue a READ_FORMAT_CAPACITIES command to the device. Ask for a arbitrary 256 bytes.
	err = ( *interface )->ReadFormatCapacities ( interface,
												 buffer,
												 sizeof ( buffer ),
												 &taskStatus,
												 &senseData );
	require_action ( ( err == kIOReturnSuccess ), ErrorExit, printf ( "ReadFormatCapacities failed, err = 0x%08x\n", err ) );
	
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		// Print the data
		printf ( "Read Format Capacities Data\n" );
		
		for ( index = 0; index < sizeof ( buffer ); index++ )
		{
			printf ( "0x%02x : ", buffer[index] );
		}
		
		printf ( "\n" );
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		
		// Something happened. Print the sense string
		PrintSenseString ( &senseData, false );
		
	}
	
	
ErrorExit:
	
	
	printf ( "\n" );
	
}


//�����������������������������������������������������������������������������
//	�	TestSCSITaskDeviceInterface - Tests the other interfaces
//									  (exclusive commands)
//�����������������������������������������������������������������������������

static void
TestSCSITaskDeviceInterface ( SCSITaskDeviceInterface ** interface )
{
	
	// We have exclusive access now. Send a TEST_UNIT_READY command.
	ExclusiveTestUnitReady ( interface );
	
	// Send an INQUIRY command.
	ExclusiveInquiry ( interface );
	
}


//�����������������������������������������������������������������������������
//	�	ExclusiveInquiry - Sends an INQUIRY command to the device
//�����������������������������������������������������������������������������

static void
ExclusiveInquiry ( SCSITaskDeviceInterface ** interface )
{
	
	SCSIServiceResponse				serviceResponse	= kSCSIServiceResponse_Request_In_Process;
	SCSITaskStatus					taskStatus		= kSCSITaskStatus_No_Status;
	SCSICmd_INQUIRY_StandardData	inqBuffer		= { 0 };
	SCSI_Sense_Data					senseData		= { 0 };
	SCSICommandDescriptorBlock		cdb				= { 0 };
	SCSITaskInterface **			task			= NULL;
	IOReturn						err	 			= 0;
	UInt64							transferCount 	= 0;
	UInt32							transferCountHi = 0;
	UInt32							transferCountLo = 0;				
	IOVirtualRange					range;
	
	printf ( "ExclusiveInquiry: " );
	
	// Create a task now that we have exclusive access
	task = ( *interface )->CreateSCSITask ( interface );
	require ( ( task != NULL ), ErrorExit );
	
	// Set up the range. The address is just the buffer's address. The length is our request size.
	range.address = ( IOVirtualAddress ) &inqBuffer;
	range.length  = sizeof ( SCSICmd_INQUIRY_StandardData );
	
	// We're going to execute an INQUIRY to the device as a
	// test of exclusive commands.
	cdb[0] = kSCSICmd_INQUIRY;
	cdb[4] = sizeof ( SCSICmd_INQUIRY_StandardData );
	
	// Set the actual cdb in the task
	err = ( *task )->SetCommandDescriptorBlock ( task, cdb, kSCSICDBSize_6Byte );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Set the scatter-gather entry in the task
	err = ( *task )->SetScatterGatherEntries ( task,
											   &range,
											   1,
											   sizeof ( SCSICmd_INQUIRY_StandardData ),
											   kSCSIDataTransfer_FromTargetToInitiator );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Set the timeout in the task
	err = ( *task )->SetTimeoutDuration ( task, 10000 );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Send it!
	err = ( *task )->ExecuteTaskSync ( task, &senseData, &taskStatus, &transferCount );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Get the SCSI service response
	err = ( *task )->GetSCSIServiceResponse ( task, &serviceResponse );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Get the transfer counts
	transferCountHi = ( ( transferCount >> 32 ) & 0xFFFFFFFF );
	transferCountLo = ( transferCount & 0xFFFFFFFF );
	
	printf ( "serviceResponse = %d, taskStatus = %d\n", serviceResponse, taskStatus );
	printf ( "transferCountHi = 0x%08lx, transferCountLo = 0x%08lx\n", transferCountHi, transferCountLo );
	
	require ( ( serviceResponse == kSCSIServiceResponse_TASK_COMPLETE ), ReleaseTask );

	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		
		char	tmp[kINQUIRY_PRODUCT_IDENTIFICATION_Length + 1];
		
		printf ( "Good Status\n" );
		printf ( "Inquiry Data\n" );
		
		printf ( "Peripheral Device Type = %d\n",
				 inqBuffer.PERIPHERAL_DEVICE_TYPE & kINQUIRY_PERIPHERAL_TYPE_Mask );
		printf ( "Removable Media Bit = %d\n",
				 inqBuffer.RMB & kINQUIRY_PERIPHERAL_RMB_MediumRemovable ? 1 : 0 );
		
		bcopy ( inqBuffer.VENDOR_IDENTIFICATION, tmp, kINQUIRY_VENDOR_IDENTIFICATION_Length );
		tmp[kINQUIRY_VENDOR_IDENTIFICATION_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_VENDOR_IDENTIFICATION_Length );
		printf ( "Vendor Identification = %s\n", tmp );
		
		bcopy ( inqBuffer.PRODUCT_IDENTIFICATION, tmp, kINQUIRY_PRODUCT_IDENTIFICATION_Length );
		tmp[kINQUIRY_PRODUCT_IDENTIFICATION_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_PRODUCT_IDENTIFICATION_Length );		
		printf ( "Product Identification = %s\n", tmp );
		
		bcopy ( inqBuffer.PRODUCT_REVISION_LEVEL, tmp, kINQUIRY_PRODUCT_REVISION_LEVEL_Length );
		tmp[kINQUIRY_PRODUCT_REVISION_LEVEL_Length] = 0;
		StripWhiteSpace ( tmp, kINQUIRY_PRODUCT_REVISION_LEVEL_Length );		
		printf ( "Product Revision Level = %s\n", tmp );
		
		printf ( "\n" );
		
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		PrintSenseString ( &senseData, false );
	}
	
	
ReleaseTask:
	
	
	require_quiet ( ( task != NULL ), ErrorExit );
	( *task )->Release ( task );
	task = NULL;
	
	
ErrorExit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	�	ExclusiveTestUnitReady -  Sense a TEST_UNIT_READY command to the device
//�����������������������������������������������������������������������������

static void
ExclusiveTestUnitReady ( SCSITaskDeviceInterface ** interface )
{
	
	SCSIServiceResponse				serviceResponse	= kSCSIServiceResponse_Request_In_Process;
	SCSITaskStatus					taskStatus		= kSCSITaskStatus_No_Status;
	SCSI_Sense_Data					senseData		= { 0 };
	SCSICommandDescriptorBlock		cdb				= { 0 };
	SCSITaskInterface **			task			= NULL;
	IOReturn						err	 			= 0;
	UInt64							transferCount	= 0;
	
	printf ( "ExclusiveTestUnitReady: " );
	
	// Create a task now that we have exclusive access
	task = ( *interface )->CreateSCSITask ( interface );
	require ( ( task != NULL ), ErrorExit );
	
	// TEST_UNIT_READY is all zeros in the CDB, so we don't actually
	// have to set any values.
	
	// cdb[0] = kSCSICmd_TEST_UNIT_READY;
	
	// Set the actual cdb in the task
	err = ( *task )->SetCommandDescriptorBlock ( task, cdb, kSCSICDBSize_6Byte );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Set the timeout in the task
	err = ( *task )->SetTimeoutDuration ( task, 5000 );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Send it!
	err = ( *task )->ExecuteTaskSync ( task, &senseData, &taskStatus, &transferCount );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	// Get the SCSI service response
	err = ( *task )->GetSCSIServiceResponse ( task, &serviceResponse );
	require ( ( err == kIOReturnSuccess ), ReleaseTask );
	
	printf ( "serviceResponse = %d, taskStatus = %d\n", serviceResponse, taskStatus );
	
	require ( ( serviceResponse == kSCSIServiceResponse_TASK_COMPLETE ), ReleaseTask );
	
	// Task status is not GOOD, print any sense string if they apply.
	if ( taskStatus == kSCSITaskStatus_GOOD )
	{
		printf ( "Good Status, device is ready\n" );
	}
	
	else if ( taskStatus == kSCSITaskStatus_CHECK_CONDITION )
	{
		PrintSenseString ( &senseData, false );	
	}
	
	
ReleaseTask:
	
	
	require_quiet ( ( task != NULL ), ErrorExit );
	( *task )->Release ( task );
	task = NULL;
	
	
ErrorExit:
	
	
	return;
	
}


//�����������������������������������������������������������������������������
//	�	PrintSenseString -  Prints out meaningful string corresponding to sense
//							data SENSE_KEY, ASC, and ASCQ
//�����������������������������������������������������������������������������

static void
PrintSenseString ( SCSI_Sense_Data * sense, Boolean addRawValues )
{
	
	char	str[256];
	UInt8	key, ASC, ASCQ;
	
	key 	= sense->SENSE_KEY & 0x0F;
	ASC 	= sense->ADDITIONAL_SENSE_CODE;
	ASCQ 	= sense->ADDITIONAL_SENSE_CODE_QUALIFIER;
	
	if ( addRawValues )
	{
	
		sprintf ( str, "Key: $%02x, ASC: $%02x, ASCQ: $%02x  ", key, ASC, ASCQ );
	
	}
	else
		str[0] = '\0';
	
	switch ( key )
	{
	
		case 0x0: 	strcat ( str, "No Sense" ); break;
		case 0x1: 	strcat ( str, "Recovered Error" ); break;
		case 0x2: 	strcat ( str, "Not Ready" ); break;
		case 0x3: 	strcat ( str, "Medium Error" ); break;
		case 0x4: 	strcat ( str, "Hardware Error" ); break;
		case 0x5: 	strcat ( str, "Illegal Request" ); break;
		case 0x6: 	strcat ( str, "Unit Attention" ); break;
		case 0x7: 	strcat ( str, "Data Protect" ); break;
		case 0x8: 	strcat ( str, "Blank Check" ); break;
		case 0x9: 	strcat ( str, "Vendor-Specific" ); break;
		case 0xA: 	strcat ( str, "Copy Aborted" ); break;
		case 0xB: 	strcat ( str, "Aborted Command" ); break;
		case 0xC: 	strcat ( str, "Equal (now obsolete)" ); break;
		case 0xD: 	strcat ( str, "Volume Overflow" ); break;
		case 0xE: 	strcat ( str, "Miscompare" ); break;
		default: 	strcat ( str, "Unknown Sense Code" ); break;
	
	}
	
	strcat ( str, ", " );
	
	switch ( ( ( UInt16 ) ASC << 8 ) | ASCQ )
	{
		
		case 0x0000: strcat ( str, "No additional sense information" ); break;
		case 0x0001: strcat ( str, "Filemark detected" ); break;
		case 0x0002: strcat ( str, "End of partition/medium detected" ); break;
		case 0x0003: strcat ( str, "Setmark detected" ); break;
		case 0x0004: strcat ( str, "Beginning of partition/medium detected" ); break;
		case 0x0005: strcat ( str, "End of data detected" ); break;
		case 0x0006: strcat ( str, "I/O process termination" ); break;
		case 0x0011: strcat ( str, "Play operation in progress" ); break;
		case 0x0012: strcat ( str, "Play operation paused" ); break;
		case 0x0013: strcat ( str, "Play operation successfully completed" ); break;
		case 0x0014: strcat ( str, "Play operation stopped due to error" ); break;
		case 0x0015: strcat ( str, "No current audio status to return" ); break;
		case 0x0016: strcat ( str, "Operation in progress" ); break;
		case 0x0017: strcat ( str, "Cleaning requested" ); break;
		case 0x0100: strcat ( str, "Mechanical positioning or changer error" ); break;
		case 0x0200: strcat ( str, "No seek complete" ); break;
		case 0x0300: strcat ( str, "Peripheral device write fault" ); break;
		case 0x0301: strcat ( str, "No write current" ); break;
		case 0x0302: strcat ( str, "Excessive write errors" ); break;
		case 0x0400: strcat ( str, "Logical unit not ready, cause not reportable" ); break;
		case 0x0401: strcat ( str, "Logical unit not ready, in process of becoming ready" ); break;
		case 0x0402: strcat ( str, "Logical unit not ready, initializing command required" ); break;
		case 0x0403: strcat ( str, "Logical unit not ready, manual intervention required" ); break;
		case 0x0404: strcat ( str, "Logical unit not ready, format in progress" ); break;
		case 0x0407: strcat ( str, "Logical unit not ready, operation in progress" ); break;
		case 0x0408: strcat ( str, "Logical unit not ready, long write in progress" ); break;
		case 0x0409: strcat ( str, "Logical unit not ready, self-test in progress" ); break;
		case 0x0500: strcat ( str, "Logical unit does not respond to selection" ); break;
		case 0x0501: strcat ( str, "Media load - Eject failed" ); break;
		case 0x0600: strcat ( str, "No reference position found" ); break;
		case 0x0700: strcat ( str, "Multiple peripheral devices selected" ); break;
		case 0x0800: strcat ( str, "Logical unit communication failure" ); break;
		case 0x0801: strcat ( str, "Logical unit communication time-out" ); break;
		case 0x0802: strcat ( str, "Logical unit communication parity error" ); break;
		case 0x0803: strcat ( str, "Logical unit communication CRC error (Ultra-DMA/32)" ); break;
		case 0x0804: strcat ( str, "Unreachable copy target" ); break;
		case 0x0900: strcat ( str, "Track following error" ); break;
		case 0x0901: strcat ( str, "Tracking servo failure" ); break;
		case 0x0902: strcat ( str, "Focus servo failure" ); break;
		case 0x0903: strcat ( str, "Spindle servo failure" ); break;
		case 0x0904: strcat ( str, "Head select fault" ); break;
		case 0x0A00: strcat ( str, "Error log overflow" ); break;
		case 0x0B00: strcat ( str, "Warning" ); break;
		case 0x0B01: strcat ( str, "Warning, specified temperature exceeded" ); break;
		case 0x0B02: strcat ( str, "Warning, enclosure degraded" ); break;
		case 0x0C00: strcat ( str, "Write error" ); break;
		case 0x0C01: strcat ( str, "Write error, recovered with auto reallocation" ); break;
		case 0x0C02: strcat ( str, "Write error, auto reallocation failed" ); break;
		case 0x0C03: strcat ( str, "Write error, recommend reassignment" ); break;
		case 0x0C04: strcat ( str, "Compression check miscompare error" ); break;
		case 0x0C05: strcat ( str, "Data expansion occurred during compression" ); break;
		case 0x0C06: strcat ( str, "Block not compressible" ); break;
		case 0x0C07: strcat ( str, "Write error, recovery needed" ); break;
		case 0x0C08: strcat ( str, "Write error, recovery failed" ); break;
		case 0x0C09: strcat ( str, "Write error, loss of streaming" ); break;
		case 0x0C0A: strcat ( str, "Write error, padding blocks added" ); break;
		case 0x1000: strcat ( str, "ID, CRC or ECC error" ); break;
		case 0x1100: strcat ( str, "Unrecovered read error" ); break;
		case 0x1101: strcat ( str, "Read retries exhausted" ); break;
		case 0x1102: strcat ( str, "Error too long to correct" ); break;
		case 0x1103: strcat ( str, "Multiple read errors" ); break;
		case 0x1104: strcat ( str, "Unrecovered read error - auto reallocate failed" ); break;
		case 0x1105: strcat ( str, "L-EC uncorrectable error" ); break;
		case 0x1106: strcat ( str, "CIRC unrecovered error" ); break;
		case 0x1107: strcat ( str, "Re-synchronization error" ); break;
		case 0x1108: strcat ( str, "Incomplete block read" ); break;
		case 0x1109: strcat ( str, "No gap found" ); break;
		case 0x110A: strcat ( str, "Miscorrected error" ); break;
		case 0x110B: strcat ( str, "Unrecovered read error - recommend reassignment" ); break;
		case 0x110C: strcat ( str, "Unrecovered read error - recommend rewrite the data" ); break;
		case 0x110D: strcat ( str, "De-compression CRC error" ); break;
		case 0x110E: strcat ( str, "Cannot decompress using declared algorithm" ); break;
		case 0x110F: strcat ( str, "Error reading UPC/EAN number" ); break;
		case 0x1110: strcat ( str, "Error reading ISRC number" ); break;
		case 0x1111: strcat ( str, "Read error, loss of streaming" ); break;
		case 0x1200: strcat ( str, "Address mark not found for ID field" ); break;
		case 0x1300: strcat ( str, "Address mark not found for data field" ); break;
		case 0x1400: strcat ( str, "Recorded entity not found" ); break;
		case 0x1401: strcat ( str, "Record not found" ); break;
		case 0x1402: strcat ( str, "Filemark or setmark not found" ); break;
		case 0x1403: strcat ( str, "End of data not found" ); break;
		case 0x1404: strcat ( str, "Block sequence error" ); break;
		case 0x1405: strcat ( str, "Record not found - recommend reassignment" ); break;
		case 0x1406: strcat ( str, "Record not found - data auto-reallocated" ); break;
		case 0x1500: strcat ( str, "Random positioning error" ); break;
		case 0x1501: strcat ( str, "Mechanical positioning or changer error" ); break;
		case 0x1502: strcat ( str, "Positioning error detected by read of medium" ); break;
		case 0x1600: strcat ( str, "Data synchronization mark error" ); break;
		case 0x1601: strcat ( str, "Data sync error - data rewritten" ); break;
		case 0x1602: strcat ( str, "Data sync error - recommend rewrite" ); break;
		case 0x1603: strcat ( str, "Data sync error - data auto-reallocated" ); break;
		case 0x1604: strcat ( str, "Data sync error - recommend reassignment" ); break;
		case 0x1700: strcat ( str, "Recovered data with no error correction applied" ); break;
		case 0x1701: strcat ( str, "Recovered data with retries" ); break;
		case 0x1702: strcat ( str, "Recovered data with positive head offset" ); break;
		case 0x1703: strcat ( str, "Recovered data with negative head offset" ); break;
		case 0x1704: strcat ( str, "Recovered data with retries and/or CIRC applied" ); break;
		case 0x1705: strcat ( str, "Recovered data using previous sector ID" ); break;
		case 0x1706: strcat ( str, "Recovered data without ECC, data auto-reallocated" ); break;
		case 0x1707: strcat ( str, "Recovered data without ECC, recommend reassignment" ); break;
		case 0x1708: strcat ( str, "Recovered data without ECC, recommend rewrite" ); break;
		case 0x1709: strcat ( str, "Recivered data without ECC, data rewritten" ); break;
		case 0x1800: strcat ( str, "Recovered data with error correction applied" ); break;
		case 0x1801: strcat ( str, "Recovered data with error correction & retries applied" ); break;
		case 0x1802: strcat ( str, "Recovered data, the data was auto-reallocated" ); break;
		case 0x1803: strcat ( str, "Recovered data with CIRC" ); break;
		case 0x1804: strcat ( str, "Recovered data with L-EC" ); break;
		case 0x1805: strcat ( str, "Recovered data, recommend reassignment" ); break;
		case 0x1806: strcat ( str, "Recovered data, recommend rewrite" ); break;
		case 0x1807: strcat ( str, "Recovered data with ECC, data rewritten" ); break;
		case 0x1808: strcat ( str, "Recovered data with linking" ); break;
		case 0x1900: strcat ( str, "Defect list error" ); break;
		case 0x1901: strcat ( str, "Defect list not available" ); break;
		case 0x1902: strcat ( str, "Defect list error in primary list" ); break;
		case 0x1903: strcat ( str, "Defect list error in grown list" ); break;
		case 0x1A00: strcat ( str, "Parameter list length error" ); break;
		case 0x1B00: strcat ( str, "Synchronous data transfer error" ); break;
		case 0x1C00: strcat ( str, "Defect list not found" ); break;
		case 0x1C01: strcat ( str, "Primary defect list not found" ); break;
		case 0x1C02: strcat ( str, "Grown defect list not found" ); break;
		case 0x1D00: strcat ( str, "Miscompare during verify operation" ); break;
		case 0x1E00: strcat ( str, "Recovered ID with ECC correction" ); break;
		case 0x1F00: strcat ( str, "Partial defect list transfer" ); break;
		case 0x2000: strcat ( str, "Invalid command operation code" ); break;
		case 0x2100: strcat ( str, "Logical block address out of range" ); break;
		case 0x2101: strcat ( str, "Invalid element address" ); break;
		case 0x2102: strcat ( str, "Invalid address for write" ); break;
		case 0x2200: strcat ( str, "Illegal function" ); break;
		case 0x2400: strcat ( str, "Invalid field in CDB" ); break;
		case 0x2401: strcat ( str, "CDB decryption error" ); break;
		case 0x2500: strcat ( str, "Logical unit not supported" ); break;
		case 0x2600: strcat ( str, "Invalid field in parameter list" ); break;
		case 0x2601: strcat ( str, "Parameter not supported" ); break;
		case 0x2602: strcat ( str, "Parameter value invalid" ); break;
		case 0x2603: strcat ( str, "Threshold parameters not supported" ); break;
		case 0x2604: strcat ( str, "Invalid release of active persistent reservation" ); break;
		case 0x2605: strcat ( str, "Data decryption error" ); break;
		case 0x2606: strcat ( str, "Too many target descriptors" ); break;
		case 0x2607: strcat ( str, "Unsupported target descriptor type code" ); break;
		case 0x2608: strcat ( str, "Too many segment descriptors" ); break;
		case 0x2609: strcat ( str, "Unsupported segment descriptor type code" ); break;
		case 0x260A: strcat ( str, "Unexpected inexact segment" ); break;
		case 0x260B: strcat ( str, "Inline data length exceeded" ); break;
		case 0x260C: strcat ( str, "Invalid operation for copy source or destination" ); break;
		case 0x260D: strcat ( str, "Copy segment granularity violation" ); break;
		case 0x2700: strcat ( str, "Write protected" ); break;
		case 0x2701: strcat ( str, "Hardware write protected" ); break;
		case 0x2702: strcat ( str, "Logical unit software write protected" ); break;
		case 0x2703: strcat ( str, "Associated write protect" ); break;
		case 0x2704: strcat ( str, "Persistent write protect" ); break;
		case 0x2705: strcat ( str, "Permanent write protect" ); break;
		case 0x2800: strcat ( str, "Not ready to ready transition, medium may have changed" ); break;
		case 0x2801: strcat ( str, "Import or export element accessed" ); break;
		case 0x2900: strcat ( str, "Power on, reset or bus device reset occurred" ); break;
		case 0x2901: strcat ( str, "Power on occured" ); break;
		case 0x2902: strcat ( str, "SCSI bus reset occurred" ); break;
		case 0x2903: strcat ( str, "Bus device reset function occurred" ); break;
		case 0x2904: strcat ( str, "Device internal reset" ); break;
		case 0x2905: strcat ( str, "Transceiver mode changed to single-ended" ); break;
		case 0x2906: strcat ( str, "Transceiver mode changed to LVD" ); break;
		case 0x2A00: strcat ( str, "Parameters changed" ); break;
		case 0x2A01: strcat ( str, "Mode parameters changed" ); break;
		case 0x2A02: strcat ( str, "Log parameters changed" ); break;
		case 0x2A03: strcat ( str, "Reservations preempted" ); break;
		case 0x2A04: strcat ( str, "Reservations released" ); break;
		case 0x2A05: strcat ( str, "Registrations preempted" ); break;
		case 0x2B00: strcat ( str, "Copy cannot execute since host cannot disconnect" ); break;
		case 0x2C00: strcat ( str, "Command sequence error" ); break;
		case 0x2C01: strcat ( str, "Too many windows specified" ); break;
		case 0x2C02: strcat ( str, "Invalid combination of windows specified" ); break;
		case 0x2C03: strcat ( str, "Current program area is not empty" ); break;
		case 0x2C04: strcat ( str, "Current program area is empty" ); break;
		case 0x2C05: strcat ( str, "Persistent prevent conflict" ); break;
		case 0x2D00: strcat ( str, "Overwrite error on update in place" ); break;
		case 0x2E00: strcat ( str, "Insufficient time for operation" ); break;
		case 0x2F00: strcat ( str, "Commands cleared by anther initiator" ); break;
		case 0x3000: strcat ( str, "Incompatible medium installed" ); break;
		case 0x3001: strcat ( str, "Cannot read medium, unknown format" ); break;
		case 0x3002: strcat ( str, "Cannot read medium, incompatible format" ); break;
		case 0x3003: strcat ( str, "Cleaning cartridge installed" ); break;
		case 0x3004: strcat ( str, "Cannot write medium, unknown format" ); break;
		case 0x3005: strcat ( str, "Cannot write medium, incompatible format" ); break;
		case 0x3006: strcat ( str, "Cannot format medium, incompatible medium" ); break;
		case 0x3007: strcat ( str, "Cleaning failure" ); break;
		case 0x3008: strcat ( str, "Cannot write, application code mismatch" ); break;
		case 0x3009: strcat ( str, "Current session not fixated for append" ); break;
		case 0x3100: strcat ( str, "Medium format corrupted" ); break;
		case 0x3101: strcat ( str, "Format command failed" ); break;
		case 0x3102: strcat ( str, "Zoned formatting failed due to spare linking" ); break;
		case 0x3200: strcat ( str, "No defect spare location available" ); break;
		case 0x3201: strcat ( str, "Defect list update failure" ); break;
		case 0x3300: strcat ( str, "Tape length error" ); break;
		case 0x3400: strcat ( str, "Enclosure failure" ); break;
		case 0x3500: strcat ( str, "Enclosure services failure" ); break;
		case 0x3501: strcat ( str, "Unsupported enclosure function" ); break;
		case 0x3502: strcat ( str, "Enclosure services unavailable" ); break;
		case 0x3503: strcat ( str, "Enclosure services transfer failure" ); break;
		case 0x3504: strcat ( str, "Enclosure services transfer refused" ); break;
		case 0x3600: strcat ( str, "Ribbon, ink, or toner failure" ); break;
		case 0x3700: strcat ( str, "Rounded parameter" ); break;
		case 0x3800: strcat ( str, "Event status notification" ); break;
		case 0x3802: strcat ( str, "ESN - Power management class event" ); break;
		case 0x3804: strcat ( str, "ESN - Media class event" ); break;
		case 0x3806: strcat ( str, "ESN - Device busy class event" ); break;
		case 0x3900: strcat ( str, "Saving parameters not supported" ); break;
		case 0x3A00: strcat ( str, "Medium not present" ); break;
		case 0x3A01: strcat ( str, "Medium not present, tray closed" ); break;
		case 0x3A02: strcat ( str, "Medium not present, tray open" ); break;
		case 0x3A03: strcat ( str, "Medium not present, loadable" ); break;
		case 0x3A04: strcat ( str, "Medium not present, medium auxiliary memory accessible" ); break;
		case 0x3B00: strcat ( str, "Sequential positioning error" ); break;
		case 0x3B01: strcat ( str, "Tape position error at beginning of medium" ); break;
		case 0x3B02: strcat ( str, "Tape position error at end of medium" ); break;
		case 0x3B03: strcat ( str, "Tape or electronic vertical forms unit not ready" ); break;
		case 0x3B04: strcat ( str, "Slew failure" ); break;
		case 0x3B05: strcat ( str, "Paper jam" ); break;
		case 0x3B06: strcat ( str, "Failed to sense top-of-form" ); break;
		case 0x3B07: strcat ( str, "Failed to sense bottom-of-form" ); break;
		case 0x3B08: strcat ( str, "Reposition error" ); break;
		case 0x3B09: strcat ( str, "Read past end of medium" ); break;
		case 0x3B0A: strcat ( str, "Read past beginning of medium" ); break;
		case 0x3B0B: strcat ( str, "Position past end of medium" ); break;
		case 0x3B0C: strcat ( str, "Position past beginning of medium" ); break;
		case 0x3B0D: strcat ( str, "Medium destination element full" ); break;
		case 0x3B0E: strcat ( str, "Medium source element empty" ); break;
		case 0x3B0F: strcat ( str, "End of medium reached" ); break;
		case 0x3B11: strcat ( str, "Medium magazine not accessible" ); break;
		case 0x3B12: strcat ( str, "Medium magazine removed" ); break;
		case 0x3B13: strcat ( str, "Medium magazine inserted" ); break;
		case 0x3B14: strcat ( str, "Medium magazine locked" ); break;
		case 0x3B15: strcat ( str, "Medium magazine unlocked" ); break;
		case 0x3B16: strcat ( str, "Mechanical positioning or changer error" ); break;
		case 0x3D00: strcat ( str, "Invalid bits in identify message" ); break;
		case 0x3E00: strcat ( str, "Logical unit has not self-configured yet" ); break;
		case 0x3E01: strcat ( str, "Logical unit failure" ); break;
		case 0x3E02: strcat ( str, "Timeout on logical unit" ); break;
		case 0x3E03: strcat ( str, "Logical unit failed self-test" ); break;
		case 0x3E04: strcat ( str, "Logical unit unable to update self-test log" ); break;
		case 0x3F00: strcat ( str, "Target operating conditions have changed" ); break;
		case 0x3F01: strcat ( str, "Microcode has been changed" ); break;
		case 0x3F02: strcat ( str, "Changed operating definition" ); break;
		case 0x3F03: strcat ( str, "Inquiry data has changed" ); break;
		case 0x3F04: strcat ( str, "Component device attached" ); break;
		case 0x3F05: strcat ( str, "Device identifier changed" ); break;
		case 0x3F06: strcat ( str, "Redundancy group created or modified" ); break;
		case 0x3F07: strcat ( str, "Redundancy group deleted" ); break;
		case 0x3F08: strcat ( str, "Spare created or modified" ); break;
		case 0x3F09: strcat ( str, "Spare deleted" ); break;
		case 0x3F0A: strcat ( str, "Volume set created or modified" ); break;
		case 0x3F0B: strcat ( str, "Volume set deleted" ); break;
		case 0x3F0C: strcat ( str, "Volume set deassigned" ); break;
		case 0x3F0D: strcat ( str, "Volume set reassigned" ); break;
		case 0x3F0E: strcat ( str, "Reported LUNs data has changed" ); break;
		case 0x3F10: strcat ( str, "Medium loadable" ); break;
		case 0x3F11: strcat ( str, "Medium auxiliary memory accessible" ); break;
		case 0x4000: strcat ( str, "RAM failure" ); break;
		case 0x4100: strcat ( str, "Data path failure" ); break;
		case 0x4200: strcat ( str, "Power-on or self-test failure" ); break;
		case 0x4300: strcat ( str, "Message error" ); break;
		case 0x4400: strcat ( str, "Internal target failure" ); break;
		case 0x4500: strcat ( str, "Select or reselect failure" ); break;
		case 0x4600: strcat ( str, "Unseccessful soft reset" ); break;
		case 0x4700: strcat ( str, "SCSI Parity error" ); break;
		case 0x4701: strcat ( str, "Data phase CRC error detected" ); break;
		case 0x4702: strcat ( str, "SCSI parity error detected during ST data phase" ); break;
		case 0x4703: strcat ( str, "Information unit CRC error detected" ); break;
		case 0x4704: strcat ( str, "Async information protection error detected" ); break;
		case 0x4800: strcat ( str, "Initiator detected error message received" ); break;
		case 0x4900: strcat ( str, "Invalid message error" ); break;
		case 0x4A00: strcat ( str, "Command phase error" ); break;
		case 0x4B00: strcat ( str, "Data phase error" ); break;
		case 0x4C00: strcat ( str, "Logical unit failed self-configuration" ); break;
		case 0x4E00: strcat ( str, "Overlapped commands attempted" ); break;
		case 0x5000: strcat ( str, "Write append error" ); break;
		case 0x5001: strcat ( str, "Write append position error" ); break;
		case 0x5002: strcat ( str, "Position error related to timing" ); break;
		case 0x5100: strcat ( str, "Erase failure" ); break;
		case 0x5300: strcat ( str, "Media load or eject failed" ); break;
		case 0x5301: strcat ( str, "Unload tape failure" ); break;
		case 0x5302: strcat ( str, "Medium removal prevented" ); break;
		case 0x5400: strcat ( str, "SCSI to host system interface failure" ); break;
		case 0x5500: strcat ( str, "System Resource failure" ); break;
		case 0x5501: strcat ( str, "System Buffer full" ); break;
		case 0x5502: strcat ( str, "Insufficient reservation resources" ); break;
		case 0x5503: strcat ( str, "Insufficient resources" ); break;
		case 0x5504: strcat ( str, "Insufficient registration resources" ); break;
		case 0x5700: strcat ( str, "Unable to recover table of contents" ); break;
		case 0x5800: strcat ( str, "Generation does not exist" ); break;
		case 0x5900: strcat ( str, "Updated block read" ); break;
		case 0x5A00: strcat ( str, "Operator request or state change input (UNSPECIFIED)" ); break;
		case 0x5A01: strcat ( str, "Operator medium removal request" ); break;
		case 0x5A02: strcat ( str, "Operator selected write protect" ); break;
		case 0x5A03: strcat ( str, "Operator selected write permit" ); break;
		case 0x5B00: strcat ( str, "Log exception" ); break;
		case 0x5B01: strcat ( str, "Threshold condition met" ); break;
		case 0x5B02: strcat ( str, "Log counter at maximum" ); break;
		case 0x5B03: strcat ( str, "Log list codes exhausted" ); break;
		case 0x5C00: strcat ( str, "RPL status change" ); break;
		case 0x5C01: strcat ( str, "Spindles synchronized" ); break;
		case 0x5C02: strcat ( str, "Spindle not synchronized" ); break;
		case 0x5D00: strcat ( str, "Failure prediction threshold exceeded, predicted logical unit failure" ); break;
		case 0x5D01: strcat ( str, "Failure prediction threshold exceeded, predicted media failure" ); break;
		case 0x5D10: strcat ( str, "Hardware impending failure - general hard drive failure" ); break;
		case 0x5D11: strcat ( str, "Hardware impending failure - drive error rate too high" ); break;
		case 0x5D12: strcat ( str, "Hardware impending failure - data error rate too high" ); break;
		case 0x5D13: strcat ( str, "Hardware impending failure - seek error rate too high" ); break;
		case 0x5D14: strcat ( str, "Hardware impending failure - too many block reassigns" ); break;
		case 0x5D15: strcat ( str, "Hardware impending failure - access times too high" ); break;
		case 0x5D16: strcat ( str, "Hardware impending failure - start unit times too high" ); break;
		case 0x5D17: strcat ( str, "Hardware impending failure - channel parametrics" ); break;
		case 0x5D18: strcat ( str, "Hardware impending failure - controller detected" ); break;
		case 0x5D19: strcat ( str, "Hardware impending failure - throughput performance" ); break;
		case 0x5D1A: strcat ( str, "Hardware impending failure - seek time performance" ); break;
		case 0x5D1B: strcat ( str, "Hardware impending failure - spin-up retry count" ); break;
		case 0x5D1C: strcat ( str, "Hardware impending failure - drive calibration retry count" ); break;
		case 0x5D20: strcat ( str, "Controller impending failure - general hard drive failure" ); break;
		case 0x5D21: strcat ( str, "Controller impending failure - drive error rate too high" ); break;
		case 0x5D22: strcat ( str, "Controller impending failure - data error rate too high" ); break;
		case 0x5D23: strcat ( str, "Controller impending failure - seek error rate too high" ); break;
		case 0x5D24: strcat ( str, "Controller impending failure - too many block reassigns" ); break;
		case 0x5D25: strcat ( str, "Controller impending failure - access times too high" ); break;
		case 0x5D26: strcat ( str, "Controller impending failure - start unit times too high" ); break;
		case 0x5D27: strcat ( str, "Controller impending failure - channel parametrics" ); break;
		case 0x5D28: strcat ( str, "Controller impending failure - controller detected" ); break;
		case 0x5D29: strcat ( str, "Controller impending failure - throughput performance" ); break;
		case 0x5D2A: strcat ( str, "Controller impending failure - seek time performance" ); break;
		case 0x5D2B: strcat ( str, "Controller impending failure - spin-up retry count" ); break;
		case 0x5D2C: strcat ( str, "Controller impending failure - drive calibration retry count" ); break;
		case 0x5DFF: strcat ( str, "Failure prediction threshold exceeded (FALSE)" ); break;
		case 0x5E00: strcat ( str, "Low power condition on" ); break;
		case 0x5E01: strcat ( str, "Idle condition activated by timer" ); break;
		case 0x5E02: strcat ( str, "Standby condition activated by timer" ); break;
		case 0x5E03: strcat ( str, "Idle condition activated by command" ); break;
		case 0x5E04: strcat ( str, "Standby condition activated by command" ); break;
		case 0x5E41: strcat ( str, "Power state change to active" ); break;
		case 0x5E42: strcat ( str, "Power state change to idle" ); break;
		case 0x5E43: strcat ( str, "Power state change to standby" ); break;
		case 0x5E45: strcat ( str, "Power state change to sleep" ); break;
		case 0x5E47: strcat ( str, "Power state change to device control" ); break;
		case 0x6000: strcat ( str, "Lamp failure" ); break;
		case 0x6100: strcat ( str, "Video acquisition error" ); break;
		case 0x6101: strcat ( str, "Unable to acquire video" ); break;
		case 0x6102: strcat ( str, "Out of focus" ); break;
		case 0x6200: strcat ( str, "Scan head positioning error" ); break;
		case 0x6300: strcat ( str, "End of user area encountered on this track" ); break;
		case 0x6301: strcat ( str, "Packet does not fit in available space" ); break;
		case 0x6400: strcat ( str, "Illegal mode for this track or incompatible medium" ); break;
		case 0x6401: strcat ( str, "Invalid packet size" ); break;
		case 0x6500: strcat ( str, "Voltage fault" ); break;
		case 0x6600: strcat ( str, "Automatic document feeder cover up" ); break;
		case 0x6601: strcat ( str, "Automatic document feeder lift up" ); break;
		case 0x6602: strcat ( str, "Document jam in automatic document feeder" ); break;
		case 0x6603: strcat ( str, "Document misfeed in automatic document feeder" ); break;
		case 0x6700: strcat ( str, "Configuration failure" ); break;
		case 0x6701: strcat ( str, "Configuration of incapable logical unit" ); break;
		case 0x6702: strcat ( str, "Add logical unit failed" ); break;
		case 0x6703: strcat ( str, "Modification of logical unit failed" ); break;
		case 0x6704: strcat ( str, "Exchange of logical unit failed" ); break;
		case 0x6705: strcat ( str, "Remove of logical unit failed" ); break;
		case 0x6706: strcat ( str, "Attachment of logical unit failed" ); break;
		case 0x6707: strcat ( str, "Creation of logical unit failed" ); break;
		case 0x6800: strcat ( str, "Logical unit not configured" ); break;
		case 0x6900: strcat ( str, "Data loss on logical unit" ); break;
		case 0x6901: strcat ( str, "Multiple logical unit failures" ); break;
		case 0x6902: strcat ( str, "A parity/data mismatch" ); break;
		case 0x6A00: strcat ( str, "Informational, refer to log" ); break;
		case 0x6B00: strcat ( str, "State change has occurred" ); break;
		case 0x6B01: strcat ( str, "Redundancy level got better" ); break;
		case 0x6B02: strcat ( str, "Redundancy level got worse" ); break;
		case 0x6C00: strcat ( str, "Rebuild failure occurred" ); break;
		case 0x6D00: strcat ( str, "Recalculate failure occurred" ); break;
		case 0x6E00: strcat ( str, "Command to logical unit failed" ); break;
		case 0x6F00: strcat ( str, "Copy protection key exchange failure, authentication failure" ); break;
		case 0x6F01: strcat ( str, "Copy protection key exchange failure, key not present" ); break;
		case 0x6F02: strcat ( str, "Copy protection key exchange failure, key not established" ); break;
		case 0x6F03: strcat ( str, "Read of scrambled sector without authentication" ); break;
		case 0x6F04: strcat ( str, "Media region code is mismatched to logical unit region" ); break;
		case 0x6F05: strcat ( str, "Drive region must be permanent/Region reset count error" ); break;
		case 0x7100: strcat ( str, "Decompression exception long algorithm id" ); break;
		case 0x7200: strcat ( str, "Session fixation error" ); break;
		case 0x7201: strcat ( str, "Session fixation error writing lead-in" ); break;
		case 0x7202: strcat ( str, "Session fixation error writing lead-out" ); break;
		case 0x7203: strcat ( str, "Session fixation error, incomplete track in session" ); break;
		case 0x7204: strcat ( str, "Empty or partially written reserved track" ); break;
		case 0x7205: strcat ( str, "No more RZone reservations are allowed" ); break;
		case 0x7300: strcat ( str, "CD control error" ); break;
		case 0x7301: strcat ( str, "Power calibration area almost full" ); break;
		case 0x7302: strcat ( str, "Power calibration area is full" ); break;
		case 0x7303: strcat ( str, "Power calibration area error" ); break;
		case 0x7304: strcat ( str, "Program memory area update failure" ); break;
		case 0x7305: strcat ( str, "Program memory area is full" ); break;
		case 0x7306: strcat ( str, "Program memory area is (almost) full" ); break;
		case 0xB900: strcat ( str, "Play operation aborted" ); break;
		case 0xBF00: strcat ( str, "Loss of streaming" ); break;
		default:
			if ( ASC == 0x40 ) { sprintf ( str, "Diagnostic failure on component $%02x", ASCQ ); break; }
			if ( ASC == 0x4D ) { sprintf ( str, "Tagged overlapped commands, queue tag = $%02x", ASCQ ); break; }
			break;
	}
	
	printf("%s\n", str);
	
}


//�����������������������������������������������������������������������������
//	�	DeviceAppeared -  Callback for when a new device appears
//�����������������������������������������������������������������������������

static void
DeviceAppeared ( void * refCon, io_iterator_t iterator )
{

#pragma unused ( refCon )

	io_service_t	obj	= MACH_PORT_NULL;
	
	obj = IOIteratorNext ( iterator );
	
	while ( obj != MACH_PORT_NULL )
	{
		
		printf ( "Device appeared.\n" );
		TestDevice ( obj );
		( void ) IOObjectRelease ( obj );
		obj = IOIteratorNext ( iterator );
		
	}
	
}


//�����������������������������������������������������������������������������
//	�	DeviceDisappeared -  Callback for when a device disappears
//�����������������������������������������������������������������������������

static void
DeviceDisappeared ( void * refCon, io_iterator_t iterator )
{

#pragma unused ( refCon )

	io_service_t	obj	= MACH_PORT_NULL;
	
	obj = IOIteratorNext ( iterator );
	
	while ( obj != MACH_PORT_NULL )
	{
		
		printf ( "Device disappeared.\n" );
		( void ) IOObjectRelease ( obj );
		obj = IOIteratorNext ( iterator );
		
	}
	
}


//�����������������������������������������������������������������������������
//	�	StripWhiteSpace -  Strips whitespace characters from the end of a string
//�����������������������������������������������������������������������������

static void
StripWhiteSpace ( char * buffer, SInt32 length )
{
	
	SInt32		index = 0;
	
	for ( index = ( length - 1 ); index >= 0; index-- )
	{
		
		if ( buffer[index] != ' ' )
			break;
		
		buffer[index] = 0;
		
	}
	
}


//�����������������������������������������������������������������������������
//	�	SignalHandler -  Callback for signal handling
//�����������������������������������������������������������������������������

static void
SignalHandler ( int sigraised )
{

#pragma unused ( sigraised )
	
	printf ( "\nInterrupted\n" );
	
	// Clean up here
	IONotificationPortDestroy ( gNotifyPort );
	
	if ( gAppearedIter )
	{
		
		IOObjectRelease ( gAppearedIter );
		gAppearedIter = 0;
		
	}
	
	if ( gDisappearedIter )
	{
		
		IOObjectRelease ( gDisappearedIter );
		gDisappearedIter = 0;
		
	}
	
	_exit ( 0 );
	
}
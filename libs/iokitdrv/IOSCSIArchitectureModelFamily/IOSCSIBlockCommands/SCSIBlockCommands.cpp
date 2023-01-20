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

// SCSI Architecture Model Family includes
#include <IOKit/scsi/SCSICommandOperationCodes.h>
#include "SCSIBlockCommands.h"


//�����������������������������������������������������������������������������
//	Macros
//�����������������������������������������������������������������������������

#define DEBUG 									0
#define DEBUG_ASSERT_COMPONENT_NAME_STRING		"SBC Command Set"

#if DEBUG
#define SCSI_SBC_COMMANDS_DEBUGGING_LEVEL		0
#endif


#include "IOSCSIArchitectureModelFamilyDebugging.h"


#if ( SCSI_SBC_COMMANDS_DEBUGGING_LEVEL >= 1 )
#define PANIC_NOW(x)		IOPanic x
#else
#define PANIC_NOW(x)
#endif

#if ( SCSI_SBC_COMMANDS_DEBUGGING_LEVEL >= 2 )
#define ERROR_LOG(x)		IOLog x
#else
#define ERROR_LOG(x)
#endif

#if ( SCSI_SBC_COMMANDS_DEBUGGING_LEVEL >= 3 )
#define STATUS_LOG(x)		IOLog x
#else
#define STATUS_LOG(x)
#endif


#define super SCSIPrimaryCommands
OSDefineMetaClassAndStructors ( SCSIBlockCommands, SCSIPrimaryCommands );


#if 0
#pragma mark -
#pragma mark SBC Command Methods
#pragma mark -
#endif


// SCSI Block Commands as defined in T10:990D SBC, Revision 8c,
// dated 13 November 1997

//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::ERASE_10
//
//�����������������������������������������������������������������������������
//		
//		The ERASE(10) command as defined in section 6.2.1
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::ERASE_10 (
				SCSITask *					request,
				SCSICmdField1Bit 			ERA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::ERASE_10 called\n" ) );

	require ( IsParameterValid ( ERA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS,
								 kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH,
								 kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_ERASE_10,
								( ERA << 2 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS 		& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 ) & 0xFF,
								  TRANSFER_LENGTH		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
								0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::ERASE_12
//
//�����������������������������������������������������������������������������
//		
//		The ERASE(12) command as defined in section 6.2.2
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::ERASE_12 (
				SCSITask *					request,
				SCSICmdField1Bit 			ERA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool		result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::ERASE_12 called\n" ) );
	
	require ( IsParameterValid ( ERA, kSCSICmdFieldMask1Bit ), ErrorExit );	
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_ERASE_12,
								( ERA << 2 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8 ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS		   & 0xFF,
								( TRANSFER_LENGTH >> 24 ) & 0xFF,
								( TRANSFER_LENGTH >> 16 ) & 0xFF,
								( TRANSFER_LENGTH >> 8  ) & 0xFF,
								  TRANSFER_LENGTH		  & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl (	request,
								0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::FORMAT_UNIT
//
//�����������������������������������������������������������������������������
//		
//		The FORMAT_UNIT command as defined in section 6.1.1
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::FORMAT_UNIT (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				IOByteCount					defectListSize,
				SCSICmdField1Bit 			FMTDATA,
				SCSICmdField1Bit 			CMPLST,
				SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
				SCSICmdField1Byte 			VENDOR_SPECIFIC,
				SCSICmdField2Byte 			INTERLEAVE,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool		result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::FORMAT_UNIT called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( FMTDATA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( CMPLST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DEFECT_LIST_FORMAT, kSCSICmdFieldMask3Bit ), ErrorExit );
	require ( IsParameterValid ( VENDOR_SPECIFIC, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( INTERLEAVE, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	if ( defectListSize > 0 )
	{
		
		// We have data to send to the device, 
		// make sure that we were given a valid buffer
		require ( IsBufferAndCapacityValid ( dataBuffer, defectListSize ), ErrorExit );
		
	}
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_FORMAT_UNIT,
								( FMTDATA << 4 ) | ( CMPLST << 4 ) | DEFECT_LIST_FORMAT,
								VENDOR_SPECIFIC,
								( INTERLEAVE >> 8 ) & 0xFF,
								  INTERLEAVE		& 0xFF,
								CONTROL );
 	
 	if ( FMTDATA == 0 )
	{
		
		// No DEFECT LIST is being sent to the device, so there
		// will be no data transfer for this request.
		SetDataTransferControl ( 	request,
									0,
									kSCSIDataTransfer_NoDataTransfer );	
		
	}
	
	else
	{
		
		// The client has requested a DEFECT LIST be sent to the device
		// to be used with the format command
		SetDataTransferControl ( 	request,
									0,
									kSCSIDataTransfer_FromInitiatorToTarget,
									dataBuffer );
									// -->Need defect list size	
		
	}
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::LOCK_UNLOCK_CACHE
//
//�����������������������������������������������������������������������������
//		
//		The LOCK_UNLOCK_CACHE command as defined in section 6.1.2
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::LOCK_UNLOCK_CACHE (
				SCSITask *					request,
				SCSICmdField1Bit 			LOCK,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::LOCK_UNLOCK_CACHE called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOCK, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_LOCK_UNLOCK_CACHE,
								( LOCK << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS >> 8 ) 	& 0xFF,
								  NUMBER_OF_BLOCKS			& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::MEDIUM_SCAN
//
//�����������������������������������������������������������������������������
//		
//		The MEDIUM_SCAN command as defined in section 6.2.3
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::MEDIUM_SCAN (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
   				SCSICmdField1Bit 			WBS,
   				SCSICmdField1Bit 			ASA,
   				SCSICmdField1Bit 			RSD,
   				SCSICmdField1Bit 			PRA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			PARAMETER_LIST_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool		result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::MEDIUM_SCAN called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( WBS, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( ASA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RSD, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( PRA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( PARAMETER_LIST_LENGTH, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, PARAMETER_LIST_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_MEDIUM_SCAN,
								( WBS << 4 ) | ( ASA << 3 ) | ( RSD << 2 ) |
									( PRA << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								0x00,
								PARAMETER_LIST_LENGTH,
								CONTROL );
	
	if ( PARAMETER_LIST_LENGTH > 0 )
	{
		
		SetDataTransferControl ( 	request,
									0,
									kSCSIDataTransfer_FromInitiatorToTarget,
									dataBuffer,
									PARAMETER_LIST_LENGTH );	
		
	}
	
	else
	{
		
		SetDataTransferControl ( 	request,
									0,
									kSCSIDataTransfer_NoDataTransfer );	
		
	}
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::PREFETCH
//
//�����������������������������������������������������������������������������
//		
//		The PREFETCH command as defined in section 6.1.3
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::PREFETCH (
				SCSITask *					request,
				SCSICmdField1Bit 			IMMED,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool		result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::PREFETCH called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( IMMED, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_PREFETCH,
								( IMMED << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS 		& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 ) & 0xFF,
								  TRANSFER_LENGTH		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_6
//
//�����������������������������������������������������������������������������
//		
//		The READ(6) command as defined in section 6.1.4
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_6 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField21Bit 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool		result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_6 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask21Bit ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_6,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0x1F,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								TRANSFER_LENGTH,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_10
//
//�����������������������������������������������������������������������������
//		
//		The READ(10) command as defined in section 6.1.5
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount  ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_10,
								( DPO << 4 ) | ( FUA << 3 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 ) & 0xFF,
								  TRANSFER_LENGTH		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_12
//
//�����������������������������������������������������������������������������
//		
//		The READ(12) command as defined in section 6.2.4
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_12 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount  ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_12,
								( DPO << 4 ) | ( FUA << 3 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								( TRANSFER_LENGTH >> 24 ) 		& 0xFF,
								( TRANSFER_LENGTH >> 16 ) 		& 0xFF,
								( TRANSFER_LENGTH >> 8  ) 		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_CAPACITY
//
//�����������������������������������������������������������������������������
//		
//		The READ_CAPACITY command as defined in section 6.1.6
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_CAPACITY (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Bit 			PMI,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_CAPACITY called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( PMI, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, 8 ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_CAPACITY,
								RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								0x00,
								PMI,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								8 );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_DEFECT_DATA_10
//
//�����������������������������������������������������������������������������
//		
//		The READ_DEFECT_DATA(10) command as defined in section 6.1.7
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_DEFECT_DATA_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			PLIST,
				SCSICmdField1Bit 			GLIST,
				SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
				SCSICmdField2Byte 			ALLOCATION_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_DEFECT_DATA_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( PLIST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( GLIST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DEFECT_LIST_FORMAT, kSCSICmdFieldMask3Bit ), ErrorExit );
	require ( IsParameterValid ( ALLOCATION_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, ALLOCATION_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_DEFECT_DATA_10,
								0x00,
								( PLIST << 4 ) | ( GLIST << 3 ) | DEFECT_LIST_FORMAT,
								0x00,
								0x00,
								0x00,
								0x00,
								( ALLOCATION_LENGTH >> 8  ) & 0xFF,
								  ALLOCATION_LENGTH			& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								ALLOCATION_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_DEFECT_DATA_12
//
//�����������������������������������������������������������������������������
//		
//		The READ_DEFECT_DATA(12) command as defined in section 6.2.5
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_DEFECT_DATA_12 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			PLIST,
				SCSICmdField1Bit 			GLIST,
				SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
				SCSICmdField4Byte 			ALLOCATION_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_DEFECT_DATA_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( PLIST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( GLIST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DEFECT_LIST_FORMAT, kSCSICmdFieldMask3Bit ), ErrorExit );
	require ( IsParameterValid ( ALLOCATION_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, ALLOCATION_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_DEFECT_DATA_12,
								( PLIST << 4 ) | ( GLIST << 3 ) | DEFECT_LIST_FORMAT,
								0x00,
								0x00,
								0x00,
								0x00,
								( ALLOCATION_LENGTH >> 24  ) & 0xFF,
								( ALLOCATION_LENGTH >> 16  ) & 0xFF,
								( ALLOCATION_LENGTH >> 8  )  & 0xFF,
								  ALLOCATION_LENGTH			 & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								ALLOCATION_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_GENERATION
//
//�����������������������������������������������������������������������������
//		
//		The READ_GENERATION command as defined in section 6.2.6
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_GENERATION (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			ALLOCATION_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_GENERATION called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( ALLOCATION_LENGTH, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, ALLOCATION_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_GENERATION,
								RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								0x00,
								ALLOCATION_LENGTH,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								ALLOCATION_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_LONG
//
//�����������������������������������������������������������������������������
//		
//		The READ_LONG command as defined in section 6.1.8
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_LONG (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			CORRCT,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			BYTE_TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_LONG called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( CORRCT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( BYTE_TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, BYTE_TRANSFER_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_LONG,
								( CORRCT << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								( BYTE_TRANSFER_LENGTH >> 8 )	 & 0xFF,
								  BYTE_TRANSFER_LENGTH	 		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								BYTE_TRANSFER_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::READ_UPDATED_BLOCK_10
//
//�����������������������������������������������������������������������������
//		
//		The READ_UPDATED_BLOCK(10) command as defined in section 6.2.7
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::READ_UPDATED_BLOCK_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt32						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
			 	SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Bit 			LATEST,
			 	SCSICmdField15Bit 			GENERATION_ADDRESS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::READ_UPDATED_BLOCK_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( LATEST, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( GENERATION_ADDRESS, kSCSICmdFieldMask5Bit ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_READ_UPDATED_BLOCK_10,
								( DPO << 4 ) | ( FUA << 3 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								( LATEST << 7 ) | ( ( GENERATION_ADDRESS >> 8 ) & 0xFF ),
								GENERATION_ADDRESS & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromTargetToInitiator,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::REASSIGN_BLOCKS
//
//�����������������������������������������������������������������������������
//		
//		The REASSIGN_BLOCKS command as defined in section 6.1.9
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::REASSIGN_BLOCKS (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::REASSIGN_BLOCKS called\n" ) );
	
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_REASSIGN_BLOCKS,
								0x00,
								0x00,
								0x00,
								0x00,
								CONTROL );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::REBUILD
//
//�����������������������������������������������������������������������������
//		
//		The REBUILD command as defined in section 6.1.10
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::REBUILD (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
			 	SCSICmdField1Bit 			INTDATA,
				SCSICmdField2Bit 			PORT_CONTROL,
			 	SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			REBUILD_LENGTH,
				SCSICmdField4Byte 			PARAMETER_LIST_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::REBUILD called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( INTDATA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( PORT_CONTROL, kSCSICmdFieldMask2Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( REBUILD_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( PARAMETER_LIST_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, PARAMETER_LIST_LENGTH ), ErrorExit );
	
	// This is a 16-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_REBUILD,
								( DPO << 4 ) | ( FUA << 3 ) | ( INTDATA < 2 ) | PORT_CONTROL,
								( LOGICAL_BLOCK_ADDRESS >> 24 )	 & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )	 & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >>  8 )	 & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								( REBUILD_LENGTH >> 24 )		 & 0xFF,
								( REBUILD_LENGTH >> 16 )		 & 0xFF,
								( REBUILD_LENGTH >>  8 )		 & 0xFF,
								  REBUILD_LENGTH			 	 & 0xFF,
								( PARAMETER_LIST_LENGTH >> 24 )	 & 0xFF,
								( PARAMETER_LIST_LENGTH >> 16 )	 & 0xFF,
								( PARAMETER_LIST_LENGTH >>  8 )	 & 0xFF,
								  PARAMETER_LIST_LENGTH			 & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								PARAMETER_LIST_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::REGENERATE
//
//�����������������������������������������������������������������������������
//		
//		The REGENERATE command as defined in section 6.1.11
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::REGENERATE (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit			DPO,
				SCSICmdField1Bit 			FUA,
			 	SCSICmdField1Bit 			INTDATA,
			 	SCSICmdField2Bit 			PORT_CONTROL,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			REGENERATE_LENGTH,
				SCSICmdField4Byte 			PARAMETER_LIST_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::REGENERATE called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( INTDATA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( PORT_CONTROL, kSCSICmdFieldMask2Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( REGENERATE_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( PARAMETER_LIST_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, PARAMETER_LIST_LENGTH ), ErrorExit );
	
	// This is a 16-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_REGENERATE,
								( DPO << 4 ) | ( FUA << 3 ) | ( INTDATA < 2 ) | PORT_CONTROL,
								( LOGICAL_BLOCK_ADDRESS >> 24 )	 & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )	 & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >>  8 )	 & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								( REGENERATE_LENGTH >> 24 )		 & 0xFF,
								( REGENERATE_LENGTH >> 16 )		 & 0xFF,
								( REGENERATE_LENGTH >>  8 )		 & 0xFF,
								  REGENERATE_LENGTH			 	 & 0xFF,
								( PARAMETER_LIST_LENGTH >> 24 )	 & 0xFF,
								( PARAMETER_LIST_LENGTH >> 16 )	 & 0xFF,
								( PARAMETER_LIST_LENGTH >>  8 )	 & 0xFF,
								  PARAMETER_LIST_LENGTH			 & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								PARAMETER_LIST_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::REZERO_UNIT
//
//�����������������������������������������������������������������������������
//		
//	��� OBSOLETE ���
//		
//		The REZERO_UNIT command as defined in SCSI-2 section 9.2.13.
//		REZERO_UNIT is obsoleted by the SBC specification.
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::REZERO_UNIT ( 
				SCSITask *					request,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::REZERO_UNIT called\n" ) );
	
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_REZERO_UNIT,
								0x00,
								0x00,
								0x00,
								0x00,
								CONTROL );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SEARCH_DATA_EQUAL_10
//
//�����������������������������������������������������������������������������
//		
//	��� OBSOLETE ���
//		
//		The SEARCH_DATA_EQUAL(10) command as defined in SCSI-2,
//		section 9.2.14.
//		SEARCH_DATA_EQUAL(10) is obsoleted by the SBC specification.
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SEARCH_DATA_EQUAL_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt32						transferCount,
				SCSICmdField1Bit 			INVERT,
				SCSICmdField1Bit 			SPNDAT,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SEARCH_DATA_EQUAL_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( INVERT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( SPNDAT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS_TO_SEARCH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer,
										 max ( transferCount, SEARCH_DATA_PARAMETER_LIST_MIN_LENGTH ) ),
										 ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SEARCH_DATA_EQUAL_10,
								( INVERT << 4 ) | ( SPNDAT << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS_TO_SEARCH >> 8 )	 & 0xFF,
								  NUMBER_OF_BLOCKS_TO_SEARCH	 	 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SEARCH_DATA_HIGH_10
//
//�����������������������������������������������������������������������������
//		
//	��� OBSOLETE ���
//		
//		The SEARCH_DATA_HIGH(10) command as defined in SCSI-2,
//		section 9.2.14.
//		SEARCH_DATA_HIGH(10) is obsoleted by the SBC specification.
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SEARCH_DATA_HIGH_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt32						transferCount,
				SCSICmdField1Bit 			INVERT,
				SCSICmdField1Bit 			SPNDAT,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SEARCH_DATA_HIGH_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( INVERT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( SPNDAT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS_TO_SEARCH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer,
										 max ( transferCount, SEARCH_DATA_PARAMETER_LIST_MIN_LENGTH ) ),
										 ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SEARCH_DATA_HIGH_10,
								( INVERT << 4 ) | ( SPNDAT << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS_TO_SEARCH >> 8 )	 & 0xFF,
								  NUMBER_OF_BLOCKS_TO_SEARCH	 	 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SEARCH_DATA_LOW_10
//
//�����������������������������������������������������������������������������
//		
//	��� OBSOLETE ���
//		
//		The SEARCH_DATA_LOW(10) command as defined in SCSI-2,
//		section 9.2.14.
//		SEARCH_DATA_LOW(10) is obsoleted by the SBC specification.
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SEARCH_DATA_LOW_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt32						transferCount,
				SCSICmdField1Bit 			INVERT,
				SCSICmdField1Bit 			SPNDAT,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SEARCH_DATA_LOW_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( INVERT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( SPNDAT, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS_TO_SEARCH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer,
										 max ( transferCount, SEARCH_DATA_PARAMETER_LIST_MIN_LENGTH ) ),
										 ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SEARCH_DATA_LOW_10,
								( INVERT << 4 ) | ( SPNDAT << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16  ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS_TO_SEARCH >> 8 )	 & 0xFF,
								  NUMBER_OF_BLOCKS_TO_SEARCH	 	 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SEEK_6
//
//�����������������������������������������������������������������������������
//		
//	��� OBSOLETE ���
//		
//		The SEEK(6) command as defined in SCSI-2, section 9.2.15.
//		SEEK(6) is obsoleted by the SBC specification.
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SEEK_6 (
				SCSITask *					request,
   				SCSICmdField21Bit 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SEEK_6 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask21Bit ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SEEK_6,
								( LOGICAL_BLOCK_ADDRESS >> 16 )  & 0x1F,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SEEK_10
//
//�����������������������������������������������������������������������������
//		
//		The SEEK(10) command as defined in section 6.1.12
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SEEK_10 (
				SCSITask *					request,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SEEK_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SEEK_10,
								0x00,
								( LOGICAL_BLOCK_ADDRESS >> 24 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								0x00,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SET_LIMITS_10
//
//�����������������������������������������������������������������������������
//		
//		The SET_LIMITS(10) command as defined in section 6.1.13
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SET_LIMITS_10 (
				SCSITask *					request,
				SCSICmdField1Bit 			RDINH,
				SCSICmdField1Bit 			WRINH,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SET_LIMITS_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RDINH, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( WRINH, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SET_LIMITS_10,
								( RDINH << 1 ) | WRINH,
								( LOGICAL_BLOCK_ADDRESS >> 24 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS >> 8  )  	 & 0xFF,
								  NUMBER_OF_BLOCKS			 	 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SET_LIMITS_12
//
//�����������������������������������������������������������������������������
//		
//		The SET_LIMITS(12) command as defined in section 6.2.8
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SET_LIMITS_12 (
				SCSITask *					request,
				SCSICmdField1Bit 			RDINH,
				SCSICmdField1Bit 			WRINH,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			NUMBER_OF_BLOCKS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SET_LIMITS_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RDINH, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( WRINH, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SET_LIMITS_12,
								( RDINH << 1 ) | WRINH,
								( LOGICAL_BLOCK_ADDRESS >> 24 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )  & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  )  & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 & 0xFF,
								( NUMBER_OF_BLOCKS >> 24  )  	 & 0xFF,
								( NUMBER_OF_BLOCKS >> 16  )  	 & 0xFF,
								( NUMBER_OF_BLOCKS >>  8  )  	 & 0xFF,
								  NUMBER_OF_BLOCKS			 	 & 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::START_STOP_UNIT
//
//�����������������������������������������������������������������������������
//		
//		The START_STOP_UNIT command as defined in section 6.1.14
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::START_STOP_UNIT (
				SCSITask *					request,
				SCSICmdField1Bit 			IMMED,
				SCSICmdField4Bit 			POWER_CONDITIONS,
				SCSICmdField1Bit 			LOEJ,
				SCSICmdField1Bit 			START,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::START_STOP_UNIT called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( IMMED, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( POWER_CONDITIONS, kSCSICmdFieldMask4Bit ), ErrorExit );
	require ( IsParameterValid ( LOEJ, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( START, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_START_STOP_UNIT,
								IMMED,
								0x00,
								0x00,
								( POWER_CONDITIONS << 4 ) | ( LOEJ << 1 ) | START,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::SYNCHRONIZE_CACHE
//
//�����������������������������������������������������������������������������
//		
//		The SYNCHRONIZE_CACHE command as defined in section 6.1.15
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::SYNCHRONIZE_CACHE (
				SCSITask *					request,
				SCSICmdField1Bit 			IMMED,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::SYNCHRONIZE_CACHE called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( IMMED, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( NUMBER_OF_BLOCKS, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately
	SetCommandDescriptorBlock (	request,
								kSCSICmd_SYNCHRONIZE_CACHE,
								( IMMED << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( NUMBER_OF_BLOCKS >> 8 )	& 0xFF,
								  NUMBER_OF_BLOCKS			& 0xFF,
								CONTROL );
	
	SetDataTransferControl (	request,
								0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::UPDATE_BLOCK
//
//�����������������������������������������������������������������������������
//		
//		The UPDATE_BLOCK command as defined in section 6.2.9
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::UPDATE_BLOCK (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::UPDATE_BLOCK called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately
	SetCommandDescriptorBlock (	request,
								kSCSICmd_UPDATE_BLOCK,
								RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								0x00,
								0x00,
								CONTROL );
	
	SetDataTransferControl (	request,
								0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::VERIFY_10
//
//�����������������������������������������������������������������������������
//		
//		The VERIFY(10) command as defined in sections 6.1.16 and 6.2.10
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::VERIFY_10 (
				SCSITask *					request,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			BLKVFY,
				SCSICmdField1Bit 			BYTCHK,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			VERIFICATION_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::VERIFY_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BLKVFY, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BYTCHK, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( VERIFICATION_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately
	SetCommandDescriptorBlock (	request,
								kSCSICmd_VERIFY_10,
								( DPO << 4 ) | ( BLKVFY << 2 ) | ( BYTCHK << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( VERIFICATION_LENGTH >> 8 )	& 0xFF,
								  VERIFICATION_LENGTH			& 0xFF,
								CONTROL );
	
	SetDataTransferControl (	request,
								0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::VERIFY_12
//
//�����������������������������������������������������������������������������
//		
//		The VERIFY(12) command as defined in section 6.2.11
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::VERIFY_12 (
				SCSITask *					request,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			BLKVFY,
				SCSICmdField1Bit 			BYTCHK,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			VERIFICATION_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::VERIFY_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BLKVFY, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BYTCHK, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( VERIFICATION_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately
	SetCommandDescriptorBlock (	request,
								kSCSICmd_VERIFY_12,
								( DPO << 4 ) | ( BLKVFY << 2 ) | ( BYTCHK << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								( VERIFICATION_LENGTH >> 24 )	& 0xFF,
								( VERIFICATION_LENGTH >> 16 )	& 0xFF,
								( VERIFICATION_LENGTH >>  8 )	& 0xFF,
								  VERIFICATION_LENGTH			& 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl (	request,
								0,
								kSCSIDataTransfer_NoDataTransfer );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_6
//
//�����������������������������������������������������������������������������
//		
//		The WRITE(6) command as defined in section 6.1.17
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_6 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField21Bit 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField1Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_6 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 6-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_6,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								TRANSFER_LENGTH,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_10
//
//�����������������������������������������������������������������������������
//		
//		The WRITE(10) command as defined in sections 6.1.18 and 6.2.12
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			EBP,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_10,
								( DPO << 4 ) | ( FUA << 3 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 ) & 0xFF,
								  TRANSFER_LENGTH		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_12
//
//�����������������������������������������������������������������������������
//		
//		The WRITE(12) command as defined in section 6.2.13
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_12 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			EBP,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( EBP, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_12,
								( DPO << 4 ) | ( FUA << 3 ) | ( EBP << 2 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								( TRANSFER_LENGTH >> 24 )		& 0xFF,
								( TRANSFER_LENGTH >> 16 )		& 0xFF,
								( TRANSFER_LENGTH >>  8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_AND_VERIFY_10
//
//�����������������������������������������������������������������������������
//		
//		The WRITE_AND_VERIFY(10) command as defined in sections 6.1.19
//		and 6.2.14
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_AND_VERIFY_10 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			EBP,
				SCSICmdField1Bit 			BYTCHK,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_AND_VERIFY_10 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( EBP, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BYTCHK, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_AND_VERIFY_10,
								( DPO << 4 ) | ( EBP << 2 ) | ( BYTCHK << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_AND_VERIFY_12
//
//�����������������������������������������������������������������������������
//		
//		The WRITE_AND_VERIFY(12) command as defined in sections 6.2.15
//		and 6.2.14
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_AND_VERIFY_12 (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				UInt64						transferCount,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			EBP,
				SCSICmdField1Bit 			BYTCHK,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_AND_VERIFY_12 called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( EBP, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( BYTCHK, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, transferCount ), ErrorExit );
	
	// This is a 12-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_AND_VERIFY_12,
								( DPO << 4 ) | ( EBP << 2 ) | ( BYTCHK << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								( TRANSFER_LENGTH >> 24 )		& 0xFF,
								( TRANSFER_LENGTH >> 16 )		& 0xFF,
								( TRANSFER_LENGTH >>  8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								0x00,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								transferCount );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_LONG
//
//�����������������������������������������������������������������������������
//		
//		The WRITE_LONG command as defined in section 6.1.20
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_LONG (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_LONG called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, TRANSFER_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_LONG,
								RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::WRITE_SAME
//
//�����������������������������������������������������������������������������
//		
//		The WRITE_SAME command as defined in section 6.1.21
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::WRITE_SAME (
				SCSITask *					request,
	 			IOMemoryDescriptor *		dataBuffer,
	   			SCSICmdField1Bit 			PBDATA,
				SCSICmdField1Bit 			LBDATA,
				SCSICmdField1Bit 			RELADR,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::WRITE_SAME called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( PBDATA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LBDATA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( RELADR, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, TRANSFER_LENGTH ), ErrorExit );
	
	// Can't have PBDATA and LBDATA set in same command
	require ( ( PBDATA == !LBDATA ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_WRITE_SAME,
								( PBDATA << 2 ) | ( LBDATA << 1 ) | RELADR,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::XDREAD
//
//�����������������������������������������������������������������������������
//		
//		The XDREAD command as defined in section 6.1.22
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::XDREAD (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::XDREAD called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, TRANSFER_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_XDREAD,
								0x00,
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::XDWRITE
//
//�����������������������������������������������������������������������������
//		
//		The XDWRITE command as defined in section 6.1.23
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::XDWRITE (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			DISABLE_WRITE,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::XDWRITE called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DISABLE_WRITE, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, TRANSFER_LENGTH ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_XDWRITE,
								( DPO << 4 ) | ( FUA << 3 ) | ( DISABLE_WRITE << 2 ),
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS			& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 )		& 0xFF,
								  TRANSFER_LENGTH				& 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::XDWRITE_EXTENDED
//
//�����������������������������������������������������������������������������
//		
//		The XDWRITE_EXTENDED command as defined in section 6.1.24
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::XDWRITE_EXTENDED (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			TABLE_ADDRESS,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField1Bit 			DISABLE_WRITE,
				SCSICmdField2Bit 			PORT_CONTROL,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField4Byte 			SECONDARY_BLOCK_ADDRESS,
				SCSICmdField4Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			SECONDARY_ADDRESS,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::XDWRITE_EXTENDED called\n" ) );
	
	// Do the pre-flight check on the passed in parameters
	require ( IsParameterValid ( TABLE_ADDRESS, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( DISABLE_WRITE, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( PORT_CONTROL, kSCSICmdFieldMask2Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( SECONDARY_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( SECONDARY_ADDRESS, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	require ( IsBufferAndCapacityValid ( dataBuffer, TRANSFER_LENGTH ), ErrorExit );
	
	// This is a 16-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_XDWRITE_EXTENDED,
								( TABLE_ADDRESS << 7 ) | ( DPO << 4 ) | ( FUA << 3 ) | ( DISABLE_WRITE < 2 ) | PORT_CONTROL,
								( LOGICAL_BLOCK_ADDRESS >> 24 )			& 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 )			& 0xFF,
								( LOGICAL_BLOCK_ADDRESS >>  8 )			& 0xFF,
								  LOGICAL_BLOCK_ADDRESS			 		& 0xFF,
								( SECONDARY_BLOCK_ADDRESS >> 24 )		& 0xFF,
								( SECONDARY_BLOCK_ADDRESS >> 16 )		& 0xFF,
								( SECONDARY_BLOCK_ADDRESS >>  8 )		& 0xFF,
								  SECONDARY_BLOCK_ADDRESS			 	& 0xFF,
								( TRANSFER_LENGTH >> 24 )				& 0xFF,
								( TRANSFER_LENGTH >> 16 )				& 0xFF,
								( TRANSFER_LENGTH >>  8 )				& 0xFF,
								  TRANSFER_LENGTH						& 0xFF,
								SECONDARY_ADDRESS,
								CONTROL );
	
	SetDataTransferControl ( 	request,
						   		0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );	
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::XPWRITE
//
//�����������������������������������������������������������������������������
//		
//		The XPWRITE command as defined in section 6.1.25
//
//�����������������������������������������������������������������������������

bool
SCSIBlockCommands::XPWRITE (
				SCSITask *					request,
				IOMemoryDescriptor *		dataBuffer,
				SCSICmdField1Bit 			DPO,
				SCSICmdField1Bit 			FUA,
				SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
				SCSICmdField2Byte 			TRANSFER_LENGTH,
				SCSICmdField1Byte 			CONTROL )
{
	
	bool	result = false;
	
	STATUS_LOG ( ( "SCSIBlockCommands::XPWRITE called\n" ) );

	require ( IsParameterValid ( DPO, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( FUA, kSCSICmdFieldMask1Bit ), ErrorExit );
	require ( IsParameterValid ( LOGICAL_BLOCK_ADDRESS, kSCSICmdFieldMask4Byte ), ErrorExit );
	require ( IsParameterValid ( TRANSFER_LENGTH, kSCSICmdFieldMask2Byte ), ErrorExit );
	require ( IsParameterValid ( CONTROL, kSCSICmdFieldMask1Byte ), ErrorExit );
	
	// This is a 10-Byte command, fill out the cdb appropriately  
	SetCommandDescriptorBlock (	request,
								kSCSICmd_XPWRITE,
								( DPO << 4 ) | ( FUA << 3 ),
								( LOGICAL_BLOCK_ADDRESS >> 24 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 16 ) & 0xFF,
								( LOGICAL_BLOCK_ADDRESS >> 8  ) & 0xFF,
								  LOGICAL_BLOCK_ADDRESS 		& 0xFF,
								0x00,
								( TRANSFER_LENGTH >> 8 ) & 0xFF,
								  TRANSFER_LENGTH		 & 0xFF,
								CONTROL );
	
	SetDataTransferControl ( 	request,
								0,
								kSCSIDataTransfer_FromInitiatorToTarget,
								dataBuffer,
								TRANSFER_LENGTH );
	
	result = true;
	
	
ErrorExit:
	
	
	return result;
	
}


#if 0
#pragma mark -
#pragma mark � Static Methods
#pragma mark -
#endif


//�����������������������������������������������������������������������������
//
//		SCSIBlockCommands::CreateSCSIBlockCommandObject
//
//�����������������������������������������������������������������������������
//		
//		Factory method for getting an instance of the command builder
//
//�����������������������������������������������������������������������������

SCSIBlockCommands *
SCSIBlockCommands::CreateSCSIBlockCommandObject ( void )
{

	return OSTypeAlloc ( SCSIBlockCommands );

}
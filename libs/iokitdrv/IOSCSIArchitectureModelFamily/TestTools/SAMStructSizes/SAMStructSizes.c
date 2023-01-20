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
#include <IOKit/scsi/SCSICmds_INQUIRY_Definitions.h>
#include <IOKit/scsi/SCSICmds_MODE_Definitions.h>
#include <IOKit/scsi/SCSICmds_REQUEST_SENSE_Defs.h>
#include <IOKit/scsi/SCSICmds_REPORT_LUNS_Definitions.h>

static void
PrintSCSICmds_INQUIRY_Sizes ( void );

static void
PrintSCSICmds_MODE_Sizes ( void );

static void
PrintSCSICmds_REQUEST_SENSE_Sizes ( void );

static void
PrintSCSICmds_REPORT_LUNS_Sizes ( void );


int
main ( int argc, const char * argv[] )
{
	
	printf ( "SAM Structure Size Tester\n\n" );
	
	PrintSCSICmds_INQUIRY_Sizes ( );
	PrintSCSICmds_MODE_Sizes ( );
	PrintSCSICmds_REQUEST_SENSE_Sizes ( );
	PrintSCSICmds_REPORT_LUNS_Sizes ( );
	
	return 0;
	
}


static void
PrintSCSICmds_INQUIRY_Sizes ( void )
{

	printf ( "INQUIRY sizes\n" );
	
	// Standard INQUIRY data (page 0x00)
	printf ( "SCSICmd_INQUIRY_StandardData = %ld\n", ( UInt32 ) sizeof ( SCSICmd_INQUIRY_StandardData ) );
	printf ( "SCSICmd_INQUIRY_StandardDataAll = %ld\n", ( UInt32 ) sizeof ( SCSICmd_INQUIRY_StandardDataAll ) );
	
	// INQUIRY Vital Products Pages
	printf ( "SCSICmd_INQUIRY_Page00_Header = %ld\n", ( UInt32 ) sizeof ( SCSICmd_INQUIRY_Page00_Header ) );
	printf ( "SCSICmd_INQUIRY_Page83_Header = %ld\n", ( UInt32 ) sizeof ( SCSICmd_INQUIRY_Page83_Header ) );
	printf ( "SCSICmd_INQUIRY_Page83_Identification_Descriptor = %ld\n", ( UInt32 ) sizeof ( SCSICmd_INQUIRY_Page83_Identification_Descriptor ) );
	
	printf ( "\n" );
	
}

static void
PrintSCSICmds_MODE_Sizes ( void )
{
	
	printf ( "MODE_SENSE and MODE_SELECT sizes\n" );
	
	// Mode parameter headers
	printf ( "SPCModeParameterHeader6 = %ld\n", ( UInt32 ) sizeof ( SPCModeParameterHeader6 ) );
	printf ( "SPCModeParameterHeader10 = %ld\n", ( UInt32 ) sizeof ( SPCModeParameterHeader10 ) );
	
	// Mode parameter block descriptors
	printf ( "ModeParameterBlockDescriptor = %ld\n", ( UInt32 ) sizeof ( ModeParameterBlockDescriptor ) );
	printf ( "DASDModeParameterBlockDescriptor = %ld\n", ( UInt32 ) sizeof ( DASDModeParameterBlockDescriptor ) );
	printf ( "LongLBAModeParameterBlockDescriptor = %ld\n", ( UInt32 ) sizeof ( LongLBAModeParameterBlockDescriptor ) );
	
	// Mode Page format header
	printf ( "ModePageFormatHeader = %ld\n", ( UInt32 ) sizeof ( ModePageFormatHeader ) );
	
	// SPC Mode pages
	printf ( "SPCModePagePowerCondition = %ld\n", ( UInt32 ) sizeof ( SPCModePagePowerCondition ) );
	
	// SBC Mode pages
	printf ( "SBCModePageFormatDevice = %ld\n", ( UInt32 ) sizeof ( SBCModePageFormatDevice ) );
	printf ( "SBCModePageRigidDiskGeometry = %ld\n", ( UInt32 ) sizeof ( SBCModePageRigidDiskGeometry ) );
	printf ( "SBCModePageFlexibleDisk = %ld\n", ( UInt32 ) sizeof ( SBCModePageFlexibleDisk ) );
	printf ( "SBCModePageCaching = %ld\n", ( UInt32 ) sizeof ( SBCModePageCaching ) );
	
	printf ( "\n" );
	
}

static void
PrintSCSICmds_REQUEST_SENSE_Sizes ( void )
{

	printf ( "REQUEST_SENSE sizes\n" );
	
	// Standard REQUEST_SENSE data
	printf ( "SCSI_Sense_Data = %ld\n", ( UInt32 ) sizeof ( SCSI_Sense_Data ) );
	
	printf ( "\n" );
	
}


static void
PrintSCSICmds_REPORT_LUNS_Sizes ( void )
{

	printf ( "REPORT_LUNS sizes\n" );
	
	// Standard REQUEST_SENSE data
	printf ( "SCSICmd_REPORT_LUNS_Header = %ld\n", ( UInt32 ) sizeof ( SCSICmd_REPORT_LUNS_Header ) );
	printf ( "SCSICmd_REPORT_LUNS_LUN_ENTRY = %ld\n", ( UInt32 ) sizeof ( SCSICmd_REPORT_LUNS_LUN_ENTRY ) );
	
	printf ( "\n" );
	
}
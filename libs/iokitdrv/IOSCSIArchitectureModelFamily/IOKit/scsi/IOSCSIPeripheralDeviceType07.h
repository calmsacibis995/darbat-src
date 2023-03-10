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

#ifndef _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_TYPE_07_H_
#define _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_TYPE_07_H_

#if defined(KERNEL) && defined(__cplusplus)


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Includes
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

// SCSI Architecture Model Family includes
#include <IOKit/scsi/IOSCSIBlockCommandsDevice.h>


//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
//	Class Declaration
//ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

class IOSCSIPeripheralDeviceType07 : public IOSCSIBlockCommandsDevice
{
	
	OSDeclareDefaultStructors ( IOSCSIPeripheralDeviceType07 )
	
protected:
	
	// Reserve space for future expansion.
	struct IOSCSIPeripheralDeviceType07ExpansionData { };
	IOSCSIPeripheralDeviceType07ExpansionData * fIOSCSIPeripheralDeviceType07Reserved;
	
public:
	
	bool			init ( OSDictionary * propTable );
	virtual bool	start ( IOService * provider );
	virtual void 	stop ( IOService *  provider );
		
private:
	
	// Space reserved for future expansion.
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 1 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 2 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 3 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 4 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 5 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 6 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 7 );
	OSMetaClassDeclareReservedUnused ( IOSCSIPeripheralDeviceType07, 8 );
	
};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif /* _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_TYPE_07_H_ */
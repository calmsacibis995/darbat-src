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

#ifndef _IOKIT_SCSI_PORTS_H_
#define _IOKIT_SCSI_PORTS_H_

// Message definition to be used with the messageClients call to 
// inform of a change in port status
enum
{
	kSCSIPort_NotificationStatusChange		= 0x68000001
};


// Port status type
typedef UInt32 SCSIPortStatus;

// Definitions for the possible statuses
enum
{
	kSCSIPort_StatusOnline	= 0,	// Port is online
	kSCSIPort_StatusOffline	= 1,	// Port is offline (e.g. unplugged cable)
	kSCSIPort_StatusFailure	= 2		// Driver has detected unrecoverable port failure (e.g. hardware port failure)
};

#endif /* _IOKIT_SCSI_PORTS_H_ */

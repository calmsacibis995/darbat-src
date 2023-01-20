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
 * Copyright (c) 2002-2003 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_ATA_SMART_USER_CLIENT_H_
#define _IOKIT_ATA_SMART_USER_CLIENT_H_


#if defined(KERNEL) && defined(__cplusplus)


//�����������������������������������������������������������������������������
//	Includes
//�����������������������������������������������������������������������������

// IOKit includes
#include <IOKit/IOLib.h>
#include <IOKit/IOUserClient.h>

// Private includes
#include "ATASMARTLib.h"
#include "ATASMARTLibPriv.h"
#include "IOATABlockStorageDevice.h"

#include <IOKit/ata/IOATACommand.h>

// Forward class declaration
class ATASMARTUserClient;


//�����������������������������������������������������������������������������
//	Typedefs
//�����������������������������������������������������������������������������

struct ATASMARTRefCon
{
	ATASMARTUserClient *	self;
	bool					isDone;
	bool					sleepOnIt;
};
typedef struct ATASMARTRefCon ATASMARTRefCon;


//�����������������������������������������������������������������������������
//	Class Declarations
//�����������������������������������������������������������������������������


class ATASMARTUserClient : public IOUserClient
{
	
	OSDeclareDefaultStructors ( ATASMARTUserClient );
	
public:
	
	virtual bool 	 initWithTask 		( task_t owningTask, void * securityToken, UInt32 type );
	
    virtual bool 	 init 				( OSDictionary * dictionary = 0 );
    virtual bool 	 start 				( IOService * provider );
	virtual void	 free				( void );
    virtual IOReturn message 			( UInt32 type, IOService * provider, void * arg );
	
    virtual IOReturn clientClose 		( void );
	
	IOReturn	EnableDisableOperations ( UInt32 enable );
	IOReturn	EnableDisableAutoSave 	( UInt32 enable );
	IOReturn	ReturnStatus		 	( UInt32 * exceedsCondition );
	IOReturn	ExecuteOfflineImmediate	( UInt32 extendedTest );
	IOReturn	ReadData				( vm_address_t data );
	IOReturn	ReadDataThresholds		( vm_address_t data );
	IOReturn	ReadLogAtAddress		( ATASMARTReadLogStruct *		readLogData,
										  UInt32						inStructSize );
	IOReturn	WriteLogAtAddress		( ATASMARTWriteLogStruct *		writeLogData,
										  UInt32						inStructSize );
	IOReturn	GetIdentifyData			( ATAGetIdentifyDataStruct *	identifyData,
										  UInt32 *						bytesTransferred,
										  UInt32						inStructSize,
										  UInt32 *						outStructSize );
	
protected:
	
	static IOExternalMethod				sMethods[kIOATASMARTMethodCount];
	
	static IOReturn		sWaitForCommand 	( void * userClient, IOATACommand * command );
	static void 		sCommandCallback	( IOATACommand * command );
	
	IOReturn 			GatedWaitForCommand	( IOATACommand * command );
	void	 			CommandCallback		( IOATACommand * command );
	
	task_t								fTask;
	IOATABlockStorageDevice *			fProvider;
	IOCommandGate *						fCommandGate;
	IOWorkLoop *						fWorkLoop;
	UInt32								fOutstandingCommands;
	
	virtual IOExternalMethod *			getTargetAndMethodForIndex ( IOService **	target,
																	 UInt32			index );
	
	IOReturn 		HandleTerminate		( IOService * provider );
	IOReturn		SendSMARTCommand	( IOATACommand * command );
	IOATACommand *	AllocateCommand		( void );
	void			DeallocateCommand	( IOATACommand * command );

};


#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif /* ! _IOKIT_ATA_SMART_USER_CLIENT_H_ */
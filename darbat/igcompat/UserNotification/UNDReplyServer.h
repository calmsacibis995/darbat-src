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
#ifndef	_UNDReply_user_
#define	_UNDReply_user_

/* Module UNDReply */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>

#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            *name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry 	*function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	UNDReply_MSG_COUNT
#define	UNDReply_MSG_COUNT	2
#endif	/* UNDReply_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <UserNotification/UNDTypes.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* SimpleRoutine UNDAlertCompletedWithResult_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDAlertCompletedWithResult_rpc
(
	UNDReplyRef reply,
	int result,
	xmlData_t data,
	mach_msg_type_number_t dataCnt
);

/* SimpleRoutine UNDNotificationCreated_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDNotificationCreated_rpc
(
	UNDReplyRef reply,
	int userLandNotificationKey
);

__END_DECLS

/********************** Caution **************************/
/* The following data types should be used to calculate  */
/* maximum message sizes only. The actual message may be */
/* smaller, and the position of the arguments within the */
/* message layout may vary from what is presented here.  */
/* For example, if any of the arguments are variable-    */
/* sized, and less than the maximum is sent, the data    */
/* will be packed tight in the actual message to reduce  */
/* the presence of holes.                                */
/********************** Caution **************************/

/* typedefs for all requests */

#ifndef __Request__UNDReply_subsystem__defined
#define __Request__UNDReply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t data;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int result;
		mach_msg_type_number_t dataCnt;
	} __Request__UNDAlertCompletedWithResult_rpc_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int userLandNotificationKey;
	} __Request__UNDNotificationCreated_rpc_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__UNDReply_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__UNDReply_subsystem__defined
#define __RequestUnion__UNDReply_subsystem__defined
union __RequestUnion__UNDReply_subsystem {
	__Request__UNDAlertCompletedWithResult_rpc_t Request_UNDAlertCompletedWithResult_rpc;
	__Request__UNDNotificationCreated_rpc_t Request_UNDNotificationCreated_rpc;
};
#endif /* !__RequestUnion__UNDReply_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__UNDReply_subsystem__defined
#define __Reply__UNDReply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__UNDAlertCompletedWithResult_rpc_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__UNDNotificationCreated_rpc_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__UNDReply_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__UNDReply_subsystem__defined
#define __ReplyUnion__UNDReply_subsystem__defined
union __ReplyUnion__UNDReply_subsystem {
	__Reply__UNDAlertCompletedWithResult_rpc_t Reply_UNDAlertCompletedWithResult_rpc;
	__Reply__UNDNotificationCreated_rpc_t Reply_UNDNotificationCreated_rpc;
};
#endif /* !__RequestUnion__UNDReply_subsystem__defined */

#ifndef subsystem_to_name_map_UNDReply
#define subsystem_to_name_map_UNDReply \
    { "UNDAlertCompletedWithResult_rpc", 6200 },\
    { "UNDNotificationCreated_rpc", 6201 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _UNDReply_user_ */

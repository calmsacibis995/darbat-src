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
#ifndef	_semaphore_user_
#define	_semaphore_user_

/* Module semaphore */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>

// XXX TGB HACK these defines were missing, found them on opendarwin
#define SEMAPHORE_OPTION_NONE		0x00000000

#define SEMAPHORE_SIGNAL		0x00000001
#define SEMAPHORE_WAIT			0x00000002
#define SEMAPHORE_WAIT_ON_SIGNAL	0x00000008

#define SEMAPHORE_SIGNAL_TIMEOUT	0x00000010
#define SEMAPHORE_SIGNAL_ALL		0x00000020
#define SEMAPHORE_SIGNAL_INTERRUPT	0x00000040	/* libmach implements */
#define SEMAPHORE_SIGNAL_PREPOST	0x00000080

#define SEMAPHORE_WAIT_TIMEOUT		0x00000100
#define SEMAPHORE_WAIT_INTERRUPT	0x00000400	/* libmach implements */

#define SEMAPHORE_TIMEOUT_NOBLOCK	0x00100000
#define SEMAPHORE_TIMEOUT_RELATIVE	0x00200000

#define SEMAPHORE_USE_SAVED_RESULT	0x01000000	/* internal use only */
#define SEMAPHORE_SIGNAL_RELEASE	0x02000000	/* internal use only */
// END TGB HACK

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

#ifndef	semaphore_MSG_COUNT
#define	semaphore_MSG_COUNT	7
#endif	/* semaphore_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine semaphore_signal */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_signal
(
	semaphore_t semaphore
);

/* Routine semaphore_signal_all */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_signal_all
(
	semaphore_t semaphore
);

/* Routine semaphore_wait */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_wait
(
	semaphore_t semaphore
);

/* Routine semaphore_signal_thread */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_signal_thread
(
	semaphore_t semaphore,
	thread_act_t thread
);

/* Routine semaphore_timedwait */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_timedwait
(
	semaphore_t semaphore,
	mach_timespec_t wait_time
);

/* Routine semaphore_wait_signal */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_wait_signal
(
	semaphore_t wait_semaphore,
	semaphore_t signal_semaphore
);

/* Routine semaphore_timedwait_signal */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t semaphore_timedwait_signal
(
	semaphore_t wait_semaphore,
	semaphore_t signal_semaphore,
	mach_timespec_t wait_time
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

#ifndef __Request__semaphore_subsystem__defined
#define __Request__semaphore_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__semaphore_signal_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__semaphore_signal_all_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__semaphore_wait_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t thread;
		/* end of the kernel processed data */
	} __Request__semaphore_signal_thread_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_timespec_t wait_time;
	} __Request__semaphore_timedwait_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t signal_semaphore;
		/* end of the kernel processed data */
	} __Request__semaphore_wait_signal_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t signal_semaphore;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_timespec_t wait_time;
	} __Request__semaphore_timedwait_signal_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__semaphore_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__semaphore_subsystem__defined
#define __RequestUnion__semaphore_subsystem__defined
union __RequestUnion__semaphore_subsystem {
	__Request__semaphore_signal_t Request_semaphore_signal;
	__Request__semaphore_signal_all_t Request_semaphore_signal_all;
	__Request__semaphore_wait_t Request_semaphore_wait;
	__Request__semaphore_signal_thread_t Request_semaphore_signal_thread;
	__Request__semaphore_timedwait_t Request_semaphore_timedwait;
	__Request__semaphore_wait_signal_t Request_semaphore_wait_signal;
	__Request__semaphore_timedwait_signal_t Request_semaphore_timedwait_signal;
};
#endif /* !__RequestUnion__semaphore_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__semaphore_subsystem__defined
#define __Reply__semaphore_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__semaphore_signal_t;
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
	} __Reply__semaphore_signal_all_t;
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
	} __Reply__semaphore_wait_t;
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
	} __Reply__semaphore_signal_thread_t;
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
	} __Reply__semaphore_timedwait_t;
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
	} __Reply__semaphore_wait_signal_t;
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
	} __Reply__semaphore_timedwait_signal_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__semaphore_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__semaphore_subsystem__defined
#define __ReplyUnion__semaphore_subsystem__defined
union __ReplyUnion__semaphore_subsystem {
	__Reply__semaphore_signal_t Reply_semaphore_signal;
	__Reply__semaphore_signal_all_t Reply_semaphore_signal_all;
	__Reply__semaphore_wait_t Reply_semaphore_wait;
	__Reply__semaphore_signal_thread_t Reply_semaphore_signal_thread;
	__Reply__semaphore_timedwait_t Reply_semaphore_timedwait;
	__Reply__semaphore_wait_signal_t Reply_semaphore_wait_signal;
	__Reply__semaphore_timedwait_signal_t Reply_semaphore_timedwait_signal;
};
#endif /* !__RequestUnion__semaphore_subsystem__defined */

#ifndef subsystem_to_name_map_semaphore
#define subsystem_to_name_map_semaphore \
    { "semaphore_signal", 617200 },\
    { "semaphore_signal_all", 617201 },\
    { "semaphore_wait", 617202 },\
    { "semaphore_signal_thread", 617203 },\
    { "semaphore_timedwait", 617204 },\
    { "semaphore_wait_signal", 617205 },\
    { "semaphore_timedwait_signal", 617206 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _semaphore_user_ */

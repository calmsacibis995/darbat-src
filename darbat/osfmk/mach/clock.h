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
#ifndef	_clock_user_
#define	_clock_user_

/* Module clock */

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

#ifndef	clock_MSG_COUNT
#define	clock_MSG_COUNT	3
#endif	/* clock_MSG_COUNT */

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


/* Routine clock_get_time */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t clock_get_time
(
	clock_serv_t clock_serv,
	mach_timespec_t *cur_time
);

/* Routine clock_get_attributes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t clock_get_attributes
(
	clock_serv_t clock_serv,
	clock_flavor_t flavor,
	clock_attr_t clock_attr,
	mach_msg_type_number_t *clock_attrCnt
);

/* Routine clock_alarm */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t clock_alarm
(
	clock_serv_t clock_serv,
	alarm_type_t alarm_type,
	mach_timespec_t alarm_time,
	clock_reply_t alarm_port
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

#ifndef __Request__clock_subsystem__defined
#define __Request__clock_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__clock_get_time_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		clock_flavor_t flavor;
		mach_msg_type_number_t clock_attrCnt;
	} __Request__clock_get_attributes_t;
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
		mach_msg_port_descriptor_t alarm_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		alarm_type_t alarm_type;
		mach_timespec_t alarm_time;
	} __Request__clock_alarm_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__clock_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__clock_subsystem__defined
#define __RequestUnion__clock_subsystem__defined
union __RequestUnion__clock_subsystem {
	__Request__clock_get_time_t Request_clock_get_time;
	__Request__clock_get_attributes_t Request_clock_get_attributes;
	__Request__clock_alarm_t Request_clock_alarm;
};
#endif /* !__RequestUnion__clock_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__clock_subsystem__defined
#define __Reply__clock_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_timespec_t cur_time;
	} __Reply__clock_get_time_t;
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
		mach_msg_type_number_t clock_attrCnt;
		int clock_attr[1];
	} __Reply__clock_get_attributes_t;
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
	} __Reply__clock_alarm_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__clock_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__clock_subsystem__defined
#define __ReplyUnion__clock_subsystem__defined
union __ReplyUnion__clock_subsystem {
	__Reply__clock_get_time_t Reply_clock_get_time;
	__Reply__clock_get_attributes_t Reply_clock_get_attributes;
	__Reply__clock_alarm_t Reply_clock_alarm;
};
#endif /* !__RequestUnion__clock_subsystem__defined */

#ifndef subsystem_to_name_map_clock
#define subsystem_to_name_map_clock \
    { "clock_get_time", 1000 },\
    { "clock_get_attributes", 1001 },\
    { "clock_alarm", 1002 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _clock_user_ */

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
#ifndef	_lock_set_server_
#define	_lock_set_server_

/* Module lock_set */

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

#ifndef	lock_set_MSG_COUNT
#define	lock_set_MSG_COUNT	6
#endif	/* lock_set_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <kern/ipc_kobject.h>
#include <kern/ipc_tt.h>
#include <kern/ipc_host.h>
#include <kern/ipc_sync.h>
#include <kern/ledger.h>
#include <kern/processor.h>
#include <kern/sync_lock.h>
#include <kern/sync_sema.h>
#include <vm/memory_object.h>
#include <vm/vm_map.h>
#include <kern/ipc_mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */


/* Routine lock_acquire */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_acquire
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_release */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_release
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_try */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_try
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_make_stable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_make_stable
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_handoff */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_handoff
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_handoff_accept */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_handoff_accept
(
	lock_set_t lock_set,
	int lock_id
);

extern boolean_t lock_set_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t lock_set_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct lock_set_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[6];
} lock_set_subsystem;

/* typedefs for all requests */

#ifndef __Request__lock_set_subsystem__defined
#define __Request__lock_set_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_acquire_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_release_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_try_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_make_stable_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_handoff_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
	} __Request__lock_handoff_accept_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__lock_set_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__lock_set_subsystem__defined
#define __RequestUnion__lock_set_subsystem__defined
union __RequestUnion__lock_set_subsystem {
	__Request__lock_acquire_t Request_lock_acquire;
	__Request__lock_release_t Request_lock_release;
	__Request__lock_try_t Request_lock_try;
	__Request__lock_make_stable_t Request_lock_make_stable;
	__Request__lock_handoff_t Request_lock_handoff;
	__Request__lock_handoff_accept_t Request_lock_handoff_accept;
};
#endif /* __RequestUnion__lock_set_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__lock_set_subsystem__defined
#define __Reply__lock_set_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__lock_acquire_t;
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
	} __Reply__lock_release_t;
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
	} __Reply__lock_try_t;
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
	} __Reply__lock_make_stable_t;
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
	} __Reply__lock_handoff_t;
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
	} __Reply__lock_handoff_accept_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__lock_set_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__lock_set_subsystem__defined
#define __ReplyUnion__lock_set_subsystem__defined
union __ReplyUnion__lock_set_subsystem {
	__Reply__lock_acquire_t Reply_lock_acquire;
	__Reply__lock_release_t Reply_lock_release;
	__Reply__lock_try_t Reply_lock_try;
	__Reply__lock_make_stable_t Reply_lock_make_stable;
	__Reply__lock_handoff_t Reply_lock_handoff;
	__Reply__lock_handoff_accept_t Reply_lock_handoff_accept;
};
#endif /* __RequestUnion__lock_set_subsystem__defined */

#ifndef subsystem_to_name_map_lock_set
#define subsystem_to_name_map_lock_set \
    { "lock_acquire", 617000 },\
    { "lock_release", 617001 },\
    { "lock_try", 617002 },\
    { "lock_make_stable", 617003 },\
    { "lock_handoff", 617004 },\
    { "lock_handoff_accept", 617005 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _lock_set_server_ */

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
#ifndef	_ledger_server_
#define	_ledger_server_

/* Module ledger */

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

#ifndef	ledger_MSG_COUNT
#define	ledger_MSG_COUNT	4
#endif	/* ledger_MSG_COUNT */

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


/* Routine ledger_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_create
(
	ledger_t parent_ledger,
	ledger_t ledger_ledger,
	ledger_t *new_ledger,
	ledger_item_t transfer
);

/* Routine ledger_terminate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_terminate
(
	ledger_t ledger
);

/* Routine ledger_transfer */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_transfer
(
	ledger_t parent_ledger,
	ledger_t child_ledger,
	ledger_item_t transfer
);

/* Routine ledger_read */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_read
(
	ledger_t ledger,
	ledger_item_t *balance,
	ledger_item_t *limit
);

extern boolean_t ledger_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t ledger_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct ledger_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[4];
} ledger_subsystem;

/* typedefs for all requests */

#ifndef __Request__ledger_subsystem__defined
#define __Request__ledger_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t ledger_ledger;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		ledger_item_t transfer;
	} __Request__ledger_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__ledger_terminate_t;
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
		mach_msg_port_descriptor_t child_ledger;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		ledger_item_t transfer;
	} __Request__ledger_transfer_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__ledger_read_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__ledger_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__ledger_subsystem__defined
#define __RequestUnion__ledger_subsystem__defined
union __RequestUnion__ledger_subsystem {
	__Request__ledger_create_t Request_ledger_create;
	__Request__ledger_terminate_t Request_ledger_terminate;
	__Request__ledger_transfer_t Request_ledger_transfer;
	__Request__ledger_read_t Request_ledger_read;
};
#endif /* __RequestUnion__ledger_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__ledger_subsystem__defined
#define __Reply__ledger_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t new_ledger;
		/* end of the kernel processed data */
	} __Reply__ledger_create_t;
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
	} __Reply__ledger_terminate_t;
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
	} __Reply__ledger_transfer_t;
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
		ledger_item_t balance;
		ledger_item_t limit;
	} __Reply__ledger_read_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__ledger_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__ledger_subsystem__defined
#define __ReplyUnion__ledger_subsystem__defined
union __ReplyUnion__ledger_subsystem {
	__Reply__ledger_create_t Reply_ledger_create;
	__Reply__ledger_terminate_t Reply_ledger_terminate;
	__Reply__ledger_transfer_t Reply_ledger_transfer;
	__Reply__ledger_read_t Reply_ledger_read;
};
#endif /* __RequestUnion__ledger_subsystem__defined */

#ifndef subsystem_to_name_map_ledger
#define subsystem_to_name_map_ledger \
    { "ledger_create", 5000 },\
    { "ledger_terminate", 5001 },\
    { "ledger_transfer", 5002 },\
    { "ledger_read", 5003 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _ledger_server_ */

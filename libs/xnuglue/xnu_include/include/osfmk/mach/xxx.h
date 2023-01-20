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
#ifndef _XXX_H
#define _XXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <xnu_glue.h>

#include <mach/vm_types.h>
#include <mach/vm_prot.h>
#include <mach/vm_inherit.h>
#include <mach/vm_param.h>
#include <mach/vm_statistics.h>

#include <mach/mach_types.h>
#include <mach/clock_types.h>
#include <mach/kern_return.h>
#include <mach/kmod.h>
#include <mach/memory_object_types.h>
#include <mach/task_info.h>
#include <mach/semaphore.h>
#include <mach/machine/vm_types.h>
#include <mach/message.h>

#include <kern/host.h>	/* host_priv_self */

/*
 * kern/task.h
 *
 */
void
task_deallocate(
        task_t          task);

/*
 * kern/task.h
 */
void
task_reference(
        task_t          task);

/*
 * mach/task.h
 */
kern_return_t task_info
(
        task_t target_task,
        task_flavor_t flavor,
        task_info_t task_info_out,
#ifndef L4IOKIT
        mach_msg_type_number_t *task_info_outCnt
#else
	natural_t	*task_info_outCnt
#endif
);

/*
 * mach/mig_msg.h
 */
#if 0
extern
mach_msg_return_t mach_msg_send_from_kernel
(
        mach_msg_header_t       *msg,
        mach_msg_size_t         send_size);
#endif

/*
 * mach/vm_map.h
 */
 
kern_return_t mach_make_memory_entry
(
        vm_map_t target_task,
        vm_size_t *size,
        vm_offset_t offset,
        vm_prot_t permission,
        mach_port_t *object_handle,
#ifndef L4IOKIT
        mem_entry_name_port_t parent_entry
#else
	void		*parent_entry
#endif	/* L4IOKIT */
);

/*
 * mach/vm_map.h
 */

kern_return_t mach_make_memory_entry_64
(
        vm_map_t target_task,
        memory_object_size_t *size,
        memory_object_offset_t offset,
        vm_prot_t permission,
        mach_port_t *object_handle,
#ifndef L4IOKIT
        mem_entry_name_port_t parent_entry
#else
	void	*parent_entry
#endif	/* L4IOKIT */
);

/*
 * vm/vm_user.c
 */
kern_return_t
vm_map(
        vm_map_t                target_map,
        vm_offset_t             *address,
        vm_size_t               size,
        vm_offset_t             mask,
        int                     flags,
        ipc_port_t              port,
        vm_offset_t             offset,
        boolean_t               copy,
        vm_prot_t               cur_protection,
        vm_prot_t               max_protection,
        vm_inherit_t            inheritance);

#if 0
kern_return_t vm_map_get_upl
(
        vm_map_t target_task,
        vm_address_t address,
        vm_size_t *size,
        upl_t *upl,
#ifndef L4IOKIT
        upl_page_info_array_t page_info,	/* XXX take this from Kashu*/
#else
	void	*page_info,
#endif
	mach_msg_type_number_t *page_infoCnt,
        integer_t *flags,
        integer_t force_data_sync
);
#endif

extern
kern_return_t vm_inherit
(
        vm_map_t target_task,
        vm_address_t address,
        vm_size_t size,
        vm_inherit_t new_inheritance
);

extern
kern_return_t vm_allocate
(
        vm_map_t target_task,
        vm_address_t *address,
        vm_size_t size,
        int flags
);

/* Routine vm_deallocate */
extern
kern_return_t vm_deallocate
(
        vm_map_t target_task,
        vm_address_t address,
        vm_size_t size
);

extern
kern_return_t
vm_region_64(
        vm_map_t                 map,
        vm_offset_t             *address,               /* IN/OUT */
        vm_size_t               *size,                  /* OUT */
        int flavor,                /* IN */
        int info,                  /* OUT */
        void *count,                 /* IN/OUT */
        void *object_name);           /* OUT */

#if 0
extern
kern_return_t
vm_region_64(
        vm_map_t                 map,
        vm_offset_t             *address,               /* IN/OUT */
        vm_size_t               *size,                  /* OUT */
        vm_region_flavor_t       flavor,                /* IN */
        vm_region_info_t       info,                  /* OUT */
        mach_msg_type_number_t  *count,                 /* IN/OUT */
        ipc_port_t              *object_name);           /* OUT */
#endif

/*
 * mach/host_priv.h
 *
 */
kern_return_t kmod_destroy
(
        host_priv_t host_priv,
        kmod_t module   
); 

/*
 * mach/upl.h
 *
 */
kern_return_t upl_abort
(
        upl_t upl_object,
        integer_t abort_cond
); 

kern_return_t upl_commit
(
        upl_t upl_object,
#ifndef L4IOKIT
        upl_page_info_array_t page_list,
#else
	void *page_list,
#endif
/*
 * XXXWTF: page_listCnt is in message.h, i include it and it compiles fine
 * for xnu_glue code but not in IO KIT?  WTF?!!!
 */
#ifndef L4IOKIT
        mach_msg_type_number_t page_listCnt
#else
	natural_t page_listCnt
#endif
);

kern_return_t mach_memory_object_memory_entry_64
(
        host_t host,
        boolean_t internal,
        memory_object_size_t size,
        vm_prot_t permission,
        memory_object_t pager,
        mach_port_t *entry_handle
);

#ifdef __cplusplus
};
#endif

#endif	/* _XXX_H */


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
/*
 * vm_user.c
 *
 * Geoffrey Lee < glee @ cse .unsw.edu.au >
 */

#include <assert.h>
#include <stdio.h>

#include <iguana/memsection.h>

#include <xnu_glue.h>	/* XXX DEPRECATED */

extern void *kernel_map;	/* XXX */

kern_return_t
vm_allocate(
	vm_map_t		map,
	vm_offset_t 		*addr,
	vm_size_t		size,
	int			flags
)
{
	memsection_ref_t	ref;

	assert(map == kernel_map);

	/*
	 * Yes, the correct thing to always do is to allocate vm.
	 *
	 * However, we may need to change this if we have no virt to 
	 * phys.  Thankfully, no one ever uses vm_allocate() and then does
	 * a translation.  Yet.
	 *
	 * XXX FIXME XXX
	 */
#if 1	/* XXX doesn't work.  See IOMapPages */
	ref = memsection_create(size, (uintptr_t *)addr);
#else
	printf("%s: warning: memsection_create_user() hardcoded for "
	    "vm_allocate()\n", __func__);
	ref = memsection_create_user(size, (uintptr_t *)addr);
#endif
	printf("%s: addr %p size %d, flags %d\n",
	    __func__, *addr, (int)size, (int)flags);
	assert(*addr);

	return KERN_SUCCESS;
}

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
        vm_inherit_t            inheritance)
{
	/*
	 * Let's print out all the args, to see what we need to support.
	 *
	 * We would ideally like to work out what kind of object this is,
	 * but we cannot since it is translated from the ipc port to the
	 * object.  Piece of crap.  I think that the mach_make_memory_entry()
	 * ipc ports are passed here, in which case, this is quite pants.
	 * Oh well ...
	 *
	 * -gl 
	 */
	printf("%s: called, dumping args\n", __func__);
	printf("%s: target_map %p size %d mask %d flags %d port %d offset %d "
	    "copy %d cur_protection %d max_protection %d inheritance %d\n",
	    __func__, target_map, size, mask, flags, port, offset, copy,
	    cur_protection,  max_protection, inheritance);
	printf("%s: faking what we want to do somewhat with memsections\n",
	    __func__);
	memsection_create(size, address);
	printf("%s: returning address %p\n", __func__, *address);
	return (KERN_SUCCESS);
}

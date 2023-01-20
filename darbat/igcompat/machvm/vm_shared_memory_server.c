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
#if 0
#include <debug.h>

#include <kern/task.h>
#include <mach/kern_return.h>
#include <mach/shared_memory_server.h>
#include <vm/vm_shared_memory_server.h>

kern_return_t
vm_get_shared_region(
	task_t	task,
	shared_region_mapping_t	*shared_region)
{
	*shared_region = (shared_region_mapping_t) task->system_shared_region;
	if (*shared_region) {
		assert((*shared_region)->ref_count > 0);
	}
	SHARED_REGION_DEBUG(("vm_get_shared_region(task=%p) -> %p\n",
			     task, *shared_region));
	return KERN_SUCCESS;
}
#endif

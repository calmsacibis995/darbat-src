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
#include <kern/kalloc.h>
#include <kern/misc_protos.h>
#include <kern/machine.h>
#include <mach/processor_info.h>

#include <l4/cpu_data.h>

ast_t *
ast_pending(void)
{
	return (&current_cpu_datap()->cpu_pending_ast);
}


processor_t
current_processor(void)
{
	return current_cpu_datap()->cpu_processor;
}

cpu_type_t
slot_type(
	int		slot_num)
{
	return (cpu_datap(slot_num)->cpu_type);
}

cpu_subtype_t
slot_subtype(
	int		slot_num)
{
	return (cpu_datap(slot_num)->cpu_subtype);
}

kern_return_t
cpu_info_count(
        __unused processor_flavor_t      flavor,
	unsigned int			*count)
{
	*count = 0;
	return (KERN_FAILURE);
}

/*ARGSUSED*/
kern_return_t
cpu_info(
        processor_flavor_t      flavor,
	int			slot_num,
	processor_info_t	info,
	unsigned int		*count)
{
	printf("cpu_info(%d,%d,%p,%p) not implemented\n",
		flavor, slot_num, info, count);
	return (KERN_FAILURE);
}

cpu_threadtype_t
slot_threadtype(
	int		slot_num)
{
	return (cpu_datap(slot_num)->cpu_threadtype);
}

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
#include <kern/cpu_number.h>
#include <kern/kalloc.h>
#include <kern/cpu_data.h>
#include <mach/machine.h>
#include <vm/vm_kern.h>

#include <kern/misc_protos.h>

/* #include <i386/misc_protos.h>*/

/* XXX */
#define MAX_CPUS	4
extern processor_t	cpu_processor_alloc(boolean_t is_boot_cpu);
void cpu_init(void);


cpu_data_t	cpu_data_master;
cpu_data_t	*cpu_data_ptr[MAX_CPUS] = { [0] &cpu_data_master };

struct processor	processor_master;

decl_simple_lock_data(,cpu_lock);	/* protects real_ncpus */
unsigned int	real_ncpus = 1;
unsigned int	max_ncpus = MAX_CPUS;




cpu_data_t *
cpu_data_alloc(boolean_t is_boot_cpu)
{
	cpu_data_t	*cdp;

	assert(is_boot_cpu);

	cdp = &cpu_data_master;
	if (cdp->cpu_processor == NULL) 
	{
		cdp->cpu_processor = &processor_master;
		cdp->cpu_pmap = NULL;
		cdp->cpu_this = cdp;
		cdp->cpu_int_stack_top = 0; //(vm_offset_t) eintstack;
	}

	return cdp;
}


void
cpu_init(void)
{
	cpu_data_t	*cdp;

	printf( "Getting current_cpu_datap\n" );
	cdp = current_cpu_datap();
	printf( "Got current_cpu_datap\n" );

#ifdef	MACH_BSD
	/* FIXME */
	cdp->cpu_type = CPU_TYPE_I386;
	cdp->cpu_subtype = CPU_SUBTYPE_PENTPRO;
#else
	cdp->cpu_type = cpuid_cputype(0);
	cdp->cpu_subtype = CPU_SUBTYPE_AT386;
#endif
	cdp->cpu_running = TRUE;
}

processor_t
cpu_to_processor(
	int			cpu)
{
	return cpu_datap(cpu)->cpu_processor;
}

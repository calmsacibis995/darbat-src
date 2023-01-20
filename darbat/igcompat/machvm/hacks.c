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

/* Some hacks to get mach vm working */

// #include <stdio.h>
#include <vm/vm_external.h>
#include <kern/cpu_data.h>


uint64_t    sane_size = 32 * 1024 * 1024;  /* XXX */
unsigned int vm_min_kernel_address;


void
vm_external_module_initialize(void)
{
	printf( "XXX: Skipping vm_external_module_initialize\n" );
}


void
_disable_preemption(void)
{

}

void
_enable_preemption(void)
{

}

#include <vm/vm_external.h>

void 
vm_external_destroy( vm_external_map_t map,
		     vm_size_t size )
{
	(void) map;
}


#include <vm/vm_kern.h>

void do_hack_test(void);
void do_hack_test(void)
{
	/* XXX: Test */
	kern_return_t kr;
	vm_offset_t off;
	int i;

	for( i = 0; i < 10; i++ )
	{
		printf( "about to kmem_alloc()\n" );
		kr = kmem_alloc( kernel_map, &off, 1024 );
		printf( "done kmem alloc, kr = %d, off = %p\n", 
			kr, (void*) off );
	}
	
}


/* XXX: not technicall VM */


#include <kern/timer.h>

void timer_update( timer_t		timer,
		   uint32_t	new_high,
		   uint32_t	new_low )
{
	return;
}





#if	MACH_ASSERT
#include <kern/machine.h>

/*
 * Machine-dependent routine to fill in an array with up to callstack_max
 * levels of return pc information.
 */
void machine_callstack(
	__unused natural_t	*buf,
	__unused vm_size_t	callstack_max)
{
}

#endif	/* MACH_ASSERT */


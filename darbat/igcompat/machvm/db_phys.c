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
/* darbat physical memory functions */

#include <stdlib.h>
//#include <stdio.h>
#include <assert.h>

/* mach includes */
#include <mach/vm_param.h>
#include <vm/pmap.h>

#include <igcompat/darbat.h>
#include "db_phys.h"

#include <DEBUG.h>
/* 80mb memory object */
#define PHYSMEM_PAGES 20480

static void *phys_mem;
static void *phys_end;
void *phys_next;
unsigned int pages_left;


void
db_phys_bootstrap(void)
{
	unsigned int memsize;

	printf( ">>> Making up some physical memory\n" );

	pages_left = PHYSMEM_PAGES;

	memsize = pages_left * PAGE_SIZE;

	/* create a physical object */
	phys_mem = darbat_rgn_alloc( memsize );
	phys_end = ((char*)phys_mem) + memsize;
	phys_next = phys_mem;

	printf( ">>> phys mem @ %p - %p\n", 
		phys_mem, ((char*)phys_mem) + memsize );

	assert( phys_mem != NULL );

}

void 
db_get_phys_region( pmap_paddr_t *start, pmap_paddr_t *end )
{
	assert( start != NULL );
	assert( end != NULL );

	*start = (pmap_paddr_t) phys_mem;
	*end = (pmap_paddr_t) phys_end;
}

void
vm_external_state_set(
	vm_external_map_t	map,
	vm_offset_t		offset)
{
	if (map == VM_EXTERNAL_NULL)
		return;

	assert( !"vm_external_state_set with non-null map!" );
}

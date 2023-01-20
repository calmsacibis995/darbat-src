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

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <vm/vm_kern.h>
#include <igcompat/darbat.h>

#include <vm/pmap.h>
#include <vm/vm_map.h>

#include <kern/debug.h> /* panic */

struct vm_map
{
	void *base;
	void *cur;
	vm_size_t size;
};

vm_map_t kernel_map = &(struct vm_map) { NULL, NULL, 0 };
void _kmem_init( void );

/* allocate for a pre-allocated vm_map */
static int
map_alloc( vm_map_t map, vm_size_t size )
{
	/* allocate the actual space */
	map->base = darbat_rgn_alloc( size );
	if( map->base == NULL )
	{
		printf( "failed to alloc size 0x%x\n", size );
		free(map);
		return KERN_FAILURE;
	}
	/* fill out the rest of the map */
	map->cur = map->base;
	map->size = size;
	
	return KERN_SUCCESS;
}

#define KOBJ_SIZE (128 * 1024 * 1024)

void
_kmem_init( void )
{
	void *kobj;

	/* allocate a kernel map object */
	kobj = darbat_rgn_alloc( KOBJ_SIZE );
	if( kobj == NULL )
		panic( "couldn't rgn alloc for kernel map" );

	/* setup the kernel map, like in vm_kern.c */
	kernel_map = vm_map_create(pmap_kernel(), (unsigned int) kobj,
				   ((unsigned int)kobj) + KOBJ_SIZE, FALSE);
	if( kernel_map == NULL )
		panic( "error creating kernel_map" );
}

kern_return_t 
kmem_suballoc( vm_map_t	        parent,
	       vm_offset_t	*addr,
	       vm_size_t	size,
	       boolean_t	pageable,
	       boolean_t	anywhere,
	       vm_map_t	        *new_map )
{
	struct vm_map *map;

	/* don't handle fixed alloc yet... if such a thing exists */
	assert( anywhere == VM_FLAGS_ANYWHERE );

	/* allocate the map */
	map = malloc( sizeof( *map ) );
	if( map == NULL )
		return KERN_FAILURE;

	if( map_alloc( map, size ) )
	    return KERN_FAILURE;

	/* store the out vars */
	*addr = (vm_offset_t) map->base;
	*new_map = map;
	
	return (KERN_SUCCESS);
}

kern_return_t
kernel_memory_allocate(
	register vm_map_t	map,
	register vm_offset_t	*addrp,
	register vm_size_t	size,
	register vm_offset_t	mask,
	int			flags)
{
	assert( map != NULL );

	/* check the length */
	if( ((uintptr_t)map->cur - (uintptr_t)map->base + size) > map->size )
	{
		printf( "map->cur %p\n", map->cur );
		printf( "map->base %p\n", map->base );
		printf( "map->size %x\n", map->size );
		printf( "size is 0x%x\n", size );
		panic( "map out of space failure!" );
		return KERN_FAILURE;
	}

	/* move the pointers & store out val */
	*addrp = (vm_offset_t) map->cur;
	map->cur = (char*)map->cur + size;

	return KERN_SUCCESS;
}

kern_return_t
kmem_alloc(
	vm_map_t	map,
	vm_offset_t	*addrp,
	vm_size_t	size)
{
	return kernel_memory_allocate(map, addrp, size, 0, 0);
}


void
kmem_free( vm_map_t	map,
	   vm_offset_t	addr,
	   vm_size_t	size )
{
	/* FIXME:  :) */
}


#endif

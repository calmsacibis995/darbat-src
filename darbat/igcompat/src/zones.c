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
#include <stdlib.h>
#include <string.h>

#include <kern/zalloc.h>
#include <assert.h>

extern zone_t kalloc_zone(vm_size_t);	/* XXX */

struct zone
{
	vm_size_t	size;   /* the size of an element */
	vm_size_t	max;    /* maximum memory to use */
	vm_size_t	alloc;  /* allocation size */
	char	       *name;   /* a name for the zone */
};

zone_t
zinit(	vm_size_t	size,		/* the size of an element */
	vm_size_t	max,		/* maximum memory to use */
	vm_size_t	alloc,		/* allocation size */
	const char	*name ) 	/* a name for the zone */
{
	zone_t z = NULL;

	z = malloc( sizeof( *z ) );

	if( z != NULL )
	{
		z->name = malloc( strlen( name ) + 1 );
		if( z == NULL )
		{
			free( z );
			return NULL;
		}
		
		strcpy( z->name, name );
		z->size = size;
		z->max = max;
		z->alloc = alloc;
	}

	return z;
}

void *
zalloc( register zone_t zone )
{
	if( zone == NULL )
		printf( "NULL zone, caller %p\n", __builtin_return_address(0) );
	assert( zone != NULL );

	return malloc( zone->size );
}

void *
zget( register zone_t zone )
{
	return zalloc( zone );
}

void *
zalloc_noblock( register zone_t zone )
{
	assert( !"zalloc_noblock" );
	return NULL;
}


zone_t
kalloc_zone( vm_size_t size )
{
	return 0;
}


void
zfree( register zone_t zone, void *addr )
{
	free( addr );
	return;
}

#endif

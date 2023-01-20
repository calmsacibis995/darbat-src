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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <mach/mach_types.h>

#include <igcompat/compat.h> /* bzero */
#include <kern/debug.h>

#include "tlpt.h"

#define dprintf(args...)

/* page table entry */
struct tlpte
{
	unsigned int pn : 20;
	unsigned int prot : 3;
	unsigned int valid : 1;
    unsigned int referenced : 1;
    unsigned int modified : 1;
};

/* leaf node */
struct tlpt_leaf
{
	struct tlpte ptes[1024];
};

/* root pagetable */
struct tlpt
{
	struct tlpt_leaf *leaves[1024];
};


tlpt_t 
tlpt_create(void)
{
	tlpt_t pt;

	pt = malloc( sizeof( *pt ) );
	if( pt == NULL )
		return NULL;

	bzero( pt, sizeof( *pt ) );

	return pt;
}

void 
tlpt_destroy(tlpt_t pt)
{
	int i;
	assert( pt != NULL );

	for( i = 0; i < 1024; i++ ) 
		if (pt->leaves[i])
			free( pt->leaves[i] );

	free( pt );
}

static void
split_addr( void *addr, int *ridx, int *lidx )
{
	unsigned int tmp;

	tmp = (unsigned int) addr;

	/* offset, leaf */
	tmp >>= 12;
	*lidx = tmp & 0x3ff;

	/* leaf, root */
	tmp >>= 10;
	*ridx = tmp & 0x3ff;
}

int 
tlpt_insert(tlpt_t pt, void *addr, ppnum_t pn, vm_prot_t prot, int referenced, int modified )
{
	int ridx, lidx;
	struct tlpt_leaf *leaf;

	assert(pt != NULL);

	dprintf( "tlpt_insert pt %p, va %p, pn %x, prot %d\n", 
		pt, addr, pn, prot );

	split_addr( addr, &ridx, &lidx );
	
	leaf = pt->leaves[ridx];

	if( leaf == NULL )
	{
		leaf = malloc ( sizeof( *leaf ) );
		if( leaf == NULL )
			panic( "OOM in tlpt" );

		bzero(leaf, sizeof(*leaf));
		pt->leaves[ridx] = leaf;
	}

	leaf->ptes[lidx].pn = pn;
	leaf->ptes[lidx].prot = prot;
	leaf->ptes[lidx].valid = 1;

	return 0;
}

int 
tlpt_lookup( tlpt_t pt, void *addr, ppnum_t *pn, vm_prot_t *prot, int *referenced, int *modified)
{
	int ridx, lidx;
	struct tlpt_leaf *leaf;

	assert(pt != NULL);

	split_addr( addr, &ridx, &lidx );
	
	leaf = pt->leaves[ridx];

	if( leaf == NULL )
		return 1;

	if( leaf->ptes[lidx].valid == 0 )
		return 1;

	*pn = leaf->ptes[lidx].pn;
	*prot = leaf->ptes[lidx].prot;
	*referenced = leaf->ptes[lidx].referenced;
	*modified = leaf->ptes[lidx].modified;

	return 0;
}

int 
tlpt_delete(tlpt_t pt, void *addr)
{
	int ridx, lidx;
	struct tlpt_leaf *leaf;

	assert(pt != NULL);

	split_addr( addr, &ridx, &lidx );
	
	leaf = pt->leaves[ridx];

	if( leaf == NULL )
		return 1;

	if( leaf->ptes[lidx].valid == 0 )
		return 1;

	leaf->ptes[lidx].valid = 0;

	return 0;
}


void
tlpt_enum( tlpt_t pt )
{
	int i, j;
	struct tlpt_leaf *leaf;

	for( i = 0; i < 1024; i++ )
	{
		leaf = pt->leaves[i];

		if( leaf == NULL )
			continue;

		for( j = 0; j < 1024; j++ )
			if( leaf->ptes[j].valid )
				panic( "TLPT not empty!\n" );
	}
}

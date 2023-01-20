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
/* phys to virt mapping table */

#include <stdlib.h>
#include <string.h>

#include <vm/pmap.h>
#include <igcompat/darbat.h>
#include <igcompat/compat.h>

#include <l4/kdebug.h>

#include "db_phys.h"
#include "ptov.h"

#include <DEBUG.h>

/* XXX */
#define PAGEBITS 12

#define dprintf(args...)

/*
 *	For each vm_page_t, there is a list of all currently
 *	valid virtual mappings of that page.  An entry is
 *	a pv_entry_t; the list is the pv_table.
 */

/* see ptov.h for the typedef */
struct pv_entry {
	struct pv_entry	*next;		/* next pv_entry */
	pmap_t		pmap;		/* pmap where mapping lies */
	vm_offset_t	va;		/* virtual address for mapping */
};

#define PV_ENTRY_NULL	((pv_entry_t) 0)

static pv_entry_t *pv_head_table;	/* array of entries, one per page */
static ppnum_t pgnum_start, pgnum_end;  /* start and end of the PV array */

static int initted = 0;

static int
ppnum_to_idx( ppnum_t addr )
{
/*
	printf( "addr: 0x%x\n", (int) addr );
	printf( "pgnum_start: 0x%x\n", (int) pgnum_start );
*/
	assert( addr >= pgnum_start );
		
	addr -= pgnum_start;

	assert( addr < pgnum_end );

	return (int) addr;
}

/* create the ptov table */
kern_return_t
ptov_init( void )
{
	int pg_len;
	pmap_paddr_t start, end;

	assert( !initted );

	/* find the bounds */
	db_get_phys_region( &start, &end );

	/* set the bounds */
	pgnum_start = start >> PAGEBITS;
	pgnum_end = end >> PAGEBITS;

	pg_len = pgnum_end - pgnum_start;

	dprintf( "pages %d - %d = %d ptov entries\n", 
		pgnum_start, pgnum_end, pg_len );

	/* allocate & clear the table */
	pv_head_table = malloc( pg_len * sizeof( pv_entry_t ) );

	dprintf( "pv_head_table is %p\n", pv_head_table );

	if( pv_head_table == NULL )
		return KERN_FAILURE;

	bzero( pv_head_table, pg_len * sizeof( pv_entry_t ) );

	initted = 1;

	return KERN_SUCCESS;
}


kern_return_t
ptov_add( pmap_t pmap, vm_offset_t va, ppnum_t addr )
{
	int pos;
	pv_entry_t ent;

	assert( initted );

	dprintf( "ptov_add on map %p, va %p, pn %x\n", 
		pmap, (void*) va, (int) addr );

	/* find the position in the table */
	pos = ppnum_to_idx( addr );

	/* get an entry & fill it out */
	ent = malloc( sizeof( *ent ) );

	if( ent == NULL )
		return KERN_FAILURE;

	/* fill out fields */
	ent->va = va;
	ent->pmap = pmap;

	/* insert it */
	ent->next = pv_head_table[pos];
	pv_head_table[pos] = ent;
      
	return KERN_SUCCESS;
}


kern_return_t
ptov_del( pmap_t pmap, vm_offset_t va, ppnum_t addr )
{
	int pos;
	pv_entry_t prev, ent;

	assert( initted );

	dprintf( "ptov_del on map %p, addr %p, %x\n", 
		pmap, (void*) va, addr );

	/* find the position in the table */
	pos = ppnum_to_idx( addr );

	/* find the entry */
	prev = NULL;
	ent = pv_head_table[pos];

	while( ent != NULL )
	{
		if( ent->pmap == pmap && ent->va == va )
			break;

		prev = ent;
		ent = ent->next;
	}

	/* bah! not there! */
	if( ent == NULL )
		return KERN_FAILURE;

	/* clean it up */
	if( prev == NULL )
		pv_head_table[pos] = ent->next;
	else
		prev->next = ent->next;

	free( ent );

	/* XXX: debug check */
	{
		/* easiest to start at the beginning again */
		ent = pv_head_table[pos];
			
		while( ent != NULL )
		{
			if( ent->pmap == pmap && ent->va == va )
				panic( "dup in ptov_del??\n" );

			ent = ent->next;
		}
	}

	return KERN_SUCCESS;
}


pv_entry_t
ptov_enum_start( ppnum_t addr )
{
	int pos;

	assert( initted );

	/* find the position in the table */
	pos = ppnum_to_idx( addr );

	/* just return the pointer */
	return pv_head_table[pos];
}

/* gets the details from the *current, passed in pv_entry* and returns
 * the *next* entry
 */
pv_entry_t
ptov_enum_next( pv_entry_t cur, pmap_t *pmap, vm_offset_t *va )
{
	assert( cur != NULL );

	*pmap = cur->pmap;
	*va = cur->va;

	return cur->next;
}

/* clear out a pagelist */
void
ptov_flush_pagelist( ppnum_t addr )
{
	int pos;
	pv_entry_t next, ent;

	assert( initted );

	dprintf( "ptov_flush_pagelist on addr %x\n", (int) addr );

	/* find the position in the table */
	pos = ppnum_to_idx( addr );


	/* get the guy */
	ent = pv_head_table[pos];
	pv_head_table[pos] = NULL;

	/* shouldn't do this */
	if( ent == NULL )
		panic( "Deleting empty ptov list!\n" );

	while( ent != NULL )
	{
		next = ent->next;

		free(ent);

		ent = next;
	}
}

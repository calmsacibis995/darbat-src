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
#include <string.h>
#include <assert.h>

#include <kern/locks.h>
#include <kern/kalloc.h>

#include <igcompat/compat.h>

/*** lock grp stuff ***/

lck_grp_t *
lck_grp_alloc_init(
	const char*	grp_name,
	lck_grp_attr_t	*attr)
{
	void *grp;

	grp = kalloc(1);

	return grp;
}

lck_grp_attr_t *
lck_grp_attr_alloc_init( void )
{
	void *attr;
	attr = kalloc(1);
	return attr;
}

void 
lck_grp_attr_free( lck_grp_attr_t *attr )
{
	kfree( attr, 1 );
}

void
lck_grp_free( lck_grp_t *grp )
{
	kfree( grp, 1 );
}

void 
lck_grp_attr_setstat( lck_grp_attr_t  *attr )
{
	(void) attr;
}


void 
lck_grp_attr_setdefault( lck_grp_attr_t	*attr )
{
	(void) attr;
}


lck_attr_t *
lck_attr_alloc_init( void )
{
	void *attr;
	attr = kalloc(1);
	return attr;
}

void
lck_attr_setdefault( lck_attr_t		*attr )
{
	(void) attr;
}

void
lck_attr_setdebug( lck_attr_t		*attr )
{
	(void) attr;
}

void
lck_attr_free( lck_attr_t		*attr)
{
	kfree( attr, 1 );
}

/*** mutex (sleep) lockes ***/

lck_mtx_t *
lck_mtx_alloc_init( lck_grp_t		*grp,
		    lck_attr_t		*attr )
{
	lck_mtx_t *lck;

	if( (lck = kalloc( sizeof(lck_mtx_t))) )
		lck_mtx_init( lck, grp, attr );

	return lck;
}

void 
lck_mtx_init( lck_mtx_t		*lck, 
	      lck_grp_t		*grp,
	      lck_attr_t	*attr )
{
	bzero( lck, sizeof( *lck ) );
}


void
lck_mtx_lock( lck_mtx_t *lck )
{
	(void) lck;
}

boolean_t
lck_mtx_try_lock( lck_mtx_t *lck )
{
	return 1;
}


void
lck_mtx_unlock( lck_mtx_t *lck )
{
	(void) lck;
}

void
lck_mtx_assert( lck_mtx_t	*lck,
		unsigned int	type )
{
	(void) lck;
}

void
lck_mtx_destroy( lck_mtx_t		*lck,
		 lck_grp_t		*grp )
{
	// Eeep! don't do this - some are static!!
	// kfree( lck, sizeof(lck_mtx_t) );
}

/*** read/write locks ***/

void
lck_rw_init( lck_rw_t		*lck, 
	     lck_grp_t		*grp,
	     lck_attr_t		*attr )
{
	bzero( lck, sizeof( *lck ) );
}

lck_rw_t *
lck_rw_alloc_init( lck_grp_t		*grp,
		   lck_attr_t		*attr )
{
	lck_rw_t *lck;

	if( (lck = kalloc( sizeof(lck_rw_t))) )
		lck_rw_init( lck, grp, attr );

	return lck;
}

void
lck_rw_lock_shared( lck_rw_t *lck)
{
	/* dum de dum */
	return;
}

lck_rw_type_t
lck_rw_done( lck_rw_t *lck)
{
	/* FIXME: may break some stuff? */
	return LCK_RW_TYPE_EXCLUSIVE;
}

void
lck_rw_lock_exclusive( lck_rw_t *lck )
{
	(void) lck;
}

void
lck_rw_unlock_exclusive( lck_rw_t *lck )
{
	(void) lck;
}


void
lck_rw_destroy( lck_rw_t  *lck,
		lck_grp_t *grp )
{
	// Don't do this! some are static!
	// kfree( lck, sizeof(lck_rw_t) );
}


/*** spin locks ***/

void
lck_spin_init( lck_spin_t		*lck, 
	       lck_grp_t		*grp,
	       lck_attr_t		*attr )
{
	bzero( lck, sizeof( *lck ) );
}

lck_spin_t *
lck_spin_alloc_init( lck_grp_t		*grp,
		     lck_attr_t		*attr )
{
	lck_spin_t *lck;

	if( (lck = kalloc( sizeof(lck_spin_t))) )
		lck_spin_init( lck, grp, attr );

	return lck;
}


#include <mach/semaphore.h>

kern_return_t
semaphore_wait( semaphore_t semaphore )
{
	return KERN_SUCCESS;
}


kern_return_t
semaphore_signal( semaphore_t semaphore )
{
	return KERN_SUCCESS;
}

#endif /* 0 */

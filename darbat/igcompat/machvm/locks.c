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
#include <kern/lock.h>

#include <igcompat/compat.h>

/* machvm mutex aliases */
/* XXX: FIXME: actually make these aliases for the BSD functions:) */
/* can we do this? they seem more different...? */

void
mutex_init( mutex_t *mutex, unsigned short tag)
{
	bzero( mutex, sizeof(*mutex) );

	// mtx->tag = tag;
	mutex->lck_mtx.lck_mtx_sw.lck_mtxi.lck_mtxi_tag = tag;
}


void 
mutex_lock( mutex_t *mutex )
{
	(void) mutex;
}

void 
mutex_unlock( mutex_t *mutex )
{
	(void) mutex;
}

boolean_t
mutex_try( mutex_t *mutex )
{
	(void) mutex;

	return TRUE; /* they get the 'lock' */
}


/* mach simple lock (spinlock) aliases */

void
usimple_lock_init(
	usimple_lock_t	l,
	__unused unsigned short	tag)
{
	(void) l;
}

void
usimple_lock( usimple_lock_t l )
{
	(void) l;
}

void
usimple_unlock( usimple_lock_t  l )
{
	(void) l;
}


/* mach read/write locks */

void
lock_init( lock_t *l,
	   boolean_t can_sleep,
	   __unused unsigned short tag,
	   unsigned short tag1)
{
	(void) l;
}

void
lock_write( register lock_t * l )
{
	(void) l;
}

void
lock_read( register lock_t * l )
{
	(void) l;
}

boolean_t
lock_read_to_write( register lock_t * l )
{
	(void) l;

	return (FALSE);
}

void
lock_write_to_read( register lock_t * l )
{
	(void) l;
}


void
lock_done( register lock_t * l )
{
	(void) l;
}
#endif /* 0 */

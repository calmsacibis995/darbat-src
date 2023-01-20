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
/*
 * thread.c
 *
 * XXX I think we need to redo the locking, at least rethink about
 * how we lock this.
 */

#include <xnucompat.h>

#include <kern/locks.h>

static struct xnu_thread *allthreads;
static struct spool	*spoolhead;
static lck_spin_t	spoollck;

void
spool_init(void)
{
	struct spool	*p;
	uintptr_t	addr;
	int		i;

	for (i = 0; i < SPOOLSIZ; i++) {
		memsection_create_direct(XNUSTACKSIZ, &addr);
		assert(addr);
		p = (struct spool *)addr;
		p->next = spoolhead;
		spoolhead = p;
	}

	lck_spin_init(&spoollck, NULL, NULL);
}

void *
spool_alloc(void)
{
	void	*p;

	lck_spin_lock(&spoollck);
	p = spoolhead;
	spoolhead = spoolhead->next;
	lck_spin_unlock(&spoollck);

	if (!p)
		assert(!"out of stack, please add more in SPOOLSIZ");

	return (p);
}

void
spool_free(s)
	void	*s;
{
	struct spool	*p = (struct spool *)s;

	lck_spin_lock(&spoollck);
	p->next = spoolhead;
	spoolhead = p;
	lck_spin_unlock(&spoollck);
}

void
xnu_thread_add(struct xnu_thread *thrd)
{

	lck_spin_lock(xnulck);
	thrd->next = allthreads;
	allthreads = thrd;
	lck_spin_unlock(xnulck);

	return;
}

struct xnu_thread *
xnu_thread_lookup(L4_ThreadId_t	tid)
{
	struct xnu_thread 	*t;

	for (t = allthreads; t; t = t->next) {
		if (t->l4tid.raw == tid.raw)
			return(t);
	}

	return (NULL);
}

void
xnu_thread_delete(L4_ThreadId_t	tid)
{
	void			*stackbase;
	struct xnu_thread	*prev, *cur;

	lck_spin_lock(xnulck);

	for (prev = NULL, cur = allthreads; cur; prev = cur, cur = cur->next) {

		if (cur->l4tid.raw != tid.raw)
			continue;

		if (prev)
			prev->next = cur->next;
		else
			allthreads = cur->next;

		stackbase = cur->stackbase;
		xnu_free(cur);
		break;
	}

	lck_spin_unlock(xnulck);

	/*
	 * XXX do not do this because currently Iguana is broken, gives
	 * XXX you the memsection, but does not grant you access to it
	 *
	 * XXX instead we hack around this with spools.
	 */
#if 0
	memsection_delete(ref);
#endif
	spool_free(stackbase);
}


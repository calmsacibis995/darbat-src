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
 * xnucompat.h
 *
 */

#ifndef _XNU_COMPAT_H
#define _XNU_COMPAT_H

#include <sys/cdefs.h>

#include <stddef.h>	/* size_t */

#include <l4/types.h>

__BEGIN_DECLS
#include <ll.h>		/* linked list XXX: get rid of these sucky list! */
#include <kern/locks.h>	/* lck_spin_t */

/*
 * pull in panic from osfmk
 *
 */
#include <kern/debug.h>

/*
 * BSD string functions
 */
extern void bcopy(const void *src, void *dst, size_t);
extern void bzero(void *, size_t);
extern int bcmp(const void *, const void *, size_t);

/*
 * l4-xnu stuff
 */

extern void l4intrinit(void);
extern void l4intr(void);
extern L4_ThreadId_t l4intrgettid(void);

extern void *xnu_malloc(size_t);
extern void xnu_free(void *);

extern lck_spin_t *xnulck;	/* global lock on the xnu subsystem */

/*
 * 32K for stack
 *
 */
#define XNUSTACKSIZ	0x8000

extern void __xnu_thread_stub(void);
extern int testandset(volatile int *);

extern void thread_call_init(void);

/*
 * The reaper.  This is all because Iguana is so miserly and does not
 * clean up the stack for us.
 */
void reaperinit(void);
extern L4_ThreadId_t reapertid;

__END_DECLS

/*
 * simple waitqueues
 */
struct waitqitem {   
        L4_Word_t event;        /* wait channel */
        L4_ThreadId_t tid;      /* waiter's thread Id */
        struct waitqitem *next; /* next entry */
};

/*
 * l4-xnu semaphore internals
 * 
 */
struct sem {
	int val;		/* current value */
	lck_spin_t lck;		/* lock */
	struct ll *ll;		/* list of waiters */
};

/*
 * xnu emulation threads internal 
 *
 */
struct xnu_thread {
	L4_ThreadId_t		l4tid;		/* L4 Thread Id */
	L4_Word_t		wchan;		/* wait channel */
	L4_Word_t		sp;		/* stack pointer */
	void			*stackbase;	/* XXX: for spools */
	memsection_ref_t	stackref;	/* stack memsection ref */
	struct xnu_thread	*next;		/* next ptr */
};

/*
 * stack pool
 */
struct spool {
	memsection_ref_t	ref;
	struct spool		*next;
};

#define	SPOOLSIZ	50

__BEGIN_DECLS
void spool_init(void);
void *spool_alloc(void);
void spool_free(void *);
void xnu_thread_add(struct xnu_thread *);
void xnu_thread_delete(L4_ThreadId_t);
struct xnu_thread *xnu_thread_lookup(L4_ThreadId_t);

/*
 * Initialization
 *
 */
void xnuinit(void);
void bsdinit(void);

/*
 * Serial hacks
 *
 */
extern struct ll 	*ttyfifo;
extern L4_ThreadId_t	serialreadtid;

/*
 * some osfmk/bsd stuff
 *
 */
extern int hz;	/* XXX bogus */
__END_DECLS

#endif	/* _XNU_COMPAT_H */


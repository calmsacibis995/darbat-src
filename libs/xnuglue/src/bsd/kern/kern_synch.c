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
 * kern_synch.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <sys/systm.h>
#include <sys/types.h>
#include <sys/proc.h>

#include <kern/debug.h>
#include <kern/sched_prim.h>

#include <l4/ipc.h>

#include <stdio.h>

/*
 * XXX
 *
 * In xnu/bsd, tsleep() calls _sleep(), which could return ERESTART,
 * EINTR, or EWOULDBLOCK depending on what happens and what flags
 * etc.
 * 
 * We don't handle any of this, we just return 0.
 */
int
tsleep(
	void		*chan,
	int		pri,
	const char	*wmsg,
	int		timo)
{
	wait_result_t	res;

	if (timo)
		printf("%s: sleeping without regard of timo %d\n", 
		    __func__, timo);

	res = assert_wait((event_t)chan, THREAD_UNINT/*XXX?*/);
	if (res != THREAD_WAITING)
		panic("assert_wait");

	(void)thread_block(THREAD_CONTINUE_NULL);

	return (0);	/* XXX */
}

void
wakeup(chan)
	register void *chan;
{
	thread_wakeup_prim((caddr_t)chan, FALSE, THREAD_AWAKENED);
}


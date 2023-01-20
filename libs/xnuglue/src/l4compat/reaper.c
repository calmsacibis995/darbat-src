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
 * reaper.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

/*
 * This is a server which sits on a loop waiting for threads to 
 * tell it that it wishes to commit seppuku.
 *
 * This is all because Iguana is so miserly and does not clean up the
 * stack for us when we terminate a thread.
 *
 * There are other leaks as well, most notably, the tls variables
 * get leaked on thread exit.
 */

#include <l4/ipc.h>
#include <l4/kdebug.h>

#include <xnucompat.h>

#include <stdio.h>

#include <iguana/memsection.h>
#include <iguana/thread.h>

L4_ThreadId_t	reapertid;
static L4_Word_t reaperstack[0x1000];
static void reaper(void);

static void
reaper(void)
{
	L4_ThreadId_t	tid;
	L4_MsgTag_t	tag;

	printf("reaper: initializing\n");

	for (;;) {

		tag = L4_Wait(&tid);
		assert(L4_IpcSucceeded(tag));

		/*
		 * Help it die.
		 *
		 * XXX subtle: delete it from the xnu thread structure
		 * first.  The thread ids may be reused and then they
		 * may sleep, and we may end up with the wrong result.
		 */
		xnu_thread_delete(tid);
		thread_delete(tid);
	}

	/* NOTREACHED */
}


void
reaperinit(void)
{
	thread_ref_t	t;
	void		**stack;

	t = thread_create_priority(0x64, &reapertid);
	L4_KDB_SetThreadName(reapertid, "reaper");

	stack = (void *)&reaperstack[0x1000-1];
	stack--;
	*stack = reaper;
	stack--;
	*stack = NULL;	/*NOARG*/

	thread_start(t, (uintptr_t)__xnu_thread_stub, (uintptr_t)stack);
}


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
 * l4intr.c
 *
 */

#include <xnucompat.h>

#include <l4/kdebug.h>
#include <l4/types.h>
#include <l4/ipc.h>
#include <l4/thread.h>
#include <l4/schedule.h>

/*
 * osfmk/l4
 *
 */
#include <l4/machine_routines.h>

#include <kern/locks.h>

#include <assert.h>
#include <stdio.h>

#include <iguana/hardware.h>
#include <iguana/thread.h>

#include <IOKit/IOReturn.h>		/* KIO... */

#include <fb.h>					/* Techfest demo */
extern int reportIRControllerInterrupts;	/* Techfest demo */
/*
 * XXX
 *
 */
#define L4_INTR	0xfff	/* XXX 64bit */

L4_ThreadId_t	l4intrmaintid;

static L4_Word_t	_l4intrmainstack[0x1000];

IOInterruptHandler	l4intrhandler;
void			*l4intrtarget;
void			*l4intrrefCon;
void			*l4intrnub;

int	l4intrsource;
int	dointr[255/*XXX*/];

L4_ThreadId_t
l4intrgettid(void)
{

	return l4intrmaintid;
}

extern lck_mtx_t	*interrupt_mutex;

void
l4intr(void)
{
	L4_Msg_t	msg;
	L4_ThreadId_t	tid;
	L4_MsgTag_t	tag;
	L4_Word_t	intr;

again:
	tag = L4_Wait(&tid);

	for (;;) {
		if (L4_IpcFailed(tag)) {
			printf("l4intr: failed ipc from 0x%lx\n", tid.raw);
			goto again;
		}

		L4_MsgStore(tag, &msg);
		intr = L4_ThreadNo(tid);

		if ((L4_MsgLabel(&msg) >> 0x4/*XXXMAGIC*/) != L4_INTR) {
			printf("l4intr: ipc from 0x%lx not of type L4INTR\n",
			     tid.raw);
			goto again;
		}

#if 0
		if (intr >= kSystemIRQCount) {
			printf("l4intr: intr %d too big from 0x%lx\n", 
			    (int)intr, tid.raw);
			goto again;
		}
#endif

		if (l4intrhandler)
			l4intrhandler(
				l4intrtarget,
				l4intrrefCon,
				l4intrnub,
				intr);

		/*
		 * We try to do this from the PIC controller.
		 */
		goto again;
	}

	/* NOTREACHED */
}

void
l4intrinit(void)
{
	thread_ref_t	t;
	void		**stack;

	t = thread_create_priority(100, &l4intrmaintid);
	L4_KDB_SetThreadName(l4intrmaintid, "l4intr");

	stack = (void *)&_l4intrmainstack[0x1000-1];
	stack--;
	*stack = l4intr;
	stack--;
	*stack = NULL;	/*NOARG*/

	/*
	 * Interrupts are up.
	 *
	 */
	interrupt_mutex = lck_mtx_alloc_init(NULL, NULL);
	if (!interrupt_mutex)
		assert(!"shit, no interrupt mutex");

	thread_start(t, (uintptr_t)__xnu_thread_stub, (uintptr_t)stack);
}

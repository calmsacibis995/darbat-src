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
 */

#include <stdio.h>

#include <l4/kdebug.h>
#include <l4/types.h>
#include <l4/ipc.h>
#include <l4/thread.h>

#include <iguana/thread.h>
#include <iguana/memsection.h>

#include <xnucompat.h>
#include <xnu_glue.h>

#include <kern/kalloc.h>
#include <kern/thread.h>
#include <kern/thread_call.h>

#include <timer/timer.h>

static int instance;

/*
 * IOKit uses this.
 *
 */
kern_return_t
kernel_thread_start(
	thread_continue_t	fcn,
	void			*param,
	thread_t		*new_thread)
{
	L4_ThreadId_t		l4tid;
	thread_t		igtid;
	memsection_ref_t	ref;
	void			*stackbase ,**stack_top, **_stack_top;
	char			name[12];
	struct xnu_thread	*xnuthrd;
	int			prio = 0x64;

	stackbase = stack_top = spool_alloc();
	/*
	 * XXX maybe we should not panic.
	 */
	if (!stack_top)
		panic("kernel_thread_start: out of memory");

	_stack_top = stack_top = (void **)((uintptr_t)stack_top + XNUSTACKSIZ);

	/*
	 * Yep.  __xnu_thread_stub (which I stole from __thread_stub in 
	 * Iguana) is backwards.  *sigh* ... what a crock.
	 */

	stack_top--;
	*stack_top = fcn;
	stack_top--;
	*stack_top = param;

	sprintf(name, "Mach%d", instance++);
	igtid = thread_create_priority(prio, &l4tid);
	L4_KDB_SetThreadName(l4tid, name);

	xnuthrd = kalloc(sizeof(struct xnu_thread));

	xnuthrd->stackbase = stackbase;
	xnuthrd->l4tid.raw = l4tid.raw;
	xnuthrd->wchan = 0;			/* not waiting */
	xnuthrd->sp = (uintptr_t)_stack_top;	/* top of stack */

	xnu_thread_add(xnuthrd);

	/*
	 * Kick it
	 *
	 */
	thread_start(igtid,
	    (uintptr_t)__xnu_thread_stub,
	    (uintptr_t)stack_top);

	if (new_thread)
		(*(L4_ThreadId_t *)new_thread).raw = L4_Myself().raw;

	return KERN_SUCCESS;
}

thread_t
kernel_thread(task_t	task, void (*startfunc)(void))
{
	thread_t	t;

	/*
	 * XXX check for error?
	 *
	 */
	(void)kernel_thread_start((thread_continue_t)startfunc, NULL, &t);

	return (t);
}

extern void __tls_free(void);

kern_return_t
thread_terminate(thread_t	t)
{
	/*
	 * XXX
	 * FIXME
	 */

	if (L4_Myself().raw != t)
		panic("not killing myself");

	/*
	 * XXX 
	 *
	 * There is some Ig-ism here, since Iguana is miserable and
	 * we need to deallocate these resorces which it has initted
	 * behind our backs.
	 */
	__tls_free();
	timer_free();

	/*
	 * Make it sleep in the kernel while the reaper kills us.  Since
	 * the reaper never replies, this is quite convenient.
	 */
	(void)L4_Call(reapertid);

	/* NOTREACHED */
	/*
	 * For this test to work, you must disable the freeing of the
	 * stack (otherwise it is trashed, and you may or may not get
	 * fairly strange results.
	 */
	printf("%s: bug\n", __func__);
	assert(!"shit");

	return KERN_SUCCESS;
}

/*
 * XXX FIXME XXX
 * 
 * THIS DOES NOT DO WHAT IT ADVERTISES TO!
 *
 * In particular, a funnel is a special type of "lock", it gets dropped
 * when the holding thread gets rescheduled, and gets reacquired when
 * the thread is scheduled again.  What this effectively means is
 * that a critical section will not be running on another CPU when it
 * is already running, but does not guarantee that the code will not
 * be run while the funnel is "acquired".
 *
 * For now, what we do is this: we just wrap it around the global spinlock,
 * though, this may or may not cause problems, performance, semantic
 * or otherwise.  This current implementation will have problems, in 
 * particular, it does not allow for recursiveness.
 */
boolean_t
thread_funnel_set(
	funnel_t	*funnel,
	boolean_t	funneled)
{
#if 0
	lck_mtx_t	*lck = (lck_mtx_t *)funnel;
	/*
	 * XXX HACK XXX
	 *
	 * funnel_t would be big enough for this.
	 */
	if (funneled)
		lck_mtx_lock(lck);
	else
		lck_mtx_unlock(lck);

#endif
	return (funneled) ? FALSE : TRUE;
}


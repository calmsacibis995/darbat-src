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
 * thread_call.c
 *
 * Documentation
 *
 * Refer to osfmk/kern/thread_call.c, there is some source code commentry
 * there at the beginning of some relevant functions.
 */

/*
 * glue stuff 
 */
#include <xnu_glue.h>
#include <xnucompat.h>

/*
 * osfmk
 */
#include <kern/kern_types.h>
#include <kern/kalloc.h>
#include <kern/thread.h>
#include <kern/thread_call.h>
#include <kern/locks.h>

/*
 * Ig
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ll.h>
#include <timer/timer.h>

/*
 * l4
 */
#include <l4/ipc.h>
#include <l4/schedule.h>
#include <l4/kdebug.h>

struct callitem {
	thread_call_t	call;
	L4_Clock_t	deadline;
};

struct	ll		*timerlist;
struct	ll		*calllist;

/*
 * see also: xnu_glue/src/xnu_sched.c
 *
 */
/* XXX: bigger stack solves all! :)  CEG */
static	L4_Word_t	_threadcallstack[0x4000];

static void mach_callout(void *);
static void threadcallserv(void);

static void
mach_callout(void *arg)
{
	thread_call_t	call = (thread_call_t)arg;

	call->func(call->param0, call->param1);
	kfree(call, sizeof(*call));
}

/*
 * thread_call_init
 *
 * Initialize the thread call system
 */
void
thread_call_init(void)
{
	thread_ref_t	t;
	L4_ThreadId_t	dummy;
	void		**stack;

	assert(timerlist = ll_new());
	assert(calllist = ll_new());

	t = thread_create_priority(100, &dummy);
	L4_KDB_SetThreadName(dummy, "thrdcallsrv");

	stack = (void *)&_threadcallstack[0x1000 - 1];
	stack--;
	*stack = threadcallserv;
	stack--;
	*stack = NULL;/*NOARG*/
	
	thread_start(t, (uintptr_t)__xnu_thread_stub, (uintptr_t)stack);
}

boolean_t
thread_call_free(
	thread_call_t	call
)
{

	if (call->state != IDLE)
		panic("thread_call_free: call state not idle");

	kfree(call, sizeof(*call));

	/*
	 * XXX what are we supposed to return here?
	 */
	return 0;
}


thread_call_t
thread_call_allocate(
	thread_call_func_t	func,
	thread_call_param_t	param
)
{
	thread_call_t	call;

	if ((call = kalloc(sizeof(*call)))) {
		call->func = func;
		call->param0 = param;
		call->state = IDLE;
	}

	return call;
}

/*
 * thread_call_dequeue
 *
 * Dequeue ourselves from the queue that  we are in
 *
 * Assertions
 * global lock is held
 * We _really_ must be on some queue.
 *
 * XXX clean this up!
 */
static void
thread_call_dequeue(
	thread_call_t	call
)
{
	struct ll	*tmplist;
	struct ll	*tmplist2;
	int		removed = 0;

	tmplist = ll_new();
	tmplist2 = ll_new();

	if (!tmplist) 
		assert(!"templist empty");

	if (!tmplist2) 
		assert(!"templist2 empty");

	for (;;) {
		struct callitem	*x;

		x = ll_pop(timerlist);
		if (!x)
			break;
		if (x->call == call) {
			xnu_free(x);
			removed = 1;
			break;
		} else
			ll_insert_before(tmplist, x);

	}

	for (;;) {
		void	*x;

		x = ll_pop(tmplist);
		if (!x)
			break;
		ll_insert_before(timerlist, x);
	}

	if (removed)
		goto out;

#if 1	/* XXX assume if it can get to calllist, then we run it anyway */
	for (;;) {
		struct callitem	*x;
	
		x = ll_pop(calllist);
		if (!x)
			break;
		if (x->call == call) {
			xnu_free(x);
			removed = 1;
			break;
		} else
			ll_insert_before(tmplist2, x);
	}

	for (;;) {
		void	*x;

		x = ll_pop(tmplist2);
		if (!x)
			break;
		ll_insert_before(calllist, x);
	}
#endif

out:
	/*
	 * paranoia
	 *
	 * if not removed then punt fatally
	 */
	if (!removed) {
		printf("%s: badness, nothing to dequeue!\n", __FUNCTION__);
		printf("%s: call %p func %p arg %p %p state = %d\n", 
			__FUNCTION__,
			call, call->func, call->param0, 
			call->param1, call->state);
		assert(!"shit");
	}

	ll_free(tmplist);
	ll_free(tmplist2);

	call->state = IDLE;
	return;
}

/*
 * thread_call_enter1
 *
 */
boolean_t
thread_call_enter1(
	thread_call_t		call,
	thread_call_param_t	param1
)
{
	boolean_t	res = TRUE;
	struct callitem	*item;

	item = kalloc(sizeof(struct callitem));
	assert(item);

	/*
	 * If it is idle, then we can queue this item again.
 	 *
	 */
	if (call->state == IDLE) {
		res = FALSE;
		goto enqueue;
	}

	/*
	 * PENDING and DELAYED common path
	 *
	 * Dequeue it from any existing queues first
	 */
	lck_spin_lock(xnulck);
	thread_call_dequeue(call);

enqueue:
	item->call = call;
	item->deadline.raw = 0;	/* almost immediate run */

	call->param1 = param1;
	call->state = PENDING;

	ll_insert_before(timerlist, item);

	lck_spin_unlock(xnulck);

	return res;
}

boolean_t
thread_call_enter(
	thread_call_t	call
)
{

	return thread_call_enter1(call, NULL);
}

/*
 * thread_call_enter1_delayed
 *
 * xnu_glue implementation notes:
 * Since we only have microsecond resolution, we divide by 1000 when we
 * get absolutetime which is in nsec.    Which means that our times may
 * be _way_ off!
 */
/*
 * XXX doesn't belong here
 */
#define roundup(x, y)	(((x) + ((y)-1)) & ~((y)-1))
#define rounddown(x, y) ((x) & ~((y)-1))

boolean_t
thread_call_enter1_delayed(
	thread_call_t		call,
	thread_call_param_t	param1,
	uint64_t		deadline/*Absolutetime*/)
{
	struct callitem		*item;
	uint64_t		up, down, mydeadline;
	boolean_t		res = TRUE;

	/*
	 * XXX: Probably bogus as shit!!
	 */
	up = roundup(deadline, 1000);
	down = rounddown(deadline, 1000);

	if ((deadline - down) >= (up - deadline)) {
		/*
		 * upper portion is closer, choose upper
		 */
		mydeadline = up;
	} else {
		mydeadline = down;
	}

	mydeadline /= 1000;	/* convert to usec */
#if 0
	printf("%s: called func %p param %p %p deadline = 0x%llx "
	    "converted 0x%llx now = 0x%llx\n", 
	    __FUNCTION__, 
	    call->func, 
	    call->param0, 
	    call->param1, 
	    deadline,
	    mydeadline,
	    L4_SystemClock().raw);
#endif

	lck_spin_lock(xnulck);
	if (call->state == IDLE) {
		res = FALSE;
		goto enqueue;
	}

	thread_call_dequeue(call);

enqueue:
	item = xnu_malloc(sizeof(struct callitem));
	assert(item);

	item->deadline.raw = mydeadline;
	item->call = call;

	call->param1 = param1;
	call->state = DELAYED;

	ll_insert_before(timerlist, item);

	lck_spin_unlock(xnulck);

	return res;
}

boolean_t
thread_call_enter_delayed(
	thread_call_t	call,
	uint64_t	deadline
)
{

	return thread_call_enter1_delayed(call, NULL, deadline);
}

boolean_t
thread_call_cancel(
	thread_call_t	call)
{
	int			done = 0;
	boolean_t		res = TRUE;

	lck_spin_lock(xnulck);
#if 0
	printf("thread_call_cancel: trying to dequeue %p %p %p state %d\n",
		call->func, call->param0, call->param1, call->state);
#endif

	if (call->state == IDLE) {
		done = 1;
		res = FALSE;
		goto out;
	}

	/*
	 * Ok, we should have something that we can can cancel.
	 * dequeue it
	 */

	thread_call_dequeue(call);
	done = 1;

out:
	lck_spin_unlock(xnulck);

	/*
	 * If it's not idle, then the cancel should always work!
	 * though, someone can still pass us garbage to remove,
	 * I guess ...
	 */
	if (!done) {
		printf("%s: shit, didn't remove anything!!", __FUNCTION__);
		printf("%s: call %p func %p args %p %p state %d\n",
		    __FUNCTION__, call, call->func, 
		    call->param0, call->param1, call->state);
		assert(!"bad");
	}

	return res;
}

/*
 * threadcallserv
 *
 */
void
threadcallserv(void)
{
	thread_call_t		call;
	struct callitem		*item;
	struct ll		*tmplist;
	L4_Clock_t		now;
	timer_t			timer;
	thread_t		dummy;

	lck_spin_lock(xnulck);
	assert(tmplist = ll_new());
	timer = timer_create();
	lck_spin_unlock(xnulck);

	assert(timer);

loop:
	L4_Sleep(L4_TimePeriod(10 * 1000/*10ms*/));
	now = L4_SystemClock();

	lck_spin_lock(xnulck);
	for (;;) {

		item = ll_pop(timerlist);
		if (!item)
			break;

		call = item->call;
		if (item->deadline.raw == 0) {
			/* immediate */
			ll_insert_before(calllist, item);
			continue;
		}

		if (now.raw >= item->deadline.raw) {
			/* call this */
			ll_insert_before(calllist, item);
			continue;
		}

		ll_insert_before(tmplist, item);
	}

	for (;;) {
		void	*x;
	
		x = ll_pop(tmplist);
		if (!x)
			break;

		ll_insert_before(timerlist, x);
	}

	lck_spin_unlock(xnulck);

	/*
	 * now, actually call the stuff that we need to this time around
	 */
	for (;;) {
		thread_call_func_t		func;
		thread_call_param_t		param0, param1;
		thread_call_t			newcall;

		lck_spin_lock(xnulck);
		item = ll_pop(calllist);
		if (!item) {
			lck_spin_unlock(xnulck);
			break;
		}

		call = item->call;
		kfree(item, sizeof(*item));

		call->state = IDLE;

		func = call->func;
		param0 = call->param0;
		param1 = call->param1;

		newcall = kalloc(sizeof(*newcall));
		assert(newcall);

		newcall->func  = func;
		newcall->param0 = param0;
		newcall->param1 = param1;

#if 0		/* instrumentation for profiling */
		printf("threadcallserv: calling %p args %p %p\n",
		    func, param0, param1);
#endif

		lck_spin_unlock(xnulck);

		kernel_thread_start(
		    (thread_continue_t)mach_callout, 
		    newcall, 
		    &dummy);
	}

	goto loop;

	/* NOTREACHED */
}


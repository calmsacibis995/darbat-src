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
 * sched_prim.c
 *
 */

#include <xnucompat.h>

#include <kern/locks.h>
#include <kern/sched_prim.h>

#include <l4/types.h>
#include <l4/ipc.h>
#include <l4/schedule.h>

#include <stdio.h>
/*
 * XXX: see osfmk/kern/kern_types.h
 *
 */
#if 0
static char *__thrstate[] = {
	"not interruptible",
	"restartable",
	"abortable"
};
#endif

static struct waitqitem *waitlist;

/*
 * assert_wait
 *
 * This implement does not have a corresponding clear_wait().
 */
wait_result_t
assert_wait(event_t     event, wait_interrupt_t interruptible)
{
	struct xnu_thread *xnuthrd;
	struct waitqitem *q;

#if 0
	printf("assert_wait: wait on event %p flags %s\n",
	    event, __thrstate[interruptible]);
#endif

	lck_spin_lock(xnulck);
	xnuthrd = xnu_thread_lookup(L4_Myself());

	if (!xnuthrd) 
		panic("assert_wait: my tid 0x%lx does not exist in "
		    "tid list\n", L4_Myself().raw);

	xnuthrd->wchan = (L4_Word_t)event;
	if (interruptible & (~THREAD_UNINT)) {
		/* other bits are set ... what are they? */
		printf("assert_wait: warning: other bits set = 0x%lx\n",
		    (unsigned long)interruptible);
	}

	/*
	 * We do not want to add things on the queue twice.
	 */
	for (q = waitlist; q; q = q->next) {
		if (q->tid.raw == L4_Myself().raw) {
			/*
			 * If this is the case we just change the wait
			 * channel and do nothing
			 */
			q->event = xnuthrd->wchan;
			goto skip;
		}
	}
	/*
	 * Shove it onto the waitq
	 */
	assert(q = xnu_malloc(sizeof(struct waitqitem)));
	q->event = xnuthrd->wchan;
	q->tid = L4_Myself();
	q->next = waitlist;
	waitlist = q;

skip:
	lck_spin_unlock(xnulck);

	return THREAD_WAITING;
}

kern_return_t
thread_wakeup_prim(event_t event, boolean_t onethrd, wait_result_t result)
{
	L4_Msg_t msg;
	L4_ThreadId_t t;
	L4_MsgTag_t tag;
	struct waitqitem *cur, *nextone, *prev;
	int awakened = 0;
	struct xnu_thread *xnuthrd;

	lck_spin_lock(xnulck);
start:
	for (cur = waitlist, prev = NULL; cur; prev = cur, cur = cur->next) {
nextstart:

		if (cur->event != (L4_Word_t)event)
			continue;

		t.raw = cur->tid.raw;
		nextone = cur->next;
		xnu_free(cur);
		xnuthrd = xnu_thread_lookup(t);
		assert(xnuthrd);
		xnuthrd->wchan = (L4_Word_t)0;
		L4_MsgClear(&msg);
#if 0
		L4_MsgAppendWord(&msg, result);
#else
		/*
		 * XXX since we never handle THREAD_INTERRUPTIBLE
		 * It makes sense we override what the caller provided us.
		 */
		if (result != THREAD_AWAKENED)
			printf("warning: result (%d) != THREAD_AWAKENED, "
			    "caller = %p\n", 
			     (int)result, __builtin_return_address(0));
		L4_MsgAppendWord(&msg, THREAD_AWAKENED);
#endif
		L4_MsgLoad(&msg);
#if 0
		printf("thread_wakeup_prim: 0x%lx waking up 0x%lx on "
		    "event %p onethread %d wait_result_t %d "
		    "rt(0) = 0x%lx "
		    "rt(1) = 0x%lx "
		    "rt(2) = 0x%lx "
		    "rt(3) = 0x%lx\n",
		    L4_Myself().raw, t.raw, event, onethrd, result,
		    __builtin_return_address(0),
		    __builtin_return_address(1),
		    __builtin_return_address(2),
		    __builtin_return_address(3)
		);
#endif

		/*
		 * Do not use zero timeout or we could race!
		 */
		tag = L4_Send(t);
		/*
		 * Can't fail: L4_Send waits for receive to b ready
		 *
		 */
		assert(L4_IpcSucceeded(tag));
		awakened++;

		if (awakened) {

			if (!prev)
				waitlist = nextone;
			else
				prev->next = nextone;
		}

		if (onethrd && awakened)
			break;

		/*
		 * XXX fix up pointers, we need a better list iter
		 */
		if (!prev)
			goto start;

		/*
		 * otherwise, current is actually nexstone and prev
		 * remains the same
		 */
		cur = nextone;

		/*
		 * nextone could be NULL, if it is on the end of the
		 * list.  If this is the case, then we ned to break
		 * out of the loop.
		 */
		if (!cur)
			break;

		goto nextstart;

	}

	lck_spin_unlock(xnulck);
	return KERN_SUCCESS;
}

wait_result_t
thread_block_parameter(thread_continue_t continuation, void *parameter)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
	L4_Word_t	dummy;
	L4_ThreadId_t	dummy_id;
	struct xnu_thread *xnuthrd;
	void		**stack_top;

	/*
	 * XXX can we race?
	 * (1) before we are put to sleep, with l4_wait, we get rescheduled.
	 * it wakes up our event ch annel, however, since we never actually
	 * slept it fails.  When we get scheduled again we actually call the
	 * wait and we sleep forever!  We can always use L4_Send which should
	 * enqueue things, but is that bvad??
	 */
	tag = L4_Wait(&dummy_id);
	assert(L4_IpcSucceeded(tag));
	L4_MsgStore(tag, &msg);

	/*
	 * Do weve continuation?
	 *
	 */
	if (continuation) {
		/*
		 * Rebuild the stack.
		 *
		 */
		lck_spin_lock(xnulck);
		xnuthrd = xnu_thread_lookup(L4_Myself());
		lck_spin_unlock(xnulck);
		assert(xnuthrd);
		stack_top = (void **)xnuthrd->sp;
		stack_top--;
		*stack_top = parameter;
		stack_top--;
		/* Fake a return address. */
		*stack_top = (void *)0xdecafbad; 

		(void)L4_ExchangeRegisters(L4_Myself(),
		    (1 << 4/*ip*/) + (1 << 3/*sp*/) +
		    (1 << 2/*S bit*/) + (1 << 1/*R bit*/), (L4_Word_t)stack_top,
		    (L4_Word_t)continuation, 0, 0, L4_nilthread,
		    &dummy, &dummy, &dummy, &dummy, &dummy, &dummy_id);

		/* NOTREACHED */
	}

	return (wait_result_t)L4_MsgWord(&msg, 0);
}

/*
 *      thread_block:
 *
 *      Block the current thread if a wait has been asserted.
 */
wait_result_t
thread_block(
	thread_continue_t       continuation)
{

	return thread_block_parameter(continuation, NULL);
}


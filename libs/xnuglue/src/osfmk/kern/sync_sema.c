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
 * sync_sema.c
 *
 * osfmk sempahores
 *
 */

#include <stdio.h>

#include <l4/types.h>
#include <l4/kdebug.h>
#include <l4/ipc.h>

#include <xnucompat.h>
#include <xnu_glue.h>

#include <kern/kalloc.h>
#include <kern/locks.h>

#include <mach/mach_types.h>
#include <mach/kern_return.h>
#include <mach/semaphore.h>

kern_return_t
semaphore_create(
	task_t		task,
	semaphore_t	*sem,
	sync_policy_t	policy,
	int		val)
{
	struct sem	*_sem;

#if 0
	printf("%s: warning: ignoring policy and task\n", __func__);
#endif
	if ((_sem = kalloc(sizeof(struct sem)))) {

		_sem->val = val;
		lck_spin_init(&_sem->lck, NULL/*ignored*/, NULL/*ignored*/);
		_sem->ll = ll_new();	/* XXX */
	} else {
		*sem = (semaphore_t)NULL/*XXX: SEMAPHORE_NULL*/;
		return KERN_RESOURCE_SHORTAGE;
	}

	*sem = (semaphore_t)_sem;

	return KERN_SUCCESS;
}

/*
 * XXX: Should consolidate with semaphore_signal()
 */
kern_return_t
semaphore_signal_all(semaphore_t	sem)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
	L4_ThreadId_t	tid;
	struct sem	*_sem;

	_sem = (struct sem *)sem;
	lck_spin_lock(&_sem->lck);

	for (; _sem->val != 0; ) {
		_sem->val++;
		tid.raw  = (L4_Word_t)ll_pop(_sem->ll);

		if (tid.raw) {

			L4_MsgClear(&msg);
			L4_MsgLoad(&msg);

			tag = L4_Send(tid);
			if (!L4_IpcSucceeded(tag)) {
				panic("semaphore_signal_all: ipc "
				    "failed to tid 0x%lx code = 0x%lx",
				    tid.raw, 
				    L4_ErrorCode());
			}
		}
	}
	/*
	 * XXX
	 *
	 * Yes, I realize this is not ideal, since it is not unlocked
	 * until the next time we get scheduled.  however, think: we hold
	 * a lock to the sem, we want to wake up everyone, which could
	 * be multiple ... so we can't unlock in the waker's address space.
	 *
	 * Rats.
	 *
	 * This problem will go away if we use asynch IPC.
	 */
	lck_spin_unlock(&_sem->lck);

	return KERN_SUCCESS;
}
	
kern_return_t
semaphore_signal(semaphore_t	sem)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
	L4_ThreadId_t	tid;
	struct sem	*_sem;

	_sem = (struct sem *)sem;
	lck_spin_lock(&_sem->lck);

	_sem->val++;
	tid.raw  = (L4_Word_t)ll_pop(_sem->ll);

	if (tid.raw) {

		L4_MsgClear(&msg);
		L4_MsgLoad(&msg);

		tag = L4_Send(tid);
		if (!L4_IpcSucceeded(tag)) {
			panic("semaphore_signal: ipc failed to tid 0x%lx "
			    "code = 0x%lx",
			    tid.raw, 
			    L4_ErrorCode());
		}
	}

	/*
	 * XXX
	 *
	 * Yes, I realize this is not ideal, since it is not unlocked
	 * until the next time we get scheduled.  however, think: we hold
	 * a lock to the sem, we want to wake up everyone, which could
	 * be multiple ... so we can't unlock in the waker's address space.
	 *
	 * Rats.
	 *
	 * This problem will go away if we use asynch IPC.
	 */
	lck_spin_unlock(&_sem->lck);

	return KERN_SUCCESS;
}

kern_return_t
semaphore_wait(semaphore_t	sem)
{
	L4_MsgTag_t	tag;
	L4_ThreadId_t	tid;
	struct sem	*_sem;

	_sem = (struct sem *)sem;
	lck_spin_lock(&_sem->lck);
	_sem->val--;

	if (_sem->val >= 0) {
		lck_spin_unlock(&_sem->lck);
		goto out;
	}

	ll_insert_before(_sem->ll, (void *)L4_Myself().raw);

	lck_spin_unlock(&_sem->lck);

	tag = L4_Wait(&tid);

	if (!L4_IpcSucceeded(tag))
		panic("semaphore_wait: failed ipc");

out:
	return KERN_SUCCESS;
}

kern_return_t
semaphore_timedwait(
	semaphore_t	semaphore,
	mach_timespec_t	wait_time)
{

	/*
	 * XXX this is broken, since we do not consider timeouts.
	 *
	 * 	- gl
	 */
	printf("%s: warning: sleeping on sempahore_timedwait without "
	    "timeout support\n", __FUNCTION__);
	return semaphore_wait(semaphore);
}

kern_return_t
semaphore_destroy(task_t task, semaphore_t sem)
{
	struct sem *_sem = (struct sem *)sem;

	ll_free(_sem->ll);

	kfree(_sem, sizeof(*_sem));

	return KERN_SUCCESS;
}

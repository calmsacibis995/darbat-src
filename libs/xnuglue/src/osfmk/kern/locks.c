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
 * locks.c
 *
 * xnu-style locks
 */

#include <xnucompat.h>

#include <kern/kalloc.h>
#include <kern/locks.h>
#include <kern/sched_prim.h>

#include <l4/schedule.h>
#include <l4/kdebug.h>
#include <stdio.h>

/*
 * Simple locks ... where exactly should they go?
 * -gl
 */
void
usimple_lock(
	usimple_lock_t	lck)
{
	lck_spin_lock((lck_spin_t *)lck);
}

void
usimple_unlock(
	usimple_lock_t	lck)
{
	lck_spin_unlock((lck_spin_t *)lck);
}


mutex_t *
mutex_alloc(unsigned short tag)
{

	return (mutex_t *)lck_mtx_alloc_init(NULL, NULL);
}

void
mutex_lock(
	lck_mtx_t	*m)
{

	lck_mtx_lock(m);
}

void
mutex_unlock(
	lck_mtx_t	*m)
{

	lck_mtx_unlock(m);
}

lck_mtx_t *
lck_mtx_alloc_init(
        lck_grp_t       *grp,
        lck_attr_t      *attr)
{
	semaphore_t	sem;
	kern_return_t	rc;

	rc = semaphore_create(NULL, &sem, 0/*XXX*/, 1);
	assert(rc == 0);	/* KERN_SUCCESS */
	return (lck_mtx_t *)sem;
}

void
lck_mtx_free(
	lck_mtx_t	*lck,
	lck_grp_t	*grp)
{

	kfree((void *)lck, sizeof(*lck));
}

void
lck_mtx_lock(
	lck_mtx_t	*lck)
{
	/*
	 * This is a mutex.
	 *
	 * This is right
	 */
	semaphore_wait((semaphore_t)lck);
}


void
lck_mtx_unlock(
	lck_mtx_t	*lck)
{
	struct sem	*sem = (struct sem *)lck;
	kern_return_t	rc;

	/*
	 * Assertion:
	 *
	 * Since this is a mutex, we want to make sure that
	 * no one is unduly increasing the number of
	 * counts.
	 *
 	 * That would be pretty bad.
	 *
	 * If we are unlocking, we MEAN unlocking.
	 */
	if (sem->val > 0) {
		printf("%s: sem %p val = %d, bad!\n", __func__, sem, sem->val);
		assert(!"bad");
	}

	rc = semaphore_signal((semaphore_t)sem);
	assert(rc == 0);	/* KERN_SUCCESS */
}

boolean_t
lck_mtx_try_lock(lck_mtx_t *lck)
{
	struct sem *_sem = (struct sem *)lck;
	int rc;

	lck_spin_lock(&_sem->lck);
	_sem->val--;

	if (_sem->val >= 0) {
		rc = 1;
		goto out;
	} else {
		_sem->val++;	/* can't lck without sleep ... */
		rc = 0;
	}

out:
	lck_spin_unlock(&_sem->lck);
	return (rc);
}


wait_result_t
lck_mtx_sleep(
        lck_mtx_t               *lck,
        lck_sleep_action_t      lck_sleep_action,
        event_t                 event,
        wait_interrupt_t        interruptible)
{
	wait_result_t	res;

	if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0)
		panic("Invalid lock sleep action %x\n", lck_sleep_action);

	res = assert_wait(event, interruptible);
	if (res == THREAD_WAITING) {
		lck_mtx_unlock(lck);
		res = thread_block(THREAD_CONTINUE_NULL);
		if (!(lck_sleep_action & LCK_SLEEP_UNLOCK))
			lck_mtx_lock(lck);
	}
	else
	if (lck_sleep_action & LCK_SLEEP_UNLOCK)
		lck_mtx_unlock(lck);

	return res;
}

lck_spin_t *
lck_spin_alloc_init(
	lck_grp_t	*grp,
	lck_attr_t	*attr)
{
	lck_spin_t	*lck;

	if ((lck = kalloc(sizeof(lck_spin_t))))
		lck_spin_init(lck, grp, attr);

	return (lck);
}

void
lck_spin_free(
	lck_spin_t	*lck,
	lck_grp_t	*grp)
{

	kfree((void *)lck, sizeof(*lck));
}

void
lck_spin_init(
	lck_spin_t	*lck,
	lck_grp_t	*grp,
	lck_attr_t	*attr)
{

	*lck = 0;
}

boolean_t
lck_spin_try_lock(lck_spin_t	*lck)
{

	return !testandset((volatile int *)lck);
}

void
lck_spin_lock(
	lck_spin_t	*lck)
{
	/*
	 * XXX
	 *
	 * This is different from Mach.  We don't spin, since then otherwise
	 * this thread is locked on the processor until the end of its
	 * timeslice.
	 */
	while (testandset((volatile int *)lck))
		L4_Yield();
}

void
lck_spin_unlock(
	lck_spin_t	*lck)
{
#if DIAGNOSTIC
	if (!(volatile int *)lck)
		panic("trying to unlock already unlocked lock");
#endif
	*(volatile int *)lck = 0;
}

wait_result_t
lck_spin_sleep(
	lck_spin_t		*lck,
	lck_sleep_action_t	lck_sleep_action,
	event_t			event,
	wait_interrupt_t	interruptible)
{
	wait_result_t	res;

	if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0)
		panic("Invalid lock sleep action %x\n", lck_sleep_action);

	res = assert_wait(event, interruptible);
	if (res == THREAD_WAITING) {
		lck_spin_unlock(lck);
		res = thread_block(THREAD_CONTINUE_NULL);
		if (!(lck_sleep_action & LCK_SLEEP_UNLOCK))
			lck_spin_lock(lck);
	} else {

		if (lck_sleep_action & LCK_SLEEP_UNLOCK)
			lck_spin_unlock(lck);
	}

	return res;
}


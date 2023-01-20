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
 * l4compat.c
 *
 * Cheesy interfaces for compatibility with L4Ka::Pistachio, somewhat.
 *
 * We have currently:
 * (1) A cheesy implementation of L4_Sleep()
 * (2) A cheesy implementation of L4_SystemClock()
 *
 * Author: Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <l4/ipc.h>

#include <assert.h>
#include <timer/timer.h>

void
L4_Sleep(L4_Time_t t)
{
	timer_t	timer, timer_ret;
	int	r;

	if (t.raw == L4_ZeroTime.raw)
		return;

	if (t.raw == L4_Never.raw) 
		L4_WaitForever();

	timer = timer_create();
	assert(timer);

	r = timer_request(
		timer, 
		MICROSECS(L4_TimePeriodAsUs(t)), 
		TIMER_ONESHOT);
	assert(r == 0);

	timer_ret = timer_wait();
	assert(timer_ret == timer);
	timer_delete(timer);

	return;
}

L4_Clock_t
L4_SystemClock(void)
{
	L4_Clock_t	dummy;

	dummy.raw = timer_current_time();
	
	return dummy;
}

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
 * osfmk/kern/clock.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */


#include <stddef.h>
#include <stdint.h>

#include <kern/clock.h>

#include <l4/ipc.h>	/* XXX correctly pull in Sleep() */

void
delay_for_interval(uint32_t	interval, uint32_t	scale)
{
	uint64_t	t;

	/*
	 * Interval in nanoseconds.  We need to convert to us.
	 *
	 */
	t = ((uint64_t)interval * scale) / 1000;

	/*
	 * XXX
	 *
	 * Got this from the AppleIntel8255x driver.
	 *
	 * It seems to state that IOSleep(1) sleeps for a minimum of
	 * 10us.  If you are going to do that, just fucking say so!
	 */
	if (t < 10)
		t = 10;

	L4_Sleep(L4_TimePeriod(t));
}

void
clock_delay_until(
	uint64_t		deadline)
{
	uint64_t	tmp;

	clock_get_uptime(&tmp);
	if (deadline >= tmp)
		return;
	/*
	 * XXX: nanosecond is machine specific, so we divide by 1000.
	 * XXX: Maybe we should just call one of the delay stuff.
	 */
	L4_Sleep(L4_TimePeriod((deadline - tmp)/1000));
}


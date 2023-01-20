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

#include <mach/mach_types.h>

#include <kern/cpu_data.h>
#include <kern/cpu_number.h>
#include <kern/clock.h>
#include <mach/mach_time.h>

#include "igcompat/darbat.h"

static clock_timer_func_t rtclock_timer_expire;

void
clock_set_timer_func( clock_timer_func_t func )
{
	if (rtclock_timer_expire == NULL)
		rtclock_timer_expire = func;
}

void
clock_set_timer_deadline( uint64_t deadline )
{
	/* dum de dum */
	return;
}

/* XXX */
void clock_intr(void);
void rtc_nanotime_update(void);

/* clock interrupt occured */
void
clock_intr(void)
{
	uint64_t abstime;
	abstime = mach_absolute_time();

	// printf( "Doing rtclock_timer_expire(%lld)\n", abstime );

	/* update the commpage with frequency info */
	/* XXX: only do this once for now */
	/* FIXME: pull in pp cpu datap stuff from rtclock, and hertz_tick */
	{
		static int done_update = 0;
		// if( !done_update )
		{
			rtc_nanotime_update();
			done_update = 1;
		}
	}

	/* the current impl. is OK to call, even if the first timer
	 * hasn't expired - it'll just ignore it.
	 */
	(*rtclock_timer_expire)(abstime);
}


/* returns the number of TSC ticks in the space of 1/20th of a second */
uint64_t timeRDTSC(void);

uint64_t
timeRDTSC(void)
{
	uint64_t freq;

	freq = darbat_cpu_freq();

	return freq / 20;
}

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
 * rtclock.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

/* Since code was taken from Apple, this probably qualifies for an APSL
 *license.  Source code was modified 2006-03-29.
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


#include <stddef.h>
#include <stdint.h>

#include <kern/clock.h>

#include <l4/ipc.h>	/* XXX should correctly pull in SystemClock() */

void
nanoseconds_to_absolutetime(
        uint64_t        nanoseconds,
        uint64_t        *result
)
{

	*result = nanoseconds;
}

void
absolutetime_to_nanoseconds(
        uint64_t        abstime,
        uint64_t        *result
)
{

	*result = abstime;
}

void
clock_absolutetime_interval_to_deadline(
	uint64_t		abstime,
	uint64_t		*result)
{

	clock_get_uptime(result);

	*result += abstime;
}

uint64_t
mach_absolute_time(void)
{
	uint64_t	result;

	clock_get_uptime(&result);
	return (result);
}

void
clock_get_uptime(uint64_t	*result)
{
	L4_Clock_t	clock;

	clock = L4_SystemClock();
	*result = clock.raw * 1000;	/* XXX: fake nanosec resolution */
}

void
clock_interval_to_absolutetime_interval(
	uint32_t		interval,
	uint32_t		scale_factor,
	uint64_t		*result
)
{
	*result = (uint64_t)interval * scale_factor;
}

void
clock_interval_to_deadline(
	uint32_t	interval,
	uint32_t	scale_factor,
	uint64_t	*result
)
{
	uint64_t	abstime;

	clock_get_uptime(result);

	clock_interval_to_absolutetime_interval(interval, scale_factor,
	    &abstime);

	*result += abstime;
}


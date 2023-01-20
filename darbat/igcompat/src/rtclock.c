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
#include <stdio.h>
#include <assert.h>

#include <kern/clock.h>

#if 0
void
clock_get_system_microtime(
	uint32_t			*secs,
	uint32_t			*microsecs)
{
	*secs = 0;
	*microsecs = 0;
}

void
clock_get_system_nanotime( uint32_t			*secs,
			   uint32_t			*nanosecs )
{
	*secs = 0;
	*nanosecs = 0;
}

void
clock_get_calendar_microtime( uint32_t			*secs,
			      uint32_t			*microsecs )
{
	*secs = 0;
	*microsecs = 0;
}

void
clock_get_boottime_nanotime( uint32_t			*secs,
			     uint32_t			*nanosecs )
{
	*secs = 0;
	*nanosecs = 0;
}


#undef clock_interval_to_deadline
void
clock_interval_to_deadline(
	uint32_t		interval,
	uint32_t		scale_factor,
	uint64_t		*result)
{
	/* hack hack */
	*result = 0;
}

#endif

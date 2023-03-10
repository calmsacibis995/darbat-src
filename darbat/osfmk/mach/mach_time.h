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
 * are subject to the Apple Public Source License Version 1.1 (the
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

#ifndef	_MACH_MACH_TIME_H_
#define	_MACH_MACH_TIME_H_

#include <mach/mach_types.h>

#include <sys/cdefs.h>

struct mach_timebase_info {
	uint32_t	numer;
	uint32_t	denom;
};

typedef struct mach_timebase_info	*mach_timebase_info_t;
typedef struct mach_timebase_info	mach_timebase_info_data_t;

__BEGIN_DECLS
#ifndef	KERNEL

kern_return_t		mach_timebase_info(
						mach_timebase_info_t	info);

kern_return_t		mach_wait_until(
						uint64_t		deadline);

#endif	/* KERNEL */

uint64_t			mach_absolute_time(void);
__END_DECLS

#endif /* _MACH_MACH_TIME_H_ */

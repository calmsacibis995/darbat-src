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
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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
/*
 *	File:	mach/lockgroup_info.h
 *
 *	Definitions for host_lockgroup_info call.
 */

#ifndef	_MACH_DEBUG_LOCKGROUP_INFO_H_
#define	_MACH_DEBUG_LOCKGROUP_INFO_H_

#include <mach/mach_types.h>

#define LOCKGROUP_MAX_NAME	64

#define LOCKGROUP_ATTR_STAT	0x01ULL

typedef struct lockgroup_info {
	char		lockgroup_name[LOCKGROUP_MAX_NAME];
	uint64_t	lockgroup_attr;
	uint64_t	lock_spin_cnt;
	uint64_t	lock_spin_util_cnt;
	uint64_t	lock_spin_held_cnt;
	uint64_t	lock_spin_miss_cnt;
	uint64_t	lock_spin_held_max;
	uint64_t	lock_spin_held_cum;
	uint64_t	lock_mtx_cnt;
	uint64_t	lock_mtx_util_cnt;
	uint64_t	lock_mtx_held_cnt;
	uint64_t	lock_mtx_miss_cnt;
	uint64_t	lock_mtx_wait_cnt;
	uint64_t	lock_mtx_held_max;
	uint64_t	lock_mtx_held_cum;
	uint64_t	lock_mtx_wait_max;
	uint64_t	lock_mtx_wait_cum;
	uint64_t	lock_rw_cnt;
	uint64_t	lock_rw_util_cnt;
	uint64_t	lock_rw_held_cnt;
	uint64_t	lock_rw_miss_cnt;
	uint64_t	lock_rw_wait_cnt;
	uint64_t	lock_rw_held_max;
	uint64_t	lock_rw_held_cum;
	uint64_t	lock_rw_wait_max;
	uint64_t	lock_rw_wait_cum;
} lockgroup_info_t;

typedef lockgroup_info_t *lockgroup_info_array_t;

#endif	/* _MACH_DEBUG_LOCKGROUP_INFO_H_ */


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
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
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
 * @OSF_COPYRIGHT@
 */

#ifndef	_MACH_SYNC_POLICY_H_
#define _MACH_SYNC_POLICY_H_

typedef int sync_policy_t;

/*
 *	These options define the wait ordering of the synchronizers
 */
#define SYNC_POLICY_FIFO		0x0
#define SYNC_POLICY_FIXED_PRIORITY	0x1
#define SYNC_POLICY_REVERSED		0x2
#define SYNC_POLICY_ORDER_MASK		0x3
#define SYNC_POLICY_LIFO		(SYNC_POLICY_FIFO|SYNC_POLICY_REVERSED)

#ifdef	KERNEL_PRIVATE

/*
 *	These options provide addition (kernel-private) behaviors
 */

#define SYNC_POLICY_PREPOST		0x4

#endif	/* KERNEL_PRIVATE */

#define SYNC_POLICY_MAX			0x7

#endif 	/* _MACH_SYNC_POLICY_H_ */

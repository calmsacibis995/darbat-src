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
 * Copyright (c) 2000-2005 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 2000 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 * 31 August 2000 (debo)
 *  Created.
 */

#ifndef	_MACH_MK_TIMER_H_
#define	_MACH_MK_TIMER_H_

#include <mach/mach_time.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

mach_port_name_t	mk_timer_create(void);

kern_return_t	mk_timer_destroy(
					mach_port_name_t	name);

kern_return_t	mk_timer_arm(
					mach_port_name_t	name,
					uint64_t			expire_time);

kern_return_t	mk_timer_cancel(
					mach_port_name_t	name,
					uint64_t			*result_time);

__END_DECLS

#pragma pack(4)
struct mk_timer_expire_msg {
	mach_msg_header_t	header;
	uint64_t			unused[3];
};
#pragma pack()

typedef struct mk_timer_expire_msg		mk_timer_expire_msg_t;

#endif /* _MACH_MK_TIMER_H_ */

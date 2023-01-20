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
// this is replaced by the mig generated stuff
#if 0

#ifndef __COMPAT_THREAD_ACT_H__
#define __COMPAT_THREAD_ACT_H__

kern_return_t thread_terminate( thread_t thread );
kern_return_t thread_resume( register thread_t thread );
kern_return_t thread_abort_safely( thread_t thread );
kern_return_t thread_abort( register thread_t thread );

#ifndef MACH_KERNEL_PRIVATE

/* a bit dodgey, but it works */
struct i386_saved_state * get_user_regs(thread_t th);

#else /* MACH_KERNEL_PRIVATE */

kern_return_t
thread_policy_set( thread_t thread,
		   thread_policy_flavor_t flavor,
		   thread_policy_t policy_info,
		   mach_msg_type_number_t count );

#endif /* MACH_KERNEL_PRIVATE */

#endif /* __COMPAT_THREAD_ACT_H__ */
#endif /* 0 */ 

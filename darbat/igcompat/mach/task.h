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

#ifndef __IG_COMPAT_TASK_H__
#define __IG_COMPAT_TASK_H__

extern kern_return_t task_suspend( task_t task );
extern kern_return_t task_resume( register task_t task );

/* CEG: namechange to avoid colliding with Iguana's */
extern kern_return_t mach_thread_create( task_t    task,
					thread_t *new_thread );

kern_return_t task_info( task_t 	         task,
			 task_flavor_t	         flavor,
			 task_info_t		 task_info_out,
			 mach_msg_type_number_t	*task_info_count );


/* according to some header file these should be here? */
kern_return_t semaphore_create( task_t task,
				semaphore_t *new_semaphore,
				sync_policy_t policy,
				int value );

kern_return_t semaphore_destroy( task_t task,
				 semaphore_t semaphore );



#endif /* __IG_COMPAT_TASK_H__*/

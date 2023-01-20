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
#include <kern/thread.h>
#include <mach/kern_return.h>
#include <machine/vmparam.h>
#include <stdio.h>
#include <DEBUG.h>
/*
 * thread_userstack:
 *
 * Return the user stack pointer from the machine
 * dependent thread state info.
 */
kern_return_t
thread_userstack(
        thread_t   thread,
        int                 flavor,
        thread_state_t      tstate,
        unsigned int        count,
        mach_vm_offset_t *,
        int					*customstack
        );

kern_return_t
thread_userstack(
        __unused thread_t   thread,
        int                 flavor,
        thread_state_t      tstate,
        unsigned int        count,
        user_addr_t    *user_stack,
        int					*customstack
        )
{
    struct i386_saved_state *state;
    i386_thread_state_t *state25;
    vm_offset_t	uesp;

    if (customstack)
        *customstack = 0;

    switch (flavor) {
        case i386_THREAD_STATE:	/* FIXME */
            state25 = (i386_thread_state_t *) tstate;
            if (state25->esp)
                *user_stack = state25->esp;
            else 
                *user_stack = USRSTACK;
            if (customstack && state25->esp)
                *customstack = 1;
            else
                *customstack = 0;
            break;

        case i386_NEW_THREAD_STATE:
            // XXX TGB HACK, was i386_NEW_THREAD_STATE_COUNT
            //if (count < i386_NEW_THREAD_STATE_COUNT)
            if (count < i386_THREAD_STATE_COUNT)
                return (KERN_INVALID_ARGUMENT);
            else {
                state = (struct i386_saved_state *) tstate;
                uesp = state->uesp;
            }

            /* If a valid user stack is specified, use it. */
            if (uesp)
                *user_stack = uesp;
            else 
                *user_stack = USRSTACK;
            if (customstack && uesp)
                *customstack = 1;
            else
                *customstack = 0;
            break;
        default :
            return (KERN_INVALID_ARGUMENT);
    }

    return (KERN_SUCCESS);
}    

/*
 * thread_adjuserstack:
 *
 * Returns the adjusted user stack pointer from the machine
 * dependent thread state info.  Used for small (<2G) deltas.
 */
uint64_t
thread_adjuserstack(
	thread_t	thread,
	int		adjust)
{

    thread->machine.pcb->iss.esp += adjust;

	return CAST_USER_ADDR_T(thread->machine.pcb->iss.esp);
}

kern_return_t
thread_entrypoint(
    thread_t,
    int,
    thread_state_t,
    unsigned int,
    mach_vm_offset_t *
); 

kern_return_t
thread_entrypoint(
    __unused thread_t   thread,
    int                 flavor,
    thread_state_t      tstate,
    unsigned int        count,
    mach_vm_offset_t    *entry_point
)
{ 
    struct i386_saved_state	*state;
    i386_thread_state_t *state25;

    /*
     * Set a default.
     */
    if (*entry_point == 0)
	*entry_point = VM_MIN_ADDRESS;
		
    switch (flavor) {
    case i386_THREAD_STATE:
	state25 = (i386_thread_state_t *) tstate;
	*entry_point = state25->eip ? state25->eip: VM_MIN_ADDRESS;
	break;

    case i386_NEW_THREAD_STATE:
	if (count < i386_THREAD_STATE_COUNT)
	    return (KERN_INVALID_ARGUMENT);
	else {
		state = (struct i386_saved_state *) tstate;

		/*
	 	* If a valid entry point is specified, use it.
	 	*/
        i386_thread_state_t * temp = (i386_thread_state_t *)tstate;
		*entry_point = state->eip ? state->eip: temp->eip;
        if(*entry_point == 0)
        {
            *entry_point = VM_MIN_ADDRESS;
        }

        // printf("entry point is %x, i think it should be %x\n", *entry_point, temp->eip);
        //*entry_point = temp->eip;
	}
	break;
    }

    return (KERN_SUCCESS);
}   

//XXX this is i386 specific, 
kern_return_t
machine_thread_state_initialize(
	thread_t thread)
{
//#pragma unused (thread)
#ifndef __i386__
#error
#endif

    return  KERN_SUCCESS;
}
#if 0

/* Initialize (or re-initialize) a thread state.  Called from execve
 * with nothing locked, returns same way.
 */
kern_return_t
thread_state_initialize(
	register thread_t		thread)
{
#if 0
	kern_return_t		result = KERN_SUCCESS;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	thread_mtx_lock(thread);

	if (thread->active) {
		if (thread != current_thread()) {
			thread_hold(thread);

			thread_mtx_unlock(thread);

			if (thread_stop(thread)) {
				thread_mtx_lock(thread);
				result = machine_thread_state_initialize( thread );
				thread_unstop(thread);
			}
			else {
				thread_mtx_lock(thread);
				result = KERN_ABORTED;
			}

			thread_release(thread);
		}
		else
            result = machine_thread_state_initialize( thread );
	}
	else
		result = KERN_TERMINATED;

	thread_mtx_unlock(thread);

	return (result);
#else
    return machine_thread_state_initialize(thread);
#endif
}

kern_return_t	thread_setstatus(
        thread_t				thread,
        int						flavor,
        thread_state_t			tstate,
        mach_msg_type_number_t	count)
{
    return KERN_SUCCESS;
}
#endif

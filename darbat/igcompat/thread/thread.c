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
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <kern/task.h>
#include <kern/queue.h>
#include <kern/thread.h>
#include <kern/thread_call.h>
#include <mach/sync_policy.h>
#include <mach/task.h>

#include <igcompat/compat.h> /* bzero */
#include <igcompat/darbat.h>

#include <kern/debug.h> /* panic! */

/* thread_act */
#include <mach/thread_act.h>

/* act stuff */
#include <kern/ast.h>

#include <DEBUG.h>

#include <l4/space.h>
#include <l4/thread.h>
#include <l4/kdebug.h>

#include <iguana/eas.h>


/* XXX */
extern void bsdinit_task(void);
extern thread_t _current_thread;

kern_return_t darbat_uthread_start( register thread_t thread );

// XXX TGB
void thread_register(unsigned long l4_tid, thread_t mach_tid);

kern_return_t 
darbat_uthread_start( register thread_t thread )
{
	assert( thread != NULL );

//	if( thread->ast & AST_BSD )
	if(1)
	{
		thread_t saved_thread;

		/* temporarily switch to the resumed thread for this */
		saved_thread = _current_thread;
		_current_thread = thread;

		/* invoke the init setup */
		bsdinit_task();
		thread->ast = 0;

		/* reset the current thread */
		_current_thread = saved_thread;

		/* do a create */
		{
			unsigned long tid;
			tid = darbat_thread_create(thread);


			// DBG();
			thread_register(tid, thread);

			thread->machine.pcb->l4_tid = tid;
		
		}
	}
	else
		assert(!"this thread_resume NYI");

	return KERN_SUCCESS;
}

/* XXX */

void
thread_setuserstack( thread_t thread, mach_vm_address_t user_stack )
{
	// thread->sp = (void*) user_stack;
	thread->machine.pcb->iss.esp = user_stack;
}


void
thread_setentrypoint( thread_t thread, mach_vm_address_t entry )
{
	// thread->ip = (void*) entry;
	thread->machine.pcb->iss.eip = entry;
}

void darbat_clean_eas(thread_t thread);
void
darbat_clean_eas(thread_t thread)
{
    // XXX this is a big performance issue, trashing EVERYONE's address space
    L4_Fpage_t fp = L4_CompleteAddressSpace;
    L4_Set_Rights(&fp, L4_FullyAccessible);
    fp = L4_UnmapFpage(fp);
}

void darbat_thread_reset(thread_t thread);
void
darbat_thread_reset(thread_t thread)
{
	if(thread->machine.pcb->l4_tid)
	{
		L4_ThreadId_t tid;
		tid.raw = thread->machine.pcb->l4_tid;
		
//		assert(!"pants");
		
		L4_AbortIpc_and_stop( tid );
		L4_Start_SpIp( tid,
			       thread->machine.pcb->iss.esp, 
			       thread->machine.pcb->iss.eip );
	}
}

unsigned int * darbat_thread_get_retvals(thread_t thread);
unsigned int *
darbat_thread_get_retvals(thread_t thread)
{
	return thread->machine.pcb->retvals;
}

L4_ThreadId_t darbat_get_l4_tid(thread_t thread);
L4_ThreadId_t
darbat_get_l4_tid(thread_t thread)
{
 	L4_ThreadId_t tid;
	
 	tid.raw = thread->machine.pcb->l4_tid;
	
 	return tid;
}

int darbat_get_syscall_no(thread_t thread);
int
darbat_get_syscall_no(thread_t thread)
{
	return thread->machine.pcb->continued_syscall_no;
}

void darbat_set_syscall_no(thread_t thread, int val);
void
darbat_set_syscall_no(thread_t thread, int val)
{
	thread->machine.pcb->continued_syscall_no = val;
}

kern_return_t
machine_thread_dup(thread_t src, thread_t dest)
{
/*
 	task_t dest_task = get_threadtask(dest);

	printf("dest state is %x\n", dest->state);
 
 	printf("dup'ing to L4_tid %x of task %p, thread %p\n", 
 	       dest->machine.pcb->l4_tid, dest_task, dest);
*/

 	L4_Copy_regs((L4_ThreadId_t) {src->machine.pcb->l4_tid}, 
 		     (L4_ThreadId_t) {dest->machine.pcb->l4_tid} );
 
 	L4_Set_UserDefinedHandleOf( (L4_ThreadId_t) {dest->machine.pcb->l4_tid}, 
 				    L4_UserDefinedHandleOf((L4_ThreadId_t) {src->machine.pcb->l4_tid}) );

/*
 	printf( "user defined handle is %p\n", 
 		(void *)(L4_UserDefinedHandleOf((L4_ThreadId_t) {src->machine.pcb->l4_tid})));
*/

 	return KERN_SUCCESS;
}

kern_return_t
machine_thread_get_eip_esp(
	thread_flavor_t flavor,
	thread_state_t tstate,
	mach_msg_type_number_t count,
    void **eip,
    void **esp);
kern_return_t
machine_thread_get_eip_esp(
	thread_flavor_t flavor,
	thread_state_t tstate,
	mach_msg_type_number_t count,
    void **eip,
    void **esp)
{
    switch(flavor)
    {
        case THREAD_SYSCALL_STATE:
            {
            struct thread_syscall_state *state = (struct thread_syscall_state *)tstate;
            *eip = (void *)(state->eip);
            *esp = (void *)(state->esp);
            }
            break;
        case i386_SAVED_STATE:
            {
            struct i386_saved_state *state = (struct i386_saved_state *)tstate;
            *eip = (void *)(state->eip);
            *esp = (void *)(state->uesp);
            }
            break;
        case i386_NEW_THREAD_STATE:
        case i386_REGS_SEGS_STATE:
            {
            if(count < i386_NEW_THREAD_STATE_COUNT)
            {
                return KERN_INVALID_ARGUMENT;
            }

            struct i386_new_thread_state *state = (struct i386_new_thread_state *)tstate;
            *eip = (void *)(state->eip);
            *esp = (void *)(state->uesp);
            }
            break;
        case i386_THREAD_STATE:
            {
            i386_thread_state_t *state = (i386_thread_state_t *)tstate;

            *eip = (void *)(state->eip);
            *esp = (void *)(state->esp);
            }
            break;
        default:
            return KERN_INVALID_ARGUMENT;
    }
    return KERN_SUCCESS;
}

void thread_set_child(thread_t child, int pid);
void
thread_set_child(thread_t child, int pid)
{
    return;
}

void darbat_fork_child_start(task_t task, user_addr_t eip);
void
darbat_fork_child_start(task_t task, user_addr_t eip)
{
 	assert(task->thread_count == 1);
	queue_head_t threads = task->threads;
 	// printf("fork child thread is %p\n", (void *)(queue_first(&threads)));
 	thread_t thread = (thread_t)(queue_first(&threads));
 	// DBG();
 	// thread_register(thread->machine.pcb->l4_tid, thread);
 	// assert(!"fork child start");
 	//L4_Start_SpIp((L4_ThreadId_t) {thread->machine.pcb->l4_tid}
 	//	      , 0 /* LOL! */, eip);
 
 	thread->machine.pcb->iss.eip = eip;
 	thread->machine.pcb->iss.esp = 0;
 
/*
 	printf( "setting fork child iss.eip to %x\n", 
 		thread->machine.pcb->iss.eip );
*/
}


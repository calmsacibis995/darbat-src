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
#include <mach/kern_return.h>
#include <mach/thread_status.h>
#include <mach/vm_param.h>

#include <kern/task.h>
#include <kern/thread.h>

#include "igcompat/darbat.h"

#include <DEBUG.h>
/* the current thread! */
/* XXX: mp */
thread_t _current_thread = NULL;


thread_t
current_thread(void)
{

    //printf(">>> current_thread called, old thread is %p\n", _current_thread);
	return _current_thread;
}


/*
 * This is used to set the current thr_act/thread
 * when starting up a new processor
 */
void
machine_set_current_thread( thread_t thread )
{
	// mp_disable_preemption();

    //printf(">>> machine_set_current_thread called with %p, old thread is %p\n", thread, _current_thread);
	_current_thread = thread;

	// mp_enable_preemption();
}


void
machine_thread_terminate_self(void)
{
}

extern void Thread_continue( void );

void
machine_stack_attach(
	thread_t		thread,
	vm_offset_t		stack)
{
	struct i386_kernel_state *statep;

	/* point to the bottom of the stack */
	thread->kernel_stack = stack;

	/* setup the startup info */
	statep = &thread->machine.pcb->kstate;

	statep->k_eip = (unsigned long) Thread_continue;
	statep->k_ebx = (unsigned long) thread_continue;
	statep->k_esp = (unsigned long) (stack + KERNEL_STACK_SIZE - 4);
}

vm_offset_t
machine_stack_detach(thread_t thread)
{
	vm_offset_t stack;

	stack = thread->kernel_stack;
	thread->kernel_stack = 0;
	return(stack);
}


/*
 * move a stack from old to new thread
 */

void
machine_stack_handoff(thread_t old,
		      thread_t new)
{
	vm_offset_t stack;

	assert(new);
	assert(old);

	stack = machine_stack_detach(old);
	machine_stack_attach(new, stack);

	machine_set_current_thread(new);

	current_cpu_datap()->cpu_active_stack = new->kernel_stack;

	return;
}

void Load_sysloop( void* );

void machine_load_sysloop(void);
void
machine_load_sysloop(void)
{
	char *sp;

    thread_t new = current_thread();

	/* compute the top of the stack */
	sp = (void*) new->kernel_stack;
	sp += KERNEL_STACK_SIZE - 8;  /* minus a random offset for some room */

	/* switch to the new stack & call 'thread_continue' */
	Load_sysloop( sp );

	/* shouldn't return! */
	panic( "Load_sysloop fell through?!\n" );
}

void Load_context( void* );

void
machine_load_context( thread_t new )
{
	char *sp;

	/* compute the top of the stack */
	sp = (void*) new->kernel_stack;
	sp += KERNEL_STACK_SIZE - 8;  /* minus a random offset for some room */

	/* switch to the new stack & call 'thread_continue' */
	Load_context( sp );

	/* shouldn't return! */
	panic( "Load_context fell through?!\n" );
}



thread_t Switch_context( thread_t old, 
			 thread_continue_t continuation, 
			 thread_t new,
			 void *old_ctx,
			 void *new_ctx );

/*
 * Switch to a new thread.
 * Save the old thread`s kernel state or continuation,
 * and return it.
 */
thread_t
machine_switch_context( thread_t old,
			thread_continue_t continuation,
			thread_t new )
{
	char *old_ct, *new_ct;
	thread_t d;

#if MACH_RT
        assert(current_cpu_datap()->cpu_active_stack == old->kernel_stack);
#endif

	/*
	 *	Save FP registers if in use.
	 */
	// XXX: probably want to use this
	// fpu_save_context(old);

	/*
	 *	Switch address maps if need be, even if not switching tasks.
	 *	(A server activation may be "borrowing" a client map.)
	 */

#if 0  /* FIXME: return to user-land or something? */
	{
		int	mycpu = cpu_number();
		
		PMAP_SWITCH_CONTEXT(old, new, mycpu);
	}
#endif

	/*
	 *	Load the rest of the user state for the new thread
	 */
	// Loads FPU registers
	// act_machine_switch_pcb(new);

	old->continuation = NULL;

	/* easier to compute these here than in asm */
	old_ct = (void*) &(old->machine.pcb->kstate);
	new_ct = (void*) &(new->machine.pcb->kstate);

	/* set the thread */
	_current_thread = new;

    /*
	printf( "Doing Switch_context to %p (ip %p, cont %p)\n", 
		new, (void*) new->machine.pcb->kstate.k_eip, continuation );
        */
	d = Switch_context(old, continuation, new,  old_ct, new_ct );

    /*
	printf( "got back from Switch_context: %p\n", d );
	printf( "going to return to: %p\n", __builtin_return_address(0) );
    */


	return d;
}



/* shouldn't really be here, but meh */
void ml_thread_policy(
	thread_t thread,
	unsigned policy_id,
	unsigned policy_info)
{
	(void) thread;
}


void
machine_thread_init(void)
{
	printf( ">>> Skipping machine_thread_init\n" );
}

#define TRET_NONE   0
#define TRET_START  1
#define TRET_SIGNAL 2

kern_return_t
machine_thread_create(
	thread_t	thread,
	task_t		task)
{
/*
	printf( ">>> doing machine_thread_create\n" );
	printf( ">>> thread is %p, task is %p\n", thread, task);
*/
	pcb_t	pcb = &thread->machine.xxx_pcb;
	task_t  old;

	thread->machine.pcb = pcb;

	simple_lock_init(&pcb->lock, 0);

	/*
	 *	Guarantee that the bootstrapped thread will be in user
	 *	mode.
	 */
	pcb->iss.cs = USER_CS;
	pcb->iss.ss = USER_DS;
	pcb->iss.ds = USER_DS;
	pcb->iss.es = USER_DS;
	pcb->iss.fs = USER_DS;
	pcb->iss.gs = USER_DS;
	pcb->iss.efl = EFL_USER_SET;


	/*
	 *     Setup the darbat parts
	 */

	/* XXX: darbat hacks */
	pcb->pthread = 0;
	pcb->l4_tid = 0;
	pcb->trap_return_action = TRET_NONE;
	pcb->sig_depth = 0;

	/* User thread - create an L4 thread for it */
	if( task != kernel_task )
	{
		unsigned long tid;

/*
		printf( ">>> Creating L4 user thread for kernel thread\n" );
*/

		/* XXX: seedy? */
		old = thread->task;
		thread->task = task;
		tid = darbat_thread_create(thread);
		
		// thread_register(tid, thread);

		thread->machine.pcb->l4_tid = tid;

		thread->task = old;

		/* tell us we need to start it */
		thread->machine.pcb->trap_return_action = TRET_START;
	}

	/*
	 *      Allocate a kernel stack per thread.
	 */
	// stack_alloc(thread);

	return(KERN_SUCCESS);
}


/* on the return path for new user-level threads.
 * check ASTs and what not
 */

void return_from_trap(void);
void i386_astintr(int);
void syscall_loop(void);


void force_ast(void);

void
force_ast(void)
{
	ast_t ast;
	thread_t thread = current_thread();

	ast = thread->ast;
	assert( ast != 0 );

	ast_propagate(thread->ast);
	ast_taken(AST_ALL, 1);
}

/* XXX */
void send_signal_message( unsigned long tid, void *func, int signum );

int pcb_process_pending_signal(void);
int
pcb_process_pending_signal(void)
{
	ast_t ast;
	thread_t thread = current_thread();
	pcb_t pcb = thread->machine.pcb;

	/* check the AST */
#if 0
	ast = *(ast_pending());
#else
	/* XXX: use the thread AST for now! */
	ast = thread->ast;
#endif

	//printf( "ast is 0x%x\n", ast );

	if( ast != 0 )
	{
		// XXX
		// i386_astintr( 0 );

		// XXXXXX
		ast_propagate(thread->ast);
		ast_taken(AST_ALL, 1);
	}

	/* XXX: only startup if it's a BSD start? */
	/*
	  printf( "Going to activate L4 thread id %x at ip 0x%x, sp 0x%x\n", 
	          pcb->l4_tid, pcb->iss.eip, pcb->iss.esp );
        */
	
	if( thread->machine.pcb->trap_return_action == TRET_SIGNAL)
    {
			assert( pcb->sig_depth > 0 );
			pcb->sig_depth--;

/*			printf( "Sending signal message\n" ); */
			/* send a signal message */
			send_signal_message( pcb->l4_tid, pcb->sig_func,
					     pcb->sig_num );
/*			printf( "Sent signal message\n" ); */
            pcb->trap_return_action = TRET_NONE;
            return 1;
	}

    return 0;
}

void
return_from_trap(void)
{
	ast_t ast;
	thread_t thread = current_thread();
	pcb_t pcb = thread->machine.pcb;

	/* check the AST */
#if 0
	ast = *(ast_pending());
#else
	/* XXX: use the thread AST for now! */
	ast = thread->ast;
#endif

	//printf( "ast is 0x%x\n", ast );

	if( ast != 0 )
	{
		// XXX
		// i386_astintr( 0 );

		// XXXXXX
		ast_propagate(thread->ast);
		ast_taken(AST_ALL, 1);
	}

	/* XXX: only startup if it's a BSD start? */
	/*
	  printf( "Going to activate L4 thread id %x at ip 0x%x, sp 0x%x\n", 
	          pcb->l4_tid, pcb->iss.eip, pcb->iss.esp );
        */
	
	switch( thread->machine.pcb->trap_return_action )
	{
		case  TRET_START:
/*
			printf( "XXXX: doing darbat_start_thread at ip %p, sp %p\n", 
				(void*) pcb->iss.eip,
				(void*) pcb->iss.esp );
*/
			darbat_start_thread( pcb->l4_tid, pcb->iss.eip,
					     pcb->iss.esp );
			break;

		case TRET_SIGNAL:

			assert( pcb->sig_depth > 0 );
			pcb->sig_depth--;

/*			printf( "Sending signal message\n" ); */
			/* send a signal message */
			send_signal_message( pcb->l4_tid, pcb->sig_func,
					     pcb->sig_num );
/*			printf( "Sent signal message\n" ); */

			break;

		case TRET_NONE:
			panic("trying to return without a TRET action?");
			//printf("trying to return without a TRET action?");
            break;

		default:
			panic("unknown TRET action!");
	}

	/* next time we don't want to do the same */
	pcb->trap_return_action = TRET_NONE;

	/* call into the sysloop */
	//printf( "return_from_trap: going into syscall_loop()\n" );
	syscall_loop();

	panic( "syscall_loop() returned!" );
}

void
machine_thread_destroy(thread_t thread)
{
	// printf("XXX: need to destroy darbat thread\n");
	thread->machine.pcb = (pcb_t)0;
}


void machine_set_signal_delivery( void *func, int sig );
void 
machine_set_signal_delivery( void *func, int sig )
{
	thread_t thread;
	pcb_t pcb;

	thread = current_thread();
	pcb = thread->machine.pcb;
 
	assert( pcb->trap_return_action == TRET_NONE );

	printf( "setting signal delivery, func = %p\n", func );
	
	pcb->trap_return_action = TRET_SIGNAL;
	pcb->sig_func = func;
	pcb->sig_num = sig;
	pcb->sig_depth++;
}

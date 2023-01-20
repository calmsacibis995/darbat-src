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
#include <platforms.h>

#include <i386/asm.h>
/* #include <i386/proc_reg.h> */
#include <assym.s>


/* Load a kernel stack on startup.
 *
 * int Load_context( void* sp ); 
 *
 * Argument is the new stack pointer. Returns 0 to the thread_continue
 * function.
 */

#if defined(__APPLE_CC__)
Entry(Load_sysloop)
#elif defined(__ELF__)
	.globl Load_sysloop
Load_sysloop:
#endif
	/* load the new stack pointer */
	movl	S_ARG0,%ecx

	/* stash it to the stack pointer and frame pointer */
	movl	%ecx,%esp
	movl	%ecx,%ebp

	/* return zero (no old thread) */
	xorl	%eax,%eax			
	pushl	%eax
	
	call	EXT(syscall_loop)

#if defined(__APPLE_CC__)
Entry(Load_context)
#elif defined(__ELF__)
	.globl Load_context
Load_context:
#endif
	/* load the new stack pointer */
	movl	S_ARG0,%ecx

	/* stash it to the stack pointer and frame pointer */
	movl	%ecx,%esp
	movl	%ecx,%ebp

	/* return zero (no old thread) */
	xorl	%eax,%eax			
	pushl	%eax
	
	call	EXT(thread_continue)



#if defined(__APPLE_CC__)	
Entry(call_continuation)
#elif defined(__ELF__)
	.globl call_continuation
call_continuation:
#endif
	movl	S_ARG0,%eax			/* get continuation */
	movl	S_ARG1,%edx			/* continuation param */
	movl	S_ARG2,%ecx			/* wait result */
	movl	%esp,%ebp			/* get kernel stack */
	orl	KERNEL_STACK_SIZE-1,%ebp
	//addl	$(-8),%ebp
	movl	%ebp,%esp			/* pop the stack */
	xorl	%ebp,%ebp			/* zero frame pointer */
	pushl	%ecx
	pushl	%edx
	call	*%eax				/* call continuation */
	/* die now if they return */
	// movl	$37,%eax
	// call	*%eax				/* die die die */
	/* what used to happen
	pushl	%eax
	call	EXT(thread_terminate)
	*/



/*      Switch from one kernel thread context to another
 *
 *      thread_t Switch_context( old, continuation, new, old_ctx, new_ctx );
 *
 *      Apple note:	
 *	This really only has to save registers
 *	when there is no explicit continuation.
 */

#if defined(__APPLE_CC__)
Entry(Switch_context)
#elif defined(__ELF__)
	.globl Switch_context
Switch_context:	
#endif
	movl	S_ARG3,%ecx                     /* get old kernel ctx */

	/* XXX: needs more constants */
	movl	%ebx,0(%ecx)			/* save registers */
	movl	%ebp,8(%ecx)
	movl	%edi,12(%ecx)
	movl	%esi,16(%ecx)
	popl	20(%ecx)			/* save return PC */
	movl	%esp,4(%ecx)			/* save SP */

	movl	0(%esp),%eax			/* return old thread */
	movl	8(%esp),%ebx			/* get new thread */

	/* load the context pointer */
	movl	16(%esp),%ecx			/* from caller */
	
	// movl    %ebx,%gs:CPU_ACTIVE_THREAD                /* new thread is active */
	//movl	TH_KERNEL_STACK(%ebx),%ecx	/* get its kernel stack */
	//lea	KERNEL_STACK_SIZE-IKS_SIZE-IEL_SIZE(%ecx),%ebx
						/* point to stack top */

	//movl	%ecx,%gs:CPU_ACTIVE_STACK	/* set current stack */
	//movl	%ebx,%gs:CPU_KERNEL_STACK	/* set stack top */


	//movl	$0,%gs:CPU_ACTIVE_KLOADED

	movl	4(%ecx),%esp		/* switch stacks */
	movl	16(%ecx),%esi		/* restore registers */
	movl	12(%ecx),%edi
	movl	8(%ecx),%ebp
	movl	0(%ecx),%ebx
	jmp	*20(%ecx)			/* return old thread */


#if defined(__APPLE_CC__)
Entry(Thread_continue)
#elif defined(__ELF__)
	.globl Thread_continue
Thread_continue:
#endif
	pushl	%eax				/* push the thread argument */
	xorl	%ebp,%ebp			/* zero frame pointer */
	call	*%ebx				/* call real continuation */


#ifdef __ELF__
	.globl thread_bootstrap_return
	.globl thread_exception_return
thread_bootstrap_return:
thread_exception_return:
#elif defined(__APPLE_CC__)
	.globl _thread_bootstrap_return
	.globl _thread_exception_return
_thread_bootstrap_return:
_thread_exception_return:
#else
#error unknown compiler
#endif
	/* XXX: FIXME: what to do about stacks? */
#if 0
	movl	%esp,%ecx			/* get kernel stack */
	or	$(KERNEL_STACK_SIZE-1),%ecx
	movl	-3-IKS_SIZE(%ecx),%esp		/* switch back to PCB stack */
#endif
	jmp	EXT(return_from_trap)



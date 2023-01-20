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
#include <mach/mach_types.h>
#include <mach/exception.h>

#include <kern/thread.h>

#include <sys/systm.h>
#include <sys/param.h>
#include <sys/proc_internal.h>
#include <sys/user.h>
#include <sys/sysproto.h>
#include <sys/sysent.h>
#include <mach/thread_act.h>	/* for thread_abort_safely */


/* XXX */
void machine_set_signal_delivery( void *func, int sig );

void
sendsig( struct proc *p, user_addr_t catcher /* sig_t */, 
	 int sig, int mask, u_long code )
{
	struct sigacts *ps = p->p_sigacts;
	int oonstack;
	thread_t thread = current_thread();
	struct uthread * ut;
    
	ut = get_bsdthread_info(thread);
	oonstack = ps->ps_sigstk.ss_flags & SA_ONSTACK;
	if ((ps->ps_flags & SAS_ALTSTACK) && !oonstack &&
		(ps->ps_sigonstack & sigmask(sig))) 
	{
		panic("can't deliver signals on ALTSTACK yet");
		ps->ps_sigstk.ss_flags |= SA_ONSTACK;
	} 

	// fp = ((struct sigframe *)scp) - 1;

	machine_set_signal_delivery( (void*) catcher, sig );

	return;
}


int
sigreturn(
	struct proc *p,
	struct sigreturn_args *uap,
	__unused int *retval)
{
#if 0
	thread_t	thread = current_thread();

	struct uthread * ut;
	ut = (struct uthread *)get_bsdthread_info(thread);

	if (context.sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;

	ut->uu_sigmask = context.sc_mask &~ sigcantmask;
	if(ut->uu_siglist & ~ut->uu_sigmask)
	{
		panic( "want to signal_setast??" );
		signal_setast(thread);
	}
#endif

	return (EJUSTRETURN);
}

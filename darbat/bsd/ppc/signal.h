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
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1992, 1993 NeXT Computer, Inc.
 */

#ifndef	_PPC_SIGNAL_
#define	_PPC_SIGNAL_ 1

#include <sys/appleapiopts.h>

#ifdef __APPLE_API_OBSOLETE
typedef int sig_atomic_t; 

/*
 * Machine-dependant flags used in sigvec call.
 */
#define	SV_SAVE_REGS	0x1000	/* Save all regs in sigcontext */

/*
 * regs_saved_t -- Describes which registers beyond what the kernel cares
 *		   about are saved to and restored from this sigcontext.
 *
 * The default is REGS_SAVED_CALLER, only the caller saved registers
 * are saved.  If the SV_SAVE_REGS flag was set when the signal
 * handler was registered with sigvec() then all the registers will be
 * saved in the sigcontext, and REGS_SAVED_ALL will be set.  The C
 * library uses REGS_SAVED_NONE in order to quickly restore kernel
 * state during a longjmp().
 */
typedef enum {
	REGS_SAVED_NONE,		/* Only kernel managed regs restored */
	REGS_SAVED_CALLER,		/* "Caller saved" regs: rpc, a0-a7,
					   t0-t4, at, lk0-lk1, xt1-xt20,
					   xr0-xr1 */
	REGS_SAVED_ALL			/* All registers */
} regs_saved_t;


/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */
struct sigcontext32 {
    int		sc_onstack;     /* sigstack state to restore */
    int		sc_mask;        /* signal mask to restore */
    int		sc_ir;			/* pc */
    int		sc_psw;         /* processor status word */
    int		sc_sp;      	/* stack pointer if sc_regs == NULL */
    void	*sc_regs;		/* (kernel private) saved state */
};

struct sigcontext64 {
    int		sc_onstack;     /* sigstack state to restore */
    int		sc_mask;        /* signal mask to restore */
    long long	sc_ir;		/* pc */
    long long	sc_psw;         /* processor status word */
    long long	sc_sp;      	/* stack pointer if sc_regs == NULL */
    void	*sc_regs;	/* (kernel private) saved state */
};

/*
 * LP64todo - Have to decide how to handle this.
 * For now, just duplicate the 32-bit context as the generic one.
 */
struct sigcontext {
    int		sc_onstack;     /* sigstack state to restore */
    int		sc_mask;        /* signal mask to restore */
    int		sc_ir;			/* pc */
    int		sc_psw;         /* processor status word */
    int		sc_sp;      	/* stack pointer if sc_regs == NULL */
    void	*sc_regs;		/* (kernel private) saved state */
};

#endif /* __APPLE_API_OBSOLETE */

#endif /* _PPC_SIGNAL_ */


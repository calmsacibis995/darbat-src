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
/*
 * xnu_glue.h
 *
 * Various glue shit
 *
 * Geoffrey Lee <glee at cse.unsw.edu.au>
 *
 * Maybe, someday, we don't have to put up with this sort of bullshit ..
 */

#ifndef _XNU_GLUE_H
#define _XNU_GLUE_H

#ifdef __cplusplus 
extern "C" {
#endif

#include <iguana/memsection.h>
#include <iguana/thread.h>

#include <libkern/OSByteOrder.h>

typedef L4_Word_t	thread_t;	/* for mach */

#include <stddef.h>
#include <stdarg.h>

#include <mach/kern_return.h>
/*
 * Oh.  The horror.
 */
#if 0
typedef int pmap_t;             /* XXX fuck */
#endif
typedef int semaphore_port_t;   /* XXX */
#ifdef __cplusplus	/* sucky!!! */	
#endif
int current_act(void);          /* XXX */
//thread_t current_thread(void);	/* XXX */
L4_Word_t current_thread(void);
kern_return_t thread_terminate(L4_Word_t);    /* XXX */
extern void *kernel_task;         /* XXX fuck */
#if 0
typedef int mach_port_t;        /* XXX fuck */
typedef int ipc_port_t;         /* XXX FUCK */
typedef int mach_port_name_t;   /* XXX */
typedef int mach_port_mscount_t;        /* XXX */
typedef int mach_port_seqno_t;  /* XXX */
#endif
/*
 * XXX: keep c++ happy.
 */
struct task {
	int dummy;
};
typedef struct task * task_t;	/* XXX */
typedef int semaphore_t;	/* XXX */
typedef int ipc_space_t;        /* XXX */
typedef int processor_t;	/* XXX */
typedef int host_t;		/* XXX kern/host.h */
typedef int host_priv_t;	/* XXX */
typedef int host_security_t;	/* XXX kern/host.h */
// XXX this always return the kernel map for now!!!!!!
#define get_task_map(x)         (kernel_map) /* XXX fuck */
#define processor_start(x)      (0)/* XXX fuck */
#define thread_set_cont_arg(/*int*/x)   (0)/* XXX */
#define thread_get_cont_arg(x)  (0)     /* XXX*/
#define clock_initialize_calendar(x)    (0)     /* XXX */
//#define ml_processor_register(a, b, x, y, z)  (0)     /* XXX */
extern task_t current_task(void);		/* XXX */
#include <mach/xxx.h>


#include <stdlib.h>
#include <string.h>
extern long long strtoq(const char *, char **, int);
extern unsigned long long strtouq(const char *, char **, int);

/*
 * scheduling stuff
 */

/*
 * Geoff's hacky scheduling server
 *
 */
extern L4_ThreadId_t xnu_schedtid;

/*
 * Semaphores
 *
 */
#define SEMWAIT         0
#define SEMSIGNAL       1
#define SEMSIGNALALL    2
#define SEMCREAT        3
#define SEMTIMEDWAIT	4

/*
 * Sleep/Wakeup
 */
#define SCHEDASSERTWAIT	5	/* assert_wait */
#define SCHEDWAKEUP     6	/* thread_wakeup_prim */
#define SCHEDBLCK       7	/* thread_block */

/*
 * thread termination
 */
#define PLEASEKILLME	8

/*
 * Interrupts.
 *
 */

extern void    *l4intrnub;
extern int     l4intrsource;
extern void    *l4intrtarget;
extern void    *l4intrrefCon;

/*
 * thread call stuff
 *
 */

/*
 * nothing here
 *
 */

/*
 * Xnu thread
 *
 * Mach threads
 * L4_ThreadId_t is not here because L4_Myself() is from the TCR, and that's
 * quite cheap.
 */

#if 0
struct xnu_thread {
	thread_ref_t	igtid;		/* Iguana thread Id */
	L4_ThreadId_t	l4tid;		/* L4 Thread Id */
	L4_Word_t	wchan;		/* wait channel */
	L4_Word_t	sp;		/* stack pointer */
	memsection_ref_t	stackref;	/* stack memsection */
	struct xnu_thread	*next;		/* next pointer */
};
	
extern struct xnu_thread *allthreads;	/* from src/thread.c */
#endif

#ifdef __cplusplus
};
#endif


#endif


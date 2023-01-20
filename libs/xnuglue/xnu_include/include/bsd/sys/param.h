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
 * sys/param.h
 *
 */

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#include <machine/param.h>

#define NBBY	8		/* XXX l4iokit hack */

#define CBLOCK  64              /* Clist block size, must be a power of 2. */
#define CBQSIZE (CBLOCK/NBBY)   /* Quote bytes/cblock - can do better. */
                                /* Data chars/clist. */
#define CBSIZE  (CBLOCK - sizeof(struct cblock *) - CBQSIZE)
#define CROUND  (CBLOCK - 1)    /* Clist rounding. */

/*
 * BSD priorities.
 *
 */
#define PSWP    0
#define PVM     4
#define PINOD   8
#define PRIBIO  16
#define PVFS    20
#define PZERO   22              /* No longer magic, shouldn't be here.  XXX */
#define PSOCK   24
#define PWAIT   32
#define PLOCK   36
#define PPAUSE  40
#define PUSER   50
#define MAXPRI  127             /* Priorities range from 0 through MAXPRI. */

#define PRIMASK 0x0ff
#define PCATCH  0x100           /* OR'd with pri for tsleep to check signals */
#define PTTYBLOCK 0x200         /* for tty SIGTTOU and SIGTTIN blocking */
#define PDROP   0x400           /* OR'd with pri to stop re-entry of interlock m utex */

#define NZERO   0               /* default "nice" */

#define CLBYTES         (CLSIZE*NBPG)

#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))

/* Macros for min/max. */
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif /* MIN */
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif  /* MAX */

#endif	/* SYS_PARAM_H */

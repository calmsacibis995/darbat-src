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
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 * Include file for xpr circular buffer silent tracing.  
 *
 */
/*
 * If the kernel flag XPRDEBUG is set, the XPR macro is enabled.  The 
 * macro should be invoked something like the following:
 *	XPR(XPR_SYSCALLS, "syscall: %d, 0x%x\n", syscallno, arg1, 0,0,0);
 * which will expand into the following code:
 *	if (xprflags & XPR_SYSCALLS)
 *		xpr("syscall: %d, 0x%x\n", syscallno, arg1, 0,0,0);
 * Xpr will log the pointer to the printf string and up to 5 arguements,
 * along with a timestamp and cpuinfo (for multi-processor systems), into
 * a circular buffer.  The actual printf processing is delayed until after
 * the buffer has been collected.  It is assumed that the text/data segments
 * of the kernel can easily be reconstructed in a post-processor which
 * performs the printf processing.
 *
 * If the XPRDEBUG compilation switch is not set, the XPR macro expands 
 * to nothing.
 */

#ifndef	_KERN_XPR_H_
#define _KERN_XPR_H_

#ifdef	MACH_KERNEL
#include <xpr_debug.h>
#else	/* MACH_KERNEL */
#include <sys/features.h>
#endif	/* MACH_KERNEL */

#include <machine/xpr.h>

#if	XPR_DEBUG

#define XPR(flags, msg, arg1, arg2, arg3, arg4, arg5) 		\
MACRO_BEGIN							\
	if (xprflags & (flags)) {				\
		xpr((msg), (long)(arg1), (long)(arg2),		\
		    (long)(arg3), (long)(arg4), (long)(arg5));	\
	}							\
MACRO_END

extern int xprflags;

/*
 * flags for message types.
 */
#define XPR_TRAPS		(1 << 1)
#define XPR_SCHED		(1 << 2)
#define	XPR_LOCK		(1 << 3)
#define	XPR_SLOCK		(1 << 4)
#define XPR_PMAP		(1 << 6)
#define XPR_VM_MAP		(1 << 7)
#define	XPR_VM_OBJECT		(1 << 8)
#define	XPR_VM_OBJECT_CACHE	(1 << 9)
#define	XPR_VM_PAGE		(1 << 10)
#define	XPR_VM_PAGEOUT		(1 << 11)
#define	XPR_MEMORY_OBJECT	(1 << 12)
#define	XPR_VM_FAULT		(1 << 13)
#define	XPR_VM_OBJECT_REP	(1 << 14)
#define	XPR_DEFAULT_PAGER	(1 << 15)
#define	XPR_INODE_PAGER		(1 << 16)
#define	XPR_INODE_PAGER_DATA	(1 << 17)
#define	XPR_XMM			(1 << 18)

#else	/* XPR_DEBUG */
#define XPR(flags, msg, arg1, arg2, arg3, arg4, arg5)
#endif	/* XPR_DEBUG */

struct xprbuf {
	const char 	*msg;
	long		arg1,arg2,arg3,arg4,arg5;
	int		timestamp;
	int		cpuinfo;
};

/* Bootstrap XPR facility */
extern void xprbootstrap(void);

/* Enable XPR facility */
extern void xprinit(void);

/* Log an XPR message */
extern void xpr(
	const char	*msg,
	long		arg1,
	long		arg2,
	long		arg3,
	long		arg4,
	long		arg5);

#endif /* _KERN_XPR_H_ */

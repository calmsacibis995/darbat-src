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
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
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
/* Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	setjmp.h
 *
 *	Declaration of setjmp routines and data structures.
 */
#ifndef _BSD_I386_SETJMP_H
#define _BSD_I386_SETJMP_H

#include <sys/cdefs.h>
#include <machine/signal.h>

/*
 * _JBLEN is number of ints required to save the following:
 * eax, ebx, ecx, edx, edi, esi, ebp, esp, ss, eflags, eip,
 * cs, de, es, fs, gs == 16 ints
 * onstack, mask = 2 ints
 */

#if defined(KERNEL)
typedef struct sigcontext jmp_buf[1];
#define _JBLEN ((sizeof(struct sigcontext)) / sizeof(int))
typedef int sigjmp_buf[_JBLEN+1];
#else
#define _JBLEN (18)
typedef int jmp_buf[_JBLEN];
typedef int sigjmp_buf[_JBLEN + 1];
#endif


__BEGIN_DECLS
extern int setjmp(jmp_buf env);
extern void longjmp(jmp_buf env, int val);

#ifndef _ANSI_SOURCE
int	_setjmp(jmp_buf env);
void	_longjmp(jmp_buf, int val);
int sigsetjmp(sigjmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);
#endif /* _ANSI_SOURCE  */

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_C_SOURCE)
void	longjmperror(void);
#endif /* neither ANSI nor POSIX */
__END_DECLS
#endif /* !_BSD_I386_SETJMP_H */

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
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */
/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)types.h	8.3 (Berkeley) 1/5/94
 */

#ifndef	_MACHTYPES_H_
#define	_MACHTYPES_H_

#ifndef __ASSEMBLER__
#include <ppc/_types.h>
#include <sys/cdefs.h>
/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
#ifndef _INT8_T
#define _INT8_T
typedef	__signed char		int8_t;
#endif
typedef	unsigned char		u_int8_t;
#ifndef _INT16_T
#define _INT16_T
typedef	short			int16_t;
#endif
typedef	unsigned short		u_int16_t;
#ifndef _INT32_T
#define _INT32_T
typedef	int			int32_t;
#endif
typedef	unsigned int		u_int32_t;
#ifndef _INT64_T
#define _INT64_T
typedef	long long		int64_t;
#endif
typedef	unsigned long long	u_int64_t;

#if defined(__ppc64__)
typedef int64_t			register_t;
#else
typedef int32_t			register_t;
#endif

#ifndef _INTPTR_T
#define _INTPTR_T
typedef __darwin_intptr_t	intptr_t;
#endif
#ifndef _UINTPTR_T
#define _UINTPTR_T
typedef unsigned long		uintptr_t;
#endif

/* with LP64 support pointers and longs from user address space may vary */
/* in size depending on the type of process (currently 32 or 64-bit, but */
/* may change in the future).  These types are used for  reserving the largest */
/* possible size. */
// LP64todo - typedef mach_vm_address_t	user_addr_t;	/* varying length pointers from user space */ 
// LP64todo - typedef mach_vm_size_t		user_size_t;	/* varying length values from user space (unsigned) */
typedef u_int64_t	user_addr_t;	
typedef u_int64_t	user_size_t;	
typedef int64_t		user_ssize_t;	
typedef int64_t		user_long_t;
typedef u_int64_t	user_ulong_t;
typedef int64_t		user_time_t;
#define USER_ADDR_NULL	((user_addr_t) 0)
#define CAST_USER_ADDR_T(a_ptr)   ((user_addr_t)((uintptr_t)(a_ptr)))

#ifndef __offsetof
#define __offsetof(type, field) ((size_t)(&((type *)0)->field))
#endif

#endif /* __ASSEMBLER__ */
#endif	/* _MACHTYPES_H_ */

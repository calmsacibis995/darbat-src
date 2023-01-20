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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */

#ifndef _OS_OSLIB_H
#define _OS_OSLIB_H

#include <libkern/OSBase.h>

#ifdef KERNEL
#if 0
#define MACH_ASSERT	1
#endif
#endif

__BEGIN_DECLS

#include <stdarg.h>
#ifndef L4IOKIT
#include <sys/systm.h>
#endif

#ifdef L4IOKIT
#include <xnu_glue.h>	/* will be deprecated ASAP */
#include <xnucompat.h>
#include <stdio.h>	/* printf */
#endif

#include <kern/assert.h>
#ifdef	KERNEL_PRIVATE
#include <kern/kalloc.h>
#endif

__END_DECLS

#ifndef NULL
#define NULL 0
#endif

#endif /* _OS_OSLIB_H  */

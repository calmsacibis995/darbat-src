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
 * Copyright (c) 1998-2004 Apple Computer, Inc. All rights reserved.
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
#ifndef __IOKIT_SYSTEM_H
#define __IOKIT_SYSTEM_H

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <mach/mach_types.h>
#include <mach/mach_interface.h>
#include <mach/memory_object_types.h>

#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include <IOKit/assert.h>  /* Must be before other includes of kern/assert.h */

#include <kern/kern_types.h>
#include <kern/thread.h>
#include <kern/debug.h>
#include <kern/task.h>
#include <kern/sched_prim.h>
#include <kern/locks.h>
#include <kern/queue.h>
#include <kern/ipc_mig.h>
#ifndef MACH_KERNEL_PRIVATE
#include <libkern/libkern.h>
#endif

#ifdef	KERNEL_PRIVATE
#include <kern/kalloc.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#endif /* KERNEL_PRIVATE */


extern void	_doprnt( const char *format, va_list *arg,
			void (*putc)(char), int radix );


__END_DECLS

#endif /* !__IOKIT_SYSTEM_H */

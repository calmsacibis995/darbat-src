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
 * machine_routines.c
 *
 */

#include <xnu_glue.h>
#include <xnucompat.h>

#include <kern/kern_types.h>
#include <kern/locks.h>

#include <l4/machine_routines.h>

#include <mach/vm_types.h>
#include <mach/mach_types.h>

#include <stdio.h>

lck_mtx_t	*interrupt_mutex;

/*
 * XXX: BROKEN.  Think about how to handle this.
 * XXX: I know what potential issues there but I need to think
 * XXX: and sit on it for a bit.
 */
boolean_t
ml_set_interrupts_enabled(boolean_t enable)
{

	if (enable) {
#if 0
		lck_mtx_unlock(interrupt_mutex);
#endif
		return TRUE;
	} else {
#if 0
		lck_mtx_lock(interrupt_mutex);
#endif
		return FALSE;
	}
}

void
ml_install_interrupt_handler(
    void *nub,
    int source,
    void *target,
    IOInterruptHandler handler,
    void *refCon);

void
ml_install_interrupt_handler(
    void *nub,
    int source,
    void *target,
    IOInterruptHandler handler,
    void *refCon)
{

	printf("%s: called with nub %p src %d tgt %p handler %p refCon %p\n",
	    __FUNCTION__, nub, source, target, handler, refCon);

	l4intrnub = nub;
	l4intrsource = source;
	l4intrtarget = target;
	l4intrhandler = handler;
	l4intrrefCon = refCon;

	return;
}

boolean_t
ml_at_interrupt_context(void)
{
	if (L4_Myself().raw == l4intrgettid().raw)
		return TRUE;
	else
		return FALSE;
}

/*
 * XXX: Hack.  Iguana memory is mapped 1:1 for us.
 */
vm_offset_t
ml_static_ptovirt(
	vm_offset_t paddr)
{
#ifdef VERBOSE_IOKIT
	printf("%s: warning: Iguana memory mapped 1:1\n", __func__);
#endif
	return (paddr);
} 

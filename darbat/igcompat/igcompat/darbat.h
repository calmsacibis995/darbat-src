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

#ifndef __IG_DARBAT_H__
#define __IG_DARBAT_H__
#include <mach/mach_types.h>

void *darbat_rgn_alloc( uintptr_t size );
void *darbat_mapped_rgn_alloc( uintptr_t size ); /* one we can map() on */

int darbat_find_root_image( void **, uintptr_t * );


/* do a virt/phys alias in the AS */
void darbat_map( void *phys, void *virt );

/* flush a mapping */
void darbat_flush_page( void *addr );
void darbat_unmap_page( void *addr );

/* create a local L4 thread */
unsigned long darbat_create_kthread( void (*)(void*), void* );

/* Create a thread (and a space?) */
unsigned long darbat_thread_create( thread_t thread );

/* send an L4 startup message to a thread */
void darbat_start_thread( unsigned int, unsigned int, unsigned int );

/* call a function periodically, every msec milliseconds */
int darbat_periodic_function( int (*)(void), unsigned msec );

/* poll the input console */
#if 0
int darbat_cons_poll(void);
#else	/* XXX not yet */
void darbat_cons_write(int c);
int darbat_cons_poll(void);
#endif

int darbat_cons_poll_nonblocking(void);

uint64_t darbat_cpu_freq(void);

#endif /* __IG_DARBAT_H__ */

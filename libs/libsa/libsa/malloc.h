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
#ifndef _LIBSA_MALLOC_H_
#define _LIBSA_MALLOC_H_

#include <sys/cdefs.h>
#include "stdlib.h"

__BEGIN_DECLS

/*****
 * These functions are the minimum necessary for use
 * by kld and its client.
 */
void * malloc(size_t size);
void * realloc(void * address, size_t new_size);
void   free(void * address);

void   malloc_init(void);
void   malloc_reset(void); // Destroy all memory regions


/*****
 * These functions aren't compiled into the kernel.
 * Their definitions are in the files malloc_debug
 * and malloc_unused, in case they're ever needed.
 */
#if 0
void   free_all(void);     // "Free" all memory blocks
size_t malloc_size(void * address);
int    malloc_is_valid(void * address);

#ifdef DEBUG
size_t malloc_hiwat(void);
size_t malloc_current_usage(void);
size_t malloc_region_usage(void);
double malloc_peak_usage(void);
double malloc_min_usage(void);
size_t malloc_unused(void);
double malloc_current_efficiency(void);
void malloc_clear_hiwat(void);
void malloc_report(void);
int malloc_sanity_check(void);
#endif /* DEBUG */
#endif /* 0 */

__END_DECLS

#endif /* defined _LIBSA_MALLOC_H_ */

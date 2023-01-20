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
#ifndef _LIBSA_STDLIB_H_
#define _LIBSA_STDLIB_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

#ifndef L4IOKIT
#ifndef _SIZE_T
#define _SIZE_T
typedef __darwin_size_t	size_t;
#endif

#ifndef NULL
#define NULL   (0)
#endif
#else
#include <stdlib.h>
#endif

#ifndef L4IOKIT
__private_extern__ char *kld_basefile_name;
#else
extern char *kld_basefile_name;
#endif


__BEGIN_DECLS

#ifndef L4IOKIT
__private_extern__ void * malloc(size_t size);
__private_extern__ void   free(void * address);
__private_extern__ void   free_all(void);     // "Free" all memory blocks
__private_extern__ void   malloc_reset(void); // Destroy all memory regions
__private_extern__ void * realloc(void * address, size_t new_size);

__private_extern__ char * strrchr(const char *cp, int ch);
#else
#include <stdlib.h>
#endif

#ifndef L4IOKIT	/* In Ig libc XXX Ig libc verison sux! */
__private_extern__ void qsort(
    void * array,
    size_t nmembers,
    size_t member_size,
    int (*)(const void *, const void *));
#endif

#ifdef L4IOKIT
/*
 * In Ig's stdlib.h, but Ig doesn't implement it!
 *
 */
#endif
#ifndef L4IOKIT
__private_extern__ void * bsearch(
    register const void *key,
    const void *base0,
    size_t nmemb,
    register size_t size,
    register int (*compar)(const void *, const void *));
#endif

#ifndef L4IOKIT
/* These are defined in the kernel.
 */
extern long     strtol(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
#endif

__END_DECLS

#endif /* _LIBSA_STDLIB_H_ */

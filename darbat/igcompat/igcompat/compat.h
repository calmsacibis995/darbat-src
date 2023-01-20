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

#ifndef __IG_COMPAT_H__
#define __IG_COMPAT_H__

/* XXX: boolean_t is a pain... we need to move PE_parse_boot_arg! */
#include <mach/i386/boolean.h>

/*
 * How the heck do you have bcopy() and friends without this?
 *
 */
#include <string.h>

#if 0
extern boolean_t PE_parse_boot_arg(
	const char	*arg_string,
	void    	*arg_ptr);
#endif /* 0 */

//extern char * PE_boot_args(void);

/* not defined anywhere handy */
extern void kprintf(const char *, ...);


/* NFI where these should come from really */
// void bcopy(const void *src, void *dest, size_t n);
#define bcopy( src, dest, n ) memmove( (dest), (src), (n) )

// void bzero(void *s, size_t n);
#define bzero( s, n ) memset( (s), 0, (n) )

// int bcmp(const void *s1, const void *s2, size_t n);
#define bcmp( s1, s2, n ) memcmp( (s1), (s2), (n) )


#endif /* __IG_COMPAT_H__ */

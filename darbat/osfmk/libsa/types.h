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
 * @OSF_COPYRIGHT@
 */
/*
 * HISTORY
 * 
 * Revision 1.1.1.1  1998/09/22 21:05:51  wsanchez
 * Import of Mac OS X kernel (~semeria)
 *
 * Revision 1.1.1.1  1998/03/07 02:25:35  wsanchez
 * Import of OSF Mach kernel (~mburg)
 *
 * Revision 1.1.2.1  1996/09/17  16:56:21  bruel
 * 	created from standalone mach servers.
 * 	[96/09/17            bruel]
 *
 * $EndLog$
 */

#ifndef _MACH_TYPES_H_
#define _MACH_TYPES_H_

#include "machine/types.h"

#ifndef	_SIZE_T
#define _SIZE_T
typedef unsigned long	size_t;
#endif	/* _SIZE_T */

/*
 * Common type definitions that lots of old files seem to want.
 */

typedef	unsigned char	u_char;		/* unsigned char */
typedef	unsigned short	u_short;	/* unsigned short */
typedef	unsigned int	u_int;		/* unsigned int */
typedef	unsigned long	u_long;		/* unsigned long */

typedef struct _quad_ {
	unsigned int	val[2];		/* 2 32-bit values make... */
} quad;					/* an 8-byte item */

typedef	char *		caddr_t;	/* address of a (signed) char */

typedef int		time_t;		/* a signed 32    */
typedef unsigned int	daddr_t;	/* an unsigned 32 */
#if 0 /* off_t should be 64-bit ! */
typedef	unsigned int	off_t;		/* another unsigned 32 */
#endif


#define	major(i)	(((i) >> 8) & 0xFF)
#define	minor(i)	((i) & 0xFF)
#define	makedev(i,j)	((((i) & 0xFF) << 8) | ((j) & 0xFF))

#ifndef	NULL
#define	NULL		((void *) 0)	/* the null pointer */
#endif

/*
 * Shorthand type definitions for unsigned storage classes
 */
typedef	unsigned char	uchar_t;
typedef	unsigned short	ushort_t;
typedef	unsigned int	uint_t;
typedef unsigned long	ulong_t;
typedef	volatile unsigned char	vuchar_t;
typedef	volatile unsigned short	vushort_t;
typedef	volatile unsigned int	vuint_t;
typedef volatile unsigned long	vulong_t;
#endif	/* _MACH_TYPES_H_ */

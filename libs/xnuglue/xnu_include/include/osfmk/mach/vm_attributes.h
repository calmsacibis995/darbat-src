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
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	mach/vm_attributes.h
 *	Author:	Alessandro Forin
 *
 *	Virtual memory attributes definitions.
 *
 *	These definitions are in addition to the machine-independent
 *	ones (e.g. protection), and are only selectively supported
 *	on specific machine architectures.
 *
 */

#ifndef	_MACH_VM_ATTRIBUTES_H_
#define	_MACH_VM_ATTRIBUTES_H_

/*
 *	Types of machine-dependent attributes
 */
typedef unsigned int	vm_machine_attribute_t;

#define	MATTR_CACHE		1	/* cachability */
#define MATTR_MIGRATE		2	/* migrability */
#define	MATTR_REPLICATE		4	/* replicability */

/*
 *	Values for the above, e.g. operations on attribute
 */
typedef int		vm_machine_attribute_val_t;

#define MATTR_VAL_OFF		0	/* (generic) turn attribute off */
#define MATTR_VAL_ON		1	/* (generic) turn attribute on */
#define MATTR_VAL_GET		2	/* (generic) return current value */

#define MATTR_VAL_CACHE_FLUSH	6	/* flush from all caches */
#define MATTR_VAL_DCACHE_FLUSH	7	/* flush from data caches */
#define MATTR_VAL_ICACHE_FLUSH	8	/* flush from instruction caches */
#define MATTR_VAL_CACHE_SYNC	9	/* sync I+D caches */
#define MATTR_VAL_CACHE_SYNC	9	/* sync I+D caches */

#define MATTR_VAL_GET_INFO	10	/* get page info (stats) */

#endif	/* _MACH_VM_ATTRIBUTES_H_ */

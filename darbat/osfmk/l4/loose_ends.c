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
#include <string.h>
#include <mach/boolean.h>
#include <mach/i386/vm_types.h>
#include <mach/i386/vm_param.h>
#include <kern/kern_types.h>
#include <kern/misc_protos.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_fault.h>


uint32_t
hw_atomic_or(
	uint32_t	*dest,
	uint32_t	mask)
{
	uint32_t	oldValue;
	uint32_t	newValue;

	/*
	 *	Atomically ORs the second parameter into the first.
	 *	Returns the result.
	 */


//      XXX: not so atomic :)
//	do {
		oldValue = *dest;
		newValue = (oldValue | mask);

		*dest = newValue;

//	} while (!OSCompareAndSwap((UInt32)oldValue,
//		(UInt32)newValue, (UInt32 *)dest));
	
	return newValue;
}


uint32_t
hw_atomic_and(
	uint32_t	*dest,
	uint32_t	mask)
{
	uint32_t	oldValue;
	uint32_t	newValue;
	
	// do {
		oldValue = *dest;
		newValue = (oldValue & mask);

		*dest = newValue;

		//} while (!OSCompareAndSwap((UInt32)oldValue,
		//		   (UInt32)newValue, (UInt32 *)dest));
	
	return newValue;
}

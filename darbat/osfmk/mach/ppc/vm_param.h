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
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
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

#ifndef	_MACH_PPC_VM_PARAM_H_
#define _MACH_PPC_VM_PARAM_H_

/*
 * These are the global definitions
 */

#define BYTE_SIZE		8		/* byte size in bits */

#define PPC_PGBYTES		4096	/* bytes per ppc page */
#define PPC_PGSHIFT		12		/* number of bits to shift for pages */

#define	PAGE_SIZE		PPC_PGBYTES
#define	PAGE_SHIFT		PPC_PGSHIFT
#define PAGE_MASK		(PAGE_SIZE - 1)

#if 0
#define VM_MAX_PAGE_ADDRESS 0xFFFFFFFFFFFFF000ULL
#else
/* 
 * LP64todo - For now, we are limited to 51-bits of user addressing
 */
#define VM_MAX_PAGE_ADDRESS 0x0007FFFFFFFFF000ULL
#endif

#define MACH_VM_MIN_ADDRESS	((mach_vm_offset_t) 0)
#define MACH_VM_MAX_ADDRESS	((mach_vm_offset_t) VM_MAX_PAGE_ADDRESS)

/*
 * These are the values relative to the local process.
 */
#if defined (__ppc64__)
/*
 * LP64todo - We don't have the 64-bit address space layout yet.
 * Use the 32-bit stack layout for now.
 */
#define VM_MIN_ADDRESS	((vm_offset_t) MACH_VM_MIN_ADDRESS)
#define VM_MAX_ADDRESS	((vm_offset_t) MACH_VM_MAX_ADDRESS)
#define USER_STACK_END  	((vm_offset_t) 0x00000000ffff0000ULL)
#else
#define VM_MIN_ADDRESS	((vm_offset_t) 0)
#define VM_MAX_ADDRESS	((vm_offset_t) (VM_MAX_PAGE_ADDRESS & 0xFFFFFFFF))
#define USER_STACK_END  	((vm_offset_t) 0xffff0000U)
#endif /* defined(__ppc64__) */

#ifdef	KERNEL_PRIVATE

/* Kernel-wide values */
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0x00001000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0xDFFFFFFF)
#define KERNEL_STACK_SIZE		(4 * PPC_PGBYTES)
#define INTSTACK_SIZE		(5 * PPC_PGBYTES)

#define VM_MAP_MIN_ADDRESS	MACH_VM_MIN_ADDRESS
#define VM_MAP_MAX_ADDRESS	MACH_VM_MAX_ADDRESS

#ifdef	MACH_KERNEL_PRIVATE

/* For implementing legacy 32-bit interfaces */
#define VM32_SUPPORT
#define VM32_MIN_ADDRESS	((vm32_offset_t) 0)
#define VM32_MAX_ADDRESS	((vm32_offset_t) (VM_MAX_PAGE_ADDRESS & 0xFFFFFFFF))

#endif	/* MACH_KERNEL_PRIVATE */

#endif	/* KERNEL_PRIVATE */

#endif	/* _MACH_PPC_VM_PARAM_H_ */

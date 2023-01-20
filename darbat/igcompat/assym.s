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
#define AST_URGENT	$4
#define SLOCK_ILK	$0
#define MUTEX_LOCKED	4
#define MUTEX_WAITERS	8
#define MUTEX_PROMOTED_PRI	10
#define MUTEX_IND	4103
#define MUTEX_ITAG	0
#define MUTEX_PTR	4
#define TH_RECOVER	$452
#define TH_CONTINUATION	$124
#define TH_KERNEL_STACK	$140
#define TASK_MACH_EXC_PORT	$248
#define ACT_MACH_EXC_PORT	$920
#define ACT_TASK	$768
#define ACT_PCB	$764
#define ACT_MAP	$772
#define MAP_PMAP	$68
#define KSS_EBX	16360
#define KSS_ESP	16364
#define KSS_EBP	16368
#define KSS_EDI	16372
#define KSS_ESI	16376
#define KSS_EIP	16380
#define IKS_SIZE	$24
#define IEL_SIZE	$4
#define PCB_FPS	$212
#define PCB_ISS	$80
#define FP_VALID	$0
#define FP_SAVE_STATE	$4
#define R_CS	$60
#define R_SS	$72
#define R_UESP	$68
#define R_EBP	$24
#define R_EAX	$44
#define R_EBX	$32
#define R_ECX	$40
#define R_EDX	$36
#define R_ESI	$20
#define R_EDI	$16
#define R_TRAPNO	$48
#define R_ERR	$52
#define R_EFLAGS	$64
#define R_EIP	$56
#define R_CR2	$28
#define ISS_SIZE	$124
#define I_ECX	$20
#define I_EIP	$28
#define I_CS	$32
#define I_EFL	$36
#define NBPG	$4096
#define PAGE_SIZE	$4096
#define PAGE_MASK	$4095
#define PAGE_SHIFT	$12
#define NKPT	$32
#define KPTDI	$768
#define VM_MIN_ADDRESS	$0
#define VM_MAX_ADDRESS	$-1073741824
#define LINEAR_KERNELBASE	$-1073741824
#define KERNEL_STACK_SIZE	$16384
#define COMM_PAGE_BASE_ADDR	$-81920
#define PDESHIFT	$22
#define PTEMASK	$1023
#define PTEINDX	$2
#define PTE_PFN	$-4096
#define PTE_V	$1
#define PTE_W	$2
#define PTE_PS	$128
#define PTE_U	$4
#define PTE_INVALID	$-2
#define CR4_PAE	$32
#define NPGPTD	$1
#define IDTSZ	$256
#define GDTSZ	$13
#define LDTSZ	$15
#define KERNEL_CS	$8
#define KERNEL_DS	$16
#define USER_CS	$23
#define USER_DS	$31
#define KERNEL_TSS	$32
#define KERNEL_LDT	$24
#define CPU_DATA_GS	$72
#define CPU_THIS	$0
#define CPU_ACTIVE_THREAD	4
#define CPU_ACTIVE_KLOADED	$8
#define CPU_ACTIVE_STACK	$12
#define CPU_KERNEL_STACK	$16
#define CPU_INT_STACK_TOP	$20
#define CPU_INTERRUPT_LEVEL	$32
#define CPU_SIMPLE_LOCK_COUNT	$28
#define CPU_NUMBER_GS	$36
#define CPU_RUNNING	$72
#define CPU_MCOUNT_OFF	$52
#define CPU_PENDING_AST	$56
#define CPU_DESC_TABLEP	$164
#define CPU_PROCESSOR	$156
#define CPU_RTC_NANOTIME	$112
#define INTEL_PTE_KERNEL	$3
#define PTDPTDI	$1021
#define PDESHIFT	$22
#define PDESIZE	$4
#define PTESIZE	$4
#define APTDPTDI	$1022
#define KERNELBASEPDE	$3072
#define TSS_ESP0	$4
#define TSS_SS0	$8
#define TSS_LDT	$96
#define TSS_PDBR	$28
#define TSS_LINK	$0
#define K_TASK_GATE	$133
#define K_TRAP_GATE	$143
#define U_TRAP_GATE	$239
#define K_INTR_GATE	$142
#define K_TSS	$137
#define USL_INTERLOCK	$0
#define INTSTACK_SIZE	$16384
#define MP_GDT	$2048
#define MP_IDT	$0
#define TIMER_LOW	$0
#define TIMER_HIGH	$4
#define TIMER_HIGHCHK	$8
#define NANOTIME_BASE_TSC	$0
#define NANOTIME_BASE_NS	$8
#define NANOTIME_SCALE	$16
#define NANOTIME_SHIFT	$20
#define NANOTIME_CHECK_TSC	$24
#define RTN_TSC	$0
#define RTN_NANOS	$8
#define RTN_SCALE	$16
#define RTN_SHIFT	$20
#define TIMER_LOW	$0
#define TIMER_HIGH	$4
#define TIMER_HIGHCHK	$8
#define TIMER_TSTAMP	$12
#define CURRENT_TIMER	$1216
#define SYSTEM_TIMER	$220
#define USER_TIMER	$300

/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  Karlsruhe University
 *                
 * File path:     arch/ia32/ia32.h
 * Description:   IA32 specific constants
 *		  do _not_ put any functions into this file
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: ia32.h,v 1.6 2004/09/15 18:07:50 jdoll Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__IA32__IA32_H__
#define __ARCH__IA32__IA32_H__


/**********************************************************************
 *    MMU
 **********************************************************************/

#define IA32_PAGEDIR_BITS	22
#define IA32_PAGEDIR_SIZE	(__UL(1) << IA32_PAGEDIR_BITS)
#define IA32_PAGEDIR_MASK	(~(IA32_PAGEDIR_SIZE - 1))

#define IA32_SUPERPAGE_BITS	22
#define IA32_SUPERPAGE_SIZE	(__UL(1) << IA32_SUPERPAGE_BITS)
#define IA32_SUPERPAGE_MASK	(~(IA32_SUPERPAGE_SIZE - 1))

#define IA32_PAGE_BITS		12
#define IA32_PAGE_SIZE		(__UL(1) << IA32_PAGE_BITS)
#define IA32_PAGE_MASK		(~(IA32_PAGE_SIZE - 1))

#define IA32_PTAB_BYTES		4096

#define IA32_PAGE_VALID		(1<<0)
#define IA32_PAGE_WRITABLE	(1<<1)
#define IA32_PAGE_USER		(1<<2)
#define IA32_PAGE_KERNEL	(0<<2)
#define IA32_PAGE_WRITE_THROUGH	(1<<3)
#define IA32_PAGE_CACHE_DISABLE	(1<<4)
#define IA32_PAGE_ACCESSED	(1<<5)
#define IA32_PAGE_DIRTY		(1<<6)
#define IA32_PAGE_SUPER		(1<<7)
#define IA32_PAGE_GLOBAL	(1<<8)
#define IA32_PAGE_FLAGS_MASK	(0x017f)
#define IA32_PTAB_FLAGS_MASK	(0x0007)



/**********************************************************************
 *    CPU features (CPUID)  
 **********************************************************************/

#define IA32_FEAT_FPU	(1 << 0)
#define IA32_FEAT_VME	(1 << 1)
#define IA32_FEAT_DE	(1 << 2)
#define IA32_FEAT_PSE	(1 << 3)
#define IA32_FEAT_TSC	(1 << 4)
#define IA32_FEAT_MSR	(1 << 5)
#define IA32_FEAT_PAE	(1 << 6)
#define IA32_FEAT_MCE	(1 << 7)
#define IA32_FEAT_CXS	(1 << 8)
#define IA32_FEAT_APIC	(1 << 9)
#define IA32_FEAT_SEP	(1 << 11)
#define IA32_FEAT_MTRR	(1 << 12)
#define IA32_FEAT_PGE	(1 << 13)
#define IA32_FEAT_MCA	(1 << 14)
#define IA32_FEAT_CMOV	(1 << 15)
#define IA32_FEAT_FGPAT	(1 << 16)
#define IA32_FEAT_PSE36	(1 << 17)
#define IA32_FEAT_PSN	(1 << 18)
#define IA32_FEAT_CLFLSH	(1 << 19)
#define IA32_FEAT_DS	(1 << 21)
#define IA32_FEAT_ACPI	(1 << 22)
#define IA32_FEAT_MMX	(1 << 23)
#define IA32_FEAT_FXSR	(1 << 24)
#define IA32_FEAT_XMM	(1 << 25)



/**********************************************************************
 *    EFLAGS register bits 
 **********************************************************************/

#define IA32_EFL_CF	(1 <<  0)	/* carry flag			*/
#define IA32_EFL_PF	(1 <<  2)	/* parity flag			*/
#define IA32_EFL_AF	(1 <<  4)	/* auxiliary carry flag		*/
#define IA32_EFL_ZF	(1 <<  6)	/* zero flag			*/
#define IA32_EFL_SF	(1 <<  7)	/* sign flag			*/
#define IA32_EFL_TF	(1 <<  8)	/* trap flag			*/
#define IA32_EFL_IF	(1 <<  9)	/* interrupt enable flag	*/
#define IA32_EFL_DF	(1 << 10)	/* direction flag		*/
#define IA32_EFL_OF	(1 << 11)	/* overflow flag		*/
#define IA32_EFL_NT	(1 << 14)	/* nested task flag		*/
#define IA32_EFL_RF	(1 << 16)	/* resume flag			*/
#define IA32_EFL_VM	(1 << 17)	/* virtual 8086 mode		*/
#define IA32_EFL_AC	(1 << 18)	/* alignement check		*/
#define IA32_EFL_VIF	(1 << 19)	/* virtual interrupt flag	*/
#define IA32_EFL_VIP	(1 << 20)	/* virtual interrupt pending	*/
#define IA32_EFL_ID	(1 << 21)	/* ID flag			*/
#define IA32_EFL_IOPL(x)	((x & 3) << 12)	/* the IO privilege level field	*/



/**********************************************************************
 *    control register bits (CR0, CR3, CR4)
 **********************************************************************/

#define IA32_CR0_PE	(1 <<  0)	/* enable protected mode	*/
#define IA32_CR0_EM	(1 <<  2)	/* disable fpu			*/
#define IA32_CR0_TS	(1 <<  3)	/* task switched		*/
#define IA32_CR0_WP	(1 << 16)	/* force write protection on user
					   read only pages for kernel	*/
#define IA32_CR0_NW	(1 << 29)	/* not write through		*/
#define IA32_CR0_CD	(1 << 30)	/* cache disabled		*/
#define IA32_CR0_PG	(1 << 31)	/* enable paging		*/

#define IA32_CR3_PCD	(1 <<  3)	/* page-level cache disable	*/
#define IA32_CR3_PWT	(1 <<  4)	/* page-level writes transparent*/

#define IA32_CR4_VME	(1 <<  0)	/* virtual 8086 mode extension	*/
#define IA32_CR4_PVI	(1 <<  1)	/* enable protected mode
					   virtual interrupts		*/
#define IA32_CR4_TSD	(1 <<  2)	/* time stamp disable		*/
#define IA32_CR4_DE	(1 <<  3)	/* debug extensions		*/
#define IA32_CR4_PSE	(1 <<  4)	/* page size extension (4MB)	*/
#define IA32_CR4_PAE	(1 <<  5)	/* physical address extension	*/
#define IA32_CR4_MCE	(1 <<  6)	/* machine check extensions	*/
#define IA32_CR4_PGE	(1 <<  7)	/* enable global pages		*/
#define IA32_CR4_PCE	(1 <<  8)	/* allow user to use rdpmc	*/
#define IA32_CR4_OSFXSR	(1 <<  9)	/* enable fxsave/fxrstor + sse	*/
#define IA32_CR4_OSXMMEXCPT (1 << 10)	/* support for unmsk. SIMD exc. */



/**********************************************************************
 * Model specific register locations.
 **********************************************************************/

#define IA32_SYSENTER_CS_MSR		0x174
#define IA32_SYSENTER_EIP_MSR		0x176
#define IA32_SYSENTER_ESP_MSR		0x175

#define IA32_DEBUGCTL			0x1d9

#if defined(CONFIG_CPU_IA32_I686)
# define IA32_PERFCTR0			0x0c1
# define IA32_PERFCTR1			0x0c2
# define IA32_EVENTSEL0			0x186
# define IA32_EVENTSEL1			0x187
# define IA32_LASTBRANCHFROMIP		0x1db
# define IA32_LASTBRANCHTOIP		0x1dc
# define IA32_LASTINTFROMIP		0x1dd
# define IA32_LASTINTTOIP		0x1de
# define IA32_MTRRBASE(x)		(0x200 + 2*(x) + 0)
# define IA32_MTRRMASK(x)		(0x200 + 2*(x) + 1)
#endif /* CONFIG_CPU_IA32_I686 */

#if defined(CONFIG_CPU_IA32_P4)
# define IA32_MISC_ENABLE		0x1a0
# define IA32_COUNTER_BASE		0x300
# define IA32_CCCR_BASE			0x360
# define IA32_TC_PRECISE_EVENT		0x3f0
# define IA32_PEBS_ENABLE		0x3f1
# define IA32_PEBS_MATRIX_VERT		0x3f2
# define IA32_DS_AREA			0x600
# define IA32_LER_FROM_LIP		0x1d7
# define IA32_LER_TO_LIP		0x1d8
# define IA32_LASTBRANCH_TOS		0x1da
# define IA32_LASTBRANCH_0		0x1db
# define IA32_LASTBRANCH_1		0x1dc
# define IA32_LASTBRANCH_2		0x1dd
# define IA32_LASTBRANCH_3		0x1de

/* Processor features in the MISC_ENABLE MSR. */
# define IA32_ENABLE_FAST_STRINGS	(1 << 0)
# define IA32_ENABLE_X87_FPU		(1 << 2)
# define IA32_ENABLE_THERMAL_MONITOR	(1 << 3)
# define IA32_ENABLE_SPLIT_LOCK_DISABLE	(1 << 4)
# define IA32_ENABLE_PERFMON		(1 << 7)
# define IA32_ENABLE_BRANCH_TRACE	(1 << 11)
# define IA32_ENABLE_PEBS		(1 << 12)

/* Preceise Event-Based Sampling (PEBS) support. */
# define IA32_PEBS_REPLAY_TAG_MASK	((1 << 12)-1)
# define IA32_PEBS_UOP_TAG		(1 << 24)
# define IA32_PEBS_ENABLE_PEBS		(1 << 25)
#endif /* CONFIG_CPU_IA32_P4 */

#if defined(CONFIG_CPU_IA32_K8)
# define IA32_LASTBRANCH_0		0x1db
# define IA32_LASTBRANCH_1		0x1dc
# define IA32_LASTBRANCH_2		0x1dd
# define IA32_LASTBRANCH_3		0x1de

# define IA32_EVENTSEL0			0xc0010000
# define IA32_EVENTSEL1			0xc0010001
# define IA32_EVENTSEL2			0xc0010002
# define IA32_EVENTSEL3			0xc0010003
# define IA32_PERFCTR0			0xc0010004
# define IA32_PERFCTR1			0xc0010005
# define IA32_PERFCTR2			0xc0010006
# define IA32_PERFCTR3			0xc0010007
#endif /* CONFIG_CPU_IA32_K8 */



/**********************************************************************
 *   Cache line configurations
 **********************************************************************/

/* 486 */
#if defined(CONFIG_CPU_IA32_I486)
# define IA32_CACHE_LINE_SIZE_L1        16
# define IA32_CACHE_LINE_SIZE_L2        16

/* P1, PII, PIII */
#elif defined(CONFIG_CPU_IA32_I586) || defined(CONFIG_CPU_IA32_I686) || defined(CONFIG_CPU_IA32_C3)
# define IA32_CACHE_LINE_SIZE_L1	32
# define IA32_CACHE_LINE_SIZE_L2	32

/* P4, Xeon */
#elif defined(CONFIG_CPU_IA32_P4)
# define IA32_CACHE_LINE_SIZE_L1	32
# define IA32_CACHE_LINE_SIZE_L2	64

/* AMD K8 (Opteron) */
#elif defined(CONFIG_CPU_IA32_K8)
# define IA32_CACHE_LINE_SIZE_L1	64
# define IA32_CACHE_LINE_SIZE_L2	64

#else
# error unknown architecture - specify cache line size
#endif



#endif /* !__ARCH__IA32__IA32_H__ */

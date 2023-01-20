/*********************************************************************
 *                
 * Copyright (C) 2003,  Karlsruhe University
 *                
 * File path:     arch/amd64/cpuid.h
 * Description:   X86-64 CPUID features 
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
 * $Id: cpuid.h,v 1.2 2003/09/24 19:04:26 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__AMD64__CPUID_H__
#define __ARCH__AMD64__CPUID_H__

#include <init.h>

/* CPUID functions */
#define CPUID_PROCESSOR_VENDOR		0x0
#define CPUID_MAX_STD_FN_NR		0x0
#define CPUID_STD_FEATURES		0x1

#define CPUID_MAX_EXT_FN_NR		0x80000000
#define CPUID_AMD_FEATURES		0x80000001

#define CPUID_CPU_NAME1			0x80000002
#define CPUID_CPU_NAME2			0x80000003
#define CPUID_CPU_NAME3			0x80000004
#define CPUID_CACHE_FEATURES1		0x80000005
#define CPUID_CACHE_FEATURES2		0x80000006
#define CPUID_APM_FEATURES		0x80000007
#define CPUID_ADDRESS_SIZES		0x80000008

/* CPUID standard features */
#define CPUID_STD_HAS_FPU	        (1 <<  0)	/* x87 unit */
#define CPUID_STD_HAS_VME	        (1 <<  1)	/* virtual mode */
#define CPUID_STD_HAS_DBX	        (1 <<  2)	/* debug extensions */
#define CPUID_STD_HAS_PSE	        (1 <<  3)	/* page size */
#define CPUID_STD_HAS_TSC	        (1 <<  4)	/* time stamp counters */
#define CPUID_STD_HAS_MSR	        (1 <<  5)	/* model specific regs */
#define CPUID_STD_HAS_PAE	        (1 <<  6)	/* physical address
							 * extensions  */
#define CPUID_STD_HAS_MCE	        (1 <<  7)	/* machine check
							 * exception */
#define CPUID_STD_HAS_CMPXCHG8	        (1 <<  8)	/* cmpxchg8 */
#define CPUID_STD_HAS_APIC	        (1 <<  9)	/* apic */
#define CPUID_STD_HAS_SYSENTER	        (1 << 11)	/* sysenter/exit*/
#define CPUID_STD_HAS_MTRR	        (1 << 12)	/* MTRRs */
#define CPUID_STD_HAS_PGE	        (1 << 13)	/* global pages */
#define CPUID_STD_HAS_MCA	        (1 << 14)	/* machine check
							 * architecture  */
#define CPUID_STD_HAS_CMOV	        (1 << 15)	/* conditional moves */
#define CPUID_STD_HAS_PAT	        (1 << 16)	/* page attribute table */
#define CPUID_STD_HAS_PSE2	        (1 << 17)	/* page size (another one?)*/
#define CPUID_STD_HAS_CFLUSH	        (1 << 19)	/* cflush */
#define CPUID_STD_HAS_MMX	        (1 << 23)	/* mmx extensions */
#define CPUID_STD_HAS_FXSAVE	        (1 << 24)	/* fxsave/fxstor */
#define CPUID_STD_HAS_SSE	        (1 << 25)	/* sse */
#define CPUID_STD_HAS_SSE2	        (1 << 26)	/* sse */
							 
/* CPUID extended AMD features (if different to standard features) */
#define CPUID_AMD_HAS_SYSCALL		(1 << 11)	/* syscall/sysret */
#define CPUID_AMD_HAS_NX		(1 << 20)	/* nx page protection */
#define CPUID_AMD_HAS_AMDMMX		(1 << 22)	/* amd mmx extensions */
#define CPUID_AMD_HAS_LONGMODE		(1 << 29)	/* long mode  */
#define CPUID_AMD_HAS_3DNOWEXT		(1 << 30)	/* amd 3dnow extensions */
#define CPUID_AMD_HAS_3DNOW		(1 << 31)	/* amd 3dnow! */

/* CPUID extended APM features */
#define CPUID_APM_HAS_TS		(1 << 0)        /* thermal sensor */
#define CPUID_APM_HAS_FID		(1 << 1)        /* frequency id control */
#define CPUID_APM_HAS_VID		(1 << 2)        /* voltage id control */
#define CPUID_APM_HAS_TT		(1 << 3)        /* thermal trip */


typedef union {
    u32_t raw[2];

    struct{
	struct{
	    u32_t entries	:8;
	    u32_t assoc		:8;
	} itlb_2m;
	
	struct{
	    u32_t entries	:8;
	    u32_t assoc		:8;
	} dtlb_2m;
	
	struct{
	    u32_t entries	:8;
	    u32_t assoc		:8;
	} itlb_4k;
	
	struct{
	    u32_t entries	:8;
	    u32_t assoc		:8;
	} dtlb_4k;
    }d;
} amd64_tlb_info_t;


typedef union {
    u32_t raw[2];
    struct{ 
	struct{
	    u32_t l_size	:8;
	    u32_t l_per_tag	:8;
	    u32_t assoc		:8;
	    u32_t size		:8;
	} icache;
	struct{
	    u32_t l_size	:8;
	    u32_t l_per_tag	:8;
	    u32_t assoc		:8;
	    u32_t size		:8;
	} dcache;
    }d;
} amd64_cache_info_t;


class amd64_cpu_features_t{

private:
    char cpu_vendor[13];
    char cpu_name[49];
    u8_t family;
    u8_t model;
    u8_t stepping;
    u8_t brand_id;
    u8_t cflush_size;
    u8_t apic_id;

    u32_t max_std_fn;
    u32_t max_ext_fn;

    u32_t std_features;
    u32_t amd_features;
    u32_t apm_features;
    
    amd64_tlb_info_t l1_tlb;
    amd64_cache_info_t l1_cache;

    amd64_tlb_info_t l2_tlb;
    amd64_cache_info_t l2_cache;

    bool l2_2m_tlb_unified;
    bool l2_4k_tlb_unified;
    bool l2_cache_unified;

    u8_t paddr_bits;
    u8_t vaddr_bits;
    
public:
    amd64_cpu_features_t() SECTION(SEC_INIT);
    void dump_features();

    char *get_cpu_vendor() { return cpu_vendor; }
    char *get_cpu_name() { return cpu_name; }

    u8_t get_family() { return family; }
    u8_t get_model() { return model; }
    u8_t get_stepping() { return stepping; }
    u8_t get_brand_id() { return brand_id; }
    u8_t get_cflush_size() { return cflush_size; }
    u8_t get_apic_id() { return apic_id; }
    
    u32_t get_std_features() { return std_features; }
    u32_t get_amd_features() { return amd_features; }
    u32_t get_apm_features() { return apm_features; }

    amd64_tlb_info_t get_l1_tlb() { return l1_tlb; }
    amd64_cache_info_t get_l1_cache() { return l1_cache; }
    
    amd64_tlb_info_t get_l2_tlb() { return l2_tlb; } 
    amd64_cache_info_t get_l2_cache() { return l2_cache; }

    bool l2_2m_tlb_is_unified() { return l2_2m_tlb_unified; }
    bool l2_4k_tlb_is_unified() { return l2_4k_tlb_unified; }
    bool l2_cache_is_unified() { return l2_cache_unified; }
    
    u8_t get_paddr_bits() { return paddr_bits; }
    u8_t get_vaddr_bits() { return vaddr_bits; }

    static bool has_cpuid();
    static void cpuid(word_t fn_idx, 
		      u32_t *eax, u32_t *ebx, u32_t *ecx, u32_t *edx);
};

INLINE bool amd64_cpu_features_t::has_cpuid(){
    u32_t prev, now;
    __asm__(
	"pushf\n\t"
	"pop %%eax\n\t"
	"mov %%eax, %%ebx\n\t"
	"xor $((1<<21)), %%eax\n\t"
	"push %%eax\n\t"
	"popf\n\t" 
	"pushf\n\t"
	"pop %%eax\n\t"
	"xor %%ebx, %%eax\n\t"
	: "=a" (now), "=b" (prev)
	);
    return (prev != now);
}

INLINE void amd64_cpu_features_t::cpuid(word_t fn_idx,
		       u32_t *eax, u32_t *ebx, u32_t *ecx, u32_t *edx )
{
    __asm__ (
	"cpuid"
	: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
	: "a" (fn_idx)
	);
}

/* from init.cc */
extern amd64_cpu_features_t boot_cpu_ft;
#endif /* !__ARCH__AMD64__CPUID_H__ */

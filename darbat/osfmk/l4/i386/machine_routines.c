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
#include <i386/machine_routines.h>
#include <i386/io_map_entries.h>
#include <l4/i386/cpuid.h>
#include <i386/fpu.h>
#include <kern/processor.h>
#include <kern/machine.h>
#include <kern/cpu_data.h>
#include <kern/cpu_number.h>
#include <kern/thread.h>
#include <l4/cpu_data.h>
#include <i386/machine_cpu.h>
#include <i386/mp.h>
#include <i386/mp_events.h>
#include <i386/cpu_threads.h>
#include <l4/pmap.h>
#include <i386/misc_protos.h>
#include <mach/vm_param.h>

void
ml_cpu_get_info(ml_cpu_info_t *cpu_infop)
{
	boolean_t	os_supports_sse;
	i386_cpu_info_t *cpuid_infop;

	if (cpu_infop == NULL)
		return;
 
	/*
	 * Are we supporting XMM/SSE/SSE2?
	 * As distinct from whether the cpu has these capabilities.
	 */
    // TGB HACK!!!
	os_supports_sse = 1; //get_cr4() & CR4_XMM;
	if ((cpuid_features() & CPUID_FEATURE_SSE2) && os_supports_sse)
		cpu_infop->vector_unit = 4;
	else if ((cpuid_features() & CPUID_FEATURE_SSE) && os_supports_sse)
		cpu_infop->vector_unit = 3;
	else if (cpuid_features() & CPUID_FEATURE_MMX)
		cpu_infop->vector_unit = 2;
	else
		cpu_infop->vector_unit = 0;

	cpuid_infop  = cpuid_info();

	cpu_infop->cache_line_size = cpuid_infop->cache_linesize; 

	cpu_infop->l1_icache_size = cpuid_infop->cache_size[L1I];
	cpu_infop->l1_dcache_size = cpuid_infop->cache_size[L1D];
  
        if (cpuid_infop->cache_size[L2U] > 0) {
            cpu_infop->l2_settings = 1;
            cpu_infop->l2_cache_size = cpuid_infop->cache_size[L2U];
        } else {
            cpu_infop->l2_settings = 0;
            cpu_infop->l2_cache_size = 0xFFFFFFFF;
        }

        if (cpuid_infop->cache_size[L3U] > 0) {
            cpu_infop->l2_settings = 1;
            cpu_infop->l2_cache_size = cpuid_infop->cache_size[L3U];
        } else {
            cpu_infop->l3_settings = 0;
            cpu_infop->l3_cache_size = 0xFFFFFFFF;
        }
}

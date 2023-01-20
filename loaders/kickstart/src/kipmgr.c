/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  Karlsruhe University
 *                
 * File path:     kipmgr.cc
 * Description:   Manager for Kernel Interface Page/Kernel
 *                Configuration Page.   The KIP manager can handle both
 *                64bit and 32bit KIPs.
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
 * $Id: kipmgr.cc,v 1.15 2004/06/03 13:19:46 skoglund Exp $
 *                
 ********************************************************************/


#include <string.h>
#include <elf/elf.h>
#include <stdio.h>
#include <stdbool.h>
#include <l4/types.h>

#include "lib.h"
#include "kipmgr.h"


#define KCP_OFFSET(field) \
	(((L4_Word_t) (&((L4_KernelConfigurationPage_t *) 0)->field)) / \
	 sizeof (L4_Word_t))

#define SET_KIP(field, value)	set_val (kmgr, KCP_OFFSET (field), value)
#define GET_KIP(field)		get_val (kmgr, KCP_OFFSET (field))

typedef union {
    L4_Word64_t	raw[2];
    struct {
	L4_BITFIELD5(L4_Word64_t,
	    type	:4,
	    t		:4,
	    __padding1	:1,
	    v		:1,
	    low		:64 - 10
	);
	L4_BITFIELD2(L4_Word64_t,
	    __padding2	:10,
	    high	:64 - 10
	);
    } x;
} memdesc_t;

L4_Word32_t foo;

static void
set_val(kip_manager_t *kmgr, L4_Word_t idx, L4_Word64_t value)
{
	if (kmgr->word_size == 4)
		((L4_Word32_t *) (kmgr->kip))[idx] = (L4_Word32_t) (value);
	else if (kmgr->word_size == 8)
		((L4_Word64_t *) (kmgr->kip))[idx] = (L4_Word64_t) (value);
}

static L4_Word64_t
get_val (kip_manager_t *kmgr, L4_Word_t idx)
{
	if (kmgr->word_size == 4)
		return (L4_Word64_t) (((L4_Word32_t *) kmgr->kip)[idx]);
	else if (kmgr->word_size == 8)
		return (L4_Word64_t) (((L4_Word64_t *) kmgr->kip)[idx]);
	return 0;
}

/**
 * Find location of KIP and initialize the KIP manager according to
 * the wordsize.
 *
 * @param start		start address of kernel image
 * @param end		end address of kernel image
 *
 * @returns true if KIP found and init succeeded, false otherwise
 */
bool
find_kip(kip_manager_t *kmgr, L4_Word_t start, L4_Word_t end)
{
	/*
	 * Search for location of KIP.
	 */
	L4_Word64_t meminfo;
	for (L4_Word_t p = start & ~0xFFF; p < end;
	     p += sizeof(((L4_KernelConfigurationPage_t*) p))) {
		if (((L4_KernelConfigurationPage_t*) p)->magic == L4_MAGIC) {
			kmgr->kip = (L4_KernelConfigurationPage_t*) p;

			if (((L4_Word32_t *) p)[1] != 0)
				kmgr->word_size = 4;
			else
				kmgr->word_size = 8;

			meminfo = GET_KIP (MemoryInfo);
			if (kmgr->word_size == 4)
				kmgr->mem_desc_offset = (meminfo >> 16) / 4;
			else
				kmgr->mem_desc_offset = (meminfo >> 32) / 8;
			
			return true;
		}
	}
	
	return false;
}

void
install_sigma0 (kip_manager_t *kmgr, L4_Word_t mod_start, L4_Word_t mod_end,
		L4_Word_t entry)
{
	SET_KIP (sigma0.low, mod_start);
	SET_KIP (sigma0.high, mod_end);
	SET_KIP (sigma0.ip, entry);
	
	//    this->dedicate_memory(mod_start, mod_end,
	//			  L4_BootLoaderSpecificMemoryType, 6);
}

void
install_root_task (kip_manager_t *kmgr, L4_Word_t mod_start, L4_Word_t mod_end,
		   L4_Word_t entry )
{
	SET_KIP (root_server.low, mod_start);
	SET_KIP (root_server.high, mod_end);
	SET_KIP (root_server.ip, entry);
	
	//    this->dedicate_memory(mod_start, mod_end,
	//			  L4_BootLoaderSpecificMemoryType, 7);
}

void
update_kip (kip_manager_t *kmgr, L4_Word_t boot_info)
{
	SET_KIP (BootInfo, boot_info);
	
	L4_Word64_t meminfo = GET_KIP (MemoryInfo);
	if (kmgr->word_size == 4)
		meminfo = (meminfo & ~0xffffUL) + kmgr->mem_desc_cnt;
	else if (kmgr->word_size == 8)
		meminfo = (meminfo & ~0xffffffffULL) + kmgr->mem_desc_cnt;
	
	SET_KIP (MemoryInfo, meminfo);
}

bool 
dedicate_memory (kip_manager_t *kmgr, 
		 L4_Word64_t start, L4_Word64_t end,
		 L4_Word64_t type, L4_Word64_t sub_type)
{
	memdesc_t mdesc;
	mdesc.raw[0] = get_val (kmgr, kmgr->mem_desc_offset + kmgr->mem_desc_cnt*2 + 0);
	mdesc.raw[1] = get_val (kmgr, kmgr->mem_desc_offset + kmgr->mem_desc_cnt*2 + 1);
	
	mdesc.x.type = type;
	mdesc.x.t = sub_type;
	mdesc.x.v = 0;
	mdesc.x.low = start >> 10;
	mdesc.x.high = end >> 10;
	
	set_val (kmgr, kmgr->mem_desc_offset + kmgr->mem_desc_cnt*2 + 0, mdesc.raw[0]);
	set_val (kmgr, kmgr->mem_desc_offset + kmgr->mem_desc_cnt*2 + 1, mdesc.raw[1]);
	kmgr->mem_desc_cnt++;

	return true;
}

/**
 * Returns the size of physical memory as defined by the memory
 * descriptors.
 *
 * @returns physical memory size in bytes
 */
L4_Word64_t
get_phys_mem_max(kip_manager_t *kmgr)
{
    L4_Word64_t max = 0;

    for (L4_Word_t i = 0; i < kmgr->mem_desc_cnt; i++) {
	memdesc_t mdesc;
	L4_Word64_t high;
	mdesc.raw[0] = get_val (kmgr, kmgr->mem_desc_offset + i*2 + 0);
	mdesc.raw[1] = get_val (kmgr, kmgr->mem_desc_offset + i*2 + 1);

	high = (mdesc.x.high << 10) | 0x3ff;
	if (mdesc.x.type == L4_ConventionalMemoryType
	    && mdesc.x.v == 0
	    && high > max) {
	    max = high;
	}
    }

    return max;
}


/**
 * Find the minimal page size supported by architecture/kernel.
 *
 * @returns size of smallest supported page size (in bytes)
 */
L4_Word_t
kip_get_min_pagesize (kip_manager_t *kmgr)
{
	L4_Word_t psmask = get_val (kmgr, 50);
	L4_Word_t min_pgsize = 10;
	
	if (psmask == 0)
		return 0;
	
	// Determine minimum page size
	for (L4_Word_t m = (1UL << min_pgsize);
	     (m & psmask) == 0;
	     m <<= 1, min_pgsize++)
		;
	
	return 1UL << min_pgsize;
}


/**
 * Determines whether a memory region intersects with the memory 
 * allocations defined in the kip's memory descriptors.
 *
 * @param start		The start address of the region.
 * @param size		The size of the region.
 *
 * @returns true if no conflict, otherwise false
 */
bool
kip_is_mem_region_free (kip_manager_t *kmgr, L4_Word_t start, L4_Word_t size)
{
	L4_Word_t i;
	L4_Word_t end = start - 1 + size;
	
	/* Look for conflicts with kdebug, sigma0, sigma1, and the root server. */
	L4_Word_t off = KCP_OFFSET (Kdebug);
	for (i = 0; i < 4; i++) {
		if (is_intersection (start, end,
				     get_val (kmgr, off + i*4 + 2),
				     get_val (kmgr, off + i*4 + 3)))
			return false;
	}
	/* Look for conflicts with memory descriptors. */
	for (i = 0; i < kmgr->mem_desc_cnt; i++) {
		memdesc_t mdesc;
		mdesc.raw[0] = get_val (kmgr, kmgr->mem_desc_offset + i*2 + 0);
		mdesc.raw[1] = get_val (kmgr, kmgr->mem_desc_offset + i*2 + 1);
		if (mdesc.x.type == L4_ConventionalMemoryType
		    || mdesc.x.v == 1)
			continue;
		
		L4_Word64_t low = (mdesc.x.low << 10);
		L4_Word64_t high = (mdesc.x.high << 10) | 0x3ff;
		/*
		  Look for the unfriendly "dedicated" memory descriptor that covers
		 the entire address space.
		*/
		if ((mdesc.x.type == L4_DedicatedMemoryType) &&
		    (low == 0) && ((L4_Word32_t) high == (L4_Word32_t) -1 )) {
			continue;
		}
		if (is_intersection (start, end, low, high))
			return false;
	}
	return true;
}

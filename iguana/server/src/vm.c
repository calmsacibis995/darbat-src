/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2004 National ICT Australia
 * 
 * All rights reserved. 
 * 
 * Developed by: Embedded, Real-time and Operating Systems Program (ERTOS)
 *               National ICT Australia
 *               http://www.ertos.nicta.com.au
 * 
 * Permission is granted by National ICT Australia, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of National ICT Australia, nor the names of its
 *       contributors, may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
 * PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
 * NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
 * WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
 * REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
 * THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
 * ERRORS, WHETHER OR NOT DISCOVERABLE.
 * 
 * TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
 * NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
 * THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
 * LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
 * OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
 * OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
 * OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
 * CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
 * CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
 * CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
 * DAMAGES OR OTHER LIABILITY.
 * 
 * If applicable legislation implies representations, warranties, or
 * conditions, or imposes obligations or liability on National ICT
 * Australia or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of National ICT Australia or the contributor is limited, to
 * the full extent permitted by the applicable legislation, at its
 * option, to:
 * a.  in the case of goods, any one or more of the following:
 * i.  the replacement of the goods or the supply of equivalent goods;
 * ii.  the repair of the goods;
 * iii. the payment of the cost of replacing the goods or of acquiring
 *  equivalent goods;
 * iv.  the payment of the cost of having the goods repaired; or
 * b.  in the case of services:
 * i.  the supplying of the services again; or
 * ii.  the payment of the cost of having the services supplied again.
 * 
 * The construction, validity and performance of this licence is governed
 * by the laws in force in New South Wales, Australia.
 */
/*
 * Description:
 * Generic VM code
 * Authors: Charles Gray, Ben Leslie, Alex Webster
 */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <l4/ipc.h>
#include <l4/space.h>
#include <l4/kdebug.h>
#include <l4e/misc.h>
#include <l4e/sigma0.h>
#include <inttypes.h>
#include <string.h>
#include "ig_util.h"
#include "objtable.h"
#include "pd.h"
#include "quota.h"
#include "thread.h"
#include "vm.h"

#define HEAP_SIZE (64 * 1024 * 1024)
extern void __malloc_init(void *, void *);

struct fpage_alloc pm_alloc;
struct fpage_alloc vm_alloc;

#define VMALLOC_SIZE	(4 * 1024 * 1024)
void
setup_vm(struct l4e_memory_info *meminfo)
{
	int i;
	struct memsection *heap;

	assert(meminfo != NULL);

	/* Remove bootimage objects from free VM */
	for (i = 0; i < meminfo->num_objects; i++)
		if (meminfo->objects[i].flags & IOF_VIRT)
			l4e_remove_virtmem(meminfo, meminfo->objects[i].base,
					meminfo->objects[i].end, BASE_PAGESIZE);

        /* Free up some VM to bootstrap the fpage allocator */
	for (i = 0; i < meminfo->num_vmregions; i++) {
		uintptr_t base = page_round_up(meminfo->vmregions[i].base);
		uintptr_t end = page_round_down(meminfo->vmregions[i].end + 1) - 1;
		if (end - base + 1 >= 2 * BASE_PAGESIZE) {
			fpage_free_internal(&vm_alloc, base, end);
			meminfo->vmregions[i].end = meminfo->vmregions[i].base;
			break;
		}
	}
	assert(i < meminfo->num_regions);

	/* XXX: We need to make sure the first chunk of physmem we free
	 * is at least 2 * BASE_PAGESIZE to bootstrap the slab
	 * allocators for memsections and the fpage lists.  */
	for (i = 0; i < meminfo->num_regions; i++) {
		uintptr_t base = page_round_up(meminfo->regions[i].base);
		uintptr_t end = page_round_down(meminfo->regions[i].end + 1) - 1;
		if (end - base + 1 >= 2 * BASE_PAGESIZE) {
			fpage_free_chunk(&pm_alloc, base, end);
			meminfo->regions[i].end = meminfo->regions[i].base;
			break;
		}
	}
	/* Make sure we found some physmem */
	assert(i < meminfo->num_regions);

	// L4_KDB_Enter("check 86d000");

        /* 
         * We have a "lowmemory" config option which is used in testing
         * to make sure we handle out of memory situations correctly. It
         * is impratical to test them if the kernel has lots of memory
         * available to it, so we basically limit it to 32 pages, which
         * can be exhausted reasonably quickly 
         */
#ifdef CONFIG_LOWMEMORY
        fpage_free_chunk(&pm_alloc, meminfo->regions[0].base, meminfo->regions[0].base + 42 * BASE_PAGESIZE - 1 );
#else
        for(i = 0; i < meminfo->num_regions; i++) {
                /* base and end may not be aligned, but we need them to be aligned. If
                   the area is less than a page then we shouldn't add it to the free list */

#if 0
		printf( "checking meminfo rgn %d, base=0x%x, end=0x%x\n", 
			i, meminfo->regions[i].base,
			meminfo->regions[i].end );
#endif
		/* if we made it empty... */
		if( meminfo->regions[i].base == meminfo->regions[i].end )
			continue;

                uintptr_t base = page_round_up(meminfo->regions[i].base);
                uintptr_t end = page_round_down(meminfo->regions[i].end + 1) - 1;
		if (base >= 0x800000 && end <= 0x3e7a000) {
			printf("not freeing %p %p \n",
				(void *)base, (void *)end);
			continue;
		}

		printf("%s: freeing pm %p - %p\n",
		    __func__, (void *)base, (void *)end);
#if 0
		printf("%s: freeing pm %p - %p (chuck)\n",
		    __func__, (void *)base, 
		    (void *)(page_round_down(meminfo->regions[i].end + 1) - 1));
#endif
                if (base < end) {
                        fpage_free_chunk(&pm_alloc, base, end);
                }
        }
#endif
	fpage_clear_internal(&vm_alloc);

	/* HACK HACK HACK */
	/* Initialise VM allocator */
        for (i = 0; i < meminfo->num_vmregions; i++) {
		/*
		 * Does anyone think that this Ig vm memsect system 
		 * is bloody broken??  Yes, those bloody round downs and ups
		 * are actually required ...  We round up for both,
		 * since anything sticking at the end might potentially be
		 * used XXX CHECK XXX
		 * -gl
	 	 */

		uintptr_t _freebase, _freeend;

		_freebase = page_round_up(meminfo->vmregions[i].base);
		_freeend = page_round_down(meminfo->vmregions[i].end + 1) - 1;

		printf("freeing %p - %p\n", (void *)_freebase, (void *)_freeend);
#if 0
		if (_freebase < _freeend)
			fpage_free_chunk(&vm_alloc, page_round_up(meminfo->vmregions[i].base), page_round_up(meminfo->vmregions[i].end) - 1);
#endif
		if (_freebase < _freeend)
			fpage_free_chunk(&vm_alloc, _freebase, _freeend);
	}

	/* setup the kernel heap */
	heap = pd_create_memsection(&iguana_pd, HEAP_SIZE, 0, MEM_NORMAL | MEM_USER);
	assert(heap != NULL);
	__malloc_init((void *)heap->base, (void *)heap->end);
}

/* Handle a pagefault to a given address */
uintptr_t
vm_pagefault(uintptr_t addr, L4_ThreadId_t tid)
{
	struct memsection *ms = objtable_lookup((void*)addr);

	/* For user backed memsections, we have no way of telling how
	 * big of an area is mapped, so we map as little as possible */
	if (ms->flags & MEM_USER)
		return BASE_PAGESIZE;
	else
		return L4_Size(l4e_biggest_fpage(addr, ms->base, ms->end));
}

int
vm_change_attributes(uintptr_t base, uintptr_t end, uintptr_t attributes)
{
	uintptr_t addr;

	addr = page_round_down(base);

	/* FIXME: use <= end so base == end works.
	 * This means we need to be extra careful about specifying the
	 * last byte, and not the one after! 
	 */
	while (addr < end) {
		L4_Fpage_t fpage = l4e_biggest_fpage(addr, addr, end);

		L4_LoadMR(0, fpage.raw);

		{
#ifndef ARCH_IA32 /* This isn't implemented on IA32 */
			L4_Word_t attrib[4] = { 0, 0, 0, 0 };
			int r;
			
#ifdef ARCH_ARM
			/* FIXME: (benjl) This code is ARM specific */
			/* lookup the address */
			/* Setup fpage */
			attrib[0] = L4_FlushCache; /* We have to flush first */
			/* Memory control object */
			r = L4_MemoryControl(0, attrib);
			if (r != 1) {
				printf("Failed setting attrib: %x %lx %lx %lx %lx %lx\n", addr, 
				       attrib[0], attrib[1], attrib[2], attrib[3], L4_ErrorCode());
				
			}
			assert(r == 1);
#endif /* ARCH_ARM */
			attrib[0] = attributes;
			r = L4_MemoryControl(0, attrib);

			if (r != 1) {
				return L4_ErrorCode();;
			}
#endif
		}
		addr += L4_Size(fpage);
	}
	return 0;
}

int
vm_back_mem(uintptr_t base, uintptr_t end)
{
	struct memsection *ms = objtable_lookup((void*)base);
	struct memsection *backed;

	assert(ms && (ms->flags & MEM_USER));

	while (base < end) {
		backed = pd_create_memsection(&iguana_pd, BASE_PAGESIZE, 0, MEM_NORMAL);
		if (backed == NULL) {
			/* FIXME: clean up the partially backed region */
			return -1;
		}
		memsection_page_map(ms, L4_Fpage(backed->base, BASE_PAGESIZE), L4_Fpage(base, BASE_PAGESIZE));
		base += BASE_PAGESIZE;
	}
	return 0;
}

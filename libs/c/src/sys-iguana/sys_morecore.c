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
#include "../k_r_malloc.h"
#include <stdio.h>
#include <stdint.h>
#include <iguana/cap.h>
#include <iguana/memsection.h>
#include <iguana/types.h>
#include <l4e/misc.h>

extern void free(void*);
extern Header  *_kr_malloc_freep;
#ifdef THREAD_SAFE
#include <mutex/mutex.h>
#include <l4/thread.h>
extern struct kenge_mutex malloc_mutex;
#endif /*THREAD_SAFE*/

uintptr_t __malloc_bss = 0x20000000;
uintptr_t __malloc_top = 0x30000000;
static struct cap_slot __malloc_slot; 

void
__malloc_init(void *bss_p, void *top_p)
{
	__malloc_bss = (uintptr_t) bss_p;
	__malloc_top = (uintptr_t) top_p;

#ifdef THREAD_SAFE
	malloc_mutex.holder = 0;
	malloc_mutex.needed = 0;
	malloc_mutex.count = 0;
#endif /* THREAD_SAFE */
}

static void
__malloc_slot_init(void)
{
	uintptr_t ignore;
	__malloc_slot = lookup_clist(memsection_lookup(__malloc_bss, &ignore));
	__malloc_slot.pos++;
}

#define round_up(address, size) ((((address) + ((size)-1)) & (~((size)-1))))

/*
 * sbrk equiv
 */
Header  *
morecore(unsigned nu)
{
	uintptr_t cp;
	Header *up;
	cp = __malloc_bss;
	memsection_ref_t heap;
	uintptr_t heap_base, phys_base, ignore;
	cap_t cap = INVALID_CAP;
	uintptr_t nb, mapped;

	nb = round_up(nu * sizeof(Header), NALLOC);
	if (__malloc_bss + nb > __malloc_top)
		return NULL;
	heap = memsection_lookup(__malloc_bss, &ignore);
	heap_base = (uintptr_t)memsection_base(heap);
	if (heap_base != __malloc_bss) {
		cap = _cap_memsection_create(nb, &phys_base);
		if (!IS_VALID_CAP(cap))
			return NULL;
		if (__malloc_slot.list == NULL)
			__malloc_slot_init();
		/* insert the cap so that we can page_map */
		iguana_cap_set(cap, __malloc_slot);
		for (mapped = 0; mapped < nb; mapped += l4e_min_pagesize())
			memsection_page_map(heap, 
					L4_Fpage(phys_base + mapped, l4e_min_pagesize()), 
					L4_Fpage(__malloc_bss + mapped, l4e_min_pagesize()));
	}
	__malloc_bss += nb;
	up = (Header *) cp;
	up->s.size = nb / sizeof(Header);
	free((void *) (up + 1));
	if (IS_VALID_CAP(cap)) {
		/* now we really insert the cap into our clists */
		struct cap_slot slot = iguana_cap_get_slot();
		if (slot.list == NULL)
			return NULL;
		iguana_cap_set(cap, slot);
	}
	return _kr_malloc_freep;
}

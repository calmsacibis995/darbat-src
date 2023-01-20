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
  Authors: Ben Leslie, Alex Webster
  Created: Tue Jul  6 2004 
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <l4/space.h>
#include <l4e/misc.h>
#include <l4e/sigma0.h>
#include "ig_util.h"
#include "memsection.h"
#include "objtable.h"
#include "pd.h"
#include "vm.h"

struct memsection_list internal_memsections = 
{ (void *)&internal_memsections, (void *)&internal_memsections };

static struct slab_cache ms_cache =
SLAB_CACHE_INITIALIZER(sizeof(struct memsection_node), &ms_cache);

struct memsection_node *
memsection_new(void)
{
	struct memsection_node *node;

	node = slab_cache_alloc(&ms_cache);
	if (node == NULL)
		return NULL;
	memset(node, 0, sizeof(struct memsection_node));
	node->data.magic = MEMSECTION_MAGIC;
	return node;
}

void memsection_delete(struct memsection * memsect)
{
	assert(memsect);
 	struct memsection_node *node;

 	node = (struct memsection_node *)((long) memsect - 2*sizeof(void *));

	/* Nobody should be freeing iguana's internal memsections */
	assert((memsect->flags & MEM_INTERNAL) == 0);

	if (memsect->flags & (MEM_USER | MEM_UTCB)) {
		memsection_flush(memsect);
		fpage_free_chunk(&vm_alloc, memsect->base, memsect->end);
	} else if (memsect->flags & MEM_DIRECT) {
		memsection_flush(memsect);
		fpage_free_chunk(&pm_alloc, memsect->phys.base, memsect->phys.base + (memsect->end - memsect->base));
	} else {
		memsection_flush(memsect);
		fpage_free_list(&pm_alloc, memsect->phys.list);
		fpage_free_chunk(&vm_alloc, memsect->base, memsect->end);
	}
 	objtable_delete(memsect);

 	/* manually delete it from memsection_list*/
 	node->next->prev = node->prev;
 	node->prev->next = node->next;
 	
 	//free memsect data structure.
	slab_cache_free(&ms_cache, node);
}

/*this should only be called when objtable_add() fails*/ 
void delete_memsection_from_allocator(struct memsection_node *node)
{
 	assert(node);
	slab_cache_free(&ms_cache, node);
}

int
memsection_set_attributes(struct memsection * memsect, uintptr_t attributes)
{
	int ret;
	/* Try to change the attributes */
	ret = vm_change_attributes(memsect->base, memsect->end, attributes);
	if (ret != 0) {
		int r2;
		/* It failed, so the old one should still be valid */
		r2 = vm_change_attributes(memsect->base, memsect->end, memsect->memory_attributes);
		assert(r2 == 0);
		return ret;
	}
	/* This succeded so e update the current attributes */
	memsect->memory_attributes = attributes;
	return ret;
}


void
memsection_print(struct memsection *self)
{
	DEBUG_PRINT("Memsection: %p\n", self);
	if (self == NULL) {
		return;
	}
	DEBUG_PRINT(" Owner:  %p\n", self->owner);
	DEBUG_PRINT(" Extent: <%p:%p>\n", (void*)self->base, (void*)self->end);
}

void
memsection_register_server(struct memsection *self, struct thread *server)
{
	assert(self);
	self->server = server;
}

static uintptr_t
memsection_lookup_phys(struct memsection *memsection, uintptr_t addr)
{
	struct fpage_list *node;
	uintptr_t virt;

	virt = memsection->base;

	TAILQ_FOREACH(node, &memsection->phys.list, flist) {
		MEMSECTION_PRINT("current: a=%p, v=%p, s=%p\n", (void *)addr, (void *)virt, (void *)L4_Size(node->fpage));
		if (addr >= virt && addr < virt + L4_Size(node->fpage))
			break;
		virt += L4_Size(node->fpage);
	}

	MEMSECTION_PRINT("%p, %p, %p\n", (void *)L4_Address(node->fpage), (void *)addr, (void *)virt);
	return L4_Address(node->fpage) + (addr - virt);
}

int
memsection_page_map(struct memsection *self, L4_Fpage_t from_page, L4_Fpage_t to_page)
{
	uintptr_t from_base, from_end, to_base, to_end;
	uintptr_t offset, phys, size;
	struct memsection *src;

	MEMSECTION_PRINT("page_map(<%p:%p>, <%p:%p>)\n", (void *)L4_Address(from_page), 
			(void *)(L4_Address(from_page) + L4_Size(from_page) - 1), 
			(void *)L4_Address(to_page), 
			(void *)(L4_Address(to_page) + L4_Size(to_page) - 1));

	if (!(self->flags & MEM_USER))
		return -1;
	if (L4_Size(from_page) != L4_Size(to_page))
		return -1;
	
	MEMSECTION_PRINT("seems ok...\n");

	from_base = L4_Address(from_page);
	from_end = from_base + L4_Size(from_page) - 1;
	to_base = L4_Address(to_page);
	to_end = to_base + L4_Size(to_page) - 1;

	src = objtable_lookup((void *) from_base);

	if (!src || src->flags & MEM_USER) /* can't map from user-paged ms */
		return -1;
	if (src->flags & MEM_INTERNAL)
		return -1;
	if (to_base < self->base || to_end > self->end)
		return -1;

	size = from_end - from_base + 1;
	/* XXX: we map 4k fpages even when bigger mappings are possible */
	for (offset = 0; offset < size; offset += BASE_PAGESIZE) {
		phys = memsection_lookup_phys(src, from_base + offset);
		MEMSECTION_PRINT("map(%p, %p, 0x1000)\n", (void *)(to_base + offset), (void *)phys);
		l4e_sigma0_map(to_base + offset, phys, BASE_PAGESIZE);
	}

	MEMSECTION_PRINT("done...\n");
	return 0;
}

int
memsection_page_unmap(struct memsection *self, L4_Fpage_t to_page)
{
	uintptr_t to_base, to_end;

	if (!(self->flags & MEM_USER))
		return -1;

	to_base = L4_Address(to_page);
	to_end = to_base + L4_Size(to_page);

	if (to_base < self->base || to_end > self->end)
		return -1;

	L4_Flush(to_page);
	return 0;
}

int
memsection_check_state(struct memsection *self)
{
	return !is_memsection(self);
}


void
memsection_flush(struct memsection *memsection)
{
	uintptr_t addr = memsection->base;
	L4_Fpage_t fpage;

	while (addr < memsection->end) {
		fpage = l4e_biggest_fpage(addr, addr, memsection->end);
		L4_Set_Rights(&fpage, L4_FullyAccessible);
		L4_UnmapFpage(fpage);
		addr += L4_Size(fpage);
	}
}

/* Make sure a memsection is backed in iguana's address space */
int
memsection_back(struct memsection *memsection)
{
	uintptr_t addr = memsection->base;
	uintptr_t size = memsection->end - memsection->base + 1;
	uintptr_t flags = memsection->flags;

	if (flags & (MEM_USER | MEM_UTCB)) {
		return -1;
	} else if (flags & (MEM_INTERNAL | MEM_DIRECT)) {
		/* Map it 1:1 */
		l4e_sigma0_map(addr, memsection->phys.base, size);
		return 0;
	} else {
		struct fpage_list *node;
		L4_Fpage_t vpage;

		/* Iterate thru fpage list */
		TAILQ_FOREACH(node, &memsection->phys.list, flist) {
			vpage = L4_Fpage(addr, L4_Size(node->fpage));
			l4e_sigma0_map_fpage(vpage, node->fpage);
			memset((void *)addr, 0, L4_Size(vpage));
			addr += L4_Size(vpage);
		}
		return 0;
	}
}

/* Create a memsection for use by the internal slab allocator */
struct memsection *
memsection_create_cache(struct slab_cache *sc)
{
	struct memsection_node *node;
	struct memsection_list *list;
	struct memsection *ms;
	uintptr_t phys, virt;

	MEMSECTION_PRINT("%p\n", sc);

	virt = fpage_alloc_internal(&vm_alloc, BASE_PAGESIZE);
	if (virt == -1)
		return NULL;

	MEMSECTION_PRINT("virt = %p\n", (void *)virt);
	phys = fpage_alloc_internal(&pm_alloc, BASE_PAGESIZE);
	if (phys == -1) {
		fpage_free_internal(&vm_alloc, virt, virt + BASE_PAGESIZE - 1);
		return NULL;
	}

	MEMSECTION_PRINT("phys = %p\n", (void *)phys);

	/* We can't rely on someone else to map it for us :( */
	l4e_sigma0_map(virt, phys, BASE_PAGESIZE);
	memset((void *)virt, 0, BASE_PAGESIZE);

	if (sc == &ms_cache) {
		/* XXX: If this will be used to back memsections, put
		 * the new memsection into the pool itself. */
		node = (void *)virt;
		ms = &(node->data);
		ms->base = virt;
		virt += sizeof(struct memsection_node);
	} else {
		node = slab_cache_alloc(&ms_cache);
		if (node == NULL) {
			L4_Flush(L4_Fpage(virt, BASE_PAGESIZE));
			fpage_free_chunk(&vm_alloc, virt, virt + BASE_PAGESIZE - 1);
			fpage_free_chunk(&pm_alloc, phys, phys + BASE_PAGESIZE - 1);
			return NULL;
		}
		assert(node != NULL);
		ms = &(node->data);
		ms->base = virt;
	}
	ms->end = ms->base + BASE_PAGESIZE - 1;
	ms->flags = 0;
	ms->slab_cache = sc;
	ms->phys_active = true;
	ms->phys.base = phys;

	/* XXX: Insert into internal memsections until it is safe to go
	 * into the regular list and the objtable */
	list = &internal_memsections;
	node->next = (void *)list;
	list->last->next = node;
	node->prev = list->last;
	list->last = node;

	/* Append the new pool to the list of pools in the allocator */
	TAILQ_INIT(&ms->slabs);
	for (; virt + sc->slab_size - 1 <= ms->end; virt += sc->slab_size)
		TAILQ_INSERT_TAIL(&ms->slabs, (struct slab *)virt, slabs);
	ms->slab_cache = sc;
	TAILQ_INSERT_TAIL(&sc->pools, ms, pools);

	return ms;
}

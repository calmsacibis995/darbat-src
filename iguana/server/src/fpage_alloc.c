/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2005 National ICT Australia
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
  Author: Alex Webster <Alex.Webster@nicta.com.au>
*/

#include <assert.h>
#include <l4/types.h>
#include <l4e/misc.h>
#include "fpage_alloc.h"
#include "slab_cache.h"
#include "ig_util.h"
#include "vm.h"

static struct slab_cache fp_cache =
SLAB_CACHE_INITIALIZER(sizeof(struct fpage_list), &fp_cache);

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

static inline L4_Fpage_t
buddy(L4_Fpage_t fpage)
{
	return L4_Fpage(L4_Address(fpage) ^ L4_Size(fpage), L4_Size(fpage));
}

static int
sz_order(size_t size)
{
	int order = 0;

	while ((1 << (order + MIN_FPAGE_BITS)) < size)
		order++;
	return order;
}

static inline uintptr_t
fp_end(L4_Fpage_t fpage)
{
	return L4_Address(fpage) + L4_Size(fpage) - 1;
}

static inline int
fp_order(L4_Fpage_t fpage)
{
	return L4_SizeLog2(fpage) - MIN_FPAGE_BITS;
}

/* 
 * Allocate an fpage of exactly the requested size if possible,
 * otherwise allocate the biggest available fpage. 
 */
L4_Fpage_t
fpage_alloc(struct fpage_alloc *alloc, size_t size)
{
	int i, order = sz_order(size);
	struct fpage_list *node;
	L4_Fpage_t fpage;

	FPAGE_PRINT("fpage_alloc(%p, 0x%zx)\n", alloc, size);

	/* Look for something >= to request size */
	for (i = order; i < MAX_FPAGE_ORDER; i++)
		if (!TAILQ_EMPTY(&alloc->flist[i]))
			break;
	/* Otherwise try to find something */
	while (i >= 0 && TAILQ_EMPTY(&alloc->flist[i]))
		i--;
	/* Make sure we have something left */
	if (i < 0)
		return L4_Nilpage;

	node = TAILQ_FIRST(&alloc->flist[i]);
	fpage = node->fpage;
	TAILQ_REMOVE(&alloc->flist[i], node, flist);
	slab_cache_free(&fp_cache, node);
	/* Free up any excess */
	while (fp_order(fpage) > order) {
		fpage = L4_FpageLog2(L4_Address(fpage), L4_SizeLog2(fpage) - 1);
		node = slab_cache_alloc(&fp_cache);
		if (node == NULL) {
			/* return > request size */
			return L4_FpageLog2(L4_Address(fpage), L4_SizeLog2(fpage) + 1);
		}
		assert(node != NULL);
		node->fpage = buddy(fpage);
		TAILQ_INSERT_TAIL(&alloc->flist[fp_order(fpage)], node, flist);
	}
	return fpage;
}

/* 
 * Allocate a chunk of memory.  At the moment, this memory will be
 * aligned to the next biggest fpage boundary.
 */
uintptr_t
fpage_alloc_chunk(struct fpage_alloc *alloc, size_t size)
{
	L4_Fpage_t fpage;
	
	FPAGE_PRINT("fpage_alloc_chunk(%p, 0x%zx)\n", alloc, size);
	fpage= fpage_alloc(alloc, size);
	if (L4_IsNilFpage(fpage))
		return INVALID_ADDR;
	/* We return at least as much as requested... unlike fpage_alloc()*/
	if (L4_Size(fpage) < size) {
		fpage_free_chunk(alloc, L4_Address(fpage), fp_end(fpage));
		return INVALID_ADDR;
	}

	/* trim the fpage */
	if (L4_Size(fpage) > size)
		fpage_free_chunk(alloc, L4_Address(fpage) + size, fp_end(fpage));
	return L4_Address(fpage_alloc(alloc, size));
}

/* 
 * Allocate a chunk of memory *without* allocating any fpagelist nodes.
 */
uintptr_t
fpage_alloc_internal(struct fpage_alloc *alloc, size_t size)
{
	struct fpage_list *node;
	uintptr_t mem;
	int i;

	FPAGE_PRINT("fpage_alloc_internal(%p, 0x%zx)\n", alloc, size);
	if (alloc->internal.active == false) {
		for (i = 0; TAILQ_EMPTY(&alloc->flist[i]); i++)
			;
		if (i > MAX_FPAGE_ORDER) {
			FPAGE_PRINT("out of memory\n");
			return -1;
		}
		node = TAILQ_FIRST(&alloc->flist[i]);
		alloc->internal.base = L4_Address(node->fpage);
		alloc->internal.end = fp_end(node->fpage);
		alloc->internal.active = true;
		TAILQ_REMOVE(&alloc->flist[i], node, flist);
		slab_cache_free(&fp_cache, node);
	}
	if (alloc->internal.end - alloc->internal.base + 1 < size) {
		FPAGE_PRINT("has not enough memory\n");
		return INVALID_ADDR;
	}
	mem = alloc->internal.base;
	alloc->internal.base += size;
	if (alloc->internal.base >= alloc->internal.end)
		alloc->internal.active = false;
	return mem;
}

void
fpage_free_chunk(struct fpage_alloc *alloc, uintptr_t base, uintptr_t end)
{
	FPAGE_PRINT("fpage_free_chunk(%p, %p, %p)\n", alloc, (void *)base, (void *)end);
	if (alloc->internal.active)
		fpage_clear_internal(alloc);
	fpage_free_internal(alloc, base, end);
	fpage_clear_internal(alloc);
	FPAGE_PRINT("...\n");
}

void
fpage_free_internal(struct fpage_alloc *alloc, uintptr_t base, uintptr_t end)
{
	FPAGE_PRINT("fpage_free_internal(%p, %p, %p)\n", alloc, (void *)base, (void *)end);
	if (alloc->internal.active)
		fpage_clear_internal(alloc);
	alloc->internal.base = base;
	alloc->internal.end = end;
	alloc->internal.active = true;
}

void
fpage_clear_internal(struct fpage_alloc *alloc)
{
	struct fpage_list *fpage;

	if (alloc->internal.active) {
		while (alloc->internal.base < alloc->internal.end) {
			fpage = slab_cache_alloc(&fp_cache);
			if (fpage == NULL) {
				/* Uh-oh */
				return;
			}
			fpage->fpage = l4e_biggest_fpage(alloc->internal.base, alloc->internal.base, alloc->internal.end);
			TAILQ_INSERT_TAIL(&alloc->flist[fp_order(fpage->fpage)], fpage, flist);
			alloc->internal.base += L4_Size(fpage->fpage);
		}
		alloc->internal.active = false;
	}
}

/*
 * This function is used to back memsections, it will try to allocate
 * the largest fpages it can to back [base, end].
 */
struct flist_head
fpage_alloc_list(struct fpage_alloc *alloc, uintptr_t base, uintptr_t end)
{
	struct flist_head list = TAILQ_HEAD_INITIALIZER(list);
	struct fpage_list *node;
	L4_Fpage_t fpage;

	FPAGE_PRINT("fpage_alloc_list(%p, %p, %p)\n", alloc, (void *)base, (void *)end);

	while (base < end) {
		fpage = fpage_alloc(alloc, L4_Size(l4e_biggest_fpage(base, base, end)));
		if (L4_IsNilFpage(fpage))
			goto out_of_memory;
		node = slab_cache_alloc(&fp_cache);
		if (node == NULL)
			goto out_of_memory;
		node->fpage = fpage;
		TAILQ_INSERT_TAIL(&list, node, flist);
		base += L4_Size(fpage);
	}
	FPAGE_PRINT("done\n");
	return list;
out_of_memory:
	while (!TAILQ_EMPTY(&list)) {
		node = TAILQ_FIRST(&list);
		TAILQ_REMOVE(&list, node, flist);
		fpage_free_chunk(alloc, L4_Address(node->fpage), fp_end(node->fpage));
		slab_cache_free(&fp_cache, node);
	}
	return list;
}

void
fpage_free_list(struct fpage_alloc *alloc, struct flist_head list)
{
	struct fpage_list *node, *tmp;

	for (node = TAILQ_FIRST(&list); node != NULL ; node = tmp) {
		tmp = TAILQ_NEXT(node, flist);
		fpage_free_chunk(alloc, L4_Address(node->fpage), fp_end(node->fpage));
		TAILQ_REMOVE(&list, node, flist);
		slab_cache_free(&fp_cache, node);
	}
}

/*
 * Free any memory in the fpage not in [base, end].
 */
static void
fpage_free_extra(struct fpage_alloc *alloc, L4_Fpage_t fpage, uintptr_t base, uintptr_t end)
{
	if (L4_Address(fpage) < base)
		fpage_free_chunk(alloc, L4_Address(fpage), base - 1);
	if (L4_Address(fpage) + L4_Size(fpage) - 1 > end)
		fpage_free_chunk(alloc, end + 1, fp_end(fpage));
}

/*
 * Basically allocate a specific chunk of memory (for creating fixed
 * memsections).  Doesn't check if all the memory was free -- we rely on
 * the objtable to check that.
 */
void
fpage_remove_chunk(struct fpage_alloc *alloc, uintptr_t base, uintptr_t end)
{
	int i;
	L4_Fpage_t fpage;
	uintptr_t fbase, fend;
	struct fpage_list *node, *tmp;

	FPAGE_PRINT("fpage_remove_chunk(_, %p, %p)\n", (void *)base, (void *)end);
	for (i = 0; i <= MAX_FPAGE_ORDER; i++) {
		node = TAILQ_FIRST(&alloc->flist[i]);
		for (; node != NULL; node = tmp) {
			tmp = TAILQ_NEXT(node, flist);
			fbase = L4_Address(node->fpage);
			fend = fbase + L4_Size(node->fpage) - 1;
			if (max(base, fbase) < min(end, fend)) {
				/* remove from list , then trim and free
				 * any excess memory in the fpage.  */
				fpage = node->fpage;
				TAILQ_REMOVE(&alloc->flist[i], node, flist);
				slab_cache_free(&fp_cache, node);
				fpage_free_extra(alloc, fpage, base, end);
			}
		}
	}
}

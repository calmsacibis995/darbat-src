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
 * Authors: Ben Leslie, Alex Webster
 */
#include <assert.h>
#include "memsection.h"
#include "objtable.h"
#include "pd.h"
#include "vm.h"
#include <inttypes.h>

#include "obj_btree.h"
#include <b_plus_tree.h>

#include <stdlib.h>

#include <stdio.h>
#include <inttypes.h>

#include "slab_cache.h"
 
#include "ig_util.h"

#include <l4e/sigma0.h>
#include <string.h>

static BTree _objtable;
static GBTree objtable;

static struct slab_cache bt_cache =
SLAB_CACHE_INITIALIZER(sizeof(struct sBTPage), &bt_cache);

/* FIXME: How should we really be dealing with the btree? */
void
ObjFreePage(PagePool *pool, struct sBTPage *page)
{
	slab_cache_free(&bt_cache, page);
}

struct sBTPage *
ObjAllocPage(PagePool *pool)
{
	/* XXX: this might fail... */
	return slab_cache_alloc(&bt_cache);
}

static int
insert(struct memsection *memsection)
{
	struct memsection *ignored;
	int ret;

	ret = ObjBTIns(objtable, memsection, &ignored);
	if (ret != BT_FOUND)
		return -1;
	return 0;
}

static int
delete(struct memsection *memsection)
{
	struct memsection *ignored;
	int ret;
	
	ret = ObjBTDel(objtable, memsection->base, &ignored);
	if (ret != BT_OK) 
		return -1;
	return 0;
}

int
objtable_insert(struct memsection *memsection)
{
	int r = 0;

	/* check the objtable is set up */
	if (iguana_pd_inited)
		r = insert(memsection);
	return r;
}

int
objtable_setup(struct memsection *ms, uintptr_t size, int flags)
{
	int r;

	assert(flags & MEM_NORMAL);
	ms->flags = flags;
	ms->base = fpage_alloc_chunk(&vm_alloc, size);
	if (ms->base == INVALID_ADDR)
		return -1;
	ms->end = ms->base + size - 1;

	/* Check if we need to back the memsection */
	if (!(flags & MEM_USER)) {
		ms->phys.list = fpage_alloc_list(&pm_alloc, ms->base, ms->end);
		if (TAILQ_EMPTY(&ms->phys.list)) {
			fpage_free_chunk(&vm_alloc, ms->base, ms->end);
			return -1;
		}
		memsection_back(ms);
	}

	r = objtable_insert(ms);
	if (r != 0) {
		fpage_free_chunk(&vm_alloc, ms->base, ms->end);
		fpage_free_list(&pm_alloc, ms->phys.list);
	}
	return r;
}

int
objtable_setup_fixed(struct memsection *ms, uintptr_t size, uintptr_t base, int flags)
{
	int r;

	assert(flags & MEM_FIXED);
	ms->flags = flags;
	ms->base = base;
	ms->end = base + size - 1;
	r = objtable_insert(ms);
	if (r != 0)
		return r;

	fpage_remove_chunk(&vm_alloc, base, base + size - 1);
	/* Check if we need to back the memsection */
	if (!(flags & MEM_USER)) {
		ms->phys.list = fpage_alloc_list(&pm_alloc, ms->base, ms->end);
		if (TAILQ_EMPTY(&ms->phys.list)) {
			fpage_free_chunk(&vm_alloc, ms->base, ms->end);
			return -1;
		}
		memsection_back(ms); 
	}
	return r;
}

int
objtable_setup_utcb(struct memsection *ms, uintptr_t size, int flags)
{
	int r = -1;

	assert(flags & MEM_UTCB);
	ms->flags = flags;
	ms->base = fpage_alloc_chunk(&vm_alloc, size);
	if (ms->base == INVALID_ADDR)
		return -1;
	ms->end = ms->base + size - 1;
	r = objtable_insert(ms);
	if (r != 0)
		fpage_free_chunk(&vm_alloc, ms->base, ms->end);
	return r;
}

int
objtable_setup_internal(struct memsection *ms, uintptr_t size, uintptr_t base, int flags)
{
	int r = -1;

	assert(flags & MEM_INTERNAL);
	ms->flags = flags;
	ms->base = base;
	ms->end = base + size - 1;
	ms->phys.base = base;
	r = objtable_insert(ms);
	if (r == 0)
		memsection_back(ms);
	return r;
}

int
objtable_setup_direct(struct memsection *ms, uintptr_t size, int flags)
{
	int r = -1;

	assert(flags & MEM_DIRECT);
	ms->flags = flags;
	/* allocate some phys which we will map 1:1 to virt */
	ms->base = fpage_alloc_chunk(&pm_alloc, size);
	if (ms->base == INVALID_ADDR)
		return -1;
	ms->end = ms->base + size - 1;
	ms->phys.base = ms->base;
	r = objtable_insert(ms);
	if (r != 0) {
		fpage_free_chunk(&pm_alloc, ms->base, ms->end);
		return r;
	}
	memsection_back(ms);
	return r;
}

int
objtable_delete(struct memsection *memsection)
{
	int r;
	
	//delete entry in objtable.
	r = delete(memsection);
	if (r != 0) 
	{
		ERROR_PRINT("Failed delete object, <%" PRIxPTR ":%" PRIxPTR "> shouldn't happen\n",
		       memsection->base, memsection->end);
		objtable_print();
	}
	assert(r == 0);
	return 0;
}

/* Initialisation */
void
objtable_init(void)
{
	/* alloc btree information */
	objtable = &_objtable;
	objtable->root = NULL;
	objtable->pool = NULL; /* We only have one pool -- the sas */
}

struct memsection *
objtable_lookup(void *addr)
{
	struct memsection *memsection;
	int r;
	r = ObjBTSearch(objtable, (uintptr_t) addr, &memsection);

	if (r == BT_NOT_FOUND || r == BT_INVALID) {
		/* XXX: for bootstrapping */
		struct memsection_node *ms, *first_ms = internal_memsections.first;
		for (ms = first_ms; ms->next != first_ms; ms = ms->next) {
			if ((uintptr_t)addr >= ms->data.base && (uintptr_t)addr <= ms->data.end)
				return &ms->data;
		}
		return NULL;
	}

	return memsection;
}

extern void BTPrint(GBTree const btree);

void
objtable_print(void)
{
	DEBUG_PRINT("Objtable:\n");
	BTPrint(objtable);
}

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
 Author: Ben Leslie
*/
#include <assert.h>
#include <iguana/types.h>
#include <iguana/cap.h>
#include <iguana/memsection.h>
#include <iguana/pd.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <interfaces/iguana_client.h>
#include <mutex/mutex.h>
#include <ll.h>

struct clist {
	int slot;
	size_t size;
	size_t cap_free;
	memsection_ref_t clist_memsect;
	cap_t *cap_list;
};

struct clist_list {
	struct clist_node *first;
	struct clist_node *last;
};
struct clist_node {
	struct clist_node *next;
	struct clist_node *prev;
	struct clist data;
};
static inline struct clist * clist_list_create_front(struct clist_list* list)
{
	return (struct clist *) dl_list_create_front((struct double_list *) list, sizeof(struct clist));
}
static inline struct clist * clist_list_create_back(struct clist_list* list)
{
	return (struct clist *) dl_list_create_back((struct double_list *) list, sizeof(struct clist));
}
static inline void clist_list_delete(struct clist * data)
{
	ll_delete((struct ll *) ((void**) data - 2));
}
static inline void clist_list_init(struct clist_list *list)
{
	dl_list_init((struct double_list *) list);
}
static inline void clist_list_clear(struct clist_list * list)
{
	dl_list_clear((struct double_list *) list);
}


/* FIXME: This is a hack to get Linux running for the moment */
cap_t *first_cap = NULL;

static struct clist_list clist_list;
static bool locked;

struct kenge_mutex cap_mutex;

#define mutex_lock kenge_mutex_lock
#define mutex_unlock kenge_mutex_unlock

void 
__cap_init(uintptr_t cap_slot, uintptr_t cap_used, uintptr_t cap_size, uintptr_t cap_addr)
{
	struct clist *clist;
	if (cap_addr == -1) {
		/* clist totally locked */
		locked = true;
		return;
	}

	/* Initialise the mutex */
	cap_mutex.holder = 0;
	cap_mutex.needed = 0;
	cap_mutex.count = 0;
	
	first_cap = (cap_t *) cap_addr;
	clist_list_init(&clist_list);

	clist = clist_list_create_back(&clist_list);
	clist->slot = cap_slot;
	clist->cap_list = (cap_t*) cap_addr;
	clist->cap_free = cap_used + 1;
	clist->size = cap_size;
}

/* This function assumes the caller has already aquired the cap_mutex. */
static struct clist *
create_new_clist(struct cap_slot slot)
{
	cap_t new_clist;
	struct clist *clist;
	uintptr_t cap_addr;
	size_t cap_size = clist_list.last->data.size;

	clist = clist_list_create_back(&clist_list);

	if (clist == NULL) {
		return NULL;
	}
	
	/* This one is full -- create a new clist */
	/* This clist is created to be the same size as the last clist */
	new_clist = _cap_memsection_create(cap_size * sizeof(cap_t), &cap_addr);
	if (new_clist.ref.memsection == 0) {
		/* Out of memory! */
		clist_list_delete(clist);
		return NULL;
	}

	clist->slot = pd_add_clist(pd_myself(), new_clist.ref.memsection); /* Can't fail */

	if (clist->slot == -1) {
		clist_list_delete(clist);
		/* Delete mem section, can't use memsection_delete  */
		iguana_memsection_delete(L4_Pager(), new_clist.ref.memsection, NULL);
		/* */
		return NULL;
	}
	iguana_cap_set(new_clist, slot); /* Can't fail */

	clist->cap_free = 0;
	clist->cap_list = (cap_t*) cap_addr;
	clist->clist_memsect = new_clist.ref.memsection;
	clist->size = cap_size;

	return clist;
}

struct cap_slot
iguana_cap_get_slot(void)
{
	struct cap_slot slot = { .list = NULL, .pos = 0 };

	if (locked)
		return slot;

	mutex_lock(&cap_mutex);
	
	/* Add the capabillity to the current protection domain */
	slot.list = & clist_list.last->data;
	slot.pos = clist_list.last->data.cap_free++;

	if (slot.pos == clist_list.last->data.size - 1) {
		if (create_new_clist(slot)) {
			/* Maximum recursion called here is 1, since on the
			   next call slot.pos != clist_list.last0>data.size */
			mutex_unlock(&cap_mutex);
			return iguana_cap_get_slot();
		} else {
			slot.list = NULL;
			mutex_unlock(&cap_mutex);
			return slot;
		}
	}

	assert(slot.pos != -1);

	mutex_unlock(&cap_mutex);
	return slot;
}

struct cap_slot
lookup_clist(memsection_ref_t memsection)
{
	struct cap_slot slot = { .list = NULL, .pos = 0};
	struct clist_node *node=NULL;
	int i;
	
	mutex_lock(&cap_mutex);
	for (node = clist_list.first;
		node->next != clist_list.first; node = node->next)
	{
		for (i = 0; i<= node->data.size; i++)
			if (node->data.cap_list[i].ref.memsection == memsection)
			{
				slot.list = &(node->data);
				slot.pos = i;
				mutex_unlock(&cap_mutex);
				return slot;
			}
	}
	
	assert(!"lookup_clist: Can't find the memsection in clist");
	
	return slot;
}
	
			
/* called only when allocate memction failed, release the allocated clist*/
void
iguana_cap_free_slot(struct cap_slot slot)
{
	cap_t invalid_cap = INVALID_CAP;

	mutex_lock(&cap_mutex);
	
	slot.list->cap_free--;

	if (slot.pos != slot.list->cap_free) {
		slot.list->cap_list[slot.pos] =  \
			slot.list->cap_list[slot.list->cap_free];
	}

	slot.list->cap_list[slot.list->cap_free] = invalid_cap;

	/* check if slot.pos == 0, release the cap */
	if (slot.pos == slot.list->cap_free && slot.pos == 0) /* delete the last cap in the list, need to release clist as well */
	{
		/* deregister the clist in the pd*/
		pd_release_clist(pd_myself(), 
				 (uintptr_t) slot.list->cap_list, 0);
		/* delete the memsection of the clist array */
		memsection_delete(slot.list->clist_memsect);
		/*delete clist in clist_list */ 
		clist_list_delete(slot.list);
		
	}

	mutex_unlock(&cap_mutex);
}

void
iguana_cap_set(cap_t cap, struct cap_slot slot)
{
	//printf("Putting cap into: %p %d 0x%x 0x%x\n", &slot.list->cap_list[slot.pos], slot.pos, cap.passwd, cap.ref.memsection);
	assert(IS_VALID_CAP(cap));
	mutex_lock(&cap_mutex);
	slot.list->cap_list[slot.pos] = cap;
	mutex_unlock(&cap_mutex);
}

cap_t
iguana_get_cap(uintptr_t ref, unsigned interface)
{
	uintptr_t real_ref = ref + interface;
	int i;
	cap_t cap = INVALID_CAP;
	struct clist *clist;

	mutex_lock(&cap_mutex);
	clist = &clist_list.first->data;
	/* Search for a matching cap */
	/* FIXME: Search all the clists! */
	for(i=0; i < clist->size && clist->cap_list[i].ref.obj != 0; i++) {
		if (clist->cap_list[i].ref.obj == real_ref) {
			cap = clist->cap_list[i];
			break;
		}
	}
	mutex_unlock(&cap_mutex);
	return cap;
}

bool
cap_matches(cap_t cap, objref_t object, int interface)
{
	return (cap.ref.obj == object || cap.ref.obj == object + interface);
}

cap_t *
iguana_get_clist(int slot)
{
	/* FIXME: Only do first */
	/*
	struct clist *clist = &clist_list.first->data;
	return clist->cap_list;
	*/
	cap_t *res;
	mutex_lock(&cap_mutex);
	res = first_cap;
	mutex_unlock(&cap_mutex);
	return res;
}

void cap_clist_list_delete(struct clist *list)
{
	mutex_lock(&cap_mutex);
	clist_list_delete(list);
	mutex_unlock(&cap_mutex);
}

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

#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <l4/thread.h> 
#include <iguana/memsection.h>
#include <iguana/pd.h>
#include <iguana/cap.h>
#include <assert.h>
#include <interfaces/iguana_client.h>


cap_t
_cap_memsection_create(uintptr_t size, uintptr_t *base)
{
	cap_t cap;
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, 0, MEM_NORMAL, base, NULL);
	return cap;
}

memsection_ref_t 
memsection_create(uintptr_t size, uintptr_t *base)
{
	cap_t cap;
	struct cap_slot slot;
	slot = iguana_cap_get_slot();
	if (slot.list == NULL) {
		*base = 0;
		return 0;
	}
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, 0, MEM_NORMAL, base, NULL);
	//printf("created: %x %x\n", cap.ref.memsection, *base);
	if (cap.ref.memsection != 0) {
		assert(IS_VALID_CAP(cap));
		//printf("Setting cap into slot: %p %d %d\n", slot.list, slot.pos, IS_VALID_CAP(cap));
		iguana_cap_set(cap, slot);
	} else {
		iguana_cap_free_slot(slot);
	}
	return cap.ref.memsection;
}

memsection_ref_t 
memsection_create_user(uintptr_t size, uintptr_t *base)
{
	cap_t cap;
	struct cap_slot slot;
	slot = iguana_cap_get_slot();
	if (slot.list == NULL) {
		*base = 0;
		return 0;
	}
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, 0, MEM_NORMAL | MEM_USER, base, NULL);
	if (cap.ref.memsection != 0) {
		iguana_cap_set(cap, slot);
	} else {
		iguana_cap_free_slot(slot);
	}
	return cap.ref.memsection;
}

#ifdef CONFIG_RESTRICTED_VM
/* Create some memory that is mapped 1-1 with physical */
memsection_ref_t 
memsection_create_direct(uintptr_t size, uintptr_t *base)
{
	cap_t cap;
	struct cap_slot slot;
	slot = iguana_cap_get_slot();
	if (slot.list == NULL) {
		*base = 0;
		return 0;
	}
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, 0, MEM_DIRECT, base, NULL);
	if (cap.ref.memsection != 0) {
		iguana_cap_set(cap, slot);
	} else {
		iguana_cap_free_slot(slot);
	}
	return cap.ref.memsection;
}
#endif

/* FIXME: This shouldn't be used and will go away at some stage! */
memsection_ref_t 
memsection_create_fixed(uintptr_t size, uintptr_t base)
{
	cap_t cap;
	struct cap_slot slot;
	uintptr_t ret_base;
	slot = iguana_cap_get_slot();
	if (slot.list == NULL) {
		return 0;
	}
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, base, MEM_FIXED, &ret_base, NULL);
	if (cap.ref.memsection != 0) {
		iguana_cap_set(cap, slot);
	} else {
		iguana_cap_free_slot(slot);
	}
	return cap.ref.memsection;
}

memsection_ref_t 
memsection_create_fixed_user(uintptr_t size, uintptr_t base)
{
	cap_t cap;
	struct cap_slot slot;
	uintptr_t ret_base;
	slot = iguana_cap_get_slot();
	if (slot.list == NULL) {
		return 0;
	}
	cap = iguana_pd_create_memsection(L4_Pager(), pd_myself(), size, base, MEM_FIXED | MEM_USER, &ret_base, NULL);
	if (cap.ref.memsection != 0) {
		iguana_cap_set(cap, slot);
	} else {
		iguana_cap_free_slot(slot);
	}
	return cap.ref.memsection;
}

int
memsection_register_server(memsection_ref_t memsect, thread_ref_t server)
{
	return iguana_memsection_register_server(L4_Pager(), 
						 memsect, server, NULL);
}

memsection_ref_t
memsection_lookup(objref_t object, thread_ref_t *server)
{
	return iguana_memsection_lookup(L4_Pager(), object, 
					server, NULL);
}

struct clist {
	int slot;
	size_t size;
	size_t cap_free;
	memsection_ref_t clist_memsect;
	cap_t *cap_list;
};

void
memsection_delete(memsection_ref_t memsect)
{
	cap_t invalid_cap = INVALID_CAP;
	struct cap_slot slot = { .list = NULL, .pos = 0 };
	/* delete cap that contains this memsection*/
	/* lookup_memsection and get the slot that has the clist and has the cap */

	slot = lookup_clist(memsect);	
	assert(slot.pos < (slot.list->cap_free));
	slot.list->cap_free--;	
	assert(memsect == slot.list->cap_list[slot.pos].ref.memsection);
	/*release the memsection contained in this cap */
	iguana_memsection_delete(L4_Pager(), memsect, NULL); //can't fail	
	
	if (slot.pos != slot.list->cap_free) /* not the last cap */
	{		
		slot.list->cap_list[slot.pos] = \
			slot.list->cap_list[slot.list->cap_free];
	}
	slot.list->cap_list[slot.list->cap_free] = invalid_cap;
	
	if (slot.pos == slot.list->cap_free && slot.pos == 0) /* this is the last cap in the list, need to delete the clist too */
	{
		/* deregister the clist array in the pd */ 
		pd_release_clist(pd_myself(), 
			(uintptr_t) slot.list->cap_list, slot.list->slot);
		/* delete the memsection of the clist array, will only called once, 
		     coz the cap of the clist array is stored in the last slot of prev
		     clist, and slot.pos != 0 */
		memsection_delete(slot.list->clist_memsect);
		/* delete clist struct in clist_list*/
		cap_clist_list_delete(slot.list);
	}			
	
}

void
memsection_set_attributes(memsection_ref_t memsect, uintptr_t attributes)
{
	iguana_memsection_set_attributes(L4_Pager(), memsect, attributes, NULL);
}

void *
memsection_base(memsection_ref_t memsect)
{
	uintptr_t size;
	return (void*) iguana_memsection_info(L4_Pager(), memsect, &size, NULL);
}

uintptr_t
memsection_size(memsection_ref_t memsect)
{
	uintptr_t size = 0;
	iguana_memsection_info(L4_Pager(), memsect, &size, NULL);
	return size;
}

int
memsection_page_map(memsection_ref_t memsect, L4_Fpage_t from_page, L4_Fpage_t to_page)
{
	return iguana_memsection_page_map(L4_Pager(), memsect, &from_page, &to_page, NULL);
}

int
memsection_page_unmap(memsection_ref_t memsect, L4_Fpage_t to_page)
{
	return iguana_memsection_page_unmap(L4_Pager(), memsect, &to_page, NULL);
}

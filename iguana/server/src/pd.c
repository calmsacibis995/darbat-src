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
  Author: Ben Leslie, Alex Webster
*/
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <l4/ipc.h>
#include <l4/kip.h>
#include <l4/kdebug.h>
#include <l4e/misc.h>
#include <l4e/sigma0.h>
#include "debug.h"
#include "ig_util.h"
#include "objtable.h"
#include "pd.h"
#include "quota.h"
#include "session.h"
#include "thread.h"
#include "vm.h"

struct pd iguana_pd;
bool iguana_pd_inited;

/* Utcb information */
uintptr_t utcb_size_log2;
uintptr_t utcb_size;
L4_Fpage_t kip_area;

static struct memsection *
setup_utcb_area(struct pd *self, void **base, L4_Fpage_t *area, int threads)
{
	/* Find the size of utcb */
	struct memsection *utcb_obj;
	uintptr_t area_size, fpage_size;

	/* FIXME: (benjl) We should look at the utcb min size and alignment
	   here, but for now we assume that page alignment is good enough */
	area_size = utcb_size * threads;

	/* Find the Fpage size */
	for (fpage_size = 1U; fpage_size < area_size; 
	     fpage_size = fpage_size << 1) {}
#ifdef ARCH_ARM
#define ONE_MB (1024 * 1024)
	fpage_size = (((fpage_size - 1) / ONE_MB) + 1) * ONE_MB;
#endif
#ifdef ARCH_IA32
#define FOUR_MB (4 * 1024 * 1024)
	fpage_size = (((fpage_size - 1) / FOUR_MB) + 1) * FOUR_MB;
#endif
	
	utcb_obj = pd_create_memsection(self, fpage_size, 0, MEM_UTCB);
/*	
	assert(utcb_obj);
	assert((utcb_obj->base % fpage_size) == 0);
*/
	if (!utcb_obj) return NULL;
	if ((utcb_obj->base % fpage_size)) return NULL;
	 
	*base = (void*) utcb_obj->base;
	*area = L4_Fpage((L4_Word_t) *base, area_size);

	return utcb_obj;
}

void
utcb_init(void)
{
	L4_KernelInterfacePage_t *kip;
	kip = L4_GetKernelInterface();
	utcb_size = L4_UtcbSize(kip);
	utcb_size_log2 = kip->UtcbAreaInfo.X.a;

	/* We map the kip into all area */
	kip_area = L4_FpageLog2((L4_Word_t) kip, L4_KipAreaSizeLog2(kip));
}

static struct pd*
pd_setup(struct pd *self, struct pd *parent, int max_threads)
{	
	self->magic = PD_MAGIC;
	self->owner = parent;
	self->state = pd_empty;
	self->local_threadno = bfl_new(max_threads);
	self->callback_buffer = NULL;
	/* initialize cb_alloc_handler, ignore it will cause problem when doing pd_delete()*/
	self->cba = NULL;

	thread_list_init(&self->threads);
	pd_list_init(&self->pds);
	session_p_list_init(&self->sessions);
	memsection_list_init(&self->memsections);
	eas_list_init(&self->eass);
	clist_list_init(&self->clists);
	self->quota = new_quota();
	set_quota(self->quota, QUOTA_INF);

	return self;
}

void
pd_init(struct l4e_memory_info *meminfo)
{
	struct memsection_list *list = &iguana_pd.memsections;
	struct memsection_node *node, *next, *first_ms;

	pd_setup(&iguana_pd, &iguana_pd, 10); /* Setup the iguana_pd with itself as parent */
	/* self->utcb_memsection = setup_utcb_area(self, &self->utcb_base, &self->utcb_area, max_threads); */
	iguana_pd_inited = true;

	/* Insert memsections used during bootstrapping into memsection
	 * list and objtable */
	first_ms = internal_memsections.first;
	node = first_ms;
	do {
		next = node->next;
		objtable_insert(&node->data);
		node->next = (void *)list;
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
		node = next;
	} while (node != first_ms);
}

void
pd_setup_callback(struct pd *self, struct memsection *callback_buffer)
{
	//int r;
	self->callback_buffer = callback_buffer;
	/* We don't want to fault on this memory */
	//r = vm_back_mem(callback_buffer->base, callback_buffer->end);
	//assert(r == 0);
	self->cba = cb_new_withmem((void*) callback_buffer->base, 
				   callback_buffer->end - 
				   callback_buffer->base);
}

struct pd*
pd_create(struct pd *self, int max_threads)
{
  	struct pd *new_pd;

 	if (max_threads >= MAX_THREADS_PER_APD)
		return NULL;
 	if (!self)
		return NULL;
  	if (max_threads == 0) {
  		max_threads = MAX_THREADS_PER_APD;
  	}
 
  	new_pd = pd_list_create_back(&self->pds); 
	
	if (new_pd == NULL)
		return NULL;
 	
  	pd_setup(new_pd, self, max_threads);
  
 	new_pd->utcb_memsection = setup_utcb_area(new_pd, &new_pd->utcb_base, &new_pd->utcb_area, max_threads);

 	if (!new_pd->utcb_memsection) return NULL;
  	return new_pd;

}

int
pd_delete(struct pd *pd)
{
	struct thread_node *thread;
	struct thread *dead_thread;
	struct pd_node *pds;
	struct pd *dead_pds;
	struct eas_node *eas;
	struct eas *dead_eas;
	struct memsection_node *memsection;
	struct session_p_node *session;
	struct session **dead_session;

	/* Delete callback_buffer */
	if (pd->callback_buffer)
		memsection_delete(pd->callback_buffer);
	
 	/* Delete utcb_memsection */
 	if (pd->utcb_memsection)
		memsection_delete(pd->utcb_memsection);	

	/* Delete cba */
	if (pd->cba) {
		pd->cba->cb = NULL; /* XXX: the buffer is deleted above */
		cb_free(pd->cba);
	}

 	/* Delete memsections */
 	for (memsection = pd->memsections.first;
	     memsection->next != pd->memsections.first; 
	     memsection = pd->memsections.first) {
		/* FIXME: How can this actually work? */
 		//do not need to remove it from list,
 		//memsection_delete will do it by hand.
 		memsection_delete(&(memsection->data));
 	}

	/* Delete all external as's */
	/* FIXME: We really should have a decent iterator */
	for (eas = pd->eass.first; 
	     eas->next != pd->eass.first; ) {
		dead_eas = &eas->data;
		eas = eas->next;
		eas_delete(dead_eas);
		eas_list_delete(dead_eas);
	}


	for (pds = pd->pds.first;
		pds->next != pd->pds.first; ) {
		dead_pds = &pds->data;
		pds = pds->next;
		pd_delete(dead_pds);
		pd_list_delete(dead_pds);
	}
		
	/* Delete sessions */
	for (session = pd->sessions.first;
		session->next != pd->sessions.first; ) {
		dead_session = &session->data;
		session = session->next;
		session_delete(*dead_session);
	}
	
	/* Delete all threads */
	/* FIXME: We really should have a decent iterator */
	for (thread = pd->threads.first; 
	     thread->next != pd->threads.first; ) {
		dead_thread = &thread->data;
		thread = thread->next;
		thread_delete(dead_thread);
	}

	/* Delete local_threadno */
	if (pd->local_threadno)
		free(pd->local_threadno);
	
	quota_free(pd->quota);

	pd_list_delete(pd);

	return 0;
}

struct memsection *
pd_create_memsection(struct pd *self, uintptr_t size, uintptr_t base, int flags)
{
	struct memsection_node *node;
	struct memsection *memsection;
	struct memsection_list *list;
	int r = 0;
	size = page_round_up(size);

	node = memsection_new();
	if (node == NULL)
		return NULL;
	memsection = &(node->data);

	if (flags & MEM_NORMAL) {
		r = objtable_setup(memsection, size, flags);
	} else if (flags & MEM_FIXED) {
		r = objtable_setup_fixed(memsection, size, base, flags);
	} else if (flags & MEM_UTCB) {
		r = objtable_setup_utcb(memsection, size, flags);
	} else if (flags & MEM_INTERNAL) {
		r = objtable_setup_internal(memsection, size, base, flags);
#ifdef CONFIG_RESTRICTED_VM
	} else if (flags & MEM_DIRECT) {
		r = objtable_setup_direct(memsection, size, flags);
#endif
	} else {
		/* Didn't have a valid type */
		r = -1;
	}

	if (r != 0) {
		/* Insertion into object table failed!  Delete
		 * memsection from mem_alloc, need not to delete 
		 * it from memsection_list. */
		delete_memsection_from_allocator(node);
		return NULL;
	}
	
	/*manually append memsection to memsection_list.*/
	if (iguana_pd_inited)
		list = &self->memsections;
	else
		list = &internal_memsections;
	node->next = (void *) list;
	list->last->next = node;
	node->prev = list->last;
	list->last = node;
	
	return memsection;
}

struct session *
pd_create_session(struct pd *self, struct thread *client, 
		  struct thread *server, struct memsection *clist)
{
	struct session *session = NULL;
	struct pd *other;
	uintptr_t r;

	assert(is_pd(self));
	assert(is_thread(client));
	assert(is_thread(server));
	assert(is_memsection(clist));

	other = server->owner;

	/* Create session */
	session = malloc(sizeof(struct session));

	if (session == NULL) {
		return NULL;
	}

	session->owner = self;
	/* Add it to our pd */

	session->owner_node = session_p_list_create_back(&self->sessions);

	if (session->owner_node == NULL) {
		/* We have run out of memory! */
		free(session);
		return NULL;
	}

	*session->owner_node = session;
	
	session->magic = SESSION_MAGIC;
	session->call_buf = NULL;
	session->return_buf = NULL;
	
	/* Setup fields */
	session->client = client;
	session->server = server;
	session->clist = clist;

	/* Add it to client and server */

	session->server_node = session_p_list_create_back(&client->server_sessions);
	if (session->server_node == NULL) {
		/* We have run out of memory! */
		session_p_list_delete(session->owner_node);
		free(session);
		return NULL;
	}

	*session->server_node = session;

	session->client_node = session_p_list_create_back(&server->client_sessions);
	
	if (session->client_node == NULL) {
		/* We have run out of memory! */
		session_p_list_delete(session->owner_node);
		session_p_list_delete(session->server_node);
		free(session);
		return NULL;
	}


	*session->client_node = session;

	r = pd_add_clist(other, (cap_t*) clist->base);

	if (r == 0) {
		/* Need to clean everything up to this point */
		session_p_list_delete(session->owner_node);
		session_p_list_delete(session->client_node);
		session_p_list_delete(session->server_node);
		free(session);
		return NULL;
	}

#if 0
	/* FIXME: Maybe we need to let the server know, maybe not */
	{
		/* Zero timeout ping -- FIXME: This should be handled by idl upcall
		   code, but do this later */
		L4_Msg_t msg;
		uintptr_t *size;
		uintptr_t *addr;
		/* Now notify client and server prot domains */
		size = cb_alloc(other->cba, sizeof(uintptr_t));
		if (size == NULL) {
			ERROR_PRINT("Couldn't do upcall");
			return NULL; /* Error */
		}
		*size = 2 * sizeof(uintptr_t);
		addr = cb_alloc(other->cba, *size);
		addr[0] = 0x37;
		addr[1] = (uintptr_t) client->id.raw;
		cb_sync_alloc(other->cba);
		
		L4_MsgClear(&msg);
		L4_MsgLoad(&msg);
		L4_Send_Timeout(other->threads.first->data.id, L4_ZeroTime);
	}
#endif
	return session;
}

struct eas *
pd_create_eas(struct pd *self, L4_Fpage_t kip, L4_Fpage_t utcb)
{
	struct eas *eas;
	eas = eas_list_create_back(&self->eass);
	assert(eas);
	eas_setup(eas, kip, utcb);
	return eas;
}


struct thread *
pd_create_thread(struct pd* self, int priority)
{
	struct thread *thread;
	int local_tid = 0;

	assert(self != NULL);

	switch (self->state) {
	case pd_empty:
	case pd_active:
		thread = thread_list_create_back(&self->threads);

		if (thread == NULL) {
			return NULL;
		}

		local_tid = bfl_alloc(self->local_threadno);
		assert(local_tid != -1);
		thread->owner = self;
		thread->utcb = (void*) ((uintptr_t) self->utcb_base + (utcb_size * local_tid));
		break;
	case pd_suspended:
		thread = &self->threads.first->data;
		break;
	default:
		assert(!"pd corruption");
		return 0;
	}

	if (thread_setup(thread, priority) != 0) {
		/* Need to clean up */
		if (self->state != pd_suspended) {
			bfl_free(self->local_threadno, local_tid);
			thread_list_delete(thread);
		}
		return NULL;
	}

	self->state = pd_active;
	return thread;
}

void
pd_delete_thread(struct pd *pd, struct thread *thread)
{
	/* If it is not the last thread in the eas, delete it */
	if (pd->threads.first->next != (struct thread_node *)&pd->threads) {
		thread_delete(thread);
	} else {
		L4_AbortIpc_and_stop_Thread(pd_l4_space(pd));
		pd->state = pd_suspended;
	}
}

uintptr_t
pd_add_clist(struct pd* self, cap_t *clist)
{
	struct clist_info *clist_info;
	struct memsection *memsection = objtable_lookup(clist);

	clist_info = clist_list_create_back(&self->clists);

	if (clist_info == NULL) {
		return 0;
	}

	clist_info->clist = clist;
	clist_info->type = 0; /* Unsorted is default for now */
	clist_info->length = (memsection->end - memsection->base + 1) / sizeof(cap_t);
	return (uintptr_t) clist_info;
}


void
pd_release_clist(struct pd* self, cap_t *clist)
{
	struct clist_node *clists;

	ASSERT_PTR(self);

	for (clists = self->clists.first;
	     clists->next != self->clists.first; 
	     clists = clists->next) {
 		if (clist == clists->data.clist) {
			clist_list_delete(&clists->data);
			break;
		}
	}
	return;
}

void
pd_print(struct pd* self)
{
	DEBUG_PRINT("PD: %p\n", self);
	DEBUG_PRINT(" Owner: %p\n", self->owner);
	DEBUG_PRINT(" State: %d\n", self->state);
	/* Print out thread */
	/* Print out pds */
}

int
pd_check_state(struct pd *base_pd)
{
	/* Check that the PD is valid -- this is a debugging feature */
	int r = 0;

        struct memsection_node *ms, *first_ms = base_pd->memsections.first;
        struct thread_node *td, *first_td = base_pd->threads.first;
        struct session_p_node *sd, *first_sd = base_pd->sessions.first;
        struct pd_node *pd, *first_pd = base_pd->pds.first;
        
	if (! is_pd(base_pd)) {
		return 1;
	}

	if (! is_pd(base_pd->owner)) {
		return 1;
	}

        for (ms = first_ms; ms->next != first_ms; ms = ms->next) {
		ASSERT_PTR(&ms->data);
                r += memsection_check_state(&ms->data);
        }

        for (td = first_td; td->next != first_td; td = td->next) {
		ASSERT_PTR(&td->data);
                r += thread_check_state(&td->data);
        }

        for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
		ASSERT_PTR(&sd->data);
                r += session_check_state(sd->data);
        }

        for (pd = first_pd; pd->next != first_pd; pd = pd->next) {
		ASSERT_PTR(&pd->data);
                r += pd_check_state(&pd->data);
        }

	return r;
}

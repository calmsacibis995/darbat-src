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
  Authors: Ben Leslie
*/

#include "thread.h"
#include "pd.h"

#include <l4/kip.h>
#include <l4/schedule.h>
#include <l4/kdebug.h>
#include <l4e/thread.h>

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#include <hash.h>

#include "ig_util.h"

#define THREAD_PD_HASHSIZE 1024

rfl_t thread_list;
static struct hashtable *l4tid_to_thread;
static L4_Word_t min_threadno, max_threadno;
extern L4_Fpage_t kip_area;

/* 
 * This initialise data structures for managing threads. 
 *
 * Called from: main (1)
 */
void
thread_init(void)
{
	/* Work out the thread ids that are available to us */
	L4_KernelInterfacePage_t *kip;
	int r;

	kip = L4_GetKernelInterface();
	min_threadno = L4_ThreadNo(L4_Myself()) + 2; /* +1 is the callback thread */
	max_threadno = 1ul << L4_ThreadIdBits(kip);


	thread_list = rfl_new();
	assert(thread_list != NULL);

#ifdef CONFIG_TEST_FEW_THREADS
	/* This tests iguana behaviour when the pool of available
	   thread ids is exhausted */
	max_threadno = from + 30;
#endif
	r = rfl_insert_range(thread_list, min_threadno, max_threadno);
	assert(r == 0);

        l4tid_to_thread = hash_init (THREAD_PD_HASHSIZE);
}

void
thread_free(L4_ThreadId_t thread)
{
	/* Removed thread->pd mapping */
	hash_remove (l4tid_to_thread, thread.raw);
	/* Add thread back to free pool */
	rfl_free(thread_list, L4_ThreadNo(thread));
}

int
thread_alloc(struct thread *thread)
{
	int thread_no;

	thread_no = rfl_alloc(thread_list);

	if (thread_no == -1) {
		/* Run out of threads */
		return 1;
	}

	assert(thread_no > 0);

	thread->id = L4_GlobalId(thread_no, 1);

        assert (hash_lookup (l4tid_to_thread, thread->id.raw) == NULL);
	hash_insert (l4tid_to_thread, thread->id.raw, thread);

	return 0;
}

int
thread_setup(struct thread *self, int priority)
{
	int ret = 1; 
	int r;
	L4_Word_t ignore;
	struct pd *pd;

	assert(self != NULL);

	pd = self->owner;

	/* Note: These don't allocate any resources */
	session_p_list_init(&self->client_sessions);
	session_p_list_init(&self->server_sessions);

	if (priority == -1)
		priority = 100;

	if (pd->state != pd_suspended) {
		self->magic = THREAD_MAGIC;
		self->eas = NULL;
		r = thread_alloc(self); /* Allocate a thread id, ALLOC #1 */
		if (r != 0) {  
			/* Can't allocate a new thread ID */
			return 1;
		}
	}
	if (pd->state == pd_empty) {
		/* Create thread in a new address space */
		r = L4_ThreadControl(self->id, self->id, L4_Myself(), 
				     L4_nilthread, L4_anythread, L4_anythread, 
				     self->utcb);
		if (r == 0) {
			ERROR_PRINT_L4;
		}
		assert(r != 0);
		/* Setup the new l4 address space for the pd */
#ifdef ARCH_ARM
		/* Place all iguana PDs in L4 ARM vspace #1 */
		r = L4_SpaceControl(self->id, (1<<16), kip_area, pd->utcb_area, &ignore);
#else
		r = L4_SpaceControl(self->id, 0, kip_area, pd->utcb_area, &ignore);
#endif
		if (r == 0) {
			ERROR_PRINT_L4;
		}
		assert(r == 1);
	} else {
		r = L4_ThreadControl(self->id, pd->threads.first->data.id,
				     L4_Myself(), L4_nilthread, L4_anythread,
				     L4_anythread, (void*) -1);
		if (r == 0) {
			ERROR_PRINT_L4;
		}
	}

	/* Set Priority */
	L4_Set_Priority(self->id, priority);

	/* Activate new thread */
	if (pd->state != pd_suspended) {
		r = L4_ThreadControl(self->id, pd_l4_space(pd), pd_l4_space(pd),
				     L4_Myself(), L4_anythread, L4_anythread,
				     self->utcb);
		if (r != 1) {
			if (L4_ErrorCode() == L4_ErrNoMem) {
				/* L4 has run out of memory... this is probably very bad, 
				   but we want to keep going for as long as we can */
				goto thread_error_state;
			} else {
				ERROR_PRINT_L4;
				assert(!"This shouldn't happen");
			}
		} else {
			ret = 0;
		}
	}  else {
		ret = 0;
	}

	pd->state = pd_active;
	return ret;

 thread_error_state:
	/* Here we clean up anything we have allocated */
	if (pd->state != pd_suspended) {
		/* Need to do a thread_free */
		thread_free(self->id);
	}
	return 1;
}

extern int utcb_size_log2;
void
thread_delete(struct thread *thread)
{
	struct pd *pd;
        struct session_p_node *sd;

	pd = thread->owner;	
	L4_ThreadControl(thread->id, L4_nilthread, L4_nilthread, L4_nilthread, 
			L4_nilthread, L4_nilthread, NULL);
	thread_free(thread->id);

	if (!thread->eas)
		//free local thread no.
		bfl_free(pd->local_threadno, 
			((uintptr_t)thread->utcb - (uintptr_t)pd->utcb_base)>>utcb_size_log2);

	/* Now I need to go and delete any session that we are currently involved with.
	 Note: EAS threads don't have sessions. */
	if (thread->eas == NULL) {
		for (sd = thread->client_sessions.first; 
		     sd->next != thread->client_sessions.first; 
		     sd = thread->client_sessions.first) {
			assert(is_session(sd->data));
			session_delete(sd->data);
		}	
		
		for (sd = thread->server_sessions.first; 
		     sd->next != thread->server_sessions.first; 
		     sd = thread->server_sessions.first) {
			session_delete(sd->data);
		}
	}

	thread_list_delete(thread);
	thread->magic = 0;
}

struct thread *
thread_lookup(L4_ThreadId_t thread)
{
	return hash_lookup (l4tid_to_thread, thread.raw);
}

int
thread_start(struct thread *self, uintptr_t ip, uintptr_t sp)
{
	return l4e_thread_start(self->id, ip, sp);
}

void
thread_print(struct thread *self)
{
	DEBUG_PRINT("Thread: %p (Valid: %" PRIdPTR " -- %" PRIxPTR ")\n", self, 
	       (self->magic = THREAD_MAGIC), self->magic);
	DEBUG_PRINT(" Owner   : %p\n", self->owner);
	DEBUG_PRINT(" ThreadNo: %ld\n", L4_ThreadNo(self->id));
	DEBUG_PRINT(" External: %p\n", self->eas);
	DEBUG_PRINT(" Utcb    : %p\n", self->utcb);
}

void
thread_raise_exception(struct thread *thread, uintptr_t exc, uintptr_t x)
{
	L4_Word_t old_sp, old_ip, old_flags;
	L4_Word_t new_sp, new_ip;
	uintptr_t *stack;

	L4_Stop_SpIpFlags(thread->id, &old_sp, &old_ip, &old_flags);

	stack = (uintptr_t *) thread->exception[exc].sp;
	if (!stack)
		stack = (uintptr_t *) old_sp;
	stack--; *stack = old_ip;
	stack--; *stack = old_sp;
	stack--; *stack = old_flags;
	stack--; *stack = x;

	new_sp = (uintptr_t) stack;
	new_ip = thread->exception[exc].ip;

	assert(new_ip && new_sp);
	L4_Start_SpIp(thread->id, new_sp, new_ip);
}

int
thread_check_state(struct thread *thread)
{
	int r = 0;
        struct session_p_node *sd, *first_sd;

	if (! is_thread(thread)) {
		return 1;
	}

	if (L4_ThreadNo(thread->id) > max_threadno) {
		return 1;
	}

	if (L4_ThreadNo(thread->id) < min_threadno) {
		return 1;
	}

	if (thread_lookup(thread->id) != thread) {
		return 1;
	}

	if (thread->eas == NULL) {
		first_sd = thread->client_sessions.first;
		for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
			r += session_check_state_server(sd->data, thread);
		}	
		if (r > 0)
			ERROR_PRINT("thread: %p client failed: %d\n", thread, r);
		
		first_sd = thread->server_sessions.first;
		for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
			r += session_check_state_client(sd->data, thread);
		}	
		if (r > 0)
			ERROR_PRINT("thread: %p failed: %d\n", thread, r);
	}

	return r;
}

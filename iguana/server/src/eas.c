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
#include <l4/thread.h>
#include <stdio.h>
#include <assert.h>
#include "thread.h"
#include "eas.h"
#include "ig_util.h"

int
eas_setup(struct eas *eas, L4_Fpage_t kip, L4_Fpage_t utcb)
{
	eas->kip = kip;
	eas->utcb_area = utcb;
	eas->redirector = L4_anythread;
	eas->state = eas_empty;
	thread_list_init(&eas->threads);
	return 0;
}

void
eas_delete(struct eas *eas)
{
	struct thread_node *thread;
	struct thread *dead_thread;

	/* Delete all threads */
	for (thread = eas->threads.first; 
	     thread->next != eas->threads.first; ) {
		dead_thread = &thread->data;
		thread = thread->next;
		thread_delete(dead_thread);
	}
}

struct thread *
eas_create_thread(struct eas *self, L4_ThreadId_t pager,
		  L4_ThreadId_t scheduler, uintptr_t utcb)
{
	L4_Word_t ignore;
	struct thread *thread = NULL;
	L4_Word_t r;
	int r1;

	switch (self->state) {
	case eas_empty:
	case eas_active:
		thread = thread_list_create_back(&self->threads);
		if (thread == NULL) {
			return NULL;
		}
		r1 = thread_alloc(thread); /* Allocate a thread id */
		if (r1 != 0) { 
			thread_list_delete(thread);
			return NULL;
		}
		thread->magic = THREAD_MAGIC;
		thread->eas = self;
		thread->owner = self->owner;
		thread->utcb = (void *)utcb;

		break;
	case eas_suspended:
		thread = &self->threads.first->data;
		if (thread->utcb != (void*) utcb) {
			assert(!"Creating a new thread with a utcb != thread->utcb");
		}
		break;
	default:
		assert(!"eas corruption");
		return NULL;
	}

	if (self->state == eas_empty) {
		/* Create thread in a new address space */
		r = L4_ThreadControl(thread->id, thread->id, L4_Myself(), 
				     L4_nilthread, L4_anythread, L4_anythread, 
				     (void*) utcb);
		if (r != 1) {
			if (L4_ErrorCode() == L4_ErrNoMem) {
				/* L4 has run out of memory... this is probably very bad, 
				   but we want to keep going for as long as we can */
				goto thread_error_state;
			} else {
				ERROR_PRINT("Thread control failed. %lx\n", L4_ErrorCode());
				assert(!"This shouldn't happen");
			}
		}

		/* Setup the new address space */
		r = L4_SpaceControl(thread->id, 0, self->kip, self->utcb_area,
				    &ignore); 
		if (r == 0) {
			ERROR_PRINT(" Error: %lx\n", L4_ErrorCode());
		}
		assert(r != 0);
	} else {
               r = L4_ThreadControl(thread->id, eas_l4_space(self),
                                    L4_Myself(), L4_nilthread, L4_anythread,
                                    L4_anythread, (void*) -1);
               if (r == 0) {
                       ERROR_PRINT("Error: %lx\n", L4_ErrorCode());
               }
       }

	/* Activate new thread */
	if (self->state != eas_suspended) {
		r = L4_ThreadControl(thread->id, eas_l4_space(self), 
				     scheduler, pager, L4_anythread, L4_anythread, 
				     (void*) utcb);
		if (r != 1) {
			if (L4_ErrorCode() == L4_ErrNoMem) {
				/* L4 has run out of memory... this is probably very bad, 
				   but we want to keep going for as long as we can */
				goto thread_error_state;
			} else {
				ERROR_PRINT("Thread control failed: %lx\n", L4_ErrorCode());
				assert(!"This shouldn't happen");
			}
		}
	}

	self->state = eas_active;
	return thread;
 thread_error_state:
	if (self->state != eas_suspended) {
		/* Need to do a thread_free */
		thread_free(thread->id);
	}
	thread_list_delete(thread);

	return NULL;
}

void
eas_delete_thread(struct eas *self, struct thread *thread)
{
	/* If it is not the last thread in the eas, delete it */
	if (self->threads.first->next != (struct thread_node *)&self->threads) {
		thread_delete(thread);
	} else {
		L4_AbortIpc_and_stop_Thread(eas_l4_space(self));
		self->state = eas_suspended;
	}
}


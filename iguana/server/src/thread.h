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
 Created: Mon Jul  5 2004 

 Describes the iguana thread
*/

#ifndef _IGUANA_THREAD_H_
#define _IGUANA_THREAD_H_

#include <l4/thread.h>
#include <ll.h>
#include <stdint.h>
#include <range_fl.h>

#include "exception.h"
#include "session.h"

#define THREAD_MAGIC 0x711ead

#define is_thread(ptr) ((ptr != NULL) && (ptr->magic == THREAD_MAGIC))

struct thread {
	uintptr_t magic;
	struct pd *owner; /* Our owner */
	void *utcb;
	struct eas *eas; /* If not NULL, indicates an external thread, in a different space */
	L4_ThreadId_t id;
	/* Note that these are a list of 
	   session list *, since sessions
	   will be in two linked lists */
	struct session_p_list client_sessions; 
	struct session_p_list server_sessions; 
	struct exception exception[2];
};

struct thread_list
{
	struct thread_node* first;
	struct thread_node* last;
};

struct thread_node
{
	struct thread_node* next;
	struct thread_node* prev;
	struct thread data;
};

static inline struct thread * thread_list_create_front(struct thread_list* list)
{
	return (struct thread *) dl_list_create_front((struct double_list *) list, sizeof(struct thread));
}

static inline struct thread * thread_list_create_back(struct thread_list* list)
{
	return (struct thread *) dl_list_create_back((struct double_list *) list, sizeof(struct thread));
}

static inline void thread_list_delete(struct thread * data)
{
	(void) ll_delete((struct ll *) ((void**) data - 2));
}

static inline void thread_list_init(struct thread_list *list)
{
	dl_list_init((struct double_list *) list);     
}

static inline void thread_list_clear(struct thread_list * list)
{
	dl_list_clear((struct double_list *) list) ;   
}

void thread_init(void);

struct thread *thread_lookup(L4_ThreadId_t thrd); /* Given an L4 thread ID return its associated thread */
int thread_setup(struct thread *thread, int priority); /* Called to initialise the thread structure */
int thread_start(struct thread *thread, uintptr_t ip, uintptr_t sp);
void thread_delete(struct thread *thread);
void thread_free(L4_ThreadId_t thread);

int thread_alloc(struct thread *thread);
void thread_print(struct thread *thread);

void thread_raise_exception(struct thread *thread, uintptr_t exc, uintptr_t x);

int thread_check_state(struct thread *thread);

extern rfl_t thread_list;

#endif /* _IGUANA_THREAD_H_ */

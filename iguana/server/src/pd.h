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
 Created: Mon Jul  5 2004 

 Describes the the iguana protection domain.
*/

#ifndef _IGUANA_PD_H_
#define _IGUANA_PD_H_

#include <l4e/regions.h>
#include <l4/thread.h>
#include <bit_fl.h>
#include <cb.h>
#include <iguana/types.h>
#include "thread.h"
#include "memsection.h"
#include "eas.h"
#include "session.h"

/* This is the size of the Utcb area */
#ifdef ARCH_ARM
#define MAX_THREADS_PER_APD 1000 /* FIXME: (benjl) This should be more easily configurable */
#else
#ifdef ARCH_IA32
#define MAX_THREADS_PER_APD	1000
#else
#define MAX_THREADS_PER_APD 8
#endif	/* ARCH_IA32 */
#endif	/* ARCH_ARM */
/* This is so low because we need to ensure the Utcb fpages are less
   than page size */

#define CLIST_SIZE 20 /* FIXME: Dynamic clist size, although array is 
			 negligble cf. other costs of a pd */

#define PD_MAGIC 0x9eeedeee

#define is_pd(ptr) (ptr != NULL && ptr->magic == PD_MAGIC)

/* Declare a doubly linked list of PDs */
struct pd_list
{
	struct pd_node* first;
	struct pd_node* last;
};

struct clist_list
{
	struct clist_node* first;
	struct clist_node* last;
};

struct clist_info {
	cap_t *clist;
	unsigned int type;
	uintptr_t length;
};

struct clist_node
{
    struct clist_node* next;
    struct clist_node* prev;
    struct clist_info data;
};

static inline struct clist_info * clist_list_create_front(struct clist_list* list)
{
        return (struct clist_info *) dl_list_create_front((struct double_list *) list, sizeof(struct clist_info));
}

static inline struct clist_info * clist_list_create_back(struct clist_list* list)
{
        return (struct clist_info *) dl_list_create_back((struct double_list *) list, sizeof(struct clist_info));
}

static inline void clist_list_delete(struct clist_info * data)
{
        ll_delete((struct ll *) ((void**) data - 2));
}

static inline void clist_list_init(struct clist_list *list)
{
        dl_list_init((struct double_list *) list);     
}

static inline void clist_list_clear(struct clist_list * list)
{
        dl_list_clear((struct double_list *) list) ;   
}


enum pd_state {
	pd_empty,	/* Newly created */
	pd_active,	/* Has active threads */
	pd_suspended	/* Last thread was removed, but not deleted yet */
};

struct pd {
	uintptr_t magic;
	struct pd *owner; /* Our owner */

	struct memsection *callback_buffer;
	struct cb_alloc_handle *cba;

	/* Thread Info */
	struct thread_list threads;
	bfl_t local_threadno; /* Freelist for utcbs */

	/* PD info */
	struct pd_list pds;
	struct memsection_list memsections;
	struct eas_list eass;
	struct session_p_list sessions; /* Note that these are a list of 
					   session list *, since sessions
					   will be in two linked lists */

	/* UTCB info */
	struct memsection *utcb_memsection;
	void *utcb_base;
	L4_Fpage_t utcb_area;

	/* Clist info */
	struct clist_list clists;

	enum pd_state state; /* State of the pd */

	/* Quota info */
	struct quota * quota;
};

struct pd_node
{
    struct pd_node* next;
    struct pd_node* prev;
    struct pd data;
};

static inline struct pd * pd_list_create_front(struct pd_list* list)
{
        return (struct pd *) dl_list_create_front((struct double_list *) list, sizeof(struct pd));
}

static inline struct pd * pd_list_create_back(struct pd_list* list)
{
        return (struct pd *) dl_list_create_back((struct double_list *) list, sizeof(struct pd));
}

static inline void pd_list_delete(struct pd * data)
{
        ll_delete((struct ll *) ((void**) data - 2));
}

static inline void pd_list_init(struct pd_list *list)
{
        dl_list_init((struct double_list *) list);     
}

static inline void pd_list_clear(struct pd_list * list)
{
        dl_list_clear((struct double_list *) list) ;   
}

extern struct pd iguana_pd;
extern bool iguana_pd_inited;
void pd_init(struct l4e_memory_info *meminfo);
void utcb_init(void);

struct pd* pd_create(struct pd *pd, 
		     int max_thread); /* FIXME: more options */
void pd_setup_callback(struct pd *pd, struct memsection* callback_buffer);
struct thread* pd_create_thread(struct pd *pd, int priority);
void pd_delete_thread(struct pd *pd, struct thread *thread);
void pd_delete_clist(struct pd* self, cap_t *clist);
#define pd_l4_space(pd)	(pd->threads.first->data.id)

/**
 * Create a new session.
 *
 * @param pd Owner of the session
 * @param client Client thread
 * @param server Server thread
 * @param clist A capability list which is address to the server's protection 
 * domain.
 * 
 * \return The new session. NULL on failure
 */
struct session *pd_create_session(struct pd *pd, struct thread *client, 
				  struct thread *server, struct memsection *clist);

struct memsection* pd_create_memsection(struct pd *pd, uintptr_t size, uintptr_t base, int flags);

/**
 * Create an external address space owned by a given protection domain
 *
 * @param pd The owner of the 
 *
 * @param kip The kernel information page for the external address space
 *
 * @param utcb 
 *
 * \return The newly created external address space. NULL returned in case of
 * error.
 */
struct eas* pd_create_eas(struct pd *pd, L4_Fpage_t kip, L4_Fpage_t utcb);

/**
 * Delete an external address space owned by a given protection domain
 *
 * @param pd The owner of the 
 *
 * @param eas The external address space to delete
 *
 */
void pd_delete_eas(struct pd *pd, struct eas* eas);

/**
 * Add a clist to a given protection domain. This will add the
 * clist in the first free slot.
 *
 * @param pd protection domain to add the clist to.
 * @param clist capability list to add to protection domain.
 */
uintptr_t pd_add_clist(struct pd* pd, cap_t *clist);

/**
 * Release a clist from a given protection domain. This will remove the
 * clist, and free the slot.
 *
 * @param pd protection domain to add the clist to.
 * @param clist capability list to add to protection domain.
 */
void pd_release_clist(struct pd* pd, cap_t *clist);


/**
 * Delete a protection domain, (and all the items it owns)
 *
 * @param pd The protection domain to delete
 *
 * \return 0 on succes, -1 on failure.
 */
int pd_delete(struct pd* pd);

/**
 * Pretty print a protection domain structure for debugging
 * purposes.
 *
 * @param pd The protection domain to print
 */
void pd_print(struct pd* pd);

/**
 * Check that the state of a protection domain is valid. This will recursively
 * check any other data structures owned by the PD. This allows the entire system
 * state to be checked by calling pd_check_state() on the root pd.
 *
 * @param base_pd The protection domain to check
 *
 * \return 0 on success, > 0 for each failure
 */
int pd_check_state(struct pd *base_pd);

#endif /* _IGUANA_PD_H_ */

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

 Describes the iguana memory section.
*/
#ifndef _IGUANA_MEMSECTION_H_
#define _IGUANA_MEMSECTION_H_

#include <obj_alloc/obj_alloc.h>
#include <stdint.h>
#include "session.h"
#include <l4/types.h>
#include <queue/tailq.h>
#include "slab_cache.h"
#include "fpage_alloc.h"

#define MEMSECTION_MAGIC 0x5ec71011

#define MEM_NORMAL 0x1
#define MEM_FIXED  0x2
#define MEM_DIRECT 0x4
#define MEM_UTCB   0x8
#define MEM_USER   0x10

#define MEM_VALID_USER_FLAGS ( MEM_NORMAL | MEM_FIXED | MEM_DIRECT | MEM_UTCB | MEM_USER )

#define MEM_INTERNAL 0x20

#define is_memsection(ptr) ((ptr != NULL) && (ptr->magic == MEMSECTION_MAGIC))

/* Description of the iguana memory sections */
struct memsection {
	uintptr_t magic;
	struct pd *owner; /* Our owner */
	uintptr_t base, end;
	uintptr_t phys_direct;	/* TO BE DELETED */
	uintptr_t memory_attributes;
	struct thread *server;
        uintptr_t frames;	/* TO BE DELETED */
	uintptr_t flags;
	bool phys_active;	/* TO BE DELETED */
	union {
		uintptr_t base;
		struct flist_head list;
		TAILQ_HEAD(ml_head, map_list) mappings;	/* TO BE DELETED */
	} phys;
	struct slab_cache *slab_cache;
	TAILQ_ENTRY(memsection) pools;
	TAILQ_HEAD(sl_head, slab) slabs;
	int padding;	/* TO BE DELETED */
};

struct memsection_list
{
	struct memsection_node* first;
	struct memsection_node* last;
};

struct memsection_node
{
    struct memsection_node* next;
    struct memsection_node* prev;
    struct memsection data;
};

static inline struct memsection * memsection_list_create_front(struct memsection_list* list)
{
	return (struct memsection *) dl_list_create_front((struct double_list *) list, sizeof(struct memsection));
}

static inline struct memsection * memsection_list_create_back(struct memsection_list* list)
{
        return (struct memsection *) dl_list_create_back((struct double_list *) list, sizeof(struct memsection));
}

static inline void memsection_list_delete(struct memsection * data)
{
        ll_delete((struct ll *) ((void**) data - 2));
}

static inline void memsection_list_init(struct memsection_list *list)
{
        dl_list_init((struct double_list *) list);     
}

static inline void memsection_list_clear(struct memsection_list * list)
{
        dl_list_clear((struct double_list *) list) ;   
}

extern struct memsection_list internal_memsections;

struct memsection_node *memsection_new(void);
void memsection_print(struct memsection *self);
void memsection_register_server(struct memsection *self, struct thread *server);
void memsection_delete(struct memsection * memsect);
int memsection_set_attributes(struct memsection * memsect, uintptr_t attributes);
void delete_memsection_from_allocator(struct memsection_node *node);
int memsection_page_map(struct memsection *self, L4_Fpage_t from_page, L4_Fpage_t to_page);
int memsection_page_unmap(struct memsection *self, L4_Fpage_t to_page);
int memsection_check_state(struct memsection *self);
int memsection_back(struct memsection *memsection);
void memsection_flush(struct memsection *memsection);
struct memsection *memsection_create_cache(struct slab_cache *sc);

#endif /* _IGUANA_MEMSECTION_H_ */

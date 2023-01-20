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
  Created: Sat Nov 13 2004 
*/

#ifndef _IGUANA_ASYNCH_H_
#define _IGUANA_ASYNCH_H_
#include <stdint.h>
#include <stdbool.h>
#include <l4/types.h>
#include <l4/ipc.h>

#include <l4/thread.h>
 
#define __synch_bits   (*(((uintptr_t *)__L4_TCR_ThreadLocalStorage())+3))
#define asynch_mask    (*(((uintptr_t *)__L4_TCR_ThreadLocalStorage())+4))
#define asynch_objects (*(((struct asynch ***)__L4_TCR_ThreadLocalStorage()) + 5))

struct asynch {
	uintptr_t asynch_bit; /* Obviously this overallocated, but we don't want the 
				 compiler to do any fancy padding to this struct */
	uintptr_t object_type;
};

/* buf is a pointer to the memory used for the items stored in thread local
 * storage.  buf needs to be ASYNCH_INIT_BUF_SIZE bytes large. */
void __asynch_thread_init(void *);
void __asynch_thread_free(void);
#define ASYNCH_INIT_BUF_SIZE (sizeof(struct asynch *) * sizeof(uintptr_t) * 8)

int asynch_get_bit(void);
void asynch_free_bit(int);

static inline void
asynch_init(struct asynch *object)
{
	object->asynch_bit = 0;
	object->object_type = 0;
	L4_Set_NotifyMask(0);
	L4_Accept(L4_AsynchItemsAcceptor);
}

int asynch_insert(struct asynch *object, uintptr_t obj_type, uintptr_t *synch_mask);
#define asynch_insert_type(obj, type) asynch_insert((struct asynch *) obj, type##_type, &type##_sync_mask)

void asynch_remove(struct asynch *object, uintptr_t *synch_mask);
#define asynch_remove_type(obj, type) asynch_remove((struct asynch *) obj, &type##_sync_mask)

struct asynch * asynch_check_mask(uintptr_t, bool);

static inline struct asynch *
asynch_wait_mask(uintptr_t mask)
{
	return asynch_check_mask(mask, false);
}

static inline struct asynch *
asynch_poll_mask(uintptr_t mask)
{
	return asynch_check_mask(mask, true);
}


#endif /* _IGUANA_ASYNCH_H_ */

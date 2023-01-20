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

#include <iguana/asynch.h>
#include <iguana/memsection.h>

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
 
#include <l4/types.h>
#include <l4/ipc.h>


void 
__asynch_thread_init(void *buf)
{
	__synch_bits = 0;
	asynch_mask = 0;
	asynch_objects = (struct asynch **)buf;
	assert(asynch_objects != NULL);
}

void
__asynch_thread_free(void)
{

	free(asynch_objects);
}

int
asynch_get_bit(void)
{
	int ret;
	uintptr_t x = 1;
	if (asynch_mask == UINTPTR_MAX) {
		return -1;
	}
	for (ret=0; ret < sizeof(uintptr_t) * 8; ret++) {
		if ((x & asynch_mask) == 0) {
			asynch_mask |= (1 << ret);
			break;
		}
		x <<= 1;
	}
	return ret;
}

void
asynch_free_bit(int bit)
{
	asynch_mask &= ~(1 << bit);
}

int
asynch_insert(struct asynch *object, uintptr_t obj_type, uintptr_t *synch_mask)
{
	object->asynch_bit = asynch_get_bit();
	if (object->asynch_bit == -1) {
		return -1;
	}

	object->object_type = obj_type;
	if (synch_mask) {
		*synch_mask |= (1 << object->asynch_bit);
	}
	asynch_mask |= (1 << object->asynch_bit);

	assert(asynch_objects[object->asynch_bit] == NULL);
	asynch_objects[object->asynch_bit] = object;

	return object->asynch_bit;
}

void
asynch_remove(struct asynch *object, uintptr_t *synch_mask)
{
	asynch_free_bit(object->asynch_bit);
	asynch_objects[object->asynch_bit] = NULL;
	if (synch_mask) {
		*synch_mask &= ~(1 << object->asynch_bit);
	}
	asynch_mask &= ~(1 << object->asynch_bit);
	__synch_bits &= ~(1 << object->asynch_bit);
	/* Check we don't have a pending -- setmask, zero timeout*/
}

struct asynch *
asynch_check_mask(uintptr_t mask, bool poll)
{
	L4_MsgTag_t tag = L4_Niltag;
	uintptr_t search_bits = 0;
	int ret;
	uintptr_t x = 1;
	L4_Word_t retmask = 0;

	/* No bits for this type set, so we have to wait */
	if ((mask & __synch_bits) == 0) {
		if (poll) {
			return NULL;
		}
		L4_Set_NotifyMask(mask);
		tag = L4_WaitNotify (&retmask);
		if (L4_IpcFailed(tag)) {
			printf("Error Code: %lx -- %lx\n", tag.raw, L4_ErrorCode());
		}

		/* Check that we have received an async ipc. */
		assert(L4_IpcSucceeded(tag));

		/* Lets see what bits were set */
		__synch_bits |= retmask;
	}

	search_bits = mask & __synch_bits;

	/* Find the first bit set */
	for (ret=0; ret < sizeof(uintptr_t) * 8; ret++) {
		if ((x & search_bits) != 0) {
			__synch_bits &= ~(1 << ret);
			return asynch_objects[ret];
		}
		x <<= 1;
	}
	{
		printf("BADNESS has happened.. some diagnostics:\n");
		printf("label: %" PRIxPTR "\n", tag.X.label);
		printf("mask: %" PRIxPTR " __sync_bits: %" PRIxPTR " syncword: %" PRIxPTR "\n",
		       mask, __synch_bits, (uintptr_t) retmask);
		assert(!"Received invalid wakeup");
	}
	return NULL;
}


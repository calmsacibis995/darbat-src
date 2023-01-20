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
 Created: Mon Oct  4 2004 
*/

#include <obj_alloc/obj_alloc.h>
#include <util/bits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

extern void * block_alloc(int size);
extern void block_free(void *);

static bool
allocate_new_block(struct obj_alloc *obj_alloc, void *obj_p)
{
	struct obj_alloc *new_obj_alloc = NULL;
	void *obj = NULL;
	rfl_t obj_fl = NULL;
	int r;

	new_obj_alloc = malloc(sizeof(struct obj_alloc));
	if (new_obj_alloc == NULL) {
		return false;
	}

	obj_fl = rfl_new();
	if (obj_fl == NULL) {
		free(new_obj_alloc);
		return false;
	}

	r = rfl_insert_range(obj_fl, 0, obj_alloc->block_size / obj_alloc->obj_size - 1);
	if (r != RFL_SUCCESS) {
		free(new_obj_alloc);
		rfl_destroy(obj_fl);
		return false;
	}

	if (obj_p == NULL) {
		obj = block_alloc(obj_alloc->block_size);
	} else {
		obj = obj_p;
	}
	if (obj == NULL) {
		free(new_obj_alloc);
		rfl_destroy(obj_fl);
		return false;
	}

	new_obj_alloc->obj_fl = obj_fl;
	new_obj_alloc->obj = obj;

	new_obj_alloc->prev = obj_alloc->prev;
	obj_alloc->prev = new_obj_alloc;

	return true;
}

struct obj_alloc *
obj_alloc_new(int obj_size, int block_size)
{
	return obj_alloc_new_with_mem(obj_size, block_size, NULL);
}

struct obj_alloc *
obj_alloc_new_with_mem(int obj_size, int block_size, void *first_block)
{
	bool r;
	struct obj_alloc *obj_alloc;
	struct obj_alloc tmp_obj_alloc;

	if (obj_size == 0 || block_size == 0) {
		return NULL;
	}

	obj_size = next_power_of_2(obj_size);

	tmp_obj_alloc.obj_size = obj_size;
	tmp_obj_alloc.block_size = block_size;
	tmp_obj_alloc.prev = &tmp_obj_alloc;

	r = allocate_new_block(&tmp_obj_alloc, first_block);
	if (r == false) {
		return NULL;
	}

	/* Fixup the pointers in alloc_new_block */
	obj_alloc = tmp_obj_alloc.prev;
	obj_alloc->prev = obj_alloc;
	/* Setup sizes */
	obj_alloc->block_size = block_size;
	obj_alloc->obj_size = obj_size;
	obj_alloc->new_blocks = true;
	return obj_alloc;
}

void
obj_alloc_destroy(struct obj_alloc *alloc)
{
	assert(!"Not implemented");
}

void
obj_alloc_new_block(struct obj_alloc *alloc, void *block)
{
	/* User has provided us with a new block */
	allocate_new_block(alloc, block);
}

void *
obj_alloc_alloc(struct obj_alloc *alloc)
{
	int idx;
	void *obj;
	struct obj_alloc *cur_alloc = alloc;
	assert(alloc != NULL);
	do {
		cur_alloc = cur_alloc->prev;
		idx = rfl_alloc(cur_alloc->obj_fl);
	} while (cur_alloc != alloc && idx == -1);

	if (idx == -1) {
		if (alloc->new_blocks == true) {
			/* Allocate new block */
			bool r;
			r = allocate_new_block(alloc, NULL);
			if (r == false) {
				return NULL;
			} else {
				cur_alloc = alloc->prev;
				idx = rfl_alloc(cur_alloc->obj_fl);
				assert(idx != -1); /* Can't fail this time! */
			}
		} else {
			return NULL;
		}
	}

	/* By now we should have a valid idx */
	assert(idx >= 0 && idx <= alloc->block_size / alloc->obj_size);

	obj = cur_alloc->obj + alloc->obj_size * idx;
	return obj;
}

void
obj_alloc_free(struct obj_alloc *alloc, void *obj)
{
	int idx;
	int r;
	bool found = false;
	struct obj_alloc *cur_alloc = alloc;
	assert(obj != NULL);
	do {
		cur_alloc = cur_alloc->prev;
		if (obj >= (void*) cur_alloc->obj &&
		    obj < (void*) (cur_alloc->obj + alloc->block_size)) {
			found = true;
		}
	} while (cur_alloc != alloc && found == false);

	assert (found == true); /* Tried to free something we didn't alloc */

	idx = ((char*) obj - cur_alloc->obj) / alloc->obj_size;
	r = rfl_free(cur_alloc->obj_fl, idx);
	assert(r == RFL_SUCCESS); /* FIXME: We could actually fail becuase of
				     out of memory here */
}

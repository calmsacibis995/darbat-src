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
 Description:
  range_fl implements a free list. The external interface is
  basically alloc() and free(). A simple implementation would
  just be a linked list.

  This implementation tries to improve on space needed to hold
  the free list. We have a list of ranges. This means if we have a 
  contiguous set of items the space required is very small. As long
  as the list isn't too fragmented this is a win. In the fragmented
  case we degenerate to a linked list.

  The overhead with this is that on a free it must make sure the list
  remains sorted, and also perform any range coalescing. E.g: If you
  have a list 1-3, 5-6, and then free '4' you want to get 1-6.

  Allocation is fairly straightforward, just take the front of the list
  and if you exhaust a range, then remove it from the linked list.

Authors:
  Ben Leslie <benjl@cse.unsw.edu.au>

*/

#include <ll.h>
#include <stdlib.h>
#include <stddef.h>
#include <range_fl.h>
#include <stdio.h>
#include <inttypes.h>

rfl_t
rfl_new(void)
{
	return ll_new();
}

int
rfl_insert_range(rfl_t rfl, uintptr_t from, uintptr_t to)
{
	struct ll *temp;
	struct range *range, *next_range;
	int added = 0;
	
	if (from > to) {
		/* Can't have a range like this */
		return E_RFL_INV_RANGE;
	}

	/* See we can append to existing */
	for (temp = rfl->next; temp != rfl; temp = temp->next) {
		range = temp->data;
		/* Check that the new range doesn't overlap 
		   with this existing range */
		if ( (from >= range->from && from <= range->to) ||
		     (to >= range->from && to <= range->to) ) {
			return E_RFL_OVERLAP;
		}

		if (range->from == to + 1) {
			/* In this case can add to the start of
			   this range */
			range->from = from;
			added = 1;
			break;
		}
		if (range->to == from - 1) {
			/* In this case we can add to the end of 
			   this range */
			next_range = temp->next->data;
			range->to = to;
			if (next_range != NULL && 
			    range->to + 1 == next_range->from) {
				/* Merge with next range */
				range->to = next_range->to;
				/* Now delete the next range */
				free(next_range);
				ll_delete(temp->next);
			}
			added = 1;
			break;
		}
		if (range->from > to) {
			/* In this case we need to insert it before
			   the existing range, so we break now
			   and let the logic at the end add it.
			*/
			break;
		}
	}

	if (added == 0) {
		/* 
		   Couldn't extend an existing range, lets add
		   a new range before the current one. This
		   keeps the list sorted.
		*/
		struct range *new_range = malloc(sizeof(struct range));
		if (new_range == NULL) {
			return E_RFL_NOMEM; /* Failure! */
		}
		ll_insert_before(temp, new_range);
		new_range->from = from;
		new_range->to = to;
	}

	return RFL_SUCCESS;
}


int
rfl_free(rfl_t rfl, uintptr_t val)
{
	return rfl_insert_range(rfl, val, val);
}

uintptr_t
rfl_alloc(rfl_t rfl)
{
	struct range *range;
	uintptr_t retval;
	if (rfl->next == rfl) {
		/* This is the no items left case */
		return -1;
	}
	range = rfl->next->data;
	retval = range->from;
	if (range->from == range->to) {
		/* None left in this range now, free resources */
		free(range);
		ll_delete(rfl->next);
	} else {
		/* There are more left in the range, just increment 
		   the from value
		*/
		range->from++;
	}
	return retval;
}

#if 0
void
rfl_debug(rfl_t rfl, FILE *out)
{
	struct ll *temp;
	struct range *range;

	for (temp = rfl->next; temp != rfl; temp = temp->next) {
		range = temp->data;
		printf("from: %" PRIdPTR " to: %" PRIdPTR "\n", range->from, range->to);
	}	
}
#endif

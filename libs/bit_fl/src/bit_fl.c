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
  Bit array freelist.

Authors:
  Ben Leslie <benjl@cse.unsw.edu.au>

*/

#include <stdlib.h>
#include <stddef.h>
#include <bit_fl.h>
#include <string.h>
#include <assert.h>

#define BITS_PER_LONG (sizeof(bfl_word)*8)

static int find_first_set(bfl_word x);

/* FIXME: (benjl) Find a better home for this */
static int find_first_set(bfl_word x) 
{
	int ret;
	for (ret=0; ret<BITS_PER_LONG; ret++) {
		if (x & 1ul) {
			return ret;
		}
		x >>= 1ul;
	}
	assert(!"no bit found");
	return -1;
}



bfl_t
bfl_new(uintptr_t size)
{
	int i;
	int array_size = (size / BITS_PER_LONG) + 1;
	/* Allocate enough space for the header and the bit array needed */
	bfl_t bfl = malloc(sizeof(struct bfl) + (array_size) * sizeof(int));

	if (bfl == NULL) {
		return NULL;
	}

	bfl->curpos = 0;
	bfl->len = array_size;
	/* Set all as allocated */
	memset(bfl->bitarray, 0, (array_size) * sizeof(int));
	/* Now free the ones we have */
	/* FIXME: (benjl) This is a terribly ineffecient way to do this */
	for(i=0; i < size; i++)
		bfl_free(bfl, i);
	return bfl;
}

void
bfl_free(bfl_t bfl, uintptr_t val)
{
	int idx = val / BITS_PER_LONG;
	/* Set the bit */
	bfl->bitarray[idx] |= 1ul << (val % BITS_PER_LONG);
}

uintptr_t
bfl_alloc(bfl_t bfl)
{
	/* Find empty int */
	int found = 0;
	int pos, i;
	for (i=bfl->curpos; i < bfl->len; i++) {
		if (bfl->bitarray[i] != 0) {
			found = 1;
			break;
		}
	}
	if (found == 0) {
		for(i=0; i < bfl->curpos; i++) {
			if (bfl->bitarray[i] != 0) {
				found = 1;
				break;
			}
		}
	}

	if (found == 0) {
		return -1;
	}

	pos = find_first_set(bfl->bitarray[i]);
	/* Unset the bit */
	bfl->bitarray[i] &= ~(1ul << pos);
	
	if (bfl->bitarray == 0)
		bfl->curpos = (bfl->curpos + 1) % bfl->len;
	return (i * BITS_PER_LONG) + pos;
}

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

#include <stdio.h>
#include <assert.h>
#include <obj_alloc/obj_alloc.h>

void obj_alloc_test(void);

#define TEST_SIZE 10000
#define BLOCK_SIZE 4096
#define OBJ_SIZE 32
void *objs[TEST_SIZE];

void obj_alloc_test(void)
{
	struct obj_alloc *alloc;
	int i;

	printf("obj_alloc_test\n");
	alloc = obj_alloc_new(OBJ_SIZE, BLOCK_SIZE);
	assert(alloc != NULL);
	printf("allocator: %p\n", alloc);
	printf("ALLOCATING OBJECTS...");
	for (i=0; i < TEST_SIZE; i++) {
		objs[i] = obj_alloc_alloc(alloc);
		assert(objs[i] != NULL);
		if (i % 1000 == 0) printf(".");
	}
	printf("\n");
	assert(alloc->prev->prev != alloc); /* Check sanity of list -- assume we needed > 2
					       blocks */
	assert(objs[BLOCK_SIZE/OBJ_SIZE-1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	assert(objs[BLOCK_SIZE/OBJ_SIZE+1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	printf("objs[0] = %p, objs[%d] = %p, objs[%d] = %p, objs[%d] = %p, objs[50] = %p, objs[300] = %p\n",
	       objs[0], BLOCK_SIZE/OBJ_SIZE-1, objs[BLOCK_SIZE/OBJ_SIZE-1], BLOCK_SIZE/OBJ_SIZE, 
	       objs[BLOCK_SIZE/OBJ_SIZE], BLOCK_SIZE/OBJ_SIZE + 1, objs[BLOCK_SIZE/OBJ_SIZE+1], 
	       objs[50], objs[300]);

	for (i=0; i < TEST_SIZE; i++) {
		obj_alloc_free(alloc, objs[i]);
	}

	for (i=0; i < TEST_SIZE; i++) {
		objs[i] = obj_alloc_alloc(alloc);
		assert(objs[i] != NULL);
	}

	assert(alloc->prev->prev != alloc); /* Check sanity of list -- assume we needed > 2
					       blocks */
	assert(objs[BLOCK_SIZE/OBJ_SIZE-1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	assert(objs[BLOCK_SIZE/OBJ_SIZE+1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	printf("objs[0] = %p, objs[%d] = %p, objs[%d] = %p, objs[%d] = %p, objs[50] = %p, objs[300] = %p\n",
	       objs[0], BLOCK_SIZE/OBJ_SIZE-1, objs[BLOCK_SIZE/OBJ_SIZE-1], BLOCK_SIZE/OBJ_SIZE, 
	       objs[BLOCK_SIZE/OBJ_SIZE], BLOCK_SIZE/OBJ_SIZE + 1, objs[BLOCK_SIZE/OBJ_SIZE+1], 
	       objs[50], objs[300]);


	for (i=0; i < TEST_SIZE; i++) {
		obj_alloc_free(alloc, objs[i]);
	}

	for (i=0; i < TEST_SIZE; i++) {
		objs[i] = obj_alloc_alloc(alloc);
		assert(objs[i] != NULL);
	}

	assert(alloc->prev->prev != alloc); /* Check sanity of list -- assume we needed > 2
					       blocks */
	assert(objs[BLOCK_SIZE/OBJ_SIZE-1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	assert(objs[BLOCK_SIZE/OBJ_SIZE+1] != objs[BLOCK_SIZE/OBJ_SIZE]);
	printf("objs[0] = %p, objs[%d] = %p, objs[%d] = %p, objs[%d] = %p, objs[50] = %p, objs[300] = %p\n",
	       objs[0], BLOCK_SIZE/OBJ_SIZE-1, objs[BLOCK_SIZE/OBJ_SIZE-1], BLOCK_SIZE/OBJ_SIZE, 
	       objs[BLOCK_SIZE/OBJ_SIZE], BLOCK_SIZE/OBJ_SIZE + 1, objs[BLOCK_SIZE/OBJ_SIZE+1], 
	       objs[50], objs[300]);
}

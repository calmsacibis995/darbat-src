#if 1 /* Worry about how to do this later... */
/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2003-2004 University of New South Wales
 * 
 * All rights reserved. 
 * 
 * Developed by: Operating Systems and Distributed Systems Group (DiSy)
 *               University of New South Wales
 *               http://www.disy.cse.unsw.edu.au
 * 
 * Permission is granted by University of New South Wales, free of charge, to
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
 *     * Neither the name of University of New South Wales, nor the names of its
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
 * conditions, or imposes obligations or liability on University of New South
 * Wales or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of University of New South Wales or the contributor is limited, to
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
 B+ tree debug functions.

Authors:
 Daniel Potts <danielp@cse.unsw.edu.au> - ported to kenge
*/

#include <stdio.h>
#include <inttypes.h>
#include "obj_btree.h"
#include <b_plus_tree.h>
#include "ig_util.h"

void BTPrint(GBTree const btree);

static void
BTPrintObj(const GBTObject blah)
{
	DEBUG_PRINT("  <%08" PRIxPTR ":%08" PRIxPTR ">\t%p\t\n", blah->base, blah->end, blah);
}


/* print B-tree index in inorder way started from root */
static void 
BTPrintInt(BTPage const * const root) 
{
	BTKeyCount i;
	
	DEBUG_PRINT("Page address[%p]\n", root);
	
	for(i = 0; i < root->count; i++) 
		DEBUG_PRINT("%p %" PRIxPTR " ", root->child[i], root->key[i]);
	DEBUG_PRINT("%p\n", root->child[i]);

	/* print all the children */
	for(i = 0; i <= root->count; i++) {
		if (root->isleaf) {
			BTPrintObj((GBTObject)(root->child[i]));
		} else {
			BTPrintInt(root->child[i]);
		}
	}
	DEBUG_PRINT("\n");
}

void BTPrint(GBTree const btree)
/* print b+tree (index and leaves)*/
{
	if (btree && btree->root) {
		DEBUG_PRINT("B-tree %p\n", btree);
		BTPrintInt(btree->root); 
	} else {
		DEBUG_PRINT("B-tree is empty");
	}
}
#endif

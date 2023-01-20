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
 Created: Tue Jul  6 2004 
*/


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#include "security.h"
#include "pd.h"
#include "thread.h"
#include "memsection.h"
#include "objtable.h"
#include "vm.h"
#include "ig_util.h"

/**
 * Validate access to a given reference.
 * @memsection The memory section in which the reference exists
 * @ref The reference to validate
 * @pd The protection domain attempting the access
 *
 * \return On success return the capability that provides access. On failure
 * return INVALID_CAP.
 */
static cap_t
validate_access(struct memsection *memsection, uintptr_t ref, struct pd *pd)
{
 	cap_t cap = INVALID_CAP;
	int iid_bits = 3; //memsection->iid_bits;
 	uintptr_t master_ref = ref >> iid_bits << iid_bits;
	struct clist_node *clists;

	SECURITY_PRINT("Security check ref: %" PRIxPTR "\n", ref);

	for (clists = pd->clists.first;
	     clists->next != pd->clists.first; 
	     clists = clists->next) {
 		cap_t *temp = clists->data.clist;
		SECURITY_PRINT("\tClist: %p\n", temp);
 		if (temp == NULL) {
 			break;
 		}

 		for(int j=0; j < clists->data.length && IS_VALID_CAP(temp[j]); j++) {
			SECURITY_PRINT("\t\tj: %d Ref: %" PRIxPTR " %p\n", j, temp[j].ref.obj, &temp[j].ref.obj);
 			if (temp[j].ref.obj == ref || temp[j].ref.obj == master_ref) {
 				/* Lookup cap */
				cap = temp[j];
 				goto found;
 			}
 		}
 	}
  found:
 	return cap;
}

int
security_check(L4_ThreadId_t tid, uintptr_t ref)
{
	struct thread *thread;
	struct pd *pd;
	struct memsection *memsection;
	cap_t cap;

	thread = thread_lookup(tid);
	if (thread == NULL) {
		return -1;
	}
	pd = thread->owner;

	memsection = objtable_lookup((void*)ref);

	if (memsection == NULL) {
		DEBUG_PRINT("<security> No memory section\n");
		return -2;
	}

	cap = validate_access(memsection, ref, pd);
	if (IS_VALID_CAP(cap)) {
		return 0;
	} else {
#ifdef ENABLE_CAPS
		return -1;
#else
		DEBUG_PRINT("<security> Invalid reference: %" PRIxPTR "\n", ref);
		return 0;
#endif
	}
}

/**
 * Generate a good random number for use as a capability password
 *
 * \return The random number
 */
static uintptr_t
password_gen(void)
{
	/* FIXME: For now we return a really *bad* random number */
	return rand();
}

cap_t
security_create_capability(uintptr_t reference)
{
	cap_t cap;
	cap.ref.obj = reference;
	cap.passwd = password_gen();

	return cap;
}


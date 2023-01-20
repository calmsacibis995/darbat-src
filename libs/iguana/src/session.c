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
  Created: Wed Jul 28 2004 
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <l4e/misc.h>

#include <iguana/session.h>
#include <iguana/memsection.h>
#include <iguana/thread.h>
#include <iguana/pd.h>
#include <iguana/cap.h>
#include <interfaces/iguana_client.h>

#include <stdio.h>

#include <inttypes.h>

int
_session_create(objref_t object, memsection_ref_t clist, L4_ThreadId_t *server_tid, struct session *session)
{
	cap_t cap;
	thread_ref_t server;
	memsection_ref_t memsection;

	/* Find memsection */
	memsection = memsection_lookup(object, &server);

	/* TODO: Search for existing session with that server */

	cap = iguana_pd_create_session(L4_Pager(), 
				       pd_myself(), thread_myself(), server, 
				       clist, NULL);
	if (cap.ref.session == 0) {
		return -1;
	}
	*server_tid = thread_l4tid(server);
	session->ref = cap.ref.session;
	session->clist = memsection_base(clist);
	session->cap_pos = 0;
	session->cap_size = memsection_size(clist) / sizeof(cap_t);
	session->own_clist = false;
	return 0;
}


struct session *
session_create_with_clist(objref_t object, memsection_ref_t clist, L4_ThreadId_t *server_tid)
{
	struct session *session;
	int r;

	session = malloc(sizeof(struct session));

	if (session == NULL)
		return NULL;

	r =  _session_create(object, clist, server_tid, session);

	if (r != 0) {
		free(session);
		session = NULL;
	}

	return session;
}

struct session *
session_create(objref_t object, L4_ThreadId_t *server_tid)
{
	uintptr_t ignore;
	memsection_ref_t clist_ref;
	struct session *session;

	clist_ref = memsection_create(l4e_min_pagesize(), &ignore);

	if (clist_ref == 0) {
		return 0;
	}
	session = session_create_with_clist(object, clist_ref, server_tid);

	if (session == NULL) {
		memsection_delete(clist_ref);
		return NULL;
	}

	session->own_clist = true;

	return session;
}

struct session *
session_create_full_share(objref_t object, L4_ThreadId_t *server_tid)
{
	uintptr_t ignore;
	return session_create_with_clist(object, memsection_lookup((uintptr_t)iguana_get_clist(0), &ignore), server_tid);
}


void
session_add_async(struct session *session, objref_t call_buf, objref_t return_buf)
{
	/* Add async buffers to a session */
	iguana_session_add_buffer(L4_Pager(), session->ref, call_buf, return_buf, NULL);
}

bool
session_provide_access(struct session *session, objref_t object, int interface)
{
	/* Search for the capability in our clists -- either the master or exact */
	cap_t cap;
	assert(session != NULL);

	if (session->cap_pos >= session->cap_size) 
		return false;
	/* FIXME: Find the correct interface */
	cap = iguana_get_cap(object, interface);
	session->clist[session->cap_pos++] = cap;
	return true;
}

bool
session_revoke_access(struct session *session, objref_t object, int interface)
{
	/* Search for the capability in our clists -- either the master or exact */
	cap_t cap;
	cap_t invalid = INVALID_CAP;
	int i;
	if (session->cap_pos >= session->cap_size) 
		return false;
	/* Find the capability */
	for (i=0; i < session->cap_pos; i++) {
		cap = session->clist[i];
		if (cap_matches(cap, object, interface)) {
			session->clist[i] = session->clist[--session->cap_pos];
			session->clist[session->cap_pos] = invalid;
			iguana_session_revoke(L4_Pager(), session->ref, &cap, NULL);
			/* Purge from session */
		}
	}
	return true;
}

void
session_delete(struct session *session)
{
	thread_ref_t unused;

	/* Delete the clist */
	if (session->own_clist) {
		memsection_delete(memsection_lookup((uintptr_t) session->clist, &unused));
	}

	/* Delete the session */
	iguana_session_delete(L4_Pager(), session->ref, NULL);
	free(session);
}

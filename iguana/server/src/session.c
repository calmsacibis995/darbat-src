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
  Created: Thu Aug 12 2004 
*/

#include <l4/ipc.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "session.h"
#include "memsection.h"
#include "pd.h"
#include "ig_util.h"

void
session_add_buffer(struct session *session, void *call_buf, void *return_buf)
{
	assert(session->call_buf == NULL);
	assert(session->return_buf == NULL);
	session->call_buf = call_buf;
	session->return_buf = return_buf;

	/* Now tell the server about this development */
	{
		/* Zero timeout ping -- FIXME: This should be handled by idl upcall
		   code, but do this later */
		struct pd *other = session->server->owner;
		L4_Msg_t msg;
		uintptr_t *size;
		uintptr_t *addr;
		/* Now notify client and server prot domains */
		size = cb_alloc(other->cba, sizeof(uintptr_t));
		if (size == NULL) {
			ERROR_PRINT("Couldn't do upcall");
			return;
		}
		*size = 3 * sizeof(uintptr_t);
		addr = cb_alloc(other->cba, *size);
		addr[0] = 0x38;
		addr[1] = (uintptr_t) call_buf;
		addr[2] = (uintptr_t) return_buf;
		cb_sync_alloc(other->cba);
		
		L4_MsgClear(&msg);
		L4_MsgLoad(&msg);
		L4_Reply(other->threads.first->data.id);
	}

}

void
session_delete(struct session *session)
{
	/* Tell the other side */
	ASSERT_PTR(session);
	ASSERT_PTR(session->server);
	ASSERT_PTR(session->server->owner);
	assert(is_thread(session->server));

	pd_release_clist(session->server->owner, (cap_t*) session->clist->base);

	session_p_list_delete(session->owner_node);
	session_p_list_delete(session->server_node);
	session_p_list_delete(session->client_node);
	/* Then nuke everything */
	session->magic = 0;
	free(session);
}

static int
session_check_basic_state(struct session *self)
{
	if (! is_session(self)) {
		return 1;
	}

	return 0;
}

int
session_check_state(struct session *self)
{
	int r = 0;
	if (session_check_basic_state(self) != 0) {
		return 1;
	}

	r += thread_check_state(self->client);
	r += thread_check_state(self->server);

	return r;
}

int
session_check_state_server(struct session *self, struct thread *server)
{
	int r = 0 ;
	if (session_check_basic_state(self) != 0) {
		ERROR_PRINT("check server client: %p\n", self);
		return 1;
	}

	r +=  (self->server != server);

	return r;
}

int
session_check_state_client(struct session *self, struct thread *client)
{
	int r = 0 ;
	if (session_check_basic_state(self) != 0) {
		ERROR_PRINT("check stat client: %p\n", self);
		return 1;
	}

	r += (self->client != client);

	return r;
}

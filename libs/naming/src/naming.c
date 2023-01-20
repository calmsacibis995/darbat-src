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
  Created: Tue Nov  9 2004 
*/

#include <naming/naming.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iguana/types.h>
#include <iguana/session.h>
#include <iguana/object.h>
#include <iguana/asynch.h>
#include <iguana/memsection.h>
#include <iguana/cap.h>
#include <l4/thread.h>

#include <interfaces/naming_client.h>


#define SESSION() (*(((struct naming_session **)__L4_TCR_ThreadLocalStorage()) + 2))
static objref_t __the_naming_server;
		   
void
__naming_init(objref_t naming_server)
{
        __the_naming_server = naming_server;
}

void
__naming_thread_free(void)
{

	free(SESSION());
}

void
__naming_thread_init(void *buf)
{
        uintptr_t ignore;
        int r;

        if (__the_naming_server != 0 && SESSION() == NULL) {
                //struct naming_session *ps = malloc(sizeof(*ps));
                SESSION() = buf;
                SESSION()->naming_sync_mask = 0;
                SESSION()->__naming_object.obj = __the_naming_server;
                SESSION()->naming_type = (uintptr_t)&SESSION()->naming_type;

                /* FIXME: Default behaviour should really be dedicated clist */
                r = _session_create(SESSION()->__naming_object.obj, memsection_lookup((uintptr_t)iguana_get_clist(0), &ignore),
                                       &SESSION()->__naming_object.server, &SESSION()->__naming_session);
                assert(r == 0);
                SESSION()->__naming_object.session = &SESSION()->__naming_session;
	}
}


int naming_init_buf_size(void) 
{
	return sizeof(struct naming_session);
}

int
naming_insert(const char *name, objref_t value)
{
	int r;
	uintptr_t mask = 0;
	r = naming_write_insert(SESSION()->__naming_object.server, SESSION()->__naming_object.obj,
				   (char *) name, value, &mask, NULL);
	__synch_bits |= mask;
	return r;
}

int
naming_modify(const char *name, objref_t value)
{
	int r;
	uintptr_t mask = 0;
	r =  naming_write_modify(SESSION()->__naming_object.server, SESSION()->__naming_object.obj,
				 (char *) name, value, &mask, NULL);
	__synch_bits |= mask;
	return r;
}

int
naming_delete(const char *name)
{
	int r;
	uintptr_t mask = 0;
	r = naming_write_delete(SESSION()->__naming_object.server, SESSION()->__naming_object.obj,
				(char *) name, &mask, NULL);
	__synch_bits |= mask;
	return r;
}


objref_t
naming_lookup(const char *name)
{
	return naming_read_lookup(SESSION()->__naming_object.server, SESSION()->__naming_object.obj,
				  (char *) name, NULL);
}

naming_notify_t
naming_notify(const char *name, int flags)
{
	naming_notify_t notify;
	L4_ThreadId_t me;
	int bit;
	uintptr_t mask = 0;

	notify = malloc(sizeof(struct naming_notify_obj) + strlen(name));
	/* Note: We don't need a +1 for NULL here as the name field is declared
	   as char name[1] , not char name[]. This is for compatability with pre C99
	   compiles which don't support either char name[], or char name[0]. */
	if (notify == NULL) {
		return NULL;
	}

	asynch_init(&notify->asynch);

	bit = asynch_insert_type(notify, SESSION()->naming);

	if (bit == -1) {
		free(notify);
		return NULL;
	}
	me = L4_Myself();
	notify->obj =  naming_read_notify(SESSION()->__naming_object.server, SESSION()->__naming_object.obj, (char*) name, flags, &me, (1 << bit), &mask, NULL);
	if (notify->obj == 0) {
		asynch_remove_type(notify, SESSION()->naming);
		free(notify);
		return NULL;
	}

	__synch_bits |= mask;
	strcpy(notify->name, name);
	return notify;
}

int
naming_cancel(naming_notify_t notify)
{
	naming_notify__cancel(SESSION()->__naming_object.server, notify->obj, NULL);
	asynch_remove_type(notify, SESSION()->naming);
	free(notify);
	return 0;
}

naming_notify_t
naming_wait(naming_notify_t notify)
{
	return (naming_notify_t) asynch_wait_mask(SESSION()->naming_sync_mask);
}

naming_notify_t
naming_poll(naming_notify_t notify)
{
	return (naming_notify_t) asynch_poll_mask(SESSION()->naming_sync_mask);
}

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
  Created: Fri Nov  5 2004 
  Description: Generic timer implementation. Provides higher level useful functions
   on top of the raw component interface.
*/

#include <timer/timer.h>
#include <stddef.h>
#include <interfaces/timer_client.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <naming/naming.h>
#include <iguana/object.h>
#include <iguana/asynch.h>

struct timer_session {
	object_t *timer_obj;
	uintptr_t timer_sync_mask;
	uintptr_t timer_type;
};
#define SESSION() (*(((struct timer_session **)__L4_TCR_ThreadLocalStorage()) + 1))
 
void
timer_init(void) 
{
	struct timer_session *ts;
	objref_t timer_ref;

	ts = malloc(sizeof(*ts));
	SESSION() = ts;
	SESSION()->timer_sync_mask = 0;
	SESSION()->timer_type = (uintptr_t) &ts->timer_type;

	timer_ref = naming_lookup("timer");

	/* Create a session */
	SESSION()->timer_obj = object_get_interface(timer_ref);

	assert(SESSION()->timer_obj != NULL);
}

void
timer_free(void)
{

	free(SESSION());
}

timer_t
timer_create(void)
{
	timer_t new_timer;
	cap_t timer_cap;
	int bit;
	L4_ThreadId_t me = L4_Myself(); /* FIXME ! */

	/* Call thingy */
	new_timer = malloc(sizeof(struct timer));
	if (new_timer == NULL) {
		return NULL;
	}
	asynch_init(&new_timer->asynch);
	bit = asynch_insert_type(new_timer, SESSION()->timer);

	if (bit == -1) {
		free(new_timer);
		return NULL;
	}

	timer_cap = timer_server_create(SESSION()->timer_obj->server, SESSION()->timer_obj->obj, 
					&me, (1 << bit),  NULL);

	if (timer_cap.ref.obj == 0) {
		asynch_remove_type(new_timer, SESSION()->timer);
		free(new_timer);
		return NULL;
	}

	new_timer->state = timer_cancelled_e;
	new_timer->reference = timer_cap.ref.obj;
	return new_timer;
}

int
timer_request(timer_t timer, uint64_t time, int flags)
{
	uint64_t next_wake = 0;
	if (flags & TIMER_PERIODIC) {
		/* Can't be absolute time if you want period */
		if (flags & TIMER_ABSOLUTE) {
			return -1;
		}
		timer->state = timer_periodic_e;
		timer->period = time;
	} else {
		timer->state = timer_oneshot_e;
	}
	next_wake = timer__request(SESSION()->timer_obj->server, timer->reference, time, flags, NULL);

	/* timer_request failed */
	if (next_wake == -1) {
		timer->state = timer_cancelled_e;
		return -1;
	}

	timer->wakeup_time = next_wake;
	return 0;
}

int
timer_cancel(timer_t timer)
{
	/* Call the thingy */
	timer->state = timer_cancelled_e;
	timer__cancel(SESSION()->timer_obj->server, timer->reference, NULL);
	return 0;
}

int
timer_delete(timer_t timer)
{
	/* Call the thingy */
	timer__delete(SESSION()->timer_obj->server, timer->reference, NULL);
	asynch_remove_type(timer, SESSION()->timer);
	free(timer);
	return 0;
}

timer_t
timer_wait(void)
{
	return (timer_t) asynch_wait_mask(SESSION()->timer_sync_mask);
}

int
timer_expired(timer_t timer)
{
	switch (timer->state) {
	case timer_oneshot_e:
		return (timer->wakeup_time <= timer_current_time());
	case timer_periodic_e:
		/* Period timers can never expire */
		return 1;
	case timer_cancelled_e:
		/* It is an error to test expired on a cancelled timer */
		return -1;
	}

	return 1; /* Stupid gcc! */
}

uint64_t
timer_remaining(timer_t timer)
{
	uint64_t cur_time = timer_current_time();
	switch (timer->state) {
	case timer_oneshot_e:
		if (timer->wakeup_time > cur_time) 
			return timer->wakeup_time - cur_time;
		else
			return -1;
	case timer_periodic_e:
		return (timer->wakeup_time - cur_time) % timer->period;
	case timer_cancelled_e:
		return -1;
	}

	return 1; /* Stupid gcc! */
}

uint64_t
timer_current_time(void)
{
	return timer__current_time(SESSION()->timer_obj->server, NULL);
}

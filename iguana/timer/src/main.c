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
  Created: Tue Nov  2 2004 
*/
/*
  Comments:

  This basically comes down to implementing a priority queue. The is a lot
  of literature on various types of priority queues. One that looks good is:

    Calendar Queues: a fast O(1) priority queue implementation for the
    simulation event set problem (http://portal.acm.org/citation.cfm?id=63045)

  It seems that the data structure that should be used will (obviously)
  depend on the type of events being added.
*/

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include <l4/ipc.h>
#include <l4/thread.h>
#include <l4/kdebug.h>

#include <iguana/hardware.h>
#include <iguana/memsection.h>
#include <iguana/thread.h>
#include <iguana/session.h>
#include <iguana/object.h>
#include <iguana/pd.h>

#include <driver.h>
#include <driver/driver_ops.h>
#include <driver/timer_ops.h>

#include <cb.h>
#include <range_fl.h>

#include <interfaces/timer_server.h>

#define IRQ_LABEL (((~(0UL)) << 20) >> 16) /* This should be somewhere better */

extern struct driver TIMER_DRIVER;

extern void * __callback_buffer;
struct cb_get_handle *iguana_cb_handle;

struct timer_service;

struct driver * global_device;
struct timer_service *global_timer_service;

#define TIMER_ONESHOT  1
#define TIMER_ABSOLUTE 2
#define TIMER_PERIODIC 4

enum timer_states { timer_periodic_e, timer_oneshot_e, timer_cancelled_e };

struct timer {
	struct timer *next;
	struct timer *prev;
	struct timer_service *timer_service;
	uint64_t timeout;
	int flags;
	L4_ThreadId_t thread;
	uintptr_t mask;
	enum timer_states state;
	uint64_t period;
};

struct timer_service {
	struct timer *active;
	struct timer *active_end;
	struct timer *inactive;
	struct driver *device;
};

#ifdef ENABLE_PM_THREAD
uintptr_t pm_stack[1000];
thread_ref_t pm_thread;

static void
power_management_thread(void)
{
	uint64_t last_timeout = 0;
	while(1) {
		uint64_t next_timeout;
		if (global_timer_service->active) {
			next_timeout = global_timer_service->active->timeout;
		} else {
			next_timeout = 0;
		}
		if (next_timeout != last_timeout) {
			last_timeout = next_timeout;
#if 0
			if (last_timeout != 0) {
				printf("   ====> PowerMgt: next wakeup .. %" PRId64 " <====\n",
					last_timeout - timer_current_time(global_device));
			} else {
				printf("   ====> PowerMgt: no wakups <====\n");
			}
#endif
		}
	}
}
#endif

int
main(int argc, char **argv)
{
	struct driver_ops *ops;
	ops = TIMER_DRIVER.ops.d_ops;

	iguana_cb_handle = cb_attach(__callback_buffer);

#ifdef ENABLE_PM_THREAD
	{
	L4_ThreadId_t unused;
	pm_thread = thread_create_priority(1, &unused);
	L4_KDB_SetThreadName(unused, "PwrMgmt");
	}
#endif
	device_server();
	assert(!"Should reach here\n");

	return 0;
}

IDL4_INLINE static objref_t
device_create(CORBA_Object _caller, const objref_t driver, idl4_server_environment *_env)
{
	struct driver_ops *ops;
	struct timer_service *timer_service;
	memsection_ref_t memsection;
	thread_ref_t myself, unused;

	ops = TIMER_DRIVER.ops.d_ops;
	
	/* Let us actually allocate the backed memory.. */
	
	global_timer_service = timer_service = malloc(sizeof(struct timer_service));

#ifdef ENABLE_PM_THREAD
	thread_start(pm_thread, (uintptr_t) power_management_thread,
		     (uintptr_t) &pm_stack[1000-1]);
#endif

	if (timer_service == NULL) {
		return 0;
	}
	timer_service->active = timer_service->active_end = NULL;
	timer_service->inactive = NULL;
	global_device = timer_service->device = ops->setup(0, NULL, NULL, NULL);

	if (timer_service->device == NULL) {
		free(timer_service);
		return 0;
	}
	
	driver_enable(timer_service->device);

	memsection = memsection_lookup((objref_t) timer_service, &unused);
	myself = thread_id(L4_Myself());
	memsection_register_server(memsection, myself);

	return (objref_t) timer_service;
}


IDL4_PUBLISH_DEVICE_CREATE(device_create);
void *device_vtable[DEVICE_DEFAULT_VTABLE_SIZE] = DEVICE_DEFAULT_VTABLE;
void device_discard(void) { assert(!"device discard called"); }

#if 0
static void
debug_active(struct timer *timer)
{
	struct timer_service *timer_service = timer->timer_service;
	struct timer *next;
	for(next = timer_service->active; next != NULL; next = next->next) {
		printf("%" PRId64 " (%p) -- ", next->timeout, next);
	}
	printf("\n");
}
#endif

static void
delete_inactive(struct timer *timer)
{
	struct timer_service *timer_service = timer->timer_service;
	if (timer->next) {
		timer->next->prev = timer->prev;
	}

	if (timer->prev) {
		timer->prev->next = timer->next;
	}

	if (timer_service->inactive == timer) {
		timer_service->inactive = timer->next;
	}
}

static void
insert_inactive(struct timer *timer)
{
	struct timer_service *timer_service = timer->timer_service;
	if (timer_service->inactive == NULL) {
		timer_service->inactive = timer;
		timer->next = timer->prev = NULL;
	} else {
		timer_service->inactive->prev = timer;
		timer->next = timer_service->inactive;
		timer->prev = NULL;
		timer_service->inactive = timer;
	}
}

static bool
make_active(struct timer *timer) 
{
	struct timer_service *timer_service;
	bool in_front = false;
	assert(timer);

	timer_service = timer->timer_service;
	assert(timer_service);

	 /* If LL head is not null, then active_end must be non null
	    else active_end must be null */
	assert((timer->timer_service->active != NULL) ?
	       (timer->timer_service->active_end != NULL) :
	       (timer->timer_service->active_end == NULL));

	/* Remove from inactive */
	if (timer->next != NULL) {
		timer->next->prev = timer->prev;
	}
	if (timer->prev != NULL) {
		timer->prev->next = timer->next;
	}
	if (timer_service->inactive == timer) {
		timer->timer_service->inactive = timer->next;
	}

	/* Insert into active list */
	if (timer_service->active_end == NULL) {
		assert(timer_service->active == NULL);
		/* We can just insert! */
		timer_service->active = timer;
		timer_service->active_end = timer;
		timer->prev = timer->next = NULL;
		in_front = true;
	} else if (timer->timeout < timer_service->active->timeout) {
		/* We must insert at the front -- this is the next wakeup! */
		timer_service->active->prev = timer;
		timer->next = timer_service->active;
		timer->prev = NULL;
		timer_service->active = timer;
		in_front = true;
	} else {
		/* We need to insert in an ordered way. Note: This could
		   be O(n), which may be bad depending on exactly how
		   things work */
		struct timer *back = timer_service->active_end;
		while(back->timeout > timer->timeout) {
			back = back->prev;
			assert(back != NULL);
			/* This could only happen if we are next,
			   which we can't be because we already checked
			   that! */
		}
		
		/* Now we insert behind back */
		timer->next = back->next;
		timer->prev = back;
		back->next = timer;
		if (timer->next) {
			timer->next->prev = timer;
		}
		if (timer_service->active_end == back) {
			timer_service->active_end = timer;
		}
		in_front = false;
	}

	assert(timer->next ? timer->next->prev == timer : timer_service->active_end == timer);
	assert(timer->prev ? timer->prev->next == timer : timer_service->active == timer);
	assert(timer->next ? timer->next->timeout >= timer->timeout : timer_service->active_end == timer);
	assert(timer->prev ? timer->prev->timeout <= timer->timeout : timer_service->active == timer);

	return in_front;
}

static void
deactivate_timer(struct timer *timer)
{
	if (timer->next) {
		timer->next->prev = timer->prev;
	}

	if (timer->prev) {
		timer->prev->next = timer->next;
	}

	if (timer->timer_service->active_end == timer) {
		timer->timer_service->active_end = timer->prev;
	}

	if (timer->timer_service->active == timer) {
		timer->timer_service->active = timer->next;
	}

	/* Put in the inactive */
	timer->state = timer_cancelled_e;

	/* If LL head is not null, then active_end must be non null
	   else active_end must be null */
	assert((timer->timer_service->active != NULL) ? 
			(timer->timer_service->active_end != NULL) : 
			(timer->timer_service->active_end == NULL));

	insert_inactive(timer);
}

L4_ThreadId_t recv_thread;
static void
timer_callback(callback_data_t data, int ignored, struct data *ignored_data, uintptr_t key)
{
	struct timer *timer = (struct timer *) key;
	struct timer *next_timer;
	struct driver *device = timer->timer_service->device;
	do {
		L4_Notify(timer->thread, timer->mask);

		/* The timer should be at the start of the list! */
		assert(timer->timer_service->active == timer);
		assert(timer->prev == NULL);

		if (timer->state == timer_oneshot_e) {
			/* Remove timer from active list */
			next_timer = timer->next;
			deactivate_timer(timer);
		} else {
			/* Period timer -- needs to be put straight back in the active queue */
			timer->timeout += timer->period;
			if (timer->next == NULL || timer->next->timeout > timer->timeout) {
				/* Special case -- we are still at the front of the list
				   so we don't need to do very much...
				   XXX: Periodic timers should cost a lot of quota, this could
				   easily DOS a system if someone request a short periodic timeout
				*/
				next_timer = timer;
			} else {
				/* Ok, so we are not going to be at the front this time */
				struct timer *back = timer->timer_service->active_end;

				next_timer = timer->next;
				timer->timer_service->active = next_timer;
				next_timer->prev = NULL;
				while(back->timeout > timer->timeout) {
					back = back->prev;
					assert(back != NULL);
					/* This could only happen if we are next,
					   which we can't be because we already checked
					   that! */
				}
				/* Now we insert behind back */
				timer->next = back->next;
				timer->prev = back;
				back->next = timer;
				if (timer->next) {
					timer->next->prev = timer;
				}
				if (timer->timer_service->active_end == back) {
					timer->timer_service->active_end = timer;
				}
			}
		}

		timer = NULL;
		if (next_timer) {
			if (next_timer->timeout > timer_current_time(device)) {
				/* We need to add the next timer */
				timer_timeout(device, next_timer->timeout, timer_callback, 0, (uintptr_t) next_timer);
			} else {
				timer = next_timer;
			}
		}
	} while(timer);
}


/* Create a new timer object */
IDL4_INLINE static cap_t
timer_server_create(CORBA_Object _caller, objref_t timer_service,
		    const L4_ThreadId_t *thread, uintptr_t mask,
		    idl4_server_environment *_env)
{
	cap_t cap = {{0}, 0};
	struct timer * timer;
	timer = malloc(sizeof(struct timer));

	if (timer == NULL) {
		return cap;
	}

	/* Insert into inactive list */
	timer->timer_service = (struct timer_service *) timer_service;
	timer->state = timer_cancelled_e;
	timer->thread = *thread;
	timer->mask = mask;
	insert_inactive(timer);

	cap.ref.obj = (uintptr_t) timer;
	/* FIXME: set up a password */
	return cap;
}


IDL4_PUBLISH_TIMER_SERVER_CREATE(timer_server_create)
void *timer_server_vtable[TIMER_SERVER_DEFAULT_VTABLE_SIZE] = TIMER_SERVER_DEFAULT_VTABLE;
void timer_server_discard(void) { assert(!"timer server discard called"); }

IDL4_INLINE static int
timer_cancel (CORBA_Object _caller, objref_t timer_obj, idl4_server_environment *_env)
{
	struct timer *timer = (struct timer*) timer_obj;
	struct driver *device = timer->timer_service->device;
	bool is_start = (timer->prev == NULL);
	struct timer *next_timer = timer->next;

	assert(is_start ? timer->timer_service->active == timer : 1);
	assert(next_timer == NULL ? timer->timer_service->active_end == timer : 1);

	/* Inactivate timer */
	deactivate_timer(timer);
	if (is_start) {
		if (next_timer) {
			/* Timeout at next registered time */
			timer_timeout(device, next_timer->timeout, timer_callback, 0, (uintptr_t) next_timer);
		} else {
			/* Never timeout -- nothing left in list */
			timer_timeout(device, -1, NULL, 0, (uintptr_t) 0);
		}
	}

	return 0;
}

IDL4_INLINE static uint64_t
timer_request (CORBA_Object _caller, objref_t timer_obj,
			      uint64_t time, int flags,
			      idl4_server_environment *_env)
{
	struct timer *timer = (struct timer*) timer_obj;
	struct driver *device = timer->timer_service->device;
	uint64_t abs_time;
	bool is_earliest;

	if (timer->state != timer_cancelled_e) {
		/* We need to cancel the timer first */
		timer_cancel(_caller, timer_obj, _env);
	}

	abs_time = time;

	if (!(flags & TIMER_ABSOLUTE)) {
		abs_time += timer_current_time(device);
	}

	if (flags & TIMER_PERIODIC) {
		if (flags & TIMER_ABSOLUTE) {
			return -1;
		}
		timer->state = timer_periodic_e;
		timer->period = time;
	} else {
		timer->state = timer_oneshot_e;
	}

	timer->timeout = abs_time;
	is_earliest = make_active(timer);
	//debug_active(timer);

	/* Set a request for that point in time */
	if (is_earliest) {
		timer_timeout(device, abs_time, timer_callback, 0, (uintptr_t) timer);
	}

	return abs_time;
}


IDL4_INLINE static uint64_t
current_time (CORBA_Object _caller, idl4_server_environment *_env)
{
	return timer_current_time(global_timer_service->device);
}


IDL4_INLINE static int
timer_delete (CORBA_Object _caller, objref_t timer_obj, idl4_server_environment *_env)
{
	/* First it must be cancelled */
	struct timer *timer = (struct timer*) timer_obj;

	if (timer->state != timer_cancelled_e) {
		/* We need to cancel the timer first */
		timer_cancel(_caller, timer_obj, _env);
	}

	/* Now we can remove from inactive */
	delete_inactive(timer);
	free(timer);

	return 0;
}

IDL4_PUBLISH_TIMER__REQUEST(timer_request)
IDL4_PUBLISH_TIMER__CURRENT_TIME(current_time)
IDL4_PUBLISH_TIMER__CANCEL(timer_cancel)
IDL4_PUBLISH_TIMER__DELETE(timer_delete)

void *timer__vtable[TIMER__DEFAULT_VTABLE_SIZE] = TIMER__DEFAULT_VTABLE;
void timer__discard(void) { assert(!"timer discard called"); }


void
device_server(void)
{
	L4_ThreadId_t partner;
	L4_MsgTag_t msgtag;
	idl4_msgbuf_t msgbuf;
	long cnt;
	uintptr_t *size;

	partner = L4_nilthread;
	msgtag.raw = 0;
	cnt = 0;

	while(1) {
		/* Now check async queues -- we check this everytime, which
		   is a bit silly, would be nice if we could detect a failed
		   ipc to us */
		size = cb_get(iguana_cb_handle, sizeof(uintptr_t));
		if (size) {
			//uintptr_t *data = 
			cb_get(iguana_cb_handle, *size);
			//printf("Got stuff: %" PRIdPTR "\n", *size);
			//printf("Got stuff: %" PRIxPTR " %" PRIxPTR "\n", data[0], data[1]);
		}
		/* Wait for message */


		idl4_msgbuf_sync(&msgbuf);
		idl4_reply_and_wait(&partner, &msgtag, &msgbuf, &cnt);

		if (idl4_is_error(&msgtag)) {
			printf("timer:device_server(%d) Error %"PRIxPTR" -- replying_to: %"PRIxPTR"\n", __LINE__, (unsigned int)L4_ErrorCode(),
			       (unsigned int)partner.raw);
			partner = L4_nilthread;
			msgtag.raw = 0;
			cnt = 0;
			continue;
		}
		
		if (msgtag.X.label == IRQ_LABEL) {
			driver_interrupt(global_device); /* FIXME: */
			continue;
		}
		switch (magpie_get_interface_bigid(&msgbuf)) {
		case 37:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt,
					     device_vtable[idl4_get_function_id(&msgtag) & DEVICE_FID_MASK]);
			break;
		case 40:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt,
					     timer_server_vtable[idl4_get_function_id(&msgtag) & TIMER_SERVER_FID_MASK]);
			break;
		case 41:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt,
					     timer__vtable[idl4_get_function_id(&msgtag) & TIMER__FID_MASK]);
			break;
		default:
			printf("timer: device_server: Bad label! (0x%lx)\n", magpie_get_interface_bigid(&msgbuf));
			partner = L4_nilthread;
		}
	}
}

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
#include <driver/character_ops.h>

#include <cb.h>
#include <range_fl.h>

#include <interfaces/serial_server.h>

#define IRQ_LABEL (((~(0UL)) << 20) >> 16)

struct driver_info {
	int waiting_for_device;
	int waiting_for_read;
	rfl_t read_buffers;
	objref_t sink;
};

extern struct driver SERIAL_DRIVER;
extern void _start;

struct cb_get_handle *cbg;
struct driver *device;

static struct driver_info *global_drv_info;

static void read_callback(callback_data_t data, int, struct data *, uintptr_t key);
static void write_callback(callback_data_t data, int, struct data *, uintptr_t key);

extern void * __callback_buffer;
struct cb_get_handle *iguana_cb_handle;

int
main(int argc, char **argv)
{
	struct driver_ops *ops;
	ops = SERIAL_DRIVER.ops.d_ops;

	iguana_cb_handle = cb_attach(__callback_buffer);

	device_server();
	assert(!"Should reach here\n");

	return 0;
}

IDL4_INLINE static objref_t
device_create(CORBA_Object _caller, const objref_t driver, idl4_server_environment *_env)
{
	struct driver_info *drv_info;
	bus_space_t space;
	uintptr_t space_ptr;
	uintptr_t memory;

	struct driver_ops *ops;
	ops = SERIAL_DRIVER.ops.d_ops;

	global_drv_info = drv_info = malloc(sizeof(struct driver_info));

	/* Let us actually allocate the backed memory.. */
	memory = memsection_create_user(0x1000, &space_ptr);
	space = (char*) space_ptr;

	printf("Backing memory section: %p\n", (void *)space_ptr);
#ifdef ARCH_ARM
	{
		int r;
		/* FIXME: These should be passed into the server properly */
		r = hardware_back_memsection(memory, 0x80050000, 1);
		printf("Hardware back memssection returned: %d\n", r);
		hardware_register_interrupt(L4_Myself(), 17);
	}
#endif
	printf("Backed memory section\n");
	device = ops->setup(1, &space, NULL, NULL);
	printf("Driver enable\n");
	driver_enable(device);
	printf("Done driver enable\n");
	drv_info->waiting_for_device = 0;
	drv_info->waiting_for_read = 0;

	drv_info->read_buffers = rfl_new();
	{
		char *buffer;
		struct data *data;
		data = malloc(sizeof(struct data));
		buffer = malloc(5000);
		rfl_insert_range(drv_info->read_buffers, (uintptr_t) buffer, (uintptr_t) buffer+4999);
		data->data = (void*) rfl_alloc_first(drv_info->read_buffers, &data->length);
		data->length--; /* Allow for '\0' */
		data->xferred = 0;
		char_read(device, 1, data, read_callback, NULL,
			  (uintptr_t) data);

	}
	{
		memsection_ref_t memsection;
		thread_ref_t unused;
		thread_ref_t myself;
		memsection = memsection_lookup((objref_t) drv_info, &unused);
		myself = thread_id(L4_Myself());
		memsection_register_server(memsection, myself);
	}
	return (objref_t) drv_info;
}

IDL4_PUBLISH_DEVICE_CREATE(device_create);
void *device_vtable[DEVICE_DEFAULT_VTABLE_SIZE] = DEVICE_DEFAULT_VTABLE;
void device_discard(void) {}

CORBA_Object global_client;

/* Interface stream */
IDL4_INLINE static uintptr_t
stream_write(CORBA_Object _caller, const objref_t stream_obj, 
	     const uintptr_t length, const uintptr_t data, 
	     idl4_server_environment *_env)
{
	uintptr_t __retval = 0;
	struct data *c_data;
	/* implementation of stream::write */
	c_data = malloc(sizeof(struct data));
	c_data->data = (void*) data;
	c_data->length = length;
	c_data->xferred = 0;
	global_client = _caller;

	/* FIXME: Add to queue */
	char_write(device, 1, c_data, write_callback, NULL, (uintptr_t) c_data);

	idl4_set_no_response(_env);
	return __retval;
}

static object_t *sink_instance = NULL;

/* Interface stream */
IDL4_INLINE static uintptr_t
stream_set_sink(CORBA_Object _caller, const objref_t stream_obj, 
		const objref_t sink,
		idl4_server_environment *_env)
{
	uintptr_t __retval = 0;
	sink_instance = object_get_async_interface(sink);
	/* Setup session */
	object_print(sink_instance);
	global_drv_info->sink = sink;
	return __retval;
}

IDL4_PUBLISH_STREAM_WRITE(stream_write);
IDL4_PUBLISH_STREAM_SET_SINK(stream_set_sink);
void *stream_vtable[STREAM_DEFAULT_VTABLE_SIZE] = STREAM_DEFAULT_VTABLE;
void stream_discard(void) {}

int irq_count = 0;

static void
read_callback(callback_data_t cb_data, int seqc, struct data *seqv, 
	      uintptr_t key)
{
	L4_Msg_t msg;
	uintptr_t *size;
	uintptr_t *addr;

	seqv->data[seqv->xferred] = '\0';
	//printf("%s %" PRIxPTR, seqv->data, global_drv_info->sink);
	if (sink_instance == NULL) {
		/* No sink... we just drop on the floor */
		global_drv_info->waiting_for_read = 0;
		free(seqv);
		return;
	}

	size = cb_alloc(sink_instance->call_cb, sizeof(uintptr_t));
	assert(size != NULL);
	*size = 3 * sizeof(uintptr_t);
	addr = cb_alloc(sink_instance->call_cb, *size);
	addr[0] = 0x69;
	addr[1] = (uintptr_t) seqv->data;
	addr[2] = seqv->xferred;
	cb_sync_alloc(sink_instance->call_cb);

	
	L4_MsgClear(&msg);
	L4_MsgLoad(&msg);
	//L4_Send_Timeout(sink_instance->server, L4_ZeroTime);

	/* Return unused to the pool */
	rfl_insert_range(global_drv_info->read_buffers, (uintptr_t) seqv->data + seqv->xferred, 
			 (uintptr_t) seqv->data + seqv->length);
	/* Indicate we can have more reads */
	global_drv_info->waiting_for_read = 1;
	free(seqv);
}

static void
write_callback(callback_data_t data, int seqc, struct data *seqv, 
	       uintptr_t key)
{
	uintptr_t retval = seqv->xferred;
	assert(key != 0);
	free((void*) key);
	stream_write_reply(global_client, retval);
}

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
		/* Process our own work queues */
		/* deferred_work(); */
		if (global_drv_info && global_drv_info->waiting_for_read) {
			struct data *data;
			global_drv_info->waiting_for_read = 0;
			data = malloc(sizeof(struct data));
			assert(data != NULL);
			data->data = (void*) rfl_alloc_first(global_drv_info->read_buffers, &data->length);
			if ((uintptr_t) data->data != -1) {
				data->length--;
				data->xferred = 0;
				char_read(device, 1, data, read_callback, NULL,
					  (uintptr_t) data);
			} else {
				printf("Couldn't allocate anymore!!!\n");
				free(data);
			}
		}

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
			printf("Error %lx\n", L4_ErrorCode());
			partner = L4_nilthread;
			msgtag.raw = 0;
			cnt = 0;
			continue;
		}
		
		if (msgtag.X.label == IRQ_LABEL) {
			driver_interrupt(device);
			continue;
		}

		switch (magpie_get_interface_bigid(&msgbuf)) {
		case 37:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
					     device_vtable[idl4_get_function_id(&msgtag) & DEVICE_FID_MASK]);
			break;
		case 38:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
					     stream_vtable[idl4_get_function_id(&msgtag) & STREAM_FID_MASK]);
			break;
		default:
			printf("serial: device_server: Bad label! (0x%lx)\n", magpie_get_interface_bigid(&msgbuf));
			L4_KDB_Enter("blah");
			partner = L4_nilthread;
		}
	}
}

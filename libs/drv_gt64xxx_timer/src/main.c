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
#include <driver.h>
#include <driver/timer_ops.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <l4/types.h>
#include <l4/ipc.h>
#include <l4/kdebug.h>
#include <iguana/thread.h>

/* Timer specific section */

#include <iguana/memsection.h>  /* memsection_create */
#include <iguana/hardware.h>    /* hardware_back_memsection() */
#include "gt64xxx.h"

uintptr_t GT_TIMERS_VADDR;

static int
map_gt64xxx_timer(void)
{
	size_t length = 0x1000;
	uintptr_t offset = GT_TIMERS_PHYS; /* physical address of GT timer registers */
	memsection_ref_t ms;
	int r;

	printf("GT64xxx timer driver starting...\n");

	ms = memsection_create_user(length, &GT_TIMERS_VADDR);

	if (ms == 0)
	    return 0;

	r = hardware_back_memsection(ms, offset, L4_UncachedMemory);
	if (r != 0)
	{
		printf("Error backing memory section: (%d)\n", r);
		return 0;
	}
	return 1;
}

/* Driver specific section */

static void *setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf);
static void  enable(void *device);
static void  cleanup(void *device);
static void  interrupt(void *device);
static int timeout(void *device, uint64_t time, callback_t callback, 
		   callback_data_t callback_data, uintptr_t key);
static uint64_t current_time(void *device);

struct gt64xxx_dev {
	struct driver_instance generic;
	int enabled;
};
		
static struct timer_ops ops = {
	/* Driver ops */
	{ setup,
	  enable,
	  cleanup,
	  interrupt },
	/* Timer ops */
	timeout,
	current_time
};

struct driver drv_gt64xxx_timer = 
{
	.name = "GT64xxx timer",
	.class = timer_device_e,
	.ops.t_ops = &ops
};

L4_ThreadId_t irq_tid, main_tid, handler_tid;

static void *
setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf)
{
	struct gt64xxx_dev *drv;
	L4_Word_t irq = IRQ_GT;

	if (!map_gt64xxx_timer())
	    return NULL;

	drv = malloc(sizeof(struct gt64xxx_dev));
	if (drv == 0) return 0;
	memset(drv, 0, sizeof(*drv));

	drv->generic.classp = &drv_gt64xxx_timer;

	/* Create a thread */
	main_tid = L4_Myself();
	/* benjl: This priority setting is a hack! */
	thread_create_priority(241, &handler_tid);
	L4_KDB_SetThreadName(handler_tid, "tmr_irq");

	/* Register timer interrupt */
	hardware_register_interrupt(handler_tid, irq);
	irq_tid = L4_GlobalId(irq, 1);

	/* Start the timer ticks */
	*GT_TIMER_CONTROL = (0ul<<24);
	*GT_TIMER_0 = 0xffffffff;
	*GT_TIMER_CONTROL = (1ul<<24);

	/* Enable timer0 interrupt */
	gt_write(GT_INTERRUPT_MASK, 1<<8);
	timeout(NULL, -1, NULL, NULL, 0);

	return drv;
}

static void
enable(void *device)
{
}
static void
cleanup(void *device)
{
}

callback_t timer_callback;
callback_data_t timer_data;
uintptr_t timer_key;
static int in_interrupt = 0;

static void
interrupt(void *device)
{
	in_interrupt = 1;
	timer_callback(timer_data, 0, NULL, timer_key);
	in_interrupt = 0;
}

uintptr_t irq_stack[200];

#define IRQ_LABEL (((~(0UL)) << 20) >> 16) /* This should be somewhere better */

uint64_t next_timeout, ticks = 0;
uint32_t count_from = 0xffffffff;

static void
sleep_timeout(void)
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

	uint32_t value = gt_read(GT_TIMER_0);

	ticks += count_from - value;

	while(1) {
		if (next_timeout != -1) {
			next_timeout = US_TO_TICKS(next_timeout);

			if (next_timeout > ticks)
			{
				next_timeout -= ticks;

loop:
				count_from = next_timeout >= (0xffffffff) ? (0xffffffff) : next_timeout;
				
				/* Setup the timer */
				*GT_TIMER_CONTROL = (0ul<<24);
				gt_write(GT_TIMER_0, count_from);
				*GT_TIMER_CONTROL = (1ul<<24);

				/* Wait timeout */
				tag = L4_Receive(irq_tid);
				assert(L4_IpcSucceeded(tag));

				ticks += count_from;
				*GT_INTERRUPT_CAUSE = 0;

				/* Ack the L4 interrupt */
				tag = L4_Reply(irq_tid);
				assert(L4_IpcSucceeded(tag));

				if (count_from == 0xffffffff)
				{
					next_timeout -= 0xffffffff;
					if (next_timeout)
						goto loop;
				}

				/* Reset the timer downcount */
				*GT_TIMER_CONTROL = (0ul<<24);
				*GT_TIMER_0 = 0xffffffff;
				*GT_TIMER_CONTROL = (1ul<<24);
				count_from = 0xffffffff;
			}
		} else {
			while (1) {
				/* Wait interrupt, timer stops at 0 */
				tag = L4_Receive(irq_tid);
				assert(L4_IpcSucceeded(tag));

				ticks += count_from;
				*GT_INTERRUPT_CAUSE = 0;
				
				/* Ack the L4 interrupt */
				tag = L4_Reply(irq_tid);
				assert(L4_IpcSucceeded(tag));
			}
		}
		next_timeout = -1;
		L4_MsgClear(&msg);
		L4_Set_Label(&msg.tag, IRQ_LABEL);
		L4_MsgLoad(&msg);
		L4_Call(main_tid);
	}
	assert(!"Shouldn't get here\n");
}


static int 
timeout(void *device, uint64_t time, callback_t callback, callback_data_t callback_data, uintptr_t key)
{
	L4_Word_t dummy;
	L4_ThreadId_t dummy_id;
	next_timeout = time;
	timer_callback = callback;
	timer_data = callback_data;
	timer_key = key;

	/* Exreg */
	if (in_interrupt == 0) {
		L4_ExchangeRegisters(handler_tid, L4_ExReg_sp_ip | L4_ExReg_Resume | L4_ExReg_AbortIPC | L4_ExReg_pager, 
				     (uintptr_t) &irq_stack[200-1], (uintptr_t) sleep_timeout, 
				     0, 0, L4_Pager(), &dummy, &dummy, &dummy,
				     &dummy, &dummy, &dummy_id);
	}
	return 0;
}

static uint64_t
current_time(void *device)
{
	/* Get the counter value */
	uint32_t value = gt_read(GT_TIMER_0);

	value = count_from - value;

	return TICKS_TO_US(ticks + value);
}


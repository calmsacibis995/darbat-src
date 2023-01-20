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
#include "sa1100.h"

uintptr_t SA1100_TIMERS_VADDR;

volatile uint32_t timer_high32 = 0;

static int
map_sa1100_timer(void)
{
	size_t length = 0x1000;
	uintptr_t offset = SA1100_TIMERS_PHYS; /* physical address of SA1100 timer registers */
	memsection_ref_t ms;
	int r;

	printf("SA1100 OS Timer driver starting...\n");

	ms = memsection_create_user(length, &SA1100_TIMERS_VADDR);

	if (ms == 0)
	    return 0;

	r = hardware_back_memsection(ms, offset, MEM_NORMAL);
	if (r != 0)
	{
		printf("Error backing memory section: (%d)\n", r);
		return 0;
	}
	return 1;
}

static inline uint64_t current_ticks(void);
static void timer_wrap_handler(void);
uintptr_t wrap_stack[100];

/* Driver specific section */

static void *setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf);
static void  enable(void *device);
static void  cleanup(void *device);
static void  interrupt(void *device);
static int timeout(void *device, uint64_t time, callback_t callback, 
		   callback_data_t callback_data, uintptr_t key);
static uint64_t current_time(void *device);

struct sa1100_dev {
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

struct driver drv_sa1100_timer = 
{
	.name = "SA1100 timer",
	.class = timer_device_e,
	.ops.t_ops = &ops
};

L4_ThreadId_t irq_tid, main_tid, handler_tid, wrap_tid, wrap_irq_tid;

static void
*setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf)
{
	struct sa1100_dev *drv;
	L4_Word_t irq = IRQ_OSTMR2;

	if (!map_sa1100_timer())
	    return NULL;

	drv = malloc(sizeof(struct sa1100_dev));
	if (drv == 0) return 0;
	memset(drv, 0, sizeof(*drv));

	drv->generic.classp = &drv_sa1100_timer;
	/* Create a thread */

	main_tid = L4_Myself();
	/* benjl: This priority setting is a hack! */
	thread_create_priority(241, &handler_tid);
	L4_KDB_SetThreadName(handler_tid, "tmr_irq");

	/* Register timer interrupt */
	hardware_register_interrupt(handler_tid, irq);
	irq_tid = L4_GlobalId(irq, 1);

	/* Register timer wrap interrupt */
	irq = IRQ_OSTMR1;
	thread_create_priority(242, &wrap_tid);	/* must be higher priority than handler_tid */
	L4_KDB_SetThreadName(wrap_tid, "tmr_wrap_irq");

	/* Register timer interrupt */
	hardware_register_interrupt(wrap_tid, irq);
	wrap_irq_tid = L4_GlobalId(irq, 1);

	L4_Word_t dummy;
	L4_ThreadId_t dummy_id;
	/* Start wrap handler */
	L4_ExchangeRegisters(wrap_tid, L4_ExReg_sp_ip | L4_ExReg_Resume | L4_ExReg_AbortIPC | L4_ExReg_pager, 
		(uintptr_t) &wrap_stack[100-1], (uintptr_t) timer_wrap_handler, 
		0, 0, L4_Pager(), &dummy, &dummy, &dummy,
		&dummy, &dummy, &dummy_id);

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

uint64_t next_timeout;

static inline uint64_t
current_ticks()
{
	uint64_t ticks;
	uint32_t offset;
	
	do {
	    offset = timer_high32;
	    ticks = SA1100_OS_TIMER_OSCR;
	} while (offset != timer_high32);

	return ticks + ((uint64_t)offset << 32);
}

static void
sleep_timeout(void)
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;
	int64_t sleep_ticks;

	while(1) {
		if (next_timeout != -1) {
			/* Converstion to ticks from us */
			next_timeout = US_TO_TICKS(next_timeout);

			uint64_t ref_ticks = current_ticks();
			sleep_ticks = ((int64_t)next_timeout-(int64_t)ref_ticks);
			uint64_t match_val = ref_ticks + sleep_ticks;

			/* Set match register */
			SA1100_OS_TIMER_OSMR2 = (uint32_t)(match_val);
			/* Clear the interrupt (if it was pending) */
			SA1100_OS_TIMER_OSSR = 0x04;

			ref_ticks = current_ticks();	/* Re-read timer value */

			assert(sleep_ticks < (1ll<<32));  // XXX FIXME

			if (sleep_ticks > 0) {
				if (ref_ticks < match_val) {
					SA1100_OS_TIMER_OIER = 0x07;	/* Enabled = 0, 1, 2. Disabled = 3 */

					/* Wait timeout */
					tag = L4_Receive(irq_tid);
					assert(L4_IpcSucceeded(tag));

					/* Clear timer interrupt mask */
					SA1100_OS_TIMER_OIER = 0x03;	/* Enabled = 0, 1. Disabled = 2, 3 */

					/* Ack the L4 interrupt */
					tag = L4_Reply(irq_tid);
					assert(L4_IpcSucceeded(tag));
				}
			}
		} else {
			/* No timeout, so sleep forever */
			L4_WaitForever();
		}
		next_timeout = -1;
		L4_MsgClear(&msg);
		L4_Set_Label(&msg.tag, IRQ_LABEL);
		L4_MsgLoad(&msg);
		L4_Call(main_tid);
	}
	assert(!"Shouldn't get here\n");
}


static void
timer_wrap_handler(void)
{
	L4_MsgTag_t tag;
	printf("SA1100 wrap handler installed\n");

	SA1100_OS_TIMER_OSMR1 = 0x00;	/* Set match value on wrap around */
	SA1100_OS_TIMER_OSSR = 0x02;	/* Clear pending interrupts */
	SA1100_OS_TIMER_OIER = 0x03;	/* Enabled = 0, 1. Disabled = 2, 3 */

	/* Wait first wrap */
	tag = L4_Receive(wrap_irq_tid);
	assert(L4_IpcSucceeded(tag));

	while(1) {
	    /* Increment the high 32-bits of the time */
	    timer_high32++;
	    SA1100_OS_TIMER_OSSR = 0x02;

	    /* Keep handling the L4 interrupt */
	    tag = L4_Call(wrap_irq_tid);
	    assert(L4_IpcSucceeded(tag));
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

	/* Set timer interrupt mask */
	SA1100_OS_TIMER_OIER = 0x03;	/* Enabled = 0, 1. Disabled = 2, 3 */
	/* Clear pending interrupt */
	SA1100_OS_TIMER_OSSR = 0x04;

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
	uint64_t time = current_ticks();

	return TICKS_TO_US(time);
}


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
 Authors: Ben Leslie, David Snowdown
*/
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <driver.h>
#include <driver/character_ops.h>

#include "uart.reg.h"

enum parity { PARITY_NONE, PARITY_EVEN, PARITY_ODD };
#define BAUD_RATE_CONSTANT 3686400 /* Frequency of the crystal on the SA1100 */

#define DEFAULT_BAUD 115200
#define DEFAULT_SIZE 8
#define DEFAULT_PARITY PARITY_NONE
#define DEFAULT_STOP 1

struct sa1100_uart {
	struct driver_instance generic;
	int enabled;
	int xmit_fifo;
	struct uart uart;

	/* Current transmit */
	int txen;
	int writec, writec_init;
	struct data *writev, *writev_init;
	callback_t write_callback;
	callback_data_t write_cb_data;
	uintptr_t write_key;
	/* Current recieve */
	int rxen;
	int readc, readc_init;
	struct data *readv, *readv_init;
	callback_t read_callback;
	callback_data_t read_cb_data;
	uintptr_t read_key;
};

static void *setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf);
static void enable(void *device);
static void interrupt(void *device);
static void cleanup(void *device);
static int write(void *device, int seqc, struct data *seqv, 
		 callback_t callback, callback_data_t callback_data,
		 uintptr_t key);
static int read(void *device, int seqc, struct data *seqv, 
		callback_t callback, callback_data_t callback_data,
		uintptr_t key);

int serial_set_params(struct sa1100_uart *self, 
		      unsigned baud,
		      int data_size, /* Seven or eight bits */
		      enum parity parity,
		      int stop_bits /* One or two stop bits */
		      );



static struct character_ops ops = {
	/* Driver ops */
	{ setup,
	  enable,
	  cleanup,
	  interrupt },
	/* Character ops */
	write,
	read
};

struct driver drv_sa1100_uart = 
{
	.name = "sa1100 UART",
	.class = character_device,
	.ops.c_ops = &ops
};

static void *
setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf)
{
	struct sa1100_uart *drv;

	drv = malloc(sizeof(struct sa1100_uart));
	if (drv == 0) return 0;
	memset(drv, 0, sizeof *drv);

	drv->generic.classp = &drv_sa1100_uart;
	drv->uart.bus = spacev[0];

	drv->txen = 0;
	drv->writec = 0;

	drv->rxen = 0;
	drv->readc = 0;

	serial_set_params(drv, DEFAULT_BAUD, DEFAULT_SIZE, DEFAULT_PARITY, 
			  DEFAULT_STOP);
	return drv;
}

int 
serial_set_params(struct sa1100_uart *self, 
		  unsigned baud,
		  int data_size, /* Seven or eight bits */
		  enum parity parity,
		  int stop_bits /* One or two stop bits */
		  )
{
	int brd = BAUD_RATE_CONSTANT / (16 * baud) - 1;
	
	if (data_size < 7 || data_size > 8) {
		/* Invalid data_size */
		return -1;
	}

	if (stop_bits < 1 || stop_bits > 2) {
		/* Invalid # of stop bits */
		return -1;
	}

	uart_pe_set(parity != PARITY_NONE);
	uart_oes_set(parity == PARITY_EVEN);
	uart_sbs_set(stop_bits == 1);
	uart_dss_set(data_size == 7);

	uart_brd_hi_set((brd >> 8) & 0xF);
	uart_brd_lo_set(brd & 0xFF);

	//uart_brd_set(brd);

	return 0;
}

static void 
enable(void *device)
{
	struct sa1100_uart *self = device;
	self->enabled = 1;
}

static void
cleanup(void *device)
{
	printf("Cleanup %p\n", device);
}

static int
do_write(struct sa1100_uart *self)
{
	int max_at_once = 4;
	while (uart_tnf_get() && self->writec && max_at_once--) {
		uart_data_set(self->writev->data[self->writev->xferred]);
		self->writev->xferred++;

		/* End of this data item */
		if (self->writev->xferred == self->writev->length) {
			self->writev++;
			self->writec--;
		}
	}

	if (self->writec == 0) {
		self->write_callback(self->write_cb_data, self->writec_init, 
				    self->writev_init, self->write_key);
		return 0; /* Data written */
	}
	return 1; /* Data still pending */
}

static int
do_read(struct sa1100_uart *self)
{
	int got_some = 0;
	while (uart_rne_get() && self->readc) {
		got_some = 1;
		self->readv->data[self->readv->xferred] = uart_data_get();
		//printf("foo\n");
		self->readv->xferred++;

		/* End of this data item */
		if (self->readv->xferred >= self->readv->length) {
			self->readv++;
			self->readc--;
		}
	}
	if (got_some) {
		//printf("Doing callback... %d %d %d\n", uart_rne_get(), self->readc, self->readv_init->xferred);
		self->read_callback(self->read_cb_data, self->readc_init, 
				    self->readv_init, self->read_key);
		self->readc = 0;
	} 
	if (self->readc == 0) {
		return 0; /* Data read */
	}
	return 1; /* Data still pending */
}

/* FIXME: dd_dsl.py should generate these.. */
#define uart_tfs self->uart.utsr0.r.tfs
#define uart_rfs self->uart.utsr0.r.rfs
#define uart_rid self->uart.utsr0.r.rid
#define uart_rbb self->uart.utsr0.r.rbb
#define uart_reb self->uart.utsr0.r.reb
#define uart_eif self->uart.utsr0.r.eif

static void
interrupt(void *device)
{
	struct sa1100_uart *self = device;
	uart_utsr0_read();
	if (uart_tfs) {
		if (self->writec == 0) {
			self->txen = 0;
			uart_txe_set(0); /* Disable */
			uart_tie_set(0); /* Disable */
		} else {
			do_write(self);
		}
	} 
	if (uart_rfs || uart_rid) {
		//printf("Read irq\n");
		if (self->readc == 0) {
			//printf("Disable\n");
			self->rxen = 0;
			/* Disable receiver */
			uart_rxe_set(0);
			uart_rie_set(0);
		} else {
			do_read(self);
		}
	}
	if (uart_rbb || uart_reb || uart_eif) {
		printf("Serial driver unhandled..?!\n");
	}
}

static int
write(void *device, int seqc, struct data *seqv, callback_t callback, 
      callback_data_t callback_data, uintptr_t key)
{
	struct sa1100_uart *self = device;
	assert(self->enabled);
	if (! self->txen) {
		self->txen = 1;
		uart_tie_set(1);
		uart_txe_set(1);
	}
	assert(self->writec == 0);
	self->writec = self->writec_init = seqc;
	self->writev = self->writev_init = seqv;
	self->write_callback = callback;
	self->write_cb_data = callback_data;
	self->write_key = key;
	return do_write(self);
}

static int
read(void *device, int seqc, struct data *seqv, callback_t callback, 
     callback_data_t callback_data, uintptr_t key)
{
	struct sa1100_uart *self = device;
	assert(self->enabled);
	if (! self->rxen) {
		self->rxen = 1;
		uart_rie_set(1);
		uart_rxe_set(1);
	}
	assert(self->readc == 0);
	self->readc = self->readc_init = seqc;
	self->readv = self->readv_init = seqv;
	self->read_callback = callback;
	self->read_cb_data = callback_data;
	self->read_key = key;
	return do_read(self);
}

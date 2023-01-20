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
#include <driver/character_ops.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <l4/kdebug.h>

static void *setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf);
static void  enable(void *device);
static void  cleanup(void *device);
static void  interrupt(void *device);
static int write(void *device, int seqc, struct data *seqv, 
		 callback_t callback, callback_data_t callback_data,
		 uintptr_t key);
static int read(void *device, int seqc, struct data *seqv, 
		callback_t callback, callback_data_t callback_data,
		uintptr_t key);

struct kdb_dev {
	struct driver_instance generic;
	int enabled;
	int xmit_fifo;

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

struct driver drv_l4_kdb = 
{
	.name = "L4 kdb",
	.class = character_device,
	.ops.c_ops = &ops
};




static int write(void *device, int seqc, struct data *seqv, 
		 callback_t callback, callback_data_t callback_data,
		 uintptr_t key)
{
	int i, j;
	j = seqc;
	while (j != 0)
	{
		for (i=0;i<seqv->length;i++)
		{
			L4_KDB_PrintChar(seqv->data[i]);
		}
		seqv->xferred=seqv->length;
		j--;
	}
	callback(callback_data, seqc, seqv, key);
	
	return 0;
}

static int read(void *device, int seqc, struct data *seqv, 
		callback_t callback, callback_data_t callback_data,
		uintptr_t key)
{
	return 0;
}

static void *setup(int spacec, bus_space_t *spacev, dma_handle_t dma, bus_space_t pciconf)
{
	struct kdb_dev *drv;
	drv = malloc(sizeof(struct kdb_dev));
	if (drv == 0) return 0;
	memset(drv, 0, sizeof *drv);
	
	drv->generic.classp = &drv_l4_kdb;
	
	return drv;
}

static void  enable(void *device)
{
}
static void  cleanup(void *device)
{
}
static void  interrupt(void *device)
{
}




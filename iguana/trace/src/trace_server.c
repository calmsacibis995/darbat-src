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
 Author: Carl van Schaik
 Created: Mon Oct  10 2005
*/

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#include <l4/ipc.h>
#include <l4/thread.h>
#include <l4/kip.h>

#include <iguana/hardware.h>
#include <iguana/memsection.h>
#include <trace/tracebuffer.h>

#define IRQ_LABEL (((~(0UL)) << 20) >> 16)

#define TXT_NORMAL		"\e[0m"
#define TXT_BRIGHT		"\e[1m"
#define TXT_FG_GREEN		"\e[32m"

L4_Word_t kernel_trace_irq = 0;
trace_buffer_t * kernel_tracebuffer;

static int setup(void)
{
	int i, r, found = 0;
	L4_KernelInterfacePage_t *kip;
	L4_Word_t dummy, phys = 0, size = 0;
	uintptr_t addr;
	memsection_ref_t ms_tb;

	printf("Trace server starting\n");

	kip = L4_KernelInterface( &dummy, &dummy, &dummy );

	kernel_tracebuffer = NULL;

	/* Find all the tracebuffer */
	for (i = 0; i < kip->MemoryInfo.n; i++) {
		/* get the info */
		L4_MemoryDesc_t * mdesc = L4_MemoryDesc(kip, i);

		/* is it physical? */
		if (mdesc->x.v)
			continue;

		/* look for tracebuffer object */
		if (L4_MemoryDescType(mdesc) == L4_TracebufferMemoryType) {
			phys = L4_MemoryDescLow(mdesc);
			size = L4_MemoryDescHigh(mdesc) - phys + 1; 
			found = 1;
			break;
		}
	}

	if (!found)
	    return 0;

	/* Get tracebuffer and map to ourselves */
	ms_tb = memsection_create_user(size, &addr);
	if (ms_tb == 0) {
		printf("Unable to create a trace buffer memsection\n");
		return 0;
	}
	r = hardware_back_memsection(ms_tb, phys, 0);
	if (r != 0) {
		printf("Error backing memory section: (%d)\n", r);
		return 0;
	}

	kernel_tracebuffer = (trace_buffer_t *)addr;
	printf("kernel tracebuffer %p(%ld) at %p\n", (void*)phys, size, kernel_tracebuffer);

	/* Register tracebuffer - last interrupt */
	kernel_trace_irq = L4_ThreadIdSystemBase(kip)-1;
	hardware_register_interrupt(L4_Myself(), kernel_trace_irq);

	return 1;
}

#ifdef __arm__
static void
l4e_cache_flush(void) {
	L4_Word_t attributes[4] = {0,0,0,0};
	L4_MemoryControl (-2, attributes);
}
#endif

static void dump_kernel_trace(trace_buffer_t * tb)
{
	uintptr_t buffer, count;
	uintptr_t buffer_mask;

#if 0
	printf("trace_buffer magic: %"PRIxPTR", version: %"PRIxPTR", bufid: %"PRIxPTR"\n",
			tb->magic, tb->version, tb->bufid);
#endif
	
	buffer = tb->active_buffer;
	buffer_mask = tb->buffer_empty;

	if (buffer == ~(0ul))	    /* Trace inactive/blocked */
		buffer = 0;

	count = tb->buffers;
	while (count--)
	{
		/* Data to be read in this buffer? */
		if ((buffer != tb->active_buffer) && ((~buffer_mask) & (1ul << buffer)))
		{
			uintptr_t head = tb->buffer_head[buffer];
			uintptr_t entry = 0;

			//printf("Data in %d\n", buffer);

			/* Do statistics on buffer */
			{
				uintptr_t logs = 0, ipcs = 0;
				uint64_t start = 0, end = 0, total;

				while (entry < head)
				{
					trace_entry_t * tbe = (trace_entry_t*)( (uintptr_t)tb +
							tb->buffer_offset[buffer] + entry);
					if (logs == 0)
						start = tbe->timestamp;
					end = tbe->timestamp;

					/* XXX kernel hard coded here */
					switch (tbe->hdr.x.id) {
						case 1:
							logs ++;
							break;
						case 2:
							logs ++;
							break;
						default:
							if (tbe->hdr.x.major == 3)
							    ipcs ++;
							logs ++;
							break;
					}

					entry = entry + (tbe->hdr.x.reclen * sizeof(uintptr_t));
				}

				total = end-start;
				printf(TXT_BRIGHT TXT_FG_GREEN
						"TRACE: %"PRId64" logs/s, %"PRId64" ipc/s "
						TXT_NORMAL "\n",
						total ? (uint64_t)logs*1000000/(total) : -1,
						total ? (uint64_t)ipcs*1000000/(total) : -1);
			}
			/* mark this buffer as clear */
			tb->buffer_empty |= (1ul << buffer);
#if 0
			/* Dump trace buffer to console */
			while (entry < head)
			{
			    trace_entry_t * tbe = (trace_entry_t*)(
				    (uintptr_t)tb + tb->buffer_offset[buffer] + entry);

			    printf("%6d: %9"PRIx64" ", entry, tbe->timestamp);

			    /* XXX kernel hard coded here */
			    switch (tbe->hdr.x.id) {
				case 1:
				    printf("(%d, %d, %d) evt: %d", tbe->hdr.x.major, tbe->hdr.x.minor,
					    tbe->hdr.x.user, tbe->data[0]);
				    break;
				case 2:
				    printf("(%d, %d, %d) \"%s\"", tbe->hdr.x.major, tbe->hdr.x.minor,
					    tbe->hdr.x.user, (char*)tbe->data);
				    break;
				default:
				    printf("(%d, %d, %d) %d: ",
					    tbe->hdr.x.major, tbe->hdr.x.minor, tbe->hdr.x.user,
					    tbe->hdr.x.id);

				    for ( int i = 0; i < (int)tbe->hdr.x.args; i++ )
					printf("%08"PRIxPTR", ", tbe->data[i]);
				    break;
			    }

			    printf("\n");

			    entry = entry + (tbe->hdr.x.reclen * sizeof(uintptr_t));
			}
#endif
		}

		buffer ++;
		if (buffer >= tb->buffers)
			buffer = 0;
	}
}

int main(void)
{
	L4_ThreadId_t sender;

	if (!setup())
	{
	    printf("no kernel tracebuffer found\n");
	    return 0;
	}

	sender = L4_nilthread;

	while (1) {
		L4_MsgTag_t tag;

		tag = L4_ReplyWait(sender, &sender);

		if (tag.X.label == IRQ_LABEL) {
			if (L4_ThreadNo(sender) == kernel_trace_irq)
			{
				//printf("trace: interrupt\n");
#ifdef __arm__
				l4e_cache_flush();
#endif
				dump_kernel_trace(kernel_tracebuffer);
				continue;
			}
		}

		printf("trace: unknown msg received (from %lx, tag = %lx (label %"PRIdPTR"))\n",
			sender.raw, tag.raw, tag.X.label);
		sender = L4_nilthread;
	}
	return 0;
}


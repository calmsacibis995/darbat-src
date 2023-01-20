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
 Description:
 A simple sigma0 for use with the Iguana system.

 Author: Ben Leslie
*/

#include <l4/ipc.h>
#include <l4/kip.h>
#include <l4/kcp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

uintptr_t _stack[128];
void * _stack_top = (void*) &_stack[255];

#define DEBUG_PRINT(...)

/*
 * Encoding for label field of message tag. As per the L4 manual
 */
#define L4_REQUEST_MASK		( ~((~0UL) >> ((sizeof (L4_Word_t) * 8) - 20)))
#define L4_PAGEFAULT		(-2UL << 20)
#define L4_PAGEREQUEST		(-6UL << 20)

/* structures for the bootloader mappings -- This describe mappings that
 allow the rootserver to fault on some areas of memory */
struct boot_mapping {
	uintptr_t vbase;
	uintptr_t vend;
	uintptr_t pbase;
	uintptr_t offset;
};

/* boot mapping data */
#define MAX_BOOT_MAPPINGS 10
struct boot_mapping boot_mappings[MAX_BOOT_MAPPINGS];
static unsigned num_bootmaps = 0;


static int pagebits;

/* Forward declarations */
static int do_pagefault(L4_Msg_t *msg, L4_ThreadId_t *tid);
static int do_pagerequest(L4_Msg_t *msg, L4_ThreadId_t *tid);
static void sigma0_add_bootmap(uintptr_t vaddr, uintptr_t paddr, uintptr_t size);
static void sigma0_server(void);

int my_ffs(L4_Word_t);
/* FIXME: (benjl) This should be in a better place */
/* Find the first bit set in a word */
int
my_ffs(L4_Word_t x) 
{
	int ret;
	for (ret=0; ret<sizeof(L4_Word_t) * 8; ret++) {
		if ((x & 0x1) != 0) {
			break;
		}
		x >>= 1;
	}
	return ret;
}

int
main(void)
{
	L4_KernelConfigurationPage_t *kcp;
	L4_KernelInterfacePage_t *kip;
	struct boot_info;
	int i;

	kip = L4_GetKernelInterface();
	kcp = (L4_KernelConfigurationPage_t*) kip;

	/* Add a mapping for the root server. This allows it
	   to fault in its defined region */
	sigma0_add_bootmap(kcp->root_server.low, 
			   kcp->root_server.low, 
			   kcp->root_server.high - kcp->root_server.low);

#ifdef ARCH_ARM
	{
		L4_Word_t dummy;
		L4_Word_t attrib[4] = { 0, 0, 0, 0 };
		/* Place sigma0 in L4 ARM vspace #1 with iguana */
		L4_SpaceControl(L4_Myself(), (1<<16), L4_Nilpage, L4_Nilpage, &dummy);
		/* Cache Flush */
		L4_MemoryControl(-2ul, attrib);
	}
#endif
	/* We also allow the root server to touch the boot mappings */
	for (i=0; i<L4_NumMemoryDescriptors(kip); i++) {
		L4_MemoryDesc_t *mem_desc;
		mem_desc = L4_MemoryDesc(kip, i) ;
		if ((L4_MemoryDescType(mem_desc) & 0xf) == 
		    L4_BootLoaderSpecificMemoryType) {
			sigma0_add_bootmap(L4_MemoryDescLow(mem_desc),
					   L4_MemoryDescLow(mem_desc),
					   L4_MemoryDescHigh(mem_desc) - 
					   L4_MemoryDescLow(mem_desc));
		}
	}

	/* Work out our minimum page size */
	pagebits = my_ffs(L4_PageSizeMask(kip));
	sigma0_server();
	return 0;
}

/* Add a bootmapping for the root task */
static void
sigma0_add_bootmap(uintptr_t vaddr, uintptr_t paddr, uintptr_t size)
{
	boot_mappings[num_bootmaps].vbase = vaddr;
	boot_mappings[num_bootmaps].pbase = paddr;
	boot_mappings[num_bootmaps].vend  = vaddr + size;
	boot_mappings[num_bootmaps].offset = paddr - vaddr;
	num_bootmaps++;
}

/* This is our main server loop, we accept pagefaults and explicit requests for
   memory from the root task only */
static void
sigma0_server(void)
{
	L4_MsgTag_t tag;
	bool send = false;

	/* Only receive messages from root thread */
	L4_ThreadId_t tid = L4_GlobalId \
		(L4_ThreadIdUserBase (L4_GetKernelInterface()) + 2, 1);

	/* Only accept message registers, not any mapitems */
	L4_Accept(L4_UntypedWordsAcceptor);

	do {
		L4_Msg_t msg;

		/* Call or Receive based on `send' parameter */
		if (send == true) {
			tag = L4_Call (tid);
		} else {
			tag = L4_Receive (tid);
		}

		if (L4_IpcFailed(tag)) {
			/* The ipc failed for some reason */
			send = false;
			continue;
		}

		if ((L4_UntypedWords (tag) != 2 && L4_UntypedWords (tag) != 3)|| L4_TypedWords (tag) != 0) {
			/* sigma0 received a malformed request */
			send = false;
			continue;
		}
	
		L4_MsgStore (tag, &msg);

		/*
		 * Dispatch IPC according to protocol.
		 */
		switch (tag.raw & L4_REQUEST_MASK) {
		case L4_PAGEFAULT:
			send = do_pagefault(&msg, &tid);
			break;
		case L4_PAGEREQUEST:
			send = do_pagerequest(&msg, &tid);
			break;
		default:
			/* Unknown IPC request -- This is probably bad */
			break;
		}
	} while (1);
}

/* This is called when we received an explicit pagerequest */
static int
do_pagerequest(L4_Msg_t *msg, L4_ThreadId_t *tid)
{
	L4_MapItem_t map;
	L4_Fpage_t fpage;
	L4_Word_t attr;

	/* Extract the requested fpage and attributes */
	fpage.raw = L4_MsgWord(msg, 0);
	attr = L4_MsgWord(msg, 1);

	/* Map the requested fpage back with a zero sendbase */
	/* Currently we ignore the requested attributes */
	map = L4_MapItem(fpage, 0);

	/* Marshal mapitem into the msg struct */
	L4_MsgPut(msg, 0, 0, (L4_Word_t *) 0, 2, &map);
	L4_MsgLoad(msg);

	/* Valid data to send */
	return 1;
}

/* This is called when the root tasks acutally pagefaults */
static int
do_pagefault(L4_Msg_t *msg, L4_ThreadId_t *tid)
{
	L4_MapItem_t map;
	L4_Word_t vaddr;
	L4_Word_t paddr;
	void *ip;
	int i;

	/* Extract the faulting address and the instruction pointer */
	vaddr = L4_MsgWord(msg, 0);
	ip = (void *) L4_MsgWord(msg, 1);

	/* Try to find a bootmapping for the faulting address */
	for( i = 0; i < num_bootmaps; i++ ) {
		if( vaddr >= boot_mappings[i].vbase 
		    && vaddr < boot_mappings[i].vend )
			break;
	}

	if( i == num_bootmaps ) {
		/* Couldn't find a valid mapping so it is the end
		   of the road */
		DEBUG_PRINT("s0: fault addr = %p @ ip = %p\n", (void*)vaddr, ip);
		abort();
		return 0;
	}

	/* We work out the physical address to map back */
	paddr = vaddr + boot_mappings[i].offset;

	/* Create a mapping of the minimum page size, for the physical address
	   and force the send base to be the faulting addrsss */
	map = L4_MapItem((L4_Fpage_t) (L4_FpageLog2(paddr, pagebits).raw +
				       L4_FullyAccessible), vaddr);
	/* Marshal the arguments */
	L4_MsgPut(msg, 0, 0, (L4_Word_t *) 0, 2, &map);
	L4_MsgLoad(msg);
	/* Valid data to send */
	return 1;
}

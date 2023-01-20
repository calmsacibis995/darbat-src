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
  Initialise iguana, start init task and jump to the server
  Authors: Ben Leslie, Alex Webster
  Created: Sat Jul 7 2004 
*/

#include <l4/ipc.h>
#include <l4/kdebug.h>
#include <l4e/regions.h>
#include <l4e/misc.h>

#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#include "objtable.h"
#include "security.h"
#include "memsection.h"
#include "stdio.h"
#include "pd.h"
#include "vm.h"

#include "ig_util.h"

/* Memory info -- these structures are used before we get the
   full VM and memory allocation up  */
#if 0	/* -gl: not enough for us */
#define NUM_MI_REGIONS 40
#define NUM_MI_IOREGIONS 40
#define NUM_MI_VMREGIONS 40
#define NUM_MI_OBJECTS 60
#else
#define NUM_MI_REGIONS 256
#define NUM_MI_IOREGIONS 256
#define NUM_MI_VMREGIONS 256
#define NUM_MI_OBJECTS 256
#endif
struct l4e_memory_info meminfo;
struct memdesc mi_regions[NUM_MI_REGIONS];
struct memdesc mi_ioregions[NUM_MI_IOREGIONS];
struct memdesc mi_vmregions[NUM_MI_VMREGIONS];
struct initial_obj mi_objects[NUM_MI_OBJECTS];


/* Obligatory promotion */
#ifdef DEBUG
static char banner[] =  
	"\n"
	" *****************************************\n"
	" *  Iguana system, Copyright 1996-2004   *\n"
	" *  ERTOS - National ICT Australia       *\n"
	" *****************************************\n\n";
#endif

/* Forward declaration of our server loop */
extern void iguana_server(void);

/* Forward declarations */
static void start_init(void);
static void populate_init_objects(struct l4e_memory_info *memi);

int
main(void)
{
	DEBUG_PRINT(banner);

#ifdef ARCH_ARM
	{
		L4_Word_t dummy;
		L4_Word_t attrib[4] = { 0, 0, 0, 0 };
		/* Place iguana in L4 ARM vspace #1 */
		L4_SpaceControl(L4_Myself(), (1<<16), L4_Nilpage, L4_Nilpage, &dummy);
		/* Cache Flush */
		L4_MemoryControl(-2ul, attrib);
	}
#endif
	/* Get information about the memory layout from L4 */
	l4e_get_memory_info(&meminfo, 
			    mi_regions, NUM_MI_REGIONS,
			    mi_ioregions, NUM_MI_IOREGIONS,
			    mi_vmregions, NUM_MI_VMREGIONS,
			    mi_objects, NUM_MI_OBJECTS, 
			    1, 
#ifdef CONFIG_RESTRICTED_VM
			    1
#else
			    0
#endif
			    );
	/* Initialise virtual memory */
	INIT_PRINT("setup_vm\n");
	setup_vm(&meminfo);

	/* Objtable init */
	INIT_PRINT("objtable_init\n");
	objtable_init();

	/* Now can initialise the utcb object */
	INIT_PRINT("utcb_init\n");
	utcb_init();

	/* Initialise protection domains */
	INIT_PRINT("pd_init\n");
	pd_init(&meminfo);

	/* Populate the object table */
	INIT_PRINT("populate_init_objects\n");
	populate_init_objects(&meminfo);

	/* Initialise threads */
	INIT_PRINT("thread_init\n");
	thread_init();

	/* Start userland init thread */
	INIT_PRINT("start_init\n");
	start_init();

	/* TODO: We could reclaim memory here is we need to */

	/* Now that we are ready to roll, lets start the server */
	INIT_PRINT("iguana_server\n");
	iguana_server();

	assert(!"Should never reach here");

	return 0;
}

/* Find the first application an execute it -- It will then bootstrap
   the rest of the system */
static void
start_init(void)
{
	struct initial_obj *obj, *init_obj;
	struct pd *pd;
	struct thread *thread;
	struct memsection *stack, *heap, *heap_phys, *clist_section;
	uintptr_t *user_stack, *init_vars;
	cap_t *clist;
	int i, j, r;

	/* Find init */
	for (obj=meminfo.objects, i = 0; i < meminfo.num_objects; i++, obj++) {
		if (strcmp(obj->name, "iguana_init") == 0) {
			break;
		}
	}

	init_obj = obj;

	if (i == meminfo.num_objects) {
		assert(!"Couldn't find a program to run!\n");
	}

	
	/* All go from here */
	INIT_PRINT("pd_create\n");
	pd = pd_create(&iguana_pd, 0);
	INIT_PRINT("pd_create_thread\n");
	thread = pd_create_thread(pd, -1);
	assert(thread != NULL);

  	/* create a stack */
	INIT_PRINT("pd_create_memsection (stack)\n");
 	stack = pd_create_memsection(pd, 2*l4e_min_pagesize(), 0, MEM_NORMAL);
 
 	/* create a heap */
	INIT_PRINT("pd_create_memsection (heap)\n");
 	heap = pd_create_memsection(pd, 1 * 1024 * 1024, 0, MEM_NORMAL | MEM_USER); /* FIXME: Heapsize */

	/* back the first 64k */
	heap_phys = pd_create_memsection(pd, 0x10000, 0, MEM_NORMAL);
	assert(heap_phys->base % 0x10000 == 0);
	memsection_page_map(heap, L4_Fpage(heap_phys->base, 0x10000), L4_Fpage(heap->base, 0x10000));
 
 	/* create a clist */
	INIT_PRINT("pd_create_memsection (clist)\n");
 	clist_section = pd_create_memsection(pd, l4e_min_pagesize(), 0, MEM_NORMAL);
	assert(clist_section != NULL); /* If we have run out of VM already we are in
					  trouble! */
 	clist = (cap_t *) clist_section->base;
	assert(clist != NULL);

	INIT_PRINT("creating capabilities\n");
 	/* now create capabilities and add them to the clist */
 	for (obj=meminfo.objects, i = 0, j=0; j < meminfo.num_objects; obj++, j++) {
		if (obj->flags & IOF_VIRT) {
			uintptr_t memsect = (uintptr_t) objtable_lookup((void*) obj->base);
			assert(memsect != 0);
			if (memsect != 0) {
				clist[i++] = security_create_capability(memsect);
			}
		}
 	}

	INIT_PRINT("add caps to clist\n");
 	clist[i++] = security_create_capability((uintptr_t) pd);
 	clist[i++] = security_create_capability((uintptr_t) thread);
 	clist[i++] = security_create_capability((uintptr_t) stack);
 	clist[i++] = security_create_capability((uintptr_t) heap);
	/* XXX: reserve a slot for morecore to use */
 	clist[i++] = security_create_capability((uintptr_t) heap);
 	clist[i++] = security_create_capability((uintptr_t) clist_section);
 
 	pd_add_clist(pd, clist);

	INIT_PRINT("initialising stack\n");
  	/* Setup the stack */
  	user_stack = (uintptr_t *) (stack->end + 1);

	if ( (r = vm_back_mem(heap->base, heap->base + 12*4)) != 0) {
		printf("%s: (%x) unable to back heap during startup\n", __func__, (unsigned int)L4_Myself().raw);
		abort();
	}
	init_vars = (uintptr_t *)heap->base;

	/* Copy all the arguements to __lib_init to the buffer in the heap */
	/* arguements for __libc_setup */
	*(init_vars +  0) = 0x37; /* Callback ptr */
	*(init_vars +  1) = 12;   /* stdin */
	*(init_vars +  2) = 11;   /* stdout */
	*(init_vars +  3) = 10;   /* stderr */
	*(init_vars +  4) = heap->base;
	*(init_vars +  5) = heap->end;
	/* arguements for __cap_init */
	*(init_vars +  6) = 0; /* cap_slot */
	*(init_vars +  7) = i-1; /* cap_used */
	*(init_vars +  8) = l4e_min_pagesize() / sizeof(cap_t); /* cap_size */
	*(init_vars +  9) = clist_section->base; /* cap_addr */
	/* arguements for __naming_init */
	*(init_vars + 10) = 0; /* naming_server */
	
	INIT_PRINT("start_init: initialising stack\n");
 	user_stack--; *user_stack = 0; /* argc */
 	user_stack--; *user_stack = (uintptr_t)init_vars; /* buf for __lib_init */
 
  	/* start thread */
	INIT_PRINT("setting thread name\n");
  	L4_KDB_SetThreadName(thread->id, "ig_init");

	INIT_PRINT("starting init thread\n");
 	thread_start(thread, init_obj->entry_pt, (uintptr_t) user_stack);
}

/* Create memory sections for all the initial memory objects we
   created before the proper VM system was up */
static void
populate_init_objects(struct l4e_memory_info *memi)
{
	int i;
	struct initial_obj *obj=memi->objects;

	for (i=0; i < memi->num_objects; i++, obj++) {
		if (obj->flags & IOF_VIRT) {
			struct memsection *ret;
			uintptr_t base;

			base = page_round_down(obj->base);
			ret = pd_create_memsection(&iguana_pd, obj->end - base, base, MEM_INTERNAL);

			assert(ret != NULL); /* Check it was inserted */
			assert(objtable_lookup((void*) obj->base) != 0); /* Check it is correctly in the
									    object table */
		}
	}
}

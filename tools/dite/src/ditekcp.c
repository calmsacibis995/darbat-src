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
/* KCP maniuplation functions for DITE.
*/
#include <string.h>
#include <stdlib.h>
#include "ditekcp.h"

//#define DKDEBUG printf
#define DKDEBUG(...)

struct aistruct dite_kcp[] = {
	{"magic", AI_WORD, 1},
	{"__padding04", AI_WORD, 3},
	{"Kdebug_sp", AI_WORD, 1},
	{"Kdebug_ip", AI_WORD, 1},
	{"Kdebug_low", AI_WORD, 1},
	{"Kdebug_high", AI_WORD, 1},
	{"sigma0_sp", AI_WORD, 1},
	{"sigma0_ip", AI_WORD, 1},
	{"sigma0_low", AI_WORD, 1},
	{"sigma0_high", AI_WORD, 1},
	{"sigma1_sp", AI_WORD, 1},
	{"sigma1_ip", AI_WORD, 1},
	{"sigma1_low", AI_WORD, 1},
	{"sigma1_high", AI_WORD, 1},
	{"root_server_sp", AI_WORD, 1},
	{"root_server_ip", AI_WORD, 1},
	{"root_server_low", AI_WORD, 1},
	{"root_server_high", AI_WORD, 1},
	{"__padding50", AI_WORD, 1},
	{"MemoryInfo", AI_WORD, 1},
	{"Kdebug_config", AI_WORD, 2},
	{"MainMem_low", AI_WORD, 1},
	{"MainMem_high", AI_WORD, 1},
	{"__padding68", AI_WORD, 4},
	{"DedicatedMem", AI_WORD, 10},
	{"__paddingA0", AI_WORD, 6},
	{"BootInfo", AI_WORD, 1},
	{"__paddingBC", AI_WORD, 1},
    {NULL, 0, 0}
};

struct aistruct dite_memoryinfo[] = {
	{"mdword1", AI_WORD, 1},
	{"mdword2", AI_WORD, 1},
	{NULL, 0, 0}
};

/* Locate the KCP in a target by searching for the entry with a non-null KCP
 * pointer. Note that this can only currently find the KCP if it is stored in 
 * the same file as the DIT entry which contains the KCP pointer.
*/
void *
find_kcp(struct edit_file *sources, int num_sources)
{
	int i, j;
	void *kcp;
	uint32_t magic, target_magic;
	
	for (i = 0; i < num_sources; i++) {
		if (sources[i].kcp != 0) {
			DKDEBUG("Found KCP in entry '%s' with address %llx\n", sources[i].ditname, sources[i].kcp);
			if (sources[i].objtype == OBJ_ELF32)
				sources[i].kcp &= 0x00000000ffffffffULL;
			/* Now the KCP is actually in terms of the target's virtual address; we want a pointer
			 * to play with. So we make a few assumptions... */
			for (j = 0; j < sources[i].nsegments; j++) {
				struct edit_segment *seg = &(sources[i].segments[j]);
				//DKDEBUG("seg vaddr is %llx, size is %llx\n", seg->vaddr, seg->filesize);
				if (seg->vaddr <= sources[i].kcp && seg->vaddr + seg->filesize > sources[i].kcp) {
					// Found the segment containing the KCP
					kcp = seg->data + (sources[i].kcp - seg->vaddr);
					DKDEBUG("Source endianness is %u\n", sources[i].endianness);
					target_magic = sources[i].endianness==MSB ?
						DITE_KCP_MAGIC_MSB : DITE_KCP_MAGIC_LSB;
					magic = read32(kcp, sources[i].endianness);
					//magic = ai_read(&sources[i], dite_kcp, "magic", kcp);
					if (magic != target_magic) {
						DKDEBUG("KCP magic is not correct - wanted %x but got %x\n", 
								target_magic, magic);
						return NULL;
					}	
					return kcp;
				}
			}
		}
	}
	return NULL;
}

/*
 * Patch up the kernel configuration page with the address of the bootinfo structure.
*/
int
kcp_patch_binfo(struct edit_segment *binfo_seg, struct edit_file *sources, int num_sources)
{
	void *kcp = find_kcp(sources, num_sources);

	if (!kcp)
		return -1;

	ai_write(&sources[0], dite_kcp, "BootInfo", binfo_seg->vaddr, kcp);

	return 0;
}

uint64_t
get_kcp_low(struct edit_file *source)
{
    struct edit_segment *first_segment = &source->segments[0];

    return first_segment->paddr;
}

uint64_t
get_kcp_high(struct edit_file *source)
{
    struct edit_segment *last_segment = &source->segments[source->nsegments-1];

    /* FIXME: should == the last byte of the page? */
    return last_segment->paddr + last_segment->memsize;
}

/* FIXME: We could rewrite these to be a single function using aistructs -
 * that may turn out to be cleaner. */
int
kcp_add_memory_info_32(struct edit_file *target, void *kcp, uint32_t low, uint32_t high, int is_virt, int pagesize)
{
    uint32_t memoryinfo, mdword1, mdword2;
    uint32_t meminfo_offset;

    /* printf("Setting up memory info from %x to %x\n", low, high); */
    meminfo_offset = (uint32_t)ai_read(target, dite_kcp, "MemoryInfo", kcp);

    meminfo_offset >>= 16;
    DKDEBUG("meminfo offset is %x\n", meminfo_offset);

    memoryinfo = (meminfo_offset) << 16; 
    memoryinfo |= 0x1;          /* 1 memory descriptor */
    
    mdword1 = ALIGN_DOWN(low, pagesize); 
	if (is_virt) {
		mdword1 |= 0x200; /* Set bit 9 for virtual memory */
	}
    mdword1 |= 0x2E;
    mdword2 = ALIGN(high, pagesize)-1; 

    /*printf("mdword1 is %x; mdword2 is %x, offset 1 is %p, offset 2 is %p\n", mdword1, mdword2,
      kcp+meminfo_offset, kcp+meminfo_offset + 4); */
    ai_write(target, dite_kcp, "MemoryInfo", memoryinfo, kcp);
    ai_write(target, dite_memoryinfo, "mdword1", mdword1, kcp + meminfo_offset);
    ai_write(target, dite_memoryinfo, "mdword2", mdword2, kcp + meminfo_offset);

    return 0;
}

/* FIXME: We could rewrite these to be a single function using aistructs -
 * that may turn out to be cleaner. */
	int
kcp_add_memory_info_64(struct edit_file *target, void *kcp, uint32_t low, uint32_t high, int is_virt, int pagesize)
{
	uint64_t memoryinfo, mdword1, mdword2;
	uint64_t meminfo_offset;

	/*printf("Setting up memory info from %x to %x\n", low, high); */
	meminfo_offset = (uint64_t)ai_read(target, dite_kcp, "MemoryInfo", kcp);
	meminfo_offset >>= 32;

	DKDEBUG("meminfo offset is %llx\n", meminfo_offset);

	memoryinfo = (meminfo_offset) << 32; 
	memoryinfo |= 0x1;          /* 1 memory descriptor */

	mdword1 = ALIGN_DOWN(low, pagesize); // & 0xFFFFFC00; /* Final 10 bits are all set low */
	if (is_virt)
		mdword1 |= 0x200; /* Set bit 9 for virtual memory */
	mdword1 |= 0x2E;
	mdword2 = ALIGN(high, pagesize)-1; // | 0x3FF;  /* Final 10 bits are all set high */

	ai_write(target, dite_kcp, "MemoryInfo", memoryinfo, kcp);
	ai_write(target, dite_memoryinfo, "mdword1", mdword1, kcp + meminfo_offset);
	ai_write(target, dite_memoryinfo, "mdword2", mdword2, kcp + meminfo_offset);

	return 0;
}

/* Write the correct addresses for sigma0 and kernel into the KCP. */
int
kcp_patch_initial_servers(struct edit_file *target, struct edit_file *sources, int num_sources)
{
	int i;
	uint32_t reserved_start = 0;
	void *kcp = find_kcp(sources, num_sources);

	if (!kcp)
		return -1;

	/* Zero out everything beforehand. */
	/*memset(&(kcp->Kdebug), 0, sizeof(L4_KernelRootServer_t));
	  memset(&(kcp->sigma0), 0, sizeof(L4_KernelRootServer_t));
	  memset(&(kcp->sigma1), 0, sizeof(L4_KernelRootServer_t));
	  memset(&(kcp->root_server), 0, sizeof(L4_KernelRootServer_t));
	  */
	/* Look through all segments; if we find sigma0 or the root server patch in the entry point. */
	DKDEBUG("Patching initial servers\n");
	for (i = 0; i < num_sources; i++) {
		if (sources[i].flags & FL_SIGMA0) {
			ai_write(target, dite_kcp, "sigma0_ip", sources[i].entry, kcp);
			ai_write(target, dite_kcp, "sigma0_low", get_kcp_low(&sources[i]), kcp);
			ai_write(target, dite_kcp, "sigma0_high", get_kcp_high(&sources[i]), kcp);
		} else if (sources[i].flags & FL_ROOT) {
			ai_write(target, dite_kcp, "root_server_ip", sources[i].entry, kcp);
			ai_write(target, dite_kcp, "root_server_low", get_kcp_low(&sources[i]), kcp);
			ai_write(target, dite_kcp, "root_server_high", get_kcp_high(&sources[i]), kcp);
			if (i < (num_sources - 1)) {
				reserved_start = get_kcp_low(&sources[i+1]);
			}
		}
	}

	if (reserved_start == 0) {
		/* Root server was the last source in the image. Just add the last segment. */
		reserved_start = target->segments[target->nsegments -1].paddr;
	}
	/* Add everything after the root server to a shared area in physical space. */
	switch(target->word_size){
		case WS_32BIT:
			kcp_add_memory_info_32(target, kcp, reserved_start,
					target->segments[target->nsegments - 1].paddr + target->segments[target->nsegments -1].memsize,
					0, target->pagesize);
			break;
		case WS_64BIT:
			kcp_add_memory_info_64(target, kcp, reserved_start,
					target->segments[target->nsegments - 1].paddr + target->segments[target->nsegments -1].memsize,
					0, target->pagesize);
			break;
		default:
			printf("Unknown word size for patching!\n");
			exit(1);
	}
	return 0;
}

int
kcp_clean(struct edit_file *sources, int num_sources)
{
	void *kcp = find_kcp(sources, num_sources);

	if (!kcp)
		return -1;

	/* Clean out MemoryInfo - do nothing for now. XXX */

    	ai_write(sources, dite_kcp, "MainMem_low", 0, kcp);
    	ai_write(sources, dite_kcp, "MainMem_high", 0, kcp);

	return 0;
}

int
kcp_patch_main_memory(struct edit_file *target, struct edit_file *sources, int num_sources,
		struct edit_options *target_options)
{
	void *kcp = find_kcp(sources, num_sources);
	if (!kcp)
		return -1;

	/* Pretty straightforward right here... */

    	ai_write(target, dite_kcp, "MainMem_low", target_options->kcp_mainmem_low, kcp);
    	ai_write(target, dite_kcp, "MainMem_high", target_options->kcp_mainmem_high, kcp);

	return 0;
}


/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2000-2004 University of New South Wales
 * 
 * All rights reserved. 
 * 
 * Developed by: Operating Systems and Distributed Systems Group (DiSy)
 *			   University of New South Wales
 *			   http://www.disy.cse.unsw.edu.au
 * 
 * Permission is granted by University of New South Wales, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *	 * Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimers.
 * 
 *	 * Redistributions in binary form must reproduce the above
 *	   copyright notice, this list of conditions and the following
 *	   disclaimers in the documentation and/or other materials provided
 *	   with the distribution.
 * 
 *	 * Neither the name of University of New South Wales, nor the names of its
 *	   contributors, may be used to endorse or promote products derived
 *	   from this Software without specific prior written permission.
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
 * conditions, or imposes obligations or liability on University of New South
 * Wales or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of University of New South Wales or the contributor is limited, to
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
 *		Project:  EDIT --- Extended DIT.
 *		Created:  21/07/2000 07:47:23 by Simon Winwood (sjw)
 *  Last Modified:  06/09/2002 16:42:05 by Simon Winwood (sjw)
 *   Version info:  $Revision: 1.19 $ 
 *	Description:
 *		  Does all the dirty work with DIT.
 *	   Comments:
 *
 *		License: Relicensed under UNSW OzPLB
 *
 * $Log: dit.c,v $
 * Revision 1.19  2004/07/28 05:07:30  nfd
 * Bugfix - flags were not being cleared on the newly-allocated section.
 *
 * Revision 1.18  2004/07/21 01:32:09  nfd
 * vaddr=paddr for the dit.
 *
 * Revision 1.17  2004/03/23 07:33:52  benjl
 * Added check to ensure dit doesn't overlap some other segment.
 *
 * Revision 1.16  2004/03/23 07:26:41  nfd
 * print VirtBase rather than Base so as not to confuse people (me)
 *
 * Revision 1.15  2004/03/16 05:45:51  cvansch
 * Make the dit header have a virtual and physical address dependant on the
 * previous section
 *
 * Revision 1.14  2004/03/16 00:54:09  cvansch
 * Show flags better
 *
 * Revision 1.13  2004/03/04 01:38:31  benjl
 * Removed unused variables so this compiles with -Wall -Werror.
 *
 * Revision 1.12  2004/02/26 08:03:40  benjl
 * Changes to make 80-character lines.
 * Changes to add new flags to dite.
 * Changes to add extended Dit_Phdr fields to files.
 * Changes to print out new flags and values.
 *
 * Revision 1.11  2002/09/06 07:06:24  sjw_
 * Added IA64 support, and --name flag
 *
 * Revision 1.10  2002/06/03 08:44:47  sjw_
 * MIPS changes
 *
 * Revision 1.9  2001/03/27 07:06:37  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.8  2000/11/13 12:40:07  sjw
 * Added README for brettn, and fixed a bug in dit.c
 *
 * Revision 1.7  2000/09/25 09:10:16  sjw
 * Added -O and -D.
 *
 * Revision 1.6  2000/09/01 10:18:54  sjw
 * - Moved the DIT stuff into edit.c (out of backends).
 * - Cleaned everything up.
 * - Changed a few flags.
 * - Changed meaning of a few flags (a, s, ...)
 *
 * Revision 1.5  2000/08/14 15:03:44  sjw
 * Version 0.1.4
 * ! Added --align and --nodit options (don't need pad.c anymore).
 * ! Fixed a few minor bugs.
 *
 * Revision 1.4  2000/07/25 08:18:53  sjw
 * Fixed bug in elf64.  Still pretty hacky, need to clean up arch independance
 * bit (i.e. pagesizes etc.), but it works well enough for l4/alpha.
 *
 * Revision 1.3  2000/07/24 14:48:47  sjw
 * Very basic functionality complete -- i.e. it can take in multiple elf32 or
 * elf64 files and spit out 1 elf32 file (strange bug in elf64.c?) which can
 * be recognized by 'dit'.  Still need to implement '-l' flags, but otherwise
 * it's mostly usable.
 *
 * Revision 1.2  2000/07/24 13:03:23  sjw
 * More changes.
 *
 * Revision 1.1  2000/07/20 15:43:48  sjw
 * Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 * Seems to be some problems with alignment ...
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "edit.h"
#include "log.h"
#include "dit.h"


/* Merges the DIT in source with target, and removes the segment from source.
 * Returns 1 if the DIT hasn't been found in the file.
 *
 * Note that the dit is stored in host byte order until it is written to disk.
 */
int merge_dit(struct edit_file *target, struct edit_file *source)
{
	struct edit_segment *seg;
	char *d_ident;
	int phnum;
	unsigned long phoffset;
	int i, dit_type = 0;
	void *dit_data = NULL;
	Dit_Phdr32 *phdr32;
	Dit_Phdr64 *phdr64;
	
	if(source->nsegments == 0) {
		return 1;
	}

	/* Need to check all segments. */
	/* DANGER (sjw Tue Sep 26 03:06:20 2000 ) --- Don't embed a dit file with a dit file! */
	
	seg = source->segments;
	for(i = 0; i < source->nsegments; i++, seg++) {
		/* Only check if the size is large enough */
		if(seg->filesize < sizeof(Dit_Dhdr32)) 
			continue;
	
		d_ident = seg->data;
		
		if (!strncmp(d_ident, DITMAG32, 4))
			dit_type = 1;
		else if (!strncmp(d_ident, DITMAG64, 8))
			dit_type = 2;
		else
			continue;

		dit_data = seg->data;
		/* else we have the DIT in this segment */
		break;
	}
	/* Here we have a DIT segment, so do what needs to be done */
	
	if(i == source->nsegments)
		return 1;

	log(LOG_LOW, "DIT segment is %d\n", i);

	memmove(&(source->segments[i]), &(source->segments[i + 1]), 
			(--source->nsegments - i) * sizeof(struct edit_segment));

	/* sanity check */
	if (target->dit_type && target->dit_type != dit_type)
	{
		printf("dit type mismatch\n");
		return 1;
	}

	target->dit_type = dit_type;

	switch (dit_type) {
	case 1:		/* 32-bit */
		phoffset = (unsigned long) dit_data + sizeof(Dit_Dhdr32);

		/* Read in Dhdr32 */
		/* FIXME (sjw Fri Jul 21 08:29:23 2000 ) --- Ignore phoff and phsize ... */

		phnum = read32(offsetof(Dit_Dhdr32, d_phnum) + dit_data,source->endianness);

		target->ndit += phnum;
		target->phdrs = realloc(target->phdrs, target->ndit * sizeof(Dit_Phdr));

		phdr32 = &(target->phdrs[target->ndit - phnum]).D32;
	
		for(i = 0; i < phnum; i++, phoffset += sizeof(Dit_Phdr32), phdr32++) {
			phdr32->p_base =
					read32((void *) (offsetof(Dit_Phdr32, p_base) + phoffset),
									source->endianness);
			phdr32->p_size =
					read32((void *) (offsetof(Dit_Phdr32, p_size) + phoffset),
									source->endianness);
			phdr32->p_entry =
					read32((void *) (offsetof(Dit_Phdr32, p_entry) + phoffset),
									source->endianness);
			phdr32->p_magic =
					read32((void *) (offsetof(Dit_Phdr32, p_magic) + phoffset),
									source->endianness);
			phdr32->p_phys_base =
					read32((void *) (offsetof(Dit_Phdr32, p_phys_base) + phoffset),
									source->endianness);
			phdr32->p_flags =
					read32((void *) (offsetof(Dit_Phdr32, p_flags) + phoffset),
									source->endianness);
		
			/* and the name ... */
			memcpy(phdr32->p_name, (void *) (offsetof(Dit_Phdr32, p_name) + phoffset),
							DIT_NPNAME);		
		}
		break;
	case 2:		/* 64-bit */
		phoffset = (unsigned long) dit_data + sizeof(Dit_Dhdr64);

		/* Read in Dhdr64 */
		/* FIXME (sjw Fri Jul 21 08:29:23 2000 ) --- Ignore phoff and phsize ... */

		phnum = read64(offsetof(Dit_Dhdr64, d_phnum) + dit_data,source->endianness);

		target->ndit += phnum;
		target->phdrs = realloc(target->phdrs, target->ndit * sizeof(Dit_Phdr));

		phdr64 = &(target->phdrs[target->ndit - phnum]).D64;
	
		for(i = 0; i < phnum; i++, phoffset += sizeof(Dit_Phdr64), phdr64++) {
			phdr64->p_base =
					read64((void *) (offsetof(Dit_Phdr64, p_base) + phoffset),
									source->endianness);
			phdr64->p_size =
					read64((void *) (offsetof(Dit_Phdr64, p_size) + phoffset),
									source->endianness);
			phdr64->p_entry =
					read64((void *) (offsetof(Dit_Phdr64, p_entry) + phoffset),
									source->endianness);
			phdr64->p_magic =
					read64((void *) (offsetof(Dit_Phdr64, p_magic) + phoffset),
									source->endianness);
			phdr64->p_phys_base =
					read64((void *) (offsetof(Dit_Phdr64, p_phys_base) + phoffset),
									source->endianness);
			phdr64->p_flags =
					read64((void *) (offsetof(Dit_Phdr64, p_flags) + phoffset),
									source->endianness);
		
			/* and the name ... */
			memcpy(phdr64->p_name, (void *) (offsetof(Dit_Phdr64, p_name) + phoffset),
							DIT_NPNAME);		
		}
		break;
	default:
		printf("Unsupported dit type %d\n", target->dit_type);
		return 1;
	}
	
	return 0;
}


int dit_compar32(const void *a, const void *b)
{
	return ((Dit_Phdr32 *) a)->p_phys_base - ((Dit_Phdr32 *) b)->p_phys_base;
}

int dit_compar64(const void *a, const void *b)
{
	return ((Dit_Phdr64 *) a)->p_phys_base - ((Dit_Phdr64 *) b)->p_phys_base;
}

int add_dit_entry(struct edit_file *target, struct edit_file *entry)
{
	Dit_Phdr32 phdr32;
	Dit_Phdr64 phdr64;
	
	if(entry->nsegments == 0)  /* Tool */
		return 1;

	switch (target->dit_type) {
	case 0:
		printf("Error, dit type not set\n");
		return 1;
	case 1: /* 32 bit */
		phdr32.p_base = entry->segments[0].vaddr;
		phdr32.p_phys_base = entry->segments[0].paddr;
		phdr32.p_size = entry->size;
		phdr32.p_entry = entry->entry;  /* Confused yet ;) */
		phdr32.p_magic = entry->ditmagic;
		phdr32.p_flags =
				(entry->flags & FL_EXEC ? DIT_RUN : 0) | 
				(entry->flags & FL_RESOURCE ? DIT_RMNG : 0) |
				(entry->flags & FL_KERNEL ? DIT_KERNEL : 0) | 
				(entry->flags & FL_SIGMA0 ? DIT_SIGMA0 : 0) | 
				(entry->flags & FL_SIGMA1 ? DIT_SIGMA1 : 0) | 
				(entry->flags & FL_ROOT ? DIT_ROOT : 0)
				;

		memcpy(phdr32.p_name, entry->ditname, DIT_NPNAME);

		target->phdrs = realloc(target->phdrs, (target->ndit + 1) * sizeof(Dit_Phdr32));

		((Dit_Phdr32*)target->phdrs)[target->ndit++] = phdr32;
 
		qsort(target->phdrs, target->ndit, sizeof(Dit_Phdr32), dit_compar32);
		break;
	case 2: /* 64 bit */
		phdr64.p_base = entry->segments[0].vaddr;
		phdr64.p_phys_base = entry->segments[0].paddr;
		phdr64.p_size = entry->size;
		phdr64.p_entry = entry->entry;  /* Confused yet ;) */
		phdr64.p_magic = entry->ditmagic;
		phdr64.p_flags =
				(entry->flags & FL_EXEC ? DIT_RUN : 0) | 
				(entry->flags & FL_RESOURCE ? DIT_RMNG : 0) |
				(entry->flags & FL_KERNEL ? DIT_KERNEL : 0) | 
				(entry->flags & FL_SIGMA0 ? DIT_SIGMA0 : 0) | 
				(entry->flags & FL_SIGMA1 ? DIT_SIGMA1 : 0) | 
				(entry->flags & FL_ROOT ? DIT_ROOT : 0)
				;

		memcpy(phdr64.p_name, entry->ditname, DIT_NPNAME);

		target->phdrs = realloc(target->phdrs, (target->ndit + 1) * sizeof(Dit_Phdr64));

		((Dit_Phdr64*)target->phdrs)[target->ndit++] = phdr64;
 
		qsort(target->phdrs, target->ndit, sizeof(Dit_Phdr64), dit_compar64);
		break;
	default:
		printf("Unknown dit type %d\n", target->dit_type);
		return 1;
	}
	return 0;
} 

uint64_t get_end_addr(struct edit_file *efile, int dit_segment)
{
	int i;
	struct edit_segment *segs;
	unsigned long link_addr;

	i = efile->nsegments - 1;   
	segs = efile->segments;

	/* Note that we also need to leave a page for the DIT header ... sigh */
	link_addr = ALIGN(segs[i].memsize + segs[i].vaddr - efile->offset, efile->pagesize);
	if(dit_segment == efile->nsegments) {
		link_addr += efile->pagesize;
		/* in MIPS L4, the kinfo page is right after the DIT page ... this won't hurt anyone else, I hope */
		link_addr += efile->pagesize;
	}

	return link_addr;
}

/* Creates the DIT segment and adds it to the efile */
uint64_t add_dit_segment(struct edit_file *efile, int dit_segment)
{
	void *dit_seg;
	char *d_ident;
	struct edit_segment *seg;
	unsigned long phoffset;
	uint64_t vaddr, paddr, vaddrend;
	Dit_Phdr32 *phdr32 = (Dit_Phdr32*)efile->phdrs;
	Dit_Phdr64 *phdr64 = (Dit_Phdr64*)efile->phdrs;
	int i;

	if(efile->flags & FL_NODIT) {
		return 0;
	}

	if(dit_segment == -1 || dit_segment > efile->nsegments) 
		dit_segment = efile->nsegments;

	if(dit_segment > 0) {
		seg = &(efile->segments[dit_segment - 1]);
		paddr = ALIGN(seg->paddr + seg->memsize, efile->pagesize);
		vaddr = paddr; /* DIT must be direct-mapped */
		//vaddr = ALIGN(seg->vaddr + seg->memsize, efile->pagesize);
	} else {
		seg = &(efile->segments[dit_segment]);
		/* ALIGN rounds up, so we want to subtract (2*pagesize - 1) to round down */
		paddr = ALIGN(seg->paddr - (2 * efile->pagesize - 1), efile->pagesize);
		vaddr = paddr; /* Direct-map */
		//vaddr = ALIGN(seg->vaddr - (2 * efile->pagesize - 1), efile->pagesize);
	}

	efile->segments = realloc(efile->segments, (++efile->nsegments) * sizeof(struct edit_segment));
	
	memmove(&(efile->segments[dit_segment + 1]), &(efile->segments[dit_segment]), 
			((efile->nsegments - 1) - dit_segment) * sizeof(struct edit_segment));

	/*
	 * This binfo pointer cache is bogus, if you are going to do tricks
	 * like realloc() but not updating the pointer.
	 *
	 * We will patch this one up and see when it breaks, sigh.
	 *
	 * -gl. 
	 */
	if (efile->flags & FL_USE_BINFO)
		efile->binfo_seg = &efile->segments[efile->nsegments - 1];

	seg = &(efile->segments[dit_segment]);

	dit_seg = malloc(sizeof(Dit_Dhdr) + (efile->ndit * sizeof(Dit_Phdr)));
	if(dit_seg == NULL) {
		log(LOG_CRITICAL, "Out of memory");
		return 1;
	}

	seg->vaddr = vaddr;
	seg->paddr = paddr;
	/*
	 * We have a very big boot info.  Actually, what's up with this?
	 * The filesize and the memsize should always be the same since
	 * there should never be any run-time initialization of the bootinfo
	 * that requires extra memory at the end.
	 *
	 * -gl.
	 */
#if 0 
	seg->memsize = efile->pagesize; /* FIXME(benjl): Surely this means we have lots of segments 
									   we are in trouble */
#else
	seg->memsize = 2 * efile->pagesize;
#endif
	/* Check it fits */
	if (dit_segment < efile->nsegments - 1) {
			if (seg->paddr + seg->memsize > efile->segments[dit_segment+1].paddr) {
					log(LOG_CRITICAL, "Dit overlaps segments\n");
					return 1;
			}
	}


	vaddrend = get_end_addr(efile, dit_segment);

	/* Fill in dhdr */
	d_ident = dit_seg;
	
	switch (efile->dit_type) {
	case 0:
		printf("Error, dit type not set\n");
		return 1;
	case 1: /* 32 bit */
		memcpy(d_ident, DITMAG32, 4);

		write32(sizeof(Dit_Dhdr32), offsetof(Dit_Dhdr32, d_phoff) + dit_seg,
						efile->endianness);
		write32(sizeof(Dit_Phdr32), offsetof(Dit_Dhdr32, d_phsize) + dit_seg,
						efile->endianness);
		write32(efile->ndit, offsetof(Dit_Dhdr32, d_phnum) + dit_seg,
						efile->endianness);
		write32(sizeof(Dit_Dhdr32) + efile->ndit * sizeof(Dit_Phdr32),
						offsetof(Dit_Dhdr32, d_fileend) + dit_seg,
						efile->endianness);

		write32(vaddrend, offsetof(Dit_Dhdr32, d_vaddrend) + dit_seg,
						efile->endianness);

		phoffset = (unsigned long) dit_seg + sizeof(Dit_Dhdr32);
	
		for(i = 0; i < efile->ndit; i++, phoffset += sizeof(Dit_Phdr32), phdr32++) {
			write32(phdr32->p_base,
							(void *) (offsetof(Dit_Phdr32, p_base) + phoffset),
							efile->endianness);
			write32(phdr32->p_size,
							(void *) (offsetof(Dit_Phdr32, p_size) + phoffset),
							efile->endianness);
			write32(phdr32->p_entry,
							(void *) (offsetof(Dit_Phdr32, p_entry) + phoffset),
							efile->endianness);
			write32(phdr32->p_flags,
							(void *) (offsetof(Dit_Phdr32, p_flags) + phoffset),
							efile->endianness);

			/* and the name ... */
			memcpy((void *) (offsetof(Dit_Phdr32, p_name) + phoffset),
							phdr32->p_name, DIT_NPNAME);
			write32(phdr32->p_magic, (void *) (offsetof(Dit_Phdr32, p_magic) +
									phoffset), efile->endianness);
			write32(phdr32->p_phys_base, (void *) (offsetof(Dit_Phdr32,
											p_phys_base) + phoffset),
							efile->endianness);
		}
	
		/* FIXME (sjw Tue Sep 26 03:05:20 2000 ) --- Correct? */
		seg->filesize = sizeof(Dit_Dhdr32) + efile->ndit * sizeof(Dit_Phdr32);
		break;
	case 2: /* 64 bit */
		memcpy(d_ident, DITMAG64, 8);

		write64(sizeof(Dit_Dhdr64), offsetof(Dit_Dhdr64, d_phoff) + dit_seg,
						efile->endianness);
		write64(sizeof(Dit_Phdr64), offsetof(Dit_Dhdr64, d_phsize) + dit_seg,
						efile->endianness);
		write64(efile->ndit, offsetof(Dit_Dhdr64, d_phnum) + dit_seg,
						efile->endianness);
		write64(sizeof(Dit_Dhdr64) + efile->ndit * sizeof(Dit_Phdr64),
						offsetof(Dit_Dhdr64, d_fileend) + dit_seg,
						efile->endianness);

		write64(vaddrend, offsetof(Dit_Dhdr64, d_vaddrend) + dit_seg,
						efile->endianness);

		phoffset = (unsigned long) dit_seg + sizeof(Dit_Dhdr64);
	
		for(i = 0; i < efile->ndit; i++, phoffset += sizeof(Dit_Phdr64), phdr64++) {
			write64(phdr64->p_base,
							(void *) (offsetof(Dit_Phdr64, p_base) + phoffset),
							efile->endianness);
			write64(phdr64->p_size,
							(void *) (offsetof(Dit_Phdr64, p_size) + phoffset),
							efile->endianness);
			write64(phdr64->p_entry,
							(void *) (offsetof(Dit_Phdr64, p_entry) + phoffset),
							efile->endianness);
			write64(phdr64->p_flags,
							(void *) (offsetof(Dit_Phdr64, p_flags) + phoffset),
							efile->endianness);

			/* and the name ... */
			memcpy((void *) (offsetof(Dit_Phdr64, p_name) + phoffset),
							phdr64->p_name, DIT_NPNAME);
			write64(phdr64->p_magic, (void *) (offsetof(Dit_Phdr64, p_magic) +
									phoffset), efile->endianness);
			write64(phdr64->p_phys_base, (void *) (offsetof(Dit_Phdr64,
											p_phys_base) + phoffset),
							efile->endianness);
		}
	
		/* FIXME (sjw Tue Sep 26 03:05:20 2000 ) --- Correct? */
		seg->filesize = sizeof(Dit_Dhdr64) + efile->ndit * sizeof(Dit_Phdr64);
		break;
	}

	/* Don't care about alignment */
	seg->align = 1;

	seg->data = dit_seg;
	seg->flags = 0;
  
	efile->dit_header_segment = seg;
 
	return 0;
}

int print_dit(struct edit_file *efile)
{
	int i;
	Dit_Phdr32 *phdr32 = &efile->phdrs[0].D32;
	Dit_Phdr64 *phdr64 = &efile->phdrs[0].D64;

	printf("'%s': (%d entries)\n", efile->filename, efile->ndit);
	switch (efile->dit_type) {
	case 1: /* 32 bit */
		printf("No.  Name             VirtBase   PhysBase   Entry	  Size"
						"	   Magic	   xrksSi\n");		  
		for(i = 0; i < efile->ndit; i++, phdr32++) {
			printf("%-3d  %-16s 0x%-8x 0x%-8x 0x%-8x 0x%-8x 0x%-8x  %c%c%c%c%c%c\n",
							i, phdr32->p_name, phdr32->p_base, phdr32->p_phys_base,
							phdr32->p_entry, phdr32->p_size, phdr32->p_magic,
							(phdr32->p_flags & DIT_RUN) ? 'x' : '-',
							(phdr32->p_flags & DIT_RMNG) ? 'r' : '-',
							(phdr32->p_flags & DIT_KERNEL) ? 'k' : '-',
							(phdr32->p_flags & DIT_SIGMA0) ? 's' : '-',
							(phdr32->p_flags & DIT_SIGMA1) ? 'S' : '-',
							(phdr32->p_flags & DIT_ROOT) ? 'i' : '-'
							);
		}
		printf("x = execute, r = resource mgr, k = kernel, s = sigma0, "
						"S = sigma1, i = initial\n");
		break;
	case 2: /* 64 bit */
		printf("No.  Name		 VirtBase	   PhysBase	   "
			"Entry		  Size		   Magic	   "
						"xrksSi\n");		  
		for(i = 0; i < efile->ndit; i++, phdr64++) {
			printf("%-3d  %-16s 0x%-16llx 0x%-16llx 0x%-16llx 0x%-16llx 0x%-16llx  %c%c%c%c%c%c\n",
							i, phdr64->p_name, phdr64->p_base, phdr64->p_phys_base,
							phdr64->p_entry, phdr64->p_size, phdr64->p_magic,
							(phdr64->p_flags & DIT_RUN) ? 'x' : '-',
							(phdr64->p_flags & DIT_RMNG) ? 'r' : '-',
							(phdr64->p_flags & DIT_KERNEL) ? 'k' : '-',
							(phdr64->p_flags & DIT_SIGMA0) ? 's' : '-',
							(phdr64->p_flags & DIT_SIGMA1) ? 'S' : '-',
							(phdr64->p_flags & DIT_ROOT) ? 'i' : '-'
							);
		}
		printf("x = execute, r = resource mgr, k = kernel, s = sigma0, "
						"S = sigma1, i = initial\n");
		break;
	default:
		return 1;
	}
	return 0;
}

/*
 * Local Variables: ***
 * compile-command: "make dit.o" ***
 * End: ***
 */

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
/* Target the L4 bootinfo structure. */
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "binfo.h"
#include "binfostruct.h"
#include "aistructs.h"

#include "edit.h"
#include "log.h"
#include "dit.h"

//#define BIDEBUG printf
#define BIDEBUG(...)

/* We define this here rather than using the L4 one because this is the
 * version *we* support, not the version that L4 supports. */
#define BINFO_VERSION 0x1
#define BINFO_CSEXEC_VERSION 0x1
#define BINFO_CSMOD_VERSION 0x1

#define BINFO_SIMPLEELF 0x37
#define BINFO_SIMPLEELF_VERSION 0x1

#define MAX_WORD_ALIGN 8

/* Ensure that *pstart, *vstart and *size include the areas described
 * by new_pstart, new_vstart and new_size, as well as those described
 * by their original values. */
void
binfo_extend_segment(uint64_t *pstart, uint64_t *vstart, uint64_t *size,
		uint64_t new_pstart, uint64_t new_vstart, uint64_t new_size)
{
	if (*size < new_size)
		*size = new_size; /* If *size > new_size we don't care. */
	
	if (*pstart > new_pstart) {
		*size += (*pstart - new_pstart);
		*pstart = new_pstart;
	}
	if (*vstart > new_vstart) {
		*size += (*vstart - new_vstart);
		*vstart = new_vstart;
	}

	if (*pstart + *size < new_pstart + new_size) {
		*size += (new_pstart + new_size) - (*pstart + *size);
	}
	
	if (*vstart + *size < new_vstart + new_size) {
		*size += (new_vstart + new_size) - (*vstart + *size);
	}
}

/* Return the size of a new Module record to be passed to
 * create_bootinfo_struct_module. */
size_t
binfo_sizeof_simpleelf(struct edit_file *target, struct edit_file *source, size_t elf_header_size)
{
	/* Store the module itself, the accompanying filename, the Elf header (Ehdr),
	 * and the Elf section headers (Shdr[]). */

	elf_header_size = ALIGN(elf_header_size, MAX_WORD_ALIGN);
	return ALIGN(ai_structsize(target, dite_binfo_simpleelf) + strlen(source->ditname) + 1 + elf_header_size, MAX_WORD_ALIGN);
}

/* Create a SimpleExec structure in the memory area pointed to by newrec. */
void
create_bootinfo_struct_simpleelf(struct edit_file *target,
		struct edit_file *source, void *newrec, void *elf_header,
		size_t elf_header_size)
{
	uint64_t cmdline_offset, elf_header_offset;
	/* Structure here is:
	 * dite_binfo_simpleelf
	 * filename
	 * \0
	 * Ehdr
	 * [Shdr]*
	*/

	ai_write(target, dite_binfo_simpleelf, "type", BINFO_SIMPLEELF, newrec);
	ai_write(target, dite_binfo_simpleelf, "version", BINFO_SIMPLEELF_VERSION, newrec);

	cmdline_offset = ai_structsize(target, dite_simpleexec);
	ai_write(target, dite_binfo_simpleelf, "cmdline_offset", cmdline_offset, newrec);
	strcpy(newrec + ai_structsize(target, dite_simpleexec), source->ditname);

	elf_header_offset = cmdline_offset + strlen(source->ditname) + 1;  /* include the \0 */
	elf_header_offset = ALIGN(elf_header_offset, MAX_WORD_ALIGN);
	ai_write(target, dite_binfo_simpleelf, "elf_header_offset", elf_header_offset, newrec);
	BIDEBUG("binfo memcpy: %p, %p, %d\n", newrec + elf_header_offset, elf_header, elf_header_size);
	memcpy(newrec + elf_header_offset, elf_header, elf_header_size);
}

/* Return the size of a new SimpleExec record to be passed to 
 * create_bootinfo_struct_simpleexec. */
size_t
binfo_sizeof_simpleexec(struct edit_file *target, struct edit_file *source)
{
	return ALIGN(ai_structsize(target, dite_simpleexec) + strlen(source->ditname) + 1, MAX_WORD_ALIGN); 
}

/* Create a SimpleExec structure in the memory area pointed to by newrec. */
void
create_bootinfo_struct_simpleexec(struct edit_file *target, struct edit_file *source, void *newrec)
{
	int i;
	uint64_t text_pstart = 0, text_vstart = 0, text_size = 0;
	uint64_t data_pstart = 0, data_vstart = 0, data_size = 0;

	ai_write(target, dite_simpleexec, "type", L4_BootInfo_SimpleExec, newrec);
	ai_write(target, dite_simpleexec, "version", BINFO_CSEXEC_VERSION, newrec);
	
	/* Loop through all the sections in this file, and add appropriately. */
	for (i = 0; i < source->nsegments; i++) {
		struct edit_segment *curseg = &(source->segments[i]);
		if (curseg->elf_flags & PF_X) {
			/* Executable */
			if (text_pstart || text_vstart || text_size) {
				/* Extend the segment. */
				binfo_extend_segment(&text_pstart, &text_vstart, &text_size,
						curseg->paddr, curseg->vaddr, curseg->memsize);
			} else {
				text_pstart = curseg->paddr;
				text_vstart = curseg->vaddr;
				text_size = curseg->memsize;
			}
		} else {
			/* Data */
			/* Executable */
			if (data_pstart || data_vstart || data_size) {
				/* Extend the segment. */
				binfo_extend_segment(&data_pstart, &data_vstart, &data_size,
						curseg->paddr, curseg->vaddr, curseg->memsize);
			} else {
				data_pstart = curseg->paddr;
				data_vstart = curseg->vaddr;
				data_size = curseg->memsize;
			}
		}
	}
	
	if (data_vstart == 0 && data_pstart == 0 && data_size == 0) {
		/* No data section, because all are marked executable. Make one up. */
		data_vstart = text_vstart;
		data_pstart = text_pstart;
		data_size = text_size;
	}

	ai_write(target, dite_simpleexec, "text_vstart", text_vstart, newrec);
	ai_write(target, dite_simpleexec, "text_pstart", text_pstart, newrec);
	ai_write(target, dite_simpleexec, "text_size", text_size, newrec);
	ai_write(target, dite_simpleexec, "initial_ip", source->entry, newrec);

	ai_write(target, dite_simpleexec, "data_vstart", data_vstart, newrec);
	ai_write(target, dite_simpleexec, "data_pstart", data_pstart, newrec);
	ai_write(target, dite_simpleexec, "data_size", data_size, newrec);
	
	/* Don't know, don't care about BSS. */
	ai_write(target, dite_simpleexec, "bss_vstart", 0, newrec);
	ai_write(target, dite_simpleexec, "bss_pstart", 0, newrec);
	ai_write(target, dite_simpleexec, "bss_size", 0, newrec);
	
	ai_write(target, dite_simpleexec, "cmdline_offset", ai_structsize(target, dite_simpleexec), newrec);

	ai_write(target, dite_simpleexec, "flags", 0, newrec);
	strcpy(newrec + ai_structsize(target, dite_simpleexec), source->ditname);
}


/* Return the size of a new Module record to be passed to 
 * create_bootinfo_struct_simpleexec. */
size_t
binfo_sizeof_simplemodule(struct edit_file *target, struct edit_file *source)
{
	return ALIGN(ai_structsize(target, dite_simplemodule) + strlen(source->ditname) + 1, MAX_WORD_ALIGN); 
}

/* Create a SimpleExec structure in the memory area pointed to by newrec. */
void
create_bootinfo_struct_simplemodule(struct edit_file *target, struct edit_file *source, void *newrec)
{
	uint64_t cmdline_offset, elf_header_offset;

	ai_write(target, dite_simplemodule, "type", L4_BootInfo_Module, newrec);
	ai_write(target, dite_simplemodule, "version", BINFO_CSMOD_VERSION, newrec);

	ai_write(target, dite_simplemodule, "start", source->segments[0].paddr, newrec);
	ai_write(target, dite_simplemodule, "size", source->size, newrec);

	cmdline_offset = ai_structsize(target, dite_simplemodule);
	ai_write(target, dite_simplemodule, "cmdline_offset", cmdline_offset, newrec);
	strcpy(newrec + ai_structsize(target, dite_simplemodule), source->ditname);
}

/* Create an L4 BootInfo structure from edit_file entries. */
void *
create_bootinfo_struct(struct edit_file *target, int nsources, struct edit_file *sources)
{
	void *binfo;
	int i;
	size_t current_size, prev_size = 0;
	void *prev = NULL, *newrec= NULL;
	unsigned int num_entries;
	
	BIDEBUG("Creating bootinfo structure\n");
	binfo = malloc(ai_structsize(target, dite_bootinfo)); assert(binfo);

	target->binfo_size = ai_structsize(target, dite_bootinfo);
	
	num_entries = 0;
	for (i = 0; i < target->ndit; i++) {
		struct edit_file *current_source = &sources[i];
		if (current_source->flags & FL_KERNEL) {
			/* Don't add the kernel to bootinfo */
			continue; 
		}
		if (prev) {
			ai_write(target, dite_bootrec, "offset_next", prev_size, prev);
		}
		if (current_source->objtype == OBJ_RAW) {
			/* Create a Module header for this file */
			num_entries ++;
			current_size = binfo_sizeof_simplemodule(target, current_source);
			binfo = realloc(binfo, target->binfo_size + current_size);
			assert(binfo);
			newrec = (void *)binfo + target->binfo_size;
			BIDEBUG("Allocated new Module structure at %p (binfo is %p)\n", newrec, binfo);
			create_bootinfo_struct_simplemodule(target, current_source, newrec);
			
			target->binfo_size += current_size;
			prev = newrec;
			prev_size = current_size;

		} else if (target->flags & FL_BINFO_SEXEC) { 
			/* Create a SimpleExec header for this file. */
			num_entries ++;
			current_size = binfo_sizeof_simpleexec(target, current_source);
			binfo = realloc(binfo, target->binfo_size + current_size);
			assert(binfo);
			newrec = (void *)binfo + target->binfo_size;
			BIDEBUG("Allocated new SimpleExec structure at %p (binfo is %p)\n", newrec, binfo);
			create_bootinfo_struct_simpleexec(target, current_source, newrec);
			
			target->binfo_size += current_size;
			prev = newrec;
			prev_size = current_size;
		}  else {
			/* Create a SimpleElf header instead */
			void *elf_header;
			size_t elf_header_size;

			BIDEBUG("Creating an ELF header structure, binfo is %p\n", binfo);
			elf_header = current_source->elf_create_headers(current_source, &elf_header_size);
			num_entries ++;
			current_size = binfo_sizeof_simpleelf(target, current_source, elf_header_size);
			BIDEBUG("realloc: %p, %u\n", binfo, target->binfo_size + current_size);
			binfo = realloc(binfo, target->binfo_size + current_size);
			assert(binfo);
			newrec = (void *)binfo + target->binfo_size;
			BIDEBUG("Creating the struct. (%p)\n", binfo);
			create_bootinfo_struct_simpleelf(target, current_source,
					newrec, elf_header, elf_header_size);
			
			target->binfo_size += current_size;
			prev = newrec;
			prev_size = current_size;
		}
	}
	target->binfo_size += ai_structsize(target, dite_bootinfo);

	/* Fill out the header */
	ai_write(target, dite_bootinfo, "magic", L4_BOOTINFO_MAGIC, binfo);
	ai_write(target, dite_bootinfo, "version", BINFO_VERSION, binfo);
	ai_write(target, dite_bootinfo, "size", target->binfo_size, binfo);
	ai_write(target, dite_bootinfo, "num_entries", num_entries, binfo);
	return binfo;
}

/* Find a good location for a new segment. Since we have to guess at a good
 * spot to put it, we currently only allow adding bootinfo after all the other
 * segments.
*/
int
binfo_find_suitable_addr(struct edit_file *efile, int binfo_segment, struct edit_segment *seg)
{
	struct edit_segment *closest_seg;

	if (binfo_segment == efile->nsegments -1) {
		/* At the end of the image */
		closest_seg = &(efile->segments[binfo_segment-1]);
		seg->paddr = ALIGN(closest_seg->paddr + closest_seg->memsize, efile->pagesize);
		seg->vaddr = ALIGN(closest_seg->vaddr + closest_seg->memsize, efile->pagesize);
		//seg->vaddr = seg->paddr; /* Direct-mapped segment */
	} else {
		assert(!"Don't support bootinfo not at end of image yet\n");
		/* The following code doesn't work because bootinfo may be >pagesize */
#if 0
		closest_seg = &(efile->segments[binfo_segment]); 
		/* Bootinfo takes one page so we round down and then subtract PAGESIZE. */
		seg->paddr = ALIGN_DOWN(closest_seg->paddr, efile->pagesize) - efile->pagesize;
		seg->vaddr = ALIGN_DOWN(closest_seg->vaddr, efile->pagesize) - efile->pagesize;
		//seg->vaddr = seg->paddr; /* Direct-map this segment. */
#endif
	}

	return 0;
}

/* Run through the dit checking that no segment overlaps any other segment.
 * At least, this is what we'd *like* to do. Unfortunately the dit isn't
 * sorted by paddr, so this is hard here. FIXME. 
*/
int
binfo_check_for_overlaps(struct edit_file *efile, int binfo_segment)
{
	int i, j;
	struct edit_segment *source_seg, *target_seg;
	
	for (i=0; i < efile->nsegments; i++) {
		source_seg = &efile->segments[i];
		for (j=0; j < efile->nsegments; j++) {
			if (j == i)
				continue;
			target_seg = &efile->segments[j];

			if (source_seg->paddr > target_seg->paddr
					&& source_seg->paddr < (target_seg->paddr + target_seg->memsize)) {
				printf("binfo: segments with overlapping paddrs detected. seg %d, paddr %llx, size %llx, prevseg %llx, size %llx.\n", i, source_seg->paddr, source_seg->memsize, target_seg->paddr, target_seg->memsize);
				assert(0);
			}
		}
	}

/*	if ( (binfo_segment < efile->nsegments - 1)
			&& (efile->segments[binfo_segment].paddr + efile->segments[binfo_segment].memsize
				> efile->segments[binfo_segment + 1].paddr)) {
		printf("Bootinfo paddr overlaps next segment.\n");
		assert(0);
	}*/
	return 0;
}

/* Add another segment to the target, containing the Pistachio BootInfo structure.
 * This reads the dit to do its work so must be called after the target file has
 * been created.
*/
struct edit_segment *
add_binfo_segment(struct edit_file *target, int binfo_segment, int nsources, struct edit_file *sources)
{
	struct edit_segment *seg;
	uint32_t first_entry;

	/** Create the bootinfo structure if it isn't already created */
	if(!target->binfo) {
		target->binfo = create_bootinfo_struct(target, nsources, sources);
	}

	BIDEBUG("add_binfo_segment: binfo is %p\n", target->binfo);
	/** Find a spot for this segment in the list of dit segments */
	if (binfo_segment == -1 || binfo_segment > target->nsegments)
		binfo_segment = target->nsegments;

	BIDEBUG("Adding new segment numbered %d\n", binfo_segment);

	/** Fit the new segment in */
	target->nsegments ++;
	target->segments = realloc(target->segments, target->nsegments * sizeof(struct edit_segment));
    
	memmove(&(target->segments[binfo_segment + 1]), &(target->segments[binfo_segment]), 
	    ((target->nsegments - 1) - binfo_segment) * sizeof(struct edit_segment));
	
	seg = &(target->segments[binfo_segment]);

	/* Store relevant stuff in this segment. */
	seg->memsize = ALIGN(target->binfo_size, target->pagesize);
	/* Setup paddr and vaddr */
	binfo_find_suitable_addr(target, binfo_segment, seg);
	
	seg->filesize = target->binfo_size;
	seg->align = 1;
	seg->data = target->binfo;
	seg->flags = 0;

	/* Enusre that we're not clobbering anything */
	binfo_check_for_overlaps(target, binfo_segment);

	/* Fixup the bootinfo to point to the right first_entry. */
	/* First entry is stored immediately after the bootinfo struct. */
	first_entry = ai_structsize(target, dite_bootinfo);
	BIDEBUG("* FIRST ENTRY is %x\n", first_entry);
	ai_write(target, dite_bootinfo, "first_entry", first_entry, target->binfo);

	return seg; /* If you survive, please come again */
}

/* 
 * Search through each segment of the given file until we find the L4 Bootinfo magic
 * number. Then compare versions and return the found segment if everything is OK. 
 */
struct edit_segment *
binfo_find_segment(struct edit_file *efile)
{
	int i;
	struct edit_segment *curseg;

	for (i=0; i < efile->nsegments; i++) {
		curseg = &(efile->segments[i]);
		
		if (ai_read(efile, dite_bootinfo, "magic", curseg->data) == L4_BOOTINFO_MAGIC) {
			if (ai_read(efile, dite_bootinfo, "version", curseg->data) == BINFO_VERSION) {
				return curseg; /* Found it! */
			} else {
				printf("Found a binfo segment, but for an unknown bootinfo version.\n");
			}
		}

	}
	return NULL;
}

void
binfo_print(struct edit_file *efile)
{
	struct edit_segment *binfoseg;
	void *current;
	uint64_t num_entries;
	int i;

	/* First, find the thing ... */
	binfoseg = binfo_find_segment(efile);
	if (!binfoseg) {
		printf("This file does not appear to contain a bootinfo structure.\n");
		return;
	}
	printf("Found a Bootinfo segment: vaddr %llx, paddr %llx, memsize %llx, filesize %llx.\n",
			binfoseg->vaddr, binfoseg->paddr, binfoseg->memsize, binfoseg->filesize);
	num_entries = ai_read(efile, dite_bootinfo, "num_entries", binfoseg->data);
	printf("Magic: %llx  Version: %llx  Size: %llx  Entries: %llx\n",
			ai_read(efile, dite_bootinfo, "magic", binfoseg->data),
			ai_read(efile, dite_bootinfo, "version", binfoseg->data),
			ai_read(efile, dite_bootinfo, "size", binfoseg->data),
			num_entries);
	current = binfoseg->data + ai_read(efile, dite_bootinfo, "first_entry", binfoseg->data);
	for (i=0; i < num_entries; i++) {
		uint64_t type, version;
		type = ai_read(efile, dite_bootrec, "type", current);
		version = ai_read(efile, dite_bootrec, "version", current);
		printf("%d. ", i + 1);
		switch (type) {
			case L4_BootInfo_Module:
				if (version != BINFO_CSMOD_VERSION) {
					printf("L4_BootInfo_Module: Unknown version\n");
				}	
				printf("L4_BootInfo_Module - '%s'\n\tBase: %llx  Size: %llx\n",
					(char *)(current + ai_read(efile, dite_simplemodule, "cmdline_offset", current)),
					ai_read(efile, dite_simplemodule, "start", current),
					ai_read(efile, dite_simplemodule, "size", current));
				break;
			case L4_BootInfo_SimpleExec:
				if (version != BINFO_CSEXEC_VERSION) {
					printf("L4_BootInfo_SimpleExec: Unknown version\n");
				}	
				printf("L4_BootInfo_SimpleExec - '%s'\n\tText phys: %llx  Text virt: %llx  Text size: %llx\n",
					(char *)(current + ai_read(efile, dite_simpleexec, "cmdline_offset", current)),
					ai_read(efile, dite_simpleexec, "text_pstart", current),
					ai_read(efile, dite_simpleexec, "text_vstart", current),
					ai_read(efile, dite_simpleexec, "text_size", current));
				printf("\tData phys: %llx  Data virt: %llx  Data size: %llx\n",
					ai_read(efile, dite_simpleexec, "data_pstart", current),
					ai_read(efile, dite_simpleexec, "data_vstart", current),
					ai_read(efile, dite_simpleexec, "data_size", current));
				printf("\tBSS  phys: %llx  BSS  virt: %llx  BSS  size: %llx\n",
					ai_read(efile, dite_simpleexec, "bss_pstart", current),
					ai_read(efile, dite_simpleexec, "bss_vstart", current),
					ai_read(efile, dite_simpleexec, "bss_size", current));
				printf("\tFlags: %llx  Label: %llx\n",
					ai_read(efile, dite_simpleexec, "flags", current),
					ai_read(efile, dite_simpleexec, "label", current));
				break;
			case BINFO_SIMPLEELF:
				if (version != BINFO_SIMPLEELF_VERSION) {
					printf("L4_BootInfo_SimpleElf: Unknown version\n");
				}
				printf("L4_BootInfo_SimpleElf - '%s'\n",
						(char *)(current + ai_read(efile, dite_binfo_simpleelf, "cmdline_offset", current)));
				printf("\tElf header offset: %lld\n",
						ai_read(efile, dite_binfo_simpleelf, "elf_header_offset", current));
				break;
			default:
				printf("Unsupported type (0x%x).\n", type);
				break;
		}
		printf("\n");
		current += ai_read(efile, dite_bootrec, "offset_next", current);
	}
}



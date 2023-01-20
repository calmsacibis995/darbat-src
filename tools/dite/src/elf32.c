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
 *               University of New South Wales
 *               http://www.disy.cse.unsw.edu.au
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
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of University of New South Wales, nor the names of its
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
 *        Project:  EDIT --- Extended DIT
 *        Created:  12/07/2000 19:40:57 by Simon Winwood (sjw)
 *  Last Modified:  03/06/2002 15:39:02 by Simon Winwood (sjw)
 *   Version info:  $Revision: 1.28 $ 
 *    Description:
 *          This file handles elf32.
 *
 *       Comments:
 *
 *        License: Relicensed under the UNSW OzPLB licence
 *
 *  $Log: elf32.c,v $
 *  Revision 1.28  2004/08/02 07:18:17  nfd
 *  Whoops. Remove unused variable.
 *
 *  Revision 1.27  2004/08/02 07:16:15  nfd
 *  Working support for 32-bit SimpleElf bootinfo structures.
 *
 *  Revision 1.26  2004/07/28 11:36:00  nfd
 *  Update ditekcp to use aistructs. So in theory it works perfectly - perfectly! - on 64-bit systems now.
 *
 *  Revision 1.25  2004/07/28 05:11:38  nfd
 *  Added elf32_create_headers, which returns a structure to be referenced by a SimpleElf entry in the bootinfo.
 *
 *  Revision 1.24  2004/07/26 08:14:02  nfd
 *  Create the bootinfo from the edit_segment structures, rather than from the dit structures. This is how the dit is created, too, so the procedure is less manky now. Also have a guess at which segments are executable, and which are data, based on the permissions of the program headers in the source files. This means changes to the elf-reading functions to store the phdr flags in the edit_segment struct.
 *
 *  Revision 1.23  2004/07/21 07:33:31  nfd
 *  - Bootinfo support for platforms with 64-bit word size as well - untested so far
 *  - Fix an alignment bug when setting up the memory descriptors.
 *
 *  Revision 1.22  2004/07/21 01:33:00  nfd
 *  More informative error messages. Fix entry point if we want a kernel with a paddr entry point.
 *
 *  Revision 1.21  2004/03/10 05:54:18  nfd
 *  Support for writing 64-bit values in 32-bit elf files.
 *
 *  Revision 1.20  2004/03/04 01:43:48  benjl
 *  -Wall -Werror changes.
 *
 *  Revision 1.19  2004/02/26 09:37:56  benjl
 *  Modified so that the patch address is specfied on the command line.
 *
 *  Revision 1.18  2004/02/26 08:07:27  benjl
 *  Added code to patch in dit address.
 *  Changed code to fit in 80-lines.
 *
 *  Revision 1.17  2002/06/03 08:44:47  sjw_
 *  MIPS changes
 *
 *  Revision 1.16  2001/03/27 07:06:36  sjw
 *  Added copyright notices to all of my files.
 *
 *  Revision 1.15  2000/09/25 09:10:16  sjw
 *  Added -O and -D.
 *
 *  Revision 1.14  2000/09/22 04:27:00  sjw
 *  0.2.2: Updated the help screen, minor cosmetic fixes for elf32.c
 *
 *  Revision 1.13  2000/09/01 10:18:54  sjw
 *  - Moved the DIT stuff into edit.c (out of backends).
 *  - Cleaned everything up.
 *  - Changed a few flags.
 *  - Changed meaning of a few flags (a, s, ...)
 *
 *  Revision 1.12  2000/08/14 15:03:44  sjw
 *  Version 0.1.4
 *  ! Added --align and --nodit options (don't need pad.c anymore).
 *  ! Fixed a few minor bugs.
 *
 *  Revision 1.11  2000/08/07 09:37:17  sjw
 *  It now builds with automake and autoconf.  This means that it now builds
 *  ok on OSF1, schlags broken redhat and debian.
 *
 *  Revision 1.10  2000/08/04 08:09:29  sjw
 *  Added raw output functionality.
 *  Added getopt from gcc (so I can use long opts in a portable way ;)
 *
 *  Revision 1.9  2000/07/25 08:18:53  sjw
 *  Fixed bug in elf64.  Still pretty hacky, need to clean up arch independance
 *  bit (i.e. pagesizes etc.), but it works well enough for l4/alpha.
 *
 *  Revision 1.8  2000/07/24 14:48:47  sjw
 *  Very basic functionality complete -- i.e. it can take in multiple elf32 or
 *  elf64 files and spit out 1 elf32 file (strange bug in elf64.c?) which can
 *  be recognized by 'dit'.  Still need to implement '-l' flags, but otherwise
 *  it's mostly usable.
 *
 *  Revision 1.7  2000/07/20 15:43:48  sjw
 *  Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 *  Seems to be some problems with alignment ...
 *
 *  Revision 1.6  2000/07/19 11:51:59  sjw
 *  Modified interface --- it is now quite different to DIT --- something
 *  of a unholy combination of DIT and sysgen (oh well ... )
 *  Currently it can take multiple entries on the command line.  The actual
 *  building of the DIT header is all that really remains.
 *
 *  Revision 1.5  2000/07/18 16:16:32  sjw
 *  Added some generic ELF routines (conversion between internal format and ELF
 *  machine type)
 *  Did some framework work in edit.c --- mostly dealing with creation of files
 *  etc.
 *  elf32 should now write an ELF file correctly (untested)
 *
 *  Revision 1.4  2000/07/18 06:22:53  sjw
 *  More work.  Added empty coff.[hc], but coff is horrible.
 *
 *  Revision 1.3  2000/07/14 08:32:34  sjw
 *  Added some extra command line options.
 *
 *  Modified interface to readX and writeX so that they don't need to
 *  know about struct edit_file.  This allows write directly to structs.
 *
 *  Revision 1.2  2000/07/13 16:23:48  sjw
 *  elf32 and elf64 now seem to work, in that they fill in the correct info in the
 *  edit_file structure.
 *  Need to figure out the required abstractions.  Probably only set_section etc.
 *
 *  Added dit.h from mipsL4 distro, and elf.h from linux.
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "edit.h"
#include "edit_endian.h"
#include "log.h"
#include "elf_generic.h"
#include "elf.h"

int elf32_write(struct edit_file *efile, struct edit_options *opts);

static uint16_t
init_segments(uint16_t nsegments, struct edit_segment *segments, uint16_t base_phoff, struct edit_file *efile)
{
	int i, actual_nsegments = 0;	/* = nsegments - #segments_to_ignore */
	int phoff = base_phoff;
	uint32_t p_type;

	/* For section offset fixup */
	struct edit_section *current_section;
	for (i = 0; i < nsegments; i++, phoff += sizeof(Elf32_Phdr)) {
		p_type = read32(offsetof(Elf32_Phdr, p_type) + phoff + efile->mmap,
				efile->endianness);
		if (p_type != PT_LOAD)
			continue;

		segments[actual_nsegments].vaddr =
			read32(offsetof(Elf32_Phdr, p_vaddr) + phoff + efile->mmap,
				   efile->endianness);
		segments[actual_nsegments].paddr =
			read32(offsetof(Elf32_Phdr, p_paddr) + phoff + efile->mmap,
				   efile->endianness);
		segments[actual_nsegments].memsize =
			read32(offsetof(Elf32_Phdr, p_memsz) + phoff + efile->mmap,
				   efile->endianness);
		segments[actual_nsegments].filesize =
			read32(offsetof(Elf32_Phdr, p_filesz) + phoff + efile->mmap,
				   efile->endianness);
		segments[actual_nsegments].align =
			read32(offsetof(Elf32_Phdr, p_align) + phoff + efile->mmap,
				   efile->endianness);
		segments[actual_nsegments].elf_flags =
			read32(offsetof(Elf32_Phdr, p_flags) + phoff + efile->mmap,
				   efile->endianness);

		if ((efile->flags & FL_PATCH_FILE) &&
				(efile->patch_addr >= segments[actual_nsegments].vaddr) &&
				(efile->patch_addr < segments[actual_nsegments].memsize +
				 segments[actual_nsegments].vaddr)) {
			segments[actual_nsegments].flags |= FL_S_PATCH_DIT;
			segments[actual_nsegments].patch_addr = efile->patch_addr;
		}


		segments[actual_nsegments].data =
				efile->mmap + read32(offsetof(Elf32_Phdr, p_offset) +
				phoff + efile->mmap, efile->endianness);

		/* If a section offset refers to this segment, fixup the offset
		 * to be segment-relative and include a segment number. */
		for (current_section = efile->first_section;
				current_section;
				current_section = current_section->next) {
			uint32_t seg_offset, seg_size;
			seg_offset = read32(offsetof(Elf32_Phdr, p_offset) + phoff + efile->mmap,
					efile->endianness);
			seg_size = read32(offsetof(Elf32_Phdr, p_filesz) + phoff + efile->mmap, efile->endianness);
			if (current_section->orig_offset >= seg_offset && current_section->orig_offset
					<- (seg_offset + seg_size)) {
				/* We got it.*/
				current_section->segment_num = i;
				current_section->segment_offset = current_section->orig_offset - seg_offset;
			}
		}
		
		/* look at next segment */
		actual_nsegments++;
	}

	return actual_nsegments;
}

static char *
read_section_name(struct edit_file *efile, int section_num)
{
	uint16_t e_shstrndx, e_shentsize;
	uint32_t e_shoff;
	uint32_t sh_name, sh_strtab_offset;
	char *section_header_string_table;

	e_shstrndx = read16(offsetof(Elf32_Ehdr, e_shstrndx) + efile->mmap,
			efile->endianness);
	e_shoff = read32(offsetof(Elf32_Ehdr, e_shoff) + efile->mmap, 
			efile->endianness);
	e_shentsize = read16(offsetof(Elf32_Ehdr, e_shentsize) + efile->mmap, 
			efile->endianness);

	sh_strtab_offset = read32(
			offsetof(Elf32_Shdr, sh_offset)
				+ efile->mmap
				+ e_shoff
				+ e_shentsize * e_shstrndx,
			efile->endianness);

	section_header_string_table = efile->mmap + sh_strtab_offset;

	sh_name = read32(
			offsetof(Elf32_Shdr, sh_name)
				+ efile->mmap
				+ e_shoff
				+ e_shentsize * section_num,
			efile->endianness);

	return section_header_string_table + sh_name;
}

static int
init_sections(struct edit_file *efile)
{
	uint16_t e_shnum;
	uint32_t e_shoff;
	int i;
	struct edit_section *current_section, *prev_section;
	
	e_shnum = read16(offsetof(Elf32_Ehdr, e_shnum) + efile->mmap, 
			efile->endianness);
	e_shoff = read32(offsetof(Elf32_Ehdr, e_shoff) + efile->mmap, 
			efile->endianness);

	efile->first_section = NULL;
	/* NB start with i=1 because section 0 always exists and is defined to be of type NULL */
	for (i=1; i < e_shnum; i++) {
		char *section_offset;;
		current_section = malloc(sizeof(struct edit_section));
		current_section -> next = NULL;

		section_offset = efile->mmap + e_shoff + (sizeof(Elf32_Shdr) * i);
		strcpy(current_section->name, ".");
		strcat(current_section->name, efile->ditname);
		strcat(current_section->name, read_section_name(efile, i)); 
		current_section->type = read32(offsetof(Elf32_Shdr, sh_type) + section_offset,
				efile->endianness);
		current_section->addr = read32(offsetof(Elf32_Shdr, sh_addr) + section_offset,
				efile->endianness);
		current_section->orig_offset = read32(offsetof(Elf32_Shdr, sh_offset) + section_offset,
						      efile->endianness);
		current_section->size = read32(offsetof(Elf32_Shdr, sh_size) + section_offset,
				efile->endianness);
		current_section->addralign = read32(offsetof(Elf32_Shdr, sh_addralign) + section_offset, 
				efile->endianness);
		current_section->entsize = read32(offsetof(Elf32_Shdr, sh_entsize) + section_offset,
				efile->endianness);
		current_section->flags = read32(offsetof(Elf32_Shdr, sh_flags) + section_offset,
				efile->endianness);

		if (i==1) {
			efile->first_section = current_section;
		} else {
			prev_section->next = current_section;
		}
		prev_section = current_section;
	}
}

/* Return parts of the Elf headers. Specifically, return
 * Ehdr
 * Shdr[]
 * String table
 * Phdr[]*/
void *
elf32_create_headers(struct edit_file *efile, size_t *size)
{
	void *headers;
	Elf32_Ehdr *ehdr;
	Elf32_Shdr *old_shdr, *shdr;
	int e_shentsize, e_shnum; /* Section headers */
	int e_shstrndx; /* String table section index */
	void *newstringtable;
	size_t stringtable_size;

	/* Section headers: Find out how big they are. */
	e_shentsize = read16(offsetof(Elf32_Ehdr, e_shentsize) + efile->mmap, 
			efile->endianness);
	e_shnum = read16(offsetof(Elf32_Ehdr, e_shnum) + efile->mmap,
			efile->endianness);
	assert(e_shentsize == sizeof(Elf32_Shdr));

	old_shdr = efile->mmap +
		read32(offsetof(Elf32_Ehdr, e_shoff) + efile->mmap, efile->endianness);

	/* String table: Work out where it is and how big it is. */
	e_shstrndx = read16(offsetof(Elf32_Ehdr, e_shstrndx) + efile->mmap,
			efile->endianness);
	stringtable_size = read32(&(old_shdr[e_shstrndx].sh_size), efile->endianness);
	
	*size = sizeof(Elf32_Ehdr) + (e_shentsize * e_shnum) + stringtable_size;

	headers = malloc(*size);
	assert(headers);
	ehdr = headers;
	shdr = headers + sizeof(Elf32_Ehdr);

	/* Copy the elf header across and then fix bits of it. */
	memcpy(ehdr, efile->mmap, sizeof(Elf32_Ehdr));
	write32(sizeof(Elf32_Ehdr), &(ehdr->e_shoff), efile->endianness);

	/* Copy the section headers across */
	memcpy(shdr, old_shdr, (e_shentsize * e_shnum));

	newstringtable = (void *)shdr + (e_shentsize * e_shnum);

	/* Copy the string table across */
	memcpy(newstringtable, old_shdr[e_shstrndx].sh_offset + efile->mmap, stringtable_size);
	/* Now update the relevant string table header in the new string table
	 * to point to the copied table. */
	write32((uint32_t)(newstringtable - headers), &(shdr[e_shstrndx].sh_offset),
			efile->endianness);

	return headers;
}

int elf32_register(struct edit_file *efile)
{
	char *e_ident = efile->mmap;
	uint16_t phoff;
	int elfmach;
	struct edit_segment *segs;
	int i;

	if(efile->flags & FL_NEW) {
		if(efile->objtype == OBJ_ELF32) {
			log(LOG_LOW, "Creating a new elf32 file '%s'\n", efile->filename);
			efile->write_file = elf32_write;
			efile->pagesize = elfarch_pagesize(efile->arch);
			return 0;
		} else {
			return 1;
		}
	} 

	/* Check magic */
	if(e_ident[0] != ELF_MAGIC_0 ||
			e_ident[1] != ELF_MAGIC_1 ||
			e_ident[2] != ELF_MAGIC_2 ||
			e_ident[3] != ELF_MAGIC_3)
		return 1;

	if(e_ident[EI_CLASS] != ELFCLASS32)
		return 1;

	/* Possibly allow for old elf formats */
	if(e_ident[EI_VERSION] != EV_CURRENT)
		return 1;

	/* Don't care whether or not it is executable.  Let the user shoot
	 * themself in the foot, but somebody might want to do it someday */

	/* File is a elf32, so set everything up */
	efile->objtype = OBJ_ELF32;
	if(e_ident[EI_DATA] == ELFDATA2LSB)
		efile->endianness = LSB;
	else if(e_ident[EI_DATA] == ELFDATA2MSB)
		efile->endianness = MSB;
	else {
		log(LOG_WARNING, "Unknown endianness: %d\n", e_ident[EI_DATA]);
		return 1;
	}

	elfmach = read16(offsetof(Elf32_Ehdr, e_machine) + efile->mmap, 
			efile->endianness);
	efile->arch = elfmach2arch(elfmach);
	efile->pagesize = elfarch_pagesize(efile->arch);

	if(efile->arch == ARCH_INVALID) {	
		log(LOG_WARNING, "Unknown machine type: %d\n", elfmach);
		return 1;
	}

	efile->write_file = elf32_write;

	efile->entry = read32(offsetof(Elf32_Ehdr, e_entry) + efile->mmap, 
			efile->endianness);
	efile->nsegments = read16(offsetof(Elf32_Ehdr, e_phnum) + efile->mmap, 
			efile->endianness);
	phoff = read32(offsetof(Elf32_Ehdr, e_phoff) + efile->mmap, 
			efile->endianness);

	/* Read all sections in this file */
	init_sections(efile);

	/* Set up segment table */
	segs = calloc(efile->nsegments, sizeof(struct edit_segment));
	if(segs == NULL) {
		log(LOG_CRITICAL, "calloc() failed\n");
		exit(EXIT_FAILURE);
	}

	efile->nsegments = init_segments(efile->nsegments, segs, phoff, efile);
	efile->segments = segs;

	/* Align the file to the desired value */
	i = efile->nsegments - 1;
	segs = efile->segments;
	segs[i].memsize = ALIGN(segs[i].memsize + segs[i].vaddr, 
			efile->alignment) - segs[i].vaddr;

	efile->size = segs[i].vaddr + segs[i].memsize - segs[0].vaddr;

	/* Fix the entry point. */
	if (efile->flags & FL_PHYS_ENTRY && efile->nsegments) {
		struct edit_section *current_section;
		int i, done = 0;
		for (i = 0; i < efile->nsegments; i++) {
			edit_addr start = efile->segments[i].vaddr;
			edit_addr end = efile->segments[i].vaddr + efile->segments[i].memsize;

			if ((start <= efile->entry) && (efile->entry < end))
			{
			    done = 1;
			    efile->entry = efile->segments[i].paddr +
				(efile->entry - efile->segments[i].vaddr);
			    break;
			}
		}

		/* If not found, just use seg 0 (probably will break) */
		if (!done) {
			efile->entry = efile->segments[0].paddr +
				(efile->entry - efile->segments[0].vaddr);
		}

		/* Fix all section addresses */
		for (current_section = efile->first_section; current_section != NULL;
				current_section = current_section->next) {
			done = 0;
			for (i = 0; i < efile->nsegments; i++)
			{
				edit_addr start = efile->segments[i].vaddr;
				edit_addr end = efile->segments[i].vaddr + efile->segments[i].memsize;

				if ((start <= current_section->addr) && (current_section->addr < end)) {
					done = 1;
					current_section->addr -= (efile->segments[i].vaddr -
							efile->segments[i].paddr);
					break;
				}
			}
			/* If not found, just use seg 0 (probably will break) */
			if (!done) {
				current_section->addr -= (efile->segments[0].vaddr -
						efile->segments[0].paddr);
			}
		}
	}

	/* Set the correct header generator */
	efile->elf_create_headers = elf32_create_headers;

	efile->word_size = arch_to_wordsize(efile->arch);    
	return 0;
}

static int
get_num_sections(struct edit_file *efile)
{
	uint32_t e_shnum = 0;
	struct edit_section *current = efile->first_section;

	while(current) {
		e_shnum ++;
		current = current->next;
	}
	return e_shnum;
}

int
elf32_write(struct edit_file *efile, struct edit_options *opts)
{
	FILE *fptr;
	int file_size, data_start, next_data, shdr_start, i, j;
	struct edit_segment *segs = efile->segments;
	uint32_t e_shnum;
	Elf32_Ehdr ehdr;
	Elf32_Shdr shdr;
	Elf32_Phdr phdr;
	int binfo_offset = 0;
	/* If the file hasn't been modified, then just return -- do NOT unmap the file */
	if (!(efile->flags & FL_MOD))
		return 0;

	/* File has been modified, so need to write back to disk */
	if ((fptr = fopen(efile->filename, "wb")) == NULL) {
		/* FIXME (sjw Wed Jul 19 05:24:41 2000 ) --- Should give more info here */
		log(LOG_CRITICAL, "Couldn't open target file '%s'",
			efile->filename);
		return 1;
	}

	/* Find size of file -- include space for header.  Segments will be calculated later */
	shdr_start = next_data = data_start = file_size =
		sizeof(Elf32_Ehdr) + (sizeof(Elf32_Phdr) * (efile->nsegments));

	for (i = 0; i < efile->nsegments; i++)
		shdr_start += segs[i].filesize;
	shdr_start = ALIGN(shdr_start, 4);
	memset(&ehdr, 0, sizeof(Elf32_Ehdr));

	/* Write out header */
	ehdr.e_ident[0] = ELF_MAGIC_0;
	ehdr.e_ident[1] = ELF_MAGIC_1;
	ehdr.e_ident[2] = ELF_MAGIC_2;
	ehdr.e_ident[3] = ELF_MAGIC_3;

	ehdr.e_ident[EI_CLASS] = ELFCLASS32;
	ehdr.e_ident[EI_DATA] =
		(efile->endianness == LSB ? ELFDATA2LSB : ELFDATA2MSB);
	ehdr.e_ident[EI_VERSION] = EV_CURRENT;

	write16(ET_EXEC, &(ehdr.e_type), efile->endianness);
	write16(arch2elfmach(efile->arch), &(ehdr.e_machine),
			efile->endianness);
	write32(EV_CURRENT, &(ehdr.e_version), efile->endianness);

	write32(efile->entry + opts->elf_hdr_physaddr, &(ehdr.e_entry), efile->endianness);
	write32(sizeof(Elf32_Ehdr), &(ehdr.e_phoff), efile->endianness);
	write32(shdr_start, &(ehdr.e_shoff), efile->endianness);
	write32(elfarchflags(efile->arch), &(ehdr.e_flags), efile->endianness);
	write16(sizeof(Elf32_Ehdr), &(ehdr.e_ehsize), efile->endianness);
	write16(sizeof(Elf32_Phdr), &(ehdr.e_phentsize), efile->endianness);

	/* FIXME (sjw Wed Jul 19 05:16:11 2000 ) --- Should I include the PHDR segment (spec says not to, I _think_) */
	write16(efile->nsegments, &(ehdr.e_phnum), efile->endianness);
	write16(sizeof(Elf32_Shdr), &(ehdr.e_shentsize), efile->endianness);

	/* Calculate number of section headers: 3 more than actual amount
	 * because we have to create a section header string table and a "null" entry, and binfo*/
	e_shnum = get_num_sections(efile) + 2;
	if (efile->binfo_seg)
		e_shnum += 1;
	write16(e_shnum, &(ehdr.e_shnum), efile->endianness);
	write16(e_shnum - 1, &(ehdr.e_shstrndx), efile->endianness); /* -1 for 0-based index */

	/* Write header to the file */
	if (fwrite(&(ehdr), sizeof(Elf32_Ehdr), 1, fptr) != 1) {
		log(LOG_CRITICAL, "Could not write Ehdr to '%s' (%d)\n",
			efile->filename, ferror(fptr));
		return 1;
	}

	memset(&phdr, 0, sizeof(Elf32_Phdr));

	/* Set up data that doesn't change between segments */
	write32(PT_LOAD, &(phdr.p_type), efile->endianness);

	/* Write out segment headers, and update next_data */
	for (i = 0; i < efile->nsegments; i++) {
		/* FIXME (sjw Tue Aug 15 00:46:39 2000 ) --- This isn't 'properly' aligned */

		/* FIXME (sjw Wed Jul 19 10:04:12 2000 ) --- Flags */
		write32(PF_X | PF_R | PF_W, &(phdr.p_flags), efile->endianness);
		
		write32(next_data, &(phdr.p_offset), efile->endianness);
		if (&segs[i] == efile->binfo_seg) {
			binfo_offset = next_data;
		}
                /* XXX: We shift the vaddr to work around PMON loading segments
                 * into vaddrs on MIPS.  Since some segments (the kernel) are
                 * already in kseg0, we use bitwise or to leave them alone.
                 * -- alexw */
		write32(segs[i].vaddr | opts->elf_hdr_virtaddr, &(phdr.p_vaddr), efile->endianness);
		write32(segs[i].paddr + opts->elf_hdr_physaddr, &(phdr.p_paddr), efile->endianness);
		write32(segs[i].filesize, &(phdr.p_filesz), efile->endianness);
		write32(segs[i].memsize, &(phdr.p_memsz), efile->endianness);
		write32(segs[i].align, &(phdr.p_align), efile->endianness);

		/* Write out header to the file */
		if (fwrite(&phdr, sizeof(Elf32_Phdr), 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write Phdr to '%s' (%d) (\n",
				efile->filename, ferror(fptr));
			return 1;
		}

		next_data += segs[i].filesize;
	}

	/* Write out the actual data */
	next_data = data_start;
	for (i = 0; i < efile->nsegments; i++) {

		if (segs[i].flags & FL_S_PATCH_DIT && (!(efile->flags & FL_NODIT))) {
			void *write_at = segs[i].data +
				(segs[i].patch_addr - segs[i].vaddr);
			writeword(efile->arch, efile->dit_header_segment->paddr,
					  write_at, efile->endianness);
		}
		/* nfd: Don't try writing if we have a data size of 0 */
		if (segs[i].filesize != 0
			&& fwrite(segs[i].data, segs[i].filesize, 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write data to '%s' (%d)\n",
				efile->filename, ferror(fptr));
			return 1;
		}

		next_data += segs[i].filesize;
	}

	/* Fixup offsets of existing sections. */
	/*shdr_start = next_data = data_start = file_size =
		sizeof(Elf32_Ehdr) + (sizeof(Elf32_Phdr) * (efile->nsegments));

	for (i = 0; i < efile->nsegments; i++)
		shdr_start += segs[i].filesize;*/
	struct edit_section *current_section;
	for (i = 0; i < efile->nsegments; i++) {
		for (current_section = efile->first_section;
		     current_section;
		     current_section = current_section -> next) {
			if (current_section->segment_num == i) {
				/* Fixup this section... */
				current_section->output_offset = 
					sizeof(Elf32_Ehdr) + (sizeof(Elf32_Phdr) * (efile->nsegments));
				for (j=0; j < i; j++) {
					current_section->output_offset += segs[j].filesize;
				}
				current_section->output_offset += current_section->segment_offset;
			}
		}
	}

	/* We construct two dummy section headers:
	 * - section header 0, which is empty;
	 * - section header string table.
	*/
	/* ... first section */
	fseek(fptr, shdr_start, SEEK_SET);
	current_section = calloc(1, sizeof(struct edit_section));
	current_section->next = efile->first_section;
	efile->first_section = current_section;
	/* ... final section */

	while(current_section->next != NULL) {
		current_section = current_section->next;
	}

	if (efile->binfo_seg) {
		current_section = current_section->next = 
		    calloc(1, sizeof(struct edit_section));
		current_section->type = SHT_PROGBITS;
		current_section->addr = efile->binfo_seg->paddr;
		assert(binfo_offset != 0);
		current_section->output_offset = binfo_offset;
		current_section->addralign = 0x1000;
		current_section->entsize = 0;
		current_section->flags = SHF_ALLOC;
		current_section->size = efile->binfo_size;
		strcpy(current_section->name, ".binfo");
	}

	uint32_t strtab_size = 1;
	current_section = efile->first_section; /* Get first after null segment */
	while(current_section->next != NULL) {
		strtab_size += strlen(current_section->name) + 1;
		current_section = current_section->next;
	}
	strtab_size += strlen(current_section->name) + 1;
	current_section = current_section->next = calloc(1, sizeof(struct edit_section));
	current_section->type = SHT_STRTAB;
	current_section->addr = 0;
	current_section->output_offset = shdr_start + (sizeof(shdr) * e_shnum);
	current_section->addralign = 1;
	current_section->entsize = 0;
	current_section->flags = 0;
	strcpy(current_section->name, ".shstrtab");
	strtab_size += strlen(current_section->name) + 1;
	current_section->size = strtab_size;

	/* Write out the section headers */
	current_section = efile->first_section;
	uint32_t shstrndx_pos = 1;
	while(current_section) {
		/* name, type, addr, size, addralign, entsize */
		
		write32(shstrndx_pos, &(shdr.sh_name), efile->endianness);
		write32(current_section->type, &(shdr.sh_type), efile->endianness);
		write32(current_section->flags, &(shdr.sh_flags), efile->endianness);
		write32(current_section->addr, &(shdr.sh_addr), efile->endianness);
		write32(current_section->output_offset, &(shdr.sh_offset), efile->endianness); /* FIXME! */
		write32(current_section->size, &(shdr.sh_size), efile->endianness);
		write32(0, &(shdr.sh_link), efile->endianness);
		write32(0, &(shdr.sh_info), efile->endianness);
		write32(current_section->addralign, &(shdr.sh_addralign), efile->endianness);
		write32(current_section->entsize, &(shdr.sh_entsize), efile->endianness);
		if (fwrite(&shdr, sizeof(Elf32_Shdr), 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write Shdr to '%s' (%d)\n",
				efile->filename, ferror(fptr));
			return 1;
		}
		shstrndx_pos += strlen(current_section->name) + 1;
		current_section = current_section->next;
	}

	/* We need to add a section for the bootinfo */

	/* ... finally, the section header string table itself. */
	current_section = efile->first_section;
	/* String table always begins with a null. */
	fwrite("\0", 1, 1, fptr);
	while(current_section) {
		int namelen;
		namelen = strlen(current_section->name);
		if (namelen > 0) {
			fwrite(current_section->name, 1, namelen, fptr);
		}
		fwrite("\0", 1, 1, fptr);
		current_section = current_section->next;
	}
	fclose(fptr);

	return 0;
}

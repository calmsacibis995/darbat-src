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
 *		Project:  EDIT --- Extended DIT
 *		Created:  12/07/2000 19:40:57 by Simon Winwood (sjw)
 *  Last Modified:  27/03/2001 16:57:52 by  (sjw)
 *   Version info:  $Revision: 1.21 $ 
 *	Description:
 *		  This file handles elf64.
 *
 *	   Comments:
 *		  Copied from elf32.c
 *		  I could probably do what BFD does, and have a common core for elf ... see elf_generic.
 *		  BFD requires a section table.  I don't.  However, I want objdump to work, so I have to fake it ;(
 *
 *		License: Relicensed to UNSW OzPLB licence
 *
 *  $Log: elf64.c,v $
 *  Revision 1.21  2004/07/29 07:52:09  nfd
 *  Added dummy header generator (for now)
 *
 *  Revision 1.20  2004/07/21 07:33:31  nfd
 *  - Bootinfo support for platforms with 64-bit word size as well - untested so far
 *  - Fix an alignment bug when setting up the memory descriptors.
 *
 *  Revision 1.19  2004/03/23 07:28:54  benjl
 *  Correctly setup the segment patching.
 *
 *  Revision 1.18  2004/03/10 05:54:18  nfd
 *  Support for writing 64-bit values in 32-bit elf files.
 *
 *  Revision 1.17  2004/03/04 01:43:30  benjl
 *  Readability and -Wall -Werror changes.
 *
 *  Revision 1.16  2001/03/27 07:06:36  sjw
 *  Added copyright notices to all of my files.
 *
 *  Revision 1.15  2000/09/25 09:10:16  sjw
 *  Added -O and -D.
 *
 *  Revision 1.14  2000/09/01 10:18:54  sjw
 *  - Moved the DIT stuff into edit.c (out of backends).
 *  - Cleaned everything up.
 *  - Changed a few flags.
 *  - Changed meaning of a few flags (a, s, ...)
 *
 *  Revision 1.13  2000/08/29 08:14:14  sjw
 *  Fixed some problems with sizing.  Also added -l flag.
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
 *  Revision 1.7  2000/07/24 13:03:23  sjw
 *  More changes.
 *
 *  Revision 1.6  2000/07/20 15:43:48  sjw
 *  Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 *  Seems to be some problems with alignment ...
 *
 *  Revision 1.5  2000/07/19 11:51:59  sjw
 *  Modified interface --- it is now quite different to DIT --- something
 *  of a unholy combination of DIT and sysgen (oh well ... )
 *  Currently it can take multiple entries on the command line.  The actual
 *  building of the DIT header is all that really remains.
 *
 *  Revision 1.4  2000/07/18 16:16:32  sjw
 *  Added some generic ELF routines (conversion between internal format and ELF
 *  machine type)
 *  Did some framework work in edit.c --- mostly dealing with creation of files
 *  etc.
 *  elf32 should now write an ELF file correctly (untested)
 *
 *  Revision 1.3  2000/07/18 06:22:53  sjw
 *  More work.  Added empty coff.[hc], but coff is horrible.
 *
 *  Revision 1.2  2000/07/14 08:32:34  sjw
 *  Added some extra command line options.
 *
 *  Modified interface to readX and writeX so that they don't need to
 *  know about struct edit_file.  This allows write directly to structs.
 *
 *  Revision 1.1  2000/07/13 16:23:48  sjw
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
#include <inttypes.h>

#include "edit.h"
#include "edit_endian.h"
#include "log.h"
#include "elf_generic.h"
#include "elf.h"

int elf64_write(struct edit_file *efile, struct edit_options *opts);

static uint16_t init_segments(uint16_t nsegments, struct edit_segment *segments, uint16_t base_phoff, struct edit_file *efile) 
{
	int i, actual_nsegments = 0; /* = nsegments - #segments_to_ignore */
	int phoff = base_phoff;
	uint32_t p_type; 

	for(i = 0; i < nsegments; i++, phoff += sizeof(Elf64_Phdr)) {
		p_type = read32(offsetof(Elf64_Phdr, p_type) + phoff + efile->mmap, efile->endianness);

		if(p_type != PT_LOAD)
			continue;

		segments[actual_nsegments].vaddr = 
				read64(offsetof(Elf64_Phdr, p_vaddr) + phoff + efile->mmap, 
					   efile->endianness);

		segments[actual_nsegments].paddr = 
				read64(offsetof(Elf64_Phdr, p_paddr) + phoff + efile->mmap, 
					   efile->endianness);

		segments[actual_nsegments].memsize = 
				read64(offsetof(Elf64_Phdr, p_memsz) + phoff + efile->mmap, 
					   efile->endianness);


		segments[actual_nsegments].filesize = 
				read64(offsetof(Elf64_Phdr, p_filesz) + phoff + efile->mmap, 
					   efile->endianness);
		segments[actual_nsegments].align = 
				read64(offsetof(Elf64_Phdr, p_align) + phoff + efile->mmap, 
					   efile->endianness);

		segments[actual_nsegments].elf_flags =
			read32(offsetof(Elf64_Phdr, p_flags) + phoff + efile->mmap,
				   efile->endianness);

		/* Ignore flags */
		if((efile->flags & FL_PATCH_FILE) && 
		   (efile->patch_addr >= segments[actual_nsegments].vaddr) &&
		   (efile->patch_addr < segments[actual_nsegments].memsize +
			segments[actual_nsegments].vaddr)
		   ) {
				segments[actual_nsegments].flags |= FL_S_PATCH_DIT;
				segments[actual_nsegments].patch_addr = efile->patch_addr;
		}


		segments[actual_nsegments].data = efile->mmap + read64(offsetof(Elf64_Phdr, p_offset) + phoff + efile->mmap, efile->endianness);
		
		/* look at next segment */
		actual_nsegments++;
	}

	return actual_nsegments;
}

void *
elf64_create_headers(struct edit_file *efile, size_t *size)
{
		printf("No support for elf64 SimpleElf structures yet - did you forget to "
						"include --binfo-sexec?\n");
		exit(1);
}

uint64_t
elf64_calculate_efile_size(struct edit_file *efile)
{
	int idx_low, idx_high, i;

	idx_low = idx_high = 0;

	for (i = 0; i < efile->nsegments; i++) {
		if(efile->segments[i].vaddr < efile->segments[idx_low].vaddr)
			idx_low = i;
		if(efile->segments[i].vaddr > efile->segments[idx_high].vaddr)
			idx_high = i;
	}
	return efile->segments[idx_high].vaddr - efile->segments[idx_low].vaddr
		+ efile->segments[idx_high].memsize;
}

int elf64_register(struct edit_file *efile)
{
	char *e_ident = efile->mmap;
	uint16_t phoff;
	int elfmach;
	struct edit_segment *segs;
	int i;

	if(efile->flags & FL_NEW) {
		if(efile->objtype == OBJ_ELF64) {
			log(LOG_LOW, "Creating a new elf64 file '%s'\n", efile->filename);
			efile->write_file = elf64_write;
			/* FIXME (sjw Tue Sep 26 02:45:42 2000 ) --- yuck. */
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
		
	if(e_ident[EI_CLASS] != ELFCLASS64)
		return 1;
	   
	/* Possibly allow for old elf formats */
	if(e_ident[EI_VERSION] != EV_CURRENT)
		return 1;

	/* Don't care whether or not it is executable.  Let the user shoot
	 * themself in the foot, but somebody might want to do it someday */
		
	/* File is a elf64, so set everything up */
	
	efile->objtype = OBJ_ELF64;
	if(e_ident[EI_DATA] == ELFDATA2LSB)
		efile->endianness = LSB;
	else if(e_ident[EI_DATA] == ELFDATA2MSB)
		efile->endianness = MSB;
	else {
		log(LOG_WARNING, "Unknown endianness: %d\n", e_ident[EI_DATA]);
		return 1;
	}

	elfmach = read16(offsetof(Elf64_Ehdr, e_machine) + efile->mmap, efile->endianness);

	efile->arch = elfmach2arch(elfmach);
	efile->pagesize = elfarch_pagesize(efile->arch);

	if(efile->arch == ARCH_INVALID) {		
		log(LOG_WARNING, "Unknown machine type: %d\n", elfmach);
		return 1;
	}

	efile->write_file = elf64_write;

	efile->entry = read64(offsetof(Elf64_Ehdr, e_entry) + efile->mmap, efile->endianness);
	efile->nsegments = read16(offsetof(Elf64_Ehdr, e_phnum) + efile->mmap, efile->endianness);

	phoff = read64(offsetof(Elf64_Ehdr, e_phoff) + efile->mmap, efile->endianness);

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
	segs[i].memsize = ALIGN(segs[i].memsize + segs[i].vaddr, efile->alignment) - segs[i].vaddr;

	/* Calculate size by adding memsize of all segments. */
	efile->size = elf64_calculate_efile_size(efile);
	printf("set efile size to %llx\n", efile->size);

	/* Set the correct header generator */
	efile->elf_create_headers = elf64_create_headers;

	efile->word_size = arch_to_wordsize(efile->arch);	
	return 0;
}

int elf64_write(struct edit_file *efile, struct edit_options *opts)
{
	FILE *fptr;
	int file_size, data_start, next_data, i;
	struct edit_segment *segs = efile->segments; 
	Elf64_Ehdr ehdr;
	Elf64_Shdr shdr;
	Elf64_Phdr phdr;

	/* If the file hasn't been modified, then just return -- do NOT unmap the file */
	if(!(efile->flags & FL_MOD))
		return 0;

	/* File has been modified, so need to write back to disk */
	if((fptr = fopen(efile->filename, "wb")) == NULL) {
		/* FIXME (sjw Wed Jul 19 05:24:41 2000 ) --- Should give more info here */		
		log(LOG_CRITICAL, "Couldn't open target file '%s'", efile->filename);
		return 1;
	}

	/* Find size of file -- include space for header.  Segments will be calculated later */
	next_data = data_start = file_size = sizeof(Elf64_Ehdr) + sizeof(Elf64_Shdr)
		+ (sizeof(Elf64_Phdr) * (efile->nsegments));

	memset(&ehdr, 0, sizeof(Elf64_Ehdr));
	
	/* Write out header */
	ehdr.e_ident[0] = ELF_MAGIC_0;
	ehdr.e_ident[1] = ELF_MAGIC_1;
	ehdr.e_ident[2] = ELF_MAGIC_2;
	ehdr.e_ident[3] = ELF_MAGIC_3;
	
	ehdr.e_ident[EI_CLASS] = ELFCLASS64;
	ehdr.e_ident[EI_DATA] = (efile->endianness == LSB ? ELFDATA2LSB : ELFDATA2MSB);
	ehdr.e_ident[EI_VERSION] = EV_CURRENT;

	write16(ET_EXEC, &(ehdr.e_type), efile->endianness);
	write16(arch2elfmach(efile->arch), &(ehdr.e_machine), efile->endianness);
	write32(EV_CURRENT, &(ehdr.e_version), efile->endianness);

	if(efile->flags & FL_PHYS_ENTRY) {
			write64(efile->entry + opts->elf_hdr_physaddr,
					&(ehdr.e_entry), efile->endianness);
	} else {
			write64(efile->entry, &(ehdr.e_entry), efile->endianness); 
	}
	write64(sizeof(Elf64_Ehdr) + sizeof(Elf64_Shdr), &(ehdr.e_phoff), efile->endianness);
	write64(0, &(ehdr.e_shoff), efile->endianness);
	write32(elfarchflags(efile->arch), &(ehdr.e_flags), efile->endianness);
	write16(sizeof(Elf64_Ehdr), &(ehdr.e_ehsize), efile->endianness);
	write16(sizeof(Elf64_Phdr), &(ehdr.e_phentsize), efile->endianness);

	/* FIXME (sjw Wed Jul 19 05:16:11 2000 ) --- Should I include the PHDR segment 
	   (spec says not to, I _think_) 
	*/
	write16(efile->nsegments, &(ehdr.e_phnum), efile->endianness);
	write16(0 /*sizeof(Elf64_Shdr)*/, &(ehdr.e_shentsize), efile->endianness);
	write16(0, &(ehdr.e_shnum), efile->endianness);
	write16(SHN_UNDEF, &(ehdr.e_shstrndx), efile->endianness);

	/* Write header to the file */
	if(fwrite(&(ehdr), sizeof(Elf64_Ehdr), 1, fptr) != 1) {
		log(LOG_CRITICAL, "Could not write to '%s'\n", efile->filename);
		return 1;
	}

	memset(&shdr, 0, sizeof(Elf64_Shdr));
	if(fwrite(&shdr, sizeof(Elf64_Shdr), 1, fptr) != 1) {
		log(LOG_CRITICAL, "Could not write to '%s'\n", efile->filename);
		return 1;
	}

	memset(&phdr, 0, sizeof(Elf64_Phdr));

	/* Set up data that doesn't change between segments */
	write32(PT_LOAD, &(phdr.p_type), efile->endianness);

	/* Write out segment headers, and update next_data */
	for(i = 0; i < efile->nsegments; i++) {
		/* FIXME (sjw Tue Aug 15 00:43:17 2000 ) --- We don't align this as according to the ELF spec ... don't need to */
		
		/* FIXME (sjw Wed Jul 19 10:04:12 2000 ) --- Flags */
		write32(PF_X | PF_R | PF_W, &(phdr.p_flags), efile->endianness);

		write64(next_data, &(phdr.p_offset), efile->endianness);
                /* XXX: Bitwise or used to be consistent with elf32.c
                 * see comment in that file -- alexw                    */
		write64(segs[i].vaddr | opts->elf_hdr_virtaddr, &(phdr.p_vaddr), efile->endianness);
		write64(segs[i].paddr + opts->elf_hdr_physaddr, &(phdr.p_paddr), efile->endianness);
		write64(segs[i].filesize, &(phdr.p_filesz), efile->endianness);
		write64(segs[i].memsize, &(phdr.p_memsz), efile->endianness);
		write64(segs[i].align, &(phdr.p_align), efile->endianness);

		/* Write out header to the file */
		if(fwrite(&phdr, sizeof(Elf64_Phdr), 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write to '%s'\n", efile->filename);
			return 1;
		}

		next_data += segs[i].filesize;
	}

	/* Write out the actual data */
	next_data = data_start;
	for(i = 0; i < efile->nsegments; i++) {

		if (segs[i].flags & FL_S_PATCH_DIT &&
			(!(efile->flags & FL_NODIT))) {
				void *write_at = segs[i].data + 
						(segs[i].patch_addr - segs[i].vaddr);
				printf("Writing dit magic: %" PRIx64 "\n", segs[i].patch_addr);
				writeword(efile->arch, efile->dit_header_segment->paddr, 
						write_at, efile->endianness);
		}
		
		log(LOG_LOW, "Writing segment %d at 0x%x (0x%" PRIx64 
			", 0x%" PRIx64 ")\n", i, next_data, 
			segs[i].paddr, segs[i].align); 
		
		if(fwrite(segs[i].data, segs[i].filesize, 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write to '%s'\n", efile->filename);
			return 1;
		}

		next_data += segs[i].filesize;
	}

	fclose(fptr);

	return 0;
}




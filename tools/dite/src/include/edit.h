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
 *        Created:  12/07/2000 17:35:28 by Simon Winwood (sjw)
 *  Last Modified:  06/09/2002 16:54:14 by Simon Winwood (sjw)
 *   Version info:  $Revision: 1.26 $ 
 *    Description:
 *
 *       Comments:
 *
 *        License: Relicensed under the UNSW OzPLB
 *
 * $Log: edit.h,v $
 * Revision 1.26  2004/07/29 07:50:21  nfd
 * Added "options" structure for options that only affect the target.
 *
 * Revision 1.25  2004/07/28 05:04:20  nfd
 * added "elf_create_headers" function - 32bit only so far - to help binfo create SimpleElf structures.
 * added a new flag FL_BINFO_SEXEC which binfo uses to determine whether applications in the image should be represented in the bootinfo by SimpleExec structures, or by SimpleElf structures.
 *
 * Revision 1.24  2004/07/26 08:14:01  nfd
 * Create the bootinfo from the edit_segment structures, rather than from the dit structures. This is how the dit is created, too, so the procedure is less manky now. Also have a guess at which segments are executable, and which are data, based on the permissions of the program headers in the source files. This means changes to the elf-reading functions to store the phdr flags in the edit_segment struct.
 *
 * Revision 1.23  2004/07/23 07:17:55  nfd
 * edit doesn't pretend to know what the internal format of bootinfo is now.
 *
 * Revision 1.22  2004/07/21 07:33:30  nfd
 * - Bootinfo support for platforms with 64-bit word size as well - untested so far
 * - Fix an alignment bug when setting up the memory descriptors.
 *
 * Revision 1.21  2004/07/21 01:29:24  nfd
 * Bootinfo and KCP pointers. Added bootinfo- and kcp-related flags. Added ALIGN_DOWN macro.
 *
 * Revision 1.20  2004/03/23 07:29:51  benjl
 * Split to fit in 80 col.
 *
 * Revision 1.19  2004/03/10 05:53:39  nfd
 * Add support for writing 64-bit pointers even if image is elf32.
 *
 * Revision 1.18  2004/03/04 01:33:44  benjl
 * Added flag to allow a section to be physically aligned by
 * dite. This basically means that the ELF will be relocated in
 * physical (but not virtual) memory.
 *
 * Revision 1.17  2004/02/26 09:37:55  benjl
 * Modified so that the patch address is specfied on the command line.
 *
 * Revision 1.16  2004/02/26 08:01:21  benjl
 * Added per segments flags.
 * Defined per segment flag for patching a file.
 * Added perf file KERNEL, SIGMA0, SIGMA1 and ROOT flags.
 *
 * Revision 1.15  2002/09/06 07:06:24  sjw_
 * Added IA64 support, and --name flag
 *
 * Revision 1.14  2002/06/07 02:32:45  sjw_
 * Removed 'in-place' flag.
 *
 * Revision 1.13  2001/03/27 07:06:37  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.12  2000/09/25 09:10:16  sjw
 * Added -O and -D.
 *
 * Revision 1.11  2000/09/01 10:18:54  sjw
 * - Moved the DIT stuff into edit.c (out of backends).
 * - Cleaned everything up.
 * - Changed a few flags.
 * - Changed meaning of a few flags (a, s, ...)
 *
 * Revision 1.10  2000/08/30 04:13:19  sjw
 * Added seed.
 *
 * Revision 1.9  2000/08/14 15:03:44  sjw
 * Version 0.1.4
 * ! Added --align and --nodit options (don't need pad.c anymore).
 * ! Fixed a few minor bugs.
 *
 * Revision 1.8  2000/08/07 09:37:17  sjw
 * It now builds with automake and autoconf.  This means that it now builds
 * ok on OSF1, schlags broken redhat and debian.
 *
 * Revision 1.7  2000/07/24 13:03:23  sjw
 * More changes.
 *
 * Revision 1.6  2000/07/20 15:43:48  sjw
 * Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 * Seems to be some problems with alignment ...
 *
 * Revision 1.5  2000/07/19 11:51:59  sjw
 * Modified interface --- it is now quite different to DIT --- something
 * of a unholy combination of DIT and sysgen (oh well ... )
 * Currently it can take multiple entries on the command line.  The actual
 * building of the DIT header is all that really remains.
 *
 * Revision 1.4  2000/07/18 16:16:32  sjw
 * Added some generic ELF routines (conversion between internal format and ELF
 * machine type)
 * Did some framework work in edit.c --- mostly dealing with creation of files
 * etc.
 * elf32 should now write an ELF file correctly (untested)
 *
 * Revision 1.3  2000/07/14 08:32:34  sjw
 * Added some extra command line options.
 *
 * Modified interface to readX and writeX so that they don't need to
 * know about struct edit_file.  This allows write directly to structs.
 *
 * Revision 1.2  2000/07/13 16:23:48  sjw
 * elf32 and elf64 now seem to work, in that they fill in the correct info in the
 * edit_file structure.
 * Need to figure out the required abstractions.  Probably only set_section etc.
 *
 * Added dit.h from mipsL4 distro, and elf.h from linux.
 *
 */

#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include <stdbool.h>

#include "edit_types.h"
#include "edit_endian.h"
#include "edit_arch.h"
#include "elf.h"
#include "dit.h"

typedef uint64_t edit_addr;

/* Yeah it shouldn't be here, but everything uses it ;) */
#define ALIGN(a, s)  ((((a) + (s) - 1) / (s)) * (s))
#define ALIGN_DOWN(a, s)  ( ((a)/(s)) * (s) )

#ifdef DEBUG
#define debug(x...) fprintf(stderr, x);
#else
#define debug(x...) 
#endif /* DEBUG */


  
enum objtype {
    OBJ_INVALID,
    OBJ_ELF32,
    OBJ_ELF64,
    OBJ_ECOFF,
    OBJ_RAW,
    OBJ_MACHO,	/* 32-bit Mach-O */
    OBJ_MACHO64	/* 64-bit Mach-O */
};  

struct edit_file;

enum edit_segment_flags {
	FL_S_PATCH_DIT = 1 << 0,
};

struct edit_segment {
    edit_addr vaddr;    /* 'Virtual' address (for DIT) */
    edit_addr paddr;    /* Physical address (for loader) */
    uint64_t memsize;
    uint64_t filesize;
    uint64_t align;     /* Alignment of section within file 
			   (0, 1 any alignment ) */ 
    uint64_t elf_flags;
    enum edit_segment_flags flags;
    edit_addr patch_addr; /* Patch this ! */

    void *data;
};

enum edit_file_flags {
    FL_NEW = 1 << 0,
    FL_MOD = 1 << 1,
    FL_EXEC = 1 << 2,
    FL_RESOURCE = 1 << 3,
    FL_DIT = 1 << 4,      /* Whether or not it has been added to DIT */
    FL_NODIT = 1 << 5,    /* Whether or not to include the DIT segment */
    FL_SEEDY = 1 << 6,    /* Modify sigma0 so that l4bl doesn't need to */
    FL_UPDATE = 1 << 7,   /* Whether or not to update an existing file 
			     (i.e. a source file is also the target) */
    FL_PATCH_FILE = 1 << 8,   
    FL_KERNEL = 1 << 9,
    FL_SIGMA0 = 1 << 10,
    FL_SIGMA1 = 1 << 11,
    FL_ROOT = 1 << 12,
    FL_PHYS_ALIGN = 1 << 13,
	FL_USE_BINFO = 1 << 14, /* Whether to include an L4 BootInfo header */
	FL_PHYS_ENTRY = 1 << 15, /* Physical entry point */
	FL_BINFO_SEXEC = 1 << 16, /* Use SimpleExec. */
};

/* Options that only affect the target */
struct edit_options {
	edit_addr kcp_mainmem_low;
	edit_addr kcp_mainmem_high;
	uint64_t elf_hdr_physaddr;
	uint64_t elf_hdr_virtaddr;
};

#define EDIT_SECTION_NAME_SIZE 256

struct edit_section {
	struct edit_section *next;

	char name[EDIT_SECTION_NAME_SIZE];
	uint64_t type;
	uint64_t addr; /* Address from loaded process' perspective */
	uint64_t size; /* Size of section in bytes */
	uint64_t orig_offset; /* Offset from beginning of file */
	uint64_t output_offset; /* Offset from beginning of target file */
	uint64_t addralign;
	uint64_t entsize;
	uint64_t flags;
	/* segment_offset and segment_num are used to fix up offsets when writing
	 * from one elf to another. */
	uint64_t segment_offset; /* Offset from beginning of specified segment */
	uint32_t segment_num; /* Segment number for segment_offset */
};

/* This struct defines the interface between the backends and the frontend */
struct edit_file {

    /* Set up before *_register is called */
    const char *filename;
    const char *ditname;

    /* The -M `magic' field */
    edit_addr ditmagic;
	edit_addr kcp;

	/* Word size - either deduced from architecture ('arch', below) or specified
	 * on cmdline */
	size_t word_size;

    /* The address where we want to patch in the dit address */
    edit_addr patch_addr;

    void *mmap;
    /* elf manipulation functions */
    /* Return a new Ehdr followed by the section headers. Set the e_shoff value
     * in the Ehdr to point to the section headers. Return the size of the thing
     * in *size. */
    void *(*elf_create_headers)(struct edit_file *efile, size_t *size); 

    uint64_t size;
    
    /* (last segment vaddr) + (last segment memsize) % alignment == 0 */
    uint32_t alignment;
    
    uint32_t pagesize;
    

    /* after writing target, vaddr > offset && paddr > offset 
       --- for MIPS, mostly */
    uint64_t offset;

    /* General flags */
    enum edit_file_flags flags;


    /* Set up by *_register or from source (for new file) */
    enum arch arch;
    enum objtype objtype;
    enum endianness endianness;

    /* Writes the file to disk */
    int (*write_file)(struct edit_file *efile, struct edit_options *opts);

    edit_addr entry;
    edit_addr base_address;

    /* Number of DIT entries (only valid for targets) */
    int ndit;
    int dit_type;   /* 0 = invalid, 1 = 32-bit, 2 = 64-bit */
    Dit_Phdr *phdrs;

    struct edit_segment *dit_header_segment;

    int nsegments;
    /* Segment descriptors and data, sorted on ascending addresses (physical) */
    struct edit_segment *segments;
	
	/* Bootinfo structure */
	size_t binfo_size;
	void *binfo;
	struct edit_segment *binfo_seg;
	/* Absolute physical and virtual addresses for raw files. */
	/* FIXME: Really we should be storing this in segments[0].{paddr,vaddr}
	* instead */
	edit_addr paddr;
	edit_addr vaddr;

	/* Section headers */
	struct edit_section *first_section;
};

/* Returns 0 if efile is a valid file of that object type, 1 otherwise */
typedef int (*register_func)(struct edit_file *efile);

int raw_register(struct edit_file *efile);
int elf32_register(struct edit_file *efile);
int elf64_register(struct edit_file *efile);
int ecoff_register(struct edit_file *efile);
int macho_register(struct edit_file *efile);

int merge_dit(struct edit_file *target, struct edit_file *source);
int add_dit_entry(struct edit_file *target, struct edit_file *entry);

/* Adds a DIT segment */
uint64_t add_dit_segment(struct edit_file *efile, int dit_segment);
int print_dit(struct edit_file *efile);

#endif  /* EDIT_H */







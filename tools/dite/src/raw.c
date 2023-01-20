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
 *        Project:  
 *        Created:  19/07/2000 21:16:23 by Simon Winwood (sjw)
 *  Last Modified:  27/03/2001 16:58:30 by  (sjw)
 *   Version info:  $Revision: 1.12 $ 
 *    Description:
 *
 *       Comments:
 *
 *        License: Relicensed under the UNSW OzPLB 
 *
 * $Log: raw.c,v $
 * Revision 1.12  2004/03/04 01:41:02  benjl
 * -Wall -Werror changes.
 *
 * Revision 1.11  2004/02/26 08:05:22  benjl
 * Made raw file based on files physical, not virtual addresses.
 *
 * Revision 1.10  2001/03/27 07:06:36  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.9  2000/10/06 02:49:14  sjw
 * Fixed but wrt raw and pagesize.
 *
 * Revision 1.8  2000/09/02 09:02:13  sjw
 * Fixed a minor bug with alignment
 *
 * Revision 1.7  2000/09/01 10:18:54  sjw
 * - Moved the DIT stuff into edit.c (out of backends).
 * - Cleaned everything up.
 * - Changed a few flags.
 * - Changed meaning of a few flags (a, s, ...)
 *
 * Revision 1.6  2000/08/30 04:13:19  sjw
 * Added seed.
 *
 * Revision 1.5  2000/08/14 15:03:44  sjw
 * Version 0.1.4
 * ! Added --align and --nodit options (don't need pad.c anymore).
 * ! Fixed a few minor bugs.
 *
 * Revision 1.4  2000/08/04 08:09:29  sjw
 * Added raw output functionality.
 * Added getopt from gcc (so I can use long opts in a portable way ;)
 *
 * Revision 1.3  2000/07/25 08:18:53  sjw
 * Fixed bug in elf64.  Still pretty hacky, need to clean up arch independance
 * bit (i.e. pagesizes etc.), but it works well enough for l4/alpha.
 *
 * Revision 1.2  2000/07/20 15:43:48  sjw
 * Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 * Seems to be some problems with alignment ...
 *
 * Revision 1.1  2000/07/19 11:51:59  sjw
 * Modified interface --- it is now quite different to DIT --- something
 * of a unholy combination of DIT and sysgen (oh well ... )
 * Currently it can take multiple entries on the command line.  The actual
 * building of the DIT header is all that really remains.
 *
 */


#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>


#include "edit.h"
#include "log.h"

extern unsigned long elfarch_pagesize(enum arch arch);

int raw_write(struct edit_file *efile, struct edit_options *opts);

int raw_register(struct edit_file *efile)
{
    struct edit_segment *seg;

    if(efile->objtype != OBJ_RAW)
	return 1;

    efile->write_file = raw_write;
    /* FIXME (sjw Fri Oct  6 13:46:44 2000 ) --- Badly named */
    efile->pagesize = elfarch_pagesize(efile->arch);

    if(efile->flags & FL_NEW) 
	return 0;

    /* Leave efile->entry as it is (NULL unless set 
     * at command line */

    efile->nsegments = 1;
    if((seg = malloc(sizeof(struct edit_segment))) == NULL) {
	log(LOG_CRITICAL, "Cannot allocate memory %s\n", efile->filename);
	exit(EXIT_FAILURE);
    }

    seg->vaddr = seg->paddr = efile->base_address;
    seg->filesize = efile->size;

    /* Do any rounding up, and update size */
    efile->size = seg->memsize = ALIGN(seg->filesize + seg->vaddr, efile->alignment) - seg->vaddr;
    seg->align = 1;
    seg->data = efile->mmap;

    efile->segments = seg;

    /* No add section */
    {
	struct edit_section *current_section, *prev_section;
	current_section = malloc(sizeof(struct edit_section));
	current_section->next = NULL;
	
	strcpy(current_section->name, ".raw.");
	strcat(current_section->name, efile->ditname);

	current_section->type = SHT_PROGBITS;
	current_section->addr = seg->vaddr;
	current_section->output_offset = 0x37;
	current_section->size = seg->filesize;
	current_section->addralign = 1;
	current_section->entsize = 0;
	current_section->flags = SHF_ALLOC;
	
	efile->first_section = current_section;
    }
    return 0;
}

/* If the file has been modified, then we need to write it to disk */
int raw_write(struct edit_file *efile, struct edit_options *opts)
{
    FILE *fptr;
    uint64_t base_offset, dit_vaddr;
    struct edit_segment *segs = efile->segments;
    int i, zero = 0;

    /* If the file hasn't been modified, then just return -- do NOT unmap the file */
    if(!(efile->flags & FL_MOD))
	return 0;

    /* File has been modified, so need to write back to disk */
    if((fptr = fopen(efile->filename, "w")) == NULL) {
	/* FIXME (sjw Wed Jul 19 05:24:41 2000 ) --- Should give more info here */	
	log(LOG_CRITICAL, "Couldn't open target file '%s': %s", efile->filename, strerror(errno));
	return 1;
    }

    log(LOG_LOW, "Target base 0x%" PRIx64 ", entry 0x%" PRIx64 "\n", 
	efile->segments[0].paddr, efile->entry);

    base_offset = segs[0].paddr;

    /* Do the actual output */
    for(i = 0; i < efile->nsegments; i++) {
	if(fseek(fptr, segs[i].paddr - base_offset, SEEK_SET) != 0) {
		log(LOG_CRITICAL, "Couldn't fseek on '%s': %s\n", efile->filename, 
		    strerror(errno));
	    return 1;
	}
	    
	/* Write data */
	log(LOG_LOW, "Writing segment %d (0x%" PRIx64 
	    ", 0x%" PRIx64 ")\n", i, segs[i].paddr, segs[i].paddr);	
	log(LOG_LOW, "Seek to: %" PRIx64 "\n", segs[i].paddr - base_offset);
	if(fwrite(segs[i].data, segs[i].filesize, 1, fptr) != 1) {
	    log(LOG_CRITICAL, "Could not write to '%s': %s\n", efile->filename, 
		strerror(errno));
	    return 1;
	}
    }

    --i;
    /* Round up final memsize */
    if(fseek(fptr, segs[i].paddr + segs[i].memsize - 1 - base_offset, SEEK_SET) != 0) {
	log(LOG_CRITICAL, "Couldn't fseek on '%s': %s\n", efile->filename, strerror(errno));
	return 1;
    }
    
    if(fwrite(&zero, 1, 1, fptr) != 1) {
	log(LOG_CRITICAL, "Could not write to '%s': %s\n", efile->filename, strerror(errno));
	return 1;
    }

    /* Seedy hack to get sigma0 right */
    if(efile->flags & FL_SEEDY) {
	dit_vaddr = segs[i].paddr;
	    
	/* FIXME (sjw Fri Sep  1 13:44:27 2000 ) --- Ugly */
	if(fseek(fptr, segs[1].paddr - base_offset + 4 * sizeof(uint64_t), SEEK_SET) != 0) {
	    log(LOG_CRITICAL, "Couldn't fseek on '%s': %s\n", efile->filename, strerror(errno));
	    return 1;
	}
	
	write64(dit_vaddr, &dit_vaddr, efile->endianness);

	/* Write data */
	log(LOG_LOW, "Modifying sigma0 (0x%" PRIx64 " 0x%" PRIx64 ")\n", 
	    dit_vaddr, segs[1].paddr - base_offset + 4 * sizeof(uint64_t));
	if(fwrite(&dit_vaddr, sizeof(uint64_t), 1, fptr) != 1) {
	    log(LOG_CRITICAL, "Could not write to '%s': %s\n", efile->filename, strerror(errno));
	    return 1;
	}
    }

    return 0;
}

/*
 * Local Variables: ***
 * compile-command: "make -C ../ src/raw.o" ***
 * End: ***
 */


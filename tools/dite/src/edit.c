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
 *        Created:  12/07/2000 19:46:03 by Simon Winwood (sjw)
 *  Last Modified:  24/01/2003 17:51:04 by Simon Winwood (sjw)
 *   Version info:  $Revision: 1.47 $ 
 *    Description:
 *          Main file for EDIT.
 *
 *       Comments:
 *          According to the MIPS sigma0, the DIT is the very last phdr.
 *
 *        License: Relicensed under the UNSW OzPLB license.
 *
 * $Log: edit.c,v $
 * Revision 1.47  2004/08/03 03:45:54  nfd
 * -l now returns paddr not vaddr.
 *
 * Revision 1.46  2004/07/29 07:51:22  nfd
 * When using a memory offset, only offset the paddr, not the vaddr.
 *
 * Revision 1.45  2004/07/28 05:09:29  nfd
 * Added long option --binfo-sexec.
 * Bugfix: getopt_long returns an int, not a char
 * Fix a comment.
 * Remove some useless debug.
 *
 * Revision 1.44  2004/07/26 08:14:02  nfd
 * Create the bootinfo from the edit_segment structures, rather than from the dit structures. This is how the dit is created, too, so the procedure is less manky now. Also have a guess at which segments are executable, and which are data, based on the permissions of the program headers in the source files. This means changes to the elf-reading functions to store the phdr flags in the edit_segment struct.
 *
 * Revision 1.43  2004/07/26 04:32:30  nfd
 * Support for printing bootinfo struct.
 *
 * Revision 1.42  2004/07/21 07:33:31  nfd
 * - Bootinfo support for platforms with 64-bit word size as well - untested so far
 * - Fix an alignment bug when setting up the memory descriptors.
 *
 * Revision 1.41  2004/07/21 01:41:27  nfd
 * Support more options:
 * 	-B : Include a BootInfo segment and patch the KCP to point it. Also set correct addresses for kernel, sigma0 and the root task in the KCP.
 * 	-p : The following segment has a paddr entry point; assume that the current entrypoint is a virtual address, and convert it to a physical one.
 * 	-K : Specify the virtual address of the KCP
 * Fix debug statements.
 * Slighly more informative error message, and exit with an error code, if file could not be written.
 *
 * Revision 1.40  2004/03/23 07:28:19  nfd
 * When using the -A flag, ensure that new phys addr is aligned to the same spot mod the page size as the virt addr.
 *
 * Revision 1.39  2004/03/16 05:45:02  cvansch
 * Support base_offset for elf files - physical address
 *
 * Revision 1.38  2004/03/05 04:57:39  benjl
 * Updated help to be consistent with implementation.
 * Changed strtoul to strtoull so that long addresses can be specified
 * on 32-bit machines.
 *
 * Revision 1.37  2004/03/04 01:40:04  benjl
 * Added FL_PHYS_ALIGN handling. This allows ELF segments to be
 * reloacted in physical, (but not virtual) memory.
 *
 * Removed unused variables to allow this to compile with -Wall -Werror
 *
 * Revision 1.36  2004/02/26 09:37:56  benjl
 * Modified so that the patch address is specfied on the command line.
 *
 * Revision 1.35  2004/02/26 08:04:43  benjl
 * Changes to make 80-character lines.
 * Added ARM architecture.
 * Added command line options for new fields and flags.
 *
 * Revision 1.34  2003/01/24 06:56:58  sjw_
 * Fixed small bug with --name (andrewb)
 *
 * Revision 1.33  2002/09/06 08:19:21  sjw_
 * Added N flag to opts
 *
 * Revision 1.32  2002/09/06 07:06:24  sjw_
 * Added IA64 support, and --name flag
 *
 * Revision 1.31  2002/06/07 04:48:50  sjw_
 * OBJ_RAW, not FL_RAW.  Sigh.
 *
 * Revision 1.30  2002/06/07 04:44:32  sjw_
 * Fixed FL_RAW
 *
 * Revision 1.29  2002/06/07 04:23:45  sjw_
 * Removed DEBUG
 *
 * Revision 1.28  2002/06/07 02:32:45  sjw_
 * Removed 'in-place' flag.
 *
 * Revision 1.27  2002/06/03 08:44:47  sjw_
 * MIPS changes
 *
 * Revision 1.26  2001/03/27 07:06:36  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.25  2001/03/21 14:30:30  sjw
 * Documentation fixes only --- added a manpage, and fixed an error in the
 * help screen.
 *
 * Revision 1.24  2000/11/29 04:25:02  nash
 * Added an inplace flag - this allows it to be used as a replacement for dit more easily.  Note the implementastion is a little seedy.
 *
 * Revision 1.23  2000/09/25 09:10:16  sjw
 * Added -O and -D.
 *
 * Revision 1.22  2000/09/22 04:27:00  sjw
 * 0.2.2: Updated the help screen, minor cosmetic fixes for elf32.c
 *
 * Revision 1.21  2000/09/03 10:35:15  sjw
 * Fixed a bug where the entry of the target wasn't being set properly.
 *
 * Revision 1.20  2000/09/01 10:18:54  sjw
 * - Moved the DIT stuff into edit.c (out of backends).
 * - Cleaned everything up.
 * - Changed a few flags.
 * - Changed meaning of a few flags (a, s, ...)
 *
 * Revision 1.19  2000/08/30 04:13:19  sjw
 * Added seed.
 *
 * Revision 1.18  2000/08/29 08:14:14  sjw
 * Fixed some problems with sizing.  Also added -l flag.
 *
 * Revision 1.17  2000/08/25 01:03:49  sjw
 * Added '-l' support ... little bit seedy tho ;(
 *
 * Revision 1.16  2000/08/17 07:39:53  sjw
 * Fixed a bug where atoi breaks --- used strtoul instead.
 *
 * Revision 1.15  2000/08/14 15:09:09  sjw
 * Should have used align instead of pad ;(
 *
 * Revision 1.14  2000/08/14 15:03:44  sjw
 * Version 0.1.4
 * ! Added --align and --nodit options (don't need pad.c anymore).
 * ! Fixed a few minor bugs.
 *
 * Revision 1.13  2000/08/08 12:32:56  sjw
 * Fixed a bug with setting the entry (I was setting it for the source,
 * not the target).  Not really worth incrementing the version tho.
 *
 * Revision 1.12  2000/08/07 09:37:17  sjw
 * It now builds with automake and autoconf.  This means that it now builds
 * ok on OSF1, schlags broken redhat and debian.
 *
 * Revision 1.11  2000/08/04 08:09:29  sjw
 * Added raw output functionality.
 * Added getopt from gcc (so I can use long opts in a portable way ;)
 *
 * Revision 1.10  2000/07/25 08:18:53  sjw
 * Fixed bug in elf64.  Still pretty hacky, need to clean up arch independance
 * bit (i.e. pagesizes etc.), but it works well enough for l4/alpha.
 *
 * Revision 1.9  2000/07/24 14:48:47  sjw
 * Very basic functionality complete -- i.e. it can take in multiple elf32 or
 * elf64 files and spit out 1 elf32 file (strange bug in elf64.c?) which can
 * be recognized by 'dit'.  Still need to implement '-l' flags, but otherwise
 * it's mostly usable.
 *
 * Revision 1.8  2000/07/24 13:03:23  sjw
 * More changes.
 *
 * Revision 1.7  2000/07/20 15:43:48  sjw
 * Mostly finished (I _think_).  Still a bit more DIT handling to work on tho ...
 * Seems to be some problems with alignment ...
 *
 * Revision 1.6  2000/07/19 11:51:59  sjw
 * Modified interface --- it is now quite different to DIT --- something
 * of a unholy combination of DIT and sysgen (oh well ... )
 * Currently it can take multiple entries on the command line.  The actual
 * building of the DIT header is all that really remains.
 *
 * Revision 1.5  2000/07/18 16:16:32  sjw
 * Added some generic ELF routines (conversion between internal format and ELF
 * machine type)
 * Did some framework work in edit.c --- mostly dealing with creation of files
 * etc.
 * elf32 should now write an ELF file correctly (untested)
 *
 * Revision 1.4  2000/07/18 06:22:53  sjw
 * More work.  Added empty coff.[hc], but coff is horrible.
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <libgen.h> /* For basename() */
#include <inttypes.h>
#include <assert.h>
#include <sys/mman.h>
#include <limits.h>
//#define DEBUG

#include "edit.h"
#include "getopt.h"
#include "log.h"
#include "dit.h"
#include "binfo.h"
#include "ditekcp.h"

#define MAX(a, b)    ((a) < (b) ? (b) : (a))

const static char *arches[] = {
    [ARCH_INVALID] = "invalid",
    [ARCH_MIPS32] = "mips32",
    [ARCH_MIPS64] = "mips64",
    [ARCH_SPARC32] = "sparc32",
    [ARCH_SPARC64] = "sparc64",
    [ARCH_POWERPC64] = "powerpc64",
    [ARCH_ALPHA] = "alpha",
    [ARCH_IA64] = "ia64",
    [ARCH_ARM] = "arm",
    [ARCH_IA32] = "ia32",
};

const static char *objs[] = {
    [OBJ_INVALID] = "invalid",
    [OBJ_ELF32] = "elf32",
    [OBJ_ELF64] = "elf64",
    [OBJ_ECOFF] = "ecoff",
    [OBJ_RAW] = "raw",
};

register_func register_funcs[] = {
    elf32_register,
    elf64_register,
    //    ecoff_register,
    macho_register,
    raw_register, /* Will only register files that are already set to OBJ_RAW */
};


int merge_files(struct edit_file *target, int nfiles, struct edit_file *sources);
void align_target(struct edit_file *efile, unsigned int alignment);
static int print_link(struct edit_file *efile, int dit_segment);

void print_arches(FILE *file)
{
    int i;
    
    /* Don't print out invalid ;) */
    for(i = 1; i < sizeof(arches) / sizeof(arches[0]); i++) {
	fprintf(file, "%s ", arches[i]); 
    }
    fprintf(file, "\n");
}
  
void print_objs(FILE *file)
{
    int i;

    /* Don't print out invalid ;) */
    for(i = 1; i < sizeof(objs) / sizeof(objs[0]); i++) {
	fprintf(file, "%s ", objs[i]);
    }
    fprintf(file, "\n");
}

void print_version(FILE *file, char *name)
{
	fprintf(file, "%s version " VERSION "\n", name);
}


enum longopts {LONGOPT_BINFO_SEXEC=257, LONGOPT_KCP_MAINMEM_LOW, LONGOPT_KCP_MAINMEM_HIGH, 
	LONGOPT_FIXUP_ELF_HEADER_ADD_TO_PHYSADDR, LONGOPT_FIXUP_ELF_HEADER_ADD_TO_VIRTADDR, LONGOPT_RAW_PHYS, LONGOPT_RAW_VIRT};

const static char *optstring = "-hVvqnBt:D:o:O:a:dluRP:e:b:N:M:K:ApxrksSi";

const struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'V'},
    {"verbose", no_argument, NULL, 'v'},
    {"quiet", no_argument, NULL, 'q'},
    {"nodit", no_argument, NULL, 'n'},
    {"target", required_argument, NULL, 't'},
    {"dit-segment", required_argument, NULL, 'D'},
    {"output", required_argument, NULL, 'o'},
    {"offset", required_argument, NULL, 'O'},
    {"align", required_argument, NULL, 'a'},
    {"dump", no_argument, NULL, 'd'},
    {"link", no_argument, NULL, 'l'},
    {"update-sigma0", no_argument, NULL, 'u'},
    {"include-bootinfo", no_argument, NULL, 'B'},
    {"binfo-sexec", no_argument, NULL, LONGOPT_BINFO_SEXEC},
	{"kcp-mainmem-low", required_argument, NULL, LONGOPT_KCP_MAINMEM_LOW},
	{"kcp-mainmem-high", required_argument, NULL, LONGOPT_KCP_MAINMEM_HIGH},
	{"elf-modify-physaddr", required_argument, NULL, LONGOPT_FIXUP_ELF_HEADER_ADD_TO_PHYSADDR},
	{"elf-modify-virtaddr", required_argument, NULL, LONGOPT_FIXUP_ELF_HEADER_ADD_TO_VIRTADDR},
    {"raw", no_argument, NULL, 'R'},
    {"patch", required_argument, NULL, 'P'},
    {"entry", required_argument, NULL, 'e'},
    {"base",  required_argument, NULL, 'b'},
    {"name", required_argument, NULL, 'N'},
    {"magic", required_argument, NULL, 'M'},
    {"phys-align", required_argument, NULL, 'A'},
    {"execute", no_argument, NULL, 'x'},
    {"resource", no_argument, NULL, 'r'},
    {"kernel", no_argument, NULL, 'k'},
    {"kcp", required_argument, NULL, 'K'},
    {"sigma0", no_argument, NULL, 's'},
    {"sigma1", no_argument, NULL, 'S'},
    {"initial-server",   no_argument, NULL, 'i'},
	{"raw-phys", required_argument, NULL, LONGOPT_RAW_PHYS},
	{"raw-virt", required_argument, NULL, LONGOPT_RAW_VIRT},
    {0, 0, 0, 0}
};

void usage(FILE *file, char *name)
{
    print_version(file, name);
    fprintf(file, "\n"
"Usage: %1$s [-hVvqdl] [[-Rxr] [-b <address>] [-N name] [-e <address>] <filename>] [-D segment] [-t format] -o <target>\n"
" Flags:\n"
"  General\n"
"    -h --help               : Help (this screen)\n"
"    -V --version            : Version\n"
"    -v --verbose            : Verbose\n"
"    -q --quiet              : Quiet\n"
"    -W --newapi             : Generate files with the new api feature\n"
"\n"
"   Target\n"
"    -n --nodit              : Do not include a DIT header in the output image\n"
"    -t --target=<target>    : Target format <obj>-<arch>-<endian>\n"
"    -o --output=<filename>  : Output to this filename\n"
"    -D --dit-segment=<no.>  : Set DIT as this segment (default to end) starting from 0\n"
"    -O --offset=<address>   : Offset of output segments (OBSOLETE)\n"
"    -d --dump               : Dump DIT and BootInfo segments, if present\n"
"    -l --link               : Print address to link to at end of file\n"
"    -u --update-sigma0      : Put the address of DIT into the second image\n"
"    -B --include-bootinfo   : Include an L4 BootInfo structure in the image\n"
"       --binfo-sexec        : Use SimpleExec structures for the Bootinfo rather than SimpleElf\n"
"       --kcp-mainmem-low=   : Patch the specified address into the kernel configuration page\n"
"       --kcp-mainmem-high=  : Patch the specified address into the kernel configuration page\n"
"       --elf-modify-physaddr= : Add the specified address to the segment physaddrs\n"
"                                of the Dite elf header\n"
"\n"
"  Per source file\n"
"    -a --align=<pad>        : Align end of file to this value\n"
"    -R --raw                : Raw input\n"
"    -p --physical-entry     : Rewrite the entry point of this file from the physaddr start\n"
"    -P --patch              : Patch the start of dit into this file (OBSOLETE)\n"
"    -e --entry=<address>    : Entry point\n"
"    -b --base=<address>     : Base address --- all internal file addresses are added to this (OBSOLETE)\n"
"    -N --name=<name>        : The name of the file to use in the DIT header\n"
"    -M --magic=<value>      : A magic number to associate with this file\n"
"    -K --kcp=<value>        : The vaddr of the Pistachio Kernel Configuration Page within this file\n"
"    -A --phys-align         : Change physical load address to end of image\n"
"    -x --execute            : Set execute flag\n"
"    -r --resource           : Set as resource manager\n"
"    -k --kernel             : Set as the kernel\n"
"    -s --sigma0             : Set as sigma0\n"
"    -S --sigma1             : Set as sigma1\n"
"    -i --initial-server     : Set as root task\n"
"       --raw-phys=          : Set the absolute physical address of this\n"
"                              raw file\n"
"       --raw-virt=          : Set the absolute virtual address of this\n"
"                              raw file.\n\n", name);
}

void usage_extended(FILE *file, char *name)
{
    fprintf(file,
"Examples:\n"
"\t%1$s -t elf32-mips64-big -D 1 -o kernel kernel64\n"
"\t%1$s -o kernel-serial kernel -xr serial\n"
"\n\t  This creates an elf32 file called 'kernel-serial' containing the files kernel64 and serial.\n"
"\tThe DIT contains 'kernel64' and 'serial', which is an initial server and is"
"the resource manager\n"
"\n\t%1$s -R -e 0x200000 -b 0x200000 l4pal sigma0 -xr serial -o kernel-serial\n"
"\n\t  This creates an elf64 image, with the kernel located at 0x20000\n"
"\n\t%1$s l4image -R rawdata1 -R rawdata2 -o image.boot\n"
"\n\t  This appends 'rawdata1' and 'rawdata2' to the end of l4image\n"
"\nThe DIT header will be the last (page aligned) segment in the file\n"
"\nListed below are the supported archictectures and object formats.\n"
"<endian> can be either little or big.  Note that partial target formats are\n"
"ok, the other information will be inferred from the first non-raw input file.\n", name);

    fprintf(file, " Supported arches:\n\n\t");
    print_arches(file);
    fprintf(file, "\n Supported objects (coff is not implemented yet ;):\n\n\t");
    print_objs(file);
}

int parse_target(char *target_string, enum objtype *objtype, enum arch *arch, enum endianness *endianness)
{
	int i, ret = 1;
	char *str, *strbak;

	*objtype = OBJ_INVALID;
	*arch = ARCH_INVALID;
	*endianness = END_INVALID;

	strbak = strdup(target_string);

	str = strtok(strbak, "-");
	for(i = 0; str != NULL &&  i < sizeof(objs) / sizeof(objs[0]); i++) {
		if(strncmp(objs[i], str, sizeof(objs[i])) == 0) {
			ret = 0;
			str = strtok(NULL, "-");

			*objtype = (enum objtype) i;
			break;
		}
	}

	for(i = 0; str != NULL && i < sizeof(arches) / sizeof(arches[0]); i++) {
		if(strncmp(arches[i], str, sizeof(arches[i])) == 0) {
			ret = 0;
			str = strtok(NULL, "-");

			*arch = (enum arch) i;
			break;
		}
	}

	if(str != NULL) {
		if(strncmp("little", str, sizeof("little")) == 0) {
			ret = 0;
			*endianness = LSB;
		} else if(strncmp("big", str, sizeof("big")) == 0) {
			ret = 0;
			*endianness = MSB;
		}
		str = strtok(NULL, "-");
	}

	free(strbak);

	if(str != NULL)
		ret = 1;

	return ret;
} 

void dump_efile(struct edit_file *target)
{
	int i;

	debug("* filename = %s\n", target->filename);
	debug("* flags = 0x%x\n", target->flags);
	debug("* arch = %d\n", target->arch);
	debug("* objtype = %d\n", target->objtype);
	debug("* endianness = %d\n", target->endianness);
	debug("* entry = 0x%llx\n", target->entry);
	debug("* alignment = 0x%x\n", target->alignment);
	debug("* nsegments = %d\n", target->nsegments);

	for(i = 0; i < target->nsegments; i++) {
		debug("*(%d)   vaddr = 0x%llx\n", i, target->segments[i].vaddr);    
		debug("*(%d)   paddr = 0x%llx\n", i, target->segments[i].paddr);    
		debug("*(%d)   memsize = 0x%llx\n", i, target->segments[i].memsize);    
		debug("*(%d)   filesize = 0x%llx\n", i, target->segments[i].filesize);    
		debug("*(%d)   align = 0x%llx\n", i, target->segments[i].align);    
	}
}

long
get_file_size(FILE *stream)
{
	struct stat statbuf;
	if (fstat(fileno(stream), &statbuf) == -1) {
		fprintf(stderr, "Warning: fstat failed\n");
		/* FIXME: we return 0 to stay compatible with unix.c for now*/
		return 0; 
	}
	assert(statbuf.st_size <= LONG_MAX);
	return statbuf.st_size;
}

int setup_efile(struct edit_file *efile)
{
	FILE *fptr;

	char *fname = strdup(efile->filename);


	if((fptr = fopen(efile->filename, "rb")) == NULL) {
		return 1;
	}

	if(efile->ditname == NULL)
		efile->ditname = basename(fname);

	efile->size = get_file_size(fptr);
	if(efile->size == 0) {
		efile->flags |= FL_NEW;
		return 0;
	}

	efile->mmap = mmap(NULL, efile->size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE, fileno(fptr), 0);
	assert(efile->mmap != MAP_FAILED);

	return 0;
}

int register_efile(struct edit_file *efile) 
{
	int i;

	if(efile->objtype == OBJ_RAW) {
		raw_register(efile);
		return 0;
	}

	for(i = 0; i < sizeof(register_funcs) / sizeof(register_funcs[0]); i++) {
		if(!(register_funcs[i])(efile)) {
			break;
		}
	}

	if(i == sizeof(register_funcs) / sizeof(register_funcs[0])) {
		log(LOG_WARNING, "Unrecognized format for '%s': "
				"defaulting to raw\n", efile->filename);
		efile->objtype = OBJ_RAW;
		raw_register(efile);
	}

	return 0;
}

static void
merge_sections(struct edit_file *source_file, struct edit_file *dest_file, int start_segment)
{
	struct edit_section *source_current, *dest_current;;
	source_current = source_file->first_section;
	dest_current = dest_file->first_section;
	/* Skip to the last section */
	while(dest_current != NULL && dest_current->next != NULL) {
		dest_current = dest_current->next;
	}

	while(source_current != NULL) {
		/* At the moment we only look for a KIP and copy it across if it exists.
		 * FIXME: We could do many cool things with this, such as merging string
		 * tables and preserving all sections.
		*/
		if ((source_current->type == SHT_PROGBITS || source_current->type == SHT_NOBITS) && (source_current->addr != 0)) {
			if (dest_file->first_section == NULL) {
				dest_current = dest_file->first_section = malloc(sizeof(struct edit_section));
			} else {
				dest_current = dest_current->next = malloc(sizeof(struct edit_section));
			}
			memcpy(dest_current, source_current, sizeof(struct edit_section));

			dest_current->next = NULL;
			/* Fix the offset. */
			dest_current->segment_num += start_segment;
		}
		source_current = source_current->next;
	}
}

int main(int argc, char *argv[])
{
	int c;
	int i;
	struct edit_file *sources = NULL, target;
	char *logfile = "-";   /* Default to stdout */
	enum loglevel loglevel = LOG_NORMAL;
	int num_sources = 0, tmp;
	/* Flags: */
	int dump_dit = FALSE, link_flag = FALSE;
	int dit_segment = -1;
	int binfo_segment = -1;
	int r;
	struct edit_options target_options;
	int has_kernel = 0;

	target_options.elf_hdr_physaddr = 0;
	target_options.elf_hdr_virtaddr = 0;

	if(argc < 2) {
		usage(stderr, argv[0]);
		exit(1);
	}

	/* Set up initial values */
	target = (struct edit_file) {0, };

	sources = calloc(1, sizeof(struct edit_file));
	sources[0].alignment = 1;

	while((c = getopt_long(argc, argv, optstring, longopts, &tmp)) != EOF) {
		switch (c) {
			case 1:
				sources[num_sources++].filename = optarg; //argv[optind];
				sources = realloc(sources, (num_sources + 1) * sizeof(struct edit_file));
				memset(&(sources[num_sources]), 0, sizeof(struct edit_file));
				sources[num_sources].alignment = 1;
				sources[num_sources].base_address = 0;
				break;

				/* General */

			case 'h': /* help */
				usage(stdout, argv[0]);
				usage_extended(stdout, argv[0]);
				exit(0);

			case 'V': /* version */
				print_version(stdout, argv[0]);
				exit(0);

			case 'v': /* verbose */
				loglevel = LOG_LOW;
				break;

			case 'q': /* quiet */
				loglevel = LOG_CRITICAL;
				break;

				/* Target */

			case 'n': /* no dit */
				target.flags |= FL_NODIT;
				break;

			case 'B': /* Use bootinfo format */
				target.flags |= FL_USE_BINFO;
				break;

			case LONGOPT_BINFO_SEXEC:
				target.flags |= FL_BINFO_SEXEC;
				break;

			case 't': /* target */
				if(parse_target(optarg, &(target.objtype), &(target.arch), &(target.endianness))) {
					fprintf(stderr, "%s: Unknown target: %s\n", argv[0], optarg);
					exit(EXIT_FAILURE);
				}
				break;

			case 'D': /* dit-segment */
				dit_segment = strtoull(optarg, NULL, 0);
				break;

			case 'o': /* output */
				target.filename = optarg;
				break;

			case 'O':
				/* FIXME (sjw Tue Sep 26 03:30:02 2000 ) --- Should this be signed? */
				target.offset = strtoull(optarg, NULL, 0);
				debug("target.offset = 0x%llx\n", target.offset);
				break;

			case 'd': /* dump dit */
				dump_dit = TRUE;
				break;

			case 'l':
				link_flag = TRUE;
				break;

			case 'u':
				target.flags |= FL_SEEDY;
				break;

				/* Per source file */
			case LONGOPT_RAW_PHYS:
				/* FIXME: Should be in .segments but that hasn't
				 * been allocated yet */
				sources[num_sources].paddr = strtoull(optarg, NULL, 0);
				break;

			case LONGOPT_RAW_VIRT:
				/* FIXME: Should be in .segments but that hasn't
				 * been allocated yet */
				sources[num_sources].vaddr = strtoull(optarg, NULL, 0);
				break;

			case 'a': /* align */
				sources[num_sources].alignment = strtoull(optarg, NULL, 0);

				/* Ensure that alignment > 0 */
				sources[num_sources].alignment = (sources[num_sources].alignment ? 
						sources[num_sources].alignment : 1);
				break;

			case 'P': /* Patch */
				sources[num_sources].flags |= FL_PATCH_FILE;
				sources[num_sources].patch_addr = strtoull(optarg, NULL, 0);
				break;

			case 'R': /* Raw */
				sources[num_sources].objtype = OBJ_RAW;
				break;

			case 'e': /* entry */
				sources[num_sources].entry = strtoull(optarg, NULL, 0);
				break;

			case 'p': /* Physaddr-entry-point */
				sources[num_sources].flags |= FL_PHYS_ENTRY;
				break;

			case 'b': /* base */
				sources[num_sources].base_address = strtoull(optarg, NULL, 0);
				break;

			case 'N': /* name */
				sources[num_sources].ditname = optarg;
				break;

			case 'M': /* magic */
				sources[num_sources].ditmagic = strtoull(optarg, NULL, 0);
				break;

			case 'K': /* KCP addr */
				sources[num_sources].kcp = strtoull(optarg, NULL, 0);
				break;

			case LONGOPT_KCP_MAINMEM_LOW: /* Patch low addr of main mem into KCP */
				target_options.kcp_mainmem_low = strtoull(optarg, NULL, 0);
				break;

			case LONGOPT_KCP_MAINMEM_HIGH: /* Patch high addr of main mem into KCP */
				target_options.kcp_mainmem_high = strtoull(optarg, NULL, 0);
				break;

			case LONGOPT_FIXUP_ELF_HEADER_ADD_TO_PHYSADDR:
				target_options.elf_hdr_physaddr = strtoull(optarg, NULL, 0);
				break;

			case LONGOPT_FIXUP_ELF_HEADER_ADD_TO_VIRTADDR:
				target_options.elf_hdr_virtaddr = strtoull(optarg, NULL, 0);
				break;

			case 'A': /* phys align flag */
				sources[num_sources].flags |= FL_PHYS_ALIGN;
				break;

			case 'x': /* exec flag */
				sources[num_sources].flags |= FL_EXEC;
				break;

			case 'r': /* resource manager */
				sources[num_sources].flags |= FL_RESOURCE;
				break;

			case 'k': /* kernel */
				sources[num_sources].flags |= FL_KERNEL;
				has_kernel = 1;
				break;

			case 's': /* sigma0 */
				sources[num_sources].flags |= FL_SIGMA0;
				break;

			case 'S': /* sigma1 */
				sources[num_sources].flags |= FL_SIGMA1;
				break;

			case 'i': /* intial server */
				sources[num_sources].flags |= FL_ROOT;
				break;


			default:
				usage(stderr, argv[0]);
				exit(1);
		}
	}

	init_logging(logfile, loglevel);

	if(num_sources == 0) {
		log(LOG_CRITICAL, "No sources given\n");
		usage(stderr, argv[0]);
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < num_sources; i++) {
		if(setup_efile(&(sources[i]))) {
			log(LOG_CRITICAL, "Couldn't setup %s\n", sources[i].filename);
			exit(EXIT_FAILURE);
		}

		if(register_efile(&(sources[i]))) {
			log(LOG_CRITICAL, "Couldn't register %s\n", sources[i].filename);
			exit(EXIT_FAILURE);
		}

		/* Do any target related checks */
		target.entry = (target.entry == 0 ? sources[i].entry : target.entry);
		sources[i].offset = target.offset;
		if(target.filename && !strcmp(target.filename, sources[i].filename))
			target.flags |= FL_UPDATE;

		if(sources[i].objtype != OBJ_RAW) {
			target.objtype = (target.objtype == OBJ_INVALID ? 
					sources[i].objtype : target.objtype);
			target.arch = (target.arch == ARCH_INVALID ? sources[i].arch : 
					target.arch);
			target.endianness = (target.endianness == END_INVALID ? 
					sources[i].endianness : target.endianness);
		}
	}

	/* Deduce the target word size from the architecture */
	/* FIXME: Allow over-riding with a command-line option */
	target.word_size = arch_to_wordsize(target.arch);    

	if(dump_dit) {
		/* FIXME (sjw Tue Jul 25 00:02:52 2000 ) --- seedy hack */
		if(merge_dit(&(sources[0]), &(sources[0]))) {
			log(LOG_CRITICAL, "'%s' doesn't appear to contain a DIT\n", sources[0].filename);
		} else {
			print_dit(&(sources[0]));
		}
		sources[0].word_size = arch_to_wordsize(sources[0].arch);
		printf("\n");
		binfo_print(&(sources[0]));

		exit(EXIT_SUCCESS);
	}

	if(link_flag) {
		/* This should strip off any DIT */
		merge_dit(&(sources[0]), &(sources[0]));

		print_link(&(sources[0]), dit_segment);

		exit(EXIT_SUCCESS);
	}

	if(target.filename == NULL) {
		log(LOG_CRITICAL, "Need a target\n");
		exit(EXIT_FAILURE);
	}

	target.flags |= FL_NEW;
	if(target.objtype == OBJ_INVALID || 
			target.arch == ARCH_INVALID || 
			target.endianness == END_INVALID) {
		log(LOG_CRITICAL, "Invalid target or entry: %s-%s-%s\n", 
				objs[target.objtype], 
				arches[target.arch], (target.endianness == END_INVALID ? "invalid" : 
					(target.endianness == LSB ? "little" : "big")));
		exit(EXIT_FAILURE);
	}

	if(register_efile(&target)) {
		log(LOG_CRITICAL, "Couldn't register '%s'\n", target.filename);
		exit(EXIT_FAILURE);
	}

	/* printf("Target '%s' is %s-%s-%s - %d\n", target.filename, objs[target.objtype], 
	   arches[target.arch], (target.endianness == LSB ? "little" : "big"), num_sources); */
	merge_files(&target, num_sources, sources);

	if(target.flags & FL_USE_BINFO) {
		struct edit_segment *binfo_seg;

		if (!has_kernel) {
			printf("warning: no kernel specified, skipping "
			   "binfo\n");
			goto nobinfo;
		}

		binfo_seg = add_binfo_segment(
		    &target, binfo_segment, num_sources, sources);
		if(binfo_seg == NULL) {
			log(LOG_CRITICAL, "Couldn't add bootinfo segment\n");
			exit(EXIT_FAILURE);
		}
		if(kcp_clean(sources, num_sources) != 0) {
			log(LOG_CRITICAL, "Couldn't clean KCP - is the KCP address correct? (nm <kernel> | grep kip)\n");
			exit(EXIT_FAILURE);
		}
		if(kcp_patch_binfo(binfo_seg, sources, num_sources) != 0) {
			log(LOG_CRITICAL, "Couldn't patch bootinfo into the KCP\n");
			exit(EXIT_FAILURE);
		}
		if(kcp_patch_initial_servers(&target, sources, num_sources) != 0) {
			log(LOG_CRITICAL, "Couldn't patch sigma0 and root_server into the KCP\n");
			exit(EXIT_FAILURE);
		}
		if(kcp_patch_main_memory(&target, sources, num_sources, &target_options) != 0) {
			log(LOG_CRITICAL, "Couldn't patch main memory areas into the KCP\n");
			exit(EXIT_FAILURE);
		}

		target.binfo_seg = binfo_seg;
	}

nobinfo:
	if(!(target.flags & FL_NODIT)) {
		if(add_dit_segment(&target, dit_segment)) {
			log(LOG_CRITICAL, "Couldn't add DIT segment\n");
			exit(EXIT_FAILURE);
		}
	}

	//   dump_efile(&target);
	//print_dit(&target);
	//binfo_print(&target);

	/* If we are updating an existing file, unlink it so we can overwrite it without losing data */
	if(target.flags & FL_UPDATE)
		unlink(target.filename);

	r = target.write_file(&target, &target_options);
	if (r != 0) {
		log(LOG_CRITICAL, "Couldn't write file; exiting\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}

int
seg_compar(const void *a, const void *b)
{
	return ((struct edit_segment *) a)->paddr - 
		((struct edit_segment *) b)->paddr;
}

/* Merges all the files in sources into target.  Does all the work of this program ;) */
/* FIXME (sjw Tue Sep 26 03:14:45 2000 ) --- Should reserve space for the DIT segment ...  */

int
merge_files(struct edit_file *target, int nfiles, struct edit_file *sources)
{
	int i, j, total_segments = 0;
	int target_segnum;
	struct edit_segment *segs;
	edit_addr vaddr, paddr, offset;

	target->flags |= FL_MOD;

	/* Merge any DITs.  Anything that doesn't get merged in now mark for later */
	for(i = 0; i < nfiles; i++) {
		total_segments += sources[i].nsegments;

		if(merge_dit(target, &(sources[i])))
			sources[i].flags |= FL_DIT;
	}

	segs = target->segments = malloc(total_segments * sizeof(struct edit_segment));
	if(target->segments == NULL) {
		log(LOG_CRITICAL, "Out of memory\n");
		return 1;
	}

	target_segnum = 0;
	if(target->dit_type == 0)   /* No dit found in input files */
	{
	    if (nfiles)	/* at least 1 input file */
	    {
		switch (sources[0].objtype) { /* XXX - take type from first source */
		case OBJ_ELF64:
		    target->dit_type = 2;   /* 64 bit */
		    break;
		default:
		    target->dit_type = 1;   /* 32 bit */
		    break;
		}
	    }
	}

	/* Now insert everything that has an address */
	for(i = 0; i < nfiles; i++) {
		struct edit_segment *tmp_segs;

		if(sources[i].flags & FL_PHYS_ALIGN) {
			continue;
		}

		if((sources[i].objtype == OBJ_RAW && sources[i].base_address == 0)) {
			continue;
		}


		tmp_segs = sources[i].segments;
		/* update vaddr and paddr of all segments (normalize) */
		for(j = 0; j < sources[i].nsegments; j++) {
			//tmp_segs[j].vaddr -= (tmp_segs[j].vaddr > target->offset ? 
			//		  target->offset : 0);
			tmp_segs[j].paddr -= (tmp_segs[j].paddr > target->offset ? 
					target->offset : 0) -
				sources[i].base_address;
		}

		/* Merge sections from this file with the target's sections. */
		merge_sections(&(sources[i]), target, target_segnum);

		if(sources[i].flags & FL_DIT) {
			add_dit_entry(target, &(sources[i]));
		}
		memcpy(segs, sources[i].segments, 
				sources[i].nsegments * sizeof(struct edit_segment));
		target->nsegments += sources[i].nsegments;
		segs += sources[i].nsegments;
		target_segnum += sources[i].nsegments;
	}


	//    qsort(target->segments, target->nsegments, 
	//	  sizeof(struct edit_segment), seg_compar);


	for(i = 0; i < nfiles; i++) {

		if(!((sources[i].objtype == OBJ_RAW && sources[i].base_address == 0) ||
					sources[i].flags & FL_PHYS_ALIGN))
			continue;

		/* At this point, we need to give the rest of 
		   the segments addresses ... */
		if (sources[i].vaddr != 0) {
			printf("Modifying vaddr\n");
			assert(sources[i].nsegments == 1);
			vaddr = sources[i].vaddr;
		} else {
			vaddr = target->segments[target->nsegments - 1].vaddr + 
				target->segments[target->nsegments - 1].memsize;
		}
		if (sources[i].paddr != 0) {
			printf("Modifying paddr\n");
			assert(sources[i].nsegments == 1);
			paddr = sources[i].paddr;
		} else {
			paddr = target->segments[target->nsegments - 1].paddr + 
				target->segments[target->nsegments - 1].memsize;
		}
		if (! (sources[i].flags & FL_PHYS_ALIGN)) {
			sources[i].segments[0].vaddr = ALIGN(vaddr, target->pagesize);
			sources[i].segments[0].paddr = ALIGN(paddr, target->pagesize);
		} else {
			offset = sources[i].segments[0].paddr - 
				ALIGN(paddr, target->pagesize);
			for(j = 0; j < sources[i].nsegments; j++) {
				sources[i].segments[j].paddr = 
					sources[i].segments[j].paddr - offset;
				sources[i].segments[j].paddr +=
					sources[i].segments[j].vaddr % target->pagesize;
			}
		}

		printf("Setting addr: %p\n", sources[i].segments[0].paddr );
		if (sources[i].first_section) 
			sources[i].first_section->addr = sources[i].segments[0].paddr; /* Hack! */
		merge_sections(&(sources[i]), target, target_segnum);

		if(sources[i].flags & FL_DIT) {
			add_dit_entry(target, &(sources[i]));
		}
		memcpy(&(target->segments[target->nsegments]), sources[i].segments,
				sources[i].nsegments * sizeof(struct edit_segment));
		target->nsegments += sources[i].nsegments;
		target_segnum += sources[i].nsegments;
	}

	segs = target->segments;    
	/* update vaddr and paddr of all segments */
	for(i = 0; i < target->nsegments; i++) {
		//segs[i].vaddr += target->offset;
		segs[i].paddr += target->offset;
	}
	return 0;
}

static int 
print_link(struct edit_file *efile, int dit_segment)
{
	int i;
	struct edit_segment *segs;
	unsigned long link_addr;

	i = efile->nsegments - 1;   
	segs = efile->segments;

	/* Note that we also need to leave a page for the DIT header ... sigh */
	/* NFD: Hmmm, was vaddr. */
	link_addr = ALIGN(segs[i].memsize + segs[i].paddr - efile->offset, efile->pagesize);
	if(dit_segment == efile->nsegments) {
		link_addr += efile->pagesize;
		/* in MIPS L4, the kinfo page is right after the DIT page ... this won't hurt anyone else, I hope */
		link_addr += efile->pagesize;
	}
	/* Align the output file to the desired value */
	/* FIXME (sjw Mon Sep 25 18:27:55 2000 ) --- Correct?  */
	printf("0x%lx\n", link_addr);

	return 0;
}

/*
 * Local Variables: ***
 * compile-command: "make edit.o" ***
 * End: ***
 */

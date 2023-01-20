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
 *        Created:  19/07/2000 14:07:48 by Simon Winwood (sjw)
 *  Last Modified:  06/09/2002 17:02:50 by Simon Winwood (sjw)
 *   Version info:  $Revision: 1.9 $ 
 *    Description:
 *
 *       Comments:
 *
 *        License: Relicensed under the UNSW OzPLB licence
 *
 * $Log: elf_generic.c,v $
 * Revision 1.9  2004/03/04 01:42:26  benjl
 * -Wall -Werror changes.
 *
 * Revision 1.8  2004/02/26 08:06:50  benjl
 * Added ARM pagesize as 1k.
 * Changed IA64 pagesize from 12k->16k (Is this right??).
 *
 * Revision 1.7  2002/09/06 07:06:24  sjw_
 * Added IA64 support, and --name flag
 *
 * Revision 1.6  2001/03/27 07:06:36  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.5  2000/09/25 09:10:16  sjw
 * Added -O and -D.
 *
 * Revision 1.4  2000/07/24 14:48:48  sjw
 * Very basic functionality complete -- i.e. it can take in multiple elf32 or
 * elf64 files and spit out 1 elf32 file (strange bug in elf64.c?) which can
 * be recognized by 'dit'.  Still need to implement '-l' flags, but otherwise
 * it's mostly usable.
 *
 * Revision 1.3  2000/07/24 13:03:23  sjw
 * More changes.
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

#include "elf_generic.h"

uint32_t archflags[ARCH_SIZE_DUMMY] = {
    [ARCH_MIPS64] = EF_MIPS_ARCH_3, // | EF_MIPS_ABI_ON32,
};

/* FIXME (sjw Tue Sep 26 02:34:15 2000 ) --- This should be in a config file (maybe) */
uint32_t pagesize[ARCH_SIZE_DUMMY] = {
    [ARCH_MIPS64] = 0x1000,
    [ARCH_MIPS32] = 0x1000,
    [ARCH_ARM] = 0x1000,
    [ARCH_ALPHA] = 0x2000,
    [ARCH_POWERPC64] = 0x1000,
    [ARCH_SPARC32] = 0x1000,
    [ARCH_SPARC64] = 0x1000,
    [ARCH_IA64] = 0x4000,
    [ARCH_IA32] = 0x1000,
};

/* Converts from ELF machine type to EDIT arch */

enum arch elfmach2arch(int elf_mach)
{

    switch(elf_mach) {
    case EM_ALPHA:
    case EM_FAKE_ALPHA:   /* DANGER (sjw Wed Jul 19 04:28:22 2000 ) --- WTF? */
	return ARCH_ALPHA;
    case EM_MIPS:
	/* FIXME (sjw Fri Jul 21 16:39:29 2000 ) --- Need to look at e_flags as well ;( */
	//	return ARCH_MIPS32;
    case EM_MIPS_RS4_BE:
	return ARCH_MIPS64;
    case EM_ARM:
	return ARCH_ARM;
    case EM_SPARC:
    case EM_SPARC32PLUS:
	return ARCH_SPARC32;
    case EM_SPARCV9:
	return ARCH_SPARC64;
    case EM_POWERPC64:
	return ARCH_POWERPC64;
    case EM_IA_64:
	return ARCH_IA64;
    case EM_386:
	return ARCH_IA32;
    default:
	return ARCH_INVALID;
    }

    return ARCH_INVALID;	
}

/* Converts from EDIT arch to ELF mach */
int arch2elfmach(enum arch arch)
{

    switch(arch) {
    case ARCH_INVALID:
	return EM_NONE;
    case ARCH_MIPS32:
	return EM_MIPS;
    case ARCH_MIPS64:
	return EM_MIPS;
    case ARCH_SPARC32:
	return EM_SPARC;
    case ARCH_SPARC64:
	return EM_SPARCV9;
    case ARCH_POWERPC64:
	return EM_POWERPC64;
    case ARCH_ALPHA:
	return EM_ALPHA;
    case ARCH_ARM:
	return EM_ARM;
    case ARCH_IA64:
	return EM_IA_64;
    case ARCH_IA32:
	return EM_386;
    default:
	return EM_NONE;
    }
}



uint32_t elfarchflags(enum arch arch)
{
    return archflags[arch];
}

uint32_t elfarch_pagesize(enum arch arch)
{
    return pagesize[arch];
}


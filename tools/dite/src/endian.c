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
 *        Created:  12/07/2000 17:16:13 by Simon Winwood (sjw)
 *  Last Modified:  27/03/2001 16:58:02 by  (sjw)
 *   Version info:  $Revision: 1.9 $ 
 *    Description:
 *          Endianess abstraction layer, deals with 8, 16, 32, 64.
 *
 *       Comments:
 *
 *        License: Relicensed under the UNSW OzPLB
 *
 * $Log: endian.c,v $
 * Revision 1.9  2004/07/28 11:36:00  nfd
 * Update ditekcp to use aistructs. So in theory it works perfectly - perfectly! - on 64-bit systems now.
 *
 * Revision 1.8  2004/07/21 07:33:31  nfd
 * - Bootinfo support for platforms with 64-bit word size as well - untested so far
 * - Fix an alignment bug when setting up the memory descriptors.
 *
 * Revision 1.7  2004/03/10 05:54:18  nfd
 * Support for writing 64-bit values in 32-bit elf files.
 *
 * Revision 1.6  2001/03/27 07:06:36  sjw
 * Added copyright notices to all of my files.
 *
 * Revision 1.5  2000/08/07 09:37:17  sjw
 * It now builds with automake and autoconf.  This means that it now builds
 * ok on OSF1, schlags broken redhat and debian.
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

#include <stdio.h>
#include <stdlib.h>

/* Include uint8_t etc. */
#include "edit_types.h"
#include "edit_endian.h"

/* Get byte b within x */
#define EXTB(x, b) ((uint8_t) ((x) >> ((b) * 8)) & 0xff)

/* Move a uint8_t into the position determined by b */
#define INSB(x, b) (((uint64_t) (x)) << ((b) * 8))

void write8(uint8_t data, void *iptr, enum endianness endianness)
{   
    uint8_t *ptr = iptr;
       
    *ptr = data;
}

void write16(uint16_t data, void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;

    if(endianness == LSB) {
	*ptr++ = EXTB(data, 0);
	*ptr = EXTB(data, 1);
    } else {
	*ptr++ = EXTB(data, 1);
	*ptr = EXTB(data, 0);
    }
}

void write32(uint32_t data, void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;
	
    if(endianness == LSB) {
	*ptr++ = EXTB(data, 0);
	*ptr++ = EXTB(data, 1);
	*ptr++ = EXTB(data, 2);
	*ptr = EXTB(data, 3);
    } else {
	*ptr++ = EXTB(data, 3);
	*ptr++ = EXTB(data, 2);
	*ptr++ = EXTB(data, 1);
	*ptr = EXTB(data, 0);
    }
}

void write64(uint64_t data, void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;
	
    if(endianness == LSB) {
	*ptr++ = EXTB(data, 0);
	*ptr++ = EXTB(data, 1);
	*ptr++ = EXTB(data, 2);
	*ptr++ = EXTB(data, 3);
	*ptr++ = EXTB(data, 4);
	*ptr++ = EXTB(data, 5);
	*ptr++ = EXTB(data, 6);
	*ptr = EXTB(data, 7);
    } else {
	*ptr++ = EXTB(data, 7);
	*ptr++ = EXTB(data, 6);
	*ptr++ = EXTB(data, 5);
	*ptr++ = EXTB(data, 4);
	*ptr++ = EXTB(data, 3);
	*ptr++ = EXTB(data, 2);
	*ptr++ = EXTB(data, 1);
	*ptr = EXTB(data, 0);
    }
}

int arch_to_wordsize(int arch)
{
    switch(arch){
	case ARCH_MIPS32:
	case ARCH_SPARC32:
	case ARCH_ARM:
        case ARCH_IA32:
	    return WS_32BIT;
	case ARCH_MIPS64:
	case ARCH_SPARC64:
	case ARCH_POWERPC64:
	case ARCH_ALPHA:
	case ARCH_IA64:
	    return WS_64BIT;
	default:
	    printf("Unknown architecture\n");
	    exit(1);
	    return WS_UNKNOWN;
    }
}

void writeword(enum arch arch, uint64_t data, void *iptr, enum endianness endianness)
{
    switch (arch_to_wordsize(arch)) {
	case WS_32BIT:
            write32 (data, iptr, endianness);
            break;
        case WS_64BIT:
            write64 (data, iptr, endianness);
            break;
        case WS_UNKNOWN:
        default:
            fprintf (stderr, "writeword: Unknown architecture");
            exit (1);
    }
}

uint8_t read8( void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;

    return *ptr;
}

uint16_t read16( void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;

    if(endianness == LSB) {
	return *ptr | *(ptr + 1) << 8;
    } else {
	return *ptr << 8 | *(ptr + 1);
    }
}

uint32_t read32( void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;

    if(endianness == LSB) {
	return *ptr | *(ptr + 1) << 8 | *(ptr + 2) << 16 | *(ptr + 3) << 24;
    } else {
	return *ptr << 24 | *(ptr + 1) << 16 | *(ptr + 2) << 8 | *(ptr + 3);
    }    
}

uint64_t read64(void *iptr, enum endianness endianness)
{
    uint8_t *ptr = iptr;

    if(endianness == LSB) {
	return INSB(*ptr, 0) | INSB(*(ptr + 1), 1) | INSB(*(ptr + 2), 2) | INSB(*(ptr + 3), 3) |
	    INSB(*(ptr + 4), 4) | INSB(*(ptr + 5), 5) | INSB(*(ptr + 6), 6) | INSB(*(ptr + 7), 7);
    } else {
	return INSB(*ptr, 7) | INSB(*(ptr + 1), 6) | INSB(*(ptr + 2), 5) | INSB(*(ptr + 3), 4) |
	    INSB(*(ptr + 4), 3) | INSB(*(ptr + 5), 2) | INSB(*(ptr + 6), 1) | INSB(*(ptr + 7), 0);
    }
}



/*******************************************************************************
* Filename:    src/main.c                                                      *
* Description: Elf-loader - ELF file kernel/application bootstraper, main      *
*              source file.                                                    *
* Authors:     Adam 'WeirdArms' Wiggins <awiggins@cse.unsw.edu.au>.            *
* Created:     2004-12-01                                                      *
********************************************************************************
*                                                                              *
* Australian Public Licence B (OZPLB)                                          *
*                                                                              *
* Version 1-0                                                                  *
*                                                                              *
* Copyright (c) 2004 - 2005 University of New South Wales, Australia           *
*                                                                              *
* All rights reserved.                                                         *
*                                                                              *
* Developed by: Operating Systems, Embedded and                                *
*               Distributed Systems Group (DiSy)                               *
*               University of New South Wales                                  *
*               http://www.disy.cse.unsw.edu.au                                *
*                                                                              *
* Permission is granted by University of New South Wales, free of charge, to   *
* any person obtaining a copy of this software and any associated              *
* documentation files (the "Software") to deal with the Software without       *
* restriction, including (without limitation) the rights to use, copy,         *
* modify, adapt, merge, publish, distribute, communicate to the public,        *
* sublicense, and/or sell, lend or rent out copies of the Software, and        *
* to permit persons to whom the Software is furnished to do so, subject        *
* to the following conditions:                                                 *
*                                                                              *
*     * Redistributions of source code must retain the above copyright         *
*       notice, this list of conditions and the following disclaimers.         *
*                                                                              *
*     * Redistributions in binary form must reproduce the above                *
*       copyright notice, this list of conditions and the following            *
*       disclaimers in the documentation and/or other materials provided       *
*       with the distribution.                                                 *
*                                                                              *
*     * Neither the name of University of New South Wales, nor the names of    *
*        its contributors, may be used to endorse or promote products derived  *
*       from this Software without specific prior written permission.          *
*                                                                              *
* EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT            *
* PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND           *
* NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,         *
* WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING          *
* BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS             *
* REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,             *
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,          *
* THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF        *
* ERRORS, WHETHER OR NOT DISCOVERABLE.                                         *
*                                                                              *
* TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL            *
* NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL            *
* THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,             *
* NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER               *
* LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR              *
* OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS       *
* OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR         *
* OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,                   *
* CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN           *
* CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER            *
* DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS            *
* CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,       *
* DAMAGES OR OTHER LIABILITY.                                                  *
*                                                                              *
* If applicable legislation implies representations, warranties, or            *
* conditions, or imposes obligations or liability on University of New South   *
* Wales or one of its contributors in respect of the Software that             *
* cannot be wholly or partly excluded, restricted or modified, the             *
* liability of University of New South Wales or the contributor is limited, to *
* the full extent permitted by the applicable legislation, at its              *
* option, to:                                                                  *
* a.  in the case of goods, any one or more of the following:                  *
* i.  the replacement of the goods or the supply of equivalent goods;          *
* ii.  the repair of the goods;                                                *
* iii. the payment of the cost of replacing the goods or of acquiring          *
*  equivalent goods;                                                           *
* iv.  the payment of the cost of having the goods repaired; or                *
* b.  in the case of services:                                                 *
* i.  the supplying of the services again; or                                  *
* ii.  the payment of the cost of having the services supplied again.          *
*                                                                              *
* The construction, validity and performance of this licence is governed       *
* by the laws in force in New South Wales, Australia.                          *
*                                                                              *
*******************************************************************************/

#include <elf/elf.h>
#include <stdio.h>
#include <stdlib.h>
#include "arch.h"

/*****************************
* Local function prototypes. *
*****************************/

static void load_image(void** entry);

int
main(void)
{
	void* entry = NULL;
	arch_init();

	printf("elf-loader:\tStarted\n");
	load_image(&entry);

	printf("elf-loader:\tentry point is %p\n", entry);
	arch_start_kernel(entry);

	printf("elf-loader:\tKernel start failed!\n");
	abort();

	return -1;
}

/*****************
* Extern symbols *
*****************/

/* These symbols are defined by the linker scripts. */

extern char mod_dite_start[];
extern char mod_dite_end[];

/*******************
* Local functions. *
*******************/

static void
load_image(void** entry)
{
	char* start = mod_dite_start;
	char* end = mod_dite_end;

	if(start == end) {
		printf("elf-loader: error, dite image is empty!\n");
		abort();
	}
	/*  awiggins (2004-12-21): Should probably add an alignment check? */
        /** awiggins (2005-05-29): Probably should add checks to see 
         *  the correct kind of elf file is being loaded for the platform,
         *  or does the elf library do that somewhere?.
         */
	if(!elf32_checkFile((struct Elf32_Header*)start)) {
                *entry =
			(void*)(uintptr_t)elf32_getEntryPoint((struct Elf32_Header*)start);
	} else if(!elf64_checkFile((struct Elf64_Header*)start)) {
		*entry =
                        (void*)(uintptr_t)elf64_getEntryPoint((struct Elf64_Header*)start);
	} else {
		printf("elf-loader: error, dite image not a valid elf file!\n");
		abort();
	}
#ifdef __PPC64__
	if (arch_claim_memory((struct Elf32_Header*)start)) {
		printf("could not claim memory for elf file!\n");
		abort();
	}
#endif
	if(!elf_loadFile(start, true)) {
		printf("elf-loader: error, unable to load dite image!\n");
		abort();
	}
}


/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 1997-2004 University of New South Wales
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
#ifndef DIT_H
#define DIT_H
/****************************************************************************
 * $Id: dit.h,v 1.4 2004/02/26 07:59:36 benjl Exp $
 * Copyright (C) 1997, 1998 Kevin Elphinstone, Univeristy of New South
 * Wales.
 *
 * This file is part of the L4/MIPS micro-kernel distribution.
 *
 * Relicensed under the UNSW OzPLB
 ****************************************************************************/

#define DIT_NIDENT32	4
#define DIT_NIDENT64	8
#define DIT_NPNAME	16

#define DHDR_SEG_SIZE	4096
#define DHDR_ALIGN	4096

#define DI_MAG0		0
#define DI_MAG1		1
#define DI_MAG2		2
#define DI_MAG3		3

#define DITMAG32	"dhdr"
#define DITMAG64	"DitHdr64"

#define DIT_RUN		1
#define DIT_RMNG	2  /* Resource manager */
#define DIT_KERNEL	4  /* Kernel */
#define DIT_SIGMA0	8  /* Sigma0 */
#define DIT_SIGMA1	16 /* Sigma1 */
#define DIT_ROOT	32 /* Root Task */

#if defined(_LANGUAGE_ASSEMBLY)

#define D_D_IDENT	0
#define D_D_PHOFF	4
#define D_D_PHSIZE	8
#define D_D_PHNUM	12
#define D_D_FILEEND	16
#define D_D_VADDREND	20

#define D_P_BASE	0
#define D_P_SIZE	4
#define D_P_ENTRY	8
#define D_P_FLAGS	12
#define D_P_NAME	16

#else /* assume C */

#include "edit_types.h"
#include "edit.h"

typedef uint32_t Dit_uint32;
typedef uint64_t Dit_uint64;

typedef struct {
  unsigned char d_ident[DIT_NIDENT32];
  Dit_uint32 d_phoff;
  Dit_uint32 d_phsize;
  Dit_uint32 d_phnum;
  Dit_uint32 d_fileend;
  Dit_uint32 d_vaddrend;
} Dit_Dhdr32;

typedef struct {
  unsigned char d_ident[DIT_NIDENT64];
  Dit_uint64 d_phoff;
  Dit_uint64 d_phsize;
  Dit_uint64 d_phnum;
  Dit_uint64 d_fileend;
  Dit_uint64 d_vaddrend;
} Dit_Dhdr64;

typedef struct {
  union {
    Dit_Dhdr32 D32;
    Dit_Dhdr64 D64;
  };
} Dit_Dhdr;

typedef struct {
  Dit_uint32 p_base;
  Dit_uint32 p_size;
  Dit_uint32 p_entry;
  Dit_uint32 p_flags;
  unsigned char p_name[DIT_NPNAME];
	/* These are added at the end to be backwards
	   compatible  */
  Dit_uint32 p_magic;
  Dit_uint32 p_phys_base;
} Dit_Phdr32;

typedef struct {
  Dit_uint64 p_base;
  Dit_uint64 p_size;
  Dit_uint64 p_entry;
  Dit_uint64 p_flags;
  unsigned char p_name[DIT_NPNAME];
	/* These are added at the end to be backwards
	   compatible  */
  Dit_uint64 p_magic;
  Dit_uint64 p_phys_base;
} Dit_Phdr64;

typedef struct {
  union {
    Dit_Phdr32 D32;
    Dit_Phdr64 D64;
  };
} Dit_Phdr;

#endif
#endif



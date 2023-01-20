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

#ifndef _LIBTRACE_TRACEBUFFER_H_
#define _LIBTRACE_TRACEBUFFER_H_

#include <stdint.h>
#include <l4/types.h>

typedef struct {
    uint64_t timestamp;
    union{
	struct {
#ifdef L4_64BIT
	    L4_BITFIELD7(uintptr_t,
		    id		: 16,	/* tracepoint id		*/
		    user	: 1,	/* user / kernel		*/
		    reclen	: 7,	/* number of words of data	*/
		    args	: 8,	/* number of arguments		*/
		    major	: 6,	/* major number			*/
		    minor	: 10,	/* minor number			*/
				: 16	/* unused			*/
		    );
#else /* 32BIT */
	    L4_BITFIELD6(uintptr_t,
		    id		: 8,	/* tracepoint id		*/
		    user	: 1,	/* user / kernel		*/
		    reclen	: 7,	/* number of words of data	*/
		    args	: 5,	/* number of arguments		*/
		    major	: 5,	/* major number			*/
		    minor	: 6	/* minor number			*/
		    );
#endif
	} x;
	uintptr_t raw;
    } hdr;
    uintptr_t data[1];	/* code assumes size (1 word) here, do not change */
} trace_entry_t;

#define TBUF_MAGIC	0x7b6b5b4b3b2b1b0bull
#define TBUF_VERSION	1
#define TBUF_ID		1	/* L4 tracebuffer */
#define TBUF_BUFFERS	2

typedef struct {
    uintptr_t magic;		/* magic number		*/
    uintptr_t version;		/* tracebuffer version	*/
    uintptr_t bufid;		/* tracebuffer id	*/
    uintptr_t buffers;		/* number of buffers	*/

    uintptr_t log_mask;		/* mask of major IDs	*/
    uintptr_t active_buffer;	/* current active buffer	*/
    uintptr_t buffer_empty;	/* bitmask of available buffers	*/
    uintptr_t buffer_size;	/* size of each buffer (bytes)	*/

    /* offset of each buffer	*/
    uintptr_t buffer_offset[TBUF_BUFFERS];
    /* current head pointer of each buffer (past last entry) */
    uintptr_t buffer_head[TBUF_BUFFERS];
} trace_buffer_t;

#endif

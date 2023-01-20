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
#include <iguana/memsection.h>
#include <stdio.h>
#include <l4/thread.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
 
/* FIXME: (benjl) Is this the best place to define heap size? */
#define HEAP_SIZE (1 * 1024 * 1024) /* Each program gets a 1MB heap */

void __lib_init(uintptr_t *buf);
void __libc_setup(void *callback, void *stdin_p, 
		  void *stdout_p, void *stderr_p,
		  void *heap_base_p, void *heap_end_p);
extern void __malloc_init(void *bss_p, void *top_p);
extern void __cap_init(uintptr_t cap_slot, uintptr_t cap_used, uintptr_t cap_size, uintptr_t cap_addr);
extern void __asynch_init(void);
extern void __naming_init(objref_t naming_server);
extern void __tls_init_malloc(void);

void *__callback_buffer = NULL;

void
__libc_setup(void *callback, void *stdin_p, void *stdout_p, void *stderr_p,
	     void *heap_base, void *heap_end)
{
	__malloc_init(heap_base, heap_end);
	__callback_buffer = callback;
}

/* Initialise all the libraries. */
void __lib_init(uintptr_t *buf)
{
	/* args for libc initialisation */
	void *callback	= (void *)*(buf + 0);
	void *stdin_p	= (void *)*(buf + 1);
	void *stdout_p	= (void *)*(buf + 2);
	void *stderr_p	= (void *)*(buf + 3);
	void *heap_base	= (void *)*(buf + 4);
	void *heap_end	= (void *)*(buf + 5);

	/* args for cap initialisation */
	uintptr_t cap_slot = (uintptr_t)*(buf + 6);
	uintptr_t cap_used = (uintptr_t)*(buf + 7);
	uintptr_t cap_size = (uintptr_t)*(buf + 8);
	uintptr_t cap_addr = (uintptr_t)*(buf + 9);

	/* args for naming initialisation */
	objref_t naming_server = (objref_t)*(buf + 10);


	__libc_setup(callback, stdin_p, stdout_p, stderr_p, heap_base, heap_end);
	__cap_init(cap_slot, cap_used, cap_size, cap_addr);
	__naming_init(naming_server);

	__tls_init_malloc();
}


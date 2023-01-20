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

#ifndef _LIBIGUANA_MEMSECTION_H_
#define _LIBIGUANA_MEMSECTION_H_

#include <stdint.h>
#include <l4/types.h>
#include <iguana/types.h>

#define MEM_NORMAL 0x1
#define MEM_FIXED  0x2
#define MEM_DIRECT 0x4
#define MEM_UTCB   0x8
#define MEM_USER   0x10
#define MEM_INTERNAL 0x20

/**
 * @brief Create a new memory section.
 * 
 * @param[in] size The size of the memory section in bytes
 * @param[out] *base The (virtual) base address of the new memory
 *
 * \return A reference to the new memory section.
*/
memsection_ref_t memsection_create(uintptr_t size, uintptr_t *base);
memsection_ref_t memsection_create_user(uintptr_t size, uintptr_t *base);

#ifdef CONFIG_RESTRICTED_VM
memsection_ref_t memsection_create_direct(uintptr_t size, uintptr_t *base);
#endif

/**
 * @brief Create a new memory section at a fixed location. 
 *
 * @param[in] size The size of the memory section in bytes
 * @param[in] base The virtual base address of the new memory
 *
 * \return A reference to the new memory section.
*/
memsection_ref_t memsection_create_fixed(uintptr_t size, uintptr_t base);
memsection_ref_t memsection_create_fixed_user(uintptr_t size, uintptr_t base);

memsection_ref_t memsection_create_in_area(uintptr_t size, uintptr_t base, uintptr_t end, uintptr_t *base_out);

cap_t _cap_memsection_create(uintptr_t size, uintptr_t *base);

/**
 * @brief Register a server thread for this memory section.
 *
 * @param[in] memsect The memory section to register the server for
 * @param[in] server Iguana thread reference to the server thread
 *
 * \return Undefined.
*/
int memsection_register_server(memsection_ref_t memsect, thread_ref_t server);

/**
 * @brief Return the memsection and server thread for the supplied object.
 *
 * @param[in] object The object for which memsection and server information is required
 * @param[out] *server The server thread for the supplied object
 *
 * \return The memsection for the supplied object.
*/
memsection_ref_t memsection_lookup(objref_t object, thread_ref_t *server);

void memsection_delete(memsection_ref_t);

void memsection_set_attributes(memsection_ref_t, uintptr_t);

/**
 * Return the base address of a given memory section
 *
 * @param[in] memsect The memory section to lookup
 *
 * \return The base address. NULL on failure
 */
void * memsection_base(memsection_ref_t memsect);

uintptr_t memsection_size(memsection_ref_t memsect);

int memsection_page_map(memsection_ref_t memsect, L4_Fpage_t from_page, L4_Fpage_t to_page);
int memsection_page_unmap(memsection_ref_t memsect, L4_Fpage_t to_page);

#endif /* _LIBIGUANA_MEMSECTION_H_ */

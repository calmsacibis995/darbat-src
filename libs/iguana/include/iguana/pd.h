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
#ifndef _IGUANA_PD_H_
#define _IGUANA_PD_H_

#include <l4/types.h>
#include <iguana/types.h>

/**
 * @brief Return a reference to the current protection domain.
 *
*/
pd_ref_t pd_myself(void);

/** @brief Create a new PD owned by the current PD.
 *
 * \return A reference to the new PD
*/
pd_ref_t pd_create(void);

/** @brief Create a new PD owned by the specified PD.
 *
 * @param[in] pd The owning PD
 *
 * \return A reference to the new PD
*/
pd_ref_t pd_create_pd(pd_ref_t pd);

/**
 * @brief Delete protection domain. 
 *
 * @param[in] pd The protection domain to delete
 *
 * \return If called on your own protection domain this call will not return
 */
void pd_delete(pd_ref_t pd);


/**
 * @brief Create a new thread in the specified protection domain.
 *
 * A new thread is created in the supplied PD. The L4 thread ID of the
 * new thread is stored in the thrd param, and the Iguana thread ID
 * is returned.
 *
 * @param[in] pd The containing protection domain
 * @param[out] *thrd The L4 thread ID of the new thread
 *
 * \return A reference to the new Iguana thread ID
*/
thread_ref_t pd_create_thread(pd_ref_t pd, L4_ThreadId_t *thrd);
/**
 * @brief Create a new thread in the specified protection domain with the
 * specified priority.
 *
 * A new thread is created in the supplied PD. The L4 thread ID of the
 * new thread is stored in the thrd param, and the Iguana thread ID
 * is returned. 
 *
 * @param[in] pd The containing protection domain
 * @param[in] priority The thread's initial priority, from 1 to 255.
 * @param[out] *thrd The L4 thread ID of the new thread
 *
 * \return A reference to the new Iguana thread ID
*/
thread_ref_t pd_create_thread_with_priority(pd_ref_t pd, int priority, L4_ThreadId_t *thrd);
/**
 * @brief Create a new memory section in the specified protection domain
 *
 * @param[in] pd The containing protection domain
 * @param[in] size The size of the new memory section in bytes
 * @param[out] *base The base address of the new memory section
 *
 * \return A reference to the new memory section
*/
memsection_ref_t pd_create_memsection(pd_ref_t pd, uintptr_t size, uintptr_t *base);

memsection_ref_t pd_create_memsection_user(pd_ref_t pd, uintptr_t size, uintptr_t *base);
memsection_ref_t pd_create_memsection_fixed_user(pd_ref_t pd, uintptr_t size, uintptr_t base);
/**
 * @brief Setup an async communications channel for messages.
 *
 * @param[in] pd The containing protection domain
 * @param[in] callback A reference to the callback buffer.
*/
void pd_set_callback(pd_ref_t pd, memsection_ref_t callback);
/**
 * @brief Add a clist to this protection domain
 *
 * @param[in] pd The protection domain to add the clist to
 * @param[in] clist The new clist to add
*/
uintptr_t pd_add_clist(pd_ref_t pd, memsection_ref_t clist);
/**
 * @brief Release a clist from this protection domain
 *
 * @param[in] pd The protection domain to add the clist to
 * @param[in] clist The new clist to add
*/
void pd_release_clist(pd_ref_t pd, uintptr_t clist, int slot);

#endif /*_IGUANA_PD_H_*/

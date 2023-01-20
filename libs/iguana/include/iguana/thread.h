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

#ifndef _LIBIGUANA_THREAD_H_
#define _LIBIGUANA_THREAD_H_

#include <l4/types.h>
#include <iguana/types.h>

/**
 * @brief Return the L4 global thread ID for this Iguana thread.
 *
 * @param[in] server The Iguana thread for which an L4 global ID is desired
 *
 * \return The L4 global thread ID for this thread
*/
L4_ThreadId_t thread_l4tid(thread_ref_t server);

/**
 * @brief Retrieve the Iguana thread reference of the current thread
 *
 * \return The Iguana thread reference of the current thread
*/
thread_ref_t thread_myself(void);

/**
 * @brief Create a new thread in the current PD
 *
 * A new Iguana thread is created in the current protection domain. The
 * thread is initially created inactive; use L4's ExchangeRegisters()
 * function, or thread_start(), below, to activate it.
 *
 * @param[out] thrd The L4 global thread Id of the new thread is stored here
 *
 * \return the Iguana thread reference for the new thread
*/
thread_ref_t thread_create(L4_ThreadId_t *thrd);


/**
 * @brief Create a new thread in the current PD and assign it a non-default priority.
 *
 * @param[in] priority An integer between 1 (lowest) and 255 (highest) specifying the priority
 * @param[out] *thrd The L4 global thread Id of the new thread is stored here
 *
 * \return the Iguana thread reference for the new thread
*/
thread_ref_t thread_create_priority(int priority, L4_ThreadId_t *thrd);

thread_ref_t thread_create_simple(void (*fn) (void *), void * arg, int priority);

/**
 * @brief Activate an inactive thread
 *
 * Make an inactive thread schedulable. The thread will start executing
 * at the supplied instruction pointer.
 *
 * @param[in] thread the Iguana thread reference to the thread to activate
 * @param[in] ip the initial IP address of the thread
 * @param[in] sp the initial stack pointer of the thread
*/
void thread_start(thread_ref_t thread, uintptr_t ip, uintptr_t sp);

/**
 * @brief Delete a thread.
 *
 * @param[in] thrd the L4 thread Id of the thread to delete
*/
void thread_delete(L4_ThreadId_t thrd);

void thread_delete_self(void);


/**
 * @brief Return the Iguana thread reference for a given L4 global thread Id.
 *
 * @param[in] thrd the L4 thread Id
 *
 * \return the Iguana thread reference for "thrd"
*/
thread_ref_t thread_id(L4_ThreadId_t thrd);

void thread_set_exception(thread_ref_t thread, uintptr_t exc, uintptr_t sp, uintptr_t ip);

#endif /* _LIBIGUANA_THREAD_H_ */

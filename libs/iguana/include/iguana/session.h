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

#ifndef _LIBIGUANA_SESSION_H_
#define _LIBIGUANA_SESSION_H_

#include <stdbool.h>
#include <l4/types.h>
#include <iguana/types.h>


struct session {
	session_ref_t ref;
	cap_t *clist;
	int cap_pos;
	int cap_size;
	bool own_clist;
};

/**
 * @brief Create a new session, with a specified clist
 *
 * @param object The object that you wish to access
 * @param clist The clist which the server will be provided with.
 * @param server_tid The L4 thread Id of the approriate server is returned.
 *
 * \return A pointer to the userlevel session object
 */
struct session * session_create_with_clist(objref_t object, memsection_ref_t clist, L4_ThreadId_t *server_tid);
int _session_create(objref_t object, memsection_ref_t clist, L4_ThreadId_t *server_tid, struct session *session);

/**
 * @brief Create a new session, and create a dedicated clist for it
 *
 * @param object The object that you wish to access
 * @param server_tid The L4 thread Id of the approriate server is returned
 *
 * \return A pointer to the userlevel session object
 */
struct session * session_create(objref_t object, L4_ThreadId_t *server_tid);


/** @brief Create a new session, and share your base clist with it.
 *
 * This is obviously not meant to be generally used, and provides a short cut
 * until all software correctly uses caps.
 *
 * @param[in] object The object that you wish to access
 * @param[out] server_tid The L4 thread Id of the approriate server is returned
 *
 * \return A pointer to the userlevel session object
 */
struct session * session_create_full_share(objref_t object, L4_ThreadId_t
		*server_tid);

/**
 * @brief Set up async buffers for session communcations.
 *
 * @param[in] session The session to use
 * @param[in] call_buf A circular buffer for calls through the session
 * @param[in] return_buf A circular buffer for return values from the session
*/
void session_add_async(struct session *session, objref_t call_buf, 
		       objref_t return_buf);

/**
 * Provide a given session access to a specific interface on an object
 *
 * @param session The session to provide the access to
 * @param object The object to provide access to 
 * @param interface The allowed interface
 *
 * \return True if access was provided. False otherwise. You may not be able to
 * provide access if you do not have access, or have access, but can not transfer it.
 */
bool session_provide_access(struct session *session, objref_t object, int interface);


/**
 * Provide a given session access to a specific interface on an object
 *
 * @param session The session to provide the access to
 * @param object The object to provide access to 
 * @param interface The allowed interface
 *
 * \return True if access was revoked. False otherwise. You may not be able to
 * revoke access if you have not previously provided it.
 */
bool session_revoke_access(struct session *session, objref_t object, int interface);


/**
 * Delete a session making any communication based on the session impossible.
 *
 * @param session The session to delete
 *
 */
void session_delete(struct session *session);

#endif /* _LIBIGUANA_SESSION_H_ */

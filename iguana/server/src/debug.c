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
/*
  Author: Alex Webster, Ben Leslie
*/
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h> /* For abort */
#include "debug.h"
#include "memsection.h"
#include "pd.h"
#include "ig_util.h"

static void dump_memsections(struct pd *base, int depth);

#ifdef CONFIG_TEST_IGUANA
extern int __malloc_check(void);
extern void __malloc_dump(void);
#endif

void
iguana_check_state(void)
{
	if (pd_check_state(&iguana_pd) != 0) {
		DEBUG_PRINT("\e[31;1mIguana check state failed! \e[0m\n");
		debug_dump_info();
		abort();
	}
#ifdef CONFIG_TEST_IGUANA
	if (__malloc_check() != 0) {
		DEBUG_PRINT("malloc heap corrupt\n");
		__malloc_dump();
	}
#endif
}

void
debug_dump_info(void)
{

	/* Dump availabel threads */
	DEBUG_PRINT("Thread list:\n");
	//rfl_debug(thread_list, stdout);

	/* Dump memory sections */
        dump_memsections(&iguana_pd, 0);
}

#define print_spaces(n) { int i = (2 * (n)); while (i--) DEBUG_PRINT(" "); }

static void
dump_pd(struct pd *pd)
{
        DEBUG_PRINT("pd(%p)\n", pd);
}

static void
dump_memsection(struct memsection *ms)
{
        DEBUG_PRINT("memsection(%p)", ms);
        DEBUG_PRINT(" <%p:%p>", (void *) ms->base, (void *) ms->end);
        DEBUG_PRINT(" frames: %" PRIdPTR, ms->frames);
        DEBUG_PRINT("\n");
}

static void
dump_thread(struct thread *thread, int spaces)
{
        struct session_p_node *sd, *first_sd;
	bool fail;
	fail = (thread_check_state(thread) != 0);

	if (fail) {
		DEBUG_PRINT("\e[31;1m");
	}

        DEBUG_PRINT("thread(%p)", thread);
        DEBUG_PRINT(" #%ld", L4_ThreadNo(thread->id));
	if (fail) {
		DEBUG_PRINT("\e[0m");
	}
        DEBUG_PRINT("\n");
	print_spaces(spaces + 1);
	if (thread->eas == NULL) {
		DEBUG_PRINT("Client sessions: ");
		first_sd = thread->server_sessions.first;
		for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
			DEBUG_PRINT("%p ", sd->data);
		}
		DEBUG_PRINT("\n");
		print_spaces(spaces + 1);
		DEBUG_PRINT("Server sessions: ");
		first_sd = thread->client_sessions.first;
		for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
			DEBUG_PRINT("%p ", sd->data);
		} 
		DEBUG_PRINT("\n");
	}
}

static void
dump_eas(struct eas *eas, int depth)
{
        struct thread_node *td, *first_td = eas->threads.first;

	DEBUG_PRINT("eas(%p)", eas);
	DEBUG_PRINT("\n");

        for (td = first_td; td->next != first_td; td = td->next) {
                print_spaces(depth + 1);
                dump_thread(&td->data, depth + 1);
        }
}

static void
dump_session(struct session *session)
{
	bool fail;
	fail = (session_check_state(session) != 0);

	if (fail) {
		DEBUG_PRINT("\e[31;1m");
	}

        DEBUG_PRINT("session(%p)", session);
        DEBUG_PRINT(" Client: #%ld Server: #%ld", 
	       L4_ThreadNo(session->client->id), 
	       L4_ThreadNo(session->server->id));
	if (fail) {
		DEBUG_PRINT("\e[0m");
	}
        DEBUG_PRINT("\n");
}

static void
dump_memsections(struct pd *base_pd, int depth)
{
        struct memsection_node *ms, *first_ms = base_pd->memsections.first;
        struct thread_node     *td, *first_td = base_pd->threads.first;
        struct session_p_node  *sd, *first_sd = base_pd->sessions.first;
        struct pd_node         *pd, *first_pd = base_pd->pds.first;
        struct eas_node        *ed, *first_ed = base_pd->eass.first;
        
        print_spaces(depth);
        dump_pd(base_pd);

        for (ms = first_ms; ms->next != first_ms; ms = ms->next) {
                print_spaces(depth + 1);
                dump_memsection(&ms->data);
        }

        for (td = first_td; td->next != first_td; td = td->next) {
                print_spaces(depth + 1);
                dump_thread(&td->data, depth + 1);
        }

        for (sd = first_sd; sd->next != first_sd; sd = sd->next) {
                print_spaces(depth + 1);
                dump_session(sd->data);
        }

        for (ed = first_ed; ed->next != first_ed; ed = ed->next) {
                print_spaces(depth + 1);
                dump_eas(&ed->data, depth + 1);
        }

        for (pd = first_pd; pd->next != first_pd; pd = pd->next) {
                dump_memsections(&pd->data, depth + 1);
        }
}

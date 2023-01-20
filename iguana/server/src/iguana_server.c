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
  Authors: Ben Leslie, Alex Webster
  Created: Tue Jul  6 2004 

  Description: The main iguana interface
*/
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <interfaces/iguana_server.h>
#include "security.h"
#include "thread.h"
#include "objtable.h"
#include "pd.h"
#include "vm.h"
#include "session.h"
#include "debug.h"
#include "ig_util.h"
#include "quota.h"
#include "exception.h"

#include <l4/kdebug.h>
#include <l4e/sigma0.h>

#define L4_REQUEST_MASK		( ~((~0UL) >> ((sizeof (L4_Word_t) * 8) - 20)))
#define L4_PAGEFAULT		(-2UL << 20)

/* Interface iguana_ex */

#define NUM_MI_OBJECTS 30
extern struct initial_obj mi_objects[NUM_MI_OBJECTS];

#ifdef DEBUG
static const char *
priv_lookup(uintptr_t priv)
{
	switch(priv) {
	case 4:
		return "read";
		break;
	case 2:
		return "write";
		break;
	case 1:
		return "execute";
		break;
	default:
		return "unknown";
	}
}
#endif

IDL4_INLINE static void
iguana_ex_pagefault(CORBA_Object _caller, const uintptr_t addr, 
		    const uintptr_t ip, const uintptr_t priv, 
		    idl4_fpage_t *fp, idl4_server_environment *_env)
{
	/* implementation of iguana_ex::pagefault */
	uintptr_t size;
	struct memsection *memsection;
	uintptr_t ref;
	int reason = 0;
	memsection = objtable_lookup((void*)addr);
	/* Find the memory section it belongs too */
	if (memsection == NULL) {
		DEBUG_PRINT("<iguana_server> No memory section\n");
		reason = 1;
		goto fail;
	}
	/* Here we determine the psuedo method */
	ref = (uintptr_t) memsection + priv; /* FIXME: Work out correct method! */
	if (security_check(_caller, ref) == 0) {
#if 0
		if (memsection_is_special) {
			struct thread *thread_p = thread_lookup(_caller);

			thread_raise_exception(thread_p, EXCEPTION_PAGEFAULT, addr);
			idl4_set_no_response(_env);
			return;
		}
#endif

		size = vm_pagefault(addr, _caller); /* The memory is now back in our A/S */
		if (size == 0) {
			reason = 3;
			goto fail;
		}
		idl4_fpage_set_base(fp, round_down(addr, size));
		idl4_fpage_set_mode(fp, IDL4_MODE_MAP);
		idl4_fpage_set_page(fp, L4_Fpage(round_down(addr, size), size));
		idl4_fpage_set_permissions(fp, priv);
		return;
	}  else {
		DEBUG_PRINT("security failed\n");
		reason = 2;
	}

 fail:
	{
		struct thread *thread;
		L4_Word_t sp, unused;
		char *module_name = "(unknown module)";
		int i;
		void **stack;
		L4_Stop_SpIpFlags(_caller, &sp, &unused, &unused);

		for (i=0; i < NUM_MI_OBJECTS; i++) {
			if (ip >= mi_objects[i].base && ip <= mi_objects[i].end) {
				module_name = mi_objects[i].name;
				break;
			}
		}; 
		if (reason == 3) {
			DEBUG_PRINT("\e[31;1mOut of memory %s fault (%" PRIxPTR "): %p Thread: %lx Module: %s IP: %p SP: %p\e[0m\n",
			       priv_lookup(priv), priv, (void*) addr, _caller.raw, module_name, (void*) ip, (void*) sp);
		} else {
			DEBUG_PRINT("\e[31;1mInvalid %s fault (%" PRIxPTR "): %p Thread: %lx Module: %s IP: %p SP: %p\e[0m\n",
			       priv_lookup(priv), priv, (void*) addr, _caller.raw, module_name, (void*) ip, (void*) sp);
			L4_KDB_Enter("oh no!");
		}
		DEBUG_PRINT("Stack trace back:\n");
		stack = (void**) sp;
		for (i=0; i < 10; i++) {
			DEBUG_PRINT(" <%p> : %p\n", &stack[i], stack[i]);
		}
		if (reason == 1) {
			objtable_print();
		}

		thread = thread_lookup(_caller);
		thread_delete(thread);
		/* Should setup error somehow? */
		return;
	}
}

IDL4_PUBLISH_IGUANA_EX_PAGEFAULT(iguana_ex_pagefault);
void *iguana_ex_ktable[IGUANA_EX_DEFAULT_KTABLE_SIZE] = IGUANA_EX_DEFAULT_KTABLE;
void iguana_ex_discard(void) {}


static struct pd *
get_pd(CORBA_Object _caller, const objref_t pd)
{
	struct pd *the_pd;
	the_pd = (struct pd *) pd;

	if (! is_pd(the_pd)) {
		return NULL;
	}

	return the_pd;
}

IDL4_INLINE static objref_t
iguana_pd_mypd(CORBA_Object _caller, idl4_server_environment *_env)
{
	struct thread *thread;
	struct pd *pd;

	thread = thread_lookup(_caller);
	assert(is_thread(thread));
	pd = thread->owner;
	assert(is_pd(pd));

	return (objref_t) pd;
}

IDL4_INLINE static cap_t
iguana_pd_create_memsection(CORBA_Object _caller, const objref_t pd,
			    const uintptr_t size, const uintptr_t base, const int flags, uintptr_t *out_base, 
			    idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct memsection *memsection;
	struct pd *owner;
	int _flags = flags;
	/* FIXME: We should change Iguana such that flags isn't a const */

	/* Only ever allow user to set valid flags */
	/* FIXME: We should really check for invalid bits here, rather than
	   just masking them off. If a user tries to do something stupid they
	   should get an error. */
	_flags &= MEM_VALID_USER_FLAGS;

	owner = get_pd(_caller, pd);

	if (owner == NULL) {
		return cap;
	}

	memsection = pd_create_memsection(owner, size, base, _flags);
	if (memsection != NULL) {
		*out_base = memsection->base;
	} else {
		*out_base = 0;
	}
	cap.ref.memsection = (memsection_ref_t) memsection;

	return cap;
}

IDL4_INLINE static cap_t
iguana_pd_create_thread(CORBA_Object _caller, const pd_ref_t pd, const int priority,
			L4_ThreadId_t *l4_id, idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct thread *thread;
	struct pd *owner;
	
	owner = get_pd(_caller, pd);
	*l4_id = L4_nilthread;

	if (owner != NULL) {
		thread = pd_create_thread(owner, priority);
		if (thread != NULL) {
			*l4_id = thread->id;
			cap.ref.thread = (thread_ref_t) thread;
		}
	}

	return cap;
}


IDL4_INLINE static cap_t
iguana_pd_create_eas(CORBA_Object _caller, const pd_ref_t pd, L4_Fpage_t *kip,
		     L4_Fpage_t *utcb, idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct eas *eas;
	struct pd *owner;
	

	owner = get_pd(_caller, pd);

	eas = pd_create_eas(owner, *kip, *utcb);
	cap.ref.eas = (eas_ref_t) eas;
	return cap;
}

IDL4_INLINE static cap_t
iguana_pd_create_pd(CORBA_Object _caller, const pd_ref_t pd, idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct pd *newpd;
	struct pd *owner;
	

	owner = get_pd(_caller, pd);

	newpd = pd_create(owner, 0 /* Max threads */);
	cap.ref.pd = (pd_ref_t) newpd;
	return cap;
}

IDL4_INLINE static cap_t
iguana_pd_create_session(CORBA_Object _caller, const pd_ref_t pd,
			 const thread_ref_t client, const thread_ref_t server,
			 const memsection_ref_t clist,
			 idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct session *session;
	struct pd *owner;
	
	/* FIXME: Need to do a security check here */
	if (client == 0 || server == 0) {
		return cap;
	}

	owner = get_pd(_caller, pd);

	session = pd_create_session(owner, (struct thread *) client,
				    (struct thread *) server,
				    (struct memsection *) clist);
	cap.ref.pd = (session_ref_t) session;
	return cap;
}

IDL4_INLINE static void
iguana_pd_set_callback(CORBA_Object _caller, const pd_ref_t pd, 
		       const memsection_ref_t callback_buffer, 
		       idl4_server_environment *_env)
{
	/* Currently PD callback doesn't work, and isn't actually used.
	   so we disable it for now */
	pd_setup_callback((struct pd *) pd, 
			  (struct memsection *) callback_buffer);
	return;
}




IDL4_INLINE static uintptr_t
iguana_pd_add_clist(CORBA_Object _caller, const pd_ref_t pd,
		    const memsection_ref_t clist, 
		    idl4_server_environment *_env)
{
	return pd_add_clist((struct pd *) pd,
			    (cap_t *) ((struct memsection *) clist)->base);
}

IDL4_PUBLISH_IGUANA_PD_ADD_CLIST(iguana_pd_add_clist);

IDL4_INLINE static void
iguana_pd_release_clist(CORBA_Object _caller, const pd_ref_t pd,
			const uintptr_t clist, const int slot,
			idl4_server_environment *_env)
{
	pd_release_clist((struct pd *) pd,
			 (cap_t *) clist);
}

IDL4_PUBLISH_IGUANA_PD_RELEASE_CLIST(iguana_pd_release_clist);

IDL4_INLINE static quota_ref_t
iguana_pd_get_quota(CORBA_Object _caller, const pd_ref_t pd, idl4_server_environment *_env)
{
	return (quota_ref_t)(((struct pd *)pd)->quota);
}

IDL4_INLINE static void
iguana_pd_delete(CORBA_Object _caller, const pd_ref_t pd, idl4_server_environment *_env)
{
	/* implementation of iguana_pd::delete */
	objref_t caller_pd;
	caller_pd = iguana_pd_mypd(_caller, _env);
	pd_delete((struct pd *) pd);
	if (caller_pd == pd) {
		idl4_set_no_response(_env);
	}
	return;
}


IDL4_PUBLISH_IGUANA_PD_MYPD(iguana_pd_mypd);
IDL4_PUBLISH_IGUANA_PD_CREATE_MEMSECTION(iguana_pd_create_memsection);
IDL4_PUBLISH_IGUANA_PD_CREATE_THREAD(iguana_pd_create_thread);
IDL4_PUBLISH_IGUANA_PD_CREATE_EAS(iguana_pd_create_eas);
IDL4_PUBLISH_IGUANA_PD_CREATE_PD(iguana_pd_create_pd);
IDL4_PUBLISH_IGUANA_PD_CREATE_SESSION(iguana_pd_create_session);
IDL4_PUBLISH_IGUANA_PD_SET_CALLBACK(iguana_pd_set_callback);
IDL4_PUBLISH_IGUANA_PD_GET_QUOTA(iguana_pd_get_quota);
IDL4_PUBLISH_IGUANA_PD_DELETE(iguana_pd_delete);
void *iguana_pd_vtable[IGUANA_PD_DEFAULT_VTABLE_SIZE] = IGUANA_PD_DEFAULT_VTABLE;
void iguana_pd_discard(void) {}


IDL4_INLINE static cap_t
iguana_eas_create_thread(CORBA_Object _caller, const eas_ref_t eas,
			 const L4_ThreadId_t *pager, const L4_ThreadId_t *scheduler,
			 const uintptr_t utcb, L4_ThreadId_t *l4_id,
			 idl4_server_environment *_env)
{
	cap_t cap = { { obj: 0 }, 0 };
	struct thread *thread;
	thread = eas_create_thread((void*) eas, *pager, *scheduler, utcb);
	if (thread) {
		*l4_id = thread->id;
		cap.ref.thread = (thread_ref_t) thread;
	} else {
		*l4_id = L4_nilthread;
	}
	return cap;
}

IDL4_INLINE static void
iguana_eas_delete(CORBA_Object _caller, const eas_ref_t eas, idl4_server_environment *_env)
{
	eas_delete((void *)eas);
	eas_list_delete((void *)eas);
	return;
}


IDL4_PUBLISH_IGUANA_EAS_CREATE_THREAD(iguana_eas_create_thread);
IDL4_PUBLISH_IGUANA_EAS_DELETE(iguana_eas_delete);
void *iguana_eas_vtable[IGUANA_EAS_DEFAULT_VTABLE_SIZE] = IGUANA_EAS_DEFAULT_VTABLE;

/* Interface iguana_thread */
IDL4_INLINE static thread_ref_t
iguana_thread_id(CORBA_Object _caller, const L4_ThreadId_t *thread, idl4_server_environment *_env)
{
	thread_ref_t ret_thread = 0;
	ret_thread = (thread_ref_t) thread_lookup(*thread);
	return ret_thread;
}

IDL4_INLINE static L4_ThreadId_t
iguana_thread_l4id(CORBA_Object _caller, const thread_ref_t thread, idl4_server_environment *_env)
{
	struct thread *the_thread = (struct thread *) thread;

	/* FIXME: Check permission on thread */

	if (thread == 0) {
		return L4_nilthread;
	}

	return the_thread->id;
}

IDL4_INLINE static void
iguana_thread_start(CORBA_Object _caller, const thread_ref_t thread, 
		    const uintptr_t ip, const uintptr_t sp, 
		    idl4_server_environment *_env)
{
	/* implementation of iguana_thread::start */
	thread_start((struct thread *) thread, ip, sp);
	return;
}

IDL4_INLINE static void
iguana_thread_delete(CORBA_Object _caller, const thread_ref_t thread,
		     idl4_server_environment *_env)
{
	struct thread *thread_p;
	struct thread * victim = (struct thread *)thread;

	thread_p = thread_lookup(_caller);

	if (victim == NULL) {
		return; /* no victim then we fail */
	}

	if (victim->eas) {
		eas_delete_thread(victim->eas, victim);
	} else {
		pd_delete_thread(victim->owner, victim);
	}
	if (thread_p == victim) {
		idl4_set_no_response(_env);
	}
	return;
}

IDL4_INLINE static void
iguana_thread_set_exception(CORBA_Object _caller, thread_ref_t thread,
		uintptr_t exc, uintptr_t sp, uintptr_t ip, 
		idl4_server_environment *_env)
{
 	struct thread *thread_p = (struct thread *) thread;
 
	/* XXX: check exc is a valid exception */
	DEBUG_PRINT("set(%lx, %lx)\n", (long)ip, (long)sp);
	thread_p->exception[exc].sp = sp;
	thread_p->exception[exc].ip = ip;
}

IDL4_PUBLISH_IGUANA_THREAD_ID(iguana_thread_id);
IDL4_PUBLISH_IGUANA_THREAD_L4ID(iguana_thread_l4id);
IDL4_PUBLISH_IGUANA_THREAD_DELETE(iguana_thread_delete);
IDL4_PUBLISH_IGUANA_THREAD_START(iguana_thread_start);
IDL4_PUBLISH_IGUANA_THREAD_SET_EXCEPTION(iguana_thread_set_exception);
void *iguana_thread_vtable[IGUANA_THREAD_DEFAULT_VTABLE_SIZE] = IGUANA_THREAD_DEFAULT_VTABLE;
void iguana_thread_discard(void) {}

/* Interface iguana_hardware */

IDL4_INLINE static CORBA_long
iguana_hardware_register_interrupt(CORBA_Object _caller, const objref_t hardware, 
				   const L4_ThreadId_t *handler, const CORBA_long interrupt,
				   idl4_server_environment *_env)
{
	CORBA_long __retval = 0;
	int r;
	r = L4_AssociateInterrupt(L4_GlobalId(interrupt, 1), *handler);
#if 0	/* XXX you dont want to assert() just like that. */
	assert(r == 1);
#endif
	__retval = r;
	return __retval;
}

IDL4_INLINE static CORBA_long
iguana_hardware_back_memsection(CORBA_Object _caller, const objref_t hardware,
				const memsection_ref_t memsection, const uintptr_t paddr,
				const uintptr_t attributes, idl4_server_environment *_env)
{
	CORBA_long __retval = 0;
	int r;
	struct memsection * ms = (void*) memsection;

/*
 * Bogus.  We want to be able to allocate a piece of vm, back it
 * later on without caring what kind of vm it is.  Think of 
 * vm_allocate(), then IOMapPages() in Mach.
 *
 * -gl
 */
#if 0
	if (!(ms->flags & MEM_USER))
		return -1;
#endif

	ms->phys.base = paddr;
	l4e_sigma0_map(ms->base, paddr, ms->end - ms->base + 1);
	r = vm_change_attributes(ms->base, ms->end, attributes);
	if (r != 0) {
		/* We failed in setting the attributes so we have to cleanup */
		memsection_flush(ms);
		__retval = -1;
	}
	ms->memory_attributes = attributes;
	return __retval;
}

IDL4_PUBLISH_IGUANA_HARDWARE_REGISTER_INTERRUPT(iguana_hardware_register_interrupt);
IDL4_PUBLISH_IGUANA_HARDWARE_BACK_MEMSECTION(iguana_hardware_back_memsection);
void *iguana_hardware_vtable[IGUANA_HARDWARE_DEFAULT_VTABLE_SIZE] = IGUANA_HARDWARE_DEFAULT_VTABLE;
void iguana_hardware_discard(void) {}

/* Interface iguana_memsection */

IDL4_INLINE static CORBA_long
iguana_memsection_register_server(CORBA_Object _caller, 
				  const memsection_ref_t memsection, 
				  const thread_ref_t thread, 
				  idl4_server_environment *_env)
{
	CORBA_long __retval = 0;

	if (memsection == 0) {
		return 0;
	}

	memsection_register_server(((struct memsection *) memsection), 
				   (struct thread *) thread);
	return __retval;
}

IDL4_INLINE static memsection_ref_t
iguana_memsection_lookup(CORBA_Object _caller, const uintptr_t address, 
			 thread_ref_t *server,
			 idl4_server_environment *_env)
{
	struct memsection *memsection = objtable_lookup((void*) address);
	if (memsection == NULL) {
		return 0;
	}

	*server = (thread_ref_t) memsection->server;
	return (memsection_ref_t) memsection;
}

IDL4_INLINE static void
iguana_memsection_delete(CORBA_Object _caller, const memsection_ref_t memsection, idl4_server_environment *_env)
{

	memsection_delete((struct memsection *) memsection);
	return;
}

IDL4_INLINE static CORBA_long
iguana_memsection_info(CORBA_Object _caller, const memsection_ref_t memsection, uintptr_t *size,
		       idl4_server_environment *_env)
{
	struct memsection *memsect = (struct memsection *) memsection;
	*size = memsect->end - memsect->base + 1;
	return memsect->base;
}

IDL4_INLINE static void
iguana_memsection_set_attributes(CORBA_Object _caller, const memsection_ref_t memsection, 
				 uintptr_t attributes, idl4_server_environment *_env)
{
	int ret;
	ret = memsection_set_attributes((struct memsection *) memsection, attributes);
	assert(ret == 0);
	return;
}

IDL4_INLINE static int
iguana_memsection_page_map(CORBA_Object _caller, const memsection_ref_t memsection, 
		L4_Fpage_t *from_page, L4_Fpage_t *to_page, idl4_server_environment *_env)

{
	return memsection_page_map((struct memsection *)memsection, *from_page, *to_page);
}

IDL4_INLINE static int
iguana_memsection_page_unmap(CORBA_Object _caller, const memsection_ref_t memsection, 
		L4_Fpage_t *to_page, idl4_server_environment *_env)
{
	return memsection_page_unmap((struct memsection *)memsection, *to_page);
}

IDL4_PUBLISH_IGUANA_MEMSECTION_REGISTER_SERVER(iguana_memsection_register_server);
IDL4_PUBLISH_IGUANA_MEMSECTION_DELETE(iguana_memsection_delete);
IDL4_PUBLISH_IGUANA_MEMSECTION_LOOKUP(iguana_memsection_lookup);
IDL4_PUBLISH_IGUANA_MEMSECTION_INFO(iguana_memsection_info);
IDL4_PUBLISH_IGUANA_MEMSECTION_SET_ATTRIBUTES(iguana_memsection_set_attributes);
IDL4_PUBLISH_IGUANA_MEMSECTION_PAGE_MAP(iguana_memsection_page_map);
IDL4_PUBLISH_IGUANA_MEMSECTION_PAGE_UNMAP(iguana_memsection_page_unmap);
void *iguana_memsection_vtable[IGUANA_MEMSECTION_DEFAULT_VTABLE_SIZE] = IGUANA_MEMSECTION_DEFAULT_VTABLE;
void iguana_memsection_discard(void) {}

/* Interface iguana_session */

IDL4_INLINE static void
iguana_session_delete(CORBA_Object _caller, const session_ref_t session, 
		      idl4_server_environment *_env)
{
	session_delete((struct session *) session);
	return;
}

IDL4_INLINE static int
iguana_session_revoke(CORBA_Object _caller, const session_ref_t session, const cap_t *cap,
		      idl4_server_environment *_env)
{
	struct memsection *memsection = (void*) cap->ref.memsection;
	memsection_flush(memsection);
	return 0;
}


IDL4_INLINE static void
iguana_session_add_buffer(CORBA_Object _caller, const session_ref_t session, 
			  const objref_t call_buf, const objref_t return_buf,
			  idl4_server_environment *_env)
{
	session_add_buffer((struct session *) session, 
			   (void*) call_buf, (void*) return_buf);
	return;
}

IDL4_PUBLISH_IGUANA_SESSION_DELETE(iguana_session_delete);
IDL4_PUBLISH_IGUANA_SESSION_REVOKE(iguana_session_revoke);
IDL4_PUBLISH_IGUANA_SESSION_ADD_BUFFER(iguana_session_add_buffer);
void *iguana_session_vtable[IGUANA_SESSION_DEFAULT_VTABLE_SIZE] = IGUANA_SESSION_DEFAULT_VTABLE;
void iguana_session_discard(void) {}

IDL4_INLINE static void
iguana_debug_dump_info(CORBA_Object _caller, idl4_server_environment *_env)
{
        debug_dump_info();
}

IDL4_PUBLISH_IGUANA_DEBUG_DUMP_INFO(iguana_debug_dump_info);
void *iguana_debug_vtable[IGUANA_DEBUG_DEFAULT_VTABLE_SIZE] = IGUANA_DEBUG_DEFAULT_VTABLE;

/* Interface iguana_quota */

IDL4_INLINE static CORBA_long
iguana_quota_transfer(CORBA_Object _caller, quota_ref_t q1, quota_ref_t q2, const CORBA_long amount, idl4_server_environment *_env)
{
	return quota_transfer((struct quota *)q1, (struct quota *)q2, amount);
}

IDL4_INLINE static CORBA_long
iguana_quota_get_max(CORBA_Object _caller, const quota_ref_t q, idl4_server_environment *_env)
{	
	return ((struct quota *)q)->max_pages;
}

IDL4_INLINE static CORBA_long
iguana_quota_get_used(CORBA_Object _caller, const quota_ref_t q, idl4_server_environment *_env)
{
	return ((struct quota *)q)->used_pages;
}


IDL4_PUBLISH_IGUANA_QUOTA_TRANSFER(iguana_quota_transfer);
IDL4_PUBLISH_IGUANA_QUOTA_GET_MAX(iguana_quota_get_max);
IDL4_PUBLISH_IGUANA_QUOTA_GET_USED(iguana_quota_get_used);
void *iguana_quota_vtableTN


[IGUANA_QUOTA_DEFAULT_VTABLE_SIZE] = IGUANA_QUOTA_DEFAULT_VTABLE;
void iguana_quota_discard(void) {}


void iguana_server(void);

void
iguana_server(void)
{
	L4_ThreadId_t partner;
	L4_MsgTag_t msgtag;
	idl4_msgbuf_t msgbuf;
	long cnt;
	
	idl4_msgbuf_init(&msgbuf);
	for (cnt = 0;cnt < IGUANA_EX_STRBUF_SIZE;cnt++)
		idl4_msgbuf_add_buffer(&msgbuf, malloc(8000), 8000);

	while (1) {
		partner = L4_nilthread;
		msgtag.raw = 0;
		cnt = 0;
		
		while (1) {
#ifdef CONFIG_TEST_IGUANA
			iguana_check_state();
#endif
			idl4_msgbuf_sync(&msgbuf);
			
			idl4_reply_and_wait(&partner, &msgtag, &msgbuf, &cnt);
			
			if (idl4_is_error(&msgtag)) {
				DEBUG_PRINT("###### iguana_server: Error sending IPC reply\n");
				break;
			}

			/* if it's a kernel pagefault message */
			if( (msgtag.raw & L4_REQUEST_MASK) == L4_PAGEFAULT ) {
				idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
						     iguana_ex_ktable[idl4_get_kernel_message_id(msgtag) & 
								      IGUANA_EX_KID_MASK]);
			} else {
				switch (magpie_get_interface_bigid(&msgbuf)) {
				case _C_INTERFACE_IGUANA_PD_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_pd_vtable[idl4_get_function_id(&msgtag) & 
									      IGUANA_PD_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_EAS_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_eas_vtable[idl4_get_function_id(&msgtag) & 
									       IGUANA_EAS_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_THREAD_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_thread_vtable[idl4_get_function_id(&msgtag) & 
										  IGUANA_THREAD_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_HARDWARE_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_hardware_vtable[idl4_get_function_id(&msgtag) & 
										  IGUANA_HARDWARE_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_MEMSECTION_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_memsection_vtable[idl4_get_function_id(&msgtag) & 
										  IGUANA_MEMSECTION_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_SESSION_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_session_vtable[idl4_get_function_id(&msgtag) & 
										  IGUANA_SESSION_FID_MASK]);
					break;
				case _C_INTERFACE_IGUANA_DEBUG_UUID:
					idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
							     iguana_debug_vtable[idl4_get_function_id(&msgtag) & 
										  IGUANA_DEBUG_FID_MASK]);
					break;
				default:
					DEBUG_PRINT("iguana_server: Unknown interface called (%lx)...\n", 
							magpie_get_interface_bigid(&msgbuf));
					break;
				}
			}
		}
	}
}



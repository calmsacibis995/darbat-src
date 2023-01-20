/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2004 University of New South Wales
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
/*
  Author: Ben Leslie
*/
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cb.h>
#include <ll.h>
#include <binary_tree/binary_tree.h>
#include <interfaces/naming_server.h>

static void naming_server(void);

extern void * __callback_buffer;
struct cb_get_handle *iguana_cb_handle;

struct bin_tree *bin_tree;

#define NAMING_NOTIFY_INSERT 1
#define NAMING_NOTIFY_MODIFY 2
#define NAMING_NOTIFY_DELETE 4

struct notify_list
{
    struct notify_node* first;
    struct notify_node* last;
};

struct naming_info;

struct notify {
	L4_ThreadId_t thread;
	uintptr_t mask;
	int flags;
	struct naming_info *naming_info;
};

struct notify_node
{
    struct notify_node* next;
    struct notify_node* prev;
    struct notify data;
};

static inline struct notify * notify_list_create_front(struct notify_list* list)
{
	return (struct notify *) dl_list_create_front((struct double_list *) list, sizeof(struct notify));
}\
static inline struct notify * notify_list_create_back(struct notify_list* list)
{
	return (struct notify *) dl_list_create_back((struct double_list *) list, sizeof(struct notify));
}
static inline void notify_list_delete(struct notify * data)
{
	ll_delete((struct ll *) ((void**) data - 2));
}
static inline void notify_list_init(struct notify_list *list)
{
	dl_list_init((struct double_list *) list);	\
}
static inline void notify_list_clear(struct notify_list * list)
{
	dl_list_clear((struct double_list *) list);
}


struct naming_info {
	uintptr_t data;
	/* list of notifications */
	struct notify_list notifies;
	char name[1]; /* This is the standard struct hack. C99
			 would let us do char name[], but the ARM 
			 toolchain doesn't support C99 */
};

int
main(int argc, char **argv)
{
	iguana_cb_handle = cb_attach(__callback_buffer);
	bin_tree = binary_tree_new();
	naming_server();
	assert(!"Shouldn't reach here\n");
}

static struct naming_info *
create_name_node(char *name)
{
	struct naming_info *naming_info;
	int r;

	naming_info = malloc(sizeof(struct naming_info) + strlen(name));
	/* Note: We don't need a +1 for NULL here as the name field is declared
	   as char name[1] , not char name[]. This is for compatability with pre C99
	   compiles which don't support either char name[], or char name[0]. */

	if (naming_info == NULL) {
		return NULL;
	}

	strcpy(naming_info->name, name);

	naming_info->data = 0;

	r = binary_tree_insert(bin_tree, naming_info->name, naming_info);

	if (r != 0) {
		free(naming_info);
		return NULL;
	}

	notify_list_init(&naming_info->notifies); /* FIXME: Could this fail? */
	return naming_info;
}

static inline void
do_notify(L4_ThreadId_t thread, uintptr_t mask)
{
	L4_Notify(thread, mask);
}

static void
notify_list(struct naming_info *naming_info, int flags, L4_ThreadId_t caller, uintptr_t *mask)
{
	struct notify_node *notify;
	for (notify = naming_info->notifies.first; 
	     notify->next != naming_info->notifies.first;
	     notify = notify->next) {
		if (notify->data.flags & flags) {
			do_notify(notify->data.thread, notify->data.mask);
		}
	}
}

IDL4_INLINE static objref_t
naming_insert (CORBA_Object _caller, objref_t nameserver, char *name, objref_t data,
	       uintptr_t *mask,
	       idl4_server_environment *_env)
{
	struct naming_info *naming_info;

	*mask = 0;

	/* First see if it exists */
	naming_info = binary_tree_lookup(bin_tree, name);

	if (naming_info == NULL) {
		/* Create a new one */
		naming_info = create_name_node(name);
		if (naming_info == NULL) {
			return -1;
		}
	}

	if (naming_info->data != 0) {
		return -1;
	}

	naming_info->data = data;
	/* Now go and notify any people waiting for it */
	notify_list(naming_info, NAMING_NOTIFY_INSERT, _caller, mask);

	return 0;
}

IDL4_PUBLISH_NAMING_WRITE_INSERT(naming_insert)

IDL4_INLINE static int
naming_modify (CORBA_Object _caller, objref_t nameserver, char *name, objref_t data,
	       uintptr_t *mask,
	       idl4_server_environment *_env)
{
	struct naming_info * naming_info;

	*mask = 0;

	/* First see if it exists */
	naming_info = binary_tree_lookup(bin_tree, name);

	if (naming_info == NULL) {
		return -1;
	}

	naming_info->data = data;

	/* Now go and notify and waiters */
	notify_list(naming_info, NAMING_NOTIFY_MODIFY, _caller, mask);

	return 0;
}

IDL4_PUBLISH_NAMING_WRITE_MODIFY(naming_modify)

IDL4_INLINE static int
naming_delete (CORBA_Object _caller, objref_t nameserver, char *name, 
	       uintptr_t *mask,
	       idl4_server_environment *_env)
{
	struct naming_info * naming_info;

	*mask = 0;

	/* First see if it exists */
	naming_info = binary_tree_lookup(bin_tree, name);

	if (naming_info == NULL) {
		return -1;
	}

	naming_info->data = 0;

	/* Notify people */
	notify_list(naming_info, NAMING_NOTIFY_DELETE, _caller, mask);

	/* If no people to notify remove from tree */
	if (naming_info->notifies.first == (void*) &naming_info->notifies.first) {
		/* print empty list ! */
		binary_tree_remove(bin_tree, name);
		free(naming_info);
	}
	return 0;
}


IDL4_PUBLISH_NAMING_WRITE_DELETE(naming_delete)

void *naming_write_vtable[NAMING_WRITE_DEFAULT_VTABLE_SIZE] = NAMING_WRITE_DEFAULT_VTABLE;
void naming_write_discard(void) {}


IDL4_INLINE static objref_t
naming_lookup (CORBA_Object _caller, objref_t nameserver, char *name, 
	       idl4_server_environment *_env)
{
	struct naming_info * naming_info;
	/* First see if it exists */
	naming_info = binary_tree_lookup(bin_tree, name);

	if (naming_info == NULL) {
		return 0;
	}

	return naming_info->data;
}

IDL4_INLINE static objref_t
naming_notify (CORBA_Object _caller, objref_t nameserver, char *name, int flags, L4_ThreadId_t *thread, 
	       uintptr_t mask, uintptr_t *outmask,
	       idl4_server_environment *_env)
{
	/* Notification request */
	struct naming_info * naming_info;
	struct notify *notify;
	int created = 0;
	*outmask = 0;

	/* First see if it exists */
	naming_info = binary_tree_lookup(bin_tree, name);

	if (naming_info == NULL) {
		/* Create it */
		created = 1;
		naming_info = create_name_node(name);
		if (naming_info == NULL) {
			return 0;
		}

	}

	/* Create notify struct and into list */
	notify = notify_list_create_back(&naming_info->notifies);
	if (notify == NULL) {
		if (created) {
			/* Delete newly created name node */
			binary_tree_remove(bin_tree, name);
			free(naming_info);
		}
		return 0;
	}

	notify->flags = flags;
	notify->mask = mask;
	notify->thread = *thread;
	notify->naming_info = naming_info;

	if (naming_info->data != 0 && (flags & NAMING_NOTIFY_INSERT) ) {
		/* Notify waiter */
		do_notify(*thread, mask);
	}

	return (objref_t) notify;
}

IDL4_PUBLISH_NAMING_READ_LOOKUP(naming_lookup)
IDL4_PUBLISH_NAMING_READ_NOTIFY(naming_notify)

void *naming_read_vtable[NAMING_READ_DEFAULT_VTABLE_SIZE] = NAMING_READ_DEFAULT_VTABLE;
void naming_read_discard(void) {}


IDL4_INLINE static int
naming_cancel (CORBA_Object _caller, objref_t notify_obj,
	       idl4_server_environment *_env)
{
	struct notify *notify = (struct notify*) notify_obj;
	struct naming_info *naming_info = notify->naming_info;

	/* Remove from list */
	notify_list_delete(notify);

	/* If list is empty and data == 0, remove naming data structure */
	if (naming_info->notifies.first == (void*) &naming_info->notifies.first && 
	    naming_info->data == 0) {
		/* print empty list ! */
		binary_tree_remove(bin_tree, naming_info->name);
		free(naming_info);
	}

	return 0;
}


IDL4_PUBLISH_NAMING_NOTIFY__CANCEL(naming_cancel)

void *naming_notify__vtable[NAMING_NOTIFY__DEFAULT_VTABLE_SIZE] = NAMING_NOTIFY__DEFAULT_VTABLE;
void naming_notify__discard(void) {}

static void
naming_server(void)
{
	L4_ThreadId_t partner;
	L4_MsgTag_t msgtag;
	idl4_msgbuf_t msgbuf;
	long cnt;
	uintptr_t *size;

	partner = L4_nilthread;
	msgtag.raw = 0;
	cnt = 0;

	while(1) {
		/* Now check async queues -- we check this everytime, which
		   is a bit silly, would be nice if we could detect a failed
		   ipc to us */
		size = cb_get(iguana_cb_handle, sizeof(uintptr_t));
		if (size) {
			//uintptr_t *data = 
			cb_get(iguana_cb_handle, *size);
		}
		/* Wait for message */
		idl4_msgbuf_sync(&msgbuf);
		idl4_reply_and_wait(&partner, &msgtag, &msgbuf, &cnt);
		if (idl4_is_error(&msgtag)) {
			printf("Error %lx\n", L4_ErrorCode());
			partner = L4_nilthread;
			msgtag.raw = 0;
			cnt = 0;
			continue;
		}
		
		switch (magpie_get_interface_bigid(&msgbuf)) {
		case 42:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
					     naming_write_vtable[idl4_get_function_id(&msgtag) & NAMING_WRITE_FID_MASK]);
			break;
		case 43:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
					     naming_read_vtable[idl4_get_function_id(&msgtag) & NAMING_READ_FID_MASK]);
			break;
		case 44:
			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, 
					     naming_notify__vtable[idl4_get_function_id(&msgtag) & NAMING_NOTIFY__FID_MASK]);
			break;
		default:
			printf("naming: naming_server: Bad label! (0x%lx)\n", magpie_get_interface_bigid(&msgbuf));
			partner = L4_nilthread;
		}
	}
}


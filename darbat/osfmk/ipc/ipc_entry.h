/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	ipc/ipc_entry.h
 *	Author:	Rich Draves
 *	Date:	1989
 *
 *	Definitions for translation entries, which represent
 *	tasks' capabilities for ports and port sets.
 */

#ifndef	_IPC_IPC_ENTRY_H_
#define _IPC_IPC_ENTRY_H_

#include <mach/mach_types.h>
#include <mach/port.h>
#include <mach/kern_return.h>

#include <kern/kern_types.h>
#include <kern/zalloc.h>

#include <ipc/ipc_types.h>

/*
 *	Spaces hold capabilities for ipc_object_t's.
 *	Each ipc_entry_t records a capability.  Most capabilities have
 *	small names, and the entries are elements of a table.
 *	Capabilities can have large names, and a splay tree holds
 *	those entries.  The cutoff point between the table and the tree
 *	is adjusted dynamically to minimize memory consumption.
 *
 *	The ie_index field of entries in the table implements
 *	a ordered hash table with open addressing and linear probing.
 *	This hash table converts (space, object) -> name.
 *	It is used independently of the other fields.
 *
 *	Free (unallocated) entries in the table have null ie_object
 *	fields.  The ie_bits field is zero except for IE_BITS_GEN.
 *	The ie_next (ie_request) field links free entries into a free list.
 *
 *	The first entry in the table (index 0) is always free.
 *	It is used as the head of the free list.
 */

struct ipc_entry {
	struct ipc_object *ie_object;
	ipc_entry_bits_t ie_bits;
	union {
		mach_port_index_t next;		/* next in freelist, or...  */
		ipc_table_index_t request;	/* dead name request notify */
	} index;
	union {
		mach_port_index_t table;
		struct ipc_tree_entry *tree;
	} hash;
};

#define	ie_request	index.request
#define	ie_next		index.next
#define	ie_index	hash.table

#define	IE_BITS_UREFS_MASK	0x0000ffff	/* 16 bits of user-reference */
#define	IE_BITS_UREFS(bits)	((bits) & IE_BITS_UREFS_MASK)

#define	IE_BITS_TYPE_MASK	0x001f0000	/* 5 bits of capability type */
#define	IE_BITS_TYPE(bits)	((bits) & IE_BITS_TYPE_MASK)

#define	IE_BITS_COLLISION	0x00800000	/* 1 bit for collisions */


#ifndef NO_PORT_GEN
#define	IE_BITS_GEN_MASK	0xff000000	/* 8 bits for generation */
#define	IE_BITS_GEN(bits)	((bits) & IE_BITS_GEN_MASK)
#define	IE_BITS_GEN_ONE		0x04000000	/* low bit of generation */
#define IE_BITS_NEW_GEN(old)	(((old) + IE_BITS_GEN_ONE) & IE_BITS_GEN_MASK)
#else
#define	IE_BITS_GEN_MASK	0
#define	IE_BITS_GEN(bits)	0
#define	IE_BITS_GEN_ONE		0
#define IE_BITS_NEW_GEN(old)	(old)
#endif	/* !USE_PORT_GEN */


#define	IE_BITS_RIGHT_MASK	0x007fffff	/* relevant to the right */

struct ipc_tree_entry {
	struct ipc_entry ite_entry;
	mach_port_name_t ite_name;
	struct ipc_space *ite_space;
	struct ipc_tree_entry *ite_lchild;
	struct ipc_tree_entry *ite_rchild;
};

#define	ite_bits	ite_entry.ie_bits
#define	ite_object	ite_entry.ie_object
#define	ite_request	ite_entry.ie_request
#define	ite_next	ite_entry.hash.tree

extern zone_t ipc_tree_entry_zone;

#define ite_alloc()	((ipc_tree_entry_t) zalloc(ipc_tree_entry_zone))
#define	ite_free(ite)	zfree(ipc_tree_entry_zone, (ite))

/*
 * Exported interfaces
 */

/* Search for entry in a space by name */
extern ipc_entry_t ipc_entry_lookup(
	ipc_space_t		space,
	mach_port_name_t	name);

/* Allocate an entry in a space */
extern kern_return_t ipc_entry_get(
	ipc_space_t		space,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp);

/* Allocate an entry in a space, growing the space if necessary */
extern kern_return_t ipc_entry_alloc(
	ipc_space_t		space,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp);

/* Allocate/find an entry in a space with a specific name */
extern kern_return_t ipc_entry_alloc_name(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		*entryp);

/* Deallocate an entry from a space */
extern void ipc_entry_dealloc(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry);

/* Grow the table in a space */
extern kern_return_t ipc_entry_grow_table(
	ipc_space_t		space,
	ipc_table_elems_t	target_size);

#endif	/* _IPC_IPC_ENTRY_H_ */

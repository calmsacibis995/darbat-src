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
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
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
/* pretty much clagged straight from Mach */

#if 0

// #include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/init.h>
#include <kern/zalloc.h>
#include <mach/memory_object_control.h>

#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <kern/zalloc.h>
#include <kern/kalloc.h>
#include <libkern/libkern.h>

#include <sys/vnode_internal.h>
#include <vm/vnode_pager.h>

// #include <vm/vm_object.h>
#include <vm/vm_protos.h>

/* XXX: this type is used in BSD and Mach!!! */
#define vnode_pager_t BLAH BLAH BLAH

struct vnode_pager 
{
	int 			*pager;		/* pager workaround pointer  */
	unsigned int		pager_ikot;	/* JMM: fake ip_kotype()     */
	unsigned int		ref_count;	/* reference count	     */
	memory_object_control_t control_handle;	/* mem object control handle */
	struct vnode		*vnode_handle;	/* vnode handle 	     */
};


/* TODO: Should be set dynamically by vnode_pager_bootstrap() */
#define	MAX_VNODE		10000

zone_t	vnode_pager_zone;

/* until component support available */
int	vnode_pager_workaround;


/* XXXX */
#define	IKOT_MEMORY_OBJECT		11
/********/


struct vnode_pager *
vnode_object_create(			/* forward */
	struct vnode *);

/*
 *
 */
void
vnode_pager_bootstrap(void)
{
	register vm_size_t      size;

	size = (vm_size_t) sizeof(struct vnode_pager);
	vnode_pager_zone = zinit(size, (vm_size_t) MAX_VNODE*size,
				PAGE_SIZE, "vnode pager structures");
	return;
}


/*
 *
 */
vm_pager_t
vnode_pager_setup(
	struct vnode	*vp,
	__unused memory_object_t	pager)
{
	struct vnode_pager *vnode_object;

	vnode_object = vnode_object_create(vp);
	if (vnode_object == VNODE_PAGER_NULL)
		panic("vnode_pager_setup: vnode_object_create() failed");
	return((vm_pager_t) vnode_object);
}


/*
 *
 */
struct vnode_pager *
vnode_object_create( struct vnode *vp )
{
	register struct vnode_pager * vnode_object;

	vnode_object = (struct vnode_pager *) zalloc(vnode_pager_zone);
	if (vnode_object == VNODE_PAGER_NULL)
		return(VNODE_PAGER_NULL);

	/*
	 * The vm_map call takes both named entry ports and raw memory
	 * objects in the same parameter.  We need to make sure that
	 * vm_map does not see this object as a named entry port.  So,
	 * we reserve the second word in the object for a fake ip_kotype
	 * setting - that will tell vm_map to use it as a memory object.
	 */
	vnode_object->pager = &vnode_pager_workaround;
	vnode_object->pager_ikot = IKOT_MEMORY_OBJECT;
	vnode_object->ref_count = 1;
	vnode_object->control_handle = MEMORY_OBJECT_CONTROL_NULL;
	vnode_object->vnode_handle = vp;

	return(vnode_object);
}

/*
 *
 */
void
vnode_pager_deallocate( memory_object_t mem_obj)
{
	printf( "XXX: ignoring pager_dealloc request\n" );
#if 0
	register vnode_pager_t	vnode_object;

	PAGER_DEBUG(PAGER_ALL, ("vnode_pager_deallocate: %x\n", mem_obj));

	vnode_object = vnode_pager_lookup(mem_obj);

	if (hw_atomic_sub(&vnode_object->ref_count, 1) == 0) {
		if (vnode_object->vnode_handle != NULL) {
			vnode_pager_vrele(vnode_object->vnode_handle);
		}
		zfree(vnode_pager_zone, vnode_object);
	}
	return;
#endif
}


/****** Memory Object Stuff *******/

kern_return_t
memory_object_create_named( memory_object_t pager,
			    memory_object_offset_t size,
			    memory_object_control_t *control )
{
	memory_object_control_t mc;

	mc = malloc( sizeof( *mc ) );
	if( mc == NULL )
		return KERN_FAILURE;

	mc->object = (void*) pager;

	*control = mc;

	return KERN_SUCCESS;
}


int
memory_object_control_uiomove(
	memory_object_control_t	control,
	memory_object_offset_t	offset,
	void		*	uio,
	int			start_offset,
	int			io_requested,
	int			mark_dirty)
{

	printf( "XXX: skipping memory_object_control_uiomove\n" );

	return 0;
}

#endif

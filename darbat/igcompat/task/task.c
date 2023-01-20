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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/debug.h>
#include <vm/vm_kern.h>
// #include <kern/zalloc.h>

#include <DEBUG.h>
#include <igcompat/compat.h> /* bzero */

/* stuff from mach */
#include <vm/pmap.h>
#include <vm/vm_map.h>

/* and some missing bits */
//extern pmap_t		pmap_create(vm_map_size_t size); /* Create a pmap_t. */
//extern vm_map_t		vm_map_fork(vm_map_t old_map);

#if 0
struct task
{
	int ref_count;   /* reference count */
	void *bsd_info;  /* BSD info for 'mach' thread */

	vm_map_t map;    /* VM map */

	thread_t thread;  /* XXX: The currently only thread in the task */
};
#endif

// Currently defined in an Mach header
// typedef struct task * task_t;


/* BSD imports this guy */
task_t kernel_task = &(struct task) { 1, NULL, NULL, NULL , NULL};

/* called on startup */
void _ktask_init( void );
void
_ktask_init( void )
{
	kernel_task->map = kernel_map;
}

void 
set_bsdtask_info(task_t t,void * v)
{
	t->bsd_info=v;
}


void  *
get_bsdtask_info(task_t t)
{
	return(t->bsd_info);
}


task_t 
current_task(void)
{
    return get_threadtask( current_thread() );
}

int
get_task_numacts( task_t t )
{
	/* FIXME: switch on thread == NULL? */
	return 1;
}

pmap_t
get_task_pmap( task_t t )
{
	return vm_map_get_pmap( t->map );
}

vm_map_t
get_task_map( task_t t )
{
	return t->map;
}

kern_return_t
task_create_internal(
	task_t		parent_task,
	boolean_t	inherit_memory,
	task_t		*child_task)		/* OUT */
{
	task_t		new_task;
	// processor_set_t	pset;

	DBG();

	// new_task = (task_t) zalloc(task_zone);
	new_task = malloc( sizeof( *new_task ) );

	if (new_task == TASK_NULL)
		return(KERN_RESOURCE_SHORTAGE);

	bzero( new_task, sizeof( *new_task ) );

	/* one ref for just being alive; one for our caller */
	new_task->ref_count = 2;

	/* XXX */
	new_task->thread = NULL;

	/* create an AS for it */
	if (inherit_memory)
	{
		DBG();
		new_task->map = vm_map_fork(parent_task->map);
	}
	else
	{
		DBG();
		new_task->map = vm_map_create(pmap_create(0),
					(vm_map_offset_t)(VM_MIN_ADDRESS),
					(vm_map_offset_t)(VM_MAX_ADDRESS), 
					      TRUE);
	}

    // Set the EAS
    new_task->eas = NULL;

	/* FIXME: actually do something useful here */

	/* write out the result */
	*child_task = new_task;

	return KERN_SUCCESS;
}

void
task_set_64bit(	task_t task,
		boolean_t is64bit )
{
	printf( "XXX: ignoring setting task to 64bit: %d\n", is64bit );
}

kern_return_t
task_halt( task_t task )
{
	printf( "XXX: skipping task halt on %p\n", task );

	return KERN_SUCCESS;
}

vm_map_t
swap_task_map( task_t task, vm_map_t map )
{
	vm_map_t old_map;

	old_map = task->map;
	task->map = map;

	return old_map;
}


/* XXX */ 
void _task_set_thread( task_t task, thread_t thread );

void
_task_set_thread( task_t task, thread_t thread )
{
	assert( task->thread == NULL );
	task->thread = thread;
}


/* XXX */
extern vm_map_t _task_get_map( task_t task );

vm_map_t
_task_get_map( task_t task )
{
	return task->map;
}


struct tws_hash *
task_dynamic_working_set(task_t task)
{
	return NULL;
}

integer_t 
task_pageins_inc(task_t task)
{
	return 0;
}

integer_t 
task_pageins_dec(task_t task)
{
	return 0;
}

integer_t 
task_cow_faults_inc(task_t task)
{
	return 0;
}

integer_t 
task_faults_inc(task_t task)
{
	return 0;
}

int
task_priv_flags(task_t task)
{
	return 0;
}

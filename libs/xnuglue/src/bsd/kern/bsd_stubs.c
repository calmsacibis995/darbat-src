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
/*
 * bsd_stubs.c
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include <mach/vm_types.h>
#include <machine/param.h>

#include <iguana/memsection.h>

#include <sys/systm.h>
#include <sys/errno.h>
#include <sys/conf.h>

extern int nmbclusters;
static int alloced;
static unsigned int _offset;
static uintptr_t		_base;

struct bdevsw nobdev = NO_BDEVICE;
struct cdevsw nocdev = NO_CDEVICE;

/*
 * XXX a really dodgy implementation of kmem_mb_alloc
 *
 */
/*
 * 4MB: more than enough??
 */
#define MB_BUFSIZ (4 * 1024 * 1024)
vm_offset_t kmem_mb_alloc(/*vm_map_t*/ void *mbmap, int size);
extern void *mbutl;
extern void *embutl;

vm_offset_t
kmem_mb_alloc(/*vm_map_t*/ void *mbmap, int size)
{
	memsection_ref_t	ref;
	uintptr_t		base;

	if (!alloced) {
		/*
		 * created using _direct since it's dma-able memory
	 	 *
		 */
		ref = memsection_create_direct(MB_BUFSIZ, &_base);
		assert(_base);
		mbutl = (void *)_base;
		embutl = (void*)((unsigned char *)mbutl + MB_BUFSIZ);

		printf("kmem_mb_alloc: init _base %p mbutl %p "
		    "embutl %p\n", (void *)_base, mbutl, embutl);

		alloced = 1;
	}

	printf( "kmem_mb_alloc\n" );

	base = _base + _offset/*lastoffset*/;

	if ((char *)(base + size) > (char *)embutl)
		assert(!"kmem_mb_alloc out of memory");

	/* hack debug paranoia */
	assert(size % 4096 == 0);

	_offset += size;

	return (vm_offset_t)base;
}

/*
 * XXX
 *
 * Fix these.  They are not quite right.
 *
 */
int
bdevsw_add(int index, struct bdevsw *bsw)
{

	bdevsw[index] = *bsw;
	return index;
}

int
bdevsw_remove(int index, struct bdevsw *bsw)
{

	bdevsw[index] = nobdev;

	return index;
}

int
cdevsw_add(int index, struct cdevsw *csw)
{

	/*
	 * For now only the serial uses this.
	 *
 	 * We need to fix this asap.
	 */
	if (index == -1)
		index = 0x9;

	cdevsw[index] = *csw;

	return (index);
}

int
cdevsw_remove(int index, struct cdevsw *csw)
{

	cdevsw[index] = nocdev;

	return (index);
}


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
 * iokit_rpc.c
 *
 */

#include <stdio.h>
#include <string.h>

#include <xnu_glue.h>	/* XXX DEPRECATED */
#include <mach/clock_types.h>

#include <iguana/hardware.h>
#include <iguana/memsection.h>

#include <IOKit/IOTypes.h>

#include <kern/locks.h>
#include <vm/pmap.h>

/*
 * These are in IOKit, but we probably do not want to pull
 * in headers there.
 */
extern void IOLog(const char *, ...);
kern_return_t IOMapPages(vm_map_t, vm_offset_t, vm_offset_t, vm_size_t,
	unsigned int);
unsigned int IODefaultCacheBits(addr64_t pa);

#include <l4/kdebug.h>

/*
 * XXX 64bit
 */
struct _blah {
	void	*x;
	void	*y;
};

void IOGetTime(mach_timespec_t	*);

void
IOGetTime(mach_timespec_t	*clock_time)
{
	struct _blah	*a;

	printf("%s: warning: called, faking preposterous time\n", 
	    __FUNCTION__);

	a->x = (void *)0xdeadbeef;
	a->y = (void *)0xfee1dead;

	memcpy(clock_time, a, sizeof(struct _blah));

	return;
}

kern_return_t
IOMapPages(vm_map_t map, vm_offset_t va, vm_offset_t pa,
	vm_size_t length, unsigned int options)
{
	vm_size_t	off;
	vm_prot_t	prot;
	unsigned int	flags;
	memsection_ref_t	ref;
	thread_ref_t	unused;
	pmap_t		pmap;
	int		rc;

	prot = (options & kIOMapReadOnly)
		? VM_PROT_READ : (VM_PROT_READ|VM_PROT_WRITE);

	switch (options & kIOMapCacheMask) {

		case kIOMapDefaultCache:
		default:
			flags = IODefaultCacheBits(pa);
			break;
		case kIOMapInhibitCache:
			flags = VM_WIMG_IO;
			break;
		case kIOMapWriteThruCache:
			flags = VM_WIMG_WTHRU;
			break;
		case kIOWriteCombineCache:
			flags = VM_WIMG_WCOMB;
			break;
		case kIOMapCopybackCache:
			flags = VM_WIMG_COPYBACK;
			break;
	}

	/*
	 * If we are on a architecture that actually
	 * cares about these mappings instead of the x86
	 * which does it all for us, then we need to
	 * actually do the proper MemoryControl() syscall 
	 * here.
	 *
	 * XXX FIXME XXX
	 */

	for (off = 0; off < length; off += page_size)
		pmap_enter(pmap, va + off, (pa + off) >> 12/*XXX*/,
		    prot, flags, TRUE);

	/*
	 * Grab a copy of the memesection so that we can back it
	 *
	 */
	ref = memsection_lookup(va, &unused);
	assert(ref);

	/*
	 * XXX 
	 *
	 * You can set the attributes, what is the interface to get the 
	 * attributes so they can be bitwise OR'ed?
	 */
	/*
	 * Hardware_back_memsection() only works when MEM_USER is on.
	 *
	 */
	rc = hardware_back_memsection(ref, pa, MEM_NORMAL);
	assert(rc == 0);

	return KERN_SUCCESS;
}

/*
 * XXX
 *
 * FIXME 
 */
unsigned int
IODefaultCacheBits(addr64_t pa)
{
	unsigned int flags;

	flags = VM_WIMG_IO;

	return flags;
}


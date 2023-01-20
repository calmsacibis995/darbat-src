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
#include <stdlib.h>
//#include <stdio.h>
#include <assert.h>

/* mach includes */
#include <mach/vm_param.h>
#include <vm/pmap.h>

#include <igcompat/darbat.h>
#include <l4/kdebug.h>


/* XXX: the start and end of the paged region */
void *kvm_start = NULL;
void *kvm_end = NULL;


void db_virt_bootstrap(void);

void
db_virt_bootstrap(void)
{
	void *kobj;

	kobj = darbat_mapped_rgn_alloc( VM_KERNEL_SIZE );
	if( kobj == NULL )
		panic( "unable to alloc kobj region" );
	
	kvm_start = kobj;
	kvm_end = ((char*)kobj) + VM_KERNEL_SIZE;

	printf( ">>>> kvm is %p - %p\n", 
		kvm_start, kvm_end );

	/* XXX: this is not a constant! */
 	VM_MIN_KERNEL_ADDRESS = (unsigned int) kobj;
}



void 
pmap_virtual_space( vm_offset_t *startp,
		    vm_offset_t *endp )
{
	*startp = (vm_offset_t) kvm_start;
	*endp   = (vm_offset_t) kvm_end;
}


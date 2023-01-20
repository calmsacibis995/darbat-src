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
 *	Copyright (C) 2005,  National ICT Australia
 *
 *	File:	kern/elf_loader.c
 *	Author:	Charles Gray
 *
 *	ELF file loader
 *
 *      This is lots of clag from mach_loader.c
 *
 */

#include <assert.h>

#include <sys/param.h>
#include <sys/vnode_internal.h>
#include <sys/uio.h>
#include <sys/namei.h>
#include <sys/proc_internal.h>
#include <sys/kauth.h>
#include <sys/stat.h>
#include <sys/malloc.h>
#include <sys/mount_internal.h>
#include <sys/fcntl.h>
#include <sys/ubc_internal.h>
#include <sys/imgact.h>

#include <mach/mach_types.h>
#include <mach/vm_map.h>	/* vm_allocate() */
#include <mach/mach_vm.h>	/* mach_vm_allocate() */
#include <mach/vm_statistics.h>
#include <mach/shared_memory_server.h>
#include <mach/task.h>
#include <mach/thread_act.h>
#include <mach/pmap.h>  /* pmap_reference */

#include <machine/vmparam.h>

#include <kern/kern_types.h>
#include <kern/cpu_number.h>
#include <kern/elf_loader.h>
#include <kern/kalloc.h>
#include <kern/task.h>
#include <kern/thread.h>

#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_pager.h>
#include <vm/vnode_pager.h>
#include <vm/vm_shared_memory_server.h>
#include <vm/vm_protos.h> 

// #include <stdbool.h>
// #include <stdint.h>
#include <elf/elf32.h>


/* XXXXXXXX */
#include <l4/kdebug.h>

/* XXX: see the mach_loader */
extern pmap_t	pmap_create(vm_map_size_t size);

static int
load_segment( struct Elf32_Phdr *ph, void * pager, vm_map_t map )
{
	kern_return_t		ret;
	vm_offset_t		map_addr, map_offset;
	vm_size_t		map_size, seg_size, delta_size;
	vm_prot_t 		initprot;
	vm_prot_t		maxprot;
	int diff;

	/* check the memory size */
	seg_size = round_page( ph->p_memsz );
	if (seg_size == 0)
		return(KERN_SUCCESS);

	/*
	 *	Round sizes to page size.
	 */
	map_addr = trunc_page(ph->p_vaddr);

	/* XXX: some dodgey diff magic */
	/* XXX: I hope this doesn't break the map_size! - CEG */
	diff = ph->p_vaddr - map_addr;
    printf("!!!diff is %x\n", diff);

	map_size = round_page(ph->p_filesz + diff);
	map_offset = ph->p_offset - diff;

	printf( "map_size 0x%x, map_addr 0x%x, map_offset 0x%x, diff 0x%x\n",
		(int) map_size, (int) map_addr, (int) map_offset, (int) diff );

	if (map_size > 0) 
	{
		initprot = VM_PROT_ALL;
		maxprot =  VM_PROT_ALL;

		printf( "doing a vm_map in %p, from %lx -> %lx\n",
			map, 
			(unsigned long) map_addr, (unsigned long) map_size );
		/*
		 *	Map a copy of the file into the address space.
		 */
		ret = vm_map( map,
			      &map_addr, map_size, (vm_offset_t)0,
			      VM_FLAGS_FIXED,	pager, map_offset, TRUE,
			      initprot, maxprot,
			      VM_INHERIT_DEFAULT);
		if (ret != KERN_SUCCESS)
			return(LOAD_NOSPACE);
	
		/*
		 *	If the file didn't end on a page boundary,
		 *	we need to zero the leftover.
		 */

		/** XXX: This was unimplemented ***/
		delta_size = map_size - ph->p_filesz - diff;
		if( delta_size > 0 )
		{
            printf("!!!delta < 0\n");
			vm_offset_t	tmp;
	
			ret = vm_allocate( kernel_map, &tmp, 
					   delta_size, VM_FLAGS_ANYWHERE );
			if (ret != KERN_SUCCESS)
				return(LOAD_RESOURCE);
	
			printf( "Doing copyout of delta...\n" );
			printf( "dest addr: 0x%x\n", 
				map_addr + ph->p_filesz + diff );
			printf( "copy size: 0x%x\n", delta_size );


			if( copyout( (void*)tmp, 
				     map_addr + ph->p_filesz + diff,
				     delta_size) )
			{
				(void) vm_deallocate(
						kernel_map, tmp, delta_size);
				return(LOAD_FAILURE);
			}

			// panic("inspect");
			(void) vm_deallocate(kernel_map, tmp, delta_size);
		}
	}

	/*
	 *	If the virtual size of the segment is greater
	 *	than the size from the file, we need to allocate
	 *	zero fill memory for the rest.
	 */
	delta_size = seg_size - map_size;
	if (delta_size > 0) 
	{
		vm_offset_t	tmp = map_addr + map_size;

		printf( "Doing copyout of more different delta...\n" );

		ret = vm_allocate(map, &tmp, delta_size, VM_FLAGS_FIXED);
		if (ret != KERN_SUCCESS)
			return(LOAD_NOSPACE);
	}

	return(LOAD_SUCCESS);
}

static int
load_segments( void *vaddr, int numsegs, void * pager, vm_map_t map )
{
	kern_return_t		ret;
	struct Elf32_Phdr *ph;
	int i;

	ph = vaddr;

	for( i = 0; i < numsegs; i++ )
	{
		printf( "checking program header %d\n", i );

		if( ph[i].p_type == 1 )
		{
			printf( "  p_type %d\n", ph[i].p_type );
			printf( "  p_offset 0x%x\n", ph[i].p_offset );
			printf( "  p_vaddr  0x%x\n", ph[i].p_vaddr );
			printf( "  p_memsz  0x%x\n", ph[i].p_memsz );
			printf( "  p_filesz 0x%x\n", ph[i].p_filesz );

			ret = load_segment( &ph[i], pager, map );
			if( ret != LOAD_SUCCESS )
				printf( "Failed load, %d\n", ret );
			assert( ret == LOAD_SUCCESS );
		}
		else
			printf( "  not loadable, skipping\n" );

	}

	return 0;
}


load_return_t
load_elffile(
	struct image_params	*imgp,
	struct elf_header	*header,
	thread_t 		thr_act,
	vm_map_t 		new_map,
	boolean_t		clean_regions,
	load_result_t		*result
)
{
	struct Elf32_Header* eh;
	void * pager;
	vm_size_t size, kl_size;
	caddr_t addr;
	void * kl_addr;
	off_t offset;
	struct proc *p = current_proc(); /* XXXX */
	int resid = 0;
	int r;
	struct vnode *vp;
	int error;
	boolean_t create_map = TRUE;
	vm_map_t		old_map;
	pmap_t			pmap = NULL;	/* protected by create_map */
	vm_map_t		map;

    printf("Current task is %p, current thread is %p\n", current_task(), current_map());

	/* setup the map for the new process */

	if (new_map != VM_MAP_NULL) {
		create_map = FALSE;
        printf(">>> Not creating a map\n");
	}

	if (create_map) {
        printf(">>> I AM creating a map\n");
		old_map = current_map();
// #ifdef i386
#if !DARBAT
		pmap = get_task_pmap(current_task());
		assert(pmap != NULL);
		pmap_reference(pmap);
#else
		pmap = pmap_create((vm_map_size_t) 0);
#endif
		map = vm_map_create(pmap,
				get_map_min(old_map),
				get_map_max(old_map),
				TRUE); /**** FIXME ****/
	} else
	{
		panic("using exsting map for elf?");

		map = new_map;
	}

	/* XXX: we do this early because of a copyout above... */
	/* FIXME: why? CEG */
	/* now switch the map to the new one */
	if (create_map) 
	{
		task_halt(current_task());
		
		old_map = swap_task_map(current_task(), map);

        printf(">>> Old map is %p, new map is %p\n", old_map, map);
//#ifndef i386
//		pmap_switch(pmap);	/* Make sure we are using the new pmap */
//#endif
		vm_map_deallocate(old_map);
	}


	/* parse the ELF header */
	eh = (void*) header;

	printf( "e_ident: %s\n", eh->e_ident );
	printf( "e_version: %d\n", eh->e_version );
	printf( "e_entry: %x\n", eh->e_entry );
	printf( "e_phnum: %d\n", eh->e_phnum );


	vp = imgp->ip_vp;
	printf( "vnode is %p\n", vp );

	/* map the segment info */
	UBCINFOCHECK("parse_elffile", vp);
	pager = (void *) ubc_getpager(vp);

	/* work out how big it should be */
	size = eh->e_phnum * eh->e_phentsize;

	/* we want to map it... */
	size = round_page( size );
	offset = eh->e_phoff;

	printf( "mapping %d bytes for program headers\n", size );

	/* do the map */
	addr = 0;
	kl_size = size;
	kl_addr = kalloc(size);
	addr = (caddr_t)kl_addr;
	if (addr == NULL)
		return(LOAD_NOSPACE);

	error = vn_rdwr( UIO_READ, vp, addr, size, offset,
			 UIO_SYSSPACE32, 0, kauth_cred_get(), &resid, p );
	if (error) {
		if (kl_addr )
			kfree(kl_addr, kl_size);
		return(LOAD_IOERROR);
	}

	/* fill out entry point and make up a stack address */
	result->entry_point = eh->e_entry;
	result->user_stack = 32 * 1024 * 1024;

	/*** XXX: I think we have a seedy ordering problem due to flushing
	     and not doing proper referencing?  ***/

	r = load_segments( kl_addr, eh->e_phnum, pager, map );
	assert( r == 0 );


	
	return 0;
}

/*
 * vm_kern.c
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

#include <vm/vm_kern.h>
#include <stdio.h>	/* printf */

extern vm_offset_t physalloc(int s);	// XXX: IOLib.c 

kern_return_t
kernel_memory_allocate(
                                vm_map_t        map,
                                vm_offset_t     *addrp,
                                vm_size_t       size,
                                vm_offset_t     mask,
                                int             flags)
{
	printf("%s: called %p %d %d %d\n", __func__, map, (int)size, 
	    (int)mask, (int)flags);

	memsection_create(size, addrp);
	printf("%s: got addr %p\n", __func__, (void *)*addrp);
	return KERN_SUCCESS;	
}

kern_return_t    kmem_alloc_pageable(
                                vm_map_t        map, 
                                vm_offset_t     *addrp,
                                vm_size_t       size)
{
	printf("%s: called %p %d\n", __func__, map, (int)size);
	    
	*addrp = physalloc(size);
	return (KERN_SUCCESS);
}

kern_return_t
kmem_alloc(
        vm_map_t        map,
        vm_offset_t     *addrp,
        vm_size_t       size)
{
        return kernel_memory_allocate(map, addrp, size, 0, 0);
}



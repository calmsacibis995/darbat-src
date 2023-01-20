/*
 * vm_kern.h
 *
 */
#ifndef _VM_KERN_H
#define _VM_KERN_H

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>

#ifdef KERNEL_PRIVATE

extern kern_return_t	kernel_memory_allocate(
				vm_map_t	map,
				vm_offset_t	*addrp,
				vm_size_t	siz,
				vm_offset_t	mask,
				int		flags);

kern_return_t    kmem_alloc_pageable(
                                vm_map_t        map,
                                vm_offset_t     *addrp,
                                vm_size_t       size);
#endif	/*KERNEL_PRIVATE*/

#endif	/* _VM_KERN_H */

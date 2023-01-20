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
#include <string.h>
#include <assert.h>

#include <mach/mach_types.h>
#include <mach/machine.h>

#include <sys/kernel.h>
#include <sys/sysctl.h>

uint64_t max_mem = 512*1024*1024;
vm_size_t mem_size = 512*1024*1024;
unsigned long long vm_page_mask = 4095;
int default_pager_object = 0;

/*
 * XXX -gl : this isn't right.  Not even the prototype is right!
 */
void ipc_notify_no_senders(/*some args here */void);

void
ipc_notify_no_senders(void)
{

}

/*
 * dev/random/
 */
void read_random(void *buffer, unsigned int nbytes);

void
read_random(void *buffer, unsigned int nbytes)
{

	(void)buffer;
	(void)nbytes;
}

#if 0  /* now in machvm */
/* this isn't really functionally required... */
extern kern_return_t adjust_vm_object_cache(vm_size_t oval, vm_size_t nval);
kern_return_t 
adjust_vm_object_cache(vm_size_t oval, vm_size_t nval)
{
	printf( ">>>> adjust_vm_object_cache\n" );

	return KERN_SUCCESS;
     
}
#endif

/* Do nothing for now */
/*
struct sysctl_oid *machdep_sysctl_list[] =
{
    (struct sysctl_oid *) 0
};
*/

/*
 * libkern, which calls RandomULong which is in dev/random
 */
unsigned long random(void);
unsigned long
random(void)
{
	return 9999;	/* yeh, that's random */
}

unsigned long long timer_grab(void *x);

unsigned long long timer_grab(void *x)
{
	// printf("XXX: dodging timer_grab!!!  FIXME PLEASE\n");
	return 0;
}

/* i386 for now */
cpu_type_t
cpu_type(void)
{
	return CPU_TYPE_I386;
}

cpu_subtype_t
cpu_subtype(void)
{
	return CPU_SUBTYPE_PENTPRO;
}

cpu_threadtype_t
cpu_threadtype(void)
{
	/* no hyper-threading... yet */
	return CPU_THREADTYPE_NONE;
}

/* 
 * copy a null terminated string from one point to another in 
 * the kernel address space.
 *   - no access checks are performed.
 *   - if the end of string isn't found before
 *     maxlen bytes are copied,  return ENAMETOOLONG,
 *     indicating an incomplete copy.
 *   - otherwise, return 0, indicating success.
 * the number of bytes copied is always returned in lencopied.
 */
/* from ppc/fault_copy.c -Titan1T4 VERSION  */
int copystr(const void *, void *, size_t, size_t *);

int
copystr(const void *vfrom, void *vto, size_t maxlen, size_t *lencopied)
{
    register unsigned l;
	caddr_t from, to;

	/* FIXME: discards const! */
	from = (caddr_t) vfrom;
	to = vto;
    for (l = 0; l < maxlen; l++)
        if ((*to++ = *from++) == '\0') {
            if (lencopied)
                *lencopied = l + 1;
            return 0;
        }
    if (lencopied)
	*lencopied = maxlen;
    return ENAMETOOLONG;
}

void kprintf(const char *);

void
kprintf(const char *crap)
{
    
}

int thread_policy(void);
int
thread_policy(void)
{
    return 0;
}

// TGB HACK - we will need to fix this in order to do paging
void pmap_clear_reference(int foo);
void
pmap_clear_reference(int foo)
{
    return;
}

kern_return_t task_importance(task_t task, integer_t importance);
kern_return_t
task_importance(task_t task, integer_t importance)
{
    return KERN_SUCCESS;
}

// See where this is used, it's to get rid of a really retarded gcc error 
// bsd/nfs/nfs_vnops.c:1340: warning: null argument where non-null required (argument 1)
void *tgb_hates_gcc(void * arg);
void *tgb_hates_gcc(void * arg)
{
    return arg;
}

boolean_t PEGetMachineName( char * name, int maxLength );
boolean_t PEGetMachineName( char * name, int maxLength )
{
    strncpy(name, "Darwin/L4", maxLength);
    return 1;
}

boolean_t PEGetModelName( char * name, int maxLength );
boolean_t PEGetModelName( char * name, int maxLength )
{
    strncpy(name, "Darbat", maxLength);
    return 1;
}

struct vm_map_copy {
	int			type;
#define VM_MAP_COPY_ENTRY_LIST		1
#define VM_MAP_COPY_OBJECT		2
#define VM_MAP_COPY_KERNEL_BUFFER	3
	vm_object_offset_t	offset;
	vm_map_size_t		size;
	union {
	    int hdr;	/* ENTRY_LIST */
	    vm_object_t			object; /* OBJECT */
	    struct {				
		void			*kdata;	      /* KERNEL_BUFFER */
		vm_size_t		kalloc_size;  /* size of this copy_t */
	    } c_k;
	} c_u;
};
void print_vm_map_copy(struct vm_map_copy *tmp);
void
print_vm_map_copy(struct vm_map_copy *tmp)
{
    printf("tmp->type is %d\n", tmp->type);
    switch(tmp->type)
    {
        case 1:
        case 2:
            break;
        case 3:
            printf("kdata is %p, kalloc_size is %d\n", 
                    tmp->c_u.c_k.kdata, tmp->c_u.c_k.kalloc_size);
            break;
    }
}

int sectSizePRELINK = 0;
void *sectPRELINKB = NULL;

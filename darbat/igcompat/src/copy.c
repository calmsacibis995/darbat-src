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
#include <DEBUG.h>
#include <assert.h>

#include <sys/errno.h>

#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_fault.h>
#include <vm/vm_kern.h>
#include <kern/kern_types.h>

#include <libkern/libkern.h>
#include <igcompat/compat.h>

#include <kern/task.h>
#include <kern/thread.h>

int tgb_copyoutdbg = 0;

void tgb_time(char *, int);
//#define tgb_time_dbg() DBG(); tgb_time()
#define tgb_time_dbg() //tgb_time(__FILE__,__LINE__)

extern void *kvm_start;
extern void *kvm_end;

extern void panic(const char *);

/* XXXX */
ppnum_t pmap_find_phys( pmap_t pmap, addr64_t va );

void* xlat_uaddr( pmap_t pmap, const user_addr_t uaddr );
void*
xlat_uaddr( pmap_t pmap, const user_addr_t uaddr )
{
	unsigned int pgaddr, offset, xaddr;
	user_addr_t uaddr2;

//    printf("xlat_uaddr, uaddr is %x\n", uaddr);


	/* mask the low bits */
	pgaddr = trunc_page(uaddr);
	offset = uaddr - pgaddr;
    tgb_time_dbg();
    /*
	offset = uaddr & 0xFFFUL;
	pgaddr = uaddr & (~0xFFFUL);
    */

	/* do the translate */
	xaddr = pmap_find_phys( pmap, pgaddr );

    tgb_time_dbg();
	if( xaddr == 0 )
	{
		kern_return_t rc;
		vm_map_t map = current_map();

		uaddr2 = trunc_page((vm_offset_t)uaddr);
    tgb_time_dbg();

		/* if we miss, fake a fault */
		rc = vm_fault( map, uaddr2, VM_PROT_NONE, FALSE, 
			       (pmap == kernel_pmap) ? 
			       THREAD_UNINT : THREAD_ABORTSAFE, 
			       NULL, 0 );
		
    tgb_time_dbg();
		if( rc != KERN_SUCCESS )
			printf( "rc %d\n", rc );
		assert( rc == KERN_SUCCESS );

		/* lookup again! */
		xaddr = pmap_find_phys( pmap, pgaddr );
    tgb_time_dbg();

		assert( xaddr != 0 );
	}

    tgb_time_dbg();
	xaddr <<= 12;

	xaddr |= offset;

    tgb_time_dbg();
	return (void*) xaddr;
}

void back_kaddr( void *kaddr );

void
back_kaddr( void *kaddr )
{
	unsigned int xaddr, pgaddr;
	kern_return_t rc;

	/* check if this is in our virtual object */
	if( kaddr < kvm_start )
		return;

	if( kaddr >= kvm_end )
		return;

	/* do the lookup */
    pgaddr = trunc_page(kaddr);
	xaddr = pmap_find_phys( kernel_pmap, (addr64_t)pgaddr );
		
	if( xaddr != 0 )
		return;

	// printf( "faking KERNEL vm_fault at %p\n", kaddr );

	/* if we miss, fake a fault */
	rc = vm_fault( kernel_map, (unsigned int)pgaddr, 
		       VM_PROT_NONE, FALSE, 
		       THREAD_UNINT, NULL, 0 );
	
	assert( rc == KERN_SUCCESS );
}


int 
copyinstr(const user_addr_t uaddr, void *kaddr, size_t len, size_t *done)
{
	pmap_t map;

    char *dest = (char *)kaddr;

	map = vm_map_get_pmap( current_map() );

    char *resolved = xlat_uaddr(map, uaddr);
    if(resolved == NULL)
        return EFAULT;
    size_t copied;
    back_kaddr(dest);

    for(copied = 0;copied < len; copied++)
    {
        if(((int)(&resolved[copied])) % 4096 == 0)
        {
            resolved = xlat_uaddr(map, uaddr + copied);
            if(resolved == NULL)
                return EFAULT;
        }

        if(((int)(&dest[copied])) % 4096 == 0)
        {
            back_kaddr(&dest[copied]);
        }

        dest[copied] = resolved[copied];

        if(dest[copied] == '\0')
        {
            *done = copied+1;
            return 0;
        }

    }

	return ENAMETOOLONG;
}


int
copyoutstr(const void *from, user_addr_t to, size_t maxlen, size_t *lencopied)
{
	size_t	slen;
	size_t	len;
	int	error = 0;

	slen = strlen(from) + 1;
    //printf("string is xx0'%s'0xx\n", (char *)from);
    //printf("slen is %d, maxlen is %d\n", slen, maxlen);
	if (slen > maxlen)
    {
        DBG();
		error = ENAMETOOLONG;
    }
    

	len = min(maxlen,slen);
	if (copyout(from, to, len))
    {
        DBG();
		error = EFAULT;
    }
	*lencopied = len;

	return error;
}

#define MIN(a,b) ((a)>(b)?(b):(a))
                               
int copyinfrom(vm_map_t map, const user_addr_t orig_uaddr, void *orig_kaddr, size_t len);

int
copyin(const user_addr_t orig_uaddr, void *orig_kaddr, size_t len)
{
    return copyinfrom(current_map(), orig_uaddr, orig_kaddr, len);
}



int
copyinfrom(vm_map_t map, const user_addr_t orig_uaddr, void *orig_kaddr, size_t len)
{
    size_t k_remaining, u_remaining, to_copy;
    pmap_t pmap = vm_map_get_pmap(map);
    char *u_phys = 0;
    char *k_phys = 0; 
    char *u_addr = (char *)orig_uaddr;
    char *k_addr = orig_kaddr;

    tgb_time_dbg();

    while(len)
    {
    tgb_time_dbg();
        if((uint32_t)u_phys % 4096 == 0)
        {
    tgb_time_dbg();
            u_phys = xlat_uaddr(pmap, (uint32_t)u_addr);
    tgb_time_dbg();
            if(u_phys == NULL)
            {
                return EFAULT;
            }
        }

        if((uint32_t)k_phys % 4096 == 0)
        {
    tgb_time_dbg();
            k_phys = (char *)k_addr;
            back_kaddr(k_phys);
    tgb_time_dbg();
        }

        k_remaining = trunc_page(((uint32_t)k_phys) + 4096) - (uint32_t)k_phys;
        u_remaining = trunc_page((uint32_t)u_phys + 4096) - (uint32_t)u_phys;

        to_copy = MIN(MIN(k_remaining, u_remaining), len);
        bcopy(u_phys, k_phys, to_copy);
        len -= to_copy;
        u_phys += to_copy;
        u_addr += to_copy;
        k_phys += to_copy;
        k_addr += to_copy;
    tgb_time_dbg();
    }

    return 0;
}

int
copyout(const void *orig_kaddr, user_addr_t orig_uaddr, size_t len)
{
    size_t k_remaining, u_remaining, to_copy;
    pmap_t pmap = vm_map_get_pmap(current_map());
    char *u_phys = 0;
    char *k_phys = 0; 
    char *u_addr = (char *)orig_uaddr;
    char *k_addr;
    *((const char **)&k_addr) = orig_kaddr;

    while(len)
    {
        if((uint32_t)u_phys % 4096 == 0)
        {
            u_phys = xlat_uaddr(pmap, (uint32_t)u_addr);
            if(u_phys == NULL)
            {
                return EFAULT;
            }
        }

        if((uint32_t)k_phys % 4096 == 0)
        {
            k_phys = (char *)k_addr;
            back_kaddr(k_phys);
        }

        k_remaining = trunc_page(((uint32_t)k_phys) + 4096) - (uint32_t)k_phys;
        u_remaining = trunc_page((uint32_t)u_phys + 4096) - (uint32_t)u_phys;

        to_copy = MIN(MIN(k_remaining, u_remaining), len);
        bcopy(k_phys, u_phys, to_copy);
        len -= to_copy;
        u_phys += to_copy;
        u_addr += to_copy;
        k_phys += to_copy;
        k_addr += to_copy;
    }

    return 0;
}

/* Seriously, what is with this function?! -CEG */
int copywithin(void *src, void *dst, size_t count);
int
copywithin(void *src, void *dst, size_t count)
{
	bcopy(src,dst,count);
	return 0;
}

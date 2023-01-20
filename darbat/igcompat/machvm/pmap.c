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
/* darbat pmap file */

#include <stdlib.h>
#include <string.h>

#include <vm/pmap.h>
#include <igcompat/darbat.h>
#include <igcompat/compat.h>

#include <l4/kdebug.h>

#include "tlpt.h"
#include "ptov.h"

#include <kern/task.h>
#include <kern/thread.h>

#include <DEBUG.h>

#define dprintf(args...)

extern unsigned int pages_left;
extern void * phys_next;

struct pmap
{
    /* FIXME: put something in here :) */

    /* the actual PT */
    tlpt_t pt;
};


pmap_t kernel_pmap = NULL;

void kpmap_init(void);

static vm_offset_t commpage_base = 0;
static int commpage_count = 0;

/* before kpmap_init() */
void
pmap_bootstrap(void)
{
	int r;

	printf( ">>> pmap_bootstrap\n" );

	/* startup the PtoV module */
	r = ptov_init();
	if( r != KERN_SUCCESS )
		panic( "failed to ptov_init :(" );
}

void 
kpmap_init(void)
{
    printf( ">>> Creating kernel pmap\n" );
    /* XXX: make sure we can always call this here! */
    kernel_pmap = pmap_create( 0 );
}


/* a 2nd chance to init after VM is up */
void
pmap_init(void)
{
	printf( ">>> pmap_init\n" );
}

/*
 *	Create and return a physical map.
 *
 *	If the size specified for the map
 *	is zero, the map is an actual physical
 *	map, and may be referenced by the
 *	hardware.
 *
 *	If the size specified is non-zero,
 *	the map will be used in software only, and
 *	is bounded by that size.
 */
pmap_t 
pmap_create( vm_map_size_t size )
{
    pmap_t pm;

    pm = malloc( sizeof( *pm ) );
    if( pm == NULL )
        panic( "out of memory creating pmap" );

    /* init the pagetable */

    dprintf( "*** Created pmap at %p\n", pm );
    pm->pt = tlpt_create();
    if( pm->pt == NULL )
        panic("out of memory creating tlpt");

    return pm;
}


void
pmap_remove(
        pmap_t		map,
        addr64_t	s64,
        addr64_t	e64)
{
    dprintf( "pmap_remove: pm %p, s64 %llx, e64 %llx\n", map, s64, e64 );

    if (map == PMAP_NULL) {
        return;
    }

    s64 = trunc_page(s64);

    /* flush a region? */
    while( s64 < e64 )
    {
        void *addr;
        int r, dummy;

        addr = (void*) (unsigned long) s64;

        ppnum_t pn;
        vm_prot_t prot;

        r = tlpt_lookup( map->pt, addr, &pn, &prot, &dummy, &dummy);

        /* if it's mapped... */
        if( r == 0 )
        {
            /* unmap it from user address spaces */
            darbat_unmap_page((void *)(pn<<12));

            /* unmap it from kernel if we need to */
            if( map == kernel_pmap )
            {
                darbat_flush_page( addr );
            }

            /* take out the ptov mapping */
            r = ptov_del( map, (vm_offset_t) addr, pn );

            if( r != 0 )
            {
                panic( "Mismatched ptov in pmap_remove\n" );
            }

            /*  remove tlpt entry */
            r = tlpt_delete( map->pt, addr );

            assert(r == 0);
        }

        /* next! */
        s64 += PAGE_SIZE;
    }

    return;
}

void 
pmap_enter( pmap_t		pmap,
	    vm_map_offset_t	v,
	    ppnum_t		pn,
	    vm_prot_t	prot,
	    unsigned int	flags,
	    boolean_t	wired )
{
    int r;
    v = trunc_page(v);

    dprintf( "pmap_enter: pm %p, vmp %p, pn %x, prot %d\n", 
       pmap, (void*) v, pn, prot );

    /* check for an existing entry to remove from the ptov */
    {
	    ppnum_t old_pn;
	    vm_prot_t old_prot;
        int dummy;
	    
	    /* get the record */
	    r = tlpt_lookup( pmap->pt, (void*) v, &old_pn, &old_prot, &dummy, &dummy);
	    
	    if( r == 0 )
	    {
		    dprintf( "overwriting PTE, removing old PtoV\n" );

		    r = ptov_del( pmap, v, old_pn );

		    if( r != 0 )
			    panic( "couldn't find ptov entry for PTE?\n" );
	    }
    }

    /* Insert into the pmap */
    if( pmap == kernel_pmap )
    {
        /* Insert the underlying mapping, if it's kernel */
        r = tlpt_insert( pmap->pt, (void*) v, pn, prot, 1, 1 );
        assert( r == 0 );

        darbat_map( (void*) (pn << 12), (void*) v );
    }
    else
    {
        r = tlpt_insert( pmap->pt, (void*) v, pn, prot, 0, 0 );
        assert( r == 0 );
    }

    /* insert the reverse mapping, too */
    r = ptov_add( pmap, v, pn );
    if( r != KERN_SUCCESS )
	    panic( "error inserting into PtoV table\n" );
}


void
pmap_reference(pmap_t pmap)
{
    (void) pmap;

    //printf("pmap_reference: called\n" );
}

void
pmap_destroy(pmap_t pmap)
{
	//printf( "XXX: skipping pmap_destroy on %p\n", pmap );

	/* sanity check it's clear */
	tlpt_enum( pmap->pt );
}

void
pmap_clear_refmod( ppnum_t pn, unsigned int mask )
{
	pv_entry_t ent;
    pmap_t pmap;
    vm_offset_t va;
    vm_prot_t dummy_prot;
    int modified, referenced;
    int mod_mask, ref_mask;

    mod_mask = (mask & VM_MEM_MODIFIED) ? 0 : 1;
    ref_mask = (mask & VM_MEM_REFERENCED) ? 0 : 1;

	ent = ptov_enum_start( pn );

    if(ent == NULL)
    {
        return;
    }

    ent = ptov_enum_next( ent, &pmap, &va );

    while(ent)
    {
        int r = tlpt_lookup( pmap->pt, 
                (void*)(unsigned int)va, &pn, &dummy_prot, &referenced, &modified);

        assert(r == 0);

        r = tlpt_insert( pmap->pt, 
                (void*)(unsigned int)va, pn, dummy_prot, referenced & ref_mask, 
                modified & mod_mask);

        assert(r == 0);

        ent = ptov_enum_next( ent, &pmap, &va );
    }
}

void
pmap_zero_page( ppnum_t pn )
{
    char *addr;

    dprintf( "pmap_zero_page on pn %x\n", pn );
    addr = (void*) (pn << 12);
    bzero( addr, PAGE_SIZE );
}

void darbat_remove_write(void *addr);
void darbat_flush_write(void *addr);

void
pmap_protect( pmap_t		pmap,
	      vm_offset_t	s,
	      vm_offset_t	e,
	      vm_prot_t	prot )
{
	dprintf( "\npmap_protect: pmap %p, s %x, e %x, prot %d\n",
		pmap, (unsigned int) s, (unsigned int) e, prot );

    vm_offset_t orig_s = s;

    s = trunc_page(s);
	
	switch (prot) 
	{
		case VM_PROT_READ:
		case VM_PROT_READ|VM_PROT_EXECUTE:
            {
                if(pmap == kernel_pmap)
                {
                    for(;s<e;s+= PAGE_SIZE) {
                        darbat_flush_write((void *)s);
                    }
                } else {
                    for(;s<e;s+= PAGE_SIZE) {
                        darbat_remove_write((void *)(pmap_find_phys(pmap, s) << 12));
                    }
                }

                for(s=trunc_page(orig_s);s<e;s+= PAGE_SIZE)
                {
                    ppnum_t pn;
                    vm_prot_t old_prot;
                    int ref, mod, r;

                    // Update this pmap if there's an entry for this vadddr
                    r = tlpt_lookup( pmap->pt, (void*)(unsigned int)s, 
                            &pn, &old_prot, &ref, &mod);
                    if(r == 0)
                    {
                        r = tlpt_insert( pmap->pt, (void *)(unsigned int)s,
                                pn, prot, ref, mod);
                        assert(r == 0);
                    }
                }
            }
		case VM_PROT_READ|VM_PROT_WRITE:
		case VM_PROT_ALL:
			return; /* nothing to do */
		default:
			/* remove from pmap */
			pmap_remove(pmap, (addr64_t)s, (addr64_t)e);
			
			return;
	}
}

/* XXX: this pretty nasty */
extern void *kvm_start;
extern void *kvm_end;

/* XXX: this isn't really in the interface...??? */
ppnum_t
pmap_find_phys( pmap_t pmap, addr64_t va )
{
	ppnum_t pn;
	vm_prot_t prot;
	int r;
    int dummy;

    va = trunc_page(va);

	// printf( "pmap find phys on %p, va = %llx\n", pmap, va );
	
	r = tlpt_lookup( pmap->pt, (void*)(unsigned int) va, &pn, &prot, &dummy, &dummy);

	if( r != 0 )
	{
		if( pmap == kernel_pmap )
		{
			void *kva = (void*)(unsigned int)va;

			/* XXX: we dodge non kernel virt. mappings
			 * until we push everything into kernel virt.
			 */
			if( kva < kvm_start || kva >= kvm_end )
			{
				// printf( "dodging miss on phys lookup\n" );
				return (ppnum_t) va >> 12;
			}
			
			/* fall through to a miss... */
		}

		// printf( "pt miss on phys lookup!\n" );
		return 0;
	}

	return pn;
}

void
pmap_pageable( pmap_t pmap, vm_offset_t start_addr,
	       vm_offset_t end_addr, boolean_t pageable )
{
	(void) pmap;
    //printf("pmap_pageable on %p\n", pmap );
}

void
pmap_sync_page_data_phys(ppnum_t pa)
{
	(void) pa;

	//printf("pmap_sync_page_data_phys on %d\n", pa );
}

void
pmap_change_wiring( register pmap_t map,
		    vm_offset_t v,
		    boolean_t wired )
{
	(void) map;
	//printf("pmap_change_wiring on %p map:%p\n", (void *)(unsigned long)v, map );

}

unsigned int
pmap_get_refmod(ppnum_t pa)
{
    unsigned int retval = 0;

    if(pmap_is_referenced(pa))
    {
        retval |= VM_MEM_REFERENCED;
    }
    if(pmap_is_modified(pa))
    {
        retval |= VM_MEM_MODIFIED;
    }

    return retval;
}

void
pmap_clear_modify( ppnum_t pn )
{
	return;
}


void
pmap_page_protect( ppnum_t phys, vm_prot_t prot )
{
	int remove = 0;
	int r;
	pv_entry_t ent, next;

	dprintf( "\npmap_page_protect: setting pn %x to prot %d\n", phys, prot );

	switch (prot) 
	{
		case VM_PROT_READ:
		case VM_PROT_READ|VM_PROT_EXECUTE:
            darbat_remove_write((void *)(phys << 12));
			dprintf( "pmap_page_protect to read only\n" );
			break;
		case VM_PROT_READ|VM_PROT_WRITE:
		case VM_PROT_ALL:
			return; /* nothing to do */
		default:
			dprintf("pmap_page_protect called to remove\n");
            darbat_unmap_page( (void*) (phys << 12) );
			remove = 1;
			break;
	}

	/* iterate over the phys to virt list and adjust 
	 * the perms for each entry.
	 */

	ent = ptov_enum_start( phys );

	if( ent == NULL )
	{
		dprintf( "pmap_page_protect on unreferenced page %x\n", (int) phys );
        darbat_unmap_page( (void*) (phys << 12) );

		return;
	}

	while( ent != NULL )
	{
		pmap_t pmap;
		vm_offset_t va = 0;
		
		/* get the details of the virtual mapping */
		next = ptov_enum_next( ent, &pmap, &va );

		/* find/remove the PTE */
		if( remove )
		{
			r = tlpt_delete( pmap->pt, (void*) va);

            if(pmap == kernel_pmap)
            {
                darbat_flush_page((void *)va);
            }

			if( r != 0 )
            {
				panic( "Trying to delete PT not there!\n" );
            }
		}
		else
		{
			ppnum_t pn;
			vm_prot_t old_prot;
			int r;
            int referenced, modified;

            if(pmap == kernel_pmap)
            {
                darbat_flush_write((void *)(unsigned int)va);
            }

			/* get the record */
			r = tlpt_lookup( pmap->pt, (void*)(unsigned int) va, 
					 &pn, &old_prot, &referenced, &modified );

			if( r != 0 )
			{
				panic( "PT inconsistent with PtoV list?!" );
			}

			assert( pn == phys );

			/* update the mapping */
			if( prot != old_prot )
			{
				r = tlpt_insert( pmap->pt, (void*) va, 
						 phys, prot, referenced, modified);

				if( r != 0 )
                {
					panic( "Error re-inserting PTE\n" );
                }
			}
		}

		/* move to the next one */
		ent = next;
	}

	/* potentially clear out the PtoV list */
	if( remove )
    {
		ptov_flush_pagelist( phys );
    }
	
}


/*** XXX: some place more different ***/
#include <machine/machine_routines.h>

    void
bzero_phys( addr64_t phys_address, uint32_t length)
{
    //printf( "bzero phys %llx, len %x\n", phys_address, length );
    memset((void *)((unsigned long)phys_address), 0, length);
}

extern void bcopy_phys( addr64_t from, addr64_t to, vm_size_t bytes );
    void
bcopy_phys( addr64_t from, addr64_t to, vm_size_t bytes )
{
    //printf( "bcopy phys %llx -> %llx, len %x\n", from, to, bytes );

    memcpy( (void*) (unsigned int) to, 
            (void*) (unsigned int) from, bytes );
}


extern void back_kaddr( void *kaddr );

kern_return_t 
copypv( addr64_t src64,
        addr64_t snk64,
        unsigned int size,
        int which )
{
    void *from, *to;

    dprintf( "copypv %llx -> %llx, size 0x%x, which 0x%x\n",
            src64, snk64, size, which );

    // assert( (which & cppvPsrc) == cppvPsrc );  /* only phys source */
    // assert( (which & cppvPsnk) == 0 );         /* no phys dest */
    //assert( (which & cppvKmap) == cppvKmap );  /* kernel virt */

    from = (void*) (unsigned int) src64;
    to = (void*) (unsigned int) snk64;

    /*
       printf( "about to copy %p -> %p\n", from, to );

    // XXX: need to cover page boundaries!
    back_kaddr( to );

    memcpy( to, from, size );
    */
    if( (which & cppvKmap) == cppvKmap )
    {
        // printf( "about to copy %p -> %p\n", from, to );
        int npg, i;
        unsigned long endpage;
        unsigned long startpage;

        startpage = ((unsigned long)snk64 & ~0xfffUL);
        endpage = (((unsigned long)(snk64 + size)+ 0xfffUL) & ~0xfffUL);

        dprintf("%s: startpage 0x%lx endpage 0x%lx\n",
                __FUNCTION__, startpage, endpage);
        npg = (endpage - startpage) / 0x1000;
        dprintf("%s: backing %d pages\n", __FUNCTION__, npg);

        for (i = 0; i < npg; i++) {
            dprintf("%s: backing %p\n", 
                    __FUNCTION__, (void *)startpage);
            back_kaddr((void *)(startpage + i * 0x1000));
        }

        memcpy( to, from, size );
    }
    else
    {

	    if( (which & cppvPsnk) == cppvPsnk )
	    {
		    /* why does this 'work'?! */
		    int rc = copyin( (user_addr_t) src64, to, size );

		    if( rc != 0 )
			    panic( "copypv (in) failed!\n" );
	    }
	    else
	    {
		    assert( (which & cppvPsrc) == cppvPsrc );

		    /* does this work?? */
		    int rc = copyout( from, (user_addr_t) snk64, size );
		    if (rc != 0) {
			    dprintf("copyout() failed from %p to %p "
				    "size 0x%x \n", from, to, size);
			    assert(!"stop");
		    }
	    }
    }

    return KERN_SUCCESS;
}


void mapping_set_mod( ppnum_t pn );
    void
mapping_set_mod( ppnum_t pn )
{
    (void) pn;

    //printf( "mapping_set_mod on %d\n", pn );
}


/* NFI why we need this... */
    void
mapping_free_prime(void)
{
}

/* or this... */
    void
mapping_adjust(void)
{

}

void
pmap_commpage_init(vm_offset_t kernel_commpage, vm_offset_t user_commpage, int cnt)
{
	int i;
	dprintf("pmap_commpage_init cnt: %d\n", cnt);

	commpage_base = user_commpage;
	commpage_count = cnt;

	for (i = 0; i < cnt; i++) 
	{
		ppnum_t pn;
		vm_prot_t prot;
		int r, dummy;

		r = tlpt_lookup( kernel_pmap->pt, 
				 (void *)kernel_commpage, &pn, &prot, &dummy, &dummy);

		if (r != 0)
		{
			panic("kernel_commpage");
		}

		dprintf("commpage user is %p\n", (void *)user_commpage);

		// TGB need to verfy that user_commpage is with in range to fit in page table
		r = tlpt_insert(kernel_pmap->pt, (void *)user_commpage, pn, 
				(prot | INTEL_PTE_USER | INTEL_PTE_GLOBAL) 
				& ~INTEL_PTE_WRITE, 0, 0);

		//darbat_map( (void*) (pn << 12), (void*)user_commpage );

		kernel_commpage += INTEL_PGBYTES;
		user_commpage += INTEL_PGBYTES;
	}
}

void
pmap_commpage_hack(pmap_t pmap)
{
	ppnum_t pn;
	vm_prot_t prot;
	int r;

	if(!commpage_count && !commpage_base)
	{
		dprintf("returning early from pmap_commpage_hack\n");
		return;
	}

	int i;
	for(i=0;i<commpage_count;i++)
	{
        int dummy;
		r = tlpt_lookup( kernel_pmap->pt, 
				 (void *)(commpage_base+(i*INTEL_PGBYTES)), 
				 &pn, &prot, &dummy, &dummy);

		if(r != 0)
		{
			panic("pmap_commpage_hack lookup failed");
		}

		dprintf("adding a user commpage entry at %x\n", 
		       commpage_base+(i*INTEL_PGBYTES));

		r = tlpt_insert( pmap->pt, 
				 (void *)(commpage_base+(i*INTEL_PGBYTES)), 
				 pn, prot, 1, 0);
	}
}

void
pmap_copy_page(ppnum_t src, ppnum_t dst)
{
	bcopy_phys(src << 12, dst << 12, PAGE_SIZE);
}

unsigned int
pmap_free_pages(void)
{
	return pages_left;
}

boolean_t
pmap_next_page( ppnum_t *pn )
{
	if( pages_left == 0 )
		return FALSE;

	*pn = ((ppnum_t) phys_next) >> 12;
	phys_next = ((char*)phys_next) + PAGE_SIZE;
	pages_left--;

	return TRUE;
}


boolean_t
pmap_verify_free( ppnum_t pn )
{
	return TRUE;
}

/* XXX TGB HACK This will need to be fixed for paging to work */
unsigned int 
pmap_disconnect( ppnum_t pa )
{
    unsigned int retval = pmap_get_refmod(pa);
    
    pmap_page_protect( pa, VM_PROT_NONE);

    return retval;
}

boolean_t
pmap_is_modified(ppnum_t pn)
{
	pv_entry_t ent;
    pmap_t pmap;
    vm_offset_t va;
    vm_prot_t dummy_prot;
    int dummy, modified;

	ent = ptov_enum_start( pn );

    if(ent == NULL)
    {
        return 1;
    }

    ent = ptov_enum_next( ent, &pmap, &va );

    while(ent)
    {
        int r = tlpt_lookup( pmap->pt, 
                (void*)(unsigned int)va, &pn, &dummy_prot, &dummy, &modified);

        if(r == 0 && modified)
        {
            return 1;
        }
        ent = ptov_enum_next( ent, &pmap, &va );
    }

    return 0;
}

boolean_t
pmap_is_referenced(ppnum_t pn)
{
	pv_entry_t ent;
    pmap_t pmap;
    vm_offset_t va;
    vm_prot_t dummy_prot;
    int dummy, referenced;

	ent = ptov_enum_start( pn );

    if(ent == NULL)
    {
        return 1;
    }

    ent = ptov_enum_next( ent, &pmap, &va );

    while(ent)
    {
        int r = tlpt_lookup( pmap->pt, 
                (void*)(unsigned int)va, &pn, &dummy_prot, &referenced, &dummy);

        if(r == 0 && referenced)
        {
            return 1;
        }
        ent = ptov_enum_next( ent, &pmap, &va );
    }

    return 0;
}

ppnum_t
pmap_fault( pmap_t pmap, addr64_t va, vm_prot_t prot)
{
	ppnum_t pn;
    vm_prot_t entry_prot;
	int r;
    int referenced, modified;

    prot &= (~VM_PROT_EXECUTE);
    va = trunc_page(va);

	r = tlpt_lookup( pmap->pt, (void*)(unsigned int)va, &pn, &entry_prot, 
            &referenced, &modified);

	if( r != 0 || (prot & entry_prot) != prot)
	{
		return 0;
	}

    if(prot & VM_PROT_READ)
    {
        referenced = 1;
    }
    if(prot & VM_PROT_WRITE)
    {
        modified = 1;
    }

	r = tlpt_insert( pmap->pt, (void*)(unsigned int)va, pn, entry_prot, 
            referenced, modified);

	return pn;
}

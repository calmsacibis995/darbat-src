/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     arch/ia32/pgent.h
 * Description:   Generic page table manipluation for IA-32
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: pgent.h,v 1.33 2004/10/01 23:38:00 ud3 Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__IA32__PGENT_H__
#define __ARCH__IA32__PGENT_H__

#include <kmemory.h>
#include <debug.h>
#include INC_GLUE(config.h)
#include INC_GLUE(hwspace.h)
#include INC_ARCH(ptab.h)
#include INC_ARCH(mmu.h)

#define HW_PGSHIFTS		{ 12, 22, 32 }
#if defined(CONFIG_IA32_PSE)
#define HW_VALID_PGSIZES	((1 << 12) | (1 << 22))
#else /* !CONFIG_IA32_PSE */
#define HW_VALID_PGSIZES	((1 << 12))
#endif /* CONFIG_IA32_PSE */

#define MDB_BUFLIST_SIZES	{ {12}, {8}, {4096}, {0} }
#define MDB_PGSHIFTS		{ 12, 22, 32 }
#define MDB_NUM_PGSIZES		(2)

#if defined(CONFIG_IA32_SMALL_SPACES)
#include INC_GLUE(smallspaces.h)

#define SMALLID(s) (*(smallspace_id_t *)				   \
		    ((word_t) s + (CONFIG_SMP_MAX_CPUS * IA32_PAGE_SIZE) + \
		     ((SMALL_SPACE_ID >> IA32_PAGEDIR_BITS) * 4)))
#endif

EXTERN_KMEM_GROUP (kmem_pgtab);

class mapnode_t;
class space_t;

class pgent_t
{
public:
    union {
	ia32_pgent_t    pgent;
	u32_t		raw;
    };

    enum pgsize_e {
	size_4k = 0,
	size_4m = 1,
	size_4g = 2,
	size_max = size_4m
    };

private:

    // Linknode access
#if !defined(CONFIG_SMP)
    u32_t get_linknode (pgsize_e pgsize)
	{ return *(u32_t *) ((word_t) this + IA32_PAGE_SIZE); }
    
    void set_linknode (pgsize_e pgsize, u32_t val)
	{ *(u32_t *) ((word_t) this + IA32_PAGE_SIZE) = val; }

    void sync (space_t * s, pgsize_e pgsize) { }
#else

#define PDIR_LINKNODE_OFFSET (CONFIG_SMP_MAX_CPUS * IA32_PAGE_SIZE)
#define PTAB_LINKNODE_OFFSET (IA32_PAGE_SIZE)
    u32_t get_linknode (pgsize_e pgsize)
	{ 
	    return *(u32_t *) ((word_t) this + 
			       (pgsize == size_4m ? PDIR_LINKNODE_OFFSET :
				PTAB_LINKNODE_OFFSET)); 
	}
    
    void set_linknode (pgsize_e pgsize, u32_t val)
	{ 
	    *(u32_t *) ((word_t) this + 
			(pgsize == size_4m ? PDIR_LINKNODE_OFFSET :
			 PTAB_LINKNODE_OFFSET)) = val; 
	}

    pgent_t * get_pgent_cpu(unsigned cpu)
	{ return (pgent_t*) ((word_t) this + IA32_PAGE_SIZE * cpu); }

    void sync (space_t * s, pgsize_e pgsize)
	{
	    // synchronize first level entries only
	    if (pgsize == size_4m)
		for (unsigned cpu = 1; cpu < CONFIG_SMP_MAX_CPUS; cpu++)
		{
		    pgent_t * cpu_pgent = get_pgent_cpu(cpu);
		    //printf("synching %p=%p\n", cpu_pgent, this);
		    *cpu_pgent = *this;
		}
	}
public:
    // creates a CPU local subtree for CPU local data
    void make_cpu_subtree (space_t * s, pgsize_e pgsize, bool kernel)
	{
	    ASSERT(ALWAYS, kernel); // cpu-local subtrees are _always_ kernel
	    addr_t base = kmem.alloc (kmem_pgtab, IA32_PAGE_SIZE);
	    ASSERT(ALWAYS, base);
	    pgent.set_ptab_entry (virt_to_phys (base),
			    IA32_PAGE_USER|IA32_PAGE_WRITABLE);
	}
#endif /* CONFIG_SMP */

public:

    // Predicates

    bool is_valid (space_t * s, pgsize_e pgsize)
	{ return pgent.is_valid (); }
    
    bool is_writable (space_t * s, pgsize_e pgsize)
	{ return pgent.is_writable (); }
    
    bool is_readable (space_t * s, pgsize_e pgsize)
	{ return pgent.is_valid(); }
    
    bool is_executable (space_t * s, pgsize_e pgsize)
	{ return pgent.is_valid(); }

    bool is_subtree (space_t * s, pgsize_e pgsize)
	{ return (pgsize == size_4m) && !pgent.is_superpage (); }

    bool is_kernel (space_t * s, pgsize_e pgsize)
	{ return pgent.is_kernel(); }

    // Retrieval

    addr_t address (space_t * s, pgsize_e pgsize)
	{ return pgent.get_address (); }
	
    pgent_t * subtree (space_t * s, pgsize_e pgsize)
	{ return (pgent_t *) phys_to_virt (pgent.get_ptab ()); }

    mapnode_t * mapnode (space_t * s, pgsize_e pgsize, addr_t vaddr)
	{ return (mapnode_t *) (get_linknode (pgsize) ^ (u32_t) vaddr); }

    addr_t vaddr (space_t * s, pgsize_e pgsize, mapnode_t * map)
	{ return (addr_t) (get_linknode(pgsize) ^ (u32_t) map); }

    word_t reference_bits (space_t * s, pgsize_e pgsize, addr_t vaddr)
	{
	    word_t rwx = 0;
#if defined(CONFIG_SMP)
	    if (pgsize == size_4m)
		for (unsigned cpu = 0; cpu < CONFIG_SMP_MAX_CPUS; cpu++)
		{
		    pgent_t * cpu_pgent = get_pgent_cpu (cpu);
		    if (cpu_pgent->pgent.is_accessed ()) { rwx |= 5; }
		    if (cpu_pgent->pgent.is_dirty ()) { rwx |= 6; }
		}
	    else
#endif
	    {
		if (pgent.is_accessed ()) { rwx |= 5; }
		if (pgent.is_dirty ()) { rwx |= 6; }
	    }
	    return rwx;
	}

    // Modification

    void clear (space_t * s, pgsize_e pgsize, bool kernel, addr_t vaddr)
	{
	    pgent.clear ();
	    sync (s, pgsize);

	    if (! kernel)
		set_linknode (pgsize, 0);

#if defined(CONFIG_IA32_SMALL_SPACES)
	    if (pgsize == size_4m && SMALLID (s).is_small ())
		enter_kdebug ("Removing 4M mapping from small space");
#endif
	}

    void flush (space_t * s, pgsize_e pgsize, bool kernel, addr_t vaddr)
	{
	}

    void make_subtree (space_t * s, pgsize_e pgsize, bool kernel)
	{
	    addr_t base = kmem.alloc (kmem_pgtab, kernel ? IA32_PAGE_SIZE :
			                                  IA32_PAGE_SIZE * 2);
	    ASSERT(ALWAYS, base);
	    pgent.set_ptab_entry (virt_to_phys (base),
			    IA32_PAGE_USER|IA32_PAGE_WRITABLE);

	    sync(s, pgsize);
	}

    void remove_subtree (space_t * s, pgsize_e pgsize, bool kernel)
	{
	    addr_t ptab = pgent.get_ptab ();
	    pgent.clear();
	    sync(s, pgsize);
	    kmem.free (kmem_pgtab, phys_to_virt (ptab),
		       kernel ? IA32_PAGE_SIZE : IA32_PAGE_SIZE * 2);

#if defined(CONFIG_IA32_SMALL_SPACES)
	    if (SMALLID (s).is_small ())
		enter_kdebug ("Removing subtree from small space");
#endif
	}

    void set_entry (space_t * s, pgsize_e pgsize,
		    addr_t paddr, bool readable, 
		    bool writable, bool executable, bool kernel)
	{
	    pgent.set_entry (paddr, writable,
			     (ia32_pgent_t::pagesize_e) pgsize,
			     (kernel ? (IA32_PAGE_KERNEL
#ifdef CONFIG_IA32_PGE
                                        | IA32_PAGE_GLOBAL
#endif
                                 ) 
				     : IA32_PAGE_USER) |
			     IA32_PAGE_VALID);

#if defined(CONFIG_IA32_SMALL_SPACES_GLOBAL)
	    if ((! kernel) && SMALLID (s).is_small ())
		pgent.set_global (true);
#endif

	    sync(s, pgsize);

	}

    void set_entry (space_t * s, pgsize_e pgsize, pgent_t pgent)
	{
	    this->pgent = pgent.pgent;
	    sync(s, pgsize);
	}

    void set_cacheability (space_t * s, pgsize_e pgsize, bool cacheable)
	{
	    this->pgent.set_cacheability(cacheable);
	    sync(s, pgsize);
	}

    void set_global (space_t * s, pgsize_e pgsize, bool global)
	{
#if defined(CONFIG_IA32_PGE)
	    pgent.set_global (global);
	    sync (s, pgsize);
#endif
	}

    void revoke_rights (space_t * s, pgsize_e pgsize, word_t rwx)
	{ if (rwx & 2) raw &= ~IA32_PAGE_WRITABLE; sync(s, pgsize); }

    void update_rights (space_t * s, pgsize_e pgsize, word_t rwx)
	{ if (rwx & 2) raw |= IA32_PAGE_WRITABLE; sync(s, pgsize); }

    void reset_reference_bits (space_t * s, pgsize_e pgsize)
	{ raw &= ~(IA32_PAGE_ACCESSED | IA32_PAGE_DIRTY); sync(s, pgsize); }

    void update_reference_bits (space_t * s, pgsize_e pgsize, word_t rwx)
	{ raw |= ((rwx >> 1) & 0x3) << 5; }

    void set_linknode (space_t * s, pgsize_e pgsize,
		       mapnode_t * map, addr_t vaddr)
	{ set_linknode (pgsize, (u32_t) map ^ (u32_t) vaddr); }

    // Movement

    pgent_t * next (space_t * s, pgsize_e pgsize, word_t num)
	{ return this + num; }

    // Debug

    void dump_misc (space_t * s, pgsize_e pgsize)
	{
	    if (pgent.pg.global)
		printf ("global ");

	    printf (pgent.pg.cache_disabled ? "UC" :
		    pgent.pg.write_through  ? "WT" : "WB");
	}
};


#endif /* !__ARCH__IA32__PGENT_H__ */

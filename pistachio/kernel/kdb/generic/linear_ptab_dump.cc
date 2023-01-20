/*********************************************************************
 *                
 * Copyright (C) 2002, 2003-2004,  Karlsruhe University
 *                
 * File path:     kdb/generic/linear_ptab_dump.cc
 * Description:   Linear page table dump
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
 * $Id: linear_ptab_dump.cc,v 1.15 2004/03/10 12:32:08 skoglund Exp $
 *                
 ********************************************************************/
#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <kdb/cmd.h>
#include <kdb/kdb.h>
#include <kdb/input.h>
#include <linear_ptab.h>

#include INC_ARCH(pgent.h)
#include INC_API(tcb.h)

void get_ptab_dump_ranges (addr_t * vaddr, word_t * num,
			   pgent_t::pgsize_e * max_size);

#if !defined(CONFIG_ARCH_IA32) && !defined(CONFIG_ARCH_AMD64)
void get_ptab_dump_ranges (addr_t * vaddr, word_t * num,
			   pgent_t::pgsize_e * max_size)
{
    *vaddr = (addr_t) 0;
    *num = page_table_size (pgent_t::size_max);
    *max_size = pgent_t::size_max;
}
#endif


/**
 * cmd_dump_ptab: dump page table contents
 */
DECLARE_CMD (cmd_dump_ptab, root, 'p', "ptab", "dump page table");

CMD(cmd_dump_ptab, cg)
{
    static char spaces[] = "                                ";
    char * spcptr = spaces + sizeof (spaces) - 1;
    char * spcpad = spcptr - pgent_t::size_max * 2;

    space_t * space;
    addr_t vaddr;
    word_t num;
    pgent_t * pg;
    pgent_t::pgsize_e size, max_size;

    // Arrays to implement recursion
    pgent_t * r_pg[pgent_t::size_max];
    word_t r_num[pgent_t::size_max];

    // Get dump arguments
    space = get_space ("Space");
    space = space ? space : get_kernel_space();

    size = pgent_t::size_max;
    
    get_ptab_dump_ranges (&vaddr, &num, &max_size);
    pg = space->pgent (page_table_index (pgent_t::size_max, vaddr));

    while (size != max_size)
    {
	ASSERT(DEBUG, pg->is_subtree (space, size));
	pg = pg->subtree (space, size--);
	pg = pg->next (space, size, page_table_index (size, vaddr));
    }

#if defined(CONFIG_ARCH_ARM) && defined(CONFIG_ENABLE_FASS)
    word_t domain = space->get_domain();
#endif
    while (num > 0)
    {
	if (pg->is_valid (space, size))
	{
	    if (pg->is_subtree (space, size))
	    {
		// Recurse into subtree
		printf ("%p [%p]:%s tree=%p", vaddr, pg->raw, spcptr,
			pg->subtree (space, size));
#if defined(CONFIG_ARCH_ARM) && defined(CONFIG_ENABLE_FASS)
		if ((space == get_kernel_space() || !space->is_domain_area(vaddr))
				&& size == pgent_t::size_1m)
		    domain = pg->get_domain();
#endif

		size--;
		r_pg[size] = pg->next (space, size+1, 1);
		r_num[size] = num - 1;
		spcptr -= 2;
		spcpad += 2;

		pg = pg->subtree (space, size+1);
		num = page_table_size (size);
		printf ("\n");
		continue;
	    }
	    else
	    {
		// Print valid mapping
		word_t pgsz = page_size (size);
		word_t rwx = pg->reference_bits (space, size, vaddr);
		printf ("%p [%p]:%s phys=%p  map=%p %s%3d%cB %c%c%c "
			"(%c%c%c) %s"
			,vaddr, pg->raw, spcptr, pg->address (space, size),
			space->is_mappable (vaddr) ?
			pg->mapnode (space, size, vaddr) : (void*)0,
			spcpad, (pgsz >= GB (1) ? pgsz >> 30 :
				pgsz >= MB (1) ? pgsz >> 20 : pgsz >> 10),
			pgsz >= GB (1) ? 'G' : pgsz >= MB (1) ? 'M' : 'K',
			pg->is_readable (space, size)   ? 'r' : '~',
			pg->is_writable (space, size)   ? 'w' : '~',
			pg->is_executable (space, size) ? 'x' : '~',
			rwx & 4 ? 'R' : '~',
			rwx & 2 ? 'W' : '~',
			rwx & 1 ? 'X' : '~',
			pg->is_kernel (space, size) ? "kernel" : "user  ");
		pg->dump_misc (space, size);
#if defined(CONFIG_ARCH_ARM)
		printf(" %s",
			pg->get_attributes(space, size) == cached ? "WB" :
			pg->get_attributes(space, size) == uncached ? "UC" :
			pg->get_attributes(space, size) == writethrough ? "WT" :
			pg->get_attributes(space, size) == writecombine ? "WC" :
			"??");
#if defined(CONFIG_ENABLE_FASS)
		if ((space == get_kernel_space() || !space->is_domain_area(vaddr))
				&& size == pgent_t::size_1m)
		    domain = pg->get_domain();
		printf(" domain = %d", domain);
#endif
#endif
		printf ("\n");
	    }
	}

	// Goto next ptab entry
	vaddr = addr_offset (vaddr, page_size (size));
	pg = pg->next (space, size, 1);
	num--;

	while (num == 0 && size < max_size)
	{
	    // Recurse up from subtree
	    pg = r_pg[size];
	    num = r_num[size];
	    size++;
	    spcptr += 2;
	    spcpad -= 2;
	}
    }
#if defined(CONFIG_ARCH_ARM)
    printf("Key: WB = WriteBack (cached), WT = WriteThrough (cached)\n");
    printf("     WC = WriteCombine (uncached, buffered), UC = UnCached (not buffered)\n");
#endif

    return CMD_NOQUIT;
}


/*********************************************************************
 *                
 * Copyright (C) 2003,  Karlsruhe University
 *                
 * File path:     mbi.cc
 * Description:   
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
 * $Id: mbi.cc,v 1.3 2003/12/03 21:22:29 joshua Exp $
 *                
 ********************************************************************/
/*
  Authors: Ka Group, Ben Leslie (NICTA)
  Modifications: Rewrote as pure C. Use ELF libraries 
*/

#include "mbi.h"
#include "lib.h"
#include <string.h>
#include <stdio.h>

/**
 * Returns the total size of the mbi.  Includes the size of module
 * definitions, strings, and any space necessary to maintain
 * aligment.
 *
 * @returns The total size of the mbi.
 */
L4_Word_t mbi_get_size(mbi_t *mbi)
{
    L4_Word_t tot = sizeof(mbi_t);
    L4_Word_t alignment_space = sizeof(L4_Word_t);

    tot += 1 + strlen(mbi->cmdline) + alignment_space;

    for (L4_Word_t i = 0; i < mbi->modcount; i++) {
	    tot += sizeof(mbi_module_t);
	    tot += 1 + strlen(mbi->mods[i].cmdline) + alignment_space;
    }

    return tot;
}

/**
 * Copies the current mbi into a new location.
 *
 * @param target	The destination for the new copy.  Must have enough
 * 			space to store the copy.  The space is calculated
 * 			via the get_size() method.
 */
void copy_mbi( mbi_t *mbi, mbi_t *target )
{
	// Put strings after the target mbi and after the modules.
	char *strings = (char *)( (L4_Word_t) target + sizeof(mbi_t) + 
				  sizeof(mbi_module_t)*mbi->modcount );
	
	// Copy the structure.
	memcpy( target, mbi, sizeof(mbi_t) );
	// Copy the command line.
	if(mbi->cmdline) {
		target->cmdline = strings;
		strcpy(target->cmdline, mbi->cmdline);
		strings = strings + 1 + strlen(mbi->cmdline);
		// TODO: align the strings pointer.
	}

	// Put modules at end of the target mbi.  Assume this will get
	// proper aligment.
	target->mods = (mbi_module_t *)((L4_Word_t) target  + sizeof(mbi_t) );

	for( L4_Word_t i = 0; i < mbi->modcount; i++ ) {
		// Copy the structure.
		memcpy( &target->mods[i], &mbi->mods[i], sizeof(mbi_module_t) );
		// Copy the command line.
		if(mbi->mods[i].cmdline) {
			target->mods[i].cmdline = strings;
			strcpy(target->mods[i].cmdline, mbi->mods[i].cmdline );
			strings = strings + 1 + strlen(mbi->mods[i].cmdline);
			// TODO: align the strings pointer.
		}
	}
}

extern char _kickstart_begin, _kickstart_end;

/**
 * Determines whether there is a conflict for a memory region with
 * the modules defined by the mbi.
 *
 * @param start		The start of the memory region.
 * @param size		The size of the memory region.
 *
 * @returns true if there is no conflict, otherwise false.
 */
bool
mbi_is_mem_region_free(mbi_t *mbi, L4_Word_t start, L4_Word_t size )
{
	L4_Word_t end = start - 1 + size;
	//printf("Checking free: %lx\n", start);
	// Look for conflicts with modules.
	for( L4_Word_t i = 0; i < mbi->modcount; i++ ) {
		L4_Word_t mod_start = mbi->mods[i].start;
		L4_Word_t mod_end = mbi->mods[i].end;
		//printf("mod start: %lx mod_end: %lx\n", mod_start, mod_end);
		if( is_intersection(start, end, mod_start, mod_end) )
			return false;
	}
	
	// Look for a conflict with the bootloader.
	L4_Word_t kick_begin = (L4_Word_t) &_kickstart_begin;
	L4_Word_t kick_end = (L4_Word_t) &_kickstart_end;
	//printf("kick_being: %lx kick_end %lx\n", kick_begin, kick_end);
	//printf("start: %lx end: %lx, intersection: %d\n", start, end, is_intersection( start, end, kick_begin, kick_end ));
	return !is_intersection( start, end, kick_begin, kick_end );
}

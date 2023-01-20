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
 * lkm_macho.c
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

#include <lkm/lkm.h>
#include <mach-o/mach-o.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iguana/memsection.h>

#include <l4/kdebug.h>

/*
 * XXX REMOVE ME XXX
 */
#define roundup(x, y)   (((x) + ((y)-1)) & ~((y) - 1))

#ifdef __APPLE_CC__
extern struct mach_header	_mh_execute_header;
#else
struct mach_header		_mh_execute_header;
#endif

/*
 * lkm_macho_init
 *
 * This function initializes the underlying executable, of Mach-O
 * binary format munged with the Dite program.
 */
int
lkm_macho_init(void)
{
	struct mach_header	*mh = &_mh_execute_header;
	struct segment_command	*segcmd;
	struct symtab_command	*symcmd;
	struct nlist		*syms;
	char			*strtab;
	uint32_t		vmsiz;
	int			i;

	dprintf("%s: initializing\n", __func__);

	/*
	 * If not Apple's cc, this will make it fail gracefully.
	 */	
	if (macho_checkfile(mh)) {
		dprintf("%s: not recognized Mach-O file\n", __func__);
		return (ELKMBADFILE);
	}

	lkm_hashinit(LKM_HASHSIZ);

	vmsiz  = 0;
	segcmd = (struct segment_command *)(mh + 1);
	for (i = 0; i < mh->ncmds; i++) {
		switch (segcmd->cmd) {
			case LC_SEGMENT:
				if (strcmp(segcmd->segname, "__PAGEZERO")) {
					vmsiz += roundup(segcmd->vmsize, 
					    0x1000/*XXX*/);
				}
				break;
			case LC_SYMTAB:
				symcmd = (struct symtab_command *)segcmd;
				vmsiz = roundup(vmsiz +
				    symcmd->nsyms * sizeof(struct nlist),
				    0x1000/*XXX*/);
				break;
			default:
				dprintf("%s: unrecognized load command\n", 
				    __func__);
				break;
		}

		segcmd = (struct segment_command *)((char *)segcmd + 
		     segcmd->cmdsize);
	}

	/*
	 * Yes we really have to parse this twice, since we do not know if 
	 * the LC_SYMTAB will come before the link edit segment (which it
	 * doesn't, usually.
	 */
	segcmd = (struct segment_command *)(mh + 1);
	for (i = 0; i < mh->ncmds; i++) {
		if (segcmd->cmd == LC_SEGMENT &&
		    strcmp(segcmd->segname, "__LINKEDIT") == 0) {
			syms = (struct nlist *)segcmd->vmaddr;
			strtab = (char *)(segcmd->vmaddr + 
			    symcmd->stroff - symcmd->symoff);
			break;	/* all done! */
		}
		segcmd = (struct segment_command *)((char *)segcmd + 
		     segcmd->cmdsize);
	}

	dprintf("%s: %lu syms found, nlist %p strtab %p\n", 
	     __func__, 
	    symcmd->nsyms,
	    syms,
	    strtab);

#if 1	/* XXX: Temporary */
	for (i = 0; i < symcmd->nsyms; i++) {
		if (syms[i].n_type & N_EXT) 
			lkm_hashput(syms[i].n_un.n_strx + strtab, 
			    syms[i].n_value);
	}
#endif

	dprintf("%s: initialized\n", __func__);

	return (ELKMSUCCESS);
}
 
/*
 * lkm_macho_resolve
 *
 * Resolve an undefined symbol 
 */
int
lkm_macho_resolve(name, sect, rinfo, mstart)
	const char		*name;
	struct section		*sect;
	struct relocation_info	*rinfo;
	const char		*mstart;
{
	unsigned long		*p;
	uint32_t		value;
	int			rc;

#if MACHO_NO_UNDERSCORES
	/*
	 * Mach-O seems to have an interesting property that prepends an 
	 * underscore in front of a C symbol.
	 */
	if (*name == '_')
		name++;
#endif	/*MACHO_NO_UNDERSCORES*/

	rc = lkm_hashget(name, &value);
	if (rc != ELKMSUCCESS) {
		printf("%s: cannot find sym %s\n",
		    __func__,
		    name);
		L4_KDB_Enter("please fix this");
		return rc;
	}

	p = (unsigned long *)(rinfo->r_address + sect->addr + mstart);
	dprintf("%s: attempting to patch addr %p (value = %p)...\n",
	    __func__,
	    p,
	    (void *)value);
	/*
	 * Do pc-relative addressing if required.
	 *
	 * XXX What I would really be interested to know is,
	 * XXX ELF has PCREL32 where it is target - source +
	 * XXX addend (which normally is -4).  How the hell
	 * XXX does Mach-O do this, specifically in the context
	 * XXX of a dynamically loaded kernel module inserted 
	 * XXX at run-time?
	 *
	 * -gl
	 */
	if (rinfo->r_pcrel)
		*p = (unsigned long)value - (unsigned long)p + (-4/*XXX*/);
	else	
		*p = (unsigned long)value + *p;

	dprintf("%s: patched extern sym %s at %p with 0x%lx\n",
	    __func__,
	    name, 
	    p,
	    *p);

	return ELKMSUCCESS;
}
 
/*
 * lkm_machoreloc
 *
 * Do relocations for a Mach-O section
 */
int
lkm_machoreloc(mh, sc, sect, symc, mstart, bssptr)
	struct mach_header	*mh;
	struct segment_command	*sc;
	struct section		*sect;
	struct symtab_command	*symc;
	char			*mstart;
	uintptr_t		*bssptr;
{
	struct scattered_relocation_info	*srinfo;
	struct relocation_info	*rinfo;
	struct nlist		*symtab, *sym;
	int			i;
	char			*strtab;
	unsigned long		*p;
	long			val;

	dprintf("%s: doing reloc for sect %s nrelocs %lu "
	    "relocation offset %lu\n",
	    __func__,
	    sect->sectname,
	    sect->nreloc,
	    sect->reloff);

	dprintf("%s: mh %p symc %p symc->stroff 0x%lx\n",
	    __func__,
	    mh,
	    symc,
	    symc->stroff);


	strtab = (char *)mh + symc->stroff;
	symtab = (struct nlist *)((char *)mh + symc->symoff);

	rinfo = (struct relocation_info *)((char *)mh + sect->reloff);

	dprintf("%s: printing relocation info\n", __func__);

	for (i = 0; i < sect->nreloc; i++) {

		if ((rinfo->r_address & R_SCATTERED) == 0) {
			dprintf("%s: r_address 0x%lx (%p) r_symbolnum %u "
			    "r_pcrel %u r_length %u r_extern %u r_type %u\n",
			    __func__, 
			    rinfo->r_address,
			    (char *)(rinfo->r_address + sect->addr),
			    rinfo->r_symbolnum,
			    rinfo->r_pcrel,
			    rinfo->r_length,
			    rinfo->r_extern,
			    rinfo->r_type);

			/*
			 * XXX FIXME XXX
			 *
			 * we only handle i386 for now.  I386 uses 
			 * generic Mach-O relocation.
			 */
			if (rinfo->r_type != 0)
				L4_KDB_Enter("mach-o reloc type not generic");
		}

		if (rinfo->r_address & R_SCATTERED) {
			/*
			 * This is actually a scattered relocation.
			 * We need to cast it to a scattered version
			 * and do the appropriate fixup.
			 */
			dprintf("%s: rscattered\n", __func__);
			srinfo = (struct scattered_relocation_info *)rinfo;
			p = (unsigned long *)(srinfo->r_address + 
			    sect->addr + mstart);

			/*
			 * XXX: I _think_ that is what it means.
			 * -gl
			 */
			dprintf("%s: patching scattered relocation info "
			    "0x%lx -> 0x%lx\n",
			    __func__, 
			    srinfo->r_value, 
			    mstart + srinfo->r_value);
			if (srinfo->r_type != 0 || srinfo->r_pcrel)
				L4_KDB_Enter("scattered && !generic");
			*p = *p + mstart;
			dprintf("%s: patched scattered info\n", __func__);
		} else if (rinfo->r_symbolnum == R_ABS) {
			dprintf("%s: symbol does not need relocation\n",
			    __func__);
		} else if (rinfo->r_extern) {
			/*
			 * If extern, we look elsewhere.
			 * In this case, the r_symbolnum (24 bits) contain
			 * the symbol index.
			 */
			dprintf("%s: r_extern, sym %s n_value 0x%lx \n",
			    __func__,
			    (symtab + rinfo->r_symbolnum)->n_un.n_strx +
			    strtab,
			    (symtab + rinfo->r_symbolnum)->n_value);

			sym = symtab + rinfo->r_symbolnum;

			/*
			 * We will compare the symbols with what we have
			 * existing.
			 *
			 * XXX since for now we are interfacing with ELF
			 * AND Mach-O, we have a problem.  Apple's Mach-O
			 * gcc compiler will append a leading underscore
		 	 * to a C symbol.  We make a simple sanity check
			 * to see if it is the case, and we skip over it.
			 *
		 	 * This is all done in the macho_resolve handler.
			 */

			/*
			 * Common symbols are identified by n_type N_UNDF and
			 * N_EXT with a non-zero n_value.
			 */
			if (((sym->n_type & N_TYPE) == N_UNDF) &&
			    (sym->n_type & N_EXT) && sym->n_value) {
				
				p = (unsigned long *)(rinfo->r_address + 
				    sect->addr + mstart);
				*p = (unsigned long)*bssptr + sym->n_value;
				dprintf("%s: bss %p patched with 0x%lx\n",
				    __func__, p, *p);
			} else
				lkm_macho_resolve(sym->n_un.n_strx + strtab, 
				    sect, rinfo, mstart);
		} else {
			/*
			 * Otherwise, it is a local thing.  The r_symbolnum
		 	 * contain the section ordinal.
			 */
			dprintf("%s: !r_extern\n", __func__);


			/*
			 * OK.  R_address is the field which contains
			 * the offset which we need to relocate.  Let's
			 * assume we do not have any STAB symbols ..
			 * XXX FIXME XXX
			 *
			 * The n_value contains the offset which we need
			 * to poke into.  (This is especially true for
			 * Mach-O which translates to calll instruction
			 * which does a direct memory location call.
			 * (This, of course, is x86 specific.  Blame me.)
			 */

			/*
		 	 * OK, let's patch it.  XXX FIXME TYPES XXX
			 */
			/*
			 * Note that the r_address is actually an offset
			 * within the section that we are in, and not
			 * from the start of the executable.
			 */
			p = (unsigned long *)(rinfo->r_address + sect->addr +
			    mstart);
			dprintf("%s: XXXXX %p before is 0x%lx\n", 
			     __func__, p, *p);
			/*
			 * XXX: is val an offset from the current 
			 * XXX: section, or is it from the start of
			 * XXX: the binary??
			 * XXX: -gl
			 */
			val = *p;

			if (rinfo->r_pcrel)
				;	/* What to do for this? */
			else
				*p = (unsigned long)((unsigned long)mstart + 
				    val);

			/*
			 * Apparently, the offset from start of the sections
			 * is embedded into the location itself for x86.
			 */
			dprintf("%s: patched addr %p with value 0x%lx\n",
			    __func__,
			    p,
			    *p);
		}

		rinfo++;
	}

	return ELKMSUCCESS;
}


/*
 * lkm_loadsegment
 *
 * Loads a Mach-O segment into core
 */
int
lkm_loadsegment(mh, sc, symc, entry, bssptr, mstart)
	struct mach_header	*mh;
	struct segment_command	*sc;
	struct symtab_command	*symc;
	uintptr_t		*entry;
	uintptr_t		*bssptr;
	uintptr_t		mstart;
{
	int			i;
	struct section		*sect;
	uintptr_t		addr;
	size_t			offset;

	dprintf("%s: cmd %lu cmdsize %lu name %s\n",
	    __func__,
	    sc->cmd,
	    sc->cmdsize,
	    sc->segname);

	/*
	 * XXX: generalize this.  In Apple's kld, we do not do the
	 * allocation but someone else does it for us.
	 */
#if 0
	ref = memsection_create(roundup(sc->vmsize, 0x1000), &addr);
	assert(addr);
	*mstart = addr; 
#else
	addr = mstart;
#endif

	sect = (struct section *)((char *)sc + sizeof(*sc));
	offset = 0;

	/*
	 * Does this section contain the entry point offset?
	 */
	if (*entry >= sc->vmaddr && *entry < (sc->vmaddr + sc->vmsize)) 
		(*entry) += addr;

	dprintf("%s: src %p dst %p siz %d\n",
	    __func__,
	    (char *)mh + sc->fileoff, (char *)(sc->vmaddr + addr),
	    (int)sc->filesize);
	memcpy((void *)(sc->vmaddr + addr), (char *)mh + sc->fileoff,
	    sc->filesize);
	/*
	 * zero.
	 */
	if (sc->vmsize - sc->filesize)
		memset((void *)(sc->vmaddr + sc->filesize + addr), 0,
		    sc->vmsize - sc->filesize);

	for (i = 0; i < sc->nsects; i++) {
#if 0
		/*
		 * Since we have the type MH_OBJECT, the addr
		 * is actually the memory offset at which we 
		 * choose it to be (as picked by addr earlier
		 * on in this function.  Now, just keep copying,
		 * until we reach the end ..
		 */
		memcpy((void *)(addr + sect->addr), 
		    (char *)mh + sect->offset, sect->size);

		dprintf("%s: loaded %s into %p size %lu\n",
		    __func__,
		    sect->sectname,
		    (void *)(addr + sect->addr),
		    sect->size);

		offset = addr + sect->addr + sect->size;

		/*
		 * Any relocation to do?
		 */
#endif
		if (sect->nreloc)
			lkm_machoreloc(mh, sc, sect, symc, (char *)addr, 
			    bssptr);
		sect++;
	}

#if 0
	/*
	 * Any leftovers from behind should get zero'ed.
	 *
	 */
	dprintf("%s: zeroing %p (%lu bytes)\n",
	    __func__,
	    (void *)offset,
	    sc->vmsize - sc->filesize);

	memset((void *)offset, 0, sc->vmsize - sc->filesize);
#endif

	return ELKMSUCCESS;
}

/*
 * lkm_loadsymtab
 *
 * Loads a Mach-O symbol table.
 *
 * This may seem superfluous, but there is actually something to do here.
 * We need to work out how big we are, since the common symbols aren't
 * listed.  We have to parse the symbol table for bss, work out how big
 * it is (based on the alignment restrictions as given to us by the 
 * n_value field) and return it back to the caller.
 *
 * This is probably also a convenient place to pick up the entry point.
 */
int
lkm_loadsymtab(mh, sc, name, entry, bss)
	struct mach_header	*mh;
	struct symtab_command	*sc;
	const char		*name;
	uintptr_t		*entry;
	uintptr_t		*bss;
{
	char		*strtab;
	struct nlist	*sym;
	unsigned long	i, nsyms;
	char		*myname;
	uint32_t	val;

	dprintf("%s: symtab cmd %lu cmdsize %lu offset 0x%lx nsyms %lu\n",
	    __func__,
	    sc->cmd,
	    sc->cmdsize,
	    sc->symoff,
	    sc->nsyms);

	strtab = (char *)mh + sc->stroff;
	sym = (struct nlist *)((char *)mh + sc->symoff);
	nsyms = sc->nsyms;

#if MACHO_NO_UNDERSCORES
	/*
	 * Manually append on the leading underscore.
	 *
	 * This makes us depend on Libc.
	 * Sigh.
	 */
	myname = malloc(strlen(name) + 2);
	if (!myname)
		return ELKMNOMEM;

	sprintf(myname, "_%s", name);
#else	/*MACHO_NO_UNDERSCORES*/
	myname = (char *)name;
#endif	/*MACHO_NO_UNDERSCORES*/

	for (i = 0; i < nsyms; i++) {
#if 0	/* chatty */
		dprintf("%s: got name %s\n",
		    __func__,
		    sym->n_un.n_strx + strtab);
#endif	/* chatty */
		if (strcmp(sym->n_un.n_strx + strtab, myname) == 0)  {
			dprintf("%s: found entry point match = %p\n",
			    __func__,
			    (void *)sym->n_value);
			*entry = sym->n_value;
		}

		/*
		 * Common symbols are identified by n_type N_UNDF and
		 * N_EXT with a non-zero n_value.
		 */
		if (((sym->n_type & N_TYPE) == N_UNDF) && sym->n_value)
			val = *bss = roundup(*bss, sym->n_value) + sym->n_value;

		sym++;
	}

#if MACHO_NO_UNDERSCORES
	free(myname);
#endif	/*MACHO_NO_UNDERSCORES*/

	return ELKMSUCCESS;
}

int
lkm_macho_symput(mh, sc, mstart, bssptr)
	struct mach_header	*mh;
	struct symtab_command	*sc;
	uintptr_t		mstart, bssptr;
{
	struct nlist		*sym;
	char			*strtab, *name;
	int			nsyms, i;

	strtab = (char *)mh + sc->stroff;
	sym = (struct nlist *)((char *)mh + sc->symoff);
	nsyms = sc->nsyms;

	for (i = 0; i < nsyms; i++) {

		/*
		 * Put whatever we have into the symbol hash table, but
		 * only if it is defined.  Undefined symbols that are
		 * referenced outside of the object are not added.
		 */
		if (((sym->n_type & N_TYPE) == N_UNDF) && !sym->n_value)
			goto next;

		/*
		 * get rid of the leading _ for Mach-O
		 */
		if (sym->n_un.n_strx) {
			name = sym->n_un.n_strx + strtab;
#if MACHO_NO_UNDERSCORES
			if (*name == '_')
				name++;
#endif	/*MACHO_NO_UNDERSCORES*/
		} else
			name = "(unknown symbol)";
			
		/*
		 * Special case for bss.
		 */
		if (((sym->n_type & N_TYPE) == N_UNDF) && sym->n_value) {
			bssptr = roundup(bssptr, sym->n_value);
			dprintf("%s: adding %s -> 0x%lx\n",
			    __func__,
			    sym->n_un.n_strx + strtab,
			    (unsigned long)bssptr);
			lkm_hashput(name, bssptr + sym->n_value);
			/*
			 * reserve space for this one ..
			 */
			bssptr += sym->n_value;	
			goto next;
		}

		/*
		 * Hack.
		 *
		 * -gl.
		 */
		if (strcmp(sym->n_un.n_strx + strtab, "_kmod_info") == 0) {
			printf("%s: adding %s -> 0x%lx (start = 0x%lx)\n",
			    __func__,
			    sym->n_un.n_strx + strtab,
			    (unsigned long)(sym->n_value + mstart),
			    (unsigned long)mstart);
			goto put;
		}
		
		/*
		 * Do not add if it does not have the extern bit set (N_EXT)
		 * XXX what about private extern?
		 */
		if (!(sym->n_type & N_EXT))
			goto next;

		/*
		 * For types of N_SECT, n_value is the address of the
		 * symbol (probably an offset, since this is relocatable).
		 */
		if (sym->n_type & N_SECT) {
put:
			dprintf("%s: adding %s -> 0x%lx (start = 0x%lx)\n",
			    __func__,
			    sym->n_un.n_strx + strtab,
			    (unsigned long)(sym->n_value + mstart),
			    (unsigned long)mstart);
			lkm_hashput(name, sym->n_value + mstart);
			goto next;
		}
next:
		sym++;
	}

	return ELKMSUCCESS;
}

/*
 * lkm_load_macho
 *
 * Loads a Mach-O object file (MH_OBJECT) into main memory
 */
int
lkm_load_macho(mh, name, entry, mstart)
	struct mach_header	*mh;
	const char		*name;
	uintptr_t		*entry;
	uintptr_t		mstart;
{
	struct load_command	*lc;
	struct segment_command	*segcmd;
	struct section		*sect;
	struct symtab_command	*sc = NULL;
	int			i, j;
	uintptr_t		bssstart, bssptr, bss = 0;

	/*
	 * Right now, we can't load anything other than MH_OBJECTs.
	 * For LKMs, we probably do not care about the other types.
	 */
	if (mh->filetype != MH_OBJECT)
		return ELKMBADFILE;

	lc = macho_getloadcmds(mh);

	for (i = 0; i < mh->ncmds; i++) {

		/*
		 * XXX
		 *
		 * We need to have loaded the symtab before we could 
		 * do the relocation, right?
		 *
		 * -gl
		 */
		if (lc->cmd != LC_SYMTAB) {
			lc = (struct load_command *)((char *)lc + 
			    lc->cmdsize);
			continue;
		}

		lkm_loadsymtab(mh, 
		    (struct symtab_command *)lc, 
		    name, 
		    entry,
		    &bss);
		sc = (struct symtab_command *)lc;

		break;
	}

	/*
	 * Create the .bss section.
	 *
	 * XXX This will make it a bit odd-looking wrt memory layout to
	 * the rest of the modules.
	 */
	dprintf("%s: got bss size 0x%lx\n", 
	    __func__, 
	    (unsigned long)bss);
	/*
	 * Generalize this.  We do not do the allocation in Apple's
	 * kld.
	 */
#if 0
	if (bss) {
		ref = memsection_create(roundup(bss, 0x1000), &bssptr);
		assert(bssptr);
	}
	dprintf("%s: created bss region bssptr 0x%lx\n", 
	    __func__,
	    (unsigned long)bssptr);

	bssstart = bssptr;
#endif

	/*
	 * XXX DEBUG XXX
	 * Be suspect of anyone who does not have a symbol table
	 */
	if (!sc)
		dprintf("%s: module does not have symbol table!\n",
		    __func__);

	/*
	 * Add the symbol table before we do the relocation.  Cases have
	 * been noticed where the r_extern bit is set but when the symbol
	 * is really inside the binary.   We want to be able to properly
	 * relocate such things. -gl
	 */
	lkm_macho_symput(mh, sc, mstart, bssstart);
	/*
	 * Reset lc ptr	
 	 */
	lc = macho_getloadcmds(mh);
	for (i = 0; i < mh->ncmds; i++) {

		/*
		 * In Mach-O, a LC_SEGMENT command specifies a segment
		 * that should live in memory.  We look for lc->cmd
		 * to find out what it is, if it is LC_SEGMENT, we load it.
		 */

		switch (lc->cmd) {
			case LC_SEGMENT:
				lkm_loadsegment(
				    mh,
				    (struct segment_command *)lc, 
				    sc, entry, &bssptr, mstart);
				break;
			default:
				/* XXX NOP for now */
				break;
		}

		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}

	/*
	 * Fixup the header.  
	 * XXX: I am not quite sure if we need to do this. -gl
 	 */
	mh = (struct mach_header *)(mstart - mh->sizeofcmds);
	lc = macho_getloadcmds(mh);
	for (i = 0; i < mh->ncmds; i++) {
		segcmd = (struct segment_command *)lc;
		if (segcmd->cmd == LC_SEGMENT) {
			segcmd->vmaddr += mstart;
			dprintf("%s: segcmd->vmaddr %p\n",
			    __func__, (void *)segcmd->vmaddr);
			sect = (struct section *)((char *)segcmd +
			    sizeof(*segcmd));
			for (j = 0; j < segcmd->nsects; j++) {
				sect->addr += mstart;
				dprintf("%s: sect->addr %p\n",
				    __func__, (void *)sect->addr);
				sect++;
			}
		}
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
		
	dprintf("%s: returning entry point %p\n",
	    __func__,
	    (void *)*entry);

	return ELKMSUCCESS;
}


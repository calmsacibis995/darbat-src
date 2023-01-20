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
 * lkm.c
 *
 * LKM
 *
 *
 * XXX Make 64bit safe
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

/*
 * This parses an ELF executable, and grabs the symbol tables and whatnot
 * so that they can resolve things in loadable kernel modules.
 *
 * This is mainly for L4Darwin work and we could possibly jettison this
 * once we have Mach-O loading from within the "kernel", but obviously,
 * it can be used for other purposes too.  There are some Iguana-isms 
 * in here, but they should be easy to fix.
 *
 * Unfortunately, due to the silly SimpleExec of L4 generic bootinfo, 
 * the mbi must be used to grab the binary.  Fortunately, on IA-32 the 
 * kickstart loader supports this, but you leave the other architecutures
 * out in the cold, I'm sure.
 *
 * -gl.
 * 
 * TODO
 *
 * This thing assumes that the ELF sections are laid out in a certain order.
 * If your module breaks this assumption, it is not likely to work.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <l4/bootinfo.h>
#include <l4/kdebug.h>
#include <l4/kip.h>

#include <elf/elf.h>

#include <iguana/memsection.h>

#include <lkm/lkm.h>

static char *executablename;

/*
 * XXX
 *
 * We are abusing the mbi_module_t structure here.
 */
mbi_module_t
lkm_findmodule(name)
	const char	*name;
{
	L4_KernelInterfacePage_t	*kip;
	L4_BootRec_t			*rec;
	void				*bootinfo;
	int				i;

	kip = L4_GetKernelInterface();
	bootinfo = (void *)L4_BootInfo(kip);
	rec = L4_BootInfo_FirstEntry(bootinfo);

	for (i = 0; i < L4_BootInfo_Entries(bootinfo); i++) {

		if (L4_BootRec_Type(rec) == L4_BootInfo_Module &&
		    strcmp(name, L4_Module_Cmdline(rec)) == 0) 
			return (mbi_module_t) 
			    {	.start = L4_Module_Start(rec),
				.end = L4_Module_Start(rec) + 
				    L4_Module_Size(rec),
				.entry = 0,
				/* XXX: should duplicate this string? */
				.cmdline = L4_Module_Cmdline(rec)
			    };
			  
		rec = L4_BootRec_Next(rec);
	}

	return (mbi_module_t){ .start = 0, .end = 0, 
	    .cmdline = NULL, .entry = 0};
}

mbi_module_t
lkm_findbinary(name)
	const char	*name;
{
	L4_KernelInterfacePage_t	*kip;
	L4_BootRec_t			*rec;
	void				*bootinfo;
	int				i;
	mbi_t				*mbi = NULL;
	char				*s, *t;

	kip = L4_GetKernelInterface();
	bootinfo = (void *)L4_BootInfo(kip);
	rec = L4_BootInfo_FirstEntry(bootinfo);

	for (i = 0; i < L4_BootInfo_Entries(bootinfo); i++) {

		if (L4_BootRec_Type(rec) == L4_BootInfo_Multiboot) {
			mbi = (mbi_t *)L4_MBI_Address(rec);
			break;
		}	

		rec = L4_BootRec_Next(rec);
	}

	for (i = 3; i < mbi->modcount; i++) {

		/*
		 * XXX This isn't exactly great.
		 *
		 */
		s = t = mbi->mods[i].cmdline;
		while (*s) {
			if (*s == '/')
				t = s + 1;
			s++;
		}
		if (strcmp(t, name) == 0)
			return mbi->mods[i];
	}

	L4_KDB_Enter("no module found");

	return (mbi_module_t){ .start = 0, .end = 0, 
	    .cmdline = NULL, .entry = 0};
}

char *
lkm_getexec(void)
{

	return (executablename);
}

/*
 * XXX
 *
 * Need to make sure that it is quiesient.
 */
void
lkm_fini(void)
{

	free(executablename);
}

void
lkm_init(name)
	const char		*name;
{
	struct Elf32_Header	*ehdr;
	struct Elf32_Shdr	*esymhdr;
	Elf32_Sym		*esyms;
	char			*exec, *estrtab;
	mbi_module_t		binary;
	int			ensections;
	int			ensyms;
	int			i;

	dprintf("%s: initializing\n", __func__);

	executablename = malloc(sizeof(name) + 1);
	if (!executablename)
		L4_KDB_Enter("lkm_init");

	/*
	 * XXX how big should our hash be?
	 *
	 */
	lkm_hashinit(LKM_HASHSIZ);
	strcpy(executablename, name);

	dprintf("%s: hash initialized\n", __func__);

	/*
	 * Load the main executable.
	 */
	binary = lkm_findbinary(executablename);
	exec = (char *)binary.start;
	ehdr = (struct Elf32_Header *)exec;

	dprintf("%s: found binary %s\n", 
	    __func__,
	    executablename);

	if (elf_checkFile(ehdr) < 0)
		L4_KDB_Enter("exec not elf");

	ensections = elf_getNumSections(ehdr);
	/*
	 * Grab things of interest.
	 *
	 */
	for (i = 0; i < ensections; i++) {
		if (strcmp(".symtab", elf_getSectionName(ehdr, i)) == 0) {
			esymhdr = elf32_getSectionTable(ehdr) + i;
			esyms = (Elf32_Sym *)(esymhdr->sh_offset + exec);
			break;
		}
	}

	if (!esymhdr)
		L4_KDB_Enter("exec no sym");

	ensyms = esymhdr->sh_size / esymhdr->sh_entsize;
	estrtab = (char *)elf32_getSectionNamed(ehdr, ".strtab");

	for (i = 0; i < ensyms; i++) {
		lkm_hashput(esyms->st_name + estrtab, esyms->st_value);
		esyms++;
	}

	dprintf("%s: initialized\n", __func__);
}

/*
 * XXX REMOVE ME XXX
 */
#define roundup(x, y)	(((x) + ((y)-1)) & ~((y) - 1))

int
lkm_load(name, ename, entry)
	const char 	*name;
	const char	*ename;
	uintptr_t	*entry;
{
	struct Elf32_Header	*mhdr;
	struct Elf32_Shdr	*shdr;
	struct Elf32_Shdr	*msymhdr;
	Elf32_Sym		*msyms;
	mbi_module_t		binary;
	char			*mod;
	char			*mstrtab;
	char			*tmp;
	uint32_t		mnsections;
	uint32_t		offset, roffset, woffset;
	uintptr_t		bsssiz, roregion, rwregion;
	uintptr_t		mstart, bssptr, bssstart;
	memsection_ref_t	ref;
	int			mnsyms;
	int			mnrelocs;
	int			i;

	binary = lkm_findbinary(name);
	mod = (char *)binary.start;
	mhdr = (struct Elf32_Header *)mod;
	
	if (elf_checkFile(mod) < 0)
		L4_KDB_Enter("module not elf");

	/*
	 * Unfortunately, we do not know how much space we must reserve,
	 * we must work it out.  I guess we can just test for the ALLOC flag? 
	 */
	roregion = rwregion = 0;
	mnsections = elf_getNumSections(mhdr);

	for (i = 0; i < mnsections; i++) {
		shdr = elf32_getSectionTable(mhdr) + i;
		if (shdr->sh_flags & SHF_ALLOC) {
			if (shdr->sh_flags & SHF_WRITE)
				rwregion = roundup(rwregion + shdr->sh_size,
				    shdr->sh_addralign);
			else
				roregion = roundup(roregion + shdr->sh_size,
				    shdr->sh_addralign);
		}
		if (strcmp(".symtab", elf_getSectionName(mhdr, i)) == 0) {
			msymhdr = shdr;
			msyms = (Elf32_Sym *)(msymhdr->sh_offset + mod);
			continue;
		}
		if (strcmp(".strtab", elf_getSectionName(mhdr, i)) == 0) {
			mstrtab = mod + shdr->sh_offset;
			continue;
		}
		/*
		 * XXX what if there are others that need relocation?
		 */
		if (strcmp(".rel.text", elf_getSectionName(mhdr, i)) == 0) {
			mnrelocs = shdr->sh_size / shdr->sh_entsize;
			continue;
		}
	}

	mnsyms = msymhdr->sh_size / msymhdr->sh_entsize;
	/*
	 * Stuff in common is going to need space, we need to provision
	 * for that.  That would probably be .bss.
	 */
	for (bsssiz = 0, i = 0; i < mnsyms; i++) {
		if ((msyms + i)->st_shndx == SHN_COMMON) {
			bsssiz = roundup(bsssiz + (msyms + i)->st_value,
			    (msyms + i)->st_value);
			rwregion = roundup(rwregion + (msyms + i)->st_value,
			    (msyms + i)->st_value);
		}
	}

	/*
	 * XXX: For now, do this.  We should probably separate out
	 * XXX: the r/o region and the r/w region.  But Iguana doesn't
	 * XXX: care anyway, since it maps you memory that's rwx.
	 */
	ref = memsection_create(roundup(roregion, 0x1000) + 
	    roundup(rwregion, 0x1000), &mstart);
	if (!mstart)
		L4_KDB_Enter("no vm");

	dprintf("%s: reserved %d bytes for modules\n",
	    __func__,
	    (int)(roundup(roregion, 0x1000) + roundup(rwregion, 0x1000)));
	/*
	 * Do the copy
	 *
	 */
	for (tmp = (char *)mstart, roffset = 0, 
	    woffset = roundup(roregion, 0x1000),
	    i = 0; i < mnsections; i++) {

		shdr = elf32_getSectionTable(mhdr) + i;
		offset = shdr->sh_offset;
		dprintf("%s: start to copy at %p\n",
		    __func__,
		    (void *)(mod + offset));

		if (shdr->sh_flags & SHF_ALLOC) {
			if (shdr->sh_flags & SHF_WRITE) {
				memcpy((void *)(mstart + woffset),
				    mod + offset, shdr->sh_size);
				dprintf("%s: copying W to %p (%d/%d bytes)\n",
				    __func__, 
				    (void *)(mstart + woffset),
				    shdr->sh_size,
				    shdr->sh_addralign);
				woffset = roundup(woffset + shdr->sh_size,
				    shdr->sh_addralign);
			} else {
				memcpy((void *)(mstart + roffset), 
				    mod + offset, shdr->sh_size);
				dprintf("%s: copying R to %p (%d bytes)\n",
				    __func__, 
				    (void *)(mstart + roffset),
				    (int)(shdr->sh_size));
				roffset = roundup(roffset + shdr->sh_size,
				    shdr->sh_addralign);
			}
		}
	}

	/*
	 * When we fall through to here, the common stuff can be tacked on
	 * the end.  The start of the bss is this.  It is the roregion + 
	 * rwregion + mstart, minus the size of the bss.
	 *
	 * The r/o region needs to be rounded up, but the bss sits on the
	 * rw region, and hence does not need to be rounded up since it
	 * is on the same memory map with the same protection.
	 */
	bssstart = bssptr = mstart + roundup(roregion, 0x1000) + 
	    rwregion - bsssiz;

	dprintf("%s: bssstart is %p\n", 
	    __func__,
	    (void *)bssptr);

	/*
	 * Now, really do the relocations and patch-ups.
	 */
	lkm_arch_patch(mhdr, mnsections, mstart, &bssptr, 
	    msyms, mnsyms, mnrelocs, mstrtab);

	/*
	 * Add whatever symbols we have to the global hash.
	 */

	/*
	 * First, reset the bssptr
	 */
	bssptr = bssstart;
	for (i = 0; i < mnsyms; i++) {

		/*
		 * Not global, so we do not care.
		 */
		if (!(ELF32_ST_BIND((msyms + i)->st_info) & STB_GLOBAL))
			continue;

		/*
		 * Do a "mini relocation" here.
		 *
		 * st_value is an offset from the start
		 * of the section.
		 */
		switch (ELF32_ST_TYPE((msyms + i)->st_info)) {
			case STT_OBJECT:
				if ((msyms + i)->st_shndx == SHN_COMMON) {
					/*
				 	 * BSS
					 */
					lkm_hashput((msyms + i)->st_name + 
					    mstrtab, 
					    bssptr);
					/*
					 * round up to our alignment first
					 */
					bssptr = roundup(bssptr, 
					    (msyms + i)->st_value);
					dprintf("%s: %s -> 0x%lx\n", 
					    __func__,
					    (msyms + i)->st_name + mstrtab,
					    (unsigned long)bssptr);
					/*
					 * Now, really reserve space for it.
					 */
					bssptr += (msyms + i)->st_value;
				} else {
					lkm_hashput((msyms + i)->st_name + 
					    mstrtab,
					    mstart + 
					    roundup(roregion, 0x1000) + 
					    (msyms + i)->st_value);
					dprintf("%s: %s -> 0x%lx\n", 
					    __func__,
					    (msyms + i)->st_name + mstrtab,
					    (unsigned long)(mstart + 
					    roundup(roregion, 0x1000) + 
					    (msyms + i)->st_value));
				}
				break;
			case STT_FUNC:
				/*
				 * text
				 */
				lkm_hashput((msyms + i)->st_name + mstrtab,
				    mstart + (msyms + i)->st_value);
				dprintf("%s: %s -> 0x%lx\n", 
				    __func__,
				    (msyms + i)->st_name + mstrtab,
				    (unsigned long)(mstart + 
				    (msyms + i)->st_value));
				break;
			default:
				/* uhh, what? */
				continue;/*FORLOOP*/
		}

	}

	/*
	 * Finally: find the named entry point.
	 */
	for (i = 1; i < mnsyms; i++) {
		if (strcmp((msyms + i)->st_name + mstrtab, ename) == 0) {
			*entry = (msyms + i)->st_value + mstart;
			break;
		}
	}

	return (ELKMSUCCESS);
}

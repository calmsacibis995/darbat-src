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
 * i386_reloc.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <lkm/lkm.h>
#include <stdio.h>
#include <string.h>

#include <l4/kdebug.h>

/*
 * XXX REMOVE ME XXX
 */
#define roundup(x, y)	(((x) + ((y)-1)) & ~((y) - 1))

static uint32_t lkm_arch_findoffset(struct Elf32_Header	*, int, int);
static void lkm_arch_patchlocal(struct Elf32_Header *, int, uintptr_t, 
				uintptr_t *, Elf32_Sym *, int, uint32_t *);
static int lkm_arch_patchundef(uintptr_t, char *, int, uint32_t *);

static uint32_t
lkm_arch_findoffset(mhdr, nsections, idx)
	struct Elf32_Header	*mhdr;
	int			nsections;
	int			idx;
{
	struct Elf32_Shdr	*shdr;
	int			i;
	int			writable;
	uint32_t		rsiz, siz;

	/*
	 * What are we, ourselves?  If we are a writable section,
	 * we need to parse all the readable sections first, then
	 * round up to the next page size.
	 *
	 * If we are readable, then we just say OK, give me everything
	 * that is before us.
	 */
	shdr = elf32_getSectionTable(mhdr);
	if ((shdr + idx)->sh_flags & SHF_WRITE)
		writable = 1;
	else
		writable = 0;

	dprintf("%s: sect %d writable %d\n",
	    __func__,
	    idx,
	    writable);

	for (rsiz = siz = 0, i = 0; i < nsections; i++) {
		if (shdr->sh_flags & SHF_ALLOC) {
			if (shdr->sh_flags & SHF_WRITE) {
				/*
				 * If we want a writable section, we want
				 * the rest of the r/o sections that come
				 * after us, but we do not want the
				 * r/w sections that come after us 
				 * since they would be copied after us.
				 *
				 * If we want the index of a r/o section,
				 * then we don't do this (then siz ends
				 * up being zero), since the r/o sections
				 * always fall before the r/w ones in 
				 * our LKM memory layout.
				 */
				dprintf("writable %d i = %d idx = %d, "
				    "siz %d\n", writable, i, idx, (int)siz);
				if (writable) {
					if (i >= idx)
						goto nextone;
				}
				siz += roundup(shdr->sh_size, 
				    shdr->sh_addralign);
			} else {

				/*
				 * For rsiz, we only do up to the 
				 * section we want.  (Since we assume
				 * ascending.	While for writable we must
				 * do all since all the r/o come before the
				 * r/w.
				 */
				if (!writable) {
					if (i >= idx)
						break;
				}

				rsiz += roundup(shdr->sh_size,
				    shdr->sh_addralign);
			}
		}
nextone:
		shdr++;
	}

	if (writable) 
		return roundup(rsiz, 0x1000) + siz;
	else
		return rsiz;
}

static void
lkm_arch_patchlocal(mhdr, mnsections, mstart, bssptr, sym, rtype, addr)
	struct Elf32_Header	*mhdr;
	int			mnsections;
	uintptr_t		mstart;
	uintptr_t		*bssptr;
	Elf32_Sym		*sym;
	int			rtype;
	uint32_t		*addr;
{
	int			type;
	uint32_t		offset;
	int32_t			val;

	type = ELF32_ST_TYPE(sym->st_info);

	switch (type) {
		case STT_SECTION:
			/*
			 * Here the st_shndx is actually an index into
		 	 * the section containing actual data.  We poke
			 * int that section here.
			 *
			 * The offset may be in the location itself as 
			 * an addend.
			 */
			if (rtype != R_386_32)
				L4_KDB_Enter("oops");
			if (sym->st_shndx == SHN_COMMON) {
				/*
				 * First round up to our required alignment
				 */
				*bssptr = roundup(*bssptr, sym->st_value);
				/*
				 * tack it on 
				 */
				*addr = *bssptr;
				/*
				 * finally , actually reserve space for it
				 */
				(*bssptr) += sym->st_value;
				dprintf("%s: in bss bssptr %p\n",
				    __func__, 
				    (void *)*bssptr);
				val = 0;
			} else {
				offset = lkm_arch_findoffset(mhdr, mnsections,
			 	    sym->st_shndx);
				val = *(int32_t *)addr;
				*addr = mstart + offset + val;
			}
			dprintf("%s: patching addr %p with "
			    "0x%lx at sect %d offset %d (STT_SECTION)\n",
			    __func__,
			    (void *)addr,
			    (unsigned long)*addr,
			    (int)sym->st_shndx,
			    (int)offset);
			break;
		case STT_OBJECT:
			/*
			 * This is an object.
			 *
			 * The offset is in st_value, except for SHN_COMMON
			 * stuff which have not yet been allocated.  For
			 * this we have a special case.
			 */
			if (rtype != R_386_32)
				L4_KDB_Enter("oops1");
			if (sym->st_shndx == SHN_COMMON) {
				*bssptr = roundup(*bssptr, sym->st_value);
				*addr = *bssptr;
				(*bssptr) += sym->st_value;
				dprintf("%s: in bss bssptr %p\n",
				    __func__ ,(void *)*bssptr);
				val = 0;
			} else {
				offset = lkm_arch_findoffset(mhdr, 
				    mnsections, sym->st_shndx);
			/*
			 * XXX: What bout the addend?  Is that required?
			 */
				val = sym->st_value;
				*addr = mstart + offset + val;
			}
			dprintf("%s: patching addr %p with "
			    "0x%lx offset 0x%lx sect %d offset %d"
			    "addend %lu (STT_OBJECT)\n",
			    __func__,
			    (void *)addr,
			    (unsigned long)*addr,
			    (unsigned long)offset,
			    (int)sym->st_shndx,
			    (int)offset,
			    (long)val);
			break;
		case STT_FUNC:
			if (rtype != R_386_PC32)
				L4_KDB_Enter("oops2");
			*addr = (uint32_t)(mstart + sym->st_value - 
			    (uint32_t)addr + 
			    *(int32_t *)addr);
			dprintf("%s: patching addr %p with "
			    "0x%lx (STT_FUNC)\n",
			    __func__,
			    (void *)addr,
			    (unsigned long)*addr);
			break;
		case STT_FILE:
			/*
			 * This should be ABS
			 */
			break;
		default:
			dprintf("%s: has type %d (ignore)\n",
			    __func__,
			    type);
			break;
	}
}

static int
lkm_arch_patchundef(mstart, sym, rtype, addr)
	uintptr_t	mstart;
	char		*sym;
	int		rtype;
	uint32_t	*addr;
{
	uint32_t	value;
	int		rc;

	rc = lkm_hashget(sym, &value);
	/*
	 * XXX we should have a way to return an error code here
	 */
	if (rc != ELKMSUCCESS) {
		dprintf("%s: found undefined symbol %s\n", 
		    __func__,
		    sym);
		return rc;
	}
	
	switch (rtype) {
		case R_386_PC32:
			*addr = value - (uint32_t)addr + *(int32_t *)addr;
			dprintf("%s: patched %p with "
			    "0x%lx (pc32)\n",
			    __func__,
			    (void *)addr,
			    (unsigned long)*addr);
			break;
		case R_386_32:
			*addr = value;
			break;
		default:
			dprintf("%s: bad type of reloc for "
			    "i386\n",
			    __func__);
			break;
	}

	return ELKMSUCCESS;
}

void
lkm_arch_patch(mhdr, mnsections, mstart, bssptr, msyms, mnsyms, nrelocs, 
		mstrtab)
	struct Elf32_Header	*mhdr;
	int			mnsections;
	uintptr_t		mstart;
	uintptr_t		*bssptr;
	Elf32_Sym		*msyms;
	int			mnsyms;
	int			nrelocs;
	char			*mstrtab;
{
	Elf32_Sym	*sptr;
	Elf32_Rel	*rel;
	int		symidx;
	uint32_t	*patch;
	int		i;
	int		rtype;

	/*
	 * XXX only handle text relocations for now.
	 */
	rel = elf_getSectionNamed(mhdr, ".rel.text");
	if (!rel)
		L4_KDB_Enter("no rel");

	sptr = msyms;
	for (i = 0; i < nrelocs; i++) {
		/*
		 * Let's see what type of symbol we need to relocate.
		 *
		 */
		rtype = ELF32_R_TYPE(rel->r_info);
		symidx = ELF32_R_SYM(rel->r_info);
		patch = (uint32_t *)(mstart + rel->r_offset);
		sptr = msyms + symidx;

		switch (sptr->st_shndx) {

			case SHN_UNDEF:		/* Undefined */
				lkm_arch_patchundef(mstart, 
				    sptr->st_name + mstrtab, 
				    rtype, 
				    patch);
				break;
			case SHN_ABS:		/* No relocation */
				/*
				 * Well, I lied.  You still need to offset
				 * it by the start of the module.
				 *
				 * XXX FIXME
				 */
				break;
			case SHN_COMMON:	/* Common data */
				/*FALLTHROUGH*/
			default:
				lkm_arch_patchlocal(mhdr, mnsections, mstart, 
				    bssptr, sptr, rtype, patch);
				break;
		}

		rel++;
	}

	return;
}

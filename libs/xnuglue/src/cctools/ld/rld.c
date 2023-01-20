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
 * rld.c
 *
 */

#include <stdio.h>
#include <string.h>

#include <mach-o/fat.h>
#include <mach-o/kld.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/reloc.h>

#include <l4/kdebug.h>
#if 0
#include <mach-o/mach-o.h>	/* Ig Mach-O library */
#endif
#include <lkm/lkm.h>		/* Loadable kernel module library */
#include <l4/thread.h>		/* XXX: ugg */
#include <iguana/memsection.h>

/*
 * XXX REMOVE ME XXX
 */
#define roundup(x, y)	(((x) + ((y)-1)) & ~((y) - 1))

/*
 * The user's address function to be called in layout to get the address of
 * where to link edit the result.
 */
unsigned long (*address_func)(unsigned long size, unsigned long headers_size) =
                                                                           NULL;

void
kld_address_func(
unsigned long (*func)(unsigned long size, unsigned long headers_size))
{
        address_func = func;
}

long
kld_forget_symbol(
    const char *symbol_name)
{
	if (lkm_hashdelete(symbol_name) != ELKMSUCCESS)
		return (0);
	else
		return (1);
}

/*
 * XXX: right now, this cannot deal with fat binaries.  This will
 * XXX: need to be fixed soon-ish, but we can always use lipo(1) 
 * XXX: to make an i386-only binary.
 */
long
kld_load_from_memory(
struct mach_header **header_addr,
const char *object_name,
char *object_addr,
long object_size)
{
	struct mach_header	*mh = (struct mach_header *)object_addr;
	struct segment_command	*sc;
#if 0
	struct symtab_command	*symcmd = NULL;
	struct nlist		*syms = NULL;
	char			*strtab = NULL;
#endif
	uintptr_t		addr;
	uintptr_t		dummy;	/* dummy: in kmod_info structure */
	uint32_t		i, vmsiz;

	/*
	 * Set this to one if you want it to succeed.
	 *
	 * the load address is returned via header_addr.
	 */
	if (mh->magic == FAT_MAGIC || mh->magic == FAT_CIGAM) {
		printf("%s: fat files not supported for now\n", __func__);
		goto err;
	}

	if (mh->magic != MH_MAGIC) {
		printf("%s: not of type MH_MAGIC\n", __func__);
		goto err;
	}

	if (mh->filetype != MH_OBJECT) {
		printf("%s: filetype not MH_OBJECT\n", __func__);
		goto err;
	}

	sc = (struct segment_command *)(mh + 1);
	/*
	 * First, account for the size of the headers.
	 */
	vmsiz = roundup(mh->sizeofcmds, 0x1000);	/* XXX */
	for (i = 0; i < mh->ncmds; i++) {
		/*
		 * Object files do not have __PAGEZERO.
		 */
		if (sc->cmd != LC_SEGMENT)
			goto next1;

		vmsiz += sc->vmsize;
next1:
		sc = (struct segment_command *)((char *)sc + sc->cmdsize);
	}
	/*
	 * First find out how much space we will need.  This can be done
	 * by adding up the LC_SEGMENT vmsizes.
	 */
#if 0
	vmsiz = roundup(vmsiz, 0x1000/*XXX*/);
	ref = memsection_create(vmsiz, &addr);
	if (!ref) {
		printf("%s: cannot create vm\n", __func__);
		goto err;
	}
#endif

	addr = address_func(vmsiz, mh->sizeofcmds);

#ifdef VERBOSE_IOKIT
	printf("%s: address_func returned %p\n", __func__, (void *)addr);
#endif
	if (!addr)
		return (0);

	/*
	 * Pass this back to the caller.
	 */
	*header_addr = (struct mach_header *)addr;

	printf("%s: header at %p\n", __func__, (void *)addr);
	/*
	 * it seems for MH_OBJECT types we need to copy the
	 * header directly.  So let's do that.
	 */
	memcpy((void *)addr, object_addr, mh->sizeofcmds);
	addr += mh->sizeofcmds;

	printf("%s: code at %p\n", __func__, (void *)addr);

	/*
	 * XXX: should use liblkm to do this.
	 */
	if (lkm_load_macho(mh, "__start", &dummy, addr) != ELKMSUCCESS)
		L4_KDB_Enter("oops");
#if 0	/* liblkm's job */
	sc = (struct segment_command *)(mh + 1);
	for (i = 0; i < mh->ncmds; i++) {
		/*
		 * Object files do not have __PAGEZERO.
		 */

		/*
		 * Say, Hellllloo, segment symtab.
		 * "Heeeellloooooo, segment symtab."
		 */
		if (sc->cmd == LC_SYMTAB) {
			symcmd = (struct symtab_command *)sc;
			syms = (struct nlist *)(symcmd->symoff + object_addr);
			strtab = (char *)(symcmd->stroff + object_addr);
			break;
		}
		sc = (struct segment_command *)((char *)sc + sc->cmdsize);
	}

	sc = (struct segment_command *)(mh + 1);
	for (i = 0; i < mh->ncmds; i++) {
		/*
		 * Object files do not have __PAGEZERO.
		 */
		if (sc->cmd != LC_SEGMENT)
			goto next2;

		printf("copying segment %s src %p => dst %p siz %d\n",
		    sc->segname, (void *)(addr + sc->vmaddr),
		    object_addr + sc->fileoff, (int)sc->filesize);
		memcpy((void *)(addr + sc->vmaddr), object_addr + sc->fileoff,
		    sc->filesize);
		/*
		 * zero the rest.
		 */
		if (sc->vmsize - sc->filesize)
			memset((void *)(addr + sc->vmaddr + sc->filesize), 0,
			    sc->vmsize - sc->filesize);

next2:
		sc = (struct segment_command *)((char *)sc + sc->cmdsize);
	}

	/*
	 * Add the symbols into the symbol table.
	 */

	printf("%s: adding symbols\n", __func__);
	printf("%s: nlist at %p strtab at %p\n", __func__, syms, strtab);

	for (i = 0; i < symcmd->nsyms; i++) {
		if (strcmp(syms[i].n_un.n_strx + strtab, "_kmod_info") == 0)
			printf("added kmod_info 0x%lx\n", addr + 
			    syms[i].n_value);
		/*
		 * Watch out for this: this will depend on whether
		 * the kld_lookup() function excepts a raw n_value
		 * or one which we patched up.
		 *
		 * At this momemnt I am not yet sure.  Will need to
		 * revisit later on.
		 *
		 * XXX MARK XXX
		 *
		 * -gl 
		 */
		lkm_hashput(syms[i].n_un.n_strx + strtab, 
		    addr + syms[i].n_value);
	}
#endif	/* liblkm's job */

	printf("%s: done (tid = 0x%lx)\n", __func__, L4_Myself().raw);

	return (1);
err:
	return (0);
}


long
kld_lookup(
    const char *symbol_name,
    unsigned long *value)
{

	if (lkm_hashget(symbol_name, (uint32_t *)value) != ELKMSUCCESS)
		return (0);
	return (1);
}

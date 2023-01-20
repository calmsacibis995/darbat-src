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
 * lkm.h
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#ifndef _LKM_H
#define _LKM_H

#include <lkm/mbi.h>

#include <elf/elf.h>
#include <mach-o/mach-o.h>

/*
 * Define this if you want extra ugly output debug information.
 *
 */
#if 0
#define dprintf(args...)	printf(args)
#else
#define dprintf(args...)
#endif

#define ELKMSUCCESS	0	/* all's right */
#define ELKMNOMOD	1	/* no such module */
#define ELKMBADFILE	2	/* Not a valid object executable */
#define ELKMNOSYM	3	/* Cannot find sym specified */
#define ELKMSYMEXISTS	4	/* Symbol already defined */
#define ELKMNOMEM	5	/* Out of core */

#define LKM_HASHSIZ	(32768)	/* XXX: How big should this be? */

/*
 * XXX REMOVE ME XXX
 *
 * should be in libelf
 *
 * References: ELF: Executable and Linking Format
 */

typedef struct {
	uint32_t	st_name;
	uint32_t	st_value;
	uint32_t	st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	uint16_t	st_shndx;
} Elf32_Sym;

#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

#define STN_UNDEF	0

#define STB_LOCAL	0
#define STB_GLOBAL	1
#define STB_WEAK	2
#define STB_LOPROC	13
#define STB_HIPROC	15

#define STT_NOTYPE	0
#define STT_OBJECT	1
#define	STT_FUNC	2
#define	STT_SECTION	3
#define STT_FILE	4
#define STT_LOPROC	13
#define STT_HIPROC	15

#define ELF32_ST_BIND(i)	((i) >> 4)
#define ELF32_ST_TYPE(i)	((i) & 0xf)
#define ELF32_ST_INFO(b,t)	((b) << 4) + ((t) & 0xf))

typedef struct {
	uint32_t	r_offset;
	uint32_t	r_info;
} Elf32_Rel;

typedef struct {
	uint32_t	r_offset;
	uint32_t	r_info;
	uint32_t	r_addend;
} Elf32_Rela;


#define ELF32_R_SYM(i)		((i) >> 8)
#define ELF32_R_TYPE(i)		((unsigned char)(i))
#define ELF32_R_INFO(s,t)	(((s) << 8) + (unsigned char)(t))

/*
 * Relocation types
 *
 * XXX PROCESSOR SPECIFIC XXX
 */

#define R_386_NONE	0
#define	R_386_32	1
#define	R_386_PC32	2
#define	R_386_GOT32	3
#define R_386_PLT32	4
#define R_386_COPY	5
#define R_386_GLOB_DAT	6
#define	R_386_JMP	7
#define	R_386_RELATIVE	8
#define	R_386_GOTOFF	9
#define	R_386_GOTPC	10

#ifdef __cplusplus
extern "C" {
#endif

char	*lkm_getexec(void);	/* XXX */
mbi_module_t	lkm_findbinary(const char *);
void	lkm_init(const char *);
void	lkm_fini(void);
int	lkm_load(const char *, const char *, uintptr_t *);
void	lkm_arch_patch(struct Elf32_Header *, int, uintptr_t, uintptr_t *,
			Elf32_Sym *, int, int, char *);
/*
 * XXX
 *
 */
uint32_t elf_hash(const char *);

mbi_module_t	lkm_findmodule(const char *);

/*
 * Mach-O stuff
 *
 */
int	lkm_macho_init(void);
int	lkm_loadsymtab(struct mach_header *, struct symtab_command *,
			const char *, uintptr_t *, uintptr_t *);
int	lkm_loadsegment(struct mach_header *, struct segment_command *,
			struct symtab_command *, uintptr_t *, uintptr_t *,
			uintptr_t);
int	lkm_load_macho(struct mach_header *, const char *, uintptr_t *,
			uintptr_t);
int	lkm_machoreloc(struct mach_header *, struct segment_command *, 
			struct section *, struct symtab_command *, 
			char *, uintptr_t *);
int	lkm_macho_resolve(const char *, struct section *,
			struct relocation_info *, const char *);
int	lkm_macho_symput(struct mach_header *, struct symtab_command *,
			uintptr_t, uintptr_t);
/*
 * symbol hashing
 *
 */
int	lkm_hashinit(uint32_t);
int	lkm_hashput(const char *, uint32_t);
int	lkm_hashget(const char *, uint32_t *);
int	lkm_hashdelete(const char *);
int	lkm_hashfini(void);


#ifdef __cplusplus
};
#endif

#endif	/* _LKM_H */

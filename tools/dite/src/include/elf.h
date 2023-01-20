#ifndef DITE_ELF_H
#define	DITE_ELF_H 1

#include <stdint.h>
#include "edit_types.h"

/* Elf structures from lib/elf/include/elf*.h.
 * FIXME: Dite should really just use the structures directly. 
*/

/*
 * File header 
 */
typedef struct {
	unsigned char   e_ident[16];
	uint16_t        e_type;	/* Relocatable=1, Executable=2 (+ some
				 * more ..) */
	uint16_t        e_machine;	/* Target architecture: MIPS=8 */
	uint32_t        e_version;	/* Elf version (should be 1) */
	uint32_t        e_entry;	/* Code entry point */
	uint32_t        e_phoff;	/* Program header table */
	uint32_t        e_shoff;	/* Section header table */
	uint32_t        e_flags;	/* Flags */
	uint16_t        e_ehsize;	/* ELF header size */
	uint16_t        e_phentsize;	/* Size of one program segment
					 * header */
	uint16_t        e_phnum;	/* Number of program segment
					 * headers */
	uint16_t        e_shentsize;	/* Size of one section header */
	uint16_t        e_shnum;	/* Number of section headers */
	uint16_t        e_shstrndx;	/* Section header index of the
					 * string table for section header 
					 * * names */
} Elf32_Ehdr;

typedef struct{
	unsigned char   e_ident[16];
	uint16_t        e_type;	/* Relocatable=1, Executable=2 (+ some
				 * more ..) */
	uint16_t        e_machine;	/* Target architecture: MIPS=8 */
	uint32_t        e_version;	/* Elf version (should be 1) */
	uint64_t        e_entry;	/* Code entry point */
	uint64_t        e_phoff;	/* Program header table */
	uint64_t        e_shoff;	/* Section header table */
	uint32_t        e_flags;	/* Flags */
	uint16_t        e_ehsize;	/* ELF header size */
	uint16_t        e_phentsize;	/* Size of one program segment
					 * header */
	uint16_t        e_phnum;	/* Number of program segment
					 * headers */
	uint16_t        e_shentsize;	/* Size of one section header */
	uint16_t        e_shnum;	/* Number of section headers */
	uint16_t        e_shstrndx;	/* Section header index of the
					 * string table for section header 
					 * * names */
} Elf64_Ehdr;

#define ELF_MAGIC_0 0x7f
#define ELF_MAGIC_1	'E'
#define ELF_MAGIC_2	'L'
#define ELF_MAGIC_3	'F'

#define EI_CLASS	4
#define ELFCLASS32	1
#define ELFCLASS64	2

#define EI_DATA		5
#define ELFDATA2LSB	1
#define ELFDATA2MSB	2

#define EI_VERSION	6

#define ET_NONE		0
#define ET_REL		1
#define ET_EXEC		2
#define ET_DYN		3
#define ET_CORE		4
#define	ET_NUM		5
#define ET_LOPROC	0xff00
#define ET_HIPROC	0xffff


#define EM_NONE		 0
#define EM_SPARC	 2
#define EM_386		 3
#define EM_MIPS		 8
#define EM_MIPS_RS4_BE	10

#define EM_SPARC32PLUS	18
#define EM_POWERPC64	21
#define EM_ARM		40
#define EM_FAKE_ALPHA	41
#define EM_SPARCV9	43
#define EM_IA_64	50

#define EM_ALPHA	0x9026

#define EV_NONE		0
#define EV_CURRENT	1
#define EV_NUM		2

#define SHN_UNDEF       0

/*
 * Section header 
 */
typedef struct {
	uint32_t        sh_name;
	uint32_t        sh_type;
	uint32_t        sh_flags;
	uint32_t        sh_addr;
	uint32_t        sh_offset;
	uint32_t        sh_size;
	uint32_t        sh_link;
	uint32_t        sh_info;
	uint32_t        sh_addralign;
	uint32_t        sh_entsize;
} Elf32_Shdr ;
 

typedef struct {
	uint32_t        sh_name;
	uint32_t        sh_type;
	uint64_t        sh_flags;
	uint64_t        sh_addr;
	uint64_t        sh_offset;
	uint64_t        sh_size;
	uint32_t        sh_link;
	uint32_t        sh_info;
	uint64_t        sh_addralign;
	uint64_t        sh_entsize;
}Elf64_Shdr;

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_NOBITS 8

#define SHF_ALLOC (1 << 1)

/*
 * Program header 
 */
typedef struct {
	uint32_t p_type;	/* Segment type: Loadable segment = 1 */
	uint32_t p_offset;	/* Offset of segment in file */
	uint32_t p_vaddr;	/* Reqd virtual address of segment 
					 * when loading */
	uint32_t p_paddr;	/* Reqd physical address of
					 * segment (ignore) */
	uint32_t p_filesz;	/* How many bytes this segment
					 * occupies in file */
	uint32_t p_memsz;	/* How many bytes this segment
					 * should occupy in * memory (when 
					 * * loading, expand the segment
					 * by * concatenating enough zero
					 * bytes to it) */
	uint32_t p_flags;	/* Flags: logical "or" of PF_
					 * constants below */
	uint32_t p_align;	/* Reqd alignment of segment in
					 * memory */
}Elf32_Phdr;

typedef struct {
	uint32_t        p_type;	/* Segment type: Loadable segment = 1 */
	uint32_t        p_flags;	/* Flags: logical "or" of PF_
					 * constants below */
	uint64_t        p_offset;	/* Offset of segment in file */
	uint64_t        p_vaddr;	/* Reqd virtual address of segment 
					 * when loading */
	uint64_t        p_paddr;	/* Reqd physical address of
					 * segment */
	uint64_t        p_filesz;	/* How many bytes this segment
					 * occupies in file */
	uint64_t        p_memsz;	/* How many bytes this segment
					 * should occupy in * memory (when 
					 * * loading, expand the segment
					 * by * concatenating enough zero
					 * bytes to it) */
	uint64_t        p_align;	/* Reqd alignment of segment in
					 * memory */
}Elf64_Phdr;

/* p_type */

#define	PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define	PT_NUM		7
#define PT_LOOS		0x60000000
#define PT_HIOS		0x6fffffff
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

/* p_flags */

#define PF_X		(1 << 0)
#define PF_W		(1 << 1)
#define PF_R		(1 << 2)
#define PF_MASKPROC	0xf0000000

/* MIPS architecture */

#define EF_MIPS_ARCH_1 0x00000000
#define EF_MIPS_ARCH_2 0x10000000
#define EF_MIPS_ARCH_3 0x20000000
#define EF_MIPS_ARCH_4 0x30000000
#define EF_MIPS_ARCH_5 0x40000000

/* p_type for MIPS  */

#define PT_MIPS_REGINFO	0x70000000
#define PT_MIPS_RTPROC  0x70000001
#define PT_MIPS_OPTIONS 0x70000002

#define PF_MIPS_LOCAL	0x10000000

#endif	/* DITE_ELF_H */

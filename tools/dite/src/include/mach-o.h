/*
 * mach-o.h
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 *
 * XXX THIS IS INCOMPLETE XXX
 * XXX These headers are not 64-bit clean!
 */

#ifndef _LIBMACHO_
#define _LIBMACHO_

#ifdef __cplusplus
extern "C" {
#endif

#define EMACHOSUCCESS	0
#define EMACHOBADFILE	1

#if 1
#define dprintf(args...)	printf(args)
#else
#deifne dprintf(args...)
#endif


/* Constant for the magic field of the mach_header */
#define MH_MAGIC        0xfeedface
#define MH_CIGAM        0xcefaedfe

#define MH_OBJECT	0x1


typedef int		cpu_type_t;	/* integer_t */
typedef int		cpu_subtype_t;	/* integer_t */

/*
 * The mach header appears at the very beginning of the object file.
 */
struct mach_header {
        unsigned long   magic;
        cpu_type_t      cputype;
        cpu_subtype_t   cpusubtype;
        unsigned long   filetype;
        unsigned long   ncmds;
        unsigned long   sizeofcmds;
        unsigned long   flags;
};

struct load_command {
        unsigned long cmd;
        unsigned long cmdsize;
};

/*
 * XXX
 *
 * We only care about LKMs for now.  So far only these have been observed
 * in Mach-O MH_OBJECTs.
 */
#define LC_SEGMENT		0x1
#define LC_SYMTAB		0x2


struct segment_command {
        unsigned long   cmd;
        unsigned long   cmdsize;
        char            segname[16];
        unsigned long   vmaddr;
        unsigned long   vmsize;
        unsigned long   fileoff;
        unsigned long   filesize;
        int/*vm_prot_t*/	maxprot;
        int/*vm_prot_t*/	initprot;
        unsigned long   nsects;
        unsigned long   flags;
};

struct section {
        char            sectname[16];
        char            segname[16];
        unsigned long   addr;
        unsigned long   size;
        unsigned long   offset;
        unsigned long   align;
        unsigned long   reloff;
        unsigned long   nreloc;
        unsigned long   flags;
        unsigned long   reserved1;
        unsigned long   reserved2;
};

struct symtab_command {
        unsigned long   cmd;
        unsigned long   cmdsize;
        unsigned long   symoff;
        unsigned long   nsyms;
        unsigned long   stroff;
        unsigned long   strsize;
};

struct relocation_info {
   long         r_address;
   unsigned int r_symbolnum:24,
                r_pcrel:1,
                r_length:2,
                r_extern:1,
                r_type:4;
};
#define R_ABS   0

struct nlist {
        union {
                char *n_name;
                long  n_strx;
        } n_un;
        unsigned char n_type;
        unsigned char n_sect;
        short         n_desc;
        unsigned long n_value;
};

#define N_STAB  0xe0
#define N_PEXT  0x10
#define N_TYPE  0x0e
#define N_EXT   0x01

#define N_UNDF  0x0
#define N_ABS   0x2
#define N_SECT  0xe
#define N_PBUD  0xc
#define N_INDR  0xa

#define R_SCATTERED 0x80000000

/*
 * Our decls
 *
 */
int macho_checkfile(void *);
int macho_getmachhdr(struct mach_header *, cpu_type_t *, cpu_subtype_t *,
			unsigned long *, unsigned long *, 
			unsigned long *, unsigned long *);
struct load_command *macho_getloadcmds(struct mach_header *);

/*
 * DEBUG stuff
 */
int macho_printheaders(struct mach_header *);
int macho_printloadcmds(struct mach_header *);

#ifdef __cplusplus
};
#endif

#endif	/* _LIBMACHO_ */

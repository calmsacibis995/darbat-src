/*
 * macho.c
 *
 * Dite implementation for Mach-O
 * Based on raw.c on dite.
 *
 * XXX This only handles 32-bit Mach-O files.
 * XXX This does not yet handle FAT binaries. 
 */

/*
 * What we need to get clear:
 *
 * In dite, every program segment represents, some program segment
 * set out by some policy in the original program, with PT_LOAD set.
 *
 * There are some issues with this.  First of all, in ELF the program
 * segments are unnamed whereas in Mach-O they are named.
 *
 * The second issue is we must be extra-careful in loading things.  The
 * segment themselves may describe metadata that are not in any of the 
 * sections.  For example, the first LC_SEGMENT almost always start 
 * from the beginning of the file, to pick up _mh_execute_header.  Unlike
 * ELF with a GNU toolchain, which will probably allow you to do seedy 
 * linker hacks, in Mach-O this almost certainly has to be parsed from
 * _mh_execute_header.  Not fatal, but it means that it is troublesome
 * and you must do it properly.  Perhaps they can be encoded as a bit 
 * of metadata?
 *
 * The scheme we employ is as follows: each segment (LC_SEGMENT) in Mach-O 
 * is exactly one ELF segment with PT_LOAD set.  Each of these converted
 * ELF segments contain one ELF section, namely, the LC_SEGMENT in Mach-O.
 *
 * What are we doing about symbol tables?  In order to support loadable
 * kernel modules (LKMs), the symbol tables are required, in order to
 * match up the undefined symbols with what can be used in the main
 * executable.  The symbol table is handled as follows:
 *
 * We create a special ELF segment/section called .modname.__MACHOSYMTAB.  
 * This contains the symbol table.  We also have a special section called
 * .modname.__MACHOSTRTAB.  Currently, macho.c assumes that all loadable
 * segments (LC_SEGMENT) gets specified first before any LC_SYMTAB.  If
 * this is not the case, this program will break.  This is because it 
 * tacks on a load address to both, after all of the LC_SEGMENTS.  This
 * hack is required because dite never supported symtab and * strtab 
 * (both do not usually have a LOAD set in a typical ELF file).  It would
 * be better if a raw executable was placed in the Dite boot image instead,
 * however, the current implementation refrains from doing so and does 
 * it here instead, because it will be prone to breaking in the general
 * case.  Consider the case when absolute load addresses are specified,
 * there is absolutely no guarantee that the memory region(s) is/are going
 * to be free.  Programmers who wish to make use of the symbol table will
 * have to go via this indirection, but hopefully this will not be too
 * large a price to pay, nor will it be too onerous.
 */
#include <sys/types.h>

#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "edit.h"
#include "edit_endian.h"
#include "log.h"
#include "elf_generic.h"
#include "elf.h"
#include "mach-o.h"

struct section	*macho_findsegsect(struct edit_file *, char *, char *);
int		macho_initsects(struct edit_file *);
int		macho_initsegs(struct edit_file *, struct edit_segment *);
int		macho_arch_pagesize(int);
int		macho_write(struct edit_file *, struct edit_options *opts);
int		macho_register(struct edit_file *);
uint32_t	macho_swap32(struct edit_file *efile, uint32_t val);
uint32_t	swap32(uint32_t val);
static int	get_num_sections(struct edit_file *efile);

/*
 * XXX:
 *
 * This is IA-32 specific.  However, given that we can only specify one
 * vmaddr to load, I am not quite sure what is the best way to go about
 * this.  One solution would be to alias the segments, but this would
 * require trickery.
 */
#define KERNEL_OFFSET	0xF0000000

struct section *
macho_findsegsect(struct edit_file *efile, char *segname, char *sectname)
{
	struct mach_header	*mh;
	struct segment_command	*sc;
	struct section		*sect;
	int			i, j;

	mh = efile->mmap;
	sc = (struct segment_command *)(mh + 1);

	for (i = 0; i < macho_swap32(efile, mh->ncmds); i++) {

		if (macho_swap32(efile, sc->cmd) != LC_SEGMENT)
			goto next;

		if (strcmp(sc->segname, segname))
			goto next;

		sect = (struct section *)((char *)sc + 
		    sizeof(struct segment_command));
		for (j = 0; j < macho_swap32(efile, sc->nsects); j++) {
			if (strcmp(sect->sectname, sectname) == 0)
				goto found;
			sect++;
		}
next:
		sc = (struct segment_command *)((char *)sc + 
		     macho_swap32(efile, sc->cmdsize));
	}

found:
	return (sect);
}

/*
 * Remember, a section when translated from Mach-O to ELF is really
 * a segment.  (i.e. nsegments == nsections)  Mach-O sections in LC_SEGMENT
 * do not really enter into the discussion at all.
 */
int
macho_initsects(struct edit_file *efile)
{
	struct mach_header	*mh;
	struct segment_command	*sc;
	struct symtab_command	*symcmd;
	struct nlist		*syms;
	struct edit_section	*cur, *prev;
	char			*segoff;
	uint32_t		e_shnum, e_shoff, vmend;
	int			i;
	int			segcnt;	/* Mach-O segment */

	mh = (struct mach_header *)efile->mmap;
	sc = (struct segment_command *)(mh + 1);
	segcnt = 0;
	for (i = 0; i < macho_swap32(efile, mh->ncmds); i++) {

		/*
		 * We only care about LC_SEGMENT and LC_SYMTAB.
		 */
		switch (macho_swap32(efile, sc->cmd)) {
			case LC_SEGMENT:
				break;
			case LC_SYMTAB:
//NOTYET
			default:
				goto next;
		}

		/*
		 * Do not ever load __PAGEZERO.
		 */
		if (macho_swap32(efile, sc->cmd) == LC_SEGMENT &&
		    strcmp(sc->segname, "__PAGEZERO") == 0)
			goto next;

		cur = malloc(sizeof(struct edit_section));
		cur->next = NULL;

		if (macho_swap32(efile, sc->cmd) == LC_SEGMENT) {
			(void)sprintf(cur->name, ".%s.%s", efile->ditname, 
			    sc->segname/*XXX: null terminate*/);
			/*
			 * We need SHT_PROGBITS or SHT_NOBITS to ensure that
			 * it gets added in merge_sections() in edit.c.
			 */
			cur->type = SHT_PROGBITS;
			cur->addr = macho_swap32(efile, sc->vmaddr);
			cur->orig_offset = macho_swap32(efile, sc->fileoff);
			/*
			 * Be careful here:
			 *
			 * Here we want the vm size, not the file size,
			 * even though the use of the size field implies
			 * otherwise.  The reason is because some sections
			 * zero-filled (such as bss) and we need to know about
			 * these in the sections.
			 */
			cur->size = macho_swap32(efile, sc->vmsize);
			/* a segment is page-aligned. */
			cur->addralign = elfarch_pagesize(efile->arch);
			cur->entsize = 0;	/* XXX: What about .symtab? */
			(void)cur->flags;	/* XXX: what should it be? */

			vmend = ALIGN(macho_swap32(efile, sc->vmaddr) +
			    macho_swap32(efile, sc->vmsize),
			    efile->pagesize);
		} else if (macho_swap32(efile, sc->cmd) == LC_SYMTAB) {
#ifdef NOTYET
			/*
			 * XXX!
			 *
		 	 * This assumes that LC_SYMTAB gets placed
			 * AFTER all the LC_SEGMENTS.  If this is not
			 * the case it will break!
			 */

			/*
			 * XXX
			 *
			 * This is deliberately called __MACHOSYMTAB because
			 * it is not quite the Mach-O LC_SYMTAB.
			 */
			symcmd = (struct symtab_command *)sc;

			sprintf(cur->name, ".%s.%s", efile->ditname,
			    "__MACHOSYMTAB");
			/* symtab */
			cur->type = SHT_PROGBITS;	/* XXX: symtab */
			cur->addr = vmend;		/* XXX! */
			cur->orig_offset = symcmd->stroff;
			cur->size = symcmd->nsyms * sizeof(struct nlist);
			cur->addralign = elfarch_pagesize(efile->arch);
			cur->entsize = sizeof(struct nlist);
			(void)cur->flags;	/* XXX: */

			/*
			 * Do the following couple of things manually,
			 * since in LC_SYMTAB we are really adding
			 * two sections: the symbol table and the string
			 * table.
			 */
			cur->segment_num = segcnt;
			cur->segment_offset = 0;
			if (segcnt == 0)
				efile->first_section = cur;
			else
				prev->next = cur;
			prev = cur;
			segcnt++;

			vmend += ALIGN(cur->size, efile->pagesize);

			/* strtab */
			cur = malloc(sizeof(struct edit_section));
			cur->next = NULL;
			sprintf(cur->name, ".%s.%s", efile->ditname,
			    "__MACHOSTRTAB");
			cur->type = SHT_PROGBITS;
			cur->addr = vmend;
			cur->orig_offset = symcmd->stroff;
			cur->size = symcmd->strsize;
			cur->addralign = elfarch_pagesize(efile->arch);
			cur->entsize = 0;
			(void)cur->flags;
#endif
			;
		} else {
			log(LOG_CRITICAL, "%s: oops.  should not happen\n", 
			    __func__);
			abort();
		}

		/*
		 * At this point in time, the segcnt index count
		 * variable contains the index into the number of
		 * segments we have, starting from zero.
		 */
		cur->segment_num = segcnt;
		/*
		 * always zero, since in Mach-O translation we have the
		 * policy of sect == seg
		 */
		cur->segment_offset = 0;

		if (segcnt == 0)
			efile->first_section = cur;
		else
			prev->next = cur;
		prev = cur;

		segcnt++;

next:
		sc = (struct segment_command *)((char *)sc + 
		    macho_swap32(efile, sc->cmdsize));
	}

	return (segcnt);
}

/*
 * Actually, this only gets the number of segments that we care about,
 * currently, this is LC_SEGMENT and LC_SYMTAB without __PAGEZERO.
 */
int
macho_getnsegs(struct edit_file *efile)
{
	struct mach_header	*mh;
	struct segment_command	*sc;
	int			i, segcnt;

	mh = (struct mach_header *)efile->mmap;
	sc = (struct segment_command *)(mh + 1);
	segcnt = 0;
	for (i = 0; i < macho_swap32(efile, mh->ncmds); i++) {

		/*
		 * We only care about LC_SEGMENT and LC_SYMTAB.
		 */
		switch (macho_swap32(efile, sc->cmd)) {
			case LC_SEGMENT:
				break;
			case LC_SYMTAB:
#ifdef NOTYET
				/*
				 * Do this manually: this really counts as 
				 * two in our conversion, since there is
				 * one for the symbol table and one for  
				 * the string table.
				 */
				segcnt++;
#endif
				goto next;
				break;
			default:
				goto next;
		}

		/*
		 * Do not ever load __PAGEZERO.
		 */
		if (macho_swap32(efile, sc->cmd) == LC_SEGMENT &&
		    strcmp(sc->segname, "__PAGEZERO") == 0)
			goto next;

		segcnt++;
next:
		sc = (struct segment_command *)((char *)sc + 
		    macho_swap32(efile, sc->cmdsize));
	}

	return (segcnt);
}

int
macho_initsegs(struct edit_file *efile, struct edit_segment *segments)
{
	struct mach_header	*mh;
	struct segment_command	*sc;
	struct symtab_command	*symcmd;
	struct edit_section	*cur, *prev;
	char			*segoff;
	uint32_t		vmend, e_shnum, e_shoff;
	int			i;
	int			ncmds;
	int			segcnt;

	mh = (struct mach_header *)efile->mmap;
	sc = (struct segment_command *)(mh + 1);
	segcnt = 0;
	for (i = 0; i < macho_swap32(efile, mh->ncmds); i++) {

		/*
		 * We only care about LC_SEGMENT and LC_SYMTAB.
		 */
		switch (macho_swap32(efile, sc->cmd)) {
			case LC_SEGMENT:
				break;
//NOTYET
			case LC_SYMTAB:
			default:
				goto next;
		}

		/*
		 * Do not ever load __PAGEZERO.
		 */
		if (macho_swap32(efile, sc->cmd) == LC_SEGMENT &&
		    strcmp(sc->segname, "__PAGEZERO") == 0)
			goto next;

		if (macho_swap32(efile, sc->cmd) == LC_SEGMENT) {

			segments[segcnt].vaddr = macho_swap32(efile, 
			     sc->vmaddr);
			if (macho_swap32(efile, sc->vmaddr) & KERNEL_OFFSET)
				segments[segcnt].paddr = macho_swap32(efile,
				    sc->vmaddr) - KERNEL_OFFSET;
			else
				segments[segcnt].paddr = macho_swap32(efile,
				    sc->vmaddr);
			segments[segcnt].memsize = macho_swap32(efile, 
			     sc->vmsize);
			segments[segcnt].filesize = macho_swap32(efile, 
			    sc->filesize);
			segments[segcnt].align = efile->pagesize;
			segments[segcnt].elf_flags = (PF_R|PF_W|PF_X);/*XXX*/
#if 0	/* XXX: what's this? */
			if ... FL_PATCH_FILE
#endif
			segments[segcnt].data = (char *)mh + 
			    macho_swap32(efile, sc->fileoff);

			vmend = ALIGN(macho_swap32(efile, sc->vmaddr) +
			    macho_swap32(efile, sc->vmsize), 
			    efile->pagesize);
		} else if (macho_swap32(efile, sc->cmd) == LC_SYMTAB) {
#if NOTYET
			symcmd = (struct symtab_command *)sc;
			/* symtab */
			segments[segcnt].vaddr = vmend;
			/*
			 * broken - need to substract KERNEL_OFFSET
			 */
			segments[segcnt].paddr = vmend;
			segments[segcnt].memsize = symcmd->nsyms * 
			    sizeof(struct nlist);
			segments[segcnt].filesize = segments[segcnt].memsize;
			segments[segcnt].align = efile->pagesize;
			segments[segcnt].elf_flags = (PF_R|PF_W|PF_X);/*XXX*/
			segments[segcnt].data = (char *)mh + symcmd->symoff;

			/* increment manually */
			vmend += ALIGN(segments[segcnt].memsize, 
			    efile->pagesize);
			segcnt++;

			/* strtab */
			segments[segcnt].vaddr = vmend;
			/*
	 		 * broken - need to subtract KERNEL_OFFSET
			 */
			segments[segcnt].paddr = vmend;
			segments[segcnt].memsize = symcmd->strsize;
			segments[segcnt].filesize = symcmd->strsize;
			segments[segcnt].align = efile->pagesize;
			segments[segcnt].elf_flags = (PF_R|PF_W|PF_X);/*XXX*/
			segments[segcnt].data = (char *)mh + symcmd->stroff;
#endif
			;
		} else {
			log(LOG_CRITICAL, "%s: unsupported Mach-O load cmd \n",
			    __func__);
			abort();
		}

		/*
		 * XXX: we may need to fix up section offsets for the
		 * XXX: symbol tables, as they refer to section
		 * XXX: offsets (???)  Or maybe not, as each one
		 * XXX: is individually self-contained?
		 */

		segcnt++;
next:
		sc = (struct segment_command *)((char *)sc + 
		    macho_swap32(efile, sc->cmdsize));
	}

	return (segcnt);
}

/*
 * XXX:
 *
 * All currently supported architectures for Mach-O have a pagesize of
 * 4K.  This does suck, of course, probably not the best way to do this.
 */
int
macho_arch_pagesize(int arch)
{

	return 0x1000;
}

/*
 * Not used.  Only used if we have a SimpleElf module, and this is not
 * the case with Iguana.  For now, comment all references and remove
 * all references to it.
 */
#if 0
void *
macho_create_elf_headers(struct edit_file *efile, size_t *size)
{
	void 		*headers;
	Elf32_Ehdr	*ehdr;
	Elf32_Shdr	*shdr;
	int		e_shentsize, e_shnum;
	int		e_shstrndx;
	void		*newstringtable;
	size_t		stringtable_size;

	return (NULL);
}
#endif

uint32_t
swap32(uint32_t val)
{
	uint32_t	tmp;

	tmp = val;
	((uint8_t *)&val)[0] = ((uint8_t *)&tmp)[3];
	((uint8_t *)&val)[1] = ((uint8_t *)&tmp)[2];
	((uint8_t *)&val)[2] = ((uint8_t *)&tmp)[1];
	((uint8_t *)&val)[3] = ((uint8_t *)&tmp)[0];

	return (val);
}

/*
 * Swaps a Mach-O file if necessary.
 * If not then it just returns the value.
 */
uint32_t
macho_swap32(struct edit_file *efile, uint32_t val)
{
	return read32(&val, efile->endianness);
}

/*
 * Mach-O hack:
 *
 * Mach-O contains a 2 level namespace in the binary file.  They are
 * usually labeled segment,section.  Segment and sections are usually prefixed
 * with two underscores, with segment in all caps and segment in small,
 * though this is not required for the correct operation of Mach-O files.
 *
 * Each segment has a alignment, of at least a hardware page size.  Sections
 * live within a segment, and they all have the same protection.  This 
 * is not unlike the ELF segments (phdr) and segments (shdr), but in order
 * to fit in nicely, I think we need some special hacks.
 */
int
macho_register(struct edit_file *efile)
{
	struct edit_segment	*segs;
	struct mach_header	*mh = efile->mmap;
	struct section		*sect;
	int			i;

	/*
	 * XXX: Umm.
	 */
	if (efile->flags & FL_NEW) {
		if(efile->objtype == OBJ_MACHO) {
			log(LOG_LOW, "Creating a new elf32 file '%s'\n", 
			    efile->filename);
			efile->write_file = macho_write;
			efile->pagesize = elfarch_pagesize(efile->arch);
			return (0);
		} else {
			return (1);
		}
	}

	/*
	 * Check magic.  Should be Mach-O.
	 *
	 * XXX
	 *
	 * This check will prevent us from having to take care of fickle
	 * things like byte-swapping, but we really should fix that.  In
	 * order for this to work on the PowerPC, we need to compare
	 * against MH_CIGAM too, and swap everything appropriately.
	 */
	if (mh->magic != MH_MAGIC && mh->magic != MH_CIGAM)
		return (1);

	efile->objtype = OBJ_MACHO;
	efile->write_file = macho_write;
#if 0
	efile->arch = elfmach2arch(elfmach);
	efile->endianness;
#else	/* XXX: Sorry, i386 only for now. */
	efile->arch = ARCH_IA32;
	efile->endianness = LSB;
#endif
	efile->pagesize = macho_arch_pagesize(efile->arch);

	if (efile->arch == ARCH_INVALID) {
		log(LOG_WARNING, "unknown machine type: %d\n", efile->arch);
		return (1);
	}

	/*
	 * The kernel is special.  The entry point does not sit within
	 * the text section.
	 */
	if (efile->flags & FL_KERNEL) {
		sect = macho_findsegsect(efile, "__INIT", "__startup32");
		printf("sect->addr = %p\n", (void *)sect->addr);
		efile->entry = macho_swap32(efile, sect->addr);
	} else {
		sect = macho_findsegsect(efile, "__TEXT", "__text");
		efile->entry = macho_swap32(efile, sect->addr);
	}

	macho_initsects(efile);

	efile->nsegments = macho_getnsegs(efile);
	segs = calloc(efile->nsegments, sizeof(struct edit_segment));
	if (segs == NULL) {
		log(LOG_CRITICAL, "calloc() failed\n");
		exit(EXIT_FAILURE);
	}

	(void)macho_initsegs(efile, segs);
	efile->segments = segs;

	i = efile->nsegments - 1;
	/*
	 * no need to set endianess.  Already in native endian.
	 */
	segs[i].memsize = ALIGN(segs[i].memsize + segs[i].vaddr,
	    efile->alignment) - segs[i].vaddr;

	efile->size = segs[i].vaddr + segs[i].memsize - segs[0].vaddr;

	/*
	 * XXX: Fix the entry point.
	 * XXX: Fix all section addresses
	 * XXX: Can someone please tell me what this does?
	 * XXX: has reference to PHYS_ENTRY, presumably this is
 	 * XXX: for vaddr vs paddr loading in ELF?
	 * XXX: You simply cannot do this stuff in Mach-O.
	 * XXX:	-gl
	 */

	/*
	 * XXX
	 * 
	 * We leave this blank since this is only used for SimpleElf,
	 * which we do not require in Iguana.
	 */
	efile->elf_create_headers = NULL;
	efile->word_size = arch_to_wordsize(efile->arch);

	return (0);
}

/*
 * XXX: Duplicated: elf32.c
 */
static int       
get_num_sections(struct edit_file *efile)
{
	uint32_t e_shnum = 0;
	struct edit_section *current = efile->first_section;

        while(current) {
		e_shnum++;
		current = current->next; 
        }

	return e_shnum;
}

/*
 * If the file has been modified, we use macho_write() to write it
 * to the backing store.
 *
 * XXX We can probably use the one from elf32.c.
 *
 * This is mostly clagged from elf32.c:elf32_write().
 * I only fixed the formatting where appropriate.
 *
 *	 -gl.
 */
int
macho_write(struct edit_file *efile, struct edit_options *opts)
{
	FILE			*fptr;
        struct edit_section	*current_section;
	struct edit_segment	*segs = efile->segments;
	/*
	 * XXX: These aren't right and are not 64-bit safe.
	 */
	int			file_size, data_start, next_data, shdr_start;
	int			i, j;
	uint32_t		e_shnum;
	Elf32_Ehdr		ehdr;
	Elf32_Phdr		phdr;
	Elf32_Shdr		shdr;
	int			binfo_offset = 0;	/* XXX: 64-bit */

	/*
	 * If not modified, just return.  Do not unmap.
	 */
	if (!(efile->flags & FL_MOD))
		return (0);

	fptr = fopen(efile->filename, "wb");
	if (!fptr) {
		log(LOG_CRITICAL, "Could not open target file %s: %s\n",
		    efile->filename, strerror(errno));
		return (1);
	}

	shdr_start = next_data = data_start = file_size = 
	    sizeof(Elf32_Ehdr) + (sizeof(Elf32_Phdr) * efile->nsegments);

	for (i = 0; i < efile->nsegments; i++)
		shdr_start += segs[i].filesize;
	shdr_start = ALIGN(shdr_start, 4);
	memset(&ehdr, 0, sizeof(Elf32_Ehdr));

	ehdr.e_ident[0] = ELF_MAGIC_0;
	ehdr.e_ident[1] = ELF_MAGIC_1;
	ehdr.e_ident[2] = ELF_MAGIC_2;
	ehdr.e_ident[3] = ELF_MAGIC_3;

	ehdr.e_ident[EI_CLASS] = ELFCLASS32;
	ehdr.e_ident[EI_DATA] =
		(efile->endianness == LSB ? ELFDATA2LSB : ELFDATA2MSB);
	ehdr.e_ident[EI_VERSION] = EV_CURRENT;

	write16(ET_EXEC, &(ehdr.e_type), efile->endianness);
	write16(arch2elfmach(efile->arch), &(ehdr.e_machine),
			efile->endianness);
	write32(EV_CURRENT, &(ehdr.e_version), efile->endianness);

#if 0	/* XXX -gl dont do this for macho */
	write32(efile->entry + opts->elf_hdr_physaddr, &(ehdr.e_entry), 
	    efile->endianness);
#else
	write32(efile->entry, &(ehdr.e_entry), efile->endianness);
#endif

	write32(sizeof(Elf32_Ehdr), &(ehdr.e_phoff), efile->endianness);
	write32(shdr_start, &(ehdr.e_shoff), efile->endianness);
	write32(elfarchflags(efile->arch), &(ehdr.e_flags), efile->endianness);
	write16(sizeof(Elf32_Ehdr), &(ehdr.e_ehsize), efile->endianness);
	write16(sizeof(Elf32_Phdr), &(ehdr.e_phentsize), efile->endianness);

	/* 
	 * FIXME (sjw Wed Jul 19 05:16:11 2000 ) --- Should I include the PHDR 
	 * segment (spec says not to, I _think_)
	 */
	write16(efile->nsegments, &(ehdr.e_phnum), efile->endianness);
	write16(sizeof(Elf32_Shdr), &(ehdr.e_shentsize), efile->endianness);

	/* Calculate number of section headers: 3 more than actual amount
	 * because we have to create a section header string table and a 
	 * "null" entry, and binfo*/
	e_shnum = get_num_sections(efile) + 2;
	if (efile->binfo_seg)
		e_shnum += 1;
	write16(e_shnum, &(ehdr.e_shnum), efile->endianness);
	/* -1 for 0 -based index */
	write16(e_shnum - 1, &(ehdr.e_shstrndx), efile->endianness);

	/* Write header to the file */
	if (fwrite(&(ehdr), sizeof(Elf32_Ehdr), 1, fptr) != 1) {
		log(LOG_CRITICAL, "Could not write Ehdr to '%s' (%d)\n",
			efile->filename, ferror(fptr));
		return 1;
	}

	memset(&phdr, 0, sizeof(Elf32_Phdr));

	/* Set up data that doesn't change between segments */
	write32(PT_LOAD, &(phdr.p_type), efile->endianness);

	/* Write out segment headers, and update next_data */
	for (i = 0; i < efile->nsegments; i++) {
		/* 
		 * FIXME (sjw Tue Aug 15 00:46:39 2000 ) --- 
		 * This isn't 'properly' aligned */

		/* FIXME (sjw Wed Jul 19 10:04:12 2000 ) --- Flags */
		write32(PF_X | PF_R | PF_W, &(phdr.p_flags), 
		    efile->endianness);

		write32(next_data, &(phdr.p_offset), efile->endianness);
		if (&segs[i] == efile->binfo_seg) {
			binfo_offset = next_data;
		}
		/* XXX: We shift the vaddr to work around PMON loading segments
		 * into vaddrs on MIPS.  Since some segments (the kernel) are
		 * already in kseg0, we use bitwise or to leave them alone.
		 * -- alexw */
		write32(segs[i].vaddr | opts->elf_hdr_virtaddr, 
		    &(phdr.p_vaddr), efile->endianness);
		write32(segs[i].paddr + opts->elf_hdr_physaddr, 
		    &(phdr.p_paddr), efile->endianness);
		write32(segs[i].filesize, &(phdr.p_filesz), efile->endianness);
		write32(segs[i].memsize, &(phdr.p_memsz), efile->endianness);
		write32(segs[i].align, &(phdr.p_align), efile->endianness);

		/* Write out header to the file */
		if (fwrite(&phdr, sizeof(Elf32_Phdr), 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write Phdr to '%s' "
			    "(%d)\n", efile->filename, ferror(fptr));
			return 1;
		}

		next_data += segs[i].filesize;
	}

	/* Write out the actual data */
	next_data = data_start;
	for (i = 0; i < efile->nsegments; i++) {

		if (segs[i].flags & FL_S_PATCH_DIT && 
		    (!(efile->flags & FL_NODIT))) {
			void *write_at = segs[i].data +
				(segs[i].patch_addr - segs[i].vaddr);
			writeword(efile->arch, 
			    efile->dit_header_segment->paddr,
			    write_at, efile->endianness);
		}
		/* nfd: Don't try writing if we have a data size of 0 */
		if (segs[i].filesize != 0 &&
		    fwrite(segs[i].data, segs[i].filesize, 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write data to '%s' "
			    "(%d)\n", efile->filename, ferror(fptr));
			return 1;
		}

		next_data += segs[i].filesize;
	}
	/* Fixup offsets of existing sections. */
#if 0
	shdr_start = next_data = data_start = file_size =
		sizeof(Elf32_Ehdr) + (sizeof(Elf32_Phdr) * (efile->nsegments));

	for (i = 0; i < efile->nsegments; i++)
		shdr_start += segs[i].filesize;*/
#endif
	for (i = 0; i < efile->nsegments; i++) {
		for (current_section = efile->first_section;
		    current_section;
		    current_section = current_section -> next) {
			if (current_section->segment_num == i) {
				/* Fixup this section... */
				current_section->output_offset =
				    sizeof(Elf32_Ehdr) + 
				    (sizeof(Elf32_Phdr) * (efile->nsegments));

				for (j=0; j < i; j++) 
					current_section->output_offset += 
					    segs[j].filesize;

				current_section->output_offset += 
				    current_section->segment_offset;
			}
		}
	}

	/* We construct two dummy section headers:
	 * - section header 0, which is empty;
	 * - section header string table.
	 */
	/* ... first section */
	fseek(fptr, shdr_start, SEEK_SET);
	current_section = calloc(1, sizeof(struct edit_section));
	current_section->next = efile->first_section;
	efile->first_section = current_section;
	/* ... final section */
	while(current_section->next != NULL) {
		current_section = current_section->next;
	}

	if (efile->binfo_seg) {
		current_section = current_section->next = 
		    calloc(1, sizeof(struct edit_section));
		current_section->type = SHT_PROGBITS;
		current_section->addr = efile->binfo_seg->paddr;
		assert(binfo_offset != 0);
		current_section->output_offset = binfo_offset;
		current_section->addralign = 0x1000;
		current_section->entsize = 0;
		current_section->flags = SHF_ALLOC;
		current_section->size = efile->binfo_size;
		strcpy(current_section->name, ".binfo");
	}

	uint32_t strtab_size = 1;
	/* Get first after null segment */
	current_section = efile->first_section; 
	while(current_section->next != NULL) {
		strtab_size += strlen(current_section->name) + 1;
		current_section = current_section->next;
	}
	strtab_size += strlen(current_section->name) + 1;
	current_section = current_section->next = 
	    calloc(1, sizeof(struct edit_section));
	current_section->type = SHT_STRTAB;
	current_section->addr = 0;
	current_section->output_offset = shdr_start + (sizeof(shdr) * e_shnum);
	current_section->addralign = 1;
	current_section->entsize = 0;
	current_section->flags = 0;
	strcpy(current_section->name, ".shstrtab");
	strtab_size += strlen(current_section->name) + 1;
	current_section->size = strtab_size;

	/* Write out the section headers */
	current_section = efile->first_section;
	uint32_t shstrndx_pos = 1;
	while(current_section) {
		/* name, type, addr, size, addralign, entsize */

		write32(shstrndx_pos, &(shdr.sh_name), efile->endianness);
		write32(current_section->type, &(shdr.sh_type), 
		    efile->endianness);
		write32(current_section->flags, &(shdr.sh_flags), 
		    efile->endianness);
		write32(current_section->addr, &(shdr.sh_addr), 
		    efile->endianness);
		write32(current_section->output_offset, &(shdr.sh_offset), 
		    efile->endianness); /* FIXME! */
		write32(current_section->size, &(shdr.sh_size), 
		    efile->endianness);
		write32(0, &(shdr.sh_link), efile->endianness);
		write32(0, &(shdr.sh_info), efile->endianness);
		write32(current_section->addralign, &(shdr.sh_addralign), 
		    efile->endianness);
		write32(current_section->entsize, &(shdr.sh_entsize), 
		    efile->endianness);
		if (fwrite(&shdr, sizeof(Elf32_Shdr), 1, fptr) != 1) {
			log(LOG_CRITICAL, "Could not write Shdr to '%s' "
			    "(%d)\n", efile->filename, ferror(fptr));
			return 1;
		}
		shstrndx_pos += strlen(current_section->name) + 1;
		current_section = current_section->next;
	}

	/* We need to add a section for the bootinfo */

	/* ... finally, the section header string table itself. */
	current_section = efile->first_section;
	/* String table always begins with a null. */
	fwrite("\0", 1, 1, fptr);
	while(current_section) {
		int namelen;
		namelen = strlen(current_section->name);
		if (namelen > 0) {
			fwrite(current_section->name, 1, namelen, fptr);
		}
		fwrite("\0", 1, 1, fptr);
		current_section = current_section->next;
	}
	fclose(fptr);

	return 0;
}

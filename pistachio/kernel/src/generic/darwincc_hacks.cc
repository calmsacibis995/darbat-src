/*
 * darwincc_hacks.c
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 *
 * XXX It is entirely possible that these are actually i386 specific.
 * XXX In this case, this file should be moved into an architecture-specific
 * XXX directory.
 */

#ifdef __APPLE_CC__

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include INC_GLUE(config.h)

/*
 * XXX
 *
 */
extern "C" void memset(void *, int, int);

asm(".constructors_used = 0");                  /* XXX valid? */
asm(".private_extern .constructors_used");      /* XXX valid? */


/*
 * XXX
 *
 * This sucks, but this isn't any better to that seedy linker hack in
 * the linker script.
 */
#define BOOTMEM_SIZE	(128 * 1024)

/*
 * Special segment to force alignment to page size.
 */
char bootmem[BOOTMEM_SIZE] SECTION("__BOOTMEM", "__bootmem") = { 0 };
char *_start_bootmem = &bootmem[0];
char *_end_bootmem = &bootmem[BOOTMEM_SIZE]; /* ??? */

/*
 * Stolen from i386 linker script
 *
 * Can't initialize these here.  Somehow, it creates a special
 * bootmem constructor if I do that??
 */
char *_start_bootmem_phys = 0;//_start_bootmem - KERNEL_OFFSET;
char *_end_bootmem_phys = 0;//_end_bootmem - KERNEL_OFFSET;

/*
 * stolen from i386 linker script
 *
 * These would normally be in the linker script for ELF, but they need
 * to be calculated in kernelinterface.cc for Mach-O.
 */
extern unsigned long _memory_descriptors_offset;
extern unsigned long _memory_descriptors_size;

/*
 * These are initialized in init_vars() below.
 */
char	*_bss_start;
char	*_bss_end;

/*
 * These are initialized in init_vars() below.
 */
char	*_end_init;
char	*_start_init;

/*
 * Mach-O has __common (global bss) and __bss (local bss)
 *
 * Both should be zeroed, of course.
 */
char	*_common_start;
char	*_common_end;

/*
 * I do not think there is a good way to do these.  In the Mach-O version,
 * these would have to be initialized at run-time, using the pre-defined
 * _mh_execute_header.
 *
 * -gl
 */
char	*_end_text;
char	*_start_text;
char	*_end_text_phys;
char	*_start_text_phys;

/*
 * Linker sets.  This is only valid with seedy GNU ld linker hacks,
 * not valid anywhere else.  Still, the kernel requires these symbols
 * to be defined, due to  my laziness to take out the linker set source
 * files.
 *
 * -gl
 */
unsigned long _end_sets;
unsigned long _start_sets;

/*
 * XXX FIXME
 *
 */
unsigned long __ctors_CPU__;
unsigned long __ctors_GLOBAL__;
unsigned long __ctors_NODE__;


extern struct mach_header _mh_execute_header;

struct mach_header {
        unsigned long   magic;
        int		cputype;
        int		cpusubtype;
        unsigned long   filetype;
        unsigned long   ncmds;
        unsigned long   sizeofcmds;
        unsigned long   flags;
};

#define LC_SEGMENT              0x1

struct macho_segcmd {
        unsigned long   cmd;
        unsigned long   cmdsize;
        char            segname[16];
        unsigned long   vmaddr;
        unsigned long   vmsize;
        unsigned long   fileoff;
        unsigned long   filesize;
        int/*vm_prot_t*/        maxprot;
        int/*vm_prot_t*/        initprot;
        unsigned long   nsects;
        unsigned long   flags;
};

struct macho_section {
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

static int strcmp( const char *s1, const char *s2 );

static int strcmp( const char *s1, const char *s2 )
{
        while( 1 ) {
                if( !*s1 && !*s2 )
                        return 0;
                if( (!*s1 && *s2) || (*s1 < *s2) )
                        return -1;
                if( (*s1 && !*s2) || (*s1 > *s2) )
                        return 1;
                s1++;   
                s2++;
        }
}

/*
 * findbinarysiz
 *
 * Add up anything that is not __INIT and return the size.
 */
unsigned long
findbinarysize(void)
{
	int			i = 0, ncmds;
	unsigned long		siz;
	struct mach_header	*mh;
	struct	macho_segcmd	*segcmd = NULL;

	mh = &_mh_execute_header;
	segcmd = (struct macho_segcmd *)(mh + 1);

	ncmds = mh->ncmds;

	for (siz = 0, i = 0; i < ncmds; i++) {
		if (segcmd->cmd != LC_SEGMENT)
			goto next;	/* not loading */
		if (strcmp(segcmd->segname, "__PAGEZERO") == 0)
			goto next;	/* Skip page zero */
		if (strcmp(segcmd->segname, "__INIT") == 0)
			goto next;	/* Skip initialization */
		siz += segcmd->vmsize;

next:
		segcmd = (struct macho_segcmd *)((char *)segcmd + 
		    segcmd->cmdsize);
	}

	return (siz);
}

struct macho_segcmd *
findsegnamed(const char *s)
{
	int			i = 0, ncmds;
	struct mach_header	*mh;
	struct	macho_segcmd	*segcmd = NULL;

	mh = &_mh_execute_header;
	segcmd = (struct macho_segcmd *)(mh + 1);

	ncmds = mh->ncmds;

	for (i = 0; i < ncmds; i++)  {
		if (strcmp(segcmd->segname, s) == 0)
			break;
		/*
		 * next one
		 */
		segcmd = (struct macho_segcmd *)((char *)segcmd + 
		    segcmd->cmdsize);
	}

	return (segcmd);
}

struct macho_section *
findsectnamed(const char *seg, const char *s)
{
	int			i = 0, ncmds;
	struct mach_header	*mh;
	unsigned long		j;
	struct	macho_segcmd	*segcmd = NULL;
	struct	macho_section	*sect = NULL;

	mh = &_mh_execute_header;
	segcmd = (struct macho_segcmd *)(mh + 1);

	ncmds = mh->ncmds;

	for (i = 0; i < ncmds; i++) {
		if (segcmd->cmd != LC_SEGMENT)
			continue;

		if (seg && strcmp(seg, segcmd->segname))
			goto next;

		sect = (struct macho_section *)((char *)segcmd + 
		     sizeof(*segcmd));
		for (j = 0; j < segcmd->nsects; j++) {
			if (strcmp(sect->sectname, s) == 0)
				goto found;

			sect++;
		}

		/*
		 * next one
		 */
next:
		segcmd = (struct macho_segcmd *)((char *)segcmd + 
		    segcmd->cmdsize);

	}

found:
	return (sect);
}

#include <kdb/cmd.h>
#include <kdb/tracepoints.h>

// for tracepoints
tracepoint_t *
macho_tracepoint(int idx)
{
	struct	macho_section	*sect = NULL;

	sect = findsectnamed("__TRACEPOINTS", "__tracepoints");

	if (idx * sizeof(tracepoint_t) >= sect->size)
		return NULL;

	return (tracepoint_t *)(sect->addr + idx * sizeof(tracepoint_t));
}

word_t
macho_tracepointsiz(void)
{
	struct macho_section	*sect = NULL;

	sect = findsectnamed("__TRACEPOINTS", "__tracepoints");

	return (word_t)(sect->size / sizeof(tracepoint_t));
}

// for kdebug
cmd_t *
macho_findkdebugcmd(char *name, int idx)
{
	struct	macho_section	*sect = NULL;

	/*
	 * XXX
	 */
	if (strcmp(name, "") == 0) 
		name = "root";

	sect = findsectnamed("__KDEBUG", name);

	if (idx * sizeof(cmd_t) >= sect->size)
		return NULL;

	return (cmd_t *)(sect->addr + idx * sizeof(cmd_t));
}

typedef void (*constructor)(void);
constructor	*_ctors;
int		_nstructors;

// see init.cc, clear_bss().  probably ia-32 specific?
void
clear_bss(void)
{
	struct macho_section	*sect;
	/*
	 * Get bss symbols
	 */
	sect = findsectnamed(NULL, "__bss");
	_bss_start = (char *)sect->addr;
	_bss_end = (char *)sect->addr + sect->size;
	memset(_bss_start, 0, _bss_end - _bss_start);

	/*
	 * zero the common here, might as well.
	 */
	sect = findsectnamed(NULL, "__common");
	memset((void *)sect->addr, 0, sect->size);
}

void
init_vars(void)
{
	constructor	*f;
	int		i, nstructors;
	unsigned long	binsiz;
	struct macho_segcmd	*segcmd;
	/*
	 * Find constructors segment
 	 */
	struct macho_section *sect = findsectnamed(NULL, "__constructor");
	_ctors = f = (constructor *)sect->addr;
	_nstructors = nstructors = sect->size / sizeof(constructor);
	for (i = 0; i < nstructors; i++) {
		printf("would run structor %p\n", f[i]);
	}

	_start_bootmem_phys = _start_bootmem - KERNEL_OFFSET;
	_end_bootmem_phys = _end_bootmem - KERNEL_OFFSET;

	printf("bootmem %p - %p\n", _start_bootmem, _end_bootmem);


	binsiz = findbinarysize();
	printf("binsiz = %d\n", binsiz);
	_start_text = (char *)findsegnamed("__TEXT")->vmaddr;
	_end_text = _start_text + binsiz;
	_start_text_phys = _start_text - KERNEL_OFFSET;
	_end_text_phys = _end_text - KERNEL_OFFSET;
	printf("mach-o: kernel %p - %p\n", _start_text, _end_text);

	segcmd = findsegnamed("__INIT");
	_start_init = (char *)segcmd->vmaddr;
	_end_init = (char *)(segcmd->vmaddr + segcmd->vmsize);
	printf("mach-o: %s %p - %p\n", 
	    segcmd->segname, 
	    _start_init, _end_init);
}
#endif	/*__APPLE_CC__*/


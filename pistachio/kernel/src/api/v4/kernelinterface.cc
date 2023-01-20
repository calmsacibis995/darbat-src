/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 * Copyright (C) 2005,  National ICT Australia (NICTA)
 *                
 * File path:     api/v4/kernelinterface.cc
 * Description:   defines the kernel interface page
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
 * $Id: kernelinterface.cc,v 1.46 2004/06/03 14:57:30 joshua Exp $
 *                
 ********************************************************************/

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include INC_API(kernelinterface.h)
#include INC_API(memdesc.h)
#include INC_API(user.h)
#include INC_GLUE(config.h)
#ifndef SCONS_BUILD
#include <version.h>
#endif

#if defined(CONFIG_DEBUG)
extern void kdebug_init();
# define KDEBUG_INIT	kdebug_init
# define KDEBUG_ENTRY	kdebug_entry
#else
# define KDEBUG_INIT	(0)
# define KDEBUG_ENTRY	(0)
#endif

// NICTA Experimental Version Rev.3
#define KIP_API_VERSION   {SHUFFLE2(0x03, 0x86)}

// Thread info (sign. bits (arch-specific), sysbase, userbase)
#define KIP_THREAD_INFO   {SHUFFLE3(VALID_THREADNO_BITS, 0, 0)}

// Put processor descriptors directly after KIP
#define KIP_PROCESSOR_DESC_PTR (sizeof (kernel_interface_page_t))

// Processor info field.
#define KIP_PROCESSOR_INFO	{SHUFFLE2(0,KIP_PROC_DESC_LOG2SIZE)}

// Put kernel description after processor descriptors
#define KIP_DESCRIPTION_PTR (sizeof (kernel_interface_page_t) + sizeof(procdesc_t) * CONFIG_SMP_MAX_CPUS)

/*
 * Make room for at least some memory descriptors.
 */
#if !defined(KIP_MIN_MEMDESCS)
# define KIP_MIN_MEMDESCS (8)
#endif

// Memory info is calculated by linker script
#ifdef __ELF__
extern word_t _memory_descriptors_size[];
extern word_t _memory_descriptors_offset[];
#define KIP_MEMORY_INFO					\
    {SHUFFLE2 ((word_t) &_memory_descriptors_size,	\
	       (word_t) &_memory_descriptors_offset)}
#elif defined(__APPLE_CC__)
/*
 * -gl hack for now please fix
 */
#undef KIP_MIN_MEMDESCS
#define KIP_MIN_MEMDESCS	64	/* should be enough for now */

/*
 * XXX: attribute is probably gcc specific.
 *
 * Also, we do not handle feature string, and we do not shove
 * the kernel_version_string into the kip.
 *
 * This is done to ensure that things are placed in the proper order
 * in the KIP.  In particular, things must be ordered this way in 
 * order to work.  Rather than giving some thought on how to do this
 * properly, Pistachio has traditionally relied on the linker to do the
 * right thing.  Since the Darwin ld provides no such feature, we do 
 * this ourselves.
 *
 * -gl.
 */
struct _kip {
	kernel_interface_page_t	kip;
	procdesc_t processor_descriptors[CONFIG_SMP_MAX_CPUS];
	kernel_descriptor_t kdesc;
	// the aligned(16) was stolen from the linker script
	memdesc_t memory_descriptors[KIP_MIN_MEMDESCS] 
	    __attribute__((aligned(16)));
};
/*
 * XXX: gl can't use offsetof() :(
 *
 * While I would like to use the variables instead, when I put them
 * in, they appears as zero in the binary file ... :(
 * -gl
 */
#define _ROUNDUP(x, y)   (((x) + ((y)-1)) & ~((y) - 1))
#define _SIZEOF  (sizeof(kernel_interface_page_t) + sizeof(procdesc_t) * CONFIG_SMP_MAX_CPUS + sizeof(kernel_descriptor_t))
word_t _memory_descriptors_size = \
   (2048 - _ROUNDUP(_SIZEOF, 16) & (2048-1)) / 8;
word_t _memory_descriptors_offset = _ROUNDUP(_SIZEOF, 16);
#define KIP_MEMORY_INFO \
	{ SHUFFLE2(((2048 - _ROUNDUP(_SIZEOF, 16) & (2048 -1)) / 8), \
	_ROUNDUP(_SIZEOF, 16)) }
#else
#error "unknown compiler"
#endif

#ifdef __APPLE_CC__

struct _kip kip SECTION("__KIP", "__kip") = {
#endif	/*__APPLE_CC__ */
	
#ifndef __APPLE_CC__
kernel_interface_page_t kip UNIT("kip")=
#endif
{
    {{{'L','4',230,'K'}}}, // Magic word
    KIP_API_VERSION,
    KIP_API_FLAGS,		// API flags
    KIP_DESCRIPTION_PTR,	// kernel description pointer

    KDEBUG_INIT,		// kdebug init
    KDEBUG_ENTRY,		// kdebug entry
    {0, 0},			// kdebug memory region

    {0, 0, {0, 0}},		// sigma0
    {0, 0, {0, 0}},		// sigma1
    {0, 0, {0, 0}},		// root task

    0,				// reserved0
    KIP_MEMORY_INFO,		// memory info

    {0, 0},			// kdebug config

    {0, 0},			// main memory
    {0, 0},			// reserved memory 0

    {0, 0},			// reserved memory 1
    {0, 0},			// dedicated memory 0

    {0, 0},			// dedicated memory 1
    {0, 0},			// dedicated memory 2

    {0, 0},			// dedicated memory 3
    {0, 0},			// dedicated memory 4

    {0},			// reserved1
    { IPC_NUM_MR-1 },		// Virtual register info
    KIP_UTCB_INFO,		// UTCB info
    KIP_KIP_AREA,		// KIP area info

    {0,},			// reserved 2
    0,				// boot info
    KIP_PROCESSOR_DESC_PTR,	// processor description pointer

    {0},			// clock info
    KIP_THREAD_INFO,
    KIP_ARCH_PAGEINFO,		// page info
    KIP_PROCESSOR_INFO,		// processor info

    0, 0, 0, 0,			// privileged syscalls
    0, 0, 0, 0, 0, 0, 0,	// unprivileged syscalls
    {0, 0, 0, 0, 0},          	// reserved3 (5 words)

    0, 0, 0, 0			// architecture specific syscalls
#ifndef __APPLE_CC__
};
#else
	},
	{ 0 },	/* processor descriptors */
#endif

#ifndef __APPLE_CC__
extern const kernel_descriptor_t kdesc UNIT("kip.kdesc") =
#endif
{
    {SHUFFLE2(subid:1, id:5)},
#ifdef SCONS_BUILD
    {SHUFFLE3(day:(KERNEL_GEN_DAY),month:(KERNEL_GEN_MONTH),year:(KERNEL_GEN_YEAR)) },
#else
    { KERNELGENDATE },
#endif
    {SHUFFLE3(KERNEL_VERSION,KERNEL_SUBVERSION,KERNEL_SUBSUBVERSION)},
    {{{'N','I','C','T'}}}
#ifndef __APPLE_CC__
};
#else
    },
    /* memory desc */ {}
};
#endif
 

/*
 * Generate kernel version string.
 */
ALIGNED(1) char kernel_version_string[] UNIT("kip.versionparts") =
    "NICTA::Pistachio - built on " __DATE__ " " __TIME__
    " by " __USER__ " using gcc version " __VERSION__;
    

/*
 * Terminate the feature string list.
 */
ALIGNED(1) char features_end[] UNIT("kip.features.end") = "";

/**
 * processor descriptors
 */
#ifndef __APPLE_CC__ /* in struct _kip */
procdesc_t processor_descriptors[CONFIG_SMP_MAX_CPUS] UNIT ("kip.pdesc");
#else
procdesc_t *processor_descriptors = kip.processor_descriptors;
#endif

procdesc_t * processor_info_t::get_procdesc (word_t num)
{
    return num < CONFIG_SMP_MAX_CPUS ? &processor_descriptors[num] : NULL;
}

#ifndef __APPLE_CC__
memdesc_t memory_descriptors[KIP_MIN_MEMDESCS] UNIT ("kip.mdesc");
#else
memdesc_t *memory_descriptors = kip.memory_descriptors;
#endif


/**
 * Grab memory descriptor from kernel interface page.
 *
 * @param num	the descritor number to return
 *
 * @return pointer to memory descriptor, or NULL if NUM is out of range
 */
memdesc_t * memory_info_t::get_memdesc (word_t num)
{
    if (num >= n)
	return NULL;
    return &memory_descriptors[num];
}


/**
 * Insert a memory descriptor into kernel interface page.
 *
 * @param type		descriptor type
 * @param subtype	descriptor subtype
 * @param virt		true if descriptor is for virtual memory
 * @param low		low address of memory region
 * @param high		high address of memory region
 *
 * @return true if insertion was successful, false otherwise
 */
bool memory_info_t::insert (memdesc_t::type_e type, word_t subtype,
			    bool virt, addr_t low, addr_t high)
{
    const word_t max_desc = (word_t) &_memory_descriptors_size;

    if (n >= max_desc)
    {
	printf ("Memory descriptor overflow (max=%d, n=%d)\n", max_desc, n);
	enter_kdebug ("memdesc overflow");
	return false;
    }

    memdesc_t * md = get_memdesc (n++);
    md->set (type, subtype, virt, low, (addr_t) ((word_t) high - 1));

    return true;
}


/**
 * Print kernel version string.
 */
#ifdef __ELF__
void SECTION(".init") init_hello (void)
#elif defined(__APPLE_CC__)
void SECTION("__INIT", "__init") init_hello (void)
#else
#error "unknown compiler"
#endif
{
    printf ("\n" TXT_BRIGHT TXT_FG_YELLOW "%s" TXT_NORMAL "\n",
	    kernel_version_string);
}

#if !defined(ARCH_SYSCALL0)
#define ARCH_SYSCALL0 	0
#endif

#if !defined(ARCH_SYSCALL1)
#define ARCH_SYSCALL1 	0
#endif

#if !defined(ARCH_SYSCALL2)
#define ARCH_SYSCALL2 	0
#endif

#if !defined(ARCH_SYSCALL3)
#define ARCH_SYSCALL3 	0
#endif

#ifdef __ELF__
void SECTION(".init") kernel_interface_page_t::init()
#elif defined(__APPLE_CC__)
void SECTION("__INIT", "__init") kernel_interface_page_t::init()
#else
#error "unknown compiler"
#endif
{
#if defined(KIP_SYSCALL)    
#define SET_KIP_SYSCALL(x) \
    this->x##_syscall = KIP_SYSCALL(user_##x)

    SET_KIP_SYSCALL(space_control);
    SET_KIP_SYSCALL(thread_control);
    SET_KIP_SYSCALL(processor_control);
    SET_KIP_SYSCALL(memory_control);
    SET_KIP_SYSCALL(ipc);
    SET_KIP_SYSCALL(lipc);
    SET_KIP_SYSCALL(unmap);
    SET_KIP_SYSCALL(exchange_registers);
    SET_KIP_SYSCALL(system_clock);
    SET_KIP_SYSCALL(thread_switch);
    SET_KIP_SYSCALL(schedule);
#endif    

#define SET_KIP_ARCH_SYSCALL(n) \
    this->arch_syscall##n = ARCH_SYSCALL##n

    SET_KIP_ARCH_SYSCALL (0);
    SET_KIP_ARCH_SYSCALL (1);
    SET_KIP_ARCH_SYSCALL (2);
    SET_KIP_ARCH_SYSCALL (3);

#ifdef ARCH_SPECIAL_SYSCALLS
    ARCH_SPECIAL_SYSCALLS
#endif
}


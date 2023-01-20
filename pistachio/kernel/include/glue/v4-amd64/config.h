/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/config.h
 * Description:   
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
 * $Id: config.h,v 1.10 2004/06/02 18:05:49 stoess Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_AMD64__CONFIG_H__
#define __GLUE__V4_AMD64__CONFIG_H__

#include INC_GLUE(offsets.h)

/**
   attributes for system call functions
   @param x is the name of the system call lacking the leading sys_ .
   This makes it possible to place every system call in its own section
   if required. Default is empty.
 */
#define SYSCALL_ATTR(sec_name)


/*
 * endianess and word size
 */
#define KIP_API_FLAGS	{SHUFFLE2(endian:0, word_size:1)} // 64-bit, little endian 

/**
 * number of message registers
 */
#define IPC_NUM_MR			64

/**
 * minimum size of UTCB area and number of UTCBs in this
 * 1024 Bytes aligned, 1024 Bytes size, 4K area size 
 */ 
#define KIP_UTCB_INFO           {SHUFFLE3(multiplier:1, alignment:10, size:12)} 

/**
 * size of kernel interface page
 */
#define KIP_KIP_AREA	{size:12}   // 4KB

/** 
 * Minimum number of memory descriptors required in KIP 
 * */
#define KIP_MIN_MEMDESCS        (32)


/**
 * supported page sizes and access bits
 * rwx / 4KB, 2MB
 */
#define KIP_ARCH_PAGEINFO {SHUFFLE2(rwx:7, size_mask:( ((1 << 12) | (1 << 21)) >> 10)) }


/**
 * address of syscall(x)
 * we use absolute addresses
 */
#define KIP_SYSCALL(x)          ((word_t) (&x))

/**
 * Size of a kernel TCB in bytes
 */
#define KTCB_BITS		(12)
#define KTCB_SIZE		(__UL(1) << KTCB_BITS)
#define KTCB_MASK		(~(KTCB_SIZE-1))

/**
 * Valid Part of the Global Thread ID 
 */
#define VALID_THREADNO_BITS	(17)
#define VALID_THREADNO_SHIFT	(L4_GLOBAL_VERSION_BITS - KTCB_BITS)
#define VALID_THREADNO_MASK     ((__UL(1) << VALID_THREADNO_BITS) - 1)


/**
 * 
 * 
 * On change, adapt offsets.h!
 * 
 * TODO: As 64bit mode does not check segment limits, we might want to place two invalid
 *	 mappings around the UTCB_MAPPING
 * 
 * pml4[511] pdp[511] 
 */
#define KERNEL_AREA_END		(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(511) << AMD64_PDP_BITS | __UL(511) << AMD64_PDIR_BITS)
#define APIC_MAPPINGS		(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(511) << AMD64_PDP_BITS | __UL(510) << AMD64_PDIR_BITS)
#define UTCB_MAPPING		(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(511) << AMD64_PDP_BITS | __UL(509) << AMD64_PDIR_BITS)
/*      KERNEL_OFFSET           (AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(511) << AMD64_PDP_BITS) */
#define VIDEO_MAPPING		(0xB8000)		 

/**
 * 
 * We remap the lower 4GB here
 *  
 * pml[511] pdp[510]  ... pml[511] pdp[507] 
 * 
 */
#define REMAP_32BIT_END		(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(511) << AMD64_PDP_BITS)
#define REMAP_32BIT_START	(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS | __UL(507) << AMD64_PDP_BITS)		 


/**
 * KTCB Area 
 * 
 * pml[511] pdp[506]
 * 
 * 
 */
#define KTCB_AREA_SIZE		(KTCB_SIZE << VALID_THREADNO_BITS)
#define KTCB_AREA_START		((REMAP_32BIT_START - KTCB_AREA_SIZE) & (AMD64_SIGN_EXTEND_MASK | AMD64_PML4_MASK | AMD64_PDP_MASK) )
#define KTCB_AREA_END		(KTCB_AREA_START + KTCB_AREA_SIZE)

#define KERNEL_AREA_START	KTCB_AREA_START


/**
 * Copy Area
 * 
 *   
 * pml[511] pdp[2 * count]  ... pml[511] pdp[0] 
 * thus count must be less than 506/2 = 253
 */

#define COPY_AREA_COUNT		1
#define COPY_AREA_SIZE		(__UL(2) * AMD64_PDP_SIZE)
#define COPY_AREA_START		(AMD64_SIGN_EXTENSION | __UL(511) << AMD64_PML4_BITS )	      
#define COPY_AREA_END		(COPY_AREA_START + (COPY_AREA_COUNT * COPY_AREA_SIZE))

/*
 * pml[510] = word_count field (shadow PGT)
 * pml[509] = utcb_area field  (shadow PGT)
 * pml[508] = kip_area field   (shadow PGT)
 */

/**
 * User Area
 *  
 * pml[507] .. pml[0] (without sign extension)
 * 
 * 
 */

#define USER_AREA_END		(AMD64_SIGN_EXTENSION | __UL(508) << AMD64_PML4_BITS)		
#define USER_AREA_START		(__UL(0))				





/**
 * Base address of the root task's UTCB area
 */
#define ROOT_UTCB_START		(0xBF000000)

/**
 * Address of the KIP in the root task
 */
#define ROOT_KIP_START		(0xBFF00000)

/* defines the granularity kernel code and data is mapped */
#define KERNEL_PAGE_SIZE        (AMD64_2MPAGE_SIZE)

#define VIDEO_AREA


/* Segment register values */

/* DS, ES, SS is ignored in 64bit mode, so we don't need to have 
 * segment selectors/descriptors for them
 * 
 * KCS and KCS+8 = KDS will be loaded on syscall
 * UCS and UCS+8 = UDS will be loaded on sysret
 * 
 * TSS descriptor is 16 bytes long, therefore we place it at the end
 */
#define AMD64_INVS	         0x0		/* 0		*/
#define AMD64_KCS                0x8		/* 1, RPL = 0	*/
#define AMD64_KDS                0x10		/* 2, RPL = 0	*/
#define AMD64_UCS32              0x1b		/* 3, RPL = 3	*/
#define AMD64_UDS	         0x23		/* 4, RPL = 3	*/
#define AMD64_UCS                0x2b		/* 5, RPL = 3	*/
#define AMD64_UTCBS              0x33		/* 6, RPL = 3	*/
#define AMD64_KDBS               0x38		/* 7, RPL = 0	*/
#define AMD64_TBS                0x43		/* 8, RPL = 0	*/
#define AMD64_TSS                0x48		/* 9, RPL = 0	*/

/* user mode e-flags   */
#define AMD64_USER_FLAGS         (AMD64_RFL_IOPL(3) | AMD64_RFL_IF | 2)
#define AMD64_USER_FLAGMASK      (AMD64_RFL_CF | AMD64_RFL_PF | AMD64_RFL_AF | AMD64_RFL_ZF | AMD64_RFL_SF | AMD64_RFL_OF)

/* IDT, GDT, etc. */
#define IDT_SIZE		128		/* 128 Ent.		*/
#define GDT_SIZE		11		/* 10  Ent. (2 for TSS)	*/
#define GDT_IDX(x)		((x) >> 3)

/* Syscall/Sysret code and stack segment
 * 
 * On syscall : 
 *		CS <- AMD64_SYSCALLCS
 *		SS <- AMD64_SYSCALLCS + 8
 * 
 * On sysret into compatibility mode:  
 *		CS <- AMD64_SYSRETCS
 *		SS <- AMD64_SYSRETCS + 8
 * On sysret into long mode:  
 *		CS <- AMD64_SYSRETCS + 16
 *		SS <- AMD64_SYSRETCS + 8
 */

#define AMD64_SYSCALLCS		((u64_t) AMD64_KCS)
#define AMD64_SYSRETCS		((u64_t) AMD64_UCS32)

/* Syscall/Sysret RFLAGS MASK register value */
#define AMD64_SYSCALL_FLAGMASK	(AMD64_RFL_IF | AMD64_RFL_RF | AMD64_RFL_VM)

/* global IDT entries */
#define IDT_LAPIC_TIMER         0x40
#define IDT_LAPIC_THERMAL       0x41
#define IDT_LAPIC_IPI           0x42
#define IDT_IOAPIC_BASE         0x44

/* Page size for APIC and ACPI mappings */
#define APIC_PGENTSZ	        pgent_t::size_4k
#define ACPI_PGENTSZ	        pgent_t::size_2m

/* spurious int must have lowermost 4 bits set */
#define IDT_LAPIC_SPURIOUS_INT  0x3f


/* IOAPIC Settngs */
#define EXC_INTERRUPT(name)		AMD64_EXC_NO_ERRORCODE(name, 0)				
    

/* 1.953ms per timer tick
 * VU: the hardware clock can only be configured to tick in 2^n Hz
 * 1000 / 512 Hz = 1.953125 ms/tick */
#define TIMER_TICK_LENGTH       (1953)

/*
 * stack layout (counted in words)
 * 
 * SS
 * RSP
 * RFLAGS
 * CS
 * RIP
 * ErrorCode
 * ReturnFromIPC
 */
#define KSTACK_USP              (-2)
#define KSTACK_UFLAGS           (-3)
#define KSTACK_CS               (-4)
#define KSTACK_UIP              (-5)
#define KSTACK_RET_IPC          (-8)

/*
 * attribute for NOTIFY Procedures
 * 
 * makes gcc passing all arguments on the stack
 */
#define NOTIFY_FUNC			____attribute__ ((regparm (0)))



#endif /* !__GLUE__V4_AMD64__CONFIG_H__ */

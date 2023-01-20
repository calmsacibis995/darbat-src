/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-ia32/config.h
 * Description:   configuration of IA32 architecture
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
 * $Id: config.h,v 1.45 2004/09/15 18:09:20 jdoll Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_IA32__CONFIG_H__
#define __GLUE__V4_IA32__CONFIG_H__

#include INC_GLUE(offsets.h)
#include INC_ARCH(ia32.h) /* IA32 defines (cache, pagesize) */


/**********************************************************************
 *                  Kernel interface page values
 **********************************************************************/

/* 32bit, little endian	*/
#define KIP_API_FLAGS		{SHUFFLE2(endian:0, word_size:0)}
/* 512 Bytes aligned, 512 Bytes size, 4K area size */
#define KIP_UTCB_INFO		{SHUFFLE3(multiplier:1, alignment:9, size:12)}
/* 4KB */
#define KIP_KIP_AREA		{ size:12 }

#if defined(CONFIG_IA32_PSE)
/* write+read, 4M+4K */
#define KIP_ARCH_PAGEINFO	{SHUFFLE2(rwx:6, size_mask:((1 << IA32_SUPERPAGE_BITS) | (1 << IA32_PAGE_BITS)) >> 10)}
#else /* !CONFIG_IA32_PSE */
/* write+read, 4K */
#define KIP_ARCH_PAGEINFO	{SHUFFLE2(rwx:6, size_mask:((1 << IA32_PAGE_BITS)) >> 10)}
#endif
#define KIP_SYSCALL(x)		((u8_t*)(x) - (u8_t*)&kip)

/**
 * number of message registers
 */
#define IPC_NUM_MR			64

/* configuration for KTCBs
 * make sure the KTCBs fit entirely into the TCB area
 * TCB area size == 2^(KTCB_BITS + VALID_THREADNO_BITS) */
#define KTCB_BITS		(11)
#define KTCB_SIZE		(1 << KTCB_BITS)
#define KTCB_MASK		(~(KTCB_SIZE-1))

#define VALID_THREADNO_BITS	(17)
#define THREADNO_SHIFT		(L4_GLOBAL_VERSION_BITS - KTCB_BITS)
#define THREADNO_MASK		((1 << VALID_THREADNO_BITS) - 1)


/**********************************************************************
 *                  Virtual Address Space Layout
 **********************************************************************/

/* user area */
#define USER_AREA_START		__UL(0x00000000)
#define USER_AREA_END		__UL(0xC0000000)

/* small space area */
#define SMALLSPACE_AREA_START	(USER_AREA_END)
#define SMALLSPACE_AREA_SIZE	__UL(0x10000000)
#define SMALLSPACE_AREA_END	(SMALLSPACE_AREA_START + SMALLSPACE_AREA_SIZE)

/* unused areas, 8MB each */
#define UNUSED_AREA_COUNT	1
#define UNUSED_AREA_START	(SMALLSPACE_AREA_END)
#define UNUSED_AREA_SIZE	__UL(0x00800000)
#define UNUSED_AREA_END		(UNUSED_AREA_START + (UNUSED_AREA_COUNT * UNUSED_AREA_SIZE))

/* readmem_phys remap area */
#define MEMREAD_AREA_START	(UNUSED_AREA_END)

/* abused some entries */
#define KIP_AREA_INFO		(MEMREAD_AREA_START + IA32_PAGEDIR_SIZE)
#define UTCB_AREA_INFO		(KIP_AREA_INFO + IA32_PAGEDIR_SIZE)
#define THREAD_COUNT		(UTCB_AREA_INFO + IA32_PAGEDIR_SIZE)
#define SMALL_SPACE_ID		(THREAD_COUNT + IA32_PAGEDIR_SIZE)
#define SEGDESC_LOW		(SMALL_SPACE_ID + IA32_PAGEDIR_SIZE)
#define SEGDESC_HIGH		(SEGDESC_LOW + IA32_PAGEDIR_SIZE)

#if defined(CONFIG_IA32_SMALL_SPACES)
#define PAGEDIR_STUFF_END	(SEGDESC_HIGH + IA32_PAGEDIR_SIZE)
#else
#define PAGEDIR_STUFF_END	(THREAD_COUNT + IA32_PAGEDIR_SIZE)
#endif

/* V4 UTCB addressed via %gs:0 */
#define MYUTCB_MAPPING		__UL(0xDF000000)

/* trampoline to set up segment registers after sysexit */
#define UTRAMP_MAPPING		(MYUTCB_MAPPING + IA32_PAGE_SIZE)

/* device memory */
#define APIC_MAPPINGS		(UTRAMP_MAPPING + IA32_PAGE_SIZE)
#define EFI_MAPPINGS		(APIC_MAPPINGS + IA32_PAGE_SIZE)
#define EFI_MAPPINGS_SIZE       (16)
#define DEVICE_NEXT             (EFI_MAPPINGS + (EFI_MAPPINGS_SIZE*IA32_PAGE_SIZE))
#define DBG1394_MAPPINGS        (DEVICE_NEXT)

#define VIDEO_MAPPING		(0xb8000)

/* kernel level thread control blocks */
#define KTCB_AREA_START		(0xE0000000)
#define KTCB_AREA_SIZE		(1 << (KTCB_BITS + VALID_THREADNO_BITS))
#define KTCB_AREA_END		(KTCB_AREA_START + KTCB_AREA_SIZE)

/* KERNEL_AREA
 * synched on AS creation, so include all necessary regions!!! */
#define KERNEL_AREA_START	(MYUTCB_MAPPING)
#define KERNEL_AREA_END		(0xFF000000UL)

/* address of UTCB and KIP for root servers, at end of user-AS */
#define ROOT_UTCB_START		(0xBF000000)
#define ROOT_KIP_START		(0xBFF00000)

/* startup address for application processors */
#define SMP_STARTUP_ADDRESS	(0x4000)

/* some additional memory for the kernel*/
#define ADDITIONAL_KMEM_SIZE	(0x01000000)

/* defines the granularity kernel code and data is mapped */
#if !defined(CONFIG_SMP) && defined (CONFIG_IA32_PSE)
#define KERNEL_PAGE_SIZE	(IA32_SUPERPAGE_SIZE)
#else
#define KERNEL_PAGE_SIZE	(IA32_PAGE_SIZE)
#endif

/* Cache configuration */
#define CACHE_LINE_SIZE		(IA32_CACHE_LINE_SIZE_L2)

#ifdef CONFIG_PHYSICAL_KERNEL
#define START_ADDRESS_DUMMYTCB	(start_bootmem)
#define KMEM_POOL_RESERVED	(256 * 4096)
#define START_ADDRESS_TIDTABLE  (0 + KTCB_SIZE) // -gl fix me please
#endif

/* tracebuffer size */
#define TBUFF_SIZE (CONFIG_TRACEBUF_PAGES * IA32_PAGE_SIZE)


/**********************************************************************
 *          Architectural defines (segments, interrupts, etc.)
 **********************************************************************/

/* Segment register values */
#define IA32_KCS		0x08
#define IA32_KDS		0x10
#define IA32_UCS		0x1b
#define IA32_UDS		0x23
#define IA32_UTCB		0x2b
#define IA32_TSS		0x30
#define IA32_KDB		0x38
#define IA32_TBS		0x43

/* user mode e-flags */
#define IA32_USER_FLAGS		(IA32_EFL_IOPL(3) | IA32_EFL_IF | 2)
#define IA32_USER_FLAGMASK	(IA32_EFL_CF | IA32_EFL_PF | IA32_EFL_AF | IA32_EFL_ZF | IA32_EFL_SF | IA32_EFL_OF)

/* IDT, GDT, etc. */
#define IDT_SIZE		128
#define GDT_SIZE		16

/* global IDT entries */
#define IDT_LAPIC_SPURIOUS_INT	0x3f /* spurious int vector must 
				      * have lowermost 4 bits set */
#define IDT_LAPIC_TIMER		0x40
#define IDT_LAPIC_THERMAL	0x41
#define IDT_LAPIC_XCPU_IPI	0x42
#define IDT_IOAPIC_BASE		0x44

/* Page size for APIC and ACPI mappings */
#define APIC_PGENTSZ	        pgent_t::size_4k
#define ACPI_PGENTSZ	        pgent_t::size_4m

#define EXC_INTERRUPT(name)	IA32_EXC_NO_ERRORCODE(name, 0)

/* timer frequency */
#ifdef CONFIG_IOAPIC
# define TIMER_TICK_LENGTH	(CONFIG_APIC_TIMER_TICK)
#else
/* 1.953ms per timer tick
 * VU: the hardware clock can only be configured to tick in 2^n Hz
 * 1000 / 512 Hz = 1.953125 ms/tick */
# define TIMER_TICK_LENGTH	(1953)
#endif

/* enable synchronous XCPU-requests, for TLB shoot-downs */
#define CONFIG_SMP_SYNC_REQUEST



/**********************************************************************
 *                       kernel stack layout 
 **********************************************************************/

#define KSTACK_USP		(-2)
#define KSTACK_UFLAGS		(-3)
#define KSTACK_UIP		(-5)
#define KSTACK_RET_IPC		(-6)

#endif /* !__GLUE__V4_IA32__CONFIG_H__ */

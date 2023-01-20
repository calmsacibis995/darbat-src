/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  University of Karlsruhe
 *                
 * File path:     arch/amd64/pagebits.h
 * Description:   Global page size macros 
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
 * $Id: 
 *                
 ********************************************************************/
#ifndef __ARCH__AMD64__PAGEBITS_H__
#define __ARCH__AMD64__PAGEBITS_H__

/**
 * Bits to calculate indices in the respective tables from virtual addresses 
 */

/* Sign extend 64..48 */
#define AMD64_SIGN_EXTEND_BITS   48
#define AMD64_SIGN_EXTEND_SIZE   (AMD64_64BIT_ONE << AMD64_SIGN_EXTEND_BITS)
#define AMD64_SIGN_EXTEND_MASK   (~(AMD64_SIGN_EXTEND_SIZE - 1))
#define AMD64_SIGN_EXTENSION	 (~(AMD64_SIGN_EXTEND_SIZE - 1))

/* Page map 47.. 39 */
#define AMD64_PML4_BITS		39
#define AMD64_PML4_SIZE         (AMD64_64BIT_ONE << AMD64_PML4_BITS)
#define AMD64_PML4_MASK         ((~(AMD64_PML4_SIZE - 1)) ^ (~(AMD64_SIGN_EXTEND_SIZE - 1)))
#define AMD64_PML4_IDX(x)	((x & AMD64_PML4_MASK) >> AMD64_PML4_BITS)

/* Page directory pointer 38..30 */
#define AMD64_PDP_BITS           30
#define AMD64_PDP_SIZE           (AMD64_64BIT_ONE << AMD64_PDP_BITS)
#define AMD64_PDP_MASK           ((~(AMD64_PDP_SIZE - 1))  ^ (~(AMD64_PML4_SIZE - 1)))
#define AMD64_PDP_IDX(x)	 ((x & AMD64_PDP_MASK) >> AMD64_PDP_BITS)

/* Page directory 29..21 */
#define AMD64_PDIR_BITS         21
#define AMD64_PDIR_SIZE         (AMD64_64BIT_ONE << AMD64_PDIR_BITS)
#define AMD64_PDIR_MASK         ((~(AMD64_PDIR_SIZE - 1))  ^ (~(AMD64_PDP_SIZE - 1)))
#define AMD64_PDIR_IDX(x)	((x & AMD64_PDIR_MASK) >> AMD64_PDIR_BITS)

/* Pagetable 20..12  */
#define AMD64_PTAB_BITS          12
#define AMD64_PTAB_SIZE          (AMD64_64BIT_ONE << AMD64_PTAB_BITS)
#define AMD64_PTAB_MASK          ((~(AMD64_PTAB_SIZE - 1))  ^ (~(AMD64_PDIR_SIZE - 1)))
#define AMD64_PTAB_IDX(x)        ((x & AMD64_PDIR_MASK) >> AMD64_PDIR_BITS)


/**
 *  Common page attribute bits 
 */

#define AMD64_PAGE_VALID	        (1<<0)
#define AMD64_PAGE_WRITABLE	        (1<<1)
#define AMD64_PAGE_USER			(1<<2)
#define AMD64_PAGE_KERNEL	        (0<<2)
#define AMD64_PAGE_WRITE_THROUGH	(1<<3)
#define AMD64_PAGE_CACHE_DISABLE	(1<<4)
#define AMD64_PAGE_ACCESSED	        (1<<5)
#define AMD64_PAGE_DIRTY		(1<<6)

#define AMD64_PAGE_GLOBAL	        (1<<8)
#define AMD64_PAGE_NX			(1<<63)

/* 2MByte specific page attribute bits */
#define AMD64_2MPAGE_SUPER   		(1<<7)
#define AMD64_2MPAGE_PAT  	        (1<<12)

/* 4KByte specific page attribute bits */
#define AMD64_4KPAGE_PAT   		(1<<7)

/**
 * 
 * Bits to zero out invalid parts of pagetable entries 
 */
#define AMD64_PTAB_BYTES		4096

/* Normal pagetable entry 20..0  */
#define AMD64_PTE_BITS		 12
#define AMD64_PTE_SIZE		 (AMD64_64BIT_ONE << AMD64_PTE_BITS) 
#define AMD64_PTE_MASK		 (~(AMD64_PTE_SIZE - 1))
#define AMD64_PTE_FLAGS_MASK     (0x003f)

/* 2 MByte (Super-) Pages 20..0  */
#define AMD64_2MPAGE_BITS	 21
#define AMD64_2MPAGE_SIZE	 (AMD64_64BIT_ONE << AMD64_2MPAGE_BITS) 
#define AMD64_2MPAGE_MASK	 (~(AMD64_2MPAGE_SIZE - 1))
#define AMD64_2MPAGE_FLAGS_MASK	 (0x11ff)

/* 4 KByte Page 12..0  */
#define AMD64_4KPAGE_BITS	 12
#define AMD64_4KPAGE_SIZE	 (AMD64_64BIT_ONE << AMD64_4KPAGE_BITS) 
#define AMD64_4KPAGE_MASK	 (~(AMD64_4KPAGE_SIZE - 1))
#define AMD64_4KPAGE_FLAGS_MASK	 (0x01ff)


				  
#endif /* !__ARCH__AMD64__PAGEBITS_H__ */

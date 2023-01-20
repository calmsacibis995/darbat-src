/****************************************************************************
 *
 * Copyright (C) 2002, Karlsruhe University
 *
 * File path:	types.h
 * Description:	Defines some basic, global types.
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
 * $Id: types.h,v 1.11 2003/09/24 19:04:24 skoglund Exp $
 *
 ***************************************************************************/

#ifndef __TYPES_H__
#define __TYPES_H__

#if !defined(ASSEMBLY)

#include INC_ARCH(types.h)
/* At this point we should have word_t defined */


/**
 *	addr_t - data type to store addresses
 */
typedef void*			addr_t;

#if defined(__cplusplus)
/**
 * Add offset to address.
 * @param addr		original address
 * @param off		offset to add
 * @return new address
 */
INLINE addr_t addr_offset(addr_t addr, addr_t off)
{
    return (addr_t)((word_t)addr + (word_t)off);
}
#endif

/**
 * Add offset to address.
 * @param addr		original address
 * @param off		offset to add
 * @return new address
 */
INLINE addr_t addr_offset(addr_t addr, word_t off)
{
    return (addr_t)((word_t)addr + off);
}

/**
 * Apply mask to an address.
 * @param addr		original address
 * @param mask		address mask
 * @return new address
 */
INLINE addr_t addr_mask (addr_t addr, word_t mask)
{
    return (addr_t) ((word_t) addr & mask);
}

/**
 * Align address downwards.  It is assumed that the alignment is a power of 2.
 * @param addr		original address
 * @param align		alignment
 * @return new address
 */
INLINE addr_t addr_align (addr_t addr, word_t align)
{
    return addr_mask (addr, ~(align - 1));
}

/**
 * Align address upwards.  It is assumed that the alignment is a power of 2.
 * @param addr		original address
 * @param align		alignment
 * @return new address
 */
INLINE addr_t addr_align_up (addr_t addr, word_t align)
{
    return addr_mask (addr_offset (addr, align - 1), ~(align - 1));
}



#ifndef NULL
#define NULL 0
#endif

#define BITS_WORD	(sizeof(word_t)*8)

#endif /* !defined(ASSEMBLY) */

#endif /* !__TYPES_H__ */

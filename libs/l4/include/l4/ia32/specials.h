/*********************************************************************
 *                
 * Copyright (C) 2002, 2003,  Karlsruhe University
 *                
 * File path:     l4/ia32/specials.h
 * Description:   x86 specific functions and defines
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
 * $Id: specials.h,v 1.9 2003/09/24 19:06:23 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __L4__X86__SPECIALS_H__
#define __L4__X86__SPECIALS_H__


/*
 * Architecture specific helper functions.
 */

L4_INLINE int __L4_Msb (L4_Word_t w) __attribute__ ((const));

L4_INLINE int __L4_Msb (L4_Word_t w)
{
    int bitnum;

    __asm__ (
	"/* l4_msb()		*/			\n"
	"	bsr	%1, %0				\n"

	: /* outputs */
	"=r" (bitnum)
	: /* inputs */
	"rm" (w)
	);

    return bitnum;
}




/*
 * IO fpages.
 */
typedef union {
    L4_Word_t	raw;
    struct {
	unsigned	rwx:4;
	unsigned	__two:6;
	unsigned	s:6;
	unsigned	p:16;
    } X;
} L4_IoFpage_t;

#if defined(__l4_cplusplus)
L4_INLINE L4_Fpage_t L4_Fpage (L4_Fpage_t f)
{
    L4_Fpage_t out;
    out.raw = f.raw;
    return out;
}

L4_INLINE L4_IoFpage_t L4_IoFpage (L4_IoFpage_t f)
{
    L4_IoFpage_t out;
    out.raw = f.raw;
    return out;
}

L4_INLINE L4_IoFpage_t L4_IoFpage (L4_Word_t BaseAddress, int FpageSize)
{
    L4_IoFpage_t fp;
    L4_Word_t msb = __L4_Msb (FpageSize);
    fp.X.p = BaseAddress;
    fp.X.__two = 2;
    fp.X.s = (1UL << msb) < (L4_Word_t) FpageSize ? msb + 1 : msb;
    fp.X.rwx = L4_NoAccess;
    return fp;
}

L4_INLINE L4_IoFpage_t L4_IoFpageLog2 (L4_Word_t BaseAddress, int FpageSize)
{
    L4_IoFpage_t fp;
    fp.X.p = BaseAddress;
    fp.X.__two = 2;
    fp.X.s = FpageSize;
    fp.X.rwx = L4_NoAccess;
    return fp;
}
#endif



/*
 * Control parameter for SpaceControl system call.
 */

#define L4_LargeSpace		0

L4_INLINE L4_Word_t L4_SmallSpace (L4_Word_t location, L4_Word_t size)
{
    location >>= 1;
    size >>= 2;
    return ((location & ~(size - 1)) | size) & 0xff;
}




/*
 * Cacheability hints for string items.
 */

#define L4_AllocateNewCacheLines	(L4_CacheAllocationHint_t) { raw: 1 })
#define L4_DoNotAllocateNewCacheLines	(L4_CacheAllocationHint_t) { raw: 2 })
#define L4_AllocateOnlyNewL1CacheLines	(L4_CacheAllocationHint_t) { raw: 3 })




/*
 * Memory attributes for MemoryControl system call.
 */

#define L4_UncacheableMemory		1
#define L4_WriteCombiningMemory		2
#define L4_WriteThroughMemory		5
#define L4_WriteProtectedMemory		6
#define L4_WriteBackMemory		7




#endif /* !__L4__X86__SPECIALS_H__ */

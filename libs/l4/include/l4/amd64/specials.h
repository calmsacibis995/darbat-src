/*********************************************************************
 *                
 * Copyright (C) 2002, 2003,  Karlsruhe University
 *                
 * File path:     l4/amd64/specials.h
 * Description:   amd64 specific functions and defines
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
#ifndef __L4__AMD64__SPECIALS_H__
#define __L4__AMD64__SPECIALS_H__

/*
 * Architecture specific helper functions.
 */


L4_INLINE int __L4_Msb (L4_Word_t w) __attribute__ ((const));

L4_INLINE int __L4_Msb (L4_Word_t w)
{
    L4_Word_t bitnum;

    __asm__ (
	"/* l4_msb()		*/			\n"
	"bsrq	%1, %0					\n"
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
    fp.raw = BaseAddress;
    fp.X.__two = 2;
    fp.X.s = __L4_Msb (FpageSize) - 10;
    fp.X.rwx = L4_NoAccess;
    return fp;
}

L4_INLINE L4_IoFpage_t L4_IoFpageLog2 (L4_Word_t BaseAddress, int FpageSize)
{
    L4_IoFpage_t fp;
    fp.raw = BaseAddress;
    fp.X.__two = 2;
    fp.X.s = FpageSize;
    fp.X.rwx = L4_NoAccess;
    return fp;
}
#endif




#endif /* !__L4__AMD64__SPECIALS_H__ */

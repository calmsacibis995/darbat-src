/****************************************************************************
 *
 * Copyright (C) 2003, University of New South Wales
 *
 * File path:	l4/powerpc64/kdebug.h
 * Description:	L4 Kdebug interface for PowerPC64
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
 * $Id: kdebug.h,v 1.4 2004/04/07 03:25:38 cvansch Exp $
 *
 ***************************************************************************/
#ifndef __L4__POWERPC64__KDEBUG_H__
#define __L4__POWERPC64__KDEBUG_H__


#define __L4_TRAP64_MAGIC	    (0x4c345f5050433634ul)  /* "L4_PPC64" */
#define __L4_TRAP64_KDEBUG	    (__L4_TRAP64_MAGIC + 0)
#define __L4_TRAP64_KPUTC	    (__L4_TRAP64_MAGIC + 1)
#define __L4_TRAP64_KGETC	    (__L4_TRAP64_MAGIC + 2)
#define __L4_TRAP64_KGETC_NB	    (__L4_TRAP64_MAGIC + 3)
#define __L4_TRAP64_KSET_THRD_NAME  (__L4_TRAP64_MAGIC + 5)

#define L4_KDB_Enter(str...)					\
{								\
    register L4_Word_t call asm("r0") = __L4_TRAP64_KDEBUG;	\
    asm volatile (						\
	"trap ;"						\
	"b 1f ;"						\
	".string	\"KD# " str "\";"			\
	".align 2 ;"						\
	"1:" 							\
	:: "r" (call)						\
    );								\
}


#define __L4_KDB_Op_Arg(op, name, argtype)	\
L4_INLINE void L4_KDB_##name (argtype arg)	\
{						\
    register L4_Word_t call asm("r0") = op;	\
    register L4_Word_t r_r3 asm("r3") = arg;	\
    __asm__ __volatile__ (			\
	    "trap ;"				\
	    :: "r" (call), "r" (r_r3)		\
    );						\
}


#define __L4_KDB_Op_Ret(op, name, rettype)	\
L4_INLINE rettype L4_KDB_##name (void)		\
{						\
    register L4_Word_t call asm("r0") = op;	\
    register rettype r_r3 asm("r3");		\
    __asm__ __volatile__ (			\
	    "trap ;"				\
	    : "=r" (r_r3) : "r" (call)		\
    );						\
    return r_r3;				\
}

__L4_KDB_Op_Ret( __L4_TRAP64_KGETC, ReadChar_Blocked, char );
__L4_KDB_Op_Ret( __L4_TRAP64_KGETC_NB, ReadChar, char );
__L4_KDB_Op_Arg( __L4_TRAP64_KPUTC, PrintChar, char );

L4_INLINE void
L4_KDB_SetThreadName(L4_ThreadId_t tid, const char *name)
{
    L4_Word_t *name_p = (L4_Word_t*) name;
    register L4_Word_t r_tid	asm("r3") = tid.raw;
    register L4_Word_t first	asm("r4") = name_p[0];
    register L4_Word_t call	asm("r0") = __L4_TRAP64_KSET_THRD_NAME;

    __asm__ __volatile__ (
	"trap			\n"
	:: "r" (call), "r" (r_tid), "r" (first)
    );
}

#endif	/* __L4__POWERPC64__KDEBUG_H__ */

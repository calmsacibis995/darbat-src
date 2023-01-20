/*********************************************************************
 *
 * Copyright (C) 2003-2004,  National ICT Australia (NICTA)
 *                
 * File path:     l4/arm/kdebug.h
 * Description:   ARM kernel debugger interface
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
 * $Id: kdebug.h,v 1.7 2004/06/04 08:20:12 htuch Exp $
 *                
 ********************************************************************/
#ifndef __L4__ARM__KDEBUG_H__
#define __L4__ARM__KDEBUG_H__

#include <l4/types.h>
#include <l4/arm/syscalls.h>

#ifdef __thumb__
#define ARM_IMM		"r"
#else
#define ARM_IMM		"i"
#endif

#define L4_KDB_Enter(str...)			\
do {						\
    __asm__ __volatile__ (			\
	"   adr	    r0,	1f	\n"		\
	"   mov	    ip,	sp	\n"		\
	"   mov	    sp,	%0	\n"		\
	"   mov	    lr,	pc	\n"		\
	"   swi	    0x01	\n" /* 0x01 ignored */		\
	"   b	    2f		\n"		\
	"   .align  2		\n"		\
	"1: .string " #str "	\n"		\
	"   .align  2		\n"		\
	"2:			\n"		\
	:					\
	: ARM_IMM (L4_TRAP_KDEBUG)		\
	: "r0", "ip", "lr", "memory");		\
} while (0)

#define __L4_KDB_Op_Arg(op, name, argtype)	\
L4_INLINE void L4_KDB_##name (argtype arg)	\
{						\
    register argtype param asm("r0") = arg;	\
    __asm__ __volatile__ (			\
	"   mov	    ip,	sp	\n"		\
	"   mov	    sp,	%1	\n"		\
	"   mov	    lr,	pc	\n"		\
	"   swi	    0x00	\n" /* 0x00 ignored */		\
	: "+r" (param)				\
	: ARM_IMM (op)				\
	: "ip", "lr", "memory" );		\
} 

#define __L4_KDB_Op_Ret(op, name, rettype)	\
L4_INLINE rettype L4_KDB_##name (void)		\
{						\
    register L4_Word_t ret asm("r0");		\
    __asm__ __volatile (			\
	"   mov	    ip,	sp	\n"		\
	"   mov	    sp,	%1	\n"		\
	"   mov	    lr,	pc	\n"		\
	"   swi	    0x00	\n" /* 0x00 ignored */		\
	: "=r" (ret)				\
	: ARM_IMM (op)				\
	: "ip", "lr", "memory");		\
    return ret;					\
}

#define __L4_KDB_Op_Ret_Arg(op, name, argtype, rettype)	\
L4_INLINE rettype L4_KDB_##name (argtype arg)		\
{						\
    register L4_Word_t param asm("r0") = arg;	\
    __asm__ __volatile (			\
	"   mov	    ip,	sp	\n"		\
	"   mov	    sp,	%1	\n"		\
	"   mov	    lr,	pc	\n"		\
	"   swi	    0x00	\n" /* 0x00 ignored */		\
	: "+r" (param)				\
	: ARM_IMM (op)				\
	: "lr", "memory");			\
    return param;				\
}

__L4_KDB_Op_Ret(L4_TRAP_KGETC, ReadChar_Blocked, char );
__L4_KDB_Op_Ret(L4_TRAP_KGETC_NB, ReadChar, long );
__L4_KDB_Op_Arg(L4_TRAP_KPUTC, PrintChar, char );
__L4_KDB_Op_Ret_Arg(L4_TRAP_GETCOUNTER, GetTracepointCount, L4_Word_t, L4_Word_t );
__L4_KDB_Op_Ret(L4_TRAP_GETNUMTPS, GetNumTracepoints, L4_Word_t);
__L4_KDB_Op_Arg(L4_TRAP_GETTPNAME, GetTracepointNameIntroMRs, L4_Word_t);
__L4_KDB_Op_Arg(L4_TRAP_TCCTRL, TCCtrl, L4_Word_t);

__L4_KDB_Op_Arg(L4_TRAP_PMU_RESET, _PMU_Reset, L4_Word_t);
__L4_KDB_Op_Arg(L4_TRAP_PMU_STOP, _PMU_Stop, L4_Word_t);
__L4_KDB_Op_Ret_Arg(L4_TRAP_PMU_READ, PMU_Read, L4_Word_t, L4_Word_t);
__L4_KDB_Op_Arg(L4_TRAP_PMU_CONFIG, _PMU_Config, L4_Word_t);


L4_INLINE void
L4_KDB_PMU_Reset(void)
{
	L4_KDB__PMU_Reset(0);
}

L4_INLINE void
L4_KDB_PMU_Stop(void)
{
	L4_KDB__PMU_Stop(0);
}

L4_INLINE void
L4_KDB_PMU_Set(unsigned long event0, unsigned long event1)
{
	L4_KDB__PMU_Config((event0 << 12) | (event1 << 20) | (3 << 8));
}


L4_INLINE void
L4_KDB_TracepointCountStop(void)
{
    L4_KDB_TCCtrl(0);
}


L4_INLINE void
L4_KDB_TracepointCountReset(void)
{
    L4_KDB_TCCtrl(1);
}

L4_INLINE void
L4_KDB_SetThreadName(L4_ThreadId_t tid, const char *name)
{
    L4_Word_t name_p[4], len = 0;
    char *to = (char*) &name_p;

    while(*name != '\0' && len < sizeof(name_p)) {
	*to++ = *name++;
	len++;
    }
    if (len < sizeof(name_p))
	*to = 0;

    {
	register L4_Word_t	t asm("r0") = tid.raw;
	register L4_Word_t	w0 asm("r1") = name_p[0];
	register L4_Word_t	w1 asm("r2") = name_p[1];
	register L4_Word_t	w2 asm("r3") = name_p[2];
	register L4_Word_t	w3 asm("r4") = name_p[3];

	__asm__ __volatile__ (
	    "   mov	    ip,	sp	\n"
	    "   mov	    sp,	%1	\n"
	    "   mov	    lr,	pc	\n"
	    "   swi	    0x02	\n" /* 0x02 ignored */
	    : "+r" (t)
	    : ARM_IMM (L4_TRAP_KSET_THRD_NAME),
	      "r" (w0), "r" (w1), "r" (w2), "r" (w3)
	    : "ip", "lr", "memory" );
    }
}

L4_INLINE void
L4_KDB_GetTracepointName(L4_Word_t tp, char *dest)
{
    char *src = (char *) &(__L4_ARM_Utcb())[__L4_TCR_MR_OFFSET];
    L4_KDB_GetTracepointNameIntroMRs(tp);

    /* Ewww! Another reimplementation of strcpy! */
    while(*src)
	*dest++ = *src++;
    *dest = '\0';
}

#endif /* !__L4__ARM__KDEBUG_H__ */

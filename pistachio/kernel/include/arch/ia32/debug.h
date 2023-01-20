/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     arch/ia32/debug.h
 * Description:   debugging
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
 * $Id: debug.h,v 1.10 2004/02/04 02:50:22 sgoetz Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__IA32__DEBUG_H__
#define __ARCH__IA32__DEBUG_H__

#include INC_GLUE(config.h)
#define DEBUG_SCREEN (KERNEL_OFFSET + 0xb8000)

INLINE void spin_forever(int pos = 0)
{
#if defined(CONFIG_SPIN_WHEELS)
    while(1)
	((u16_t*)(DEBUG_SCREEN))[pos] += 1;
#else /* defined(CONFIG_SPIN_WHEELS) */
    int dummy = 0;
    while(1)
	dummy = (dummy + 1) % 32;
#endif /* defined(CONFIG_SPIN_WHEELS) */
}

INLINE void spin(int pos, int cpu = 0)
{
#if defined(CONFIG_SPIN_WHEELS)
    ((u8_t*)(DEBUG_SCREEN))[(cpu * 160) + pos * 2] += 1;
    ((u8_t*)(DEBUG_SCREEN))[(cpu * 160) + pos * 2 + 1] = 7;
#endif /* defined(CONFIG_SPIN_WHEELS) */
}

#ifdef __ELF__
#if 0
/* VU: is that really architecture or implementation specific??? */
#define enter_kdebug(arg...)			\
__asm__ __volatile__ (				\
    "int $3;"					\
    "jmp 1f;"					\
    ".ascii	\"KD# " arg "\";"		\
    "1:")
#else
#define enter_kdebug(arg...)			\
__asm__ __volatile__ (				\
    "int $3			\n"		\
    "jmp 1f			\n"		\
    "mov $2f, %eax		\n"		\
    ".section .rodata		\n"		\
    "2:.ascii \"KD# " arg "\"	\n"		\
    ".byte 0			\n"		\
    ".previous			\n"		\
    "1:")
#endif
#elif defined(__APPLE_CC__)
#define enter_kdebug(arg...)			\
__asm__ __volatile__ (				\
    "int $3\n"					\
    "jmp 1f\n"					\
    "mov $2f, %eax\n"				\
    "2:.asciz 	\"KD# " arg "\"\n"		\
    "1:")
#else
#error unknown compiler
#endif


#endif /* !__ARCH__IA32__DEBUG_H__ */

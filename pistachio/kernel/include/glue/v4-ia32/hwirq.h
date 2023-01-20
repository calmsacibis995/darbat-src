/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-ia32/hwirq.h
 * Description:   Macros to define interrupt handler stubs for IA32
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
#ifndef __GLUE__V4_IA32__HWIRQ_H__
#define __GLUE__V4_IA32__HWIRQ_H__

#ifdef __ELF__
#define HW_IRQ(num)	                                        \
extern "C" void hwirq_##num();                                  \
    __asm__ (                                                   \
        "	.section .text					\n"\
        "	.align 16					\n"\
        "	.global hwirq_"#num"				\n"\
        "	.type hwirq_"#num",@function			\n"\
        "hwirq_"#num":						\n"\
        "	pusha			/* save regs    */	\n"\
	"	pushl	%ds					\n"\
	"	pushl	%es					\n"\
        "	pushl	$"#num"		/* irq number   */      \n"\
        "	jmp	hwirq_common	/* common stuff */      \n");
#elif defined (__APPLE_CC__)
#define HW_IRQ(num)	                                        \
extern "C" void hwirq_##num();                                  \
    __asm__ (                                                   \
        "	.section __TEXT,__text				\n"\
        "	.align 	4					\n"\
        "	.globl _hwirq_"#num"				\n"\
        "_hwirq_"#num":						\n"\
        "	pusha			/* save regs    */	\n"\
	"	pushl	%ds					\n"\
	"	pushl	%es					\n"\
        "	pushl	$"#num"		/* irq number   */      \n"\
        "	jmp	_hwirq_common	/* common stuff */      \n");
#else
#error "unknown compiler"
#endif


#if defined(CONFIG_IA32_SMALL_SPACES)
#define __SET_KDS						\
	"	mov	$" MKSTR(IA32_KDS) ", %eax		\n"\
	"	mov	%eax, %ds				\n"
#else
#define __SET_KDS
#endif


#ifdef __ELF__
#define HW_IRQ_COMMON()						\
    __asm__(							\
	"	.section .text					\n"\
	"	.align 16					\n"\
	"	.globl hwirq_common				\n"\
	"hwirq_common:						\n"\
	"	pushl	$intctrl	/* this pointer */	\n"\
	__SET_KDS						\
	"	call	intctrl_t_handle_irq			\n"\
	"	addl	$8,%esp		/* clear stack  */	\n"\
	"	popl	%es					\n"\
	"	popl	%ds					\n"\
	"	popa			/* restore regs */	\n"\
	"	iret						\n"\
	);
#elif defined (__APPLE_CC__)
#define HW_IRQ_COMMON()						\
    __asm__(							\
	"	.section __TEXT,__text				\n"\
	"	.align 4					\n"\
	"	.globl _hwirq_common				\n"\
	"_hwirq_common:						\n"\
	"	pushl	$_intctrl	/* this pointer */	\n"\
	__SET_KDS						\
	"	call	_intctrl_t_handle_irq			\n"\
	"	addl	$8,%esp		/* clear stack  */	\n"\
	"	popl	%es					\n"\
	"	popl	%ds					\n"\
	"	popa			/* restore regs */	\n"\
	"	iret						\n"\
	);
#else
#error "unknown compiler"
#endif

#endif /* !__GLUE__V4_IA32__HWIRQ_H__ */

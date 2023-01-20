/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     platform/pc99/startup.S
 * Description:   startup file for pc99 platform
 *		  initializes segments, invokes init_paging and
 *		  startup_system
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
 * $Id: startup.S,v 1.14 2004/05/31 14:19:52 stoess Exp $
 *                
 ********************************************************************/

	.globl	_start
	.globl	start
#ifdef __ELF__
	.section .init.startup32
#elif defined (__APPLE_CC__)
	.section __INIT,__startup32
#else
#error "unknown compiler"
#endif

start:	
_start:
	cli	/* disable int's */
	cld	/* clear direction flag */
	mov	%ds, %ax
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs
	mov	%ax, %ss

#ifdef CONFIG_EFI
	/* save arg pointer */
	mov	%esp, %ebx
#endif

	/* load temporary stack pointer */
	/*
	 * -gl important: _mini_stack-4,%esp will confuse the assembler
	 * on Mach-O
	 */
	lea	_mini_stack, %esp
	sub	$4, %esp

#ifdef CONFIG_EFI
	/* copy over the args */
	mov	0xc(%ebx), %eax
	push	%eax
	mov	0x8(%ebx), %eax
	push	%eax
	mov	0x4(%ebx), %eax
	push	%eax
#endif

	/* set up paging */
#ifdef __ELF__
	call	init_paging
#elif defined(__APPLE_CC__)
	call	_init_paging
#else
#error "unknown compiler"
#endif
	nop

#ifdef CONFIG_EFI
	/* dummy call frame thingy */
	push	0x0
#endif
	
	/* still running in 1:1 mapped area
	   jump to the top level init function */ 
#ifdef __ELF__
	jmp	startup_system
#elif defined(__APPLE_CC__)
	jmp	_startup_system
#else
#error "unknown compiler"
#endif

#ifdef __ELF__
        .align  16
#elif defined (__APPLE_CC__)
	.align	4
#else
#error "unknown compiler"
#endif
	.space	1024
_mini_stack:
#ifdef __ELF__
	.section .mb_header
	.align	4
#elif defined (__APPLE_CC__)
	.section __mb_header,__DATA
	.align 2
#else
#error "unknown compiler"
#endif
_mb_header:
        .long   0x1BADB002			/* magic */
        .long   0x00000000			/* flags */
        .long   - 0x00000000 - 0x1BADB002	/* check */

	

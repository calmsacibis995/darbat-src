/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * testmod.c
 *
 * Test module for liblkm
 *
 * This file is meant to test out the various types of things that need
 * to be handled for LKMs.  You can use this as a playground for your
 * tests.
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <l4/ipc.h>

#include <stdio.h>

/*
 * This is data.
 *
 */
static int	num = 0x42;
#ifdef __ELF__
int		anum = 0x43;
int		elfnum = 0x44;
#else
#ifdef __APPLE_CC__
extern int	elfnum;
int		applenum = 0xa991e;
#else
#error "Sorry, I can't work out what you are running on.
#endif
#endif

/*
 * This is bss.
 *
 */
static int	num2;

/*
 * This is extern'ed data symbol.
 *
 * XXX need xnuglue
 */
extern int hz;

static char	var[] = "testmod.kext: Hello world.";

void _start(void);
void f(void);
void g(void);
static int  (*printroutine)(const char *, ...);

/*
 * I'll put these in ELF ...
 *
 */
#ifdef __ELF__
void
f(void)
{

	printf("This is function f() speaking.\n");
}
#endif	/*__ELF__*/

#ifdef __APPLE_CC__
void
g(void)
{

	printf("This is function g() speaking.\n");
}
#endif	/*__APPLE_CC__*/
/*
 * _start specifies the entrypoint of the module.
 *
 */
void
_start(void)
{

	puts(var);	/* Easy. */
	/*
	 * XXX How the hell do we tell if we are running on Mach-O or not?
	 *
	 * Is there any easy compile-time way to tell?
	 */
#ifdef __ELF__
	puts("testmod.kext: You are running in ELF land.");
#else
#ifdef __APPLE_CC__
	puts("testmod.kext: You are running in Mach-O land.");
#else
#error "You are not running on a compiler which I recognize.  Sorry."
#endif
#endif
	printf("testmod.kext: this is a literal string.\n");
	printf("testmod.kext: num is %d\n", num);
	num2 = 0xcafebabe;
	printf("testmod.kext: num2 is %d\n", num2);
	printf("testmod.kext: hz = %d\n", hz);
	printf("testmod.kext: filename is %s (ABS)\n", __FILE__);
	/*
	 * In Mach-O, we try to load what was previously loaded into the
	 * ELF file.  (i.e. the Mach-O module "stacks" on top of the ELF
	 * one).
	 */
#ifdef __APPLE_CC__
#if 0	/* Disable stacking for now */
	printf("testmod.kext: elfnum is %d\n", elfnum);
#endif
	printf("testmod.kext: applenum is %d\n", applenum);
#endif

#ifdef __ELF__
	f();
#endif

#ifdef __APPLE_CC__
	g();
#endif
	printroutine = printf;
	printroutine("testmod.kext: This is printf() via function pointer.\n");
	printf("testmod.kext: Since you see this text it's probably OK.\n");
	printf("testmod.kext: Test complete, sleeping.\n");
	L4_WaitForever();
}


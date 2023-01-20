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
 * Butchered by glee at cse unsw.edu.au
 *
 */


/*********************************************************************
 *                
 * Copyright (C) 2001-2005,  Karlsruhe University
 *                
 * File path:     ia32-putc.cc
 * Description:   putc() for x86-based PCs, serial and screen
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
 * $Id: ia32-putc.cc,v 1.12 2005/03/10 15:25:34 ud3 Exp $
 *                
 ********************************************************************/

#include <l4/types.h>

#include <iguana/hardware.h>
#include <iguana/memsection.h>

#include <assert.h>
#include <stdio.h>

/* intel mac release framebuffer */
#include <fb.h>

#define DISPLAY ((char*)((0xb8000 - 0xa0000) + addr))
#define COLOR 7
#define NUM_LINES 25

void l4consinit(void);
void __l4_putc(int);

static uintptr_t		addr;

extern void *db_fb_base;

void
l4consinit(void)
{
#if 0  /* old sk00l! */
	memsection_ref_t	ref;
	int			rc;

	ref = memsection_create_user(131072, &addr);
	assert(ref);
	rc = hardware_back_memsection(ref, 0xa0000, MEM_NORMAL);
	printf("l4consinit: hw back rc = %d\n", rc);
#else
	// NOP
	// db_fb_base = fb_init(0);
#endif
}

void __l4_putc(int c)
{
    unsigned int i;

    // Shared cursor pointer
    static unsigned __l4_putc_cursor = 160 * (NUM_LINES - 1);

    // Create thread-local copy. Using proper locking would be better.
    unsigned __cursor = __l4_putc_cursor;

    switch(c) {
    case '\r':
        break;
    case '\n':
        do
	{
	    DISPLAY[__cursor++] = ' ';
	    DISPLAY[__cursor++] = COLOR;
	}
        while (__cursor % 160 != 0);
        break;
    case '\t':
        do
	  {
	    DISPLAY[__cursor++] = ' ';
	    DISPLAY[__cursor++] = COLOR;
	}
        while (__cursor % 16 != 0);
        break;
    default:
        DISPLAY[__cursor++] = c;
        DISPLAY[__cursor++] = COLOR;
    }
    if (__cursor == (160 * NUM_LINES)) {
	for (i = (160 / sizeof (L4_Word_t));
	     i < (160 / sizeof (L4_Word_t)) * NUM_LINES;
	     i++)
	    ((L4_Word_t *) DISPLAY)[i - 160 / sizeof (L4_Word_t)]
	      = ((L4_Word_t *) DISPLAY)[i];
	for (i = 0; i < 160 / sizeof (L4_Word_t); i++)
	    ((L4_Word_t *) DISPLAY)[160 / sizeof (L4_Word_t)
				  * (NUM_LINES-1) + i] = 0;
	__cursor -= 160;
    }

    // Write back thread-local cursor value
    __l4_putc_cursor = __cursor;
}


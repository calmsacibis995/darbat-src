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
/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  Karlsruhe University
 *                
 * File path:     mbi.h
 * Description:   
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
 * $Id: mbi.h,v 1.4 2004/04/14 18:47:58 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __KICKSTART__MBI_H__
#define __KICKSTART__MBI_H__

#include <l4/types.h>
#include <stdbool.h>

/**
   \file        mbi.h
   \brief       GRUB MultiBoot Info Structure

   Assumptions: Pointers are the same size as L4_Word_t
 */

typedef struct {
    L4_Word_t   start;          // Address of first byte of module
    L4_Word_t   end;            // Address of first byte after module
    char*       cmdline;        // Pointer to the command line
    L4_Word_t   entry;          // On IA-32, this officially is a
                                // padding field to make the structure
                                // 16 bytes large, but we abuse it
} mbi_module_t;

typedef struct {
	struct {
		L4_BITFIELD6(L4_Word_t,
			     mem         :1,
			     bootdev     :1,
			     cmdline     :1,
			     mods        :1,
			     syms        :2,
			     mmap        :1);
	} flags;
	
	/* Memory info in KB, valid if flags.mem is set */
	L4_Word_t           mem_lower;      //< base 0
	L4_Word_t           mem_upper;      //< base 1M
	
	/* valid if flags.bootdev is set */
	L4_Word_t           boot_device;
	
	/* The kernel command line.  Valid if flags.cmdline is set */
	char*               cmdline;
	
	/* Module info.  Valid if flags.mods is set */
	L4_Word_t           modcount;       //< Number of modules
	mbi_module_t*       mods;           //< Base of mbi_module_t table
	
	/* Kernel symbol info.  Valid if either one of flags:syms is set */
	L4_Word_t           syms[4];        
	
	/* BIOS memory map.  Valid if flags:mmap is set */
	L4_Word_t           mmap_length;    /*< Length */
	L4_Word_t           mmap_addr;      /*< Base address */
	
	L4_Word_t           drives_length;
	L4_Word_t           drives_addr;
	L4_Word_t           config_table;
	L4_Word_t           boot_loader_name;
	L4_Word_t           apm_table;
	L4_Word_t           vbe[4];
} mbi_t;

bool mbi_is_mem_region_free(mbi_t *mbi, L4_Word_t start, L4_Word_t size);
L4_Word_t mbi_get_size(mbi_t *mbi);
void copy_mbi(mbi_t *mbi, mbi_t *target);
mbi_t* prepare(void);

/*
 * Functions needed for loader format structure.
 */
bool mbi_probe (void);
L4_Word_t mbi_init (void);

#endif /* !__KICKSTART__MBI_H__ */

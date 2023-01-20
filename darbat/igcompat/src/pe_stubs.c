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
#include <stdio.h>
#include <assert.h>
#include <kern/kern_types.h>

#include <pexpert/pexpert.h>

/* this is a temporary hack */
boolean_t 
PE_parse_boot_arg(
	const char  *arg_string,
	void		*arg_ptr)
{
	return 0;
}

// virtual memory device like below, but now we have not so IOkit! :)
// static char bootargs[256] = "vmd0=0x20000.0x10000";
static char bootargs[256] = "";
char *
PE_boot_args(void)
{
	return bootargs;
}

int 
PE_current_console(PE_Video *info)
{

	//printf( "XXX: setting up bogus current console\n" );

	info->v_baseAddr = 0;
	info->v_rowBytes = 640;
	// info->v_width = 80;
	// info->v_height = 25;
	info->v_width = 0;
	info->v_height = 0;

	info->v_depth = 1;
	info->v_display = 0; /*TEXT_MODE */

	return 0;
}

extern void vcattach(void);

int 
PE_initialize_console( PE_Video * info, int op )
{
/*
	printf( ">>> in PE_initialize_console\n" );
	printf( "info: %p\n", info );
	printf( "op: %d\n", op );
*/

	return 0;
}

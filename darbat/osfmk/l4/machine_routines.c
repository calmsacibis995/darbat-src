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
#include <platforms.h>
#include <mach_kdb.h>

#include <string.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <mach/machine.h>
#include <mach/time_value.h>
#include <kern/spl.h>
#include <kern/assert.h>
#include <kern/debug.h>
#include <kern/misc_protos.h>
#include <kern/startup.h>
#include <kern/clock.h>
#include <kern/cpu_data.h>
#include <kern/machine.h>
#include <kern/thread.h>

#include <igcompat/darbat.h>

/* XXX */
extern void machine_startup(void);

void
machine_startup(void)
{
	kernel_bootstrap();
}



void
machine_init(void)
{
	printf( ">>> Doing machine_init\n" );

	clock_config();
}


#if 0
/* XXX */
struct tty;
extern int l4serial_wait_for_char(void);
extern void cons_cinput(char ch);

void
machine_idle_OLD(void)
{
	int c;

	// printf( ">>> Idle thread running\n" );

	// while(1)
	{
		/* block until we get a char */
		// printf( ">>> Idle thread waiting for char\n" );
		c = l4serial_wait_for_char();
		// printf( ">>> Idle thread got char '%c' (%d)\n", c, c );

		printf( "Feeding console...\n" );

		/* feed the char into the TTY subsystem */
		cons_cinput( c );

		// printf( "done cons_cinput\n" );

	}
}
#endif

extern void syscall_waitone(void);
// extern void syscall_yield(void);

void
machine_idle(void)
{
	// printf( ">>> Idle thread running\n" );

	/* block & wait */
	syscall_waitone();
	
	// printf( ">>> Idle thread awake\n" );
}

boolean_t 
ml_set_interrupts_enabled(boolean_t enable)
{
	return !enable;
}


/*ARGSUSED*/
/*
void
init_ast_check(
	__unused processor_t	processor)
{
}
*/


void
ml_cpu_up(void)
{
	return;
}

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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <igcompat/darbat.h>

#include <l4/kdebug.h>
#include <l4/schedule.h>
#include <l4/ipc.h>

#include <iguana/thread.h>

void l4serial_init(void);
int l4serial_wait_for_char(void);

L4_ThreadId_t darbat_main_thread, l4serial_thread;

int super_magic_serial_char = -1;

#if L4SERIAL
static void
l4serial_run( void *dummy )
{
	int c;
	int counter = 0;

	(void) dummy;

	while(1)
	{
		c = L4_KDB_ReadChar();

		/* ESC */
		if( c == 27 )
		{
			counter++;

			if( counter > 3 )
				L4_KDB_Enter( "kernel breakin" );
		}
		else if( c != -1 )
			counter = 0;

		/* some other char */
		if( c != -1 )
		{
			// printf( "got char '%c' (%d)\n", c, c );

			/* send a char */
			super_magic_serial_char = c;
			L4_Send_Nonblocking(darbat_main_thread);
		}

		L4_Yield();
	}
}
#endif

#if L4SERIAL
int
l4serial_wait_for_char(void)
{
	L4_MsgTag_t	tag;
	L4_ThreadId_t	unused;
	int		c;

	/* wait for a char */
	tag = L4_Wait(&unused);
	if (L4_IpcFailed(tag)) {
		printf("l4serial Error Code: %lx -- %lx\n", 
		       tag.raw, L4_ErrorCode());
	}

	/* pull the char out */
	c = super_magic_serial_char;

	/* clear for next time */
	super_magic_serial_char = -1;

	return c;
}
#else

int
l4serial_wait_for_char(void)
{
	int c = 0;

	L4_KDB_Enter( "in l4serial" );
	// c = darbat_cons_poll();

	return c;
}
#endif

void
l4serial_init(void)
{
#if L4SERIAL
	thread_ref_t tr;

	/* get our TID */
	darbat_main_thread = thread_l4tid( thread_myself() );

	printf( ">>> darbat main thread is %lx\n", darbat_main_thread.raw );

	/* create the thread */
	tr = thread_create_simple( l4serial_run, NULL, -1 );

	/* get its L4 ID for later */
	l4serial_thread = thread_l4tid( tr );

	printf( ">>> created L4 serial thread %lx\n", l4serial_thread.raw );
#endif
}



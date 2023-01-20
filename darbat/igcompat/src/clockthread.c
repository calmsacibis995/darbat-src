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
/* this is the L4 clock thread which sends 
 * timer ticks to darbat main kernel thread
 */


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <igcompat/darbat.h>

/* XXX: shouldn't really have IPC in here... */
#include <l4/ipc.h>

/* for panic */
#include <kern/debug.h>

#include "clockthread.h"

static L4_ThreadId_t darbat_main_thread;

static int
send_tick( void )
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

        L4_MsgClear(&msg);
        L4_Set_MsgLabel(&msg, CT_REQ_TIMER);
        L4_MsgLoad(&msg);
	
	tag = L4_Send(darbat_main_thread);

	if (L4_IpcFailed(tag))
		return 1;
	else
		return 0;
}

static int
clockthread_tick(void)
{
	int r;

	/* FIXME: Check for serial input for breakin */

	/* FIXME: have a tick bit */

	/* send a blocking IPC */
	r = send_tick();

	/* OK, keep ticking */
	return r;
}

static void
clockthread_run( void *dummy )
{
	printf( "clockthread running, going periodic...\n" );

	/* setup the timer */
	/* FIXME: use darwin units of time */
	darbat_periodic_function( clockthread_tick, 10 );

	panic( "clock thread returned, IPC error?" );
}

/* XXX */
extern L4_ThreadId_t darbat_l4id(void);

void
clockthread_init(void)
{
	int r;

	/* get our TID */
	darbat_main_thread = darbat_l4id(); 

	printf( ">>> darbat main thread is %lx\n", darbat_main_thread.raw );

	/* create the thread */
	r = darbat_create_kthread( clockthread_run, NULL );

	if( r == 0 )
		panic( "couldn't create darbat clock thread\n" );

	printf( ">>> created clock thread\n" );
}

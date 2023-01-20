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

#include <stdlib.h>

/* L4 stuff */
#include <l4/ipc.h>
#include <l4/message.h>

/* the system calls */
#include <syscallnums.h>
#include "libsystem.h"

L4_Word_t
do_syscall( L4_Word_t label,
	    unsigned int nargs, L4_Word_t a0, L4_Word_t a1, L4_Word_t a2,
	    L4_Word_t a3, L4_Word_t a4, L4_Word_t a5, L4_Word_t a6 )
{
	L4_Msg_t msg;
	L4_ThreadId_t dest;
	L4_MsgTag_t tag;
	L4_Word_t ret;

	/* setup the params */
	L4_MsgClear( &msg );
	L4_Set_MsgLabel( &msg, label );

	if( nargs > 0 )
		L4_MsgAppendWord( &msg, a0 );
	if( nargs > 1 )
		L4_MsgAppendWord( &msg, a1 );
	if( nargs > 2 )
		L4_MsgAppendWord( &msg, a2 );
	if( nargs > 3 )
		L4_MsgAppendWord( &msg, a3 );
	if( nargs > 4 )
		L4_MsgAppendWord( &msg, a4 );
	if( nargs > 5 )
		L4_MsgAppendWord( &msg, a5 );
	if( nargs > 6 )
		L4_MsgAppendWord( &msg, a6 );

	L4_MsgLoad( &msg );

	/* Get the destination */
	dest = L4_Pager();

	/* do the call */
	tag = L4_Call( dest );

	if( L4_IpcFailed( tag ) )
	{
		L4_Word_t error;
		int *foo;
		error = L4_ErrorCode();

		/* DIE! */
		*foo = error;
	}

	/* pull out the reply */
	L4_MsgStore( tag, &msg );

	ret = L4_MsgWord( &msg, 0 );

	return ret;
}

int
open(const char *pathname, int flags)
{
	return do_syscall( SYSCALL_OPEN, 3, 
			   (L4_Word_t) pathname, flags, 0644,
			   0, 0, 0, 0);
}


ssize_t
write(int fd, const void *buf, size_t count)
{
	return (ssize_t) do_syscall( SYSCALL_WRITE, 3, 
				     fd, (L4_Word_t) buf, count,
				     0, 0, 0, 0);
}


ssize_t
read(int fd, void *buf, size_t count)
{
	return (ssize_t) do_syscall( SYSCALL_READ, 3, 
				     fd, (L4_Word_t) buf, count,
				     0, 0, 0, 0);
}

int
mount(const char *type, const char *dir, int flags, void *data)
{
	return (ssize_t) do_syscall( SYSCALL_MOUNT, 4, 
				     (L4_Word_t) type, 
				     (L4_Word_t) dir, 
				     flags,(L4_Word_t) data, 
				     0, 0, 0);
}

int 
close(int d)
{
	return (int) do_syscall( SYSCALL_CLOSE, 1,
				 d, 0, 0, 0, 0, 0, 0 );
}

int
getdirentries(int fd, char *buf, int nbytes, long *basep)
{
	return (int) do_syscall( SYSCALL_GETDIRENTRIES, 4,
				 fd, (L4_Word_t) buf, 
				 nbytes, (L4_Word_t) basep,
				 0, 0, 0 );
}

int 
chdir(const char *path)
{
	return (int) do_syscall( SYSCALL_CHDIR, 1,
				 (L4_Word_t) path,
				 0, 0, 0, 0, 0, 0 );
}

pid_t
fork(void)
{
	return (ssize_t) do_syscall( SYSCALL_FORK, 0, 0, 0, 0, 0, 0, 0, 0 );
}

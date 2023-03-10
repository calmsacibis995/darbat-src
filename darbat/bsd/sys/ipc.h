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
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
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
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ipc.h	8.4 (Berkeley) 2/19/95
 */

/*
 * SVID compatible ipc.h file
 */
#ifndef _SYS_IPC_H_
#define _SYS_IPC_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>

#include <sys/_types.h>

/*
 * [XSI] The uid_t, gid_t, mode_t, and key_t types SHALL be defined as
 * described in <sys/types.h>.
 */
#ifndef _UID_T
typedef __darwin_uid_t	uid_t;		/* user id */
#define _UID_T
#endif

#ifndef _GID_T
typedef __darwin_gid_t	gid_t;
#define _GID_T
#endif

#ifndef	_MODE_T
typedef	__darwin_mode_t	mode_t;
#define _MODE_T
#endif

#ifndef _KEY_T
#define _KEY_T
typedef	__int32_t	key_t;
#endif

/*
 * Technically, we should force all code references to the new structure
 * definition, not in just the standards conformance case, and leave the
 * legacy interface there for binary compatibility only.  Currently, we
 * are only forcing this for programs requesting standards conformance.
 */
#if defined(__POSIX_C_SOURCE) || defined(kernel) || defined(__LP64__)
/*
 * [XSI] Information used in determining permission to perform an IPC
 * operation
 */
struct __ipc_perm_new {
	uid_t		uid;		/* [XSI] Owner's user ID */
	gid_t		gid;		/* [XSI] Owner's group ID */
	uid_t		cuid;		/* [XSI] Creator's user ID */
	gid_t		cgid;		/* [XSI] Creator's group ID */
	mode_t		mode;		/* [XSI] Read/write permission */
	unsigned short	_seq;		/* Reserved for internal use */
	key_t		_key;		/* Reserved for internal use */
};
#define	ipc_perm	__ipc_perm_new
#else	/* !_POSIX_C_SOURCE */
#define	ipc_perm	__ipc_perm_old
#endif	/* !_POSIX_C_SOURCE */

#if !defined(__POSIX_C_SOURCE) && !defined(__LP64__)
/*
 * Legacy structure; this structure is maintained for binary backward
 * compatability with previous versions of the interface.  New code
 * should not use this interface, since ID values may be truncated.
 */
struct __ipc_perm_old {
	__uint16_t	cuid;		/* Creator's user ID */
	__uint16_t	cgid;		/* Creator's group ID */
	__uint16_t	uid;		/* Owner's user ID */
	__uint16_t	gid;		/* Owner's group ID */
	mode_t		mode;		/* Read/Write permission */
	__uint16_t	seq;		/* Reserved for internal use */
	key_t		key;		/* Reserved for internal use */
};
#endif	/* !_POSIX_C_SOURCE */

/*
 * [XSI] Definitions shall be provided for the following constants:
 */

/* Mode bits */
#define	IPC_CREAT	001000		/* Create entry if key does not exist */
#define	IPC_EXCL	002000		/* Fail if key exists */
#define	IPC_NOWAIT	004000		/* Error if request must wait */

/* Keys */
#define	IPC_PRIVATE	((key_t)0)	/* Private key */

/* Control commands */
#define	IPC_RMID	0		/* Remove identifier */
#define	IPC_SET		1		/* Set options */
#define	IPC_STAT	2		/* Get options */


#ifndef _POSIX_C_SOURCE

/* common mode bits */
#define	IPC_R		000400		/* Read permission */
#define	IPC_W		000200		/* Write/alter permission */
#define	IPC_M		010000		/* Modify control info permission */

#endif	/* !_POSIX_C_SOURCE */


#ifdef BSD_KERNEL_PRIVATE
/*
 * Kernel implementation details which should not be utilized by user
 * space programs.
 */

/* Macros to convert between ipc ids and array indices or sequence ids */
#define	IPCID_TO_IX(id)		((id) & 0xffff)
#define	IPCID_TO_SEQ(id)	(((id) >> 16) & 0xffff)
#define	IXSEQ_TO_IPCID(ix,perm)	(((perm.seq) << 16) | (ix & 0xffff))

struct ucred;

int	ipcperm(struct ucred *, struct ipc_perm *, int);
#endif /* BSD_KERNEL_PRIVATE */

#ifndef KERNEL

__BEGIN_DECLS
/* [XSI] */
key_t	ftok(const char *, int);
__END_DECLS

#endif	/* !KERNEL */

#endif /* !_SYS_IPC_H_ */

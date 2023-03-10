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
 * Copyright (c) 1995, 1998 Apple Computer, Inc. All Rights Reserved.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)specdev.h	8.6 (Berkeley) 5/21/95
 */

#ifndef _MISCFS_SPECFS_SPECDEV_H_
#define _MISCFS_SPECFS_SPECDEV_H_

#include  <sys/appleapiopts.h>

#ifdef __APPLE_API_PRIVATE
#include <vfs/vfs_support.h>

/*
 * This structure defines the information maintained about
 * special devices. It is allocated in checkalias and freed
 * in vgone.
 */
struct specinfo {
	struct	vnode **si_hashchain;
	struct	vnode *si_specnext;
	long	si_flags;
	dev_t	si_rdev;
	daddr_t	si_size;		/* device block size in bytes */
	daddr64_t	si_lastr;	/* last read blkno (read-ahead) */
	u_int64_t	si_devsize;	/* actual device size in bytes */
};
/*
 * Exported shorthand
 */
#define v_rdev v_specinfo->si_rdev
#define v_hashchain v_specinfo->si_hashchain
#define v_specnext v_specinfo->si_specnext
#define v_specflags v_specinfo->si_flags
#define v_specsize v_specinfo->si_size
#define v_specdevsize v_specinfo->si_devsize
#define v_speclastr v_specinfo->si_lastr

/*
 * Flags for specinfo
 */
#define	SI_MOUNTEDON	0x0001	/* block special device is mounted on */

/*
 * Special device management
 */
#define	SPECHSZ	64
#if	((SPECHSZ&(SPECHSZ-1)) == 0)
#define	SPECHASH(rdev)	(((rdev>>5)+(rdev))&(SPECHSZ-1))
#else
#define	SPECHASH(rdev)	(((unsigned)((rdev>>5)+(rdev)))%SPECHSZ)
#endif

extern struct vnode *speclisth[SPECHSZ];

/*
 * Prototypes for special file operations on vnodes.
 */
extern	int (**spec_vnodeop_p)(void *);
struct	nameidata;
struct	componentname;
struct	ucred;
struct	flock;
struct	buf;
struct	uio;

int	spec_ebadf(void *);

int	spec_lookup (struct vnop_lookup_args *);
#define spec_create (int (*) (struct  vnop_access_args *))err_create
#define spec_mknod (int (*) (struct  vnop_access_args *))err_mknod
int	spec_open (struct vnop_open_args *);
int	spec_close (struct vnop_close_args *);
#define spec_access (int (*) (struct  vnop_access_args *))spec_ebadf
#define spec_getattr (int (*) (struct  vnop_getattr_args *))spec_ebadf
#define spec_setattr (int (*) (struct  vnop_setattr_args *))spec_ebadf
int	spec_read (struct vnop_read_args *);
int	spec_write (struct vnop_write_args *);
int	spec_ioctl (struct vnop_ioctl_args *);
int	spec_select (struct vnop_select_args *);
#define spec_revoke (int (*) (struct  vnop_access_args *))nop_revoke
#define spec_mmap (int (*) (struct  vnop_access_args *))err_mmap
int	spec_fsync (struct  vnop_fsync_args *);
int	spec_fsync_internal (vnode_t, int, vfs_context_t);
#define spec_remove (int (*) (struct  vnop_access_args *))err_remove
#define spec_link (int (*) (struct  vnop_access_args *))err_link
#define spec_rename (int (*) (struct  vnop_access_args *))err_rename
#define spec_mkdir (int (*) (struct  vnop_access_args *))err_mkdir
#define spec_rmdir (int (*) (struct  vnop_access_args *))err_rmdir
#define spec_symlink (int (*) (struct  vnop_access_args *))err_symlink
#define spec_readdir (int (*) (struct  vnop_access_args *))err_readdir
#define spec_readlink (int (*) (struct  vnop_access_args *))err_readlink
#define spec_inactive (int (*) (struct  vnop_access_args *))nop_inactive
#define spec_reclaim (int (*) (struct  vnop_access_args *))nop_reclaim
#define spec_lock (int (*) (struct  vnop_access_args *))nop_lock
#define spec_unlock (int (*)(struct  vnop_access_args *))nop_unlock
int	spec_strategy (struct vnop_strategy_args *);
#define spec_islocked (int (*) (struct  vnop_access_args *))nop_islocked
int	spec_pathconf (struct vnop_pathconf_args *);
#define spec_advlock (int (*) (struct  vnop_access_args *))err_advlock
#define spec_blkatoff (int (*) (struct  vnop_access_args *))err_blkatoff
#define spec_valloc (int (*) (struct  vnop_access_args *))err_valloc
#define spec_vfree (int (*) (struct  vnop_access_args *))err_vfree
#define spec_bwrite (int (*) (struct  vnop_bwrite_args *))nop_bwrite
int     spec_devblocksize (struct vnop_devblocksize_args *);
int spec_blktooff (struct  vnop_blktooff_args *);
int spec_offtoblk (struct  vnop_offtoblk_args *);
int spec_blockmap (struct  vnop_blockmap_args *);

#endif /* __APPLE_API_PRIVATE */
#endif /* _MISCFS_SPECFS_SPECDEV_H_ */

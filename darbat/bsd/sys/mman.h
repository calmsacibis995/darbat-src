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
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*-
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)mman.h	8.1 (Berkeley) 6/2/93
 */

/*
 * Currently unsupported:
 *
 * [TYM]	POSIX_TYPED_MEM_ALLOCATE
 * [TYM]	POSIX_TYPED_MEM_ALLOCATE_CONTIG
 * [TYM]	POSIX_TYPED_MEM_MAP_ALLOCATABLE
 * [TYM]	struct posix_typed_mem_info
 * [TYM]	posix_mem_offset()
 * [TYM]	posix_typed_mem_get_info()
 * [TYM]	posix_typed_mem_open()
 */

#ifndef	_SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>

#include <sys/_types.h>

/*
 * [various] The mode_t, off_t, and size_t types shall be defined as
 * described in <sys/types.h>
 */
#ifndef	_MODE_T
typedef	__darwin_mode_t	mode_t;
#define _MODE_T
#endif

#ifndef _OFF_T
typedef __darwin_off_t	off_t;
#define _OFF_T
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef __darwin_size_t	size_t;
#endif


/*
 * Protections are chosen from these bits, or-ed together
 */
#define	PROT_NONE	0x00	/* [MC2] no permissions */
#define	PROT_READ	0x01	/* [MC2] pages can be read */
#define	PROT_WRITE	0x02	/* [MC2] pages can be written */
#define	PROT_EXEC	0x04	/* [MC2] pages can be executed */

/*
 * Flags contain sharing type and options.
 * Sharing types; choose one.
 */
#define	MAP_SHARED	0x0001		/* [MF|SHM] share changes */
#define	MAP_PRIVATE	0x0002		/* [MF|SHM] changes are private */
#ifndef _POSIX_C_SOURCE
#define	MAP_COPY	MAP_PRIVATE	/* Obsolete */
#endif	/* !_POSIX_C_SOURCE */

/*
 * Other flags
 */
#define	MAP_FIXED	 0x0010	/* [MF|SHM] interpret addr exactly */
#ifndef _POSIX_C_SOURCE
#define	MAP_RENAME	 0x0020	/* Sun: rename private pages to file */
#define	MAP_NORESERVE	 0x0040	/* Sun: don't reserve needed swap area */
#define	MAP_RESERVED0080 0x0080	/* previously unimplemented MAP_INHERIT */
#define	MAP_NOEXTEND	 0x0100	/* for MAP_FILE, don't change file size */
#define	MAP_HASSEMAPHORE 0x0200	/* region may contain semaphores */
#endif	/* !_POSIX_C_SOURCE */

/*
 * Process memory locking
 */
#define MCL_CURRENT	0x0001	/* [ML] Lock only current memory */
#define MCL_FUTURE	0x0002	/* [ML] Lock all future memory as well */

/*
 * Error return from mmap()
 */
#define MAP_FAILED	((void *)-1)	/* [MF|SHM] mmap failed */

/*
 * msync() flags
 */
#define MS_ASYNC	0x0001	/* [MF|SIO] return immediately */
#define MS_INVALIDATE	0x0002	/* [MF|SIO] invalidate all cached data */
#define	MS_SYNC		0x0010	/* [MF|SIO] msync synchronously */

#ifndef _POSIX_C_SOURCE
#define MS_KILLPAGES    0x0004  /* invalidate pages, leave mapped */
#define MS_DEACTIVATE   0x0008  /* deactivate pages, leave mapped */

/*
 * Mapping type
 */
#define	MAP_FILE	0x0000	/* map from file (default) */
#define	MAP_ANON	0x1000	/* allocated from memory, swap space */
#endif	/* !_POSIX_C_SOURCE */


/*
 * Advice to madvise
 */
#define	POSIX_MADV_NORMAL	0	/* [MC1] no further special treatment */
#define	POSIX_MADV_RANDOM	1	/* [MC1] expect random page refs */
#define	POSIX_MADV_SEQUENTIAL	2	/* [MC1] expect sequential page refs */
#define	POSIX_MADV_WILLNEED	3	/* [MC1] will need these pages */
#define	POSIX_MADV_DONTNEED	4	/* [MC1] dont need these pages */

#ifndef _POSIX_C_SOURCE
#define	MADV_NORMAL		POSIX_MADV_NORMAL
#define	MADV_RANDOM		POSIX_MADV_RANDOM
#define	MADV_SEQUENTIAL		POSIX_MADV_SEQUENTIAL
#define	MADV_WILLNEED		POSIX_MADV_WILLNEED
#define	MADV_DONTNEED		POSIX_MADV_DONTNEED
#define	MADV_FREE		5	/* pages unneeded, discard contents */

/*
 * Return bits from mincore
 */
#define	MINCORE_INCORE	 	 0x1	 /* Page is incore */
#define	MINCORE_REFERENCED	 0x2	 /* Page has been referenced by us */
#define	MINCORE_MODIFIED	 0x4	 /* Page has been modified by us */
#define	MINCORE_REFERENCED_OTHER 0x8	 /* Page has been referenced */
#define	MINCORE_MODIFIED_OTHER	0x10	 /* Page has been modified */
#endif	/* !_POSIX_C_SOURCE */


#ifndef KERNEL

__BEGIN_DECLS
/* [ML] */
int	mlockall(int);
int	munlockall(void);
/* [MR] */
int	mlock(const void *, size_t);
#ifndef _MMAP
#define	_MMAP
/* [MC3]*/
void *	mmap(void *, size_t, int, int, int, off_t) __DARWIN_ALIAS(mmap);
#endif
/* [MPR] */
int	mprotect(void *, size_t, int) __DARWIN_ALIAS(mprotect);
/* [MF|SIO] */
int	msync(void *, size_t, int) __DARWIN_ALIAS(msync);
/* [MR] */
int	munlock(const void *, size_t);
/* [MC3]*/
int	munmap(void *, size_t) __DARWIN_ALIAS(munmap);
/* [SHM] */
int	shm_open(const char *, int, ...);
int	shm_unlink(const char *);
/* [ADV] */
int	posix_madvise(void *, size_t, int);

#ifndef _POSIX_C_SOURCE
int	madvise(void *, size_t, int);
int	mincore(const void *, size_t, char *);
int	minherit(void *, size_t, int);
#endif
__END_DECLS

#else	/* KERNEL */

void pshm_cache_init(void);	/* for bsd_init() */

/*
 * XXX routine exported by posix_shm.c, but never used there, only used in
 * XXX kern_mman.c in the implementation of mmap().
 */
struct mmap_args;
struct fileproc;
int pshm_mmap(struct proc *p, struct mmap_args *uap, user_addr_t *retval,
		struct fileproc *fp, off_t pageoff);
/* Really need to overhaul struct fileops to avoid this... */
struct pshmnode;
struct stat;
int pshm_stat(struct pshmnode *pnode, struct stat *sb);
struct fileproc;
int pshm_truncate(struct proc *p, struct fileproc *fp, int fd, off_t length, register_t *retval);

#endif /* KERNEL */
#endif /* !_SYS_MMAN_H_ */

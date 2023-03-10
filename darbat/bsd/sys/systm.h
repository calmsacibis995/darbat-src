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
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1982, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *	@(#)systm.h	8.7 (Berkeley) 3/29/95
 */
 
/*
 * The `securelevel' variable controls the security level of the system.
 * It can only be decreased by process 1 (/sbin/init).
 *
 * Security levels are as follows:
 *   -1	permannently insecure mode - always run system in level 0 mode.
 *    0	insecure mode - immutable and append-only flags make be turned off.
 *	All devices may be read or written subject to permission modes.
 *    1	secure mode - immutable and append-only flags may not be changed;
 *	raw disks of mounted filesystems, /dev/mem, and /dev/kmem are
 *	read-only.
 *    2	highly secure mode - same as (1) plus raw disks are always
 *	read-only whether mounted or not. This level precludes tampering 
 *	with filesystems by unmounting them, but also inhibits running
 *	newfs while the system is secured.
 *
 * In normal operation, the system runs in level 0 mode while single user
 * and in level 1 mode while multiuser. If level 2 mode is desired while
 * running multiuser, it can be set in the multiuser startup script
 * (/etc/rc.local) using sysctl(1). If it is desired to run the system
 * in level 0 mode while multiuser, initialize the variable securelevel
 * in /sys/kern/kern_sysctl.c to -1. Note that it is NOT initialized to
 * zero as that would allow the vmunix binary to be patched to -1.
 * Without initialization, securelevel loads in the BSS area which only
 * comes into existence when the kernel is loaded and hence cannot be
 * patched by a stalking hacker.
 */

#ifndef _SYS_SYSTM_H_
#define	_SYS_SYSTM_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#ifdef BSD_KERNEL_PRIVATE
#include <sys/tty.h>
#include <sys/vm.h>
#include <sys/linker_set.h>
#endif
#include <sys/proc.h>
__BEGIN_DECLS
#ifdef KERNEL
#include <libkern/libkern.h>
#endif
#include <kern/thread.h>
#include <kern/debug.h>
__END_DECLS

#ifdef BSD_KERNEL_PRIVATE
extern char version[];		/* system version */
extern char copyright[];	/* system copyright */


extern int	boothowto;	/* reboot flags, from console subsystem */
extern int	show_space;

extern int nblkdev;		/* number of entries in bdevsw */
extern int nchrdev;		/* number of entries in cdevsw */
#endif /* BSD_KERNEL_PRIVATE */

#ifdef KERNEL_PRIVATE
#define NO_FUNNEL 0
#define KERNEL_FUNNEL 1

extern int securelevel;		/* system security level */
extern dev_t rootdev;		/* root device */
extern struct vnode *rootvp;	/* vnode equivalent to above */
extern funnel_t * kernel_flock;

#endif /* KERNEL_PRIVATE */

#define SYSINIT(a,b,c,d,e)
#define MALLOC_DEFINE(a,b,c)

#define getenv_int(a,b) (*b = 0)
#define	KASSERT(exp,msg)

/*
 * General function declarations.
 */
__BEGIN_DECLS
int	nullop(void);
int	nulldev(void);
int	enoioctl(void);
int	enxio(void);
int	eopnotsupp(void);
int	einval(void);

#ifdef BSD_KERNEL_PRIVATE
int	seltrue(dev_t dev, int which, struct proc *p);
void	ttyprintf(struct tty *, const char *, ...);
void	realitexpire(void *);
int	hzto(struct timeval *tv);
#endif /* __APPLE_API_UNSTABLE */

void	*hashinit(int count, int type, u_long *hashmask);

void	tablefull(const char *);

int	kvprintf(char const *, void (*)(int, void*), void *, int,
		      __darwin_va_list);

void	uprintf(const char *, ...);


void	ovbcopy(const void *from, void *to, size_t len);
int	copywithin(void *saddr, void *daddr, size_t len);

int	fubyte(user_addr_t addr);
int	fuibyte(user_addr_t addr);
int	subyte(user_addr_t addr, int byte);
int	suibyte(user_addr_t addr, int byte);
long   fuword(user_addr_t addr);
long   fuiword(user_addr_t addr);
int    suword(user_addr_t addr, long word);
int    suiword(user_addr_t addr, long word);
int64_t	fulong(user_addr_t addr);
int	sulong(user_addr_t addr, int64_t longword);
uint64_t fuulong(user_addr_t addr);
int	suulong(user_addr_t addr, uint64_t ulongword);
#define fusize(_a)	((user_size_t)fulong(_a))
#define susize(_a, _s)	sulong((_a), (_s))
#define fuptr(a)	((user_addr_t)fulong(_a)
#define suptr(_a, _p)	sulong((_a), (_p))
int	useracc(user_addr_t addr, user_size_t len,int prot);

typedef void (*timeout_fcn_t)(void *);
#ifdef KERNEL_PRIVATE
void	timeout(void (*)(void *), void *arg, int ticks);
void	untimeout(void (*)(void *), void *arg);
#endif /* KERNEL_PRIVATE */
void	bsd_timeout(void (*)(void *), void *arg, struct timespec * ts);
void	bsd_untimeout(void (*)(void *), void *arg);

void	set_fsblocksize(struct vnode *);

#ifdef BSD_KERNEL_PRIVATE
int	vslock(user_addr_t addr, user_size_t len);
int	vsunlock(user_addr_t addr, user_size_t len, int dirtied);
int	clone_system_shared_regions(int shared_regions_active,
				    int chain_regions,
				    int base_vnode);

extern kern_return_t bsd_exception(int, exception_data_type_t codes[], int);
extern void	bsdinit_task(void);
void	bsd_hardclock(boolean_t usermode, caddr_t pc, int numticks);
void	gatherstats(boolean_t usermode, caddr_t pc);

void	initclocks(void);

void	startprofclock(struct proc *);
void	stopprofclock(struct proc *);
void	setstatclockrate(int hzrate);

struct time_value;
void	get_procrustime(struct time_value *tv);

void	load_init_program(struct proc *p);
#endif /* BSD_KERNEL_PRIVATE */


__END_DECLS

#endif /* !_SYS_SYSTM_H_ */


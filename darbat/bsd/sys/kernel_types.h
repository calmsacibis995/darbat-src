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
#ifndef _KERN_SYS_KERNELTYPES_H_
#define _KERN_SYS_KERNELTYPES_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>

#ifdef BSD_BUILD
/* Macros(?) to clear/set/test flags. */
#define	SET(t, f)	(t) |= (f)
#define	CLR(t, f)	(t) &= ~(f)
#define	ISSET(t, f)	((t) & (f))
#endif


typedef int errno_t;
typedef int64_t daddr64_t;

typedef	int64_t	ino64_t;

#ifndef BSD_BUILD
struct buf;
typedef struct buf * buf_t;

struct file;
typedef struct file * file_t;

struct ucred;
typedef struct ucred * ucred_t;

struct mount;
typedef struct mount * mount_t;

#ifdef TBDDDD
typedef struct fsid { int32_t val[2]; } fsid_t;	/* file system id type */
#endif /* TBDDDD */

struct vnode;
typedef struct vnode * vnode_t;

struct proc;
typedef struct proc * proc_t;

struct uio;
typedef struct uio * uio_t;

struct vfs_context;
typedef struct vfs_context * vfs_context_t;

struct vfstable;
typedef struct vfstable * vfstable_t;

struct __ifnet;
struct __mbuf;
struct __pkthdr;
struct __socket;
struct __sockopt;
struct __ifaddr;
struct __ifmultiaddr;
struct __ifnet_filter;
struct __rtentry;

typedef	struct __ifnet*			ifnet_t;
typedef	struct __mbuf*			mbuf_t;
typedef	struct __pkthdr*		pkthdr_t;
typedef	struct __socket*		socket_t;
typedef struct __sockopt*		sockopt_t;
typedef struct __ifaddr*		ifaddr_t;
typedef struct __ifmultiaddr*	ifmultiaddr_t;
typedef struct __ifnet_filter*	interface_filter_t;
typedef struct __rtentry*		route_t;

#else /* BSD_BUILD */

typedef struct buf * buf_t;
typedef struct file * file_t;
typedef struct ucred * ucred_t;
typedef struct mount * mount_t;
typedef struct vnode * vnode_t;
typedef struct proc * proc_t;
typedef struct uio * uio_t;
typedef struct user_iovec * user_iovec_t;
typedef struct vfs_context * vfs_context_t;
typedef struct vfstable * vfstable_t;

#if KERNEL_PRIVATE
typedef struct kern_iovec * kern_iovec_t;
typedef	struct ifnet*		ifnet_t;
typedef	struct mbuf*		mbuf_t;
typedef	struct pkthdr*		pkthdr_t;
typedef	struct socket*		socket_t;
typedef struct sockopt*		sockopt_t;
typedef struct ifaddr*		ifaddr_t;
typedef struct ifmultiaddr*	ifmultiaddr_t;
typedef struct ifnet_filter*	interface_filter_t;
typedef struct rtentry*		route_t;
#endif /* KERNEL_PRIVATE */

#endif /* !BSD_BUILD */

#ifndef _KAUTH_GUID
#define _KAUTH_GUID
/* Apple-style globally unique identifier */
typedef struct {
#define KAUTH_GUID_SIZE	16	/* 128-bit identifier */
	unsigned char g_guid[KAUTH_GUID_SIZE];
} guid_t;
#define _GUID_T
#endif /* _KAUTH_GUID */

#ifndef _KAUTH_ACE
#define _KAUTH_ACE
struct kauth_ace;
typedef struct kauth_ace * kauth_ace_t;
#endif
#ifndef _KAUTH_ACL
#define _KAUTH_ACL
struct kauth_acl;
typedef struct kauth_acl * kauth_acl_t;
#endif
#ifndef _KAUTH_FILESEC
#define _KAUTH_FILESEC
struct kauth_filesec;
typedef struct kauth_filesec * kauth_filesec_t;
#endif

#endif /* !_KERN_SYS_KERNELTYPES_H_ */

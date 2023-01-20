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

#ifndef __IG_BSD_INIT__
#define __IG_BSD_INIT__

extern void file_lock_init(void);
extern void kmeminit(void);
extern void bsd_bufferinit(void);
extern void ubc_init(void);
extern void vfsinit(void);
extern void mbinit(void);

extern void knote_init(void);
extern void aio_init(void);
extern void pipeinit(void);
extern void psem_cache_init(void);
extern void sysctl_register_fixed(void); 
extern void dlil_init(void);
extern void proto_kpi_init(void);
extern void socketinit(void);
extern void domaininit(void);

extern int  ether_family_init(void);
extern void vnode_pager_bootstrap(void);
extern void bsd_utaskbootstrap(void);

extern void kminit(void);

extern void sysv_shm_lock_init(void);
extern void sysv_sem_lock_init(void);
extern void sysv_msg_lock_init(void);
extern void pshm_lock_init(void);
extern void psem_lock_init(void);

extern void klogwakeup(void);

/* from places other than bsd_init */
/*__private_extern__*/ void vntblinit(void);
void nchinit(void);

#if DEVFS
extern int devfs_kernel_mount(char * str);
#endif

#endif /* __IG_BSD_INIT__ */

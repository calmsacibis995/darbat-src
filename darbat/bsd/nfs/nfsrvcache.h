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
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
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
 *	@(#)nfsrvcache.h	8.3 (Berkeley) 3/30/95
 * FreeBSD-Id: nfsrvcache.h,v 1.9 1997/06/03 17:22:47 dfr Exp $
 */


#ifndef _NFS_NFSRVCACHE_H_
#define _NFS_NFSRVCACHE_H_

#include <sys/appleapiopts.h>

#ifdef __APPLE_API_PRIVATE
/*
 * Definitions for the server recent request cache
 */

#define	NFSRVCACHESIZ	64

struct nfsrvcache {
	TAILQ_ENTRY(nfsrvcache) rc_lru;		/* LRU chain */
	LIST_ENTRY(nfsrvcache) rc_hash;		/* Hash chain */
	u_long	rc_xid;				/* rpc id number */
	union {
		mbuf_t ru_repmb;		/* Reply mbuf list OR */
		int ru_repstat;			/* Reply status */
	} rc_un;
	union nethostaddr rc_haddr;		/* Host address */
	u_int32_t rc_proc;			/* rpc proc number */
	u_char	rc_state;		/* Current state of request */
	u_char	rc_flag;		/* Flag bits */
};

#define	rc_reply	rc_un.ru_repmb
#define	rc_status	rc_un.ru_repstat
#define	rc_inetaddr	rc_haddr.had_inetaddr
#define	rc_nam		rc_haddr.had_nam

/* Cache entry states */
#define	RC_UNUSED	0
#define	RC_INPROG	1
#define	RC_DONE		2

/* Return values */
#define	RC_DROPIT	0
#define	RC_REPLY	1
#define	RC_DOIT		2
#define	RC_CHECKIT	3

/* Flag bits */
#define	RC_LOCKED	0x01
#define	RC_WANTED	0x02
#define	RC_REPSTATUS	0x04
#define	RC_REPMBUF	0x08
#define	RC_INETADDR	0x20
#define	RC_NAM		0x40

#endif /* __APPLE_API_PRIVATE */
#endif /* _NFS_NFSRVCACHE_H_ */

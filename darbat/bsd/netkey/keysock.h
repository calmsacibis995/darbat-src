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
/*	$KAME: keysock.h,v 1.7 2000/03/25 07:24:14 sumikawa Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETKEY_KEYSOCK_H_
#define _NETKEY_KEYSOCK_H_
#include <sys/appleapiopts.h>

/* statistics for pfkey socket */
struct pfkeystat {
	/* kernel -> userland */
	u_quad_t out_total;		/* # of total calls */
	u_quad_t out_bytes;		/* total bytecount */
	u_quad_t out_msgtype[256];	/* message type histogram */
	u_quad_t out_invlen;		/* invalid length field */
	u_quad_t out_invver;		/* invalid version field */
	u_quad_t out_invmsgtype;	/* invalid message type field */
	u_quad_t out_tooshort;		/* msg too short */
	u_quad_t out_nomem;		/* memory allocation failure */
	u_quad_t out_dupext;		/* duplicate extension */
	u_quad_t out_invexttype;	/* invalid extension type */
	u_quad_t out_invsatype;		/* invalid sa type */
	u_quad_t out_invaddr;		/* invalid address extension */
	/* userland -> kernel */
	u_quad_t in_total;		/* # of total calls */
	u_quad_t in_bytes;		/* total bytecount */
	u_quad_t in_msgtype[256];	/* message type histogram */
	u_quad_t in_msgtarget[3];	/* one/all/registered */
	u_quad_t in_nomem;		/* memory allocation failure */
	/* others */
	u_quad_t sockerr;		/* # of socket related errors */
};

#define KEY_SENDUP_ONE		0
#define KEY_SENDUP_ALL		1
#define KEY_SENDUP_REGISTERED	2

#ifdef KERNEL_PRIVATE
#ifdef KERNEL
struct keycb {
	struct rawcb kp_raw;	/* rawcb */
	int kp_promisc;		/* promiscuous mode */
	int kp_registered;	/* registered socket */
};

extern struct pfkeystat pfkeystat;

#ifdef __APPLE__
extern int key_output(struct mbuf *, struct socket* so);
#else
extern int key_output(struct mbuf *, ...);
#endif
extern int key_usrreq(struct socket *,
	int, struct mbuf *, struct mbuf *, struct mbuf *);

extern int key_sendup(struct socket *, struct sadb_msg *, u_int, int);
extern int key_sendup_mbuf(struct socket *, struct mbuf *, int);
#endif /* KERNEL */
#endif /* KERNEL_PRIVATE */

#endif /*_NETKEY_KEYSOCK_H_*/

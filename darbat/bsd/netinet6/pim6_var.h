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
/*	$FreeBSD: src/sys/netinet6/pim6_var.h,v 1.2.2.1 2000/07/15 07:14:36 kris Exp $	*/
/*	$KAME: pim6_var.h,v 1.8 2000/06/06 08:07:43 jinmei Exp $	*/

/*
 * Copyright (C) 1998 WIDE Project.
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

#ifndef _NETINET6_PIM6_VAR_H_
#define _NETINET6_PIM6_VAR_H_
#include <sys/appleapiopts.h>

/*
 * Protocol Independent Multicast (PIM),
 * implementation-specific definitions.
 *
 * Written by George Edmond Eddy (Rusty), ISI, February 1998
 * Modified by Pavlin Ivanov Radoslavov, USC/ISI, May 1998
 */

struct pim6stat {
	u_quad_t pim6s_rcv_total;	/* total PIM messages received	*/
	u_quad_t pim6s_rcv_tooshort;	/* received with too few bytes	*/
	u_quad_t pim6s_rcv_badsum;	/* received with bad checksum	*/
	u_quad_t pim6s_rcv_badversion;	/* received bad PIM version	*/
	u_quad_t pim6s_rcv_registers;	/* received registers		*/
	u_quad_t pim6s_rcv_badregisters; /* received invalid registers	*/
	u_quad_t pim6s_snd_registers;	/* sent registers		*/
};

extern struct pim6stat pim6stat;


/*
 * Names for PIM sysctl objects
 */
#define PIM6CTL_STATS		1	/* statistics (read-only) */
#define PIM6CTL_MAXID		2

#ifdef KERNEL_PRIVATE
#define PIM6CTL_NAMES { \
	{ 0, 0 }, \
	{ 0, 0 }, \
}

int pim6_input(struct mbuf **, int*);

#endif //KERNEL_PRIVATE
#endif //_NETINET6_PIM6_VAR_H_

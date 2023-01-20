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
/*
 * machine/param.h
 *
 * XXX should be arch dependent!!  This is for x86!!
 */

#ifndef _MACHINE_PARAM_H
#define _MACHINE_PARAM_H


#define MCLBYTES	2048	/* large enough for ethernet mtu */
#define MSIZE		256	/* size of an mbuf */

#define NBPG		4096	/* bytes/page */

#define NMBCLUSTERS     ((1024 * 512) / MCLBYTES)       /* cl map size: 0.5MB */

#define CLSIZE		1
#define PGOFSET		(NBPG - 1)
#define PGSHIFT		(12)
#define MCLSHIFT	(11)

#endif	/* _MACHINE_PARAM_H */

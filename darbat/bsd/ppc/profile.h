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
 * Copyright (c) 1997, Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef _BSD_PPC_PROFILE_H_
#define _BSD_PPC_PROFILE_H_

#include <sys/appleapiopts.h>

#ifdef KERNEL
#ifdef __APPLE_API_UNSTABLE
/*
 * Block interrupts during mcount so that those interrupts can also be
 * counted (as soon as we get done with the current counting).  On the
 * PPC platfom, can't do splhigh/splx as those are C routines and can
 * recursively invoke mcount.
 */
extern unsigned long disable_ee();
extern void restore_ee(unsigned long smsr);

#define MCOUNT_INIT		register unsigned long smsr;

#define	MCOUNT_ENTER	smsr = disable_ee();

#define	MCOUNT_EXIT		restore_ee(smsr);

#endif /* __APPLE_API_UNSTABLE */
#endif /* KERNEL */

#endif /* _BSD_PPC_PROFILE_H_ */

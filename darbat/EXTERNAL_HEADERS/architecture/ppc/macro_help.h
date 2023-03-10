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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1996 NeXT Software, Inc.
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 *	File:	architecture/ppc/macro_help.h
 *
 *	Provide help in making lint-free macro routines
 *
 * HISTORY
 *
 *	29-Dec-96  Umesh Vaishampayan  (umeshv@NeXT.com)
 *		Created from m98k version. 
 */

#ifndef	_ARCH_PPC_MACRO_HELP_H_
#define	_ARCH_PPC_MACRO_HELP_H_

#ifndef	MACRO_BEGIN
# define		MACRO_BEGIN	do {
#endif	/* MACRO_BEGIN */

#ifndef	MACRO_END
# define		MACRO_END	} while (0)
#endif	/* MACRO_END */

#ifndef	MACRO_RETURN
# define		MACRO_RETURN	if (1) return
#endif	/* MACRO_RETURN */

#endif	/* _ARCH_PPC_MACRO_HELP_H_ */


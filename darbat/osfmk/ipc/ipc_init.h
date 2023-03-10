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
 * @OSF_COPYRIGHT@
 */
/*
 * HISTORY
 * 
 * Revision 1.1.1.1  1998/09/22 21:05:29  wsanchez
 * Import of Mac OS X kernel (~semeria)
 *
 * Revision 1.1.1.1  1998/03/07 02:26:15  wsanchez
 * Import of OSF Mach kernel (~mburg)
 *
 * Revision 1.1.6.1  1994/09/23  02:07:56  ezf
 * 	change marker to not FREE
 * 	[1994/09/22  21:29:04  ezf]
 *
 * Revision 1.1.2.4  1993/07/22  16:16:03  rod
 * 	Add ANSI prototypes.  CR #9523.
 * 	[1993/07/22  13:29:57  rod]
 * 
 * Revision 1.1.2.3  1993/06/07  22:10:25  jeffc
 * 	CR9176 - ANSI C violations: trailing tokens on CPP
 * 	directives, extra semicolons after decl_ ..., asm keywords
 * 	[1993/06/07  19:01:24  jeffc]
 * 
 * Revision 1.1.2.2  1993/06/02  23:31:04  jeffc
 * 	Added to OSF/1 R1.3 from NMK15.0.
 * 	[1993/06/02  21:09:31  jeffc]
 * 
 * Revision 1.1  1992/09/30  02:28:50  robert
 * 	Initial revision
 * 
 * $EndLog$
 */
/* CMU_HIST */
/*
 * Revision 2.4  91/05/14  16:32:45  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/02/05  17:21:42  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  15:45:16  mrt]
 * 
 * Revision 2.2  90/06/02  14:49:59  rpd
 * 	Created for new IPC.
 * 	[90/03/26  20:55:26  rpd]
 * 
 */
/* CMU_ENDHIST */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	ipc/ipc_init.h
 *	Author:	Rich Draves
 *	Date:	1989
 *
 *	Declarations of functions to initialize the IPC system.
 */

#ifndef	_IPC_IPC_INIT_H_
#define _IPC_IPC_INIT_H_

extern int ipc_space_max;
extern int ipc_tree_entry_max;
extern int ipc_port_max;
extern int ipc_pset_max;

/*
 * Exported interfaces
 */

/* IPC initialization needed before creation of kernel task */
extern void ipc_bootstrap(void);

/* Remaining IPC initialization */
extern void ipc_init(void);

#endif	/* _IPC_IPC_INIT_H_ */

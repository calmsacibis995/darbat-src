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
 * Revision 1.1.1.1  1998/09/22 21:05:48  wsanchez
 * Import of Mac OS X kernel (~semeria)
 *
 * Revision 1.1.1.1  1998/03/07 02:26:09  wsanchez
 * Import of OSF Mach kernel (~mburg)
 *
 * Revision 1.1.6.1  1994/09/23  01:22:27  ezf
 * 	change marker to not FREE
 * 	[1994/09/22  21:11:20  ezf]
 *
 * Revision 1.1.2.4  1993/09/17  21:34:42  robert
 * 	change marker to OSF_FREE_COPYRIGHT
 * 	[1993/09/17  21:27:27  robert]
 * 
 * Revision 1.1.2.3  1993/08/03  18:21:39  rod
 * 	ANSI prototypes:  prototype thread_kdb_return().  CR #9523.
 * 	[1993/08/03  13:06:06  rod]
 * 
 * Revision 1.1.2.2  1993/07/27  18:28:24  elliston
 * 	Add ANSI prototypes.  CR #9523.
 * 	[1993/07/27  18:13:18  elliston]
 * 
 * $EndLog$
 */

#ifndef	_DDB_DB_TRAP_H_
#define	_DDB_DB_TRAP_H_

#include <mach/boolean.h>


/* Prototypes for functions exported by this module.
 */

void db_task_trap(
	int		type,
	int		code,
	boolean_t	user_space);

void db_trap(
	int	type,
	int	code);

/* Other exported prototypes
 */

void thread_kdb_return(void);

#endif	/* !_DDB_DB_TRAP_H_ */

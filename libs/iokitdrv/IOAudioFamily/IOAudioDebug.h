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
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOAUDIODEBUG_H
#define _IOAUDIODEBUG_H

#ifdef L4IOKIT
/*
 * Yes, these folks are just so lazy to write their own logging functions
 * and stole it from the IOUSBFamily.
 */
#define DEBUG
#endif

#ifdef DEBUG
#ifndef L4IOKIT
	#define DEBUG_LEVEL 1
#else
	#define	DEBUG_LEVEL	10
#endif

	#include <IOKit/usb/IOUSBLog.h>

	#define audioDebugIOLog( level, message... ) \
		do {USBLog( level, message );} while (0)

	#ifdef assert
		#undef assert

		#define AssertionMessage( cond, file, line ) \
			"assert \"" #cond "\" failed in " #file " at line " #line

		#define AssertionFailed( cond, file, line ) \
			panic(AssertionMessage( cond, file, line ));

		#define	assert( cond )								\
			if( !(cond) ) {									\
				AssertionFailed( cond, __FILE__, __LINE__ )	\
			}
	#endif
#else
	#define audioDebugIOLog( level, message... ) ;
#endif

#endif /* _IOAUDIODEBUG_H */

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
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */

#ifndef _OS_OSTYPES_H
#define _OS_OSTYPES_H

typedef unsigned int 	   UInt;
typedef signed int         SInt;

#ifndef __MACTYPES__	/* CF MacTypes.h */
#ifndef __TYPES__	/* guess... Mac Types.h */

typedef unsigned char 	   UInt8;
typedef unsigned short 	   UInt16;
typedef unsigned long 	   UInt32;
typedef unsigned long long UInt64;
// L4IOKIT !!  Fucking defines.
#if	__BIG_ENDIAN__
//#if		defined(__BIG_ENDIAN__)
typedef	struct UnsignedWide {
			UInt32		hi;
			UInt32		lo;
}							UnsignedWide;
#elif	__LITTLE_ENDIAN__
//#elif		defined(__LITTLE_ENDIAN__)
typedef	struct UnsignedWide {
			UInt32		lo;
			UInt32		hi;
}							UnsignedWide;
#else
#error Unknown endianess.
#endif

typedef signed char 	   SInt8;
typedef signed short 	   SInt16;
typedef signed long 	   SInt32;
typedef signed long long   SInt64;
// L4IOKIT!!
//#if		defined(__BIG_ENDIAN__)
#if	__BIG_ENDIAN__
typedef	struct wide {
			SInt32		hi;
			UInt32		lo;
}							wide;
//#elif		defined(__LITTLE_ENDIAN__)
#elif		__LITTLE_ENDIAN__
typedef	struct wide {
			UInt32		lo;
			SInt32		hi;
}							wide;
#else
#error Unknown endianess.
#endif

typedef SInt32				OSStatus;
typedef UnsignedWide		AbsoluteTime;
typedef UInt32				OptionBits;

typedef unsigned char Boolean;

#endif /* __TYPES__ */
#endif /* __MACTYPES__ */

#if !defined(OS_INLINE)
#	define OS_INLINE static inline
#endif

#endif /* _OS_OSTYPES_H */

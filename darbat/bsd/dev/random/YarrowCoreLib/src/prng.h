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
 * Copyright (c) 1999, 2000-2001 Apple Computer, Inc. All rights reserved.
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
	File:		prng.h

	Contains:	Core routines for the Counterpane Yarrow PRNG.

	Written by:	Counterpane, Inc. 

	Copyright: (c) 2000 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		02/10/99	dpm		Created, based on Counterpane source.
 
*/
/*
	prng.h

	Main private header for the Counterpane PRNG. Use this to be able access the
	initialization and destruction routines from the DLL.
*/

#ifndef __YARROW_PRNG_H__
#define __YARROW_PRNG_H__

#if		defined(macintosh) || defined(__APPLE__)
#include "dev/random/YarrowCoreLib/include/yarrow.h"
/* Private function forward declarations */
// this is in yarrow.h...YARROWAPI prng_error_status prngInitialize(void);
// ditto....             YARROWAPI prng_error_status prngDestroy(void);
YARROWAPI prng_error_status prngInputEntropy(PrngRef prng, BYTE *inbuf,UINT inbuflen,UINT poolnum);
#else	/* original yarrow code */
/* Declare YARROWAPI as __declspec(dllexport) before
   including this file in the actual DLL */
#ifndef YARROWAPI 
#define YARROWAPI __declspec(dllimport)
#endif

/* Private function forward declarations */
YARROWAPI int prngInitialize(void);
YARROWAPI int prngDestroy(void);
YARROWAPI int prngInputEntropy(BYTE *inbuf,UINT inbuflen,UINT poolnum);

#endif	/* macintosh */
#endif	/* __YARROW_PRNG_H__ */

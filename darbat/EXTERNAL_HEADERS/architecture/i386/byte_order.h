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
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Byte ordering conversion (for i386).
 *
 * HISTORY
 *
 * 8 October 1992 ? at NeXT
 *	Converted to NXxxx versions.  Condensed history.
 *
 * 18 May 1992 ? at NeXT
 *	Created.
 */
 
static __inline__
unsigned short
NXSwapShort(
    unsigned short	inv
)
{
    register unsigned short value = inv;
    
    __asm__ volatile( "xchgb %h1, %b1" : "=q" (value) : "0" (value));

    return (value);
}
 
static __inline__
unsigned long
NXSwapInt(
    unsigned long inv
)
{
    register unsigned int outv = inv;
    
    __asm__ volatile( "bswap %0" : "=r"	(outv) : "0" (outv));
	
    return (outv);
}
 
static __inline__
unsigned long
NXSwapLong(
    unsigned long	inv
)
{
    unsigned long	outv;
    
    __asm__ volatile(
    	"bswap %0"
	
	: "=r"	(outv)
	: "0"	(inv));
	
    return (outv);
}

static __inline__
unsigned long long
NXSwapLongLong(
    unsigned long long	inv
)
{
    union llconv {
	unsigned long long	ull;
	unsigned long		ul[2];
    } *inp, outv;
    
    inp = (union llconv *)&inv;
    
    outv.ul[0] = NXSwapLong(inp->ul[1]);
    outv.ul[1] = NXSwapLong(inp->ul[0]);
    	
    return (outv.ull);
}

static __inline__ NXSwappedFloat
NXConvertHostFloatToSwapped(float x)
{
    union fconv {
	float number;
	NXSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static __inline__ float
NXConvertSwappedFloatToHost(NXSwappedFloat x)
{
    union fconv {
	float number;
	NXSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static __inline__ NXSwappedDouble
NXConvertHostDoubleToSwapped(double x)
{
    union dconv {
	double number;
	NXSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static __inline__ double
NXConvertSwappedDoubleToHost(NXSwappedDouble x)
{
    union dconv {
	double number;
	NXSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static __inline__ NXSwappedFloat
NXSwapFloat(NXSwappedFloat x)
{
    return NXSwapLong(x);
}

static __inline__ NXSwappedDouble
NXSwapDouble(NXSwappedDouble x)
{
    return NXSwapLongLong(x);
}

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
 * bsdglue.h
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

/*
 * NOTE:
 *
 * This file is meant to be included ONCE ONLY.
 */

/*
 * IOKit types.
 *
 * The types include should be included before this so we should be
 * okay.
 */
#include <IOKit/IOLib.h>

#if 0	/* should not need these */
typedef UInt32	u_int32_t;	/* FIXME: in bsd/i386/types.h */
typedef UInt16	u_int16_t;
typedef UInt8	u_int8_t;
#endif

static void bus_space_write_4( int, void *, unsigned, UInt32 );
static UInt32 bus_space_read_4( int, void *, unsigned offset );

static void bus_space_write_2( int,void *, unsigned, UInt16 );
static UInt16 bus_space_read_2( int, void *, unsigned offset );

static void bus_space_write_1( int, void *, unsigned, UInt8 );
static UInt8 bus_space_read_1( int, void *, unsigned offset );

/*
 * Bus read/write functions.
 */
static UInt32
bus_space_read_4(int tag, void *base, unsigned offset)
{

	return *(volatile UInt32 *)((char *)base + offset);
}

static void
bus_space_write_4(int tag, void *base, unsigned offset, UInt32 val)
{

	*(volatile UInt32 *)((char *)base + offset) = val;
}

static UInt16
bus_space_read_2(int tag, void *base, unsigned offset)
{

	return *(volatile UInt16 *)((char *)base + offset);
}

static void
bus_space_write_2(int tag, void *base, unsigned offset, UInt16 val)
{

	*(volatile UInt16 *)((char *)base + offset) = val;
}

static UInt8
bus_space_read_1(int tag, void *base, unsigned offset)
{

	return *(volatile UInt8 *)((char *)base + offset);
}

static void
bus_space_write_1(int tag, void *base, unsigned offset, UInt8 val)
{

	*(volatile UInt8 *)((char *)base + offset) = val;
}

/*
 * DELAY() in BSD will wait for n microseconds.
 *
 * However, we do not allow ourselves to sleep for less than 10us,
 * based on a comment of what was said in AppleIntel8255x.  Don't know
 * whether it makes a difference for the other BSDs, but sleeping for
 * longer than required should not be a problem.
 */
#define DELAY(n)	IODelay(n)

/*
 * Hacks.
 *
 * These must be kept in sync.
 */
#define ETHER_ADDR_LEN	6


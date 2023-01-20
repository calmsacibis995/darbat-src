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
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <mach/mach_types.h>
#include <IOKit/IOMapper.h>

#include <igcompat/darbat.h>

/**** XXX this is pretty seedy ****/

// typedef int dev_t;
// typedef unsigned int u_int32_t;

kern_return_t IOFindBSDRoot( char *, dev_t *, u_int32_t * );
void IOKitResetTime(void);

/**********************************/

ppnum_t 
IOMapperIOVMAlloc(unsigned pages)
{
        return 0;
}

extern void clock_initialize_calendar(void);

void
IOKitResetTime(void)
{
    clock_initialize_calendar();
	printf( "not so IOKit: reset time!!\n" );
}


dev_t ddevadd( int devid, unsigned int nblocks, unsigned int blocksz );
extern void disk_get_geom( unsigned int *nblocks, unsigned int *blocksz );

static void
setup_disk(void)
{
	unsigned int nblocks, blocksz;
	dev_t dev;

	disk_get_geom( &nblocks, &blocksz );

	/* setup a device */
	dev = ddevadd( -1, nblocks, blocksz );

	printf( "added disk device # 0x%x\n", dev );
}

dev_t mdevadd(int devid, ppnum_t base, unsigned int size, int phys);

kern_return_t 
IOFindBSDRoot( char * rootName, dev_t * root, u_int32_t * flags )
{
	void *base;
	uintptr_t size;
	int r;
	dev_t dev;

	/* find the disk image */
	r = darbat_find_root_image( &base, &size );
	if( r != 0 )
	{
		printf( "IOKit: error finding root image!\n" );
		return 1;
	}

	/* construct the disk */
	/* XXX: 3rd param was zero */
	dev = mdevadd( -1, ((uintptr_t)base) >> 12, size >> 12, 1 );
	if( dev == -1 )
	{
		printf( "IOKit: error adding mdev device!\n" );
		return 1;
	}

	/* fill out the info */
	strcpy( rootName, "vmd0" );
	*root = dev;
	*flags = 0;

	/* Setup the IOKit disk */
	setup_disk();

	return 0;
}


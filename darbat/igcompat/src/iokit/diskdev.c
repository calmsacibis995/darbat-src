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
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: Utah Hdr: vn.c 1.13 94/04/02
 *
 *	from: @(#)vn.c	8.6 (Berkeley) 4/1/94
 * $FreeBSD: src/sys/dev/vn/vn.c,v 1.105.2.4 2001/11/18 07:11:00 dillon Exp $
 */

/*
 * L4 blocking IO disk driver.
 *
 * Hacked from the block interface to a ramdisk.  
 *
 */

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/fcntl.h>
#include <sys/conf.h>
#include <sys/disk.h>
#include <sys/stat.h>
#include <sys/vm.h>
#include <sys/uio_internal.h>
#include <libkern/libkern.h>

#include <vm/pmap.h>
#include <vm/vm_pager.h>
#include <mach/memory_object_types.h>

#include <miscfs/devfs/devfs.h>

#include <kern/debug.h>
#include <igcompat/compat.h> /* bcopy */


static open_close_fcn_t	ddevopen;
static open_close_fcn_t	ddevclose;
static psize_fcn_t	ddevsize;
static strategy_fcn_t	ddevstrategy;
static int		ddevbioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p);
static int		ddevcioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p);
static int 		ddevrw(dev_t dev, struct uio *uio, int ioflag);

extern void		bcopy_phys(addr64_t from, addr64_t to, vm_size_t bytes);
extern void		mapping_set_mod(ppnum_t pn);
extern ppnum_t 	        pmap_find_phys(pmap_t pmap, addr64_t va);


/*
 * cdevsw
 *	D_DISK		we want to look like a disk
 *	D_CANFREE	We support B_FREEBUF
 */

static struct bdevsw ddevbdevsw = {
	/* open */	ddevopen,
	/* close */	ddevclose,
	/* strategy */	ddevstrategy,
	/* ioctl */	ddevbioctl,
	/* dump */	eno_dump,
	/* psize */	ddevsize,
	/* flags */	D_DISK,
};

static struct cdevsw ddevcdevsw = {
	/* open */	ddevopen,
	/* close */	ddevclose,
	/* read */	ddevrw,
	/* write */	ddevrw,
	/* ioctl */	ddevcioctl,
	/* stop */	eno_stop,
	/* reset */	eno_reset,
	/* ttys */	0,
	/* select */	eno_select,
	/* mmap */	eno_mmap,
	/* strategy */	eno_strat,
	/* getc */	eno_getc,
	/* putc */	eno_putc,
	/* flags */	D_DISK,
};

struct ddev 
{
	int		ddFlags;	/* flags */
	int		ddSecsize;	/* sector size */
	int		ddBDev;		/* Block device number */
	int		ddCDev;		/* Character device number */
	void *		ddbdevb;
	void *		ddcdevb;

	unsigned int    blocksz;
	unsigned int    nblocks;
	
#if 0
	vm_offset_t	ddBase;		/* file size in bytes */
	uint32_t	ddSize;		/* file size in bytes */
#endif
} ddev[16];

/* ddFlags */
#define ddInited	0x01	/* This device defined */
#define	ddRO		0x02	/* This device is read-only */

int ddevBMajor = -1;
int ddevCMajor = -1;

static int ddevioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p, int is_char);
dev_t ddevadd( int devid, unsigned int nblocks, unsigned int blocksz );

dev_t ddevlookup(int devid);

static	int 
ddevclose(__unused dev_t dev, __unused int flags, 
		      __unused int devtype, __unused struct proc *p) 
{

	return (0);
}

static	int 
ddevopen(dev_t dev, int flags, __unused int devtype, 
		     __unused struct proc *p) 
{
	
	int devid;

	devid = minor(dev);									/* Get minor device number */

	if (devid > 16) return (ENXIO);						/* Not valid */

	if ((flags & FWRITE) && (ddev[devid].ddFlags & ddRO)) 
		return (EACCES);	/* Currently mounted RO */

	return(0);
}

static int 
ddevrw(dev_t dev, struct uio *uio, __unused int ioflag) 
{
	int 			status;
	int 			devid;
#if 0
	addr64_t		mdata;
	enum uio_seg 	saveflag;
#endif

	devid = minor(dev);	/* Get minor device number */

	if (devid > 16) 
		return (ENXIO);			/* Not valid */

	if (!(ddev[devid].ddFlags & ddInited))
		return (ENXIO);	/* Have we actually been defined yet? */

	panic("in ddevrw");
	status = 0;
#if 0
	mdata = ((addr64_t)ddev[devid].mdBase << 12) + uio->uio_offset;	/* Point to the area in "file" */
	
	saveflag = uio->uio_segflg;							/* Remember what the request is */
#if LP64_DEBUG
	if (IS_VALID_UIO_SEGFLG(uio->uio_segflg) == 0) {
	  panic("ddevrw - invalid uio_segflg\n"); 
	}
#endif /* LP64_DEBUG */
	/* Make sure we are moving from physical ram if physical device */
	if (ddev[devid].ddFlags & sdPhys) {
		if (uio->uio_segflg == UIO_USERSPACE64) 
			uio->uio_segflg = UIO_PHYS_USERSPACE64;	
		else if (uio->uio_segflg == UIO_USERSPACE32)
			uio->uio_segflg = UIO_PHYS_USERSPACE32;	
		else
			uio->uio_segflg = UIO_PHYS_USERSPACE;	
	}

	status = uiomove64(mdata, uio_resid(uio), uio);		/* Move the data */
	uio->uio_segflg = saveflag;							/* Restore the flag */
#endif
	return (status);
}

extern void disk_read(unsigned long long offset, unsigned int size);
extern void disk_write(caddr_t vaddr, unsigned long long offset, 
	unsigned int size);
extern void *shared_buffer;

static void 
ddevstrategy(struct buf *bp) 
{
	int devid;
	unsigned long long offset;  /* disk offset */
	caddr_t vaddr;

	/* Get minor device number */
	devid = minor(buf_device(bp));

	/* Have we actually been defined yet? */
	if ((ddev[devid].ddFlags & ddInited) == 0) 
	{
	        buf_seterror(bp, ENXIO);
		buf_biodone(bp);
		return;
	}

	/* Set byte count */
	buf_setresid(bp, buf_count(bp));
	
	/* Get offset into file */
	offset = ((unsigned long long)buf_blkno(bp)) 
		* ((unsigned long long) ddev[devid].ddSecsize);

#if 0
	/* Are they trying to read/write at/after end? */
	if( blkoff >= (ddev[devid].ddSize << 12) )
	{
		if(blkoff != (ddev[devid].ddSize << 12)) 
		{		/* Are we trying to read after EOF? */
		        buf_seterror(bp, EINVAL); /* Yeah, this is an error */
		}
		buf_biodone(bp);								/* Return */
		return;
	}

	/* Will this read go past end? */
	if ((blkoff + buf_count(bp)) > (ddev[devid].ddSize << 12)) 
	{
		/* Yes, trim to max */
		buf_setcount(bp, ((ddev[devid].ddSize << 12) - blkoff));
	}
#endif

	/*
	 * make sure the buffer's data area is
	 * accessible
	 */
	if( buf_map( bp, (caddr_t *)&vaddr ) )
	        panic( "ramstrategy: buf_map failed\n" );

	/* Is this a read? */
	if (buf_flags(bp) & B_READ) 
	{
		unsigned int size = (size_t)buf_count(bp);

/*
		printf( "ddev doing a B_READ\n" );
		printf( "buf_blkno 0x%llx\n", 
			(unsigned long long)buf_blkno(bp) );
		printf( "sec_size 0x%x\n", ddev[devid].ddSecsize );
		printf( "offset 0x%llx\n", offset );
		printf( "size 0x%x\n", size );
*/
		/* issue the read to the disk */
		disk_read(offset, size);

		/* copy the data to its destination */
		memcpy( (void*) vaddr, shared_buffer, size );

//		printf( "done read, copied to 0x%p\n", vaddr );
	}
	else
	{
		/* This is a write */

		/*
	 	 * XXX not tested!
		 *
		 * This may break your disk.
		 */
		disk_write(vaddr, offset, (size_t)buf_count(bp));
#if 0
		/* This is virtual, just put the data */
		bcopy((void *)vaddr, (void *)((uintptr_t)fvaddr),
		      (size_t)buf_count(bp));
#endif
	}

	/*
	 * buf_unmap takes care of all the cases
	 * it will unmap the buffer from kernel
	 * virtual space if that was the state
	 * when we mapped it.
	 */
	buf_unmap(bp);

	/* Nothing more to do */
	buf_setresid(bp, 0);

	/* Say we've finished */
	buf_biodone(bp);			
}

static int 
ddevbioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p) 
{
	return (ddevioctl(dev, cmd, data, flag, p, 0));
}

static int 
ddevcioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p) 
{
	return (ddevioctl(dev, cmd, data, flag, p, 1));
}

static int 
ddevioctl(dev_t dev, u_long cmd, caddr_t data, __unused int flag, 
					 struct proc *p, int is_char) 
{
	int error;
	u_long *f;
	u_int64_t *o;
	int devid;


	/* Get minor device number */
	devid = minor(dev);

	/* Not valid */
	if (devid > 16) 
		return (ENXIO);

	/* Are we superman? */
	error = proc_suser(p);
	if (error) 
		/* Nope... */
		return (error);

	f = (u_long*)data;
	o = (u_int64_t *)data;

	switch (cmd) {

		case DKIOCGETMAXBLOCKCOUNTREAD:
			// printf( "ddev ioctl DKIOCGETMAXBLOCKCOUNTREAD\n" );
			*o = 32;
			break;
		
		case DKIOCGETMAXBLOCKCOUNTWRITE:
			// printf( "ddev ioctl DKIOCGETMAXBLOCKCOUNTWRITE\n" );
			*o = 32;
			break;
		
		case DKIOCGETMAXSEGMENTCOUNTREAD:
			// printf( "ddev ioctl DKIOCGETMAXSEGMENTCOUNTREAD\n" );
			*o = 32;
			break;
		
		case DKIOCGETMAXSEGMENTCOUNTWRITE:
			// printf( "ddev ioctl DKIOCGETMAXSEGMENTCOUNTWRITE\n" );
			*o = 32;
			break;
		
		case DKIOCGETBLOCKSIZE:
			// printf( "ddev ioctl DKIOCGETBLOCKSIZE\n" );
			*f = ddev[devid].ddSecsize;
			// printf( "*f = 0x%lx\n", *f );
			break;
		
		case DKIOCSETBLOCKSIZE:
			// printf( "ddev ioctl DKIOCSETBLOCKSIZE\n" );
			/* We can only do this for a block */
			if (is_char) 
				return (ENODEV);

			/* Too short? */
			if (*f < DEV_BSIZE) 
				return (EINVAL);

			/* set the new block size */
			ddev[devid].ddSecsize = *f;
			// printf( "*f = 0x%lx\n", *f );
			break;
			
		case DKIOCISWRITABLE:
			// printf( "ddev ioctl DKIOCISWRITABLE\n" );
			*f = 0; /* was 1 */
			break;
			
		case DKIOCGETBLOCKCOUNT32:
			// printf( "ddev ioctl DKIOCGETBLOCKCOUNT32\n" );
			if(!(ddev[devid].ddFlags & ddInited)) 
				return (ENXIO);
			*f = (ddev[devid].nblocks * ddev[devid].blocksz)
				/ ddev[devid].ddSecsize;
			break;
			
		case DKIOCGETBLOCKCOUNT:
			// printf( "ddev ioctl DKIOCGETBLOCKCOUNT\n" );
			if(!(ddev[devid].ddFlags & ddInited)) 
				return (ENXIO);
			*o = (((unsigned long long)ddev[devid].nblocks) 
			      * ((unsigned long long) ddev[devid].blocksz))
				/ ((unsigned long long)ddev[devid].ddSecsize);
			// printf( "*o = 0x%llx\n", *o );
			break;
			
		default:
			// printf( "ddev ioctl default\n" );
			error = ENOTTY;
			break;
	}
	return(error);
}


static	int 
ddevsize(dev_t dev) 
{

	int devid;

	/* Get minor device number */
	devid = minor(dev);
	
	/* Not valid */
	if (devid > 16) 
		return (ENXIO);

	/* Not inited yet */
	if ((ddev[devid].ddFlags & ddInited) == 0) 
		return(-1);

	return(ddev[devid].ddSecsize);
}

#include <pexpert/pexpert.h>

dev_t 
ddevadd( int devid, unsigned int nblocks, unsigned int blocksz )
{
	
	int i;
	
	printf( "ddevadd: adding ddev 0x%x blocks, bs %d\n", 
		nblocks, blocksz );

	if(devid < 0) 
	{
		/* Search all known disk devices */
		devid = -1;
		for(i = 0; i < 16; i++) 
		{
			/* Is this a free one? */
			if(!(ddev[i].ddFlags & ddInited)) 
			{
				/* Remember first free one */
				if(devid < 0)
					devid = i;

				/* Skip check */
				continue;
			}
		}

		/* Do we have free slots? */
		if(devid < 0) 
		{
			panic("ddevadd: attempt to add more than 16 disk devices\n");
		}
	}
	else 
	{
		/* Giving us something bogus? */
		if( devid >= 16 )
		{
			panic("ddevadd: attempt to explicitly add a bogus disk device: &08X\n", devid);
		}

		/* Already there? */
		if(ddev[devid].ddFlags & ddInited) 
		{
			panic("ddevadd: attempt to explicitly add a previously defined disk device: &08X\n", devid);
		}
	}
	
	/* Have we gotten a major number yet? */
	if(ddevBMajor < 0) 
	{
		/* Add to the table and figure out a major number */
		ddevBMajor = bdevsw_add(-1, &ddevbdevsw);
		if (ddevBMajor < 0) 
		{
			printf("ddevadd: error - bdevsw_add() returned %d\n", ddevBMajor);
			return -1;
		}
	}
	
	/* Have we gotten a major number yet? */
	if(ddevCMajor < 0) 
	{
		/* Add to the table and figure out a major number */
		ddevCMajor = cdevsw_add_with_bdev(-1, &ddevcdevsw, ddevBMajor);
		if( ddevCMajor < 0 )
		{
			printf("diskdevice_init: error - cdevsw_add() returned %d\n", ddevCMajor);
			return -1;
		}
	}

	/* Get the device number */
	ddev[devid].ddBDev = makedev(ddevBMajor, devid);

	/* Make the node */
	ddev[devid].ddbdevb = devfs_make_node( ddev[devid].ddBDev, DEVFS_BLOCK,
					       UID_ROOT, GID_OPERATOR, 
					       0600, "ikd%d", devid );
	/* Did we make one? */
	if( ddev[devid].ddbdevb == NULL ) 
	{
		printf("ddevadd: devfs_make_node for block failed!\n");
		/* Nope... */
		return -1;
	}

	/* Get the device number */
	ddev[devid].ddCDev = makedev(ddevCMajor, devid);
	/* Make the node */
	ddev[devid].ddcdevb = devfs_make_node( ddev[devid].ddCDev, DEVFS_CHAR,
					       UID_ROOT, GID_OPERATOR, 
					       0600, "rikd%d", devid );
	/* Did we make one? */
	if( ddev[devid].ddcdevb == NULL ) 
	{
		printf("ddevadd: devfs_make_node for character failed!\n");
		/* Nope... */
		return -1;
	}
	
	/* Set the number of blocks */
	ddev[devid].nblocks = nblocks;

	/* Set the length of the ram disk */
	ddev[devid].blocksz = blocksz;
	ddev[devid].ddSecsize = blocksz;  /* start like this */

	/* Show we are all set up */
	ddev[devid].ddFlags |= ddInited;
	printf("Added disk device ikd%x/rikd%x (%08X/%08X) len %08X blocksz %08X\n", 
		devid, devid, ddev[devid].ddBDev, ddev[devid].ddCDev, 
	       nblocks, blocksz );

	return ddev[devid].ddBDev;
}


dev_t 
ddevlookup(int devid) 
{
	
	/* Filter any bogus requests */
	if((devid < 0) || (devid > 15)) 
		return -1;

	/* This one hasn't been defined */
	if(!(ddev[devid].ddFlags & ddInited)) 
		return -1;

	/* Return the device number */
	return ddev[devid].ddBDev;
}

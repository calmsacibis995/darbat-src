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
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
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
 * HISTORY:
 * 16-Mar-88  John Seamons (jks) at NeXT
 *	Cleaned up to support standard disk label definitions.
 *
 * 24-Feb-88  Mike DeMoney (mike) at NeXT
 *	Added d_boot0_blkno to indicate logical block number
 *	of "block 0" boot.  This blkno is in d_secsize sectors.
 *	Added d_bootfile to indicate the default operating system
 *	image to be booted by the blk 0 boot.
 *	Changed d_name and d_type to be char arrays rather than ptrs
 *	so they are part of label.  This limits length of info in
 *	/etc/disktab, sorry.
 */

#ifndef	_SYS_DISKTAB_
#define	_SYS_DISKTAB_

#include <sys/appleapiopts.h>

#ifdef	__APPLE_API_OBSOLETE

/*
 * Disk description table, see disktab(5)
 */
#ifndef KERNEL
#define	DISKTAB		"/etc/disktab"
#endif	/* !KERNEL */

#define	MAXDNMLEN	24	// drive name length
#define	MAXMPTLEN	16	// mount point length
#define	MAXFSTLEN	8	// file system type length
#define	MAXTYPLEN	24	// drive type length
#define	NBOOTS		2	// # of boot blocks
#define	MAXBFLEN 	24	// bootfile name length
#define	MAXHNLEN 	32	// host name length
#define	NPART		8	// # of partitions

typedef struct partition {
	int	p_base;		/* base sector# of partition */
	int	p_size;		/* #sectors in partition */
	short	p_bsize;	/* block size in bytes */
	short	p_fsize;	/* frag size in bytes */
	char	p_opt;		/* 's'pace/'t'ime optimization pref */
	short	p_cpg;		/* cylinders per group */
	short	p_density;	/* bytes per inode density */
	char	p_minfree;	/* minfree (%) */
	char	p_newfs;	/* run newfs during init */
	char	p_mountpt[MAXMPTLEN];/* mount point */
	char	p_automnt;	/* auto-mount when inserted */
	char	p_type[MAXFSTLEN];/* file system type */
} partition_t;

typedef struct disktab {
	char	d_name[MAXDNMLEN];	/* drive name */
	char	d_type[MAXTYPLEN];	/* drive type */
	int	d_secsize;		/* sector size in bytes */
	int	d_ntracks;		/* # tracks/cylinder */
	int	d_nsectors;		/* # sectors/track */
	int	d_ncylinders;		/* # cylinders */
	int	d_rpm;			/* revolutions/minute */
	short	d_front;		/* size of front porch (sectors) */
	short	d_back;			/* size of back porch (sectors) */
	short	d_ngroups;		/* number of alt groups */
	short	d_ag_size;		/* alt group size (sectors) */
	short	d_ag_alts;		/* alternate sectors / alt group */
	short	d_ag_off;		/* sector offset to first alternate */
	int	d_boot0_blkno[NBOOTS];	/* "blk 0" boot locations */
	char	d_bootfile[MAXBFLEN];	/* default bootfile */
	char	d_hostname[MAXHNLEN];	/* host name */
	char	d_rootpartition;	/* root partition e.g. 'a' */
	char	d_rwpartition;		/* r/w partition e.g. 'b' */
	partition_t d_partitions[NPART];
} disktab_t;

#ifndef KERNEL
struct	disktab *getdiskbyname(), *getdiskbydev();
#endif	/* !KERNEL */

#endif	/* __APPLE_API_OBSOLETE */

#endif	/* _SYS_DISKTAB_ */

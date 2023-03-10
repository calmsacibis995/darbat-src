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
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* $FreeBSD: src/sys/msdosfs/fat.h,v 1.9 1999/12/29 04:54:53 peter Exp $ */
/*	$NetBSD: fat.h,v 1.12 1997/11/17 15:36:36 ws Exp $	*/

/*-
 * Copyright (C) 1994, 1997 Wolfgang Solfrank.
 * Copyright (C) 1994, 1997 TooLs GmbH.
 * All rights reserved.
 * Original code by Paul Popelka (paulp@uts.amdahl.com) (see below).
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
 *	This product includes software developed by TooLs GmbH.
 * 4. The name of TooLs GmbH may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY TOOLS GMBH ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TOOLS GMBH BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Written by Paul Popelka (paulp@uts.amdahl.com)
 *
 * You can do anything you want with this software, just don't say you wrote
 * it, and don't remove this notice.
 *
 * This software is provided "as is".
 *
 * The author supplies this software to be publicly redistributed on the
 * understanding that the author is not responsible for the correct
 * functioning of this software in any circumstances and is not liable for
 * any damages caused by this software.
 *
 * October 1992
 */


/*
 * Some useful cluster numbers.
 */
#define	MSDOSFSROOT	0		/* cluster 0 means the root dir */
#define	CLUST_FREE	0		/* cluster 0 also means a free cluster */
#define	MSDOSFSFREE	CLUST_FREE
#define	CLUST_FIRST	2		/* first legal cluster number */
#define	CLUST_RSRVD	0xfffffff6	/* reserved cluster range */
#define	CLUST_BAD	0xfffffff7	/* a cluster with a defect */
#define	CLUST_EOFS	0xfffffff8	/* start of eof cluster range */
#define	CLUST_EOFE	0xffffffff	/* end of eof cluster range */

/*
 * Note: FILENO_EMPTY must be larger than FAT32_MASK so that it can't accidentally
 * occur as a valid cluster number.
 */
#define FILENO_EMPTY	999999999	/* Fake file number used for empty files */
#define FILENO_ROOT	1		/* File number used for root directory of FAT12 and FAT16 */

#define	FAT12_MASK	0x00000fff	/* mask for 12 bit cluster numbers */
#define	FAT16_MASK	0x0000ffff	/* mask for 16 bit cluster numbers */
#define	FAT32_MASK	0x0fffffff	/* mask for FAT32 cluster numbers */

/*
 * MSDOSFS:
 * Return true if filesystem uses 12 bit fats. Microsoft Programmer's
 * Reference says if the maximum cluster number in a filesystem is greater
 * than 4078 ((CLUST_RSRVS - CLUST_FIRST) & FAT12_MASK) then we've got a
 * 16 bit fat filesystem. While mounting, the result of this test is stored
 * in pm_fatentrysize.
 * GEMDOS-flavour (atari):
 * If the filesystem is on floppy we've got a 12 bit fat filesystem, otherwise
 * 16 bit. We check the d_type field in the disklabel struct while mounting
 * and store the result in the pm_fatentrysize. Note that this kind of
 * detection gets flakey when mounting a vnd-device.
 */
#define	FAT12(pmp)	(pmp->pm_fatmask == FAT12_MASK)
#define	FAT16(pmp)	(pmp->pm_fatmask == FAT16_MASK)
#define	FAT32(pmp)	(pmp->pm_fatmask == FAT32_MASK)

#define	MSDOSFSEOF(pmp, cn)	((((cn) | ~(pmp)->pm_fatmask) & CLUST_EOFS) == CLUST_EOFS)

#ifdef KERNEL
/*
 * These are the values for the function argument to the function
 * fatentry().
 */
#define	FAT_GET		0x0001	/* get a fat entry */
#define	FAT_SET		0x0002	/* set a fat entry */
#define	FAT_GET_AND_SET	(FAT_GET | FAT_SET)

/*
 * Flags to extendfile:
 */
#define	DE_CLEAR	1	/* Zero out the blocks allocated */
#define DE_SYNC		IO_SYNC	/* 0x4 do it synchronisly...from vnode.h */


void msdosfs_fat_init(void);
void msdosfs_fat_uninit(void);
int  msdosfs_fat_init_vol(struct msdosfsmount *pmp, vfs_context_t context);
void msdosfs_fat_uninit_vol(struct msdosfsmount *pmp);
int pcbmap __P((struct denode *dep, u_long findcn, u_long numclusters, daddr64_t *bnp, u_long *cnp, u_long *sp, vfs_context_t context));
int clusterfree __P((struct msdosfsmount *pmp, u_long cn, u_long *oldcnp, vfs_context_t context));
int clusteralloc __P((struct msdosfsmount *pmp, u_long start, u_long count, u_long fillwith, u_long *retcluster, u_long *got, vfs_context_t context));
int fatentry __P((int function, struct msdosfsmount *pmp, u_long cluster, u_long *oldcontents, u_long newcontents, vfs_context_t context));
int freeclusterchain __P((struct msdosfsmount *pmp, u_long startchain, vfs_context_t context));
int extendfile __P((struct denode *dep, u_long count, vfs_context_t context));
void fc_purge __P((struct denode *dep, u_int frcn));

/* [2753891]
 * Routine to mark a FAT16 or FAT32 volume as "clean" or "dirty" by manipulating the upper bit
 * of the FAT entry for cluster 1.  Note that this bit is not defined for FAT12 volumes.
 */
int markvoldirty(struct msdosfsmount *pmp, int dirty, vfs_context_t context);

enum vtype msdosfs_check_link(struct denode *dep, vfs_context_t context);

#endif	/* KERNEL */

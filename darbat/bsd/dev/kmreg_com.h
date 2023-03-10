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
/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * kmreg_com.h - machine independent km ioctl interface.
 *
 * HISTORY
 * 16-Jan-92    Doug Mitchell at NeXT 
 *      Created. 
 */
 
#ifdef	KERNEL_PRIVATE

#ifndef	_BSD_DEV_KMREG_COM_
#define _BSD_DEV_KMREG_COM_

#include <sys/types.h>
#include <sys/ioctl.h> 

/* 
 * Colors for fg, bg in struct km_drawrect 
 */
#define KM_COLOR_WHITE		0
#define KM_COLOR_LTGRAY		1
#define KM_COLOR_DKGRAY		2
#define KM_COLOR_BLACK		3

/*
 * The data to be rendered is treated as a pixmap of 2 bit pixels.
 * The most significant bits of each byte is the leftmost pixel in that 
 * byte.  Pixel values are assigned as described above.
 *
 * Each scanline should start on a 4 pixel boundry within the bitmap,
 * and should be a multiple of 4 pixels in length.
 *
 * For the KMIOCERASERECT call, 'data' should be an integer set to the 
 * color to be used for the clear operation (data.fill).
 * A rect at (x,y) measuring 'width' by 'height' will be cleared to 
 * the specified value.
 */
struct km_drawrect {
	unsigned short x;	/* Upper left corner of rect to be imaged. */
	unsigned short y;
	unsigned short width;	/* Width and height of rect to be imaged, 
				 * in pixels */
	unsigned short height;
	union {
		void *bits;	/* Pointer to 2 bit per pixel raster data. */
		int   fill;	/* Const color for erase operation. */
	} data;
};

/*
 * Argument to KMIOCANIMCTL.
 */
typedef enum {
	KM_ANIM_STOP,		/* stop permanently */
	KM_ANIM_SUSPEND,	/* suspend */
	KM_ANIM_RESUME		/* resume */
} km_anim_ctl_t;

#define	KMIOCPOPUP	_IO('k', 1)		/* popup new window */
#define	KMIOCRESTORE	_IO('k', 2)		/* restore background */
#define	KMIOCDUMPLOG	_IO('k', 3)		/* dump message log */
#define KMIOCDRAWRECT	_IOW('k', 5, struct km_drawrect)  /* Draw rect from 
							   * bits */
#define KMIOCERASERECT	_IOW('k', 6, struct km_drawrect)  /* Erase a rect */

#ifdef	KERNEL_PRIVATE
#define	KMIOCDISABLCONS	_IO('k', 8)		/* disable console messages */
#endif	/* KERNEL_PRIVATE */

#define KMIOCANIMCTL	_IOW('k',9, km_anim_ctl_t)	
						/* stop animation */
#define KMIOCSTATUS	_IOR('k',10, int)	/* get status bits */
#define KMIOCSIZE	_IOR('k',11, struct winsize) /* get screen size */

/*
 * Status bits returned via KMIOCSTATUS.
 */
#define KMS_SEE_MSGS	0x00000001

#endif	/* _BSD_DEV_KMREG_COM_ */

#endif	/* KERNEL_PRIVATE */

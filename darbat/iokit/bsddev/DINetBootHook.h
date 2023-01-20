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
 *  DINetBootHook.h
 *  DiskImages
 *
 *  Created by Byron Han on Sat Apr 13 2002.
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 *	Revision History
 *
 *	$Log: DINetBootHook.h,v $
 *	Revision 1.3  2002/05/22 18:50:49  aramesh
 *	Kernel API Cleanup
 *	Bug #: 2853781
 *	Changes from Josh(networking), Rick(IOKit), Jim & David(osfmk), Umesh, Dan & Ramesh(BSD)
 *	Submitted by: Ramesh
 *	Reviewed by: Vincent
 *	
 *	Revision 1.2.12.1  2002/05/21 23:08:14  aramesh
 *	Kernel API Cleanup
 *	Bug #: 2853781
 *	Submitted by: Josh, Umesh, Jim, Rick and Ramesh
 *	Reviewed by: Vincent
 *	
 *	Revision 1.2  2002/05/03 18:08:39  lindak
 *	Merged PR-2909558 into Jaguar (siegmund POST WWDC: add support for NetBoot
 *	over IOHDIXController)
 *	
 *	Revision 1.1.2.1  2002/04/24 22:29:12  dieter
 *	Bug #: 2909558
 *	- added IOHDIXController netboot stubs
 *	
 *	Revision 1.2  2002/04/14 22:56:47  han
 *	fixed up comment re dev_t
 *	
 *	Revision 1.1  2002/04/13 19:22:28  han
 *	added stub file DINetBookHook.c
 *	
 *
 */

#ifndef __DINETBOOKHOOK_H__
#define __DINETBOOKHOOK_H__

#include <sys/appleapiopts.h>

#ifdef __APPLE_API_PRIVATE 

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/*
	Name:		di_root_image
	Function:	mount the disk image returning the dev node
	Parameters:	path	->		path/url to disk image
				devname	<-		dev node used to set the rootdevice global variable
				dev_p	<-		combination of major/minor node
	Comments:	
*/
int di_root_image(const char *path, char devname[], dev_t *dev_p);

#ifdef __cplusplus
};
#endif

#endif /* __APPLE_API_PRIVATE */

#endif __DINETBOOKHOOK_H__

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
 * mach_header.c
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

#include <stdio.h>

#include <mach-o/mach_header.h>

extern struct mach_header _mh_execute_header;

/*
 * XXX: definitely belongs in libmach-o.
 */
struct segment_command *
getsegbyname(const char *s)
{
	int			i = 0, ncmds;
	struct mach_header	*mh;
	struct segment_command	*segcmd;

	mh = &_mh_execute_header;
	segcmd = (struct segment_command *)(mh + 1);
	ncmds = mh->ncmds;

	for (i = 0; i < ncmds; i++) {
		if (strcmp(segcmd->segname, s) == 0)
			return (segcmd);

		segcmd = (struct segment_command *)((char *)segcmd +
		    segcmd->cmdsize);
	}

	return (NULL);
}

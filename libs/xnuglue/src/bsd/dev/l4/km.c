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
 * km.c
 *
 */

#include <l4/ipc.h>

#include <xnucompat.h>
#include <stdio.h>	/* printf on err */

void cons_cinput(char);
int kmputc(int);

void darbat_char_notify( int c );

void
cons_cinput(char ch)
{
	//L4_MsgTag_t	tag;

	if (!ttyfifo)
		return;

#if 0
	lck_spin_lock(xnulck);
	ll_add_end(ttyfifo, (void *)(int)ch);
	lck_spin_unlock(xnulck);

	printf("cons_cinput called, c = %d (%c) \n", ch, ch);
#else
	darbat_char_notify( ch );
#endif

#if 0	
	/*
	 * Wake up guy
	 *
	 */
	tag = L4_Send(serialreadtid);
	if (L4_IpcFailed(tag))
		printf("%s: send to 0x%lx failed\n", 
		    __func__, serialreadtid.raw);
#endif
	return;
}

int
kmputc(c)
	int	c;
{

	printf("kmputc called, c = %d (%c) \n", c, c);

	return (0);
}

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
 * disk.c
 *
 * Simple test for I/O Kit disk read performance, cross protection domain.
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au>
 *
 * It is harmless if you leave this here, if you want to enable this test,
 * make sure that you enable the reply to the L4_Call() in iokit.c in
 * the main Iguana I/O Kit server.
 */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <l4/ipc.h>
#include <l4/kdebug.h>
#include <l4/schedule.h>
#include <l4/thread.h>

#include <kern/debug.h>
#include <kern/locks.h>

#include <iguana/memsection.h>

/*
 * XXX
 *
 * Should be in iokit_disk.h
 */
#include <iguana/iokit_disk.h>

#include <naming/naming.h>

/*
 * XXX does not belong here
 */
enum uio_rw { UIO_READ, UIO_WRITE };

static L4_Word_t num_sectors; /* number of sectors on the disk */
static L4_ThreadId_t iokit_tid;
void *shared_buffer;

static lck_mtx_t	*disklck;
static lck_grp_t	*disklckgrp;
static lck_grp_attr_t	*disklckgrpattr;
static lck_attr_t	*disklckattr;


extern void disk_get_geom( unsigned int *nblocks, unsigned int *blocksz );

void 
disk_get_geom( unsigned int *nblocks, unsigned int *blocksz )
{
	*nblocks = num_sectors;
	*blocksz = 512;
}


/*
 * XXX header please
 *
 * Also, there should be some way for these routines to return
 * error values!!
 */
void disk_read(unsigned long long offset, unsigned int size);
void disk_write(unsigned long /*caddr_t*/vaddr, unsigned long long offset, 
	unsigned int size);
void disk_rdwr(unsigned long long offset, unsigned int size, int what);

void
disk_read(unsigned long long offset, unsigned int size)
{

	lck_mtx_lock(disklck);
	disk_rdwr(offset, size, DISKREAD);
	lck_mtx_unlock(disklck);
}

void
disk_write(unsigned long/*caddr_t*/ vaddr,
	unsigned long long offset, unsigned int size)
{

	lck_mtx_lock(disklck);
	/*
	 * Clag that into the buffer.
	 *
	 */
	memcpy(shared_buffer, (void *)vaddr, size);
	disk_rdwr(offset, size, DISKWRITE);
	lck_mtx_unlock(disklck);
}


void
disk_rdwr(unsigned long long offset, unsigned int size, int what)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
	L4_Word_t	bs;
	L4_Word_t	done;

#if 0
	switch (what) {
		case DISKREAD:
			/* FALLTHROUGH */
		case DISKWRITE:
			break;
		default:
			panic("disk_rdwr: bad request");
	}
#endif
	if (size > DISKBUFSIZ) 
		bs = DISKBUFSIZ;
	else
		bs = size;

	for (done = 0; done < size; done += bs) {

		L4_MsgClear(&msg);
		L4_MsgAppendWord(&msg, what);
		L4_MsgAppendWord(&msg, 
			(L4_Word_t)((offset + done) & 0xffffffffULL));
		L4_MsgAppendWord(&msg, 
			(L4_Word_t)((offset  + done) >> 32ULL));
		/*
		 * XXX guess we should check disk geom.  Could read past
		 * the end of the disk, if it happened to be the last block
		 * and offset > end of block
		 */
		L4_MsgAppendWord(&msg, (L4_Word_t)bs);
		L4_MsgLoad(&msg);

#if 0
		printf("%s: op %s offset %llu bs %d\n",
		    __FUNCTION__,
		    what == DISKREAD ? "read" : "write", 
		    offset, size);
#endif
		tag = L4_Call(iokit_tid);
		if (!L4_IpcSucceeded(tag))
			panic("iokitdisk: disk transfer to iokit server "
			    "failed");
	}
}


/* XXXXXXXXXXX */
/* just easier this way for now... */
void disk_net_tx(void);

void
disk_net_tx(void)
{
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;

	/* setup msg */
	L4_MsgClear(&msg);
	L4_Set_MsgLabel(&msg, 0x101 << 4);
	L4_MsgAppendWord(&msg, 0x101); /* MR 0 = LOL */

	/* send */
	L4_MsgLoad(&msg);
	tag = L4_Send(iokit_tid);
	assert(L4_IpcSucceeded(tag));
}

int disk_init(void);

int
disk_init(void)
{
	uintptr_t	sharedbase;
#if 0	/* requires l4compat */
	L4_Word64_t	starttime, endtime;
#endif
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
#if 0	/* TESTING ONLY */
	int		left, bs;
#endif

	printf("iokit_disk: initializing.\n");

	sharedbase = 0;
	while(sharedbase == 0) {
		sharedbase = naming_lookup("iokit_memsection");
		if (sharedbase == 0)
			L4_Yield();
	}

	shared_buffer = (void*) sharedbase;
	printf("iokit_disk: got sharedbase %p\n", shared_buffer);

	iokit_tid.raw = 0;
	while(iokit_tid.raw == 0) {
		iokit_tid.raw = naming_lookup("iokit_tid");
		if (iokit_tid.raw == 0)
			L4_Yield();
	}

	printf("iokit_disk: got iokit_tid 0x%lx\n", iokit_tid.raw);

	printf("iokit_disk: making sure shared base (%p) is OK.\n",
	    (void *)sharedbase);

	memset((void *)sharedbase, '\0', DISKBUFSIZ);

	printf("iokit_disk: ok.\n");

	/*
	 * Initialize the locks.
	 *
	 */
	disklckgrpattr = lck_grp_attr_alloc_init();
	disklckattr = lck_attr_alloc_init();
	lck_attr_setdefault(disklckattr);
	lck_grp_attr_setdefault(disklckgrpattr);
	disklckgrp = lck_grp_alloc_init("disklck", disklckgrpattr);
	disklck = lck_mtx_alloc_init(disklckgrp, disklckattr);

	L4_MsgClear(&msg);
	L4_Set_MsgLabel(&msg, 0xab << 4);
	L4_MsgLoad(&msg);
	tag = L4_Call(iokit_tid);
	assert(L4_IpcSucceeded(tag));

	/* get the value out */
	L4_MsgStore(tag, &msg);
	num_sectors = L4_MsgWord(&msg, 0);

	printf( "iokit replied, num_sectors = %lu\n", num_sectors );

#if 0	/* TESTING ONLY */
	printf( "iokit_disk: doing inter-space read test.\n" );

// #define MOVESIZE	(14 * 1024 * 1024)
#define MOVESIZE	(64 * 1024) 

	/*
	 * mr 0: read/write
	 * mr 1: offset (low)
	 * mr 2: offset (high)
	 * mr 3: size
	 */
	// bs = 4 * 1024;
	bs = 512;

	for (;;) 
	{

		left = MOVESIZE;

		if (bs > (4 * 1024))
			break;

#if 0		/* XXX: requires l4compat */
		starttime = L4_SystemClock().raw;
#endif

		for (;;) 
		{

			/*
			 * From the lmdd source code this is seems to
			 * what happens when we use the move= parameter.
			 *
			 * It uses integers, and it rounds down.
			 * We'll emulate this
			 */
			if (left < bs)
				break;

			/* XXX: call disk_read instead of clagging! */
			L4_MsgClear(&msg);
			L4_MsgAppendWord(&msg, UIO_READ);
			L4_MsgAppendWord(&msg, (L4_Word_t)(MOVESIZE - left));
			L4_MsgAppendWord(&msg, (L4_Word_t)0);
			L4_MsgAppendWord(&msg, bs);
			L4_MsgLoad(&msg);
			tag = L4_Call(iokit_tid);

			printf("first word of the shared base is %p\n",
			    (void *)*(unsigned long *)sharedbase);
			left -= bs;
		}

#if 0		/* XXX: requires l4compat */
		endtime = L4_SystemClock().raw;

		printf("iokit_disk: time taken %llu us (bs = %dk)\n",
		    (endtime - starttime), bs);
#else
		printf("iokit_disk: test done.\n");
#endif

		bs *= 2;

		break;
	}

#endif	/* TESTING ONLY */
	return (0);
}

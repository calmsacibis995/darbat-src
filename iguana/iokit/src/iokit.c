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
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2004 National ICT Australia
 * 
 * All rights reserved. 
 * 
 * Developed by: Embedded, Real-time and Operating Systems Program (ERTOS)
 *               National ICT Australia
 *               http://www.ertos.nicta.com.au
 * 
 * Permission is granted by National ICT Australia, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of National ICT Australia, nor the names of its
 *       contributors, may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
 * PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
 * NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
 * WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
 * REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
 * THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
 * ERRORS, WHETHER OR NOT DISCOVERABLE.
 * 
 * TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
 * NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
 * THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
 * LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
 * OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
 * OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
 * OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
 * CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
 * CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
 * CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
 * DAMAGES OR OTHER LIABILITY.
 * 
 * If applicable legislation implies representations, warranties, or
 * conditions, or imposes obligations or liability on National ICT
 * Australia or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of National ICT Australia or the contributor is limited, to
 * the full extent permitted by the applicable legislation, at its
 * option, to:
 * a.  in the case of goods, any one or more of the following:
 * i.  the replacement of the goods or the supply of equivalent goods;
 * ii.  the repair of the goods;
 * iii. the payment of the cost of replacing the goods or of acquiring
 *  equivalent goods;
 * iv.  the payment of the cost of having the goods repaired; or
 * b.  in the case of services:
 * i.  the supplying of the services again; or
 * ii.  the payment of the cost of having the services supplied again.
 * 
 * The construction, validity and performance of this licence is governed
 * by the laws in force in New South Wales, Australia.
 */

/*
 * Geoffrey Lee < glee at cse.unsw.edu.au > 
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <l4/ipc.h>
#include <l4/kdebug.h>
#include <l4/schedule.h>	/* L4_Yield() */
#include <l4/types.h>		/* L4_Clock_t */

#include <iguana/thread.h>
#include <iguana/memsection.h>

#include <naming/naming.h>

#include <iguana/iokit_disk.h>

#include <kern/locks.h>
#include <kern/thread.h>
#include <xnucompat.h>

#include <pexpert/pexpert.h>

#include <ll.h>		/* crappy linked lists */

// #include <fb.h>		/* crappy fb */

L4_ThreadId_t		iokitservtid;
L4_ThreadId_t		darbattid;
L4_ThreadId_t		iokittesttid;

#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/conf.h>	/* bdevsw/cdevsw */
#include <sys/disk.h>	/* ioctl DKIOCGETBLOCKCOUNT{,32} */
#include <sys/uio_internal.h>

/*
 * Darwin dev_t's majors are 8 bits, followed by 24 bits for the minor.
 */
#define ROOTMINOR	(2UL)	/* Minor of the root disk. */
#define DISKMAJOR	(14UL)
#define DISKDEV		((DISKMAJOR << 24UL) | ROOTMINOR) /* 14,ROOTMINOR */
//#define DISKDEV		((DISKMAJOR << 24UL) | 0x0UL) /* 14,0 (disk0s0) */

#define SERIALMAJOR	(9UL)
#define SERIALDEV	(SERIALMAJOR)
#define SERIAL0A	((SERIALMAJOR << 24UL) | 0x1)
#define SERIAL0B	((SERIALMAJOR << 24UL) | 0x3UL)

void iokit_main(void);

uintptr_t	sharedbase;

/* XXX */
extern void do_net_tx(void);

static unsigned
read_cycles( void )
{
    unsigned ret;
    asm volatile ("rdtsc" :"=a" (ret) : :"edx");
    return ret;
}



int
main(int argc, char *argv[])
{
	/*
	 * start XNU glue emulation
	 */
	xnuinit();

	/*
	 * This is required because we really need a separate context
	 * for the I/O Kit.
	 *
	 * This is done so that even the initialization thread of the I/O 
	 * Kit is registered with the xnuglue threading mechanism
	 */
	kernel_thread_start((thread_continue_t)iokit_main, NULL, NULL);

	/*
	 * XXX should kill?
	 */
	L4_Sleep(L4_Never);
}

void serialread(void);
void bsdthread(void);
struct ll *ttyfifo;
int serialReady;	/* XXX */
static L4_ThreadId_t	serialwaittid;
L4_ThreadId_t	serialreadtid;

/*
 * serialread()
 *
 * This is essentialy a callout that fires every 30msec to check
 * whether we have a character.  If we have, then we read it in, and
 * then hand it back to the user.
 */
void
serialread(void)
{
	L4_Msg_t	msg;
	L4_ThreadId_t	tid;
	L4_MsgTag_t	tag;
	int		c;
#if 0	/* XXX: enable me for DTK */
	int		rc;
#endif

	printf("serialread: initializing.\n");
	ttyfifo = ll_new();
	assert(ttyfifo);
	serialreadtid.raw = L4_Myself().raw;

	L4_KDB_SetThreadName(L4_Myself(), "iokitserial");

#if 0	/* XXX: Enable me for DTK */
	/*
	 * Now, everything is ready, so open the device!
 	 */
	while (serialReady != 2)
		L4_Sleep(L4_TimePeriod(30 * 1000));

	printf("iokit: trying to open device 0x%lx\n", SERIAL0B);
	rc = cdevsw[SERIALMAJOR].d_open(
		SERIAL0B, 0/*r/w*/, 0020000/*S_ISCHR*/,
		NULL/*proc_t*/);
	printf("iokit: rc is %d\n", rc);
#endif

restart:
	tag = L4_Wait(&tid);
	for (;;) {

		lck_spin_lock(xnulck);

		if (serialwaittid.raw != L4_nilthread.raw) {

			c = (int)ll_pop(ttyfifo);
			if (!c)
				c = -1;
#if 0
			if (!c) {
			/*
			 * Surely if we got woken up there must be a char??
			 *
			 */
				assert(!"shit serial no char");
			}
#endif

			L4_MsgClear(&msg);
			L4_MsgAppendWord(&msg, c);
			L4_MsgLoad(&msg);

			L4_Set_VirtualSender(iokitservtid);

			tid.raw = serialwaittid.raw;
			/*
			 * Reset the  thread
			 *
			 */
			serialwaittid.raw = L4_nilthread.raw;
			lck_spin_unlock(xnulck);

			tag = L4_ReplyWait(tid, &tid);
		} else {
			/*
			 * Right, no one is waiting.
			 *
			 */
			lck_spin_unlock(xnulck);
			goto restart;		
		}
	}
}

void wakeserial(void);

/*
 * wakeserial
 *
 * This function is called with the xnulck lock held.
 */
void
wakeserial(void)
{
	L4_MsgTag_t	tag;
#if 0
	int 		c;
#endif

	/*
	 * See if we have a character.  If so, then put it back on the
	 * the queue and then do a manual wakeup.
	 *
	 * XXX XXX no peek function in the lists.
	 */
	if (ttyfifo) {
#if 0
		if ((c = (int)ll_pop(ttyfifo))) {

			ll_add_front(ttyfifo, (void *)c);
#endif
			tag = L4_Send(serialreadtid);
			assert(L4_IpcSucceeded(tag));
#if 0
		}
#endif
	}
}

/* XXX */
void iokit_netbuf_init( void * start, unsigned len );

void
iokit_main(void)
{
	
	PE_init_platform(0, NULL);
	PE_init_iokit();

	/*
	 * Must be called separately from xnuinit().
	 *
	 * We need to initialize the IOKit first, as it makes some use
	 * of libkern and etc.
	 */
	bsdinit();

	sharedbase = 0;

	/*
	 * XXX:
	 *
	 * 0, or -1UL?
	 */
	while (!sharedbase) {
		if (!(sharedbase = naming_lookup("iokit_memsection")))
			L4_Yield();
	}

	printf("iokit: making sure shared base (%p) is OK.\n", 
		(void *)sharedbase);
	memset((void *)sharedbase, 0x42/*poison*/,DISKBUFSIZ);

	/* XXX: Give the rest of the buffer to network */
	iokit_netbuf_init( (char*)sharedbase + DISKBUFSIZ, 
			   (1<<20) - DISKBUFSIZ );

	/*
	 * Start serial read thread here
	 *
	 * XXX we should get rid of this
	 *
	 * Unify this??
	 */
	kernel_thread_start((thread_continue_t)serialread, NULL, NULL);
	kernel_thread_start((thread_continue_t)bsdthread, NULL, NULL);

	L4_Sleep(L4_Never);
}

void
bsdthread(void)
{
	L4_MsgTag_t	tag;
	L4_ThreadId_t	tid;
	L4_Msg_t	msg;
	L4_Word_t	mr[3];
	int		i, rc;
	int		c;
	unsigned long	blockcnt;
	/*
	 * BSD stuff
	 */
	uio_t		uio;
	struct	iovec	iovec;

	iokitservtid = L4_Myself();
	naming_insert("iokit_tid", L4_Myself().raw);

	printf("iokit: waiting for filesystem to be up.\n");

	/*
	 * Wait for notification from IOMediaBSDClient that the FS is
	 * up.  Basically wait for all the users of the iokit server
	 *
	 * XXX this is *NOT* the right way to do this!  The right way is
	 * to call IOFindBSDRoot which does black magic matching.
	 *
	 * The other obvious issue is that any schmuck can send is an
	 * IPC message and then afterwards, if it is not from IOMediaBSDClient,
	 * we are fucked.
	 *
	 * Also wait for wombat, but we don't know who will come firrst.  But
	 * Wombat will have the extra tag of 0xab >> 4.
	 */
	for (i = 0; i < 2; i++) {
startover:
		tag = L4_Wait(&tid);
		assert(L4_IpcSucceeded(tag));
		L4_MsgStore(tag, &msg);

		switch (L4_MsgLabel(&msg) >> 4) {
			case 0xab:
				printf("iokit: 0x%lx claims to be darbat.\n", 
				    tid.raw);
				darbattid.raw = tid.raw;
				break;
			case 0xac:
				printf("iokit: 0x%lx claims to be "
				     "iokittest.\n", tid.raw);
				iokittesttid.raw = tid.raw;
				break;
			default:
				/*XXX DISGUSTING XXX*/
				L4_MsgStore(tag, &msg);
				if (L4_MsgWord(&msg, 0) != ROOTMINOR) 
					goto startover;
				else
				printf("iokit: 0x%lx claims to be fs.\n", 
				    tid.raw);
				/*
			 	 * For fs, we just need to be woken up.
				 */
				break;
		}
	}

	/*
	 * Open the device.  This probably doesn't do much,
	 * except increase the reference count or some such.
	 *
	 * XXX OK?  We issue S_ISBLK on a character device.
	 * The code inside seems to suggest that this is not checked
	 * since it uses the same functions for both block and character
	 * access but don't count on it.
	 */
	rc = cdevsw[DISKMAJOR].d_open(
		DISKDEV, 0/*r/o*/, 0060000/*S_ISBLK*/,
		NULL/*proc_t, ignored*/);

	printf("iokit: rc is %d\n", rc);
	printf("iokit: %s device 0x%lx\n", 
		(rc == 0) ?  "opened" : "failed to open",
		DISKDEV);

	uio = malloc(sizeof(struct uio));
	if (!uio)
		panic("blkthread: can't allocate uio");

	/*
	 * Send a reply back to Darbat to tell us how big the disk
	 * is.  Actually, perhaps we can send the geometry here in one 
	 * go too, but we can't be bothered.  XXX TODO
	 *
	 * XXX using unsigned long for blockcnt is probably bad
	 */
	rc = cdevsw[DISKMAJOR].d_ioctl(DISKDEV, 
			DKIOCGETBLOCKCOUNT32, 
			(caddr_t)&blockcnt, 0, 0);
	printf("iokit: ioctl DKIOCGETBLOCKCOUNT returned %d, "
		"blockcount is %lu\n", rc, blockcnt);
	assert(rc == 0);
	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, (L4_Word_t)blockcnt);
	L4_MsgLoad(&msg);
	tag = L4_Reply(darbattid);
	assert(L4_IpcSucceeded(tag));

restart:
	/*
	 * Simply assume that this is actually from Darbat.
	 *
	 * It might not be ...
	 *
	 * XXX FIXMEEEEE!!!
	 */
	tag = L4_Wait(&tid);

	for (;;) {
		iovec.iov_base = (void *)sharedbase;
		assert(iovec.iov_base);

		/*
		 *
	 	 * XXX fixme
		 *
		 * Since DISKBUFSIZ is not necessarily 512, you might
		 * run past the end of the disk.  That's bad.
		 */
		iovec.iov_len = DISKBUFSIZ;

		uio->uio_iovs.iovp = &iovec;
		uio->uio_iovcnt = 1;
		uio->uio_offset = 0;
		uio->uio_resid = DISKBUFSIZ;
		(void)uio->uio_segflg;
		uio->uio_rw = UIO_READ;
		uio->uio_max_iovs = 1;

		if (!L4_IpcSucceeded(tag)) {
			printf("iokit: badness failed ipc\n");
			goto restart;
		}

		L4_MsgStore(tag, &msg);

		/*
		 * XXX DOCUMENT ME
		 *
	 	 * Protocol:
		 *
		 * mr[0] = request
		 * mr[1] = offset_lo
		 * mr[2] = offset_hi
		 * mr[3] = size
		 *
		 */
		for (i = 0; i < 4; i++)
			mr[i] = L4_MsgWord(&msg, i);

		switch (mr[0]/*req*/) {

			case DISKREAD:
				uio->uio_rw = UIO_READ;
				uio->uio_offset = 
				    ((unsigned long long)mr[2] << 32ULL) |
				    (unsigned long long)mr[1];
				/*
			 	 * these two are fine, they will be patched
				 * back up to the default when we loop around
				 */
				uio->uio_resid = mr[3];
				iovec.iov_len = mr[3];

				rc = cdevsw[DISKMAJOR].d_read(DISKDEV, 
					uio, 0/*unused*/);
	
				if (rc != 0) {
					printf("iokit: got rc %d!\n", rc);
					L4_KDB_Enter("XXX");
				}
				break;
			case DISKWRITE:
				uio->uio_rw = UIO_WRITE;
				uio->uio_offset = 
				    ((unsigned long long)mr[2] << 32ULL) |
				    (unsigned long long)mr[1];
				/*
			 	 * these two are fine, they will be patched
				 * back up to the default when we loop around
				 */
				uio->uio_resid = mr[3];
				iovec.iov_len = mr[3];
				rc = cdevsw[DISKMAJOR].d_write(DISKDEV,
					uio, 0/*unused*/);
				if (rc != 0) {
					printf("iokit: got rc %d!\n", rc);
					L4_KDB_Enter("XXX");
				}
				break;
			case SERIALWRITE:
				/* XXX BANDAID */
#if 0	/* XXX: Only for DTK */
				if (serialReady != 2)
					break;
				rc = cdevsw[SERIALMAJOR].d_write(
				    SERIAL0B, (void *)&mr[1],
				    0/*XXX what's this?*/);
				/* XXX CHECK rc ? */
#else	/* only for production h/w */
				// fb_putchar_interp((unsigned char)mr[1]);
				L4_KDB_Enter("No serial write!!");
#endif
				break;
			case SERIALREAD:

				/* don't poll IOKit via IPC */
				L4_KDB_Enter("No serial read!!");

				/*
				 * XXX we bypass all of that serial tty layer
				 * stuff!!!!
				 */
				//lck_spin_lock(xnulck);
				serialwaittid.raw = tid.raw;
				/*
				 * XXX
				 *
				 * Hack: the buffer might have filled up
				 * in the meantime, in which case, we kick
				 * the serialread thread directly.
				 */
#if 0
				wakeserial();
				lck_spin_unlock(xnulck);
				goto restart;	/* don't reply */
#endif
				lck_spin_lock(xnulck);
				c = -1;
				if (ttyfifo)
					c = (int)ll_pop(ttyfifo);
				if (c == 0)
					c = -1;
				lck_spin_unlock(xnulck);
				break;

			case 0x101: /* LOL! ^_^ */
				do_net_tx();
				goto restart; /* don't reply */
				break;
			default:
				printf( "unknown IOKit disk req: 0x%x\n",
					(unsigned int) mr[0] );
				goto restart;
				break;
		}

		L4_MsgClear(&msg);
		L4_Set_MsgLabel(&msg, 0x66 << 4);
		L4_MsgAppendWord(&msg, c);
		L4_MsgLoad(&msg);

		tag = L4_ReplyWait(tid, &tid);
	}

	L4_KDB_Enter("NOTREACHED");
}

/* Notify Darbat (main thread for now...) that we have received some data.
 * since it does a blocking send, and may otherwise be busy, do retries.
 *
 * something something.
 */
void darbat_rx_notify(void);

/* XXX: network packet received */
/* clag from clockthread.h */
#define CT_REQ_RX     0x1414

void
darbat_rx_notify(void)
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

	while(1)
	{
		L4_MsgClear(&msg);
		L4_Set_MsgLabel(&msg, CT_REQ_RX);
		L4_MsgLoad(&msg);

		tag = L4_Send_Nonblocking( darbattid );

		/* notify sent OK */
		if( L4_IpcSucceeded( tag ) )
			return;

		/* All we can do is yield and try again */
		// printf( "Yielding on RX notify\n" );
		// L4_Yield();
		L4_ThreadSwitch( darbattid );
	}
}


/* XXX: console char received */
/* clag from clockthread.h */
#define CT_REQ_CONSIN     0x4321

void darbat_char_notify( int c );

void
darbat_char_notify( int c )
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

	// printf( "IOKit sending char %c (%d)\n", c, c );

	while(1)
	{
		L4_MsgClear(&msg);
		L4_Set_MsgLabel(&msg, CT_REQ_CONSIN);
		L4_MsgAppendWord(&msg, c);
		L4_MsgLoad(&msg);

		tag = L4_Send_Nonblocking( darbattid );

		/* notify sent OK */
		if( L4_IpcSucceeded( tag ) )
			return;

		/* All we can do is yield and try again */
		// printf( "iokit: Yielding on cons input\n" );
		// L4_Yield();
		L4_ThreadSwitch( darbattid );
	}
}
/*
 * iokit_test.c
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

#include <l4/ipc.h>
#include <l4/thread.h>

#include <iguana/memsection.h>
#include <iguana/iokit_disk.h>

/*
 * XXX does not belong here
 */
enum uio_rw { UIO_READ, UIO_WRITE };

struct test {
	int	reverse;	/* reverse block size ? */
	int	skipsiz;	/* skip # byytes per transfer */
	int	minblocksiz;	/* min. block size touse */
	int	maxblocksiz;	/* max block sizae to use */
	int	movesiz;	/* tottal bytes to trasnfer */
	int	offset;		/* initial offset of disk/part to start */
};

/*
 * Definable constants
 *
 * MOVESIZE: move how many bytes per benchmark
 * SKIPSIZE: skip over how many bytes per block transfer
 * OFFSET: start at OFFSET of partition/disk
 * MAXBLOCKSIZ: maximum block size per transfer to use ( < MOVESIZE )
 * MINBLOCKSIZ: minimum block size to use
 */
#define MOVESIZ		(14 * 1024 * 1024)
#define SKIPSIZ		(16 * 1024 * 1024)
#define OFFSET		(0)
#define MAXBLOCKSIZ	(8 * 1024 * 1024)
#define MINBLOCKSIZ	(4 * 1024)

struct test testdat[] = {
	{ 0, 0, MINBLOCKSIZ, MAXBLOCKSIZ, MOVESIZ, 0 },
	{ 1, 0, MINBLOCKSIZ, MAXBLOCKSIZ, MOVESIZ, 0 },
	{ 0, SKIPSIZ, MINBLOCKSIZ, MAXBLOCKSIZ, MOVESIZ, 0 },
	{ 1, SKIPSIZ, MINBLOCKSIZ, MAXBLOCKSIZ, MOVESIZ, 0 }
};

int
main(void)
{
	uintptr_t	sharedbase;
	L4_Word64_t	starttime, endtime;
	L4_Msg_t	msg;
	L4_MsgTag_t	tag;
	L4_ThreadId_t	iokit_tid;
	int		i, left, bs;

	printf("iokit_test: initializing.\n");

	sharedbase = 0;
	iokit_tid.raw = 0;

	do 
		sharedbase = naming_lookup("iokit_memsection");
	while (!sharedbase);

	do
		iokit_tid.raw = naming_lookup("iokit_tid");
	while (!iokit_tid.raw);

	printf("iokit_test: iokit_tid is 0x%lx\n", iokit_tid.raw);

	printf("iokit_test: making sure shared base (%p) is OK.\n",
	    (void *)sharedbase);

	memset((void *)sharedbase, '\0', DISKBUFSIZ);

	printf("iokit_test: ok.\n");

	L4_MsgClear(&msg);
	L4_Set_MsgLabel(&msg, 0xac << 4);
	L4_MsgLoad(&msg);
	tag = L4_Call(iokit_tid);
	assert(L4_IpcSucceeded(tag));

restart:
	printf("iokit_test: doing inter-space read test.\n");


	/*
	 * mr 0: read/write
	 * mr 1: offset
	 * mr 2: size
	 */

	for (i = 0; i < sizeof(testdat)/sizeof(testdat[0]); i++) {

		bs = testdat[i].reverse ? testdat[i].maxblocksiz : 
		    testdat[i].minblocksiz;

		for (;;) {

			left = testdat[i].movesiz;

			if (bs > testdat[i].maxblocksiz ||
			    bs < testdat[i].minblocksiz)
				break;

			starttime = L4_SystemClock().raw;

			for (;;) {

				/*
				 * From the lmdd source code this is seems to
				 * what happens when we use the move= parameter.
				 *
				 * It uses integers, and it rounds down.
				 * We'll emulate this
				 */
				if (left < bs)
					break;

				/*
				 * XXX
				 *
				 * BROKEN as 32 bit we run over off_t boundary
				 * which is 64!
				 */
				L4_MsgClear(&msg);
				L4_MsgAppendWord(&msg, DISKREAD);
				L4_MsgAppendWord(&msg, 
				    (L4_Word_t)(testdat[i].movesiz - left +
			    	    testdat[i].skipsiz + testdat[i].offset));
				L4_MsgAppendWord(&msg, bs);
				L4_MsgLoad(&msg);
				tag = L4_Call(iokit_tid);

				left -= bs;

			}

			endtime = L4_SystemClock().raw;

			printf("iokit_test: time taken %llu us (bs = %d "
			    "reverse = %d movesize = %d skipsiz = %d)\n",
			    (endtime - starttime), bs, testdat[i].reverse,
			    testdat[i].movesiz, testdat[i].skipsiz);

			bs = (testdat[i].reverse) ? bs / 2 : bs * 2;
		}
	}

	printf("iokit_test: inter-space read test completed.\n");

	goto restart;

	L4_Sleep(L4_Never);

	/* NOTREACHED */
	return (0);
}


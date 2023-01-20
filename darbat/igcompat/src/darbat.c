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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <igcompat/darbat.h>
#include <iguana/memsection.h>

#include <l4/bootinfo.h>
#include <l4/kip.h>
#include <l4/thread.h>
#include <l4/schedule.h>
#include <l4/ipc.h>
#include <l4/space.h>
#include <l4/kdebug.h>
#include <l4e/thread.h>

#include <kern/debug.h>
#include <kern/task.h>
#include <kern/thread.h>

#include <iguana/eas.h>
#include <iguana/thread.h>

#include <naming/naming.h>
/* XXX: this file uses the kenge timers */
#include <timer/timer.h>

#include <iguana/iokit_disk.h>	/* XXX has serial stuff thre too!! */

#define ROOTDISK_NAME "disk.img"


/* misc stuff */
uint64_t
darbat_cpu_freq(void)
{
	L4_KernelInterfacePage_t *kip;
	L4_ProcDesc_t *pd;
	L4_Word_t freq, dummy;

	kip = L4_KernelInterface(&dummy, &dummy, &dummy);
	
	pd = L4_ProcDesc( kip, 0 );

	freq = L4_ProcDescInternalFreq( pd );

	return ((uint64_t)freq) * 1000; /* freq is in kHz */
}


/* memory regions */
void *
darbat_rgn_alloc( uintptr_t size )
{
	memsection_ref_t ref;
	uintptr_t base;

	ref = memsection_create( size, &base );

	return (void*) base;
}

void *
darbat_mapped_rgn_alloc( uintptr_t size )
{
	memsection_ref_t ref;
	uintptr_t base;

	ref = memsection_create_user( size, &base );

	return (void*) base;
}

void
darbat_map( void *phys, void *virt )
{
	memsection_ref_t ref;
	thread_ref_t dummy_server;
	int r;
	L4_Fpage_t from_fp, to_fp;

    //printf("Doing a darbat map %p -> %p\n", phys, virt);

	/* ref == ref to destination (to_fp obj) */
	ref = memsection_lookup( (objref_t) virt, &dummy_server );

	/* construct fpages */
	/* to_fp == in user paged memsection, from_fp == iguana backed */
	from_fp = L4_Fpage( (L4_Word_t) phys, 4096 );
	to_fp = L4_Fpage( (L4_Word_t) virt, 4096 );

	r = memsection_page_map( ref, from_fp, to_fp );
	assert( r == 0 );
	
}

void 
darbat_flush_page( void *addr )
{
	//int r;
	//memsection_ref_t ref;
	L4_Fpage_t fp;
	//thread_ref_t dummy_server;

	/* virt obj */
	//ref = memsection_lookup( (objref_t) addr, &dummy_server );

	/* this *should* do the L4 unmap, too */
	fp = L4_Fpage( (L4_Word_t) addr, 4096 );
	L4_Set_Rights( &fp, L4_FullyAccessible ); /* set the perms */
    L4_Flush(fp);
    //r = memsection_page_unmap( ref, fp );
	//assert( r == 0 );

}

void
darbat_unmap_page(void *addr)
{
	L4_Fpage_t fp = L4_Fpage((L4_Word_t)addr, 4096); 
	L4_Set_Rights(&fp, L4_FullyAccessible);
	L4_UnmapFpage(fp);
}

void darbat_remove_write(void *addr);
void
darbat_remove_write(void *addr)
{
	L4_Fpage_t fp = L4_Fpage((L4_Word_t)addr, 4096); 
	L4_Set_Rights(&fp, L4_Writable);
    L4_UnmapFpage(fp);
}

void darbat_flush_write(void *addr);
void darbat_flush_write(void *addr)
{
	L4_Fpage_t fp = L4_Fpage((L4_Word_t)addr, 4096); 
	L4_Set_Rights(&fp, L4_Writable);
    L4_Flush(fp);
}

/* threads 'n' stuff */
/* XXX */
L4_ThreadId_t darbat_l4id(void);

L4_ThreadId_t
darbat_l4id(void)
{
	return thread_l4tid( thread_myself() );
}

unsigned long
darbat_create_kthread( void (*start_ip)(void*), void *arg )
{
	thread_ref_t tr;
	L4_ThreadId_t tid;

	/* create the thread */
	tr = thread_create_simple( start_ip, arg, -1 );
	
	printf( "XXX: what's thread_create failure look like?\n" );

	/* get the L4 id */
	tid = thread_l4tid( tr );
	
	return tid.raw;
}

void 
darbat_start_thread( unsigned int ntid, unsigned int nip, unsigned int nsp )
{
	L4_ThreadId_t tid;
	L4_Word_t ip, sp;
	int r;

	tid.raw = ntid;
	ip = nip;
	sp = nsp;

	// L4_KDB_Enter("starting thread");

	r = l4e_thread_start( tid, ip, sp );

	if( r != 0 )
		assert( !"failed to l4e_thread_start?" );
}


void darbat_clean_eas(thread_t);
unsigned long
darbat_thread_create( thread_t thread )
{
	/* create a space */
	L4_ThreadId_t tid;
	task_t task;
	eas_ref_t eas;

	task = get_threadtask(thread);

	eas = task_get_eas(task);

	if( eas == 0)
	{
		assert(!"creating a darbat thread in a task without an EAS");
	}

	void *utcb = task_get_next_utcb_base(task);
	tid = eas_create_thread(eas, L4_Myself(), L4_Myself(), utcb);

	return tid.raw;
}

int
darbat_cons_poll_nonblocking(void)
{
	return L4_KDB_ReadChar();

	// OK to poll: IOKit returns -1 if no char.
	// return darbat_cons_poll();
}

#if 0	/* Arcane code */
int
darbat_cons_poll(void)
{

	return L4_KDB_ReadChar_Blocked();
}
#endif

extern void vcputc(int l, int u, int c);

#if !L4SERIAL
void
darbat_cons_write(int c)
{
#if 0
	L4_ThreadId_t	tid;
	L4_MsgTag_t	tag;
	L4_Msg_t	msg;	

	tid.raw = 0;
	/*
	 * XXX stupid
	 *
	 * We should cache this lookup
	 */
	while (tid.raw == 0) {
		tid.raw = naming_lookup("iokit_tid");
		if (tid.raw == 0)
			L4_Yield();
	}

	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, SERIALWRITE);
	L4_MsgAppendWord(&msg, (L4_Word_t)c);
	L4_MsgLoad(&msg);

	tag = L4_Call(tid);
	if (!L4_IpcSucceeded(tag))
		panic("oops");
#else
	vcputc( 0, 0, c );
#endif
	return;
}
#endif	/*L4SERIAL*/

#if 0
int
darbat_cons_poll(void)
{
	L4_ThreadId_t	tid;
	L4_MsgTag_t	tag;
	L4_Msg_t	msg;	
	int		c;

	tid.raw = 0;
	/*
	 * XXX
	 */
	while (tid.raw == 0) {
		tid.raw = naming_lookup("iokit_tid");
		if (tid.raw == 0)
			L4_Yield();
	}

	//printf("%s: got tid 0x%lx\n", __func__, tid.raw);

	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, SERIALREAD);
	L4_MsgLoad(&msg);

	tag = L4_Call(tid);
	if (!L4_IpcSucceeded(tag))
		panic("oops");

	L4_MsgStore(tag, &msg);

	c = (int)L4_MsgWord(&msg, 0);

	return c;
}
#endif

/***** Timers ******/

int 
darbat_periodic_function( int (*func)(void), unsigned msec )
{
	timer_t timer;
	timer_t timer_ret;
	int ret, r;

	{
		/* I'm not sure on the rules of doing this init...  CEG */
		static int done_init = 0;

		/* XXX: can fail, but has no return value. If the malloc
		 * inside fails, it de-references it anyway...
		 */
		if( done_init == 0 )
		{
			printf( "Doing timer_init\n" );
			timer_init();
			done_init = 1;
		}
	}

	printf( "Doing timer_create\n" );
	timer = timer_create();
	if( timer == NULL )
		return -1;

	printf( "Doing timer_request\n" );
	r = timer_request(timer, MILLISECS(msec), TIMER_PERIODIC);
	if( r != 0 )
		return -1;
	printf( "Done timer_request\n" );

	/* go into the waiting loop */
	while(1)
	{
		timer_ret = timer_wait();
		
		if( timer_ret != timer )
		{
			panic( "Strage timer_wait return value!?\n" );
			continue;
		}
		
		ret = func();
		if( ret != 0 )
			break;
	}

	/* clean up */
	r = timer_delete(timer);
	if( r != 0 )
		printf( "XXX: failed to delete timer!\n" );
		

	/* return exit code */
	return ret;
}


/***** This is kinda crappy ******/

static L4_BootRec_t *
find_bootrec(const char *fname)
{
	L4_KernelInterfacePage_t *kip;
	L4_BootRec_t *rec;
	void *bootinfo;
	unsigned num_recs, objs;

	/* Iterate through bootinfo */
	kip = L4_GetKernelInterface();
	bootinfo = (void*) L4_BootInfo(kip);
	num_recs = L4_BootInfo_Entries(bootinfo);
	rec = L4_BootInfo_FirstEntry(bootinfo);

	while(num_recs > 0)
	{
		L4_Word_t type;
		/* find what type it is */
		type = L4_BootRec_Type(rec);
		objs = 0;
		 /* Found it? */
		if (type == L4_BootInfo_Module 
		    && (strcmp(L4_Module_Cmdline(rec), fname) == 0))
			break;
		rec = L4_BootRec_Next(rec);
		num_recs--;
	}

	if (num_recs > 0)
		return rec;
	else
		return NULL;
}




/* find the root image in the bootinfo */
int
darbat_find_root_image( void **base, uintptr_t *size )
{
	L4_BootRec_t *rec = NULL;
	
	rec = find_bootrec( ROOTDISK_NAME );

	if( rec == NULL )
	{
		printf( "failed to find '%s' in L4 bootinfo\n", ROOTDISK_NAME );
		return 1;
	}

	*base = (void*) L4_Module_Start(rec);
	*size = L4_Module_Size(rec);

	return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <l4/kip.h>
#include <l4/thread.h>
#include <l4/kdebug.h>
#include <iguana/debug.h>
#include <iguana/memsection.h>
#include <iguana/pd.h>
#include <iguana/thread.h>
#include <iguana/session.h>
#include <iguana/cap.h>
#include <iguana/eas.h>
#include <iguana/object.h>
#include "test_libs_iguana.h"

#include <interfaces/iguana_client.h>

#define PAGE_SIZE 4096
#define MEM_SIZE 0x100

START_TEST(test_pd_myself)
{
	pd_ref_t myself = 0;
	myself = pd_myself();
	fail_if(myself == 0, "NULL pd returned");
}
END_TEST

START_TEST(test_pd_create)
{
	pd_ref_t newpd = 0;
	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	if (newpd != 0) {
		pd_delete(newpd);
	}
}
END_TEST

#ifdef CONFIG_LOWMEMORY
START_TEST(test_pd_create_many)
{
	pd_ref_t *pds = NULL;
	int max_pds;
	int i = 0, cursize = 100;
	
	pds = malloc(sizeof(struct session *) * cursize);

	do {
		if (i >= cursize) {
			cursize += 100;
			pds = realloc(pds, sizeof(pd_ref_t) * cursize);
			if (pds == NULL) {
				fail("Unable to allocate memory");
				break;
			}
		}
		pds[i] = pd_create(); 
	} while (pds[i++] != 0);

	max_pds = i - 1;
	printf("Created %d PDs\n", max_pds);

	for(i=0; i < max_pds; i++) {
		pd_delete(pds[i]);
	}

	free(pds);

	fail_unless(max_pds > 0, "Unable to create any protection domains");

	for(i=0; i < max_pds * 3; i++) {
		pd_ref_t pd;
		pd = pd_create();
		fail_if(pd == 0, "Unable to create PD");
		if (pd == 0) {
			printf("Couldn't create session\n");
			break;
		}
		pd_delete(pd);
	}
}
END_TEST
#endif

START_TEST(test_pd_create_pd)
{
	pd_ref_t newpd=0;
	newpd = pd_create_pd(pd_myself());
	fail_if(newpd == 0, "NULL pd returned");
	if (newpd != 0) {
		pd_delete(newpd);
	}
}
END_TEST

START_TEST(test_pd_myself_create_thread)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST

START_TEST(test_pd_myself_create_thread_with_priority)
{
	thread_ref_t iguana_thrd = 0;
	L4_ThreadId_t l4_thrd;
	
	iguana_thrd = pd_create_thread_with_priority(pd_myself(), 100, &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST
#if 0
START_TEST(test_pd_create_thread)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	pd_ref_t newpd=0;
	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	iguana_thrd = pd_create_thread(newpd, &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	thread_delete(l4_thrd);
	pd_delete(newpd);
}
END_TEST

START_TEST(test_pd_create_thread_with_priority)
{
	thread_ref_t iguana_thrd = 0;
	L4_ThreadId_t l4_thrd;
	pd_ref_t newpd=0;
	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	iguana_thrd = pd_create_thread_with_priority(newpd, 100, &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	thread_delete(l4_thrd);
	pd_delete(newpd);
}
END_TEST
#endif

START_TEST(test_pd_myself_create_memsection)
{
	memsection_ref_t memsec=0;
	uintptr_t base;
	int i=0;
	char *p;

	memsec = pd_create_memsection(pd_myself(), MEM_SIZE, &base);
	fail_if(memsec == 0, "NULL memsection returned");
	
	if (memsec == 0) {
		return;
	}
	p = (char*) base;

	memset(p, '%', 0x10);

	for (i=0;i<0x10;i++) {
		fail_if(*p != '%', "error data");
		p++;
	}

	memsection_delete(memsec);
}
END_TEST

START_TEST(test_pd_create_memsection)
{
	pd_ref_t newpd=0;
	memsection_ref_t memsec=0;
	uintptr_t base;


	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	memsec = pd_create_memsection(newpd, MEM_SIZE, &base);
	fail_if(memsec == 0, "NULL memsection returned");
	int i=0;
	char *p = (char *) base;
	memset((void *)base, '%', 0x10);
	for (i=0;i<0x10;i++)
	{
		fail_if(*p != '%', "error data");
		p++;
	}

	pd_delete(newpd);
}
END_TEST

START_TEST(test_pd_myself_set_callback)
{
	uintptr_t callback, callback_base;
	callback = pd_create_memsection(pd_myself(), MEM_SIZE, &callback_base);
	fail_if(callback == 0, "NULL memsection returned");
	pd_set_callback(pd_myself(), callback);
	memsection_delete(callback);
}
END_TEST

START_TEST(test_pd_set_callback)
{
	pd_ref_t newpd=0;
	uintptr_t callback, callback_base;
	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	callback = pd_create_memsection(newpd, MEM_SIZE, &callback_base);
	fail_if(callback == 0, "NULL memsection returned");
	pd_set_callback(newpd, callback);
	pd_delete(newpd);
}
END_TEST

START_TEST(test_pd_myself_add_release_clist)
{
	uintptr_t clist, clist_base;

	clist = pd_create_memsection(pd_myself(), MEM_SIZE, &clist_base);
	fail_if(clist == 0, "NULL clist returned");

	pd_add_clist(pd_myself(), clist);
	pd_release_clist(pd_myself(), clist, 0);

	memsection_delete(clist);
}
END_TEST

START_TEST(test_pd_add_release_clist)
{
	pd_ref_t newpd=0;
	uintptr_t clist, clist_base;
	newpd = pd_create();
	fail_if(newpd == 0, "NULL pd returned");
	clist = pd_create_memsection(newpd, MEM_SIZE, &clist_base);
	fail_if(clist == 0, "NULL memsection returned");
	pd_add_clist(newpd, clist);
	pd_release_clist(newpd, clist, 0);
	pd_delete(newpd);

}
END_TEST

START_TEST(test_memsect_create)
{
	uintptr_t base;
	memsection_ref_t ref;

	ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(ref == 0, "reference not zero");
}
END_TEST

START_TEST(test_memsect_delete)
{
	uintptr_t base;
	memsection_ref_t ref;

	ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(ref == 0, "reference not zero");

	memsection_delete(ref);
}
END_TEST

START_TEST(test_memsect_zeroing)
{
	uintptr_t base;
	memsection_ref_t ref;
	char *foo;
	ref = memsection_create(0x1000, &base);

	fail_if(base == 0, "base pointer not-null");
	fail_if(ref == 0, "reference not zero");

	if (base == 0 || ref == 0) {
		return;
	}
	
	foo = (char*) base;
	*foo = 'a';

	memsection_delete(ref);
	ref = memsection_create(0x1000, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(ref == 0, "reference not zero");
	foo = (char*) base;
	
	fail_if(*foo == 'a', "Memory not zeroed");
}
END_TEST

#ifdef CONFIG_RESTRICTED_VM
START_TEST(test_memsect_create_direct)
{
	uintptr_t base, base2;
	memsection_ref_t ref, ref2;
	memsection_ref_t *refs = NULL;
	int i = 0, cursize = 100;
	int max_memsections;
	int memsection_size = 250 * 0x1000;

	refs = malloc(sizeof(memsection_ref_t) * cursize);
	
	do {
		if (i >= cursize) {
			cursize += 100;
			refs = realloc(refs, sizeof(memsection_ref_t) * cursize);
			if (refs == NULL) {
				fail("Unable to allocate memory");
				break;
			}
		}
		refs[i] = memsection_create_direct(memsection_size, &base);
	} while (refs[i++] != 0);

	max_memsections = i - 1;

	for(i=0; i < max_memsections; i++) {
		memsection_delete(refs[i]);
	}

	free(refs);

	fail_unless(max_memsections > 0, "Unable to create and direct section");

	/* If we create/del we should easily be able to allocate 2 *
	   the max */
	for(i=0; i < max_memsections * 3; i++) {
		printf(".");
		ref = memsection_create(memsection_size, &base);
		fail_if(base == 0, "base pointer not-null");
		if (base == 0) {
			break;
		}
		fail_if(ref == 0, "reference not zero");
		ref2 = memsection_create_direct(memsection_size, &base2);
		fail_if(base2 == 0, "base pointer not-null");
		if (base2 == 0) {
			break;
		}
		fail_if(ref == 0, "reference not zero");
		memsection_delete(ref);
		memsection_delete(ref2);
	}
	printf("\n");
}
END_TEST
#endif

#if 0
START_TEST(test_memsect_create_fixed)
{
	uintptr_t base1, base2;
	memsection_ref_t ref1, ref2;
	ref1 = memsection_create_direct(MEM_SIZE, &base1);
	fail_if(base1 == 0, "base pointer not-null");
	fail_if(ref1 == 0, "reference not zero");
	base2 = base1 + PAGE_SIZE * (MEM_SIZE/MEM_SIZE + 1); 
	ref2 = memsection_create_fixed(MEM_SIZE, base2);
	fail_if(base2 == 0, "base pointer not-null");
	fail_if(ref2 == 0, "reference not zero");
	memsection_delete(ref1);
	memsection_delete(ref2);
}
END_TEST
#endif

START_TEST(test_memsection_register_server)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
 }
END_TEST

START_TEST(test_memsection_lookup)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0, mem_lookup;
	thread_ref_t iguana_thrd=0, sever_thrd=0;
	L4_ThreadId_t l4_thrd;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);
	mem_lookup = memsection_lookup(base + PAGE_SIZE/2, &sever_thrd);
	fail_if(mem_lookup != mem_ref, "not the right mem section");
	fail_if(sever_thrd != iguana_thrd, "not the right thread");
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
 }
END_TEST

START_TEST(test_memsection_base)
{
	uintptr_t base=0, mem_base;
	memsection_ref_t mem_ref=0;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	mem_base = (uintptr_t)memsection_base(mem_ref);
	fail_if(mem_base != base, "not the right mem section");
	memsection_delete(mem_ref);
}
END_TEST

START_TEST(test_memsection_set_attributes)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	memsection_set_attributes(mem_ref, 1);
	memsection_delete(mem_ref);
}
END_TEST

START_TEST(test_thread_create)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	iguana_thrd = thread_create(&l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST

START_TEST(test_thread_l4tid)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd, l4_tid;
	iguana_thrd = thread_create(&l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	l4_tid = thread_l4tid(iguana_thrd);
	fail_if(l4_tid.raw != l4_thrd.raw, "not right l4 thread ID");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST

START_TEST(test_thread_myself)
{
	thread_ref_t iguana_thrd=0, my_thrd;
	L4_ThreadId_t l4_thrd;
	iguana_thrd = thread_create(&l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	my_thrd = thread_myself();
	fail_if(my_thrd == iguana_thrd, "not right iguana thread ID");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST

START_TEST(test_thread_create_priority)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	iguana_thrd = thread_create_priority(100, &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	if (iguana_thrd != 0) {
		thread_delete(l4_thrd);
	}
}
END_TEST

START_TEST(test_thread_delete)
{
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	iguana_thrd = thread_create(&l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	thread_delete(l4_thrd);
}
END_TEST

START_TEST(test_thread_delete_self)
{
	/*no way to check it becuase idl4_set_no_response invoked
	in this case*/
}
END_TEST

START_TEST(test_thread_start)
{
	/*how to get the IP and SP?*/ 
	
}
END_TEST

START_TEST(test_thread_create_simple)
{
	/*need the description for this function*/
	
}
END_TEST

START_TEST(test_thread_create_many)
{
	thread_ref_t *threads = NULL;
	L4_ThreadId_t ignore;
	int max_threads;
	int i = 0, cursize = 100;

	printf("Thread create many\n");

	threads = malloc(sizeof(struct thread *) * cursize);

	do {
		printf(".");
		if (i >= cursize) {
			cursize += 100;
			threads = realloc(threads, sizeof(struct thread *) * cursize);
			if (threads == NULL) {
				fail("Unable to allocate memory");
				break;
			}
		}
		threads[i] = thread_create(&ignore);
	} while (threads[i++] != 0);

	max_threads = i - 1;

	printf("Created %d threads\n", max_threads);

	for(i=0; i < max_threads; i++) {
		iguana_thread_delete(L4_Pager(), threads[i], NULL);
	}

	free(threads);

	fail_unless(max_threads > 0, "Unable to any threads");

	for(i=0; i < max_threads * 3; i++) {
		thread_ref_t thrd;
		thrd = thread_create(&ignore);
		fail_if(thrd == 0, "Unable to create thread");
		if (thrd == 0) {
			break;
		}
		thread_delete(ignore);
	}
}
END_TEST

START_TEST(test_session_create_with_clist)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	struct session *sess;

	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");

	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);

	sess = session_create_with_clist(base, mem_ref, &l4_thrd);
	fail_if(sess == 0, "NULL session returned");

	session_delete(sess);
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
}
END_TEST

START_TEST(test_session_create)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	struct session *sess;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);
	sess = session_create(base, &l4_thrd);
	fail_if(sess == 0, "NULL session returned");
	session_delete(sess);
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
	
}
END_TEST

START_TEST(test_session_create_full_share)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	struct session *sess;
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);
	sess = session_create_full_share(base, &l4_thrd);
	fail_if(sess == 0, "NULL session returned");
	session_delete(sess);
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
}
END_TEST

#if 0
START_TEST(test_session_add_async)
{
	uintptr_t base=0;
	memsection_ref_t mem_ref=0, callback, retcb;
	objref_t callback_base, return_base;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	struct session *sess;
	pd_ref_t mypd = 0;
	mypd = pd_create();
	fail_if(mypd == 0, "NULL pd returned");
	callback = pd_create_memsection(mypd, MEM_SIZE, &callback_base);
  	pd_set_callback(mypd, callback);
	retcb = pd_create_memsection(mypd, MEM_SIZE, &return_base);
	mem_ref = memsection_create(MEM_SIZE, &base);
	fail_if(base == 0, "base pointer not-null");
	fail_if(mem_ref == 0, "reference not zero");
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	fail_if(iguana_thrd == 0, "NULL thread returned");
	memsection_register_server(mem_ref, iguana_thrd);
	sess = session_create_full_share(base, &l4_thrd);
	fail_if(sess == 0, "NULL session returned");
	session_add_async(sess, callback_base, return_base);
	session_delete(sess);
	memsection_delete(mem_ref);
	thread_delete(l4_thrd);
	pd_delete(mypd);
	
}
END_TEST
#endif

START_TEST(test_session_provide_access)
{
	static char *mystring = "be in touch!";
	uintptr_t ignore;
	struct session *sess;
	pd_ref_t subpd1 = 0;
	uintptr_t str1_addr;
	memsection_ref_t mem_ref1;
	thread_ref_t thrd1=0;
	L4_ThreadId_t l4_thrd1;
	subpd1 = pd_create();
	fail_if(subpd1 == 0, "NULL pd returned");
	mem_ref1 = pd_create_memsection(subpd1, MEM_SIZE, &str1_addr);
	thrd1 = pd_create_thread(subpd1, &l4_thrd1);
	fail_if(thrd1 == 0, "NULL thread returned");
	memsection_register_server(mem_ref1, thrd1);
	sess = session_create_full_share((objref_t)str1_addr, &l4_thrd1);
	fail_if(sess == 0, "NULL session returned");
	if (sess == NULL) {
		return;
	}
	session_provide_access(sess,  memsection_lookup((uintptr_t) mystring, &ignore), MASTER_IID);
	session_delete(sess);
	memsection_delete(mem_ref1);
	thread_delete(l4_thrd1);
	pd_delete(subpd1);
}
END_TEST

START_TEST(test_eas_create)
{
	eas_ref_t eas;
	L4_Fpage_t utcb_area, kip_area;
	L4_KernelInterfacePage_t *kip;

	kip = L4_GetKernelInterface();
	kip_area = L4_FpageLog2((uintptr_t) kip, L4_KipAreaSizeLog2(kip));
	utcb_area = L4_FpageLog2(0x0, 16); 
	eas = eas_create(kip_area, utcb_area);
	fail_if(eas == 0, "NULL eas returned");
}
END_TEST

START_TEST(test_eas_delete)
{
	eas_ref_t eas;
	L4_Fpage_t utcb_area, kip_area;
	L4_KernelInterfacePage_t *kip;

	kip = L4_GetKernelInterface();
	kip_area = L4_FpageLog2((uintptr_t) kip, L4_KipAreaSizeLog2(kip));
	utcb_area = L4_FpageLog2(0x0, 16); 
	eas = eas_create(kip_area, utcb_area);
	fail_if(eas == 0, "NULL eas returned");
	eas_delete(eas);
}
END_TEST

START_TEST(test_eas_thread_create)
{
	eas_ref_t eas;
	L4_ThreadId_t tid;
	L4_Fpage_t utcb_area, kip_area;
	L4_KernelInterfacePage_t *kip;

	kip = L4_GetKernelInterface();
	kip_area = L4_FpageLog2((uintptr_t) kip, L4_KipAreaSizeLog2(kip));
	utcb_area = L4_FpageLog2(0x0, 16); /* 16 bits worth of threads! Lots ! */
	eas = eas_create(kip_area, utcb_area);
	fail_if(eas == 0, "NULL eas returned");
	tid = eas_create_thread(eas, L4_Myself(), L4_Myself(), 0);
	fail_if(tid.raw == 0, "NULL eas thread created");
	eas_delete(eas);
}
END_TEST

START_TEST(test_eas_thread_create_many)
{
	eas_ref_t eas;
	L4_Fpage_t utcb_area, kip_area;
	L4_KernelInterfacePage_t *kip;
	thread_ref_t *threads = NULL;
	L4_ThreadId_t ignore;
	L4_ThreadId_t myself = L4_Myself();
	int max_threads;
	int i = 0, cursize = 100;

	kip = L4_GetKernelInterface();
	kip_area = L4_FpageLog2((uintptr_t) kip, L4_KipAreaSizeLog2(kip));
	utcb_area = L4_FpageLog2(0x0, 16); /* 16 bits worth of threads! Lots ! */
	eas = eas_create(kip_area, utcb_area);

	printf("Thread create many\n");

	threads = malloc(sizeof(struct thread *) * cursize);

	do {
		printf(".");
		if (i >= cursize) {
			cursize += 100;
			threads = realloc(threads, sizeof(struct thread *) * cursize);
			if (threads == NULL) {
				fail("Unable to allocate memory");
				break;
			}
		}
		threads[i] = iguana_eas_create_thread(L4_Pager(), eas, &myself, &myself,
						      (uintptr_t) 0, &ignore, NULL).ref.thread;
	} while (threads[i++] != 0);

	max_threads = i - 1;

	printf("Created %d threads\n", max_threads);

	for(i=0; i < max_threads; i++) {
		iguana_thread_delete(L4_Pager(), threads[i], NULL);
	}

	free(threads);

	fail_unless(max_threads > 0, "Unable to any threads");

	for(i=0; i < max_threads * 3; i++) {
		thread_ref_t thrd;
		thrd = thread_create(&ignore);
		fail_if(thrd == 0, "Unable to create thread");
		if (thrd == 0) {
			break;
		}
		thread_delete(ignore);
	}

	eas_delete(eas);
}
END_TEST


START_TEST(test_iguana_cap_get_and_free_slot)
{
	struct cap_slot slot;
	slot = iguana_cap_get_slot();
	fail_if (slot.list == NULL, "NULL slot returned");
	iguana_cap_free_slot(slot);
}	
END_TEST

START_TEST(test_iguana_get_cap)
{
	memsection_ref_t mem_ref;
	uintptr_t base;
	cap_t mem_cap;
	mem_ref = pd_create_memsection(pd_myself(), MEM_SIZE, &base);
	fail_if(mem_ref == 0, "NULL memory returned");
	mem_cap = iguana_get_cap(mem_ref, MASTER_IID);
	fail_if(mem_cap.ref.memsection == 0, "NULL cap retunred");
}
END_TEST

START_TEST(test_iguana_cap_set)
{
	memsection_ref_t mem_ref;
	uintptr_t base;
	cap_t mem_cap;
	struct cap_slot slot;
	mem_ref = pd_create_memsection(pd_myself(), MEM_SIZE, &base);
	fail_if(mem_ref == 0, "NULL memory returned");
	mem_cap = iguana_get_cap(mem_ref, MASTER_IID);
	fail_if(mem_cap.ref.memsection == 0, "NULL cap retunred");
	slot = iguana_cap_get_slot();
	fail_if (slot.list == NULL, "NULL slot returned");
	iguana_cap_set(mem_cap, slot);
	iguana_cap_free_slot(slot);
}
END_TEST

/*FIXME, should this def go to a head file?*/
struct clist {
	int slot;
	size_t size;
	size_t cap_free;
	memsection_ref_t clist_memsect;
	cap_t *cap_list;
};
START_TEST(test_lookup_clist)
{
	struct cap_slot slot;
	memsection_ref_t mem_ref;
	uintptr_t base;
	mem_ref = memsection_create(MEM_SIZE, &base);
	slot = lookup_clist(mem_ref);
	fail_if (slot.list == NULL, "NULL slot returned");
	fail_if(mem_ref != (slot.list->cap_list[slot.pos]).ref.memsection, 
		"wrong mem section");
	iguana_cap_free_slot(slot);
}
END_TEST

START_TEST(test_object_get_interface)
{
	memsection_ref_t mem_ref;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	uintptr_t base;
	object_t *obj_interface;
	mem_ref = memsection_create(MEM_SIZE, &base);
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	memsection_register_server(mem_ref, iguana_thrd);
	obj_interface = object_get_interface(base);
	thread_delete(l4_thrd);
	fail_if(obj_interface == 0, "NULL obj interface returned");
}
END_TEST

START_TEST(test_memsection_page_map)
{
	memsection_ref_t ms1, ms2;
	uintptr_t base1, base2;
	char *p, *q;
	L4_Fpage_t fpage1, fpage2;

	ms1 = memsection_create(MEM_SIZE, &base1);
	p = (void *)base1;
	fpage1 = L4_Fpage(base1, PAGE_SIZE);

	ms2 = memsection_create_user(MEM_SIZE, &base2);
	q = (void *)base2;
	fpage2 = L4_Fpage(base2, PAGE_SIZE);

	memsection_page_map(ms2, fpage1, fpage2);

	strcpy(p,"abcdefg123456");
	fail_if(strcmp(p, q) != 0, "page not mapped correctly");

	memsection_delete(ms1);
	memsection_delete(ms2);
}
END_TEST

#if 0
START_TEST(test_object_get_async_interface)
{
	memsection_ref_t mem_ref;
	thread_ref_t iguana_thrd=0;
	L4_ThreadId_t l4_thrd;
	uintptr_t base;
	object_t *obj_interface;
	mem_ref = memsection_create(MEM_SIZE, &base);
	iguana_thrd = pd_create_thread(pd_myself(), &l4_thrd);
	memsection_register_server(mem_ref, iguana_thrd);
	obj_interface = object_get_async_interface(base);
	fail_if(obj_interface == 0, "NULL obj interface returned");
	object_print(obj_interface);
}
END_TEST
#endif
//extern size_t __malloc_instrumented_allocated;

#ifdef CONFIG_LOWMEMORY
START_TEST(test_session_create_many)
{
	struct session **sessions = NULL;
	L4_ThreadId_t ignore;
	int max_sessions;
	int i = 0, cursize = 100;
	memsection_ref_t    local_control_mem_section;
	uintptr_t           mem_section_ptr;

	local_control_mem_section = memsection_create(4096, &mem_section_ptr);
	memsection_register_server(local_control_mem_section, thread_myself());

	sessions = malloc(sizeof(struct session *) * cursize);

	do {
		printf(".");
		if (i >= cursize) {
			cursize += 100;
			sessions = realloc(sessions, sizeof(struct session *) * cursize);
			if (sessions == NULL) {
				fail("Unable to allocate memory");
				break;
			}
		}
		sessions[i] = session_create((objref_t)mem_section_ptr, &ignore);
	} while (sessions[i++] != 0);

	max_sessions = i - 1;
	printf("Created %d sessions\n", max_sessions);

	for(i=0; i < max_sessions; i++) {
		session_delete(sessions[i]);
	}

	free(sessions);

	fail_unless(max_sessions > 0, "Unable to create and direct section");

	for(i=0; i < max_sessions * 3; i++) {
		struct session      *sess;
		printf(",");
		//printf("session_create: %d\n", __malloc_instrumented_allocated);
		sess = session_create((objref_t)mem_section_ptr, &ignore);
		//printf("done session create: %d\n", __malloc_instrumented_allocated);
		//printf("Doing failif: %d\n", __malloc_instrumented_allocated);
		fail_if(sess == NULL, "Unable to create session");
		//printf("Done  failif: %d\n", __malloc_instrumented_allocated);
		if (sess == NULL) {
			printf("Couldn't create session\n");
			break;
		}
		//printf("doing session delete: %d\n", __malloc_instrumented_allocated);
		session_delete(sess);
		//printf("done session delete: %d\n", __malloc_instrumented_allocated);
	}
	memsection_delete(local_control_mem_section);
	printf("finished\n");
}
END_TEST
#endif

#ifdef CONFIG_LOWMEMORY
extern uintptr_t __malloc_bss;
extern uintptr_t __malloc_top;
#endif

Suite *
make_test_libs_iguana_suite(void)
{
	Suite *suite;
	TCase *tc;

	/* During our tests we really want to make sure that the testing program doesn't
	   run out of memory, so we touch a lot of pages on our heap now to make sure we
	   have enough memory */
#ifdef CONFIG_LOWMEMORY
	{
		/* Here we are evil and reduce our heap, but make it all
		   mapped, so we won't accidently fault */
#define PAGESIZE 0x1000
#define NUM_PAGES 5
		__malloc_top = __malloc_bss + NUM_PAGES * PAGESIZE;
		for(uintptr_t m = __malloc_bss; m < __malloc_top; m += PAGESIZE) {
			*((char*)m) = 'a';
		}
	}
#endif

	suite = suite_create("Iguana tests");

	tc = tcase_create("Memory Sections");
	tcase_add_test(tc, test_memsect_create);
	tcase_add_test(tc, test_memsect_delete);
	tcase_add_test(tc, test_memsect_zeroing);
#ifdef CONFIG_RESTRICTED_VM
	tcase_add_test(tc, test_memsect_create_direct);
#endif
	//	tcase_add_test(tc, test_memsect_create_fixed);
	tcase_add_test(tc, test_memsection_register_server);
	tcase_add_test(tc, test_memsection_lookup);
	tcase_add_test(tc, test_memsection_base);
	tcase_add_test(tc, test_memsection_set_attributes);
	tcase_add_test(tc, test_memsection_page_map);
	suite_add_tcase(suite, tc);

	
	tc = tcase_create("OBJ Sections");
	tcase_add_test(tc, test_object_get_interface);
	//tcase_add_test(tc, test_object_get_async_interface);
	suite_add_tcase(suite, tc);
	
	tc = tcase_create("CAP Sections");
	tcase_add_test(tc, test_iguana_cap_get_and_free_slot);
	tcase_add_test(tc, test_iguana_get_cap);
	tcase_add_test(tc, test_iguana_cap_set);
	tcase_add_test(tc, test_lookup_clist);
	suite_add_tcase(suite, tc);
	
	tc = tcase_create("EAS Sections");
	tcase_add_test(tc, test_eas_create);
	tcase_add_test(tc, test_eas_delete);
	tcase_add_test(tc, test_eas_thread_create);
	tcase_add_test(tc, test_eas_thread_create_many);
	suite_add_tcase(suite, tc);
	
	tc = tcase_create("Session Sections");
	tcase_add_test(tc, test_session_create_with_clist);
	tcase_add_test(tc, test_session_create);
	tcase_add_test(tc, test_session_create_full_share);
#ifdef CONFIG_LOWMEMORY
	tcase_add_test(tc, test_session_create_many);
#endif
	//tcase_add_test(tc, test_session_add_async);

	tcase_add_test(tc, test_session_provide_access);
	suite_add_tcase(suite, tc);

	tc = tcase_create("PD tests");
	tcase_add_test(tc, test_pd_myself);
	tcase_add_test(tc, test_pd_create);
#ifdef CONFIG_LOWMEMORY
	tcase_add_test(tc, test_pd_create_many);
#endif
	tcase_add_test(tc, test_pd_create_pd);
	tcase_add_test(tc, test_pd_myself_create_thread);
	tcase_add_test(tc, test_pd_myself_create_thread_with_priority);
	//tcase_add_test(tc, test_pd_create_thread);
	//tcase_add_test(tc, test_pd_create_thread_with_priority);
	tcase_add_test(tc, test_pd_myself_create_memsection);
	tcase_add_test(tc, test_pd_myself_set_callback);
	tcase_add_test(tc, test_pd_create_memsection);
	tcase_add_test(tc, test_pd_set_callback);
	tcase_add_test(tc, test_pd_myself_add_release_clist);
	tcase_add_test(tc, test_pd_add_release_clist);
	suite_add_tcase(suite, tc);

	tc = tcase_create("Thread tests");
	tcase_add_test(tc, test_thread_create);
	tcase_add_test(tc, test_thread_l4tid);
	tcase_add_test(tc, test_thread_myself);
	tcase_add_test(tc, test_thread_create_priority);
	tcase_add_test(tc, test_thread_delete);
	tcase_add_test(tc, test_thread_delete_self);
	tcase_add_test(tc, test_thread_start);
	tcase_add_test(tc, test_thread_create_simple);
	tcase_add_test(tc, test_thread_create_many);
	suite_add_tcase(suite, tc);

	return suite;
}


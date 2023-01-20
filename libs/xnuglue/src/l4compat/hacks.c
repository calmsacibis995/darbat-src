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
 * hacks.c
 *
 */

#include <kern/kalloc.h>
#include <kern/locks.h>
#include <kern/thread.h>
#include <mach/kern_return.h>
#include <xnucompat.h>

#include <iguana/memsection.h>
#include <timer/timer.h>
#include <xnu_k_r_malloc.h>

#include <stdio.h>

#include <l4/kdebug.h>
#include <l4/ipc.h>	/* XXX correctly pull in Sleep? */

#include <lkm/lkm.h>

// #include <fb.h>		/* XXX */

#include <pexpert/i386/boot.h>	/* XXX */

#include <l4/kip.h>
#include <l4/bootinfo.h>

/*
 * MacOSX does not use this.
 * 
 * Well, actually, that is a lie.  It appears that with Xcode 2.3
 * this symbol is defined.  If you are using an older version of XCode
 * then you must uncomment the below line, or if you are using an ELF
 * compiler you will need that too.  The following define is therefore
 * bogus.
 */
#ifdef __ELF__
void *__dso_handle;
#endif

/*
 * MacOSX does not use this.
 *
 */
void __cxa_atexit(void);
void __cxa_atexit(void) {}

/*
 * These are probably auto generated.
 *
 */
char version[] = "0.0.1";
char osrelease[] = "0.0.1";
vm_size_t page_size = 0x1000;	/* XXX */
int page_shift = 12;	/* XXX */

/*
 * This is mbuf stuff.
 *
 */
int nmbclusters;
void *mb_map;	/* should be vm_map */

/*
 * Timer tick.
 *
 * Of course, this is TOTALLY bogus, and needs fixing.
 * XXX FIXME XXX
 */
int hz = 100;

/*
 * XXX
 *
 * kernel_flock
 * In our version, it is really a mutex, we do some evil casting to
 * sneak past the compiler.
 * 
 */
funnel_t	*kernel_flock;

/*
 * XXX these should be in a header, somewhere?
 *
 */
extern kern_return_t	IOKitBSDInit(void);
extern void		mbinit(void);

lck_spin_t		*xnulck;

/*
 * XXX
 *
 * We don't static-ize this so that when we disable it for whatever reason
 * it does not complain.
 */
void lkm_test(void);

/*
 * XXX REMOVE ME XXX
 */
#include <mach-o/mach-o.h>

#define LKMTEST	1

#if !LKMTEST
void
lkm_test(void)
{
	printf("%s: dummy function, skipping\n", __func__);
}
#else	/*LKMTEST*/
void
lkm_test(void)
{
	/*
	 * All of the test code is gone now (since we know it works).
	 * It is still in the revision control.
	 */
	lkm_macho_init();
}
#endif	/*LKMTEST*/

void
xnuinit(void)
{
	memsection_ref_t	ref;
	uintptr_t		xnu_malloc_base;

	printf("%s: initializing.\n", __func__);

	timer_init();	/* XXX get rid of me */

	lkm_test();

	/*
	 * XXX REMOVE ME XXX
	 */
	// fb_init(1);
	// fb_puts("ERTOS NICTA Techfest Demo");
	// fb_puts("L4/Darwin - Darbat Loading...." );

	/*
	 * Initialize the stack pool.  This is static, and if you run out
	 * you will crash and burn.
	 */
	spool_init();
	/*
	 * Initialize the xnu memory allocator.  This has 1-1 virt / phys
	 * correspondence, good for drivers.
	 *
	 * XXX this is a hack.  We really need the translation.
	 */
	ref = memsection_create_direct(8 * 1024 * 1024, &xnu_malloc_base);
	assert(xnu_malloc_base);
	__xnu_malloc_init((void *)xnu_malloc_base, 
	     (void *)(xnu_malloc_base + 8*1024*1024));

	/*
	 * Initialize the xnu global lock.
	 *
	 * Note that passing in NULL for the attrs probably isn't
	 * very nice.
	 */
	xnulck = lck_spin_alloc_init(NULL, NULL);
	kernel_flock = (funnel_t *)lck_mtx_alloc_init(NULL, NULL);

	assert(xnulck);
	assert(kernel_flock);

	reaperinit();
	thread_call_init();
	l4intrinit();
}

void
bsdinit(void)
{
	kern_return_t	rc;

	rc = IOKitBSDInit();
	printf("IOKitBSDInit: rc is %d\n", rc);

	mbinit();
}

/*
 * HACKS
 *
 */

void thread_deallocate(void);
void
thread_deallocate(void)
{

	printf("%s: dodging for now.\n", __func__);
}

/*
 * This must return 0 in the glue, as the return value is checked!
 *
 */
int PE_parse_boot_arg(void);

int
PE_parse_boot_arg(void)
{

	return (0);
}

/*
 * XXX
 *
 */
//L4_Word_t current_thread(void);
L4_Word_t
current_thread(void)
{

	return L4_Myself().raw;
}

/*
 * We dodge this for now.
 *
 * This is called from IOTimerEventSource::timeoutAndRelease.
 */
void kernel_debug(void);
void
kernel_debug(void)
{

}

/*
 * This is not actually used by IOKit per se, but it requires it to
 * return something non-null as IOMediaBSDClient tests for that.
 */
void *devfs_make_node(void);
void *
devfs_make_node(void)
{

	return (void *)0xdecafbad;
}

/*
 * This needs to return a memory_object_t which should not be NULL.
 *
 */
void *device_pager_setup(void);
void *device_pager_setup(void)
{
	return (void *)0xabcdef;
}

/*
 * This is here because it clutters the screen.
 *
 * This has been hacked around in IOMediaBSDClient, umm, perhaps
 * that is not so good.
 *
 * Will shall see, we may need to revisist this.
 */
void ttwrite(void);

void
ttwrite(void)
{

	return;
}

/*
 * XXX
 *
 * We only need this because it falls off the end of the function.
 *
 * Sigh ..
 */
void __xnu_stub_terminate(void);
void
__xnu_stub_terminate(void)
{

	thread_terminate((thread_t)L4_Myself().raw);
	/* NOTREACHED */
}

/*
 * This is only here because it clutters the screen too much.
 *
 */
int uio_isuserspace(void);
int
uio_isuserspace(void)
{

	return (0);
}

/*
 * sysctlbyname() implementation.  This is by no means complete.
 * The problem is that the ATI driver makes use of this (to get the
 * cacheline size, and to get the memory size, apparently.
 *
 * Of course, we currently have no way of telling either, so we just hardcode
 * this to be what's on the production hardware for now.  On the Core Solos
 * and the Core Duos, the cacheline size is 64, while for memsize, it is
 * 512M (subject to whether it is build to order, of course).
 *
 * The arguments for calling the in-kernel (so to speak..) sysctlbyname()
 * is exactly the same for the sysctlbyname(3) library call in userland.
 *
 * -gl.
 */
int sysctlbyname( const char *name, void *oldp, size_t *oldlenp, void *newp, 
	size_t newlen);
int
sysctlbyname(
	const char *name, 
	void *oldp, 
	size_t 
	*oldlenp, 
	void *newp, 
	size_t newlen)
{
	struct fakesysctl {
		char	*name;
		int	siz;
		int	data;	/* XXX: data is var sized */
	};
	int	i;

	struct fakesysctl s[] = {
		{ "hw.memsize", 8, 32 },
		{ "hw.cachelinesize", 4, 64 }
	};

	printf("%s: warning: is fake\n", __func__);

	/*
	 * XXX: for now, the sysctls that we handle are r/o.  Make it so.
	 */
	if (newp) {
		printf("%s: ERROR newp is not null\n", __func__);
		panic("diediedie");
	}

	for (i = 0; i < sizeof(s) / sizeof(struct fakesysctl); i++) {
		if (strcmp(s[i].name, name) == 0) {
			switch (s[i].siz) {
				/* OK, this is stupid. */
				case 1:
					*(uint8_t *)oldp = 
					     (uint8_t)s[i].data;
					break;
				case 2:
					*(uint16_t *)oldp = 
					     (uint16_t)s[i].data;
					break;
				case 4:
					*(uint32_t *)oldp = 
					     (uint32_t)s[i].data;
					break;
				case 8:
					*(uint64_t *)oldp = 
					    (uint64_t)s[i].data;
					break;
				default:
					printf("%s: warning: "
					    "unsupported size %d\n", 
					    __func__,
					    s[i].siz);
			}
			if (oldlenp)
				*oldlenp = s[i].siz;
			goto done;
		}
	}

	printf("%s: warning: could not find appropriate sysctl for %s\n", 
	    __func__,
	    name);
done:
	return (0);
}
  
/*
 * This is required to initialize the initial list of drivers.  Under
 * Iguana this would mean that we parse the bootinfo to see what's there
 * and stuff the binaries in.  Needless to say, this needs revision.
 *
 * There are several invariants that we need to follow here.  First, 
 * we always prefix the name of the driver with DarwinDriver.  If it is not
 * there then it is not a driver and we skip over it.
 * Second the driver plist always follows.
 */
void l4_init_bootargs( KernelBootArgs_t *args);

#define DARWINDRIVER	"DarwinDriver"
#define PLIST		".plist"

/*
 * clagged from libsa/catalog.cpp
 * -gl
 */
typedef struct MemoryMapFileInfo {
    uint32_t paddr;
    uint32_t length;
} MemoryMapFileInfo;

typedef struct BootxDriverInfo {
    char *plistAddr;
    long  plistLength;
    void *moduleAddr;
    long  moduleLength;
} BootxDriverInfo;

/*
 * XXX: we need to free the memory that we have malloc()'ed here.
 * XXX: -gl
 */
void
l4_init_bootargs( KernelBootArgs_t *args)
{
	L4_KernelInterfacePage_t	*kip;
	L4_BootRec_t			*tmprec, *rec;
	void				*bootinfo;
	int				i;
	int				ndrivers;
	BootxDriverInfo			*driverinfo;

	printf("%s: guessing what drivers to include into list\n", __func__);

	kip = L4_GetKernelInterface();
	bootinfo = (void *)L4_BootInfo(kip);
	rec = L4_BootInfo_FirstEntry(bootinfo);

	for (ndrivers = i = 0; i < L4_BootInfo_Entries(bootinfo); i++) {
		if (L4_BootRec_Type(rec) == L4_BootInfo_Module &&
		    strncmp(L4_Module_Cmdline(rec), DARWINDRIVER,
		    strlen(DARWINDRIVER)) == 0) {
			/*
			 * OK, we found what we want.  Fill in the values
			 * We expect the bootinfo to be laid out in the
			 * order plist, driver, plist, driver, etc.
			 */
			driverinfo = kalloc(sizeof(BootxDriverInfo));
			if (!driverinfo)
				assert(!"shit");
			memset(driverinfo, 0, sizeof(BootxDriverInfo));
			driverinfo->plistAddr = (char *)L4_Module_Start(rec);
			driverinfo->plistLength = L4_Module_Size(rec);

			/*
			 * What follows next must be the driver, manually
			 * do the increment.  We could guess wrong, and 
			 * could be another plist instead.  This would
			 * happen with extensions that have no code.  Peek
			 * and see what it is, if it is plist, (based on 
			 * the file extension).
			 *
			 * So, 4 cases:
			 *
			 * (0) We are the last entry.  In this case
			 * nothing can come after us, so we must be
			 * a plist.
			 *
			 * (1) not Darwin related.  This does not have
			 * DarwinDriver signature prepended.
			 *
			 * (2) Has DarwinDriver but is plist.  So we must
			 * have no code for the current extension.
		 	 *
			 * (3) Assume it is code.
			 */
			tmprec = L4_BootRec_Next(rec);
			if (((i + 1) == L4_BootInfo_Entries(bootinfo)) ||
			    (L4_BootRec_Type(tmprec) == L4_BootInfo_Module &&
			    ((strncmp(L4_Module_Cmdline(tmprec), DARWINDRIVER,
			    strlen(DARWINDRIVER)) == 0 &&
			    strncmp(L4_Module_Cmdline(tmprec) + 
			    strlen(L4_Module_Cmdline(tmprec)) - strlen(PLIST),
			    PLIST, strlen(PLIST)) == 0) ||
			    strncmp(L4_Module_Cmdline(tmprec), DARWINDRIVER,
			    strlen(DARWINDRIVER)) != 0))) {
				/* OK, seems to be another plist. */
				printf("%s: registering plist only %s\n",
				    __func__, 
				    L4_Module_Cmdline(rec));
			} else {
				rec = L4_BootRec_Next(rec);
				i++;
				driverinfo->moduleAddr = 
				    (void *)L4_Module_Start(rec);
				driverinfo->moduleLength = L4_Module_Size(rec);

				printf("%s: registering plist and code %s\n",
				    __func__,
				    L4_Module_Cmdline(rec) + 
				    strlen(DARWINDRIVER));
			}

			args->numBootDrivers++;
			args->driverConfig[ndrivers].type = 
			    kBootDriverTypeKEXT;
			args->driverConfig[ndrivers].address = 
			    (unsigned long)driverinfo;
			args->driverConfig[ndrivers].size = 
			    sizeof(*driverinfo);
			ndrivers++;
		}

		rec = L4_BootRec_Next(rec);
	}

	printf("%s: found %d drivers\n", __func__, ndrivers);
}

/*
 * XXX: hack.
 */
extern void *kernel_task;	/* l4compat/stubs.c */
task_t 
current_task(void)
{
	return (task_t)kernel_task;
}
/*
 * Hacks for indirect symbols.  Yuck ... please please can we have the rld.c
 * from cctools.
 * -gl
 */
#define IOLock	void
#define IORWLock void
#define IOSimpleLock void
void    IOLockLock( IOLock * lock)
{
    lck_mtx_lock(lock);
}
boolean_t IOLockTryLock( IOLock * lock)
{
    return(lck_mtx_try_lock(lock));
}

void    IOLockUnlock( IOLock * lock)
{
    lck_mtx_unlock(lock);
}
void IOSimpleLockUnlock( IOSimpleLock * lock){    lck_spin_unlock( lock ); }
void IOSimpleLockLock( IOSimpleLock *lock) { lck_spin_lock( lock ); }
boolean_t IOSimpleLockTryLock( IOSimpleLock * lock )
{    return( lck_spin_try_lock( lock ) );}

void    IORWLockRead( IORWLock * lock)
{    //lck_rw_lock_shared( lock);
	printf("shit: %s called\n", __func__);
}
void    IORWLockUnlock( IORWLock * lock)
{
    //lck_rw_done( lock);
	printf("shit: %s called\n", __func__);
}
void    IORWLockWrite( IORWLock * lock)
{
    //lck_rw_lock_exclusive( lock);
	printf("shit: %s called\n", __func__);
}


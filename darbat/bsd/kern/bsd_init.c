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
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1982, 1986, 1989, 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)init_main.c	8.16 (Berkeley) 5/14/95
 */

/* 
 *
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#include <sys/param.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/mount_internal.h>
#include <sys/proc_internal.h>
#include <sys/kauth.h>
#include <sys/systm.h>
#include <sys/vnode_internal.h>
#include <sys/conf.h>
#include <sys/buf_internal.h>
#include <sys/clist.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/systm.h>
#include <sys/mman.h>

#include <bsm/audit_kernel.h>

#include <sys/malloc.h>
#include <sys/dkstat.h>

#include <kern/startup.h>
#include <kern/thread.h>
#include <kern/task.h>
#include <kern/ast.h>

#include <mach/vm_param.h>
#include <mach/task.h>
#include <mach/thread_act.h>

#include <vm/vm_map.h>
#include <vm/vm_kern.h>

#include <sys/ux_exception.h>	/* for ux_exception_port */

#include <sys/reboot.h>
#include <mach/exception_types.h>
#include <dev/busvar.h>			/* for pseudo_inits */
#include <sys/kdebug.h>

#include <mach/mach_types.h>
#include <mach/vm_prot.h>
#include <mach/semaphore.h>
#include <mach/sync_policy.h>
#include <kern/clock.h>
#include <mach/kern_return.h>

#include <mach/shared_memory_server.h>
#include <vm/vm_shared_memory_server.h>

#include <net/init.h>

#if DARBAT
extern void l4consinit(void);
void vcattach(void);
extern void cnputcusr(char c);
void refresh_screen(void);
#endif

// We import this from osfmk (will need to do this properly later...) ceg
#include <kern/thread.h>
// #include <vm/vm_kern.h>
#include <igcompat/compat.h>
#include <pexpert/pexpert.h>  /* PE_parse_boot_args */
#include <DEBUG.h>

extern int app_profile;		/* on/off switch for pre-heat cache */

char    copyright[] =
"Copyright (c) 1982, 1986, 1989, 1991, 1993\n\t"
"The Regents of the University of California. "
"All rights reserved.\n\n";

// Is this used?
// extern void	ux_handler();

/* Components of the first process -- never freed. */
struct	proc proc0;
struct	session session0;
struct	pgrp pgrp0;
struct	filedesc filedesc0;
struct	plimit limit0;
struct	pstats pstats0;
struct	sigacts sigacts0;
struct	proc *kernproc, *initproc;

long tk_cancc;
long tk_nin;
long tk_nout;
long tk_rawcc;

int lock_trace = 0;
/* Global variables to make pstat happy. We do swapping differently */
int nswdev, nswap;
int nswapmap;
void *swapmap;
struct swdevt swdevt[1];

dev_t	rootdev;		/* device of the root */
dev_t	dumpdev;		/* device to take dumps on */
long	dumplo;			/* offset into dumpdev */
long	hostid;
char	hostname[MAXHOSTNAMELEN];
int		hostnamelen;
char	domainname[MAXDOMNAMELEN];
int		domainnamelen;
char	classichandler[32] = {0};  
uint32_t	classichandler_fsid = -1L;
long	classichandler_fileid = -1L;

char rootdevice[16]; 	/* hfs device names have at least 9 chars */

#ifdef  KMEMSTATS
struct	kmemstats kmemstats[M_LAST];
#endif

int	lbolt;				/* awoken once a second */
struct	vnode *rootvp;
int boothowto = RB_DEBUG;

#define	BSD_PAGABLE_MAP_SIZE	(16 * 512 * 1024)
vm_map_t	bsd_pageable_map;
vm_map_t	mb_map;
semaphore_t execve_semaphore;

int	cmask = CMASK;

int parse_bsd_args(void);
extern int bsd_hardclockinit;
extern task_t bsd_init_task;
extern char    init_task_failure_data[];
extern void time_zone_slock_init(void);
static void process_name(char *, struct proc *);

static void setconf(void);

funnel_t *kernel_flock;

/* FIXME: find a better place for these defns. */
kern_return_t IOFindBSDRoot( char *, dev_t *, u_int32_t * );
void IOKitResetTime(void);


/*
 * Initialization code.
 * Called from cold start routine as
 * soon as a stack and segmentation
 * have been established.
 * Functions:
 *	turn on clock
 *	hand craft 0th process
 *	call all initialization routines
 *  hand craft 1st user process
 */

/*
 *	Sets the name for the given task.
 */
static void
process_name(s, p)
	char		*s;
	struct proc *p;
{
	int		length = strlen(s);

	bcopy(s, p->p_comm,
		length >= sizeof(p->p_comm) ? sizeof(p->p_comm) :
			length + 1);
}

/* To allow these values to be patched, they're globals here */
#include <machine/vmparam.h>
struct rlimit vm_initial_limit_stack = { DFLSSIZ, MAXSSIZ };
struct rlimit vm_initial_limit_data = { DFLDSIZ, MAXDSIZ };
struct rlimit vm_initial_limit_core = { DFLCSIZ, MAXCSIZ };

extern thread_t	cloneproc(struct proc *, int);
extern int 	(*mountroot)(void);
#if NFSCLIENT
extern int 	netboot_mountroot(void); 	/* netboot.c */
#endif
extern int	netboot_setup(struct proc * p);

lck_grp_t * proc_lck_grp;
lck_grp_attr_t * proc_lck_grp_attr;
lck_attr_t * proc_lck_attr;

/* hook called after root is mounted XXX temporary hack */
void (*mountroot_post_hook)(void);

/* all these pesky init functions */
#include <sys/init.h>

/* blah */
static void lightning_bolt(void*);
static void bsd_autoconf(void);

/* this is *really* seedy */
extern void thread_wakeup( event_t x);

/*
 * This function is called very early on in the Mach startup, from the
 * function start_kernel_threads() in osfmk/kern/startup.c.  It's called
 * in the context of the current (startup) task using a call to the
 * function kernel_thread_create() to jump into start_kernel_threads().
 * Internally, kernel_thread_create() calls thread_create_internal(),
 * which calls uthread_alloc().  The function of uthread_alloc() is
 * normally to allocate a uthread structure, and fill out the uu_sigmask,
 * uu_act, and uu_ucred fields.  It skips filling these out in the case
 * of the "task" being "kernel_task", because the order of operation is
 * inverted.  To account for that, we need to manually fill in at least
 * the uu_cred field so that the uthread structure can be used like any
 * other.
 */
void bsd_init(void); /* erk */

extern void loopattach(void);	/* -gl erk */
void
bsd_init(void)
{
	register struct proc *p;
	struct uthread *ut;
	// nested
	// extern kauth_cred_t rootcred;
	register int i;
	struct vfs_context context;
	kern_return_t	ret;
	boolean_t funnel_state;
	struct ucred temp_cred;

	kernel_flock = funnel_alloc(KERNEL_FUNNEL);
	if (kernel_flock == (funnel_t *)0 ) {
		panic("bsd_init: Failed to allocate kernel funnel");
	}
        
	funnel_state = thread_funnel_set(kernel_flock, TRUE);

	printf(copyright);

	printf( ">>> doing a kmeminit\n" );
	kmeminit();
	
	printf( ">>> parsing args\n" );
	parse_bsd_args();

	/* Initialize the uthread zone */
	//uthread_zone_init();	/* XXX redundant: previous uthread_alloc() */

	/* Initialize kauth subsystem before instancing the first credential */
	printf( ">>> kauthinit\n" );
	kauth_init();

	/* Initialize process and pgrp structures. */
	printf( ">>> procinit\n" );
	procinit();

	printf( ">>> procinit done\n" );

	kernproc = &proc0;

	p = kernproc;

	printf( ">>> set info\n" );

	/* kernel_task->proc = kernproc; */
	set_bsdtask_info(kernel_task,(void *)p);
	p->p_pid = 0;

	printf( ">>> process_name\n" );

	/* give kernproc a name */
	process_name("kernel_task", p);

	printf( ">>> proc lock\n" );

	/* allocate proc lock group attribute and group */
	proc_lck_grp_attr= lck_grp_attr_alloc_init();
	lck_grp_attr_setstat(proc_lck_grp_attr);

	proc_lck_grp = lck_grp_alloc_init("proc",  proc_lck_grp_attr);


	/* Allocate proc lock attribute */
	proc_lck_attr = lck_attr_alloc_init();
	//lck_attr_setdebug(proc_lck_attr);

	lck_mtx_init(&p->p_mlock, proc_lck_grp, proc_lck_attr);
	lck_mtx_init(&p->p_fdmlock, proc_lck_grp, proc_lck_attr);

	if (current_task() != kernel_task)
		printf("bsd_init: We have a problem, "
				"current task is not kernel task\n");
	
	ut = (uthread_t)get_bsdthread_info(current_thread());

	printf( ">>> create 0\n" );

	/*
	 * Create process 0.
	 */
	LIST_INSERT_HEAD(&allproc, p, p_list);
	p->p_pgrp = &pgrp0;
	LIST_INSERT_HEAD(PGRPHASH(0), &pgrp0, pg_hash);
	LIST_INIT(&pgrp0.pg_members);
	LIST_INSERT_HEAD(&pgrp0.pg_members, p, p_pglist);

	pgrp0.pg_session = &session0;
	session0.s_count = 1;
	session0.s_leader = p;

	p->task = kernel_task;
	
	p->p_stat = SRUN;
	p->p_flag = P_SYSTEM;
	p->p_nice = NZERO;
	p->p_pptr = p;

	printf( ">>> lockinit\n" );

	/* signal_lock is *seedy* */
	lockinit((void*)&p->signal_lock, PVM, "signal", 0, 0);

	TAILQ_INIT(&p->p_uthlist);
	p->sigwait = FALSE;
	p->sigwait_thread = THREAD_NULL;
	p->exit_thread = THREAD_NULL;

	/*
	 * Create credential.  This also Initializes the audit information.
	 * XXX It is not clear what the initial values should be for audit ID,
	 * XXX session ID, etc..
	 */
	bzero(&temp_cred, sizeof(temp_cred));
	temp_cred.cr_ngroups = 1;

	p->p_ucred = kauth_cred_create(&temp_cred); 

	printf( ">>> blah\n" );

	/* give the (already exisiting) initial thread a reference on it */
	kauth_cred_ref(p->p_ucred);
	ut->uu_ucred = p->p_ucred;
	
	TAILQ_INIT(&p->aio_activeq);
	TAILQ_INIT(&p->aio_doneq);
	p->aio_active_count = 0;
	p->aio_done_count = 0;

	printf( ">>> file_lock_init\n" );

	file_lock_init();

	/* Create the file descriptor table. */
	filedesc0.fd_refcnt = 1+1;	/* +1 so shutdown will not _FREE_ZONE */
	p->p_fd = &filedesc0;
	filedesc0.fd_cmask = cmask;
	filedesc0.fd_knlistsize = -1;
	filedesc0.fd_knlist = NULL;
	filedesc0.fd_knhash = NULL;
	filedesc0.fd_knhashmask = 0;

	/* Create the limits structures. */
	p->p_limit = &limit0;
	for (i = 0; i < sizeof(p->p_rlimit)/sizeof(p->p_rlimit[0]); i++)
		limit0.pl_rlimit[i].rlim_cur = 
			limit0.pl_rlimit[i].rlim_max = RLIM_INFINITY;
	limit0.pl_rlimit[RLIMIT_NOFILE].rlim_cur = NOFILE;
	limit0.pl_rlimit[RLIMIT_NPROC].rlim_cur = MAXUPRC;
	limit0.pl_rlimit[RLIMIT_NPROC].rlim_max = maxproc;
	limit0.pl_rlimit[RLIMIT_STACK] = vm_initial_limit_stack;
	limit0.pl_rlimit[RLIMIT_DATA] = vm_initial_limit_data;
	limit0.pl_rlimit[RLIMIT_CORE] = vm_initial_limit_core;
	limit0.p_refcnt = 1;

	p->p_stats = &pstats0;
	p->p_sigacts = &sigacts0;

	/*
	 * Charge root for two  processes: init and mach_init.
	 */
	(void)chgproccnt(0, 1);

	/*
	 *	Allocate a kernel submap for pageable memory
	 *	for temporary copying (execve()).
	 */

	printf( ">>> pageable map init\n" );
	{
		vm_offset_t	min;

		ret = kmem_suballoc(kernel_map,
				&min,
				(vm_size_t)BSD_PAGABLE_MAP_SIZE,
				TRUE,
				VM_FLAGS_ANYWHERE,
				&bsd_pageable_map);
		if (ret != KERN_SUCCESS) 
			panic("bsd_init: Failed to allocate bsd pageable map");
	}

	/*
	 * Initialize buffers and hash links for buffers
	 *
	 * SIDE EFFECT: Starts a thread for bcleanbuf_thread(), so must
	 *		happen after a credential has been associated with
	 *		the kernel task.
	 */
	printf( ">>> bsd_bufferinit\n" );
	bsd_bufferinit();

	/* Initialize the execve() semaphore */
	printf( ">>> execve semaphore_create\n" );
	ret = semaphore_create(kernel_task, &execve_semaphore,
			SYNC_POLICY_FIFO, (BSD_PAGABLE_MAP_SIZE / NCARGS));
	if (ret != KERN_SUCCESS)
		panic("bsd_init: Failed to create execve semaphore");

	/*
	 * Initialize the calendar.
	 */
	printf( ">>> Init calendar\n" );
	IOKitResetTime();

	ubc_init();

	/* Initialize the file systems. */
	printf( ">>> vfsinit\n" );
	vfsinit();

	/* Initialize mbuf's. */
	printf( ">>> mbinit\n" );
	mbinit();

	/*
	 * Initializes security event auditing.
	 * XXX: Should/could this occur later?
	 */
	printf( ">>> audit_init\n" );
	audit_init();  

	/* Initialize kqueues */
	printf( ">>> knote_init\n" );
	knote_init();

	/* Initialize for async IO */
	printf( ">>> aio_init\n" );
	aio_init();

	/* Initialize pipes */
	printf( ">>> pipe_init\n" );
	pipeinit();

	/* Initialize SysV shm subsystem locks; the subsystem proper is
	 * initialized through a sysctl.
	 */
	printf( ">>> sysv, posix, shm, sem, msg\n" );
	sysv_shm_lock_init();
	sysv_sem_lock_init();
	sysv_msg_lock_init();
	pshm_lock_init();
	psem_lock_init();

	/* POSIX Shm and Sem */
	pshm_cache_init();
	psem_cache_init();
	time_zone_slock_init();

	/*
	 * Initialize protocols.  Block reception of incoming packets
	 * until everything is ready.
	 */
	printf( ">>> sysctl_register_fixed\n" );
	sysctl_register_fixed();
	printf( ">>> sysctl_mib_init\n" );
	sysctl_mib_init();
	printf( ">>> dlil_init\n" );
	dlil_init();
	printf( ">>> proto_kpi_init\n" );
	proto_kpi_init();
	printf( ">>> socketinit\n" );
	socketinit();
	printf( ">>> domaininit\n" );
	domaininit();

	printf( ">>> done protocols\n" );

	p->p_fd->fd_cdir = NULL;
	p->p_fd->fd_rdir = NULL;

#ifdef GPROF
	/* Initialize kernel profiling. */
	kmstartup();
#endif

	/* kick off timeout driven events by calling first time */
	printf( ">>> lightning bolt\n" );
	thread_wakeup(&lbolt);
	timeout((void (*)(void *))lightning_bolt, 0, hz);

	/* FIXME: check this? */
	printf( ">>> bsd_autoconf\n" );
	bsd_autoconf();


	/*
	 * We attach the loopback interface *way* down here to ensure
	 * it happens after autoconf(), otherwise it becomes the
	 * "primary" interface.
	 */
#if 0	/* see extern on top */
#include <loop.h>
#endif
#if NLOOP > 0
	loopattach();			/* XXX */
#endif
   
        /* Register the built-in dlil ethernet interface family */
	printf( ">>> ether_family_init\n" );
	ether_family_init();

	/* Call any kext code that wants to run just after network init */
	printf( ">>> net_init_run\n" );
	net_init_run();

	printf( ">>> skipping vnode_pager_bootstrap\n" );
	vnode_pager_bootstrap();

#if 0
	/* XXX Hack for early debug stop */
	printf("\nabout to sleep for 10 seconds\n");
	IOSleep( 10 * 1000 );
	/* Debugger("hello"); */
#endif

	printf( ">>> inittodr\n" );
	inittodr(0);

#if DARBAT
	/*
	 * XXX
	 * 
	 */

	// Use the mach code instead
	// l4consinit();

	/**** XXXXX ****/
	printf( "doing vc attach...\n" );
	vcattach();
	printf( "clearing screen\n" );
	refresh_screen();
#endif

	/* Mount the root file system. */
	printf( ">>> mounting root...\n" );
	while( TRUE) {
		int err;

		setconf();
		bsd_hardclockinit = -1;	/* start ticking */

		printf( ">>> vfs_mountroot\n" );
		if (0 == (err = vfs_mountroot()))
			break;
#if NFSCLIENT
		if (mountroot == netboot_mountroot) {
			printf("cannot mount network root, errno = %d\n", err);
			mountroot = NULL;
			if (0 == (err = vfs_mountroot()))
				break;
		}
#endif
		printf("cannot mount root, errno = %d\n", err);
		boothowto |= RB_ASKNAME;

		panic("I die now");
	}

	context.vc_proc = p;
	context.vc_ucred = p->p_ucred;
	mountlist.tqh_first->mnt_flag |= MNT_ROOTFS;

	/* Get the vnode for '/'.  Set fdp->fd_fd.fd_cdir to reference it. */
	printf( ">>> finding '/'\n" );
	if (VFS_ROOT(mountlist.tqh_first, &rootvnode, &context))
		panic("bsd_init: cannot find root vnode");
	rootvnode->v_flag |= VROOT;
	(void)vnode_ref(rootvnode);
	(void)vnode_put(rootvnode);
	filedesc0.fd_cdir = rootvnode;

#if NFSCLIENT
	if (mountroot == netboot_mountroot) {
		int err;
		/* post mount setup */
		if ((err = netboot_setup(p))) {
			panic("bsd_init: NetBoot could not find root, %d", err);
		}
	}
#endif
	

	microtime(&p->p_stats->p_start);
	p->p_rtime.tv_sec = p->p_rtime.tv_usec = 0;

#if DEVFS
	{
	    devfs_kernel_mount("/dev");
	}
#endif /* DEVFS */
	
	/* Initialize signal state for process 0. */
	printf( ">>> siginit\n" );
	siginit(p);

	printf( ">>> bsd_utaskbootstrap\n" );
	bsd_utaskbootstrap();

	/* invoke post-root-mount hook */
	printf( ">>> mountroot_post_hook\n" );
	if (mountroot_post_hook != NULL)
		mountroot_post_hook();
	
	printf( ">>> release funnel\n" );
	(void) thread_funnel_set(kernel_flock, funnel_state);

	printf( ">>> bsd_init out!\n" );
}

/* Called with kernel funnel held */
void
bsdinit_task(void)
{
	struct proc *p = current_proc();
	struct uthread *ut;
	thread_t th_act;
	shared_region_mapping_t system_region;

	printf( "XXXXXXXXXX: in bsdinit_task\n" );

	process_name("init", p);
	
	DBG();

	// Ignore user exception handlers...
	// ux_handler_init();

	th_act = current_thread();

	DBG();

/* pfft... ports */
#if 0
	(void) host_set_exception_ports(host_priv_self(),
					EXC_MASK_ALL & ~(EXC_MASK_SYSCALL |
							 EXC_MASK_MACH_SYSCALL |
							 EXC_MASK_RPC_ALERT),
					ux_exception_port,
					EXCEPTION_DEFAULT, 0);

	(void) task_set_exception_ports(get_threadtask(th_act),
					EXC_MASK_ALL & ~(EXC_MASK_SYSCALL |
							 EXC_MASK_MACH_SYSCALL |
							 EXC_MASK_RPC_ALERT),
					ux_exception_port,
				EXCEPTION_DEFAULT, 0);
#endif



	/* this code seem inconsequential...? */
	(void) ut;
	// ut = (uthread_t)get_bsdthread_info(th_act);
	// ut->uu_ar0 = (void *)get_user_regs(th_act);

	DBG();

	bsd_hardclockinit = 1;	/* Start bsd hardclock */
	bsd_init_task = get_threadtask(th_act);
	init_task_failure_data[0] = 0;

	DBG();

#if 0// DARBAT
	/* this other stuff seems unuseful right now */
	(void) system_region;
#else
	system_region = lookup_default_shared_region(ENV_DEFAULT_ROOT, cpu_type());
        if (system_region == NULL) {
		shared_file_boot_time_init(ENV_DEFAULT_ROOT, cpu_type());
	} else {
		vm_set_shared_region(get_threadtask(th_act), system_region);
	}
#endif

	load_init_program(p);

	/* turn on app-profiling i.e. pre-heating */
	app_profile = 1;
	lock_trace = 1;

	DBG();
}

static void
lightning_bolt(void* dummy)
{			
	boolean_t 	funnel_state;

	funnel_state = thread_funnel_set(kernel_flock, TRUE);

	thread_wakeup(&lbolt);
	timeout(lightning_bolt,0,hz);
	klogwakeup();

	(void) thread_funnel_set(kernel_flock, FALSE);
}

extern void mdevinit( int );

static void
bsd_autoconf(void)
{
	// extern kern_return_t IOKitBSDInit( void );

	kminit();

	/* XXX: temp hack startup by ceg */
	mdevinit(0);

	/* 
	 * Early startup for bsd pseudodevices.
	 */
/* FIXME: where does pseudo_inits come from? */
#if 0
	{
	    struct pseudo_init *pi;
	
	    for (pi = pseudo_inits; pi->ps_func; pi++)
		(*pi->ps_func) (pi->ps_count);
	}
#endif
	// return( IOKitBSDInit());
}


#include <sys/disklabel.h>  /* for MAXPARTITIONS */

#define DARBAT_DISK 1
#define DARBAT_NETWORK 1  /* relies on darbat disk */

#if DARBAT_DISK	/* glee */
extern void disk_init(void);

/* disk relies on network for startup */
#if DARBAT_NETWORK
extern void net_init(void);
#endif
#else
#if DARBAT_NETWORK
#error DARBAT_NETWORK relies on DARBAT_DISK startup
#endif
#endif


static void
setconf(void)
{	
	u_int32_t	flags;
	kern_return_t	err;

	/*
	 * calls into IOKit can generate networking registrations
	 * which needs to be under network funnel. Right thing to do
	 * here is to drop the funnel alltogether and regrab it afterwards
	 */
	thread_funnel_set(kernel_flock, FALSE);
	err = IOFindBSDRoot( rootdevice, &rootdev, &flags );
	thread_funnel_set(kernel_flock, TRUE);
	if( err) {
		printf("setconf: IOFindBSDRoot returned an error (%d);"
			"setting rootdevice to 'sd0a'.\n", err); /* XXX DEBUG TEMP */
		rootdev = makedev( 6, 0 );
		strcpy( rootdevice, "sd0a" );
		flags = 0;
	}

#if NFSCLIENT
	if( flags & 1 ) {
		/* network device */
		mountroot = netboot_mountroot;
	} else {
#endif
		/* otherwise have vfs determine root filesystem */
		mountroot = NULL;
#if NFSCLIENT
	}
#endif

#if DARBAT_DISK	/* glee: XXX I don't know where to put this. */
	disk_init();
#endif

#if DARBAT_NETWORK
	net_init();
#endif

}

void
bsd_utaskbootstrap(void)
{
	thread_t th_act;
	struct uthread *ut;

	printf( "bsd_utaskbootstrap: 1\n" );

	th_act = cloneproc(kernproc, 0);
	printf( "bsd_utaskbootstrap: 2\n" );
	initproc = pfind(1);			
	printf( "bsd_utaskbootstrap: 3\n" );	
	/* Set the launch time for init */
	microtime(&initproc->p_stats->p_start);

	printf( "bsd_utaskbootstrap: 4\n" );
	ut = (struct uthread *)get_bsdthread_info(th_act);
	printf( "bsd_utaskbootstrap: 5 (ut = %p)\n", ut );
	ut->uu_sigmask = 0;
	
	printf( "bsd_init: doing act_set_astbsd!\n" );
	act_set_astbsd(th_act);

	printf( "bsd_utaskbootstrap: 6\n" );
	(void) thread_resume(th_act);
	printf( "bsd_utaskbootstrap: 7\n" );
}

extern char init_args[];
extern int srv;
extern int ncl;

int
parse_bsd_args(void)
{
	char	namep[16];

	int len;

#if 0	/* XXX glee: disabled conditionally doing it for now */
	if (PE_parse_boot_arg("-s", namep)) {
#endif
		boothowto |= RB_SINGLE;
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -s");
		else
			strcat(init_args,"-s");
#if 0	/* XXX glee */
	}
#endif

	if (PE_parse_boot_arg("-b", namep)) {
		boothowto |= RB_NOBOOTRC;
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -b");
		else
			strcat(init_args,"-b");
	}

	if (PE_parse_boot_arg("-F", namep)) {
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -F");
		else
			strcat(init_args,"-F");
	}

	if (PE_parse_boot_arg("-v", namep)) {
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -v");
		else
			strcat(init_args,"-v");
	}

	if (PE_parse_boot_arg("-x", namep)) { /* safe boot */
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -x");
		else
			strcat(init_args,"-x");
	}

	if (PE_parse_boot_arg("-d", namep)) {
		len = strlen(init_args);
		if(len != 0)
			strcat(init_args," -d");
		else
			strcat(init_args,"-d");
	}

	PE_parse_boot_arg("srv", &srv);
	PE_parse_boot_arg("ncl", &ncl);
	PE_parse_boot_arg("nbuf", &nbuf);

	return 0;
}

#if !NFSCLIENT
int netboot_root(void);

int 
netboot_root(void)
{
	return(0);
}
#endif

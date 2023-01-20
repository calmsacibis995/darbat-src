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
// #include <stdio.h>

#include <vm/vm_map.h>
#include <vm/vm_fault.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/debug.h>

#include <l4/types.h>
#include <l4/ipc.h>
#include <l4/thread.h>
#include <l4/kdebug.h>
#include <l4/kip.h>

/*******************************/

/* for system calls - do we need all this? */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/file_internal.h>
#include <sys/stat.h>
#include <sys/vnode_internal.h>
#include <sys/mount_internal.h>
#include <sys/proc_internal.h>
#include <sys/kauth.h>
#include <sys/uio_internal.h>
#include <sys/malloc.h>
#include <sys/mman.h>
#include <sys/dirent.h>
#include <sys/attr.h>
#include <sys/sysctl.h>
#include <sys/ubc.h>
#include <sys/quota.h>
#include <sys/kdebug.h>
#include <sys/fsevents.h>
#include <sys/sysproto.h>
#include <sys/xattr.h>
#include <sys/ubc_internal.h>
#include <machine/cons.h>
#include <machine/limits.h>
#include <miscfs/specfs/specdev.h>

#include <igcompat/compat.h>

#include <sys/sysent.h> // For BSD trap table
#include <kern/syscall_sw.h> // For Mach trap table

/*******************************/

/* shared with user-land */
#include <syscallnums.h>

#include <i386/cpu_capabilities.h>
#include <sys/sysproto.h>
#include <mach/vm_prot.h>
#include <vm/pmap.h>

#include <igcompat/timer.h>

#include "clockthread.h"  /* timer tick */
#include "igcompat/darbat.h"

#include <DEBUG.h>

#define TECHFEST_FRAMEBUFFER_HACK 0
#define PRINT_PAGEFAULTS 0
#define PRINT_BSD 0
#define PRINT_MACH 0

#define USE_FUNNEL 0
// Global vars for asm bullshit
L4_Word_t ASM_MR0;
L4_Word_t ASM_MR1;
L4_Word_t ASM_MR2;
L4_Word_t ASM_TO;
L4_Word_t ASM_FROM;

void *ASM_jump_addr;

#define TGB_ASM 0
#define TGB_TIMING 0

/* XXXX: framebuffer hack!! */
void *db_fb_base = NULL;

#define USER_FB_BASE 0x40000000
#define FB_SIZE (64<<20)  /* 64mb buffer */

// XXX TGB COMMPAGE HACK
extern void *commPagePtr;

#define get_syscall_proc() current_proc()

/* XXX */
#define PAGEBITS 12
#define L4_PAGEFAULT (0xffe0)
#define L4_EXCEPTION (0xffb0)

L4_ThreadId_t darbat_get_l4_tid(thread_t);

/* XXXXXX - is this even right? CEG */
extern void machine_set_current_thread( thread_t );
void darbat_clean_eas(thread_t thread);


thread_t set_thread( L4_ThreadId_t tid );
thread_t
set_thread( L4_ThreadId_t tid )
{
 	thread_t thread;
 	
 	thread = current_thread();
  
 	assert( darbat_get_l4_tid(thread).raw == tid.raw );
  
 	return thread;
}

void send_signal_message( unsigned long tid, void *func, int signum );
void
send_signal_message( unsigned long tid, void *func, int signum )
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

    L4_MsgClear(&msg);
    L4_Set_MsgLabel(&msg, 0x541);
    L4_MsgAppendWord(&msg, 2);
    L4_MsgAppendWord(&msg, (L4_Word_t) func);
    L4_MsgAppendWord(&msg, signum);
    L4_MsgLoad(&msg);

	tag = L4_Send( (L4_ThreadId_t) { tid } );

	if( L4_IpcFailed( tag ) )
		panic( "send_signal_message failed!\n" );
}

ppnum_t resolve_pagefault(vm_offset_t va, int read, int write, int exec);
ppnum_t 
resolve_pagefault(vm_offset_t va, int read, int write, int exec)
{
    vm_map_t map = current_map();
    pmap_t pmap = vm_map_get_pmap(map);
    va = trunc_page(va);

    vm_prot_t prot = 0;
    if(read)
        prot |= VM_PROT_READ;
    if(write)
        prot |= VM_PROT_WRITE;
    if(exec)
        prot |= VM_PROT_EXECUTE;

    ppnum_t retval = pmap_fault(pmap, va, prot);

    if(retval)
    {
        return retval;
    }

    kern_return_t rc = vm_fault( map, va, prot, FALSE, 
            (pmap == kernel_pmap) ? 
            THREAD_UNINT : THREAD_ABORTSAFE, 
            NULL, 0 );

    if(rc != KERN_SUCCESS)
    {
        printf( "vm_fault rc: %d\n", rc );

        if(vm_fault( map, va, 0, FALSE, 
                    (pmap == kernel_pmap) ? 
                    THREAD_UNINT : THREAD_ABORTSAFE, 
                    NULL, 0 ) == KERN_SUCCESS)
        {
		printf("FAULT: va %p there but bad protection\n", (void*) va);
        }
        else
        {
            printf("bugger\n");
        }
        return 0;
    }

    retval = pmap_fault(pmap, va, prot);

    return retval;
}


/* the pager */
static int
pager(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg)
{
    L4_Word_t addr = L4_MsgWord( msg, 0 );
    L4_MapItem_t map_item;
    ppnum_t pn;
    vm_offset_t va;

    /* Get the faulting address */

#define MVS(A) *((void **)&(A))

    //thread_t old_thread;
    //old_thread = set_thread( tid );

#define TGB_MASK_PROT(A,B) ((A & (1 << B)) != 0)
    L4_Word_t prots = tag.raw;//L4_MsgWord(msg, -1);

    int prot_read = TGB_MASK_PROT(prots, 18);
    int prot_write = TGB_MASK_PROT(prots, 17);
    int prot_exec = TGB_MASK_PROT(prots, 16);

    /* check the pagetable */
    va = trunc_page(addr);

#if PRINT_PAGEFAULTS
    L4_Word_t eip = L4_MsgWord(msg, 1);
    printf("ta: %p th: %p PAGEFAULT eip: %p addr: %p\n",
            current_task(), current_thread(), MVS(eip), MVS(addr));
#endif

    // printf( "doing pmap lookup on %p\n", (void*) (unsigned int) va );

    if(va >= (vm_offset_t)_COMM_PAGE_BASE_ADDRESS && va < (vm_offset_t)0xb0000000)
    {
        // COMM_PAGE fault
        // TODO make sure that this is registered in each address space so that
        // vm_allocate won't stomp over it
        pn = (ppnum_t)commPagePtr + (va - ((vm_offset_t)_COMM_PAGE_BASE_ADDRESS));

        pn >>= 12;

    }
#if TECHFEST_FRAMEBUFFER_HACK
    else if( va >= (vm_offset_t)USER_FB_BASE 
	     && va < (vm_offset_t)(USER_FB_BASE+FB_SIZE))
    {
	    // printf( "XXXXXXXXXXXX: fault in Framebuffer: 0x%x\n", (unsigned) va );

	    /* XXX: tom made me do it! */
	    pn = (ppnum_t)db_fb_base + (va-((vm_offset_t)USER_FB_BASE));

	    {
		    /* XXX: touch it */
		    volatile int *pnn = (volatile int *)pn;
		    volatile int t;
		    t = *pnn;
		    *pnn = t;
	    }

	    pn >>= 12;
    }
#endif
    else
    {
        pn = resolve_pagefault(va, prot_read, prot_write, prot_exec);
    }

    if( !pn )
	    printf( "fault: 0x%x\n", (unsigned) va );

    assert(pn);

    L4_Word_t protection = 0;
    if(prot_read)
        protection |= L4_Readable;
    if(prot_write)
        protection |= L4_Writable;
    if(prot_exec)
        protection |= L4_eXecutable; 

    /* Construct fpage IPC message */
    
    map_item = L4_MapItem ( (L4_Fpage_t)
            (L4_FpageLog2( pn << 12, PAGEBITS ).raw +
             protection),
            addr);
    L4_MsgPut (msg, 0, 0, (L4_Word_t *) 0, 2, &map_item);
    L4_MsgLoad (msg);

    return 0;
}

void __pthread_cset(struct sysent *);
void __pthread_creset(struct sysent *);
int * get_bsduthreadrval(thread_t);
void * get_bsduthreadarg(thread_t);

void *thread_get_funnel_lock(void);

void darbat_set_syscall_no(thread_t, int);
int darbat_get_syscall_no(thread_t);
task_t darbat_task_for_pid(int pid);
void darbat_fork_child_start(task_t task, user_addr_t eip);
void darbat_thread_reset(thread_t thread);

void force_ast(void);

extern const char *syscallnames[];



/* call a mach syscall */
static int
do_mach_syscall( int syscall_no, user_addr_t uesp )
{
	L4_Word_t args[10];
	int nargs, retval;

        if(syscall_no >= mach_trap_count)
        {
            assert(!"got a bad syscall number for a mach trap\n");
        }

        nargs = mach_trap_table[syscall_no].mach_trap_arg_count;

#if PRINT_MACH
        task_t task = current_task();
	thread_t thread = current_thread();
        printf("ta: %p th: %p MACH %d", task, thread, syscall_no);
#endif

#if TGB_TIMING
	if(syscall_no == 31)
	{
		tgb_time_now();
	}
#endif
        if(nargs == 0)
        {
            retval = mach_trap_table[syscall_no].mach_trap_function();
        }
        else
        {
            retval = copyin(uesp, args, nargs*sizeof(int));
            assert(!retval);
            // TODO fix this to return an error

            int (*function)(L4_Word_t *) = (int (*)(L4_Word_t *))
                (mach_trap_table[syscall_no].mach_trap_function);

            retval = function(args);
        }
#if TGB_TIMING
	if(syscall_no == 31)
	{
		tgb_time_now();
	}
#endif

#if PRINT_MACH
        printf(" retval: %d\n", retval);
#endif

	return retval;
}

int
handle_fork_ipc(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg);
int handle_fork_ipc(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg)
{
    thread_t thread = current_thread();
    int *vt = (int *)get_bsduthreadarg(thread);

    struct sysent *callp;
    int error = 0;
    int *retvals = get_bsduthreadrval(thread);
#if USE_FUNNEL
    int funnel_type = NO_FUNNEL;
#endif 
    
    user_addr_t fork_child_resume = L4_MsgWord(msg, 0);

    darbat_set_syscall_no(thread, 2 /* SYS_fork */);

    callp = &sysent[2];

#if PRINT_BSD
    task_t task = current_task();
    printf( "ta: %p th: %p BSD %d: '%s'", 
            task, thread, 2, syscallnames[2] );
#endif

#if 0 // don't really want to deal with signals yet
    if ((error = __pthread_cset(callp))) {
        /* cancelled system call; let it returned with EINTR for handling */
        L4_MsgClear(msg);
        L4_MsgAppendWord(msg, error);
        L4_MsgLoad(msg);
        return 1;
    }
#endif

#if USE_FUNNEL
    funnel_type = (callp->sy_funnel & FUNNEL_MASK);
    if(funnel_type == KERNEL_FUNNEL)
    {
        (void) thread_funnel_set(kernel_flock, TRUE);
    }
#endif

    // Don't really feel like doing ktrace either :D
    // ktrsyscall(current_proc(), code, callp->sy_narg, vt, funnel_type);

    retvals[0] = 0;
    retvals[1] = 0;

    current_proc();

    error = (*(callp->sy_call))((void *) current_proc(), (void *) vt, (int *)retvals);

#if PRINT_BSD
    printf(" retval e: %d 0:%d 1:%d\n", error, (int)retvals[0], (int)retvals[1]);
#endif
        if(error == ERESTART)
        {
            panic("shouldn't get ERESTART in fork\n");
        }

        // Not handling signals yet (uncomment this is you do pthread_cset)
        //__pthread_creset(callp);
#if USE_FUNNEL
        if(funnel_type != NO_FUNNEL)
        {
            thread_funnel_set(thread_get_funnel_lock(), FALSE);
        }
#endif 

    L4_MsgClear(msg);
    L4_Set_MsgLabel(msg, 0x542);

    if(error)
    {
        L4_MsgAppendWord(msg, 1);
        L4_MsgAppendWord(msg, error);
    }
    else
    {
        // No error, yay!
        L4_MsgAppendWord(msg, 0);
        L4_MsgAppendWord(msg, retvals[0]);
        darbat_fork_child_start(darbat_task_for_pid(retvals[0]), fork_child_resume);
    }
            
    L4_MsgLoad(msg);

    return 1;
}

int
handle_mach_trap(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg);
int handle_mach_trap(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg)
{
	L4_Word_t args[10];
    int syscall_no = (int)L4_MsgWord(msg, 0);
    int nargs = L4_MsgWord(msg, 1);
    int retval;

    syscall_no *= -1;

    if(syscall_no >= mach_trap_count)
    {
        assert(!"got a bad syscall number for a mach trap\n");
    }

    if(mach_trap_table[syscall_no].mach_trap_arg_count > nargs)
    {
        printf("mach trap nargs mismatch %d, was %d, should be %d\n", 
                syscall_no, mach_trap_table[syscall_no].mach_trap_arg_count, nargs);
        L4_KDB_Enter("syscall nargs bad!");
    }


#if PRINT_MACH
        task_t task = current_task();
	thread_t thread = current_thread();
        printf("ta: %p th: %p MACH %d", task, thread, syscall_no);
#endif

    if(nargs == 0)
    {
        retval = mach_trap_table[syscall_no].mach_trap_function();
    }
    else
    {
        int i;
        for(i=0;i<nargs;i++)
        {
            args[i] = L4_MsgWord(msg, i+2);
        }
        //bcopy(&(msg->msg[3]), args, nargs*sizeof(int));

        int (*function)(L4_Word_t *) = (int (*)(L4_Word_t *))
            (mach_trap_table[syscall_no].mach_trap_function);

        retval = function(args);
    }

#if PRINT_MACH
        printf(" retval: %d\n", retval);
#endif

    L4_MsgClear(msg);
    L4_Set_MsgLabel(msg, 0x543);
    L4_MsgAppendWord(msg, retval);
    L4_MsgLoad(msg);
    return 1;
}

int
handle_bsd_trap(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg);
int handle_bsd_trap(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg)
{
    thread_t thread = current_thread();
    int syscall_no = (int)L4_MsgWord(msg, 0);
    int nargs = L4_MsgWord(msg, 1);
    assert(syscall_no >= 0 && syscall_no < nsysent);

#if 1
    /* Debugging test to make sure we're sending the right number of args */
    if(sysent[syscall_no].sy_narg > nargs)
    {
        printf("syscall nargs mismatch %d, was %d, should be %d\n", 
                syscall_no, sysent[syscall_no].sy_narg, nargs);
        L4_KDB_Enter("syscall nargs bad!");
    }
#endif

    int *vt = (int *)get_bsduthreadarg(thread);

    int i;
    for(i=0;i<nargs;i++)
    {
        vt[i] = L4_MsgWord(msg, i+2);
    }
    //bcopy(&(msg->msg[3]), vt, nargs*sizeof(int));

    int error = 0;
    struct sysent *callp;
    int *retvals = get_bsduthreadrval(thread);
#if USE_FUNNEL
    int funnel_type = NO_FUNNEL;
#endif 

    darbat_set_syscall_no(thread, syscall_no);

    callp = (syscall_no >= nsysent) ? &sysent[63] : &sysent[syscall_no];

#if PRINT_BSD
    task_t task = current_task();
    printf( "ta: %p th: %p BSD %d: '%s'", 
    task, thread, syscall_no, syscallnames[syscall_no] );
#endif

    // Debug before the call is made
    switch(syscall_no)
    {
        default:
            break;
    }

#if 0 // don't really want to deal with signals yet
        if ((error = __pthread_cset(callp))) {
            /* cancelled system call; let it returned with EINTR for handling */
            L4_MsgClear(msg);
            L4_MsgAppendWord(msg, error);
            L4_MsgLoad(msg);
            return 1;
        }
#endif

#if USE_FUNNEL
        funnel_type = (callp->sy_funnel & FUNNEL_MASK);
        if(funnel_type == KERNEL_FUNNEL)
        {
            (void) thread_funnel_set(kernel_flock, TRUE);
        }
#endif

        // Don't really feel like doing ktrace either :D
        // ktrsyscall(current_proc(), code, callp->sy_narg, vt, funnel_type);

        retvals[0] = 0;
        retvals[1] = 0;

        current_proc();

            error = (*(callp->sy_call))((void *) current_proc(), (void *) vt, (int *)retvals);

#if PRINT_BSD
        printf(" retval e: %d 0:%d 1:%d\n", error, (int)retvals[0], (int)retvals[1]);
#endif
        
        // Necessary for execve 
        if(syscall_no == 59 && error == 0)
        {
            darbat_clean_eas(current_thread());
            darbat_thread_reset(current_thread());
            return 0;
        }

        if(error == ERESTART)
        {
            force_ast();
        }

        // Not handling signals yet (uncomment this is you do pthread_cset)
        //__pthread_creset(callp);
#if USE_FUNNEL
        if(funnel_type != NO_FUNNEL)
        {
            thread_funnel_set(thread_get_funnel_lock(), FALSE);
        }
#endif 

	/*
	 * There are a couple of calls that we do not want to return
	 * if there is no error.  These are the exec() family of syscalls,
	 * exit(), as well as sigreturn().
	 *
	 * XXX: Should probably watch out for kill on ourself too.	
	 */
	if (error == 0) {

		switch (syscall_no) {
			case 59:	/* Execve */
			case 184:	/* Sigreturn, ppc */
			case 103:	/* ditto, non-ppc */
			case 1:		/* Exit() */
				return 0;
			default:
				break;
		}
	}

    L4_MsgClear(msg);
    L4_Set_MsgLabel(msg, 541);

    if(!error)
    {
        L4_MsgAppendWord(msg, 0);
        L4_MsgAppendWord(msg, retvals[0]);
        L4_MsgAppendWord(msg, retvals[1]);
    }
    else
    {
        if(error == EJUSTRETURN)
        {
            L4_MsgAppendWord(msg, 0);
            L4_MsgAppendWord(msg, 0);
            L4_MsgAppendWord(msg, 0);
        }
        else if(error == ERESTART)
        {
            L4_MsgAppendWord(msg, 2);
            L4_MsgAppendWord(msg, 0);
            L4_MsgAppendWord(msg, 0);
        }
        else
        {
            L4_MsgAppendWord(msg, 1);
            L4_MsgAppendWord(msg, error);
        }
    }

    if(syscall_no == 2)
    {
        L4_KDB_Enter("fork coming through cool_ipc");
    }
#if 0
    // DEBUG
    if(syscall_no == 202 && error != 0)
    {
        printf("You've just had a sysctl fail, you REALLY want to fix this\n"
                "Please add the appropirate entry in 'bsd/kern/sysctl_init.c'\n"
                "You may find 'bsd/sys/sysctl.h' useful in conjunction with the\n"
                "numbers above to figure out which entry you want to add\n");

        L4_KDB_Enter("Here, have a manual backtrace!");
    }
    else if(error != 0)
    {
        //L4_KDB_Enter("A syscall returned an error, you might want to fix it");
    }
#endif

        L4_MsgLoad(msg);

        return 1;
}

extern void machine_load_sysloop(void);
void unix_syscall_return(int error);

void
unix_syscall_return(int error)
{
    thread_t thread = current_thread();
    int *retvals = get_bsduthreadrval(thread);

    int syscall_no = darbat_get_syscall_no(thread);
#if USE_FUNNEL
    struct sysent *callp = (syscall_no >= nsysent) ? &sysent[63] : &sysent[syscall_no];
    int funnel_type = (callp->sy_funnel & FUNNEL_MASK);
#endif

#if PRINT_BSD
    printf("UNIX SYSCALL RETURN\n"
            "e: %d 0:%d 1:%d\n", error, (int)retvals[0], (int)retvals[1]);
#endif

    // Not handling signals yet (uncomment this is you do pthread_cset)
#if USE_FUNNEL
    if((funnel_type  & FUNNEL_MASK)!= NO_FUNNEL)
    {
        thread_funnel_set(thread_get_funnel_lock(), FALSE);
    }
#endif 

    // We don't to reply to an execv if there's no error
    if(syscall_no == 59 && error == 0)
    {
        return;
    }

    L4_Msg_t msg;
    L4_MsgClear(&msg);
    L4_Set_MsgLabel(&msg, 0x541);

    if(!error)
    {
        L4_MsgAppendWord(&msg, 0);
        L4_MsgAppendWord(&msg, retvals[0]);
        L4_MsgAppendWord(&msg, retvals[1]);
    }
    else
    {
        if(error == EJUSTRETURN)
        {
            L4_MsgAppendWord(&msg, 0);
            L4_MsgAppendWord(&msg, 0);
            L4_MsgAppendWord(&msg, 0);
        }
        else if(error == ERESTART)
        {
            L4_MsgAppendWord(&msg, 2);
            L4_MsgAppendWord(&msg, 0);
            L4_MsgAppendWord(&msg, 0);
        }
        else
        {
            L4_MsgAppendWord(&msg, 1);
            L4_MsgAppendWord(&msg, error);
        }
    }
    

    if(syscall_no == 202 && error != 0)
    {
        printf( "You've just had a sysctl fail, you REALLY want to fix this\n"
                "Please add the appropirate entry in 'bsd/kern/sysctl_init.c'\n"
                "You may find 'bsd/sys/sysctl.h' useful in conjunction with the\n"
                "numbers above to figure out which entry you want to add\n");

        L4_KDB_Enter("Here, have a manual backtrace!");
    }

    L4_MsgLoad(&msg);
    L4_Send(darbat_get_l4_tid(thread));
    machine_load_sysloop();
    panic("Load_sysloop returned!!!");
}

void thread_syscall_return(kern_return_t ret);
void
thread_syscall_return(kern_return_t ret)
{

#if PRINT_MACH
        printf("THREAD_SYSCALL_RETURN retval: %d\n", ret);
#endif
    thread_t thread = current_thread();
    L4_Msg_t msg;
    L4_MsgClear(&msg);
    L4_Set_MsgLabel(&msg, 0x543);
    L4_MsgAppendWord(&msg, ret);
    L4_MsgLoad(&msg);
    L4_Send(darbat_get_l4_tid(thread));
    machine_load_sysloop();
    panic("Load_sysloop returned!!!");
}

/* x86 exception handler */

/* from wombat */
#define IA32_EXC_GENERAL_PROTECTION    13
#define IS_IA32_GP(msg)		       (L4_MsgWord(msg, 2) == IA32_EXC_GENERAL_PROTECTION)
#define L4_ARCH_IS_SYSCALL(tag, msg)   ((L4_UntypedWords(tag) == 12) && (IS_IA32_GP(msg)))
#define L4_ARCH_IS_EXCEPTION(tag, msg) ((L4_UntypedWords(tag) == 12) && !(IS_IA32_GP(msg)))

static int
except_handler(L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg)
{
	int send = 0;
	int i;

	/* debug */
	printf( "caught exception (tid 0x%lx, tag 0x%lx)\n", 
		tid.raw, tag.raw );
	for (i = 0; i < 12; i++)
		printf( "mr%d = 0x%lx\n", 
			i + 1, L4_MsgWord(msg, i) );

	/* see if it's a binary emulated syscall */
	if( L4_ARCH_IS_SYSCALL(tag, msg) )
	{
		L4_Word_t intnum;
		user_addr_t uesp, ueip;
		int callnum;
		int retval = 0xdeadbeef;  /* junk to catch bugs */

		printf( "Looks like a binary syscall!\n" );

		ueip = (user_addr_t) L4_MsgWord(msg, 0);
		uesp = (user_addr_t) L4_MsgWord(msg, 7);

		printf( "ip: 0x%lx\n", (unsigned long) ueip );
		printf( "sp: 0x%lx\n", (unsigned long) uesp );

		/* work out the int arg */
		intnum = (L4_MsgWord( msg, 3 ) - 2) >> 3;

		printf( "int: 0x%x\n", (int) intnum );

		switch( intnum )
		{
			case 0x2:
				panic("dbg int $2\n");
				break;

			case 0x3:
				panic("how'd you get here?!\n");
				break;

			case 0x80:    /* sysctl? */
				panic("sysctl?\n");
				break;

			case 0x81:    /* mach syscall */
				printf( "mach syscall\n" );
		                L4_KDB_Enter("binary mach syscall");

				callnum = - (int) L4_MsgWord( msg, 11 );

				printf( "mach syscall %d [count = %d]\n", 
					callnum, mach_trap_count );
				
				retval = do_mach_syscall( callnum, uesp );
				send = 1;
				break;

			case 0x82:
				panic( "pthread exit?!\n" );
				break;

			default:
				panic( "bogus int exception?!" );
		}

		/* shove the retval back into eax */
		L4_MsgPutWord( msg, 11, (L4_Word_t) retval );

		/* set it to restart at the next instruction */
		ueip += 2;
		L4_MsgPutWord( msg, 0, (L4_Word_t) ueip );

		/* zero the label */
		L4_Set_MsgLabel( msg, 0 );

		/* load the message to send */
		L4_MsgLoad(msg);
	}
	else
		panic( "FIXME: user exception\n" );

	panic( "what about gs?!?!\n" );

	return send;
}


extern void cons_cinput(char ch); /* so we can process tty chars */
static void
poll_cons(void)
{
	int c;

	c = darbat_cons_poll_nonblocking();


	if( c == 0xb ) /* ctrl+k */
		L4_KDB_Enter("ctrl+k");

	if( c != -1 )
		cons_cinput( c );
}

/* XXX */
extern void clock_intr(void);
extern void net_rx_handle(void);

/* IPC from the timer or some other guy */
/* FIXME: Call from within the idle loop?
 * Why does idle spin, anywho?
 */
static int
handle_other_ipc( L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg )
{
        L4_Word_t label;
	int send = 0;

	/* deliver char, do timer tick, do something else */
	
	/* request type */
        label = L4_Label(tag);
        char c;

	switch( label )
	{
		case CT_REQ_TIMER:
			/* timer tick */
			clock_intr();
			
			/* and while we're here, poll l4 serial */
			poll_cons();

			break;

		case CT_REQ_CONSIN:
			/* character on the console */
			/* pull out the char */
			c = L4_MsgWord( msg, 0 );
			/* feed it */
			cons_cinput( c );
			break;

		case CT_REQ_RX:
			// printf( "doing net_rx_handle\n" );
			net_rx_handle();
			break;

		default:
			printf("unknown syscall IPC? %d\n" , (int)label);
			printf("tid is %lx\n", tid.raw);
			printf("my tid is 0x%lx\n", L4_Myself().raw);
			L4_KDB_Enter("wtf!");
	}

	return send;
}

int pcb_process_pending_signal(void);

/* IPC from user - syscall, pagefault, exception, whatever */
static int
handle_user_ipc( L4_ThreadId_t tid, L4_MsgTag_t tag, L4_Msg_t *msg )
{
        L4_Word_t label;

	int send = 1;  /* In most cases we will want to send a reply */

        /* special case for pagefault handling */
        label = L4_Label(tag);
        if( (label & (~7U)) == L4_PAGEFAULT )
            label = L4_PAGEFAULT;
        /*
         * Dispatch IPC according to protocol.
         */
        switch( label )
        {
            case L4_PAGEFAULT:
                // printf ("got a PF\n");
                /* A pagefault occured. 
                 * Dispatch to the pager 
                 */
                //printf("got a pagefault\n");
                if( pager(tid, tag, msg) != 0 )
                {
                    send = 0; /* Don't want to reply 
                               * if pager call failed 
                               */
                }
                break;

	    /* Architecture specific exception */
	    case L4_EXCEPTION:
		    send = except_handler( tid, tag, msg );
		    break;

	    /* XNU syscall */
            case 1337:
                DBG();
                L4_KDB_Enter("this shouldn't happen");
                send = 0; //do_xnu_syscall(tid, tag, msg);
                break;
	    /* What the hell is this? CEG */
            case 1344:
                send = 1;
                break;
            case 0x541:
                send = handle_bsd_trap(tid, tag, msg);
                /*
                if(pcb_process_pending_signal())
                {
                    send = 0;
                }
                */
                break;
            case 0x542:
                send = handle_fork_ipc(tid, tag, msg);
                break;
            case 0x543:
                send = handle_mach_trap(tid, tag, msg);
                break;
            default:
                printf( "unknown syscall IPC? %d\n" , (int)label);
                printf( "tid is %lx\n", tid.raw);
                L4_KDB_Enter("wtf!");
                send = 0;
        }

	return send;
}


void myreplywait(void);
void 
myreplywait(void)
{
            __asm__ __volatile__ (
#ifdef __ELF__
                "push %%ebp\n\t"
                "movl ASM_TO,  %%eax\n\t"
                "movl ASM_FROM,  %%edx\n\t"
                "movl ASM_MR0, %%esi\n\t"
                "movl %%gs:0, %%ecx\n\t"
                "movl (4)(%%ecx), %%edi\n\t"
                "movl (8)(%%ecx), %%ebp\n\t"
                "movl ASM_jump_addr, %%ecx\n\t"
                "call *%%ecx\n\t"
                "movl %%eax, ASM_FROM\n\t"
                "movl %%esi, ASM_MR0\n\t"
                "movl %%esi, (%%ebx)\n\t"
                "movl %%edi, (4)(%%ebx)\n\t"
                "movl %%ebp, (8)(%%ebx)\n\t"
                "pop %%ebp"
#elif defined(__APPLE_CC__)
                "push %%ebp\n\t"
                "movl _ASM_TO,  %%eax\n\t"
                "movl _ASM_FROM,  %%edx\n\t"
                "movl _ASM_MR0, %%esi\n\t"
                "movl %%gs:0, %%ecx\n\t"
                "movl (4)(%%ecx), %%edi\n\t"
                "movl (8)(%%ecx), %%ebp\n\t"
                "movl _ASM_jump_addr, %%ecx\n\t"
                "call *%%ecx\n\t"
                "movl %%eax, _ASM_FROM\n\t"
                "movl %%esi, _ASM_MR0\n\t"
                "movl %%esi, (%%ebx)\n\t"
                "movl %%edi, (4)(%%ebx)\n\t"
                "movl %%ebp, (8)(%%ebx)\n\t"
                "pop %%ebp"
#else
#error "unknown compiler"
#endif
                :
                :
                :"eax","ebx","ecx","edx","edi","esi");
}

/* for the idle loop - wait for one message */
void syscall_waitone(void);
void 
syscall_waitone(void)
{
    L4_ThreadId_t tid;
    L4_MsgTag_t tag;
    L4_Msg_t msg;
    int send;

    tag = L4_Wait (&tid);

    L4_MsgStore (tag, &msg); /* Get the tag */

    /* user-land can't be messaging us */

    send = handle_other_ipc( tid, tag, &msg );
    assert(send == 0); /* don't want to reply from here (yet?) */
}


/* the main app loop */
void syscall_loop(void);

void
syscall_loop(void)
{
    L4_ThreadId_t tid;
    L4_MsgTag_t tag;
    L4_Msg_t msg;
    int send;

    // setup for asm crap
#if TGB_ASM
    L4_Word_t dummy;
    L4_KernelInterfacePage_t *kip =
        (L4_KernelInterfacePage_t *)L4_KernelInterface(&dummy, &dummy, &dummy);
    (void)dummy;
    ASM_jump_addr = (void *)(*((L4_Word_t *)&kip) + kip->Ipc);
#endif

    //printf(">>>> in syscall_loop()\n" );

    /* Setup which messages we will recieve */
    L4_Accept (L4_UntypedWordsAcceptor);

    /* Wait for the first message */
#if !TGB_ASM
    tag = L4_Wait (&tid);
#else
// BEGIN ASM FOR L4_WAIT
    {
        ASM_TO = L4_nilthread.raw;
        ASM_FROM = L4_anythread.raw;

        __asm__ __volatile__ (
            "pushl %%eax\n\t"
            "pushl %%ebx\n\t"
            "pushl %%ecx\n\t"
            "pushl %%edx\n\t"
            "pushl %%edi\n\t"
            "pushl %%esi\n\t"
            "pushl %%ebp\n\t"
#ifdef __ELF__
            "movl ASM_TO,  %%eax\n\t"
            "movl ASM_FROM,  %%edx\n\t"
            "movl $0x00004000, %%esi\n\t"
            "movl ASM_jump_addr, %%ecx\n\t"
            "call *%%ecx\n\t"
            "movl %%eax, ASM_FROM\n\t"
            "movl %%esi, ASM_MR0\n\t"
#elif defined(__APPLE_CC__)
            "movl _ASM_TO,  %%eax\n\t"
            "movl _ASM_FROM,  %%edx\n\t"
            "movl $0x00004000, %%esi\n\t"
            "movl _ASM_jump_addr, %%ecx\n\t"
            "call *%%ecx\n\t"
            "movl %%eax, _ASM_FROM\n\t"
            "movl %%esi, _ASM_MR0\n\t"
#else
#error "unknown compiler"
#endif
            "movl %%esi, (%%ebx)\n\t"
            "movl %%edi, (4)(%%ebx)\n\t"
            "movl %%ebp, (8)(%%ebx)\n\t"
            "popl %%ebp\n\t"
            "popl %%esi\n\t"
            "popl %%edi\n\t"
            "popl %%edx\n\t"
            "popl %%ecx\n\t"
            "popl %%ebx\n\t"
            "popl %%eax"
            :
            :);
        DBG();

        tid.raw = ASM_FROM;
        tag.raw = ASM_MR0;
        // END ASM FOR L4_WAIT
    }
#endif

    for(;;) 
    {
	thread_t thread;

	/* make sure whatever happens we know we've handled it... */
        send = 0x37;

        /* At this point we have recieved an IPC */
        L4_MsgStore (tag, &msg); /* Get the tag */

	/* see if it's from user-land, or somewhere else */
	thread = current_thread();
	if( darbat_get_l4_tid(thread).raw == tid.raw )
	{
		/* message from user-land */
		send = handle_user_ipc( tid, tag, &msg );
	}
	else
	{
		/* other IPC - clock thread */
		send = handle_other_ipc( tid, tag, &msg );
	}


	assert( send != 0x37 );
        if (send == 0)
        {
            /* Nothing to send, so we just wait */
            tag = L4_Wait (&tid);

        }
        else
        {
            /* Reply to caller and wait for next IPC */
#if !TGB_ASM 
        tag = L4_ReplyWait (tid, &tid);
#else
        {
            tag = L4_MsgTag();
            L4_Clear_SendBlock(&tag);
            L4_Set_ReceiveBlock(&tag);

            ASM_MR0 = tag.raw;
            ASM_TO = tid.raw;
            ASM_FROM = L4_anythread.raw;

            myreplywait();
            //DBG();
        // BEGIN ASM FOR L4_ReplyWait
            tid.raw = ASM_FROM;
            tag.raw = ASM_MR0;
        }
// END ASM FOR L4_WAIT
#endif


            if (L4_IpcFailed(tag)) 
            {
                L4_Word_t ec = L4_ErrorCode();
                printf("l4_request_page: IPC error (%p)\n", (void *)(ec));
                
                //l4e_print_error(ec);
            }

        }


    }
}


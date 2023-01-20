/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/syscalls.cc
 * Description:   
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: syscalls.cc,v 1.4 2004/06/02 21:24:14 stoess Exp $
 *                
 ********************************************************************/
#include <debug.h>
#include <kdb/tracepoints.h>
#include INC_API(kernelinterface.h)
#include INC_API(procdesc.h)
#include INC_API(syscalls.h)
#include INC_API(thread.h)
#include INC_API(tcb.h)
#include INC_API(user.h)
#include INC_GLUE(offsets.h)

DECLARE_TRACEPOINT(SYSCALL_MEMORY_CONTROL);


#define IS_SYSCALL(ip, syscall ) ( (ip & ~(SYSCALL_ALIGN - 1)) ==  (word_t) syscall)
extern "C" amd64_sysret_t syscall_dispatcher(word_t arg1,  /* RSI */
				   word_t arg2,  /* RDI */
				   word_t arg3,  /* RDX */
				   word_t uip,   /* RCX */
				   word_t arg4,  /* R08 */ 
				   word_t arg5,  /* R09 */ 
				   word_t arg6,  /* stack */ 
				   word_t arg7,  /* stack */ 
				   word_t usp,   /* stack */ 
				   word_t ufl    /* stack */ )
{
#if 0
    printf("arg1: %x\n", arg1);
    printf("arg2: %x\n",  arg2);
    printf("arg3: %x\n", arg3);
    printf("arg4: %x\n", arg4);
    printf("arg5: %x\n", arg5);
    printf("arg6: %x\n", arg6);
    printf("arg7: %x\n", arg7);
    printf("uip: %x\n", uip);
    printf("usp: %x\n", usp);
    printf("ufl: %x\n", ufl);
#endif

    amd64_sysret_t ret;

    if (IS_SYSCALL(uip, user_exchange_registers)){
	threadid_t dest;
	dest.set_raw(arg6);
	threadid_t pager;
	pager.set_raw(arg1);
	sys_exchange_registers (dest, arg2, arg3, arg4, arg5, arg7, pager, dest.is_local());

    }
    else if (IS_SYSCALL(uip, user_thread_control)){
	threadid_t dest;
	dest.set_raw(arg1);
	threadid_t pager;
	pager.set_raw(arg2);
	threadid_t scheduler;
	scheduler.set_raw(arg3);
	threadid_t space;
	space.set_raw(arg4);
	return sys_thread_control (dest, space, scheduler, pager, arg5);
    }
    else if (IS_SYSCALL(uip, user_space_control)){
	threadid_t space_tid;
	space_tid.set_raw(arg1);
	fpage_t kip_area;
	kip_area.raw = arg3;
	fpage_t utcb_area;
	utcb_area.raw = arg4;
	threadid_t redirector;
	redirector.set_raw(arg5);
	return sys_space_control(space_tid, arg2, kip_area, utcb_area, redirector);
    }
    else if (IS_SYSCALL(uip, user_schedule)){
	threadid_t dest;
	dest.set_raw(arg1);
	return sys_schedule (dest, arg3, arg4, arg2, arg5);
    }    
    else if (IS_SYSCALL(uip, user_thread_switch)){
	threadid_t dest;
	dest.set_raw(arg1);
	sys_thread_switch (dest);
    }
    else if (IS_SYSCALL(uip, user_unmap)){
	sys_unmap(arg3);
	ret.rax = get_current_tcb()->get_local_id ().get_raw ();
	ret.rdx = 0;
	return ret;
    }
    else if (IS_SYSCALL(uip, user_processor_control)){
	sys_processor_control (arg1, arg2, arg3, arg4);
    }  
    else if (IS_SYSCALL(uip, user_memory_control)){
	TRACEPOINT (SYSCALL_MEMORY_CONTROL, printf("SYS_MEMORY_CONTROL\n"));
	//sys_memory_control (arg2, arg3, arg4, arg5, arg6);
	ret.rax = 0;
	ret.rdx = 0;
    }
    else {
	UNIMPLEMENTED();
    }
    
    ret.rax = 0;
    ret.rdx = 0;
    return ret;
    
}



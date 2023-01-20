/*********************************************************************
 *                
 * Copyright (C) 2002-2003,  Karlsruhe University
 *                
 * File path:     glue/v4-ia32/syscalls.h
 * Description:   syscall macros
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
 * $Id: syscalls.h,v 1.19 2003/09/24 19:04:36 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_IA32__SYSCALLS_H__
#define __GLUE__V4_IA32__SYSCALLS_H__

#include INC_ARCH(trapgate.h)
//
// System call function attributes
//
#define SYSCALL_ATTR(sec_name)


//
//	Ipc ()
//
// Use three register parameters (to_tid = EAX, from_tid = EDX, restore_sp = ECX).
//
#define SYS_IPC(to, from)				\
  void __attribute__ ((regparm (3))) sys_ipc (to, from, word_t restore_sp)

#define RETURN_IPC_SANITY					\
    if (!current->get_state().is_running())			\
    {	printf("line %d\n", __LINE__);				\
	enter_kdebug("return_ipc ! running");}			\
    if (current->queue_state.is_set(queue_state_t::wakeup))	\
    {	printf("line %d\n", __LINE__);				\
	enter_kdebug("return_ipc in wakeup");}


#define return_ipc(from)			\
{						\
    asm("leal -4(%0), %%esp	\n"		\
	"ret			\n"		\
	::					\
	"c" (restore_sp),			\
	"a" (from.get_raw()));			\
	while(1);				\
}


//
//	ThreadControl ()
//
#define SYS_THREAD_CONTROL(dest, space, scheduler, pager, \
		send_redirector_tid, recv_redirector_tid, utcb_address) \
  void sys_thread_control (dest, space, scheduler, pager, send_redirector_tid,\
  	recv_redirector_tid, utcb_address, ia32_exceptionframe_t * __frame)

#define return_thread_control(result)		\
{						\
    __frame->eax = result;			\
    return;					\
}


//
//	SpaceControl ()
//
#define SYS_SPACE_CONTROL(space, control, kip_area, utcb_area)	\
  void sys_space_control (space, control, kip_area, utcb_area,	\
		          ia32_exceptionframe_t * __frame)

#define return_space_control(result, control)	\
{						\
    __frame->eax = result;			\
    __frame->ecx = control;			\
    return;					\
}


//
//	Schedule ()
//
#define SYS_SCHEDULE(dest, ts_len, total_quantum, processor_control, prio )\
  void sys_schedule (dest, ts_len, total_quantum, processor_control, prio, \
		     ia32_exceptionframe_t * __frame)

#define return_schedule(result, rem_ts, rem_total)	\
{							\
    __frame->eax = result;				\
    __frame->ecx = rem_ts;				\
    __frame->edx = rem_total;				\
    return;						\
}


//
//	ExchangeRegisters ()
//
#define SYS_EXCHANGE_REGISTERS(dest, control, usp, uip,		\
			       uflags, uhandle, pager)		\
  void sys_exchange_registers (dest, control, usp, uip,		\
			       uflags, uhandle, pager,		\
			       ia32_exceptionframe_t * __frame)

#define return_exchange_registers(result,			\
    control, sp, ip, flags, pager, handle)			\
{								\
    __frame->eax = (result).get_raw();				\
    __frame->ecx = control;					\
    __frame->edx = sp;						\
    __frame->esi = ip;						\
    __frame->edi = flags;					\
    __frame->ebx = handle;					\
    __frame->ebp = pager.get_raw();				\
    return;							\
}


//
//	ThreadSwitch ()
//
#define SYS_THREAD_SWITCH(dest)					\
  void sys_thread_switch (dest)

#define return_thread_switch() return


//
//	Unmap ()
//
#define SYS_UNMAP(control)					\
  void sys_unmap (control)

#define return_unmap() return


//
//	ProcessorControl ()
//
#define SYS_PROCESSOR_CONTROL(processor_no, internal_frequency,	\
			      external_frequency, voltage)	\
  void sys_processor_control (processor_no, internal_frequency,	\
			      external_frequency, voltage)

#define return_processor_control() return


//
//	MemoryControl ()
//
#define SYS_MEMORY_CONTROL(control, attribute0, attribute1,	\
			   attribute2, attribute3)		\
  void sys_memory_control (control, attribute0, attribute1,	\
		           attribute2, attribute3)

#define return_memory_control()	return


/* entry functions for exceptions */
extern "C" void exc_user_sysipc(void);
extern "C" void exc_user_syscall(void);
extern "C" void exc_user_privsyscall(void);


#endif /* !__GLUE__V4_IA32__SYSCALLS_H__ */

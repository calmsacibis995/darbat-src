/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/syscalls.h
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
 * $Id: syscalls.h,v 1.6 2004/05/31 13:46:44 stoess Exp $
 * 
 ********************************************************************/
#ifndef __GLUE__V4_AMD64__SYSCALLS_H__
#define __GLUE__V4_AMD64__SYSCALLS_H__

#include INC_ARCH(trapgate.h)
//
// System call function attributes
//
#define SYSCALL_ATTR(sec_name) 

typedef struct { word_t rax;  word_t rdx;} amd64_sysret_t;
//
//	Ipc ()
//
//      GCC won't put to, from in registers, as they are classes with overloaded
//	operators.
//
#define SYS_IPC(to, from, timeout)				\
  amd64_sysret_t SYSCALL_ATTR ("ipc") sys_ipc (to, from, word_t amd64_rsi,\
					 word_t amd64_rdi, word_t amd64_rdx,\
					 word_t amd64_rcx, timeout)

#define return_ipc(from)			\
{						\
	amd64_sysret_t amd64_ret;		\
	amd64_ret.rax = (from).get_raw();	\
	amd64_ret.rdx = current->get_tag().raw;	\
	current->set_partner (from);		\
	return amd64_ret;			\
} 

//
//	ThreadControl ()
//
#define SYS_THREAD_CONTROL(dest, space, scheduler, pager, utcb_address)\
   amd64_sysret_t sys_thread_control (dest, space, scheduler, pager, utcb_address)

#define return_thread_control(result)		\
{						\
	amd64_sysret_t amd64_ret;		\
	amd64_ret.rax = result;			\
	amd64_ret.rdx = 0;			\
	return amd64_ret;			\
}
//
//	SpaceControl ()
//
#define SYS_SPACE_CONTROL(space, control, kip_area, utcb_area,	\
			  redirector)					\
  amd64_sysret_t SYSCALL_ATTR ("space_control")			\
  sys_space_control (space, control, kip_area, utcb_area,		\
		     redirector)

#define return_space_control(result, control)	\
{						\
	amd64_sysret_t amd64_ret;		\
	amd64_ret.rax = result;			\
	amd64_ret.rdx = control;		\
	return amd64_ret;			\
} 

//
//	Schedule ()
//
#define SYS_SCHEDULE(dest, time_control, processor_control,	\
		     prio, preemption_control)			\
  amd64_sysret_t SYSCALL_ATTR ("schedule")			\
  sys_schedule (dest, time_control, processor_control,		\
		prio, preemption_control)

#define return_schedule(result, time_control)	\
{						\
	amd64_sysret_t amd64_ret;		\
	amd64_ret.rax = result;			\
	amd64_ret.rdx = time_control;		\
	return amd64_ret;			\
} 




//
//	ExchangeRegisters ()
//
//
#define SYS_EXCHANGE_REGISTERS(dest, control, usp, uip,         \
                               uflags, uhandle, pager, is_local)\
  void sys_exchange_registers (dest, control, usp, uip,         \
                               uflags, uhandle, pager, is_local)


#define return_exchange_registers(result,					\
    control, sp, ip, flags, pager, handle)					\
{										\
   word_t amd64_dummy, amd64_uip;						\
   tcb_t *amd64_current = get_current_tcb();					\
   struct {									\
	word_t       rdi;							\
	word_t       r8;							\
	word_t       r9;							\
	word_t       r10;							\
	word_t       r11;							\
	word_t       rsp;							\
    }amd64_ret;									\
    amd64_ret.rdi = pager.get_raw();						\
    amd64_ret.r8 =  ip;								\
    amd64_ret.r9 = flags;							\
    amd64_ret.r10 = handle;							\
    amd64_ret.r11 = (word_t) amd64_current->get_user_flags();			\
    amd64_ret.rsp = (word_t) amd64_current->get_user_sp();			\
    amd64_uip = (word_t) amd64_current->get_user_ip();				\
    __asm__ __volatile__("movq   (%[ret]), %%rdi	\n"			\
			 "movq  8(%[ret]), %%r8		\n"			\
			 "movq 16(%[ret]), %%r9		\n"			\
			 "movq 24(%[ret]), %%r10	\n"			\
			 "movq 32(%[ret]), %%r11	\n"			\
			 "movq 40(%[ret]), %%rsp	\n"			\
			 "sysretq"						\
			 : /* outputs */					\
			 "=a" (amd64_dummy),		/* %0 RAX */		\
			 "=b" (amd64_dummy),		/* %1 RBX */		\
			 "=c" (amd64_dummy),		/* %2 RCX */		\
			 "=d" (amd64_dummy),		/* %3 RDX */		\
			 "=S" (amd64_dummy)		/* %4 RSI */		\
			 : /* inputs */						\
				"0" (result),		/* %5  RAX */		\
			 [ret]	"1" (&amd64_ret),	/* %6  RBX */		\
				"2" (amd64_uip),	/* %7  RCX */		\
				"3" (sp),		/* %8  RDX */		\
				"4" (control)		/* %9  RSI  */		\
			 /* no clobbers */					\
	);									\
    while(1);									\
}

//
//	ThreadSwitch ()
//
#define SYS_THREAD_SWITCH(dest)					\
  void SYSCALL_ATTR ("thread_switch")				\
  sys_thread_switch (dest)

#define return_thread_switch() return


//
//	Unmap ()
//
#define SYS_UNMAP(control)					\
  void SYSCALL_ATTR ("unmap") sys_unmap (control)

#define return_unmap() return


//
//	ProcessorControl ()
//
#define SYS_PROCESSOR_CONTROL(processor_no, internal_frequency,	\
			      external_frequency, voltage)	\
  void SYSCALL_ATTR ("processor_control")			\
  sys_processor_control (processor_no, internal_frequency,	\
			 external_frequency, voltage)

#define return_processor_control() return


//
//	MemoryControl ()
//
#define SYS_MEMORY_CONTROL(control, attribute0, attribute1,	\
			   attribute2, attribute3)		\
  void SYSCALL_ATTR ("memory_control")				\
  sys_memory_control (control, attribute0, attribute1,		\
		      attribute2, attribute3)

#define return_memory_control()	return



/* entry functions for dispatching syscalls */
extern "C" void syscall_entry();

#endif /* !__GLUE__V4_AMD64__SYSCALLS_H__ */

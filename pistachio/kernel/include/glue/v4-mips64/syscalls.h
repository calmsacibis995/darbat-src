/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  University of New South Wales
 *                
 * File path:     glue/v4-mips64/syscalls.h
 * Description:   Syscall specific macros
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
 * $Id: syscalls.h,v 1.19 2004/12/09 01:00:07 cvansch Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_MIPS64__SYSCALLS_H__
#define __GLUE__V4_MIPS64__SYSCALLS_H__

#if defined(ASSEMBLY)
#define UL(x)	(x)
#else
#define UL(x)	(x##ul)
#endif


#define L4_TRAP_KPUTC			UL(-100)
#define L4_TRAP_KGETC			UL(-101)
#define L4_TRAP_KDEBUG			UL(-102)
#define L4_TRAP_UNUSED			UL(-103)
#define L4_TRAP_KGETC_NB		UL(-104)
#define L4_TRAP_READ_PERF		UL(-110)
#define L4_TRAP_WRITE_PERF		UL(-111)
#define L4_TRAP_KSET_THRD_NAME		UL(-120)

/* The syscall assembler depends on the values below */
#define SYSCALL_ipc			UL(-101)
#define SYSCALL_thread_switch		UL(-102)
#define SYSCALL_thread_control		UL(-103)
#define SYSCALL_exchange_registers	UL(-104)
#define SYSCALL_schedule		UL(-105)
#define SYSCALL_unmap			UL(-106)
#define SYSCALL_space_control		UL(-107)
#define SYSCALL_processor_control	UL(-108)
#define SYSCALL_memory_control		UL(-109)
#define SYSCALL_unused			UL(-110)

#if !defined(ASSEMBLY)

//
// System call function attributes.
//

#define SYSCALL_ATTR(sec_name)

#define SYS_IPC_RETURN_TYPE                     threadid_t
#define SYS_THREAD_CONTROL_RETURN_TYPE          word_t
#define SYS_EXCHANGE_REGISTERS_RETURN_TYPE      threadid_t
#define SYS_SPACE_CONTROL_RETURN_TYPE           word_t
#define SYS_SCHEDULE_RETURN_TYPE                word_t
#define SYS_MEMORY_CONTROL_RETURN_TYPE          word_t

//
// Syscall declaration wrappers.
//

#define SYS_IPC(to, from)					\
  SYS_IPC_RETURN_TYPE SYSCALL_ATTR ("ipc") 			\
  sys_ipc (to, from)

#define SYS_THREAD_CONTROL(dest, space, scheduler, pager,	\
		send_redirector, recv_redirector, utcb)		\
  SYS_THREAD_CONTROL_RETURN_TYPE SYSCALL_ATTR ("thread_control")\
  sys_thread_control (dest, space, scheduler, pager,		\
		  send_redirector, recv_redirector, utcb)

#define SYS_SPACE_CONTROL(space, control, kip_area, utcb_area)	\
  SYS_SPACE_CONTROL_RETURN_TYPE SYSCALL_ATTR ("space_control")	\
  sys_space_control (space, control, kip_area, utcb_area)

#define SYS_SCHEDULE(dest, ts_len, total_quantum,		\
		     processor_control, prio)			\
  SYS_SCHEDULE_RETURN_TYPE SYSCALL_ATTR ("schedule")		\
  sys_schedule (dest, ts_len, total_quantum,			\
		processor_control, prio)

#define SYS_EXCHANGE_REGISTERS(dest, control, usp, uip, uflags,	\
			uhandle, pager)				\
  SYS_EXCHANGE_REGISTERS_RETURN_TYPE SYSCALL_ATTR ("exchange_registers")	\
  sys_exchange_registers (dest, control, usp, uip,		\
			  uflags, uhandle, pager)

#define SYS_THREAD_SWITCH(dest)					\
  void SYSCALL_ATTR ("thread_switch")				\
  sys_thread_switch (dest)

#define SYS_UNMAP(control)					\
  void SYSCALL_ATTR ("unmap") sys_unmap (control)

#define SYS_PROCESSOR_CONTROL(processor_no, internal_frequency,	\
			      external_frequency, voltage)	\
  void SYSCALL_ATTR ("processor_control")			\
  sys_processor_control (processor_no, internal_frequency,	\
			 external_frequency, voltage)

#define SYS_MEMORY_CONTROL(control, attribute0, attribute1,	\
			   attribute2, attribute3)		\
  SYS_MEMORY_CONTROL_RETURN_TYPE SYSCALL_ATTR ("memory_control")	\
  sys_memory_control (control, attribute0, attribute1,		\
		      attribute2, attribute3)

/**
 * The application gets the kernel info page by doing some illegal instruction, with 
 * at ($1) == 0x1face (interface) ca11 (call) 14 (L4) e1f (ELF) 64 (MIPS64)
 */
#define MAGIC_KIP_REQUEST          (0x1FACECA1114e1f64ULL)


/**
 * Preload registers and return from sys_ipc
 * @param from The FROM value after the system call
 */

#define return_ipc(from)	return (from)


/**
 * Preload registers and return from sys_thread_control
 * @param result The RESULT value after the system call
 */

#define return_thread_control(result)	return (result)

/**
 * Preload registers and return from sys_exchange_registers
 * @param result The RESULT value after the system call
 * @param control The CONTROL value after the system call
 * @param sp The SP value after the system call
 * @param ip The IP value after the system call
 * @param flags The FLAGS value after the system call
 * @param pager The PAGER value after the system call
 * @param handle The USERDEFINEDHANDLE value after the system call
 */

#define return_exchange_registers(result, control, sp, ip, flags, pager, handle)    \
{								\
    register word_t ctrl asm("$4") = control;	/* a0 */	\
    register word_t sp_r asm("$5") = sp;	/* a1 */	\
    register word_t ip_r asm("$6") = ip;	/* a2 */	\
    register word_t flg asm("$7") = flags;	/* a3 */	\
    register word_t pgr asm("$8") = pager.get_raw();	/* t0 */	\
    register word_t hdl asm("$9") = handle;	/* t1 */	\
\
    __asm__ __volatile__ (					\
	"" : : "r" (ctrl), "r" (sp_r), "r" (ip_r),		\
	"r" (flg), "r" (pgr), "r" (hdl)				\
    );								\
    return (result);						\
}


/**
 * Return from sys_thread_switch
 */
#define return_thread_switch()	return


/**
 * Return from sys_unmap
 */
#define return_unmap() return


/**
 * Preload registers and return from sys_thread_switch
 * @param result The RESULT value after the system call
 * @param control The CONTROL value after the system call
 */
#define return_space_control(result, control)		\
{   \
    register word_t c asm("$4") = control; /* a0 */	\
    __asm__ __volatile__ (				\
	"" : : "r" (c)					\
    );							\
    return (result);					\
}


/**
 * Preload registers and return from sys_schedule
 * @param result The RESULT value after the system call
 * @param time_control The TIME_CONTROL value after the system call
 */
#define return_schedule(result, rem_ts, rem_total)	\
{							\
    register word_t ts asm("$5") = rem_ts;		\
    register word_t tot asm("$6") = rem_total;		\
							\
    __asm__ __volatile__ (				\
       "" : : "r" (ts), "r" (tot)			\
    );							\
    return (result);					\
}

/**
 * Return from sys_memory_control
 */
#define return_memory_control(result)	return (result)

/**
 * Return from sys_processor_control
 */
#define return_processor_control() return

#endif /* !ASSEMBLY */

#endif /* !__GLUE__V4_MIPS64__SYSCALLS_H__ */

/*********************************************************************
 *                
 * Copyright (C) 2001-2004,  Karlsruhe University
 *                
 * File path:     l4/thread.h
 * Description:   Thread handling interfaces
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
 * $Id: thread.h,v 1.21 2004/03/12 17:52:14 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __L4__THREAD_H__
#define __L4__THREAD_H__

#include <l4/types.h>
#include __L4_INC_ARCH(syscalls.h)
#include __L4_INC_ARCH(vregs.h)


/*
 * Thread states
 */

typedef struct L4_ThreadState {
    L4_Word_t	raw;
} L4_ThreadState_t;

L4_INLINE L4_Bool_t L4_ThreadWasHalted (L4_ThreadState_t s)
{
    return s.raw & (1 << 0);
}

L4_INLINE L4_Bool_t L4_ThreadWasReceiving (L4_ThreadState_t s)
{
    return s.raw & (1 << 1);
}

L4_INLINE L4_Bool_t L4_ThreadWasSending (L4_ThreadState_t s)
{
    return s.raw & (1 << 2);
}

L4_INLINE L4_Bool_t L4_ThreadWasIpcing (L4_ThreadState_t s)
{
    return s.raw & (3 << 1);
}



/*
 * TCR related functions
 */

L4_INLINE L4_ThreadId_t L4_MyGlobalId (void)
{
    L4_ThreadId_t id;
    id.raw = __L4_TCR_MyGlobalId ();
    return id;
}

L4_INLINE L4_ThreadId_t L4_Myself (void)
{
    return L4_MyGlobalId ();
}

L4_INLINE L4_Word_t L4_ProcessorNo (void)
{
    return __L4_TCR_ProcessorNo ();
}

L4_INLINE L4_Word_t L4_UserDefinedHandle (void)
{
    return __L4_TCR_UserDefinedHandle ();
}

L4_INLINE void L4_Set_UserDefinedHandle (L4_Word_t NewValue)
{
    __L4_TCR_Set_UserDefinedHandle (NewValue);
}

L4_INLINE L4_ThreadId_t L4_Pager (void)
{
    L4_ThreadId_t id;
    id.raw = __L4_TCR_Pager ();
    return id;
}

L4_INLINE void L4_Set_Pager (L4_ThreadId_t NewPager)
{
    __L4_TCR_Set_Pager (NewPager.raw);
}

L4_INLINE L4_ThreadId_t L4_ExceptionHandler (void)
{
    L4_ThreadId_t id;
    id.raw = __L4_TCR_ExceptionHandler ();
    return id;
}

L4_INLINE void L4_Set_ExceptionHandler (L4_ThreadId_t NewHandler)
{
    __L4_TCR_Set_ExceptionHandler (NewHandler.raw);
}

L4_INLINE L4_Word_t L4_ErrorCode (void)
{
    return __L4_TCR_ErrorCode ();
}

L4_INLINE L4_ThreadId_t L4_IntendedReceiver (void)
{
    L4_ThreadId_t id;
    id.raw = __L4_TCR_IntendedReceiver ();
    return id;
}

L4_INLINE L4_ThreadId_t L4_ActualSender (void)
{
    L4_ThreadId_t id;
    id.raw = __L4_TCR_ActualSender ();
    return id;
}

L4_INLINE void L4_Set_VirtualSender (L4_ThreadId_t t)
{
    __L4_TCR_Set_VirtualSender (t.raw);
}



/*
 * Derived functions
 */

/*
 * These are the functions derived from the exchange register syscall.
 * For normal C, function overloading is not supported.  Functions
 * with unique names (i.e., with the suffix inside <> appended) have
 * therefore been provided.
 *
 *   L4_SameThreads				(l, r)
 *   L4_UserDefinedHandle<Of>			(t)
 *   L4_Set_UserDefinedHandle<Of>		(t, handle)
 *   L4_Pager<Of>				(t)
 *   L4_Set_Pager<Of>				(t, pager)
 *   L4_Start					(t)
 *   L4_Start<_SpIp>				(t, sp, ip)
 *   L4_Start<_SpIpFlags>			(t, sp, ip, flags)
 *   L4_Stop					(t)
 *   L4_Stop_Thread				(t)	// No return state
 *   L4_Stop<_SpIpFlags>			(t, &sp, &ip, &flags)
 *   L4_AbortReceive_and_stop			(t)
 *   L4_AbortReceive_and_stop_Thread		(t)	// No return state
 *   L4_AbortReceive_and_stop<_SpIpFlags>	(t, &sp, &ip, &flags)
 *   L4_AbortSend_and_stop			(t)
 *   L4_AbortSend_and_stop_Thread		(t)	// No return state
 *   L4_AbortSend_and_stop<_SpIpFlags>		(t, &sp, &ip, &flags)
 *   L4_AbortIpc_and_stop_Thread		(t)	// No return state
 *   L4_AbortIpc_and_stop<_SpIpFlags>		(t, &sp, &ip, &flags)
 *   L4_CopyVolatile_regs			(src, dest)
 *   L4_CopySaved_regs<_SpIp>			(src, dest)
 *   L4_Copy_regs<_SpIp>			(src, dest)
 *   L4_Copy_regs_to_mrs			(src)
 *
 */

L4_INLINE L4_Word_t L4_UserDefinedHandleOf (L4_ThreadId_t t)
{
    L4_Word_t dummy, handle;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Deliver, 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &handle,
				 &dummy_id);

    return handle;
}

L4_INLINE void L4_Set_UserDefinedHandleOf (L4_ThreadId_t t, L4_Word_t handle)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_user, 0, 0, 0, handle, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_Word_t L4_UserDefinedHandle (L4_ThreadId_t t)
{
    return L4_UserDefinedHandleOf (t);
}

L4_INLINE void L4_Set_UserDefinedHandle (L4_ThreadId_t t, L4_Word_t handle)
{
    L4_Set_UserDefinedHandleOf (t, handle);
}
#endif /* __l4_cplusplus */

L4_INLINE L4_ThreadId_t L4_PagerOf (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t pager;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Deliver, 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &pager);

    return pager;
}

L4_INLINE void L4_Set_PagerOf (L4_ThreadId_t t, L4_ThreadId_t p)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_pager, 0, 0, 0, 0, p,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_ThreadId_t L4_Pager (L4_ThreadId_t t)
{
    return L4_PagerOf (t);
}

L4_INLINE void L4_Set_Pager (L4_ThreadId_t t, L4_ThreadId_t p)
{
    L4_Set_PagerOf (t, p);
}
#endif /* __l4_cplusplus */

L4_INLINE void L4_Start (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Resume + L4_ExReg_AbortIPC, 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_Start_SpIp (L4_ThreadId_t t, L4_Word_t sp, L4_Word_t ip)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_sp_ip + L4_ExReg_Resume + L4_ExReg_AbortIPC,
				 sp, ip, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}


L4_INLINE void L4_Start_SpIpFlags (L4_ThreadId_t t, L4_Word_t sp,
				   L4_Word_t ip, L4_Word_t flags)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_sp_ip_flags +  L4_ExReg_Resume + L4_ExReg_AbortIPC,
				 sp, ip, flags, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

#if defined(__l4_cplusplus)
L4_INLINE void L4_Start (L4_ThreadId_t t, L4_Word_t sp, L4_Word_t ip)
{
    L4_Start_SpIp (t, sp, ip);
}


L4_INLINE void L4_Start (L4_ThreadId_t t, L4_Word_t sp,
			 L4_Word_t ip, L4_Word_t flags)
{
    L4_Start_SpIpFlags (t, sp, ip, flags);
}
#endif

L4_INLINE L4_ThreadState_t L4_Stop (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);

    return state;
}

L4_INLINE void L4_Stop_Thread (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt, 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE L4_ThreadState_t L4_Stop_SpIpFlags (L4_ThreadId_t t,
					      L4_Word_t *sp,
					      L4_Word_t *ip,
					      L4_Word_t *flags)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, sp, ip, flags, &dummy,
				 &dummy_id);

    return state;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_ThreadState_t L4_Stop (L4_ThreadId_t t, L4_Word_t *sp,
				    L4_Word_t *ip, L4_Word_t *flags)
{
    return L4_Stop_SpIpFlags (t, sp, ip, flags);
}
#endif

L4_INLINE L4_ThreadState_t L4_AbortReceive_and_stop (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortRecvIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);

    return state;
}

L4_INLINE void L4_AbortReceive_and_stop_Thread (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortRecvIPC,
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE L4_ThreadState_t L4_AbortReceive_and_stop_SpIpFlags (
    L4_ThreadId_t t,
    L4_Word_t *sp,
    L4_Word_t *ip,
    L4_Word_t *flags)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortRecvIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, sp, ip, flags, &dummy,
				 &dummy_id);

    return state;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_ThreadState_t L4_AbortReceive_and_stop (L4_ThreadId_t t,
						     L4_Word_t *sp,
						     L4_Word_t *ip,
						     L4_Word_t *flags)
{
    return L4_AbortReceive_and_stop_SpIpFlags (t, sp, ip, flags);
}
#endif
    
L4_INLINE L4_ThreadState_t L4_AbortSend_and_stop (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortSendIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);

    return state;
}

L4_INLINE void L4_AbortSend_and_stop_Thread (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortSendIPC,
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE L4_ThreadState_t L4_AbortSend_and_stop_SpIpFlags (
    L4_ThreadId_t t,
    L4_Word_t *sp,
    L4_Word_t *ip,
    L4_Word_t *flags)
{

    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortSendIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, sp, ip, flags, &dummy,
				 &dummy_id);

    return state;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_ThreadState_t L4_AbortSend_and_stop (L4_ThreadId_t t,
						   L4_Word_t *sp,
						   L4_Word_t *ip,
						   L4_Word_t *flags)
{
    return L4_AbortSend_and_stop_SpIpFlags (t, sp, ip, flags);
}
#endif

L4_INLINE L4_ThreadState_t L4_AbortIpc_and_stop (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);

    return state;
}

L4_INLINE void L4_AbortIpc_and_stop_Thread (L4_ThreadId_t t)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortIPC,
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE L4_ThreadState_t L4_AbortIpc_and_stop_SpIpFlags (L4_ThreadId_t t,
							   L4_Word_t *sp,
							   L4_Word_t *ip,
							   L4_Word_t *flags)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;
    L4_ThreadState_t state;

    (void) L4_ExchangeRegisters (t, L4_ExReg_Halt + L4_ExReg_AbortIPC + L4_ExReg_Deliver,
				 0, 0, 0, 0, L4_nilthread,
				 &state.raw, sp, ip, flags, &dummy,
				 &dummy_id);

    return state;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_ThreadState_t L4_AbortIpc_and_stop (L4_ThreadId_t t,
						 L4_Word_t *sp,
						 L4_Word_t *ip,
						 L4_Word_t *flags)
{
    return L4_AbortIpc_and_stop_SpIpFlags (t, sp, ip, flags);
}
#endif

L4_INLINE void L4_CopyVolatile_regs (L4_ThreadId_t src, L4_ThreadId_t dest)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (dest, L4_ExReg_VolatileRegs + L4_ExReg_SrcThread(src),
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_CopySaved_regs (L4_ThreadId_t src, L4_ThreadId_t dest)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (dest, L4_ExReg_SavedRegs + L4_ExReg_SrcThread(src),
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_CopySaved_regs_SpIp (L4_ThreadId_t src, L4_ThreadId_t dest, L4_Word_t sp, L4_Word_t ip)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (dest, L4_ExReg_sp_ip + L4_ExReg_SavedRegs + L4_ExReg_SrcThread(src),
				 sp, ip, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_Copy_regs (L4_ThreadId_t src, L4_ThreadId_t dest)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (dest, L4_ExReg_VolatileRegs + L4_ExReg_SavedRegs + L4_ExReg_SrcThread(src),
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_Copy_regs_SpIp (L4_ThreadId_t src, L4_ThreadId_t dest, L4_Word_t sp, L4_Word_t ip)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (dest, L4_ExReg_sp_ip + L4_ExReg_VolatileRegs +
				 L4_ExReg_SavedRegs + L4_ExReg_SrcThread(src),
				 sp, ip, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE void L4_Copy_regs_to_mrs (L4_ThreadId_t src)
{
    L4_Word_t dummy;
    L4_ThreadId_t dummy_id;

    (void) L4_ExchangeRegisters (src, L4_ExReg_RegsToMRs, 
				 0, 0, 0, 0, L4_nilthread,
				 &dummy, &dummy, &dummy, &dummy, &dummy,
				 &dummy_id);
}

L4_INLINE L4_Word_t L4_AssociateInterrupt (L4_ThreadId_t InterruptThread,
					   L4_ThreadId_t HandlerThread)
{
    return L4_ThreadControl (InterruptThread, InterruptThread,
			     L4_nilthread, HandlerThread, 
			     L4_anythread, L4_anythread, (void *) -1);
}

L4_INLINE L4_Word_t L4_DeassociateInterrupt (L4_ThreadId_t InterruptThread)
{
    return L4_ThreadControl (InterruptThread, InterruptThread,
			     L4_nilthread, InterruptThread, 
			     L4_anythread, L4_anythread, (void *) -1);
}

#endif /* !__L4__THREAD_H__ */

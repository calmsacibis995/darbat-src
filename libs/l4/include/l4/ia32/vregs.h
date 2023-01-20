/*********************************************************************
 *                
 * Copyright (C) 2001-2003,  Karlsruhe University
 *                
 * File path:     l4/ia32/vregs.h
 * Description:   x86 virtual registers
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
 * $Id: vregs.h,v 1.12 2003/12/12 15:54:29 joshua Exp $
 *                
 ********************************************************************/
#ifndef __L4__X86__VREGS_H__
#define __L4__X86__VREGS_H__


/*
 * All virtual registers on x86 is located in a user Level Thread
 * Control Block (UTCB).
 */

#if (__GNUC__ >= 3) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96))
L4_INLINE L4_Word_t * __L4_X86_Utcb (void) __attribute__ ((pure));
#endif

L4_INLINE L4_Word_t * __L4_X86_Utcb (void)
{
    L4_Word_t *utcb;

    __asm__ __volatile__ (
	"/* __L4_X86_Utcb() */			\n"
	"	mov %%gs:0, %0			\n"

	: /* outputs */
	"=r"(utcb)

	/* no inputs */
	/* no clobbers */
	);

    return utcb;
}



#define __L4_NUM_MRS	64

/*
 * Location of TCRs within UTCB.
 */

#define __L4_TCR_PREEMPTED_IP			(-3)
#define __L4_TCR_PREEMPT_CALLBACK_IP		(-4)
#define __L4_TCR_VIRTUAL_ACTUAL_SENDER		(-5)
#define __L4_TCR_INTENDED_RECEIVER		(-6)
#define __L4_TCR_ERROR_CODE			(-7)
#define __L4_TCR_PREEMPT_FLAGS			(-8)
#define __L4_TCR_COP_FLAGS			(-8)
#define __L4_TCR_EXCEPTION_HANDLER		(-9)
#define __L4_TCR_PAGER				(-10)
#define __L4_TCR_USER_DEFINED_HANDLE		(-11)
#define __L4_TCR_PROCESSOR_NO			(-12)
#define __L4_TCR_ACCEPTOR			(-13)
#define __L4_TCR_NOTIFY_BITS			(-14)
#define __L4_TCR_NOTIFY_MASK			(-15)
#define __L4_TCR_MY_GLOBAL_ID			(-16)
#define __L4_TCR_THREAD_WORD_0			(-17)
#define __L4_TCR_THREAD_WORD_1			(-18)
#define __L4_TCR_PLAT_TLS			(-19)


/*
 * Thread Control Registers.
 */

L4_INLINE L4_Word_t __L4_TCR_MyGlobalId (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_MY_GLOBAL_ID];
}

L4_INLINE L4_Word_t __L4_TCR_ProcessorNo (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_PROCESSOR_NO];
}

L4_INLINE L4_Word_t __L4_TCR_UserDefinedHandle (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_USER_DEFINED_HANDLE];
}

L4_INLINE void __L4_TCR_Set_UserDefinedHandle (L4_Word_t w)
{
    (__L4_X86_Utcb ())[__L4_TCR_USER_DEFINED_HANDLE] = w;
}

L4_INLINE L4_Word_t __L4_TCR_Pager (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_PAGER];
}

L4_INLINE void __L4_TCR_Set_Pager (L4_Word_t w)
{
    (__L4_X86_Utcb ())[__L4_TCR_PAGER] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ExceptionHandler (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_EXCEPTION_HANDLER];
}

L4_INLINE void __L4_TCR_Set_ExceptionHandler (L4_Word_t w)
{
    (__L4_X86_Utcb ())[__L4_TCR_EXCEPTION_HANDLER] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ErrorCode (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_ERROR_CODE];
}

L4_INLINE L4_Word_t __L4_TCR_IntendedReceiver(void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_INTENDED_RECEIVER];
}

L4_INLINE L4_Word_t __L4_TCR_ActualSender (void)
{
    return (__L4_X86_Utcb ())[__L4_TCR_VIRTUAL_ACTUAL_SENDER];
}

L4_INLINE void __L4_TCR_Set_VirtualSender (L4_Word_t w)
{
    (__L4_X86_Utcb ())[__L4_TCR_VIRTUAL_ACTUAL_SENDER] = w;
}

L4_INLINE L4_Word_t __L4_TCR_Acceptor( void )
{
    return (__L4_X86_Utcb ())[__L4_TCR_ACCEPTOR];
}

L4_INLINE void __L4_TCR_Set_Acceptor( L4_Word_t w )
{
    (__L4_X86_Utcb ())[__L4_TCR_ACCEPTOR] = w;
}

L4_INLINE L4_Word_t __L4_TCR_NotifyBits( void )
{
    return (__L4_X86_Utcb ())[__L4_TCR_NOTIFY_BITS];
}

L4_INLINE L4_Word_t __L4_TCR_NotifyMask( void )
{
    return (__L4_X86_Utcb ())[__L4_TCR_NOTIFY_MASK];
}

L4_INLINE void __L4_TCR_Set_NotifyMask( L4_Word_t w )
{
    (__L4_X86_Utcb ())[__L4_TCR_NOTIFY_MASK] = w;
}

L4_INLINE void __L4_TCR_Set_NotifyBits( L4_Word_t w )
{
    (__L4_X86_Utcb())[ __L4_TCR_NOTIFY_BITS ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadWord (L4_Word_t n)
{
    return (__L4_X86_Utcb ())[__L4_TCR_THREAD_WORD_0 - (int) n];
}

L4_INLINE void __L4_TCR_Set_ThreadWord (L4_Word_t n, L4_Word_t w)
{
    (__L4_X86_Utcb ())[__L4_TCR_THREAD_WORD_0 - (int) n] = w;
}

L4_INLINE void L4_Set_CopFlag (L4_Word_t n)
{
    __asm__ ("orl %0, %1"
	     :
	     :
	     "ir" (1 << (8 + n)),
	     "m" ((__L4_X86_Utcb ())[__L4_TCR_COP_FLAGS]));
}

L4_INLINE void L4_Clr_CopFlag (L4_Word_t n)
{
    __asm__ ("andl %0, %1"
	     :
	     :
	     "ir" (~(1 << (8 + n))),
	     "m" ((__L4_X86_Utcb ())[__L4_TCR_COP_FLAGS]));
}

L4_INLINE L4_Word_t L4_PreemptedIP( void )
{
    return (__L4_X86_Utcb())[ __L4_TCR_PREEMPTED_IP ];
}

L4_INLINE void L4_Set_PreemptCallbackIP( L4_Word_t ip )
{
    (__L4_X86_Utcb())[ __L4_TCR_PREEMPT_CALLBACK_IP] = ip;
}

L4_INLINE L4_Bool_t L4_EnablePreemptionCallback (void)
{
    L4_Word8_t retval = 0;

    __asm__ ("bts %1, %2; setc %0"
	     : "=r" (retval)
	     : "i" (5), "m" ((__L4_X86_Utcb ())[__L4_TCR_PREEMPT_FLAGS]));

    return (L4_Bool_t)retval;
}

L4_INLINE L4_Bool_t L4_DisablePreemptionCallback (void)
{
    L4_Word8_t retval = 0;

    __asm__ ("btr %1, %2; setc %0"
	     : "=r" (retval)
	     : "i" (5), "m" ((__L4_X86_Utcb ())[__L4_TCR_PREEMPT_FLAGS]));

    return (L4_Bool_t)retval;
}


/*
 * Message Registers.
 */

L4_INLINE void L4_StoreMR (int i, L4_Word_t * w)
{
    *w = (__L4_X86_Utcb ())[i];
}

L4_INLINE void L4_LoadMR (int i, L4_Word_t w)
{
    (__L4_X86_Utcb ())[i] = w;
}

L4_INLINE void L4_StoreMRs (int i, int k, L4_Word_t * w)
{
    L4_Word_t * mr = __L4_X86_Utcb () + i;

    while (k-- > 0)
	*w++ = *mr++;
}

L4_INLINE void L4_LoadMRs (int i, int k, L4_Word_t * w)
{
    L4_Word_t * mr = __L4_X86_Utcb () + i;

    while (k-- > 0)
	*mr++ = *w++;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadLocalStorage (void)
{
    return (__L4_X86_Utcb())[__L4_TCR_PLAT_TLS];
}

L4_INLINE void __L4_TCR_Set_ThreadLocalStorage(L4_Word_t w)
{
    (__L4_X86_Utcb())[__L4_TCR_PLAT_TLS] = w;
}

/*
 * Buffer Registers.
 */

L4_INLINE void L4_StoreBR (int i, L4_Word_t * w)
{
    *w = (__L4_X86_Utcb ())[-16 - i];
}

L4_INLINE void L4_LoadBR (int i, L4_Word_t w)
{
    (__L4_X86_Utcb ())[-16 - i] = w;
}

L4_INLINE void L4_StoreBRs (int i, int k, L4_Word_t * w)
{
    L4_Word_t * br = (__L4_X86_Utcb ()) - 16 - i;

    while (k-- > 0)
	*w++ = *br--;
}

L4_INLINE void L4_LoadBRs (int i, int k, L4_Word_t * w)
{
    L4_Word_t * br = (__L4_X86_Utcb ()) - 16 - i;

    while (k-- > 0)
	*br-- = *w++;
}


#endif /* !__L4__X86__VREGS_H__ */

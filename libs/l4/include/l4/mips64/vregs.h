/*********************************************************************
 *                
 * Copyright (C) 2002, 2003,   University of New South Wales
 *                
 * File path:     l4/mips64/vregs.h
 * Description:   Mips64 virtual register ABI
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
 * $Id: vregs.h,v 1.8 2004/04/28 03:04:36 cvansch Exp $
 *                
 ********************************************************************/

#ifndef __L4__MIPS64__VREGS_H__
#define __L4__MIPS64__VREGS_H__

#define __L4_NUM_MRS	64

/*
 * Location of TCRs within UTCB.
 */

/* Thread local storage */
#define __L4_TCR_PLAT_TLS			(__L4_TCR_PLATFORM_OFFSET + 0)
#define __L4_TCR_PLATFORM_OFFSET		(80)

#define __L4_TCR_MR_OFFSET		        (16)
#define __L4_TCR_THREAD_WORD1    		(15)
#define __L4_TCR_THREAD_WORD0    		(14)
#define __L4_TCR_VIRTUAL_ACTUAL_SENDER		(13)
#define __L4_TCR_INTENDED_RECEIVER		(12)
#define __L4_TCR_ERROR_CODE			(11)
#define __L4_TCR_USER_DEFINED_HANDLE		(10)
#define __L4_TCR_PREEMPTED_IP			(9)
#define __L4_TCR_PREEMPT_CALLBACK_IP		(8)
#define __L4_TCR_NOTIFY_BITS			(7)
#define __L4_TCR_NOTIFY_MASK			(6)
#define __L4_TCR_ACCEPTOR			(5)
#define __L4_TCR_COP_FLAGS			(4)
#define __L4_TCR_PREEMPT_FLAGS			(4)
#define __L4_TCR_EXCEPTION_HANDLER		(3)
#define __L4_TCR_PAGER				(2)
#define __L4_TCR_PROCESSOR_NO			(1)
#define __L4_TCR_MY_GLOBAL_ID			(0)

#if !defined(__ASSEMBLER__)

L4_INLINE L4_Word_t *__L4_Mips64_Utcb( void ) __attribute__ ((const));
L4_INLINE L4_Word_t *__L4_Mips64_Utcb( void )
{
    register L4_Word_t * utcb asm ("$26");	// k0
    return utcb;
}

typedef struct {
    L4_Word8_t	    PreemptFlags;
    L4_Word8_t	    CopFlags;
    L4_Word16_t	    __reserved0;
    L4_Word32_t	    __reserved1;
} UtcbParts;

/*
 * Thread Control Registers.
 */

L4_INLINE L4_Word_t __L4_TCR_MyGlobalId( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_MY_GLOBAL_ID ];
}

L4_INLINE L4_Word_t __L4_TCR_ProcessorNo( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_PROCESSOR_NO ];
}

L4_INLINE L4_Word_t __L4_TCR_UserDefinedHandle( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_USER_DEFINED_HANDLE ];
}

L4_INLINE void __L4_TCR_Set_UserDefinedHandle( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_USER_DEFINED_HANDLE ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_Pager( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_PAGER ];
}

L4_INLINE void __L4_TCR_Set_Pager( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_PAGER ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ExceptionHandler( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_EXCEPTION_HANDLER ];
}

L4_INLINE void __L4_TCR_Set_ExceptionHandler( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_EXCEPTION_HANDLER ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_Acceptor( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_ACCEPTOR ];
}

L4_INLINE void __L4_TCR_Set_Acceptor( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_ACCEPTOR ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_NotifyMask( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_NOTIFY_MASK ];
}

L4_INLINE L4_Word_t __L4_TCR_NotifyBits( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_NOTIFY_BITS ];
}

L4_INLINE void __L4_TCR_Set_NotifyMask( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_NOTIFY_MASK ] = w;
}

L4_INLINE void __L4_TCR_Set_NotifyBits( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_NOTIFY_BITS ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ErrorCode( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_ERROR_CODE ];
}

L4_INLINE L4_Word_t __L4_TCR_IntendedReceiver( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_INTENDED_RECEIVER ];
}

L4_INLINE L4_Word_t __L4_TCR_ActualSender( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_VIRTUAL_ACTUAL_SENDER ];
}

L4_INLINE void __L4_TCR_Set_VirtualSender( L4_Word_t w )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_VIRTUAL_ACTUAL_SENDER ] = w;
}

L4_INLINE L4_Word_t L4_PreemptedIP( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_PREEMPTED_IP];
}

L4_INLINE void L4_Set_PreemptCallbackIP( L4_Word_t ip )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_PREEMPT_CALLBACK_IP] = ip;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadWord (L4_Word_t n)
{
    return (__L4_Mips64_Utcb ())[__L4_TCR_THREAD_WORD0 + (int) n];
}

L4_INLINE void __L4_TCR_Set_ThreadWord (L4_Word_t n, L4_Word_t w)
{
    (__L4_Mips64_Utcb ())[__L4_TCR_THREAD_WORD0 + (int) n] = w;
}

#define COP_FLAGS   ((UtcbParts *)&(__L4_Mips64_Utcb())[ __L4_TCR_COP_FLAGS ])->CopFlags

L4_INLINE void L4_Set_CopFlag( L4_Word_t n )
{
    COP_FLAGS |= (1 << n);
}

L4_INLINE void L4_Clr_CopFlag( L4_Word_t n )
{
    COP_FLAGS &= ~(1 << n);
}

#define PREEMPT_FLAGS	((UtcbParts *)&(__L4_Mips64_Utcb())[ __L4_TCR_PREEMPT_FLAGS ])->PreemptFlags

L4_INLINE L4_Bool_t L4_EnablePreemptionCallback( void )
{
    L4_Bool_t old = (PREEMPT_FLAGS >> 5) & 1;
    PREEMPT_FLAGS |= (1 << 5);
    return old;
}

L4_INLINE L4_Bool_t L4_DisablePreemptionCallback( void )
{
    L4_Bool_t old = (PREEMPT_FLAGS >> 5) & 1;
    PREEMPT_FLAGS &= ~(1 << 5);
    return old;
}

L4_INLINE L4_Bool_t L4_EnablePreemption( void )
{
    L4_Bool_t old = (PREEMPT_FLAGS >> 6) & 1;
    PREEMPT_FLAGS |= (1 << 6);
    return old;
}

L4_INLINE L4_Bool_t L4_DisablePreemption( void )
{
    L4_Bool_t old = (PREEMPT_FLAGS >> 6) & 1;
    PREEMPT_FLAGS &= ~(1 << 6);
    return old;
}

L4_INLINE L4_Bool_t L4_PreemptionPending( void )
{
    L4_Bool_t retval = (PREEMPT_FLAGS >> 7) & 1;
    return retval;
}


/*
 * Message Registers.
 */

L4_INLINE void L4_StoreMR( int i, L4_Word_t * w )
{
    *w = (__L4_Mips64_Utcb())[__L4_TCR_MR_OFFSET +  i ];
}

L4_INLINE void L4_LoadMR( int i, L4_Word_t w )
{
    (__L4_Mips64_Utcb())[__L4_TCR_MR_OFFSET + i ] = w;
}

L4_INLINE void L4_StoreMRs( int i, int k, L4_Word_t * w )
{
    L4_Word_t * mr = &(__L4_Mips64_Utcb())[__L4_TCR_MR_OFFSET + i];

    while( k-- > 0 )
	*w++ = *mr++;
}

L4_INLINE void L4_LoadMRs( int i, int k, L4_Word_t * w )
{
    L4_Word_t * mr = &(__L4_Mips64_Utcb())[__L4_TCR_MR_OFFSET + i];

    while( k-- > 0 )
	*mr++ = *w++;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadLocalStorage ( void )
{
    return (__L4_Mips64_Utcb())[ __L4_TCR_PLAT_TLS ];
}

L4_INLINE void __L4_TCR_Set_ThreadLocalStorage ( L4_Word_t tls )
{
    (__L4_Mips64_Utcb())[ __L4_TCR_PLAT_TLS ] = tls;
}

#endif

#endif	/* __L4__MIPS64__VREGS_H__ */


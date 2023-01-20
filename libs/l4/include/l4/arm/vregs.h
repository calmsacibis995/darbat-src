/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2003-2004 National ICT Australia
 * 
 * All rights reserved. 
 * 
 * Developed by: Embedded, Real-time and Operating Systems Program (ERTOS)
 *               National ICT Australia
 *               http://www.ertos.nicta.com.au
 * 
 * Permission is granted by National ICT Australia, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of National ICT Australia, nor the names of its
 *       contributors, may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
 * PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
 * NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
 * WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
 * REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
 * THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
 * ERRORS, WHETHER OR NOT DISCOVERABLE.
 * 
 * TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
 * NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
 * THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
 * LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
 * OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
 * OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
 * OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
 * CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
 * CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
 * CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
 * DAMAGES OR OTHER LIABILITY.
 * 
 * If applicable legislation implies representations, warranties, or
 * conditions, or imposes obligations or liability on National ICT
 * Australia or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of National ICT Australia or the contributor is limited, to
 * the full extent permitted by the applicable legislation, at its
 * option, to:
 * a.  in the case of goods, any one or more of the following:
 * i.  the replacement of the goods or the supply of equivalent goods;
 * ii.  the repair of the goods;
 * iii. the payment of the cost of replacing the goods or of acquiring
 *  equivalent goods;
 * iv.  the payment of the cost of having the goods repaired; or
 * b.  in the case of services:
 * i.  the supplying of the services again; or
 * ii.  the payment of the cost of having the services supplied again.
 * 
 * The construction, validity and performance of this licence is governed
 * by the laws in force in New South Wales, Australia.
 */
#ifndef __L4__ARM__VREGS_H__
#define __L4__ARM__VREGS_H__

#define L4_TRAP_KPUTC		0xffffffa0
#define L4_TRAP_KGETC		0xffffffa4
#define L4_TRAP_KGETC_NB	0xffffffa8
#define L4_TRAP_KDEBUG		0xffffffac
#define L4_TRAP_GETUTCB		0xffffffb0
#define L4_TRAP_KIP		0xffffffb4
#define L4_TRAP_KSET_THRD_NAME	0xffffffb8
#define L4_TRAP_GETCOUNTER	0xffffffbc
#define L4_TRAP_GETNUMTPS       0xffffffc0
#define L4_TRAP_GETTPNAME       0xffffffc4
#define L4_TRAP_TCCTRL          0xffffffc8

#define L4_TRAP_PMU_RESET       0xffffffcc
#define L4_TRAP_PMU_STOP        0xffffffd0
#define L4_TRAP_PMU_READ        0xffffffd4
#define L4_TRAP_PMU_CONFIG      0xffffffd8

#define USER_UTCB_REF           0xff000ff0

#define __L4_NUM_MRS	32

/*
 * Location of TCRs within UTCB.
 * Note: Keep vregs_asm.h up to date with these below
 */

#define __L4_TCR_USER_NUM			(10)
#define __L4_TCR_USER_OFFSET			(54)	/* 54..63 */
#define __L4_TCR_PLATFORM_NUM			(6)
/* Thread local storage */
#define __L4_TCR_PLAT_TLS			(__L4_TCR_PLATFORM_OFFSET + 0)
#define __L4_TCR_PLATFORM_OFFSET		(48)	/* 48..53 */

#define __L4_TCR_MR_OFFSET		        (16)

#define __L4_TCR_KERNEL_RESERVED1		(15)	/* __L4_TCR_IDL4_RESTORE_COUNT */
#define __L4_TCR_KERNEL_RESERVED0		(14)

#define __L4_TCR_PREEMPTED_IP			(13)
#define __L4_TCR_PREEMPT_CALLBACK_IP		(12)
#define __L4_TCR_VIRTUAL_ACTUAL_SENDER		(11)
#define __L4_TCR_INTENDED_RECEIVER		(10)
#define __L4_TCR_ERROR_CODE			(9)
#define __L4_TCR_PROCESSOR_NO			(8)
#define __L4_TCR_NOTIFY_BITS			(7)
#define __L4_TCR_NOTIFY_MASK			(6)
#define __L4_TCR_ACCEPTOR			(5)
#define __L4_TCR_COP_FLAGS			(4)
#define __L4_TCR_PREEMPT_FLAGS			(4)
#define __L4_TCR_EXCEPTION_HANDLER		(3)
#define __L4_TCR_PAGER				(2)
#define __L4_TCR_USER_DEFINED_HANDLE		(1)
#define __L4_TCR_MY_GLOBAL_ID			(0)

#if !defined(__ASSEMBLER__)
 
L4_INLINE L4_Word_t *__L4_ARM_Utcb( void ) __attribute__ ((const));
L4_INLINE L4_Word_t *__L4_ARM_Utcb( void )
{
    return *(L4_Word_t **)(USER_UTCB_REF);
}

/*
 * Thread Control Registers.
 */

L4_INLINE L4_Word_t __L4_TCR_MyGlobalId( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_MY_GLOBAL_ID ];
}

L4_INLINE L4_Word_t __L4_TCR_ProcessorNo( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_PROCESSOR_NO ];
}

L4_INLINE L4_Word_t __L4_TCR_UserDefinedHandle( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_USER_DEFINED_HANDLE ];
}

L4_INLINE void __L4_TCR_Set_UserDefinedHandle( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_USER_DEFINED_HANDLE ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_Pager( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_PAGER ];
}

L4_INLINE void __L4_TCR_Set_Pager( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_PAGER ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ExceptionHandler( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_EXCEPTION_HANDLER ];
}

L4_INLINE void __L4_TCR_Set_ExceptionHandler( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_EXCEPTION_HANDLER ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ErrorCode( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_ERROR_CODE ];
}

L4_INLINE L4_Word_t __L4_TCR_IntendedReceiver( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_INTENDED_RECEIVER ];
}

L4_INLINE L4_Word_t __L4_TCR_Acceptor( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_ACCEPTOR ];
}

L4_INLINE void __L4_TCR_Set_Acceptor( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_ACCEPTOR ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_NotifyMask( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_NOTIFY_MASK ];
}

L4_INLINE L4_Word_t __L4_TCR_NotifyBits( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_NOTIFY_BITS ];
}

L4_INLINE void __L4_TCR_Set_NotifyMask( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_NOTIFY_MASK ] = w;
}

L4_INLINE void __L4_TCR_Set_NotifyBits( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_NOTIFY_BITS ] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ActualSender( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_VIRTUAL_ACTUAL_SENDER ];
}

L4_INLINE void __L4_TCR_Set_VirtualSender( L4_Word_t w )
{
    (__L4_ARM_Utcb())[ __L4_TCR_VIRTUAL_ACTUAL_SENDER ] = w;
}

L4_INLINE void L4_Set_CopFlag( L4_Word_t n )
{
    (__L4_ARM_Utcb())[ __L4_TCR_COP_FLAGS ] |= (1 << n);
}

L4_INLINE void L4_Clr_CopFlag( L4_Word_t n )
{
    (__L4_ARM_Utcb())[ __L4_TCR_COP_FLAGS ] &= ~(1 << n);
}

L4_INLINE L4_Word_t L4_PreemptedIP( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_PREEMPTED_IP ];
}

L4_INLINE void L4_Set_PreemptCallbackIP( L4_Word_t ip )
{
    (__L4_ARM_Utcb())[ __L4_TCR_PREEMPT_CALLBACK_IP] = ip;
}

L4_INLINE L4_Bool_t L4_EnablePreemptionCallback( void )
{
    L4_Bool_t old = ((__L4_ARM_Utcb())[ __L4_TCR_PREEMPT_FLAGS ] >> 5) & 1;
    (__L4_ARM_Utcb())[ __L4_TCR_PREEMPT_FLAGS ] |= (1 << 5);
    return old;
}

L4_INLINE L4_Bool_t L4_DisablePreemptionCallback( void )
{
    L4_Bool_t old = ((__L4_ARM_Utcb())[ __L4_TCR_PREEMPT_FLAGS ] >> 5) & 1;
    (__L4_ARM_Utcb())[ __L4_TCR_PREEMPT_FLAGS ] &= ~(1 << 5);
    return old;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadWord (L4_Word_t n)
{
    return (__L4_ARM_Utcb ())[__L4_TCR_USER_OFFSET + (int) n];
}

L4_INLINE void __L4_TCR_Set_ThreadWord (L4_Word_t n, L4_Word_t w)
{
    (__L4_ARM_Utcb ())[__L4_TCR_USER_OFFSET + (int) n] = w;
}

L4_INLINE L4_Word_t __L4_TCR_ThreadLocalStorage ( void )
{
    return (__L4_ARM_Utcb())[ __L4_TCR_PLAT_TLS ];
}

L4_INLINE void __L4_TCR_Set_ThreadLocalStorage ( L4_Word_t tls )
{
    (__L4_ARM_Utcb())[ __L4_TCR_PLAT_TLS ] = tls;
}


/*
 * Message Registers.
 */

L4_INLINE void L4_StoreMR( int i, L4_Word_t * w )
{
    *w = (__L4_ARM_Utcb())[__L4_TCR_MR_OFFSET +  i ];
}

L4_INLINE void L4_LoadMR( int i, L4_Word_t w )
{
    (__L4_ARM_Utcb())[__L4_TCR_MR_OFFSET + i ] = w;
}

L4_INLINE void L4_StoreMRs( int i, int k, L4_Word_t * w )
{
    L4_Word_t * mr = &(__L4_ARM_Utcb())[__L4_TCR_MR_OFFSET + i];

    while( k-- > 0 ) {
	*w++ = *mr++;
    }
}

L4_INLINE void L4_LoadMRs( int i, int k, L4_Word_t * w )
{
    L4_Word_t * mr = &(__L4_ARM_Utcb())[__L4_TCR_MR_OFFSET + i];

    while( k-- > 0 )
	*mr++ = *w++;
}

#endif

#endif	/* __L4__ARM__VREGS_H__ */


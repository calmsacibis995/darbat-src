/*********************************************************************
 *                
 * Copyright (C) 2004,  National ICT Australia (NICTA)
 *                
 * File path:     arch/arm/omap1510/syscon.h
 * Description:   TI OMAP1510 coprocessor-15 definitions
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
 * $Id: syscon.h,v 1.1 2004/08/12 10:58:53 cvansch Exp $
 *                
 ********************************************************************/


#ifndef _ARCH_ARM_SA1100_SYSCON_H_
#define _ARCH_ARM_SA1100_SYSCON_H_

/* Coprocessor 15 */
#define CP15			p15

/* Primary CP15 registers (CRn) */
#define C15_id			c0
#define C15_control		c1
#define C15_ttbase		c2
#define C15_domain		c3
#define C15_fault_status	c5
#define C15_fault_addr		c6
#define C15_cache_con		c7
#define C15_tlb			c8
#define C15_read_buf		c9
#define C15_pid			c13
#define C15_breakpoints		c14
#define C15_function		c15

/* Default secondary register (CRm) */
#define C15_CRm_default		c0
/* Default opcode2 register (opcode2) */
#define C15_OP2_default		0

/* CP15 - Control Register */
#define C15_CONTROL_FIXED	0x0070
#define C15_CONTROL_M		0x0001			/* Memory management enable	*/
#define C15_CONTROL_A		0x0002			/* Alignment fault enable	*/
#define C15_CONTROL_C		0x0004			/* Data cache enable		*/
#define C15_CONTROL_B		0x0080			/* Big endian enable		*/
#define C15_CONTROL_S		0x0100			/* System access checks in MMU	*/
#define C15_CONTROL_R		0x0200			/* ROM access checks in MMU	*/
#define C15_CONTROL_I		0x1000			/* Instruction cache enable	*/
#define C15_CONTROL_X		0x2000			/* Remap interrupt vector	*/
#define C15_CONTROL_RR		0x4000			/* Round Robin Replacement	*/
#define C15_CONTROL_CK_FB	0x00000000		/* Clocking: Fast Bus		*/
#define C15_CONTROL_CK_Sync	0x40000000		/* Clocking: Synchronous	*/
#define C15_CONTROL_CK_ASync	0xc0000000		/* Clocking: Asynchronous	*/

/* Default to little endian */
#define C15_CONTROL_INIT	(C15_CONTROL_FIXED)
/* Kernel mode - little endian, cached, write buffer, remap to 0xffff0000 */
#define C15_CONTROL_KERNEL	(C15_CONTROL_FIXED | C15_CONTROL_M | C15_CONTROL_C | \
				 C15_CONTROL_S | C15_CONTROL_I | C15_CONTROL_X | C15_CONTROL_CK_FB)

#if !defined(ASSEMBLY)

#define _INS_(x) #x
#define STR(x) _INS_(x)

/* Read from coprocessor 15 register */
#define read_cp15_register(CRn, CRm, op2)	\
({ word_t _read;				\
    __asm__ __volatile__ (			\
    "mrc    p15, 0, %0,"STR(CRn)",			\
    "STR(CRm)","STR(op2)";\n"			\
    : "=r" (_read));				\
    _read;})

/* Write to coprocessor 15 register */
#define write_cp15_register(CRn, CRm, op2, val)	\
    __asm__ __volatile__ (			\
    "mcr    p15, 0, %0,"STR(CRn)",			\
    "STR(CRm)","STR(op2)";\n"			\
    :: "r" (val));				\

#endif

#define CPWAIT

#endif /*_ARCH_ARM_SA1100_SYSCON_H_*/

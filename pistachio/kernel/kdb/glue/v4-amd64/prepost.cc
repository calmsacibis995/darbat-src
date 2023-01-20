/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     kdb/glue/v4-amd64/prepost.cc
 * Description:   X86-64 specific handlers for KDB entry and exit
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
 * $Id: 
 *                
 ********************************************************************/

#include <debug.h>
#include <kdb/kdb.h>
#include <kdb/console.h>

#include <debug.h>
#include <linear_ptab.h>
#include INC_API(tcb.h)

#include INC_ARCH(traps.h)	/* for X86-64 exception numbers	*/
#include INC_ARCH(trapgate.h)	/* for amd64_exceptionframe_t	*/
#include INC_PLAT(nmi.h)	/* for nmi_t			*/

extern "C" int disas(addr_t pc);


bool SECTION(SEC_KDEBUG) kdb_t::pre() {

    amd64_exceptionframe_t* f = (amd64_exceptionframe_t*) kdb_param;

    switch (f->reason)
    {
    case AMD64_EXC_DEBUG:	/* single step, hw breakpoints */
	printf("--- Breakpoint ---\n");
	printf("Addr=%16x, Dumping frame:\n", f->rip);
	printf("\tRAX %16x", f->rax);
	printf("\t R8 %16x\n", f->r8 );
	printf("\tRCX %16x", f->rcx);
	printf("\t R9 %16x\n", f->r9 );
	printf("\tRDX %16x", f->rdx);
	printf("\tR10 %16x\n", f->r10);
	printf("\tRBX %16x", f->rbx);
	printf("\tR11 %16x\n", f->r11);
	printf("\tRSP %16x", f->rsp);
	printf("\tR12 %16x\n", f->r12);
	printf("\tRBP %16x", f->rbp);
	printf("\tR13 %16x\n", f->r13);
	printf("\tRSI %16x", f->rsi);
	printf("\tR14 %16x\n", f->r14);
	printf("\tRDI %16x", f->rdi);
	printf("\tR15 %16x\n", f->r15);
	printf("\tRIP %16x\n", f->rip);
	printf("\tERR %16x", f->error);
	printf("\tRFL %16x\n", f->rflags);
	printf("\t CS %16x", f->cs);
	printf("\t SS %16x\n", f->ss);	    
	if (f->rflags & (1 << 8))
	{
#if defined(CONFIG_KDB_DISAS)
	    disas((addr_t) f->rip);
	    printf("\n");
#endif
	    f->rflags &= ~(1 << 8);
	}

	break;


    case AMD64_EXC_NMI:		/* well, the name says enough	*/
	printf("--- NMI ---\n");
	break;
	
    case AMD64_EXC_BREAKPOINT: /* int3 */
    {
	space_t * space = kdb.kdb_current->get_space();
	if (!space) space = get_kernel_space();
	
	addr_t addr = (addr_t)(f->rip);
	
	unsigned char c;
	if (! readmem(space, addr, &c) )
	    break;
	
	bool enter_kernel_debugger = true;

	if (c == 0x90)
	{
	    addr = addr_offset(addr, 1);
	    enter_kernel_debugger = false;
	}
	
	if (!readmem(space, addr, &c) )
	    break;
	
	if (c == 0xeb)
	{
	    /* jmp rel */
	    if ((u16_t) space->get_from_user(addr_offset(addr, 2)) == 0xc748)
	    {
		/* movq addr32, %rax */
		s64_t user_addr = (s64_t) (s32_t) (space->get_from_user(addr_offset(addr, 5)));
		
		printf("--- \"%s\" ---\n"
		       "--------------------------------- (rip=%8p, rsp=%8p) ---\n", 
		       user_addr, f->rip - 1, f->rsp);
		
	    }
	    if ( (u8_t) space->get_from_user(addr_offset(addr, 2)) == 0xb8){
		/* movq addr64, %rax */
		addr_t user_addr = (addr_t *) space->get_from_user(addr_offset(addr, 3)) ;
		printf("--- \"%s\" ---\n"
		       "--------------------------------- (rip=%p, rsp=%p) ---\n", 
		       user_addr, f->rip - 1, f->rsp);
	    }
	}
	else if (c == 0x3c)
	{
	    // putc / getc
	    if (!readmem (space, addr_offset(addr, 1), &c))
		break;
	    switch(c)
	    {
	    case 0x0:
		putc(f->rax); return false;
	    case 0xd:
	    	f->rax = getc(); return false;
	    default:
		printf("kdb: unknown opcode: int3, cmpb %d\n", space->get_from_user(addr_offset(addr, 1)));
	    }
	}
	else
	    printf("%x, %x\n", space->get_from_user(addr), space->get_from_user(addr_offset(addr, 1)));

	return enter_kernel_debugger;

    }; break;

    default:
	printf("--- KD# unknown reason ---\n");
	break;
    } /* switch */

    return true;
};




void SECTION(SEC_KDEBUG) kdb_t::post() {

    amd64_exceptionframe_t* f = (amd64_exceptionframe_t*) kdb_param;
    switch (f->reason)
    {
    case AMD64_EXC_DEBUG:
	/* Set RF in RFLAGS. This will disable breakpoints for one
	   instruction. The processor will reset it afterwards. */
	f->rflags |= (1 << 16);
	break;

    case AMD64_EXC_NMI:
	nmi_t().unmask();
	break;

    } /* switch */
    return;
};

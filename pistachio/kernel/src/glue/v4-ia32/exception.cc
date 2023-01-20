/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-ia32/exception.cc
 * Description:   exception handling
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
 * $Id: exception.cc,v 1.35 2004/12/09 01:20:56 cvansch Exp $
 *                
 ********************************************************************/

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <kdb/tracepoints.h>
#include INC_ARCH(traps.h)
#include INC_ARCH(trapgate.h)
#include INC_API(tcb.h)
#include INC_API(space.h)
#include INC_API(kernelinterface.h)

DECLARE_TRACEPOINT (IA32_GP);
DECLARE_TRACEPOINT (IA32_UD);
DECLARE_TRACEPOINT (IA32_NOMATH);
DECLARE_TRACEPOINT (IA32_SEGRELOAD);
DECLARE_TRACEPOINT (EXCEPTION_IPC);

static bool send_exception_ipc(ia32_exceptionframe_t * frame, word_t exception)
{
    tcb_t * current = get_current_tcb();
//    if (current->get_exception_handler().is_nilthread())
//	return false;
/*#warning HACK*/
    if( current->get_scheduler().is_nilthread() )
	return false;

    TRACEPOINT_TB (EXCEPTION_IPC,
		   printf ("exception ipc at %x, %T (%p) -> %T \n", frame->eip, current->get_global_id().get_raw(),
		       current, current->get_scheduler().get_raw()),
		   "exception_ipc at %x (current=%p)", frame->eip, (u32_t)current);

    /* setup exception IPC */
    word_t saved_mr[13];
    msg_tag_t tag;

    // save message registers 
    for (int i = 0; i < 13; i++)
	saved_mr[i] = current->get_mr(i);
    acceptor_t saved_acceptor = current->get_acceptor();
    current->set_saved_partner (current->get_partner());
    current->set_saved_state (current->get_state());

    tag.set(0, 12, -5 << 4, true, true);
    current->set_mr(0, tag.raw);
    current->set_mr(1, frame->eip);
    current->set_mr(2, frame->eflags);
    current->set_mr(3, exception);
    current->set_mr(4, frame->error);
    current->set_mr(5, frame->edi);
    current->set_mr(6, frame->esi);
    current->set_mr(7, frame->ebp);
    current->set_mr(8, frame->esp);
    current->set_mr(9, frame->ebx);
    current->set_mr(10, frame->edx);
    current->set_mr(11, frame->ecx);
    current->set_mr(12, frame->eax);

//    tag = current->do_ipc(current->get_exception_handler(), 
//	current->get_exception_handler(), 
//	timeout_t::never());
/*#warning HACK */
    tag = current->do_ipc(current->get_scheduler(),
            current->get_scheduler());

    if (!tag.is_error())
    {
	frame->eip = current->get_mr(1);
	current->set_user_flags(current->get_mr(2));
	frame->edi = current->get_mr(5);
	frame->esi = current->get_mr(6);
	frame->ebp = current->get_mr(7);
	frame->esp = current->get_mr(8);
	frame->ebx = current->get_mr(9);
	frame->edx = current->get_mr(10);
	frame->ecx = current->get_mr(11);
	frame->eax = current->get_mr(12);
    }
    else
    {
	enter_kdebug("exception delivery error");
    }

    for (int i = 0; i < 13; i++)
	current->set_mr(i, saved_mr[i]);
    current->set_acceptor(saved_acceptor);
    current->set_partner(current->get_saved_partner ());
    current->set_saved_partner (NILTHREAD);
    current->set_state (current->get_saved_state ());
    current->set_saved_state (thread_state_t::aborted);

    return !tag.is_error();
}


static inline u8_t read_data (space_t * s, addr_t a)
{
    if (s->is_user_area (a))
	return s->get_from_user (a);
    else
	return *(u8_t *) a;
}

/**
 * Try handling the faulting instruction by decoding the instruction
 * stream.  If we are able to handle the fault in the kernel (e.g., by
 * reloading segment registers), we do so without involving the
 * user-level exception handler.
 *
 * @param frame		exception frame
 *
 * @return true if kernel handled the fault, false otherwise
 */
static bool handle_faulting_instruction (ia32_exceptionframe_t * frame)
{
    tcb_t * current = get_current_tcb ();
    space_t * space = current->get_space ();
    addr_t instr = (addr_t) frame->eip;
    u8_t i0;

    switch (i0 = read_data (space, instr))
    {
#if defined(CONFIG_IA32_SMALL_SPACES)
    case 0xcf:
    {
	/*
	 * CF		iret
	 *
	 * When returning to user-level the instruction pointer
	 * might happen to be outside the small space.  If so, we
	 * must promote the space to a large one.
	 */
	if (! space->is_user_area (instr) &&
	    space->is_small () &&
	    (word_t) current->get_user_ip () > space->smallid ()->size ())
	{
	    space->make_large ();
	    return true;
	}
	break;
    }
#endif
    
    case 0x0f: /* two-byte instruction prefix */
    {
	switch( read_data( space, addr_offset(instr, 1)) )
	{
	case 0x30:
    	    /* wrmsr */
	    if ( is_privileged_space(space) ) {
		ia32_wrmsr (frame->ecx, ((u64_t)(frame->eax)) | 
			((u64_t)(frame->edx)) << 32);
		frame->eip += 2;
		return true;
	    } break;

	case 0x32:
	    /* rdmsr */
	    if ( is_privileged_space(space) ) {
		u64_t val = ia32_rdmsr (frame->ecx);
		frame->eax = (u32_t)val;
		frame->edx = (u32_t)(val >> 32);
		frame->eip += 2;
		return true;
	    } break;
	    
	case 0xa1:
	case 0xa9:
	    goto pop_seg;
	}
	break;
    } /* two-byte prefix */

    case 0x8e:
    case 0x07:
    case 0x17:
    case 0x1f:
    pop_seg:
	/*
	 * 8E /r	mov %reg, %segreg
	 * 07		pop %es
	 * 17		pop %ss
	 * 1F		pop %ds
	 * 0F A1	pop %fs
	 * 0F A9	pop %gs
	 *
	 * Segment descriptor is being written with an invalid value.
	 * Reset all descriptors with the correct value and skip the
	 * instruction.
	 */

	if (! space->is_user_area (instr))
	    // Assume that kernel knows what it is doing.
	    break;

	TRACEPOINT (IA32_SEGRELOAD);
	reload_user_segregs ();
	frame->ds = frame->es = IA32_UDS;
	frame->eip++;
	if (i0 == 0x8e || i0 == 0x0f)
	    frame->eip++;
	return true;
    }

#if defined(CONFIG_IA32_SMALL_SPACES)
    /*
     * A GP(0) or SS(0) might indicate that a small address space
     * tries to access memory outside of the small space boundary.
     * Try to promote space to a large one instead of sending
     * exception IPC.
     */
    if ((frame->reason == IA32_EXC_STACKSEG_FAULT ||
	 frame->reason == IA32_EXC_GENERAL_PROTECTION) &&
	frame->error == 0 && space->is_small ())
    {
	space->make_large ();
	return true;
    }
#endif

    return false;
}


IA32_EXC_NO_ERRORCODE(exc_catch, -1)
{
    printf("exception caught\n");
#if defined(CONFIG_DEBUG)
    /*
     * Instead of spinning, perhaps we could do some useful work, like
     * calling kdebug.
     */
     enter_kdebug("exception caught");
#else
    while(1);
#endif
}

IA32_EXC_NO_ERRORCODE(exc_invalid_opcode, IA32_EXC_INVALIDOPCODE)
{
    tcb_t * current = get_current_tcb();
    space_t * space = current->get_space();
    addr_t addr = (addr_t)frame->eip;

    TRACEPOINT_TB (IA32_UD,
	    printf ("%t: invalid opcode at IP %p\n", current, addr),
	    "ia32_ud at %x (current=%x)", (u32_t)addr, (u32_t)current);

    /* instruction emulation, only in user area! */
    if (space->is_user_area(addr))
    {
	switch(space->get_from_user(addr))
	{
	case 0xf0: /* lock prefix */
	    if (space->get_from_user(addr_offset(addr, 1)) == 0x90)
	    {
		/* lock; nop */
		frame->eax = (u32_t)space->get_kip_page_area().get_base();
		frame->ecx = get_kip()->api_version;
		frame->edx = get_kip()->api_flags;
		frame->esi = get_kip()->get_kernel_descriptor()->kernel_id.get_raw();
		frame->eip+= 2;
		return;
	    }
	default:
	    printf("invalid opcode  at IP %p\n", addr);
	    enter_kdebug("invalid opcode");
	}
    }

    if (send_exception_ipc(frame, IA32_EXC_INVALIDOPCODE))
	return;
    
    get_current_tcb()->set_state(thread_state_t::halted);
    get_current_tcb()->switch_to_idle();
}


extern "C" void sysexit_tramp (void);
extern "C" void sysexit_tramp_end (void);
extern "C" void reenter_sysexit (void);

IA32_EXC_WITH_ERRORCODE(exc_gp, IA32_EXC_GENERAL_PROTECTION)
{
    kdebug_check_breakin();
#if defined(CONFIG_IA32_SMALL_SPACES) && defined(CONFIG_IA32_SYSENTER)
    /*
     * Check if we caught an exception in the sysexit trampoline.
     */
    tcb_t * current = get_current_tcb ();
    addr_t user_eip = current->get_user_ip ();

    if (user_eip >= (addr_t) sysexit_tramp &&
	user_eip <  (addr_t) sysexit_tramp_end &&
	current->get_space ()->is_small ())
    {
	/*
	 * If we faulted at the LRET instruction or otherwise was
	 * interrupted during the sysexit trampoline (i.e., still in
	 * user level) we must IRET to the kernel due to the user
	 * space code segment limitation.  We must also disable
	 * interrupts since we can not be allowed to be preempted in
	 * the reenter-trampoline.
	 */
	frame->cs = IA32_KCS;
	frame->eflags &= ~IA32_EFL_IF;
	frame->ecx = (word_t) current->get_user_sp ();
	frame->eip = (word_t) reenter_sysexit;
	return;
    }
#endif

    /*
     * A GP(0) could mean that we have a segment register with zero
     * contents.  If so, just reload all segment register selectors
     * with appropriate values.
     */

    if (frame->error == 0)
    {
	word_t fs, gs;
	asm ("	mov	%%fs, %w0	\n"
	     "	mov	%%gs, %w1	\n"
	     :"=r"(fs), "=r"(gs));

	if ((frame->ds & 0xffff) == 0 || (frame->es & 0xffff) == 0 ||
	    fs == 0 || gs == 0 )
	{
	    TRACEPOINT (IA32_SEGRELOAD);
	    reload_user_segregs ();
	    frame->ds = frame->es =
		(frame->cs & 0xffff) == IA32_UCS ? IA32_UDS : IA32_KDS;
	    return;
	}
    }


    /*
     * In some cases we handle the faulting instruction without
     * involving the user-level exception handler.
     */
    if (handle_faulting_instruction (frame))
	return;

    TRACEPOINT_TB (IA32_GP,
		   printf ("general protection fault @ %p, error: %x\n", 
			   frame->eip, frame->error),
		   "ia32_gp at %x (error=%d)",
		   frame->eip, frame->error);

    if (send_exception_ipc(frame, IA32_EXC_GENERAL_PROTECTION))
	return;

#ifdef CONFIG_KDB
    void ia32_dump_frame (ia32_exceptionframe_t * frame);
    ia32_dump_frame (frame);

    enter_kdebug("#GP");
#endif

    get_current_tcb()->set_state(thread_state_t::halted);
    get_current_tcb()->switch_to_idle();
}

IA32_EXC_NO_ERRORCODE(exc_nomath_coproc, IA32_EXC_NOMATH_COPROC)
{
    tcb_t * current = get_current_tcb();

    TRACEPOINT(IA32_NOMATH, 
        printf("IA32_NOMATH %t @ %p\n", current, frame->eip));

    current->resources.ia32_no_math_exception(current);
}

IA32_EXC_NO_ERRORCODE(exc_fpu_fault, IA32_EXC_FPU_FAULT)
{
    printf("fpu fault exception @ %p", frame->eip);

    if (send_exception_ipc(frame, IA32_EXC_FPU_FAULT))
	return;
    
    get_current_tcb()->set_state(thread_state_t::halted);
    get_current_tcb()->switch_to_idle();
}

IA32_EXC_NO_ERRORCODE(exc_simd_fault, IA32_EXC_SIMD_FAULT)
{
    printf("simd fault exception @ %p", frame->eip);

    if (send_exception_ipc(frame, IA32_EXC_SIMD_FAULT))
	return;
    
    get_current_tcb()->set_state(thread_state_t::halted);
    get_current_tcb()->switch_to_idle();
}



u64_t exc_catch_all[IDT_SIZE] UNIT("ia32.exc_all");

extern "C" void exc_catch_common_handler(ia32_exceptionframe_t *frame){

    word_t irq  = (frame->error - 5 - (word_t) exc_catch_all) / 8;
    printf("Invalid jump to IDT entry no %d - bogus interrupt?\n", irq);
    enter_kdebug("Invalid IDT jump");
}

void exc_catch_common_wrapper() 
{							
    __asm__ (						
#ifdef __ELF__
        ".section .data.ia32.exc_common		\n"
	".global exc_catch_common		\n"
	"\t.type exc_catch_common,@function	\n"
#elif defined (__APPLE_CC__)
	".globl exc_catch_common		\n"
#else
#error "unknown compiler"
#endif
	"exc_catch_common:			\n"
	"pusha					\n"
	"push	%%ds				\n"
	"push	%%es				\n"
	"push	%0				\n"
	"push	%%esp				\n"
#ifdef __ELF__
	"call  exc_catch_common_handler		\n"		
#elif defined(__APPLE_CC__)
	"call  _exc_catch_common_handler	\n"		
#else
#error "unknown compiler"
#endif
	"addl  $8, %%esp			\n"		
	"popl	%%es				\n"
	"popl	%%ds				\n"
	"popa					\n"
	"addl	$4, %%esp			\n"
	"iret					\n"		
#ifdef __ELF__
	".previous				\n"
#endif
	:						
	: "i"(0)					
	);						
}							

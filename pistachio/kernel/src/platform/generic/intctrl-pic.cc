/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     platform/generic/intctrl-pic.cc
 * Description:   Implementation of class handling the PIC cascade in
 *                standard PCs
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
 * $Id: intctrl-pic.cc,v 1.1 2004/03/01 16:54:49 stoess Exp $
 *                
 ********************************************************************/

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include INC_API(interrupt.h)
#include INC_GLUE(hwirq.h)
#include INC_GLUE(idt.h)
#include INC_ARCH(trapgate.h)

void handle_interrupt(word_t irq);

/* the global interrupt controller */
intctrl_t intctrl;

HW_IRQ( 0);
HW_IRQ( 1);
HW_IRQ( 2);
HW_IRQ( 3);
HW_IRQ( 4);
HW_IRQ( 5);
HW_IRQ( 6);
HW_IRQ( 7);
HW_IRQ( 8);
HW_IRQ( 9);
HW_IRQ(10);
HW_IRQ(11);
HW_IRQ(12);
HW_IRQ(13);
HW_IRQ(14);
HW_IRQ(15);

/* have this asm _after_ the entry points to get forward jumps */
HW_IRQ_COMMON();


void intctrl_t::init_arch()
{
    const int base = 0x20;
    /* setup the IDT */
#if 0
    for (int i=0; i<16; i++)
	idt.add_int_gate(base+i, (void(*)()) &hwirq_0+((hwirq1-hwirq0)*i));
#else    
    idt.add_int_gate(base+ 0, (void(*)()) &hwirq_0);
    idt.add_int_gate(base+ 1, (void(*)()) &hwirq_1);
    idt.add_int_gate(base+ 2, (void(*)()) &hwirq_2);
    idt.add_int_gate(base+ 3, (void(*)()) &hwirq_3);
    idt.add_int_gate(base+ 4, (void(*)()) &hwirq_4);
    idt.add_int_gate(base+ 5, (void(*)()) &hwirq_5);
    idt.add_int_gate(base+ 6, (void(*)()) &hwirq_6);
    idt.add_int_gate(base+ 7, (void(*)()) &hwirq_7);
    idt.add_int_gate(base+ 8, (void(*)()) &hwirq_8);
    idt.add_int_gate(base+ 9, (void(*)()) &hwirq_9);
    idt.add_int_gate(base+10, (void(*)()) &hwirq_10);
    idt.add_int_gate(base+11, (void(*)()) &hwirq_11);
    idt.add_int_gate(base+12, (void(*)()) &hwirq_12);
    idt.add_int_gate(base+13, (void(*)()) &hwirq_13);
    idt.add_int_gate(base+14, (void(*)()) &hwirq_14);
    idt.add_int_gate(base+15, (void(*)()) &hwirq_15);
#endif

    /* initialize master
       - one slave connected to pin 2
       - reports to vectors 0x20-0x21,0x23-0x27 */
    master.init(base, (1 << 2));

    /* initialize slave
       - its slave id is 2
       - reports to vectors 0x28-0x2F*/
    slave.init(base+8, 2);

    /* unmask the slave on the master */
    master.unmask(2);
}

    
void intctrl_t::handle_irq(word_t irq) 
{
    if (is_masked(irq)){
	//TRACE("Bogus IRQ %d raised\n", irq);
	return;
    }
    mask_and_ack(irq);
    //TRACE("IRQ %d raised\n", irq);
    handle_interrupt(irq);
}


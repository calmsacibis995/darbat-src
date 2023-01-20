/*********************************************************************
 *                
 * Copyright (C) 2002, 2004-2003,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/intctrl.h
 * Description:   
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
 * $Id: intctrl.h,v 1.3 2004/02/25 18:09:26 stoess Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_AMD64__INTCTRL_H__
#define __GLUE__V4_AMD64__INTCTRL_H__

#include <intctrl.h>
/* find the proper intctrl_t class */
#if defined(CONFIG_IOAPIC)
#  include <platform/generic/intctrl-apic.h>
#else /* !defined(CONFIG_IOAPIC) */
#  include <platform/generic/intctrl-pic.h>

INLINE bool intctrl_t::is_irq_available(word_t irq)
{
    return (irq != 8 && irq != 2);
}
#endif /* !defined(CONFIG_IOAPIC) */


/**
 * @return pointer to interrupt controller
 */
INLINE intctrl_t * get_interrupt_ctrl() 
{
    extern intctrl_t intctrl;
    return &intctrl;
}

#endif /* !__GLUE__V4_AMD64__INTCTRL_H__ */

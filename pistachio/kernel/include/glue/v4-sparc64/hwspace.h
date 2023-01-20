/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  University of New South Wales
 *                
 * File path:     glue/v4-sparc64/hwspace.h
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
 * $Id: hwspace.h,v 1.4 2004/02/22 23:09:26 philipd Exp $
 *                
 ********************************************************************/

#ifndef __GLUE__V4_SPARC64__HWSPACE_H__
#define __GLUE__V4_SPARC64__HWSPACE_H__

#include INC_API(kernelinterface.h)

INLINE addr_t virt_to_phys(addr_t addr)
{
    extern word_t _start_text[];
    extern kernel_interface_page_t kip[];
    memdesc_t* memdesc = kip->memory_info.get_memdesc(0);
    return (addr_t)((word_t)addr - (word_t)_start_text + (word_t)memdesc->low());
}

INLINE addr_t phys_to_virt(addr_t addr)
{
    extern word_t _start_text[];
    extern kernel_interface_page_t kip[];
    memdesc_t* memdesc = kip->memory_info.get_memdesc(0);
    return (addr_t)((word_t)addr - (word_t)memdesc->low() + (word_t)_start_text);
}

#endif /* !__GLUE__V4_SPARC64__HWSPACE_H__ */

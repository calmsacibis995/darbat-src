/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-ia32/resources.h
 * Description:   ia32 specific resources
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
 * $Id: resources.h,v 1.8 2004/04/20 15:35:41 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_IA32__RESOURCES_H__
#define __GLUE__V4_IA32__RESOURCES_H__

#include INC_API(resources.h)

#define HAVE_RESOURCE_TYPE_E
enum resource_type_e {
    FPU			= 0,
#if defined(CONFIG_IA32_SMALL_SPACES)
    IPC_PAGE_TABLE	= 1,
#endif
};

class thread_resources_t : public generic_thread_resources_t
{
public:
    void dump(tcb_t * tcb);
    void save(tcb_t * tcb) __asm__ ("tcb_resources_save");
    void load(tcb_t * tcb) __asm__ ("tcb_resources_load");
    void purge(tcb_t * tcb);
    void init(tcb_t * tcb);
    void free(tcb_t * tcb);

public:
    void ia32_no_math_exception(tcb_t * tcb);

private:
    addr_t fpu_state;
};


#endif /* !__GLUE__V4_IA32__RESOURCES_H__ */

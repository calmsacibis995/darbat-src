/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/resources.cc
 * Description:   thread resource management
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
#include INC_API(tcb.h)
#include INC_ARCH(fpu.h)
#include INC_GLUE(resource_functions.h)
#include <kdb/tracepoints.h>

#define FPU_REENABLE
static tcb_t * fpu_owner UNIT("cpulocal");

DECLARE_KMEM_GROUP (kmem_resources);

#ifdef FPU_REENABLE
DECLARE_TRACEPOINT(AMD64_FPU_REENABLE);
#endif

void thread_resources_t::save(tcb_t * tcb)
{
    if (tcb->resource_bits.have_resource(FPU))
    {
	amd64_fpu_t::disable();
#ifndef FPU_REENABLE
	tcb->resource_bits -= FPU;
#endif
    }
}

void thread_resources_t::load(tcb_t * tcb)
{
#ifdef FPU_REENABLE
    if (tcb->resource_bits.have_resource(FPU))
    {
	ASSERT (fpu_owner == tcb);
	ASSERT (fpu_state != NULL);
	TRACEPOINT(AMD64_FPU_REENABLE, 
		   printf("strictly reenabling FPU for %t\n", tcb));
	amd64_fpu_t::enable();
    }
#endif
}

void thread_resources_t::purge(tcb_t * tcb)
{
    if (fpu_owner == tcb)
    {
	amd64_fpu_t::enable();
	amd64_fpu_t::save_state(this->fpu_state);
	fpu_owner = NULL;
	amd64_fpu_t::disable();

#ifdef FPU_REENABLE
	tcb->resource_bits -= FPU;
#endif
    }
}


void thread_resources_t::init(tcb_t * tcb)
{
    tcb->resource_bits.init();
    fpu_state = NULL;

    pdp = NULL;
}


void thread_resources_t::free(tcb_t * tcb)
{
    ASSERT(tcb);
    if (fpu_state)
    {
	kmem.free(kmem_resources, fpu_state, amd64_fpu_t::get_state_size());
	fpu_state = NULL;

	if (fpu_owner == tcb)
	{
	    fpu_owner = NULL;
	    amd64_fpu_t::disable();
	}
    }
}

void thread_resources_t::amd64_no_math_exception(tcb_t * tcb)
{
    ASSERT(&tcb->resources == this);
    amd64_fpu_t::enable();

    // if the current thread owns the fpu already do a quick exit
    if (fpu_owner != tcb)
    {
	if (fpu_owner != NULL)
	{
	    amd64_fpu_t::save_state(fpu_owner->resources.fpu_state);
#ifdef  FPU_REENABLE
	    fpu_owner->resource_bits -= FPU;
#endif
	}
	fpu_owner = tcb;

	if (fpu_state == NULL)
	{
	    fpu_state = kmem.alloc(kmem_resources, amd64_fpu_t::get_state_size());
	    amd64_fpu_t::init();
	}
	else
	    amd64_fpu_t::load_state(fpu_state);
    }

    tcb->resource_bits += FPU;
}


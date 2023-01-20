/*********************************************************************
 *                
 * Copyright (C) 2002, 2004,  Karlsruhe University
 * Copyright (C) 2005,  National ICT Australia (NICTA)
 *                
 * File path:     api/v4/space.h
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
 * $Id: space.h,v 1.11 2004/11/17 16:46:13 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __API__V4__SPACE_H__
#define __API__V4__SPACE_H__

#include <kmemory.h>
#include INC_GLUE(space.h)

EXTERN_KMEM_GROUP (kmem_utcb);

space_t * allocate_space();
void free_space(space_t * space);

extern space_t * sigma0_space;
extern space_t * sigma1_space;
extern space_t * roottask_space;

INLINE bool is_sigma0_space(space_t * space)
{
    return (space == sigma0_space);
}

INLINE bool is_sigma1_space(space_t * space)
{
    return (space == sigma1_space);
}

INLINE bool is_roottask_space(space_t * space)
{
    return (space == roottask_space);
}

INLINE bool is_privileged_space(space_t * space)
{
    return (is_roottask_space(space) ||
	    is_sigma0_space(space) || 
	    is_sigma1_space(space));
}


INLINE bool space_t::is_mappable(addr_t addr)
{
#ifndef CONFIG_ARCH_ARM
    return (is_user_area(addr) && 
	(!get_kip_page_area().is_addr_in_fpage(addr)) &&
	(!get_utcb_page_area().is_addr_in_fpage(addr)));
#else
    return is_user_area(addr);
#endif
}

INLINE bool space_t::is_mappable(fpage_t fpage)
{
#ifndef CONFIG_ARCH_ARM
    return (this->is_user_area(fpage) &&
	(!get_kip_page_area().is_overlapping(fpage) &&
	(!get_utcb_page_area().is_overlapping(fpage))));
#else
    return this->is_user_area(fpage);
#endif
}

INLINE bool space_t::is_user_area(fpage_t fpage)
{
    return is_user_area(fpage.get_address()) && 
	is_user_area(addr_offset(fpage.get_address(), fpage.get_size()-1));
}

#ifndef CONFIG_ARCH_ARM
INLINE bool space_t::is_initialized()
{
    return !get_kip_page_area().is_nil_fpage();
}
#endif

#endif /* !__API__V4__SPACE_H__ */

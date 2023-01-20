/*********************************************************************
 *                
 * Copyright (C) 2003-2004,  National ICT Australia (NICTA)
 *                
 * File path:     glue/v4-arm/hwspace.h
 * Description:   Conversion functions for hardware space addresses
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
 * $Id: hwspace.h,v 1.7 2004/06/04 02:26:52 cvansch Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_ARM__HWSPACE_H__
#define __GLUE__V4_ARM__HWSPACE_H__

#include INC_PLAT(offsets.h)

template<typename T> INLINE T virt_to_phys(T x)
{
#if (VIRT_ADDR_BASE != VIRT_ADDR_RAM)
    if ((u32_t)x < VIRT_ADDR_RAM)
	return (T) ((u32_t) x - KERNEL_ROM_OFFSET);
    else
#endif
	return (T) ((u32_t) x - KERNEL_RAM_OFFSET);
}

template<typename T> INLINE T phys_to_virt(T x)
{
#if (VIRT_ADDR_BASE != VIRT_ADDR_RAM)
    if ((u32_t)x < PHYS_ADDR_RAM)
	return (T) ((u32_t) x + KERNEL_ROM_OFFSET);
    else
#endif
	return (T) ((u32_t) x + KERNEL_RAM_OFFSET);
}

template<typename T> INLINE T virt_to_ram(T x)
{
    return (T) ((u32_t) x - KERNEL_RAM_OFFSET);
}

template<typename T> INLINE T phys_to_ram(T x)
{
    return (T) ((u32_t) x + KERNEL_RAM_OFFSET);
}

#endif /* !__GLUE__V4_ARM__HWSPACE_H__ */

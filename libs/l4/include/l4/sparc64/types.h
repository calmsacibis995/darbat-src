/*********************************************************************
 *                
 * Copyright (C) 2003,  University of New South Wales
 *                
 * File path:     l4/sparc64/types.h
 * Description:   Sparc v9 specific type declararions
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
 * $Id: types.h,v 1.2 2003/09/24 19:06:26 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __L4__SPARC64__TYPES_H__
#define __L4__SPARC64__TYPES_H__

#undef L4_32BIT
#define L4_64BIT
#undef L4_LITTLE_ENDIAN
#define L4_BIG_ENDIAN

typedef unsigned int __attribute__((__mode__(__DI__))) L4_Word64_t;
typedef unsigned int		L4_Word32_t;
typedef unsigned short		L4_Word16_t;
typedef unsigned char		L4_Word8_t;

typedef L4_Word64_t		L4_Word_t;
typedef L4_Word64_t		L4_Size_t;


#endif /* !__L4__SPARC64__TYPES_H__ */

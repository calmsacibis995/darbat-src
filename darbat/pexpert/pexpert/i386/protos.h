/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef _PEXPERT_I386_PROTOS_H
#define _PEXPERT_I386_PROTOS_H

//------------------------------------------------------------------------
// x86 IN/OUT I/O inline functions.
//
// IN :  inb, inw, inl
//       IN(port)
//
// OUT:  outb, outw, outl
//       OUT(port, data)

typedef unsigned short   i386_ioport_t;

#define __IN(s, u) \
static __inline__ unsigned u \
in##s(i386_ioport_t port) \
{ \
    unsigned u data; \
    asm volatile ( \
        "in" #s " %1,%0" \
        : "=a" (data) \
        : "d" (port)); \
    return (data); \
}

#define __OUT(s, u) \
static __inline__ void \
out##s(i386_ioport_t port, unsigned u data) \
{ \
    asm volatile ( \
        "out" #s " %1,%0" \
        : \
        : "d" (port), "a" (data)); \
}

__IN(b, char)
__IN(w, short)
__IN(l, long)

__OUT(b, char)
__OUT(w, short)
__OUT(l, long)

extern void cninit(void);
extern int  sprintf(char * str, const char * format, ...);

//------------------------------------------------------------------------
// from osfmk/console/panic_dialog.c
extern void panic_ui_initialize(const unsigned char * clut);

//------------------------------------------------------------------------
// from osfmk/i386/AT386/video_console.c

extern void vc_progress_initialize( void * desc,
                                    const unsigned char * data,
                                    const unsigned char * clut );

extern void vc_display_icon( void * desc, const unsigned char * data );

#endif /* _PEXPERT_I386_PROTOS_H */

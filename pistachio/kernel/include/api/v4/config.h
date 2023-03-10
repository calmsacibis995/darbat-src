/*********************************************************************
 *                
 * Copyright (C) 2002-2003,  Karlsruhe University
 *                
 * File path:     api/v4/config.h
 * Description:   V4 specific configurations
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
 * $Id: config.h,v 1.14 2003/09/24 19:04:24 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __API__V4__CONFIG_H__
#define __API__V4__CONFIG_H__

#if defined(CONFIG_IS_32BIT)
# define L4_GLOBAL_THREADNO_BITS		18
# define L4_GLOBAL_INTRNO_BITS			18
# define L4_GLOBAL_VERSION_BITS			14
# define L4_FPAGE_BASE_BITS			22
#elif defined(CONFIG_IS_64BIT)
# define L4_GLOBAL_THREADNO_BITS		32
# define L4_GLOBAL_INTRNO_BITS			32
# define L4_GLOBAL_VERSION_BITS			32
# define L4_FPAGE_BASE_BITS			54
#else
# error undefined architecture width (32/64bit?)
#endif

#define DEFAULT_TIMESLICE_LENGTH	10000
#define DEFAULT_TOTAL_QUANTUM		0
#define MAX_PRIO			255
#define ROOT_PRIORITY			MAX_PRIO
#define DEFAULT_PRIORITY		100

/*
 * root server configuration
 */
#define ROOT_MAX_THREADS		256
#define ROOT_VERSION			1

#endif /* !__API__V4__CONFIG_H__ */

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
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
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
/*
 * host_info.h
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 *
 * XXX This is not complete, we snag whatever we need from the file XXX
 */

#ifndef _OSFMK_HOST_INFO_H
#define _OSFMK_HOST_INFO_H

#include <mach/message.h>
#include <mach/vm_statistics.h>
#include <mach/machine.h>
#include <mach/machine/vm_types.h>

#define	HOST_INFO_MAX	(1024)

struct host_basic_info {
        integer_t               max_cpus;               /* max number of CPUs po ssible */
        integer_t               avail_cpus;             /* number of CPUs now av ailable */
        natural_t               memory_size;            /* size of memory in byt es, capped at 2 GB */
        cpu_type_t              cpu_type;               /* cpu type */
        cpu_subtype_t           cpu_subtype;            /* cpu subtype */
        cpu_threadtype_t        cpu_threadtype;         /* cpu threadtype */
        integer_t               physical_cpu;           /* number of physical CP Us now available */
        integer_t               physical_cpu_max;       /* max number of physica l CPUs possible */
        integer_t               logical_cpu;            /* number of logical cpu now available */
        integer_t               logical_cpu_max;        /* max number of physica l CPUs possible */
        uint64_t                max_mem;                /* actual size of physic
al memory */
};

typedef integer_t	host_flavor_t;
typedef struct host_basic_info host_basic_info_data_t;
typedef integer_t	*host_info_t;

#define HOST_BASIC_INFO		1

#endif	/*_OSFMK_HOST_INFO_H*/


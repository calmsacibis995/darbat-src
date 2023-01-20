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
 * osfmk/mach/mach_host.h
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 *
 * Normally, this stuff would have been generated from MIG.  But since we do
 * not have MIG support in the XNU emulation, let us do this manually.
 *
 * The defs of these were snagged from the MIG generated version and from
 * the MIG files themselves.
 */

#include <mach/kern_return.h>
#include <mach/host_info.h>

#ifndef _OSFMK_MACH_HOST_H
#define _OSFMK_MACH_HOST_H

kern_return_t
host_info(host_t, host_flavor_t, host_info_t, mach_msg_type_number_t *);

#endif	/*_OSFMK_MACH_HOST_H*/


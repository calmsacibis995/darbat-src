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
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _NET_MULTICAST_LIST_H
#define _NET_MULTICAST_LIST_H

#include <sys/queue.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/kpi_interface.h>

/*
 * multicast_util.h:
 * - keep track of multicast addresses on one device for programming on
 *   another (VLAN, BOND)
 */
struct multicast_entry {
	SLIST_ENTRY(multicast_entry)	mc_entries;
	ifmultiaddr_t			mc_ifma;
};
SLIST_HEAD(multicast_list, multicast_entry);

void
multicast_list_init(struct multicast_list * mc_list);

int
multicast_list_program(struct multicast_list * mc_list,
		       struct ifnet * source_ifp,
		       struct ifnet * target_ifp);
int
multicast_list_remove(struct multicast_list * mc_list);

#endif /* _NET_MULTICAST_LIST_H */

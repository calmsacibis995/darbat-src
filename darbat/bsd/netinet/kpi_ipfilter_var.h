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

#ifndef __KPI_IPFILTER_VAR__
#define __KPI_IPFILTER_VAR__

#include <sys/appleapiopts.h>
#include <netinet/kpi_ipfilter.h>

#ifdef KERNEL_PRIVATE

/* Private data structure, stripped out by ifdef tool */
/* Implementation specific bits */

#include <sys/queue.h>

struct ipfilter {
	TAILQ_ENTRY(ipfilter)	ipf_link;
	struct ipf_filter		ipf_filter;
	struct ipfilter_list	*ipf_head;
	TAILQ_ENTRY(ipfilter)	ipf_tbr;
};
TAILQ_HEAD(ipfilter_list, ipfilter);


extern struct ipfilter_list	ipv6_filters;
extern struct ipfilter_list	ipv4_filters;

ipfilter_t ipf_get_inject_filter(struct mbuf *m);
void ipf_ref(void);
void ipf_unref(void);
int ipf_init(void);

void    ip_proto_dispatch_in(struct mbuf *m, int hlen, u_int8_t proto, ipfilter_t ipfref);


#endif /* KERNEL_PRIVATE */

#endif /*__KPI_IPFILTER_VAR__*/

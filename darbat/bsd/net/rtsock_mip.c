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
/*	$KAME$	*/

/* to be included from net/rtsock.c - ugly but necessary for portability */
/*
 * Mobile IPv6 addition.
 * Send a routing message to all routing socket listeners.
 */
void
rt_mip6msg(cmd, ifp, rt)
	int cmd;
	struct ifnet *ifp;
	register struct rtentry *rt;
{
	struct rt_addrinfo info;
	struct sockaddr *sa = 0;
	struct mbuf *m = 0;
	register struct rt_msghdr *rtm;

#ifdef MIP6_DEBUG
	printf("route_cb.any_count = %d\n", route_cb.any_count);
#endif
	bzero((caddr_t)&info, sizeof(info));

	if (rt == 0 || ifp == 0)
		return;
	netmask = rt_mask(rt);
	dst = sa = rt_key(rt);
	gate = rt->rt_gateway;
	genmask = rt->rt_genmask;
	if ((m = rt_msg1(cmd, &info)) == NULL) {
#ifdef MIP6_DEBUG
		printf("failure... \n");
#endif
		return;
	}
	rtm = mtod(m, struct rt_msghdr *);
	rtm->rtm_index = ifp->if_index;
	rtm->rtm_flags |= rt->rt_flags;
	rtm->rtm_rmx = rt->rt_rmx;
	rtm->rtm_addrs = info.rti_addrs;
	rtm->rtm_flags |= RTF_DONE;

	route_proto.sp_protocol = sa ? sa->sa_family : 0;
#ifdef __bsdi__
	raw_input(m, NULL, &route_proto, &route_src, &route_dst);
#else
	raw_input(m, &route_proto, &route_src, &route_dst);
#endif
}

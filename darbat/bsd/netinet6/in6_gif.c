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
#include <igcompat/compat.h>
/*	$FreeBSD: src/sys/netinet6/in6_gif.c,v 1.2.2.3 2001/07/03 11:01:52 ume Exp $	*/
/*	$KAME: in6_gif.c,v 1.49 2001/05/14 14:02:17 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/queue.h>
#include <sys/syslog.h>

#include <sys/malloc.h>
#include <sys/protosw.h>

#include <net/if.h>
#include <net/route.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#if INET
#include <netinet/ip.h>
#endif
#include <netinet/ip_encap.h>
#if INET6
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/in6_gif.h>
#include <netinet6/in6_var.h>
#endif
#include <netinet/ip_ecn.h>
#if INET6
#include <netinet6/ip6_ecn.h>
#endif

#include <net/if_gif.h>

#include <net/net_osdep.h>
#include <net/dlil.h>

int
in6_gif_output(
	struct ifnet *ifp,
	int family, /* family of the packet to be encapsulate. */
	struct mbuf *m,
	struct rtentry *rt)
{
	struct gif_softc *sc = (struct gif_softc*)ifp;
	struct sockaddr_in6 *dst = (struct sockaddr_in6 *)&sc->gif_ro6.ro_dst;
	struct sockaddr_in6 *sin6_src = (struct sockaddr_in6 *)sc->gif_psrc;
	struct sockaddr_in6 *sin6_dst = (struct sockaddr_in6 *)sc->gif_pdst;
	struct ip6_hdr *ip6;
	int proto;
	u_int8_t itos, otos;

	if (sin6_src == NULL || sin6_dst == NULL ||
	    sin6_src->sin6_family != AF_INET6 ||
	    sin6_dst->sin6_family != AF_INET6) {
		m_freem(m);
		return EAFNOSUPPORT;
	}

	switch (family) {
#if INET
	case AF_INET:
	    {
		struct ip *ip;

		proto = IPPROTO_IPV4;
		if (m->m_len < sizeof(*ip)) {
			m = m_pullup(m, sizeof(*ip));
			if (!m)
				return ENOBUFS;
		}
		ip = mtod(m, struct ip *);
		itos = ip->ip_tos;
		break;
	    }
#endif
#if INET6
	case AF_INET6:
	    {
		struct ip6_hdr *ip6;
		proto = IPPROTO_IPV6;
		if (m->m_len < sizeof(*ip6)) {
			m = m_pullup(m, sizeof(*ip6));
			if (!m)
				return ENOBUFS;
		}
		ip6 = mtod(m, struct ip6_hdr *);
		itos = (ntohl(ip6->ip6_flow) >> 20) & 0xff;
		break;
	    }
#endif
	default:
#if DEBUG
		printf("in6_gif_output: warning: unknown family %d passed\n",
			family);
#endif
		m_freem(m);
		return EAFNOSUPPORT;
	}
	
	/* prepend new IP header */
	M_PREPEND(m, sizeof(struct ip6_hdr), M_DONTWAIT);
	if (m && m->m_len < sizeof(struct ip6_hdr))
		m = m_pullup(m, sizeof(struct ip6_hdr));
	if (m == NULL) {
		printf("ENOBUFS in in6_gif_output %d\n", __LINE__);
		return ENOBUFS;
	}

	ip6 = mtod(m, struct ip6_hdr *);
	ip6->ip6_flow	= 0;
	ip6->ip6_vfc	&= ~IPV6_VERSION_MASK;
	ip6->ip6_vfc	|= IPV6_VERSION;
	ip6->ip6_plen	= htons((u_short)m->m_pkthdr.len);
	ip6->ip6_nxt	= proto;
	ip6->ip6_hlim	= ip6_gif_hlim;
	ip6->ip6_src	= sin6_src->sin6_addr;
	/* bidirectional configured tunnel mode */
	if (!IN6_IS_ADDR_UNSPECIFIED(&sin6_dst->sin6_addr))
		ip6->ip6_dst = sin6_dst->sin6_addr;
	else  {
		m_freem(m);
		return ENETUNREACH;
	}
	if (ifp->if_flags & IFF_LINK1)
		ip_ecn_ingress(ECN_ALLOWED, &otos, &itos);
	else
		ip_ecn_ingress(ECN_NOCARE, &otos, &itos);
	ip6->ip6_flow &= ~ntohl(0xff00000);
	ip6->ip6_flow |= htonl((u_int32_t)otos << 20);

	if (dst->sin6_family != sin6_dst->sin6_family ||
	     !IN6_ARE_ADDR_EQUAL(&dst->sin6_addr, &sin6_dst->sin6_addr)) {
		/* cache route doesn't match */
		bzero(dst, sizeof(*dst));
		dst->sin6_family = sin6_dst->sin6_family;
		dst->sin6_len = sizeof(struct sockaddr_in6);
		dst->sin6_addr = sin6_dst->sin6_addr;
		if (sc->gif_ro6.ro_rt) {
			rtfree(sc->gif_ro6.ro_rt);
			sc->gif_ro6.ro_rt = NULL;
		}
#if 0
		sc->gif_if.if_mtu = GIF_MTU;
#endif
	}

	if (sc->gif_ro6.ro_rt == NULL) {
		rtalloc((struct route *)&sc->gif_ro6);
		if (sc->gif_ro6.ro_rt == NULL) {
			m_freem(m);
			return ENETUNREACH;
		}

		/* if it constitutes infinite encapsulation, punt. */
		if (sc->gif_ro.ro_rt->rt_ifp == ifp) {
			m_freem(m);
			return ENETUNREACH;	/*XXX*/
		}
#if 0
		ifp->if_mtu = sc->gif_ro6.ro_rt->rt_ifp->if_mtu
			- sizeof(struct ip6_hdr);
#endif
	}
	
#if IPV6_MINMTU
	/*
	 * force fragmentation to minimum MTU, to avoid path MTU discovery.
	 * it is too painful to ask for resend of inner packet, to achieve
	 * path MTU discovery for encapsulated packets.
	 */
	return(ip6_output(m, 0, &sc->gif_ro6, IPV6_MINMTU, 0, NULL, 0));
#else
	return(ip6_output(m, 0, &sc->gif_ro6, 0, 0, NULL, 0));
#endif
}

int in6_gif_input(mp, offp)
	struct mbuf **mp;
	int *offp;
{
	struct mbuf *m = *mp;
	struct ifnet *gifp = NULL;
	struct ip6_hdr *ip6;
	int af = 0;
	u_int32_t otos;
	u_int8_t proto;

	ip6 = mtod(m, struct ip6_hdr *);

	gifp = (struct ifnet *)encap_getarg(m);

	if (gifp == NULL || (gifp->if_flags & IFF_UP) == 0) {
		m_freem(m);
		ip6stat.ip6s_nogif++;
		return IPPROTO_DONE;
	}

	proto = ip6->ip6_nxt;
	otos = ip6->ip6_flow;
	m_adj(m, *offp);

	switch (proto) {
#if INET
	case IPPROTO_IPV4:
	    {
		struct ip *ip;
		u_int8_t otos8;
		af = AF_INET;
		otos8 = (ntohl(otos) >> 20) & 0xff;
		if (m->m_len < sizeof(*ip)) {
			m = m_pullup(m, sizeof(*ip));
			if (!m)
				return IPPROTO_DONE;
		}
		ip = mtod(m, struct ip *);
		if (gifp->if_flags & IFF_LINK1)
			ip_ecn_egress(ECN_ALLOWED, &otos8, &ip->ip_tos);
		else
			ip_ecn_egress(ECN_NOCARE, &otos8, &ip->ip_tos);
		break;
	    }
#endif /* INET */
#if INET6
	case IPPROTO_IPV6:
	    {
		struct ip6_hdr *ip6;
		af = AF_INET6;
		if (m->m_len < sizeof(*ip6)) {
			m = m_pullup(m, sizeof(*ip6));
			if (!m)
				return IPPROTO_DONE;
		}
		ip6 = mtod(m, struct ip6_hdr *);
		if (gifp->if_flags & IFF_LINK1)
			ip6_ecn_egress(ECN_ALLOWED, &otos, &ip6->ip6_flow);
		else
			ip6_ecn_egress(ECN_NOCARE, &otos, &ip6->ip6_flow);
		break;
	    }
#endif
	default:
		ip6stat.ip6s_nogif++;
		m_freem(m);
		return IPPROTO_DONE;
	}
		
	dlil_input(gifp, m, m);
	return IPPROTO_DONE;
}

/*
 * validate outer address.
 */
static int
gif_validate6( const struct ip6_hdr *ip6, struct gif_softc *sc, struct ifnet *ifp)
{
	struct sockaddr_in6 *src, *dst;

	src = (struct sockaddr_in6 *)sc->gif_psrc;
	dst = (struct sockaddr_in6 *)sc->gif_pdst;

	/*
	 * Check for address match.  Note that the check is for an incoming
	 * packet.  We should compare the *source* address in our configuration
	 * and the *destination* address of the packet, and vice versa.
	 */
	if (!IN6_ARE_ADDR_EQUAL(&src->sin6_addr, &ip6->ip6_dst) ||
	    !IN6_ARE_ADDR_EQUAL(&dst->sin6_addr, &ip6->ip6_src))
		return 0;

	/* martian filters on outer source - done in ip6_input */

	/* ingress filters on outer source */
	if ((sc->gif_if.if_flags & IFF_LINK2) == 0 && ifp) {
		struct sockaddr_in6 sin6;
		struct rtentry *rt;

		bzero(&sin6, sizeof(sin6));
		sin6.sin6_family = AF_INET6;
		sin6.sin6_len = sizeof(struct sockaddr_in6);
		sin6.sin6_addr = ip6->ip6_src;
#ifndef SCOPEDROUTING
		sin6.sin6_scope_id = 0; /* XXX */
#endif

		rt = rtalloc1((struct sockaddr *)&sin6, 0, 0UL);
		if (!rt || rt->rt_ifp != ifp) {
#if 0
			log(LOG_WARNING, "%s: packet from %s dropped "
			    "due to ingress filter\n", if_name(&sc->gif_if),
			    ip6_sprintf(&sin6.sin6_addr));
#endif
			if (rt)
				rtfree(rt);
			return 0;
		}
		rtfree(rt);
	}

	return 128 * 2;
}

/*
 * we know that we are in IFF_UP, outer address available, and outer family
 * matched the physical addr family.  see gif_encapcheck().
 * sanity check for arg should have been done in the caller.
 */
int
gif_encapcheck6(struct mbuf *m, int off, int proto, void *arg)
{
	struct ip6_hdr ip6;
	struct gif_softc *sc;
	struct ifnet *ifp;

	/* sanity check done in caller */
	sc = (struct gif_softc *)arg;

	/* LINTED const cast */
	m_copydata(m, 0, sizeof(ip6), (caddr_t)&ip6);
	ifp = ((m->m_flags & M_PKTHDR) != 0) ? m->m_pkthdr.rcvif : NULL;

	return gif_validate6(&ip6, sc, ifp);
}

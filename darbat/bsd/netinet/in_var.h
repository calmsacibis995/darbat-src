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
/*
 * Copyright (c) 1985, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)in_var.h	8.2 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/netinet/in_var.h,v 1.33.2.2 2001/07/17 10:50:01 ru Exp $
 */

#ifndef _NETINET_IN_VAR_H_
#define _NETINET_IN_VAR_H_
#include <sys/appleapiopts.h>

#include <sys/queue.h>
#ifdef __APPLE__
#include <sys/kern_event.h>
#endif

#ifdef PRIVATE

/*
 * Interface address, Internet version.  One of these structures
 * is allocated for each Internet address on an interface.
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
#define	ia_ifp		ia_ifa.ifa_ifp
#define ia_flags	ia_ifa.ifa_flags
					/* ia_{,sub}net{,mask} in host order */
	u_long	ia_net;			/* network number of interface */
	u_long	ia_netmask;		/* mask of net part */
	u_long	ia_subnet;		/* subnet number, including net */
	u_long	ia_subnetmask;		/* mask of subnet part */
	struct	in_addr ia_netbroadcast; /* to recognize net broadcasts */
	TAILQ_ENTRY(in_ifaddr) ia_link;	/* tailq macro glue */
	struct	sockaddr_in ia_addr;	/* reserve space for interface name */
	struct	sockaddr_in ia_dstaddr; /* reserve space for broadcast addr */
#define	ia_broadaddr	ia_dstaddr
	struct	sockaddr_in ia_sockmask; /* reserve space for general netmask */
};
#endif /* PRIVATE */

struct	in_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in ifra_addr;
	struct	sockaddr_in ifra_broadaddr;
#define ifra_dstaddr ifra_broadaddr
	struct	sockaddr_in ifra_mask;
#ifdef __APPLE__
        u_long              dlt;
#endif
};

/*
 * Event data, internet style.
 */
struct kev_in_data {
	struct net_event_data   link_data;
	struct in_addr  ia_addr;
	u_long	ia_net;			/* network number of interface */
	u_long	ia_netmask;		/* mask of net part */
	u_long	ia_subnet;		/* subnet number, including net */
	u_long	ia_subnetmask;		/* mask of subnet part */
	struct	in_addr ia_netbroadcast; /* to recognize net broadcasts */
	struct  in_addr ia_dstaddr;
};

struct kev_in_collision {
	struct	net_event_data	link_data;	/* link colliding arp was received on */
	struct	in_addr	ia_ipaddr;	/* IP address we and another node are using */
	u_char	hw_len;	/* length of hardware address */
	u_char	hw_addr[0];	/* variable length hardware address */
};


/*
 * Define inet event subclass and specific inet events.
 */

#define KEV_INET_SUBCLASS 1

#define KEV_INET_NEW_ADDR     1
#define KEV_INET_CHANGED_ADDR 2
#define KEV_INET_ADDR_DELETED 3
#define KEV_INET_SIFDSTADDR   4
#define KEV_INET_SIFBRDADDR   5
#define KEV_INET_SIFNETMASK   6
#define KEV_INET_ARPCOLLISION 7	/* use kev_in_collision */

#ifdef KERNEL_PRIVATE
/*
 * Given a pointer to an in_ifaddr (ifaddr),
 * return a pointer to the addr as a sockaddr_in.
 */
#define IA_SIN(ia)    (&(((struct in_ifaddr *)(ia))->ia_addr))
#define IA_DSTSIN(ia) (&(((struct in_ifaddr *)(ia))->ia_dstaddr))

#define IN_LNAOF(in, ifa) \
	((ntohl((in).s_addr) & ~((struct in_ifaddr *)(ifa)->ia_subnetmask))

extern	TAILQ_HEAD(in_ifaddrhead, in_ifaddr) in_ifaddrhead;
extern	struct	ifqueue	ipintrq;		/* ip packet input queue */
extern	struct	in_addr zeroin_addr;
extern	u_char	inetctlerrmap[];
extern	lck_mtx_t *rt_mtx;

/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.
 */
#define INADDR_TO_IFP(addr, ifp) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
{ \
	struct in_ifaddr *ia; \
\
	lck_mtx_assert(rt_mtx, LCK_MTX_ASSERT_NOTOWNED); \
	lck_mtx_lock(rt_mtx); \
	TAILQ_FOREACH(ia, &in_ifaddrhead, ia_link) \
		if (IA_SIN(ia)->sin_addr.s_addr == (addr).s_addr) \
			break; \
	(ifp) = (ia == NULL) ? NULL : ia->ia_ifp; \
	lck_mtx_unlock(rt_mtx); \
}

/*
 * Macro for finding the internet address structure (in_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA(ifp, ia) \
	/* struct ifnet *ifp; */ \
	/* struct in_ifaddr *ia; */ \
{ \
	lck_mtx_assert(rt_mtx, LCK_MTX_ASSERT_NOTOWNED); \
	lck_mtx_lock(rt_mtx); \
	for ((ia) = TAILQ_FIRST(&in_ifaddrhead); \
	    (ia) != NULL && (ia)->ia_ifp != (ifp); \
	    (ia) = TAILQ_NEXT((ia), ia_link)) \
		continue; \
	lck_mtx_unlock(rt_mtx); \
}

/*
 * This information should be part of the ifnet structure but we don't wish
 * to change that - as it might break a number of things
 */

struct router_info {
	struct ifnet *rti_ifp;
	int    rti_type; /* type of router which is querier on this interface */
	int    rti_time; /* # of slow timeouts since last old query */
	struct router_info *rti_next;
};

/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * For every entry on the interface's if_multiaddrs list which represents
 * an IP multicast group, there is one of these structures.  They are also
 * kept on a system-wide list to make it easier to keep our legacy IGMP code
 * compatible with the rest of the world (see IN_FIRST_MULTI et al, below).
 */
struct in_multi {
	LIST_ENTRY(in_multi) inm_link;	/* queue macro glue */
	struct	in_addr inm_addr;	/* IP multicast address, convenience */
	struct	ifnet *inm_ifp;		/* back pointer to ifnet */
	struct	ifmultiaddr *inm_ifma;	/* back pointer to ifmultiaddr */
	u_int	inm_timer;		/* IGMP membership report timer */
	u_int	inm_state;		/*  state of the membership */
	struct	router_info *inm_rti;	/* router info*/
};

#ifdef SYSCTL_DECL
SYSCTL_DECL(_net_inet_ip);
SYSCTL_DECL(_net_inet_raw);
#endif

extern LIST_HEAD(in_multihead, in_multi) in_multihead;

/*
 * Structure used by macros below to remember position when stepping through
 * all of the in_multi records.
 */
struct in_multistep {
	struct in_multi *i_inm;
};

/*
 * Macro for looking up the in_multi record for a given IP multicast address
 * on a given interface.  If no matching record is found, "inm" is set null.
 */
#define IN_LOOKUP_MULTI(addr, ifp, inm) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
	/* struct in_multi *inm; */ \
do { \
	struct ifmultiaddr *ifma; \
\
	LIST_FOREACH(ifma, &((ifp)->if_multiaddrs), ifma_link) { \
		if (ifma->ifma_addr->sa_family == AF_INET \
		    && ((struct sockaddr_in *)ifma->ifma_addr)->sin_addr.s_addr == \
		    (addr).s_addr) \
			break; \
	} \
	(inm) = ifma ? ifma->ifma_protospec : 0; \
} while(0)

/*
 * Macro to step through all of the in_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN_NEXT_MULTI(step, inm) \
	/* struct in_multistep  step; */ \
	/* struct in_multi *inm; */ \
do { \
	if (((inm) = (step).i_inm) != NULL) \
		(step).i_inm = LIST_NEXT((step).i_inm, inm_link); \
} while(0)

#define IN_FIRST_MULTI(step, inm) \
	/* struct in_multistep step; */ \
	/* struct in_multi *inm; */ \
do { \
	(step).i_inm = LIST_FIRST(&in_multihead); \
	IN_NEXT_MULTI((step), (inm)); \
} while(0)

struct	route;
struct	in_multi *in_addmulti(struct in_addr *, struct ifnet *);
void	in_delmulti(struct in_multi **);
int	in_control(struct socket *, u_long, caddr_t, struct ifnet *,
			struct proc *);
void	in_rtqdrain(void);
void	ip_input(struct mbuf *);
int	in_ifadown(struct ifaddr *ifa, int);
void	in_ifscrub(struct ifnet *, struct in_ifaddr *, int);
int	ipflow_fastforward(struct mbuf *);
void	ipflow_create(const struct route *, struct mbuf *);
void	ipflow_slowtimo(void);

#endif /* KERNEL_PRIVATE */

/* INET6 stuff */
#include <netinet6/in6_var.h>

#endif /* _NETINET_IN_VAR_H_ */

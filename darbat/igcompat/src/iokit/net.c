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
 * net.c
 *
 * Simple test for I/O Kit network
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <sys/kpi_mbuf.h>
#include <net/kpi_interface.h>
#include <net/if_types.h>
#include <net/dlil.h>
#include <net/if_dl.h>
#include <net/if_ether.h>
#include <net/ethernet.h>
#include <net/route.h>
#include <net/bpf.h>

#include <kern/debug.h>

#include <kern/locks.h>  /* for the spinlock */
#include <iokit_cli/net.h>

#include <iguana/iokit_disk.h>

#include <igcompat/compat.h>

void net_init(void);
void net_rx_handle(void);

static const u_char ether_broadcast_addr[ETHER_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

// peel:  0:16:cb:89:63:cc
static u_char my_mac_addr[ETHER_ADDR_LEN]={0x0, 0x16, 0xcb, 0x89, 0x63, 0xcc};

/* our network IF handle */
static ifnet_t darbat_ifnet = NULL;

/* pointer to the copy buffer with IOKit */
static struct netbuf *netbuf = NULL;


static int
get_mtu( ifnet_t ifn )
{
	return 1500;
}

static int
get_hdrlen( void )
{
	return ETHER_HDR_LEN;
}

static int
get_addrlen( void )
{
	return ETHER_ADDR_LEN;
}

#define dprintf(x...)

/******* data to/from IOKit ********/


#if 0
static char hexarr[] = "0123456789abcdef";
#endif

void
net_rx_handle(void)
{
	struct netbuf_desc *desc;
	mbuf_t mbuf;
	errno_t err;
	unsigned int chunks;
	void *data;
	int hdrlen = get_hdrlen(); /* XXX */

	assert( netbuf != NULL );

	dprintf( "in net_rx_handle...\n" );

	netbuf_lock( netbuf );

	/* find the next consumer guy */
	while( (desc = get_cons_desc( netbuf->rx )) )
	{
		/* say hello */
		dprintf( "found desc: data %p, len %d\n", 
			desc->data, desc->length );

		/* dump some data */
#if 0
		{
			int i, max;
			char sbuf[32*3 + 20]; /* XXX */
			max = 32;
			if( max > desc->length )
				max = desc->length;

			for( i = 0; i < max; i++ )
			{
				sbuf[i*3+0] = hexarr[(((char*)desc->data)[i]>>4)&0xf];
				sbuf[i*3+1] = hexarr[((char*)desc->data)[i]&0xf];
				sbuf[i*3+2] = ' ';
			}
			sbuf[i] = '\0';
			printf( "rx_handle[%d]: %s\n", desc->length, sbuf );
		}
#endif

		// mbuf_alloc
		chunks = 1;
		err =  mbuf_allocpacket( MBUF_WAITOK, desc->length,
					 &chunks, &mbuf );
		if( err != 0 )
			panic( "couldn't allocate darbat recv mbuf :(\n" );

		/* setup (copy in) packet data */
		data = mbuf_data( mbuf );
		memcpy( data, desc->data, desc->length );

		//printf( "mbuf_len was %d, making %d\n", (int)mbuf_len(mbuf), desc->length );

		/* setup packet header */
		/* This works for recv OK! */
		mbuf_pkthdr_setrcvif( mbuf, darbat_ifnet );
		mbuf_pkthdr_setheader(mbuf, mbuf_data(mbuf));
		mbuf_pkthdr_setlen( mbuf, desc->length - hdrlen );

		/* set data ptr + len */
		mbuf_setdata( mbuf, (char *)mbuf_data(mbuf) + hdrlen, 
			      desc->length - hdrlen);

		// then free the comm desc for more RX later! :)
		netbuf_free_data( netbuf, desc->data );

		// push up to the next layer!
		// FIXME: could queue these...
		ifnet_input( darbat_ifnet, mbuf, NULL );
	}

	netbuf_unlock( netbuf );

	dprintf( "done net_rx_handle!\n" );

}

void disk_net_tx(void);

/******* functions called from the link layer ********/
static int
output_shim(ifnet_t ifn, mbuf_t m)
{
	mbuf_t pkt, next;

	assert( netbuf != NULL );
	dprintf( "darbat doing a TX\n" );

	netbuf_lock(netbuf);

	/* copy packet data and descs to queue */
	/* clag from net_stubs in iokit RX path */
	pkt = m;
	do 
	{
		/* copy it in! */
		copy_packet_in( netbuf, netbuf->tx, pkt, 1 );

		/* go to the next packet & free the current one */
		next = mbuf_nextpkt( pkt );
		mbuf_free( pkt );  /* XXX: free here? */
		pkt = next;
	} while( pkt );

	netbuf_unlock(netbuf);

	/* send a message to say we've queued stuff */
	disk_net_tx();
	
	return 0;
}

static void
netrtrequest(int cmd, struct rtentry *rt, struct sockaddr *sa)
{
	if (rt) {
		rt->rt_rmx.rmx_mtu = rt->rt_ifp->if_mtu; /* for ISO */
		/*
		 * For optimal performance, the send and receive buffers
		 * should be at least twice the MTU plus a little more for
		 * overhead.
		 */
		rt->rt_rmx.rmx_recvpipe = 
			rt->rt_rmx.rmx_sendpipe = 3 * get_mtu(NULL);
	}
}

static errno_t
ioctl_shim(ifnet_t ifn, u_int32_t cmd, void * data)
{
	struct ifreq *  ifr = (struct ifreq *) data;
	errno_t         ret = EOPNOTSUPP;
	register struct ifaddr *ifa;

	if ( ifr == NULL )
		return EINVAL;

	switch ( cmd )
	{
		// Get interface MTU.
		case SIOCGIFMTU:
			ifr->ifr_mtu = get_mtu( ifn );
			ret = 0;    // no error
			break;

		// set MTU
		case SIOCSIFMTU:
			printf( "trying to set MTU %d\n", ifr->ifr_mtu );
			ret = 0;
			break;


		case SIOCADDMULTI:
		case SIOCDELMULTI:
			if (ifr == 0)
			{
				ret = EAFNOSUPPORT;		/* XXX */
				break;
			}
			switch (ifr->ifr_addr.sa_family) 
			{
				case AF_INET:
					break;
				default:
					ret = EAFNOSUPPORT;
					break;
			}
			break;

		case SIOCSIFADDR:
			ifnet_set_flags( darbat_ifnet, 
					 IFF_UP | IFF_RUNNING, 
					 IFF_UP | IFF_RUNNING );
			ifa = (struct ifaddr *)data;
			ifa->ifa_rtrequest = netrtrequest;

			/*
			 * Everything else is done at a higher level.
			 */
			break;

		case SIOCSIFFLAGS:
			break;
			

		default:
			// DLOG(%s: command not handled (%08lx), getName(), cmd);
			printf("net.c: command not handled (%x)\n", cmd);
			break;
	}


	return ret;
}

static errno_t
set_bpf_tap_shim( ifnet_t ifn,
		  bpf_tap_mode    mode,
		  bpf_packet_func func )
{
	panic( "set_bpf_tap_shim\n" );
	return 1;
}

static void 
detach_shim(ifnet_t ifn)
{
	panic( "detach_shim\n" );
}

static void
setup_ifnet( char *mac_addr, uint32_t asize )
{
	struct ifnet_init_params iparams;
	char buffer[2*sizeof(struct sockaddr_dl)];
	struct sockaddr_dl *ll_addr;
	int r;

	assert( asize == ETHER_ADDR_LEN );

	/* fill out the params */
	memset(&iparams, 0, sizeof(iparams));
	iparams.name = "dn"; /* darbat network */
	iparams.unit = 0;   /* zeroth */
	iparams.output = output_shim;
	iparams.ioctl  = ioctl_shim;
	iparams.set_bpf_tap = set_bpf_tap_shim;
	iparams.detach = detach_shim;
	iparams.softc = NULL;

	/* ethernet part */
	iparams.uniqueid = mac_addr;
	iparams.uniqueid_len = asize;
	iparams.type = IFT_ETHER;
	iparams.family  = APPLE_IF_FAM_ETHERNET;
	iparams.demux = ether_demux;
	iparams.add_proto = ether_add_proto;
	iparams.del_proto = ether_del_proto;
	iparams.framer = ether_frameout;
	iparams.check_multi = ether_check_multi;
	iparams.broadcast_addr = ether_broadcast_addr;
	iparams.broadcast_len = ETHER_ADDR_LEN; // sizeof(ether_broadcast_addr);

	/* now we can allocate an ifnet */
	r = ifnet_allocate( &iparams, &darbat_ifnet );

	if( r != 0 || darbat_ifnet == NULL )
		panic( "failed to ifnet_allocate :(\n" );

	/* setup the link-layer address structure */
	memset(buffer, 0, sizeof(buffer));
	ll_addr = (struct sockaddr_dl *)buffer;
	// asize = sizeof(buffer) - offsetof(struct sockaddr_dl, sdl_data);

	assert( asize == 6 );	
	assert( asize == ETHER_ADDR_LEN );

	bcopy(mac_addr, ll_addr->sdl_data, asize);
	ll_addr->sdl_len = offsetof(struct sockaddr_dl, sdl_data) + asize;
	ll_addr->sdl_family = AF_LINK;
	ll_addr->sdl_alen = asize;

	/* FIXME: should sync more... */
	
	/* ... like MTU */
	if( ifnet_set_mtu( darbat_ifnet, get_mtu( NULL ) ) )
		panic( "failed to set MTU\n" );

	/* set addr len */
	if( ifnet_set_addrlen( darbat_ifnet, get_addrlen() ) != 0 )
		panic( "failed to set addrlen!\n" );

	if( ifnet_set_hdrlen( darbat_ifnet, get_hdrlen() ) != 0 )
		panic( "failed to set hdrlen\n" );

#if 0
	if( ifnet_set_flags( darbat_ifnet, 
			     IFF_UP|IFF_RUNNING, IFF_UP|IFF_RUNNING ) != 0 )
		panic( "failed to set flags :(\n" );
#else
	{
		// unsigned flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_NOTRAILERS | IFF_RUNNING;
		unsigned flags = IFF_BROADCAST | IFF_RUNNING;
		if( ifnet_set_flags( darbat_ifnet, flags, flags ) != 0 )
			panic( "failed to set flags :(\n" );
	}
#endif

	/* loop and dummy do (something like) this... */
	// dlil_if_attach(darbat_ifnet);

	// bpfattach(darbat_ifnet, DLT_NULL, sizeof(u_int));

	/* do the attach... */
	if( ifnet_attach( darbat_ifnet, ll_addr ) != 0 )
		panic( "failed to attach network card!\n" );
}


/* XXX: from disk.c */
extern void *shared_buffer;

void 
net_init(void)
{
	assert( ETHER_ADDR_LEN == 6 );
	assert( ETHER_HDR_LEN == 14 );

	/* create a fake network card */
	printf( ">>> net_init setting up fake network card\n" );

	/* setup the shared buffer pointer */
	if( shared_buffer == NULL )
		panic( "net_init: no IOKit comms buffer\n" );

	netbuf = (void*) ((char*) shared_buffer + DISKBUFSIZ);

	/* setup the ifnet */
	setup_ifnet( my_mac_addr, get_addrlen() );
}

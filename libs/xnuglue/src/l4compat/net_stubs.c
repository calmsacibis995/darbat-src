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
 * net_stubs.c
 *
 * These includes were copied from various files in the bsd/net directory,
 * esp. in kpi_interface.c.
 */

/*
 * kpi_interface.c
 *
 */
#include <net/kpi_interface.h>
#include <sys/kpi_mbuf.h>

#include <kern/kalloc.h>	/* kalloc/kfree */

#include <stdio.h>

// #include <kern/locks.h>  /* for the spinlock */
#include <iokit_cli/net.h>

// #include <iguana/iokit_disk.h>

extern void panic(const char *, ...);
void darbat_rx_notify(void);
static struct netbuf *netbuf;

#if 0
static char hexarr[] = "0123456789abcdef";
#endif

/* XXX */
void do_net_tx(void);
void yukon_do_tx( void *data, unsigned size );

//#define dprintf(x...) 
#define dprintf(x...) printf(x)


/* network card done with a TX buffer */
void handle_tx_done( void *data );

void
handle_tx_done( void *data )
{
	assert( data != NULL );

	/* just free the data buffer */
	netbuf_lock( netbuf );
	netbuf_free_data( netbuf, data );
	netbuf_unlock( netbuf );
}

/* got a kick from darbat */
void
do_net_tx(void)
{
	struct netbuf_desc *desc;

	assert( netbuf != NULL );

	dprintf( "in do_net_tx...\n" );

	netbuf_lock(netbuf);

	/* find the next consumer guy */
	while( (desc = get_cons_desc( netbuf->tx )) )
	{
		/* say hello */
		dprintf( "found desc: data %p, len %d\n", 
			desc->data, desc->length );

		/* request the TX */
		/** XXX: push it directly to yukon, in place tho! :) **/
		//yukon_do_tx( desc->data, desc->length );
	}

	netbuf_unlock(netbuf);

	dprintf( "iokit: done net_tx!\n" );
}

errno_t
ifnet_input( ifnet_t interface,
	     mbuf_t first_packet,
	     const struct ifnet_stat_increment_param *stats )
{
	mbuf_t pkt, next;

	dprintf( "ifnet_input on if %p\n", interface );

	assert( netbuf != NULL );

	netbuf_lock(netbuf);

	/* copy packet data and descs to queue */
	pkt = first_packet;
	do 
	{
		copy_packet_in( netbuf, netbuf->rx, pkt, 0 );

		/* go to the next packet & free the current one */
		next = mbuf_nextpkt( pkt );
		assert( mbuf_next( pkt ) == NULL );
		mbuf_free( pkt );
		pkt = next;
	} while( pkt );

	netbuf_unlock(netbuf);

	/* send a notification to darbat */
	darbat_rx_notify();

	return 0;
}

void iokit_netbuf_init( void * start, unsigned len );

void 
iokit_netbuf_init( void * start, unsigned len )
{
	netbuf = netbuf_init( start, len );
}

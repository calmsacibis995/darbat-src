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
/* source for IOKit copying network interface */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <net/kpi_interface.h>
#include <sys/kpi_mbuf.h>

#include <iokit_cli/net.h>

#include <l4/schedule.h>

#define COPY_DUMP 0

#if COPY_DUMP
static char hexarr[] = "0123456789abcdef";
#endif

/* XXX */
extern void panic(char *msg);

/* copy a whole packet into a queue */
/* XXX: make sure you call holding the lock! */
void
copy_packet_in( struct netbuf *nb, struct netbuf_q *q, mbuf_t pkt, int tx )
{
	size_t	len;
	void   *data, *data_dest;
	struct netbuf_desc *desc;

	assert( nb != NULL );
	assert( pkt != NULL );


	/* FIXME: we don't deal with fragments yet */
	assert( mbuf_next( pkt ) == NULL );

	/* XXX */
	if( mbuf_next( pkt ) != NULL )
	{
		{
			int i = 0;
			mbuf_t m;

			m = pkt;
			while( m )
			{
				m = mbuf_next( m );
				i++;
			}
			printf( "counted %d mbufs on chain\n", i );
		}

		printf( "trying pullup!\n" );
		if( mbuf_pullup( &pkt, mbuf_pkthdr_len(pkt) ) != 0 )
			panic( "eep, mbuf wouldn't pullup :(\n" );
	}

	/* pull out fields - use the whole packet */
	/* stupid mbufs, this should be different on TX and RX
	 * ... but we hide that in the output shim
	 */
#if COPY_DUMP
	printf( "mbuf_len:        %d\n", mbuf_len( pkt ) );
	printf( "mbuf_pkthdr_len: %d\n", mbuf_pkthdr_len( pkt ) );
	printf( "mbuf_data:          %p\n", mbuf_data( pkt ) );
	printf( "mbuf_pkthdr_header: %p\n", mbuf_pkthdr_header( pkt ) );
#endif
	if( tx )
	{
		len = mbuf_len( pkt );
		data = mbuf_data( pkt );
	}
	else
	{
		// printf( "mbuf_len:        %d\n", mbuf_len( pkt ) );
		//printf( "mbuf_pkthdr_len: %d\n", mbuf_pkthdr_len( pkt ) );

		len = mbuf_pkthdr_len( pkt ) + 14; /* XXX: they took it! */
		data = mbuf_pkthdr_header( pkt );
	}

	/* FIXME: we won't fragment a chunk */
	assert( len <= NB_PKT_SIZE );

	/* get a packet to copy into */
	data_dest = alloc_databuf( nb );
	assert( data_dest != NULL );

	/* get the next producer desc */
	desc = get_prod_desc( q );
	assert( desc != NULL );

	/* copy the data */
	memcpy( data_dest, data, len );

	/* fill out the desc */
	desc->length = len;
	desc->data = data_dest;

	/* dump some data */
#if COPY_DUMP
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
		printf( "%s-data[%d]: %s\n", tx ? "TX" : "RX", 
			desc->length, sbuf );
	}
#endif

	/* all done */
}


/* take a data buffer off the free list */
void*
alloc_databuf( struct netbuf *nb )
{
	void **ret;
	
	ret = nb->free;
	if( ret == NULL )
		return NULL; /* no more free buffers :( */


	// printf( "alloc dataptr %p\n", ret );

	nb->free = *ret;

	/* write crap into it */
	memset( ret, 0x55 /* like rx2600s */, NB_PKT_SIZE );

	return ret;
}

/* put a buffer on the free list */
void
netbuf_free_data( struct netbuf *nb, void *data )
{
	void **cur;

	assert( (((unsigned)data) & 0x7ff) == 0 );

	// printf( "freeing dataptr %p\n", data );

	cur = (void*) data;
	
	/* cur points to last free guy */
	*cur = nb->free;
	
	/* head is now cur */
	nb->free = cur;
}

/* get the next producer to write something into */
struct netbuf_desc *
get_prod_desc( struct netbuf_q *q )
{
	struct netbuf_desc *desc;

	/* check for loop */
	if( (q->prod + 1) % q->nents == q->cons )
		return NULL;

	/* next desc to produce into */
	desc = &q->ring[q->prod];

	/* increment the pointer */
	q->prod = (q->prod + 1) % q->nents;

	return desc;
}

struct netbuf_desc *
get_cons_desc( struct netbuf_q *q )
{
	struct netbuf_desc *desc;

	/* nothing new */
	if( q->cons == q->prod )
		return NULL;

	/* next desc to produce into */
	desc = &q->ring[q->cons];

	/* increment the pointer */
	q->cons = (q->cons + 1) % q->nents;

	return desc;
}



struct netbuf *
netbuf_init( void * start, unsigned len )
{
	struct netbuf *netbuf;
	char *buf;
	int i;

	/* zero out the thing */
	memset( (void *)start, 0, len );

	/* work out where the header goes */
	buf = start;

	netbuf = (void*) buf;

	printf( "IOKit thinks netbuf is %p\n", netbuf );

	/* init the lock */
	// lck_spin_init( &netbuf->lock, NULL, NULL );
	netbuf->lock = 0;
	
	/* and the free pointer */
	netbuf->free = NULL;

	/* work out where the RX header is */
	buf += sizeof( *netbuf );
	netbuf->rx = (void*) buf;
	netbuf->rx->nents = NB_RX_ENTS;
	
	/* and TX header */
	netbuf->tx = netbuf->rx + 1;
	netbuf->tx->nents = NB_TX_ENTS;

	/* after the end of TX */
	buf = (void*) (netbuf->tx + 1);

	/* now for the RX descs */
	netbuf->rx->ring = (void*) buf;
	netbuf->rx->prod = netbuf->rx->cons = 0;

	/* and the TX ring */
	netbuf->tx->ring = netbuf->rx->ring + netbuf->rx->nents;
	netbuf->tx->prod = netbuf->tx->cons = 0;

	/* work out the end of TX */
	buf = (char*) (netbuf->tx->ring + netbuf->tx->nents);
	
	/* align that to 2048 packet boundary */
	if( ((unsigned) buf) & (NB_PKT_SIZE-1) )
	{
		buf = (void*)((((unsigned)buf)&(~(NB_PKT_SIZE-1)))+NB_PKT_SIZE);
		printf( "Aligned buf to %p\n", buf );
	}

	/* now make free packets */
	i = 0;
	while( buf < (((char*)start)+len) )
	{
		/* free it */
		netbuf_free_data( netbuf, buf );

		/* next */
		buf += NB_PKT_SIZE;
		i++;
	}

	/* Should be done! */
	printf( "netbuf init done, freed %d pkts, last is %p\n", 
		i, netbuf->free );

	return netbuf;
}


/**** XXX: locking! ****/
extern int netbuf_testandset(int*);

#define LOCK_IT 1

void 
netbuf_lock(struct netbuf *nb)
{
#if LOCK_IT
	// printf( "locking lock...\n" );
	while( netbuf_testandset(&nb->lock) )
		L4_Yield();
	// printf( "lock locked!\n" );
#endif
}

void 
netbuf_unlock(struct netbuf *nb)
{
#if LOCK_IT
	// printf("unlocking lock...\n");
	nb->lock = 0;
#endif
}

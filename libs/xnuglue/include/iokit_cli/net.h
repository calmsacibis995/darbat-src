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

/* IOKit client network buffer */
/* slow hacked-up copy interface */

#define NB_PKT_SIZE 2048
#define NB_RX_ENTS 64
#define NB_TX_ENTS 64

struct netbuf_desc
{
	/* length of buffer */
	unsigned length;

	/* pointer to data */
	void *data;

	/* FIXME: flags? more bits? tag? */
};

/* a single TX or RX ring */
struct netbuf_q
{
	/* number of items in the ring */
	unsigned nents;

	/* producer and consumer pointers */
	unsigned prod;
	unsigned cons;

	/* pointer to the start of the ring */
	struct netbuf_desc *ring;
};


/* describes a copy/transfer region */
struct netbuf
{
	/* mutex */
	/* FIXME: probably want to L4-ify this later */
	int  lock;
	
	/* rx_descs */
	struct netbuf_q *rx;

	/* tx descs */
	struct netbuf_q *tx;

	/* first free buffer */
	void **free;
};



/* interface functions */
struct netbuf *netbuf_init( void * start, unsigned len );

void copy_packet_in( struct netbuf *nb, struct netbuf_q *q, 
		     mbuf_t pkt, int tx );

void *alloc_databuf( struct netbuf *nb );
void netbuf_free_data( struct netbuf *nb, void *data );

struct netbuf_desc *get_prod_desc( struct netbuf_q *q );
struct netbuf_desc *get_cons_desc( struct netbuf_q *q );

void netbuf_lock(struct netbuf *nb);
void netbuf_unlock(struct netbuf *nb);



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
/* This is a BSD/Linux mash-up file */

/*
 * New driver for Marvell Yukon 2 chipset.
 * Based on earlier sk98lin, and skge driver.
 *
 * This driver intentionally does not support all the features
 * of the original driver such as link fail-over and link management because
 * those should be done at higher levels.
 *
 * Copyright (C) 2005 Stephen Hemminger <shemminger@osdl.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*	$OpenBSD: if_sk.c,v 1.100 2006/04/23 21:02:58 brad Exp $	*/

/*
 * Copyright (c) 1997, 1998, 1999, 2000
 *	Bill Paul <wpaul@ctr.columbia.edu>.  All rights reserved.
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
 *	This product includes software developed by Bill Paul.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: /c/ncvs/src/sys/pci/if_sk.c,v 1.20 2000/04/22 02:16:37 wpaul Exp $
 */

/*
 * Copyright (c) 2003 Nathan L. Binkert <binkertn@umich.edu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * SysKonnect SK-NET gigabit ethernet driver for FreeBSD. Supports
 * the SK-984x series adapters, both single port and dual port.
 * References:
 * 	The XaQti XMAC II datasheet,
 * http://www.freebsd.org/~wpaul/SysKonnect/xmacii_datasheet_rev_c_9-29.pdf
 *	The SysKonnect GEnesis manual, http://www.syskonnect.com
 *
 * Note: XaQti has been acquired by Vitesse, and Vitesse does not have the
 * XMAC II datasheet online. I have put my copy at people.freebsd.org as a
 * convenience to others until Vitesse corrects this problem:
 *
 * http://people.freebsd.org/~wpaul/SysKonnect/xmacii_datasheet_rev_c_9-29.pdf
 *
 * Written by Bill Paul <wpaul@ee.columbia.edu>
 * Department of Electrical Engineering
 * Columbia University, New York City
 */

/*
 * The SysKonnect gigabit ethernet adapters consist of two main
 * components: the SysKonnect GEnesis controller chip and the XaQti Corp.
 * XMAC II gigabit ethernet MAC. The XMAC provides all of the MAC
 * components and a PHY while the GEnesis controller provides a PCI
 * interface with DMA support. Each card may have between 512K and
 * 2MB of SRAM on board depending on the configuration.
 *
 * The SysKonnect GEnesis controller can have either one or two XMAC
 * chips connected to it, allowing single or dual port NIC configurations.
 * SysKonnect has the distinction of being the only vendor on the market
 * with a dual port gigabit ethernet NIC. The GEnesis provides dual FIFOs,
 * dual DMA queues, packet/MAC/transmit arbiters and direct access to the
 * XMAC registers. This driver takes advantage of these features to allow
 * both XMACs to operate as independent interfaces.
 */


// Our card!!! (I think...)
// CHIP_ID_YUKON_EC   = 0xb6, /* Chip ID for YUKON-2 EC */

#define MTU 1500
#define ETH_HLEN 14
#define POLL_TIMEOUT 100


#include "yukonosx.h"

//#define DPRINTFN(n,x)   if (skdebug >= (n)) printf x
#define DPRINTFN(n,x)   printf x
#define DPRINTF(x)

/**** CEG Stuff ****/
static void sk_dump_isr( unsigned int status, char *msg );
static void sk_dump_hw_err(void);
static void dump_yukon_gpsr(void);
static void dump_marvel_phy_ints( yukonosx *yosx );
static void dump_link_status( yukonosx *yosx );
static void check_queues( yukonosx *yosx );
static void dump_phy_stats(void);


#define ETH_GSTRING_LEN 20
static const struct sky2_stat 
{
        char name[ETH_GSTRING_LEN];
        UInt16 offset;
} sky2_stats[] = {
        { "tx_bytes",      GM_TXO_OK_HI },
        { "rx_bytes",      GM_RXO_OK_HI },
        { "tx_broadcast",  GM_TXF_BC_OK },
        { "rx_broadcast",  GM_RXF_BC_OK },
        { "tx_multicast",  GM_TXF_MC_OK },
        { "rx_multicast",  GM_RXF_MC_OK },
        { "tx_unicast",    GM_TXF_UC_OK },
        { "rx_unicast",    GM_RXF_UC_OK },
        { "tx_mac_pause",  GM_TXF_MPAUSE },
        { "rx_mac_pause",  GM_RXF_MPAUSE },
        { "collisions",    GM_TXF_SNG_COL },
        { "late_collision",GM_TXF_LAT_COL },
        { "aborted",       GM_TXF_ABO_COL },
        { "multi_collisions", GM_TXF_MUL_COL },
        { "fifo_underrun", GM_TXE_FIFO_UR },
        { "fifo_overflow", GM_RXE_FIFO_OV },
        { "rx_toolong",    GM_RXF_LNG_ERR },
        { "rx_jabber",     GM_RXF_JAB_PKT },
        { "rx_runt",       GM_RXE_FRAG },
        { "rx_too_long",   GM_RXF_LNG_ERR },
        { "rx_fcs_error",   GM_RXF_FCS_ERR },
};


#define SK_SETBIT(sc, reg, x)		\
	CSR_WRITE_4(sc, reg, CSR_READ_4(sc, reg) | x)

#define SK_CLRBIT(sc, reg, x)		\
	CSR_WRITE_4(sc, reg, CSR_READ_4(sc, reg) & ~x)

#define SK_WIN_SETBIT_4(sc, reg, x)	\
	sk_win_write_4(sc, reg, sk_win_read_4(sc, reg) | x)

#define SK_WIN_CLRBIT_4(sc, reg, x)	\
	sk_win_write_4(sc, reg, sk_win_read_4(sc, reg) & ~x)

#define SK_WIN_SETBIT_2(sc, reg, x)	\
	sk_win_write_2(sc, reg, sk_win_read_2(sc, reg) | x)

#define SK_WIN_CLRBIT_2(sc, reg, x)	\
	sk_win_write_2(sc, reg, sk_win_read_2(sc, reg) & ~x)


#define sky2_write32(a, b, c) CSR_WRITE_4(a, b, c)
#define sky2_read32( a, b ) CSR_READ_4(a, b)

#define sky2_write16(a, b, c) CSR_WRITE_2(a, b, c)
#define sky2_read16( a, b ) CSR_READ_2(a, b)

#define sky2_write8(a, b, c) CSR_WRITE_1(a, b, c)
#define sky2_read8( a, b ) CSR_READ_1(a, b)

#define super IOEthernetController
OSDefineMetaClassAndStructors(yukonosx, IOEthernetController)

static inline UInt32
sk_win_read_4(struct sk_softc *sc, UInt32 reg)
{
	return CSR_READ_4(sc, reg);
}

static inline UInt16
sk_win_read_2(struct sk_softc *sc, UInt32 reg)
{
	return CSR_READ_2(sc, reg);
}

static inline UInt8
sk_win_read_1(struct sk_softc *sc, UInt32 reg)
{
	//printf("doing sk_win_read_1\n" );
	return CSR_READ_1(sc, reg);
}

static inline void
sk_win_write_4(struct sk_softc *sc, u_int32_t reg, UInt32 x)
{
	CSR_WRITE_4(sc, reg, x);
}

static inline void
sk_win_write_2(struct sk_softc *sc, u_int32_t reg, UInt16 x)
{
	CSR_WRITE_2(sc, reg, x);
}

static inline void
sk_win_write_1(struct sk_softc *sc, u_int32_t reg, UInt8 x)
{
	CSR_WRITE_1(sc, reg, x);
}


static void
ypanic( const char *msg )
{
	IOLog( "YukonOSX panic: %s", msg );
	asm( "int $3" );
}

bool yukonosx::readPHY(UInt8 phy, UInt8 reg, UInt16 *data_p)
{
	int	i;
	UInt16	val;

        SK_YU_WRITE_2(sc_if, YUKON_SMICR, YU_SMICR_PHYAD(phy) |
             YU_SMICR_REGAD(reg) | YU_SMICR_OP_READ);
        
        for (i = 0; i < SK_TIMEOUT; i++) {
                DELAY(1);
                val = SK_YU_READ_2(sc_if, YUKON_SMICR);
                if (val & YU_SMICR_READ_VALID)
                        break;
        }

        if (i == SK_TIMEOUT)  {
		IOLog("yukonosx: phy %d failed to come ready\n", phy);
		return false;
        }
        
        DPRINTFN(9, ("sk_marv_miibus_readreg: i=%d, timeout=%d\n", i,
                     SK_TIMEOUT));

        val = SK_YU_READ_2(sc_if, YUKON_SMIDR);

        DPRINTFN(9, ("sk_marv_miibus_readreg phy=%d, reg=%#x, val=%#x\n",
                     phy, reg, val));

	*data_p = val;
	return true;
}

bool
yukonosx::writePHY(UInt8 phy, UInt8 reg, UInt16 val)
{
	int	i;

       DPRINTFN(9, ("sk_marv_miibus_writereg phy=%d reg=%#x val=%#x\n",
                     phy, reg, val));

        SK_YU_WRITE_2(sc_if, YUKON_SMIDR, val);
        SK_YU_WRITE_2(sc_if, YUKON_SMICR, YU_SMICR_PHYAD(phy) |
                      YU_SMICR_REGAD(reg) | YU_SMICR_OP_WRITE);

        for (i = 0; i < SK_TIMEOUT; i++) {
                IODelay(1);
                if (SK_YU_READ_2(sc_if, YUKON_SMICR) & YU_SMICR_BUSY)
                        break;
        }

        if (i == SK_TIMEOUT) {
		IOLog("yukonosx: phy %d write timed out\n", phy);
		return false;
	}

	return true;
}

bool yukonosx::initTx()
{

	assert( sizeof( *tx ) == 8 );
	bzero(ring->txRing, sizeof(TxDesc) * SK_TX_RING_CNT);

	// OpenBSD syncs the dma ring at the end.  I do not think we
	// need to do this on any platform which the IOKit supports
	// for now
	//
	// -gl
	return true;
}

bool yukonosx::initRx()
{
	assert( sizeof( RxDesc ) == 8 );

	/* zero the descriptors */
	bzero(ring->rxRing, sizeof(RxDesc) * SK_RX_RING_CNT);

	/* and the shadow */
	bzero(ring->tag_list, sizeof(ring->tag_list[0]) * SK_RX_RING_CNT);

	return true;
}

/* we have received a buffer into 'tag', size specified by size */
void yukonosx::rx_good_packet( void *tag, unsigned size )
{
	mbuf_t pkt; /* packet to shove back in to card */
	mbuf_t input_pkt;  /* packet to input to higher layers */
	bool   replaced;
	
	/* the tag is a pointer to an mbuf */
	pkt = (mbuf_t) tag;
	assert( pkt != NULL );

	/* get another mbuf to recv into */
	input_pkt = replaceOrCopyPacket( &pkt, size, &replaced );

	if( input_pkt == NULL )
	{
		IOLog( "YukonOSX: no more RX packets available!!\n" );
		input_pkt = pkt;
	}
	else
	{
		/* submit (old or new) pkt back into the RX queue */
		free_rx_mbuf( pkt );

		/* Tell chip about available it */
		sky2_write16(hw, Y2_QADDR(Q_R1, PREF_UNIT_PUT_IDX), rx_put);
	}

		
	/* either way, shove the input packet up into the higher layers */
	/* XXX: 0x1 == kInputOptionQueuePacket, but headers won't work? */
	networkIface->inputPacket( input_pkt, size, 0x1 );
	packets_queued = 1;
}

/* XXX */
extern "C" void handle_tx_done( void * );

void yukonosx::done_tx_packet( StDesc *le )
{
	TxDesc *tx;
	void *data;

	/* find what we sent */
	tx = &ring->txRing[tx_cons];

	/* the data we sent */
	data = (void*) tx->tx.addr;

	/* increment the tx consumer */
	tx_cons = (tx_cons + 1) % SK_TX_RING_CNT;

	/* zero it */
	tx->tx.addr = NULL;
	tx->length = 0;
        tx->ctrl = 0;
        tx->opcode = 0;

	/* free the data, or whatever */
	handle_tx_done( data );
}

/* pull the front packet off the recv queue.
 * Status etc. details are in le
 */
void yukonosx::rx_packet( StDesc *le )
{
	unsigned old_idx;
	RxDesc *rx;
	void   *tag;
	unsigned size = 0, status = 0;
	
	/* Find the tag & rx */
	tag = ring->tag_list[rx_check];
	rx = &ring->rxRing[rx_check];
	old_idx = rx_check;

	// printf( "recv rx->length was %d\n", rx->length );

	/* next advance the recv pointer */
	/* FIXME: dynamic buf count?? */
	rx_check = (rx_check + 1) % SK_RX_RING_CNT;

	/* interesting bits of the status desc */
	size = le->length;
	status = le->status;

	/* scrub the old stuff */
	le->length = 0;
	le->status = 0;
	le->link = 0;
	le->opcode = 0;
	rx->addr = 0;
	rx->length = 0;
	rx->ctrl = 0;
	rx->opcode = 0;
	ring->tag_list[old_idx] = NULL;

	/* check the status */
	if( (status & GMR_FS_RX_OK) == 0 )
	{
		/* resubmit the packet */
		// IOLog( "packet resubmit!\n" );
		// ypanic("resubmit!");
		free_rx_mbuf( (mbuf_t) tag );
		
		/* kick the card */
		sky2_write16(hw, Y2_QADDR(Q_R1, PREF_UNIT_PUT_IDX), rx_put);
		return;
	}

	/* we got some data, hand it to the next level */
	// IOLog( "doing RX good packet, tag %p, size 0x%x\n", tag, size );
	rx_good_packet( tag, size );
}

void yukonosx::handleBMU()
{
	UInt16 hwidx, old_idx;

	sky2_write32(hw, STAT_CTRL, SC_STAT_CLR_IRQ);

	/* FIXME: may need to kick the card here... */

	hwidx = sky2_read16(hw, STAT_PUT_IDX);

	/* until we catch up to where the hardware's written... */
	while( st_idx != hwidx )
	{
		/* this pointer */
		StDesc *le = &ring->stRing[st_idx];
		
		/* increment next pointer */
		old_idx = st_idx;
		st_idx = (st_idx + 1) % STATUS_RING_SIZE;

		if( le->link != 0 )
			ypanic( "Strange MAC in link reg?!\n" );

		/* FIXME: check if we're up */

		/* work out what this status guy says */
		switch( le->opcode & ~HW_OWNER )
		{
			case OP_RXSTAT:
/*
				printf( "st[%d] says rx (0x%x, 0x%x, 0x%x, 0x%x)\n", 
					old_idx, 
					le->status, le->length, 
					le->link, le->opcode );
				*/
				rx_packet( le );

				break;

			case OP_TXINDEXLE:
/*				printf( "st[%d] says tx\n", old_idx ); */
				done_tx_packet( le );
				break;

			default:
				ypanic( "strange opcode in status list?\n" );
		}
	}
}


void yukonosx::intHandler()
{
	UInt32 status;

        // status = sky2_read32(hw, B0_Y2_SP_ISRC2);
	status = CSR_READ_4(sc_if, SK_ISR);
        if( status == 0 || status == ~0 )
	{
		// IOLog( "YukonOSX: ISR reports no interrupt\n" );
		return;
	}

	/* BMU interrupts */	
        if( status & Y2_IS_STAT_BMU )
	{
		// IOLog( "YukonOSX: handling BMU\n" );
		handleBMU();
	}

	/* hopefully these ones go away by themselves :) */
        if (status & Y2_IS_IRQ_PHY1)
	{
		UInt16 phy_stat;

		IOLog( "YukonOSX: got PHY1 intr\n" );
		readPHY((UInt8) 0, (UInt8) PHY_MARV_INT_STAT, &phy_stat );
		printf( "PHY_MARV_INT_STAT: 0x%x\n", phy_stat );

		dump_link_status( this );
	}

        if (status & Y2_IS_IRQ_MAC1)
		IOLog( "YukonOSX: got MAC1 intr\n" );

        if( status & Y2_IS_IRQ_PHY2 || status & Y2_IS_IRQ_MAC2 )
		ypanic( "eep, action on PHY/MAC 2!\n" );

	/* I guess this clears the interrupt? */
        // sky2_write32(hw, B0_Y2_SP_ICR, 2);

	/* do we need to flush the input queue */
	if( packets_queued )
	{
		networkIface->flushInputQueue();
		packets_queued = 0;
	}
}


void yukonosx::interruptOccurred()
{
	// UInt32	status;
	// int	claimed = 0;

	// ypanic( "actual interrupt delivered!\n" );

	/* actual int handler */
	intHandler();
}

IOReturn yukonosx::setPromiscuousMode( bool active )
{
	/* FIXME: this doesn't really work */

	IOLog( "Trying to set promiscuous on yukon, ignoring\n" );
	
	// return kIOReturnSuccess;
	return kIOReturnUnsupported;
}

bool yukonosx::reset()
{
	UInt32	imtimer_ticks;

	IOLog("yukonosx::resetChip\n");

	CSR_WRITE_2(sc, SK_CSR, SK_CSR_SW_RESET);
        CSR_WRITE_2(sc, SK_CSR, SK_CSR_MASTER_RESET);
	// yukon specific
        CSR_WRITE_2(sc, SK_LINK_CTRL, SK_LINK_RESET_SET);

        IODelay(1000);
        CSR_WRITE_2(sc, SK_CSR, SK_CSR_SW_UNRESET);
        IODelay(2);
        CSR_WRITE_2(sc, SK_CSR, SK_CSR_MASTER_UNRESET);
        // Yukon specific
        CSR_WRITE_2(sc, SK_LINK_CTRL, SK_LINK_RESET_CLEAR);

        DPRINTFN(2, ("sk_reset: sk_csr=%x\n", CSR_READ_2(sc, SK_CSR)));
        DPRINTFN(2, ("sk_reset: sk_link_ctrl=%x\n",
                     CSR_READ_2(sc, SK_LINK_CTRL)));

        /* Enable RAM interface */
        sk_win_write_4(0/*sc*/, SK_RAMCTL, SK_RAMCTL_UNRESET);

	{
		/* Power stuff as suggested by Linux */
		
		CSR_WRITE_1(0, SK_POWER, 
			    (unsigned char)(PC_VAUX_ENA | PC_VCC_ENA |
					    PC_VAUX_OFF | PC_VCC_ON));
	}
	

        /*
         * Configure interrupt moderation. The moderation timer
         * defers interrupts specified in the interrupt moderation
         * timer mask based on the timeout specified in the interrupt
         * moderation timer init register. Each bit in the timer
         * register represents one tick, so to specify a timeout in
         * microseconds, we have to multiply by the correct number of
         * ticks-per-microsecond.
         */
	// XXX: what should the timer be for Yukon-II?
	// XXX: I guess this will work since it is at the end of the
	// XXX: switch case, at default:
	// XXX:
	// XXX: -gl
	imtimer_ticks = SK_IMTIMER_TICKS_YUKON;

        sk_win_write_4(/*sc*/0, SK_IMTIMERINIT, SK_IM_USECS(100));
        sk_win_write_4(/*sc*/0, SK_IMMR, SK_ISR_TX1_S_EOF|SK_ISR_TX2_S_EOF|
            SK_ISR_RX1_EOF|SK_ISR_RX2_EOF);
        sk_win_write_1(/*sc*/0, SK_IMTIMERCTL, SK_IMCTL_START);

	return true;
}

bool yukonosx::stopChip(void)
{
	// TODO:
	// write the driver is loaded led to turn it off
	// not that it matters, since the iMac does not have the LED
	// visible anyway

	// reset();

	IOLog( "YukonOSX: stopChip called\n" );

	return true;
}

bool yukonosx::ifup_bsd()
{
	UInt8		skrs;
	UInt16		reg;

	skrs = sk_win_read_1(/*sc*/0, SK_EPROM0);
        if (skrs == 0x00)
        	ramSize = 0x20000;
        else
        	ramSize = skrs * (1<<12);

	ramBufferOffset = SK_RBOFF_0;

	// divide the SRAM buffers eventually between tx and rx
	// (note: we do not have to, but this happens to be what the
	// OpenBSD driver does).
	// -gl
	{	// this code is specifically for Yukon-II
		// or those with a single MAC
		UInt32	chunk, val;

		chunk = ramSize / 2;
		val = ramBufferOffset / sizeof(UInt64);
		rxRamStart = val;
		val += (chunk / sizeof(UInt64));
		rxRamEnd = val - 1;
		txRamStart = val;
		val += (chunk / sizeof(UInt64));
		txRamEnd = val - 1;
	}

	IOLog("yukonosx: rxStart %p rxEnd %p txStart %p txEnd %p\n",
	    (void *)rxRamStart, (void *)rxRamEnd,
	    (void *)txRamStart, (void *)txRamEnd);

	// write the rambuffer locations to the chip
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_CTLTST, SK_RBCTL_UNRESET);
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_START, rxRamStart);
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_WR_PTR, rxRamStart);
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_RD_PTR, rxRamStart);
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_END, rxRamEnd);
        SK_IF_WRITE_4(sc_if, 0, SK_RXRB1_CTLTST, SK_RBCTL_ON);

        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_CTLTST, SK_RBCTL_UNRESET);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_CTLTST, SK_RBCTL_STORENFWD_ON);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_START, txRamStart);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_WR_PTR, txRamStart);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_RD_PTR, txRamStart);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_END, txRamEnd);
        SK_IF_WRITE_4(sc_if, 1, SK_TXRBS1_CTLTST, SK_RBCTL_ON);

	// allocate dma bufs
	// XXX: do we not have to call ->prepare()?
	mDesc = IOBufferMemoryDescriptor::withOptions(kIOMemoryUnshared, 
	    sizeof(Ring), PAGE_SIZE * 2);
	// alias it with the actual structure
	ring = (Ring *)mDesc->getBytesNoCopy();

	initTx();

	check_queues( this );

	initRx();

	check_queues( this );

	ypanic( "ifup_bsd stop\n" );

	// configure transmit arbiters
        SK_IF_WRITE_1(sc_if, 0, SK_TXAR1_COUNTERCTL,
            SK_TXARCTL_ON|SK_TXARCTL_FSYNC_ON);


        /* Configure BMUs */
        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_BMU_CSR, SK_RXBMU_ONLINE);

	/* Linux suggest we do this... */
        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_BMU_CSR, SK_RXBMU_CLR_IRQ_PAR);


        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_CURADDR_LO,
		      (UInt32) &ring->rxRing[0] );
//		      SK_RX_RING_ADDR(sc_if, 0));
        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_CURADDR_HI, 0);

        SK_IF_WRITE_4(sc_if, 1, SK_TXQS1_BMU_CSR, SK_TXBMU_ONLINE);
        SK_IF_WRITE_4(sc_if, 1, SK_TXQS1_CURADDR_LO,
		      (UInt32) &ring->txRing[0]);
//		      SK_TX_RING_ADDR(sc_if, 0));
        SK_IF_WRITE_4(sc_if, 1, SK_TXQS1_CURADDR_HI, 0);


	IOLog( "YukonOSX: doing RX BMU start!\n" );
        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_BMU_CSR, SK_RXBMU_RX_START);

	IOLog( "YukonOSX: doing TX BMU start!\n" );
        // SK_IF_WRITE_4(sc_if, 0, SK_TXQ1_BMU_CSR, SK_TXBMU_TX_START);
	CSR_WRITE_4(0, SK_BMU_TXS_CSR1, SK_TXBMU_TX_START );


	// XXX: do not enable intr just yet
	intrMask = 0;
	// intrMask |= SK_INTRS1;
	// intrMask |= SK_ISR_EXTERNAL_REG;
	intrMask = 0xffffffff;
        CSR_WRITE_4(sc, SK_IMR, intrMask);

	// yukon specific
	reg = SK_YU_READ_2(sc_if, YUKON_GPCR);
	reg |= YU_GPCR_TXEN | YU_GPCR_RXEN;
	reg &= ~(YU_GPCR_SPEED_EN | YU_GPCR_DPLX_EN);
	printf( "writing GPCR reg 0x%x\n", reg );
	SK_YU_WRITE_2(sc_if, YUKON_GPCR, reg);

        /* Start BMUs. */
        SK_IF_WRITE_4(sc_if, 0, SK_RXQ1_BMU_CSR, SK_RXBMU_RX_START);

	return 0;
}


/* Assign Ram Buffer allocation.
 * start and end are in units of 4k bytes
 * ram registers are in units of 64bit words
 */
void 
sky2_ramset(UInt16 q, UInt8 startk, UInt8 endk)
{
        UInt32 start, end;

        start = startk * 4096/8;
        end = (endk * 4096/8) - 1;

        sky2_write8(hw, RB_ADDR(q, RB_CTRL), RB_RST_CLR);
        sky2_write32(hw, RB_ADDR(q, RB_START), start);
        sky2_write32(hw, RB_ADDR(q, RB_END), end);
        sky2_write32(hw, RB_ADDR(q, RB_WP), start);
        sky2_write32(hw, RB_ADDR(q, RB_RP), start);

        if (q == Q_R1 || q == Q_R2)
	{
                UInt32 space = (endk - startk) * 4096/8;
                UInt32 tp = space - space/4;

                /* On receive queue's set the thresholds
                 * give receiver priority when > 3/4 full
                 * send pause when down to 2K
                 */
                sky2_write32(hw, RB_ADDR(q, RB_RX_UTHP), tp);
                sky2_write32(hw, RB_ADDR(q, RB_RX_LTHP), space/2);

                tp = space - 2048/8;
                sky2_write32(hw, RB_ADDR(q, RB_RX_UTPP), tp);
                sky2_write32(hw, RB_ADDR(q, RB_RX_LTPP), space/4);
        }
	else
	{
                /* Enable store & forward on Tx queue's because
                 * Tx FIFO is only 1K on Yukon
                 */
                // sky2_write8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_STFWD);
        }

        sky2_write8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_OP_MD);
        sky2_read8(hw, RB_ADDR(q, RB_CTRL));
}


/* Setup Bus Memory Interface */
void yukonosx::sky2_qset( UInt16 q )
{
        sky2_write32( 0, Q_ADDR(q, Q_CSR), BMU_CLR_RESET );
        sky2_write32( 0, Q_ADDR(q, Q_CSR), BMU_OPER_INIT );
        sky2_write32( 0, Q_ADDR(q, Q_CSR), BMU_FIFO_OP_ON );
        sky2_write32( 0, Q_ADDR(q, Q_WM),  BMU_WM_DEFAULT );
}

static UInt16
gma_read16(unsigned port, unsigned reg)
{
        return sky2_read16(0, SK_GMAC_REG(port,reg));
}

static void 
gma_write16(unsigned port, int r, UInt16 v)
{
        sky2_write16(0, SK_GMAC_REG(port,r), v);
}

static UInt32 
gma_read32(unsigned port, unsigned reg)
{
        unsigned base = SK_GMAC_REG(port, reg);
        return (UInt32) sky2_read16(0, base)
                | (UInt32) sky2_read16(0, base+4) << 16;
}

static void 
gma_set_addr(unsigned port, unsigned reg, const UInt8 *addr)
{
         gma_write16(port, reg,  (UInt16) addr[0] | ((UInt16) addr[1] << 8));
         gma_write16(port, reg+4,(UInt16) addr[2] | ((UInt16) addr[3] << 8));
         gma_write16(port, reg+8,(UInt16) addr[4] | ((UInt16) addr[5] << 8));
}

#define PHY_RETRIES             1000

/* Access to external PHY */
static int 
gm_phy_write(unsigned port, UInt16 reg, UInt16 val)
{
        int i;

        gma_write16(port, GM_SMI_DATA, val);
        gma_write16(port, GM_SMI_CTRL,
                    GM_SMI_CT_PHY_AD(PHY_ADDR_MARV) | GM_SMI_CT_REG_AD(reg));

        for (i = 0; i < PHY_RETRIES; i++) {
                if (!(gma_read16(port, GM_SMI_CTRL) & GM_SMI_CT_BUSY))
                        return 0;
		DELAY(10);
        }

	ypanic( "phy write timeout\n" );

        return -1;
}

static int 
__gm_phy_read(unsigned port, UInt16 reg, UInt16 *val)
{
        int i;
	
        gma_write16(port, GM_SMI_CTRL, GM_SMI_CT_PHY_AD(PHY_ADDR_MARV)
                    | GM_SMI_CT_REG_AD(reg) | GM_SMI_CT_OP_RD);

        for (i = 0; i < PHY_RETRIES; i++) {
                if (gma_read16(port, GM_SMI_CTRL) & GM_SMI_CT_RD_VAL) {
                        *val = gma_read16(port, GM_SMI_DATA);
                        return 0;
                }

		DELAY(10);
        }

        return -1;
}

static UInt16 
gm_phy_read(unsigned port, UInt16 reg)
{
	UInt16 v = 0;
	
	if (__gm_phy_read(port, reg, &v) != 0)
                ypanic( "phy read timeout\n" );

	return v;
}


/* Setup prefetch unit registers. This is the interface between
 * hardware and driver list elements
 */
static void 
sky2_prefetch_init( UInt32 qaddr, UInt64 addr, UInt32 last)
{
        sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_SET);
        sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_CLR);
        sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_HI), 0);
        sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_LO), (UInt32) addr);
        sky2_write16(hw, Y2_QADDR(qaddr, PREF_UNIT_LAST_IDX), last);
        sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_OP_ON);

        sky2_read32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL));
}

static void 
sky2_phy_init( yukonosx *yosx, unsigned port)
{
        UInt16 ctrl, ct1000, adv, ledctrl, ledover;

        ctrl = gm_phy_read(port, PHY_MARV_PHY_CTRL);
	
	/* disable energy detect */
	ctrl &= ~PHY_M_PC_EN_DET_MSK;

	/* enable automatic crossover */
	ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO);

	gm_phy_write(port, PHY_MARV_PHY_CTRL, ctrl);

        ctrl = gm_phy_read(port, PHY_MARV_CTRL);
	ctrl &= ~PHY_CT_ANE;

        ctrl |= PHY_CT_RESET;
        gm_phy_write(port, PHY_MARV_CTRL, ctrl);

        ctrl = 0;
        ct1000 = 0;
        adv = PHY_AN_CSMA;

	ct1000 |= PHY_M_1000C_AFD;
	ct1000 |= PHY_M_1000C_AHD;
	adv |= PHY_M_AN_100_FD;
	adv |= PHY_M_AN_100_HD;
	adv |= PHY_M_AN_10_FD;
	adv |= PHY_M_AN_10_HD;

	/* Restart Auto-negotiation */
	ctrl |= PHY_CT_ANE | PHY_CT_RE_CFG;

        gm_phy_write(port, PHY_MARV_AUNE_ADV, adv);
        gm_phy_write(port, PHY_MARV_CTRL, ctrl);

        /* Setup Phy LED's */
        ledctrl = PHY_M_LED_PULS_DUR(PULS_170MS);
        ledover = 0;

	/* set Tx LED (LED_TX) to blink mode on Rx OR Tx activity */
	ledctrl |= PHY_M_LED_BLINK_RT(BLINK_84MS) | PHY_M_LEDC_TX_CTRL;
	/* turn off the Rx LED (LED_RX) */
	ledover |= PHY_M_LED_MO_RX(MO_LED_OFF);

	gm_phy_write(port, PHY_MARV_LED_CTRL, ledctrl);

        /* Enable phy interrupt on auto-negotiation complete (or link up) */
	// gm_phy_write(port, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL);
	gm_phy_write(port, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL  | PHY_M_IS_LST_CHANGE | PHY_M_IS_FIFO_ERROR );
	// yosx->writePHY(0, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL | PHY_M_IS_LST_CHANGE | PHY_M_IS_FIFO_ERROR );

}

/* Port related registers FIFO, and Arbiter */
#define SK_REG_LINUX(port,reg)        (((port)<<7)+(reg))


static void 
sky2_phy_stats( UInt64 *data, unsigned count )
{
        unsigned port = 0;
        unsigned i;

        data[0] = (UInt64) gma_read32(port, GM_TXO_OK_HI) << 32
		| (UInt64) gma_read32(port, GM_TXO_OK_LO);
        data[1] = (UInt64) gma_read32(port, GM_RXO_OK_HI) << 32
		| (UInt64) gma_read32(port, GM_RXO_OK_LO);

        for (i = 2; i < count; i++)
                data[i] = (UInt64) gma_read32(port, sky2_stats[i].offset);
}

/* Chip internal frequency for clock calculations */
static UInt32 
sky2_mhz()
{
	return 125;     /* 125 Mhz */
}

static UInt32 
sky2_us2clk(UInt32 us)
{
        return sky2_mhz() * us;
}

static int 
sky2_set_power_state()
{
        printf("sky2_set_power_state\n");
        sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);

	/* switch power to VCC (WA for VAUX problem) */
	sky2_write8(hw, B0_POWER_CTRL,
		    PC_VAUX_ENA | PC_VCC_ENA | PC_VAUX_OFF | PC_VCC_ON);

	/* disable Core Clock Division, */
	sky2_write32(hw, B2_Y2_CLK_CTRL, Y2_CLK_DIV_DIS);

	sky2_write8(hw, B2_Y2_CLK_GATE, 0);

        sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

        return 0;
}


static void 
sky2_phy_reset(unsigned port)
{
        UInt16 reg;

        /* disable all GMAC IRQ's */
        sky2_write8(hw, SK_REG_LINUX(port, GMAC_IRQ_MSK), 0);

        /* disable PHY IRQs */
        gm_phy_write(port, PHY_MARV_INT_MASK, 0);

        gma_write16(port, GM_MC_ADDR_H1, 0);        /* clear MC hash */
        gma_write16(port, GM_MC_ADDR_H2, 0);
        gma_write16(port, GM_MC_ADDR_H3, 0);
        gma_write16(port, GM_MC_ADDR_H4, 0);

        reg = gma_read16(port, GM_RX_CTRL);
        reg |= GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA;
        gma_write16(port, GM_RX_CTRL, reg);

        /* enable all GMAC IRQ's */
        // sky2_write8(hw, SK_REG_LINUX(port, GMAC_IRQ_MSK), 0xff);
}

static int 
sky2_reset( yukonosx *yosx )
{
        sky2_write8(hw, B0_CTST, CS_RST_CLR);

        /* disable ASF */
	sky2_write8(hw, B28_Y2_ASF_STAT_CMD, Y2_ASF_RESET);
	sky2_write16(hw, B0_CTST, Y2_ASF_DISABLE);

        /* do a SW reset */
        sky2_write8(hw, B0_CTST, CS_RST_SET);
        sky2_write8(hw, B0_CTST, CS_RST_CLR);

#if 0
        /* clear PCI errors, if any */
        status = sky2_pci_read16(hw, PCI_STATUS);

        sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
        sky2_pci_write16(hw, PCI_STATUS, status | PCI_STATUS_ERROR_BITS);
#else
	// FIXME: don't really need this?
        sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
#endif

        sky2_write8(hw, B0_CTST, CS_MRST_CLR);

#if 0
        /* clear any PEX errors */
        if (pci_find_capability(hw->pdev, PCI_CAP_ID_EXP)) 
                sky2_pci_write32(hw, PEX_UNC_ERR_STAT, 0xffffffffUL);
#endif

        sky2_set_power_state(); // (PCI_D0);

	sky2_write8(hw, SK_REG_LINUX(0, GMAC_LINK_CTRL), GMLC_RST_SET);
	sky2_write8(hw, SK_REG_LINUX(0, GMAC_LINK_CTRL), GMLC_RST_CLR);

	// FIXME: don't really need this?
        sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

        /* Clear I2C IRQ noise */
        sky2_write32(hw, B2_I2C_IRQ, 1);

        /* turn off hardware timer (unused) */
        sky2_write8(hw, B2_TI_CTRL, TIM_STOP);
        sky2_write8(hw, B2_TI_CTRL, TIM_CLR_IRQ);

        sky2_write8(hw, B0_Y2LED, LED_STAT_ON);

        /* Turn off descriptor polling */
        sky2_write32(hw, B28_DPT_CTRL, DPT_STOP);

        /* Turn off receive timestamp */
        sky2_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_STOP);
        sky2_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

        /* enable the Tx Arbiters */
	sky2_write8(hw, SK_REG_LINUX(0, TXA_CTRL), TXA_ENA_ARB);

        /* Initialize ram interface */
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_CTRL), RI_RST_CLR);

	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_R1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_XA1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_XS1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_R1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_XA1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_XS1), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_R2), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_XA2), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_WTO_XS2), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_R2), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_XA2), SK_RI_TO_53);
	sky2_write8(hw, RAM_BUFFER(0, B3_RI_RTO_XS2), SK_RI_TO_53);

        sky2_write32(hw, B0_HWE_IMSK, Y2_HWE_ALL_MASK);

	sky2_phy_reset(0);

        sky2_write32(hw, STAT_CTRL, SC_STAT_RST_SET);
        sky2_write32(hw, STAT_CTRL, SC_STAT_RST_CLR);

	
	UInt32 st_dma = (UInt32) yosx->ring->stRing;
	assert( (st_dma & 0xfff) == 0 );  /* seems to want 4k alignment?! */
        sky2_write32(hw, STAT_LIST_ADDR_LO, st_dma);
        sky2_write32(hw, STAT_LIST_ADDR_HI, 0);

        /* Set the list last index */
        sky2_write16(hw, STAT_LAST_IDX, STATUS_RING_SIZE - 1);

        /* These status setup values are copied from SysKonnect's driver */
	// sky2_write16(hw, STAT_TX_IDX_TH, 10);
	sky2_write16(hw, STAT_TX_IDX_TH, 1);
	sky2_write8(hw, STAT_FIFO_WM, 16);

	/* set Status-FIFO ISR watermark */
	sky2_write8(hw, STAT_FIFO_ISR_WM, 16);

	sky2_write32(hw, STAT_TX_TIMER_INI, sky2_us2clk(1000));
	sky2_write32(hw, STAT_ISR_TIMER_INI, sky2_us2clk(7));

        /* enable status unit */
        sky2_write32(hw, STAT_CTRL, SC_STAT_OP_ON);

        sky2_write8(hw, STAT_TX_TIMER_CTRL, TIM_START);
        sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
        sky2_write8(hw, STAT_ISR_TIMER_CTRL, TIM_START);

        return 0;
}

static void 
sky2_mac_init( yukonosx *yosx,  unsigned port )
{
        UInt16 reg;
        int i;
        const UInt8 *addr = yosx->myAddress.bytes;

        sky2_write32(hw, SK_REG_LINUX(port, GPHY_CTRL), GPC_RST_SET);
        sky2_write32(hw, SK_REG_LINUX(port, GPHY_CTRL), GPC_RST_CLR|GPC_ENA_PAUSE);

        sky2_write8(hw, SK_REG_LINUX(port, GMAC_CTRL), GMC_RST_CLR);

	reg = GM_GPCR_SPEED_1000 | GM_GPCR_SPEED_100 | GM_GPCR_DUP_FULL;

	/* XXX: disable pause frames */
	sky2_write32(hw, SK_REG_LINUX(port, GMAC_CTRL), GMC_PAUSE_OFF);

	reg |= GM_GPCR_FC_TX_DIS | GM_GPCR_FC_RX_DIS | GM_GPCR_AU_FCT_DIS;

        gma_write16(port, GM_GP_CTRL, reg);

        sky2_read16(hw, SK_REG_LINUX(port, GMAC_IRQ_SRC));

	/* Do the phy init */
	printf( "doing phy_init on port %d\n", port );
        sky2_phy_init(yosx, port);

        /* MIB clear */
        reg = gma_read16(port, GM_PHY_ADDR);
        gma_write16(port, GM_PHY_ADDR, reg | GM_PAR_MIB_CLR);

        for (i = 0; i < GM_MIB_CNT_SIZE; i++)
                gma_read16(port, GM_MIB_CNT_BASE + 8 * i);
        gma_write16(port, GM_PHY_ADDR, reg);

        /* transmit control */
        gma_write16(port, GM_TX_CTRL, TX_COL_THR(TX_COL_DEF));

        /* receive control reg: unicast + multicast + no FCS  */
        gma_write16(port, GM_RX_CTRL,
                    GM_RXCR_UCF_ENA | GM_RXCR_CRC_DIS | GM_RXCR_MCF_ENA);

        /* transmit flow control */
        gma_write16(port, GM_TX_FLOW_CTRL, 0xffff);

        /* transmit parameter */
        gma_write16(port, GM_TX_PARAM,
                    TX_JAM_LEN_VAL(TX_JAM_LEN_DEF) |
                    TX_JAM_IPG_VAL(TX_JAM_IPG_DEF) |
                    TX_IPG_JAM_DATA(TX_IPG_JAM_DEF) |
                    TX_BACK_OFF_LIM(TX_BOF_LIM_DEF));

        /* serial mode register */
        reg = DATA_BLIND_VAL(DATA_BLIND_DEF) |
                GM_SMOD_VLAN_ENA | IPG_DATA_VAL(IPG_DATA_DEF);

        if (MTU > ETH_DATA_LEN)
                reg |= GM_SMOD_JUMBO_ENA;

        gma_write16(port, GM_SERIAL_MODE, reg);

        /* virtual address for data */
        gma_set_addr(port, GM_SRC_ADDR_2L, addr);

        /* physical address: used for pause frames */
        gma_set_addr(port, GM_SRC_ADDR_1L, addr);

        /* ignore counter overflows */ /* well, don't ignore */
        gma_write16(port, GM_TX_IRQ_MSK, 1);
        gma_write16(port, GM_RX_IRQ_MSK, 1);
        gma_write16(port, GM_TR_IRQ_MSK, 1);

        /* Configure Rx MAC FIFO */
        sky2_write8(hw, SK_REG_LINUX(port, RX_GMF_CTRL_T), GMF_RST_CLR);
        sky2_write32(hw, SK_REG_LINUX(port, RX_GMF_CTRL_T),
                     GMF_OPER_ON | GMF_RX_F_FL_ON);

        /* Flush Rx MAC FIFO on any flow control or error */
        sky2_write16(hw, SK_REG_LINUX(port, RX_GMF_FL_MSK), GMR_FS_ANY_ERR);

        /* Set threshold to 0xa (64 bytes)
         *  ASF disabled so no need to do WA dev #4.30
         */
        sky2_write16(hw, SK_REG_LINUX(port, RX_GMF_FL_THR), RX_GMF_FL_THR_DEF);

        /* Configure Tx MAC FIFO */
        sky2_write8(hw, SK_REG_LINUX(port, TX_GMF_CTRL_T), GMF_RST_CLR);
        sky2_write16(hw, SK_REG_LINUX(port, TX_GMF_CTRL_T), GMF_OPER_ON);
}


static void 
sky2_link_up()
{
        unsigned port = 0;
        UInt16 reg = 0;

        /* Enable Transmit FIFO Underrun */
	// don't need these from the GMAC unless debugging... 
	// reg = GM_IS_TX_COMPL | GM_IS_RX_COMPL; /* DBG: see mac rx/tx */
	// reg = 0xff; /* see everything */
	reg |= GMAC_DEF_MSK;
        sky2_write8(hw, SK_REG_LINUX(port, GMAC_IRQ_MSK),  reg);

        reg = gma_read16(port, GM_GP_CTRL);
	reg &= ~GM_GPCR_AU_ALL_DIS;
	reg |= GM_GPCR_DUP_FULL;

	/** XXX: enable either PROM or LOOP causes things not to work?! */
	/* promiscuous mode */
	// reg |= GM_GPCR_PROM_ENA;
	
	/* loopback enabled */
	// reg |= GM_GPCR_LOOP_ENA;


        /* enable Rx/Tx */
        reg |= GM_GPCR_RX_ENA | GM_GPCR_TX_ENA;
        gma_write16(port, GM_GP_CTRL, reg);
        gma_read16(port, GM_GP_CTRL);

        gm_phy_write(port, PHY_MARV_INT_MASK, PHY_M_DEF_MSK);

	// FIXME: need these?
        // netif_carrier_on(sky2->netdev);
        // netif_wake_queue(sky2->netdev);

        /* Turn on link LED */
        sky2_write8(hw, SK_REG_LINUX(port, LNK_LED_REG),
                    LINKLED_ON | LINKLED_BLINK_OFF | LINKLED_LINKSYNC_OFF);

	printf( "YukonOSX: done link up!\n" );
}

bool yukonosx::ifup_linux_1()
{
	/****** 
	 *
	 *      static int sky2_up(struct net_device *dev)
	 *
	 ******/

	unsigned int ramsize, rxspace;
	
	ramsize = sky2_read8(hw, B2_E_0);
 
	/* XXX: disable all interrupts */
	sky2_write32( hw, B0_IMSK, 0 );



	/* CEG: this value works out how much of the onboard RAM in the card
	 * is devoted to the tx and rx FIFOs for the MAC(s?)
	 */
	/* Give transmitter one third (rounded up) */
	rxspace = ramsize - (ramsize + 2) / 3;

	printf( "ramsize: 0x%x\n", ramsize );
	printf( "rxpsace: 0x%x\n", rxspace );

	sky2_ramset(Q_R1, 0, rxspace);
	sky2_ramset(Q_XA1, rxspace, ramsize);
	
	/* Make sure SyncQ is disabled */
	sky2_write8( hw, RB_ADDR(Q_XS1, RB_CTRL),
		     RB_RST_SET );
	
	sky2_qset( Q_XA1 );

	/* Set almost empty threshold */
	// XXX: not us
	// if (hw->chip_id == CHIP_ID_YUKON_EC_U && hw->chip_rev == 1)
	//	sky2_write16(hw, Q_ADDR(txqaddr[port], Q_AL), 0x1a0);
	
	sky2_prefetch_init( Q_XA1, (UInt64) ring->txRing, SK_TX_RING_CNT - 1 );
	
	return 0;
}


/* Tell chip where to start receive checksum.
 * Actually has two checksums, but set both same to avoid possible byte
 * order problems.
 */
static void 
rx_set_checksum( yukonosx *yosx )
{
#if 0
	RxDesc *rx = &yosx->ring->rxRing[1];

        rx->addr = (ETH_HLEN << 16) | ETH_HLEN;
        rx->ctrl = 0;
        rx->opcode = OP_TCPSTART | HW_OWNER;
#endif

	/* set it */
        sky2_write32( 0, Q_ADDR(Q_R1, Q_CSR), BMU_DIS_RX_CHKSUM );
}

bool yukonosx::ifup_linux_2()
{
	/****** 
	 *
	 *      static int sky2_rx_start(struct sky2_port *sky2)
	 *
	 ******/

	/* Setup Bus Memory Interface */
	// static void sky2_qset(struct sky2_hw *hw, u16 q)
	sky2_qset( Q_R1 );

	/* Setup prefetch unit registers. This is the interface between
	 * hardware and driver list elements
	 */
	sky2_prefetch_init(Q_R1, (UInt64) ring->rxRing, SK_RX_RING_CNT - 1);


	/** This is where Linux does RX queue initialisation... **/

	initRx();

	/** End RX queue init **/

	/* do this later than linux, after initRx */
        rx_set_checksum( this );

        /* Truncate oversize frames */

	// incompatable with BSD macros
	// sky2_write16(hw, SK_REG(0, RX_GMF_TR_THR), 1600); /* XXX */
	// sky2_write32(hw, SK_REG(0, RX_GMF_CTRL_T), RX_TRUNC_ON);

	/// XXX: assumes port == 0
	// sky2_write16(hw, RX_GMF_TR_THR, 1600); /* XXX */
	// sky2_write32(hw, RX_GMF_CTRL_T, RX_TRUNC_ON);
 
	/* Tell chip about available buffers */
	/* XXX: old code */
	// int put_idx = RX_BUF_COUNT+1; /* right IDX? */
	// sky2_write16(hw, Y2_QADDR(Q_R1, PREF_UNIT_PUT_IDX), put_idx);

	// sky2_read16(hw, Y2_QADDR(Q_R1, PREF_UNIT_PUT_IDX));

	return 0;
}

bool yukonosx::ifup_linux_3()
{
	/***** Back to static int sky2_up(struct net_device *dev)  ****/

	
	/* Enable interrupts from phy/mac for port */
	// hw->intr_mask |= (port == 0) ? Y2_IS_PORT_1 : Y2_IS_PORT_2;

	// XXXXX
	// sky2_write32( hw, B0_IMSK, Y2_IS_BASE | Y2_IS_PORT_1 );
	sky2_write32( hw, B0_IMSK, 0 );

	/* do the link up */
	sky2_link_up();

	return 0;
}



/* this is a mix of rx_start and ifup from linux sky2 */
bool yukonosx::ifup_linux()
{
	/* first make some TX/RX memory */
	mDesc = IOBufferMemoryDescriptor::withOptions(kIOMemoryUnshared, 
						      sizeof(Ring), PAGE_SIZE);
	// alias it with the actual structure
	ring = (Ring *)mDesc->getBytesNoCopy();

	/* reset the board */
	printf( "sky2_reset\n" );
	sky2_reset( this );	
	
	/* do the mac init */
	printf( "mac_init\n" );
	sky2_mac_init( this, 0 );

	/* alloc TX buffers */
	initTx();
	
	IOLog( "ifup_linux_1\n" );
	ifup_linux_1();

	IOLog( "ifup_linux_2\n" );
	ifup_linux_2();

	IOLog( "ifup_linux_3\n" );
	ifup_linux_3();

	return 0;
}

RxDesc *yukonosx::next_rx_desc( void *tag )
{
	/* get the RX desc */
	RxDesc *le = &ring->rxRing[rx_put];

	/* write the tag into the shadow array */
	ring->tag_list[rx_put] = tag;
	
	/* increment */
	rx_put = (rx_put + 1) % SK_RX_RING_CNT;

	return le;
}

void yukonosx::free_rx_desc( void *buf, UInt16 size, void *tag )
{
	RxDesc *rx = next_rx_desc( tag );

	rx->addr = (UInt32) buf;
	assert(rx->addr & 0xf == 0); /* want 16-byte aligned? */

	rx->length = size;
	// printf( "rx->length: %d, size: %d\n", rx->length, size );
	rx->ctrl = 0;
	rx->opcode = OP_PACKET |  HW_OWNER;
}

void yukonosx::free_rx_mbuf( mbuf_t pkt )
{
	void *addr;
	addr = (void*) mbuf_data( pkt );

	free_rx_desc( addr, YUKON_BUFSIZE, (void*) pkt );
}

TxDesc *yukonosx::next_tx_desc()
{
	TxDesc *le = &ring->txRing[tx_prod];
	tx_prod = (tx_prod + 1) % SK_TX_RING_CNT;

	return le;
}

int yukonosx::xmit_frame( void *data, int size )
{
	TxDesc *tx = next_tx_desc();

	tx->tx.addr = (UInt32) data;
	tx->length = size;
        tx->ctrl = EOP;
        tx->opcode = HW_OWNER | OP_PACKET;

	/* kick the card */
	sky2_write16( hw, Y2_QADDR(Q_XA1, PREF_UNIT_PUT_IDX), tx_prod );
}

/* hack from outside */
static yukonosx *the_yukon = (yukonosx *) NULL;
extern "C" 
{
	void yukon_do_tx( void *data, unsigned size );

	void
	yukon_do_tx( void *data, unsigned size )
	{
		if( the_yukon == NULL )
		{
			printf( "Yukon not setup, skipping actual TX\n" );
			/* nothing setup yet! */
			return;
		}
/*
		else
			printf( "tx %p, len %d\n", data, size );
*/
		/* make sure it's not too small! */
		if( size < 64 )
			size = 64;

		the_yukon->xmit_frame( data, size );
	}
}


void yukonosx::timeoutOccurred( IOTimerEventSource* timer )
{

	// ypanic( "YukonOSX: timeoutOccured - old skool.\n" );

	/* poll interrupt stuff */
	intHandler();

	/* and leave */
        timerSrc->setTimeoutMS( POLL_TIMEOUT );
}

	
bool yukonosx::start(IOService *provider)
{
	IOMemoryMap	*map;
	UInt16		reg;
	UInt32		i;

	IOLog("YukonOSX::start\n" );

	nub = OSDynamicCast(IOPCIDevice, provider);

	if (!nub || !super::start(provider)) {
		IOLog("yukonosx: can't start super\n");
		return false;
	}

	map = nub->mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress0);
	if (!map) {
		IOLog("yukonosx:: can't find register base\n");
		return false;
	}

	// XXX power management

	reg = nub->configRead16(kIOPCIConfigCommand);
	reg |= (kIOPCICommandBusMaster | kIOPCICommandMemorySpace);
	reg &= ~kIOPCICommandIOSpace;

	nub->configWrite16(kIOPCIConfigCommand, reg);

	csrBase = (void *)map->getVirtualAddress();
	for (i = 0; i < sizeof(IOEthernetAddress); i++) {

		myAddress.bytes[i] = sk_win_read_1(0, SK_MAC0_0 + 
		    /*(sa->skc_port) * 8*/ + i);
	}

	IOLog("ethernet addr %x:%x:%x:%x:%x:%x\n",
	    myAddress.bytes[0],
	    myAddress.bytes[1],
	    myAddress.bytes[2],
	    myAddress.bytes[3],
	    myAddress.bytes[4],
	    myAddress.bytes[5]);

	IOLog( "base: %p\n", csrBase );

	/* zero indexes */
	rx_put = rx_check = 0;
	tx_prod = tx_cons = 0;
	st_idx = 0;

	/* bring up the interface */
	ifup_linux();

	/* sleep for a bit :) */
	IOSleep(1000);

	if( sky2_read8(hw, STAT_LEV_TIMER_CTRL) == TIM_START )
	{
		printf( "OMFG, timer stuff\n" );
		sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_STOP);
		sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
	}

	/* free up some recv descriptors */
	for( i = 0; i < RX_BUF_COUNT; i++ )
	{
		mbuf_t pkt;

		pkt = allocatePacket( YUKON_BUFSIZE );
		if( pkt == NULL )
			ypanic( "Could not allocate RX packet!\n" );

		free_rx_mbuf( pkt );
	}

	/* Tell chip about available buffers */
	printf( "telling chip about %d buffers\n", rx_put );
        sky2_write16(hw, Y2_QADDR(Q_R1, PREF_UNIT_PUT_IDX), rx_put);


#if 0
	/* blah blah */
	free_rx_desc( ring->rx_buf[i], 2048 );

	/* do a TX */
	do_tx_arp( this );
	do_tx_arp( this );


	while( 1 )
	{
		IOSleep(1000);

		intHandler();
	}
	
	ypanic( "about to reg intr\n" );
#endif

#if 0
	{
		for( i = 0; i < 20; i++ )
		{
			printf( "YukonOSX: Sleeping for PCI startup...\n" );
			IOSleep(1000);
		}
	}
#endif

#if 0
	IOLog( "YukonOSX: registering interrupt\n" );

	interruptSrc = IOInterruptEventSource::interruptEventSource(
			(OSObject*)this,
			OSMemberFunctionCast(IOInterruptAction, this,
			&yukonosx::interruptOccurred),
                        (IOService*)provider,
                        (int)0 );

	if (interruptSrc == NULL) {
		ypanic("yukonosx: no interrupt src\n");
		return false;
	}

	if (workLoop->addEventSource(interruptSrc) != kIOReturnSuccess) {
 		ypanic("yukonosx: can't add event src\n");
		return false;
	}
#endif
	/*
	 * XXX allocate descriptor queues
 	 */

	// setPromiscuousMode( true );


	timerSrc = IOTimerEventSource::timerEventSource(this,
	    OSMemberFunctionCast(IOTimerEventSource::Action, this, 
				 &yukonosx::timeoutOccurred));

	if( timerSrc == NULL )
		ypanic( "Couldn't create timer source\n" );

	if( workLoop->addEventSource(timerSrc) != kIOReturnSuccess )
	{
		ypanic("yukonosx: can't add timer src\n");
		return false;
	}

	/* Stuff from UniNEnet */

	if ( !attachInterface( (IONetworkInterface**)&networkIface, false ) )
	{	
		ypanic( "UniNEnet::start - attachInterface failed" );      
		return false;
	}

	/* register it */
	networkIface->registerService();


	/* ready to go */
	/* Thanks to Geoff we have interrupts! :) */
        timerSrc->setTimeoutMS( POLL_TIMEOUT );

	// XXX should be here??
	// XXX -gl
	// workLoop->enableAllInterrupts();

	/* evil ceg hack */
	the_yukon = this;

	return true;
}

bool yukonosx::createWorkLoop()
{

	workLoop = IOWorkLoop::workLoop();

	return (workLoop != 0);
}

IOReturn yukonosx::enable(IONetworkInterface *netif)
{

	return kIOReturnSuccess;
}

IOReturn yukonosx::disable(IONetworkInterface *netif)
{

	return kIOReturnSuccess;
}

bool yukonosx::phyReset()
{
	IOLog("yukonosx: phyReset\n");	
  /* GMAC and GPHY Reset */
        SK_IF_WRITE_4(sc_if, 0, SK_GPHY_CTRL, SK_GPHY_RESET_SET);

        SK_IF_WRITE_4(sc_if, 0, SK_GMAC_CTRL, SK_GMAC_RESET_SET);
        DELAY(1000);
        SK_IF_WRITE_4(sc_if, 0, SK_GMAC_CTRL, SK_GMAC_RESET_CLEAR);        

	/* this *seems* to be correct?! */
	SK_IF_WRITE_4(sc_if, 0, SK_GMAC_CTRL, SK_GMAC_RESET_SET);

        IODelay(1000);

	return true;
}

bool yukonosx::initHW()
{
	UInt16	reg;
	UInt32	i;

	// reset the chip
	printf( "YukonOSX: doing reset\n" );
	reset();

	printf( "YukonOSX: doing phyInit\n" );
	phyInit();

        /* unused read of the interrupt source register */
	{
		unsigned int foo;

		DPRINTFN(6, ("sk_init_yukon: 4\n"));
		foo = SK_IF_READ_2(sc_if, 0, SK_GMAC_ISR);

		printf( "SK_GMAC_ISR: 0x%x\n", foo );

		dump_yukon_gpsr();
	}

        DPRINTFN(6, ("sk_init_yukon: 4a\n"));
        reg = SK_YU_READ_2(sc_if, YUKON_PAR);
        DPRINTFN(6, ("sk_init_yukon: YUKON_PAR=%#x\n", reg));
        /* MIB Counter Clear Mode set */
        reg |= YU_PAR_MIB_CLR;
        DPRINTFN(6, ("sk_init_yukon: YUKON_PAR=%#x\n", reg));
        DPRINTFN(6, ("sk_init_yukon: 4b\n"));
        SK_YU_WRITE_2(sc_if, YUKON_PAR, reg);

        /* MIB Counter Clear Mode clear */
        DPRINTFN(6, ("sk_init_yukon: 5\n"));
        reg &= ~YU_PAR_MIB_CLR;
        SK_YU_WRITE_2(sc_if, YUKON_PAR, reg);

        /* receive control reg */
        DPRINTFN(6, ("sk_init_yukon: 7\n"));
        SK_YU_WRITE_2(sc_if, YUKON_RCR, YU_RCR_UFLEN | YU_RCR_MUFLEN |
                      YU_RCR_CRCR);

        /* transmit parameter register */
        DPRINTFN(6, ("sk_init_yukon: 8\n"));
        SK_YU_WRITE_2(sc_if, YUKON_TPR, YU_TPR_JAM_LEN(0x3) |
                      YU_TPR_JAM_IPG(0xb) | YU_TPR_JAM2DATA_IPG(0x1a) );

        /* serial mode register */
        DPRINTFN(6, ("sk_init_yukon: 9\n"));
        SK_YU_WRITE_2(sc_if, YUKON_SMR, YU_SMR_DATA_BLIND(0x1c) |
                      YU_SMR_MFL_VLAN | YU_SMR_MFL_JUMBO |
                      YU_SMR_IPG_DATA(0x1e));

        /* Setup Yukon's address */
        for (i = 0; i < 6; i++) {
                /* Write Source Address 1 (unicast filter) */
                SK_YU_WRITE_1(/*sc_if*/, YUKON_SAL1 + i * 4,
				myAddress.bytes[i]);
        }

        for (i = 0; i < 3; i++) 
	{
                reg = sk_win_read_2(/*sc_if->sk_softc*/0,
                                    //SK_MAC1_0 + i * 2 + sc_if->sk_port * 8);
                                    SK_MAC1_0 + i * 2 + 0 * 8);
                SK_YU_WRITE_2(sc_if, YUKON_SAL2 + i * 4, reg);
        }

        /* Set multicast filter */
        DPRINTFN(6, ("sk_init_yukon: 11\n"));
        //sk_setmulti(sc_if);

        /* enable interrupt mask for counter overflows */
	/* This masks them off */
        DPRINTFN(6, ("sk_init_yukon: 12\n"));
        SK_YU_WRITE_2(sc_if, YUKON_TIMR, 0);
        SK_YU_WRITE_2(sc_if, YUKON_RIMR, 0);
        SK_YU_WRITE_2(sc_if, YUKON_TRIMR, 0);

        /* Configure RX MAC FIFO */
        SK_IF_WRITE_1(sc_if, 0, SK_RXMF1_CTRL_TEST, SK_RFCTL_RESET_CLEAR);
        SK_IF_WRITE_4(sc_if, 0, SK_RXMF1_CTRL_TEST, SK_RFCTL_OPERATION_ON + 128);

        /* Configure TX MAC FIFO */
        SK_IF_WRITE_1(sc_if, 0, SK_TXMF1_CTRL_TEST, SK_TFCTL_RESET_CLEAR);
        SK_IF_WRITE_4(sc_if, 0, SK_TXMF1_CTRL_TEST, SK_TFCTL_OPERATION_ON);

        DPRINTFN(6, ("sk_init_yukon: end\n"));

	return true;
}

bool yukonosx::phyInit()
{
	UInt32	phy;

	IOLog("yukonosx:: phyReset()\n");

	phyReset();

	IOLog("yukonosx:: phyInit()\n");

	phy = SK_GPHY_INT_POL_HI | SK_GPHY_DIS_FC | SK_GPHY_DIS_SLEEP |
                SK_GPHY_ENA_XC | SK_GPHY_ANEG_ALL | SK_GPHY_ENA_PAUSE;

	phy |= SK_GPHY_COPPER;

        SK_IF_WRITE_4(sc_if, 0, SK_GPHY_CTRL, phy | SK_GPHY_RESET_SET);
        DELAY(1000);
        SK_IF_WRITE_4(sc_if, 0, SK_GPHY_CTRL, phy | SK_GPHY_RESET_CLEAR);

	/* loopback off */
        SK_IF_WRITE_4(sc_if, 0, SK_GMAC_CTRL, SK_GMAC_LOOP_OFF |
                      SK_GMAC_PAUSE_ON | SK_GMAC_RESET_CLEAR);

	/* Unmask PHY interrupts */
	// gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL);
	writePHY(0, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL | PHY_M_IS_LST_CHANGE );


	/* more linux stuff */
	// u16 ectrl = gm_phy_read(hw, port, PHY_MARV_EXT_CTRL);
	// ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
	//          PHY_M_EC_MAC_S_MSK);
	// ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);
	// ectrl |= PHY_M_EC_DSC_2(2) | PHY_M_EC_DOWN_S_ENA;
	// gm_phy_write(hw, port, PHY_MARV_EXT_CTRL, ectrl);

	UInt16 ectrl;

	readPHY( 0, PHY_MARV_EXT_CTRL, &ectrl );
	ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
		   PHY_M_EC_MAC_S_MSK);
	ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);
	ectrl |= PHY_M_EC_DSC_2(2) | PHY_M_EC_DOWN_S_ENA;
	writePHY( 0, PHY_MARV_EXT_CTRL, ectrl );


	/* Some random Linux init */
	// ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
	/* Energy detect */
	// ctrl &= ~PHY_M_PC_EN_DET_MSK;
	/* enable automatic crossover */
	// ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO);
	// gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);

	UInt16 ctrl;

	readPHY( 0, PHY_MARV_PHY_CTRL, &ctrl );
	ctrl &= ~PHY_M_PC_EN_DET_MSK;
	ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO);
	writePHY( 0, PHY_MARV_PHY_CTRL, ctrl );

	/* some kinda reset */
	//   ctrl = gm_phy_read(hw, port, PHY_MARV_CTRL);
        //   ctrl |= PHY_CT_ANE;
        //   ctrl |= PHY_CT_RESET;
        //   gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);

	readPHY( 0, PHY_MARV_CTRL, &ctrl );
        ctrl |= PHY_CT_ANE;
        ctrl |= PHY_CT_RESET;
	writePHY( 0, PHY_MARV_CTRL, ctrl );


	return true;
}

IOReturn yukonosx::getHardwareAddress(IOEthernetAddress *addrs)
{

	bcopy(&myAddress, addrs, sizeof(*addrs));
	return kIOReturnSuccess;
}

#define reg_print(x, n) do_reg_print( x, n, #n )

static void
do_reg_print( unsigned int status, unsigned int bit, const char *name )
{
	if( status & bit )
		IOLog( "### %s\n", name );
#if 0
	else
		IOLog( "    %s\n", name );
#endif
}

static void
sk_dump_isr( unsigned int status, char *msg )
{
	IOLog( "%s: dumping ISR 0x%x\n", msg, status );
	
	reg_print( status, Y2_IS_HW_ERR    );
	reg_print( status, Y2_IS_STAT_BMU  );
	reg_print( status, Y2_IS_ASF       );
	
	reg_print( status, Y2_IS_POLL_CHK  );
	reg_print( status, Y2_IS_TWSI_RDY  );
	reg_print( status, Y2_IS_IRQ_SW    );
	reg_print( status, Y2_IS_TIMINT    );
	
	reg_print( status, Y2_IS_IRQ_PHY2  );
	reg_print( status, Y2_IS_IRQ_MAC2  );
	reg_print( status, Y2_IS_CHK_RX2   );
	reg_print( status, Y2_IS_CHK_TXS2  );
	reg_print( status, Y2_IS_CHK_TXA2  );
	
	reg_print( status, Y2_IS_IRQ_PHY1  );
	reg_print( status, Y2_IS_IRQ_MAC1  );
	reg_print( status, Y2_IS_CHK_RX1   );
	reg_print( status, Y2_IS_CHK_TXS1  );
	reg_print( status, Y2_IS_CHK_TXA1  );
}

static void
sk_dump_hw_err(void)
{
	unsigned int foo;

	foo = CSR_READ_4(0, SK_IESR );
	IOLog( "SK_IESR: 0x%x\n", foo );
}

static void
dump_marvel_phy_ints( yukonosx *yosx )
{
	UInt16 foo;

	yosx->readPHY((UInt8) 0, (UInt8) PHY_MARV_INT_STAT, &foo );
	printf( "PHY_MARV_INT_STAT: 0x%x\n", foo );
}

static void
dump_yukon_gpsr(void)
{
	unsigned int foo;

	foo = SK_YU_READ_2(sc_if, YUKON_GPSR);
	printf( "YUKON_GPSR: %x\n", foo );
}

static void
dump_link_status( yukonosx *yosx )
{
	UInt32 aux;
	
	yosx->readPHY( 0, PHY_MARV_PHY_STAT, (UInt16*) &aux);

	printf( "Link status:\n" );

	if( (aux & PHY_M_PS_LINK_UP) == 0 )
	{
		printf( "\tLink down :(\n" );
		return;
	}

	if( (aux & PHY_M_PS_SPDUP_RES) == 0 )
	{
		printf( "Speed & Duplex not yet resolved\n" );
		return;
	}

	/* speed */
	switch (aux & PHY_M_PS_SPEED_MSK) 
	{
		case PHY_M_PS_SPEED_1000:
			printf( "\t1000MBit\n" );
			break;
		case PHY_M_PS_SPEED_100:
			printf( "\t100MBit\n" );
			break;
		default:
			printf( "\t10MBit\n" );
	}

	/* duplex mode */
	if( aux & PHY_M_PS_FULL_DUP ) 
		printf( "\tFull Duplex\n" );
	else
		printf( "\tHalf Duplex\n" );
}

#define PHY_STAT_COUNT 21
static void
dump_phy_stats(void)
{
	int i;
	UInt64 data[21];

	sky2_phy_stats( data, PHY_STAT_COUNT );

	printf( "PHY Stats:\n" );
	for( i = 0; i < PHY_STAT_COUNT; i++ )
		if( data[i] != 0 )
			printf( "\t%s: %d\n", 
				sky2_stats[i].name, (int) data[i] );
	printf( "done PHY Stats\n" );
}

static void
check_queues( yukonosx *yosx )
{
	char *p;
	int i;

#if 0
	/* linux */
	{
		UInt32 status;
		status = sky2_read32(hw, B0_Y2_SP_ISRC2);
		printf( "B0_Y2_SP_ISRC2: 0x%x\n", status );
		if( status & Y2_IS_STAT_BMU )
			ypanic( "OMFG! BMU STATUS!\n" );

		status = sky2_read8(hw, SK_REG_LINUX(0, GMAC_IRQ_SRC));
		printf( "GMAC_IRQ_SRC: 0x%x\n", status );

		status = gma_read16(0, GM_GP_STAT);
		printf( "GM_GP_STAT: 0x%x\n", status );

	}
#endif

	printf( "check_queues txRing = 0x%x, rxRing = 0x%x\n",
		yosx->ring->txRing[0].opcode,
		yosx->ring->rxRing[0].opcode );

	if( (yosx->ring->txRing[0].opcode & HW_OWNER) == 0 )
		printf( "I pwn txRing 0\n" );

	if( (yosx->ring->rxRing[1].opcode & HW_OWNER) == 0 )
		printf( "I pwn rxRing 1\n" );

	/* from the _poll function */
	sky2_write32(hw, STAT_CTRL, SC_STAT_CLR_IRQ);

	/* check the status guys */
	for( i = 0; i < STATUS_RING_SIZE; i++ )
	{
		StDesc *st;
		
		st = &yosx->ring->stRing[i];

		if( i == 0 )
			printf( "stRing[0] is %p\n", st );


		if( st->opcode != 0 
		    || st->status != 0 
		    || st->length != 0 
		    || st->link != 0 )
		{
			printf( "opcode %d = 0x%x\n", i, 
				yosx->ring->stRing[i].opcode );
			printf( "status %d = 0x%x\n", i, 
				yosx->ring->stRing[i].status );
		}
	}

#if 0
	for( int j = 0; j < RX_BUF_COUNT; j++ )
	{
		p = &yosx->ring->rx_buf[j][0];

		for( i = 0; i < 2048; i++ )
		{
			if( p[i] != 0 )
			{
				printf( "data in rx packet %d, %p\n", j, p );
				break;
			}
		}
	}
#endif

#if 0
	/* BMU status */
	{
		unsigned int foo;
		foo = sky2_read32( hw, Y2_QADDR(Q_R1, Q_CSR) );
		printf( "Q_R1.CSR : 0x%x\n", foo );
		foo = sky2_read32( hw, Y2_QADDR(Q_XA1, Q_CSR) );
		printf( "Q_XA1.CSR: 0x%x\n", foo );

	}
#endif

}



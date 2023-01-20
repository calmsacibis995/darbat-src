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
 * yukonosx.h
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

#ifndef _YUKONOSX_H
#define _YUKONOSX_H

#define YUKONOSX

/*
 * First things first: include the BSD glue
 *
 *	-gl
 */
#include "bsdglue.h"

#include "if_skreg.h"
//#include "if_skvar.h"
#include "brgphyreg.h"
#include "mii.h"

#define __MBUF_TRANSITION_    /* New-style IOKit mbufs */

#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/network/IOEthernetController.h>
#include <IOKit/network/IOEthernetInterface.h>
#include <IOKit/network/IOGatedOutputQueue.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/network/IOMbufMemoryCursor.h>
#include <IOKit/IODeviceMemory.h>
#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/IOLib.h>            /* bcopy */

#include <libkern/OSByteOrder.h>

// for now
void			*csrBase;

typedef struct 
{
	union {
		UInt32  addr;
                struct {
                        UInt16  offset;
                        UInt16  start;
                } csum  __attribute((packed));
                struct {
                        UInt16  size;
                        UInt16  rsvd;
                } tso  __attribute((packed));
        } tx;
        UInt16  length; /* also vlan tag or checksum start */
        UInt8   ctrl;
        UInt8   opcode;
} __attribute((packed)) TxDesc;

typedef struct 
{
	UInt32  addr;
	UInt16  length;
	UInt8   ctrl;
	UInt8   opcode;
} __attribute((packed)) RxDesc;

typedef struct
{
	UInt32  status; /* also checksum */
        UInt16  length; /* also vlan tag */
        UInt8   link;
        UInt8   opcode;
} __attribute((packed)) StDesc;  /* Status descriptor */

/* that's what Linux does */
#define STATUS_RING_SIZE 2048

/* half a page, not *too* much bigger than ethernet MTU :) */
#define YUKON_BUFSIZE 2048

typedef struct _Ring {
	/* xmit and recv descriptor arrays */
	TxDesc	txRing[SK_TX_RING_CNT];
	RxDesc	rxRing[SK_RX_RING_CNT + 256];  /* XXX: alignment! */

	/* status descriptor array */
	StDesc  stRing[STATUS_RING_SIZE];

#if 0
	/* test single packet tx and rx buffers */
	char    tx_buf[2048];
	char    rx_buf[RX_BUF_COUNT][2048];
#endif

/* try to keep this many RX buffers available*/
#define RX_BUF_COUNT 64

	/* shadow list for rxRing with pointers to actual recv mbufs */
	void*	tag_list[SK_RX_RING_CNT];
} Ring;

/*
 * HACKS
 *
 */

/*
 * Used to be in if_skvar.h
 *
 */
#ifdef YUKONOSX
#define SK_TX_RING_ADDR(sc, i) \
    offsetof(Ring, txRing[(i)])

#define SK_RX_RING_ADDR(sc, i) \
    offsetof(Ring, rxRing[(i)])

#endif /*YUKONOSX*/

class yukonosx : public IOEthernetController
{
	OSDeclareDefaultStructors(yukonosx)
//private:
public:
	IOPCIDevice		*nub;

	IOWorkLoop		*workLoop;
	IOTimerEventSource	*timerSrc;
	IOInterruptEventSource	*interruptSrc;
	IOEthernetInterface	*networkIface;

	IOEthernetAddress	myAddress;

	// description of the tx and rx bufs
	Ring				*ring;
	IOBufferMemoryDescriptor	*mDesc;

	bool reset();
	bool stopChip();
	bool phyReset();
	bool phyInit();
	bool writePHY(UInt8, UInt8, UInt16);
	bool readPHY(UInt8, UInt8, UInt16 *);
	bool initTx();
	bool initRx();
	bool ifup_bsd();

	void sky2_qset( UInt16 q );

	/* g++ is sooo crap */
	bool ifup_linux_1();
	bool ifup_linux_2();
	bool ifup_linux_3();

	bool ifup_linux();
       
	/* grab the next free rx desc */
	RxDesc *next_rx_desc( void *tag );

	/* make a buffer available for RX */
	void free_rx_desc( void *buf, UInt16 size, void *tag );

	/* take an mbuf and receive into it. calls free_rx_desc */
	void free_rx_mbuf( mbuf_t mbuf );

	/* do something with an rx descriptor back from the card */
	void rx_packet( StDesc *le );

	/* once we know a recv was good, pass the tag for the hw packet
	 * to the next level 
	 */
	void rx_good_packet( void *tag, unsigned size );

	/* transmit done handler */
	void done_tx_packet( StDesc *le );

	/* get the next TX desc */
	TxDesc *next_tx_desc();

	/* xmit a frame */
	int xmit_frame( void *data, int size );

	/* actual interrupt function called */
	void interruptOccurred();
	void timeoutOccurred( IOTimerEventSource* );

	/* poll the card for stuff */
	void intHandler();
	void handleBMU();

	/* init the hardware */
	bool initHW();

	/* ring buffer pointers */
	unsigned rx_put, rx_check; /* rx put and where to start checking */
	unsigned tx_prod, tx_cons; /* producer (next) and consumer (card's) */
	unsigned st_idx; /* current index in status buffer we look at */

	/* did we queue packets on an interrupt? */
	unsigned packets_queued;

	/* current interrupt mask - needed? */
	UInt32	intrMask;

	/* don't really need these guys? */
	UInt32	ramSize;
	UInt32	ramBufferOffset;

	UInt32	txRamStart, txRamEnd;
	UInt32	rxRamStart, rxRamEnd;

public:
	virtual bool start (IOService *provider);

	virtual IOReturn enable(IONetworkInterface *);
	virtual IOReturn disable(IONetworkInterface *);

        virtual IOReturn setPromiscuousMode(bool active);

	virtual bool createWorkLoop();
	virtual IOReturn getHardwareAddress(IOEthernetAddress *);
};

#endif	/*_YUKONOSX_H*/

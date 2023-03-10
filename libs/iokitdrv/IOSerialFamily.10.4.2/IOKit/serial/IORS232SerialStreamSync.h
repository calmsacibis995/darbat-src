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
 * IORS232SerialStreamSync.h
 * This file contains RS232 specific extensions to the IOSerialStreamSync class.
 *
 * 2000-10-21	gvdl	Initial real change to IOKit serial family.
 */  

#ifndef _SERIAL_IORS232SERIALSTREAMSYNC_H
#define _SERIAL_IORS232SERIALSTREAMSYNC_H

#include <sys/ioctl.h>
#include <IOKit/serial/IOSerialStreamSync.h>

/*
 * Extra events for RS232 based PortDevices
 */  

#define PD_RS232_E_RX_LINE_BREAK      (PD_DATA_VOID|PD_OP(63))  // line break was received
#define PD_RS232_E_LINE_BREAK         (PD_DATA_BYTE|PD_OP(62))  // BOOL set/clear line break    

#define PD_RS232_E_RX_STOP_BITS       (PD_DATA_LONG|PD_OP(61))  // half stop bits
#define PD_RS232_E_STOP_BITS          (PD_DATA_LONG|PD_OP(60))  // half stop bits

#define PD_RS232_E_XON_BYTE           (PD_DATA_BYTE|PD_OP(59))  // The XON char for TX&RX
#define PD_RS232_E_XOFF_BYTE          (PD_DATA_BYTE|PD_OP(58))  // The XOFF char for TX&RX

#define PD_RS232_E_MIN_LATENCY        (PD_DATA_BYTE|PD_OP(57))  // BOOL true if low latency req

/*
 * RS232 Parity stuff, used with the DATA_INTEGRITY event
 */  
#define PD_RS232_PARITY_DEFAULT	0	// Valid only for RX, means follow TX
#define PD_RS232_PARITY_NONE	1	// No Parity bit inserted or expected
#define PD_RS232_PARITY_ODD	2	// Odd Parity bit inserted or expected
#define PD_RS232_PARITY_EVEN	3	// Even Parity bit inserted or expected
#define PD_RS232_PARITY_MARK	4	// Mark inserted or expected
#define PD_RS232_PARITY_SPACE	5	// Space inserted or expected
#define PD_RS232_PARITY_ANY	6	// Valid only for RX, means discard parity

/*
 * RS232 Flow Control specifiers, used with the FLOW_CONTROL event
 * NB. The XON  character is set with FLOW_START_DATA
 * and the XOFF character is set with FLOW_STOP_DATA.
 *
 * Signal  Name                          Direction
 *  RFR     Ready For Receive             Output generated by UART
 *  RTS     Ready To Send (alias of RFR)  Output generated by UART
 *  CTS     Clear To Send		  Input sensed by UART
 *  DTR     Data Terminal Ready           Output generated by UART
 *  DSR     Data Set Ready                Input sensed by UART
 *  TXO     XON/XOFF/XANY protocol        Characters received by UART
 *  RXO     XON/XOFF protocol             Characters transmitted by UART
 *  DCD     Data Carrier Detect           Input sensed by UART
 */

/*
 * RS232 State Word extensions, based on <bsd/sys/ioctl.h>
 * Also the 'current state' bits for enq/deq of Flow Control event
 */  
#define PD_RS232_S_MASK   0x0000ffffUL
#define PD_RS232_S_SHIFT  0	// to align State bits for enq/deq event
#define PD_RS232_D_MASK   0xffff0000UL
#define PD_RS232_D_SHIFT  16	// to align Delta bits for enq/deq event
#define PD_RS232_A_MASK   0x0000ffffUL
#define PD_RS232_A_SHIFT  0	// to align Auto bits for req/exec event
#define PD_RS232_N_MASK   0xffff0000UL
#define PD_RS232_N_SHIFT  16	// to align Notify bits for req/exec event

#define	PD_RS232_S_LE	TIOCM_LE	// line enable
#define	PD_RS232_S_DTR	TIOCM_DTR	// data terminal ready
#define	PD_RS232_S_RTS	TIOCM_RTS	// request to send
#define	PD_RS232_S_RFR	PD_RS232_S_RTS	// ready for receive
#define	PD_RS232_S_TXO	TIOCM_ST	// TX XON/XOFF
#define	PD_RS232_S_RXO	TIOCM_SR	// RX XON/XOFF
#define	PD_RS232_S_CTS	TIOCM_CTS	// clear to send
#define	PD_RS232_S_CAR	TIOCM_CAR	// carrier detect
#define	PD_RS232_S_DCD	PD_RS232_S_CAR
#define	PD_RS232_S_RNG	TIOCM_RNG	// ring
#define	PD_RS232_S_RI	PD_RS232_S_RNG
#define	PD_RS232_S_DSR	TIOCM_DSR	// data set ready

#define	PD_RS232_S_BRK	0x00000800UL	// break active Extension to TIOCM   
#define	PD_RS232_S_LOOP	0x00001000UL	// LOOP back Extension to TIOCM
#define PD_RS232_S_TXQ	0x00002000UL	// User flowcontrol bit
#define PD_RS232_S_RXQ	0x00004000UL	// User flowcontrol bit

// The 'delta' bits for enq/deq of Flow Control event
#define	PD_RS232_D_LE	(PD_RS232_S_LE  << PD_RS232_D_SHIFT)
#define	PD_RS232_D_DTR	(PD_RS232_S_DTR << PD_RS232_D_SHIFT)
#define	PD_RS232_D_RTS	(PD_RS232_S_RTS << PD_RS232_D_SHIFT)
#define	PD_RS232_D_RFR	(PD_RS232_S_RFR << PD_RS232_D_SHIFT)
#define	PD_RS232_D_TXO	(PD_RS232_S_TXO << PD_RS232_D_SHIFT)
#define	PD_RS232_D_RXO	(PD_RS232_S_RXO << PD_RS232_D_SHIFT)
#define	PD_RS232_D_CTS	(PD_RS232_S_CTS << PD_RS232_D_SHIFT)
#define	PD_RS232_D_CAR	(PD_RS232_S_CAR << PD_RS232_D_SHIFT)
#define	PD_RS232_D_DCD	(PD_RS232_S_DCD << PD_RS232_D_SHIFT)
#define	PD_RS232_D_RNG	(PD_RS232_S_RNG << PD_RS232_D_SHIFT)
#define	PD_RS232_D_RI	(PD_RS232_S_RI  << PD_RS232_D_SHIFT)
#define	PD_RS232_D_DSR	(PD_RS232_S_DSR << PD_RS232_D_SHIFT)
 
#define	PD_RS232_D_BRK	(PD_RS232_S_BRK  << PD_RS232_D_SHIFT)
#define	PD_RS232_D_LOOP (PD_RS232_S_LOOP << PD_RS232_D_SHIFT)
#define PD_RS232_D_TXQ	(PD_RS232_S_TXQ  << PD_RS232_D_SHIFT)
#define PD_RS232_D_RXQ	(PD_RS232_S_RXQ  << PD_RS232_D_SHIFT)

// The 'auto' bits for exec/req of Flow Control event
#define	PD_RS232_A_LE	PD_RS232_S_LE
#define	PD_RS232_A_DTR	PD_RS232_S_DTR
#define	PD_RS232_A_RTS	PD_RS232_S_RTS
#define	PD_RS232_A_RFR	PD_RS232_S_RFR
#define	PD_RS232_A_TXO	PD_RS232_S_TXO
#define	PD_RS232_A_RXO	PD_RS232_S_RXO
#define	PD_RS232_A_CTS	PD_RS232_S_CTS
#define	PD_RS232_A_CAR	PD_RS232_S_CAR
#define	PD_RS232_A_DCD	PD_RS232_S_DCD
#define	PD_RS232_A_RNG	PD_RS232_S_RNG
#define	PD_RS232_A_RI	PD_RS232_S_RI
#define	PD_RS232_A_DSR	PD_RS232_S_DSR
#define PD_RS232_A_XANY	0x00000400	// changes _A_TXO from XON/XOFF to XANY/XOFF
#define	PD_RS232_A_BRK	PD_RS232_S_BRK   
#define	PD_RS232_A_LOOP PD_RS232_S_LOOP
#define PD_RS232_A_TXQ	PD_RS232_S_TXQ
#define PD_RS232_A_RXQ	PD_RS232_S_RXQ

// The 'notify' bits for exec/req of Flow Control event
#define	PD_RS232_N_LE	(PD_RS232_S_LE  << PD_RS232_N_SHIFT)
#define	PD_RS232_N_DTR	(PD_RS232_S_DTR << PD_RS232_N_SHIFT)
#define	PD_RS232_N_RTS	(PD_RS232_S_RTS << PD_RS232_N_SHIFT)
#define	PD_RS232_N_RFR	(PD_RS232_S_RFR << PD_RS232_N_SHIFT)
#define	PD_RS232_N_TXO	(PD_RS232_S_TXO << PD_RS232_N_SHIFT)
#define	PD_RS232_N_RXO	(PD_RS232_S_RXO << PD_RS232_N_SHIFT)
#define	PD_RS232_N_CTS	(PD_RS232_S_CTS << PD_RS232_N_SHIFT)
#define	PD_RS232_N_CAR	(PD_RS232_S_CAR << PD_RS232_N_SHIFT)
#define	PD_RS232_N_DCD	(PD_RS232_S_DCD << PD_RS232_N_SHIFT)
#define	PD_RS232_N_RNG	(PD_RS232_S_RNG << PD_RS232_N_SHIFT)
#define	PD_RS232_N_RI	(PD_RS232_S_RI  << PD_RS232_N_SHIFT)
#define	PD_RS232_N_DSR	(PD_RS232_S_DSR << PD_RS232_N_SHIFT)

#define	PD_RS232_N_BRK	(PD_RS232_S_BRK  << PD_RS232_N_SHIFT)
#define	PD_RS232_N_LOOP (PD_RS232_S_LOOP << PD_RS232_N_SHIFT)
#define PD_RS232_N_TXQ	(PD_RS232_S_TXQ  << PD_RS232_N_SHIFT)
#define PD_RS232_N_RXQ	(PD_RS232_S_RXQ  << PD_RS232_N_SHIFT)

class IORS232SerialStreamSync : public IOSerialStreamSync
{
    OSDeclareDefaultStructors(IORS232SerialStreamSync)
};

#endif /* !_SERIAL_IORS232SERIALSTREAMSYNC_H */


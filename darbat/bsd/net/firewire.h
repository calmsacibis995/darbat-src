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
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
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
 * Fundamental constants relating to FireWire network device.
 */

#ifndef _NET_FIREWIRE_H_
#define _NET_FIREWIRE_H_

#include <sys/appleapiopts.h>

/*
 * The number of bytes in a FireWire EUI-64.
 */
#define	FIREWIRE_EUI64_LEN		8

/*
 * The number of bytes in the type field.
 */
#define	FIREWIRE_TYPE_LEN		2

/*
 * The length of the header provided by the FireWire network device.
 */
#define	FIREWIRE_HDR_LEN		(FIREWIRE_EUI64_LEN*2+FIREWIRE_TYPE_LEN)

/*
 * The minimum packet length.
 */
#define	FIREWIRE_MIN_LEN		64

/*
 * The maximum packet length.
 */
#define	FIREWIRE_MAX_LEN		4096

/*
 * A macro to validate a length with
 */
#define	FIREWIRE_IS_VALID_LEN(foo)	\
	((foo) >= FIREWIRE_MIN_LEN && (foo) <= FIREWIRE_MAX_LEN)

/*
 * Structure of header provided by the FireWire network device.
 *
 * The device uses a simplified header with just the non-changing
 * EUI-64 addresses and ethernet type specified;
 */
struct	firewire_header {
	u_char	firewire_dhost[FIREWIRE_EUI64_LEN];
	u_char	firewire_shost[FIREWIRE_EUI64_LEN];
	u_short	firewire_type;		/* ethertype */
};

/*
 * Format of FireWire EUI-64.
 */
struct	firewire_eui64 {
	u_char octet[FIREWIRE_EUI64_LEN];
};

/*
 * Format of FireWire hardware address.
 */
struct firewire_address {
    u_char 	eui64[FIREWIRE_EUI64_LEN];
    u_char 	maxRec;
    u_char 	spd;
    u_int16_t 	unicastFifoHi;
    u_int32_t 	unicastFifoLo;
};

#define FIREWIRE_ADDR_LEN	16 	/* sizeof(struct firewire_address) */


#define FIREWIRE_MTU	(FIREWIRE_MAX_LEN - FIREWIRE_HDR_LEN)
#define	FIREWIRE_MIN	(FIREWIRE_MIN_LEN - FIREWIRE_HDR_LEN)

#endif /* !_NET_FIREWIRE_H_ */

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
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _NET_IF_BOND_VAR_H_
#define	_NET_IF_BOND_VAR_H_

#include <sys/types.h>

#include <net/lacp.h>

#define IF_BOND_OP_ADD_INTERFACE		1
#define IF_BOND_OP_REMOVE_INTERFACE		2
#define IF_BOND_OP_GET_STATUS			3
#define IF_BOND_OP_SET_VERBOSE			4

struct if_bond_partner_state {
    lacp_system 		ibps_system;
    lacp_system_priority 	ibps_system_priority;
    lacp_key			ibps_key;
    lacp_port			ibps_port;
    lacp_port_priority		ibps_port_priority;
    lacp_actor_partner_state	ibps_state;
    u_char			ibps_reserved1;
};

#define IF_BOND_STATUS_SELECTED_STATE_UNSELECTED	0
#define IF_BOND_STATUS_SELECTED_STATE_SELECTED		1
#define IF_BOND_STATUS_SELECTED_STATE_STANDBY		2

struct if_bond_status {
    char 			ibs_if_name[IFNAMSIZ];	/* interface name */
    lacp_port_priority		ibs_port_priority;
    lacp_actor_partner_state	ibs_state;
    u_char			ibs_selected_state;
    struct if_bond_partner_state ibs_partner_state;
    u_int32_t			ibs_reserved[8];
};

#define IF_BOND_STATUS_REQ_VERSION	1

struct if_bond_status_req {
    int		ibsr_version;	/* version */
    int		ibsr_total;	/* returned number of struct if_bond_status's */
    int		ibsr_count;	/* number that will fit in ibsr_buffer */
    union {			/* buffer to hold if_bond_status's */
	char *		ibsru_buffer32;
	u_int64_t	ibsru_buffer64;
    } ibsr_ibsru;
    lacp_key	ibsr_key;	/* returned */
    u_int16_t	ibsr_reserved0;	/* for future use */
    u_int32_t	ibsr_reserved[3];/* for future use */
};

#if defined(__LP64__)
#define ibsr_buffer	ibsr_ibsru.ibsru_buffer64
#else
#define ibsr_buffer	ibsr_ibsru.ibsru_buffer32
#endif

struct if_bond_req {
    u_int32_t	ibr_op;				/* operation */
    union {
	char	ibru_if_name[IFNAMSIZ];		/* interface name */
	struct if_bond_status_req ibru_status;	/* status information */
	int	ibru_int_val;
    } ibr_ibru;
};

#ifdef KERNEL_PRIVATE
int bond_family_init(void);
#endif KERNEL_PRIVATE

#endif /* _NET_IF_BOND_VAR_H_ */

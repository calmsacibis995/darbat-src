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
 *	Copyright (c) 1997-1998 Apple Computer, Inc.
 *	All Rights Reserved.
 */

/*
 *   Modified, March 17, 1997 by Tuyen Nguyen for MacOSX.
 */
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/param.h>
#include <machine/spl.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/filedesc.h>
#include <sys/fcntl.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>

#include <net/if.h>

#include <netat/sysglue.h> 
#include <netat/appletalk.h>
#include <netat/ep.h>
#include <netat/ddp.h>
#include <netat/debug.h>
#include <netat/at_snmp.h>
#include <netat/at_pcb.h>
#include <netat/at_var.h>

extern snmpStats_t snmpStats;

/****************************************************************/
/*								*/
/*								*/
/*			Echo Protocol				*/
/*								*/
/*								*/
/****************************************************************/

void ep_input (mp, ifID)
     gbuf_t	*mp;
     register at_ifaddr_t *ifID;
{
	register at_ddp_t	*ddp;

	snmpStats.ec_echoReq++;
	ddp = (at_ddp_t *)gbuf_rptr(mp);

	/* ep packets that have a source broadcast can cause
         * possible broadcast storms, prevent that here
         */
	if ( NET_VALUE(ddp->src_net) == 0 || ddp->src_node == 255) {
		gbuf_freem(mp);
		return;
	}
	
	/*
	 * Check if this AEP message is for us or need to be forwarded
	 */
	if (!ROUTING_MODE || 
	    (ifID->ifThisNode.s_net == NET_VALUE(ddp->dst_net))
	    && (ifID->ifThisNode.s_node == ddp->dst_node)) {

		dPrintf(D_M_AEP, D_L_INFO, ("aep_input: received for this port from %d:%d\n",
			NET_VALUE(ddp->src_net), ddp->src_node));

		if (ddp->type == DDP_ECHO && 
		    ddp->data[0] == EP_REQUEST) {
			ddp->data[0] = EP_REPLY;
			NET_NET(ddp->dst_net, ddp->src_net);
			ddp->dst_node = ddp->src_node;
			ddp->dst_socket = ddp->src_socket;
			/* send the packet out.... */
			snmpStats.ec_echoReply++;
			(void)ddp_output(&mp, (at_socket)EP_SOCKET, FALSE);
		} else
			gbuf_freem(mp);
	}
	else {
		dPrintf(D_M_AEP, D_L_INFO,
			 ("aep_input: calling routing needed  from %d:%d to %d:%d\n",
			NET_VALUE(ddp->src_net), ddp->src_node, NET_VALUE(ddp->dst_net),
			ddp->dst_node));
		routing_needed(mp, ifID, TRUE);
	}

	return;
}

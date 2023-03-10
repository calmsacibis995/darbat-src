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
 * Copyright (c) 2002,2000 Apple Computer, Inc. All rights reserved.
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
 * @OSF_COPYRIGHT@
 */

/*
 * Mach RPC Subsystem Interfaces
 */

#ifndef	_MACH_RPC_H_
#define _MACH_RPC_H_

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/vm_types.h>

#include <mach/mig.h>
#include <mach/mig_errors.h>
#include <mach/machine/rpc.h>
#include <mach/thread_status.h>

/*
 * These are the types for RPC-specific variants of the MIG routine
 * descriptor and subsystem data types.
 *
 * THIS IS ONLY FOR COMPATIBILITY.  WE WILL NOT BE IMPLEMENTING THIS.
 */

/*
 * Basic mach rpc types.
 */
typedef unsigned int    routine_arg_type;
typedef unsigned int	routine_arg_offset;
typedef unsigned int	routine_arg_size;

/*
 * Definitions for a signature's argument and routine descriptor's.
 */
struct rpc_routine_arg_descriptor {
	routine_arg_type	type;	   /* Port, Array, etc. */
        routine_arg_size        size;      /* element size in bytes */
        routine_arg_size        count;     /* number of elements */
	routine_arg_offset	offset;	   /* Offset in list of routine args */
};
typedef struct rpc_routine_arg_descriptor *rpc_routine_arg_descriptor_t;

struct rpc_routine_descriptor {
	mig_impl_routine_t	impl_routine;	/* Server work func pointer   */
	mig_stub_routine_t	stub_routine;	/* Unmarshalling func pointer */
	unsigned int		argc;		/* Number of argument words   */
	unsigned int		descr_count;	/* Number of complex argument */
					        /* descriptors                */
	rpc_routine_arg_descriptor_t
				arg_descr;	/* Pointer to beginning of    */
						/* the arg_descr array        */
	unsigned int		max_reply_msg;	/* Max size for reply msg     */
};
typedef struct rpc_routine_descriptor *rpc_routine_descriptor_t;

#define RPC_DESCR_SIZE(x) ((x)->descr_count * \
				sizeof(struct rpc_routine_arg_descriptor))

struct rpc_signature {
    struct rpc_routine_descriptor rd;
    struct rpc_routine_arg_descriptor rad[1];
};

#define RPC_SIGBUF_SIZE 8

/*
 *	A subsystem describes a set of server routines that can be invoked by
 *	mach_rpc() on the ports that are registered with the subsystem.  For
 *	each routine, the routine number is given, along with the
 *	address of the implementation function in the server and a
 *	description of the arguments of the routine (it's "signature").
 *
 *	This structure definition is only a template for what is really a
 *	variable-length structure (generated by MIG for each subsystem).
 *	The actual structures do not always have one entry in the routine
 *	array, and also have a varying number of entries in the arg_descr
 *	array.  Each routine has an array of zero or more arg descriptors
 *	one for each complex arg.  These arrays are all catenated together
 *	to form the arg_descr field of the subsystem struct.  The
 *	arg_descr field of each routine entry points to a unique sub-sequence
 *	within this catenated array.  The goal is to keep everything
 *	contiguous.
 */
struct rpc_subsystem {
	void		*reserved;	/* Reserved for system use */

	mach_msg_id_t	start;		/* Min routine number */
	mach_msg_id_t	end;		/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max mach_msg size */
	vm_address_t	base_addr;	/* Address of this struct in user */

	struct rpc_routine_descriptor	/* Array of routine descriptors */
			routine[1       /* Actually, (start-end+1) */
				 ];

	struct rpc_routine_arg_descriptor
			arg_descriptor[1   /* Actually, the sum of the descr_ */
					]; /* count fields for all routines   */
};
typedef struct rpc_subsystem  *rpc_subsystem_t;

#define RPC_SUBSYSTEM_NULL	((rpc_subsystem_t) 0)

#endif	/* _MACH_RPC_H_ */

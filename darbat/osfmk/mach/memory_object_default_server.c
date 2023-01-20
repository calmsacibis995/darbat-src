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
 * IDENTIFICATION:
 * stub generated Tue Mar  7 16:25:31 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module memory_object_default */

#define	__MIG_check__Request__memory_object_default_subsystem__ 1
#define	__NDR_convert__Request__memory_object_default_subsystem__ 1

#include "memory_object_default_server.h"

#undef mig_internal
#ifndef	mig_internal
#define	mig_internal	static __inline__
#endif	/* mig_internal */

#ifndef	mig_external
#define mig_external
#endif	/* mig_external */

#if	!defined(__MigTypeCheck) && defined(TypeCheck)
#define	__MigTypeCheck		TypeCheck	/* Legacy setting */
#endif	/* !defined(__MigTypeCheck) */

#if	!defined(__MigKernelSpecificCode) && defined(_MIG_KERNEL_SPECIFIC_CODE_)
#define	__MigKernelSpecificCode	_MIG_KERNEL_SPECIFIC_CODE_	/* Legacy setting */
#endif	/* !defined(__MigKernelSpecificCode) */

#ifndef	LimitCheck
#define	LimitCheck 0
#endif	/* LimitCheck */

#ifndef	min
#define	min(a,b)  ( ((a) < (b))? (a): (b) )
#endif	/* min */

#if !defined(_WALIGN_)
#define _WALIGN_(x) (((x) + 3) & ~3)
#endif /* !defined(_WALIGN_) */

#if !defined(_WALIGNSZ_)
#define _WALIGNSZ_(x) _WALIGN_(sizeof(x))
#endif /* !defined(_WALIGNSZ_) */

#ifndef	UseStaticTemplates
#define	UseStaticTemplates	0
#endif	/* UseStaticTemplates */

#ifndef	__DeclareRcvRpc
#define	__DeclareRcvRpc(_NUM_, _NAME_)
#endif	/* __DeclareRcvRpc */

#ifndef	__BeforeRcvRpc
#define	__BeforeRcvRpc(_NUM_, _NAME_)
#endif	/* __BeforeRcvRpc */

#ifndef	__AfterRcvRpc
#define	__AfterRcvRpc(_NUM_, _NAME_)
#endif	/* __AfterRcvRpc */

#ifndef	__DeclareRcvSimple
#define	__DeclareRcvSimple(_NUM_, _NAME_)
#endif	/* __DeclareRcvSimple */

#ifndef	__BeforeRcvSimple
#define	__BeforeRcvSimple(_NUM_, _NAME_)
#endif	/* __BeforeRcvSimple */

#ifndef	__AfterRcvSimple
#define	__AfterRcvSimple(_NUM_, _NAME_)
#endif	/* __AfterRcvSimple */

#define novalue void

#if	__MigKernelSpecificCode
#define msgh_request_port	msgh_remote_port
#define MACH_MSGH_BITS_REQUEST(bits)	MACH_MSGH_BITS_REMOTE(bits)
#define msgh_reply_port		msgh_local_port
#define MACH_MSGH_BITS_REPLY(bits)	MACH_MSGH_BITS_LOCAL(bits)
#else
#define msgh_request_port	msgh_local_port
#define MACH_MSGH_BITS_REQUEST(bits)	MACH_MSGH_BITS_LOCAL(bits)
#define msgh_reply_port		msgh_remote_port
#define MACH_MSGH_BITS_REPLY(bits)	MACH_MSGH_BITS_REMOTE(bits)
#endif /* __MigKernelSpecificCode */

#define MIG_RETURN_ERROR(X, code)	{\
				((mig_reply_error_t *)X)->RetCode = code;\
				((mig_reply_error_t *)X)->NDR = NDR_record;\
				return;\
				}

/* Forward Declarations */


mig_internal novalue _Xmemory_object_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_default_subsystem__
#if !defined(__MIG_check__Request__memory_object_create_t__defined)
#define __MIG_check__Request__memory_object_create_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#if	defined(__NDR_convert__int_rep__memory_object_default__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__memory_object_default__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_default__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__memory_object_default__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_default__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__memory_object_default__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#if	defined(__NDR_convert__char_rep__memory_object_default__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__memory_object_default__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_default__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__memory_object_default__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_default__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__memory_object_default__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#if	defined(__NDR_convert__float_rep__memory_object_default__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__memory_object_default__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_default__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__memory_object_default__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_default__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__memory_object_default__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_create_t(__Request__memory_object_create_t *In0P)
{

	typedef __Request__memory_object_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined)
		__NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size(&In0P->new_memory_object_size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_create_t__new_memory_object_size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined)
		__NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size(&In0P->new_memory_object_size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_create_t__new_memory_object_size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined)
		__NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size(&In0P->new_memory_object_size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_create_t__new_memory_object_size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_create_t__defined) */
#endif /* __MIG_check__Request__memory_object_default_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_create */
mig_internal novalue _Xmemory_object_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_size_t new_memory_object_size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_create_t __Request;
	typedef __Reply__memory_object_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_memory_objectTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_memory_objectTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	memory_object_t new_memory_object;

	__DeclareRcvRpc(2250, "memory_object_create")
	__BeforeRcvRpc(2250, "memory_object_create")

#if	defined(__MIG_check__Request__memory_object_create_t__defined)
	check_result = __MIG_check__Request__memory_object_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_create_t__defined) */

#if	UseStaticTemplates
	OutP->new_memory_object = new_memory_objectTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->new_memory_object.disposition = 17;
#else
	OutP->new_memory_object.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->new_memory_object.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = default_pager_memory_object_create(null_conversion(In0P->Head.msgh_request_port), In0P->new_memory_object_size, &new_memory_object);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->new_memory_object.name = (mach_port_t)convert_memory_object_to_port(new_memory_object);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(2250, "memory_object_create")
}



/* Description of this subsystem, for use in direct RPC */
const struct default_pager_memory_object_default_subsystem default_pager_memory_object_default_subsystem = {
	memory_object_default_server_routine,
	2250,
	2251,
	(mach_msg_size_t)sizeof(union __ReplyUnion__default_pager_memory_object_default_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_create, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_create_t)},
	}
};

mig_external boolean_t memory_object_default_server
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{
	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	register mig_routine_t routine;

	OutHeadP->msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REPLY(InHeadP->msgh_bits), 0);
	OutHeadP->msgh_remote_port = InHeadP->msgh_reply_port;
	/* Minimal size: routine() will update it if different */
	OutHeadP->msgh_size = (mach_msg_size_t)sizeof(mig_reply_error_t);
	OutHeadP->msgh_local_port = MACH_PORT_NULL;
	OutHeadP->msgh_id = InHeadP->msgh_id + 100;

	if ((InHeadP->msgh_id > 2250) || (InHeadP->msgh_id < 2250) ||
	    ((routine = default_pager_memory_object_default_subsystem.routine[InHeadP->msgh_id - 2250].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t memory_object_default_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 2250;

	if ((msgh_id > 0) || (msgh_id < 0))
		return 0;

	return default_pager_memory_object_default_subsystem.routine[msgh_id].stub_routine;
}

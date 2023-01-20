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
 * stub generated Tue Mar  7 16:25:30 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module memory_object */

#define	__MIG_check__Request__memory_object_subsystem__ 1
#define	__NDR_convert__Request__memory_object_subsystem__ 1

#include "memory_object_server.h"

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


mig_internal novalue _Xmemory_object_init
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_terminate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_data_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_data_return
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_data_initialize
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_data_unlock
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_synchronize
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_unmap
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_init_t__defined)
#define __MIG_check__Request__memory_object_init_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_init_t(__Request__memory_object_init_t *In0P)
{

	typedef __Request__memory_object_init_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->memory_control.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->memory_control.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined)
		__NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size(&In0P->memory_object_page_size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_init_t__memory_object_page_size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined)
		__NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size(&In0P->memory_object_page_size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_init_t__memory_object_page_size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined)
		__NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size(&In0P->memory_object_page_size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_init_t__memory_object_page_size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_init_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_init */
mig_internal novalue _Xmemory_object_init
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t memory_control;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		memory_object_cluster_size_t memory_object_page_size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_init_t __Request;
	typedef __Reply__memory_object_init_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_init_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_init_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2200, "memory_object_init")
	__BeforeRcvRpc(2200, "memory_object_init")

#if	defined(__MIG_check__Request__memory_object_init_t__defined)
	check_result = __MIG_check__Request__memory_object_init_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_init_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->memory_control.name);

	OutP->RetCode = dp_memory_object_init(convert_port_to_memory_object(In0P->Head.msgh_request_port), memory_control, In0P->memory_object_page_size);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->memory_control.name))
		ipc_port_release_send((ipc_port_t)In0P->memory_control.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2200, "memory_object_init")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_terminate_t__defined)
#define __MIG_check__Request__memory_object_terminate_t__defined

mig_internal kern_return_t __MIG_check__Request__memory_object_terminate_t(__Request__memory_object_terminate_t *In0P)
{

	typedef __Request__memory_object_terminate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_terminate_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_terminate */
mig_internal novalue _Xmemory_object_terminate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_terminate_t __Request;
	typedef __Reply__memory_object_terminate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_terminate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_terminate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2201, "memory_object_terminate")
	__BeforeRcvRpc(2201, "memory_object_terminate")

#if	defined(__MIG_check__Request__memory_object_terminate_t__defined)
	check_result = __MIG_check__Request__memory_object_terminate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_terminate_t__defined) */

	OutP->RetCode = dp_memory_object_terminate(convert_port_to_memory_object(In0P->Head.msgh_request_port));
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2201, "memory_object_terminate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_data_request_t__defined)
#define __MIG_check__Request__memory_object_data_request_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#if	defined(__NDR_convert__int_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#if	defined(__NDR_convert__char_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__length(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#if	defined(__NDR_convert__float_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_data_request_t(__Request__memory_object_data_request_t *In0P)
{

	typedef __Request__memory_object_data_request_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_data_request_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_request_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined)
		__NDR_convert__int_rep__Request__memory_object_data_request_t__length(&In0P->length, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_request_t__length__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined)
		__NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access(&In0P->desired_access, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_request_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_data_request_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_request_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined)
		__NDR_convert__char_rep__Request__memory_object_data_request_t__length(&In0P->length, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_request_t__length__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined)
		__NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access(&In0P->desired_access, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_request_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_data_request_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_request_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined)
		__NDR_convert__float_rep__Request__memory_object_data_request_t__length(&In0P->length, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_request_t__length__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined)
		__NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access(&In0P->desired_access, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_request_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_data_request_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_data_request */
mig_internal novalue _Xmemory_object_data_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t length;
		vm_prot_t desired_access;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_data_request_t __Request;
	typedef __Reply__memory_object_data_request_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_data_request_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_data_request_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2202, "memory_object_data_request")
	__BeforeRcvRpc(2202, "memory_object_data_request")

#if	defined(__MIG_check__Request__memory_object_data_request_t__defined)
	check_result = __MIG_check__Request__memory_object_data_request_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_data_request_t__defined) */

	OutP->RetCode = dp_memory_object_data_request(convert_port_to_memory_object(In0P->Head.msgh_request_port), In0P->offset, In0P->length, In0P->desired_access);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2202, "memory_object_data_request")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_data_return_t__defined)
#define __MIG_check__Request__memory_object_data_return_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined
#if	defined(__NDR_convert__int_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__int_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined
#if	defined(__NDR_convert__int_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__int_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined
#if	defined(__NDR_convert__int_rep__memory_object__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__int_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__int_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined
#if	defined(__NDR_convert__char_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__char_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined
#if	defined(__NDR_convert__char_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__char_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined
#if	defined(__NDR_convert__char_rep__memory_object__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__char_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__char_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined
#if	defined(__NDR_convert__float_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__float_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined
#if	defined(__NDR_convert__float_rep__memory_object__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__float_rep__memory_object__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined
#if	defined(__NDR_convert__float_rep__memory_object__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__float_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__float_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_data_return_t(__Request__memory_object_data_return_t *In0P)
{

	typedef __Request__memory_object_data_return_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_data_return_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_return_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_data_return_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_return_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined)
		__NDR_convert__int_rep__Request__memory_object_data_return_t__dirty(&In0P->dirty, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_return_t__dirty__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined)
		__NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy(&In0P->kernel_copy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_return_t__kernel_copy__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined)
		__NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags(&In0P->upl_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_return_t__upl_flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_data_return_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_return_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_data_return_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_return_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined)
		__NDR_convert__char_rep__Request__memory_object_data_return_t__dirty(&In0P->dirty, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_return_t__dirty__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined)
		__NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy(&In0P->kernel_copy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_return_t__kernel_copy__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined)
		__NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags(&In0P->upl_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_return_t__upl_flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_data_return_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_return_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_data_return_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_return_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined)
		__NDR_convert__float_rep__Request__memory_object_data_return_t__dirty(&In0P->dirty, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_return_t__dirty__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined)
		__NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy(&In0P->kernel_copy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_return_t__kernel_copy__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined)
		__NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags(&In0P->upl_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_return_t__upl_flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_data_return_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_data_return */
mig_internal novalue _Xmemory_object_data_return
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		boolean_t dirty;
		boolean_t kernel_copy;
		int upl_flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_data_return_t __Request;
	typedef __Reply__memory_object_data_return_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_data_return_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_data_return_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2203, "memory_object_data_return")
	__BeforeRcvRpc(2203, "memory_object_data_return")

#if	defined(__MIG_check__Request__memory_object_data_return_t__defined)
	check_result = __MIG_check__Request__memory_object_data_return_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_data_return_t__defined) */

	OutP->RetCode = dp_memory_object_data_return(convert_port_to_memory_object(In0P->Head.msgh_request_port), In0P->offset, In0P->size, &OutP->resid_offset, &OutP->io_error, In0P->dirty, In0P->kernel_copy, In0P->upl_flags);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2203, "memory_object_data_return")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_data_initialize_t__defined)
#define __MIG_check__Request__memory_object_data_initialize_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_data_initialize_t(__Request__memory_object_data_initialize_t *In0P)
{

	typedef __Request__memory_object_data_initialize_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_initialize_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_data_initialize_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_initialize_t__size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_initialize_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_data_initialize_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_initialize_t__size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_initialize_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_data_initialize_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_initialize_t__size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_data_initialize_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_data_initialize */
mig_internal novalue _Xmemory_object_data_initialize
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_data_initialize_t __Request;
	typedef __Reply__memory_object_data_initialize_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_data_initialize_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_data_initialize_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2204, "memory_object_data_initialize")
	__BeforeRcvRpc(2204, "memory_object_data_initialize")

#if	defined(__MIG_check__Request__memory_object_data_initialize_t__defined)
	check_result = __MIG_check__Request__memory_object_data_initialize_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_data_initialize_t__defined) */

	OutP->RetCode = dp_memory_object_data_initialize(convert_port_to_memory_object(In0P->Head.msgh_request_port), In0P->offset, In0P->size);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2204, "memory_object_data_initialize")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_data_unlock_t__defined)
#define __MIG_check__Request__memory_object_data_unlock_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#if	defined(__NDR_convert__int_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#if	defined(__NDR_convert__char_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#if	defined(__NDR_convert__float_rep__memory_object__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_data_unlock_t(__Request__memory_object_data_unlock_t *In0P)
{

	typedef __Request__memory_object_data_unlock_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_data_unlock_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined)
		__NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access(&In0P->desired_access, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_data_unlock_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_data_unlock_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined)
		__NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access(&In0P->desired_access, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_data_unlock_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_data_unlock_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined)
		__NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access(&In0P->desired_access, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_data_unlock_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_data_unlock_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_data_unlock */
mig_internal novalue _Xmemory_object_data_unlock
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		vm_prot_t desired_access;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_data_unlock_t __Request;
	typedef __Reply__memory_object_data_unlock_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_data_unlock_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_data_unlock_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2205, "memory_object_data_unlock")
	__BeforeRcvRpc(2205, "memory_object_data_unlock")

#if	defined(__MIG_check__Request__memory_object_data_unlock_t__defined)
	check_result = __MIG_check__Request__memory_object_data_unlock_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_data_unlock_t__defined) */

	OutP->RetCode = dp_memory_object_data_unlock(convert_port_to_memory_object(In0P->Head.msgh_request_port), In0P->offset, In0P->size, In0P->desired_access);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2205, "memory_object_data_unlock")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_synchronize_t__defined)
#define __MIG_check__Request__memory_object_synchronize_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__int_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#if	defined(__NDR_convert__int_rep__memory_object__vm_sync_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__memory_object__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_sync_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__char_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#if	defined(__NDR_convert__char_rep__memory_object__vm_sync_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__memory_object__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_sync_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_cluster_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_cluster_size_t((memory_object_cluster_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__float_rep__memory_object__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#if	defined(__NDR_convert__float_rep__memory_object__vm_sync_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__memory_object__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_sync_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__memory_object__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__memory_object__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_synchronize_t(__Request__memory_object_synchronize_t *In0P)
{

	typedef __Request__memory_object_synchronize_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_synchronize_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_synchronize_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_synchronize_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_synchronize_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined)
		__NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags(&In0P->sync_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_synchronize_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_synchronize_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_synchronize_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_synchronize_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_synchronize_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined)
		__NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags(&In0P->sync_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_synchronize_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_synchronize_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_synchronize_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_synchronize_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_synchronize_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined)
		__NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags(&In0P->sync_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_synchronize_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_synchronize_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_synchronize */
mig_internal novalue _Xmemory_object_synchronize
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		vm_sync_t sync_flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_synchronize_t __Request;
	typedef __Reply__memory_object_synchronize_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_synchronize_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_synchronize_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2206, "memory_object_synchronize")
	__BeforeRcvRpc(2206, "memory_object_synchronize")

#if	defined(__MIG_check__Request__memory_object_synchronize_t__defined)
	check_result = __MIG_check__Request__memory_object_synchronize_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_synchronize_t__defined) */

	OutP->RetCode = dp_memory_object_synchronize(convert_port_to_memory_object(In0P->Head.msgh_request_port), In0P->offset, In0P->size, In0P->sync_flags);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2206, "memory_object_synchronize")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_subsystem__
#if !defined(__MIG_check__Request__memory_object_unmap_t__defined)
#define __MIG_check__Request__memory_object_unmap_t__defined

mig_internal kern_return_t __MIG_check__Request__memory_object_unmap_t(__Request__memory_object_unmap_t *In0P)
{

	typedef __Request__memory_object_unmap_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_unmap_t__defined) */
#endif /* __MIG_check__Request__memory_object_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_unmap */
mig_internal novalue _Xmemory_object_unmap
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_unmap_t __Request;
	typedef __Reply__memory_object_unmap_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_unmap_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_unmap_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(2207, "memory_object_unmap")
	__BeforeRcvRpc(2207, "memory_object_unmap")

#if	defined(__MIG_check__Request__memory_object_unmap_t__defined)
	check_result = __MIG_check__Request__memory_object_unmap_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_unmap_t__defined) */

	OutP->RetCode = dp_memory_object_unmap(convert_port_to_memory_object(In0P->Head.msgh_request_port));
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2207, "memory_object_unmap")
}



/* Description of this subsystem, for use in direct RPC */
const struct dp_memory_object_subsystem dp_memory_object_subsystem = {
	memory_object_server_routine,
	2200,
	2208,
	(mach_msg_size_t)sizeof(union __ReplyUnion__dp_memory_object_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_init, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_init_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_terminate, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_terminate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_data_request, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_data_request_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_data_return, 9, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_data_return_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_data_initialize, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_data_initialize_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_data_unlock, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_data_unlock_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_synchronize, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_synchronize_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_unmap, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_unmap_t)},
	}
};

mig_external boolean_t memory_object_server
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

	if ((InHeadP->msgh_id > 2207) || (InHeadP->msgh_id < 2200) ||
	    ((routine = dp_memory_object_subsystem.routine[InHeadP->msgh_id - 2200].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t memory_object_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 2200;

	if ((msgh_id > 7) || (msgh_id < 0))
		return 0;

	return dp_memory_object_subsystem.routine[msgh_id].stub_routine;
}

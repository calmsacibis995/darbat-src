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
 * stub generated Tue Mar  7 16:25:29 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module mach_host */

#define	__MIG_check__Request__mach_host_subsystem__ 1
#define	__NDR_convert__Request__mach_host_subsystem__ 1

#include "mach_host_server.h"

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


mig_internal novalue _Xhost_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_kernel_version
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_page_size
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_memory_object_memory_entry
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_processor_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_io_master
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_clock_service
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xkmod_get_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_zone_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_virtual_physical_table_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_ipc_hash_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xenable_bluebox
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xdisable_bluebox
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_default
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_memory_object_memory_entry_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_statistics
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_request_notification
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_lockgroup_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_info_t__defined)
#define __MIG_check__Request__host_info_t__defined
#ifndef __NDR_convert__int_rep__Request__host_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__mach_host__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_host__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__host_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_info_t(__Request__host_info_t *In0P)
{

	typedef __Request__host_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__host_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined)
		__NDR_convert__int_rep__Request__host_info_t__host_info_outCnt(&In0P->host_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_info_t__host_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_info_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__host_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_info_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__host_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_info */
mig_internal novalue _Xhost_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		host_flavor_t flavor;
		mach_msg_type_number_t host_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_info_t __Request;
	typedef __Reply__host_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(200, "host_info")
	__BeforeRcvRpc(200, "host_info")

#if	defined(__MIG_check__Request__host_info_t__defined)
	check_result = __MIG_check__Request__host_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_info_t__defined) */

	OutP->host_info_outCnt = 14;
	if (In0P->host_info_outCnt < OutP->host_info_outCnt)
		OutP->host_info_outCnt = In0P->host_info_outCnt;

	OutP->RetCode = host_info(convert_port_to_host(In0P->Head.msgh_request_port), In0P->flavor, OutP->host_info_out, &OutP->host_info_outCnt);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 56) + (((4 * OutP->host_info_outCnt)));

	__AfterRcvRpc(200, "host_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_kernel_version_t__defined)
#define __MIG_check__Request__host_kernel_version_t__defined

mig_internal kern_return_t __MIG_check__Request__host_kernel_version_t(__Request__host_kernel_version_t *In0P)
{

	typedef __Request__host_kernel_version_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_kernel_version_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_kernel_version */
mig_internal novalue _Xhost_kernel_version
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
	typedef __Request__host_kernel_version_t __Request;
	typedef __Reply__host_kernel_version_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_kernel_version_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_kernel_version_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(201, "host_kernel_version")
	__BeforeRcvRpc(201, "host_kernel_version")

#if	defined(__MIG_check__Request__host_kernel_version_t__defined)
	check_result = __MIG_check__Request__host_kernel_version_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_kernel_version_t__defined) */

	OutP->RetCode = host_kernel_version(convert_port_to_host(In0P->Head.msgh_request_port), OutP->kernel_version);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->kernel_versionCnt = strlen(OutP->kernel_version) + 1;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 512) + (_WALIGN_((OutP->kernel_versionCnt + 3) & ~3));

	__AfterRcvRpc(201, "host_kernel_version")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_page_size_t__defined)
#define __MIG_check__Request__host_page_size_t__defined

mig_internal kern_return_t __MIG_check__Request__host_page_size_t(__Request__host_page_size_t *In0P)
{

	typedef __Request__host_page_size_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_page_size_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_page_size */
mig_internal novalue _Xhost_page_size
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
	typedef __Request__host_page_size_t __Request;
	typedef __Reply__host_page_size_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_page_size_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_page_size_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(202, "host_page_size")
	__BeforeRcvRpc(202, "host_page_size")

#if	defined(__MIG_check__Request__host_page_size_t__defined)
	check_result = __MIG_check__Request__host_page_size_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_page_size_t__defined) */

	OutP->RetCode = host_page_size(convert_port_to_host(In0P->Head.msgh_request_port), &OutP->out_page_size);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(202, "host_page_size")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__mach_memory_object_memory_entry_t__defined)
#define __MIG_check__Request__mach_memory_object_memory_entry_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#if	defined(__NDR_convert__int_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__int_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined */

#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#if	defined(__NDR_convert__int_rep__mach_host__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__mach_host__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__mach_host__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#if	defined(__NDR_convert__int_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#if	defined(__NDR_convert__char_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__char_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#if	defined(__NDR_convert__char_rep__mach_host__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__mach_host__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__mach_host__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#if	defined(__NDR_convert__char_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#if	defined(__NDR_convert__float_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__float_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#if	defined(__NDR_convert__float_rep__mach_host__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__mach_host__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__mach_host__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#if	defined(__NDR_convert__float_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined */


mig_internal kern_return_t __MIG_check__Request__mach_memory_object_memory_entry_t(__Request__mach_memory_object_memory_entry_t *In0P)
{

	typedef __Request__mach_memory_object_memory_entry_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->pager.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->pager.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal(&In0P->internal, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__internal__defined */
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission(&In0P->permission, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal(&In0P->internal, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__internal__defined */
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission(&In0P->permission, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal(&In0P->internal, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__internal__defined */
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission(&In0P->permission, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_memory_object_memory_entry_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_memory_object_memory_entry */
mig_internal novalue _Xmach_memory_object_memory_entry
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t pager;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		boolean_t internal;
		vm_size_t size;
		vm_prot_t permission;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_memory_object_memory_entry_t __Request;
	typedef __Reply__mach_memory_object_memory_entry_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_memory_object_memory_entry_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_memory_object_memory_entry_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t entry_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t entry_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(203, "mach_memory_object_memory_entry")
	__BeforeRcvRpc(203, "mach_memory_object_memory_entry")

#if	defined(__MIG_check__Request__mach_memory_object_memory_entry_t__defined)
	check_result = __MIG_check__Request__mach_memory_object_memory_entry_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_memory_object_memory_entry_t__defined) */

#if	UseStaticTemplates
	OutP->entry_handle = entry_handleTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->entry_handle.disposition = 17;
#else
	OutP->entry_handle.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->entry_handle.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = mach_memory_object_memory_entry(convert_port_to_host(In0P->Head.msgh_request_port), In0P->internal, In0P->size, In0P->permission, convert_port_to_memory_object(In0P->pager.name), &OutP->entry_handle.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->pager.name))
		ipc_port_release_send((ipc_port_t)In0P->pager.name);
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(203, "mach_memory_object_memory_entry")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_processor_info_t__defined)
#define __MIG_check__Request__host_processor_info_t__defined
#ifndef __NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__mach_host__processor_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__mach_host__processor_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__mach_host__processor_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_processor_info_t(__Request__host_processor_info_t *In0P)
{

	typedef __Request__host_processor_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__host_processor_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_processor_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__host_processor_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_processor_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__host_processor_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_processor_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_processor_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_processor_info */
mig_internal novalue _Xhost_processor_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_flavor_t flavor;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_processor_info_t __Request;
	typedef __Reply__host_processor_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_processor_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_processor_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t out_processor_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t out_processor_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(204, "host_processor_info")
	__BeforeRcvRpc(204, "host_processor_info")

#if	defined(__MIG_check__Request__host_processor_info_t__defined)
	check_result = __MIG_check__Request__host_processor_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_processor_info_t__defined) */

#if	UseStaticTemplates
	OutP->out_processor_info = out_processor_infoTemplate;
#else	/* UseStaticTemplates */
	OutP->out_processor_info.deallocate =  FALSE;
	OutP->out_processor_info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->out_processor_info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_processor_info(convert_port_to_host(In0P->Head.msgh_request_port), In0P->flavor, &OutP->out_processor_count, (processor_info_array_t *)&(OutP->out_processor_info.address), &OutP->out_processor_infoCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->out_processor_info.size = OutP->out_processor_infoCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(204, "host_processor_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_get_io_master_t__defined)
#define __MIG_check__Request__host_get_io_master_t__defined

mig_internal kern_return_t __MIG_check__Request__host_get_io_master_t(__Request__host_get_io_master_t *In0P)
{

	typedef __Request__host_get_io_master_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_io_master_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_io_master */
mig_internal novalue _Xhost_get_io_master
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
	typedef __Request__host_get_io_master_t __Request;
	typedef __Reply__host_get_io_master_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_io_master_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_io_master_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t io_masterTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t io_masterTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(205, "host_get_io_master")
	__BeforeRcvRpc(205, "host_get_io_master")

#if	defined(__MIG_check__Request__host_get_io_master_t__defined)
	check_result = __MIG_check__Request__host_get_io_master_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_io_master_t__defined) */

#if	UseStaticTemplates
	OutP->io_master = io_masterTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->io_master.disposition = 17;
#else
	OutP->io_master.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->io_master.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_get_io_master(convert_port_to_host(In0P->Head.msgh_request_port), &OutP->io_master.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(205, "host_get_io_master")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_get_clock_service_t__defined)
#define __MIG_check__Request__host_get_clock_service_t__defined
#ifndef __NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#if	defined(__NDR_convert__int_rep__mach_host__clock_id_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__mach_host__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock_id_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined */

#ifndef __NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#if	defined(__NDR_convert__char_rep__mach_host__clock_id_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__mach_host__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock_id_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined */

#ifndef __NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#if	defined(__NDR_convert__float_rep__mach_host__clock_id_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__mach_host__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock_id_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined */


mig_internal kern_return_t __MIG_check__Request__host_get_clock_service_t(__Request__host_get_clock_service_t *In0P)
{

	typedef __Request__host_get_clock_service_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined)
		__NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id(&In0P->clock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_get_clock_service_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined)
		__NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id(&In0P->clock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_get_clock_service_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined)
		__NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id(&In0P->clock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_get_clock_service_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_clock_service_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_clock_service */
mig_internal novalue _Xhost_get_clock_service
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		clock_id_t clock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_get_clock_service_t __Request;
	typedef __Reply__host_get_clock_service_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_clock_service_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_clock_service_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t clock_servTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t clock_servTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	clock_serv_t clock_serv;

	__DeclareRcvRpc(206, "host_get_clock_service")
	__BeforeRcvRpc(206, "host_get_clock_service")

#if	defined(__MIG_check__Request__host_get_clock_service_t__defined)
	check_result = __MIG_check__Request__host_get_clock_service_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_clock_service_t__defined) */

#if	UseStaticTemplates
	OutP->clock_serv = clock_servTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->clock_serv.disposition = 17;
#else
	OutP->clock_serv.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->clock_serv.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_get_clock_service(convert_port_to_host(In0P->Head.msgh_request_port), In0P->clock_id, &clock_serv);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->clock_serv.name = (mach_port_t)convert_clock_to_port(clock_serv);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(206, "host_get_clock_service")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__kmod_get_info_t__defined)
#define __MIG_check__Request__kmod_get_info_t__defined

mig_internal kern_return_t __MIG_check__Request__kmod_get_info_t(__Request__kmod_get_info_t *In0P)
{

	typedef __Request__kmod_get_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__kmod_get_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine kmod_get_info */
mig_internal novalue _Xkmod_get_info
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
	typedef __Request__kmod_get_info_t __Request;
	typedef __Reply__kmod_get_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__kmod_get_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__kmod_get_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t modulesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t modulesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(207, "kmod_get_info")
	__BeforeRcvRpc(207, "kmod_get_info")

#if	defined(__MIG_check__Request__kmod_get_info_t__defined)
	check_result = __MIG_check__Request__kmod_get_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__kmod_get_info_t__defined) */

#if	UseStaticTemplates
	OutP->modules = modulesTemplate;
#else	/* UseStaticTemplates */
	OutP->modules.deallocate =  FALSE;
	OutP->modules.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->modules.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = kmod_get_info(convert_port_to_host(In0P->Head.msgh_request_port), (kmod_args_t *)&(OutP->modules.address), &OutP->modulesCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->modules.size = OutP->modulesCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(207, "kmod_get_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_zone_info_t__defined)
#define __MIG_check__Request__host_zone_info_t__defined

mig_internal kern_return_t __MIG_check__Request__host_zone_info_t(__Request__host_zone_info_t *In0P)
{

	typedef __Request__host_zone_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_zone_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_zone_info */
mig_internal novalue _Xhost_zone_info
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
	typedef __Request__host_zone_info_t __Request;
	typedef __Reply__host_zone_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_zone_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_zone_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t namesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t namesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(208, "host_zone_info")
	__BeforeRcvRpc(208, "host_zone_info")

#if	defined(__MIG_check__Request__host_zone_info_t__defined)
	check_result = __MIG_check__Request__host_zone_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_zone_info_t__defined) */

#if	UseStaticTemplates
	OutP->names = namesTemplate;
#else	/* UseStaticTemplates */
	OutP->names.deallocate =  TRUE;
	OutP->names.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->names.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


#if	UseStaticTemplates
	OutP->info = infoTemplate;
#else	/* UseStaticTemplates */
	OutP->info.deallocate =  TRUE;
	OutP->info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	OutP->namesCnt = 0;

	OutP->infoCnt = 0;

	RetCode = host_zone_info(convert_port_to_host(In0P->Head.msgh_request_port), (zone_name_array_t *)&(OutP->names.address), &OutP->namesCnt, (zone_info_array_t *)&(OutP->info.address), &OutP->infoCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->names.size = OutP->namesCnt * 80;

	OutP->info.size = OutP->infoCnt * 36;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 2;
	__AfterRcvRpc(208, "host_zone_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_virtual_physical_table_info_t__defined)
#define __MIG_check__Request__host_virtual_physical_table_info_t__defined

mig_internal kern_return_t __MIG_check__Request__host_virtual_physical_table_info_t(__Request__host_virtual_physical_table_info_t *In0P)
{

	typedef __Request__host_virtual_physical_table_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_virtual_physical_table_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_virtual_physical_table_info */
mig_internal novalue _Xhost_virtual_physical_table_info
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
	typedef __Request__host_virtual_physical_table_info_t __Request;
	typedef __Reply__host_virtual_physical_table_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_virtual_physical_table_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_virtual_physical_table_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(209, "host_virtual_physical_table_info")
	__BeforeRcvRpc(209, "host_virtual_physical_table_info")

#if	defined(__MIG_check__Request__host_virtual_physical_table_info_t__defined)
	check_result = __MIG_check__Request__host_virtual_physical_table_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_virtual_physical_table_info_t__defined) */

#if	UseStaticTemplates
	OutP->info = infoTemplate;
#else	/* UseStaticTemplates */
	OutP->info.deallocate =  TRUE;
	OutP->info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	OutP->infoCnt = 0;

	RetCode = host_virtual_physical_table_info(convert_port_to_host(In0P->Head.msgh_request_port), (hash_info_bucket_array_t *)&(OutP->info.address), &OutP->infoCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->info.size = OutP->infoCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(209, "host_virtual_physical_table_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_ipc_hash_info_t__defined)
#define __MIG_check__Request__host_ipc_hash_info_t__defined

mig_internal kern_return_t __MIG_check__Request__host_ipc_hash_info_t(__Request__host_ipc_hash_info_t *In0P)
{

	typedef __Request__host_ipc_hash_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_ipc_hash_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_ipc_hash_info */
mig_internal novalue _Xhost_ipc_hash_info
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
	typedef __Request__host_ipc_hash_info_t __Request;
	typedef __Reply__host_ipc_hash_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_ipc_hash_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_ipc_hash_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(210, "host_ipc_hash_info")
	__BeforeRcvRpc(210, "host_ipc_hash_info")

#if	defined(__MIG_check__Request__host_ipc_hash_info_t__defined)
	check_result = __MIG_check__Request__host_ipc_hash_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_ipc_hash_info_t__defined) */

#if	UseStaticTemplates
	OutP->info = infoTemplate;
#else	/* UseStaticTemplates */
	OutP->info.deallocate =  TRUE;
	OutP->info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	OutP->infoCnt = 0;

	RetCode = host_ipc_hash_info(convert_port_to_host(In0P->Head.msgh_request_port), (hash_info_bucket_array_t *)&(OutP->info.address), &OutP->infoCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->info.size = OutP->infoCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(210, "host_ipc_hash_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__enable_bluebox_t__defined)
#define __MIG_check__Request__enable_bluebox_t__defined
#ifndef __NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined
#if	defined(__NDR_convert__int_rep__mach_host__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__int_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__int_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined */

#ifndef __NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#if	defined(__NDR_convert__int_rep__mach_host__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__int_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__int_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined */

#ifndef __NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#if	defined(__NDR_convert__int_rep__mach_host__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__int_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__int_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined */

#ifndef __NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined
#if	defined(__NDR_convert__char_rep__mach_host__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__char_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__char_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined */

#ifndef __NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#if	defined(__NDR_convert__char_rep__mach_host__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__char_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__char_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined */

#ifndef __NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#if	defined(__NDR_convert__char_rep__mach_host__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__char_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__char_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined */

#ifndef __NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined
#if	defined(__NDR_convert__float_rep__mach_host__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__float_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__float_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__taskID(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined */

#ifndef __NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#if	defined(__NDR_convert__float_rep__mach_host__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__float_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__float_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined */

#ifndef __NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#if	defined(__NDR_convert__float_rep__mach_host__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__float_rep__mach_host__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__float_rep__mach_host__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined
#define	__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined */


mig_internal kern_return_t __MIG_check__Request__enable_bluebox_t(__Request__enable_bluebox_t *In0P)
{

	typedef __Request__enable_bluebox_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined) || \
	defined(__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined) || \
	defined(__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined)
		__NDR_convert__int_rep__Request__enable_bluebox_t__taskID(&In0P->taskID, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__enable_bluebox_t__taskID__defined */
#if defined(__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined)
		__NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart(&In0P->TWI_TableStart, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__enable_bluebox_t__TWI_TableStart__defined */
#if defined(__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
		__NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart(&In0P->Desc_TableStart, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__enable_bluebox_t__Desc_TableStart__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined) || \
	defined(__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined) || \
	defined(__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined)
		__NDR_convert__char_rep__Request__enable_bluebox_t__taskID(&In0P->taskID, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__enable_bluebox_t__taskID__defined */
#if defined(__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined)
		__NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart(&In0P->TWI_TableStart, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__enable_bluebox_t__TWI_TableStart__defined */
#if defined(__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
		__NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart(&In0P->Desc_TableStart, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__enable_bluebox_t__Desc_TableStart__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined) || \
	defined(__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined) || \
	defined(__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined)
		__NDR_convert__float_rep__Request__enable_bluebox_t__taskID(&In0P->taskID, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__enable_bluebox_t__taskID__defined */
#if defined(__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined)
		__NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart(&In0P->TWI_TableStart, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__enable_bluebox_t__TWI_TableStart__defined */
#if defined(__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined)
		__NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart(&In0P->Desc_TableStart, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__enable_bluebox_t__Desc_TableStart__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__enable_bluebox_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine enable_bluebox */
mig_internal novalue _Xenable_bluebox
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		unsigned taskID;
		unsigned TWI_TableStart;
		unsigned Desc_TableStart;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__enable_bluebox_t __Request;
	typedef __Reply__enable_bluebox_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__enable_bluebox_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__enable_bluebox_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(211, "enable_bluebox")
	__BeforeRcvRpc(211, "enable_bluebox")

#if	defined(__MIG_check__Request__enable_bluebox_t__defined)
	check_result = __MIG_check__Request__enable_bluebox_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__enable_bluebox_t__defined) */

	OutP->RetCode = enable_bluebox(convert_port_to_host(In0P->Head.msgh_request_port), In0P->taskID, In0P->TWI_TableStart, In0P->Desc_TableStart);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(211, "enable_bluebox")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__disable_bluebox_t__defined)
#define __MIG_check__Request__disable_bluebox_t__defined

mig_internal kern_return_t __MIG_check__Request__disable_bluebox_t(__Request__disable_bluebox_t *In0P)
{

	typedef __Request__disable_bluebox_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__disable_bluebox_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine disable_bluebox */
mig_internal novalue _Xdisable_bluebox
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
	typedef __Request__disable_bluebox_t __Request;
	typedef __Reply__disable_bluebox_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__disable_bluebox_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__disable_bluebox_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(212, "disable_bluebox")
	__BeforeRcvRpc(212, "disable_bluebox")

#if	defined(__MIG_check__Request__disable_bluebox_t__defined)
	check_result = __MIG_check__Request__disable_bluebox_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__disable_bluebox_t__defined) */

	OutP->RetCode = disable_bluebox(convert_port_to_host(In0P->Head.msgh_request_port));
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(212, "disable_bluebox")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__processor_set_default_t__defined)
#define __MIG_check__Request__processor_set_default_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_default_t(__Request__processor_set_default_t *In0P)
{

	typedef __Request__processor_set_default_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_default_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_default */
mig_internal novalue _Xprocessor_set_default
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
	typedef __Request__processor_set_default_t __Request;
	typedef __Reply__processor_set_default_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_default_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_default_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t default_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t default_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	processor_set_name_t default_set;

	__DeclareRcvRpc(213, "processor_set_default")
	__BeforeRcvRpc(213, "processor_set_default")

#if	defined(__MIG_check__Request__processor_set_default_t__defined)
	check_result = __MIG_check__Request__processor_set_default_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_default_t__defined) */

#if	UseStaticTemplates
	OutP->default_set = default_setTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->default_set.disposition = 17;
#else
	OutP->default_set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->default_set.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = processor_set_default(convert_port_to_host(In0P->Head.msgh_request_port), &default_set);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->default_set.name = (mach_port_t)convert_pset_name_to_port(default_set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(213, "processor_set_default")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__processor_set_create_t__defined)
#define __MIG_check__Request__processor_set_create_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_create_t(__Request__processor_set_create_t *In0P)
{

	typedef __Request__processor_set_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_create_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_create */
mig_internal novalue _Xprocessor_set_create
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
	typedef __Request__processor_set_create_t __Request;
	typedef __Reply__processor_set_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	processor_set_t new_set;
	processor_set_name_t new_name;

	__DeclareRcvRpc(214, "processor_set_create")
	__BeforeRcvRpc(214, "processor_set_create")

#if	defined(__MIG_check__Request__processor_set_create_t__defined)
	check_result = __MIG_check__Request__processor_set_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_create_t__defined) */

#if	UseStaticTemplates
	OutP->new_set = new_setTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->new_set.disposition = 17;
#else
	OutP->new_set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->new_set.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


#if	UseStaticTemplates
	OutP->new_name = new_nameTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->new_name.disposition = 17;
#else
	OutP->new_name.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->new_name.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = processor_set_create(convert_port_to_host(In0P->Head.msgh_request_port), &new_set, &new_name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->new_set.name = (mach_port_t)convert_pset_to_port(new_set);

	OutP->new_name.name = (mach_port_t)convert_pset_name_to_port(new_name);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 2;
	__AfterRcvRpc(214, "processor_set_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__mach_memory_object_memory_entry_64_t__defined)
#define __MIG_check__Request__mach_memory_object_memory_entry_64_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#if	defined(__NDR_convert__int_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__int_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */

#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__int_rep__mach_host__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__mach_host__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__mach_host__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__int_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#if	defined(__NDR_convert__char_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__char_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__char_rep__mach_host__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__mach_host__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__mach_host__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__char_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#if	defined(__NDR_convert__float_rep__mach_host__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__float_rep__mach_host__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__float_rep__mach_host__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__mach_host__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__mach_host__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__float_rep__mach_host__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */


mig_internal kern_return_t __MIG_check__Request__mach_memory_object_memory_entry_64_t(__Request__mach_memory_object_memory_entry_64_t *In0P)
{

	typedef __Request__mach_memory_object_memory_entry_64_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->pager.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->pager.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal(&In0P->internal, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
		__NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal(&In0P->internal, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
		__NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal(&In0P->internal, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__internal__defined */
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined)
		__NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_memory_object_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_memory_object_memory_entry_64_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_memory_object_memory_entry_64 */
mig_internal novalue _Xmach_memory_object_memory_entry_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t pager;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		boolean_t internal;
		memory_object_size_t size;
		vm_prot_t permission;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_memory_object_memory_entry_64_t __Request;
	typedef __Reply__mach_memory_object_memory_entry_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_memory_object_memory_entry_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_memory_object_memory_entry_64_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t entry_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t entry_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(215, "mach_memory_object_memory_entry_64")
	__BeforeRcvRpc(215, "mach_memory_object_memory_entry_64")

#if	defined(__MIG_check__Request__mach_memory_object_memory_entry_64_t__defined)
	check_result = __MIG_check__Request__mach_memory_object_memory_entry_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_memory_object_memory_entry_64_t__defined) */

#if	UseStaticTemplates
	OutP->entry_handle = entry_handleTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->entry_handle.disposition = 17;
#else
	OutP->entry_handle.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->entry_handle.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = mach_memory_object_memory_entry_64(convert_port_to_host(In0P->Head.msgh_request_port), In0P->internal, In0P->size, In0P->permission, convert_port_to_memory_object(In0P->pager.name), &OutP->entry_handle.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->pager.name))
		ipc_port_release_send((ipc_port_t)In0P->pager.name);
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(215, "mach_memory_object_memory_entry_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_statistics_t__defined)
#define __MIG_check__Request__host_statistics_t__defined
#ifndef __NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#if	defined(__NDR_convert__int_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_statistics_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__mach_host__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_host__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#if	defined(__NDR_convert__char_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_statistics_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#if	defined(__NDR_convert__float_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_statistics_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_statistics_t(__Request__host_statistics_t *In0P)
{

	typedef __Request__host_statistics_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_statistics_t__flavor__defined)
		__NDR_convert__int_rep__Request__host_statistics_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_statistics_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined)
		__NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt(&In0P->host_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_statistics_t__host_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_statistics_t__flavor__defined)
		__NDR_convert__char_rep__Request__host_statistics_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_statistics_t__flavor__defined)
		__NDR_convert__float_rep__Request__host_statistics_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_statistics_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_statistics */
mig_internal novalue _Xhost_statistics
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		host_flavor_t flavor;
		mach_msg_type_number_t host_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_statistics_t __Request;
	typedef __Reply__host_statistics_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_statistics_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_statistics_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(216, "host_statistics")
	__BeforeRcvRpc(216, "host_statistics")

#if	defined(__MIG_check__Request__host_statistics_t__defined)
	check_result = __MIG_check__Request__host_statistics_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_statistics_t__defined) */

	OutP->host_info_outCnt = 14;
	if (In0P->host_info_outCnt < OutP->host_info_outCnt)
		OutP->host_info_outCnt = In0P->host_info_outCnt;

	OutP->RetCode = host_statistics(convert_port_to_host(In0P->Head.msgh_request_port), In0P->flavor, OutP->host_info_out, &OutP->host_info_outCnt);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 56) + (((4 * OutP->host_info_outCnt)));

	__AfterRcvRpc(216, "host_statistics")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_request_notification_t__defined)
#define __MIG_check__Request__host_request_notification_t__defined
#ifndef __NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#if	defined(__NDR_convert__int_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_host__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined */

#ifndef __NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#if	defined(__NDR_convert__char_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_host__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined */

#ifndef __NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#if	defined(__NDR_convert__float_rep__mach_host__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__mach_host__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__mach_host__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_host__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__mach_host__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined
#define	__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined */


mig_internal kern_return_t __MIG_check__Request__host_request_notification_t(__Request__host_request_notification_t *In0P)
{

	typedef __Request__host_request_notification_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->notify_port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->notify_port.disposition != 18)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined)
		__NDR_convert__int_rep__Request__host_request_notification_t__notify_type(&In0P->notify_type, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_request_notification_t__notify_type__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined)
		__NDR_convert__char_rep__Request__host_request_notification_t__notify_type(&In0P->notify_type, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_request_notification_t__notify_type__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined)
		__NDR_convert__float_rep__Request__host_request_notification_t__notify_type(&In0P->notify_type, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_request_notification_t__notify_type__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_request_notification_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_request_notification */
mig_internal novalue _Xhost_request_notification
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t notify_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		host_flavor_t notify_type;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_request_notification_t __Request;
	typedef __Reply__host_request_notification_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_request_notification_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_request_notification_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(217, "host_request_notification")
	__BeforeRcvRpc(217, "host_request_notification")

#if	defined(__MIG_check__Request__host_request_notification_t__defined)
	check_result = __MIG_check__Request__host_request_notification_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_request_notification_t__defined) */

	OutP->RetCode = host_request_notification(convert_port_to_host(In0P->Head.msgh_request_port), In0P->notify_type, In0P->notify_port.name);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(217, "host_request_notification")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_host_subsystem__
#if !defined(__MIG_check__Request__host_lockgroup_info_t__defined)
#define __MIG_check__Request__host_lockgroup_info_t__defined

mig_internal kern_return_t __MIG_check__Request__host_lockgroup_info_t(__Request__host_lockgroup_info_t *In0P)
{

	typedef __Request__host_lockgroup_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_lockgroup_info_t__defined) */
#endif /* __MIG_check__Request__mach_host_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_lockgroup_info */
mig_internal novalue _Xhost_lockgroup_info
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
	typedef __Request__host_lockgroup_info_t __Request;
	typedef __Reply__host_lockgroup_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_lockgroup_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_lockgroup_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t lockgroup_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t lockgroup_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(218, "host_lockgroup_info")
	__BeforeRcvRpc(218, "host_lockgroup_info")

#if	defined(__MIG_check__Request__host_lockgroup_info_t__defined)
	check_result = __MIG_check__Request__host_lockgroup_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_lockgroup_info_t__defined) */

#if	UseStaticTemplates
	OutP->lockgroup_info = lockgroup_infoTemplate;
#else	/* UseStaticTemplates */
	OutP->lockgroup_info.deallocate =  TRUE;
	OutP->lockgroup_info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->lockgroup_info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	OutP->lockgroup_infoCnt = 0;

	RetCode = host_lockgroup_info(convert_port_to_host(In0P->Head.msgh_request_port), (lockgroup_info_array_t *)&(OutP->lockgroup_info.address), &OutP->lockgroup_infoCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->lockgroup_info.size = OutP->lockgroup_infoCnt * 252;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(218, "host_lockgroup_info")
}



/* Description of this subsystem, for use in direct RPC */
const struct mach_host_subsystem mach_host_subsystem = {
	mach_host_server_routine,
	200,
	219,
	(mach_msg_size_t)sizeof(union __ReplyUnion__mach_host_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_info, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_kernel_version, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_kernel_version_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_page_size, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_page_size_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_memory_object_memory_entry, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_memory_object_memory_entry_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_processor_info, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_processor_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_io_master, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_io_master_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_clock_service, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_clock_service_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xkmod_get_info, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__kmod_get_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_zone_info, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_zone_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_virtual_physical_table_info, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_virtual_physical_table_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_ipc_hash_info, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_ipc_hash_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xenable_bluebox, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__enable_bluebox_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xdisable_bluebox, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__disable_bluebox_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_default, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_default_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_create, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_memory_object_memory_entry_64, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_memory_object_memory_entry_64_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_statistics, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_statistics_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_request_notification, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_request_notification_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_lockgroup_info, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_lockgroup_info_t)},
	}
};

mig_external boolean_t mach_host_server
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

	if ((InHeadP->msgh_id > 218) || (InHeadP->msgh_id < 200) ||
	    ((routine = mach_host_subsystem.routine[InHeadP->msgh_id - 200].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t mach_host_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 200;

	if ((msgh_id > 18) || (msgh_id < 0))
		return 0;

	return mach_host_subsystem.routine[msgh_id].stub_routine;
}

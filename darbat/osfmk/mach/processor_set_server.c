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
 * stub generated Tue Mar  7 16:25:32 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module processor_set */

#define	__MIG_check__Request__processor_set_subsystem__ 1
#define	__NDR_convert__Request__processor_set_subsystem__ 1

#include "processor_set_server.h"

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


mig_internal novalue _Xprocessor_set_statistics
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_max_priority
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_policy_enable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_policy_disable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_tasks
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_threads
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_policy_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_stack_usage
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_set_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_statistics_t__defined)
#define __MIG_check__Request__processor_set_statistics_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#if	defined(__NDR_convert__int_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined
#if	defined(__NDR_convert__int_rep__processor_set__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt(a, f) \
	__NDR_convert__int_rep__processor_set__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#if	defined(__NDR_convert__char_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#if	defined(__NDR_convert__float_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_statistics_t(__Request__processor_set_statistics_t *In0P)
{

	typedef __Request__processor_set_statistics_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined)
		__NDR_convert__int_rep__Request__processor_set_statistics_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_statistics_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined)
		__NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt(&In0P->info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_statistics_t__info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined)
		__NDR_convert__char_rep__Request__processor_set_statistics_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined)
		__NDR_convert__float_rep__Request__processor_set_statistics_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_statistics_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_statistics */
mig_internal novalue _Xprocessor_set_statistics
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_set_flavor_t flavor;
		mach_msg_type_number_t info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_statistics_t __Request;
	typedef __Reply__processor_set_statistics_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_statistics_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_statistics_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_name_t pset;

	__DeclareRcvRpc(4000, "processor_set_statistics")
	__BeforeRcvRpc(4000, "processor_set_statistics")

#if	defined(__MIG_check__Request__processor_set_statistics_t__defined)
	check_result = __MIG_check__Request__processor_set_statistics_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_statistics_t__defined) */

	pset = convert_port_to_pset_name(In0P->Head.msgh_request_port);

	OutP->info_outCnt = 5;
	if (In0P->info_outCnt < OutP->info_outCnt)
		OutP->info_outCnt = In0P->info_outCnt;

	OutP->RetCode = processor_set_statistics(pset, In0P->flavor, OutP->info_out, &OutP->info_outCnt);
	pset_deallocate(pset);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 20) + (((4 * OutP->info_outCnt)));

	__AfterRcvRpc(4000, "processor_set_statistics")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_destroy_t__defined)
#define __MIG_check__Request__processor_set_destroy_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_destroy_t(__Request__processor_set_destroy_t *In0P)
{

	typedef __Request__processor_set_destroy_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_destroy_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_destroy */
mig_internal novalue _Xprocessor_set_destroy
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
	typedef __Request__processor_set_destroy_t __Request;
	typedef __Reply__processor_set_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t set;

	__DeclareRcvRpc(4001, "processor_set_destroy")
	__BeforeRcvRpc(4001, "processor_set_destroy")

#if	defined(__MIG_check__Request__processor_set_destroy_t__defined)
	check_result = __MIG_check__Request__processor_set_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_destroy_t__defined) */

	set = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_destroy(set);
	pset_deallocate(set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(4001, "processor_set_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_max_priority_t__defined)
#define __MIG_check__Request__processor_set_max_priority_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined
#if	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined
#if	defined(__NDR_convert__int_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__int_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined
#if	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined
#if	defined(__NDR_convert__char_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__char_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined
#if	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined
#if	defined(__NDR_convert__float_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__float_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined
#define	__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_max_priority_t(__Request__processor_set_max_priority_t *In0P)
{

	typedef __Request__processor_set_max_priority_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined)
		__NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority(&In0P->max_priority, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_max_priority_t__max_priority__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined)
		__NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads(&In0P->change_threads, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_max_priority_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined) || \
	defined(__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined)
		__NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority(&In0P->max_priority, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_max_priority_t__max_priority__defined */
#if defined(__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined)
		__NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads(&In0P->change_threads, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_max_priority_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined) || \
	defined(__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined)
		__NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority(&In0P->max_priority, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_max_priority_t__max_priority__defined */
#if defined(__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined)
		__NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads(&In0P->change_threads, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_max_priority_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_max_priority_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_max_priority */
mig_internal novalue _Xprocessor_set_max_priority
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int max_priority;
		boolean_t change_threads;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_max_priority_t __Request;
	typedef __Reply__processor_set_max_priority_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_max_priority_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_max_priority_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t processor_set;

	__DeclareRcvRpc(4002, "processor_set_max_priority")
	__BeforeRcvRpc(4002, "processor_set_max_priority")

#if	defined(__MIG_check__Request__processor_set_max_priority_t__defined)
	check_result = __MIG_check__Request__processor_set_max_priority_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_max_priority_t__defined) */

	processor_set = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_max_priority(processor_set, In0P->max_priority, In0P->change_threads);
	pset_deallocate(processor_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(4002, "processor_set_max_priority")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_policy_enable_t__defined)
#define __MIG_check__Request__processor_set_policy_enable_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined
#if	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined
#if	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined
#if	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_policy_enable_t(__Request__processor_set_policy_enable_t *In0P)
{

	typedef __Request__processor_set_policy_enable_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_enable_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_enable_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_enable_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_policy_enable_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_policy_enable */
mig_internal novalue _Xprocessor_set_policy_enable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int policy;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_policy_enable_t __Request;
	typedef __Reply__processor_set_policy_enable_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_policy_enable_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_policy_enable_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t processor_set;

	__DeclareRcvRpc(4003, "processor_set_policy_enable")
	__BeforeRcvRpc(4003, "processor_set_policy_enable")

#if	defined(__MIG_check__Request__processor_set_policy_enable_t__defined)
	check_result = __MIG_check__Request__processor_set_policy_enable_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_policy_enable_t__defined) */

	processor_set = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_policy_enable(processor_set, In0P->policy);
	pset_deallocate(processor_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(4003, "processor_set_policy_enable")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_policy_disable_t__defined)
#define __MIG_check__Request__processor_set_policy_disable_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined
#if	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined
#if	defined(__NDR_convert__int_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__int_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined
#if	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined
#if	defined(__NDR_convert__char_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__char_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined
#if	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined
#if	defined(__NDR_convert__float_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__float_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_policy_disable_t(__Request__processor_set_policy_disable_t *In0P)
{

	typedef __Request__processor_set_policy_disable_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_disable_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads(&In0P->change_threads, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_disable_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_disable_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads(&In0P->change_threads, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_disable_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_disable_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads(&In0P->change_threads, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_disable_t__change_threads__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_policy_disable_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_policy_disable */
mig_internal novalue _Xprocessor_set_policy_disable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int policy;
		boolean_t change_threads;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_policy_disable_t __Request;
	typedef __Reply__processor_set_policy_disable_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_policy_disable_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_policy_disable_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t processor_set;

	__DeclareRcvRpc(4004, "processor_set_policy_disable")
	__BeforeRcvRpc(4004, "processor_set_policy_disable")

#if	defined(__MIG_check__Request__processor_set_policy_disable_t__defined)
	check_result = __MIG_check__Request__processor_set_policy_disable_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_policy_disable_t__defined) */

	processor_set = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_policy_disable(processor_set, In0P->policy, In0P->change_threads);
	pset_deallocate(processor_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(4004, "processor_set_policy_disable")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_tasks_t__defined)
#define __MIG_check__Request__processor_set_tasks_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_tasks_t(__Request__processor_set_tasks_t *In0P)
{

	typedef __Request__processor_set_tasks_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_tasks_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_tasks */
mig_internal novalue _Xprocessor_set_tasks
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
	typedef __Request__processor_set_tasks_t __Request;
	typedef __Reply__processor_set_tasks_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_tasks_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_tasks_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t task_listTemplate = {
		/* addr = */		(void *)0,
		/* coun = */		0,
		/* deal = */		FALSE,
		/* copy is meaningful only in overwrite mode */
		/* copy = */		MACH_MSG_PHYSICAL_COPY,
		/* disp = */		17,
		/* type = */		MACH_MSG_OOL_PORTS_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t task_listTemplate = {
		/* addr = */		(void *)0,
		/* coun = */		0,
		/* deal = */		FALSE,
		/* copy is meaningful only in overwrite mode */
		/* copy = */		MACH_MSG_PHYSICAL_COPY,
		/* disp = */		19,
		/* type = */		MACH_MSG_OOL_PORTS_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	processor_set_t processor_set;

	__DeclareRcvRpc(4005, "processor_set_tasks")
	__BeforeRcvRpc(4005, "processor_set_tasks")

#if	defined(__MIG_check__Request__processor_set_tasks_t__defined)
	check_result = __MIG_check__Request__processor_set_tasks_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_tasks_t__defined) */

#if	UseStaticTemplates
	OutP->task_list = task_listTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->task_list.disposition = 17;
#else
	OutP->task_list.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->task_list.deallocate =  FALSE;
	OutP->task_list.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	processor_set = convert_port_to_pset(In0P->Head.msgh_request_port);

	RetCode = processor_set_tasks(processor_set, (task_array_t *)&(OutP->task_list.address), &OutP->task_listCnt);
	pset_deallocate(processor_set);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->task_list.count = OutP->task_listCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(4005, "processor_set_tasks")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_threads_t__defined)
#define __MIG_check__Request__processor_set_threads_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_threads_t(__Request__processor_set_threads_t *In0P)
{

	typedef __Request__processor_set_threads_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_threads_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_threads */
mig_internal novalue _Xprocessor_set_threads
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
	typedef __Request__processor_set_threads_t __Request;
	typedef __Reply__processor_set_threads_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_threads_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_threads_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t thread_listTemplate = {
		/* addr = */		(void *)0,
		/* coun = */		0,
		/* deal = */		FALSE,
		/* copy is meaningful only in overwrite mode */
		/* copy = */		MACH_MSG_PHYSICAL_COPY,
		/* disp = */		17,
		/* type = */		MACH_MSG_OOL_PORTS_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t thread_listTemplate = {
		/* addr = */		(void *)0,
		/* coun = */		0,
		/* deal = */		FALSE,
		/* copy is meaningful only in overwrite mode */
		/* copy = */		MACH_MSG_PHYSICAL_COPY,
		/* disp = */		19,
		/* type = */		MACH_MSG_OOL_PORTS_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	processor_set_t processor_set;

	__DeclareRcvRpc(4006, "processor_set_threads")
	__BeforeRcvRpc(4006, "processor_set_threads")

#if	defined(__MIG_check__Request__processor_set_threads_t__defined)
	check_result = __MIG_check__Request__processor_set_threads_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_threads_t__defined) */

#if	UseStaticTemplates
	OutP->thread_list = thread_listTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->thread_list.disposition = 17;
#else
	OutP->thread_list.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->thread_list.deallocate =  FALSE;
	OutP->thread_list.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	processor_set = convert_port_to_pset(In0P->Head.msgh_request_port);

	RetCode = processor_set_threads(processor_set, (thread_act_array_t *)&(OutP->thread_list.address), &OutP->thread_listCnt);
	pset_deallocate(processor_set);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->thread_list.count = OutP->thread_listCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(4006, "processor_set_threads")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_policy_control_t__defined)
#define __MIG_check__Request__processor_set_policy_control_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#if	defined(__NDR_convert__int_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#if	defined(__NDR_convert__int_rep__processor_set__processor_set_info_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__processor_set__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__processor_set_info_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__processor_set__integer_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__processor_set__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__processor_set__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined
#if	defined(__NDR_convert__int_rep__processor_set__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__processor_set__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined
#if	defined(__NDR_convert__int_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__int_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__int_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#if	defined(__NDR_convert__char_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#if	defined(__NDR_convert__char_rep__processor_set__processor_set_info_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__processor_set__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__processor_set_info_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__processor_set__integer_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__processor_set__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__processor_set__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined
#if	defined(__NDR_convert__char_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__char_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__char_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#if	defined(__NDR_convert__float_rep__processor_set__processor_set_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set_flavor_t((processor_set_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#if	defined(__NDR_convert__float_rep__processor_set__processor_set_info_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__processor_set__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__processor_set_info_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__processor_set_info_t((processor_set_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__processor_set__integer_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__processor_set__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__processor_set__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined
#if	defined(__NDR_convert__float_rep__processor_set__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__float_rep__processor_set__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined
#define	__NDR_convert__float_rep__Request__processor_set_policy_control_t__change(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_policy_control_t(__Request__processor_set_policy_control_t *In0P, __Request__processor_set_policy_control_t **In1PP)
{

	typedef __Request__processor_set_policy_control_t __Request;
	__Request *In1P;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */
	unsigned int msgh_size_delta;

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 20)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt(&In0P->policy_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined */
	msgh_size_delta = (4 * In0P->policy_infoCnt);
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 20) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 20);

#if	defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_infoCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_control_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info(&In0P->policy_info, In0P->NDR.int_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_control_t__policy_info__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined)
		__NDR_convert__int_rep__Request__processor_set_policy_control_t__change(&In1P->change, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_policy_control_t__change__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_control_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info(&In0P->policy_info, In0P->NDR.char_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_control_t__policy_info__defined */
#if defined(__NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined)
		__NDR_convert__char_rep__Request__processor_set_policy_control_t__change(&In1P->change, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_policy_control_t__change__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_control_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info(&In0P->policy_info, In0P->NDR.float_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_control_t__policy_info__defined */
#if defined(__NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined)
		__NDR_convert__float_rep__Request__processor_set_policy_control_t__change(&In1P->change, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_policy_control_t__change__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_policy_control_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_policy_control */
mig_internal novalue _Xprocessor_set_policy_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_set_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		integer_t policy_info[5];
		boolean_t change;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_policy_control_t __Request;
	typedef __Reply__processor_set_policy_control_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Request *In1P;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_policy_control_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_policy_control_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t pset;

	__DeclareRcvRpc(4007, "processor_set_policy_control")
	__BeforeRcvRpc(4007, "processor_set_policy_control")

#if	defined(__MIG_check__Request__processor_set_policy_control_t__defined)
	check_result = __MIG_check__Request__processor_set_policy_control_t((__Request *)In0P, (__Request **)&In1P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_policy_control_t__defined) */

	pset = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_policy_control(pset, In0P->flavor, In0P->policy_info, In0P->policy_infoCnt, In1P->change);
	pset_deallocate(pset);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(4007, "processor_set_policy_control")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_stack_usage_t__defined)
#define __MIG_check__Request__processor_set_stack_usage_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_set_stack_usage_t(__Request__processor_set_stack_usage_t *In0P)
{

	typedef __Request__processor_set_stack_usage_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_stack_usage_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_stack_usage */
mig_internal novalue _Xprocessor_set_stack_usage
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
	typedef __Request__processor_set_stack_usage_t __Request;
	typedef __Reply__processor_set_stack_usage_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_stack_usage_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_stack_usage_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t pset;

	__DeclareRcvRpc(4008, "processor_set_stack_usage")
	__BeforeRcvRpc(4008, "processor_set_stack_usage")

#if	defined(__MIG_check__Request__processor_set_stack_usage_t__defined)
	check_result = __MIG_check__Request__processor_set_stack_usage_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_stack_usage_t__defined) */

	pset = convert_port_to_pset(In0P->Head.msgh_request_port);

	OutP->RetCode = processor_set_stack_usage(pset, &OutP->total, &OutP->space, &OutP->resident, &OutP->maxusage, &OutP->maxstack);
	pset_deallocate(pset);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(4008, "processor_set_stack_usage")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_set_subsystem__
#if !defined(__MIG_check__Request__processor_set_info_t__defined)
#define __MIG_check__Request__processor_set_info_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__processor_set__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined
#if	defined(__NDR_convert__int_rep__processor_set__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt(a, f) \
	__NDR_convert__int_rep__processor_set__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__processor_set__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__processor_set__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__processor_set_info_t(__Request__processor_set_info_t *In0P)
{

	typedef __Request__processor_set_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__processor_set_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined)
		__NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt(&In0P->info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_set_info_t__info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__processor_set_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_set_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__processor_set_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_set_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_set_info_t__defined) */
#endif /* __MIG_check__Request__processor_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_set_info */
mig_internal novalue _Xprocessor_set_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flavor;
		mach_msg_type_number_t info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_set_info_t __Request;
	typedef __Reply__processor_set_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_set_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_set_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t hostTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t hostTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	processor_set_name_t set_name;
	host_t host;

	__DeclareRcvRpc(4009, "processor_set_info")
	__BeforeRcvRpc(4009, "processor_set_info")

#if	defined(__MIG_check__Request__processor_set_info_t__defined)
	check_result = __MIG_check__Request__processor_set_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_set_info_t__defined) */

#if	UseStaticTemplates
	OutP->host = hostTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->host.disposition = 17;
#else
	OutP->host.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->host.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	set_name = convert_port_to_pset_name(In0P->Head.msgh_request_port);

	OutP->info_outCnt = 5;
	if (In0P->info_outCnt < OutP->info_outCnt)
		OutP->info_outCnt = In0P->info_outCnt;

	RetCode = processor_set_info(set_name, In0P->flavor, &host, OutP->info_out, &OutP->info_outCnt);
	pset_deallocate(set_name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->host.name = (mach_port_t)convert_host_to_port(host);


	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 20) + (((4 * OutP->info_outCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(4009, "processor_set_info")
}



/* Description of this subsystem, for use in direct RPC */
const struct processor_set_subsystem processor_set_subsystem = {
	processor_set_server_routine,
	4000,
	4010,
	(mach_msg_size_t)sizeof(union __ReplyUnion__processor_set_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_statistics, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_statistics_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_destroy, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_max_priority, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_max_priority_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_policy_enable, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_policy_enable_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_policy_disable, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_policy_disable_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_tasks, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_tasks_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_threads, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_threads_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_policy_control, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_policy_control_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_stack_usage, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_stack_usage_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_set_info, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_set_info_t)},
	}
};

mig_external boolean_t processor_set_server
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

	if ((InHeadP->msgh_id > 4009) || (InHeadP->msgh_id < 4000) ||
	    ((routine = processor_set_subsystem.routine[InHeadP->msgh_id - 4000].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t processor_set_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 4000;

	if ((msgh_id > 9) || (msgh_id < 0))
		return 0;

	return processor_set_subsystem.routine[msgh_id].stub_routine;
}

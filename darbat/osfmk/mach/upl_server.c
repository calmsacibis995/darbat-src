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
 * stub generated Tue Mar  7 16:25:34 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module upl */

#define	__MIG_check__Request__upl_subsystem__ 1
#define	__NDR_convert__Request__upl_subsystem__ 1

#include "upl_server.h"

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


mig_internal novalue _Xupl_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_abort_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_commit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_commit_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_abort_t__defined)
#define __MIG_check__Request__upl_abort_t__defined
#ifndef __NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined
#if	defined(__NDR_convert__int_rep__upl__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__int_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__int_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined */

#ifndef __NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined
#if	defined(__NDR_convert__char_rep__upl__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__char_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__char_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined */

#ifndef __NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined
#if	defined(__NDR_convert__float_rep__upl__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__float_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__float_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_t__abort_cond(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined */


mig_internal kern_return_t __MIG_check__Request__upl_abort_t(__Request__upl_abort_t *In0P)
{

	typedef __Request__upl_abort_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined)
		__NDR_convert__int_rep__Request__upl_abort_t__abort_cond(&In0P->abort_cond, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_abort_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined)
		__NDR_convert__char_rep__Request__upl_abort_t__abort_cond(&In0P->abort_cond, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_abort_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined)
		__NDR_convert__float_rep__Request__upl_abort_t__abort_cond(&In0P->abort_cond, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_abort_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_abort_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine upl_abort */
mig_internal novalue _Xupl_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		integer_t abort_cond;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__upl_abort_t __Request;
	typedef __Reply__upl_abort_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_abort_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_abort_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2050, "upl_abort")
	__BeforeRcvRpc(2050, "upl_abort")

#if	defined(__MIG_check__Request__upl_abort_t__defined)
	check_result = __MIG_check__Request__upl_abort_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_abort_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_abort(upl_object, In0P->abort_cond);
	upl_deallocate(upl_object);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2050, "upl_abort")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_abort_range_t__defined)
#define __MIG_check__Request__upl_abort_range_t__defined
#ifndef __NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined
#if	defined(__NDR_convert__int_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl_offset_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__upl_abort_range_t__size__defined
#if	defined(__NDR_convert__int_rep__upl__upl_size_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__int_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl_size_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__int_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__int_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_abort_range_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined
#if	defined(__NDR_convert__int_rep__upl__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__int_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__int_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined */

#ifndef __NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined
#if	defined(__NDR_convert__char_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl_offset_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__upl_abort_range_t__size__defined
#if	defined(__NDR_convert__char_rep__upl__upl_size_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__char_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl_size_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__char_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__char_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_abort_range_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined
#if	defined(__NDR_convert__char_rep__upl__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__char_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__char_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined */

#ifndef __NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined
#if	defined(__NDR_convert__float_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl_offset_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__offset(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__upl_abort_range_t__size__defined
#if	defined(__NDR_convert__float_rep__upl__upl_size_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__float_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl_size_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__float_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__float_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_abort_range_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined
#if	defined(__NDR_convert__float_rep__upl__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__float_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__float_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined
#define	__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined */


mig_internal kern_return_t __MIG_check__Request__upl_abort_range_t(__Request__upl_abort_range_t *In0P)
{

	typedef __Request__upl_abort_range_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined)
		__NDR_convert__int_rep__Request__upl_abort_range_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_abort_range_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__upl_abort_range_t__size__defined)
		__NDR_convert__int_rep__Request__upl_abort_range_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_abort_range_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined)
		__NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond(&In0P->abort_cond, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_abort_range_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined)
		__NDR_convert__char_rep__Request__upl_abort_range_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_abort_range_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__upl_abort_range_t__size__defined)
		__NDR_convert__char_rep__Request__upl_abort_range_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_abort_range_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined)
		__NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond(&In0P->abort_cond, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_abort_range_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined)
		__NDR_convert__float_rep__Request__upl_abort_range_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_abort_range_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__upl_abort_range_t__size__defined)
		__NDR_convert__float_rep__Request__upl_abort_range_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_abort_range_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined)
		__NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond(&In0P->abort_cond, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_abort_range_t__abort_cond__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_abort_range_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine upl_abort_range */
mig_internal novalue _Xupl_abort_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		upl_offset_t offset;
		upl_size_t size;
		integer_t abort_cond;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__upl_abort_range_t __Request;
	typedef __Reply__upl_abort_range_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_abort_range_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_abort_range_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2051, "upl_abort_range")
	__BeforeRcvRpc(2051, "upl_abort_range")

#if	defined(__MIG_check__Request__upl_abort_range_t__defined)
	check_result = __MIG_check__Request__upl_abort_range_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_abort_range_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_abort_range(upl_object, In0P->offset, In0P->size, In0P->abort_cond, &OutP->empty);
	upl_deallocate(upl_object);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2051, "upl_abort_range")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_commit_t__defined)
#define __MIG_check__Request__upl_commit_t__defined
#ifndef __NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#if	defined(__NDR_convert__int_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__int_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__int_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__int_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__int_rep__upl_page_info_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__int_rep__upl_page_info_t)
#elif	defined(__NDR_convert__int_rep__upl__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__int_rep__upl__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__upl__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__int_rep__upl__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_t__page_list__defined */

#ifndef __NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined
#if	defined(__NDR_convert__int_rep__upl__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__upl__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined */

#ifndef __NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#if	defined(__NDR_convert__char_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__char_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__char_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__char_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__char_rep__upl_page_info_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__char_rep__upl_page_info_t)
#elif	defined(__NDR_convert__char_rep__upl__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__char_rep__upl__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__upl__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__char_rep__upl__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_commit_t__page_list__defined */

#ifndef __NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#if	defined(__NDR_convert__float_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__float_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__float_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__float_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__float_rep__upl_page_info_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__float_rep__upl_page_info_t)
#elif	defined(__NDR_convert__float_rep__upl__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__float_rep__upl__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__upl__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__float_rep__upl__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_commit_t__page_list__defined */


mig_internal kern_return_t __MIG_check__Request__upl_commit_t(__Request__upl_commit_t *In0P)
{

	typedef __Request__upl_commit_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 2048)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 2048) + ((8 * In0P->page_listCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__upl_commit_t__page_list__defined)
		__NDR_convert__int_rep__Request__upl_commit_t__page_list(&In0P->page_list, In0P->NDR.int_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__upl_commit_t__page_list__defined)
		__NDR_convert__char_rep__Request__upl_commit_t__page_list(&In0P->page_list, In0P->NDR.char_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__char_rep__Request__upl_commit_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__upl_commit_t__page_list__defined)
		__NDR_convert__float_rep__Request__upl_commit_t__page_list(&In0P->page_list, In0P->NDR.float_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__float_rep__Request__upl_commit_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_commit_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine upl_commit */
mig_internal novalue _Xupl_commit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__upl_commit_t __Request;
	typedef __Reply__upl_commit_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_commit_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_commit_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2052, "upl_commit")
	__BeforeRcvRpc(2052, "upl_commit")

#if	defined(__MIG_check__Request__upl_commit_t__defined)
	check_result = __MIG_check__Request__upl_commit_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_commit_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_commit(upl_object, In0P->page_list, In0P->page_listCnt);
	upl_deallocate(upl_object);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2052, "upl_commit")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_commit_range_t__defined)
#define __MIG_check__Request__upl_commit_range_t__defined
#ifndef __NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined
#if	defined(__NDR_convert__int_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl_offset_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__int_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__upl_commit_range_t__size__defined
#if	defined(__NDR_convert__int_rep__upl__upl_size_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__int_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl_size_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__int_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__int_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_range_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined
#if	defined(__NDR_convert__int_rep__upl__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__upl__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined */

#ifndef __NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#if	defined(__NDR_convert__int_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__int_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__int_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__int_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__int_rep__upl_page_info_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__int_rep__upl_page_info_t)
#elif	defined(__NDR_convert__int_rep__upl__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__int_rep__upl__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__upl__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__int_rep__upl__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined */

#ifndef __NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined
#if	defined(__NDR_convert__int_rep__upl__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__upl__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined */

#ifndef __NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined
#if	defined(__NDR_convert__char_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl_offset_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__char_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__upl_commit_range_t__size__defined
#if	defined(__NDR_convert__char_rep__upl__upl_size_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__char_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl_size_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__char_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__char_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_commit_range_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined
#if	defined(__NDR_convert__char_rep__upl__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__upl__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined */

#ifndef __NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#if	defined(__NDR_convert__char_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__char_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__char_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__char_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__char_rep__upl_page_info_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__char_rep__upl_page_info_t)
#elif	defined(__NDR_convert__char_rep__upl__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__char_rep__upl__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__upl__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__char_rep__upl__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined */

#ifndef __NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined
#if	defined(__NDR_convert__float_rep__upl__upl_offset_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl_offset_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl_offset_t((upl_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__float_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__offset(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__upl_commit_range_t__size__defined
#if	defined(__NDR_convert__float_rep__upl__upl_size_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__float_rep__upl__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl_size_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__float_rep__upl_size_t((upl_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__float_rep__upl__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_commit_range_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined
#if	defined(__NDR_convert__float_rep__upl__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__upl__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__upl__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__upl__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined */

#ifndef __NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#if	defined(__NDR_convert__float_rep__upl__upl_page_info_array_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__float_rep__upl__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__upl_page_info_array_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__float_rep__upl_page_info_array_t((upl_page_info_array_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__upl__upl_page_info_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__float_rep__upl__upl_page_info_t)
#elif	defined(__NDR_convert__float_rep__upl_page_info_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((upl_page_info_t *)(a), f, c, __NDR_convert__float_rep__upl_page_info_t)
#elif	defined(__NDR_convert__float_rep__upl__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__float_rep__upl__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2 * (c), __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__upl__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__float_rep__upl__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined
#define	__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2 * (c), __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined */


mig_internal kern_return_t __MIG_check__Request__upl_commit_range_t(__Request__upl_commit_range_t *In0P)
{

	typedef __Request__upl_commit_range_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 2048)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 2048) + ((8 * In0P->page_listCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined) || \
	defined(__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined)
		__NDR_convert__int_rep__Request__upl_commit_range_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__size__defined)
		__NDR_convert__int_rep__Request__upl_commit_range_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined)
		__NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__cntrl_flags__defined */
#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined)
		__NDR_convert__int_rep__Request__upl_commit_range_t__page_list(&In0P->page_list, In0P->NDR.int_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined) || \
	defined(__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined)
		__NDR_convert__char_rep__Request__upl_commit_range_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_commit_range_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__upl_commit_range_t__size__defined)
		__NDR_convert__char_rep__Request__upl_commit_range_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_commit_range_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined)
		__NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__upl_commit_range_t__cntrl_flags__defined */
#if defined(__NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined)
		__NDR_convert__char_rep__Request__upl_commit_range_t__page_list(&In0P->page_list, In0P->NDR.char_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__char_rep__Request__upl_commit_range_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined) || \
	defined(__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined)
		__NDR_convert__float_rep__Request__upl_commit_range_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_commit_range_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__upl_commit_range_t__size__defined)
		__NDR_convert__float_rep__Request__upl_commit_range_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_commit_range_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined)
		__NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__upl_commit_range_t__cntrl_flags__defined */
#if defined(__NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined)
		__NDR_convert__float_rep__Request__upl_commit_range_t__page_list(&In0P->page_list, In0P->NDR.float_rep, In0P->page_listCnt);
#endif	/* __NDR_convert__float_rep__Request__upl_commit_range_t__page_list__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_commit_range_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine upl_commit_range */
mig_internal novalue _Xupl_commit_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		upl_offset_t offset;
		upl_size_t size;
		integer_t cntrl_flags;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__upl_commit_range_t __Request;
	typedef __Reply__upl_commit_range_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_commit_range_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_commit_range_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2053, "upl_commit_range")
	__BeforeRcvRpc(2053, "upl_commit_range")

#if	defined(__MIG_check__Request__upl_commit_range_t__defined)
	check_result = __MIG_check__Request__upl_commit_range_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_commit_range_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_commit_range(upl_object, In0P->offset, In0P->size, In0P->cntrl_flags, In0P->page_list, In0P->page_listCnt, &OutP->empty);
	upl_deallocate(upl_object);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2053, "upl_commit_range")
}



/* Description of this subsystem, for use in direct RPC */
const struct upl_subsystem upl_subsystem = {
	upl_server_routine,
	2050,
	2054,
	(mach_msg_size_t)sizeof(union __ReplyUnion__upl_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xupl_abort, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_abort_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xupl_abort_range, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_abort_range_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xupl_commit, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_commit_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xupl_commit_range, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_commit_range_t)},
	}
};

mig_external boolean_t upl_server
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

	if ((InHeadP->msgh_id > 2053) || (InHeadP->msgh_id < 2050) ||
	    ((routine = upl_subsystem.routine[InHeadP->msgh_id - 2050].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t upl_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 2050;

	if ((msgh_id > 3) || (msgh_id < 0))
		return 0;

	return upl_subsystem.routine[msgh_id].stub_routine;
}

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
 * stub generated Tue Mar  7 16:25:28 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module lock_set */

#define	__MIG_check__Request__lock_set_subsystem__ 1
#define	__NDR_convert__Request__lock_set_subsystem__ 1

#include "lock_set_server.h"

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


mig_internal novalue _Xlock_acquire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_release
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_try
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_make_stable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_handoff
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_handoff_accept
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_acquire_t__defined)
#define __MIG_check__Request__lock_acquire_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_acquire_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_acquire_t(__Request__lock_acquire_t *In0P)
{

	typedef __Request__lock_acquire_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_acquire_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_acquire_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_acquire_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_acquire_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_acquire_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_acquire_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_acquire_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_acquire */
mig_internal novalue _Xlock_acquire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_acquire_t __Request;
	typedef __Reply__lock_acquire_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_acquire_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_acquire_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617000, "lock_acquire")
	__BeforeRcvRpc(617000, "lock_acquire")

#if	defined(__MIG_check__Request__lock_acquire_t__defined)
	check_result = __MIG_check__Request__lock_acquire_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_acquire_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_acquire(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617000, "lock_acquire")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_release_t__defined)
#define __MIG_check__Request__lock_release_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_release_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_release_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_release_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_release_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_release_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_release_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_release_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_release_t(__Request__lock_release_t *In0P)
{

	typedef __Request__lock_release_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_release_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_release_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_release_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_release_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_release_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_release_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_release_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_release_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_release_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_release_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_release */
mig_internal novalue _Xlock_release
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_release_t __Request;
	typedef __Reply__lock_release_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_release_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_release_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617001, "lock_release")
	__BeforeRcvRpc(617001, "lock_release")

#if	defined(__MIG_check__Request__lock_release_t__defined)
	check_result = __MIG_check__Request__lock_release_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_release_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_release(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617001, "lock_release")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_try_t__defined)
#define __MIG_check__Request__lock_try_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_try_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_try_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_try_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_try_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_try_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_try_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_try_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_try_t(__Request__lock_try_t *In0P)
{

	typedef __Request__lock_try_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_try_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_try_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_try_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_try_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_try_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_try_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_try_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_try_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_try_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_try_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_try */
mig_internal novalue _Xlock_try
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_try_t __Request;
	typedef __Reply__lock_try_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_try_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_try_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617002, "lock_try")
	__BeforeRcvRpc(617002, "lock_try")

#if	defined(__MIG_check__Request__lock_try_t__defined)
	check_result = __MIG_check__Request__lock_try_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_try_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_try(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617002, "lock_try")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_make_stable_t__defined)
#define __MIG_check__Request__lock_make_stable_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_make_stable_t(__Request__lock_make_stable_t *In0P)
{

	typedef __Request__lock_make_stable_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_make_stable_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_make_stable_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_make_stable_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_make_stable_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_make_stable_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_make_stable_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_make_stable_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_make_stable */
mig_internal novalue _Xlock_make_stable
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_make_stable_t __Request;
	typedef __Reply__lock_make_stable_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_make_stable_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_make_stable_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617003, "lock_make_stable")
	__BeforeRcvRpc(617003, "lock_make_stable")

#if	defined(__MIG_check__Request__lock_make_stable_t__defined)
	check_result = __MIG_check__Request__lock_make_stable_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_make_stable_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_make_stable(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617003, "lock_make_stable")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_handoff_t__defined)
#define __MIG_check__Request__lock_handoff_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_handoff_t(__Request__lock_handoff_t *In0P)
{

	typedef __Request__lock_handoff_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_handoff_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_handoff_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_handoff_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_handoff_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_handoff_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_handoff_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_handoff_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_handoff */
mig_internal novalue _Xlock_handoff
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_handoff_t __Request;
	typedef __Reply__lock_handoff_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_handoff_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_handoff_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617004, "lock_handoff")
	__BeforeRcvRpc(617004, "lock_handoff")

#if	defined(__MIG_check__Request__lock_handoff_t__defined)
	check_result = __MIG_check__Request__lock_handoff_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_handoff_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_handoff(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617004, "lock_handoff")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__lock_set_subsystem__
#if !defined(__MIG_check__Request__lock_handoff_accept_t__defined)
#define __MIG_check__Request__lock_handoff_accept_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined
#if	defined(__NDR_convert__int_rep__lock_set__int__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__lock_set__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__int_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined */

#ifndef __NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined
#if	defined(__NDR_convert__char_rep__lock_set__int__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__lock_set__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__char_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined */

#ifndef __NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined
#if	defined(__NDR_convert__float_rep__lock_set__int__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__lock_set__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__float_rep__lock_set__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined
#define	__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined */


mig_internal kern_return_t __MIG_check__Request__lock_handoff_accept_t(__Request__lock_handoff_accept_t *In0P)
{

	typedef __Request__lock_handoff_accept_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined)
		__NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id(&In0P->lock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_handoff_accept_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined)
		__NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id(&In0P->lock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_handoff_accept_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined)
		__NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id(&In0P->lock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_handoff_accept_t__lock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_handoff_accept_t__defined) */
#endif /* __MIG_check__Request__lock_set_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_handoff_accept */
mig_internal novalue _Xlock_handoff_accept
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int lock_id;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_handoff_accept_t __Request;
	typedef __Reply__lock_handoff_accept_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_handoff_accept_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_handoff_accept_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	lock_set_t lock_set;

	__DeclareRcvRpc(617005, "lock_handoff_accept")
	__BeforeRcvRpc(617005, "lock_handoff_accept")

#if	defined(__MIG_check__Request__lock_handoff_accept_t__defined)
	check_result = __MIG_check__Request__lock_handoff_accept_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_handoff_accept_t__defined) */

	lock_set = convert_port_to_lock_set(In0P->Head.msgh_request_port);

	OutP->RetCode = lock_handoff_accept(lock_set, In0P->lock_id);
	lock_set_dereference(lock_set);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617005, "lock_handoff_accept")
}



/* Description of this subsystem, for use in direct RPC */
const struct lock_set_subsystem lock_set_subsystem = {
	lock_set_server_routine,
	617000,
	617006,
	(mach_msg_size_t)sizeof(union __ReplyUnion__lock_set_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_acquire, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_acquire_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_release, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_release_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_try, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_try_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_make_stable, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_make_stable_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_handoff, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_handoff_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_handoff_accept, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_handoff_accept_t)},
	}
};

mig_external boolean_t lock_set_server
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

	if ((InHeadP->msgh_id > 617005) || (InHeadP->msgh_id < 617000) ||
	    ((routine = lock_set_subsystem.routine[InHeadP->msgh_id - 617000].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t lock_set_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 617000;

	if ((msgh_id > 5) || (msgh_id < 0))
		return 0;

	return lock_set_subsystem.routine[msgh_id].stub_routine;
}

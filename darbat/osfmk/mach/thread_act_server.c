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
 * stub generated Tue Mar  7 16:25:33 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module thread_act */

#define	__MIG_check__Request__thread_act_subsystem__ 1
#define	__NDR_convert__Request__thread_act_subsystem__ 1

#include "thread_act_server.h"

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


mig_internal novalue _Xthread_terminate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xact_get_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xact_set_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_get_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_set_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_suspend
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_resume
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_abort_safely
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_depress_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_get_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_set_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_set_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_get_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_swap_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_policy_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_policy_get
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_sample
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_assign
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_assign_default
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_get_assignment
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_set_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_terminate_t__defined)
#define __MIG_check__Request__thread_terminate_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_terminate_t(__Request__thread_terminate_t *In0P)
{

	typedef __Request__thread_terminate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_terminate_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_terminate */
mig_internal novalue _Xthread_terminate
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
	typedef __Request__thread_terminate_t __Request;
	typedef __Reply__thread_terminate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_terminate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_terminate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3600, "thread_terminate")
	__BeforeRcvRpc(3600, "thread_terminate")

#if	defined(__MIG_check__Request__thread_terminate_t__defined)
	check_result = __MIG_check__Request__thread_terminate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_terminate_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_terminate(target_act);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3600, "thread_terminate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__act_get_state_t__defined)
#define __MIG_check__Request__act_get_state_t__defined
#ifndef __NDR_convert__int_rep__Request__act_get_state_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__act_get_state_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined
#define	__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined */

#ifndef __NDR_convert__char_rep__Request__act_get_state_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__act_get_state_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__act_get_state_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__act_get_state_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__act_get_state_t(__Request__act_get_state_t *In0P)
{

	typedef __Request__act_get_state_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__act_get_state_t__flavor__defined)
		__NDR_convert__int_rep__Request__act_get_state_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__act_get_state_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined)
		__NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt(&In0P->old_stateCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__act_get_state_t__old_stateCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__act_get_state_t__flavor__defined)
		__NDR_convert__char_rep__Request__act_get_state_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__act_get_state_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__act_get_state_t__flavor__defined)
		__NDR_convert__float_rep__Request__act_get_state_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__act_get_state_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__act_get_state_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine act_get_state */
mig_internal novalue _Xact_get_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flavor;
		mach_msg_type_number_t old_stateCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__act_get_state_t __Request;
	typedef __Reply__act_get_state_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__act_get_state_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__act_get_state_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3601, "act_get_state")
	__BeforeRcvRpc(3601, "act_get_state")

#if	defined(__MIG_check__Request__act_get_state_t__defined)
	check_result = __MIG_check__Request__act_get_state_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__act_get_state_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->old_stateCnt = 144;
	if (In0P->old_stateCnt < OutP->old_stateCnt)
		OutP->old_stateCnt = In0P->old_stateCnt;

	OutP->RetCode = act_get_state(target_act, In0P->flavor, OutP->old_state, &OutP->old_stateCnt);
	thread_deallocate(target_act);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 576) + (((4 * OutP->old_stateCnt)));

	__AfterRcvRpc(3601, "act_get_state")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__act_set_state_t__defined)
#define __MIG_check__Request__act_set_state_t__defined
#ifndef __NDR_convert__int_rep__Request__act_set_state_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__act_set_state_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__int_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__int_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__natural_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__natural_t)
#elif	defined(__NDR_convert__int_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__act_set_state_t__new_state__defined */

#ifndef __NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined */

#ifndef __NDR_convert__char_rep__Request__act_set_state_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__act_set_state_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__char_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__char_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__natural_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__natural_t)
#elif	defined(__NDR_convert__char_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__act_set_state_t__new_state__defined */

#ifndef __NDR_convert__float_rep__Request__act_set_state_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__act_set_state_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__float_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__float_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__natural_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__natural_t)
#elif	defined(__NDR_convert__float_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__act_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__act_set_state_t__new_state__defined */


mig_internal kern_return_t __MIG_check__Request__act_set_state_t(__Request__act_set_state_t *In0P)
{

	typedef __Request__act_set_state_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 576)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt(&In0P->new_stateCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 576) + ((4 * In0P->new_stateCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined) || \
	defined(__NDR_convert__int_rep__Request__act_set_state_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__act_set_state_t__flavor__defined)
		__NDR_convert__int_rep__Request__act_set_state_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__act_set_state_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__act_set_state_t__new_state__defined)
		__NDR_convert__int_rep__Request__act_set_state_t__new_state(&In0P->new_state, In0P->NDR.int_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__int_rep__Request__act_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__act_set_state_t__flavor__defined)
		__NDR_convert__char_rep__Request__act_set_state_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__act_set_state_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__act_set_state_t__new_state__defined)
		__NDR_convert__char_rep__Request__act_set_state_t__new_state(&In0P->new_state, In0P->NDR.char_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__char_rep__Request__act_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__act_set_state_t__flavor__defined)
		__NDR_convert__float_rep__Request__act_set_state_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__act_set_state_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__act_set_state_t__new_state__defined)
		__NDR_convert__float_rep__Request__act_set_state_t__new_state(&In0P->new_state, In0P->NDR.float_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__float_rep__Request__act_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__act_set_state_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine act_set_state */
mig_internal novalue _Xact_set_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flavor;
		mach_msg_type_number_t new_stateCnt;
		natural_t new_state[144];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__act_set_state_t __Request;
	typedef __Reply__act_set_state_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__act_set_state_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__act_set_state_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3602, "act_set_state")
	__BeforeRcvRpc(3602, "act_set_state")

#if	defined(__MIG_check__Request__act_set_state_t__defined)
	check_result = __MIG_check__Request__act_set_state_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__act_set_state_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = act_set_state(target_act, In0P->flavor, In0P->new_state, In0P->new_stateCnt);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3602, "act_set_state")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_get_state_t__defined)
#define __MIG_check__Request__thread_get_state_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_get_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__thread_get_state_t(__Request__thread_get_state_t *In0P)
{

	typedef __Request__thread_get_state_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_get_state_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_get_state_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined)
		__NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt(&In0P->old_stateCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_get_state_t__old_stateCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_get_state_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_get_state_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_get_state_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_get_state_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_get_state_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_get_state */
mig_internal novalue _Xthread_get_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		thread_state_flavor_t flavor;
		mach_msg_type_number_t old_stateCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_get_state_t __Request;
	typedef __Reply__thread_get_state_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_get_state_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_get_state_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3603, "thread_get_state")
	__BeforeRcvRpc(3603, "thread_get_state")

#if	defined(__MIG_check__Request__thread_get_state_t__defined)
	check_result = __MIG_check__Request__thread_get_state_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_get_state_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->old_stateCnt = 144;
	if (In0P->old_stateCnt < OutP->old_stateCnt)
		OutP->old_stateCnt = In0P->old_stateCnt;

	OutP->RetCode = thread_get_state(target_act, In0P->flavor, OutP->old_state, &OutP->old_stateCnt);
	thread_deallocate(target_act);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 576) + (((4 * OutP->old_stateCnt)));

	__AfterRcvRpc(3603, "thread_get_state")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_set_state_t__defined)
#define __MIG_check__Request__thread_set_state_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__int_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__int_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__natural_t)
#elif	defined(__NDR_convert__int_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__char_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__char_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__natural_t)
#elif	defined(__NDR_convert__char_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__float_rep__thread_act__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__float_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__thread_act__natural_t)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__natural_t)
#elif	defined(__NDR_convert__float_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__uint32_t)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_set_state_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined */


mig_internal kern_return_t __MIG_check__Request__thread_set_state_t(__Request__thread_set_state_t *In0P)
{

	typedef __Request__thread_set_state_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 576)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt(&In0P->new_stateCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 576) + ((4 * In0P->new_stateCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_state_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_set_state_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_state_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined)
		__NDR_convert__int_rep__Request__thread_set_state_t__new_state(&In0P->new_state, In0P->NDR.int_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_set_state_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_state_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined)
		__NDR_convert__char_rep__Request__thread_set_state_t__new_state(&In0P->new_state, In0P->NDR.char_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_set_state_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_state_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined)
		__NDR_convert__float_rep__Request__thread_set_state_t__new_state(&In0P->new_state, In0P->NDR.float_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_set_state_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_set_state_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_set_state */
mig_internal novalue _Xthread_set_state
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		thread_state_flavor_t flavor;
		mach_msg_type_number_t new_stateCnt;
		natural_t new_state[144];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_set_state_t __Request;
	typedef __Reply__thread_set_state_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_set_state_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_set_state_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3604, "thread_set_state")
	__BeforeRcvRpc(3604, "thread_set_state")

#if	defined(__MIG_check__Request__thread_set_state_t__defined)
	check_result = __MIG_check__Request__thread_set_state_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_set_state_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_set_state(target_act, In0P->flavor, In0P->new_state, In0P->new_stateCnt);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3604, "thread_set_state")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_suspend_t__defined)
#define __MIG_check__Request__thread_suspend_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_suspend_t(__Request__thread_suspend_t *In0P)
{

	typedef __Request__thread_suspend_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_suspend_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_suspend */
mig_internal novalue _Xthread_suspend
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
	typedef __Request__thread_suspend_t __Request;
	typedef __Reply__thread_suspend_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_suspend_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_suspend_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3605, "thread_suspend")
	__BeforeRcvRpc(3605, "thread_suspend")

#if	defined(__MIG_check__Request__thread_suspend_t__defined)
	check_result = __MIG_check__Request__thread_suspend_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_suspend_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_suspend(target_act);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3605, "thread_suspend")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_resume_t__defined)
#define __MIG_check__Request__thread_resume_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_resume_t(__Request__thread_resume_t *In0P)
{

	typedef __Request__thread_resume_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_resume_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_resume */
mig_internal novalue _Xthread_resume
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
	typedef __Request__thread_resume_t __Request;
	typedef __Reply__thread_resume_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_resume_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_resume_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3606, "thread_resume")
	__BeforeRcvRpc(3606, "thread_resume")

#if	defined(__MIG_check__Request__thread_resume_t__defined)
	check_result = __MIG_check__Request__thread_resume_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_resume_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_resume(target_act);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3606, "thread_resume")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_abort_t__defined)
#define __MIG_check__Request__thread_abort_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_abort_t(__Request__thread_abort_t *In0P)
{

	typedef __Request__thread_abort_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_abort_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_abort */
mig_internal novalue _Xthread_abort
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
	typedef __Request__thread_abort_t __Request;
	typedef __Reply__thread_abort_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_abort_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_abort_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3607, "thread_abort")
	__BeforeRcvRpc(3607, "thread_abort")

#if	defined(__MIG_check__Request__thread_abort_t__defined)
	check_result = __MIG_check__Request__thread_abort_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_abort_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_abort(target_act);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3607, "thread_abort")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_abort_safely_t__defined)
#define __MIG_check__Request__thread_abort_safely_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_abort_safely_t(__Request__thread_abort_safely_t *In0P)
{

	typedef __Request__thread_abort_safely_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_abort_safely_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_abort_safely */
mig_internal novalue _Xthread_abort_safely
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
	typedef __Request__thread_abort_safely_t __Request;
	typedef __Reply__thread_abort_safely_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_abort_safely_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_abort_safely_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3608, "thread_abort_safely")
	__BeforeRcvRpc(3608, "thread_abort_safely")

#if	defined(__MIG_check__Request__thread_abort_safely_t__defined)
	check_result = __MIG_check__Request__thread_abort_safely_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_abort_safely_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_abort_safely(target_act);
	thread_deallocate(target_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3608, "thread_abort_safely")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_depress_abort_t__defined)
#define __MIG_check__Request__thread_depress_abort_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_depress_abort_t(__Request__thread_depress_abort_t *In0P)
{

	typedef __Request__thread_depress_abort_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_depress_abort_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_depress_abort */
mig_internal novalue _Xthread_depress_abort
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
	typedef __Request__thread_depress_abort_t __Request;
	typedef __Reply__thread_depress_abort_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_depress_abort_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_depress_abort_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3609, "thread_depress_abort")
	__BeforeRcvRpc(3609, "thread_depress_abort")

#if	defined(__MIG_check__Request__thread_depress_abort_t__defined)
	check_result = __MIG_check__Request__thread_depress_abort_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_depress_abort_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_depress_abort(thread);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3609, "thread_depress_abort")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_get_special_port_t__defined)
#define __MIG_check__Request__thread_get_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined */

#ifndef __NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined */

#ifndef __NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined */


mig_internal kern_return_t __MIG_check__Request__thread_get_special_port_t(__Request__thread_get_special_port_t *In0P)
{

	typedef __Request__thread_get_special_port_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined)
		__NDR_convert__int_rep__Request__thread_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined)
		__NDR_convert__char_rep__Request__thread_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined)
		__NDR_convert__float_rep__Request__thread_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_get_special_port_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_get_special_port */
mig_internal novalue _Xthread_get_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int which_port;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_get_special_port_t __Request;
	typedef __Reply__thread_get_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_get_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_get_special_port_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t special_portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t special_portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	thread_act_t thr_act;

	__DeclareRcvRpc(3610, "thread_get_special_port")
	__BeforeRcvRpc(3610, "thread_get_special_port")

#if	defined(__MIG_check__Request__thread_get_special_port_t__defined)
	check_result = __MIG_check__Request__thread_get_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_get_special_port_t__defined) */

#if	UseStaticTemplates
	OutP->special_port = special_portTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->special_port.disposition = 17;
#else
	OutP->special_port.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->special_port.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	thr_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	RetCode = thread_get_special_port(thr_act, In0P->which_port, &OutP->special_port.name);
	thread_deallocate(thr_act);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3610, "thread_get_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_set_special_port_t__defined)
#define __MIG_check__Request__thread_set_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined */


mig_internal kern_return_t __MIG_check__Request__thread_set_special_port_t(__Request__thread_set_special_port_t *In0P)
{

	typedef __Request__thread_set_special_port_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->special_port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->special_port.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined)
		__NDR_convert__int_rep__Request__thread_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined)
		__NDR_convert__char_rep__Request__thread_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined)
		__NDR_convert__float_rep__Request__thread_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_set_special_port_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_set_special_port */
mig_internal novalue _Xthread_set_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t special_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int which_port;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_set_special_port_t __Request;
	typedef __Reply__thread_set_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_set_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_set_special_port_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thr_act;

	__DeclareRcvRpc(3611, "thread_set_special_port")
	__BeforeRcvRpc(3611, "thread_set_special_port")

#if	defined(__MIG_check__Request__thread_set_special_port_t__defined)
	check_result = __MIG_check__Request__thread_set_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_set_special_port_t__defined) */

	thr_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_set_special_port(thr_act, In0P->which_port, In0P->special_port.name);
	thread_deallocate(thr_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3611, "thread_set_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_info_t__defined)
#define __MIG_check__Request__thread_info_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_flavor_t((thread_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__thread_info_t(__Request__thread_info_t *In0P)
{

	typedef __Request__thread_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined)
		__NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt(&In0P->thread_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_info_t__thread_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_info_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_info_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_info_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_info */
mig_internal novalue _Xthread_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		thread_flavor_t flavor;
		mach_msg_type_number_t thread_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_info_t __Request;
	typedef __Reply__thread_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t target_act;

	__DeclareRcvRpc(3612, "thread_info")
	__BeforeRcvRpc(3612, "thread_info")

#if	defined(__MIG_check__Request__thread_info_t__defined)
	check_result = __MIG_check__Request__thread_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_info_t__defined) */

	target_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->thread_info_outCnt = 12;
	if (In0P->thread_info_outCnt < OutP->thread_info_outCnt)
		OutP->thread_info_outCnt = In0P->thread_info_outCnt;

	OutP->RetCode = thread_info(target_act, In0P->flavor, OutP->thread_info_out, &OutP->thread_info_outCnt);
	thread_deallocate(target_act);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 48) + (((4 * OutP->thread_info_outCnt)));

	__AfterRcvRpc(3612, "thread_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_set_exception_ports_t__defined)
#define __MIG_check__Request__thread_set_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__thread_set_exception_ports_t(__Request__thread_set_exception_ports_t *In0P)
{

	typedef __Request__thread_set_exception_ports_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->new_port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->new_port.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_set_exception_ports_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_set_exception_ports */
mig_internal novalue _Xthread_set_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t new_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		exception_mask_t exception_mask;
		exception_behavior_t behavior;
		thread_state_flavor_t new_flavor;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_set_exception_ports_t __Request;
	typedef __Reply__thread_set_exception_ports_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_set_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_set_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3613, "thread_set_exception_ports")
	__BeforeRcvRpc(3613, "thread_set_exception_ports")

#if	defined(__MIG_check__Request__thread_set_exception_ports_t__defined)
	check_result = __MIG_check__Request__thread_set_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_set_exception_ports_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_set_exception_ports(thread, In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3613, "thread_set_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_get_exception_ports_t__defined)
#define __MIG_check__Request__thread_get_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined */


mig_internal kern_return_t __MIG_check__Request__thread_get_exception_ports_t(__Request__thread_get_exception_ports_t *In0P)
{

	typedef __Request__thread_get_exception_ports_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_get_exception_ports_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_get_exception_ports */
mig_internal novalue _Xthread_get_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		exception_mask_t exception_mask;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_get_exception_ports_t __Request;
	typedef __Reply__thread_get_exception_ports_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
	unsigned int msgh_size;
	unsigned int msgh_size_delta;

#ifdef	__MIG_check__Request__thread_get_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_get_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlersTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlersTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	thread_act_t thread;
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlers[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(3614, "thread_get_exception_ports")
	__BeforeRcvRpc(3614, "thread_get_exception_ports")

#if	defined(__MIG_check__Request__thread_get_exception_ports_t__defined)
	check_result = __MIG_check__Request__thread_get_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_get_exception_ports_t__defined) */

	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i;

	    ptr = &OutP->old_handlers[0];
	    for (i = 0; i < 32; ptr++, i++) {
#if	UseStaticTemplates
		*ptr = old_handlersTemplate;
#else	/* UseStaticTemplates */
		ptr->name = MACH_PORT_NULL;
#if __MigKernelSpecificCode
		ptr->disposition = 17;
#else
		ptr->disposition = 19;
#endif /* __MigKernelSpecificCode */
		ptr->type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */
	    }
	}


	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	masksCnt = 32;

	RetCode = thread_get_exception_ports(thread, In0P->exception_mask, OutP->masks, &masksCnt, old_handlers, old_behaviors, old_flavors);
	thread_deallocate(thread);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i, j;

	    ptr = &OutP->old_handlers[0];
	    j = min(32, masksCnt);
	    for (i = 0; i < j; ptr++, i++) {
		ptr->name = old_handlers[i];
	    }
	}


	OutP->NDR = NDR_record;

	OutP->masksCnt = masksCnt;
	msgh_size_delta = ((4 * masksCnt));
	msgh_size = (mach_msg_size_t)(sizeof(Reply) - 384) + msgh_size_delta;
	OutP = (Reply *) ((pointer_t) OutP + msgh_size_delta - 128);
	(void)memcpy((char *) OutP->old_behaviors, (const char *) old_behaviors, 4 * masksCnt);
	msgh_size_delta = ((4 * masksCnt));
	msgh_size += msgh_size_delta;
	OutP = (Reply *) ((pointer_t) OutP + msgh_size_delta - 128);
	(void)memcpy((char *) OutP->old_flavors, (const char *) old_flavors, 4 * masksCnt);
	msgh_size += ((4 * masksCnt));

	OutP = (Reply *) OutHeadP;
	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = msgh_size;
	OutP->msgh_body.msgh_descriptor_count = 32;
	__AfterRcvRpc(3614, "thread_get_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_swap_exception_ports_t__defined)
#define __MIG_check__Request__thread_swap_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__thread_act__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__thread_act__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__thread_swap_exception_ports_t(__Request__thread_swap_exception_ports_t *In0P)
{

	typedef __Request__thread_swap_exception_ports_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->new_port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->new_port.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_swap_exception_ports_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_swap_exception_ports */
mig_internal novalue _Xthread_swap_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t new_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		exception_mask_t exception_mask;
		exception_behavior_t behavior;
		thread_state_flavor_t new_flavor;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_swap_exception_ports_t __Request;
	typedef __Reply__thread_swap_exception_ports_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
	unsigned int msgh_size;
	unsigned int msgh_size_delta;

#ifdef	__MIG_check__Request__thread_swap_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_swap_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlersTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlersTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	thread_act_t thread;
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlers[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(3615, "thread_swap_exception_ports")
	__BeforeRcvRpc(3615, "thread_swap_exception_ports")

#if	defined(__MIG_check__Request__thread_swap_exception_ports_t__defined)
	check_result = __MIG_check__Request__thread_swap_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_swap_exception_ports_t__defined) */

	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i;

	    ptr = &OutP->old_handlers[0];
	    for (i = 0; i < 32; ptr++, i++) {
#if	UseStaticTemplates
		*ptr = old_handlersTemplate;
#else	/* UseStaticTemplates */
		ptr->name = MACH_PORT_NULL;
#if __MigKernelSpecificCode
		ptr->disposition = 17;
#else
		ptr->disposition = 19;
#endif /* __MigKernelSpecificCode */
		ptr->type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */
	    }
	}


	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	masksCnt = 32;

	RetCode = thread_swap_exception_ports(thread, In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor, OutP->masks, &masksCnt, old_handlers, old_behaviors, old_flavors);
	thread_deallocate(thread);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i, j;

	    ptr = &OutP->old_handlers[0];
	    j = min(32, masksCnt);
	    for (i = 0; i < j; ptr++, i++) {
		ptr->name = old_handlers[i];
	    }
	}


	OutP->NDR = NDR_record;

	OutP->masksCnt = masksCnt;
	msgh_size_delta = ((4 * masksCnt));
	msgh_size = (mach_msg_size_t)(sizeof(Reply) - 384) + msgh_size_delta;
	OutP = (Reply *) ((pointer_t) OutP + msgh_size_delta - 128);
	(void)memcpy((char *) OutP->old_behaviors, (const char *) old_behaviors, 4 * masksCnt);
	msgh_size_delta = ((4 * masksCnt));
	msgh_size += msgh_size_delta;
	OutP = (Reply *) ((pointer_t) OutP + msgh_size_delta - 128);
	(void)memcpy((char *) OutP->old_flavors, (const char *) old_flavors, 4 * masksCnt);
	msgh_size += ((4 * masksCnt));

	OutP = (Reply *) OutHeadP;
	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = msgh_size;
	OutP->msgh_body.msgh_descriptor_count = 32;
	__AfterRcvRpc(3615, "thread_swap_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_policy_t__defined)
#define __MIG_check__Request__thread_policy_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#if	defined(__NDR_convert__int_rep__thread_act__policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_t__base__defined
#if	defined(__NDR_convert__int_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_t__base__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined
#if	defined(__NDR_convert__int_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__int_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__int_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#if	defined(__NDR_convert__char_rep__thread_act__policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_t__base__defined
#if	defined(__NDR_convert__char_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_t__base__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined
#if	defined(__NDR_convert__char_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__char_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__char_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#if	defined(__NDR_convert__float_rep__thread_act__policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_t__base__defined
#if	defined(__NDR_convert__float_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_t__base__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined
#if	defined(__NDR_convert__float_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__float_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined
#define	__NDR_convert__float_rep__Request__thread_policy_t__set_limit(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined */


mig_internal kern_return_t __MIG_check__Request__thread_policy_t(__Request__thread_policy_t *In0P, __Request__thread_policy_t **In1PP)
{

	typedef __Request__thread_policy_t __Request;
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

#if defined(__NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_policy_t__baseCnt(&In0P->baseCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined */
	msgh_size_delta = (4 * In0P->baseCnt);
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 20) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 20);

#if	defined(__NDR_convert__int_rep__Request__thread_policy_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_t__base__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_t__baseCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_policy_t__policy__defined)
		__NDR_convert__int_rep__Request__thread_policy_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__thread_policy_t__base__defined)
		__NDR_convert__int_rep__Request__thread_policy_t__base(&In0P->base, In0P->NDR.int_rep, In0P->baseCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_t__base__defined */
#if defined(__NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined)
		__NDR_convert__int_rep__Request__thread_policy_t__set_limit(&In1P->set_limit, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_t__set_limit__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_policy_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_policy_t__policy__defined)
		__NDR_convert__char_rep__Request__thread_policy_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__thread_policy_t__base__defined)
		__NDR_convert__char_rep__Request__thread_policy_t__base(&In0P->base, In0P->NDR.char_rep, In0P->baseCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_t__base__defined */
#if defined(__NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined)
		__NDR_convert__char_rep__Request__thread_policy_t__set_limit(&In1P->set_limit, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_t__set_limit__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_policy_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_policy_t__policy__defined)
		__NDR_convert__float_rep__Request__thread_policy_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__thread_policy_t__base__defined)
		__NDR_convert__float_rep__Request__thread_policy_t__base(&In0P->base, In0P->NDR.float_rep, In0P->baseCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_t__base__defined */
#if defined(__NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined)
		__NDR_convert__float_rep__Request__thread_policy_t__set_limit(&In1P->set_limit, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_t__set_limit__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_policy_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_policy */
mig_internal novalue _Xthread_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		policy_t policy;
		mach_msg_type_number_t baseCnt;
		integer_t base[5];
		boolean_t set_limit;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_policy_t __Request;
	typedef __Reply__thread_policy_t Reply;

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
#ifdef	__MIG_check__Request__thread_policy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_policy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thr_act;

	__DeclareRcvRpc(3616, "thread_policy")
	__BeforeRcvRpc(3616, "thread_policy")

#if	defined(__MIG_check__Request__thread_policy_t__defined)
	check_result = __MIG_check__Request__thread_policy_t((__Request *)In0P, (__Request **)&In1P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_policy_t__defined) */

	thr_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_policy(thr_act, In0P->policy, In0P->base, In0P->baseCnt, In1P->set_limit);
	thread_deallocate(thr_act);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3616, "thread_policy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_policy_set_t__defined)
#define __MIG_check__Request__thread_policy_set_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__thread_act__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__thread_act__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__thread_act__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__thread_policy_t((thread_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined */


mig_internal kern_return_t __MIG_check__Request__thread_policy_set_t(__Request__thread_policy_set_t *In0P)
{

	typedef __Request__thread_policy_set_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 64)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt(&In0P->policy_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 64) + ((4 * In0P->policy_infoCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_set_t__policy_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_policy_set_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_set_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined)
		__NDR_convert__int_rep__Request__thread_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.int_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_policy_set_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_set_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined)
		__NDR_convert__char_rep__Request__thread_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.char_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_policy_set_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_set_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined)
		__NDR_convert__float_rep__Request__thread_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.float_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_policy_set_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_policy_set */
mig_internal novalue _Xthread_policy_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		thread_policy_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		integer_t policy_info[16];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_policy_set_t __Request;
	typedef __Reply__thread_policy_set_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_policy_set_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_policy_set_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3617, "thread_policy_set")
	__BeforeRcvRpc(3617, "thread_policy_set")

#if	defined(__MIG_check__Request__thread_policy_set_t__defined)
	check_result = __MIG_check__Request__thread_policy_set_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_policy_set_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_policy_set(thread, In0P->flavor, In0P->policy_info, In0P->policy_infoCnt);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3617, "thread_policy_set")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_policy_get_t__defined)
#define __MIG_check__Request__thread_policy_get_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#if	defined(__NDR_convert__int_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined */

#ifndef __NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined
#if	defined(__NDR_convert__int_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__int_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__int_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#if	defined(__NDR_convert__char_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined
#if	defined(__NDR_convert__char_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__char_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__char_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#if	defined(__NDR_convert__float_rep__thread_act__thread_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_policy_flavor_t((thread_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_act__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined
#if	defined(__NDR_convert__float_rep__thread_act__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__float_rep__thread_act__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined
#define	__NDR_convert__float_rep__Request__thread_policy_get_t__get_default(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined */


mig_internal kern_return_t __MIG_check__Request__thread_policy_get_t(__Request__thread_policy_get_t *In0P)
{

	typedef __Request__thread_policy_get_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_policy_get_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_get_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined)
		__NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt(&In0P->policy_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_get_t__policy_infoCnt__defined */
#if defined(__NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined)
		__NDR_convert__int_rep__Request__thread_policy_get_t__get_default(&In0P->get_default, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_policy_get_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_get_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined)
		__NDR_convert__char_rep__Request__thread_policy_get_t__get_default(&In0P->get_default, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_policy_get_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_get_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined)
		__NDR_convert__float_rep__Request__thread_policy_get_t__get_default(&In0P->get_default, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_policy_get_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_policy_get */
mig_internal novalue _Xthread_policy_get
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		thread_policy_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		boolean_t get_default;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_policy_get_t __Request;
	typedef __Reply__thread_policy_get_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
	unsigned int msgh_size_delta;

#ifdef	__MIG_check__Request__thread_policy_get_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_policy_get_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3618, "thread_policy_get")
	__BeforeRcvRpc(3618, "thread_policy_get")

#if	defined(__MIG_check__Request__thread_policy_get_t__defined)
	check_result = __MIG_check__Request__thread_policy_get_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_policy_get_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->policy_infoCnt = 16;
	if (In0P->policy_infoCnt < OutP->policy_infoCnt)
		OutP->policy_infoCnt = In0P->policy_infoCnt;

	OutP->RetCode = thread_policy_get(thread, In0P->flavor, OutP->policy_info, &OutP->policy_infoCnt, &In0P->get_default);
	thread_deallocate(thread);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	msgh_size_delta = ((4 * OutP->policy_infoCnt));
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 64) + msgh_size_delta;
	OutP = (Reply *) ((pointer_t) OutP + msgh_size_delta - 64);

	OutP->get_default = In0P->get_default;

	OutP = (Reply *) OutHeadP;
	__AfterRcvRpc(3618, "thread_policy_get")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_sample_t__defined)
#define __MIG_check__Request__thread_sample_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_sample_t(__Request__thread_sample_t *In0P)
{

	typedef __Request__thread_sample_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->reply.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->reply.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_sample_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_sample */
mig_internal novalue _Xthread_sample
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t reply;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_sample_t __Request;
	typedef __Reply__thread_sample_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_sample_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_sample_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3619, "thread_sample")
	__BeforeRcvRpc(3619, "thread_sample")

#if	defined(__MIG_check__Request__thread_sample_t__defined)
	check_result = __MIG_check__Request__thread_sample_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_sample_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_sample(thread, In0P->reply.name);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3619, "thread_sample")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_assign_t__defined)
#define __MIG_check__Request__thread_assign_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_assign_t(__Request__thread_assign_t *In0P)
{

	typedef __Request__thread_assign_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->new_set.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->new_set.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_assign_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_assign */
mig_internal novalue _Xthread_assign
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t new_set;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_assign_t __Request;
	typedef __Reply__thread_assign_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_assign_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_assign_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;
	processor_set_t new_set;

	__DeclareRcvRpc(3621, "thread_assign")
	__BeforeRcvRpc(3621, "thread_assign")

#if	defined(__MIG_check__Request__thread_assign_t__defined)
	check_result = __MIG_check__Request__thread_assign_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_assign_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	new_set = convert_port_to_pset(In0P->new_set.name);

	OutP->RetCode = thread_assign(thread, new_set);
	pset_deallocate(new_set);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->new_set.name))
		ipc_port_release_send((ipc_port_t)In0P->new_set.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3621, "thread_assign")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_assign_default_t__defined)
#define __MIG_check__Request__thread_assign_default_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_assign_default_t(__Request__thread_assign_default_t *In0P)
{

	typedef __Request__thread_assign_default_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_assign_default_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_assign_default */
mig_internal novalue _Xthread_assign_default
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
	typedef __Request__thread_assign_default_t __Request;
	typedef __Reply__thread_assign_default_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_assign_default_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_assign_default_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(3622, "thread_assign_default")
	__BeforeRcvRpc(3622, "thread_assign_default")

#if	defined(__MIG_check__Request__thread_assign_default_t__defined)
	check_result = __MIG_check__Request__thread_assign_default_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_assign_default_t__defined) */

	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	OutP->RetCode = thread_assign_default(thread);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3622, "thread_assign_default")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_get_assignment_t__defined)
#define __MIG_check__Request__thread_get_assignment_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_get_assignment_t(__Request__thread_get_assignment_t *In0P)
{

	typedef __Request__thread_get_assignment_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_get_assignment_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_get_assignment */
mig_internal novalue _Xthread_get_assignment
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
	typedef __Request__thread_get_assignment_t __Request;
	typedef __Reply__thread_get_assignment_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_get_assignment_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_get_assignment_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t assigned_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t assigned_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	thread_act_t thread;
	processor_set_name_t assigned_set;

	__DeclareRcvRpc(3623, "thread_get_assignment")
	__BeforeRcvRpc(3623, "thread_get_assignment")

#if	defined(__MIG_check__Request__thread_get_assignment_t__defined)
	check_result = __MIG_check__Request__thread_get_assignment_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_get_assignment_t__defined) */

#if	UseStaticTemplates
	OutP->assigned_set = assigned_setTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->assigned_set.disposition = 17;
#else
	OutP->assigned_set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->assigned_set.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	thread = convert_port_to_thread(In0P->Head.msgh_request_port);

	RetCode = thread_get_assignment(thread, &assigned_set);
	thread_deallocate(thread);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->assigned_set.name = (mach_port_t)convert_pset_name_to_port(assigned_set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3623, "thread_get_assignment")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__thread_act_subsystem__
#if !defined(__MIG_check__Request__thread_set_policy_t__defined)
#define __MIG_check__Request__thread_set_policy_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#if	defined(__NDR_convert__int_rep__thread_act__policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__policy_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#if	defined(__NDR_convert__int_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_policy_t__base__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#if	defined(__NDR_convert__int_rep__thread_act__policy_limit_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__int_rep__thread_act__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_limit_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__int_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_act__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__thread_act__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined */

#ifndef __NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined
#if	defined(__NDR_convert__int_rep__thread_act__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt(a, f) \
	__NDR_convert__int_rep__thread_act__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined
#define	__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#if	defined(__NDR_convert__char_rep__thread_act__policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__policy_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#if	defined(__NDR_convert__char_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_policy_t__base__defined */

#ifndef __NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#if	defined(__NDR_convert__char_rep__thread_act__policy_limit_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__char_rep__thread_act__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_limit_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__char_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_act__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__thread_act__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#if	defined(__NDR_convert__float_rep__thread_act__policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__policy_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__thread_act__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#if	defined(__NDR_convert__float_rep__thread_act__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__thread_act__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_policy_t__base__defined */

#ifndef __NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#if	defined(__NDR_convert__float_rep__thread_act__policy_limit_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__float_rep__thread_act__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_limit_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__float_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_act__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__thread_act__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__thread_act__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__thread_act__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__thread_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined */


mig_internal kern_return_t __MIG_check__Request__thread_set_policy_t(__Request__thread_set_policy_t *In0P, __Request__thread_set_policy_t **In1PP)
{

	typedef __Request__thread_set_policy_t __Request;
	__Request *In1P;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */
	unsigned int msgh_size_delta;

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 24)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request))
)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->pset.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->pset.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt(&In0P->baseCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined */
	msgh_size_delta = (4 * In0P->baseCnt);
#if	__MigTypeCheck
	if (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 24) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
	msgh_size -= msgh_size_delta;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 20);

#if defined(__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt(&In1P->limitCnt, In1P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 24) + ((4 * In1P->limitCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_policy_t__baseCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_set_policy_t__limitCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined)
		__NDR_convert__int_rep__Request__thread_set_policy_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_set_policy_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__thread_set_policy_t__base__defined)
		__NDR_convert__int_rep__Request__thread_set_policy_t__base(&In0P->base, In0P->NDR.int_rep, In0P->baseCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_set_policy_t__base__defined */
#if defined(__NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined)
		__NDR_convert__int_rep__Request__thread_set_policy_t__limit(&In1P->limit, In0P->NDR.int_rep, In1P->limitCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_set_policy_t__limit__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined)
		__NDR_convert__char_rep__Request__thread_set_policy_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_set_policy_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__thread_set_policy_t__base__defined)
		__NDR_convert__char_rep__Request__thread_set_policy_t__base(&In0P->base, In0P->NDR.char_rep, In0P->baseCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_set_policy_t__base__defined */
#if defined(__NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined)
		__NDR_convert__char_rep__Request__thread_set_policy_t__limit(&In1P->limit, In0P->NDR.char_rep, In1P->limitCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_set_policy_t__limit__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined)
		__NDR_convert__float_rep__Request__thread_set_policy_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_set_policy_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__thread_set_policy_t__base__defined)
		__NDR_convert__float_rep__Request__thread_set_policy_t__base(&In0P->base, In0P->NDR.float_rep, In0P->baseCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_set_policy_t__base__defined */
#if defined(__NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined)
		__NDR_convert__float_rep__Request__thread_set_policy_t__limit(&In1P->limit, In0P->NDR.float_rep, In1P->limitCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_set_policy_t__limit__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_set_policy_t__defined) */
#endif /* __MIG_check__Request__thread_act_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_set_policy */
mig_internal novalue _Xthread_set_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t pset;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		policy_t policy;
		mach_msg_type_number_t baseCnt;
		integer_t base[5];
		mach_msg_type_number_t limitCnt;
		integer_t limit[1];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_set_policy_t __Request;
	typedef __Reply__thread_set_policy_t Reply;

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
#ifdef	__MIG_check__Request__thread_set_policy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_set_policy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thr_act;
	processor_set_t pset;

	__DeclareRcvRpc(3624, "thread_set_policy")
	__BeforeRcvRpc(3624, "thread_set_policy")

#if	defined(__MIG_check__Request__thread_set_policy_t__defined)
	check_result = __MIG_check__Request__thread_set_policy_t((__Request *)In0P, (__Request **)&In1P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_set_policy_t__defined) */

	thr_act = convert_port_to_thread(In0P->Head.msgh_request_port);

	pset = convert_port_to_pset(In0P->pset.name);

	OutP->RetCode = thread_set_policy(thr_act, pset, In0P->policy, In0P->base, In0P->baseCnt, In1P->limit, In1P->limitCnt);
	pset_deallocate(pset);
	thread_deallocate(thr_act);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->pset.name))
		ipc_port_release_send((ipc_port_t)In0P->pset.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3624, "thread_set_policy")
}



/* Description of this subsystem, for use in direct RPC */
const struct thread_act_subsystem thread_act_subsystem = {
	thread_act_server_routine,
	3600,
	3625,
	(mach_msg_size_t)sizeof(union __ReplyUnion__thread_act_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_terminate, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_terminate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xact_get_state, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__act_get_state_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xact_set_state, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__act_set_state_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_get_state, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_get_state_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_set_state, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_set_state_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_suspend, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_suspend_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_resume, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_resume_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_abort, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_abort_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_abort_safely, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_abort_safely_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_depress_abort, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_depress_abort_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_get_special_port, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_get_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_set_special_port, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_set_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_info, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_set_exception_ports, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_set_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_get_exception_ports, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_get_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_swap_exception_ports, 10, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_swap_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_policy, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_policy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_policy_set, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_policy_set_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_policy_get, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_policy_get_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_sample, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_sample_t)},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_assign, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_assign_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_assign_default, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_assign_default_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_get_assignment, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_get_assignment_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_set_policy, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_set_policy_t)},
	}
};

mig_external boolean_t thread_act_server
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

	if ((InHeadP->msgh_id > 3624) || (InHeadP->msgh_id < 3600) ||
	    ((routine = thread_act_subsystem.routine[InHeadP->msgh_id - 3600].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t thread_act_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 3600;

	if ((msgh_id > 24) || (msgh_id < 0))
		return 0;

	return thread_act_subsystem.routine[msgh_id].stub_routine;
}

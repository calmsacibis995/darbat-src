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

/* Module semaphore */

#define	__MIG_check__Request__semaphore_subsystem__ 1
#define	__NDR_convert__Request__semaphore_subsystem__ 1

#include "semaphore_server.h"

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


mig_internal novalue _Xsemaphore_signal
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_signal_all
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_wait
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_signal_thread
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_timedwait
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_wait_signal
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_timedwait_signal
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_signal_t__defined)
#define __MIG_check__Request__semaphore_signal_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_signal_t(__Request__semaphore_signal_t *In0P)
{

	typedef __Request__semaphore_signal_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_signal_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_signal */
mig_internal novalue _Xsemaphore_signal
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
	typedef __Request__semaphore_signal_t __Request;
	typedef __Reply__semaphore_signal_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_signal_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_signal_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t semaphore;

	__DeclareRcvRpc(617200, "semaphore_signal")
	__BeforeRcvRpc(617200, "semaphore_signal")

#if	defined(__MIG_check__Request__semaphore_signal_t__defined)
	check_result = __MIG_check__Request__semaphore_signal_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_signal_t__defined) */

	semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	OutP->RetCode = semaphore_signal(semaphore);
	semaphore_dereference(semaphore);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617200, "semaphore_signal")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_signal_all_t__defined)
#define __MIG_check__Request__semaphore_signal_all_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_signal_all_t(__Request__semaphore_signal_all_t *In0P)
{

	typedef __Request__semaphore_signal_all_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_signal_all_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_signal_all */
mig_internal novalue _Xsemaphore_signal_all
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
	typedef __Request__semaphore_signal_all_t __Request;
	typedef __Reply__semaphore_signal_all_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_signal_all_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_signal_all_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t semaphore;

	__DeclareRcvRpc(617201, "semaphore_signal_all")
	__BeforeRcvRpc(617201, "semaphore_signal_all")

#if	defined(__MIG_check__Request__semaphore_signal_all_t__defined)
	check_result = __MIG_check__Request__semaphore_signal_all_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_signal_all_t__defined) */

	semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	OutP->RetCode = semaphore_signal_all(semaphore);
	semaphore_dereference(semaphore);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617201, "semaphore_signal_all")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_wait_t__defined)
#define __MIG_check__Request__semaphore_wait_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_wait_t(__Request__semaphore_wait_t *In0P)
{

	typedef __Request__semaphore_wait_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_wait_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_wait */
mig_internal novalue _Xsemaphore_wait
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
	typedef __Request__semaphore_wait_t __Request;
	typedef __Reply__semaphore_wait_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_wait_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_wait_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t semaphore;

	__DeclareRcvRpc(617202, "semaphore_wait")
	__BeforeRcvRpc(617202, "semaphore_wait")

#if	defined(__MIG_check__Request__semaphore_wait_t__defined)
	check_result = __MIG_check__Request__semaphore_wait_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_wait_t__defined) */

	semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	OutP->RetCode = semaphore_wait(semaphore);
	semaphore_dereference(semaphore);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617202, "semaphore_wait")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_signal_thread_t__defined)
#define __MIG_check__Request__semaphore_signal_thread_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_signal_thread_t(__Request__semaphore_signal_thread_t *In0P)
{

	typedef __Request__semaphore_signal_thread_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->thread.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->thread.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_signal_thread_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_signal_thread */
mig_internal novalue _Xsemaphore_signal_thread
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t thread;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_signal_thread_t __Request;
	typedef __Reply__semaphore_signal_thread_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_signal_thread_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_signal_thread_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t semaphore;
	thread_act_t thread;

	__DeclareRcvRpc(617203, "semaphore_signal_thread")
	__BeforeRcvRpc(617203, "semaphore_signal_thread")

#if	defined(__MIG_check__Request__semaphore_signal_thread_t__defined)
	check_result = __MIG_check__Request__semaphore_signal_thread_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_signal_thread_t__defined) */

	semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	thread = convert_port_to_thread(In0P->thread.name);

	OutP->RetCode = semaphore_signal_thread(semaphore, thread);
	thread_deallocate(thread);
	semaphore_dereference(semaphore);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->thread.name))
		ipc_port_release_send((ipc_port_t)In0P->thread.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617203, "semaphore_signal_thread")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_timedwait_t__defined)
#define __MIG_check__Request__semaphore_timedwait_t__defined
#ifndef __NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#if	defined(__NDR_convert__int_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__int_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__int_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__semaphore__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__semaphore__int)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__int)
#elif	defined(__NDR_convert__int_rep__semaphore__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined */

#ifndef __NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#if	defined(__NDR_convert__char_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__char_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__char_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__semaphore__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__semaphore__int)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__int)
#elif	defined(__NDR_convert__char_rep__semaphore__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined */

#ifndef __NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#if	defined(__NDR_convert__float_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__float_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__float_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__semaphore__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__semaphore__int)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__int)
#elif	defined(__NDR_convert__float_rep__semaphore__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined */


mig_internal kern_return_t __MIG_check__Request__semaphore_timedwait_t(__Request__semaphore_timedwait_t *In0P)
{

	typedef __Request__semaphore_timedwait_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined)
		__NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time(&In0P->wait_time, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__semaphore_timedwait_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined)
		__NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time(&In0P->wait_time, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__semaphore_timedwait_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined)
		__NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time(&In0P->wait_time, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__semaphore_timedwait_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_timedwait_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_timedwait */
mig_internal novalue _Xsemaphore_timedwait
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_timespec_t wait_time;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_timedwait_t __Request;
	typedef __Reply__semaphore_timedwait_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_timedwait_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_timedwait_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t semaphore;

	__DeclareRcvRpc(617204, "semaphore_timedwait")
	__BeforeRcvRpc(617204, "semaphore_timedwait")

#if	defined(__MIG_check__Request__semaphore_timedwait_t__defined)
	check_result = __MIG_check__Request__semaphore_timedwait_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_timedwait_t__defined) */

	semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	OutP->RetCode = semaphore_timedwait(semaphore, In0P->wait_time);
	semaphore_dereference(semaphore);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617204, "semaphore_timedwait")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_wait_signal_t__defined)
#define __MIG_check__Request__semaphore_wait_signal_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_wait_signal_t(__Request__semaphore_wait_signal_t *In0P)
{

	typedef __Request__semaphore_wait_signal_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->signal_semaphore.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->signal_semaphore.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_wait_signal_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_wait_signal */
mig_internal novalue _Xsemaphore_wait_signal
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t signal_semaphore;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_wait_signal_t __Request;
	typedef __Reply__semaphore_wait_signal_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_wait_signal_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_wait_signal_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t wait_semaphore;
	semaphore_t signal_semaphore;

	__DeclareRcvRpc(617205, "semaphore_wait_signal")
	__BeforeRcvRpc(617205, "semaphore_wait_signal")

#if	defined(__MIG_check__Request__semaphore_wait_signal_t__defined)
	check_result = __MIG_check__Request__semaphore_wait_signal_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_wait_signal_t__defined) */

	wait_semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	signal_semaphore = convert_port_to_semaphore(In0P->signal_semaphore.name);

	OutP->RetCode = semaphore_wait_signal(wait_semaphore, signal_semaphore);
	semaphore_dereference(signal_semaphore);
	semaphore_dereference(wait_semaphore);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->signal_semaphore.name))
		ipc_port_release_send((ipc_port_t)In0P->signal_semaphore.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617205, "semaphore_wait_signal")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__semaphore_subsystem__
#if !defined(__MIG_check__Request__semaphore_timedwait_signal_t__defined)
#define __MIG_check__Request__semaphore_timedwait_signal_t__defined
#ifndef __NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#if	defined(__NDR_convert__int_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__int_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__int_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__semaphore__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__semaphore__int)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__int)
#elif	defined(__NDR_convert__int_rep__semaphore__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */

#ifndef __NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#if	defined(__NDR_convert__char_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__char_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__char_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__semaphore__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__semaphore__int)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__int)
#elif	defined(__NDR_convert__char_rep__semaphore__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */

#ifndef __NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#if	defined(__NDR_convert__float_rep__semaphore__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__float_rep__semaphore__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__float_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__semaphore__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__semaphore__int)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__int)
#elif	defined(__NDR_convert__float_rep__semaphore__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__semaphore__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined
#define	__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */


mig_internal kern_return_t __MIG_check__Request__semaphore_timedwait_signal_t(__Request__semaphore_timedwait_signal_t *In0P)
{

	typedef __Request__semaphore_timedwait_signal_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->signal_semaphore.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->signal_semaphore.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
		__NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time(&In0P->wait_time, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
		__NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time(&In0P->wait_time, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined)
		__NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time(&In0P->wait_time, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__semaphore_timedwait_signal_t__wait_time__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_timedwait_signal_t__defined) */
#endif /* __MIG_check__Request__semaphore_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_timedwait_signal */
mig_internal novalue _Xsemaphore_timedwait_signal
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t signal_semaphore;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_timespec_t wait_time;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_timedwait_signal_t __Request;
	typedef __Reply__semaphore_timedwait_signal_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_timedwait_signal_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_timedwait_signal_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	semaphore_t wait_semaphore;
	semaphore_t signal_semaphore;

	__DeclareRcvRpc(617206, "semaphore_timedwait_signal")
	__BeforeRcvRpc(617206, "semaphore_timedwait_signal")

#if	defined(__MIG_check__Request__semaphore_timedwait_signal_t__defined)
	check_result = __MIG_check__Request__semaphore_timedwait_signal_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_timedwait_signal_t__defined) */

	wait_semaphore = convert_port_to_semaphore(In0P->Head.msgh_request_port);

	signal_semaphore = convert_port_to_semaphore(In0P->signal_semaphore.name);

	OutP->RetCode = semaphore_timedwait_signal(wait_semaphore, signal_semaphore, In0P->wait_time);
	semaphore_dereference(signal_semaphore);
	semaphore_dereference(wait_semaphore);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->signal_semaphore.name))
		ipc_port_release_send((ipc_port_t)In0P->signal_semaphore.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(617206, "semaphore_timedwait_signal")
}



/* Description of this subsystem, for use in direct RPC */
const struct semaphore_subsystem semaphore_subsystem = {
	semaphore_server_routine,
	617200,
	617207,
	(mach_msg_size_t)sizeof(union __ReplyUnion__semaphore_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_signal, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_signal_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_signal_all, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_signal_all_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_wait, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_wait_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_signal_thread, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_signal_thread_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_timedwait, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_timedwait_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_wait_signal, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_wait_signal_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_timedwait_signal, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_timedwait_signal_t)},
	}
};

mig_external boolean_t semaphore_server
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

	if ((InHeadP->msgh_id > 617206) || (InHeadP->msgh_id < 617200) ||
	    ((routine = semaphore_subsystem.routine[InHeadP->msgh_id - 617200].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t semaphore_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 617200;

	if ((msgh_id > 6) || (msgh_id < 0))
		return 0;

	return semaphore_subsystem.routine[msgh_id].stub_routine;
}

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
 */

/* Module notify */

#define	__MIG_check__Request__notify_subsystem__ 1
#define	__NDR_convert__Request__notify_subsystem__ 1

#include "mach_notify_server.h"

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

#define msgh_request_port	msgh_local_port
#define MACH_MSGH_BITS_REQUEST(bits)	MACH_MSGH_BITS_LOCAL(bits)
#define msgh_reply_port		msgh_remote_port
#define MACH_MSGH_BITS_REPLY(bits)	MACH_MSGH_BITS_REMOTE(bits)

#define MIG_RETURN_ERROR(X, code)	{\
				((mig_reply_error_t *)X)->RetCode = code;\
				((mig_reply_error_t *)X)->NDR = NDR_record;\
				return;\
				}

/* Forward Declarations */


mig_internal novalue _Xmach_notify_port_deleted
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_notify_port_destroyed
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_notify_no_senders
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_notify_send_once
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_notify_dead_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__notify_subsystem__
#if !defined(__MIG_check__Request__mach_notify_port_deleted_t__defined)
#define __MIG_check__Request__mach_notify_port_deleted_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined
#if	defined(__NDR_convert__int_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__int_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined
#if	defined(__NDR_convert__char_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__char_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined
#if	defined(__NDR_convert__float_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__float_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_notify_port_deleted_t(__Request__mach_notify_port_deleted_t *In0P)
{

	typedef __Request__mach_notify_port_deleted_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined)
		__NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_notify_port_deleted_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined)
		__NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_notify_port_deleted_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined)
		__NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_notify_port_deleted_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_notify_port_deleted_t__defined) */
#endif /* __MIG_check__Request__notify_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* SimpleRoutine mach_notify_port_deleted */
mig_internal novalue _Xmach_notify_port_deleted
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_notify_port_deleted_t __Request;
	typedef __Reply__mach_notify_port_deleted_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_notify_port_deleted_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_notify_port_deleted_t__defined */

	__DeclareRcvSimple(65, "mach_notify_port_deleted")
	__BeforeRcvSimple(65, "mach_notify_port_deleted")

#if	defined(__MIG_check__Request__mach_notify_port_deleted_t__defined)
	check_result = __MIG_check__Request__mach_notify_port_deleted_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_notify_port_deleted_t__defined) */

	OutP->RetCode = do_mach_notify_port_deleted(In0P->Head.msgh_request_port, In0P->name);
	__AfterRcvSimple(65, "mach_notify_port_deleted")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__notify_subsystem__
#if !defined(__MIG_check__Request__mach_notify_port_destroyed_t__defined)
#define __MIG_check__Request__mach_notify_port_destroyed_t__defined

mig_internal kern_return_t __MIG_check__Request__mach_notify_port_destroyed_t(__Request__mach_notify_port_destroyed_t *In0P)
{

	typedef __Request__mach_notify_port_destroyed_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->rights.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->rights.disposition != 16)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_notify_port_destroyed_t__defined) */
#endif /* __MIG_check__Request__notify_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* SimpleRoutine mach_notify_port_destroyed */
mig_internal novalue _Xmach_notify_port_destroyed
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t rights;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_notify_port_destroyed_t __Request;
	typedef __Reply__mach_notify_port_destroyed_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_notify_port_destroyed_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_notify_port_destroyed_t__defined */

	__DeclareRcvSimple(69, "mach_notify_port_destroyed")
	__BeforeRcvSimple(69, "mach_notify_port_destroyed")

#if	defined(__MIG_check__Request__mach_notify_port_destroyed_t__defined)
	check_result = __MIG_check__Request__mach_notify_port_destroyed_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_notify_port_destroyed_t__defined) */

	OutP->RetCode = do_mach_notify_port_destroyed(In0P->Head.msgh_request_port, In0P->rights.name);
	__AfterRcvSimple(69, "mach_notify_port_destroyed")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__notify_subsystem__
#if !defined(__MIG_check__Request__mach_notify_no_senders_t__defined)
#define __MIG_check__Request__mach_notify_no_senders_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#if	defined(__NDR_convert__int_rep__notify__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__notify__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__notify__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__notify__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__notify__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__notify__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined */

#ifndef __NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#if	defined(__NDR_convert__char_rep__notify__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__notify__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__notify__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__notify__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__notify__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__notify__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined */

#ifndef __NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#if	defined(__NDR_convert__float_rep__notify__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__notify__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__notify__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__notify__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__notify__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__notify__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined */


mig_internal kern_return_t __MIG_check__Request__mach_notify_no_senders_t(__Request__mach_notify_no_senders_t *In0P)
{

	typedef __Request__mach_notify_no_senders_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined)
		__NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount(&In0P->mscount, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_notify_no_senders_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined)
		__NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount(&In0P->mscount, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_notify_no_senders_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined)
		__NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount(&In0P->mscount, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_notify_no_senders_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_notify_no_senders_t__defined) */
#endif /* __MIG_check__Request__notify_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* SimpleRoutine mach_notify_no_senders */
mig_internal novalue _Xmach_notify_no_senders
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_mscount_t mscount;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_notify_no_senders_t __Request;
	typedef __Reply__mach_notify_no_senders_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_notify_no_senders_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_notify_no_senders_t__defined */

	__DeclareRcvSimple(70, "mach_notify_no_senders")
	__BeforeRcvSimple(70, "mach_notify_no_senders")

#if	defined(__MIG_check__Request__mach_notify_no_senders_t__defined)
	check_result = __MIG_check__Request__mach_notify_no_senders_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_notify_no_senders_t__defined) */

	OutP->RetCode = do_mach_notify_no_senders(In0P->Head.msgh_request_port, In0P->mscount);
	__AfterRcvSimple(70, "mach_notify_no_senders")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__notify_subsystem__
#if !defined(__MIG_check__Request__mach_notify_send_once_t__defined)
#define __MIG_check__Request__mach_notify_send_once_t__defined

mig_internal kern_return_t __MIG_check__Request__mach_notify_send_once_t(__Request__mach_notify_send_once_t *In0P)
{

	typedef __Request__mach_notify_send_once_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_notify_send_once_t__defined) */
#endif /* __MIG_check__Request__notify_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* SimpleRoutine mach_notify_send_once */
mig_internal novalue _Xmach_notify_send_once
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
	typedef __Request__mach_notify_send_once_t __Request;
	typedef __Reply__mach_notify_send_once_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_notify_send_once_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_notify_send_once_t__defined */

	__DeclareRcvSimple(71, "mach_notify_send_once")
	__BeforeRcvSimple(71, "mach_notify_send_once")

#if	defined(__MIG_check__Request__mach_notify_send_once_t__defined)
	check_result = __MIG_check__Request__mach_notify_send_once_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_notify_send_once_t__defined) */

	OutP->RetCode = do_mach_notify_send_once(In0P->Head.msgh_request_port);
	__AfterRcvSimple(71, "mach_notify_send_once")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__notify_subsystem__
#if !defined(__MIG_check__Request__mach_notify_dead_name_t__defined)
#define __MIG_check__Request__mach_notify_dead_name_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined
#if	defined(__NDR_convert__int_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__int_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined
#if	defined(__NDR_convert__char_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__char_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined
#if	defined(__NDR_convert__float_rep__notify__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__float_rep__notify__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_notify_dead_name_t(__Request__mach_notify_dead_name_t *In0P)
{

	typedef __Request__mach_notify_dead_name_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined)
		__NDR_convert__int_rep__Request__mach_notify_dead_name_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_notify_dead_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined)
		__NDR_convert__char_rep__Request__mach_notify_dead_name_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_notify_dead_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined)
		__NDR_convert__float_rep__Request__mach_notify_dead_name_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_notify_dead_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_notify_dead_name_t__defined) */
#endif /* __MIG_check__Request__notify_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* SimpleRoutine mach_notify_dead_name */
mig_internal novalue _Xmach_notify_dead_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_notify_dead_name_t __Request;
	typedef __Reply__mach_notify_dead_name_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_notify_dead_name_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_notify_dead_name_t__defined */

	__DeclareRcvSimple(72, "mach_notify_dead_name")
	__BeforeRcvSimple(72, "mach_notify_dead_name")

#if	defined(__MIG_check__Request__mach_notify_dead_name_t__defined)
	check_result = __MIG_check__Request__mach_notify_dead_name_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_notify_dead_name_t__defined) */

	OutP->RetCode = do_mach_notify_dead_name(In0P->Head.msgh_request_port, In0P->name);
	__AfterRcvSimple(72, "mach_notify_dead_name")
}



/* Description of this subsystem, for use in direct RPC */
const struct do_notify_subsystem do_notify_subsystem = {
	notify_server_routine,
	64,
	73,
	(mach_msg_size_t)sizeof(union __ReplyUnion__do_notify_subsystem),
	(vm_address_t)0,
	{
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_notify_port_deleted, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_notify_port_deleted_t)},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_notify_port_destroyed, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_notify_port_destroyed_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_notify_no_senders, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_notify_no_senders_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_notify_send_once, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_notify_send_once_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_notify_dead_name, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_notify_dead_name_t)},
	}
};

mig_external boolean_t notify_server
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

	if ((InHeadP->msgh_id > 72) || (InHeadP->msgh_id < 64) ||
	    ((routine = do_notify_subsystem.routine[InHeadP->msgh_id - 64].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t notify_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 64;

	if ((msgh_id > 8) || (msgh_id < 0))
		return 0;

	return do_notify_subsystem.routine[msgh_id].stub_routine;
}

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

/* Module processor */

#define	__MIG_check__Request__processor_subsystem__ 1
#define	__NDR_convert__Request__processor_subsystem__ 1

#include "processor_server.h"

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


mig_internal novalue _Xprocessor_start
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_exit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_assign
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xprocessor_get_assignment
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_start_t__defined)
#define __MIG_check__Request__processor_start_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_start_t(__Request__processor_start_t *In0P)
{

	typedef __Request__processor_start_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_start_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_start */
mig_internal novalue _Xprocessor_start
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
	typedef __Request__processor_start_t __Request;
	typedef __Reply__processor_start_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_start_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_start_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(3000, "processor_start")
	__BeforeRcvRpc(3000, "processor_start")

#if	defined(__MIG_check__Request__processor_start_t__defined)
	check_result = __MIG_check__Request__processor_start_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_start_t__defined) */

	OutP->RetCode = processor_start(convert_port_to_processor(In0P->Head.msgh_request_port));
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3000, "processor_start")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_exit_t__defined)
#define __MIG_check__Request__processor_exit_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_exit_t(__Request__processor_exit_t *In0P)
{

	typedef __Request__processor_exit_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_exit_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_exit */
mig_internal novalue _Xprocessor_exit
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
	typedef __Request__processor_exit_t __Request;
	typedef __Reply__processor_exit_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_exit_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_exit_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(3001, "processor_exit")
	__BeforeRcvRpc(3001, "processor_exit")

#if	defined(__MIG_check__Request__processor_exit_t__defined)
	check_result = __MIG_check__Request__processor_exit_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_exit_t__defined) */

	OutP->RetCode = processor_exit(convert_port_to_processor(In0P->Head.msgh_request_port));
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3001, "processor_exit")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_info_t__defined)
#define __MIG_check__Request__processor_info_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__processor__processor_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor__int__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__processor__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__processor__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__processor__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt(a, f) \
	__NDR_convert__int_rep__processor__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__processor__processor_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor__int__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__processor__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__processor__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__processor__processor_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor_flavor_t((processor_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor__int__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__processor__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__processor__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__processor_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__processor_info_t(__Request__processor_info_t *In0P)
{

	typedef __Request__processor_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__processor_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined)
		__NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt(&In0P->processor_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_info_t__processor_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_info_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__processor_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_info_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__processor_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_info_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_info */
mig_internal novalue _Xprocessor_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_flavor_t flavor;
		mach_msg_type_number_t processor_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_info_t __Request;
	typedef __Reply__processor_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_info_t__defined */

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
	host_t host;

	__DeclareRcvRpc(3002, "processor_info")
	__BeforeRcvRpc(3002, "processor_info")

#if	defined(__MIG_check__Request__processor_info_t__defined)
	check_result = __MIG_check__Request__processor_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_info_t__defined) */

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


	OutP->processor_info_outCnt = 12;
	if (In0P->processor_info_outCnt < OutP->processor_info_outCnt)
		OutP->processor_info_outCnt = In0P->processor_info_outCnt;

	RetCode = processor_info(convert_port_to_processor(In0P->Head.msgh_request_port), In0P->flavor, &host, OutP->processor_info_out, &OutP->processor_info_outCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->host.name = (mach_port_t)convert_host_to_port(host);


	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 48) + (((4 * OutP->processor_info_outCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3002, "processor_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_control_t__defined)
#define __MIG_check__Request__processor_control_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#if	defined(__NDR_convert__int_rep__processor__processor_info_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__int_rep__processor__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__processor_info_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__int_rep__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__processor__integer_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__processor__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__processor__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__processor__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined */

#ifndef __NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined
#if	defined(__NDR_convert__int_rep__processor__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt(a, f) \
	__NDR_convert__int_rep__processor__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined
#define	__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined */

#ifndef __NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#if	defined(__NDR_convert__char_rep__processor__processor_info_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__char_rep__processor__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__processor_info_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__char_rep__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__processor__integer_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__processor__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__processor__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__processor__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined */

#ifndef __NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#if	defined(__NDR_convert__float_rep__processor__processor_info_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__float_rep__processor__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__processor_info_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__float_rep__processor_info_t((processor_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__processor__integer_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__processor__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__processor__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__processor__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined
#define	__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined */


mig_internal kern_return_t __MIG_check__Request__processor_control_t(__Request__processor_control_t *In0P)
{

	typedef __Request__processor_control_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 48)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt(&In0P->processor_cmdCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 48) + ((4 * In0P->processor_cmdCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined) || \
	defined(__NDR_convert__int_rep__Request__processor_control_t__processor_cmdCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined)
		__NDR_convert__int_rep__Request__processor_control_t__processor_cmd(&In0P->processor_cmd, In0P->NDR.int_rep, In0P->processor_cmdCnt);
#endif	/* __NDR_convert__int_rep__Request__processor_control_t__processor_cmd__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined)
		__NDR_convert__char_rep__Request__processor_control_t__processor_cmd(&In0P->processor_cmd, In0P->NDR.char_rep, In0P->processor_cmdCnt);
#endif	/* __NDR_convert__char_rep__Request__processor_control_t__processor_cmd__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined)
		__NDR_convert__float_rep__Request__processor_control_t__processor_cmd(&In0P->processor_cmd, In0P->NDR.float_rep, In0P->processor_cmdCnt);
#endif	/* __NDR_convert__float_rep__Request__processor_control_t__processor_cmd__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_control_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_control */
mig_internal novalue _Xprocessor_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t processor_cmdCnt;
		integer_t processor_cmd[12];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_control_t __Request;
	typedef __Reply__processor_control_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_control_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_control_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(3003, "processor_control")
	__BeforeRcvRpc(3003, "processor_control")

#if	defined(__MIG_check__Request__processor_control_t__defined)
	check_result = __MIG_check__Request__processor_control_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_control_t__defined) */

	OutP->RetCode = processor_control(convert_port_to_processor(In0P->Head.msgh_request_port), In0P->processor_cmd, In0P->processor_cmdCnt);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3003, "processor_control")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_assign_t__defined)
#define __MIG_check__Request__processor_assign_t__defined
#ifndef __NDR_convert__int_rep__Request__processor_assign_t__wait__defined
#if	defined(__NDR_convert__int_rep__processor__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__int_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__int_rep__processor__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__int_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__processor_assign_t__wait__defined */

#ifndef __NDR_convert__char_rep__Request__processor_assign_t__wait__defined
#if	defined(__NDR_convert__char_rep__processor__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__char_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__char_rep__processor__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__char_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__processor_assign_t__wait__defined */

#ifndef __NDR_convert__float_rep__Request__processor_assign_t__wait__defined
#if	defined(__NDR_convert__float_rep__processor__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__float_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__float_rep__processor__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__processor_assign_t__wait__defined
#define	__NDR_convert__float_rep__Request__processor_assign_t__wait(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__processor_assign_t__wait__defined */


mig_internal kern_return_t __MIG_check__Request__processor_assign_t(__Request__processor_assign_t *In0P)
{

	typedef __Request__processor_assign_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__processor_assign_t__wait__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__processor_assign_t__wait__defined)
		__NDR_convert__int_rep__Request__processor_assign_t__wait(&In0P->wait, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__processor_assign_t__wait__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__processor_assign_t__wait__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__processor_assign_t__wait__defined)
		__NDR_convert__char_rep__Request__processor_assign_t__wait(&In0P->wait, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__processor_assign_t__wait__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__processor_assign_t__wait__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__processor_assign_t__wait__defined)
		__NDR_convert__float_rep__Request__processor_assign_t__wait(&In0P->wait, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__processor_assign_t__wait__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_assign_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_assign */
mig_internal novalue _Xprocessor_assign
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
		NDR_record_t NDR;
		boolean_t wait;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__processor_assign_t __Request;
	typedef __Reply__processor_assign_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_assign_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_assign_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	processor_set_t new_set;

	__DeclareRcvRpc(3004, "processor_assign")
	__BeforeRcvRpc(3004, "processor_assign")

#if	defined(__MIG_check__Request__processor_assign_t__defined)
	check_result = __MIG_check__Request__processor_assign_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_assign_t__defined) */

	new_set = convert_port_to_pset(In0P->new_set.name);

	OutP->RetCode = processor_assign(convert_port_to_processor(In0P->Head.msgh_request_port), new_set, In0P->wait);
	pset_deallocate(new_set);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->new_set.name))
		ipc_port_release_send((ipc_port_t)In0P->new_set.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3004, "processor_assign")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__processor_subsystem__
#if !defined(__MIG_check__Request__processor_get_assignment_t__defined)
#define __MIG_check__Request__processor_get_assignment_t__defined

mig_internal kern_return_t __MIG_check__Request__processor_get_assignment_t(__Request__processor_get_assignment_t *In0P)
{

	typedef __Request__processor_get_assignment_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__processor_get_assignment_t__defined) */
#endif /* __MIG_check__Request__processor_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine processor_get_assignment */
mig_internal novalue _Xprocessor_get_assignment
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
	typedef __Request__processor_get_assignment_t __Request;
	typedef __Reply__processor_get_assignment_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__processor_get_assignment_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__processor_get_assignment_t__defined */

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
	processor_set_name_t assigned_set;

	__DeclareRcvRpc(3005, "processor_get_assignment")
	__BeforeRcvRpc(3005, "processor_get_assignment")

#if	defined(__MIG_check__Request__processor_get_assignment_t__defined)
	check_result = __MIG_check__Request__processor_get_assignment_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__processor_get_assignment_t__defined) */

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


	RetCode = processor_get_assignment(convert_port_to_processor(In0P->Head.msgh_request_port), &assigned_set);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->assigned_set.name = (mach_port_t)convert_pset_name_to_port(assigned_set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3005, "processor_get_assignment")
}



/* Description of this subsystem, for use in direct RPC */
const struct processor_subsystem processor_subsystem = {
	processor_server_routine,
	3000,
	3006,
	(mach_msg_size_t)sizeof(union __ReplyUnion__processor_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_start, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_start_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_exit, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_exit_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_info, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_control, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_control_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_assign, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_assign_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xprocessor_get_assignment, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__processor_get_assignment_t)},
	}
};

mig_external boolean_t processor_server
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

	if ((InHeadP->msgh_id > 3005) || (InHeadP->msgh_id < 3000) ||
	    ((routine = processor_subsystem.routine[InHeadP->msgh_id - 3000].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t processor_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 3000;

	if ((msgh_id > 5) || (msgh_id < 0))
		return 0;

	return processor_subsystem.routine[msgh_id].stub_routine;
}

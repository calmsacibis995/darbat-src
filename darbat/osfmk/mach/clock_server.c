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
 * stub generated Tue Mar  7 16:25:25 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module clock */

#define	__MIG_check__Request__clock_subsystem__ 1
#define	__NDR_convert__Request__clock_subsystem__ 1

#include "clock_server.h"

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


mig_internal novalue _Xclock_get_time
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xclock_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xclock_alarm
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__clock_subsystem__
#if !defined(__MIG_check__Request__clock_get_time_t__defined)
#define __MIG_check__Request__clock_get_time_t__defined

mig_internal kern_return_t __MIG_check__Request__clock_get_time_t(__Request__clock_get_time_t *In0P)
{

	typedef __Request__clock_get_time_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__clock_get_time_t__defined) */
#endif /* __MIG_check__Request__clock_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine clock_get_time */
mig_internal novalue _Xclock_get_time
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
	typedef __Request__clock_get_time_t __Request;
	typedef __Reply__clock_get_time_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__clock_get_time_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__clock_get_time_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(1000, "clock_get_time")
	__BeforeRcvRpc(1000, "clock_get_time")

#if	defined(__MIG_check__Request__clock_get_time_t__defined)
	check_result = __MIG_check__Request__clock_get_time_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__clock_get_time_t__defined) */

	OutP->RetCode = clock_get_time(convert_port_to_clock(In0P->Head.msgh_request_port), &OutP->cur_time);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(1000, "clock_get_time")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__clock_subsystem__
#if !defined(__MIG_check__Request__clock_get_attributes_t__defined)
#define __MIG_check__Request__clock_get_attributes_t__defined
#ifndef __NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__int_rep__clock__clock_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__clock__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock__int__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined
#if	defined(__NDR_convert__int_rep__clock__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt(a, f) \
	__NDR_convert__int_rep__clock__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined
#define	__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined */

#ifndef __NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__char_rep__clock__clock_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__clock__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock__int__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__float_rep__clock__clock_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__clock__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__clock_flavor_t((clock_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock__int__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__clock_get_attributes_t(__Request__clock_get_attributes_t *In0P)
{

	typedef __Request__clock_get_attributes_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined)
		__NDR_convert__int_rep__Request__clock_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__clock_get_attributes_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined)
		__NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt(&In0P->clock_attrCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__clock_get_attributes_t__clock_attrCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined)
		__NDR_convert__char_rep__Request__clock_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__clock_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined)
		__NDR_convert__float_rep__Request__clock_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__clock_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__clock_get_attributes_t__defined) */
#endif /* __MIG_check__Request__clock_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine clock_get_attributes */
mig_internal novalue _Xclock_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		clock_flavor_t flavor;
		mach_msg_type_number_t clock_attrCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__clock_get_attributes_t __Request;
	typedef __Reply__clock_get_attributes_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__clock_get_attributes_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__clock_get_attributes_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(1001, "clock_get_attributes")
	__BeforeRcvRpc(1001, "clock_get_attributes")

#if	defined(__MIG_check__Request__clock_get_attributes_t__defined)
	check_result = __MIG_check__Request__clock_get_attributes_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__clock_get_attributes_t__defined) */

	OutP->clock_attrCnt = 1;
	if (In0P->clock_attrCnt < OutP->clock_attrCnt)
		OutP->clock_attrCnt = In0P->clock_attrCnt;

	OutP->RetCode = clock_get_attributes(convert_port_to_clock(In0P->Head.msgh_request_port), In0P->flavor, OutP->clock_attr, &OutP->clock_attrCnt);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 4) + (((4 * OutP->clock_attrCnt)));

	__AfterRcvRpc(1001, "clock_get_attributes")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__clock_subsystem__
#if !defined(__MIG_check__Request__clock_alarm_t__defined)
#define __MIG_check__Request__clock_alarm_t__defined
#ifndef __NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#if	defined(__NDR_convert__int_rep__clock__alarm_type_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__clock__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__alarm_type_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock__int__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined */

#ifndef __NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#if	defined(__NDR_convert__int_rep__clock__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__int_rep__clock__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_timespec_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__int_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock__int__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__clock__int)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__int_rep__int)
#elif	defined(__NDR_convert__int_rep__clock__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__clock__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined */

#ifndef __NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#if	defined(__NDR_convert__char_rep__clock__alarm_type_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__clock__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__alarm_type_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock__int__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined */

#ifndef __NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#if	defined(__NDR_convert__char_rep__clock__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__char_rep__clock__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_timespec_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__char_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock__int__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__clock__int)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__char_rep__int)
#elif	defined(__NDR_convert__char_rep__clock__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__clock__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined */

#ifndef __NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#if	defined(__NDR_convert__float_rep__clock__alarm_type_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__clock__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__alarm_type_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__alarm_type_t((alarm_type_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock__int__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__clock__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__clock__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined */

#ifndef __NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#if	defined(__NDR_convert__float_rep__clock__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__float_rep__clock__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_timespec_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__float_rep__mach_timespec_t((mach_timespec_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock__int__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__clock__int)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int *)(a), f, 2, __NDR_convert__float_rep__int)
#elif	defined(__NDR_convert__float_rep__clock__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__clock__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined
#define	__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined */


mig_internal kern_return_t __MIG_check__Request__clock_alarm_t(__Request__clock_alarm_t *In0P)
{

	typedef __Request__clock_alarm_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->alarm_port.type != MACH_MSG_PORT_DESCRIPTOR)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined) || \
	defined(__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined)
		__NDR_convert__int_rep__Request__clock_alarm_t__alarm_type(&In0P->alarm_type, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__clock_alarm_t__alarm_type__defined */
#if defined(__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined)
		__NDR_convert__int_rep__Request__clock_alarm_t__alarm_time(&In0P->alarm_time, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__clock_alarm_t__alarm_time__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined) || \
	defined(__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined)
		__NDR_convert__char_rep__Request__clock_alarm_t__alarm_type(&In0P->alarm_type, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__clock_alarm_t__alarm_type__defined */
#if defined(__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined)
		__NDR_convert__char_rep__Request__clock_alarm_t__alarm_time(&In0P->alarm_time, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__clock_alarm_t__alarm_time__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined) || \
	defined(__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined)
		__NDR_convert__float_rep__Request__clock_alarm_t__alarm_type(&In0P->alarm_type, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__clock_alarm_t__alarm_type__defined */
#if defined(__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined)
		__NDR_convert__float_rep__Request__clock_alarm_t__alarm_time(&In0P->alarm_time, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__clock_alarm_t__alarm_time__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__clock_alarm_t__defined) */
#endif /* __MIG_check__Request__clock_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine clock_alarm */
mig_internal novalue _Xclock_alarm
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t alarm_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		alarm_type_t alarm_type;
		mach_timespec_t alarm_time;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__clock_alarm_t __Request;
	typedef __Reply__clock_alarm_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__clock_alarm_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__clock_alarm_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(1002, "clock_alarm")
	__BeforeRcvRpc(1002, "clock_alarm")

#if	defined(__MIG_check__Request__clock_alarm_t__defined)
	check_result = __MIG_check__Request__clock_alarm_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__clock_alarm_t__defined) */

	OutP->RetCode = clock_alarm(convert_port_to_clock(In0P->Head.msgh_request_port), In0P->alarm_type, In0P->alarm_time, In0P->alarm_port.name, In0P->alarm_port.disposition);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(1002, "clock_alarm")
}



/* Description of this subsystem, for use in direct RPC */
const struct clock_subsystem clock_subsystem = {
	clock_server_routine,
	1000,
	1003,
	(mach_msg_size_t)sizeof(union __ReplyUnion__clock_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xclock_get_time, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__clock_get_time_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xclock_get_attributes, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__clock_get_attributes_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xclock_alarm, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__clock_alarm_t)},
	}
};

mig_external boolean_t clock_server
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

	if ((InHeadP->msgh_id > 1002) || (InHeadP->msgh_id < 1000) ||
	    ((routine = clock_subsystem.routine[InHeadP->msgh_id - 1000].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t clock_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 1000;

	if ((msgh_id > 2) || (msgh_id < 0))
		return 0;

	return clock_subsystem.routine[msgh_id].stub_routine;
}

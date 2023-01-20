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
 * stub generated Tue Mar  7 16:25:31 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module memory_object_control */

#define	__MIG_check__Request__memory_object_control_subsystem__ 1
#define	__NDR_convert__Request__memory_object_control_subsystem__ 1

#include "memory_object_control_server.h"

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


mig_internal novalue _Xmemory_object_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_change_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_synchronize_completed
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_lock_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_upl_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_super_upl_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_page_op
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_recover_named
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_release_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmemory_object_range_op
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_get_attributes_t__defined)
#define __MIG_check__Request__memory_object_get_attributes_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt(a, f) \
	__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_get_attributes_t(__Request__memory_object_get_attributes_t *In0P)
{

	typedef __Request__memory_object_get_attributes_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined)
		__NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_get_attributes_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined)
		__NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt(&In0P->attributesCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_get_attributes_t__attributesCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined)
		__NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined)
		__NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_get_attributes_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_get_attributes */
mig_internal novalue _Xmemory_object_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_flavor_t flavor;
		mach_msg_type_number_t attributesCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_get_attributes_t __Request;
	typedef __Reply__memory_object_get_attributes_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_get_attributes_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_get_attributes_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2000, "memory_object_get_attributes")
	__BeforeRcvRpc(2000, "memory_object_get_attributes")

#if	defined(__MIG_check__Request__memory_object_get_attributes_t__defined)
	check_result = __MIG_check__Request__memory_object_get_attributes_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_get_attributes_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->attributesCnt = 6;
	if (In0P->attributesCnt < OutP->attributesCnt)
		OutP->attributesCnt = In0P->attributesCnt;

	OutP->RetCode = memory_object_get_attributes(memory_control, In0P->flavor, OutP->attributes, &OutP->attributesCnt);
	memory_object_control_deallocate(memory_control);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 24) + (((4 * OutP->attributesCnt)));

	__AfterRcvRpc(2000, "memory_object_get_attributes")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_change_attributes_t__defined)
#define __MIG_check__Request__memory_object_change_attributes_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_info_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__int_rep__memory_object_control__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__memory_object_info_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__int_rep__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__int_rep__memory_object_control__int)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__int_rep__int)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__memory_object_control__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt(a, f) \
	__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_info_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__char_rep__memory_object_control__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__memory_object_info_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__char_rep__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__char_rep__memory_object_control__int)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__char_rep__int)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__memory_object_control__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_flavor_t((memory_object_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_info_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__float_rep__memory_object_control__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__memory_object_info_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__float_rep__memory_object_info_t((memory_object_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__float_rep__memory_object_control__int)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int *)(a), f, c, __NDR_convert__float_rep__int)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__memory_object_control__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined
#define	__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_change_attributes_t(__Request__memory_object_change_attributes_t *In0P)
{

	typedef __Request__memory_object_change_attributes_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 24)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt(&In0P->attributesCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 24) + ((4 * In0P->attributesCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributesCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined)
		__NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined)
		__NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes(&In0P->attributes, In0P->NDR.int_rep, In0P->attributesCnt);
#endif	/* __NDR_convert__int_rep__Request__memory_object_change_attributes_t__attributes__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined)
		__NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_change_attributes_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined)
		__NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes(&In0P->attributes, In0P->NDR.char_rep, In0P->attributesCnt);
#endif	/* __NDR_convert__char_rep__Request__memory_object_change_attributes_t__attributes__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined)
		__NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_change_attributes_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined)
		__NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes(&In0P->attributes, In0P->NDR.float_rep, In0P->attributesCnt);
#endif	/* __NDR_convert__float_rep__Request__memory_object_change_attributes_t__attributes__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_change_attributes_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_change_attributes */
mig_internal novalue _Xmemory_object_change_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_flavor_t flavor;
		mach_msg_type_number_t attributesCnt;
		int attributes[6];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_change_attributes_t __Request;
	typedef __Reply__memory_object_change_attributes_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_change_attributes_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_change_attributes_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2001, "memory_object_change_attributes")
	__BeforeRcvRpc(2001, "memory_object_change_attributes")

#if	defined(__MIG_check__Request__memory_object_change_attributes_t__defined)
	check_result = __MIG_check__Request__memory_object_change_attributes_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_change_attributes_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_change_attributes(memory_control, In0P->flavor, In0P->attributes, In0P->attributesCnt);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2001, "memory_object_change_attributes")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_synchronize_completed_t__defined)
#define __MIG_check__Request__memory_object_synchronize_completed_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__memory_object_control__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__memory_object_control__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__memory_object_control__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined
#define	__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_synchronize_completed_t(__Request__memory_object_synchronize_completed_t *In0P)
{

	typedef __Request__memory_object_synchronize_completed_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined)
		__NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length(&In0P->length, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_synchronize_completed_t__length__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined)
		__NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length(&In0P->length, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_synchronize_completed_t__length__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined)
		__NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length(&In0P->length, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_synchronize_completed_t__length__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_synchronize_completed_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_synchronize_completed */
mig_internal novalue _Xmemory_object_synchronize_completed
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		vm_offset_t length;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_synchronize_completed_t __Request;
	typedef __Reply__memory_object_synchronize_completed_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_synchronize_completed_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_synchronize_completed_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2002, "memory_object_synchronize_completed")
	__BeforeRcvRpc(2002, "memory_object_synchronize_completed")

#if	defined(__MIG_check__Request__memory_object_synchronize_completed_t__defined)
	check_result = __MIG_check__Request__memory_object_synchronize_completed_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_synchronize_completed_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_synchronize_completed(memory_control, In0P->offset, In0P->length);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2002, "memory_object_synchronize_completed")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_lock_request_t__defined)
#define __MIG_check__Request__memory_object_lock_request_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_return_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_return_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__memory_object_control__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_return_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_return_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__memory_object_control__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__size(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_return_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_return_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__memory_object_return_t((memory_object_return_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__memory_object_control__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined
#define	__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_lock_request_t(__Request__memory_object_lock_request_t *In0P)
{

	typedef __Request__memory_object_lock_request_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_lock_request_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_lock_request_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_lock_request_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_lock_request_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined)
		__NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return(&In0P->should_return, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_lock_request_t__should_return__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined)
		__NDR_convert__int_rep__Request__memory_object_lock_request_t__flags(&In0P->flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_lock_request_t__flags__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined)
		__NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value(&In0P->lock_value, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_lock_request_t__lock_value__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_lock_request_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_lock_request_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_lock_request_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_lock_request_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined)
		__NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return(&In0P->should_return, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_lock_request_t__should_return__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined)
		__NDR_convert__char_rep__Request__memory_object_lock_request_t__flags(&In0P->flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_lock_request_t__flags__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined)
		__NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value(&In0P->lock_value, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_lock_request_t__lock_value__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_lock_request_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_lock_request_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_lock_request_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_lock_request_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined)
		__NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return(&In0P->should_return, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_lock_request_t__should_return__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined)
		__NDR_convert__float_rep__Request__memory_object_lock_request_t__flags(&In0P->flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_lock_request_t__flags__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined)
		__NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value(&In0P->lock_value, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_lock_request_t__lock_value__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_lock_request_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_lock_request */
mig_internal novalue _Xmemory_object_lock_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_size_t size;
		memory_object_return_t should_return;
		integer_t flags;
		vm_prot_t lock_value;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_lock_request_t __Request;
	typedef __Reply__memory_object_lock_request_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_lock_request_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_lock_request_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2003, "memory_object_lock_request")
	__BeforeRcvRpc(2003, "memory_object_lock_request")

#if	defined(__MIG_check__Request__memory_object_lock_request_t__defined)
	check_result = __MIG_check__Request__memory_object_lock_request_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_lock_request_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_lock_request(memory_control, In0P->offset, In0P->size, &OutP->resid_offset, &OutP->io_errno, In0P->should_return, In0P->flags, In0P->lock_value);
	memory_object_control_deallocate(memory_control);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2003, "memory_object_lock_request")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_destroy_t__defined)
#define __MIG_check__Request__memory_object_destroy_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__kern_return_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__memory_object_control__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__kern_return_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__kern_return_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__memory_object_control__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__kern_return_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__kern_return_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__memory_object_control__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__kern_return_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__kern_return_t((kern_return_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__memory_object_control__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined
#define	__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_destroy_t(__Request__memory_object_destroy_t *In0P)
{

	typedef __Request__memory_object_destroy_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined)
		__NDR_convert__int_rep__Request__memory_object_destroy_t__reason(&In0P->reason, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_destroy_t__reason__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined)
		__NDR_convert__char_rep__Request__memory_object_destroy_t__reason(&In0P->reason, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_destroy_t__reason__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined)
		__NDR_convert__float_rep__Request__memory_object_destroy_t__reason(&In0P->reason, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_destroy_t__reason__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_destroy_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_destroy */
mig_internal novalue _Xmemory_object_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t reason;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_destroy_t __Request;
	typedef __Reply__memory_object_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2004, "memory_object_destroy")
	__BeforeRcvRpc(2004, "memory_object_destroy")

#if	defined(__MIG_check__Request__memory_object_destroy_t__defined)
	check_result = __MIG_check__Request__memory_object_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_destroy_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_destroy(memory_control, In0P->reason);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2004, "memory_object_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_upl_request_t__defined)
#define __MIG_check__Request__memory_object_upl_request_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_upl_request_t(__Request__memory_object_upl_request_t *In0P)
{

	typedef __Request__memory_object_upl_request_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_upl_request_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_upl_request_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_upl_request_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_upl_request_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined)
		__NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_upl_request_t__page_listCnt__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
		__NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_upl_request_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_upl_request_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_upl_request_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_upl_request_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
		__NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_upl_request_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_upl_request_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_upl_request_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_upl_request_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined)
		__NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_upl_request_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_upl_request */
mig_internal novalue _Xmemory_object_upl_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		vm_size_t size;
		mach_msg_type_number_t page_listCnt;
		integer_t cntrl_flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_upl_request_t __Request;
	typedef __Reply__memory_object_upl_request_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_upl_request_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_upl_request_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t uplTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t uplTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	memory_object_control_t memory_control;
	upl_t upl;

	__DeclareRcvRpc(2005, "memory_object_upl_request")
	__BeforeRcvRpc(2005, "memory_object_upl_request")

#if	defined(__MIG_check__Request__memory_object_upl_request_t__defined)
	check_result = __MIG_check__Request__memory_object_upl_request_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_upl_request_t__defined) */

#if	UseStaticTemplates
	OutP->upl = uplTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->upl.disposition = 17;
#else
	OutP->upl.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->upl.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->page_listCnt = 256;
	if (In0P->page_listCnt < OutP->page_listCnt)
		OutP->page_listCnt = In0P->page_listCnt;

	RetCode = memory_object_upl_request(memory_control, In0P->offset, In0P->size, &upl, OutP->page_list, &OutP->page_listCnt, In0P->cntrl_flags);
	memory_object_control_deallocate(memory_control);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->upl.name = (mach_port_t)convert_upl_to_port(upl);


	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 2048) + (((8 * OutP->page_listCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(2005, "memory_object_upl_request")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_super_upl_request_t__defined)
#define __MIG_check__Request__memory_object_super_upl_request_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__memory_object_control__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__memory_object_control__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__memory_object_control__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_super_upl_request_t(__Request__memory_object_super_upl_request_t *In0P)
{

	typedef __Request__memory_object_super_upl_request_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined)
		__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined)
		__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size(&In0P->super_size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__super_size__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined)
		__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__page_listCnt__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
		__NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined)
		__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined)
		__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size(&In0P->super_size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__super_size__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
		__NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined)
		__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined)
		__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size(&In0P->super_size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__super_size__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined)
		__NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags(&In0P->cntrl_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_super_upl_request_t__cntrl_flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_super_upl_request_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_super_upl_request */
mig_internal novalue _Xmemory_object_super_upl_request
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		vm_size_t size;
		vm_size_t super_size;
		mach_msg_type_number_t page_listCnt;
		integer_t cntrl_flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_super_upl_request_t __Request;
	typedef __Reply__memory_object_super_upl_request_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_super_upl_request_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_super_upl_request_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t uplTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t uplTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	memory_object_control_t memory_control;
	upl_t upl;

	__DeclareRcvRpc(2006, "memory_object_super_upl_request")
	__BeforeRcvRpc(2006, "memory_object_super_upl_request")

#if	defined(__MIG_check__Request__memory_object_super_upl_request_t__defined)
	check_result = __MIG_check__Request__memory_object_super_upl_request_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_super_upl_request_t__defined) */

#if	UseStaticTemplates
	OutP->upl = uplTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->upl.disposition = 17;
#else
	OutP->upl.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->upl.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->page_listCnt = 256;
	if (In0P->page_listCnt < OutP->page_listCnt)
		OutP->page_listCnt = In0P->page_listCnt;

	RetCode = memory_object_super_upl_request(memory_control, In0P->offset, In0P->size, In0P->super_size, &upl, OutP->page_list, &OutP->page_listCnt, In0P->cntrl_flags);
	memory_object_control_deallocate(memory_control);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->upl.name = (mach_port_t)convert_upl_to_port(upl);


	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 2048) + (((8 * OutP->page_listCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(2006, "memory_object_super_upl_request")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_page_op_t__defined)
#define __MIG_check__Request__memory_object_page_op_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_page_op_t__ops(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_page_op_t(__Request__memory_object_page_op_t *In0P)
{

	typedef __Request__memory_object_page_op_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined)
		__NDR_convert__int_rep__Request__memory_object_page_op_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_page_op_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined)
		__NDR_convert__int_rep__Request__memory_object_page_op_t__ops(&In0P->ops, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_page_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined)
		__NDR_convert__char_rep__Request__memory_object_page_op_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_page_op_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined)
		__NDR_convert__char_rep__Request__memory_object_page_op_t__ops(&In0P->ops, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_page_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined)
		__NDR_convert__float_rep__Request__memory_object_page_op_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_page_op_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined)
		__NDR_convert__float_rep__Request__memory_object_page_op_t__ops(&In0P->ops, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_page_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_page_op_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_page_op */
mig_internal novalue _Xmemory_object_page_op
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		integer_t ops;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_page_op_t __Request;
	typedef __Reply__memory_object_page_op_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_page_op_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_page_op_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2007, "memory_object_page_op")
	__BeforeRcvRpc(2007, "memory_object_page_op")

#if	defined(__MIG_check__Request__memory_object_page_op_t__defined)
	check_result = __MIG_check__Request__memory_object_page_op_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_page_op_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_page_op(memory_control, In0P->offset, In0P->ops, &OutP->phys_entry, &OutP->flags);
	memory_object_control_deallocate(memory_control);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2007, "memory_object_page_op")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_recover_named_t__defined)
#define __MIG_check__Request__memory_object_recover_named_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__int_rep__memory_object_control__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__char_rep__memory_object_control__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__float_rep__memory_object_control__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined
#define	__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_recover_named_t(__Request__memory_object_recover_named_t *In0P)
{

	typedef __Request__memory_object_recover_named_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
		__NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating(&In0P->wait_on_terminating, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
		__NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating(&In0P->wait_on_terminating, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined)
		__NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating(&In0P->wait_on_terminating, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_recover_named_t__wait_on_terminating__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_recover_named_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_recover_named */
mig_internal novalue _Xmemory_object_recover_named
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		boolean_t wait_on_terminating;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_recover_named_t __Request;
	typedef __Reply__memory_object_recover_named_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_recover_named_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_recover_named_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2008, "memory_object_recover_named")
	__BeforeRcvRpc(2008, "memory_object_recover_named")

#if	defined(__MIG_check__Request__memory_object_recover_named_t__defined)
	check_result = __MIG_check__Request__memory_object_recover_named_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_recover_named_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_recover_named(memory_control, In0P->wait_on_terminating);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2008, "memory_object_recover_named")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_release_name_t__defined)
#define __MIG_check__Request__memory_object_release_name_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__int_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__char_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined
#define	__NDR_convert__float_rep__Request__memory_object_release_name_t__flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_release_name_t(__Request__memory_object_release_name_t *In0P)
{

	typedef __Request__memory_object_release_name_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined)
		__NDR_convert__int_rep__Request__memory_object_release_name_t__flags(&In0P->flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_release_name_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined)
		__NDR_convert__char_rep__Request__memory_object_release_name_t__flags(&In0P->flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_release_name_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined)
		__NDR_convert__float_rep__Request__memory_object_release_name_t__flags(&In0P->flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_release_name_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_release_name_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_release_name */
mig_internal novalue _Xmemory_object_release_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		integer_t flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_release_name_t __Request;
	typedef __Reply__memory_object_release_name_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_release_name_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_release_name_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2009, "memory_object_release_name")
	__BeforeRcvRpc(2009, "memory_object_release_name")

#if	defined(__MIG_check__Request__memory_object_release_name_t__defined)
	check_result = __MIG_check__Request__memory_object_release_name_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_release_name_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_release_name(memory_control, In0P->flags);
	memory_object_control_deallocate(memory_control);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2009, "memory_object_release_name")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__memory_object_control_subsystem__
#if !defined(__MIG_check__Request__memory_object_range_op_t__defined)
#define __MIG_check__Request__memory_object_range_op_t__defined
#ifndef __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__int_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__int_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined */

#ifndef __NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined
#if	defined(__NDR_convert__int_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__int_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__int_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__int_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__char_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__char_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined */

#ifndef __NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined
#if	defined(__NDR_convert__char_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__char_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__char_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__char_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__float_rep__memory_object_control__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__float_rep__memory_object_control__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined */

#ifndef __NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined
#if	defined(__NDR_convert__float_rep__memory_object_control__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__float_rep__memory_object_control__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_control__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__float_rep__memory_object_control__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined
#define	__NDR_convert__float_rep__Request__memory_object_range_op_t__ops(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined */


mig_internal kern_return_t __MIG_check__Request__memory_object_range_op_t(__Request__memory_object_range_op_t *In0P)
{

	typedef __Request__memory_object_range_op_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined) || \
	defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined)
		__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg(&In0P->offset_beg, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_beg__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined)
		__NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end(&In0P->offset_end, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_range_op_t__offset_end__defined */
#if defined(__NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined)
		__NDR_convert__int_rep__Request__memory_object_range_op_t__ops(&In0P->ops, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__memory_object_range_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined) || \
	defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined)
		__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg(&In0P->offset_beg, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_beg__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined)
		__NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end(&In0P->offset_end, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_range_op_t__offset_end__defined */
#if defined(__NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined)
		__NDR_convert__char_rep__Request__memory_object_range_op_t__ops(&In0P->ops, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__memory_object_range_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined) || \
	defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined)
		__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg(&In0P->offset_beg, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_beg__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined)
		__NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end(&In0P->offset_end, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_range_op_t__offset_end__defined */
#if defined(__NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined)
		__NDR_convert__float_rep__Request__memory_object_range_op_t__ops(&In0P->ops, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__memory_object_range_op_t__ops__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__memory_object_range_op_t__defined) */
#endif /* __MIG_check__Request__memory_object_control_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine memory_object_range_op */
mig_internal novalue _Xmemory_object_range_op
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset_beg;
		memory_object_offset_t offset_end;
		integer_t ops;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__memory_object_range_op_t __Request;
	typedef __Reply__memory_object_range_op_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__memory_object_range_op_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__memory_object_range_op_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	memory_object_control_t memory_control;

	__DeclareRcvRpc(2010, "memory_object_range_op")
	__BeforeRcvRpc(2010, "memory_object_range_op")

#if	defined(__MIG_check__Request__memory_object_range_op_t__defined)
	check_result = __MIG_check__Request__memory_object_range_op_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__memory_object_range_op_t__defined) */

	memory_control = convert_port_to_mo_control(In0P->Head.msgh_request_port);

	OutP->RetCode = memory_object_range_op(memory_control, In0P->offset_beg, In0P->offset_end, In0P->ops, &OutP->range);
	memory_object_control_deallocate(memory_control);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2010, "memory_object_range_op")
}



/* Description of this subsystem, for use in direct RPC */
const struct memory_object_control_subsystem memory_object_control_subsystem = {
	memory_object_control_server_routine,
	2000,
	2011,
	(mach_msg_size_t)sizeof(union __ReplyUnion__memory_object_control_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_get_attributes, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_get_attributes_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_change_attributes, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_change_attributes_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_synchronize_completed, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_synchronize_completed_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_lock_request, 10, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_lock_request_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_destroy, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_upl_request, 8, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_upl_request_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_super_upl_request, 9, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_super_upl_request_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_page_op, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_page_op_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_recover_named, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_recover_named_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_release_name, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_release_name_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmemory_object_range_op, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__memory_object_range_op_t)},
	}
};

mig_external boolean_t memory_object_control_server
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

	if ((InHeadP->msgh_id > 2010) || (InHeadP->msgh_id < 2000) ||
	    ((routine = memory_object_control_subsystem.routine[InHeadP->msgh_id - 2000].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t memory_object_control_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 2000;

	if ((msgh_id > 10) || (msgh_id < 0))
		return 0;

	return memory_object_control_subsystem.routine[msgh_id].stub_routine;
}

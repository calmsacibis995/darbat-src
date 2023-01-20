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
 * stub generated Tue Mar  7 16:25:27 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module host_priv */

#define	__MIG_check__Request__host_priv_subsystem__ 1
#define	__NDR_convert__Request__host_priv_subsystem__ 1

#include "host_priv_server.h"

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


mig_internal novalue _Xhost_get_boot_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_reboot
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_priv_statistics
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_default_memory_manager
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_allocate_cpm
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_processors
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_clock_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xkmod_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xkmod_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xkmod_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_set_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_set_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_swap_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_load_symbol_table
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_vm_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_processor_sets
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_processor_set_priv
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xset_dp_control_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xget_dp_control_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_set_UNDServer
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xhost_get_UNDServer
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_get_boot_info_t__defined)
#define __MIG_check__Request__host_get_boot_info_t__defined

mig_internal kern_return_t __MIG_check__Request__host_get_boot_info_t(__Request__host_get_boot_info_t *In0P)
{

	typedef __Request__host_get_boot_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_boot_info_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_boot_info */
mig_internal novalue _Xhost_get_boot_info
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
	typedef __Request__host_get_boot_info_t __Request;
	typedef __Reply__host_get_boot_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_boot_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_boot_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(400, "host_get_boot_info")
	__BeforeRcvRpc(400, "host_get_boot_info")

#if	defined(__MIG_check__Request__host_get_boot_info_t__defined)
	check_result = __MIG_check__Request__host_get_boot_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_boot_info_t__defined) */

	OutP->RetCode = host_get_boot_info(convert_port_to_host_priv(In0P->Head.msgh_request_port), OutP->boot_info);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->boot_infoCnt = strlen(OutP->boot_info) + 1;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 4096) + (_WALIGN_((OutP->boot_infoCnt + 3) & ~3));

	__AfterRcvRpc(400, "host_get_boot_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_reboot_t__defined)
#define __MIG_check__Request__host_reboot_t__defined
#ifndef __NDR_convert__int_rep__Request__host_reboot_t__options__defined
#if	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__int_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__int_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__int_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__int_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_reboot_t__options__defined */

#ifndef __NDR_convert__char_rep__Request__host_reboot_t__options__defined
#if	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__char_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__char_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__char_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__char_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_reboot_t__options__defined */

#ifndef __NDR_convert__float_rep__Request__host_reboot_t__options__defined
#if	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__float_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__float_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__float_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_reboot_t__options__defined
#define	__NDR_convert__float_rep__Request__host_reboot_t__options(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_reboot_t__options__defined */


mig_internal kern_return_t __MIG_check__Request__host_reboot_t(__Request__host_reboot_t *In0P)
{

	typedef __Request__host_reboot_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_reboot_t__options__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_reboot_t__options__defined)
		__NDR_convert__int_rep__Request__host_reboot_t__options(&In0P->options, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_reboot_t__options__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_reboot_t__options__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_reboot_t__options__defined)
		__NDR_convert__char_rep__Request__host_reboot_t__options(&In0P->options, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_reboot_t__options__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_reboot_t__options__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_reboot_t__options__defined)
		__NDR_convert__float_rep__Request__host_reboot_t__options(&In0P->options, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_reboot_t__options__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_reboot_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_reboot */
mig_internal novalue _Xhost_reboot
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int options;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_reboot_t __Request;
	typedef __Reply__host_reboot_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_reboot_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_reboot_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(401, "host_reboot")
	__BeforeRcvRpc(401, "host_reboot")

#if	defined(__MIG_check__Request__host_reboot_t__defined)
	check_result = __MIG_check__Request__host_reboot_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_reboot_t__defined) */

	OutP->RetCode = host_reboot(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->options);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(401, "host_reboot")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_priv_statistics_t__defined)
#define __MIG_check__Request__host_priv_statistics_t__defined
#ifndef __NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#if	defined(__NDR_convert__int_rep__host_priv__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__host_priv__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#if	defined(__NDR_convert__char_rep__host_priv__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#if	defined(__NDR_convert__float_rep__host_priv__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__host_flavor_t((host_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined
#define	__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_priv_statistics_t(__Request__host_priv_statistics_t *In0P)
{

	typedef __Request__host_priv_statistics_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined)
		__NDR_convert__int_rep__Request__host_priv_statistics_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_priv_statistics_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined)
		__NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt(&In0P->host_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_priv_statistics_t__host_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined)
		__NDR_convert__char_rep__Request__host_priv_statistics_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_priv_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined)
		__NDR_convert__float_rep__Request__host_priv_statistics_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_priv_statistics_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_priv_statistics_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_priv_statistics */
mig_internal novalue _Xhost_priv_statistics
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
	typedef __Request__host_priv_statistics_t __Request;
	typedef __Reply__host_priv_statistics_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_priv_statistics_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_priv_statistics_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(402, "host_priv_statistics")
	__BeforeRcvRpc(402, "host_priv_statistics")

#if	defined(__MIG_check__Request__host_priv_statistics_t__defined)
	check_result = __MIG_check__Request__host_priv_statistics_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_priv_statistics_t__defined) */

	OutP->host_info_outCnt = 14;
	if (In0P->host_info_outCnt < OutP->host_info_outCnt)
		OutP->host_info_outCnt = In0P->host_info_outCnt;

	OutP->RetCode = host_priv_statistics(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->flavor, OutP->host_info_out, &OutP->host_info_outCnt);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 56) + (((4 * OutP->host_info_outCnt)));

	__AfterRcvRpc(402, "host_priv_statistics")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_default_memory_manager_t__defined)
#define __MIG_check__Request__host_default_memory_manager_t__defined
#ifndef __NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined */

#ifndef __NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined */

#ifndef __NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined
#define	__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined */


mig_internal kern_return_t __MIG_check__Request__host_default_memory_manager_t(__Request__host_default_memory_manager_t *In0P)
{

	typedef __Request__host_default_memory_manager_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->default_manager.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->default_manager.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined)
		__NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size(&In0P->cluster_size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_default_memory_manager_t__cluster_size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined)
		__NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size(&In0P->cluster_size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_default_memory_manager_t__cluster_size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined)
		__NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size(&In0P->cluster_size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_default_memory_manager_t__cluster_size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_default_memory_manager_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_default_memory_manager */
mig_internal novalue _Xhost_default_memory_manager
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t default_manager;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_size_t cluster_size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_default_memory_manager_t __Request;
	typedef __Reply__host_default_memory_manager_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_default_memory_manager_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_default_memory_manager_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t default_managerTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t default_managerTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		20,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(403, "host_default_memory_manager")
	__BeforeRcvRpc(403, "host_default_memory_manager")

#if	defined(__MIG_check__Request__host_default_memory_manager_t__defined)
	check_result = __MIG_check__Request__host_default_memory_manager_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_default_memory_manager_t__defined) */

#if	UseStaticTemplates
	OutP->default_manager = default_managerTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->default_manager.disposition = 17;
#else
	OutP->default_manager.disposition = 20;
#endif /* __MigKernelSpecificCode */
	OutP->default_manager.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_default_memory_manager(convert_port_to_host_priv(In0P->Head.msgh_request_port), &In0P->default_manager.name, In0P->cluster_size);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->default_manager.name = In0P->default_manager.name;

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(403, "host_default_memory_manager")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__vm_wire_t__defined)
#define __MIG_check__Request__vm_wire_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_wire_t__address__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_wire_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_wire_t__size__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_wire_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined */

#ifndef __NDR_convert__char_rep__Request__vm_wire_t__address__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_wire_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_wire_t__size__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_wire_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined */

#ifndef __NDR_convert__float_rep__Request__vm_wire_t__address__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_wire_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_wire_t__size__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_wire_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined */


mig_internal kern_return_t __MIG_check__Request__vm_wire_t(__Request__vm_wire_t *In0P)
{

	typedef __Request__vm_wire_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->task.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->task.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_wire_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_wire_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_wire_t__address__defined)
		__NDR_convert__int_rep__Request__vm_wire_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_wire_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_wire_t__size__defined)
		__NDR_convert__int_rep__Request__vm_wire_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_wire_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined)
		__NDR_convert__int_rep__Request__vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_wire_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_wire_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_wire_t__address__defined)
		__NDR_convert__char_rep__Request__vm_wire_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_wire_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_wire_t__size__defined)
		__NDR_convert__char_rep__Request__vm_wire_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_wire_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined)
		__NDR_convert__char_rep__Request__vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_wire_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_wire_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_wire_t__address__defined)
		__NDR_convert__float_rep__Request__vm_wire_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_wire_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_wire_t__size__defined)
		__NDR_convert__float_rep__Request__vm_wire_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_wire_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined)
		__NDR_convert__float_rep__Request__vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_wire_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_wire */
mig_internal novalue _Xvm_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_prot_t desired_access;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_wire_t __Request;
	typedef __Reply__vm_wire_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_wire_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_wire_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t task;

	__DeclareRcvRpc(404, "vm_wire")
	__BeforeRcvRpc(404, "vm_wire")

#if	defined(__MIG_check__Request__vm_wire_t__defined)
	check_result = __MIG_check__Request__vm_wire_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_wire_t__defined) */

	task = convert_port_to_map(In0P->task.name);

	OutP->RetCode = vm_wire(convert_port_to_host_priv(In0P->Head.msgh_request_port), task, In0P->address, In0P->size, In0P->desired_access);
	vm_map_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->task.name))
		ipc_port_release_send((ipc_port_t)In0P->task.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(404, "vm_wire")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__thread_wire_t__defined)
#define __MIG_check__Request__thread_wire_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_wire_t__wired__defined
#if	defined(__NDR_convert__int_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__int_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__int_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__int_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_wire_t__wired__defined */

#ifndef __NDR_convert__char_rep__Request__thread_wire_t__wired__defined
#if	defined(__NDR_convert__char_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__char_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__char_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__char_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_wire_t__wired__defined */

#ifndef __NDR_convert__float_rep__Request__thread_wire_t__wired__defined
#if	defined(__NDR_convert__float_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__float_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__float_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__thread_wire_t__wired__defined
#define	__NDR_convert__float_rep__Request__thread_wire_t__wired(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_wire_t__wired__defined */


mig_internal kern_return_t __MIG_check__Request__thread_wire_t(__Request__thread_wire_t *In0P)
{

	typedef __Request__thread_wire_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__thread_wire_t__wired__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_wire_t__wired__defined)
		__NDR_convert__int_rep__Request__thread_wire_t__wired(&In0P->wired, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_wire_t__wired__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_wire_t__wired__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_wire_t__wired__defined)
		__NDR_convert__char_rep__Request__thread_wire_t__wired(&In0P->wired, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_wire_t__wired__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_wire_t__wired__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_wire_t__wired__defined)
		__NDR_convert__float_rep__Request__thread_wire_t__wired(&In0P->wired, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_wire_t__wired__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_wire_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_wire */
mig_internal novalue _Xthread_wire
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
		NDR_record_t NDR;
		boolean_t wired;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__thread_wire_t __Request;
	typedef __Reply__thread_wire_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_wire_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_wire_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	thread_act_t thread;

	__DeclareRcvRpc(405, "thread_wire")
	__BeforeRcvRpc(405, "thread_wire")

#if	defined(__MIG_check__Request__thread_wire_t__defined)
	check_result = __MIG_check__Request__thread_wire_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_wire_t__defined) */

	thread = convert_port_to_thread(In0P->thread.name);

	OutP->RetCode = thread_wire(convert_port_to_host_priv(In0P->Head.msgh_request_port), thread, In0P->wired);
	thread_deallocate(thread);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->thread.name))
		ipc_port_release_send((ipc_port_t)In0P->thread.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(405, "thread_wire")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__vm_allocate_cpm_t__defined)
#define __MIG_check__Request__vm_allocate_cpm_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined
#if	defined(__NDR_convert__int_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__int_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined
#if	defined(__NDR_convert__char_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__char_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined
#if	defined(__NDR_convert__float_rep__host_priv__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__float_rep__host_priv__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined */


mig_internal kern_return_t __MIG_check__Request__vm_allocate_cpm_t(__Request__vm_allocate_cpm_t *In0P)
{

	typedef __Request__vm_allocate_cpm_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->task.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->task.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined)
		__NDR_convert__int_rep__Request__vm_allocate_cpm_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined)
		__NDR_convert__int_rep__Request__vm_allocate_cpm_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined)
		__NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere(&In0P->anywhere, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_cpm_t__anywhere__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined)
		__NDR_convert__char_rep__Request__vm_allocate_cpm_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined)
		__NDR_convert__char_rep__Request__vm_allocate_cpm_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined)
		__NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere(&In0P->anywhere, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_cpm_t__anywhere__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined)
		__NDR_convert__float_rep__Request__vm_allocate_cpm_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined)
		__NDR_convert__float_rep__Request__vm_allocate_cpm_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined)
		__NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere(&In0P->anywhere, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_cpm_t__anywhere__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_allocate_cpm_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_allocate_cpm */
mig_internal novalue _Xvm_allocate_cpm
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		boolean_t anywhere;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_allocate_cpm_t __Request;
	typedef __Reply__vm_allocate_cpm_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_allocate_cpm_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_allocate_cpm_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t task;

	__DeclareRcvRpc(406, "vm_allocate_cpm")
	__BeforeRcvRpc(406, "vm_allocate_cpm")

#if	defined(__MIG_check__Request__vm_allocate_cpm_t__defined)
	check_result = __MIG_check__Request__vm_allocate_cpm_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_allocate_cpm_t__defined) */

	task = convert_port_to_map(In0P->task.name);

	OutP->RetCode = vm_allocate_cpm(convert_port_to_host_priv(In0P->Head.msgh_request_port), task, &In0P->address, In0P->size, In0P->anywhere);
	vm_map_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->task.name))
		ipc_port_release_send((ipc_port_t)In0P->task.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(406, "vm_allocate_cpm")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_processors_t__defined)
#define __MIG_check__Request__host_processors_t__defined

mig_internal kern_return_t __MIG_check__Request__host_processors_t(__Request__host_processors_t *In0P)
{

	typedef __Request__host_processors_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_processors_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_processors */
mig_internal novalue _Xhost_processors
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
	typedef __Request__host_processors_t __Request;
	typedef __Reply__host_processors_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_processors_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_processors_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t out_processor_listTemplate = {
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
	const static mach_msg_ool_ports_descriptor_t out_processor_listTemplate = {
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
	__DeclareRcvRpc(407, "host_processors")
	__BeforeRcvRpc(407, "host_processors")

#if	defined(__MIG_check__Request__host_processors_t__defined)
	check_result = __MIG_check__Request__host_processors_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_processors_t__defined) */

#if	UseStaticTemplates
	OutP->out_processor_list = out_processor_listTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->out_processor_list.disposition = 17;
#else
	OutP->out_processor_list.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->out_processor_list.deallocate =  FALSE;
	OutP->out_processor_list.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_processors(convert_port_to_host_priv(In0P->Head.msgh_request_port), (processor_array_t *)&(OutP->out_processor_list.address), &OutP->out_processor_listCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->out_processor_list.count = OutP->out_processor_listCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(407, "host_processors")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_get_clock_control_t__defined)
#define __MIG_check__Request__host_get_clock_control_t__defined
#ifndef __NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#if	defined(__NDR_convert__int_rep__host_priv__clock_id_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__host_priv__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__clock_id_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined */

#ifndef __NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#if	defined(__NDR_convert__char_rep__host_priv__clock_id_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__host_priv__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__clock_id_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined */

#ifndef __NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#if	defined(__NDR_convert__float_rep__host_priv__clock_id_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__host_priv__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__clock_id_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__clock_id_t((clock_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined
#define	__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined */


mig_internal kern_return_t __MIG_check__Request__host_get_clock_control_t(__Request__host_get_clock_control_t *In0P)
{

	typedef __Request__host_get_clock_control_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined)
		__NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id(&In0P->clock_id, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_get_clock_control_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined)
		__NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id(&In0P->clock_id, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_get_clock_control_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined)
		__NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id(&In0P->clock_id, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_get_clock_control_t__clock_id__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_clock_control_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_clock_control */
mig_internal novalue _Xhost_get_clock_control
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
	typedef __Request__host_get_clock_control_t __Request;
	typedef __Reply__host_get_clock_control_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_clock_control_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_clock_control_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t clock_ctrlTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t clock_ctrlTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	clock_ctrl_t clock_ctrl;

	__DeclareRcvRpc(408, "host_get_clock_control")
	__BeforeRcvRpc(408, "host_get_clock_control")

#if	defined(__MIG_check__Request__host_get_clock_control_t__defined)
	check_result = __MIG_check__Request__host_get_clock_control_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_clock_control_t__defined) */

#if	UseStaticTemplates
	OutP->clock_ctrl = clock_ctrlTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->clock_ctrl.disposition = 17;
#else
	OutP->clock_ctrl.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->clock_ctrl.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_get_clock_control(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->clock_id, &clock_ctrl);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->clock_ctrl.name = (mach_port_t)convert_clock_ctrl_to_port(clock_ctrl);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(408, "host_get_clock_control")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__kmod_create_t__defined)
#define __MIG_check__Request__kmod_create_t__defined
#ifndef __NDR_convert__int_rep__Request__kmod_create_t__info__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__natural_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__int_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_create_t__info__defined */

#ifndef __NDR_convert__char_rep__Request__kmod_create_t__info__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__natural_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__char_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__kmod_create_t__info__defined */

#ifndef __NDR_convert__float_rep__Request__kmod_create_t__info__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__host_priv__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__natural_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__host_priv__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_create_t__info__defined
#define	__NDR_convert__float_rep__Request__kmod_create_t__info(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__kmod_create_t__info__defined */


mig_internal kern_return_t __MIG_check__Request__kmod_create_t(__Request__kmod_create_t *In0P)
{

	typedef __Request__kmod_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__kmod_create_t__info__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__kmod_create_t__info__defined)
		__NDR_convert__int_rep__Request__kmod_create_t__info(&In0P->info, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__kmod_create_t__info__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__kmod_create_t__info__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__kmod_create_t__info__defined)
		__NDR_convert__char_rep__Request__kmod_create_t__info(&In0P->info, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__kmod_create_t__info__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__kmod_create_t__info__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__kmod_create_t__info__defined)
		__NDR_convert__float_rep__Request__kmod_create_t__info(&In0P->info, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__kmod_create_t__info__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__kmod_create_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine kmod_create */
mig_internal novalue _Xkmod_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t info;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__kmod_create_t __Request;
	typedef __Reply__kmod_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__kmod_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__kmod_create_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(409, "kmod_create")
	__BeforeRcvRpc(409, "kmod_create")

#if	defined(__MIG_check__Request__kmod_create_t__defined)
	check_result = __MIG_check__Request__kmod_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__kmod_create_t__defined) */

	OutP->RetCode = kmod_create(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->info, &OutP->module);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(409, "kmod_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__kmod_destroy_t__defined)
#define __MIG_check__Request__kmod_destroy_t__defined
#ifndef __NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#if	defined(__NDR_convert__int_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__kmod_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_destroy_t__module__defined */

#ifndef __NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#if	defined(__NDR_convert__char_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__kmod_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__kmod_destroy_t__module__defined */

#ifndef __NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#if	defined(__NDR_convert__float_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__kmod_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_destroy_t__module(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__kmod_destroy_t__module__defined */


mig_internal kern_return_t __MIG_check__Request__kmod_destroy_t(__Request__kmod_destroy_t *In0P)
{

	typedef __Request__kmod_destroy_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__kmod_destroy_t__module__defined)
		__NDR_convert__int_rep__Request__kmod_destroy_t__module(&In0P->module, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__kmod_destroy_t__module__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__kmod_destroy_t__module__defined)
		__NDR_convert__char_rep__Request__kmod_destroy_t__module(&In0P->module, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__kmod_destroy_t__module__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__kmod_destroy_t__module__defined)
		__NDR_convert__float_rep__Request__kmod_destroy_t__module(&In0P->module, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__kmod_destroy_t__module__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__kmod_destroy_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine kmod_destroy */
mig_internal novalue _Xkmod_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kmod_t module;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__kmod_destroy_t __Request;
	typedef __Reply__kmod_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__kmod_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__kmod_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(410, "kmod_destroy")
	__BeforeRcvRpc(410, "kmod_destroy")

#if	defined(__MIG_check__Request__kmod_destroy_t__defined)
	check_result = __MIG_check__Request__kmod_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__kmod_destroy_t__defined) */

	OutP->RetCode = kmod_destroy(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->module);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(410, "kmod_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__kmod_control_t__defined)
#define __MIG_check__Request__kmod_control_t__defined
#ifndef __NDR_convert__int_rep__Request__kmod_control_t__module__defined
#if	defined(__NDR_convert__int_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__kmod_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_control_t__module__defined */

#ifndef __NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#if	defined(__NDR_convert__int_rep__host_priv__kmod_control_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__kmod_control_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_control_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__kmod_control_t__data__defined
#if	defined(__NDR_convert__int_rep__host_priv__kmod_args_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__int_rep__host_priv__kmod_args_t((kmod_args_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__kmod_args_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__int_rep__kmod_args_t((kmod_args_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_control_t__data__defined */

#ifndef __NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__dataCnt(a, f) \
	__NDR_convert__int_rep__host_priv__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined
#define	__NDR_convert__int_rep__Request__kmod_control_t__dataCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined */

#ifndef __NDR_convert__char_rep__Request__kmod_control_t__module__defined
#if	defined(__NDR_convert__char_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__kmod_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__kmod_control_t__module__defined */

#ifndef __NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#if	defined(__NDR_convert__char_rep__host_priv__kmod_control_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__kmod_control_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__kmod_control_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__kmod_control_t__data__defined
#if	defined(__NDR_convert__char_rep__host_priv__kmod_args_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__char_rep__host_priv__kmod_args_t((kmod_args_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__kmod_args_t__defined)
#define	__NDR_convert__char_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__char_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__char_rep__kmod_args_t((kmod_args_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__kmod_control_t__data__defined */

#ifndef __NDR_convert__float_rep__Request__kmod_control_t__module__defined
#if	defined(__NDR_convert__float_rep__host_priv__kmod_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__kmod_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__kmod_t((kmod_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__module__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__module(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__kmod_control_t__module__defined */

#ifndef __NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#if	defined(__NDR_convert__float_rep__host_priv__kmod_control_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__kmod_control_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__kmod_control_flavor_t((kmod_control_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__kmod_control_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__kmod_control_t__data__defined
#if	defined(__NDR_convert__float_rep__host_priv__kmod_args_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__float_rep__host_priv__kmod_args_t((kmod_args_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__kmod_args_t__defined)
#define	__NDR_convert__float_rep__Request__kmod_control_t__data__defined
#define	__NDR_convert__float_rep__Request__kmod_control_t__data(a, f, c) \
	__NDR_convert__float_rep__kmod_args_t((kmod_args_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__kmod_control_t__data__defined */


mig_internal kern_return_t __MIG_check__Request__kmod_control_t(__Request__kmod_control_t *In0P)
{

	typedef __Request__kmod_control_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->data.type != MACH_MSG_OOL_DESCRIPTOR)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__kmod_control_t__module__defined) || \
	defined(__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__kmod_control_t__data__defined) || \
	defined(__NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__kmod_control_t__module__defined)
		__NDR_convert__int_rep__Request__kmod_control_t__module(&In0P->module, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__kmod_control_t__module__defined */
#if defined(__NDR_convert__int_rep__Request__kmod_control_t__flavor__defined)
		__NDR_convert__int_rep__Request__kmod_control_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__kmod_control_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined)
		__NDR_convert__int_rep__Request__kmod_control_t__dataCnt(&In0P->dataCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__kmod_control_t__dataCnt__defined */
#if defined(__NDR_convert__int_rep__Request__kmod_control_t__data__defined)
		__NDR_convert__int_rep__Request__kmod_control_t__data((kmod_args_t)(In0P->data.address), In0P->NDR.int_rep, In0P->dataCnt);
#endif	/* __NDR_convert__int_rep__Request__kmod_control_t__data__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__kmod_control_t__module__defined) || \
	defined(__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__kmod_control_t__data__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__kmod_control_t__module__defined)
		__NDR_convert__char_rep__Request__kmod_control_t__module(&In0P->module, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__kmod_control_t__module__defined */
#if defined(__NDR_convert__char_rep__Request__kmod_control_t__flavor__defined)
		__NDR_convert__char_rep__Request__kmod_control_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__kmod_control_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__kmod_control_t__data__defined)
		__NDR_convert__char_rep__Request__kmod_control_t__data((kmod_args_t)(In0P->data.address), In0P->NDR.char_rep, In0P->dataCnt);
#endif	/* __NDR_convert__char_rep__Request__kmod_control_t__data__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__kmod_control_t__module__defined) || \
	defined(__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__kmod_control_t__data__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__kmod_control_t__module__defined)
		__NDR_convert__float_rep__Request__kmod_control_t__module(&In0P->module, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__kmod_control_t__module__defined */
#if defined(__NDR_convert__float_rep__Request__kmod_control_t__flavor__defined)
		__NDR_convert__float_rep__Request__kmod_control_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__kmod_control_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__kmod_control_t__data__defined)
		__NDR_convert__float_rep__Request__kmod_control_t__data((kmod_args_t)(In0P->data.address), In0P->NDR.float_rep, In0P->dataCnt);
#endif	/* __NDR_convert__float_rep__Request__kmod_control_t__data__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__kmod_control_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine kmod_control */
mig_internal novalue _Xkmod_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t data;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		kmod_t module;
		kmod_control_flavor_t flavor;
		mach_msg_type_number_t dataCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__kmod_control_t __Request;
	typedef __Reply__kmod_control_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__kmod_control_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__kmod_control_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t dataTemplate = {
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
	const static mach_msg_ool_descriptor_t dataTemplate = {
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
	__DeclareRcvRpc(411, "kmod_control")
	__BeforeRcvRpc(411, "kmod_control")

#if	defined(__MIG_check__Request__kmod_control_t__defined)
	check_result = __MIG_check__Request__kmod_control_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__kmod_control_t__defined) */

#if	UseStaticTemplates
	OutP->data = dataTemplate;
#else	/* UseStaticTemplates */
	OutP->data.deallocate =  FALSE;
	OutP->data.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->data.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = kmod_control(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->module, In0P->flavor, (kmod_args_t *)&(In0P->data.address), &In0P->dataCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->data.size = OutP->dataCnt;


	OutP->NDR = NDR_record;


	OutP->data.address = In0P->data.address;

	OutP->dataCnt = In0P->dataCnt;

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(411, "kmod_control")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_get_special_port_t__defined)
#define __MIG_check__Request__host_get_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__host_get_special_port_t__node__defined
#if	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_get_special_port_t__node__defined */

#ifndef __NDR_convert__int_rep__Request__host_get_special_port_t__which__defined
#if	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_get_special_port_t__which__defined */

#ifndef __NDR_convert__char_rep__Request__host_get_special_port_t__node__defined
#if	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_get_special_port_t__node__defined */

#ifndef __NDR_convert__char_rep__Request__host_get_special_port_t__which__defined
#if	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_get_special_port_t__which__defined */

#ifndef __NDR_convert__float_rep__Request__host_get_special_port_t__node__defined
#if	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__node(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_get_special_port_t__node__defined */

#ifndef __NDR_convert__float_rep__Request__host_get_special_port_t__which__defined
#if	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_get_special_port_t__which(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_get_special_port_t__which__defined */


mig_internal kern_return_t __MIG_check__Request__host_get_special_port_t(__Request__host_get_special_port_t *In0P)
{

	typedef __Request__host_get_special_port_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined) || \
	defined(__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_get_special_port_t__node__defined)
		__NDR_convert__int_rep__Request__host_get_special_port_t__node(&In0P->node, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_get_special_port_t__node__defined */
#if defined(__NDR_convert__int_rep__Request__host_get_special_port_t__which__defined)
		__NDR_convert__int_rep__Request__host_get_special_port_t__which(&In0P->which, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_get_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined) || \
	defined(__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_get_special_port_t__node__defined)
		__NDR_convert__char_rep__Request__host_get_special_port_t__node(&In0P->node, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_get_special_port_t__node__defined */
#if defined(__NDR_convert__char_rep__Request__host_get_special_port_t__which__defined)
		__NDR_convert__char_rep__Request__host_get_special_port_t__which(&In0P->which, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_get_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined) || \
	defined(__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_get_special_port_t__node__defined)
		__NDR_convert__float_rep__Request__host_get_special_port_t__node(&In0P->node, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_get_special_port_t__node__defined */
#if defined(__NDR_convert__float_rep__Request__host_get_special_port_t__which__defined)
		__NDR_convert__float_rep__Request__host_get_special_port_t__which(&In0P->which, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_get_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_special_port_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_special_port */
mig_internal novalue _Xhost_get_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int node;
		int which;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_get_special_port_t __Request;
	typedef __Reply__host_get_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_special_port_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(412, "host_get_special_port")
	__BeforeRcvRpc(412, "host_get_special_port")

#if	defined(__MIG_check__Request__host_get_special_port_t__defined)
	check_result = __MIG_check__Request__host_get_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_special_port_t__defined) */

#if	UseStaticTemplates
	OutP->port = portTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->port.disposition = 17;
#else
	OutP->port.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->port.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_get_special_port(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->node, In0P->which, &OutP->port.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(412, "host_get_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_set_special_port_t__defined)
#define __MIG_check__Request__host_set_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__host_set_special_port_t__which__defined
#if	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__int_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_set_special_port_t__which__defined */

#ifndef __NDR_convert__char_rep__Request__host_set_special_port_t__which__defined
#if	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__char_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_set_special_port_t__which__defined */

#ifndef __NDR_convert__float_rep__Request__host_set_special_port_t__which__defined
#if	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined
#define	__NDR_convert__float_rep__Request__host_set_special_port_t__which(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_set_special_port_t__which__defined */


mig_internal kern_return_t __MIG_check__Request__host_set_special_port_t(__Request__host_set_special_port_t *In0P)
{

	typedef __Request__host_set_special_port_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->port.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_set_special_port_t__which__defined)
		__NDR_convert__int_rep__Request__host_set_special_port_t__which(&In0P->which, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_set_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_set_special_port_t__which__defined)
		__NDR_convert__char_rep__Request__host_set_special_port_t__which(&In0P->which, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_set_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_set_special_port_t__which__defined)
		__NDR_convert__float_rep__Request__host_set_special_port_t__which(&In0P->which, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_set_special_port_t__which__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_set_special_port_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_set_special_port */
mig_internal novalue _Xhost_set_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int which;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_set_special_port_t __Request;
	typedef __Reply__host_set_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_set_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_set_special_port_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(413, "host_set_special_port")
	__BeforeRcvRpc(413, "host_set_special_port")

#if	defined(__MIG_check__Request__host_set_special_port_t__defined)
	check_result = __MIG_check__Request__host_set_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_set_special_port_t__defined) */

	OutP->RetCode = host_set_special_port(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->which, In0P->port.name);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(413, "host_set_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_set_exception_ports_t__defined)
#define __MIG_check__Request__host_set_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_set_exception_ports_t(__Request__host_set_exception_ports_t *In0P)
{

	typedef __Request__host_set_exception_ports_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_set_exception_ports_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_set_exception_ports */
mig_internal novalue _Xhost_set_exception_ports
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
	typedef __Request__host_set_exception_ports_t __Request;
	typedef __Reply__host_set_exception_ports_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_set_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_set_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(414, "host_set_exception_ports")
	__BeforeRcvRpc(414, "host_set_exception_ports")

#if	defined(__MIG_check__Request__host_set_exception_ports_t__defined)
	check_result = __MIG_check__Request__host_set_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_set_exception_ports_t__defined) */

	OutP->RetCode = host_set_exception_ports(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(414, "host_set_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_get_exception_ports_t__defined)
#define __MIG_check__Request__host_get_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined */


mig_internal kern_return_t __MIG_check__Request__host_get_exception_ports_t(__Request__host_get_exception_ports_t *In0P)
{

	typedef __Request__host_get_exception_ports_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_exception_ports_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_exception_ports */
mig_internal novalue _Xhost_get_exception_ports
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
	typedef __Request__host_get_exception_ports_t __Request;
	typedef __Reply__host_get_exception_ports_t Reply;

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

#ifdef	__MIG_check__Request__host_get_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_exception_ports_t__defined */

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
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlers[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(415, "host_get_exception_ports")
	__BeforeRcvRpc(415, "host_get_exception_ports")

#if	defined(__MIG_check__Request__host_get_exception_ports_t__defined)
	check_result = __MIG_check__Request__host_get_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_exception_ports_t__defined) */

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


	masksCnt = 32;

	RetCode = host_get_exception_ports(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->exception_mask, OutP->masks, &masksCnt, old_handlers, old_behaviors, old_flavors);
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
	__AfterRcvRpc(415, "host_get_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_swap_exception_ports_t__defined)
#define __MIG_check__Request__host_swap_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__host_priv__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__host_priv__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__host_priv__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__host_swap_exception_ports_t(__Request__host_swap_exception_ports_t *In0P)
{

	typedef __Request__host_swap_exception_ports_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__host_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__host_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_swap_exception_ports_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_swap_exception_ports */
mig_internal novalue _Xhost_swap_exception_ports
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
	typedef __Request__host_swap_exception_ports_t __Request;
	typedef __Reply__host_swap_exception_ports_t Reply;

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

#ifdef	__MIG_check__Request__host_swap_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_swap_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlerssTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t old_handlerssTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlerss[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(416, "host_swap_exception_ports")
	__BeforeRcvRpc(416, "host_swap_exception_ports")

#if	defined(__MIG_check__Request__host_swap_exception_ports_t__defined)
	check_result = __MIG_check__Request__host_swap_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_swap_exception_ports_t__defined) */

	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i;

	    ptr = &OutP->old_handlerss[0];
	    for (i = 0; i < 32; ptr++, i++) {
#if	UseStaticTemplates
		*ptr = old_handlerssTemplate;
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


	masksCnt = 32;

	RetCode = host_swap_exception_ports(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor, OutP->masks, &masksCnt, old_handlerss, old_behaviors, old_flavors);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	{
	    register	mach_msg_port_descriptor_t	*ptr;
	    register int	i, j;

	    ptr = &OutP->old_handlerss[0];
	    j = min(32, masksCnt);
	    for (i = 0; i < j; ptr++, i++) {
		ptr->name = old_handlerss[i];
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
	__AfterRcvRpc(416, "host_swap_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_load_symbol_table_t__defined)
#define __MIG_check__Request__host_load_symbol_table_t__defined
#ifndef __NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined
#if	defined(__NDR_convert__int_rep__host_priv__symtab_name_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__int_rep__host_priv__symtab_name_t((symtab_name_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__symtab_name_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__int_rep__symtab_name_t((symtab_name_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt(a, f) \
	__NDR_convert__int_rep__host_priv__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined */

#ifndef __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__int_rep__host_priv__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined */

#ifndef __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt(a, f) \
	__NDR_convert__int_rep__host_priv__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined
#define	__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined */

#ifndef __NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined
#if	defined(__NDR_convert__char_rep__host_priv__symtab_name_t__defined)
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__char_rep__host_priv__symtab_name_t((symtab_name_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__symtab_name_t__defined)
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__char_rep__symtab_name_t((symtab_name_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__char_rep__host_priv__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined */

#ifndef __NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined
#if	defined(__NDR_convert__float_rep__host_priv__symtab_name_t__defined)
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__float_rep__host_priv__symtab_name_t((symtab_name_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__symtab_name_t__defined)
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__name(a, f, c) \
	__NDR_convert__float_rep__symtab_name_t((symtab_name_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__float_rep__host_priv__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined
#define	__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab(a, f, c) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined */


mig_internal kern_return_t __MIG_check__Request__host_load_symbol_table_t(__Request__host_load_symbol_table_t *In0P, __Request__host_load_symbol_table_t **In1PP)
{

	typedef __Request__host_load_symbol_table_t __Request;
	__Request *In1P;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */
	unsigned int msgh_size_delta;

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 2) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 32)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request))
)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->task.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->task.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->symtab.type != MACH_MSG_OOL_DESCRIPTOR)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt(&In0P->nameCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined */
	msgh_size_delta = _WALIGN_(In0P->nameCnt);
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 32) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 32);

#if	defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__nameCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined) || \
	defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined)
		__NDR_convert__int_rep__Request__host_load_symbol_table_t__name(&In0P->name, In0P->NDR.int_rep, In0P->nameCnt);
#endif	/* __NDR_convert__int_rep__Request__host_load_symbol_table_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined)
		__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt(&In1P->symtabCnt, In1P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtabCnt__defined */
#if defined(__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined)
		__NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab((vm_offset_t)(In0P->symtab.address), In0P->NDR.int_rep, In1P->symtabCnt);
#endif	/* __NDR_convert__int_rep__Request__host_load_symbol_table_t__symtab__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined)
		__NDR_convert__char_rep__Request__host_load_symbol_table_t__name(&In0P->name, In0P->NDR.char_rep, In0P->nameCnt);
#endif	/* __NDR_convert__char_rep__Request__host_load_symbol_table_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined)
		__NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab((vm_offset_t)(In0P->symtab.address), In0P->NDR.char_rep, In1P->symtabCnt);
#endif	/* __NDR_convert__char_rep__Request__host_load_symbol_table_t__symtab__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined)
		__NDR_convert__float_rep__Request__host_load_symbol_table_t__name(&In0P->name, In0P->NDR.float_rep, In0P->nameCnt);
#endif	/* __NDR_convert__float_rep__Request__host_load_symbol_table_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined)
		__NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab((vm_offset_t)(In0P->symtab.address), In0P->NDR.float_rep, In1P->symtabCnt);
#endif	/* __NDR_convert__float_rep__Request__host_load_symbol_table_t__symtab__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_load_symbol_table_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_load_symbol_table */
mig_internal novalue _Xhost_load_symbol_table
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t task;
		mach_msg_ool_descriptor_t symtab;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[32];
		mach_msg_type_number_t symtabCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_load_symbol_table_t __Request;
	typedef __Reply__host_load_symbol_table_t Reply;

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
#ifdef	__MIG_check__Request__host_load_symbol_table_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_load_symbol_table_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(417, "host_load_symbol_table")
	__BeforeRcvRpc(417, "host_load_symbol_table")

#if	defined(__MIG_check__Request__host_load_symbol_table_t__defined)
	check_result = __MIG_check__Request__host_load_symbol_table_t((__Request *)In0P, (__Request **)&In1P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_load_symbol_table_t__defined) */

	task = convert_port_to_task(In0P->task.name);

	OutP->RetCode = host_load_symbol_table(convert_port_to_host_priv(In0P->Head.msgh_request_port), task, In0P->name, (vm_offset_t)(In0P->symtab.address), In1P->symtabCnt);
	task_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->task.name))
		ipc_port_release_send((ipc_port_t)In0P->task.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(417, "host_load_symbol_table")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__mach_vm_wire_t__defined)
#define __MIG_check__Request__mach_vm_wire_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined
#if	defined(__NDR_convert__int_rep__host_priv__mach_vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__int_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__host_priv__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined */

#ifndef __NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined
#if	defined(__NDR_convert__char_rep__host_priv__mach_vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined
#if	defined(__NDR_convert__char_rep__host_priv__mach_vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__char_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__host_priv__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined */

#ifndef __NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined
#if	defined(__NDR_convert__float_rep__host_priv__mach_vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__mach_vm_address_t((mach_vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined
#if	defined(__NDR_convert__float_rep__host_priv__mach_vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__mach_vm_size_t((mach_vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__host_priv__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#if	defined(__NDR_convert__float_rep__host_priv__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__host_priv__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__host_priv__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined
#define	__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined */


mig_internal kern_return_t __MIG_check__Request__mach_vm_wire_t(__Request__mach_vm_wire_t *In0P)
{

	typedef __Request__mach_vm_wire_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->task.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->task.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined)
		__NDR_convert__int_rep__Request__mach_vm_wire_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_vm_wire_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined)
		__NDR_convert__int_rep__Request__mach_vm_wire_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_vm_wire_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined)
		__NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined)
		__NDR_convert__char_rep__Request__mach_vm_wire_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_vm_wire_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined)
		__NDR_convert__char_rep__Request__mach_vm_wire_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_vm_wire_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined)
		__NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined)
		__NDR_convert__float_rep__Request__mach_vm_wire_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_vm_wire_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined)
		__NDR_convert__float_rep__Request__mach_vm_wire_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_vm_wire_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined)
		__NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access(&In0P->desired_access, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_vm_wire_t__desired_access__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_vm_wire_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_vm_wire */
mig_internal novalue _Xmach_vm_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_vm_address_t address;
		mach_vm_size_t size;
		vm_prot_t desired_access;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_vm_wire_t __Request;
	typedef __Reply__mach_vm_wire_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_vm_wire_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_vm_wire_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t task;

	__DeclareRcvRpc(418, "mach_vm_wire")
	__BeforeRcvRpc(418, "mach_vm_wire")

#if	defined(__MIG_check__Request__mach_vm_wire_t__defined)
	check_result = __MIG_check__Request__mach_vm_wire_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_vm_wire_t__defined) */

	task = convert_port_to_map(In0P->task.name);

	OutP->RetCode = mach_vm_wire(convert_port_to_host_priv(In0P->Head.msgh_request_port), task, In0P->address, In0P->size, In0P->desired_access);
	vm_map_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->task.name))
		ipc_port_release_send((ipc_port_t)In0P->task.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(418, "mach_vm_wire")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_processor_sets_t__defined)
#define __MIG_check__Request__host_processor_sets_t__defined

mig_internal kern_return_t __MIG_check__Request__host_processor_sets_t(__Request__host_processor_sets_t *In0P)
{

	typedef __Request__host_processor_sets_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_processor_sets_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_processor_sets */
mig_internal novalue _Xhost_processor_sets
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
	typedef __Request__host_processor_sets_t __Request;
	typedef __Reply__host_processor_sets_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_processor_sets_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_processor_sets_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t processor_setsTemplate = {
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
	const static mach_msg_ool_ports_descriptor_t processor_setsTemplate = {
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
	__DeclareRcvRpc(419, "host_processor_sets")
	__BeforeRcvRpc(419, "host_processor_sets")

#if	defined(__MIG_check__Request__host_processor_sets_t__defined)
	check_result = __MIG_check__Request__host_processor_sets_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_processor_sets_t__defined) */

#if	UseStaticTemplates
	OutP->processor_sets = processor_setsTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->processor_sets.disposition = 17;
#else
	OutP->processor_sets.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->processor_sets.deallocate =  FALSE;
	OutP->processor_sets.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_processor_sets(convert_port_to_host_priv(In0P->Head.msgh_request_port), (processor_set_name_array_t *)&(OutP->processor_sets.address), &OutP->processor_setsCnt);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->processor_sets.count = OutP->processor_setsCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(419, "host_processor_sets")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_processor_set_priv_t__defined)
#define __MIG_check__Request__host_processor_set_priv_t__defined

mig_internal kern_return_t __MIG_check__Request__host_processor_set_priv_t(__Request__host_processor_set_priv_t *In0P)
{

	typedef __Request__host_processor_set_priv_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->set_name.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->set_name.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_processor_set_priv_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_processor_set_priv */
mig_internal novalue _Xhost_processor_set_priv
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t set_name;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_processor_set_priv_t __Request;
	typedef __Reply__host_processor_set_priv_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_processor_set_priv_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_processor_set_priv_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t setTemplate = {
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
	processor_set_t set;

	__DeclareRcvRpc(420, "host_processor_set_priv")
	__BeforeRcvRpc(420, "host_processor_set_priv")

#if	defined(__MIG_check__Request__host_processor_set_priv_t__defined)
	check_result = __MIG_check__Request__host_processor_set_priv_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_processor_set_priv_t__defined) */

#if	UseStaticTemplates
	OutP->set = setTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->set.disposition = 17;
#else
	OutP->set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->set.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	set_name = convert_port_to_pset_name(In0P->set_name.name);

	RetCode = host_processor_set_priv(convert_port_to_host_priv(In0P->Head.msgh_request_port), set_name, &set);
	pset_deallocate(set_name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->set_name.name))
		ipc_port_release_send((ipc_port_t)In0P->set_name.name);
#endif /* __MigKernelSpecificCode */
	OutP->set.name = (mach_port_t)convert_pset_to_port(set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(420, "host_processor_set_priv")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__set_dp_control_port_t__defined)
#define __MIG_check__Request__set_dp_control_port_t__defined

mig_internal kern_return_t __MIG_check__Request__set_dp_control_port_t(__Request__set_dp_control_port_t *In0P)
{

	typedef __Request__set_dp_control_port_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->control_port.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->control_port.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__set_dp_control_port_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine set_dp_control_port */
mig_internal novalue _Xset_dp_control_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t control_port;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__set_dp_control_port_t __Request;
	typedef __Reply__set_dp_control_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__set_dp_control_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__set_dp_control_port_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(421, "set_dp_control_port")
	__BeforeRcvRpc(421, "set_dp_control_port")

#if	defined(__MIG_check__Request__set_dp_control_port_t__defined)
	check_result = __MIG_check__Request__set_dp_control_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__set_dp_control_port_t__defined) */

	OutP->RetCode = set_dp_control_port(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->control_port.name);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(421, "set_dp_control_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__get_dp_control_port_t__defined)
#define __MIG_check__Request__get_dp_control_port_t__defined

mig_internal kern_return_t __MIG_check__Request__get_dp_control_port_t(__Request__get_dp_control_port_t *In0P)
{

	typedef __Request__get_dp_control_port_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__get_dp_control_port_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine get_dp_control_port */
mig_internal novalue _Xget_dp_control_port
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
	typedef __Request__get_dp_control_port_t __Request;
	typedef __Reply__get_dp_control_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__get_dp_control_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__get_dp_control_port_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t contorl_portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t contorl_portTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(422, "get_dp_control_port")
	__BeforeRcvRpc(422, "get_dp_control_port")

#if	defined(__MIG_check__Request__get_dp_control_port_t__defined)
	check_result = __MIG_check__Request__get_dp_control_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__get_dp_control_port_t__defined) */

#if	UseStaticTemplates
	OutP->contorl_port = contorl_portTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->contorl_port.disposition = 17;
#else
	OutP->contorl_port.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->contorl_port.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = get_dp_control_port(convert_port_to_host_priv(In0P->Head.msgh_request_port), &OutP->contorl_port.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(422, "get_dp_control_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_set_UNDServer_t__defined)
#define __MIG_check__Request__host_set_UNDServer_t__defined

mig_internal kern_return_t __MIG_check__Request__host_set_UNDServer_t(__Request__host_set_UNDServer_t *In0P)
{

	typedef __Request__host_set_UNDServer_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->server.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->server.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_set_UNDServer_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_set_UNDServer */
mig_internal novalue _Xhost_set_UNDServer
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t server;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__host_set_UNDServer_t __Request;
	typedef __Reply__host_set_UNDServer_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_set_UNDServer_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_set_UNDServer_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	__DeclareRcvRpc(423, "host_set_UNDServer")
	__BeforeRcvRpc(423, "host_set_UNDServer")

#if	defined(__MIG_check__Request__host_set_UNDServer_t__defined)
	check_result = __MIG_check__Request__host_set_UNDServer_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_set_UNDServer_t__defined) */

	OutP->RetCode = host_set_UNDServer(convert_port_to_host_priv(In0P->Head.msgh_request_port), In0P->server.name);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(423, "host_set_UNDServer")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__host_priv_subsystem__
#if !defined(__MIG_check__Request__host_get_UNDServer_t__defined)
#define __MIG_check__Request__host_get_UNDServer_t__defined

mig_internal kern_return_t __MIG_check__Request__host_get_UNDServer_t(__Request__host_get_UNDServer_t *In0P)
{

	typedef __Request__host_get_UNDServer_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__host_get_UNDServer_t__defined) */
#endif /* __MIG_check__Request__host_priv_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine host_get_UNDServer */
mig_internal novalue _Xhost_get_UNDServer
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
	typedef __Request__host_get_UNDServer_t __Request;
	typedef __Reply__host_get_UNDServer_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__host_get_UNDServer_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__host_get_UNDServer_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t serverTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t serverTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	__DeclareRcvRpc(424, "host_get_UNDServer")
	__BeforeRcvRpc(424, "host_get_UNDServer")

#if	defined(__MIG_check__Request__host_get_UNDServer_t__defined)
	check_result = __MIG_check__Request__host_get_UNDServer_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__host_get_UNDServer_t__defined) */

#if	UseStaticTemplates
	OutP->server = serverTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->server.disposition = 17;
#else
	OutP->server.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->server.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	RetCode = host_get_UNDServer(convert_port_to_host_priv(In0P->Head.msgh_request_port), &OutP->server.name);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(424, "host_get_UNDServer")
}



/* Description of this subsystem, for use in direct RPC */
const struct host_priv_subsystem host_priv_subsystem = {
	host_priv_server_routine,
	400,
	425,
	(mach_msg_size_t)sizeof(union __ReplyUnion__host_priv_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_boot_info, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_boot_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_reboot, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_reboot_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_priv_statistics, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_priv_statistics_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_default_memory_manager, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_default_memory_manager_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_wire, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_wire_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_wire, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_wire_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_allocate_cpm, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_allocate_cpm_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_processors, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_processors_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_clock_control, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_clock_control_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xkmod_create, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__kmod_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xkmod_destroy, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__kmod_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xkmod_control, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__kmod_control_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_special_port, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_set_special_port, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_set_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_set_exception_ports, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_set_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_exception_ports, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_swap_exception_ports, 10, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_swap_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_load_symbol_table, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_load_symbol_table_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_vm_wire, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_vm_wire_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_processor_sets, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_processor_sets_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_processor_set_priv, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_processor_set_priv_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xset_dp_control_port, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__set_dp_control_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xget_dp_control_port, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__get_dp_control_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_set_UNDServer, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_set_UNDServer_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xhost_get_UNDServer, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__host_get_UNDServer_t)},
	}
};

mig_external boolean_t host_priv_server
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

	if ((InHeadP->msgh_id > 424) || (InHeadP->msgh_id < 400) ||
	    ((routine = host_priv_subsystem.routine[InHeadP->msgh_id - 400].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t host_priv_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 400;

	if ((msgh_id > 24) || (msgh_id < 0))
		return 0;

	return host_priv_subsystem.routine[msgh_id].stub_routine;
}

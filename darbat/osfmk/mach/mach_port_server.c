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
 *	KernelServer
 */

/* Module mach_port */

#define	__MIG_check__Request__mach_port_subsystem__ 1
#define	__NDR_convert__Request__mach_port_subsystem__ 1

#include "mach_port_server.h"

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


mig_internal novalue _Xmach_port_names
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_type
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_rename
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_allocate_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_allocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_deallocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_get_refs
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_mod_refs
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_set_mscount
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_get_set_status
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_move_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_request_notification
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_insert_right
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_extract_right
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_set_seqno
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_set_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_allocate_qos
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_allocate_full
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_port_space
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_get_srights
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_space_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_dnrequest_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_kernel_object
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_insert_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_port_extract_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_names_t__defined)
#define __MIG_check__Request__mach_port_names_t__defined

mig_internal kern_return_t __MIG_check__Request__mach_port_names_t(__Request__mach_port_names_t *In0P)
{

	typedef __Request__mach_port_names_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_names_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_names */
mig_internal novalue _Xmach_port_names
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
	typedef __Request__mach_port_names_t __Request;
	typedef __Reply__mach_port_names_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_names_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_names_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t namesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t typesTemplate = {
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
	const static mach_msg_ool_descriptor_t namesTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		FALSE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t typesTemplate = {
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
	ipc_space_t task;

	__DeclareRcvRpc(3200, "mach_port_names")
	__BeforeRcvRpc(3200, "mach_port_names")

#if	defined(__MIG_check__Request__mach_port_names_t__defined)
	check_result = __MIG_check__Request__mach_port_names_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_names_t__defined) */

#if	UseStaticTemplates
	OutP->names = namesTemplate;
#else	/* UseStaticTemplates */
	OutP->names.deallocate =  FALSE;
	OutP->names.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->names.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


#if	UseStaticTemplates
	OutP->types = typesTemplate;
#else	/* UseStaticTemplates */
	OutP->types.deallocate =  FALSE;
	OutP->types.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->types.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->namesCnt = 0;

	OutP->typesCnt = 0;

	RetCode = mach_port_names(task, (mach_port_name_array_t *)&(OutP->names.address), &OutP->namesCnt, (mach_port_type_array_t *)&(OutP->types.address), &OutP->typesCnt);
	space_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->names.size = OutP->namesCnt * 4;

	OutP->types.size = OutP->typesCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 2;
	__AfterRcvRpc(3200, "mach_port_names")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_type_t__defined)
#define __MIG_check__Request__mach_port_type_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_type_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_type_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_type_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_type_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_type_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_type_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_type_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_type_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_type_t(__Request__mach_port_type_t *In0P)
{

	typedef __Request__mach_port_type_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_type_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_type_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_type_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_type_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_type_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_type_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_type_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_type_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_type_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_type_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_type_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_type_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_type_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_type */
mig_internal novalue _Xmach_port_type
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
	typedef __Request__mach_port_type_t __Request;
	typedef __Reply__mach_port_type_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_type_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_type_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3201, "mach_port_type")
	__BeforeRcvRpc(3201, "mach_port_type")

#if	defined(__MIG_check__Request__mach_port_type_t__defined)
	check_result = __MIG_check__Request__mach_port_type_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_type_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_type(task, In0P->name, &OutP->ptype);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3201, "mach_port_type")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_rename_t__defined)
#define __MIG_check__Request__mach_port_rename_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__old_name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_rename_t__new_name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_rename_t(__Request__mach_port_rename_t *In0P)
{

	typedef __Request__mach_port_rename_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined)
		__NDR_convert__int_rep__Request__mach_port_rename_t__old_name(&In0P->old_name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_rename_t__old_name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined)
		__NDR_convert__int_rep__Request__mach_port_rename_t__new_name(&In0P->new_name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_rename_t__new_name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined)
		__NDR_convert__char_rep__Request__mach_port_rename_t__old_name(&In0P->old_name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_rename_t__old_name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined)
		__NDR_convert__char_rep__Request__mach_port_rename_t__new_name(&In0P->new_name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_rename_t__new_name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined)
		__NDR_convert__float_rep__Request__mach_port_rename_t__old_name(&In0P->old_name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_rename_t__old_name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined)
		__NDR_convert__float_rep__Request__mach_port_rename_t__new_name(&In0P->new_name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_rename_t__new_name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_rename_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_rename */
mig_internal novalue _Xmach_port_rename
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t old_name;
		mach_port_name_t new_name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_rename_t __Request;
	typedef __Reply__mach_port_rename_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_rename_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_rename_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3202, "mach_port_rename")
	__BeforeRcvRpc(3202, "mach_port_rename")

#if	defined(__MIG_check__Request__mach_port_rename_t__defined)
	check_result = __MIG_check__Request__mach_port_rename_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_rename_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_rename(task, In0P->old_name, In0P->new_name);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3202, "mach_port_rename")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_allocate_name_t__defined)
#define __MIG_check__Request__mach_port_allocate_name_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_allocate_name_t(__Request__mach_port_allocate_name_t *In0P)
{

	typedef __Request__mach_port_allocate_name_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_name_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_name_t__right__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_name_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_name_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_name_t__right__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_name_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_name_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_name_t__right__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_name_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_name_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_allocate_name_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_allocate_name */
mig_internal novalue _Xmach_port_allocate_name
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_right_t right;
		mach_port_name_t name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_allocate_name_t __Request;
	typedef __Reply__mach_port_allocate_name_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_allocate_name_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_allocate_name_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3203, "mach_port_allocate_name")
	__BeforeRcvRpc(3203, "mach_port_allocate_name")

#if	defined(__MIG_check__Request__mach_port_allocate_name_t__defined)
	check_result = __MIG_check__Request__mach_port_allocate_name_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_allocate_name_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_allocate_name(task, In0P->right, In0P->name);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3203, "mach_port_allocate_name")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_allocate_t__defined)
#define __MIG_check__Request__mach_port_allocate_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_allocate_t(__Request__mach_port_allocate_t *In0P)
{

	typedef __Request__mach_port_allocate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_t__right__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_t__right__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_t__right__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_allocate_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_allocate */
mig_internal novalue _Xmach_port_allocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_right_t right;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_allocate_t __Request;
	typedef __Reply__mach_port_allocate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_allocate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_allocate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3204, "mach_port_allocate")
	__BeforeRcvRpc(3204, "mach_port_allocate")

#if	defined(__MIG_check__Request__mach_port_allocate_t__defined)
	check_result = __MIG_check__Request__mach_port_allocate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_allocate_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_allocate(task, In0P->right, &OutP->name);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3204, "mach_port_allocate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_destroy_t__defined)
#define __MIG_check__Request__mach_port_destroy_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_destroy_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_destroy_t(__Request__mach_port_destroy_t *In0P)
{

	typedef __Request__mach_port_destroy_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_destroy_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_destroy_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_destroy_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_destroy_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_destroy_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_destroy_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_destroy_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_destroy */
mig_internal novalue _Xmach_port_destroy
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
	typedef __Request__mach_port_destroy_t __Request;
	typedef __Reply__mach_port_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3205, "mach_port_destroy")
	__BeforeRcvRpc(3205, "mach_port_destroy")

#if	defined(__MIG_check__Request__mach_port_destroy_t__defined)
	check_result = __MIG_check__Request__mach_port_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_destroy_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_destroy(task, In0P->name);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3205, "mach_port_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_deallocate_t__defined)
#define __MIG_check__Request__mach_port_deallocate_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_deallocate_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_deallocate_t(__Request__mach_port_deallocate_t *In0P)
{

	typedef __Request__mach_port_deallocate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_deallocate_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_deallocate_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_deallocate_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_deallocate_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_deallocate_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_deallocate_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_deallocate_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_deallocate */
mig_internal novalue _Xmach_port_deallocate
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
	typedef __Request__mach_port_deallocate_t __Request;
	typedef __Reply__mach_port_deallocate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_deallocate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_deallocate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3206, "mach_port_deallocate")
	__BeforeRcvRpc(3206, "mach_port_deallocate")

#if	defined(__MIG_check__Request__mach_port_deallocate_t__defined)
	check_result = __MIG_check__Request__mach_port_deallocate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
	{ 
		MIG_RETURN_ERROR(OutP, check_result); 
	}
#endif	/* defined(__MIG_check__Request__mach_port_deallocate_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_deallocate(task, In0P->name);
	space_deallocate(task);
	
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3206, "mach_port_deallocate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_get_refs_t__defined)
#define __MIG_check__Request__mach_port_get_refs_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_get_refs_t(__Request__mach_port_get_refs_t *In0P)
{

	typedef __Request__mach_port_get_refs_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_get_refs_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_refs_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_get_refs_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_refs_t__right__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_get_refs_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_refs_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_get_refs_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_refs_t__right__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_get_refs_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_refs_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_get_refs_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_refs_t__right__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_get_refs_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_get_refs */
mig_internal novalue _Xmach_port_get_refs
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_right_t right;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_get_refs_t __Request;
	typedef __Reply__mach_port_get_refs_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_get_refs_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_get_refs_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3207, "mach_port_get_refs")
	__BeforeRcvRpc(3207, "mach_port_get_refs")

#if	defined(__MIG_check__Request__mach_port_get_refs_t__defined)
	check_result = __MIG_check__Request__mach_port_get_refs_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_get_refs_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_get_refs(task, In0P->name, In0P->right, &OutP->refs);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3207, "mach_port_get_refs")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_mod_refs_t__defined)
#define __MIG_check__Request__mach_port_mod_refs_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_delta_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_delta_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_delta_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_delta_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_delta_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_delta_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__mach_port_delta_t((mach_port_delta_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined
#define	__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_mod_refs_t(__Request__mach_port_mod_refs_t *In0P)
{

	typedef __Request__mach_port_mod_refs_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_mod_refs_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_mod_refs_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__right__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined)
		__NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta(&In0P->delta, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_mod_refs_t__delta__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_mod_refs_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_mod_refs_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__right__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined)
		__NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta(&In0P->delta, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_mod_refs_t__delta__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_mod_refs_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_mod_refs_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__right__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined)
		__NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta(&In0P->delta, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_mod_refs_t__delta__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_mod_refs_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_mod_refs */
mig_internal novalue _Xmach_port_mod_refs
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_right_t right;
		mach_port_delta_t delta;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_mod_refs_t __Request;
	typedef __Reply__mach_port_mod_refs_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_mod_refs_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_mod_refs_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3208, "mach_port_mod_refs")
	__BeforeRcvRpc(3208, "mach_port_mod_refs")

#if	defined(__MIG_check__Request__mach_port_mod_refs_t__defined)
	check_result = __MIG_check__Request__mach_port_mod_refs_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_mod_refs_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_mod_refs(task, In0P->name, In0P->right, In0P->delta);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3208, "mach_port_mod_refs")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_set_mscount_t__defined)
#define __MIG_check__Request__mach_port_set_mscount_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_set_mscount_t(__Request__mach_port_set_mscount_t *In0P)
{

	typedef __Request__mach_port_set_mscount_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_set_mscount_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_mscount_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined)
		__NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount(&In0P->mscount, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_mscount_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_set_mscount_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_mscount_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined)
		__NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount(&In0P->mscount, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_mscount_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_set_mscount_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_mscount_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined)
		__NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount(&In0P->mscount, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_mscount_t__mscount__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_set_mscount_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_set_mscount */
mig_internal novalue _Xmach_port_set_mscount
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_mscount_t mscount;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_set_mscount_t __Request;
	typedef __Reply__mach_port_set_mscount_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_set_mscount_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_set_mscount_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3210, "mach_port_set_mscount")
	__BeforeRcvRpc(3210, "mach_port_set_mscount")

#if	defined(__MIG_check__Request__mach_port_set_mscount_t__defined)
	check_result = __MIG_check__Request__mach_port_set_mscount_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_set_mscount_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_set_mscount(task, In0P->name, In0P->mscount);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3210, "mach_port_set_mscount")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_get_set_status_t__defined)
#define __MIG_check__Request__mach_port_get_set_status_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_get_set_status_t(__Request__mach_port_get_set_status_t *In0P)
{

	typedef __Request__mach_port_get_set_status_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_get_set_status_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_set_status_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_get_set_status_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_set_status_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_get_set_status_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_set_status_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_get_set_status_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_get_set_status */
mig_internal novalue _Xmach_port_get_set_status
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
	typedef __Request__mach_port_get_set_status_t __Request;
	typedef __Reply__mach_port_get_set_status_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_get_set_status_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_get_set_status_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t membersTemplate = {
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
	const static mach_msg_ool_descriptor_t membersTemplate = {
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
	ipc_space_t task;

	__DeclareRcvRpc(3211, "mach_port_get_set_status")
	__BeforeRcvRpc(3211, "mach_port_get_set_status")

#if	defined(__MIG_check__Request__mach_port_get_set_status_t__defined)
	check_result = __MIG_check__Request__mach_port_get_set_status_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_get_set_status_t__defined) */

#if	UseStaticTemplates
	OutP->members = membersTemplate;
#else	/* UseStaticTemplates */
	OutP->members.deallocate =  FALSE;
	OutP->members.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->members.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->membersCnt = 0;

	RetCode = mach_port_get_set_status(task, In0P->name, (mach_port_name_array_t *)&(OutP->members.address), &OutP->membersCnt);
	space_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->members.size = OutP->membersCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3211, "mach_port_get_set_status")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_move_member_t__defined)
#define __MIG_check__Request__mach_port_move_member_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__int_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__char_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__member(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined
#define	__NDR_convert__float_rep__Request__mach_port_move_member_t__after(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_move_member_t(__Request__mach_port_move_member_t *In0P)
{

	typedef __Request__mach_port_move_member_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined)
		__NDR_convert__int_rep__Request__mach_port_move_member_t__member(&In0P->member, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_move_member_t__member__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined)
		__NDR_convert__int_rep__Request__mach_port_move_member_t__after(&In0P->after, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_move_member_t__after__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined)
		__NDR_convert__char_rep__Request__mach_port_move_member_t__member(&In0P->member, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_move_member_t__member__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined)
		__NDR_convert__char_rep__Request__mach_port_move_member_t__after(&In0P->after, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_move_member_t__after__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined)
		__NDR_convert__float_rep__Request__mach_port_move_member_t__member(&In0P->member, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_move_member_t__member__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined)
		__NDR_convert__float_rep__Request__mach_port_move_member_t__after(&In0P->after, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_move_member_t__after__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_move_member_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_move_member */
mig_internal novalue _Xmach_port_move_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t member;
		mach_port_name_t after;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_move_member_t __Request;
	typedef __Reply__mach_port_move_member_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_move_member_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_move_member_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3212, "mach_port_move_member")
	__BeforeRcvRpc(3212, "mach_port_move_member")

#if	defined(__MIG_check__Request__mach_port_move_member_t__defined)
	check_result = __MIG_check__Request__mach_port_move_member_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_move_member_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_move_member(task, In0P->member, In0P->after);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3212, "mach_port_move_member")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_request_notification_t__defined)
#define __MIG_check__Request__mach_port_request_notification_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_msg_id_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__mach_port__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_id_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_msg_id_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__mach_port__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_msg_id_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_msg_id_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__mach_port__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_msg_id_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__mach_msg_id_t((mach_msg_id_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__mach_port__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__integer_t((integer_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_mscount_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__mach_port_mscount_t((mach_port_mscount_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined
#define	__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_request_notification_t(__Request__mach_port_request_notification_t *In0P)
{

	typedef __Request__mach_port_request_notification_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->notify.type != MACH_MSG_PORT_DESCRIPTOR || (
	    In0P->notify.disposition != MACH_MSG_TYPE_MOVE_SEND_ONCE &&  
	    In0P->notify.disposition != MACH_MSG_TYPE_MAKE_SEND_ONCE))
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_request_notification_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_request_notification_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined)
		__NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid(&In0P->msgid, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_request_notification_t__msgid__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined)
		__NDR_convert__int_rep__Request__mach_port_request_notification_t__sync(&In0P->sync, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_request_notification_t__sync__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_request_notification_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_request_notification_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined)
		__NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid(&In0P->msgid, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_request_notification_t__msgid__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined)
		__NDR_convert__char_rep__Request__mach_port_request_notification_t__sync(&In0P->sync, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_request_notification_t__sync__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_request_notification_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_request_notification_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined)
		__NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid(&In0P->msgid, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_request_notification_t__msgid__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined)
		__NDR_convert__float_rep__Request__mach_port_request_notification_t__sync(&In0P->sync, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_request_notification_t__sync__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_request_notification_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_request_notification */
mig_internal novalue _Xmach_port_request_notification
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t notify;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_msg_id_t msgid;
		mach_port_mscount_t sync;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_request_notification_t __Request;
	typedef __Reply__mach_port_request_notification_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_request_notification_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_request_notification_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t previousTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		18,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t previousTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		18,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	ipc_space_t task;

	__DeclareRcvRpc(3213, "mach_port_request_notification")
	__BeforeRcvRpc(3213, "mach_port_request_notification")

#if	defined(__MIG_check__Request__mach_port_request_notification_t__defined)
	check_result = __MIG_check__Request__mach_port_request_notification_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_request_notification_t__defined) */

#if	UseStaticTemplates
	OutP->previous = previousTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->previous.disposition = 18;
#else
	OutP->previous.disposition = 18;
#endif /* __MigKernelSpecificCode */
	OutP->previous.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_space(In0P->Head.msgh_request_port);

	RetCode = mach_port_request_notification(task, In0P->name, In0P->msgid, In0P->sync, In0P->notify.name, &OutP->previous.name);
	space_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3213, "mach_port_request_notification")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_insert_right_t__defined)
#define __MIG_check__Request__mach_port_insert_right_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_right_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_insert_right_t(__Request__mach_port_insert_right_t *In0P)
{

	typedef __Request__mach_port_insert_right_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->poly.type != MACH_MSG_PORT_DESCRIPTOR)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_insert_right_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_insert_right_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_insert_right_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_insert_right_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_insert_right_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_insert_right_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_insert_right_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_insert_right */
mig_internal novalue _Xmach_port_insert_right
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t poly;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_insert_right_t __Request;
	typedef __Reply__mach_port_insert_right_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_insert_right_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_insert_right_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3214, "mach_port_insert_right")
	__BeforeRcvRpc(3214, "mach_port_insert_right")

#if	defined(__MIG_check__Request__mach_port_insert_right_t__defined)
	check_result = __MIG_check__Request__mach_port_insert_right_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_insert_right_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_insert_right(task, In0P->name, In0P->poly.name, In0P->poly.disposition);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3214, "mach_port_insert_right")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_extract_right_t__defined)
#define __MIG_check__Request__mach_port_extract_right_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_msg_type_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__unsigned__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_msg_type_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_msg_type_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__unsigned__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_msg_type_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_msg_type_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__mach_msg_type_name_t((mach_msg_type_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__mach_port__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__unsigned__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__unsigned((unsigned *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_extract_right_t(__Request__mach_port_extract_right_t *In0P)
{

	typedef __Request__mach_port_extract_right_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_extract_right_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_extract_right_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined)
		__NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name(&In0P->msgt_name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_extract_right_t__msgt_name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_extract_right_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_extract_right_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined)
		__NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name(&In0P->msgt_name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_extract_right_t__msgt_name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_extract_right_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_extract_right_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined)
		__NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name(&In0P->msgt_name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_extract_right_t__msgt_name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_extract_right_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_extract_right */
mig_internal novalue _Xmach_port_extract_right
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_msg_type_name_t msgt_name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_extract_right_t __Request;
	typedef __Reply__mach_port_extract_right_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_extract_right_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_extract_right_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t polyTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		((mach_msg_type_name_t) -1),
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t polyTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		((mach_msg_type_name_t) -1),
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	ipc_space_t task;
	mach_msg_type_name_t polyPoly;

	__DeclareRcvRpc(3215, "mach_port_extract_right")
	__BeforeRcvRpc(3215, "mach_port_extract_right")

#if	defined(__MIG_check__Request__mach_port_extract_right_t__defined)
	check_result = __MIG_check__Request__mach_port_extract_right_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_extract_right_t__defined) */

#if	UseStaticTemplates
	OutP->poly = polyTemplate;
#else	/* UseStaticTemplates */
	OutP->poly.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_space(In0P->Head.msgh_request_port);

	RetCode = mach_port_extract_right(task, In0P->name, In0P->msgt_name, &OutP->poly.name, &polyPoly);
	space_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->poly.disposition = polyPoly;

#if	__MigKernelSpecificCode
	if (polyPoly == MACH_MSG_TYPE_PORT_RECEIVE)
	  if (IP_VALID((ipc_port_t) In0P->Head.msgh_reply_port) &&
	    IP_VALID((ipc_port_t) OutP->poly.name) &&
	    ipc_port_check_circularity((ipc_port_t) OutP->poly.name, (ipc_port_t) In0P->Head.msgh_reply_port))
		OutP->Head.msgh_bits |= MACH_MSGH_BITS_CIRCULAR;
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3215, "mach_port_extract_right")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_set_seqno_t__defined)
#define __MIG_check__Request__mach_port_set_seqno_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_seqno_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_seqno_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_seqno_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_seqno_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_seqno_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_seqno_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__mach_port_seqno_t((mach_port_seqno_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_set_seqno_t(__Request__mach_port_set_seqno_t *In0P)
{

	typedef __Request__mach_port_set_seqno_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_set_seqno_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_seqno_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined)
		__NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno(&In0P->seqno, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_seqno_t__seqno__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_set_seqno_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_seqno_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined)
		__NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno(&In0P->seqno, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_seqno_t__seqno__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_set_seqno_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_seqno_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined)
		__NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno(&In0P->seqno, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_seqno_t__seqno__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_set_seqno_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_set_seqno */
mig_internal novalue _Xmach_port_set_seqno
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_seqno_t seqno;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_set_seqno_t __Request;
	typedef __Reply__mach_port_set_seqno_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_set_seqno_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_set_seqno_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3216, "mach_port_set_seqno")
	__BeforeRcvRpc(3216, "mach_port_set_seqno")

#if	defined(__MIG_check__Request__mach_port_set_seqno_t__defined)
	check_result = __MIG_check__Request__mach_port_set_seqno_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_set_seqno_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_set_seqno(task, In0P->name, In0P->seqno);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3216, "mach_port_set_seqno")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_get_attributes_t__defined)
#define __MIG_check__Request__mach_port_get_attributes_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_port__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_get_attributes_t(__Request__mach_port_get_attributes_t *In0P)
{

	typedef __Request__mach_port_get_attributes_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_get_attributes_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined)
		__NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined)
		__NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt(&In0P->port_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_attributes_t__port_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_get_attributes_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_attributes_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined)
		__NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_get_attributes_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_attributes_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined)
		__NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_attributes_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_get_attributes_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_get_attributes */
mig_internal novalue _Xmach_port_get_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_flavor_t flavor;
		mach_msg_type_number_t port_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_get_attributes_t __Request;
	typedef __Reply__mach_port_get_attributes_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_get_attributes_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_get_attributes_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3217, "mach_port_get_attributes")
	__BeforeRcvRpc(3217, "mach_port_get_attributes")

#if	defined(__MIG_check__Request__mach_port_get_attributes_t__defined)
	check_result = __MIG_check__Request__mach_port_get_attributes_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_get_attributes_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->port_info_outCnt = 10;
	if (In0P->port_info_outCnt < OutP->port_info_outCnt)
		OutP->port_info_outCnt = In0P->port_info_outCnt;

	OutP->RetCode = mach_port_get_attributes(task, In0P->name, In0P->flavor, OutP->port_info_out, &OutP->port_info_outCnt);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 40) + (((4 * OutP->port_info_outCnt)));

	__AfterRcvRpc(3217, "mach_port_get_attributes")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_set_attributes_t__defined)
#define __MIG_check__Request__mach_port_set_attributes_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_info_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__int_rep__mach_port__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__mach_port_info_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__int_rep__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__mach_port__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_port__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined
#define	__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_info_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__char_rep__mach_port__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__mach_port_info_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__char_rep__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__mach_port__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port_flavor_t((mach_port_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_info_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__float_rep__mach_port__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__mach_port_info_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__float_rep__mach_port_info_t((mach_port_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__mach_port__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined
#define	__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_set_attributes_t(__Request__mach_port_set_attributes_t *In0P)
{

	typedef __Request__mach_port_set_attributes_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 40)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt(&In0P->port_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 40) + ((4 * In0P->port_infoCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_set_attributes_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined)
		__NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined)
		__NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info(&In0P->port_info, In0P->NDR.int_rep, In0P->port_infoCnt);
#endif	/* __NDR_convert__int_rep__Request__mach_port_set_attributes_t__port_info__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_set_attributes_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined)
		__NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined)
		__NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info(&In0P->port_info, In0P->NDR.char_rep, In0P->port_infoCnt);
#endif	/* __NDR_convert__char_rep__Request__mach_port_set_attributes_t__port_info__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_set_attributes_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined)
		__NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined)
		__NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info(&In0P->port_info, In0P->NDR.float_rep, In0P->port_infoCnt);
#endif	/* __NDR_convert__float_rep__Request__mach_port_set_attributes_t__port_info__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_set_attributes_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_set_attributes */
mig_internal novalue _Xmach_port_set_attributes
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_flavor_t flavor;
		mach_msg_type_number_t port_infoCnt;
		integer_t port_info[10];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_set_attributes_t __Request;
	typedef __Reply__mach_port_set_attributes_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_set_attributes_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_set_attributes_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3218, "mach_port_set_attributes")
	__BeforeRcvRpc(3218, "mach_port_set_attributes")

#if	defined(__MIG_check__Request__mach_port_set_attributes_t__defined)
	check_result = __MIG_check__Request__mach_port_set_attributes_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_set_attributes_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_set_attributes(task, In0P->name, In0P->flavor, In0P->port_info, In0P->port_infoCnt);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3218, "mach_port_set_attributes")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_allocate_qos_t__defined)
#define __MIG_check__Request__mach_port_allocate_qos_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_qos_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__int_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__int_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_qos_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__char_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__char_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_qos_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__float_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__float_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_allocate_qos_t(__Request__mach_port_allocate_qos_t *In0P)
{

	typedef __Request__mach_port_allocate_qos_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__right__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos(&In0P->qos, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_qos_t__qos__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__right__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos(&In0P->qos, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_qos_t__qos__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__right__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos(&In0P->qos, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_qos_t__qos__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_allocate_qos_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_allocate_qos */
mig_internal novalue _Xmach_port_allocate_qos
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_right_t right;
		mach_port_qos_t qos;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_allocate_qos_t __Request;
	typedef __Reply__mach_port_allocate_qos_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_allocate_qos_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_allocate_qos_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3219, "mach_port_allocate_qos")
	__BeforeRcvRpc(3219, "mach_port_allocate_qos")

#if	defined(__MIG_check__Request__mach_port_allocate_qos_t__defined)
	check_result = __MIG_check__Request__mach_port_allocate_qos_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_allocate_qos_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_allocate_qos(task, In0P->right, &In0P->qos, &OutP->name);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->qos = In0P->qos;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3219, "mach_port_allocate_qos")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_allocate_full_t__defined)
#define __MIG_check__Request__mach_port_allocate_full_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_right_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_qos_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__int_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__int_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_right_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_qos_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__char_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__char_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_right_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__mach_port_right_t((mach_port_right_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__mach_port__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_qos_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_qos_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__float_rep__mach_port_qos_t((mach_port_qos_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__float_rep__mach_port__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((integer_t *)(a), f, 2, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__mach_port__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(a, f) \
	__NDR_convert__ARRAY((int32_t *)(a), f, 2, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_allocate_full_t(__Request__mach_port_allocate_full_t *In0P)
{

	typedef __Request__mach_port_allocate_full_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->proto.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->proto.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_full_t__right(&In0P->right, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__right__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos(&In0P->qos, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__qos__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_allocate_full_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_allocate_full_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_full_t__right(&In0P->right, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__right__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos(&In0P->qos, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__qos__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_allocate_full_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_allocate_full_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_full_t__right(&In0P->right, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__right__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos(&In0P->qos, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__qos__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_allocate_full_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_allocate_full_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_allocate_full_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_allocate_full */
mig_internal novalue _Xmach_port_allocate_full
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t proto;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_port_right_t right;
		mach_port_qos_t qos;
		mach_port_name_t name;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_allocate_full_t __Request;
	typedef __Reply__mach_port_allocate_full_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_allocate_full_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_allocate_full_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3220, "mach_port_allocate_full")
	__BeforeRcvRpc(3220, "mach_port_allocate_full")

#if	defined(__MIG_check__Request__mach_port_allocate_full_t__defined)
	check_result = __MIG_check__Request__mach_port_allocate_full_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_allocate_full_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_allocate_full(task, In0P->right, In0P->proto.name, &In0P->qos, &In0P->name);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->qos = In0P->qos;

	OutP->name = In0P->name;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3220, "mach_port_allocate_full")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__task_set_port_space_t__defined)
#define __MIG_check__Request__task_set_port_space_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined
#if	defined(__NDR_convert__int_rep__mach_port__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__int_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__int_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined
#if	defined(__NDR_convert__char_rep__mach_port__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__char_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__char_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined
#if	defined(__NDR_convert__float_rep__mach_port__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__float_rep__mach_port__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__float_rep__mach_port__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined
#define	__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_port_space_t(__Request__task_set_port_space_t *In0P)
{

	typedef __Request__task_set_port_space_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined)
		__NDR_convert__int_rep__Request__task_set_port_space_t__table_entries(&In0P->table_entries, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_port_space_t__table_entries__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined)
		__NDR_convert__char_rep__Request__task_set_port_space_t__table_entries(&In0P->table_entries, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_port_space_t__table_entries__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined)
		__NDR_convert__float_rep__Request__task_set_port_space_t__table_entries(&In0P->table_entries, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_port_space_t__table_entries__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_port_space_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_port_space */
mig_internal novalue _Xtask_set_port_space
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int table_entries;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_port_space_t __Request;
	typedef __Reply__task_set_port_space_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_port_space_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_port_space_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3221, "task_set_port_space")
	__BeforeRcvRpc(3221, "task_set_port_space")

#if	defined(__MIG_check__Request__task_set_port_space_t__defined)
	check_result = __MIG_check__Request__task_set_port_space_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_port_space_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_port_space(task, In0P->table_entries);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3221, "task_set_port_space")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_get_srights_t__defined)
#define __MIG_check__Request__mach_port_get_srights_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_get_srights_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_get_srights_t(__Request__mach_port_get_srights_t *In0P)
{

	typedef __Request__mach_port_get_srights_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_get_srights_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_get_srights_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_get_srights_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_get_srights_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_get_srights_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_get_srights_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_get_srights_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_get_srights */
mig_internal novalue _Xmach_port_get_srights
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
	typedef __Request__mach_port_get_srights_t __Request;
	typedef __Reply__mach_port_get_srights_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_get_srights_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_get_srights_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3222, "mach_port_get_srights")
	__BeforeRcvRpc(3222, "mach_port_get_srights")

#if	defined(__MIG_check__Request__mach_port_get_srights_t__defined)
	check_result = __MIG_check__Request__mach_port_get_srights_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_get_srights_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_get_srights(task, In0P->name, &OutP->srights);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3222, "mach_port_get_srights")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_space_info_t__defined)
#define __MIG_check__Request__mach_port_space_info_t__defined

mig_internal kern_return_t __MIG_check__Request__mach_port_space_info_t(__Request__mach_port_space_info_t *In0P)
{

	typedef __Request__mach_port_space_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_space_info_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_space_info */
mig_internal novalue _Xmach_port_space_info
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
	typedef __Request__mach_port_space_info_t __Request;
	typedef __Reply__mach_port_space_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_space_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_space_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t table_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t tree_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t table_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t tree_infoTemplate = {
		/* addr = */		(void *)0,
		/* size = */		0,
		/* deal = */		TRUE,
		/* copy = */		MACH_MSG_VIRTUAL_COPY,
		/* pad2 = */		0,
		/* type = */		MACH_MSG_OOL_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	ipc_space_t task;

	__DeclareRcvRpc(3223, "mach_port_space_info")
	__BeforeRcvRpc(3223, "mach_port_space_info")

#if	defined(__MIG_check__Request__mach_port_space_info_t__defined)
	check_result = __MIG_check__Request__mach_port_space_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_space_info_t__defined) */

#if	UseStaticTemplates
	OutP->table_info = table_infoTemplate;
#else	/* UseStaticTemplates */
	OutP->table_info.deallocate =  TRUE;
	OutP->table_info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->table_info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


#if	UseStaticTemplates
	OutP->tree_info = tree_infoTemplate;
#else	/* UseStaticTemplates */
	OutP->tree_info.deallocate =  TRUE;
	OutP->tree_info.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->tree_info.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->table_infoCnt = 0;

	OutP->tree_infoCnt = 0;

	RetCode = mach_port_space_info(task, &OutP->space_info, (ipc_info_name_array_t *)&(OutP->table_info.address), &OutP->table_infoCnt, (ipc_info_tree_name_array_t *)&(OutP->tree_info.address), &OutP->tree_infoCnt);
	space_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->table_info.size = OutP->table_infoCnt * 28;

	OutP->tree_info.size = OutP->tree_infoCnt * 36;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 2;
	__AfterRcvRpc(3223, "mach_port_space_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_dnrequest_info_t__defined)
#define __MIG_check__Request__mach_port_dnrequest_info_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_dnrequest_info_t(__Request__mach_port_dnrequest_info_t *In0P)
{

	typedef __Request__mach_port_dnrequest_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_dnrequest_info_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_dnrequest_info_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_dnrequest_info_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_dnrequest_info_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_dnrequest_info */
mig_internal novalue _Xmach_port_dnrequest_info
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
	typedef __Request__mach_port_dnrequest_info_t __Request;
	typedef __Reply__mach_port_dnrequest_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_dnrequest_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_dnrequest_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3224, "mach_port_dnrequest_info")
	__BeforeRcvRpc(3224, "mach_port_dnrequest_info")

#if	defined(__MIG_check__Request__mach_port_dnrequest_info_t__defined)
	check_result = __MIG_check__Request__mach_port_dnrequest_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_dnrequest_info_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_dnrequest_info(task, In0P->name, &OutP->dnr_total, &OutP->dnr_used);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3224, "mach_port_dnrequest_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_kernel_object_t__defined)
#define __MIG_check__Request__mach_port_kernel_object_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_kernel_object_t(__Request__mach_port_kernel_object_t *In0P)
{

	typedef __Request__mach_port_kernel_object_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_kernel_object_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_kernel_object_t__name__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_kernel_object_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_kernel_object_t__name__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_kernel_object_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_kernel_object_t__name__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_kernel_object_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_kernel_object */
mig_internal novalue _Xmach_port_kernel_object
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
	typedef __Request__mach_port_kernel_object_t __Request;
	typedef __Reply__mach_port_kernel_object_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_kernel_object_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_kernel_object_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3225, "mach_port_kernel_object")
	__BeforeRcvRpc(3225, "mach_port_kernel_object")

#if	defined(__MIG_check__Request__mach_port_kernel_object_t__defined)
	check_result = __MIG_check__Request__mach_port_kernel_object_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_kernel_object_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_kernel_object(task, In0P->name, &OutP->object_type, &OutP->object_addr);
	space_deallocate(task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3225, "mach_port_kernel_object")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_insert_member_t__defined)
#define __MIG_check__Request__mach_port_insert_member_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined
#define	__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_insert_member_t(__Request__mach_port_insert_member_t *In0P)
{

	typedef __Request__mach_port_insert_member_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_insert_member_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_insert_member_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined)
		__NDR_convert__int_rep__Request__mach_port_insert_member_t__pset(&In0P->pset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_insert_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_insert_member_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_insert_member_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined)
		__NDR_convert__char_rep__Request__mach_port_insert_member_t__pset(&In0P->pset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_insert_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_insert_member_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_insert_member_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined)
		__NDR_convert__float_rep__Request__mach_port_insert_member_t__pset(&In0P->pset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_insert_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_insert_member_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_insert_member */
mig_internal novalue _Xmach_port_insert_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_name_t pset;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_insert_member_t __Request;
	typedef __Reply__mach_port_insert_member_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_insert_member_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_insert_member_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3226, "mach_port_insert_member")
	__BeforeRcvRpc(3226, "mach_port_insert_member")

#if	defined(__MIG_check__Request__mach_port_insert_member_t__defined)
	check_result = __MIG_check__Request__mach_port_insert_member_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_insert_member_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_insert_member(task, In0P->name, In0P->pset);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3226, "mach_port_insert_member")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__mach_port_subsystem__
#if !defined(__MIG_check__Request__mach_port_extract_member_t__defined)
#define __MIG_check__Request__mach_port_extract_member_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined */

#ifndef __NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined
#if	defined(__NDR_convert__int_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__int_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_port_name_t__defined)
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__int_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined */

#ifndef __NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined
#if	defined(__NDR_convert__char_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__char_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__mach_port_name_t__defined)
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__char_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__name(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined */

#ifndef __NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined
#if	defined(__NDR_convert__float_rep__mach_port__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__float_rep__mach_port__mach_port_name_t((mach_port_name_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__mach_port_name_t__defined)
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined
#define	__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset(a, f) \
	__NDR_convert__float_rep__mach_port_name_t((mach_port_name_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined */


mig_internal kern_return_t __MIG_check__Request__mach_port_extract_member_t(__Request__mach_port_extract_member_t *In0P)
{

	typedef __Request__mach_port_extract_member_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined)
		__NDR_convert__int_rep__Request__mach_port_extract_member_t__name(&In0P->name, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_extract_member_t__name__defined */
#if defined(__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined)
		__NDR_convert__int_rep__Request__mach_port_extract_member_t__pset(&In0P->pset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_port_extract_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined)
		__NDR_convert__char_rep__Request__mach_port_extract_member_t__name(&In0P->name, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_extract_member_t__name__defined */
#if defined(__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined)
		__NDR_convert__char_rep__Request__mach_port_extract_member_t__pset(&In0P->pset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_port_extract_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined)
		__NDR_convert__float_rep__Request__mach_port_extract_member_t__name(&In0P->name, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_extract_member_t__name__defined */
#if defined(__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined)
		__NDR_convert__float_rep__Request__mach_port_extract_member_t__pset(&In0P->pset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_port_extract_member_t__pset__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_port_extract_member_t__defined) */
#endif /* __MIG_check__Request__mach_port_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_port_extract_member */
mig_internal novalue _Xmach_port_extract_member
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_port_name_t name;
		mach_port_name_t pset;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_port_extract_member_t __Request;
	typedef __Reply__mach_port_extract_member_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_port_extract_member_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_port_extract_member_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	ipc_space_t task;

	__DeclareRcvRpc(3227, "mach_port_extract_member")
	__BeforeRcvRpc(3227, "mach_port_extract_member")

#if	defined(__MIG_check__Request__mach_port_extract_member_t__defined)
	check_result = __MIG_check__Request__mach_port_extract_member_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_port_extract_member_t__defined) */

	task = convert_port_to_space(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_port_extract_member(task, In0P->name, In0P->pset);
	space_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3227, "mach_port_extract_member")
}



/* Description of this subsystem, for use in direct RPC */
const struct mach_port_subsystem mach_port_subsystem = {
	mach_port_server_routine,
	3200,
	3228,
	(mach_msg_size_t)sizeof(union __ReplyUnion__mach_port_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_names, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_names_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_type, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_type_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_rename, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_rename_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_allocate_name, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_allocate_name_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_allocate, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_allocate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_destroy, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_deallocate, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_deallocate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_get_refs, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_get_refs_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_mod_refs, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_mod_refs_t)},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_set_mscount, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_set_mscount_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_get_set_status, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_get_set_status_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_move_member, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_move_member_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_request_notification, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_request_notification_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_insert_right, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_insert_right_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_extract_right, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_extract_right_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_set_seqno, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_set_seqno_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_get_attributes, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_get_attributes_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_set_attributes, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_set_attributes_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_allocate_qos, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_allocate_qos_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_allocate_full, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_allocate_full_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_port_space, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_port_space_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_get_srights, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_get_srights_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_space_info, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_space_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_dnrequest_info, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_dnrequest_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_kernel_object, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_kernel_object_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_insert_member, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_insert_member_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_port_extract_member, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_port_extract_member_t)},
	}
};

mig_external boolean_t mach_port_server
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

	if ((InHeadP->msgh_id > 3227) || (InHeadP->msgh_id < 3200) ||
	    ((routine = mach_port_subsystem.routine[InHeadP->msgh_id - 3200].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t mach_port_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 3200;

	if ((msgh_id > 27) || (msgh_id < 0))
		return 0;

	return mach_port_subsystem.routine[msgh_id].stub_routine;
}

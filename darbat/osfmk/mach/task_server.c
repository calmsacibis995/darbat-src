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

/* Module task */

#define	__MIG_check__Request__task_subsystem__ 1
#define	__NDR_convert__Request__task_subsystem__ 1

#include "task_server.h"

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


mig_internal novalue _Xtask_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_terminate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_threads
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_ports_register
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_ports_lookup
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_suspend
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_resume
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_get_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_special_port
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xthread_create_running
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_get_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_swap_exception_ports
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_set_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xlock_set_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xsemaphore_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_policy_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_policy_get
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_sample
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_emulation
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_get_emulation_vector
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_emulation_vector
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_ras_pc
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_assign
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_assign_default
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_get_assignment
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_set_policy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_create_t__defined)
#define __MIG_check__Request__task_create_t__defined
#ifndef __NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined
#define	__NDR_convert__int_rep__Request__task_create_t__ledgersCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined
#define	__NDR_convert__int_rep__Request__task_create_t__ledgersCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined */

#ifndef __NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__int_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__int_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined */

#ifndef __NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__char_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__char_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined */

#ifndef __NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__float_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined
#define	__NDR_convert__float_rep__Request__task_create_t__inherit_memory(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined */


mig_internal kern_return_t __MIG_check__Request__task_create_t(__Request__task_create_t *In0P)
{

	typedef __Request__task_create_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->ledgers.type != MACH_MSG_OOL_PORTS_DESCRIPTOR ||
	    In0P->ledgers.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined)
		__NDR_convert__int_rep__Request__task_create_t__ledgersCnt(&In0P->ledgersCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_create_t__ledgersCnt__defined */
#if defined(__NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined)
		__NDR_convert__int_rep__Request__task_create_t__inherit_memory(&In0P->inherit_memory, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_create_t__inherit_memory__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	0 || \
	defined(__NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined)
		__NDR_convert__char_rep__Request__task_create_t__inherit_memory(&In0P->inherit_memory, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_create_t__inherit_memory__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	0 || \
	defined(__NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined)
		__NDR_convert__float_rep__Request__task_create_t__inherit_memory(&In0P->inherit_memory, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_create_t__inherit_memory__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_create_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_create */
mig_internal novalue _Xtask_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_ports_descriptor_t ledgers;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t ledgersCnt;
		boolean_t inherit_memory;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_create_t __Request;
	typedef __Reply__task_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_taskTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_taskTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	task_t target_task;
	task_t child_task;

	__DeclareRcvRpc(3400, "task_create")
	__BeforeRcvRpc(3400, "task_create")

#if	defined(__MIG_check__Request__task_create_t__defined)
	check_result = __MIG_check__Request__task_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_create_t__defined) */

#if	UseStaticTemplates
	OutP->child_task = child_taskTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->child_task.disposition = 17;
#else
	OutP->child_task.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->child_task.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = task_create(target_task, (ledger_array_t)(In0P->ledgers.address), In0P->ledgersCnt, In0P->inherit_memory, &child_task);
	task_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->child_task.name = (mach_port_t)convert_task_to_port(child_task);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3400, "task_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_terminate_t__defined)
#define __MIG_check__Request__task_terminate_t__defined

mig_internal kern_return_t __MIG_check__Request__task_terminate_t(__Request__task_terminate_t *In0P)
{

	typedef __Request__task_terminate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_terminate_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_terminate */
mig_internal novalue _Xtask_terminate
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
	typedef __Request__task_terminate_t __Request;
	typedef __Reply__task_terminate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_terminate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_terminate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3401, "task_terminate")
	__BeforeRcvRpc(3401, "task_terminate")

#if	defined(__MIG_check__Request__task_terminate_t__defined)
	check_result = __MIG_check__Request__task_terminate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_terminate_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_terminate(target_task);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3401, "task_terminate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_threads_t__defined)
#define __MIG_check__Request__task_threads_t__defined

mig_internal kern_return_t __MIG_check__Request__task_threads_t(__Request__task_threads_t *In0P)
{

	typedef __Request__task_threads_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_threads_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_threads */
mig_internal novalue _Xtask_threads
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
	typedef __Request__task_threads_t __Request;
	typedef __Reply__task_threads_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_threads_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_threads_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t act_listTemplate = {
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
	const static mach_msg_ool_ports_descriptor_t act_listTemplate = {
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
	task_t target_task;

	__DeclareRcvRpc(3402, "task_threads")
	__BeforeRcvRpc(3402, "task_threads")

#if	defined(__MIG_check__Request__task_threads_t__defined)
	check_result = __MIG_check__Request__task_threads_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_threads_t__defined) */

#if	UseStaticTemplates
	OutP->act_list = act_listTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->act_list.disposition = 17;
#else
	OutP->act_list.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->act_list.deallocate =  FALSE;
	OutP->act_list.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = task_threads(target_task, (thread_act_array_t *)&(OutP->act_list.address), &OutP->act_listCnt);
	task_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->act_list.count = OutP->act_listCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3402, "task_threads")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__mach_ports_register_t__defined)
#define __MIG_check__Request__mach_ports_register_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined
#define	__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined
#define	__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined */


mig_internal kern_return_t __MIG_check__Request__mach_ports_register_t(__Request__mach_ports_register_t *In0P)
{

	typedef __Request__mach_ports_register_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->init_port_set.type != MACH_MSG_OOL_PORTS_DESCRIPTOR ||
	    In0P->init_port_set.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined)
		__NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt(&In0P->init_port_setCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_ports_register_t__init_port_setCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_ports_register_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_ports_register */
mig_internal novalue _Xmach_ports_register
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_ports_descriptor_t init_port_set;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t init_port_setCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_ports_register_t __Request;
	typedef __Reply__mach_ports_register_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_ports_register_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_ports_register_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3403, "mach_ports_register")
	__BeforeRcvRpc(3403, "mach_ports_register")

#if	defined(__MIG_check__Request__mach_ports_register_t__defined)
	check_result = __MIG_check__Request__mach_ports_register_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_ports_register_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = mach_ports_register(target_task, (mach_port_array_t)(In0P->init_port_set.address), In0P->init_port_setCnt);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3403, "mach_ports_register")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__mach_ports_lookup_t__defined)
#define __MIG_check__Request__mach_ports_lookup_t__defined

mig_internal kern_return_t __MIG_check__Request__mach_ports_lookup_t(__Request__mach_ports_lookup_t *In0P)
{

	typedef __Request__mach_ports_lookup_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_ports_lookup_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_ports_lookup */
mig_internal novalue _Xmach_ports_lookup
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
	typedef __Request__mach_ports_lookup_t __Request;
	typedef __Reply__mach_ports_lookup_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_ports_lookup_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_ports_lookup_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_ports_descriptor_t init_port_setTemplate = {
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
	const static mach_msg_ool_ports_descriptor_t init_port_setTemplate = {
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
	task_t target_task;

	__DeclareRcvRpc(3404, "mach_ports_lookup")
	__BeforeRcvRpc(3404, "mach_ports_lookup")

#if	defined(__MIG_check__Request__mach_ports_lookup_t__defined)
	check_result = __MIG_check__Request__mach_ports_lookup_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_ports_lookup_t__defined) */

#if	UseStaticTemplates
	OutP->init_port_set = init_port_setTemplate;
#else	/* UseStaticTemplates */
#if	__MigKernelSpecificCode
	OutP->init_port_set.disposition = 17;
#else
	OutP->init_port_set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->init_port_set.deallocate =  FALSE;
	OutP->init_port_set.type = MACH_MSG_OOL_PORTS_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = mach_ports_lookup(target_task, (mach_port_array_t *)&(OutP->init_port_set.address), &OutP->init_port_setCnt);
	task_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->init_port_set.count = OutP->init_port_setCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3404, "mach_ports_lookup")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_info_t__defined)
#define __MIG_check__Request__task_info_t__defined
#ifndef __NDR_convert__int_rep__Request__task_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__task__task_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined
#define	__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined */

#ifndef __NDR_convert__char_rep__Request__task_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__task__task_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__task__task_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_info_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__task_info_t(__Request__task_info_t *In0P)
{

	typedef __Request__task_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__task_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined)
		__NDR_convert__int_rep__Request__task_info_t__task_info_outCnt(&In0P->task_info_outCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_info_t__task_info_outCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_info_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__task_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_info_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__task_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_info_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_info_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_info */
mig_internal novalue _Xtask_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		task_flavor_t flavor;
		mach_msg_type_number_t task_info_outCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_info_t __Request;
	typedef __Reply__task_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3405, "task_info")
	__BeforeRcvRpc(3405, "task_info")

#if	defined(__MIG_check__Request__task_info_t__defined)
	check_result = __MIG_check__Request__task_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_info_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->task_info_outCnt = 10;
	if (In0P->task_info_outCnt < OutP->task_info_outCnt)
		OutP->task_info_outCnt = In0P->task_info_outCnt;

	OutP->RetCode = task_info(target_task, In0P->flavor, OutP->task_info_out, &OutP->task_info_outCnt);
	task_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 40) + (((4 * OutP->task_info_outCnt)));

	__AfterRcvRpc(3405, "task_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_info_t__defined)
#define __MIG_check__Request__task_set_info_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#if	defined(__NDR_convert__int_rep__task__task_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_info_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#if	defined(__NDR_convert__int_rep__task__task_info_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__int_rep__task__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task_info_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__int_rep__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__task__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__task__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#if	defined(__NDR_convert__char_rep__task__task_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_info_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#if	defined(__NDR_convert__char_rep__task__task_info_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__char_rep__task__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task_info_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__char_rep__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__task__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__task__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#if	defined(__NDR_convert__float_rep__task__task_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task_flavor_t((task_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_info_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#if	defined(__NDR_convert__float_rep__task__task_info_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__float_rep__task__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task_info_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__float_rep__task_info_t((task_info_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__task__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__task__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined
#define	__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_info_t(__Request__task_set_info_t *In0P)
{

	typedef __Request__task_set_info_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 40)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt(&In0P->task_info_inCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 40) + ((4 * In0P->task_info_inCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_info_t__task_info_inCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_info_t__flavor__defined)
		__NDR_convert__int_rep__Request__task_set_info_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_info_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined)
		__NDR_convert__int_rep__Request__task_set_info_t__task_info_in(&In0P->task_info_in, In0P->NDR.int_rep, In0P->task_info_inCnt);
#endif	/* __NDR_convert__int_rep__Request__task_set_info_t__task_info_in__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_info_t__flavor__defined)
		__NDR_convert__char_rep__Request__task_set_info_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_info_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined)
		__NDR_convert__char_rep__Request__task_set_info_t__task_info_in(&In0P->task_info_in, In0P->NDR.char_rep, In0P->task_info_inCnt);
#endif	/* __NDR_convert__char_rep__Request__task_set_info_t__task_info_in__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_info_t__flavor__defined)
		__NDR_convert__float_rep__Request__task_set_info_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_info_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined)
		__NDR_convert__float_rep__Request__task_set_info_t__task_info_in(&In0P->task_info_in, In0P->NDR.float_rep, In0P->task_info_inCnt);
#endif	/* __NDR_convert__float_rep__Request__task_set_info_t__task_info_in__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_info_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_info */
mig_internal novalue _Xtask_set_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		task_flavor_t flavor;
		mach_msg_type_number_t task_info_inCnt;
		integer_t task_info_in[10];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_info_t __Request;
	typedef __Reply__task_set_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_info_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3406, "task_set_info")
	__BeforeRcvRpc(3406, "task_set_info")

#if	defined(__MIG_check__Request__task_set_info_t__defined)
	check_result = __MIG_check__Request__task_set_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_info_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_info(target_task, In0P->flavor, In0P->task_info_in, In0P->task_info_inCnt);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3406, "task_set_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_suspend_t__defined)
#define __MIG_check__Request__task_suspend_t__defined

mig_internal kern_return_t __MIG_check__Request__task_suspend_t(__Request__task_suspend_t *In0P)
{

	typedef __Request__task_suspend_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_suspend_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_suspend */
mig_internal novalue _Xtask_suspend
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
	typedef __Request__task_suspend_t __Request;
	typedef __Reply__task_suspend_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_suspend_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_suspend_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3407, "task_suspend")
	__BeforeRcvRpc(3407, "task_suspend")

#if	defined(__MIG_check__Request__task_suspend_t__defined)
	check_result = __MIG_check__Request__task_suspend_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_suspend_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_suspend(target_task);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3407, "task_suspend")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_resume_t__defined)
#define __MIG_check__Request__task_resume_t__defined

mig_internal kern_return_t __MIG_check__Request__task_resume_t(__Request__task_resume_t *In0P)
{

	typedef __Request__task_resume_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_resume_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_resume */
mig_internal novalue _Xtask_resume
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
	typedef __Request__task_resume_t __Request;
	typedef __Reply__task_resume_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_resume_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_resume_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3408, "task_resume")
	__BeforeRcvRpc(3408, "task_resume")

#if	defined(__MIG_check__Request__task_resume_t__defined)
	check_result = __MIG_check__Request__task_resume_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_resume_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_resume(target_task);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3408, "task_resume")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_get_special_port_t__defined)
#define __MIG_check__Request__task_get_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined */

#ifndef __NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined */

#ifndef __NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_get_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined */


mig_internal kern_return_t __MIG_check__Request__task_get_special_port_t(__Request__task_get_special_port_t *In0P)
{

	typedef __Request__task_get_special_port_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined)
		__NDR_convert__int_rep__Request__task_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined)
		__NDR_convert__char_rep__Request__task_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined)
		__NDR_convert__float_rep__Request__task_get_special_port_t__which_port(&In0P->which_port, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_get_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_get_special_port_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_get_special_port */
mig_internal novalue _Xtask_get_special_port
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
	typedef __Request__task_get_special_port_t __Request;
	typedef __Reply__task_get_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_get_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_get_special_port_t__defined */

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
	task_t task;

	__DeclareRcvRpc(3409, "task_get_special_port")
	__BeforeRcvRpc(3409, "task_get_special_port")

#if	defined(__MIG_check__Request__task_get_special_port_t__defined)
	check_result = __MIG_check__Request__task_get_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_get_special_port_t__defined) */

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


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = task_get_special_port(task, In0P->which_port, &OutP->special_port.name);
	task_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3409, "task_get_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_special_port_t__defined)
#define __MIG_check__Request__task_set_special_port_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__int_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__char_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined
#define	__NDR_convert__float_rep__Request__task_set_special_port_t__which_port(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_special_port_t(__Request__task_set_special_port_t *In0P)
{

	typedef __Request__task_set_special_port_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined)
		__NDR_convert__int_rep__Request__task_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined)
		__NDR_convert__char_rep__Request__task_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined)
		__NDR_convert__float_rep__Request__task_set_special_port_t__which_port(&In0P->which_port, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_special_port_t__which_port__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_special_port_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_special_port */
mig_internal novalue _Xtask_set_special_port
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
	typedef __Request__task_set_special_port_t __Request;
	typedef __Reply__task_set_special_port_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_special_port_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_special_port_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3410, "task_set_special_port")
	__BeforeRcvRpc(3410, "task_set_special_port")

#if	defined(__MIG_check__Request__task_set_special_port_t__defined)
	check_result = __MIG_check__Request__task_set_special_port_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_special_port_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_special_port(task, In0P->which_port, In0P->special_port.name);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3410, "task_set_special_port")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__thread_create_t__defined)
#define __MIG_check__Request__thread_create_t__defined

mig_internal kern_return_t __MIG_check__Request__thread_create_t(__Request__thread_create_t *In0P)
{

	typedef __Request__thread_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_create_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_create */
mig_internal novalue _Xthread_create
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
	typedef __Request__thread_create_t __Request;
	typedef __Reply__thread_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_actTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_actTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	task_t parent_task;
	thread_act_t child_act;

	__DeclareRcvRpc(3411, "thread_create")
	__BeforeRcvRpc(3411, "thread_create")

#if	defined(__MIG_check__Request__thread_create_t__defined)
	check_result = __MIG_check__Request__thread_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_create_t__defined) */

#if	UseStaticTemplates
	OutP->child_act = child_actTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->child_act.disposition = 17;
#else
	OutP->child_act.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->child_act.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	parent_task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = mach_thread_create(parent_task, &child_act);
	task_deallocate(parent_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->child_act.name = (mach_port_t)convert_thread_to_port(child_act);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3411, "thread_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__thread_create_running_t__defined)
#define __MIG_check__Request__thread_create_running_t__defined
#ifndef __NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#if	defined(__NDR_convert__int_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#if	defined(__NDR_convert__int_rep__task__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__int_rep__task__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__thread_state_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__int_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__task__natural_t)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__natural_t)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__task__uint32_t)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined */

#ifndef __NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined
#define	__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined */

#ifndef __NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#if	defined(__NDR_convert__char_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#if	defined(__NDR_convert__char_rep__task__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__char_rep__task__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__thread_state_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__char_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__task__natural_t)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__natural_t)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__task__uint32_t)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__char_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined */

#ifndef __NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#if	defined(__NDR_convert__float_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#if	defined(__NDR_convert__float_rep__task__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__float_rep__task__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__thread_state_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__float_rep__thread_state_t((thread_state_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__task__natural_t)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__natural_t)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__task__uint32_t)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined
#define	__NDR_convert__float_rep__Request__thread_create_running_t__new_state(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined */


mig_internal kern_return_t __MIG_check__Request__thread_create_running_t(__Request__thread_create_running_t *In0P)
{

	typedef __Request__thread_create_running_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 576)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt(&In0P->new_stateCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 576) + ((4 * In0P->new_stateCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined) || \
	defined(__NDR_convert__int_rep__Request__thread_create_running_t__new_stateCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined)
		__NDR_convert__int_rep__Request__thread_create_running_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__thread_create_running_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined)
		__NDR_convert__int_rep__Request__thread_create_running_t__new_state(&In0P->new_state, In0P->NDR.int_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__int_rep__Request__thread_create_running_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined)
		__NDR_convert__char_rep__Request__thread_create_running_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__thread_create_running_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined)
		__NDR_convert__char_rep__Request__thread_create_running_t__new_state(&In0P->new_state, In0P->NDR.char_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__char_rep__Request__thread_create_running_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined)
		__NDR_convert__float_rep__Request__thread_create_running_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__thread_create_running_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined)
		__NDR_convert__float_rep__Request__thread_create_running_t__new_state(&In0P->new_state, In0P->NDR.float_rep, In0P->new_stateCnt);
#endif	/* __NDR_convert__float_rep__Request__thread_create_running_t__new_state__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__thread_create_running_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine thread_create_running */
mig_internal novalue _Xthread_create_running
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
	typedef __Request__thread_create_running_t __Request;
	typedef __Reply__thread_create_running_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__thread_create_running_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__thread_create_running_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_actTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t child_actTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	task_t parent_task;
	thread_act_t child_act;

	__DeclareRcvRpc(3412, "thread_create_running")
	__BeforeRcvRpc(3412, "thread_create_running")

#if	defined(__MIG_check__Request__thread_create_running_t__defined)
	check_result = __MIG_check__Request__thread_create_running_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__thread_create_running_t__defined) */

#if	UseStaticTemplates
	OutP->child_act = child_actTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->child_act.disposition = 17;
#else
	OutP->child_act.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->child_act.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	parent_task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = thread_create_running(parent_task, In0P->flavor, In0P->new_state, In0P->new_stateCnt, &child_act);
	task_deallocate(parent_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->child_act.name = (mach_port_t)convert_thread_to_port(child_act);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3412, "thread_create_running")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_exception_ports_t__defined)
#define __MIG_check__Request__task_set_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__task__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__task__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__task__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_exception_ports_t(__Request__task_set_exception_ports_t *In0P)
{

	typedef __Request__task_set_exception_ports_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_exception_ports_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_exception_ports */
mig_internal novalue _Xtask_set_exception_ports
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
	typedef __Request__task_set_exception_ports_t __Request;
	typedef __Reply__task_set_exception_ports_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_exception_ports_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3413, "task_set_exception_ports")
	__BeforeRcvRpc(3413, "task_set_exception_ports")

#if	defined(__MIG_check__Request__task_set_exception_ports_t__defined)
	check_result = __MIG_check__Request__task_set_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_exception_ports_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_exception_ports(task, In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3413, "task_set_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_get_exception_ports_t__defined)
#define __MIG_check__Request__task_get_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__task__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__task__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__task__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined */


mig_internal kern_return_t __MIG_check__Request__task_get_exception_ports_t(__Request__task_get_exception_ports_t *In0P)
{

	typedef __Request__task_get_exception_ports_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_get_exception_ports_t__exception_mask__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_get_exception_ports_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_get_exception_ports */
mig_internal novalue _Xtask_get_exception_ports
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
	typedef __Request__task_get_exception_ports_t __Request;
	typedef __Reply__task_get_exception_ports_t Reply;

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

#ifdef	__MIG_check__Request__task_get_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_get_exception_ports_t__defined */

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
	task_t task;
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlers[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(3414, "task_get_exception_ports")
	__BeforeRcvRpc(3414, "task_get_exception_ports")

#if	defined(__MIG_check__Request__task_get_exception_ports_t__defined)
	check_result = __MIG_check__Request__task_get_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_get_exception_ports_t__defined) */

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


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	masksCnt = 32;

	RetCode = task_get_exception_ports(task, In0P->exception_mask, OutP->masks, &masksCnt, old_handlers, old_behaviors, old_flavors);
	task_deallocate(task);
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
	__AfterRcvRpc(3414, "task_get_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_swap_exception_ports_t__defined)
#define __MIG_check__Request__task_swap_exception_ports_t__defined
#ifndef __NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__int_rep__task__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_mask_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__int_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__exception_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__int_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__char_rep__task__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_mask_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__char_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__exception_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__char_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#if	defined(__NDR_convert__float_rep__task__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_mask_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__exception_mask_t((exception_mask_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined */

#ifndef __NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#if	defined(__NDR_convert__float_rep__task__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__exception_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__exception_behavior_t((exception_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined */

#ifndef __NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#if	defined(__NDR_convert__float_rep__task__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__thread_state_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__thread_state_flavor_t((thread_state_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined
#define	__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined */


mig_internal kern_return_t __MIG_check__Request__task_swap_exception_ports_t(__Request__task_swap_exception_ports_t *In0P)
{

	typedef __Request__task_swap_exception_ports_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined)
		__NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined)
		__NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined) || \
	defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined) || \
	defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined)
		__NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask(&In0P->exception_mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__exception_mask__defined */
#if defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined)
		__NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior(&In0P->behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__behavior__defined */
#if defined(__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined)
		__NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor(&In0P->new_flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_swap_exception_ports_t__new_flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_swap_exception_ports_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_swap_exception_ports */
mig_internal novalue _Xtask_swap_exception_ports
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
	typedef __Request__task_swap_exception_ports_t __Request;
	typedef __Reply__task_swap_exception_ports_t Reply;

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

#ifdef	__MIG_check__Request__task_swap_exception_ports_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_swap_exception_ports_t__defined */

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
	task_t task;
	mach_msg_type_number_t masksCnt;
	exception_handler_t old_handlerss[32];
	exception_behavior_t old_behaviors[32];
	thread_state_flavor_t old_flavors[32];

	__DeclareRcvRpc(3415, "task_swap_exception_ports")
	__BeforeRcvRpc(3415, "task_swap_exception_ports")

#if	defined(__MIG_check__Request__task_swap_exception_ports_t__defined)
	check_result = __MIG_check__Request__task_swap_exception_ports_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_swap_exception_ports_t__defined) */

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


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	masksCnt = 32;

	RetCode = task_swap_exception_ports(task, In0P->exception_mask, In0P->new_port.name, In0P->behavior, In0P->new_flavor, OutP->masks, &masksCnt, old_handlerss, old_behaviors, old_flavors);
	task_deallocate(task);
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
	__AfterRcvRpc(3415, "task_swap_exception_ports")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__lock_set_create_t__defined)
#define __MIG_check__Request__lock_set_create_t__defined
#ifndef __NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined */

#ifndef __NDR_convert__int_rep__Request__lock_set_create_t__policy__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__lock_set_create_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined */

#ifndef __NDR_convert__char_rep__Request__lock_set_create_t__policy__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__lock_set_create_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined */

#ifndef __NDR_convert__float_rep__Request__lock_set_create_t__policy__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__lock_set_create_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__lock_set_create_t__policy__defined */


mig_internal kern_return_t __MIG_check__Request__lock_set_create_t(__Request__lock_set_create_t *In0P)
{

	typedef __Request__lock_set_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined) || \
	defined(__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined)
		__NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks(&In0P->n_ulocks, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_set_create_t__n_ulocks__defined */
#if defined(__NDR_convert__int_rep__Request__lock_set_create_t__policy__defined)
		__NDR_convert__int_rep__Request__lock_set_create_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__lock_set_create_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined) || \
	defined(__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined)
		__NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks(&In0P->n_ulocks, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_set_create_t__n_ulocks__defined */
#if defined(__NDR_convert__char_rep__Request__lock_set_create_t__policy__defined)
		__NDR_convert__char_rep__Request__lock_set_create_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__lock_set_create_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined) || \
	defined(__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined)
		__NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks(&In0P->n_ulocks, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_set_create_t__n_ulocks__defined */
#if defined(__NDR_convert__float_rep__Request__lock_set_create_t__policy__defined)
		__NDR_convert__float_rep__Request__lock_set_create_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__lock_set_create_t__policy__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_set_create_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_set_create */
mig_internal novalue _Xlock_set_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int n_ulocks;
		int policy;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_set_create_t __Request;
	typedef __Reply__lock_set_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_set_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_set_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_lock_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t new_lock_setTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	task_t task;
	lock_set_t new_lock_set;

	__DeclareRcvRpc(3416, "lock_set_create")
	__BeforeRcvRpc(3416, "lock_set_create")

#if	defined(__MIG_check__Request__lock_set_create_t__defined)
	check_result = __MIG_check__Request__lock_set_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_set_create_t__defined) */

#if	UseStaticTemplates
	OutP->new_lock_set = new_lock_setTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->new_lock_set.disposition = 17;
#else
	OutP->new_lock_set.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->new_lock_set.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = lock_set_create(task, &new_lock_set, In0P->n_ulocks, In0P->policy);
	task_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->new_lock_set.name = (mach_port_t)convert_lock_set_to_port(new_lock_set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3416, "lock_set_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__lock_set_destroy_t__defined)
#define __MIG_check__Request__lock_set_destroy_t__defined

mig_internal kern_return_t __MIG_check__Request__lock_set_destroy_t(__Request__lock_set_destroy_t *In0P)
{

	typedef __Request__lock_set_destroy_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->lock_set.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->lock_set.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__lock_set_destroy_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine lock_set_destroy */
mig_internal novalue _Xlock_set_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t lock_set;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__lock_set_destroy_t __Request;
	typedef __Reply__lock_set_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__lock_set_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__lock_set_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;
	lock_set_t lock_set;

	__DeclareRcvRpc(3417, "lock_set_destroy")
	__BeforeRcvRpc(3417, "lock_set_destroy")

#if	defined(__MIG_check__Request__lock_set_destroy_t__defined)
	check_result = __MIG_check__Request__lock_set_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__lock_set_destroy_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	lock_set = convert_port_to_lock_set(In0P->lock_set.name);

	OutP->RetCode = lock_set_destroy(task, lock_set);
	lock_set_dereference(lock_set);
	task_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->lock_set.name))
		ipc_port_release_send((ipc_port_t)In0P->lock_set.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3417, "lock_set_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__semaphore_create_t__defined)
#define __MIG_check__Request__semaphore_create_t__defined
#ifndef __NDR_convert__int_rep__Request__semaphore_create_t__policy__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__semaphore_create_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__semaphore_create_t__value__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__int_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__semaphore_create_t__value__defined */

#ifndef __NDR_convert__char_rep__Request__semaphore_create_t__policy__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__semaphore_create_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__semaphore_create_t__value__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__char_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__semaphore_create_t__value__defined */

#ifndef __NDR_convert__float_rep__Request__semaphore_create_t__policy__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__semaphore_create_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__semaphore_create_t__value__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value__defined
#define	__NDR_convert__float_rep__Request__semaphore_create_t__value(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__semaphore_create_t__value__defined */


mig_internal kern_return_t __MIG_check__Request__semaphore_create_t(__Request__semaphore_create_t *In0P)
{

	typedef __Request__semaphore_create_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__semaphore_create_t__value__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__semaphore_create_t__policy__defined)
		__NDR_convert__int_rep__Request__semaphore_create_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__semaphore_create_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__semaphore_create_t__value__defined)
		__NDR_convert__int_rep__Request__semaphore_create_t__value(&In0P->value, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__semaphore_create_t__value__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__semaphore_create_t__value__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__semaphore_create_t__policy__defined)
		__NDR_convert__char_rep__Request__semaphore_create_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__semaphore_create_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__semaphore_create_t__value__defined)
		__NDR_convert__char_rep__Request__semaphore_create_t__value(&In0P->value, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__semaphore_create_t__value__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__semaphore_create_t__value__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__semaphore_create_t__policy__defined)
		__NDR_convert__float_rep__Request__semaphore_create_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__semaphore_create_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__semaphore_create_t__value__defined)
		__NDR_convert__float_rep__Request__semaphore_create_t__value(&In0P->value, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__semaphore_create_t__value__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_create_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_create */
mig_internal novalue _Xsemaphore_create
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int policy;
		int value;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_create_t __Request;
	typedef __Reply__semaphore_create_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_create_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_create_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t semaphoreTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t semaphoreTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		19,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	task_t task;
	semaphore_t semaphore;

	__DeclareRcvRpc(3418, "semaphore_create")
	__BeforeRcvRpc(3418, "semaphore_create")

#if	defined(__MIG_check__Request__semaphore_create_t__defined)
	check_result = __MIG_check__Request__semaphore_create_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_create_t__defined) */

#if	UseStaticTemplates
	OutP->semaphore = semaphoreTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->semaphore.disposition = 17;
#else
	OutP->semaphore.disposition = 19;
#endif /* __MigKernelSpecificCode */
	OutP->semaphore.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = semaphore_create(task, &semaphore, In0P->policy, In0P->value);
	task_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->semaphore.name = (mach_port_t)convert_semaphore_to_port(semaphore);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3418, "semaphore_create")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__semaphore_destroy_t__defined)
#define __MIG_check__Request__semaphore_destroy_t__defined

mig_internal kern_return_t __MIG_check__Request__semaphore_destroy_t(__Request__semaphore_destroy_t *In0P)
{

	typedef __Request__semaphore_destroy_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->semaphore.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->semaphore.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__semaphore_destroy_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine semaphore_destroy */
mig_internal novalue _Xsemaphore_destroy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t semaphore;
		/* end of the kernel processed data */
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__semaphore_destroy_t __Request;
	typedef __Reply__semaphore_destroy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__semaphore_destroy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__semaphore_destroy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;
	semaphore_t semaphore;

	__DeclareRcvRpc(3419, "semaphore_destroy")
	__BeforeRcvRpc(3419, "semaphore_destroy")

#if	defined(__MIG_check__Request__semaphore_destroy_t__defined)
	check_result = __MIG_check__Request__semaphore_destroy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__semaphore_destroy_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	semaphore = convert_port_to_semaphore(In0P->semaphore.name);

	OutP->RetCode = semaphore_destroy(task, semaphore);
	semaphore_dereference(semaphore);
	task_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->semaphore.name))
		ipc_port_release_send((ipc_port_t)In0P->semaphore.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3419, "semaphore_destroy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_policy_set_t__defined)
#define __MIG_check__Request__task_policy_set_t__defined
#ifndef __NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#if	defined(__NDR_convert__int_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__int_rep__task__task_policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__task__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task_policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__int_rep__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__task__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__task__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#if	defined(__NDR_convert__char_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__char_rep__task__task_policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__task__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task_policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__char_rep__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__task__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__task__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#if	defined(__NDR_convert__float_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__flavor(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#if	defined(__NDR_convert__float_rep__task__task_policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__task__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task_policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__float_rep__task_policy_t((task_policy_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__task__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__task__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined
#define	__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined */


mig_internal kern_return_t __MIG_check__Request__task_policy_set_t(__Request__task_policy_set_t *In0P)
{

	typedef __Request__task_policy_set_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 64)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt(&In0P->policy_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined */
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 64) + ((4 * In0P->policy_infoCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_set_t__policy_infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined)
		__NDR_convert__int_rep__Request__task_policy_set_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_set_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined)
		__NDR_convert__int_rep__Request__task_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.int_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__int_rep__Request__task_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined)
		__NDR_convert__char_rep__Request__task_policy_set_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_set_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined)
		__NDR_convert__char_rep__Request__task_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.char_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__char_rep__Request__task_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined) || \
	defined(__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined)
		__NDR_convert__float_rep__Request__task_policy_set_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_set_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined)
		__NDR_convert__float_rep__Request__task_policy_set_t__policy_info(&In0P->policy_info, In0P->NDR.float_rep, In0P->policy_infoCnt);
#endif	/* __NDR_convert__float_rep__Request__task_policy_set_t__policy_info__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_policy_set_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_policy_set */
mig_internal novalue _Xtask_policy_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		task_policy_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		integer_t policy_info[16];
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_policy_set_t __Request;
	typedef __Reply__task_policy_set_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_policy_set_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_policy_set_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3420, "task_policy_set")
	__BeforeRcvRpc(3420, "task_policy_set")

#if	defined(__MIG_check__Request__task_policy_set_t__defined)
	check_result = __MIG_check__Request__task_policy_set_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_policy_set_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_policy_set(task, In0P->flavor, In0P->policy_info, In0P->policy_infoCnt);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3420, "task_policy_set")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_policy_get_t__defined)
#define __MIG_check__Request__task_policy_get_t__defined
#ifndef __NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#if	defined(__NDR_convert__int_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__int_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#if	defined(__NDR_convert__char_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__char_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#if	defined(__NDR_convert__float_rep__task__task_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__task__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task_policy_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__task_policy_flavor_t((task_policy_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__flavor(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined
#define	__NDR_convert__float_rep__Request__task_policy_get_t__get_default(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined */


mig_internal kern_return_t __MIG_check__Request__task_policy_get_t(__Request__task_policy_get_t *In0P)
{

	typedef __Request__task_policy_get_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined)
		__NDR_convert__int_rep__Request__task_policy_get_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_get_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined)
		__NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt(&In0P->policy_infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_get_t__policy_infoCnt__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined)
		__NDR_convert__int_rep__Request__task_policy_get_t__get_default(&In0P->get_default, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined)
		__NDR_convert__char_rep__Request__task_policy_get_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_get_t__flavor__defined */
#if defined(__NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined)
		__NDR_convert__char_rep__Request__task_policy_get_t__get_default(&In0P->get_default, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined)
		__NDR_convert__float_rep__Request__task_policy_get_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_get_t__flavor__defined */
#if defined(__NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined)
		__NDR_convert__float_rep__Request__task_policy_get_t__get_default(&In0P->get_default, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_get_t__get_default__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_policy_get_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_policy_get */
mig_internal novalue _Xtask_policy_get
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		task_policy_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		boolean_t get_default;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_policy_get_t __Request;
	typedef __Reply__task_policy_get_t Reply;

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

#ifdef	__MIG_check__Request__task_policy_get_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_policy_get_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3421, "task_policy_get")
	__BeforeRcvRpc(3421, "task_policy_get")

#if	defined(__MIG_check__Request__task_policy_get_t__defined)
	check_result = __MIG_check__Request__task_policy_get_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_policy_get_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->policy_infoCnt = 16;
	if (In0P->policy_infoCnt < OutP->policy_infoCnt)
		OutP->policy_infoCnt = In0P->policy_infoCnt;

	OutP->RetCode = task_policy_get(task, In0P->flavor, OutP->policy_info, &OutP->policy_infoCnt, &In0P->get_default);
	task_deallocate(task);
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
	__AfterRcvRpc(3421, "task_policy_get")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_sample_t__defined)
#define __MIG_check__Request__task_sample_t__defined

mig_internal kern_return_t __MIG_check__Request__task_sample_t(__Request__task_sample_t *In0P)
{

	typedef __Request__task_sample_t __Request;
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
#endif /* !defined(__MIG_check__Request__task_sample_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_sample */
mig_internal novalue _Xtask_sample
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
	typedef __Request__task_sample_t __Request;
	typedef __Reply__task_sample_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_sample_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_sample_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3422, "task_sample")
	__BeforeRcvRpc(3422, "task_sample")

#if	defined(__MIG_check__Request__task_sample_t__defined)
	check_result = __MIG_check__Request__task_sample_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_sample_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_sample(task, In0P->reply.name);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3422, "task_sample")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_policy_t__defined)
#define __MIG_check__Request__task_policy_t__defined
#ifndef __NDR_convert__int_rep__Request__task_policy_t__policy__defined
#if	defined(__NDR_convert__int_rep__task__policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_t__base__defined
#if	defined(__NDR_convert__int_rep__task__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__task__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__task__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_t__base__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_t__set_limit__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_t__set_limit__defined */

#ifndef __NDR_convert__int_rep__Request__task_policy_t__change__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__int_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_policy_t__change__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_t__policy__defined
#if	defined(__NDR_convert__char_rep__task__policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_t__base__defined
#if	defined(__NDR_convert__char_rep__task__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__task__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__task__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_t__base__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_t__set_limit__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_t__set_limit__defined */

#ifndef __NDR_convert__char_rep__Request__task_policy_t__change__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__char_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_policy_t__change__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_t__policy__defined
#if	defined(__NDR_convert__float_rep__task__policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_t__base__defined
#if	defined(__NDR_convert__float_rep__task__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__task__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__task__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_t__base__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_t__set_limit__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__set_limit__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__set_limit(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_t__set_limit__defined */

#ifndef __NDR_convert__float_rep__Request__task_policy_t__change__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_policy_t__change__defined
#define	__NDR_convert__float_rep__Request__task_policy_t__change(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_policy_t__change__defined */


mig_internal kern_return_t __MIG_check__Request__task_policy_t(__Request__task_policy_t *In0P, __Request__task_policy_t **In1PP)
{

	typedef __Request__task_policy_t __Request;
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

#if defined(__NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__task_policy_t__baseCnt(&In0P->baseCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined */
	msgh_size_delta = (4 * In0P->baseCnt);
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 20) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 20);

#if	defined(__NDR_convert__int_rep__Request__task_policy_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_t__base__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_t__baseCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_t__set_limit__defined) || \
	defined(__NDR_convert__int_rep__Request__task_policy_t__change__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_policy_t__policy__defined)
		__NDR_convert__int_rep__Request__task_policy_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_t__base__defined)
		__NDR_convert__int_rep__Request__task_policy_t__base(&In0P->base, In0P->NDR.int_rep, In0P->baseCnt);
#endif	/* __NDR_convert__int_rep__Request__task_policy_t__base__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_t__set_limit__defined)
		__NDR_convert__int_rep__Request__task_policy_t__set_limit(&In1P->set_limit, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_t__set_limit__defined */
#if defined(__NDR_convert__int_rep__Request__task_policy_t__change__defined)
		__NDR_convert__int_rep__Request__task_policy_t__change(&In1P->change, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_policy_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__task_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__task_policy_t__set_limit__defined) || \
	defined(__NDR_convert__char_rep__Request__task_policy_t__change__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_policy_t__policy__defined)
		__NDR_convert__char_rep__Request__task_policy_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__task_policy_t__base__defined)
		__NDR_convert__char_rep__Request__task_policy_t__base(&In0P->base, In0P->NDR.char_rep, In0P->baseCnt);
#endif	/* __NDR_convert__char_rep__Request__task_policy_t__base__defined */
#if defined(__NDR_convert__char_rep__Request__task_policy_t__set_limit__defined)
		__NDR_convert__char_rep__Request__task_policy_t__set_limit(&In1P->set_limit, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_t__set_limit__defined */
#if defined(__NDR_convert__char_rep__Request__task_policy_t__change__defined)
		__NDR_convert__char_rep__Request__task_policy_t__change(&In1P->change, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_policy_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__task_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__task_policy_t__set_limit__defined) || \
	defined(__NDR_convert__float_rep__Request__task_policy_t__change__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_policy_t__policy__defined)
		__NDR_convert__float_rep__Request__task_policy_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__task_policy_t__base__defined)
		__NDR_convert__float_rep__Request__task_policy_t__base(&In0P->base, In0P->NDR.float_rep, In0P->baseCnt);
#endif	/* __NDR_convert__float_rep__Request__task_policy_t__base__defined */
#if defined(__NDR_convert__float_rep__Request__task_policy_t__set_limit__defined)
		__NDR_convert__float_rep__Request__task_policy_t__set_limit(&In1P->set_limit, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_t__set_limit__defined */
#if defined(__NDR_convert__float_rep__Request__task_policy_t__change__defined)
		__NDR_convert__float_rep__Request__task_policy_t__change(&In1P->change, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_policy_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_policy */
mig_internal novalue _Xtask_policy
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
		boolean_t change;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_policy_t __Request;
	typedef __Reply__task_policy_t Reply;

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
#ifdef	__MIG_check__Request__task_policy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_policy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3423, "task_policy")
	__BeforeRcvRpc(3423, "task_policy")

#if	defined(__MIG_check__Request__task_policy_t__defined)
	check_result = __MIG_check__Request__task_policy_t((__Request *)In0P, (__Request **)&In1P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_policy_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_policy(task, In0P->policy, In0P->base, In0P->baseCnt, In1P->set_limit, In1P->change);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3423, "task_policy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_emulation_t__defined)
#define __MIG_check__Request__task_set_emulation_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#if	defined(__NDR_convert__int_rep__task__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#if	defined(__NDR_convert__char_rep__task__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#if	defined(__NDR_convert__float_rep__task__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_emulation_t(__Request__task_set_emulation_t *In0P)
{

	typedef __Request__task_set_emulation_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined)
		__NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt(&In0P->routine_entry_pt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_emulation_t__routine_entry_pt__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined)
		__NDR_convert__int_rep__Request__task_set_emulation_t__routine_number(&In0P->routine_number, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_emulation_t__routine_number__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined)
		__NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt(&In0P->routine_entry_pt, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_emulation_t__routine_entry_pt__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined)
		__NDR_convert__char_rep__Request__task_set_emulation_t__routine_number(&In0P->routine_number, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_emulation_t__routine_number__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined)
		__NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt(&In0P->routine_entry_pt, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_emulation_t__routine_entry_pt__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined)
		__NDR_convert__float_rep__Request__task_set_emulation_t__routine_number(&In0P->routine_number, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_emulation_t__routine_number__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_emulation_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_emulation */
mig_internal novalue _Xtask_set_emulation
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t routine_entry_pt;
		int routine_number;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_emulation_t __Request;
	typedef __Reply__task_set_emulation_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_emulation_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_emulation_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_port;

	__DeclareRcvRpc(3424, "task_set_emulation")
	__BeforeRcvRpc(3424, "task_set_emulation")

#if	defined(__MIG_check__Request__task_set_emulation_t__defined)
	check_result = __MIG_check__Request__task_set_emulation_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_emulation_t__defined) */

	target_port = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_emulation(target_port, In0P->routine_entry_pt, In0P->routine_number);
	task_deallocate(target_port);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3424, "task_set_emulation")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_get_emulation_vector_t__defined)
#define __MIG_check__Request__task_get_emulation_vector_t__defined

mig_internal kern_return_t __MIG_check__Request__task_get_emulation_vector_t(__Request__task_get_emulation_vector_t *In0P)
{

	typedef __Request__task_get_emulation_vector_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_get_emulation_vector_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_get_emulation_vector */
mig_internal novalue _Xtask_get_emulation_vector
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
	typedef __Request__task_get_emulation_vector_t __Request;
	typedef __Reply__task_get_emulation_vector_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_get_emulation_vector_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_get_emulation_vector_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t emulation_vectorTemplate = {
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
	const static mach_msg_ool_descriptor_t emulation_vectorTemplate = {
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
	task_t task;

	__DeclareRcvRpc(3425, "task_get_emulation_vector")
	__BeforeRcvRpc(3425, "task_get_emulation_vector")

#if	defined(__MIG_check__Request__task_get_emulation_vector_t__defined)
	check_result = __MIG_check__Request__task_get_emulation_vector_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_get_emulation_vector_t__defined) */

#if	UseStaticTemplates
	OutP->emulation_vector = emulation_vectorTemplate;
#else	/* UseStaticTemplates */
	OutP->emulation_vector.deallocate =  FALSE;
	OutP->emulation_vector.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->emulation_vector.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = task_get_emulation_vector(task, &OutP->vector_start, (emulation_vector_t *)&(OutP->emulation_vector.address), &OutP->emulation_vectorCnt);
	task_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->emulation_vector.size = OutP->emulation_vectorCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3425, "task_get_emulation_vector")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_emulation_vector_t__defined)
#define __MIG_check__Request__task_set_emulation_vector_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined
#if	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#if	defined(__NDR_convert__int_rep__task__emulation_vector_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__int_rep__task__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__emulation_vector_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__int_rep__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__int_rep__task__vm_offset_t)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__int_rep__vm_offset_t)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__task__natural_t)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__int_rep__natural_t)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__task__uint32_t)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__int_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined
#if	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#if	defined(__NDR_convert__char_rep__task__emulation_vector_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__char_rep__task__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__emulation_vector_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__char_rep__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__char_rep__task__vm_offset_t)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__char_rep__vm_offset_t)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__task__natural_t)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__char_rep__natural_t)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__task__uint32_t)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__char_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined
#if	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#if	defined(__NDR_convert__float_rep__task__emulation_vector_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__float_rep__task__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__emulation_vector_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__float_rep__emulation_vector_t((emulation_vector_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__float_rep__task__vm_offset_t)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, c, __NDR_convert__float_rep__vm_offset_t)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__task__natural_t)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((natural_t *)(a), f, c, __NDR_convert__float_rep__natural_t)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__task__uint32_t)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined
#define	__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector(a, f, c) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, c, __NDR_convert__float_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_emulation_vector_t(__Request__task_set_emulation_vector_t *In0P)
{

	typedef __Request__task_set_emulation_vector_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->emulation_vector.type != MACH_MSG_OOL_DESCRIPTOR)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined)
		__NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start(&In0P->vector_start, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__vector_start__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined)
		__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt(&In0P->emulation_vectorCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vectorCnt__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined)
		__NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector((emulation_vector_t)(In0P->emulation_vector.address), In0P->NDR.int_rep, In0P->emulation_vectorCnt);
#endif	/* __NDR_convert__int_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined)
		__NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start(&In0P->vector_start, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_emulation_vector_t__vector_start__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined)
		__NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector((emulation_vector_t)(In0P->emulation_vector.address), In0P->NDR.char_rep, In0P->emulation_vectorCnt);
#endif	/* __NDR_convert__char_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined)
		__NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start(&In0P->vector_start, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_emulation_vector_t__vector_start__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined)
		__NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector((emulation_vector_t)(In0P->emulation_vector.address), In0P->NDR.float_rep, In0P->emulation_vectorCnt);
#endif	/* __NDR_convert__float_rep__Request__task_set_emulation_vector_t__emulation_vector__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_emulation_vector_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_emulation_vector */
mig_internal novalue _Xtask_set_emulation_vector
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t emulation_vector;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int vector_start;
		mach_msg_type_number_t emulation_vectorCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_emulation_vector_t __Request;
	typedef __Reply__task_set_emulation_vector_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_emulation_vector_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_emulation_vector_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3426, "task_set_emulation_vector")
	__BeforeRcvRpc(3426, "task_set_emulation_vector")

#if	defined(__MIG_check__Request__task_set_emulation_vector_t__defined)
	check_result = __MIG_check__Request__task_set_emulation_vector_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_emulation_vector_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_emulation_vector(task, In0P->vector_start, (emulation_vector_t)(In0P->emulation_vector.address), In0P->emulation_vectorCnt);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3426, "task_set_emulation_vector")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_ras_pc_t__defined)
#define __MIG_check__Request__task_set_ras_pc_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#if	defined(__NDR_convert__int_rep__task__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#if	defined(__NDR_convert__int_rep__task__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#if	defined(__NDR_convert__char_rep__task__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#if	defined(__NDR_convert__char_rep__task__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#if	defined(__NDR_convert__float_rep__task__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#if	defined(__NDR_convert__float_rep__task__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__task__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__task__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__task__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined
#define	__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_ras_pc_t(__Request__task_set_ras_pc_t *In0P)
{

	typedef __Request__task_set_ras_pc_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined)
		__NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc(&In0P->basepc, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_ras_pc_t__basepc__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined)
		__NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc(&In0P->boundspc, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_ras_pc_t__boundspc__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined)
		__NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc(&In0P->basepc, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_ras_pc_t__basepc__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined)
		__NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc(&In0P->boundspc, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_ras_pc_t__boundspc__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined)
		__NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc(&In0P->basepc, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_ras_pc_t__basepc__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined)
		__NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc(&In0P->boundspc, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_ras_pc_t__boundspc__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_ras_pc_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_ras_pc */
mig_internal novalue _Xtask_set_ras_pc
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t basepc;
		vm_address_t boundspc;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_ras_pc_t __Request;
	typedef __Reply__task_set_ras_pc_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_ras_pc_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_ras_pc_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t target_task;

	__DeclareRcvRpc(3427, "task_set_ras_pc")
	__BeforeRcvRpc(3427, "task_set_ras_pc")

#if	defined(__MIG_check__Request__task_set_ras_pc_t__defined)
	check_result = __MIG_check__Request__task_set_ras_pc_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_ras_pc_t__defined) */

	target_task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_set_ras_pc(target_task, In0P->basepc, In0P->boundspc);
	task_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3427, "task_set_ras_pc")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_assign_t__defined)
#define __MIG_check__Request__task_assign_t__defined
#ifndef __NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__int_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__int_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined */

#ifndef __NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__char_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__char_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined */

#ifndef __NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__float_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined
#define	__NDR_convert__float_rep__Request__task_assign_t__assign_threads(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined */


mig_internal kern_return_t __MIG_check__Request__task_assign_t(__Request__task_assign_t *In0P)
{

	typedef __Request__task_assign_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined)
		__NDR_convert__int_rep__Request__task_assign_t__assign_threads(&In0P->assign_threads, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_assign_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined)
		__NDR_convert__char_rep__Request__task_assign_t__assign_threads(&In0P->assign_threads, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_assign_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined)
		__NDR_convert__float_rep__Request__task_assign_t__assign_threads(&In0P->assign_threads, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_assign_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_assign_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_assign */
mig_internal novalue _Xtask_assign
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
		boolean_t assign_threads;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_assign_t __Request;
	typedef __Reply__task_assign_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_assign_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_assign_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;
	processor_set_t new_set;

	__DeclareRcvRpc(3429, "task_assign")
	__BeforeRcvRpc(3429, "task_assign")

#if	defined(__MIG_check__Request__task_assign_t__defined)
	check_result = __MIG_check__Request__task_assign_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_assign_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	new_set = convert_port_to_pset(In0P->new_set.name);

	OutP->RetCode = task_assign(task, new_set, In0P->assign_threads);
	pset_deallocate(new_set);
	task_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->new_set.name))
		ipc_port_release_send((ipc_port_t)In0P->new_set.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3429, "task_assign")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_assign_default_t__defined)
#define __MIG_check__Request__task_assign_default_t__defined
#ifndef __NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined */

#ifndef __NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined */

#ifndef __NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined
#define	__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined */


mig_internal kern_return_t __MIG_check__Request__task_assign_default_t(__Request__task_assign_default_t *In0P)
{

	typedef __Request__task_assign_default_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined)
		__NDR_convert__int_rep__Request__task_assign_default_t__assign_threads(&In0P->assign_threads, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_assign_default_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined)
		__NDR_convert__char_rep__Request__task_assign_default_t__assign_threads(&In0P->assign_threads, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_assign_default_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined)
		__NDR_convert__float_rep__Request__task_assign_default_t__assign_threads(&In0P->assign_threads, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_assign_default_t__assign_threads__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_assign_default_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_assign_default */
mig_internal novalue _Xtask_assign_default
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		boolean_t assign_threads;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_assign_default_t __Request;
	typedef __Reply__task_assign_default_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_assign_default_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_assign_default_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;

	__DeclareRcvRpc(3430, "task_assign_default")
	__BeforeRcvRpc(3430, "task_assign_default")

#if	defined(__MIG_check__Request__task_assign_default_t__defined)
	check_result = __MIG_check__Request__task_assign_default_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_assign_default_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	OutP->RetCode = task_assign_default(task, In0P->assign_threads);
	task_deallocate(task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3430, "task_assign_default")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_get_assignment_t__defined)
#define __MIG_check__Request__task_get_assignment_t__defined

mig_internal kern_return_t __MIG_check__Request__task_get_assignment_t(__Request__task_get_assignment_t *In0P)
{

	typedef __Request__task_get_assignment_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_get_assignment_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_get_assignment */
mig_internal novalue _Xtask_get_assignment
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
	typedef __Request__task_get_assignment_t __Request;
	typedef __Reply__task_get_assignment_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_get_assignment_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_get_assignment_t__defined */

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
	task_t task;
	processor_set_name_t assigned_set;

	__DeclareRcvRpc(3431, "task_get_assignment")
	__BeforeRcvRpc(3431, "task_get_assignment")

#if	defined(__MIG_check__Request__task_get_assignment_t__defined)
	check_result = __MIG_check__Request__task_get_assignment_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_get_assignment_t__defined) */

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


	task = convert_port_to_task(In0P->Head.msgh_request_port);

	RetCode = task_get_assignment(task, &assigned_set);
	task_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->assigned_set.name = (mach_port_t)convert_pset_name_to_port(assigned_set);


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3431, "task_get_assignment")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__task_subsystem__
#if !defined(__MIG_check__Request__task_set_policy_t__defined)
#define __MIG_check__Request__task_set_policy_t__defined
#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#if	defined(__NDR_convert__int_rep__task__policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__policy_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__policy__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#if	defined(__NDR_convert__int_rep__task__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_base_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__int_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__task__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__task__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__base__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#if	defined(__NDR_convert__int_rep__task__policy_limit_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__int_rep__task__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__policy_limit_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__int_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__task__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__task__integer_t)
#elif	defined(__NDR_convert__int_rep__integer_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__int_rep__integer_t)
#elif	defined(__NDR_convert__int_rep__task__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__task__int32_t)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__int_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__limit__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined
#if	defined(__NDR_convert__int_rep__task__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt(a, f) \
	__NDR_convert__int_rep__task__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined */

#ifndef __NDR_convert__int_rep__Request__task_set_policy_t__change__defined
#if	defined(__NDR_convert__int_rep__task__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__int_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__int_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_set_policy_t__change__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#if	defined(__NDR_convert__char_rep__task__policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__policy_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_policy_t__policy__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#if	defined(__NDR_convert__char_rep__task__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_base_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__char_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__task__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__task__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_policy_t__base__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#if	defined(__NDR_convert__char_rep__task__policy_limit_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__char_rep__task__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__policy_limit_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__char_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__task__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__task__integer_t)
#elif	defined(__NDR_convert__char_rep__integer_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__char_rep__integer_t)
#elif	defined(__NDR_convert__char_rep__task__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__task__int32_t)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__char_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_policy_t__limit__defined */

#ifndef __NDR_convert__char_rep__Request__task_set_policy_t__change__defined
#if	defined(__NDR_convert__char_rep__task__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__char_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__char_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_set_policy_t__change__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#if	defined(__NDR_convert__float_rep__task__policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__policy_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__policy_t((policy_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__task__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__policy(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_policy_t__policy__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#if	defined(__NDR_convert__float_rep__task__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__task__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_base_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__float_rep__policy_base_t((policy_base_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__task__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__task__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__base(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_policy_t__base__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#if	defined(__NDR_convert__float_rep__task__policy_limit_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__float_rep__task__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__policy_limit_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__float_rep__policy_limit_t((policy_limit_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__task__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__task__integer_t)
#elif	defined(__NDR_convert__float_rep__integer_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((integer_t *)(a), f, c, __NDR_convert__float_rep__integer_t)
#elif	defined(__NDR_convert__float_rep__task__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__task__int32_t)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__limit(a, f, c) \
	__NDR_convert__ARRAY((int32_t *)(a), f, c, __NDR_convert__float_rep__int32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_policy_t__limit__defined */

#ifndef __NDR_convert__float_rep__Request__task_set_policy_t__change__defined
#if	defined(__NDR_convert__float_rep__task__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__float_rep__task__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_set_policy_t__change__defined
#define	__NDR_convert__float_rep__Request__task_set_policy_t__change(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_set_policy_t__change__defined */


mig_internal kern_return_t __MIG_check__Request__task_set_policy_t(__Request__task_set_policy_t *In0P, __Request__task_set_policy_t **In1PP, __Request__task_set_policy_t **In2PP)
{

	typedef __Request__task_set_policy_t __Request;
	__Request *In1P;
	__Request *In2P;
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

#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt(&In0P->baseCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined */
	msgh_size_delta = (4 * In0P->baseCnt);
#if	__MigTypeCheck
	if (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 24) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
	msgh_size -= msgh_size_delta;
#endif	/* __MigTypeCheck */

	*In1PP = In1P = (__Request *) ((pointer_t) In0P + msgh_size_delta - 20);

#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt(&In1P->limitCnt, In1P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined */
	msgh_size_delta = (4 * In1P->limitCnt);
#if	__MigTypeCheck
	if (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 24) + msgh_size_delta)
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	*In2PP = In2P = (__Request *) ((pointer_t) In1P + msgh_size_delta - 4);

#if	defined(__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_policy_t__base__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_policy_t__baseCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_policy_t__limitCnt__defined) || \
	defined(__NDR_convert__int_rep__Request__task_set_policy_t__change__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__policy__defined)
		__NDR_convert__int_rep__Request__task_set_policy_t__policy(&In0P->policy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__policy__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__base__defined)
		__NDR_convert__int_rep__Request__task_set_policy_t__base(&In0P->base, In0P->NDR.int_rep, In0P->baseCnt);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__base__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__limit__defined)
		__NDR_convert__int_rep__Request__task_set_policy_t__limit(&In1P->limit, In0P->NDR.int_rep, In1P->limitCnt);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__limit__defined */
#if defined(__NDR_convert__int_rep__Request__task_set_policy_t__change__defined)
		__NDR_convert__int_rep__Request__task_set_policy_t__change(&In2P->change, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_set_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined) || \
	defined(__NDR_convert__char_rep__Request__task_set_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined) || \
	0 || \
	defined(__NDR_convert__char_rep__Request__task_set_policy_t__change__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_set_policy_t__policy__defined)
		__NDR_convert__char_rep__Request__task_set_policy_t__policy(&In0P->policy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_policy_t__policy__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_policy_t__base__defined)
		__NDR_convert__char_rep__Request__task_set_policy_t__base(&In0P->base, In0P->NDR.char_rep, In0P->baseCnt);
#endif	/* __NDR_convert__char_rep__Request__task_set_policy_t__base__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_policy_t__limit__defined)
		__NDR_convert__char_rep__Request__task_set_policy_t__limit(&In1P->limit, In0P->NDR.char_rep, In1P->limitCnt);
#endif	/* __NDR_convert__char_rep__Request__task_set_policy_t__limit__defined */
#if defined(__NDR_convert__char_rep__Request__task_set_policy_t__change__defined)
		__NDR_convert__char_rep__Request__task_set_policy_t__change(&In2P->change, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_set_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined) || \
	defined(__NDR_convert__float_rep__Request__task_set_policy_t__base__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined) || \
	0 || \
	defined(__NDR_convert__float_rep__Request__task_set_policy_t__change__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_set_policy_t__policy__defined)
		__NDR_convert__float_rep__Request__task_set_policy_t__policy(&In0P->policy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_policy_t__policy__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_policy_t__base__defined)
		__NDR_convert__float_rep__Request__task_set_policy_t__base(&In0P->base, In0P->NDR.float_rep, In0P->baseCnt);
#endif	/* __NDR_convert__float_rep__Request__task_set_policy_t__base__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_policy_t__limit__defined)
		__NDR_convert__float_rep__Request__task_set_policy_t__limit(&In1P->limit, In0P->NDR.float_rep, In1P->limitCnt);
#endif	/* __NDR_convert__float_rep__Request__task_set_policy_t__limit__defined */
#if defined(__NDR_convert__float_rep__Request__task_set_policy_t__change__defined)
		__NDR_convert__float_rep__Request__task_set_policy_t__change(&In2P->change, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_set_policy_t__change__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_set_policy_t__defined) */
#endif /* __MIG_check__Request__task_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_set_policy */
mig_internal novalue _Xtask_set_policy
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
		boolean_t change;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_set_policy_t __Request;
	typedef __Reply__task_set_policy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Request *In1P;
	Request *In2P;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_set_policy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_set_policy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	task_t task;
	processor_set_t pset;

	__DeclareRcvRpc(3432, "task_set_policy")
	__BeforeRcvRpc(3432, "task_set_policy")

#if	defined(__MIG_check__Request__task_set_policy_t__defined)
	check_result = __MIG_check__Request__task_set_policy_t((__Request *)In0P, (__Request **)&In1P, (__Request **)&In2P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_set_policy_t__defined) */

	task = convert_port_to_task(In0P->Head.msgh_request_port);

	pset = convert_port_to_pset(In0P->pset.name);

	OutP->RetCode = task_set_policy(task, pset, In0P->policy, In0P->base, In0P->baseCnt, In1P->limit, In1P->limitCnt, In2P->change);
	pset_deallocate(pset);
	task_deallocate(task);
#if	__MigKernelSpecificCode
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}

	if (IP_VALID((ipc_port_t)In0P->pset.name))
		ipc_port_release_send((ipc_port_t)In0P->pset.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3432, "task_set_policy")
}



/* Description of this subsystem, for use in direct RPC */
const struct task_subsystem task_subsystem = {
	task_server_routine,
	3400,
	3433,
	(mach_msg_size_t)sizeof(union __ReplyUnion__task_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_create, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_terminate, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_terminate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_threads, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_threads_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_ports_register, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_ports_register_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_ports_lookup, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_ports_lookup_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_info, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_info, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_suspend, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_suspend_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_resume, 1, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_resume_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_get_special_port, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_get_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_special_port, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_special_port_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_create, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xthread_create_running, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__thread_create_running_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_exception_ports, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_get_exception_ports, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_get_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_swap_exception_ports, 10, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_swap_exception_ports_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_set_create, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_set_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xlock_set_destroy, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__lock_set_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_create, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_create_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xsemaphore_destroy, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__semaphore_destroy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_policy_set, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_policy_set_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_policy_get, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_policy_get_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_sample, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_sample_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_policy, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_policy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_emulation, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_emulation_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_get_emulation_vector, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_get_emulation_vector_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_emulation_vector, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_emulation_vector_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_ras_pc, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_ras_pc_t)},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_assign, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_assign_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_assign_default, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_assign_default_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_get_assignment, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_get_assignment_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_set_policy, 8, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_set_policy_t)},
	}
};

mig_external boolean_t task_server
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

	if ((InHeadP->msgh_id > 3432) || (InHeadP->msgh_id < 3400) ||
	    ((routine = task_subsystem.routine[InHeadP->msgh_id - 3400].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t task_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 3400;

	if ((msgh_id > 32) || (msgh_id < 0))
		return 0;

	return task_subsystem.routine[msgh_id].stub_routine;
}

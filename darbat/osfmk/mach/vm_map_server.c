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
 * stub generated Tue Mar  7 16:25:34 2006
 * with a MiG generated Sun Apr 10 19:04:13 PDT 2005 by root@turing.apple.com
 * OPTIONS: 
 *	KernelServer
 */

/* Module vm_map */

#define	__MIG_check__Request__vm_map_subsystem__ 1
#define	__NDR_convert__Request__vm_map_subsystem__ 1

#include "vm_map_server.h"

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


mig_internal novalue _Xvm_region
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_allocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_deallocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_protect
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_inherit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_read
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_read_list
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_write
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_copy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_read_overwrite
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_msync
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_behavior_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_map
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_machine_attribute
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_remap
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xtask_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_make_memory_entry
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_map_page_query
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_vm_region_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_mapped_pages_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_region_recurse
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_region_recurse_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_vm_region_info_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_region_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xmach_make_memory_entry_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_map_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xvm_purgable_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_region_t__defined)
#define __MIG_check__Request__vm_region_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_region_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined
#if	defined(__NDR_convert__int_rep__vm_map__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__infoCnt(a, f) \
	__NDR_convert__int_rep__vm_map__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_t__infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__vm_region_t(__Request__vm_region_t *In0P)
{

	typedef __Request__vm_region_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_region_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_region_t__address__defined)
		__NDR_convert__int_rep__Request__vm_region_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_t__flavor__defined)
		__NDR_convert__int_rep__Request__vm_region_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined)
		__NDR_convert__int_rep__Request__vm_region_t__infoCnt(&In0P->infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_t__infoCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_region_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_region_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_region_t__address__defined)
		__NDR_convert__char_rep__Request__vm_region_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_region_t__flavor__defined)
		__NDR_convert__char_rep__Request__vm_region_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_region_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_region_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_region_t__address__defined)
		__NDR_convert__float_rep__Request__vm_region_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_region_t__flavor__defined)
		__NDR_convert__float_rep__Request__vm_region_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_region_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_region */
mig_internal novalue _Xvm_region
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_region_flavor_t flavor;
		mach_msg_type_number_t infoCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_region_t __Request;
	typedef __Reply__vm_region_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_region_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_region_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	vm_map_t target_task;

	__DeclareRcvRpc(3800, "vm_region")
	__BeforeRcvRpc(3800, "vm_region")

#if	defined(__MIG_check__Request__vm_region_t__defined)
	check_result = __MIG_check__Request__vm_region_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_region_t__defined) */

#if	UseStaticTemplates
	OutP->object_name = object_nameTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->object_name.disposition = 17;
#else
	OutP->object_name.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->object_name.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->infoCnt = 10;
	if (In0P->infoCnt < OutP->infoCnt)
		OutP->infoCnt = In0P->infoCnt;

	RetCode = vm_region(target_task, &In0P->address, &OutP->size, In0P->flavor, OutP->info, &OutP->infoCnt, &OutP->object_name.name);
	vm_map_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 40) + (((4 * OutP->infoCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3800, "vm_region")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_allocate_t__defined)
#define __MIG_check__Request__vm_allocate_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_allocate_t__flags__defined
#if	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_allocate_t__flags__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_allocate_t__flags__defined
#if	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_allocate_t__flags__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_allocate_t__flags__defined
#if	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_allocate_t__flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_allocate_t__flags__defined */


mig_internal kern_return_t __MIG_check__Request__vm_allocate_t(__Request__vm_allocate_t *In0P)
{

	typedef __Request__vm_allocate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_allocate_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_allocate_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_allocate_t__address__defined)
		__NDR_convert__int_rep__Request__vm_allocate_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_allocate_t__size__defined)
		__NDR_convert__int_rep__Request__vm_allocate_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_allocate_t__flags__defined)
		__NDR_convert__int_rep__Request__vm_allocate_t__flags(&In0P->flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_allocate_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_allocate_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_allocate_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_allocate_t__address__defined)
		__NDR_convert__char_rep__Request__vm_allocate_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_allocate_t__size__defined)
		__NDR_convert__char_rep__Request__vm_allocate_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_allocate_t__flags__defined)
		__NDR_convert__char_rep__Request__vm_allocate_t__flags(&In0P->flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_allocate_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_allocate_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_allocate_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_allocate_t__address__defined)
		__NDR_convert__float_rep__Request__vm_allocate_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_allocate_t__size__defined)
		__NDR_convert__float_rep__Request__vm_allocate_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_allocate_t__flags__defined)
		__NDR_convert__float_rep__Request__vm_allocate_t__flags(&In0P->flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_allocate_t__flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_allocate_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_allocate */
mig_internal novalue _Xvm_allocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		int flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_allocate_t __Request;
	typedef __Reply__vm_allocate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_allocate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_allocate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3801, "vm_allocate")
	__BeforeRcvRpc(3801, "vm_allocate")

#if	defined(__MIG_check__Request__vm_allocate_t__defined)
	check_result = __MIG_check__Request__vm_allocate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_allocate_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_allocate(target_task, &In0P->address, In0P->size, In0P->flags);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3801, "vm_allocate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_deallocate_t__defined)
#define __MIG_check__Request__vm_deallocate_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_deallocate_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_deallocate_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_deallocate_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_deallocate_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_deallocate_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_deallocate_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_deallocate_t__size__defined */


mig_internal kern_return_t __MIG_check__Request__vm_deallocate_t(__Request__vm_deallocate_t *In0P)
{

	typedef __Request__vm_deallocate_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_deallocate_t__address__defined)
		__NDR_convert__int_rep__Request__vm_deallocate_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_deallocate_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_deallocate_t__size__defined)
		__NDR_convert__int_rep__Request__vm_deallocate_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_deallocate_t__size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_deallocate_t__address__defined)
		__NDR_convert__char_rep__Request__vm_deallocate_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_deallocate_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_deallocate_t__size__defined)
		__NDR_convert__char_rep__Request__vm_deallocate_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_deallocate_t__size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_deallocate_t__address__defined)
		__NDR_convert__float_rep__Request__vm_deallocate_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_deallocate_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_deallocate_t__size__defined)
		__NDR_convert__float_rep__Request__vm_deallocate_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_deallocate_t__size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_deallocate_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_deallocate */
mig_internal novalue _Xvm_deallocate
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_deallocate_t __Request;
	typedef __Reply__vm_deallocate_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_deallocate_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_deallocate_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3802, "vm_deallocate")
	__BeforeRcvRpc(3802, "vm_deallocate")

#if	defined(__MIG_check__Request__vm_deallocate_t__defined)
	check_result = __MIG_check__Request__vm_deallocate_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_deallocate_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_deallocate(target_task, In0P->address, In0P->size);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3802, "vm_deallocate")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_protect_t__defined)
#define __MIG_check__Request__vm_protect_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_protect_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_protect_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_protect_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_protect_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined */

#ifndef __NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__int_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined */

#ifndef __NDR_convert__char_rep__Request__vm_protect_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_protect_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_protect_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_protect_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined */

#ifndef __NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__char_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined */

#ifndef __NDR_convert__float_rep__Request__vm_protect_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_protect_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_protect_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_protect_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__set_maximum(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined */

#ifndef __NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined
#define	__NDR_convert__float_rep__Request__vm_protect_t__new_protection(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined */


mig_internal kern_return_t __MIG_check__Request__vm_protect_t(__Request__vm_protect_t *In0P)
{

	typedef __Request__vm_protect_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_protect_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_protect_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_protect_t__address__defined)
		__NDR_convert__int_rep__Request__vm_protect_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_protect_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_protect_t__size__defined)
		__NDR_convert__int_rep__Request__vm_protect_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_protect_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined)
		__NDR_convert__int_rep__Request__vm_protect_t__set_maximum(&In0P->set_maximum, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_protect_t__set_maximum__defined */
#if defined(__NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined)
		__NDR_convert__int_rep__Request__vm_protect_t__new_protection(&In0P->new_protection, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_protect_t__new_protection__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_protect_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_protect_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_protect_t__address__defined)
		__NDR_convert__char_rep__Request__vm_protect_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_protect_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_protect_t__size__defined)
		__NDR_convert__char_rep__Request__vm_protect_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_protect_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined)
		__NDR_convert__char_rep__Request__vm_protect_t__set_maximum(&In0P->set_maximum, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_protect_t__set_maximum__defined */
#if defined(__NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined)
		__NDR_convert__char_rep__Request__vm_protect_t__new_protection(&In0P->new_protection, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_protect_t__new_protection__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_protect_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_protect_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_protect_t__address__defined)
		__NDR_convert__float_rep__Request__vm_protect_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_protect_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_protect_t__size__defined)
		__NDR_convert__float_rep__Request__vm_protect_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_protect_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined)
		__NDR_convert__float_rep__Request__vm_protect_t__set_maximum(&In0P->set_maximum, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_protect_t__set_maximum__defined */
#if defined(__NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined)
		__NDR_convert__float_rep__Request__vm_protect_t__new_protection(&In0P->new_protection, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_protect_t__new_protection__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_protect_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_protect */
mig_internal novalue _Xvm_protect
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		boolean_t set_maximum;
		vm_prot_t new_protection;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_protect_t __Request;
	typedef __Reply__vm_protect_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_protect_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_protect_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3803, "vm_protect")
	__BeforeRcvRpc(3803, "vm_protect")

#if	defined(__MIG_check__Request__vm_protect_t__defined)
	check_result = __MIG_check__Request__vm_protect_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_protect_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_protect(target_task, In0P->address, In0P->size, In0P->set_maximum, In0P->new_protection);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3803, "vm_protect")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_inherit_t__defined)
#define __MIG_check__Request__vm_inherit_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_inherit_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_inherit_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined */

#ifndef __NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_inherit_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_inherit_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined */

#ifndef __NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_inherit_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_inherit_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined */


mig_internal kern_return_t __MIG_check__Request__vm_inherit_t(__Request__vm_inherit_t *In0P)
{

	typedef __Request__vm_inherit_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_inherit_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_inherit_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_inherit_t__address__defined)
		__NDR_convert__int_rep__Request__vm_inherit_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_inherit_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_inherit_t__size__defined)
		__NDR_convert__int_rep__Request__vm_inherit_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_inherit_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined)
		__NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance(&In0P->new_inheritance, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_inherit_t__new_inheritance__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_inherit_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_inherit_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_inherit_t__address__defined)
		__NDR_convert__char_rep__Request__vm_inherit_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_inherit_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_inherit_t__size__defined)
		__NDR_convert__char_rep__Request__vm_inherit_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_inherit_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined)
		__NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance(&In0P->new_inheritance, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_inherit_t__new_inheritance__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_inherit_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_inherit_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_inherit_t__address__defined)
		__NDR_convert__float_rep__Request__vm_inherit_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_inherit_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_inherit_t__size__defined)
		__NDR_convert__float_rep__Request__vm_inherit_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_inherit_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined)
		__NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance(&In0P->new_inheritance, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_inherit_t__new_inheritance__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_inherit_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_inherit */
mig_internal novalue _Xvm_inherit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_inherit_t new_inheritance;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_inherit_t __Request;
	typedef __Reply__vm_inherit_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_inherit_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_inherit_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3804, "vm_inherit")
	__BeforeRcvRpc(3804, "vm_inherit")

#if	defined(__MIG_check__Request__vm_inherit_t__defined)
	check_result = __MIG_check__Request__vm_inherit_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_inherit_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_inherit(target_task, In0P->address, In0P->size, In0P->new_inheritance);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3804, "vm_inherit")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_read_t__defined)
#define __MIG_check__Request__vm_read_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_read_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_read_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_t__size__defined */


mig_internal kern_return_t __MIG_check__Request__vm_read_t(__Request__vm_read_t *In0P)
{

	typedef __Request__vm_read_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_read_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_read_t__size__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_read_t__address__defined)
		__NDR_convert__int_rep__Request__vm_read_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_read_t__size__defined)
		__NDR_convert__int_rep__Request__vm_read_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_t__size__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_read_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_read_t__size__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_read_t__address__defined)
		__NDR_convert__char_rep__Request__vm_read_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_read_t__size__defined)
		__NDR_convert__char_rep__Request__vm_read_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_t__size__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_read_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_read_t__size__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_read_t__address__defined)
		__NDR_convert__float_rep__Request__vm_read_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_read_t__size__defined)
		__NDR_convert__float_rep__Request__vm_read_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_t__size__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_read_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_read */
mig_internal novalue _Xvm_read
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_read_t __Request;
	typedef __Reply__vm_read_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_read_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_read_t__defined */

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
	vm_map_t target_task;

	__DeclareRcvRpc(3805, "vm_read")
	__BeforeRcvRpc(3805, "vm_read")

#if	defined(__MIG_check__Request__vm_read_t__defined)
	check_result = __MIG_check__Request__vm_read_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_read_t__defined) */

#if	UseStaticTemplates
	OutP->data = dataTemplate;
#else	/* UseStaticTemplates */
	OutP->data.deallocate =  FALSE;
	OutP->data.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->data.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = vm_read(target_task, In0P->address, In0P->size, (vm_offset_t *)&(OutP->data.address), &OutP->dataCnt);
	vm_map_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->data.size = OutP->dataCnt;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3805, "vm_read")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_read_list_t__defined)
#define __MIG_check__Request__vm_read_list_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_read_entry_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__int_rep__vm_map__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_read_entry_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__int_rep__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__int_rep__vm_map__vm_offset_t)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__int_rep__vm_offset_t)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__int_rep__vm_map__natural_t)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__int_rep__natural_t)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__int_rep__vm_map__uint32_t)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__int_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined */

#ifndef __NDR_convert__int_rep__Request__vm_read_list_t__count__defined
#if	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__int_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_list_t__count__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_read_entry_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__char_rep__vm_map__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_read_entry_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__char_rep__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__char_rep__vm_map__vm_offset_t)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__char_rep__vm_offset_t)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__char_rep__vm_map__natural_t)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__char_rep__natural_t)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__char_rep__vm_map__uint32_t)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__char_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_list_t__count__defined
#if	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__char_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_list_t__count__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_read_entry_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__float_rep__vm_map__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_read_entry_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__float_rep__vm_read_entry_t((vm_read_entry_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__float_rep__vm_map__vm_offset_t)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((vm_offset_t *)(a), f, 512, __NDR_convert__float_rep__vm_offset_t)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__float_rep__vm_map__natural_t)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((natural_t *)(a), f, 512, __NDR_convert__float_rep__natural_t)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__float_rep__vm_map__uint32_t)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__data_list(a, f) \
	__NDR_convert__ARRAY((uint32_t *)(a), f, 512, __NDR_convert__float_rep__uint32_t)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_list_t__count__defined
#if	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count__defined
#define	__NDR_convert__float_rep__Request__vm_read_list_t__count(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_list_t__count__defined */


mig_internal kern_return_t __MIG_check__Request__vm_read_list_t(__Request__vm_read_list_t *In0P)
{

	typedef __Request__vm_read_list_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_read_list_t__count__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined)
		__NDR_convert__int_rep__Request__vm_read_list_t__data_list(&In0P->data_list, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_list_t__data_list__defined */
#if defined(__NDR_convert__int_rep__Request__vm_read_list_t__count__defined)
		__NDR_convert__int_rep__Request__vm_read_list_t__count(&In0P->count, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_list_t__count__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_read_list_t__count__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined)
		__NDR_convert__char_rep__Request__vm_read_list_t__data_list(&In0P->data_list, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_list_t__data_list__defined */
#if defined(__NDR_convert__char_rep__Request__vm_read_list_t__count__defined)
		__NDR_convert__char_rep__Request__vm_read_list_t__count(&In0P->count, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_list_t__count__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_read_list_t__count__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined)
		__NDR_convert__float_rep__Request__vm_read_list_t__data_list(&In0P->data_list, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_list_t__data_list__defined */
#if defined(__NDR_convert__float_rep__Request__vm_read_list_t__count__defined)
		__NDR_convert__float_rep__Request__vm_read_list_t__count(&In0P->count, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_list_t__count__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_read_list_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_read_list */
mig_internal novalue _Xvm_read_list
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_read_entry_t data_list;
		natural_t count;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_read_list_t __Request;
	typedef __Reply__vm_read_list_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_read_list_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_read_list_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3806, "vm_read_list")
	__BeforeRcvRpc(3806, "vm_read_list")

#if	defined(__MIG_check__Request__vm_read_list_t__defined)
	check_result = __MIG_check__Request__vm_read_list_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_read_list_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_read_list(target_task, In0P->data_list, In0P->count);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	{   typedef struct { char data[2048]; } *sp;
	    * (sp) OutP->data_list = * (sp) In0P->data_list;
	}

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3806, "vm_read_list")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_write_t__defined)
#define __MIG_check__Request__vm_write_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_write_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_write_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_write_t__data__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__int_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_write_t__data__defined */

#ifndef __NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined
#if	defined(__NDR_convert__int_rep__vm_map__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__dataCnt(a, f) \
	__NDR_convert__int_rep__vm_map__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined
#define	__NDR_convert__int_rep__Request__vm_write_t__dataCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined */

#ifndef __NDR_convert__char_rep__Request__vm_write_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_write_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_write_t__data__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__char_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_write_t__data__defined */

#ifndef __NDR_convert__float_rep__Request__vm_write_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_write_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_write_t__data__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__float_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f, c)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_write_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_write_t__data(a, f, c) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f, c)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_write_t__data__defined */


mig_internal kern_return_t __MIG_check__Request__vm_write_t(__Request__vm_write_t *In0P)
{

	typedef __Request__vm_write_t __Request;
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

#if	defined(__NDR_convert__int_rep__Request__vm_write_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_write_t__data__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_write_t__address__defined)
		__NDR_convert__int_rep__Request__vm_write_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_write_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined)
		__NDR_convert__int_rep__Request__vm_write_t__dataCnt(&In0P->dataCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_write_t__dataCnt__defined */
#if defined(__NDR_convert__int_rep__Request__vm_write_t__data__defined)
		__NDR_convert__int_rep__Request__vm_write_t__data((vm_offset_t)(In0P->data.address), In0P->NDR.int_rep, In0P->dataCnt);
#endif	/* __NDR_convert__int_rep__Request__vm_write_t__data__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_write_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_write_t__data__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_write_t__address__defined)
		__NDR_convert__char_rep__Request__vm_write_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_write_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_write_t__data__defined)
		__NDR_convert__char_rep__Request__vm_write_t__data((vm_offset_t)(In0P->data.address), In0P->NDR.char_rep, In0P->dataCnt);
#endif	/* __NDR_convert__char_rep__Request__vm_write_t__data__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_write_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_write_t__data__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_write_t__address__defined)
		__NDR_convert__float_rep__Request__vm_write_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_write_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_write_t__data__defined)
		__NDR_convert__float_rep__Request__vm_write_t__data((vm_offset_t)(In0P->data.address), In0P->NDR.float_rep, In0P->dataCnt);
#endif	/* __NDR_convert__float_rep__Request__vm_write_t__data__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_write_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_write */
mig_internal novalue _Xvm_write
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
		vm_address_t address;
		mach_msg_type_number_t dataCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_write_t __Request;
	typedef __Reply__vm_write_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_write_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_write_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3807, "vm_write")
	__BeforeRcvRpc(3807, "vm_write")

#if	defined(__MIG_check__Request__vm_write_t__defined)
	check_result = __MIG_check__Request__vm_write_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_write_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_write(target_task, In0P->address, (vm_offset_t)(In0P->data.address), In0P->dataCnt);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3807, "vm_write")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_copy_t__defined)
#define __MIG_check__Request__vm_copy_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_copy_t__source_address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_copy_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_copy_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__int_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_copy_t__source_address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_copy_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_copy_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__char_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__source_address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_copy_t__source_address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_copy_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_copy_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined
#define	__NDR_convert__float_rep__Request__vm_copy_t__dest_address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined */


mig_internal kern_return_t __MIG_check__Request__vm_copy_t(__Request__vm_copy_t *In0P)
{

	typedef __Request__vm_copy_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_copy_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_copy_t__source_address__defined)
		__NDR_convert__int_rep__Request__vm_copy_t__source_address(&In0P->source_address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_copy_t__source_address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_copy_t__size__defined)
		__NDR_convert__int_rep__Request__vm_copy_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_copy_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined)
		__NDR_convert__int_rep__Request__vm_copy_t__dest_address(&In0P->dest_address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_copy_t__dest_address__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_copy_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_copy_t__source_address__defined)
		__NDR_convert__char_rep__Request__vm_copy_t__source_address(&In0P->source_address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_copy_t__source_address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_copy_t__size__defined)
		__NDR_convert__char_rep__Request__vm_copy_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_copy_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined)
		__NDR_convert__char_rep__Request__vm_copy_t__dest_address(&In0P->dest_address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_copy_t__dest_address__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_copy_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_copy_t__source_address__defined)
		__NDR_convert__float_rep__Request__vm_copy_t__source_address(&In0P->source_address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_copy_t__source_address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_copy_t__size__defined)
		__NDR_convert__float_rep__Request__vm_copy_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_copy_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined)
		__NDR_convert__float_rep__Request__vm_copy_t__dest_address(&In0P->dest_address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_copy_t__dest_address__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_copy_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_copy */
mig_internal novalue _Xvm_copy
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t source_address;
		vm_size_t size;
		vm_address_t dest_address;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_copy_t __Request;
	typedef __Reply__vm_copy_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_copy_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_copy_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3808, "vm_copy")
	__BeforeRcvRpc(3808, "vm_copy")

#if	defined(__MIG_check__Request__vm_copy_t__defined)
	check_result = __MIG_check__Request__vm_copy_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_copy_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_copy(target_task, In0P->source_address, In0P->size, In0P->dest_address);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3808, "vm_copy")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_read_overwrite_t__defined)
#define __MIG_check__Request__vm_read_overwrite_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined
#define	__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined */


mig_internal kern_return_t __MIG_check__Request__vm_read_overwrite_t(__Request__vm_read_overwrite_t *In0P)
{

	typedef __Request__vm_read_overwrite_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined)
		__NDR_convert__int_rep__Request__vm_read_overwrite_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_overwrite_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined)
		__NDR_convert__int_rep__Request__vm_read_overwrite_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_overwrite_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined)
		__NDR_convert__int_rep__Request__vm_read_overwrite_t__data(&In0P->data, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_read_overwrite_t__data__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined)
		__NDR_convert__char_rep__Request__vm_read_overwrite_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_overwrite_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined)
		__NDR_convert__char_rep__Request__vm_read_overwrite_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_overwrite_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined)
		__NDR_convert__char_rep__Request__vm_read_overwrite_t__data(&In0P->data, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_read_overwrite_t__data__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined)
		__NDR_convert__float_rep__Request__vm_read_overwrite_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_overwrite_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined)
		__NDR_convert__float_rep__Request__vm_read_overwrite_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_overwrite_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined)
		__NDR_convert__float_rep__Request__vm_read_overwrite_t__data(&In0P->data, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_read_overwrite_t__data__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_read_overwrite_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_read_overwrite */
mig_internal novalue _Xvm_read_overwrite
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_address_t data;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_read_overwrite_t __Request;
	typedef __Reply__vm_read_overwrite_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_read_overwrite_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_read_overwrite_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3809, "vm_read_overwrite")
	__BeforeRcvRpc(3809, "vm_read_overwrite")

#if	defined(__MIG_check__Request__vm_read_overwrite_t__defined)
	check_result = __MIG_check__Request__vm_read_overwrite_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_read_overwrite_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_read_overwrite(target_task, In0P->address, In0P->size, In0P->data, &OutP->outsize);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3809, "vm_read_overwrite")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_msync_t__defined)
#define __MIG_check__Request__vm_msync_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_msync_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_msync_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_msync_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_msync_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_sync_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__vm_map__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_sync_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined */

#ifndef __NDR_convert__char_rep__Request__vm_msync_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_msync_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_msync_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_msync_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_sync_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__vm_map__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_sync_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined */

#ifndef __NDR_convert__float_rep__Request__vm_msync_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_msync_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_msync_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_msync_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_sync_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__vm_map__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_sync_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__vm_sync_t((vm_sync_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined
#define	__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined */


mig_internal kern_return_t __MIG_check__Request__vm_msync_t(__Request__vm_msync_t *In0P)
{

	typedef __Request__vm_msync_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_msync_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_msync_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_msync_t__address__defined)
		__NDR_convert__int_rep__Request__vm_msync_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_msync_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_msync_t__size__defined)
		__NDR_convert__int_rep__Request__vm_msync_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_msync_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined)
		__NDR_convert__int_rep__Request__vm_msync_t__sync_flags(&In0P->sync_flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_msync_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_msync_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_msync_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_msync_t__address__defined)
		__NDR_convert__char_rep__Request__vm_msync_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_msync_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_msync_t__size__defined)
		__NDR_convert__char_rep__Request__vm_msync_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_msync_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined)
		__NDR_convert__char_rep__Request__vm_msync_t__sync_flags(&In0P->sync_flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_msync_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_msync_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_msync_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_msync_t__address__defined)
		__NDR_convert__float_rep__Request__vm_msync_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_msync_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_msync_t__size__defined)
		__NDR_convert__float_rep__Request__vm_msync_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_msync_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined)
		__NDR_convert__float_rep__Request__vm_msync_t__sync_flags(&In0P->sync_flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_msync_t__sync_flags__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_msync_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_msync */
mig_internal novalue _Xvm_msync
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_sync_t sync_flags;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_msync_t __Request;
	typedef __Reply__vm_msync_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_msync_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_msync_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3810, "vm_msync")
	__BeforeRcvRpc(3810, "vm_msync")

#if	defined(__MIG_check__Request__vm_msync_t__defined)
	check_result = __MIG_check__Request__vm_msync_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_msync_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_msync(target_task, In0P->address, In0P->size, In0P->sync_flags);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3810, "vm_msync")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_behavior_set_t__defined)
#define __MIG_check__Request__vm_behavior_set_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__vm_map__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_behavior_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined */

#ifndef __NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__vm_map__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_behavior_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined */

#ifndef __NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__vm_map__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_behavior_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__vm_behavior_t((vm_behavior_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined
#define	__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined */


mig_internal kern_return_t __MIG_check__Request__vm_behavior_set_t(__Request__vm_behavior_set_t *In0P)
{

	typedef __Request__vm_behavior_set_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined)
		__NDR_convert__int_rep__Request__vm_behavior_set_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_behavior_set_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined)
		__NDR_convert__int_rep__Request__vm_behavior_set_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_behavior_set_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined)
		__NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior(&In0P->new_behavior, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_behavior_set_t__new_behavior__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined)
		__NDR_convert__char_rep__Request__vm_behavior_set_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_behavior_set_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined)
		__NDR_convert__char_rep__Request__vm_behavior_set_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_behavior_set_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined)
		__NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior(&In0P->new_behavior, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_behavior_set_t__new_behavior__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined)
		__NDR_convert__float_rep__Request__vm_behavior_set_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_behavior_set_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined)
		__NDR_convert__float_rep__Request__vm_behavior_set_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_behavior_set_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined)
		__NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior(&In0P->new_behavior, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_behavior_set_t__new_behavior__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_behavior_set_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_behavior_set */
mig_internal novalue _Xvm_behavior_set
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_behavior_t new_behavior;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_behavior_set_t __Request;
	typedef __Reply__vm_behavior_set_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_behavior_set_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_behavior_set_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3811, "vm_behavior_set")
	__BeforeRcvRpc(3811, "vm_behavior_set")

#if	defined(__MIG_check__Request__vm_behavior_set_t__defined)
	check_result = __MIG_check__Request__vm_behavior_set_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_behavior_set_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_behavior_set(target_task, In0P->address, In0P->size, In0P->new_behavior);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3811, "vm_behavior_set")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_map_t__defined)
#define __MIG_check__Request__vm_map_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_map_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__mask__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__mask__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__flags__defined
#if	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__flags__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__offset__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__copy__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__copy__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__max_protection__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_t__inheritance__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__mask__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__mask__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__flags__defined
#if	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__flags__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__offset__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__copy__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__copy__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__max_protection__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_t__inheritance__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__mask__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__mask(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__mask__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__flags__defined
#if	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__flags__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__offset__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__offset(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__copy__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__copy(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__copy__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__cur_protection(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__max_protection(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__max_protection__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_t__inheritance(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_t__inheritance__defined */


mig_internal kern_return_t __MIG_check__Request__vm_map_t(__Request__vm_map_t *In0P)
{

	typedef __Request__vm_map_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->object.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->object.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_map_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__mask__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__flags__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__copy__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_map_t__address__defined)
		__NDR_convert__int_rep__Request__vm_map_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__size__defined)
		__NDR_convert__int_rep__Request__vm_map_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__mask__defined)
		__NDR_convert__int_rep__Request__vm_map_t__mask(&In0P->mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__mask__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__flags__defined)
		__NDR_convert__int_rep__Request__vm_map_t__flags(&In0P->flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__flags__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__offset__defined)
		__NDR_convert__int_rep__Request__vm_map_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__copy__defined)
		__NDR_convert__int_rep__Request__vm_map_t__copy(&In0P->copy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__copy__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined)
		__NDR_convert__int_rep__Request__vm_map_t__cur_protection(&In0P->cur_protection, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__cur_protection__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__max_protection__defined)
		__NDR_convert__int_rep__Request__vm_map_t__max_protection(&In0P->max_protection, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__max_protection__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_t__inheritance__defined)
		__NDR_convert__int_rep__Request__vm_map_t__inheritance(&In0P->inheritance, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_map_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__mask__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__flags__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__copy__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_map_t__address__defined)
		__NDR_convert__char_rep__Request__vm_map_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__size__defined)
		__NDR_convert__char_rep__Request__vm_map_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__mask__defined)
		__NDR_convert__char_rep__Request__vm_map_t__mask(&In0P->mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__mask__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__flags__defined)
		__NDR_convert__char_rep__Request__vm_map_t__flags(&In0P->flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__flags__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__offset__defined)
		__NDR_convert__char_rep__Request__vm_map_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__copy__defined)
		__NDR_convert__char_rep__Request__vm_map_t__copy(&In0P->copy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__copy__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined)
		__NDR_convert__char_rep__Request__vm_map_t__cur_protection(&In0P->cur_protection, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__cur_protection__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__max_protection__defined)
		__NDR_convert__char_rep__Request__vm_map_t__max_protection(&In0P->max_protection, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__max_protection__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_t__inheritance__defined)
		__NDR_convert__char_rep__Request__vm_map_t__inheritance(&In0P->inheritance, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_map_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__mask__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__flags__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__copy__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_map_t__address__defined)
		__NDR_convert__float_rep__Request__vm_map_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__size__defined)
		__NDR_convert__float_rep__Request__vm_map_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__mask__defined)
		__NDR_convert__float_rep__Request__vm_map_t__mask(&In0P->mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__mask__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__flags__defined)
		__NDR_convert__float_rep__Request__vm_map_t__flags(&In0P->flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__flags__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__offset__defined)
		__NDR_convert__float_rep__Request__vm_map_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__copy__defined)
		__NDR_convert__float_rep__Request__vm_map_t__copy(&In0P->copy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__copy__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined)
		__NDR_convert__float_rep__Request__vm_map_t__cur_protection(&In0P->cur_protection, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__cur_protection__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__max_protection__defined)
		__NDR_convert__float_rep__Request__vm_map_t__max_protection(&In0P->max_protection, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__max_protection__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_t__inheritance__defined)
		__NDR_convert__float_rep__Request__vm_map_t__inheritance(&In0P->inheritance, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_map_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_map */
mig_internal novalue _Xvm_map
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t object;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_address_t mask;
		int flags;
		vm_offset_t offset;
		boolean_t copy;
		vm_prot_t cur_protection;
		vm_prot_t max_protection;
		vm_inherit_t inheritance;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_map_t __Request;
	typedef __Reply__vm_map_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_map_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_map_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3812, "vm_map")
	__BeforeRcvRpc(3812, "vm_map")

#if	defined(__MIG_check__Request__vm_map_t__defined)
	check_result = __MIG_check__Request__vm_map_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_map_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_map(target_task, &In0P->address, In0P->size, In0P->mask, In0P->flags, null_conversion(In0P->object.name), In0P->offset, In0P->copy, In0P->cur_protection, In0P->max_protection, In0P->inheritance);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->object.name))
		ipc_port_release_send((ipc_port_t)In0P->object.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3812, "vm_map")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_machine_attribute_t__defined)
#define __MIG_check__Request__vm_machine_attribute_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_machine_attribute_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__vm_map__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_machine_attribute_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined */

#ifndef __NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__vm_map__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined */

#ifndef __NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_machine_attribute_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__vm_map__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_machine_attribute_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined */

#ifndef __NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__vm_map__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined */

#ifndef __NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_machine_attribute_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__vm_map__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_machine_attribute_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__vm_machine_attribute_t((vm_machine_attribute_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined */

#ifndef __NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__vm_map__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_machine_attribute_val_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__vm_machine_attribute_val_t((vm_machine_attribute_val_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined
#define	__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined */


mig_internal kern_return_t __MIG_check__Request__vm_machine_attribute_t(__Request__vm_machine_attribute_t *In0P)
{

	typedef __Request__vm_machine_attribute_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined)
		__NDR_convert__int_rep__Request__vm_machine_attribute_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_machine_attribute_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined)
		__NDR_convert__int_rep__Request__vm_machine_attribute_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_machine_attribute_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined)
		__NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute(&In0P->attribute, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_machine_attribute_t__attribute__defined */
#if defined(__NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined)
		__NDR_convert__int_rep__Request__vm_machine_attribute_t__value(&In0P->value, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_machine_attribute_t__value__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined)
		__NDR_convert__char_rep__Request__vm_machine_attribute_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_machine_attribute_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined)
		__NDR_convert__char_rep__Request__vm_machine_attribute_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_machine_attribute_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined)
		__NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute(&In0P->attribute, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_machine_attribute_t__attribute__defined */
#if defined(__NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined)
		__NDR_convert__char_rep__Request__vm_machine_attribute_t__value(&In0P->value, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_machine_attribute_t__value__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined)
		__NDR_convert__float_rep__Request__vm_machine_attribute_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_machine_attribute_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined)
		__NDR_convert__float_rep__Request__vm_machine_attribute_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_machine_attribute_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined)
		__NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute(&In0P->attribute, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_machine_attribute_t__attribute__defined */
#if defined(__NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined)
		__NDR_convert__float_rep__Request__vm_machine_attribute_t__value(&In0P->value, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_machine_attribute_t__value__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_machine_attribute_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_machine_attribute */
mig_internal novalue _Xvm_machine_attribute
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_machine_attribute_t attribute;
		vm_machine_attribute_val_t value;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_machine_attribute_t __Request;
	typedef __Reply__vm_machine_attribute_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_machine_attribute_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_machine_attribute_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3813, "vm_machine_attribute")
	__BeforeRcvRpc(3813, "vm_machine_attribute")

#if	defined(__MIG_check__Request__vm_machine_attribute_t__defined)
	check_result = __MIG_check__Request__vm_machine_attribute_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_machine_attribute_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_machine_attribute(target_task, In0P->address, In0P->size, In0P->attribute, &In0P->value);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->value = In0P->value;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3813, "vm_machine_attribute")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_remap_t__defined)
#define __MIG_check__Request__vm_remap_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__target_address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__mask__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__src_address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__copy__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__copy__defined */

#ifndef __NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__target_address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__mask__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__src_address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__copy__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__copy__defined */

#ifndef __NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__target_address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__target_address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__mask(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__mask__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__anywhere(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__src_address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__src_address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__copy__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__copy(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__copy__defined */

#ifndef __NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_remap_t__inheritance(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined */


mig_internal kern_return_t __MIG_check__Request__vm_remap_t(__Request__vm_remap_t *In0P)
{

	typedef __Request__vm_remap_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->src_task.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->src_task.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__mask__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__copy__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__target_address__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__target_address(&In0P->target_address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__target_address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__size__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__mask__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__mask(&In0P->mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__mask__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__anywhere(&In0P->anywhere, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__anywhere__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__src_address__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__src_address(&In0P->src_address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__src_address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__copy__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__copy(&In0P->copy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__copy__defined */
#if defined(__NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined)
		__NDR_convert__int_rep__Request__vm_remap_t__inheritance(&In0P->inheritance, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_remap_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__mask__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__copy__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__target_address__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__target_address(&In0P->target_address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__target_address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__size__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__mask__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__mask(&In0P->mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__mask__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__anywhere(&In0P->anywhere, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__anywhere__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__src_address__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__src_address(&In0P->src_address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__src_address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__copy__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__copy(&In0P->copy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__copy__defined */
#if defined(__NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined)
		__NDR_convert__char_rep__Request__vm_remap_t__inheritance(&In0P->inheritance, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_remap_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__mask__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__copy__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__target_address__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__target_address(&In0P->target_address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__target_address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__size__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__mask__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__mask(&In0P->mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__mask__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__anywhere(&In0P->anywhere, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__anywhere__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__src_address__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__src_address(&In0P->src_address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__src_address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__copy__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__copy(&In0P->copy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__copy__defined */
#if defined(__NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined)
		__NDR_convert__float_rep__Request__vm_remap_t__inheritance(&In0P->inheritance, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_remap_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_remap_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_remap */
mig_internal novalue _Xvm_remap
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t src_task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_address_t target_address;
		vm_size_t size;
		vm_address_t mask;
		boolean_t anywhere;
		vm_address_t src_address;
		boolean_t copy;
		vm_inherit_t inheritance;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_remap_t __Request;
	typedef __Reply__vm_remap_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_remap_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_remap_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;
	vm_map_t src_task;

	__DeclareRcvRpc(3814, "vm_remap")
	__BeforeRcvRpc(3814, "vm_remap")

#if	defined(__MIG_check__Request__vm_remap_t__defined)
	check_result = __MIG_check__Request__vm_remap_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_remap_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	src_task = convert_port_to_map(In0P->src_task.name);

	OutP->RetCode = vm_remap(target_task, &In0P->target_address, In0P->size, In0P->mask, In0P->anywhere, src_task, In0P->src_address, In0P->copy, &OutP->cur_protection, &OutP->max_protection, In0P->inheritance);
	vm_map_deallocate(src_task);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->src_task.name))
		ipc_port_release_send((ipc_port_t)In0P->src_task.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->target_address = In0P->target_address;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3814, "vm_remap")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__task_wire_t__defined)
#define __MIG_check__Request__task_wire_t__defined
#ifndef __NDR_convert__int_rep__Request__task_wire_t__must_wire__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__int_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__int_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__task_wire_t__must_wire__defined */

#ifndef __NDR_convert__char_rep__Request__task_wire_t__must_wire__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__char_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__char_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__task_wire_t__must_wire__defined */

#ifndef __NDR_convert__float_rep__Request__task_wire_t__must_wire__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__float_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__task_wire_t__must_wire__defined
#define	__NDR_convert__float_rep__Request__task_wire_t__must_wire(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__task_wire_t__must_wire__defined */


mig_internal kern_return_t __MIG_check__Request__task_wire_t(__Request__task_wire_t *In0P)
{

	typedef __Request__task_wire_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__task_wire_t__must_wire__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__task_wire_t__must_wire__defined)
		__NDR_convert__int_rep__Request__task_wire_t__must_wire(&In0P->must_wire, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__task_wire_t__must_wire__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__task_wire_t__must_wire__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__task_wire_t__must_wire__defined)
		__NDR_convert__char_rep__Request__task_wire_t__must_wire(&In0P->must_wire, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__task_wire_t__must_wire__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__task_wire_t__must_wire__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__task_wire_t__must_wire__defined)
		__NDR_convert__float_rep__Request__task_wire_t__must_wire(&In0P->must_wire, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__task_wire_t__must_wire__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__task_wire_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine task_wire */
mig_internal novalue _Xtask_wire
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		boolean_t must_wire;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__task_wire_t __Request;
	typedef __Reply__task_wire_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__task_wire_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__task_wire_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3815, "task_wire")
	__BeforeRcvRpc(3815, "task_wire")

#if	defined(__MIG_check__Request__task_wire_t__defined)
	check_result = __MIG_check__Request__task_wire_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__task_wire_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = task_wire(target_task, In0P->must_wire);
	vm_map_deallocate(target_task);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(3815, "task_wire")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__mach_make_memory_entry_t__defined)
#define __MIG_check__Request__mach_make_memory_entry_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined */


mig_internal kern_return_t __MIG_check__Request__mach_make_memory_entry_t(__Request__mach_make_memory_entry_t *In0P)
{

	typedef __Request__mach_make_memory_entry_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->parent_entry.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->parent_entry.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission(&In0P->permission, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission(&In0P->permission, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission(&In0P->permission, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_make_memory_entry_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_make_memory_entry */
mig_internal novalue _Xmach_make_memory_entry
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t parent_entry;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_size_t size;
		vm_offset_t offset;
		vm_prot_t permission;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_make_memory_entry_t __Request;
	typedef __Reply__mach_make_memory_entry_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_make_memory_entry_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_make_memory_entry_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	vm_map_t target_task;
	mem_entry_name_port_t object_handle;

	__DeclareRcvRpc(3816, "mach_make_memory_entry")
	__BeforeRcvRpc(3816, "mach_make_memory_entry")

#if	defined(__MIG_check__Request__mach_make_memory_entry_t__defined)
	check_result = __MIG_check__Request__mach_make_memory_entry_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_make_memory_entry_t__defined) */

#if	UseStaticTemplates
	OutP->object_handle = object_handleTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->object_handle.disposition = 17;
#else
	OutP->object_handle.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->object_handle.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = mach_make_memory_entry(target_task, &In0P->size, In0P->offset, In0P->permission, &object_handle, null_conversion(In0P->parent_entry.name));
	vm_map_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->parent_entry.name))
		ipc_port_release_send((ipc_port_t)In0P->parent_entry.name);
#endif /* __MigKernelSpecificCode */
	OutP->object_handle.name = (mach_port_t)null_conversion(object_handle);


	OutP->NDR = NDR_record;


	OutP->size = In0P->size;

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3816, "mach_make_memory_entry")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_map_page_query_t__defined)
#define __MIG_check__Request__vm_map_page_query_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__vm_offset_t((vm_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined */


mig_internal kern_return_t __MIG_check__Request__vm_map_page_query_t(__Request__vm_map_page_query_t *In0P)
{

	typedef __Request__vm_map_page_query_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined)
		__NDR_convert__int_rep__Request__vm_map_page_query_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_page_query_t__offset__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined)
		__NDR_convert__char_rep__Request__vm_map_page_query_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_page_query_t__offset__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined)
		__NDR_convert__float_rep__Request__vm_map_page_query_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_page_query_t__offset__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_map_page_query_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_map_page_query */
mig_internal novalue _Xvm_map_page_query
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_offset_t offset;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_map_page_query_t __Request;
	typedef __Reply__vm_map_page_query_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_map_page_query_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_map_page_query_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_map;

	__DeclareRcvRpc(3817, "vm_map_page_query")
	__BeforeRcvRpc(3817, "vm_map_page_query")

#if	defined(__MIG_check__Request__vm_map_page_query_t__defined)
	check_result = __MIG_check__Request__vm_map_page_query_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_map_page_query_t__defined) */

	target_map = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_map_page_query(target_map, In0P->offset, &OutP->disposition, &OutP->ref_count);
	vm_map_deallocate(target_map);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3817, "vm_map_page_query")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__mach_vm_region_info_t__defined)
#define __MIG_check__Request__mach_vm_region_info_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined */


mig_internal kern_return_t __MIG_check__Request__mach_vm_region_info_t(__Request__mach_vm_region_info_t *In0P)
{

	typedef __Request__mach_vm_region_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined)
		__NDR_convert__int_rep__Request__mach_vm_region_info_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_vm_region_info_t__address__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined)
		__NDR_convert__char_rep__Request__mach_vm_region_info_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_vm_region_info_t__address__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined)
		__NDR_convert__float_rep__Request__mach_vm_region_info_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_vm_region_info_t__address__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_vm_region_info_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_vm_region_info */
mig_internal novalue _Xmach_vm_region_info
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_vm_region_info_t __Request;
	typedef __Reply__mach_vm_region_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_vm_region_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_vm_region_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t objectsTemplate = {
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
	const static mach_msg_ool_descriptor_t objectsTemplate = {
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
	vm_map_t task;

	__DeclareRcvRpc(3818, "mach_vm_region_info")
	__BeforeRcvRpc(3818, "mach_vm_region_info")

#if	defined(__MIG_check__Request__mach_vm_region_info_t__defined)
	check_result = __MIG_check__Request__mach_vm_region_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_vm_region_info_t__defined) */

#if	UseStaticTemplates
	OutP->objects = objectsTemplate;
#else	/* UseStaticTemplates */
	OutP->objects.deallocate =  FALSE;
	OutP->objects.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->objects.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = mach_vm_region_info(task, In0P->address, &OutP->region, (vm_info_object_array_t *)&(OutP->objects.address), &OutP->objectsCnt);
	vm_map_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->objects.size = OutP->objectsCnt * 84;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3818, "mach_vm_region_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_mapped_pages_info_t__defined)
#define __MIG_check__Request__vm_mapped_pages_info_t__defined

mig_internal kern_return_t __MIG_check__Request__vm_mapped_pages_info_t(__Request__vm_mapped_pages_info_t *In0P)
{

	typedef __Request__vm_mapped_pages_info_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_mapped_pages_info_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_mapped_pages_info */
mig_internal novalue _Xvm_mapped_pages_info
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
	typedef __Request__vm_mapped_pages_info_t __Request;
	typedef __Reply__vm_mapped_pages_info_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_mapped_pages_info_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_mapped_pages_info_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t pagesTemplate = {
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
	const static mach_msg_ool_descriptor_t pagesTemplate = {
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
	vm_map_t task;

	__DeclareRcvRpc(3819, "vm_mapped_pages_info")
	__BeforeRcvRpc(3819, "vm_mapped_pages_info")

#if	defined(__MIG_check__Request__vm_mapped_pages_info_t__defined)
	check_result = __MIG_check__Request__vm_mapped_pages_info_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_mapped_pages_info_t__defined) */

#if	UseStaticTemplates
	OutP->pages = pagesTemplate;
#else	/* UseStaticTemplates */
	OutP->pages.deallocate =  FALSE;
	OutP->pages.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->pages.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = vm_mapped_pages_info(task, (page_address_array_t *)&(OutP->pages.address), &OutP->pagesCnt);
	vm_map_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->pages.size = OutP->pagesCnt * 4;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3819, "vm_mapped_pages_info")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_region_recurse_t__defined)
#define __MIG_check__Request__vm_region_recurse_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined
#if	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined
#if	defined(__NDR_convert__int_rep__vm_map__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt(a, f) \
	__NDR_convert__int_rep__vm_map__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined
#if	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined
#if	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined */


mig_internal kern_return_t __MIG_check__Request__vm_region_recurse_t(__Request__vm_region_recurse_t *In0P)
{

	typedef __Request__vm_region_recurse_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_t__nesting_depth__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt(&In0P->infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_t__infoCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined)
		__NDR_convert__char_rep__Request__vm_region_recurse_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_recurse_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined)
		__NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_recurse_t__nesting_depth__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined)
		__NDR_convert__float_rep__Request__vm_region_recurse_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_recurse_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined)
		__NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_recurse_t__nesting_depth__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_region_recurse_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_region_recurse */
mig_internal novalue _Xvm_region_recurse
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		natural_t nesting_depth;
		mach_msg_type_number_t infoCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_region_recurse_t __Request;
	typedef __Reply__vm_region_recurse_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_region_recurse_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_region_recurse_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3821, "vm_region_recurse")
	__BeforeRcvRpc(3821, "vm_region_recurse")

#if	defined(__MIG_check__Request__vm_region_recurse_t__defined)
	check_result = __MIG_check__Request__vm_region_recurse_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_region_recurse_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->infoCnt = 19;
	if (In0P->infoCnt < OutP->infoCnt)
		OutP->infoCnt = In0P->infoCnt;

	OutP->RetCode = vm_region_recurse(target_task, &In0P->address, &OutP->size, &In0P->nesting_depth, OutP->info, &OutP->infoCnt);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->nesting_depth = In0P->nesting_depth;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 76) + (((4 * OutP->infoCnt)));

	__AfterRcvRpc(3821, "vm_region_recurse")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_region_recurse_64_t__defined)
#define __MIG_check__Request__vm_region_recurse_64_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#if	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined
#if	defined(__NDR_convert__int_rep__vm_map__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt(a, f) \
	__NDR_convert__int_rep__vm_map__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#if	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#if	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined
#define	__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */


mig_internal kern_return_t __MIG_check__Request__vm_region_recurse_64_t(__Request__vm_region_recurse_64_t *In0P)
{

	typedef __Request__vm_region_recurse_64_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_64_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined)
		__NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt(&In0P->infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_recurse_64_t__infoCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined)
		__NDR_convert__char_rep__Request__vm_region_recurse_64_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_recurse_64_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined)
		__NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined)
		__NDR_convert__float_rep__Request__vm_region_recurse_64_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_recurse_64_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined)
		__NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth(&In0P->nesting_depth, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_recurse_64_t__nesting_depth__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_region_recurse_64_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_region_recurse_64 */
mig_internal novalue _Xvm_region_recurse_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		natural_t nesting_depth;
		mach_msg_type_number_t infoCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_region_recurse_64_t __Request;
	typedef __Reply__vm_region_recurse_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_region_recurse_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_region_recurse_64_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3822, "vm_region_recurse_64")
	__BeforeRcvRpc(3822, "vm_region_recurse_64")

#if	defined(__MIG_check__Request__vm_region_recurse_64_t__defined)
	check_result = __MIG_check__Request__vm_region_recurse_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_region_recurse_64_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->infoCnt = 19;
	if (In0P->infoCnt < OutP->infoCnt)
		OutP->infoCnt = In0P->infoCnt;

	OutP->RetCode = vm_region_recurse_64(target_task, &In0P->address, &OutP->size, &In0P->nesting_depth, OutP->info, &OutP->infoCnt);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->nesting_depth = In0P->nesting_depth;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 76) + (((4 * OutP->infoCnt)));

	__AfterRcvRpc(3822, "vm_region_recurse_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__mach_vm_region_info_64_t__defined)
#define __MIG_check__Request__mach_vm_region_info_64_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined
#define	__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined */


mig_internal kern_return_t __MIG_check__Request__mach_vm_region_info_64_t(__Request__mach_vm_region_info_64_t *In0P)
{

	typedef __Request__mach_vm_region_info_64_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined)
		__NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_vm_region_info_64_t__address__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined)
		__NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_vm_region_info_64_t__address__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined)
		__NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_vm_region_info_64_t__address__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_vm_region_info_64_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_vm_region_info_64 */
mig_internal novalue _Xmach_vm_region_info_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_vm_region_info_64_t __Request;
	typedef __Reply__mach_vm_region_info_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_vm_region_info_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_vm_region_info_64_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_ool_descriptor_t objectsTemplate = {
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
	const static mach_msg_ool_descriptor_t objectsTemplate = {
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
	vm_map_t task;

	__DeclareRcvRpc(3823, "mach_vm_region_info_64")
	__BeforeRcvRpc(3823, "mach_vm_region_info_64")

#if	defined(__MIG_check__Request__mach_vm_region_info_64_t__defined)
	check_result = __MIG_check__Request__mach_vm_region_info_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_vm_region_info_64_t__defined) */

#if	UseStaticTemplates
	OutP->objects = objectsTemplate;
#else	/* UseStaticTemplates */
	OutP->objects.deallocate =  FALSE;
	OutP->objects.copy = MACH_MSG_VIRTUAL_COPY;
	OutP->objects.type = MACH_MSG_OOL_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = mach_vm_region_info_64(task, In0P->address, &OutP->region, (vm_info_object_array_t *)&(OutP->objects.address), &OutP->objectsCnt);
	vm_map_deallocate(task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */
	OutP->objects.size = OutP->objectsCnt * 84;


	OutP->NDR = NDR_record;


	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3823, "mach_vm_region_info_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_region_64_t__defined)
#define __MIG_check__Request__vm_region_64_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_64_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined */

#ifndef __NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined
#if	defined(__NDR_convert__int_rep__vm_map__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt(a, f) \
	__NDR_convert__int_rep__vm_map__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__mach_msg_type_number_t__defined)
#define	__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined
#define	__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt(a, f) \
	__NDR_convert__int_rep__mach_msg_type_number_t((mach_msg_type_number_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_64_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__char_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_64_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_region_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_region_flavor_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_region_flavor_t((vm_region_flavor_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined
#define	__NDR_convert__float_rep__Request__vm_region_64_t__flavor(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined */


mig_internal kern_return_t __MIG_check__Request__vm_region_64_t(__Request__vm_region_64_t *In0P)
{

	typedef __Request__vm_region_64_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_region_64_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_region_64_t__address__defined)
		__NDR_convert__int_rep__Request__vm_region_64_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_64_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined)
		__NDR_convert__int_rep__Request__vm_region_64_t__flavor(&In0P->flavor, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_64_t__flavor__defined */
#if defined(__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined)
		__NDR_convert__int_rep__Request__vm_region_64_t__infoCnt(&In0P->infoCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_region_64_t__infoCnt__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_region_64_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined) || \
	0
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_region_64_t__address__defined)
		__NDR_convert__char_rep__Request__vm_region_64_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_64_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined)
		__NDR_convert__char_rep__Request__vm_region_64_t__flavor(&In0P->flavor, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_region_64_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_region_64_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined) || \
	0
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_region_64_t__address__defined)
		__NDR_convert__float_rep__Request__vm_region_64_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_64_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined)
		__NDR_convert__float_rep__Request__vm_region_64_t__flavor(&In0P->flavor, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_region_64_t__flavor__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_region_64_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_region_64 */
mig_internal novalue _Xvm_region_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_region_flavor_t flavor;
		mach_msg_type_number_t infoCnt;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_region_64_t __Request;
	typedef __Reply__vm_region_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_region_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_region_64_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_nameTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	vm_map_t target_task;

	__DeclareRcvRpc(3824, "vm_region_64")
	__BeforeRcvRpc(3824, "vm_region_64")

#if	defined(__MIG_check__Request__vm_region_64_t__defined)
	check_result = __MIG_check__Request__vm_region_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_region_64_t__defined) */

#if	UseStaticTemplates
	OutP->object_name = object_nameTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->object_name.disposition = 17;
#else
	OutP->object_name.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->object_name.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->infoCnt = 10;
	if (In0P->infoCnt < OutP->infoCnt)
		OutP->infoCnt = In0P->infoCnt;

	RetCode = vm_region_64(target_task, &In0P->address, &OutP->size, In0P->flavor, OutP->info, &OutP->infoCnt, &OutP->object_name.name);
	vm_map_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply) - 40) + (((4 * OutP->infoCnt)));

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3824, "vm_region_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__mach_make_memory_entry_64_t__defined)
#define __MIG_check__Request__mach_make_memory_entry_64_t__defined
#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_size_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined
#if	defined(__NDR_convert__int_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_size_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined
#if	defined(__NDR_convert__char_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_size_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__memory_object_size_t((memory_object_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined
#if	defined(__NDR_convert__float_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined
#define	__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined */


mig_internal kern_return_t __MIG_check__Request__mach_make_memory_entry_64_t(__Request__mach_make_memory_entry_64_t *In0P)
{

	typedef __Request__mach_make_memory_entry_64_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->parent_entry.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->parent_entry.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined)
		__NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__mach_make_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined)
		__NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__mach_make_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined)
		__NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission(&In0P->permission, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__mach_make_memory_entry_64_t__permission__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__mach_make_memory_entry_64_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine mach_make_memory_entry_64 */
mig_internal novalue _Xmach_make_memory_entry_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t parent_entry;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		memory_object_size_t size;
		memory_object_offset_t offset;
		vm_prot_t permission;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__mach_make_memory_entry_64_t __Request;
	typedef __Reply__mach_make_memory_entry_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__mach_make_memory_entry_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__mach_make_memory_entry_64_t__defined */

#if	__MigKernelSpecificCode
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#else
#if	UseStaticTemplates
	const static mach_msg_port_descriptor_t object_handleTemplate = {
		/* name = */		MACH_PORT_NULL,
		/* pad1 = */		0,
		/* pad2 = */		0,
		/* disp = */		17,
		/* type = */		MACH_MSG_PORT_DESCRIPTOR,
	};
#endif	/* UseStaticTemplates */

#endif /* __MigKernelSpecificCode */
	kern_return_t RetCode;
	vm_map_t target_task;

	__DeclareRcvRpc(3825, "mach_make_memory_entry_64")
	__BeforeRcvRpc(3825, "mach_make_memory_entry_64")

#if	defined(__MIG_check__Request__mach_make_memory_entry_64_t__defined)
	check_result = __MIG_check__Request__mach_make_memory_entry_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__mach_make_memory_entry_64_t__defined) */

#if	UseStaticTemplates
	OutP->object_handle = object_handleTemplate;
#else	/* UseStaticTemplates */
#if __MigKernelSpecificCode
	OutP->object_handle.disposition = 17;
#else
	OutP->object_handle.disposition = 17;
#endif /* __MigKernelSpecificCode */
	OutP->object_handle.type = MACH_MSG_PORT_DESCRIPTOR;
#endif	/* UseStaticTemplates */


	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	RetCode = mach_make_memory_entry_64(target_task, &In0P->size, In0P->offset, In0P->permission, &OutP->object_handle.name, null_conversion(In0P->parent_entry.name));
	vm_map_deallocate(target_task);
	if (RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->parent_entry.name))
		ipc_port_release_send((ipc_port_t)In0P->parent_entry.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->size = In0P->size;

	OutP->Head.msgh_bits |= MACH_MSGH_BITS_COMPLEX;
	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	OutP->msgh_body.msgh_descriptor_count = 1;
	__AfterRcvRpc(3825, "mach_make_memory_entry_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_map_64_t__defined)
#define __MIG_check__Request__vm_map_64_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_size_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__size__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__mask__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__flags__defined
#if	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__flags__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__offset__defined
#if	defined(__NDR_convert__int_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__memory_object_offset_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__int_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__int_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint64_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__int_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__offset__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__copy__defined
#if	defined(__NDR_convert__int_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__int_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__boolean_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__int_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__copy__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_prot_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined */

#ifndef __NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_inherit_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_size_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__size__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__mask__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__flags__defined
#if	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__flags__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__offset__defined
#if	defined(__NDR_convert__char_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__memory_object_offset_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__char_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__char_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint64_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__char_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__offset__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__copy__defined
#if	defined(__NDR_convert__char_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__char_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__boolean_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__char_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__copy__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_prot_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined */

#ifndef __NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_inherit_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_size_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_size_t((vm_size_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__size(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__size__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__mask(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__mask__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__flags__defined
#if	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__flags(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__flags__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__offset__defined
#if	defined(__NDR_convert__float_rep__vm_map__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__memory_object_offset_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__float_rep__memory_object_offset_t((memory_object_offset_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__float_rep__vm_map__uint64_t((uint64_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint64_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__offset(a, f) \
	__NDR_convert__float_rep__uint64_t((uint64_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__offset__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__copy__defined
#if	defined(__NDR_convert__float_rep__vm_map__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__float_rep__vm_map__boolean_t((boolean_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__boolean_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__copy__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__copy(a, f) \
	__NDR_convert__float_rep__boolean_t((boolean_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__copy__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_prot_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_prot_t((vm_prot_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined */

#ifndef __NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_inherit_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_inherit_t((vm_inherit_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined
#define	__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined */


mig_internal kern_return_t __MIG_check__Request__vm_map_64_t(__Request__vm_map_64_t *In0P)
{

	typedef __Request__vm_map_64_t __Request;
#if	__MigTypeCheck
	if (!(In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->msgh_body.msgh_descriptor_count != 1) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	if (In0P->object.type != MACH_MSG_PORT_DESCRIPTOR ||
	    In0P->object.disposition != 17)
		return MIG_TYPE_ERROR;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_map_64_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__size__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__copy__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__address__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__size__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__size(&In0P->size, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__size__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__mask__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__mask(&In0P->mask, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__mask__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__flags__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__flags(&In0P->flags, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__flags__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__offset__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__offset(&In0P->offset, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__offset__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__copy__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__copy(&In0P->copy, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__copy__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__cur_protection(&In0P->cur_protection, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__cur_protection__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__max_protection(&In0P->max_protection, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__max_protection__defined */
#if defined(__NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined)
		__NDR_convert__int_rep__Request__vm_map_64_t__inheritance(&In0P->inheritance, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_map_64_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_map_64_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__size__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__copy__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__address__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__size__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__size(&In0P->size, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__size__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__mask__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__mask(&In0P->mask, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__mask__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__flags__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__flags(&In0P->flags, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__flags__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__offset__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__offset(&In0P->offset, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__offset__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__copy__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__copy(&In0P->copy, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__copy__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__cur_protection(&In0P->cur_protection, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__cur_protection__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__max_protection(&In0P->max_protection, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__max_protection__defined */
#if defined(__NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined)
		__NDR_convert__char_rep__Request__vm_map_64_t__inheritance(&In0P->inheritance, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_map_64_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_map_64_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__size__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__copy__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__address__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__size__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__size(&In0P->size, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__size__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__mask__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__mask(&In0P->mask, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__mask__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__flags__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__flags(&In0P->flags, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__flags__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__offset__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__offset(&In0P->offset, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__offset__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__copy__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__copy(&In0P->copy, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__copy__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__cur_protection(&In0P->cur_protection, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__cur_protection__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__max_protection(&In0P->max_protection, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__max_protection__defined */
#if defined(__NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined)
		__NDR_convert__float_rep__Request__vm_map_64_t__inheritance(&In0P->inheritance, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_map_64_t__inheritance__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_map_64_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_map_64 */
mig_internal novalue _Xvm_map_64
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t object;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		vm_address_t address;
		vm_size_t size;
		vm_address_t mask;
		int flags;
		memory_object_offset_t offset;
		boolean_t copy;
		vm_prot_t cur_protection;
		vm_prot_t max_protection;
		vm_inherit_t inheritance;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_map_64_t __Request;
	typedef __Reply__vm_map_64_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_map_64_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_map_64_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3826, "vm_map_64")
	__BeforeRcvRpc(3826, "vm_map_64")

#if	defined(__MIG_check__Request__vm_map_64_t__defined)
	check_result = __MIG_check__Request__vm_map_64_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_map_64_t__defined) */

	target_task = convert_port_entry_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_map_64(target_task, &In0P->address, In0P->size, In0P->mask, In0P->flags, null_conversion(In0P->object.name), In0P->offset, In0P->copy, In0P->cur_protection, In0P->max_protection, In0P->inheritance);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode

	if (IP_VALID((ipc_port_t)In0P->object.name))
		ipc_port_release_send((ipc_port_t)In0P->object.name);
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->address = In0P->address;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3826, "vm_map_64")
}

#if (__MigTypeCheck || __NDR_convert__ )
#if __MIG_check__Request__vm_map_subsystem__
#if !defined(__MIG_check__Request__vm_purgable_control_t__defined)
#define __MIG_check__Request__vm_purgable_control_t__defined
#ifndef __NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_address_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__natural_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__uint32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__int_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined */

#ifndef __NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#if	defined(__NDR_convert__int_rep__vm_map__vm_purgable_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__vm_map__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_purgable_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined */

#ifndef __NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined
#if	defined(__NDR_convert__int_rep__vm_map__int__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__int_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__int__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__int_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__int_rep__vm_map__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__int_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__int_rep__int32_t__defined)
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__int_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__int_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined */

#ifndef __NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_address_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__natural_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__uint32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__char_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined */

#ifndef __NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#if	defined(__NDR_convert__char_rep__vm_map__vm_purgable_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__vm_map__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_purgable_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined */

#ifndef __NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined
#if	defined(__NDR_convert__char_rep__vm_map__int__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__char_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__int__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__char_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__char_rep__vm_map__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__char_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__char_rep__int32_t__defined)
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__char_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__char_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined */

#ifndef __NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_address_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__vm_address_t((vm_address_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__natural_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__natural_t((natural_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__vm_map__uint32_t((uint32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__uint32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__address(a, f) \
	__NDR_convert__float_rep__uint32_t((uint32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined */

#ifndef __NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#if	defined(__NDR_convert__float_rep__vm_map__vm_purgable_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__vm_map__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_purgable_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__vm_purgable_t((vm_purgable_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__control(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined */

#ifndef __NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined
#if	defined(__NDR_convert__float_rep__vm_map__int__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__float_rep__vm_map__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__int__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__float_rep__int((int *)(a), f)
#elif	defined(__NDR_convert__float_rep__vm_map__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__float_rep__vm_map__int32_t((int32_t *)(a), f)
#elif	defined(__NDR_convert__float_rep__int32_t__defined)
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined
#define	__NDR_convert__float_rep__Request__vm_purgable_control_t__state(a, f) \
	__NDR_convert__float_rep__int32_t((int32_t *)(a), f)
#endif /* defined(__NDR_convert__*__defined) */
#endif /* __NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined */


mig_internal kern_return_t __MIG_check__Request__vm_purgable_control_t(__Request__vm_purgable_control_t *In0P)
{

	typedef __Request__vm_purgable_control_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if	defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined) || \
	defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep) {
#if defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined)
		__NDR_convert__int_rep__Request__vm_purgable_control_t__address(&In0P->address, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_purgable_control_t__address__defined */
#if defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined)
		__NDR_convert__int_rep__Request__vm_purgable_control_t__control(&In0P->control, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_purgable_control_t__control__defined */
#if defined(__NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined)
		__NDR_convert__int_rep__Request__vm_purgable_control_t__state(&In0P->state, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__vm_purgable_control_t__state__defined */
	}
#endif	/* defined(__NDR_convert__int_rep...) */

#if	defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined) || \
	defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined)
	if (In0P->NDR.char_rep != NDR_record.char_rep) {
#if defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined)
		__NDR_convert__char_rep__Request__vm_purgable_control_t__address(&In0P->address, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_purgable_control_t__address__defined */
#if defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined)
		__NDR_convert__char_rep__Request__vm_purgable_control_t__control(&In0P->control, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_purgable_control_t__control__defined */
#if defined(__NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined)
		__NDR_convert__char_rep__Request__vm_purgable_control_t__state(&In0P->state, In0P->NDR.char_rep);
#endif	/* __NDR_convert__char_rep__Request__vm_purgable_control_t__state__defined */
	}
#endif	/* defined(__NDR_convert__char_rep...) */

#if	defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined) || \
	defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined)
	if (In0P->NDR.float_rep != NDR_record.float_rep) {
#if defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined)
		__NDR_convert__float_rep__Request__vm_purgable_control_t__address(&In0P->address, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_purgable_control_t__address__defined */
#if defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined)
		__NDR_convert__float_rep__Request__vm_purgable_control_t__control(&In0P->control, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_purgable_control_t__control__defined */
#if defined(__NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined)
		__NDR_convert__float_rep__Request__vm_purgable_control_t__state(&In0P->state, In0P->NDR.float_rep);
#endif	/* __NDR_convert__float_rep__Request__vm_purgable_control_t__state__defined */
	}
#endif	/* defined(__NDR_convert__float_rep...) */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__vm_purgable_control_t__defined) */
#endif /* __MIG_check__Request__vm_map_subsystem__ */
#endif /* ( __MigTypeCheck || __NDR_convert__ ) */


/* Routine vm_purgable_control */
mig_internal novalue _Xvm_purgable_control
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_address_t address;
		vm_purgable_t control;
		int state;
		mach_msg_trailer_t trailer;
	} Request;
#ifdef  __MigPackStructs
#pragma pack()
#endif
	typedef __Request__vm_purgable_control_t __Request;
	typedef __Reply__vm_purgable_control_t Reply;

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__vm_purgable_control_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__vm_purgable_control_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	vm_map_t target_task;

	__DeclareRcvRpc(3830, "vm_purgable_control")
	__BeforeRcvRpc(3830, "vm_purgable_control")

#if	defined(__MIG_check__Request__vm_purgable_control_t__defined)
	check_result = __MIG_check__Request__vm_purgable_control_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__vm_purgable_control_t__defined) */

	target_task = convert_port_to_map(In0P->Head.msgh_request_port);

	OutP->RetCode = vm_purgable_control(target_task, In0P->address, In0P->control, &In0P->state);
	vm_map_deallocate(target_task);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->state = In0P->state;

	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(3830, "vm_purgable_control")
}



/* Description of this subsystem, for use in direct RPC */
const struct vm_map_subsystem vm_map_subsystem = {
	vm_map_server_routine,
	3800,
	3831,
	(mach_msg_size_t)sizeof(union __ReplyUnion__vm_map_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_region, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_region_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_allocate, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_allocate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_deallocate, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_deallocate_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_protect, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_protect_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_inherit, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_inherit_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_read, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_read_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_read_list, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_read_list_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_write, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_write_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_copy, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_copy_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_read_overwrite, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_read_overwrite_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_msync, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_msync_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_behavior_set, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_behavior_set_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_map, 11, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_map_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_machine_attribute, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_machine_attribute_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_remap, 11, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_remap_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xtask_wire, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__task_wire_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_make_memory_entry, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_make_memory_entry_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_map_page_query, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_map_page_query_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_vm_region_info, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_vm_region_info_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_mapped_pages_info, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_mapped_pages_info_t)},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_region_recurse, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_region_recurse_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_region_recurse_64, 6, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_region_recurse_64_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_vm_region_info_64, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_vm_region_info_64_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_region_64, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_region_64_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xmach_make_memory_entry_64, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__mach_make_memory_entry_64_t)},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_map_64, 12, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_map_64_t)},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
          { (mig_impl_routine_t) 0,
            (mig_stub_routine_t) _Xvm_purgable_control, 4, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__vm_purgable_control_t)},
	}
};

mig_external boolean_t vm_map_server
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

	if ((InHeadP->msgh_id > 3830) || (InHeadP->msgh_id < 3800) ||
	    ((routine = vm_map_subsystem.routine[InHeadP->msgh_id - 3800].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t vm_map_server_routine
	(mach_msg_header_t *InHeadP)
{
	register int msgh_id;

	msgh_id = InHeadP->msgh_id - 3800;

	if ((msgh_id > 30) || (msgh_id < 0))
		return 0;

	return vm_map_subsystem.routine[msgh_id].stub_routine;
}

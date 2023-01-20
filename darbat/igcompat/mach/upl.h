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

#ifndef __IG_UPL_H__
#define __IG_UPL_H__

kern_return_t upl_commit( upl_t			upl,
			  upl_page_info_t		*page_list,
			  mach_msg_type_number_t	count );

kern_return_t upl_commit_range( upl_t			upl, 
				upl_offset_t		offset, 
				upl_size_t		size,
				int			flags,
				upl_page_info_t		*page_list,
				mach_msg_type_number_t	count,
				boolean_t		*empty );

kern_return_t upl_abort_range( upl_t			upl, 
			       upl_offset_t		offset, 
			       upl_size_t		size,
			       int			error,
			       boolean_t		*empty );

kern_return_t upl_abort( upl_t	upl,
			 int	error );





#endif /* __IG_UPL_H__ */

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
 * kern_subr.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <sys/param.h>
#include <sys/uio_internal.h>

/*
 * uio_resid - return the residual IO value for the given uio_t
 */
user_ssize_t uio_resid( uio_t a_uio )
{
#if DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__);
	}
/*      if (IS_VALID_UIO_SEGFLG(a_uio->uio_segflg) == 0) { */
/*	      panic("%s :%d - invalid uio_segflg\n", __FILE__, __LINE__);  */
/*      } */
#endif /* DEBUG */

	/* return 0 if there are no active iovecs */
	if (a_uio == NULL) {
		return( 0 );
	}

	if (UIO_IS_64_BIT_SPACE(a_uio)) {
#if 1 // LP64todo - remove this temp workaround once we go live with uio KPI
		return( (user_ssize_t)a_uio->uio_resid );
#else
		return( a_uio->uio_resid_64 );
#endif
	}
	return( (user_ssize_t)a_uio->uio_resid );
}

/*
 * uio_setresid - set the residual IO value for the given uio_t
 */
void uio_setresid( uio_t a_uio, user_ssize_t a_value )
{
#if DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__);
	}
/*      if (IS_VALID_UIO_SEGFLG(a_uio->uio_segflg) == 0) { */
/*	      panic("%s :%d - invalid uio_segflg\n", __FILE__, __LINE__);  */
/*      } */
#endif /* DEBUG */

	if (a_uio == NULL) {
		return;
	}

	if (UIO_IS_64_BIT_SPACE(a_uio)) {
#if 1 // LP64todo - remove this temp workaround once we go live with uio KPI
		a_uio->uio_resid = (int)a_value;
#else
		a_uio->uio_resid_64 = a_value;
#endif
	}
	else {
		a_uio->uio_resid = (int)a_value;
	}
	return;
}

/*
 * uio_offset - return the current offset value for the given uio_t
 */
off_t uio_offset( uio_t a_uio )
{
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__);
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL) {
		return(0);
	}       
	return( a_uio->uio_offset );
}

/*
 * uio_rw - return the read / write flag for the given uio_t
 */
int uio_rw( uio_t a_uio )
{
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__);
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL) {
		return(-1);
	}
	return( a_uio->uio_rw );
}

/*
 * uio_getiov - get iovec data associated with the given uio_t.  Use
 *  a_index to iterate over each iovec (0 to (uio_iovcnt(uio_t) - 1)).
 *  a_baseaddr_p and a_length_p may be NULL.
 *      returns -1 when a_index is >= uio_t.uio_iovcnt or invalid uio_t.
 *      returns 0 when data is returned.
 */
int uio_getiov( uio_t a_uio,
		 int a_index,
		 user_addr_t * a_baseaddr_p,
		 user_size_t * a_length_p )
{
	if (a_uio == NULL) {
#if DEBUG
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__);
#endif /* DEBUG */
		return(-1);
	}
	if ( a_index < 0 || a_index >= a_uio->uio_iovcnt) {
		return(-1);
	}

	if (UIO_IS_64_BIT_SPACE(a_uio)) {
		if (a_baseaddr_p != NULL) {
			*a_baseaddr_p = 
			    a_uio->uio_iovs.uiovp[a_index].iov_base;
		}
		if (a_length_p != NULL) {
			*a_length_p = a_uio->uio_iovs.uiovp[a_index].iov_len;
		}
	} else {
		if (a_baseaddr_p != NULL) {
			*a_baseaddr_p = 
			    a_uio->uio_iovs.kiovp[a_index].iov_base;
		}
		if (a_length_p != NULL) {
			*a_length_p = a_uio->uio_iovs.kiovp[a_index].iov_len;
		}
	}

	return( 0 );
}



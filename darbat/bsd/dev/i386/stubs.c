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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
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
 * Copyright (c) 1997 by Apple Computer, Inc., all rights reserved
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/kauth.h>
#include <sys/ucred.h>
#include <sys/proc_internal.h>
#include <sys/user.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <vm/vm_map.h>

/* XXX should be elsewhere (cpeak) */
extern int	set_bsduthreadargs(thread_t, void *, void *);
extern void	*get_bsduthreadarg(thread_t);
extern int	*get_bsduthreadrval(thread_t);
extern int	*get_bsduthreadlowpridelay(thread_t);

/* 
 * copy a null terminated string from the kernel address space into
 * the user address space.
 *   - if the user is denied write access, return EFAULT.
 *   - if the end of string isn't found before
 *     maxlen bytes are copied,  return ENAMETOOLONG,
 *     indicating an incomplete copy.
 *   - otherwise, return 0, indicating success.
 * the number of bytes copied is always returned in lencopied.
 */
int
copyoutstr(const void *from, user_addr_t to, size_t maxlen, size_t *lencopied)
{
	size_t	slen;
	size_t	len;
	int	error = 0;

	slen = strlen(from) + 1;
	if (slen > maxlen)
		error = ENAMETOOLONG;

	len = min(maxlen,slen);
	if (copyout(from, to, len))
		error = EFAULT;
	*lencopied = len;

	return error;
}


/* 
 * copy a null terminated string from one point to another in 
 * the kernel address space.
 *   - no access checks are performed.
 *   - if the end of string isn't found before
 *     maxlen bytes are copied,  return ENAMETOOLONG,
 *     indicating an incomplete copy.
 *   - otherwise, return 0, indicating success.
 * the number of bytes copied is always returned in lencopied.
 */
/* from ppc/fault_copy.c -Titan1T4 VERSION  */
int
copystr(const void *vfrom, void *vto, size_t maxlen, size_t *lencopied)
{
	size_t		l;
	char const	*from = (char const *) vfrom;
	char		*to = (char *) vto;

	for (l = 0; l < maxlen; l++) {
		if ((*to++ = *from++) == '\0') {
			if (lencopied)
				*lencopied = l + 1;
			return 0;
		}
	}
	if (lencopied)
		*lencopied = maxlen;
	return ENAMETOOLONG;
}

int
copywithin(void *src, void *dst, size_t count)
{
	bcopy(src,dst,count);
	return 0;
}

int
set_bsduthreadargs(thread_t th, void * pcb, __unused void *ignored_arg)
{
	struct uthread * ut;
	struct proc *p = current_proc();

	ut = get_bsdthread_info(th);
	ut->uu_ar0 = (int *)pcb;

	/*
	 * Delayed binding of thread credential to process credential.
	 *
	 * XXX This doesn't really belong here, but the i386 code has a
	 * XXX number of seemingly gratuitous structural differences that
	 * XXX make this the most appropriate place to do the work.
	 */
	if (ut->uu_ucred != p->p_ucred &&
	    (ut->uu_flag & UT_SETUID) == 0) {
		kauth_cred_t old = ut->uu_ucred;
		proc_lock(p);
		ut->uu_ucred = p->p_ucred;
		kauth_cred_ref(ut->uu_ucred);
		proc_unlock(p);
		if (old != NOCRED)
			kauth_cred_rele(old);
	}

	return(1);
}

void *
get_bsduthreadarg(thread_t th)
{
struct uthread *ut;
	ut = get_bsdthread_info(th);
	return((void *)(ut->uu_arg));
}

int *
get_bsduthreadrval(thread_t th)
{
struct uthread *ut;
	ut = get_bsdthread_info(th);
	return(&ut->uu_rval[0]);
}

int *
get_bsduthreadlowpridelay(thread_t th)
{
struct uthread *ut;
	ut = get_bsdthread_info(th);
	return(&ut->uu_lowpri_delay);
}

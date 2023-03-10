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
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
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
/*	$NetBSD: sem.h,v 1.5 1994/06/29 06:45:15 cgd Exp $	*/

/*
 * SVID compatible sem.h file
 *
 * Author:  Daniel Boulet
 * John Bellardo modified the implementation for Darwin. 12/2000
 */

#ifndef _SYS_SEM_H_
#define _SYS_SEM_H_


#include <sys/cdefs.h>
#include <sys/_types.h>

/*
 * [XSI]	All of the symbols from <sys/ipc.h> SHALL be defined
 *		when this header is included
 */
#include <sys/ipc.h>


/*
 * [XSI] The pid_t, time_t, key_t, and size_t types shall be defined as
 * described in <sys/types.h>.
 *
 * NOTE:	The definition of the key_t type is implicit from the
 *		inclusion of <sys/ipc.h>
 */
#ifndef _PID_T
typedef __darwin_pid_t	pid_t;
#define _PID_T
#endif

#ifndef	_TIME_T
#define	_TIME_T
typedef	__darwin_time_t	time_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef __darwin_size_t	size_t;
#endif

/*
 * Technically, we should force all code references to the new structure
 * definition, not in just the standards conformance case, and leave the
 * legacy interface there for binary compatibility only.  Currently, we
 * are only forcing this for programs requesting standards conformance.
 */
#if defined(__POSIX_C_SOURCE) || defined(kernel) || defined(__LP64__)
/*
 * Structure used internally.
 * 
 * This structure is exposed because standards dictate that it is used as
 * the semun union member 'buf' as the fourth argment to semctl() when the
 * third argument is IPC_STAT or IPC_SET.
 *
 * Note: only the fields sem_perm, sem_nsems, sem_otime, and sem_ctime
 * are meaningful in user space.
 */
struct __semid_ds_new {
	struct __ipc_perm_new sem_perm;	/* [XSI] operation permission struct */
	__int32_t	sem_base;	/* 32 bit base ptr for semaphore set */
	unsigned short	sem_nsems;	/* [XSI] number of sems in set */
	time_t		sem_otime;	/* [XSI] last operation time */
	__int32_t	sem_pad1;	/* RESERVED: DO NOT USE! */
	time_t		sem_ctime;	/* [XSI] last change time */
    					/* Times measured in secs since */
    					/* 00:00:00 GMT, Jan. 1, 1970 */
	__int32_t	sem_pad2;	/* RESERVED: DO NOT USE! */
	__int32_t	sem_pad3[4];	/* RESERVED: DO NOT USE! */
};
#define	semid_ds	__semid_ds_new
#else	/* !_POSIX_C_SOURCE */
#define	semid_ds	__semid_ds_old
#endif	/* !_POSIX_C_SOURCE */

#if !defined(__POSIX_C_SOURCE) && !defined(__LP64__)
struct __semid_ds_old {
	struct __ipc_perm_old sem_perm;	/* [XSI] operation permission struct */
	__int32_t	sem_base;	/* 32 bit base ptr for semaphore set */
	unsigned short	sem_nsems;	/* [XSI] number of sems in set */
	time_t		sem_otime;	/* [XSI] last operation time */
	__int32_t	sem_pad1;	/* RESERVED: DO NOT USE! */
	time_t		sem_ctime;	/* [XSI] last change time */
    					/* Times measured in secs since */
    					/* 00:00:00 GMT, Jan. 1, 1970 */
	__int32_t	sem_pad2;	/* RESERVED: DO NOT USE! */
	__int32_t	sem_pad3[4];	/* RESERVED: DO NOT USE! */
};
#endif	/* !_POSIX_C_SOURCE */

/*
 * Possible values for the third argument to semctl()
 */
#define GETNCNT	3	/* [XSI] Return the value of semncnt {READ} */
#define GETPID	4	/* [XSI] Return the value of sempid {READ} */
#define GETVAL	5	/* [XSI] Return the value of semval {READ} */
#define GETALL	6	/* [XSI] Return semvals into arg.array {READ} */
#define GETZCNT	7	/* [XSI] Return the value of semzcnt {READ} */
#define SETVAL	8	/* [XSI] Set the value of semval to arg.val {ALTER} */
#define SETALL	9	/* [XSI] Set semvals from arg.array {ALTER} */


/* A semaphore; this is an anonymous structure, not for external use */
struct sem {
	unsigned short	semval;		/* semaphore value */
	pid_t		sempid;		/* pid of last operation */
	unsigned short	semncnt;	/* # awaiting semval > cval */
	unsigned short	semzcnt;	/* # awaiting semval == 0 */
};


/*
 * Structure of array element for second argument to semop()
 */
struct sembuf {
	unsigned short	sem_num;	/* [XSI] semaphore # */
	short		sem_op;		/* [XSI] semaphore operation */
	short		sem_flg;	/* [XSI] operation flags */
};

/*
 * Possible flag values for sem_flg
 */
#define SEM_UNDO	010000		/* [XSI] Set up adjust on exit entry */


#ifndef _POSIX_C_SOURCE

/*
 * System imposed limit on the value of the third parameter to semop().
 * This is arbitrary, and the standards unfortunately do not provide a
 * way for user applications to retrieve this value (e.g. via sysconf()
 * or from a manifest value in <unistd.h>).  The value shown here is
 * informational, and subject to change in future revisions.
 */
#define MAX_SOPS	5	/* maximum # of sembuf's per semop call */


/*
 * Union used as the fourth argment to semctl() in all cases.  Specific
 * member values are used for different values of the third parameter:
 * 
 * Command					Member
 * -------------------------------------------	------
 * GETALL, SETALL				array
 * SETVAL					val
 * IPC_STAT, IPC_SET				buf
 *
 * The union definition is intended to be defined by the user application
 * in conforming applications; it is provided here for two reasons:
 * 
 * 1)	Historical source compatability for non-conforming applications
 *	expecting this header to declare the union type on their behalf
 *
 * 2)	Documentation; specifically, 64 bit applications that do not pass
 *	this structure for 'val', or, alternately, a 64 bit type, will
 *	not function correctly
 */
union semun {
	int		val;		/* value for SETVAL */
	struct semid_ds	*buf;		/* buffer for IPC_STAT & IPC_SET */
	unsigned short	*array;		/* array for GETALL & SETALL */
};
typedef union semun semun_t;


/*
 * Permissions
 */
#define SEM_A		0200	/* alter permission */
#define SEM_R		0400	/* read permission */

#endif	/* !_POSIX_C_SOURCE */



#ifndef KERNEL

__BEGIN_DECLS
#ifndef _POSIX_C_SOURCE
int	semsys(int, ...);
#endif /* !_POSIX_C_SOURCE */
int	semctl(int, int, int, ...) __DARWIN_ALIAS(semctl);
int	semget(key_t, int, int);
int	semop(int, struct sembuf *, size_t);
__END_DECLS

#endif /* !KERNEL */

#endif /* !_SEM_H_ */

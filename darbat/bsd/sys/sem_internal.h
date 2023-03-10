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
 * Copyright (c) 2000-2005 Apple Computer, Inc. All rights reserved.
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
 * SVID compatible sem_internal.h file
 *
 * Author:  Daniel Boulet
 */
/*
 * John Bellardo modified the implementation for Darwin. 12/2000
 */

#ifndef _SYS_SEM__INTERNALH_
#define _SYS_SEM__INTERNALH_

#include <sys/sem.h>
#include <sys/cdefs.h>


/*
 * This structure is variant for 64 bits because of sem_otime and sem_ctime.
 */

#if __DARWIN_ALIGN_NATURAL
#pragma options align=natural
#endif

struct user_semid_ds {
	struct ipc_perm sem_perm;	/* [XSI] operation permission struct */
	struct sem	*sem_base;	/* 32 bit base ptr for semaphore set */
	unsigned short	sem_nsems;	/* [XSI] number of sems in set */
	user_time_t	sem_otime;	/* [XSI] last operation time */
	__int32_t	sem_pad1;	/* RESERVED: DO NOT USE! */
	user_time_t	sem_ctime;	/* [XSI] last change time */
    					/* Times measured in secs since */
    					/* 00:00:00 GMT, Jan. 1, 1970 */
	__int32_t	sem_pad2;	/* RESERVED: DO NOT USE! */
	__int32_t	sem_pad3[4];	/* RESERVED: DO NOT USE! */
};

union user_semun {
	user_addr_t	buf;		/* buffer for IPC_STAT & IPC_SET */
	user_addr_t	array;		/* array for GETALL & SETALL */
};
typedef union user_semun user_semun_t;

#if __DARWIN_ALIGN_NATURAL
#pragma options align=reset
#endif


/*
 * Kernel implementation stuff
 */
#define SEMVMX	32767		/* semaphore maximum value */
#define SEMAEM	16384		/* adjust on exit max value */

/*
 * Configuration parameters.  SEMMNI, SEMMNS, and SEMMNU are hard limits.
 * The code dynamically allocates enough memory to satisfy the current
 * demand in even increments of SEMMNI_INC, SEMMNS_INC, and SEMMNU_INC.
 * The code will never allocate more than the hard limits.  The *_INC's
 * are defined in the kernel section of the header.
 */
/*
 * Configuration parameters
 */
#ifndef SEMMNS			/* # of semaphores in system */
#define SEMMNS	(1048576/sizeof(struct sem))
#endif				/* no more than 1M of semaphore data */
#ifndef SEMMNI			/* # of semaphore identifiers */
#define SEMMNI	SEMMNS		/* max of 1 for each semaphore */
#endif
#ifndef SEMUME
#define SEMUME	10		/* max # of undo entries per process */
#endif
#ifndef SEMMNU			/* # of undo structures in system */
#define SEMMNU	SEMMNS		/* 1 for each semaphore.  This is quite large */
#endif				/* This should be max 1 for each process */

/* shouldn't need tuning */
#ifndef SEMMAP
#define SEMMAP	30		/* # of entries in semaphore map */
#endif
#ifndef SEMMSL
#define SEMMSL	SEMMNS		/* max # of semaphores per id */
#endif
#ifndef SEMOPM
#define SEMOPM	100		/* max # of operations per semop call */
#endif


/*
 * Undo structure (internal: one per process)
 */
struct sem_undo {
	struct	sem_undo *un_next;	/* ptr to next active undo structure */
	struct	proc *un_proc;		/* owner of this structure */
	short	un_cnt;			/* # of active entries */
	struct undo {
		short	une_adjval;	/* adjust on exit values */
		short	une_num;	/* semaphore # */
		int	une_id;		/* semid */
		struct undo *une_next;	/* next undo entry */
	} *un_ent;			/* undo entries */
};

/*
 * semaphore info struct (internal; for administrative limits and ipcs)
 */
struct seminfo {
	int	semmap,		/* # of entries in semaphore map */
		semmni,		/* # of semaphore identifiers */
		semmns,		/* # of semaphores in system */
		semmnu,		/* # of undo structures in system */
		semmsl,		/* max # of semaphores per id */
		semopm,		/* max # of operations per semop call */
		semume,		/* max # of undo entries per process */
		semusz,		/* size in bytes of undo structure */
		semvmx,		/* semaphore maximum value */
		semaem;		/* adjust on exit max value */
};
extern struct seminfo	seminfo;

/* internal "mode" bits */
#define	SEM_ALLOC	01000	/* semaphore is allocated */
#define	SEM_DEST	02000	/* semaphore will be destroyed on last detach */

#define SEMMNI_INC	8	/* increment value for semaphore identifiers */
#define SEMMNS_INC	64	/* increment value for semaphores */
#define SEMMNU_INC	32	/* increment value for undo structures */

/*
 * Due to the way semaphore memory is allocated, we have to ensure that
 * SEMUSZ is properly aligned.
 *
 * We are not doing strange semaphore memory allocation anymore, so
 * these macros are no longer needed.
 */

/*
 * #define SEM_ALIGN(bytes) (((bytes) + (sizeof(long) - 1)) & ~(sizeof(long) - 1))
 */

/* actual size of an undo structure */
/*
 * #define SEMUSZ	SEM_ALIGN(offsetof(struct sem_undo, un_ent[SEMUME]))
 */
#define SEMUSZ		sizeof(struct sem_undo)

extern struct user_semid_ds	*sema;		/* semaphore id pool */
extern struct sem		*sem_pool;	/* semaphore pool */
/* This is now a struct sem_undo with the new memory allocation 
 * extern int	*semu;		// undo structure pool
 */
extern struct sem_undo	*semu;		/* undo structure pool */

/*
 * Macro to find a particular sem_undo vector
 */
/* Until we can initialize seminfo.semusz to SEMUSZ, we hard code the size macro
 * in SEMU.  This should be fixed when (if) we implement dynamic pool sizes
 *
 * #define SEMU(ix)     ((struct sem_undo *)(((intptr_t)semu)+ix * seminfo.semusz))
 */
/*
 * This macro doesn't work because we are using a staticly allocated array
 * for semu now.
 * #define SEMU(ix)        ((struct sem_undo *)(((intptr_t)semu)+ix * SEMUSZ)) 
 */
#define SEMU(ix)        (&semu[ix])


/*
 * Process sem_undo vectors at proc exit.
 */
void	semexit(struct proc *p);

/*
 * Parameters to the semconfig system call
 */
typedef enum {
	SEM_CONFIG_FREEZE,	/* Freeze the semaphore facility. */
	SEM_CONFIG_THAW		/* Thaw the semaphore facility. */
} semconfig_ctl_t;


#endif /* !_SYS_SEM__INTERNALH_ */

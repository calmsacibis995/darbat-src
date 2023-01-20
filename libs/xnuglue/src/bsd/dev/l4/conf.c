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
/*Since code was taken from Apple, this probably qualifies for an APSL
 *license.  Source code was modified 2006-03-29. */

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

#include <assert.h>

#define __DARWIN_UNIX03	0	/*XXX for errno.h */

#include <stdint.h>


#include <sys/systm.h>
#include <sys/errno.h>
#include <sys/conf.h>

#include <stdio.h>

/*
 * XXX
 *
 * This is deliberately redone instead of #include <sys/uio.h>
 * Due to conflicts.
 * Sigh.
 */
struct iovec {
        unsigned int iov_base;       /* Base address. */        /* uint32 */
        unsigned int iov_len;        /* Length. */              /* uint32 */
};

union iovecs {
        struct iovec            *iovp;
};

enum uio_rw { UIO_READ, UIO_WRITE };

/*
 * See notes in sys/uio.h
 */
enum uio_seg {
        UIO_USERSPACE           = 0,    /* kernel address is virtual,  to/from u
ser virtual */
        UIO_SYSSPACE            = 2,    /* kernel address is virtual,  to/from s
ystem virtual */
        UIO_USERSPACE32         = 5,    /* kernel address is virtual,  to/from u
ser 32-bit virtual */
        UIO_USERSPACE64         = 8,    /* kernel address is virtual,  to/from u
ser 64-bit virtual */
        UIO_SYSSPACE32          = 11    /* kernel address is virtual,  to/from s
ystem virtual */
};

/*
 * XXX
 *
 */

struct uio {
        union iovecs    uio_iovs;               /* current iovec */
        int             uio_iovcnt;             /* active iovecs */
        off_t           uio_offset;
        int             uio_resid;              /* compatibility uio_resid (pre-
LP64) */
        enum uio_seg    uio_segflg;
        enum uio_rw     uio_rw;
#ifndef L4IOKIT
        proc_t          uio_procp;              /* obsolete - not used! */
#endif
#ifndef L4IOKIT
        user_ssize_t    uio_resid_64;
#endif
        int             uio_size;               /* size for use
with kfree */
        int             uio_max_iovs;   /* max number of iovecs
this uio_t can hold */

#ifndef L4IOKIT
        u_int32_t       uio_flags;
#endif
};

#if 0
typedef struct uio * uio_t;
#endif

/*
 * sys/conf.h
 *
 */
/*
 * Contents of empty bdevsw slot.
 */
#if 0
#define  NO_BDEVICE                                             \
        { eno_opcl,     eno_opcl,       eno_strat, eno_ioctl,   \
          eno_dump,     eno_psize,      0       }
#endif

#if 0
/*
 * Contents of an empty cdevsw slot
 */
#define  NO_CDEVICE                                                      \
    {                                                                   \
        eno_opcl,       eno_opcl,       eno_rdwrt,      eno_rdwrt,      \
        eno_ioctl,      eno_stop,       eno_reset,      0,              \
        (select_fcn_t *)seltrue,        eno_mmap,       eno_strat,      eno_getc
,       \
        eno_putc,       0                                               \
    }
#endif

/*
 * cdevsw: stolen from bsd/dev/i386/conf.c
 *
 */
struct cdevsw   cdevsw[] =
{
        /*
         *      For character devices, every other block of 16 slots is
         *      reserved to NeXT.  The other slots are available for
         *      the user.  This way we can both add new entries without
         *      running into each other.  Be sure to fill in NeXT's
         *      16 reserved slots when you jump over us -- we'll do the
         *      same for you.
         */

        /* 0 - 15 are reserved to NeXT */

    NO_CDEVICE,                                                         /* 0*/
    NO_CDEVICE,                                                         /* 1*/
    NO_CDEVICE,                                                         /* 2*/
    NO_CDEVICE,                                                         /* 3*/
    NO_CDEVICE,                                                         /* 4*/
    NO_CDEVICE,                                                         /* 5*/
    NO_CDEVICE,                                                         /* 6*/
    NO_CDEVICE,                                                         /* 7*/
    NO_CDEVICE,                                                         /* 8*/
    NO_CDEVICE,                                                         /* 9*/
    NO_CDEVICE,                                                         /*10*/
    NO_CDEVICE,                                                         /*11*/
    NO_CDEVICE,                                                         /*12*/
    NO_CDEVICE,                                                         /*13*/
    NO_CDEVICE,                                                         /*14*/
    NO_CDEVICE,                                                         /*15*/

        /* 16 - 31 are reserved to the user */
    NO_CDEVICE,                                                         /*16*/
    NO_CDEVICE,                                                         /*17*/
    NO_CDEVICE,                                                         /*18*/
    NO_CDEVICE,                                                         /*19*/
    NO_CDEVICE,                                                         /*20*/
    NO_CDEVICE,                                                         /*21*/
    NO_CDEVICE,                                                         /*22*/
    NO_CDEVICE,                                                         /*23*/
    NO_CDEVICE,                                                         /*24*/
    NO_CDEVICE,                                                         /*25*/
    NO_CDEVICE,                                                         /*26*/
    NO_CDEVICE,                                                         /*27*/
    NO_CDEVICE,                                                         /*28*/
    NO_CDEVICE,                                                         /*29*/
    NO_CDEVICE,                                                         /*30*/
    NO_CDEVICE,                                                         /*31*/
    NO_CDEVICE,                                                         /*32*/
    NO_CDEVICE,                                                         /*33*/
    NO_CDEVICE,                                                         /*34*/
    NO_CDEVICE,                                                         /*35*/
    NO_CDEVICE,                                                         /*36*/
    NO_CDEVICE,                                                         /*37*/
    NO_CDEVICE,                                                         /*38*/
    NO_CDEVICE,                                                         /*39*/
    NO_CDEVICE,                                                         /*40*/
    NO_CDEVICE,                                                         /*41*/
    NO_CDEVICE                                                         /*42*/
};

int     nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

/*
 * bdevsw: stolen from bsd/dev/i386/conf.c
 *
 */
struct bdevsw   bdevsw[] =
{
        /*
         *      For block devices, every other block of 8 slots is
         *      reserved to NeXT.  The other slots are available for
         *      the user.  This way we can both add new entries without
         *      running into each other.  Be sure to fill in NeXT's
         *      8 reserved slots when you jump over us -- we'll do the
         *      same for you.
         */

        /* 0 - 7 are reserved to NeXT */

        NO_BDEVICE,                                                     /* 0*/
        NO_BDEVICE,                                                     /* 1*/
        NO_BDEVICE,                                                     /* 2*/
        NO_BDEVICE,                                                     /* 3*/
        NO_BDEVICE,                                                     /* 4*/
        NO_BDEVICE,                                                     /* 5*/
        NO_BDEVICE,                                                     /* 6*/
        NO_BDEVICE,                                                     /* 7*/

        /* 8 - 15 are reserved to the user */

        NO_BDEVICE,                                                     /* 8*/
        NO_BDEVICE,                                                     /* 9*/
        NO_BDEVICE,                                                     /*10*/
        NO_BDEVICE,                                                     /*11*/
        NO_BDEVICE,                                                     /*12*/
        NO_BDEVICE,                                                     /*13*/
        NO_BDEVICE,                                                     /*14*/
        NO_BDEVICE,                                                     /*15*/

        /* 16 - 23 are reserved to NeXT */
        NO_BDEVICE,                                                     /*16*/
        NO_BDEVICE,                                                     /*17*/
        NO_BDEVICE,                                                     /*18*/
        NO_BDEVICE,                                                     /*18*/
        NO_BDEVICE,                                                     /*20*/
        NO_BDEVICE,                                                     /*21*/
        NO_BDEVICE,                                                     /*22*/
        NO_BDEVICE,                                                     /*23*/
};

int     nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);


#if 0 	/* XXX BIG FAT REMINDER */
int
devfs_make_node(void);
int
devfs_make_node(void)
{

	xnu_printf("stubs4: devfs_make_node called\n");
	return 0xabcdef;	/* this requires ti to return something */
}
#endif

#if 0
int
uio_iovcnt(uio_t	uio);
int
uio_iovcnt(uio_t	uio)
{

	return uio->uio_iovcnt;
}

int
uio_isuserspace(uio_t	uio);
int
uio_isuserspace(uio_t	uio)
{

	return 0;	/* never userspace, but we are userspace :) */
}

off_t
uio_offset(uio_t	uio);
off_t
uio_offset(uio_t	uio)
{

	return uio->uio_offset;
}

int
uio_resid(uio_t	uio);
int
uio_resid(uio_t	uio)
{

	return uio->uio_resid;
}

int
uio_rw(uio_t	uio);
int
uio_rw(uio_t	uio)
{

	return uio->uio_rw;
}

void
uio_setresid(uio_t uio, int newresid);
void
uio_setresid(uio_t uio, int newresid)
{

	uio->uio_resid = newresid;
}

/*
 * This doesn't do anything checking which may be bad
 */
int
uio_getiov(
	uio_t	a_uio,
	int	a_index,
	unsigned long *a_addr_p,
	unsigned int *a_length_p);
int
uio_getiov(
	uio_t	a_uio,
	int	a_index,
	unsigned long *a_addr_p,
	unsigned int *a_length_p)
{

#if 0
	xnu_printf("%s: called with %p %d %p %p\n",
		__FUNCTION__, a_uio, a_index, a_addr_p, a_length_p);
#endif

	if (a_addr_p)
		*a_addr_p = a_uio->uio_iovs.iovp[a_index].iov_base;
	if (a_length_p)
		*a_length_p = a_uio->uio_iovs.iovp[a_index].iov_len;

	return 0;
}
#endif

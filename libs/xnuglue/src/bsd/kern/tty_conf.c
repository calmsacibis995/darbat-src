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
 * ttyconf.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/conf.h>
#include <sys/errno.h>

#include <sys/tty.h>

#ifndef MAXLDISC
#define MAXLDISC 8
#endif

#define NeXT    /* glee: XXX */

#ifndef NeXT
static l_open_t	 l_noopen;
static l_close_t	l_noclose;
static l_rint_t	 l_norint;
#else /* NeXT */
#define l_noopen	((l_open_t *)  &enodev)
#define l_noclose       ((l_close_t *) &enodev)
#define l_noread	((l_read_t *)  &enodev)
#define l_nowrite       ((l_write_t *) &enodev)
#define l_norint	((l_rint_t *)  &enodev)
#endif /* !NeXT */

static l_ioctl_t	l_noioctl;
static l_start_t	l_nostart;

/*
 * XXX it probably doesn't matter what the entries other than the l_open
 * entry are here.  The l_noioctl and ttymodem entries still look fishy.
 * Reconsider the removal of nullmodem anyway.  It was too much like
 * ttymodem, but a completely null version might be useful.
 */
#define NODISC(n) \
	{ l_noopen,     l_noclose,      l_noread,       l_nowrite, \
	  l_noioctl,    l_norint,       l_nostart,      ttymodem }


struct  linesw linesw[MAXLDISC] =
{
				/* 0- termios */
	{ ttyopen,      ttylclose,      ttread,	 ttwrite,
	  l_noioctl,    ttyinput,       ttwwakeup,      ttymodem },
	NODISC(1),	 	/* 1- defunct */
				/* 2- NTTYDISC */
#if COMPAT_43_TTY
	{ ttyopen,      ttylclose,      ttread,	 ttwrite,
	  l_noioctl,    ttyinput,       ttwwakeup,      ttymodem },
#else
	NODISC(2),
#endif
	NODISC(3),	      /* TABLDISC */
	NODISC(4),	      /* SLIPDISC */
	NODISC(5),	      /* PPPDISC */
	NODISC(6),	      /* loadable */
	NODISC(7),	      /* loadable */
};


/*
 * Do nothing specific version of line
 * discipline specific ioctl command.
 */
static int
l_noioctl(__unused struct tty *tp, __unused u_long cmd, __unused caddr_t data,
	  __unused int flags, __unused struct proc *p)
{

	return ENOTTY;
}

static void
l_nostart(__unused struct tty *tp)
    { }


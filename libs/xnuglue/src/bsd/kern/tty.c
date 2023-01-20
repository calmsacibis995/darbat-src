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
 * bsd/kern/tty.c
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

/* Since code was taken from Apple, this probably qualifies for an APSL
 *license.  Source code was modified 2006-03-29.
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
 * Funnels
 *
 */
extern void *kernel_flock;
#include <kern/thread.h>

#include <sys/param.h>
#define TTYDEFCHARS 1
#include <sys/systm.h>
#undef  TTYDEFCHARS
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/proc_internal.h>
#include <sys/stat.h>
#include <sys/conf.h>
#include <sys/tty.h>

#include <l4/ipc.h>
#include <stdio.h>
#include <ll.h>

#include <kern/debug.h>

#include <xnucompat.h>

/* Macros to clear/set/test flags. */
#define SET(t, f)       (t) |= (f)
#define CLR(t, f)       (t) &= ~(f)
#define ISSET(t, f)     ((t) & (f))

#define NeXT	1	/* XXX glee */


/*
 * XXX FIXME XXX
 *
 */
#define spltty()	(1)
#define splx(x)

/*
 * Wake up any readers on a tty.
 */
void
ttwakeup(tp)
	register struct tty *tp;
{
	
#ifndef L4IOKIT
#ifndef NeXT
	if (tp->t_rsel.si_pid != 0)
#endif		    
		selwakeup(&tp->t_rsel);
	if (ISSET(tp->t_state, TS_ASYNC))
		pgsignal(tp->t_pgrp, SIGIO, 1);
#endif
	wakeup(TSA_HUP_OR_INPUT(tp));
}

/*
 * Wake up any writers on a tty.
 */
void
ttwwakeup(tp)
	register struct tty *tp;
{
#ifndef L4IOKIT
#ifndef NeXT
	if (tp->t_wsel.si_pid != 0 && tp->t_outq.c_cc <= tp->t_lowat)
#else
	if (tp->t_outq.c_cc <= tp->t_lowat)
#endif
		selwakeup(&tp->t_wsel);
#endif
	if (ISSET(tp->t_state, TS_BUSY | TS_SO_OCOMPLETE) ==
	    TS_SO_OCOMPLETE && tp->t_outq.c_cc == 0) {
		CLR(tp->t_state, TS_SO_OCOMPLETE);
		wakeup(TSA_OCOMPLETE(tp));
	}
	if (ISSET(tp->t_state, TS_SO_OLOWAT) &&
	    tp->t_outq.c_cc <= tp->t_lowat) {
		CLR(tp->t_state, TS_SO_OLOWAT);
		wakeup(TSA_OLOWAT(tp));
	}
}

/*
 * Handle modem control transition on a tty.
 * Flag indicates new state of carrier.
 * Returns 0 if the line should be turned off, otherwise 1.
 */
int
ttymodem(tp, flag)
	register struct tty *tp;
	int flag;
{
	boolean_t funnel_state;

	funnel_state = thread_funnel_set(kernel_flock, TRUE);

	if (ISSET(tp->t_state, TS_CARR_ON) && ISSET(tp->t_cflag, MDMBUF)) {
		/*
		 * MDMBUF: do flow control according to carrier flag
		 * XXX TS_CAR_OFLOW doesn't do anything yet.  TS_TTSTOP
		 * works if IXON and IXANY are clear.
		 */
		if (flag) {
			CLR(tp->t_state, TS_CAR_OFLOW);
			CLR(tp->t_state, TS_TTSTOP);
#ifndef L4IOKIT	/* What is this? */
			ttstart(tp);
#endif
		} else if (!ISSET(tp->t_state, TS_CAR_OFLOW)) {
			SET(tp->t_state, TS_CAR_OFLOW);
			SET(tp->t_state, TS_TTSTOP);
#ifndef L4IOKIT	/* what is this? */
			ttystop(tp, 0);
#endif
		}
	} else if (flag == 0) {
		/*
		 * Lost carrier.
		 */
		CLR(tp->t_state, TS_CARR_ON);
		if (ISSET(tp->t_state, TS_ISOPEN) &&
		    !ISSET(tp->t_cflag, CLOCAL)) {
			SET(tp->t_state, TS_ZOMBIE);
			CLR(tp->t_state, TS_CONNECTED);
#ifndef L4IOKIT	/* XXX: signals?  Yeh, sure ... */
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			ttyflush(tp, FREAD | FWRITE);
#endif
			thread_funnel_set(kernel_flock, funnel_state);
			return (0);
		}
	} else {
		/*
		 * Carrier now on.
		 */
		SET(tp->t_state, TS_CARR_ON);
		if (!ISSET(tp->t_state, TS_ZOMBIE)) 
			SET(tp->t_state, TS_CONNECTED);
		wakeup(TSA_CARR_ON(tp));
		ttwakeup(tp);
		ttwwakeup(tp);
	}
	thread_funnel_set(kernel_flock, funnel_state);
	return (1);
}

/*
 * Set tty hi and low water marks.
 *
 * Try to arrange the dynamics so there's about one second
 * from hi to low water.
 *
 */
void
ttsetwater(struct tty *tp)
{
	int cps;
	unsigned int x;
                        
#define CLAMP(x, h, l)  ((x) > h ? h : ((x) < l) ? l : (x))
                        
	cps = tp->t_ospeed / 10;  
	tp->t_lowat = x = CLAMP(cps / 2, TTMAXLOWAT, TTMINLOWAT);
	x += cps;
	x = CLAMP(x, TTMAXHIWAT, TTMINHIWAT);
	tp->t_hiwat = roundup(x, CBSIZE);
#undef  CLAMP
}

/* XXX */
void darbat_char_notify( int c );

/*
 * Input a character
 *
 */
int
ttyinput(c, tp)
	int		c;
	struct tty	*tp;
{
	L4_MsgTag_t	tag;

	if (!ttyfifo)
		return (0);

#if 0
	lck_spin_lock(xnulck);
	ll_add_end(ttyfifo, (void *)c);
	lck_spin_unlock(xnulck);

	tag = L4_Send(serialreadtid);
	if (!L4_IpcSucceeded(tag))
		panic("ttyinput: can't pass to iokit server");
#else
	darbat_char_notify(c);
#endif

	return (0);	/* XXX errno */
}

/*
 * Look up a code for a specified speed in a conversion table;
 * used by drivers to map software speed values to hardware parameters.
 */
int
ttspeedtab(speed, table)
	int speed;
	register struct speedtab *table;
{
	
	for ( ; table->sp_speed != -1; table++)
		if (table->sp_speed == speed)
			return (table->sp_code);
	return (-1);
}

/*
 * Initial open of tty, or (re)entry to standard tty line discipline.
 */
int
ttyopen(device, tp)
	dev_t device;
	register struct tty *tp;
{
	int s;
	boolean_t funnel_state;

	funnel_state = thread_funnel_set(kernel_flock, TRUE);
	s = spltty();
	tp->t_dev = device;
	if (!ISSET(tp->t_state, TS_ISOPEN)) {
		SET(tp->t_state, TS_ISOPEN);
		if (ISSET(tp->t_cflag, CLOCAL)) {
			SET(tp->t_state, TS_CONNECTED); }
		bzero(&tp->t_winsize, sizeof(tp->t_winsize));
	}

#ifndef NeXT
	/*
	 * Initialize or restore a cblock allocation policy suitable for
	 * the standard line discipline.
	 */
	clist_alloc_cblocks(&tp->t_canq, TTYHOG, 512);
	clist_alloc_cblocks(&tp->t_outq, TTMAXHIWAT + OBUFSIZ + 100,
			    TTMAXHIWAT + OBUFSIZ + 100);
	clist_alloc_cblocks(&tp->t_rawq, TTYHOG, TTYHOG);
#endif /* !NeXT */

	splx(s);
	thread_funnel_set(kernel_flock, funnel_state);
	return (0);
}


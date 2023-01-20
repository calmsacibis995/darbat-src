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
 * IOSerialBSDClient.h
 *
 * 2000-10-21	gvdl	Initial real change to IOKit serial family.
 *
 */


#ifndef _IOSERIALSERVER_H
#define _IOSERIALSERVER_H

#include <IOKit/IOLib.h>
#include <IOKit/IOReturn.h>
#include <IOKit/IOTypes.h>

#include <IOKit/IOService.h>

#define	TTY_DIALIN_INDEX	0
#define	TTY_CALLOUT_INDEX	1
#define TTY_NUM_FLAGS		1
#define TTY_NUM_TYPES		(1 << TTY_NUM_FLAGS)

class IOSerialStreamSync;
class IOSerialSessionSync;
class IOSerialBSDClient : public IOService
{
    OSDeclareDefaultStructors(IOSerialBSDClient);

public:
    //
    // IOService overrides
    //
    virtual void free();

    virtual bool start(IOService *provider);
    virtual bool matchPropertyTable(OSDictionary *table);
    virtual bool requestTerminate(IOService *provider, IOOptionBits options);
    virtual bool didTerminate(IOService *provider, IOOptionBits options, bool *defer);

    virtual IOReturn setProperties(OSObject *properties);

    // BSD TTY linediscipline stuff
    static struct cdevsw devsw;

private:
    struct Session {
        struct tty ftty;	// Unix tty structure
        /*
         * This is the glue between the tty line discipline and the bsd
         * client.  Must be at begining of this struct otherwise I wont
         * be able to map between the tp pointer and my own class instance.
         */

        struct termios fInitTerm;
        void *fCDevNode;
        IOSerialBSDClient *fThis;
        int fErrno;		/* errno for session termination */
    } fSessions[TTY_NUM_TYPES];

    struct timeval fDTRDownTime;
    struct timeval fLastUsedTime;

    Session *fActiveSession;
    IOThread frxThread;		// Recieve data and event's thread
    IOThread ftxThread;		// Transmit data and state tracking thread

    dev_t fBaseDev;

    int fInOpensPending;	/* Count of opens waiting for carrier */
    thread_call_t fDCDThreadCall;	/* used for DCD debouncing */

    /* state determined at time of open */
    bool fPreemptAllowed; 		/* Active session is pre-emptible */
    bool fConnectTransit;		/* A thread is open() or closing()  */

    boolean_t   fAcquired:1;		/* provider has been acquired */
    boolean_t   fIsClosing:1;		/* Session is actively closing */
    boolean_t   fDeferTerminate:1;	/* A terminate has been defered */
    boolean_t   fHasAuditSleeper:1;	/* A process is sleeping on audit */
    boolean_t   fKillThreads:1;		/* Threads must terminate */
    boolean_t   fIstxEnabled:1;		/* en/disabled due to flow control */
    boolean_t   fIsrxEnabled:1;		/* TP_CREAD dependent */
    boolean_t   frxBlocked:1;		/* the rx_thread suspended */
    boolean_t   fDCDTimerDue:1;		/* DCD debounce flag */

    IOSerialStreamSync *fProvider;

    /*
     * TTY glue layer private routines
     */

    // Open/close semantic routines
    int open(dev_t dev, int flags, int devtype, struct proc *p);
    void close(dev_t dev, int flags, int devtype, struct proc *p);
    void startConnectTransit();
    void endConnectTransit();
    void initSession(Session *sp);
    bool waitOutDelay(void *event,
		      const struct timeval *start,
		      const struct timeval *duration);
    int waitForIdle();
    void preemptActive();

    // General routines
    bool createDevNodes();
    bool setBaseTypeForDev();

    IOReturn setOneProperty(const OSSymbol *key, OSObject *value);

    void optimiseInput(struct termios *t);
    void convertFlowCtrl(Session *sp, struct termios *t);

    // Modem control routines
    virtual int  mctl(u_int bits, int how);

    // Receive and Transmit engine thread functions
    void getData(Session *sp);
    void procEvent(Session *sp);
    void txload(Session *sp, u_long *wait_mask);
    void rxFunc();
    void txFunc();

    void launchThreads();
    void killThreads();
    void cleanupResources();

    // session based accessors to Serial Stream Sync 
    IOReturn sessionSetState(Session *sp, UInt32 state, UInt32 mask);
    UInt32   sessionGetState(Session *sp);
    IOReturn sessionWatchState(Session *sp, UInt32 *state, UInt32 mask);
    UInt32   sessionNextEvent(Session *sp);
    IOReturn sessionExecuteEvent(Session *sp, UInt32 event, UInt32 data);
    IOReturn sessionRequestEvent(Session *sp, UInt32 event, UInt32 *data);
    IOReturn
        sessionEnqueueEvent(Session *sp, UInt32 event, UInt32 data, bool sleep);
    IOReturn sessionDequeueEvent
        (Session *sp, UInt32 *event, UInt32 *data, bool sleep);
    IOReturn sessionEnqueueData
        (Session *sp, UInt8 *buffer, UInt32 size, UInt32 *count, bool sleep);
    IOReturn sessionDequeueData
        (Session *sp, UInt8 *buffer, UInt32 size, UInt32 *count, UInt32 min);

    // Unix character device switch table routines.
    static int  iossopen(dev_t dev, int flags, int devtype, struct proc *p);
    static int  iossclose(dev_t dev, int flags, int devtype, struct proc *p);
    static int  iossread(dev_t dev, struct uio *uio, int ioflag);
    static int  iosswrite(dev_t dev, struct uio *uio, int ioflag);
    static int  iossselect(dev_t dev, int which, void *wql, struct proc *p);
    static int  iossioctl(dev_t dev, u_long cmd, caddr_t data, int fflag,
                            struct proc *p);
    static int  iossstop(struct tty *tp, int rw);
    static void iossstart(struct tty *tp);	// assign to tp->t_oproc
    static int  iossparam(struct tty *tp, struct termios *t);
    static void iossdcddelay(thread_call_param_t vSelf, thread_call_param_t vSp);
};

#endif /* ! _IOSERIALSERVER_H */


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
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/* Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 * Copyright (c) 1994-1996 NeXT Software, Inc.  All rights reserved. 
 */

#ifndef _IOKIT_IOCONDITIONLOCK_H
#define _IOKIT_IOCONDITIONLOCK_H

#include <libkern/c++/OSObject.h>
#include <IOKit/IOLib.h>
#include <IOKit/system.h>

#include <IOKit/IOLocks.h>

class IOConditionLock : public OSObject
{
    OSDeclareDefaultStructors(IOConditionLock)

private:
    IOLock *		cond_interlock;		// condition var Simple lock
    volatile int	condition;

    IOLock *		sleep_interlock;	// sleep lock Simple lock
    unsigned char	interruptible;
    volatile bool	want_lock;
    volatile bool	waiting;

public:
    static IOConditionLock *withCondition(int condition, bool inIntr = true);
    virtual bool initWithCondition(int condition, bool inIntr = true);
    virtual void free();

    virtual bool tryLock();	// acquire lock, no waiting
    virtual int  lock();	// acquire lock (enter critical section)
    virtual void unlock();	// release lock (leave critical section)

    virtual bool getInterruptible() const;
    virtual int  getCondition() const;
    virtual int  setCondition(int condition);

    virtual int  lockWhen(int condition); // acquire lock when condition
    virtual void unlockWith(int condition); // set condition & release lock
};

#endif /* _IOKIT_IOCONDITIONLOCK_H */

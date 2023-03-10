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
/*
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved. 
 *
 * IOTimerEventSource.cpp
 *
 * HISTORY
 * 2-Feb-1999		Joe Liu (jliu) created.
 * 1999-10-14		Godfrey van der Linden(gvdl)
 *		Revamped to use thread_call APIs
 *
 */

#include <sys/cdefs.h>

__BEGIN_DECLS
#include <kern/thread_call.h>
__END_DECLS

#include <IOKit/assert.h>
#include <IOKit/system.h>

#include <IOKit/IOLib.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOWorkLoop.h>

#include <IOKit/IOTimeStamp.h>

#define super IOEventSource
OSDefineMetaClassAndStructors(IOTimerEventSource, IOEventSource)
OSMetaClassDefineReservedUnused(IOTimerEventSource, 0);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 1);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 2);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 3);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 4);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 5);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 6);
OSMetaClassDefineReservedUnused(IOTimerEventSource, 7);

// 
// reserved != 0 means IOTimerEventSource::timeoutAndRelease is being used,
// not a subclassed implementation. 
//

bool IOTimerEventSource::checkForWork() { return false; }

// Timeout handler function. This function is called by the kernel when
// the timeout interval expires.
//
void IOTimerEventSource::timeout(void *self)
{
    IOTimerEventSource *me = (IOTimerEventSource *) self;

    if (me->enabled && me->action)
    {
        IOWorkLoop *
        wl = me->workLoop;
        if (wl)
        {
            Action doit;
            wl->closeGate();
            doit = (Action) me->action;
            if (doit && me->enabled && AbsoluteTime_to_scalar(&me->abstime))
            {
                IOTimeStampConstant(IODBG_TIMES(IOTIMES_ACTION),
                                    (unsigned int) doit, (unsigned int) me->owner);
                (*doit)(me->owner, me);
            }
            wl->openGate();
        }
    }
}

void IOTimerEventSource::timeoutAndRelease(void * self, void * count)
{
    IOTimerEventSource *me = (IOTimerEventSource *) self;

    if (me->enabled && me->action)
    {
        IOWorkLoop *
        wl = me->reserved->workLoop;
        if (wl)
        {
            Action doit;
            wl->closeGate();
            doit = (Action) me->action;
            if (doit && (me->reserved->calloutGeneration == (SInt32) count))
            {
                IOTimeStampConstant(IODBG_TIMES(IOTIMES_ACTION),
                                    (unsigned int) doit, (unsigned int) me->owner);
                (*doit)(me->owner, me);
            }
            wl->openGate();
        }
    }

    me->reserved->workLoop->release();
    me->release();
}

void IOTimerEventSource::setTimeoutFunc()
{
    // reserved != 0 means IOTimerEventSource::timeoutAndRelease is being used,
    // not a subclassed implementation
    reserved = IONew(ExpansionData, 1);
    calloutEntry = (void *) thread_call_allocate((thread_call_func_t) &IOTimerEventSource::timeoutAndRelease,
                                                 (thread_call_param_t) this);
}

bool IOTimerEventSource::init(OSObject *inOwner, Action inAction)
{
    if (!super::init(inOwner, (IOEventSource::Action) inAction) )
        return false;

    setTimeoutFunc();
    if (!calloutEntry)
        return false;

    return true;
}

IOTimerEventSource *
IOTimerEventSource::timerEventSource(OSObject *inOwner, Action inAction)
{
    IOTimerEventSource *me = new IOTimerEventSource;

    if (me && !me->init(inOwner, inAction)) {
        me->release();
        return 0;
    }

    return me;
}

void IOTimerEventSource::free()
{
    if (calloutEntry) {
        cancelTimeout();
        thread_call_free((thread_call_t) calloutEntry);    
    }

    if (reserved)
        IODelete(reserved, ExpansionData, 1);

    super::free();
}

void IOTimerEventSource::cancelTimeout()
{
    if (reserved)
        reserved->calloutGeneration++;
    bool active = thread_call_cancel((thread_call_t) calloutEntry);
    AbsoluteTime_to_scalar(&abstime) = 0;
    if (active && reserved)
    {
        release();
        workLoop->release();
    }
}

void IOTimerEventSource::enable()
{
    super::enable();
    if (kIOReturnSuccess != wakeAtTime(abstime))
        super::disable(); // Problem re-scheduling timeout ignore enable
}

void IOTimerEventSource::disable()
{
    if (reserved)
        reserved->calloutGeneration++;
    bool active = thread_call_cancel((thread_call_t) calloutEntry);
    super::disable();
    if (active && reserved)
    {
        release();
        workLoop->release();
    }
}

IOReturn IOTimerEventSource::setTimeoutTicks(UInt32 ticks)
{
    return setTimeout(ticks, kTickScale);
}

IOReturn IOTimerEventSource::setTimeoutMS(UInt32 ms)
{
    return setTimeout(ms, kMillisecondScale);
}

IOReturn IOTimerEventSource::setTimeoutUS(UInt32 us)
{
    return setTimeout(us, kMicrosecondScale);
}

IOReturn IOTimerEventSource::setTimeout(UInt32 interval, UInt32 scale_factor)
{
    AbsoluteTime end;
    
    clock_interval_to_deadline(interval, scale_factor, &end);
    return wakeAtTime(end);
}

IOReturn IOTimerEventSource::setTimeout(mach_timespec_t interval)
{
    AbsoluteTime end, nsecs;

    clock_interval_to_absolutetime_interval
        (interval.tv_nsec, kNanosecondScale, &nsecs);
    clock_interval_to_deadline
        (interval.tv_sec, NSEC_PER_SEC, &end);
    ADD_ABSOLUTETIME(&end, &nsecs);

    return wakeAtTime(end);
}

IOReturn IOTimerEventSource::setTimeout(AbsoluteTime interval)
{
    AbsoluteTime end;

    clock_get_uptime(&end);
    ADD_ABSOLUTETIME(&end, &interval);

    return wakeAtTime(end);
}

IOReturn IOTimerEventSource::wakeAtTimeTicks(UInt32 ticks)
{
    return wakeAtTime(ticks, kTickScale);
}

IOReturn IOTimerEventSource::wakeAtTimeMS(UInt32 ms)
{
    return wakeAtTime(ms, kMillisecondScale);
}

IOReturn IOTimerEventSource::wakeAtTimeUS(UInt32 us)
{
    return wakeAtTime(us, kMicrosecondScale);
}

IOReturn IOTimerEventSource::wakeAtTime(UInt32 inAbstime, UInt32 scale_factor)
{
    AbsoluteTime end;
    clock_interval_to_absolutetime_interval(inAbstime, scale_factor, &end);

    return wakeAtTime(end);
}

IOReturn IOTimerEventSource::wakeAtTime(mach_timespec_t inAbstime)
{
    AbsoluteTime end, nsecs;

    clock_interval_to_absolutetime_interval
        (inAbstime.tv_nsec, kNanosecondScale, &nsecs);
    clock_interval_to_absolutetime_interval
        (inAbstime.tv_sec, kSecondScale, &end);
    ADD_ABSOLUTETIME(&end, &nsecs);

    return wakeAtTime(end);
}

void IOTimerEventSource::setWorkLoop(IOWorkLoop *inWorkLoop)
{
    super::setWorkLoop(inWorkLoop);
    if ( enabled && AbsoluteTime_to_scalar(&abstime) && workLoop )
        wakeAtTime(abstime);
}

IOReturn IOTimerEventSource::wakeAtTime(AbsoluteTime inAbstime)
{
    if (!action)
        return kIOReturnNoResources;

    abstime = inAbstime;
    if ( enabled && AbsoluteTime_to_scalar(&abstime) && workLoop )
    {
        if (reserved)
        {
            retain();
            workLoop->retain();
            reserved->workLoop = workLoop;
            reserved->calloutGeneration++;
            if (thread_call_enter1_delayed((thread_call_t) calloutEntry, 
                    (void *) reserved->calloutGeneration, abstime))
            {
                release();
                workLoop->release();
            }
        }
        else
            thread_call_enter_delayed((thread_call_t) calloutEntry, abstime);
    }

    return kIOReturnSuccess;
}

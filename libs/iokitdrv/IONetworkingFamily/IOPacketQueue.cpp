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
 * Copyright (c) 1998 Apple Computer, Inc.  All rights reserved. 
 *
 * IOPacketQueue.cpp - Implements a FIFO mbuf packet queue.
 *
 * HISTORY
 * 9-Dec-1998       Joe Liu (jliu) created.
 *
 */

#include <IOKit/assert.h>
#include <IOKit/IOLib.h>    // IOLog
#include <IOKit/network/IOPacketQueue.h>
#include "IOMbufQueue.h"

#define super OSObject
OSDefineMetaClassAndStructors( IOPacketQueue, OSObject )
OSMetaClassDefineReservedUnused( IOPacketQueue,  0);
OSMetaClassDefineReservedUnused( IOPacketQueue,  1);
OSMetaClassDefineReservedUnused( IOPacketQueue,  2);
OSMetaClassDefineReservedUnused( IOPacketQueue,  3);
OSMetaClassDefineReservedUnused( IOPacketQueue,  4);
OSMetaClassDefineReservedUnused( IOPacketQueue,  5);
OSMetaClassDefineReservedUnused( IOPacketQueue,  6);
OSMetaClassDefineReservedUnused( IOPacketQueue,  7);
OSMetaClassDefineReservedUnused( IOPacketQueue,  8);
OSMetaClassDefineReservedUnused( IOPacketQueue,  9);
OSMetaClassDefineReservedUnused( IOPacketQueue, 10);
OSMetaClassDefineReservedUnused( IOPacketQueue, 11);
OSMetaClassDefineReservedUnused( IOPacketQueue, 12);
OSMetaClassDefineReservedUnused( IOPacketQueue, 13);
OSMetaClassDefineReservedUnused( IOPacketQueue, 14);
OSMetaClassDefineReservedUnused( IOPacketQueue, 15);


//---------------------------------------------------------------------------
// Lock macros

#define LOCK     IOSimpleLockLock(_lock)
#define UNLOCK   IOSimpleLockUnlock(_lock)

//---------------------------------------------------------------------------
// Initialize an IOPacketQueue object.

bool IOPacketQueue::initWithCapacity(UInt32 capacity)
{
    if (super::init() == false)
    {
        IOLog("IOPacketQueue: super::init() failed\n");
        return false;
    }

    _queue = IONew(IOMbufQueue, 1);
    if (_queue == 0)
        return false;

    IOMbufQueueInit(_queue, capacity);

    if ((_lock = IOSimpleLockAlloc()) == 0)
        return false;

    IOSimpleLockInit(_lock);

    return true;
}

//---------------------------------------------------------------------------
// Factory method that will construct and initialize an IOPacketQueue object.

IOPacketQueue * IOPacketQueue::withCapacity(UInt32 capacity)
{
    IOPacketQueue * queue = new IOPacketQueue;

    if (queue && !queue->initWithCapacity(capacity))
    {
        queue->release();
        queue = 0;
    }
    return queue;
}

//---------------------------------------------------------------------------
// Frees the IOPacketQueue instance.

void IOPacketQueue::free()
{
    if (_lock)
    {
        IOSimpleLockFree(_lock);
        _lock = 0;
    }

    if (_queue)
    {
        flush();
        IODelete(_queue, IOMbufQueue, 1);
        _queue = 0;
    }

    super::free();
}

//---------------------------------------------------------------------------
// Get the current size of the queue.

UInt32 IOPacketQueue::getSize() const
{
    return IOMbufQueueGetSize(_queue);
}

//---------------------------------------------------------------------------
// Change the capacity of the queue.

bool IOPacketQueue::setCapacity(UInt32 capacity)
{
    IOMbufQueueSetCapacity(_queue, capacity);
    return true;
}

//---------------------------------------------------------------------------
// Get the capacity of the queue.

UInt32 IOPacketQueue::getCapacity() const
{
    return IOMbufQueueGetCapacity(_queue);
}

//---------------------------------------------------------------------------
// Peek at the head of the queue without dequeueing the packet.

const mbuf_t IOPacketQueue::peek() const
{
    return IOMbufQueuePeek(_queue);
}

//---------------------------------------------------------------------------
// Add a packet chain to the head of the queue.

void IOPacketQueue::prepend(mbuf_t m)
{
    IOMbufQueuePrepend(_queue, m);
}

void IOPacketQueue::prepend(IOPacketQueue * queue)
{
    IOMbufQueuePrepend(_queue, queue->_queue);
}

//---------------------------------------------------------------------------
// Add a packet chain to the tail of the queue.

bool IOPacketQueue::enqueue(mbuf_t m)
{
    return IOMbufQueueEnqueue(_queue, m);
}

bool IOPacketQueue::enqueue(IOPacketQueue * queue)
{
    return IOMbufQueueEnqueue(_queue, queue->_queue);
}

UInt32 IOPacketQueue::enqueueWithDrop(mbuf_t m)
{
    return IOMbufQueueEnqueue(_queue, m) ? 0 : IOMbufFree(m);
}

//---------------------------------------------------------------------------
// Remove a single packet from the head of the queue.

mbuf_t IOPacketQueue::dequeue()
{
    return IOMbufQueueDequeue(_queue);
}

//---------------------------------------------------------------------------
// Remove all packets from the queue and return the chain of packet(s).

mbuf_t IOPacketQueue::dequeueAll()
{
    return IOMbufQueueDequeueAll(_queue);
}

//---------------------------------------------------------------------------
// Remove all packets from the queue and put them back to the free mbuf
// pool. The size of the queue will be cleared to zero.

UInt32 IOPacketQueue::flush()
{
    return IOMbufFree(IOMbufQueueDequeueAll(_queue));
}

//---------------------------------------------------------------------------
// Locked forms of prepend/enqueue/dequeue/dequeueAll methods.
// A spinlock will enforce mutually exclusive queue access.

void IOPacketQueue::lockPrepend(mbuf_t m)
{
    LOCK;
    IOMbufQueuePrepend(_queue, m);
    UNLOCK;
}

bool IOPacketQueue::lockEnqueue(mbuf_t m)
{
    bool ok;
    LOCK;
    ok = IOMbufQueueEnqueue(_queue, m);
    UNLOCK;
    return ok;
}

UInt32 IOPacketQueue::lockEnqueueWithDrop(mbuf_t m)
{
    bool ok;
    LOCK;
    ok = IOMbufQueueEnqueue(_queue, m);
    UNLOCK;
    return ok ? 0 : IOMbufFree(m);
}

mbuf_t IOPacketQueue::lockDequeue()
{
    mbuf_t m;
    LOCK;
    m = IOMbufQueueDequeue(_queue);
    UNLOCK;
    return m;
}

mbuf_t IOPacketQueue::lockDequeueAll()
{
    mbuf_t m;
    LOCK;
    m = IOMbufQueueDequeueAll(_queue);
    UNLOCK;
    return m;
}

UInt32 IOPacketQueue::lockFlush()
{
    mbuf_t m;
    LOCK;
    m = IOMbufQueueDequeueAll(_queue);
    UNLOCK;
    return IOMbufFree(m);
}

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
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#include <IOKit/assert.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/pwr_mgt/RootDomain.h>
#include <IOKit/storage/IOBlockStorageDevice.h>
#include <IOKit/storage/IOBlockStorageDriver.h>
#include <IOKit/storage/IOMedia.h>

#define super IOStorage
OSDefineMetaClassAndStructors(IOBlockStorageDriver, IOStorage)

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const UInt32 kPollerInterval = 1000;                           // (ms, 1 second)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define isMediaRemovable() _removable

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static char * strclean(char * s)
{
    //
    // strclean() trims any spaces at either end of the string, strips any
    // control characters within the string, and collapses any sequence of
    // spaces within the string into a single space.
    //
 
    int sourceIndex = 0, targetIndex = 0, targetLength = 0;

    for ( ; s[sourceIndex] > '\0' && s[sourceIndex] <= ' '; sourceIndex++ );

    for ( ; s[sourceIndex]; sourceIndex++ )
    {
        if ( s[sourceIndex] < '\0' || s[sourceIndex] >= ' ' )
        {
            if ( s[sourceIndex] != ' ' )
            {
                if ( targetLength < targetIndex )
                {
                    targetIndex = targetLength + 1;
                }

                targetLength = targetIndex + 1;
            }

            s[targetIndex++] = s[sourceIndex];
        }
    }

    s[targetLength] = '\0';

    return s;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOBlockStorageDevice * IOBlockStorageDriver::getProvider() const
{
    //
    // Obtain this object's provider.  We override the superclass's method to
    // return a more specific subclass of IOService -- IOBlockStorageDevice.  
    // This method serves simply as a convenience to subclass developers.
    //

    return (IOBlockStorageDevice *) IOService::getProvider();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBlockStorageDriver::init(OSDictionary * properties)
{
    //
    // Initialize this object's minimal state.
    //

    // Ask our superclass' opinion.

#ifdef L4IOKIT
    //IOLog("IOBlockStorageDriver::init\n");
    //L4_KDB_Enter("X");
#endif

#ifndef L4OIKIT
    if (super::init(properties) == false)  return false;
#else
    if (super::init(properties) == false)  {
	IOLog("IOBlockStorageDriver::init init properties returned false\n");
	return false;
    }
#endif

    // Initialize our state.

    _expansionData = IONew(ExpansionData, 1);
#ifdef L4IOKIT
    //IOLog("IOBlockStorageDriver:: _expansionData = %p\n", _expansionData);
#endif
    if (_expansionData == 0)  return false;

    initMediaState();
    
    _ejectable                    = false;
    _lockable                     = false;
    _pollIsExpensive              = false;
    _pollIsRequired               = false;
    _removable                    = false;
    
    _mediaBlockSize               = 0;
    _maxBlockNumber               = 0;

    _maxReadBlockTransfer         = 256;
    _maxWriteBlockTransfer        = 256;
    _maxReadByteTransfer          = 131072;
    _maxWriteByteTransfer         = 131072;
    _maxReadSegmentTransfer       = 0;
    _maxWriteSegmentTransfer      = 0;
    _maxReadSegmentByteTransfer   = 0;
    _maxWriteSegmentByteTransfer  = 0;

    _mediaStateLock               = IOLockAlloc();

    if (_mediaStateLock == 0)
        return false;

    _deblockRequestWriteLock      = IOLockAlloc();
    _deblockRequestWriteLockCount = 0;
    _openClients                  = OSSet::withCapacity(2);
    _pollerCall                   = thread_call_allocate(poller, this);
    _powerEventNotifier           = 0;

    for (unsigned index = 0; index < kStatisticsCount; index++)
        _statistics[index] = OSNumber::withNumber(0ULL, 64);

    if (_deblockRequestWriteLock == 0 || _openClients == 0 || _pollerCall == 0)
        return false;

    for (unsigned index = 0; index < kStatisticsCount; index++)
        if (_statistics[index] == 0)  return false;

    // Create our registry properties.

    OSDictionary * statistics = OSDictionary::withCapacity(kStatisticsCount);

    if (statistics == 0)  return false;

    statistics->setObject( kIOBlockStorageDriverStatisticsBytesReadKey,
                           _statistics[kStatisticsBytesRead] );
    statistics->setObject( kIOBlockStorageDriverStatisticsBytesWrittenKey,
                           _statistics[kStatisticsBytesWritten] );
    statistics->setObject( kIOBlockStorageDriverStatisticsReadErrorsKey,
                           _statistics[kStatisticsReadErrors] );
    statistics->setObject( kIOBlockStorageDriverStatisticsWriteErrorsKey,
                           _statistics[kStatisticsWriteErrors] );
    statistics->setObject( kIOBlockStorageDriverStatisticsLatentReadTimeKey,
                           _statistics[kStatisticsLatentReadTime] );
    statistics->setObject( kIOBlockStorageDriverStatisticsLatentWriteTimeKey,
                           _statistics[kStatisticsLatentWriteTime] );
    statistics->setObject( kIOBlockStorageDriverStatisticsReadsKey,
                           _statistics[kStatisticsReads] );
    statistics->setObject( kIOBlockStorageDriverStatisticsWritesKey,
                           _statistics[kStatisticsWrites] );
    statistics->setObject( kIOBlockStorageDriverStatisticsReadRetriesKey,
                           _statistics[kStatisticsReadRetries] );
    statistics->setObject( kIOBlockStorageDriverStatisticsWriteRetriesKey,
                           _statistics[kStatisticsWriteRetries] );
    statistics->setObject( kIOBlockStorageDriverStatisticsTotalReadTimeKey,
                           _statistics[kStatisticsTotalReadTime] );
    statistics->setObject( kIOBlockStorageDriverStatisticsTotalWriteTimeKey,
                           _statistics[kStatisticsTotalWriteTime] );
    
    setProperty(kIOBlockStorageDriverStatisticsKey, statistics);

    statistics->release();

#ifdef L4IOKIT
   //IOLog("IOBlockStorageDriver::init all done!\n");
   //L4_KDB_Enter("X");
#endif
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBlockStorageDriver::start(IOService * provider)
{
    //
    // This method is called once we have been attached to the provider object.
    //

    // Open the block storage device.

#ifdef L4IOKIT
    //IOLog("IOBlockStorageDriver::start starting.\n");
    //L4_KDB_Enter("X");
#endif

    if (provider->open(this) == false)  return false;

    // Prepare the block storage driver for operation.

    if (handleStart(provider) == false)
    {
        provider->close(this);
        return false;
    }

    // Initiate the poller mechanism if it is required.
    if (isMediaRemovable() && isMediaPollRequired() && !isMediaPollExpensive())
    {
        lockForArbitration();        // (disable opens/closes; a recursive lock)

        if (!isOpen() && !isInactive())
            schedulePoller();                           // (schedule the poller)

        unlockForArbitration();       // (enable opens/closes; a recursive lock)
    }

    // Register this object so it can be found via notification requests. It is
    // not being registered to have I/O Kit attempt to have drivers match on it,
    // which is the reason most other services are registered -- that's not the
    // intention of this registerService call.

    registerService();

#ifdef L4IOKIT
    //IOLog("IOBlockStorageDriver::%s returning true.\n", __FUNCTION__);
    //L4_KDB_Enter("X");
#endif
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBlockStorageDriver::yield(IOService *  provider,
                                 IOOptionBits options,
                                 void *       argument)
{
    //
    // This method is called as a result of a kIOMessageServiceIsRequestingClose
    // provider message.  The argument is passed in as-is from the message.  The
    // options are unused.
    //

    bool success;

    lockForArbitration();

    // Yield the block storage device.

    success = handleYield(provider, options, argument);

    if (success)
    {
        // Close the block storage device.

        provider->close(this);
    }

    unlockForArbitration();

    return success;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::free()
{
    //
    // Free all of this object's outstanding resources.
    //

    if (_mediaStateLock)  IOLockFree(_mediaStateLock);

    if (_deblockRequestWriteLock)  IOLockFree(_deblockRequestWriteLock);
    if (_openClients)  _openClients->release();
    if (_pollerCall)  thread_call_free(_pollerCall);

    for (unsigned index = 0; index < kStatisticsCount; index++)
        if (_statistics[index])  _statistics[index]->release();

    if (_expansionData)  IODelete(_expansionData, ExpansionData, 1);

    super::free();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBlockStorageDriver::handleOpen(IOService *  client,
                                      IOOptionBits options,
                                      void *       argument)
{
    //
    // The handleOpen method grants or denies permission to access this object
    // to an interested client.  The argument is an IOStorageAccess value that
    // specifies the level of access desired -- reader or reader-writer.
    //
    // This method can be invoked to upgrade or downgrade the access level for
    // an existing client as well.  The previous access level will prevail for
    // upgrades that fail, of course.   A downgrade should never fail.  If the
    // new access level should be the same as the old for a given client, this
    // method will do nothing and return success.  In all cases, one, singular
    // close-per-client is expected for all opens-per-client received.
    //
    // This method assumes that the arbitration lock is held.
    //

    assert(client);

    // Ensure there is media in the block storage device.

    if (getMediaState() == kIOMediaStateOffline)  return false;

    // Handle the first open on removable media in a special case.

    if (isMediaRemovable() && _openClients->getCount() == 0)
    {
        // Halt the poller if it is active and this is the first open.

        if (isMediaPollRequired() && !isMediaPollExpensive())
            unschedulePoller();                       // (unschedule the poller)

        // Lock down the media while we have opens on this driver object.

        lockMedia(true);
    }

    // Process the open.

    _openClients->setObject(client);            // (works for up/downgrade case)

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBlockStorageDriver::handleIsOpen(const IOService * client) const
{
    //
    // The handleIsOpen method determines whether the specified client, or any
    // client if none is specificed, presently has an open on this object.
    //
    // This method assumes that the arbitration lock is held.
    //

    if (client)
        return _openClients->containsObject(client);
    else
        return (_openClients->getCount() != 0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::handleClose(IOService * client, IOOptionBits options)
{
    //
    // The handleClose method drops the incoming client's access to this object.
    //
    // This method assumes that the arbitration lock is held.
    //

    assert(client);

    // Process the close.

    _openClients->removeObject(client);

    // Handle the last close in a special case.

    if (_openClients->getCount() == 0)
    {
        if (isInactive())
        {
            // Yield the block storage device.

            message(kIOMessageServiceIsRequestingClose, getProvider(), 0);
        }
        else
        {
            if (isMediaRemovable())
            {
                // Unlock the removable media.

                if (getMediaState() == kIOMediaStateOnline)
                {
                    lockMedia(false);
                }

                // Reactivate the poller.

                if (isMediaPollRequired() && !isMediaPollExpensive())
                    schedulePoller();                   // (schedule the poller)
            }
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::read(IOService *          /* client */,
                                UInt64               byteStart,
                                IOMemoryDescriptor * buffer,
                                IOStorageCompletion  completion)
{
    //
    // The read method is the receiving end for all read requests from the
    // storage framework, ie. via the media object created by this driver.
    //
    // This method initiates a sequence of methods (stages) for each read/write
    // request.  The first is prepareRequest, which allocates and prepares some
    // context for the transfer; the second is deblockRequest, which aligns the
    // transfer at the media's block boundaries; third is breakUpRequest, which
    // breaks up the transfer into multiple sub-transfers when certain hardware
    // constraints are exceeded; fourth is executeRequest, which implements the
    // actual transfer from the block storage device.
    //

    // State our assumptions.

    assert(buffer->getDirection() == kIODirectionIn);

    // Prepare the transfer.

#ifdef L4IOKIT
 //   IOLog("IOBlockStorageDriver::read byteStart %llu buffer %p completion %p\n", 
	//byteStart, buffer, completion);
    //L4_KDB_Enter("XXX");
#endif
    prepareRequest(byteStart, buffer, completion);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::write(IOService *          /* client */,
                                 UInt64               byteStart,
                                 IOMemoryDescriptor * buffer,
                                 IOStorageCompletion  completion)
{
    //
    // The write method is the receiving end for all write requests from the
    // storage framework, ie. via the media object created by this driver.
    //
    // This method initiates a sequence of methods (stages) for each read/write
    // request.  The first is prepareRequest, which allocates and prepares some
    // context for the transfer; the second is deblockRequest, which aligns the
    // transfer at the media's block boundaries; third is breakUpRequest, which
    // breaks up the transfer into multiple sub-transfers when certain hardware
    // constraints are exceeded; fourth is executeRequest, which implements the
    // actual transfer from the block storage device.
    //

    // State our assumptions.

    assert(buffer->getDirection() == kIODirectionOut);

    // Prepare the transfer.

    prepareRequest(byteStart, buffer, completion);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::addToBytesTransferred(UInt64 bytesTransferred,
                                                 UInt64 totalTime,       // (ns)
                                                 UInt64 latentTime,      // (ns)
                                                 bool   isWrite)
{
    //
    // Update the total number of bytes transferred, the total transfer time,
    // and the total latency time -- used for statistics.
    //

    if (isWrite)
    {
        _statistics[kStatisticsWrites]->addValue(1);
        _statistics[kStatisticsBytesWritten]->addValue(bytesTransferred);
        _statistics[kStatisticsTotalWriteTime]->addValue(totalTime);
        _statistics[kStatisticsLatentWriteTime]->addValue(latentTime);
        if (bytesTransferred <= getMediaBlockSize())
            _statistics[kStatisticsSingleBlockWrites]->addValue(1);
    }
    else
    {
        _statistics[kStatisticsReads]->addValue(1);
        _statistics[kStatisticsBytesRead]->addValue(bytesTransferred);
        _statistics[kStatisticsTotalReadTime]->addValue(totalTime);
        _statistics[kStatisticsLatentReadTime]->addValue(latentTime);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::incrementRetries(bool isWrite)
{
    //
    // Update the total retry count -- used for statistics.
    //

    if (isWrite)
        _statistics[kStatisticsWriteRetries]->addValue(1);
    else
        _statistics[kStatisticsReadRetries]->addValue(1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::incrementErrors(bool isWrite)
{
    //
    // Update the total error count -- used for statistics.
    //

    if (isWrite)
        _statistics[kStatisticsWriteErrors]->addValue(1);
    else
        _statistics[kStatisticsReadErrors]->addValue(1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt32 IOBlockStorageDriver::getStatistics(UInt64 * statistics,
                                           UInt32   statisticsMaxCount) const
{
    //
    // Ask the driver to report its operating statistics.
    //
    // The statistics are each indexed by IOBlockStorageDriver::Statistics
    // indices.  This routine fills the caller's buffer, up to the maximum
    // count specified if the real number of statistics would overflow the
    // buffer.  The return value indicates the actual number of statistics
    // copied to the buffer.
    //
    // If the statistics buffer is not supplied or if the maximum count is
    // zero, the routine returns the proposed count of statistics instead.
    //

    if (statistics == 0)
        return kStatisticsCount;

    UInt32 statisticsCount = min(kStatisticsCount, statisticsMaxCount);

    for (unsigned index = 0; index < statisticsCount; index++)
        statistics[index] = _statistics[index]->unsigned64BitValue();

    return statisticsCount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt64 IOBlockStorageDriver::getStatistic(Statistics statistic) const
{
    //
    // Ask the driver to report one of its operating statistics.
    //

    if ((UInt32) statistic >= kStatisticsCount)  return 0;

    return _statistics[statistic]->unsigned64BitValue();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOBlockStorageDriver::Context * IOBlockStorageDriver::allocateContext()
{
    //
    // Allocate a context structure for a read/write operation.
    //

    Context * context = IONew(Context, 1);

    if (context)
    {
        bzero(context, sizeof(Context));
    }

    return context;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::deleteContext(
                                        IOBlockStorageDriver::Context * context)
{
    //
    // Delete a context structure from a read/write operation.
    //

    IODelete(context, Context, 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::prepareRequest(UInt64               byteStart,
                                          IOMemoryDescriptor * buffer,
                                          IOStorageCompletion  completion)
{
    //
    // The prepareRequest method allocates and prepares state for the transfer.
    //
    // This method is part of a sequence of methods invoked for each read/write
    // request.  The first is prepareRequest, which allocates and prepares some
    // context for the transfer; the second is deblockRequest, which aligns the
    // transfer at the media's block boundaries; third is breakUpRequest, which
    // breaks up the transfer into multiple sub-transfers when certain hardware
    // constraints are exceeded; fourth is executeRequest, which implements the
    // actual transfer from the block storage device.
    //

    Context * context;

    // Allocate a context structure to hold some of our state.

    context = allocateContext();

    if (context == 0)
    {
        complete(completion, kIOReturnNoMemory);
        return;
    }
    
    // Fill in the context structure with some of our state.

    context->block.size = getMediaBlockSize();
    context->block.type = kBlockTypeStandard;

    context->original.byteStart  = byteStart;
    context->original.buffer     = buffer;
    context->original.buffer->retain();
    context->original.completion = completion;

    clock_get_uptime(&context->timeStart);

    completion.target    = this;
    completion.action    = prepareRequestCompletion;
    completion.parameter = context;

    // Deblock the transfer.

    deblockRequest(byteStart, buffer, completion, context);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::prepareRequestCompletion(void *   target,
                                                    void *   parameter,
                                                    IOReturn status,
                                                    UInt64   actualByteCount)
{
    //
    // This is the completion routine for the prepared request.  It updates
    // the driver's statistics, performs some clean up work, then calls the
    // original request's completion routine.
    //

    Context *              context = (Context              *) parameter;
    IOBlockStorageDriver * driver  = (IOBlockStorageDriver *) target;
    bool                   isWrite;
    AbsoluteTime           time;
    UInt64                 timeInNanoseconds;

    isWrite = (context->original.buffer->getDirection() == kIODirectionOut);

    // Update the error state, on a short transfer.

    if (actualByteCount < context->original.buffer->getLength())
    {
        if (status == kIOReturnSuccess)
        {
            status = kIOReturnUnderrun;
        }
    }

    // Update the dirtied state.

    if (actualByteCount && isWrite)
    {
        driver->_mediaDirtied = true;
    }

    // Update the total number of bytes transferred and the total transfer time.

    clock_get_uptime(&time);
    SUB_ABSOLUTETIME(&time, &context->timeStart);
    absolutetime_to_nanoseconds(time, &timeInNanoseconds);

    driver->addToBytesTransferred(actualByteCount, timeInNanoseconds, 0, isWrite);

    // Update the total error count.

    if (status != kIOReturnSuccess)
    {
        driver->incrementErrors(isWrite);
    }

    // Complete the transfer request.

    IOStorage::complete(context->original.completion, status, actualByteCount);

    // Release our resources.

    context->original.buffer->release();

    driver->deleteContext(context);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::schedulePoller()
{
    //
    // Schedule the poller mechanism.
    //
    // This method assumes that the arbitration lock is held.
    //

    AbsoluteTime deadline;

    retain();

    clock_interval_to_deadline(kPollerInterval, kMillisecondScale, &deadline);
    thread_call_enter_delayed(_pollerCall, deadline);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::unschedulePoller()
{
    //
    // Unschedule the poller mechanism.
    //
    // This method assumes that the arbitration lock is held.
    //

    if (thread_call_cancel(_pollerCall))  release();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::poller(void * target, void *)
{
    //
    // This method is the timeout handler for the poller mechanism.  It polls
    // for media and reschedules another timeout if there are still no opens.
    //

#ifdef L4IOKIT
    IOLog("IOBlockStorageDriver::%s polling.\n", __func__);
#endif
    IOBlockStorageDriver * driver = (IOBlockStorageDriver *) target;

    driver->pollMedia();

    driver->lockForArbitration();    // (disable opens/closes; a recursive lock)

    if (!driver->isOpen() && !driver->isInactive())
        driver->schedulePoller();                       // (schedule the poller)

    driver->unlockForArbitration();   // (enable opens/closes; a recursive lock)

    driver->release();            // (drop the retain associated with this poll)
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOReturn IOBlockStorageDriver::message(UInt32      type,
                                       IOService * provider,
                                       void *      argument)
{
    //
    // Generic entry point for calls from the provider.  A return value of
    // kIOReturnSuccess indicates that the message was received, and where
    // applicable, that it was successful.
    //

    switch (type)
    {
        case kIOMessageMediaStateHasChanged:
        {
            IOReturn status;
            IOLockLock(_mediaStateLock);    
            status = mediaStateHasChanged((IOMediaState) argument);
            IOLockUnlock(_mediaStateLock);    
            return status;
        }
        case kIOMessageServiceIsRequestingClose:
        {
            bool success;
            success = yield(provider, 0, argument);
            return success ? kIOReturnSuccess : kIOReturnBusy;
        }
        default:
        {
            return super::message(type, provider, argument);
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/* Accept a new piece of media, doing whatever's necessary to make it
 * show up properly to the system. The arbitration lock is assumed to
 * be held during the call.
 */
IOReturn
IOBlockStorageDriver::acceptNewMedia(void)
{
    IOReturn result;
    bool ok;
    UInt64 nbytes;
    char name[128];
    bool nameSep;

    if (_maxBlockNumber) {
        nbytes = _mediaBlockSize * (_maxBlockNumber + 1);  
    } else {
        nbytes = 0;
    }

    /* Instantiate a media object and attach it to ourselves. */

    name[0] = 0;
    nameSep = false;
    if (getProvider()->getVendorString()) {
        strcat(name, getProvider()->getVendorString());
        nameSep = true;
    }
    if (getProvider()->getProductString()) {
        if (nameSep == true)  strcat(name, " ");
        strcat(name, getProvider()->getProductString());
        nameSep = true;
    }
    if (nameSep == true)  strcat(name, " ");
    strcat(name, "Media");
    strclean(name);

    _mediaObject = instantiateMediaObject(0,nbytes,_mediaBlockSize,name);
    result = (_mediaObject) ? kIOReturnSuccess : kIOReturnBadArgument;
    
    if (result == kIOReturnSuccess) {
        if (getProperty(kIOMediaIconKey, gIOServicePlane)) {
            _mediaObject->removeProperty(kIOMediaIconKey);
        }
        ok = _mediaObject->attach(this);	/* attach media object above us */
        if (ok) {
            IOService *parent = this;
            OSNumber *unit = NULL;
            OSNumber *unitLUN = NULL;
            OSString *unitName = NULL;

            /* Wire the media object to the device tree. */

            while ((parent = parent->getProvider())) {
                if (!unit) {
                    unit = OSDynamicCast(OSNumber, parent->getProperty("IOUnit"));
                }
                if (!unitLUN) {
                    unitLUN = OSDynamicCast(OSNumber, parent->getProperty("IOUnitLUN"));
                }
                if (!unitName) {
                    unitName = OSDynamicCast(OSString, parent->getProperty("IOUnitName"));
                }
                if (parent->inPlane(gIODTPlane)) {
                    IORegistryEntry *child;
                    IORegistryIterator *children;
                    if (!unit || !parent->getProvider()) {
                        break;
                    }

                    children = IORegistryIterator::iterateOver(parent, gIODTPlane);
                    if (!children) {
                        break;
                    }
                    while ((child = children->getNextObject())) {
                        if (!OSDynamicCast(IOMedia, child)) {
                            child->detachAll(gIODTPlane);
                        }
                    }
                    children->release();

                    if (_mediaObject->attachToParent(parent, gIODTPlane)) {
                        char location[ 32 ];
                        if (unitLUN && unitLUN->unsigned32BitValue()) {
                            sprintf(location, "%x,%x:0", unit->unsigned32BitValue(), unitLUN->unsigned32BitValue());
                        } else {
                            sprintf(location, "%x:0", unit->unsigned32BitValue());
                        }
                        _mediaObject->setLocation(location, gIODTPlane);
                        _mediaObject->setName(unitName ? unitName->getCStringNoCopy() : "", gIODTPlane);
                    }
                    break;
                }
            }

            _mediaPresent = true;
            _mediaObject->registerService();		/* enable matching */
        } else {
            _mediaObject->release();
            _mediaObject = 0;
            return(kIOReturnNoMemory);	/* give up now */
        }
    }
    
    return(result);
}

IOReturn
IOBlockStorageDriver::checkForMedia(void)
{
    IOReturn result;
    bool currentState;
    bool changed;
    
    IOLockLock(_mediaStateLock);    

    result = getProvider()->reportMediaState(&currentState,&changed);
    if (result != kIOReturnSuccess) {		/* the poll operation failed */
        IOLog("%s[IOBlockStorageDriver]::checkForMedia; err '%s' from reportMediaState\n",
              getName(),stringFromReturn(result));
    } else {

        changed = currentState ? !_mediaPresent : _mediaPresent;
        if (changed) {	/* the poll succeeded, media state has changed */
            result = mediaStateHasChanged(currentState ? kIOMediaStateOnline
                                                       : kIOMediaStateOffline);
        }
    }

    IOLockUnlock(_mediaStateLock);
    return(result);
}

IOReturn
IOBlockStorageDriver::mediaStateHasChanged(IOMediaState state)
{
    IOReturn result;

    /* The media has changed state. See if it's just inserted or removed. */

    if (state == kIOMediaStateOnline) {		/* media is now present */

        if (_mediaPresent) {
            return(kIOReturnBadArgument);
        }

        /* Allow a subclass to decide whether we accept the media. Such a
         * decision might be based on things like password-protection, etc.
         */

        if (validateNewMedia() == false) {	/* we're told to reject it */
#ifdef L4IOKIT
	IOLog("validateNewMedia returns false\n");
#endif
            rejectMedia();			/* so let subclass do whatever it wants */
            return(kIOReturnSuccess);		/* pretend nothing happened */
        }

        result = recordMediaParameters();	/* learn about media */
#ifdef L4IOKKIT
	IOLog("recordMediaParameters result = %d\n", result);
#endif
        if (result != kIOReturnSuccess) {	/* couldn't record params */
            initMediaState();		/* deny existence of new media */
	    IOLog("%s[IOBlockStorageDriver]::checkForMedia: err '%s' from recordMediaParameters\n",
			getName(),stringFromReturn(result));
            return(result);
        }

        /* Now we do what's necessary to make the new media
         * show up properly in the system.
         */

        lockForArbitration();    
        result = acceptNewMedia();

        if (result != kIOReturnSuccess) {
            initMediaState();		/* deny existence of new media */
	    IOLog("%s[IOBlockStorageDriver]::checkForMedia; err '%s' from acceptNewMedia\n",
            getName(),stringFromReturn(result));
        }

        unlockForArbitration();    
        return(result);		/* all done, new media is ready */

    } else {				/* media is now absent */

        lockForArbitration();
        result = decommissionMedia(true);	/* force a teardown */
        unlockForArbitration();

        if (result != kIOReturnSuccess && result != kIOReturnNoMedia) {
	    IOLog("%s[IOBlockStorageDriver]::checkForMedia; err '%s' from decommissionNewMedia\n",
			getName(),stringFromReturn(result));
            return(result);
        }

        return(kIOReturnSuccess);		/* all done; media is gone */
    }
}

UInt64
IOBlockStorageDriver::constrainByteCount(UInt64 /* requestedCount */ ,bool isWrite)
{
    if (isWrite) {
        return(_maxWriteByteTransfer);
    } else {
        return(_maxReadByteTransfer);
    }
}

/* Decommission a piece of media that has become unavailable either due to
 * ejection or some outside force (e.g. the Giant Hand of the User).
 * (I prefer the term "decommission" rather than "abandon." The former implies
 * a well-determined procedure, whereas the latter implies leaving the media
 * in an orphaned state.)
 */
/* Tear down the stack above the specified object. Usually these objects will
 * be of type IOMedia, but they could be any IOService. The arbitration lock is
 * assumed to be held during the call.
 */
IOReturn
IOBlockStorageDriver::decommissionMedia(bool forcible)
{
    IOReturn result;

    if (_mediaObject) {
        /* If this is a forcible decommission (i.e. media is gone), we don't
         * care whether the teardown worked; we forget about the media.
         */
        if ((forcible || !_openClients->containsObject(_mediaObject)) &&
            (isInactive() || _mediaObject->terminate() || forcible)) {
            IORegistryEntry * parent;

            /* Unwire the media object from the device tree. */

            if ( (parent = _mediaObject->getParentEntry(gIODTPlane)) ) {
                _mediaObject->detachFromParent(parent, gIODTPlane);
            }

            _mediaObject->release();
            _mediaObject = 0;

            initMediaState();        /* clear all knowledge of the media */
            result = kIOReturnSuccess;

        } else {
            result = kIOReturnBusy;
        }
    } else {
        result = kIOReturnNoMedia;
    }

    return(result);
}

IOReturn
IOBlockStorageDriver::ejectMedia(void)
{
    IOReturn result;

    IOLockLock(_mediaStateLock);

    if (isMediaEjectable())
    {
        bool mediaDirtied = _mediaDirtied;

        lockForArbitration();
        result = decommissionMedia(false);	/* try to teardown */
        unlockForArbitration();

        if (result == kIOReturnSuccess) {	/* eject */
            if (mediaDirtied) {
                synchronizeCache(this);
            }

            (void)lockMedia(false);

            (void)getProvider()->doEjectMedia();	/* ignore any error */
        }
    }
    else /* if (!isMediaEjectable()) */
    {
        lockForArbitration();

        if (_mediaObject) {
            if (!_openClients->containsObject(_mediaObject)) {
                result = kIOReturnSuccess;
            } else {
                result = kIOReturnBusy;
            }
        } else {
            result = kIOReturnNoMedia;
        }

        if (result == kIOReturnSuccess) {	/* eject */
            if (_mediaDirtied) {
                _mediaDirtied = false;
                synchronizeCache(this);
            }

            if (isMediaRemovable())
                (void)lockMedia(false);

            (void)getProvider()->doEjectMedia();	/* ignore any error */
        }

        unlockForArbitration();
    }

    IOLockUnlock(_mediaStateLock);

    return(result);
}

void
IOBlockStorageDriver::executeRequest(UInt64                          byteStart,
                                     IOMemoryDescriptor *            buffer,
                                     IOStorageCompletion             completion,
                                     IOBlockStorageDriver::Context * context)
{
    UInt64 block;
    UInt64 nblks;
    IOReturn result;

    if (!_mediaPresent) {		/* no media? you lose */
        complete(completion, kIOReturnNoMedia,0);
        return;
    }

    /* We know that we are never called with a request too large,
     * nor one that is misaligned with a block.
     */
    assert((byteStart           % context->block.size) == 0);
    assert((buffer->getLength() % context->block.size) == 0);
    
    block = byteStart           / context->block.size;
    nblks = buffer->getLength() / context->block.size;

/* Now the protocol-specific provider implements the actual
     * start of the data transfer: */

    result = getProvider()->doAsyncReadWrite(buffer,block,nblks,completion);
    
    if (result != kIOReturnSuccess) {		/* it failed to start */
        IOLog("%s[IOBlockStorageDriver]; executeRequest: request failed to start!\n",getName());
        complete(completion,result);
        return;
    }
}

IOReturn
IOBlockStorageDriver::formatMedia(UInt64 byteCapacity)
{
    IOReturn result;

    IOLockLock(_mediaStateLock);

    lockForArbitration();
    result = decommissionMedia(false);	/* try to teardown */
    unlockForArbitration();

    if (result == kIOReturnSuccess) {	/* format */
        result = getProvider()->doFormatMedia(byteCapacity);

        if (result == kIOReturnSuccess) {
            result = mediaStateHasChanged(kIOMediaStateOnline);
        } else {
            (void)mediaStateHasChanged(kIOMediaStateOnline);
        }
    }

    IOLockUnlock(_mediaStateLock);

    return(result);
}

const char *
IOBlockStorageDriver::getDeviceTypeName(void)
{
    return(kIOBlockStorageDeviceTypeGeneric);
}

UInt32
IOBlockStorageDriver::getFormatCapacities(UInt64 * capacities,
                                            UInt32   capacitiesMaxCount) const
{
    return(getProvider()->doGetFormatCapacities(capacities,capacitiesMaxCount));
}

UInt64
IOBlockStorageDriver::getMediaBlockSize() const
{
    return(_mediaBlockSize);
}

IOMediaState
IOBlockStorageDriver::getMediaState() const
{
    if (_mediaPresent) {
        return(kIOMediaStateOnline);
    } else {
        return(kIOMediaStateOffline);
    }
}

IOReturn
IOBlockStorageDriver::handlePowerEvent(void *target,void *refCon,
                                       UInt32 messageType,IOService *provider,
                                       void *messageArgument,vm_size_t argSize)
{
    IOBlockStorageDriver *driver = (IOBlockStorageDriver *)target;
    IOReturn result;

    switch (messageType) {
        case kIOMessageSystemWillPowerOff:
        case kIOMessageSystemWillRestart:
            if (!driver->isInactive()) {
                if (driver->_mediaPresent) {
                    if (driver->_mediaDirtied) {
                        driver->synchronizeCache(driver);
                    }
                    if (!driver->isMediaRemovable() && (messageType == kIOMessageSystemWillPowerOff)) {
                        driver->getProvider()->doEjectMedia();
                    }
                }
            }
            result = kIOReturnSuccess;
            break;

        default:
            result = kIOReturnUnsupported;
            break;
    }

    return(result);
}

bool
IOBlockStorageDriver::handleStart(IOService * provider)
{
    IOReturn result;

    OSNumber * maxBlockCountRead;
    OSNumber * maxBlockCountWrite;
    OSNumber * maxByteCountRead;
    OSNumber * maxByteCountWrite;
    OSNumber * maxSegmentCountRead;
    OSNumber * maxSegmentCountWrite;
    OSNumber * maxSegmentByteCountRead;
    OSNumber * maxSegmentByteCountWrite;

    /* The protocol-specific provider determines whether the media is removable. */

    result = getProvider()->reportRemovability(&_removable);
    if (result != kIOReturnSuccess) {
	IOLog("%s[IOBlockStorageDriver]::handleStart; err '%s' from reportRemovability\n",
			getName(),stringFromReturn(result));
        return(false);
    }

    if (_removable) {

        /* The protocol-specific provider determines whether we must poll to detect
         * media insertion. Nonremovable devices never need polling.
         */
        
        result = getProvider()->reportPollRequirements(&_pollIsRequired,&_pollIsExpensive);

            if (result != kIOReturnSuccess) {
	    IOLog("%s[IOBlockStorageDriver]::handleStart; err '%s' from reportPollRequirements\n",
			getName(),stringFromReturn(result));
            return(false);
        }
        
        /* The protocol-specific provider determines whether the media is ejectable
         * under software control.
         */
        result = getProvider()->reportEjectability(&_ejectable);
        if (result != kIOReturnSuccess) {
	    IOLog("%s[IOBlockStorageDriver]::handleStart; err '%s' from reportEjectability\n",
			getName(),stringFromReturn(result));
            return(false);
        }

        /* The protocol-specific provider determines whether the media is lockable
         * under software control.
         */
        result = getProvider()->reportLockability(&_lockable);
        if (result != kIOReturnSuccess) {
	    IOLog("%s[IOBlockStorageDriver]::handleStart; err '%s' from reportLockability\n",
			getName(),stringFromReturn(result));
            return(false);
        }

    } else {		/* fixed disk: not ejectable, not lockable */
        _ejectable	= false;
        _lockable	= false;
        _pollIsRequired	= true;		/* polling detects device disappearance */
    }
    
    /* Obtain the constraint values for reads and writes. */

    maxBlockCountRead = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumBlockCountReadKey,
                                     /* plane */ gIOServicePlane ) );
    maxBlockCountWrite = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumBlockCountWriteKey,
                                     /* plane */ gIOServicePlane ) );
    maxByteCountRead = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumByteCountReadKey,
                                     /* plane */ gIOServicePlane ) );
    maxByteCountWrite = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumByteCountWriteKey,
                                     /* plane */ gIOServicePlane ) );
    maxSegmentCountRead = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumSegmentCountReadKey,
                                     /* plane */ gIOServicePlane ) );
    maxSegmentCountWrite = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumSegmentCountWriteKey,
                                     /* plane */ gIOServicePlane ) );
    maxSegmentByteCountRead = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumSegmentByteCountReadKey,
                                     /* plane */ gIOServicePlane ) );
    maxSegmentByteCountWrite = OSDynamicCast(
                        /* class  */ OSNumber,
                        /* object */ getProperty(
                                     /* key   */ kIOMaximumSegmentByteCountWriteKey,
                                     /* plane */ gIOServicePlane ) );

    /* Obtain the constraint values for reads and writes (old method). */

    if ( maxBlockCountRead == 0 || maxBlockCountWrite == 0 )
    {
        UInt64 maxReadTransfer;
        UInt64 maxWriteTransfer;

        result = getProvider()->reportMaxReadTransfer(512, &maxReadTransfer);

        if (result == kIOReturnSuccess)
        {
            _maxReadBlockTransfer = maxReadTransfer / 512;
        }

        result = getProvider()->reportMaxWriteTransfer(512, &maxWriteTransfer);

        if (result == kIOReturnSuccess)
        {
            _maxWriteBlockTransfer = maxWriteTransfer / 512;
        }
    }

    _maxReadSegmentTransfer  = _maxReadByteTransfer  / page_size;
    _maxWriteSegmentTransfer = _maxWriteByteTransfer / page_size;

    _maxReadByteTransfer  = 0;
    _maxWriteByteTransfer = 0;

    /* Process the constraint values: */

    if ( maxBlockCountRead )
    {
        _maxReadBlockTransfer = maxBlockCountRead->unsigned64BitValue();
    }

    if ( maxBlockCountWrite )
    {
        _maxWriteBlockTransfer = maxBlockCountWrite->unsigned64BitValue();
    }

    if ( maxByteCountRead )
    {
        _maxReadByteTransfer = maxByteCountRead->unsigned64BitValue();
    }

    if ( maxByteCountWrite )
    {
        _maxWriteByteTransfer = maxByteCountWrite->unsigned64BitValue();
    }

    if ( maxSegmentCountRead )
    {
        _maxReadSegmentTransfer = maxSegmentCountRead->unsigned64BitValue();
    }

    if ( maxSegmentCountWrite )
    {
        _maxWriteSegmentTransfer = maxSegmentCountWrite->unsigned64BitValue();
    }

    if ( maxSegmentByteCountRead )
    {
        _maxReadSegmentByteTransfer = maxSegmentByteCountRead->unsigned64BitValue();
    }

    if ( maxSegmentByteCountWrite )
    {
        _maxWriteSegmentByteTransfer = maxSegmentByteCountWrite->unsigned64BitValue();
    }

    /* Publish the default constraint values: */

    if ( maxBlockCountRead == 0 )
    {
        getProvider()->setProperty(kIOMaximumBlockCountReadKey, _maxReadBlockTransfer, 64);
    }

    if ( maxBlockCountWrite == 0 )
    {
        getProvider()->setProperty(kIOMaximumBlockCountWriteKey, _maxWriteBlockTransfer, 64);
    }

    if ( maxSegmentCountRead == 0 )
    {
        getProvider()->setProperty(kIOMaximumSegmentCountReadKey, _maxReadSegmentTransfer, 64);
    }

    if ( maxSegmentCountWrite == 0 )
    {
        getProvider()->setProperty(kIOMaximumSegmentCountWriteKey, _maxWriteSegmentTransfer, 64);
    }

    /* Check for the device being ready with media inserted: */

    result = checkForMedia();

    /* The poll should never fail for nonremovable media: */
    
    if (result != kIOReturnSuccess && !_removable) {
	IOLog("%s[IOBlockStorageDriver]::handleStart: err '%s' from checkForMedia\n",
			getName(),stringFromReturn(result));
        return(false);
    }

    /* Set up the power event handler for restarts and shutdowns: */

    _powerEventNotifier = registerPrioritySleepWakeInterest(handlePowerEvent,this);
    if (_powerEventNotifier) {
        retain();
    }

    return(true);
}

/* The driver has been instructed to yield. The arbitration lock is assumed to
 * be held during the call.
 */
bool
IOBlockStorageDriver::handleYield(IOService *  provider,
                                  IOOptionBits options,
                                  void *       argument)
{
    // Determine whether there are outstanding opens on this driver object.

    if (isOpen())
    {
        return false;
    }

    // Halt the poller mechanism.

    if (isMediaRemovable() && isMediaPollRequired() && !isMediaPollExpensive())
    {
        unschedulePoller();                           // (unschedule the poller)
    }

    // Force a teardown.

    decommissionMedia(true);

    return true;
}

void
IOBlockStorageDriver::initMediaState(void)
{
    _mediaDirtied   = false;
    _mediaPresent   = false;
    _mediaType      = 0;
    _writeProtected = false;
}

IOMedia *
IOBlockStorageDriver::instantiateDesiredMediaObject(void)
{
    return(new IOMedia);
}

IOMedia *
IOBlockStorageDriver::instantiateMediaObject(UInt64 base,UInt64 byteSize,
                                        UInt32 blockSize,char *mediaName)
{
    IOMediaAttributeMask attributes = 0;
    IOMedia *m;
    bool result;

    m = instantiateDesiredMediaObject();
    if (m == NULL) {
        return(NULL);
    }

    attributes |= _ejectable ? kIOMediaAttributeEjectableMask : 0;
    attributes |= _removable ? kIOMediaAttributeRemovableMask : 0;

    result = m->init(   base,			/* base byte offset */
                        byteSize,		/* byte size */
                        blockSize,		/* preferred block size */
                        attributes,		/* attributes */
                        true,			/* TRUE if whole physical media */
                        !_writeProtected,	/* TRUE if writable */
        		"");			/* content hint */

    if (result) {
        char *picture = "External.icns";

        if (_removable) {
            picture = "Removable.icns";
        } else {
            OSDictionary *dictionary = OSDynamicCast(OSDictionary, getProvider()->getProperty(kIOPropertyProtocolCharacteristicsKey));

            if (dictionary) {
                OSString *string = OSDynamicCast(OSString, dictionary->getObject(kIOPropertyPhysicalInterconnectLocationKey));

                if (string) {
                    const char *value = string->getCStringNoCopy();

                    if (value && !strcmp(value, kIOPropertyExternalKey)) {
                        picture = "External.icns";
                    } else {
                        picture = "Internal.icns";
                    }
                }
            }
        }

        if (picture) {
            OSDictionary *dictionary = OSDictionary::withCapacity(2);
            OSString *identifier = OSString::withCString("com.apple.iokit.IOStorageFamily");
            OSString *resourceFile = OSString::withCString(picture);

            if (dictionary && identifier && resourceFile) {
                dictionary->setObject("CFBundleIdentifier", identifier);
                dictionary->setObject("IOBundleResourceFile", resourceFile);
            }

            m->setProperty(kIOMediaIconKey, dictionary);

            if (resourceFile) {
                resourceFile->release();
            }
            if (identifier) {
                identifier->release();
            }
            if (dictionary) {
                dictionary->release();
            }
        }

        m->setName(mediaName);

        return(m);
        
    } else {					/* some init error */
        m->release();
        return(NULL);		/* beats me...call it this error */
    }
}

bool
IOBlockStorageDriver::isMediaEjectable(void) const
{
    return(_ejectable);
}

bool
IOBlockStorageDriver::isMediaPollExpensive(void) const
{
    return(_pollIsExpensive);
}

bool
IOBlockStorageDriver::isMediaPollRequired(void) const
{
    return(_pollIsRequired);
}

bool
IOBlockStorageDriver::isMediaWritable(void) const
{
    return(!_writeProtected);
}

IOReturn
IOBlockStorageDriver::lockMedia(bool locked)
{
    if (_lockable) {
        return(getProvider()->doLockUnlockMedia(locked));
    } else {
        return(kIOReturnUnsupported);        
    }
}

IOReturn
IOBlockStorageDriver::pollMedia(void)
{
    if (!_pollIsRequired) {			/* shouldn't poll; it's an error */
        
        return(kIOReturnUnsupported);
        
    } else {					/* poll is required...do it */

        return(checkForMedia());
        
    }
}

IOReturn
IOBlockStorageDriver::recordMediaParameters(void)
{
    IOReturn result;

    /* Determine the device's block size and max block number.
     * What should an unformatted device report? All zeroes.
     */

    result = getProvider()->reportBlockSize(&_mediaBlockSize);    
    if (result != kIOReturnSuccess) {
        goto err;
    }

    result = getProvider()->reportMaxValidBlock(&_maxBlockNumber);    
    if (result != kIOReturnSuccess) {
        goto err;
    }

    /* Is the media write-protected? */

    result = getProvider()->reportWriteProtection(&_writeProtected);
    if (result != kIOReturnSuccess) {
        goto err;
    }

    return(kIOReturnSuccess);		/* everything was successful */

    /* If we fall thru to here, we had some kind of error. Set everything to
     * a reasonable state since we haven't got any real information.
     */

err:
    _mediaPresent = false;
    _writeProtected = true;

    return(result);
}

void
IOBlockStorageDriver::rejectMedia(void)
{
    (void)getProvider()->doEjectMedia();	/* eject it, ignoring any error */
    initMediaState();			/* deny existence of new media */
}

void
IOBlockStorageDriver::stop(IOService * provider)
{
    if (_powerEventNotifier) {
        _powerEventNotifier->remove();
        _powerEventNotifier = NULL;
        release();
    }
    super::stop(provider);
}

IOReturn
IOBlockStorageDriver::synchronizeCache(IOService *client)
{
    return(getProvider()->doSynchronizeCache());
}

bool
IOBlockStorageDriver::validateNewMedia(void)
{
    return(true);
}

// -----------------------------------------------------------------------------
// Deblocker Implementation

#include <IOKit/IOBufferMemoryDescriptor.h>

class IODeblocker : public IOMemoryDescriptor
{
    OSDeclareDefaultStructors(IODeblocker);

protected:

    UInt64                     _blockSize;

    struct
    {
        IOMemoryDescriptor * buffer;
        UInt32               offset;
        UInt32               length;
    }                          _chunks[3];
    UInt32                     _chunksCount;

    IOBufferMemoryDescriptor * _excessBuffer;
    UInt64                     _excessCountFinal;
    UInt64                     _excessCountStart;

    IOMemoryDescriptor *       _requestBuffer;
    IOStorageCompletion        _requestCompletion;
    void *                     _requestContext;
    UInt64                     _requestCount;
    bool                       _requestIsOneBlock;
    UInt64                     _requestStart;

    enum
    {
        kStageInit,
        kStagePrepareExcessStart,
        kStagePrepareExcessFinal,
        kStageLast,
        kStageDone
    } _stage;

    virtual void free();

    virtual bool initWithAddress( void *      address,       /* not supported */
                                  IOByteCount withLength,
                                  IODirection withDirection );

    virtual bool initWithAddress( vm_address_t address,      /* not supported */
                                  IOByteCount  withLength,
                                  IODirection  withDirection,
                                  task_t       withTask );

    virtual bool initWithPhysicalAddress( 
                                  IOPhysicalAddress address, /* not supported */
                                  IOByteCount       withLength,
                                  IODirection       withDirection );

    virtual bool initWithPhysicalRanges( 
                                  IOPhysicalRange * ranges,  /* not supproted */
                                  UInt32            withCount,
                                  IODirection       withDirection,
                                  bool              asReference = false );

    virtual bool initWithRanges(  IOVirtualRange * ranges,   /* not supported */
                                  UInt32           withCount,
                                  IODirection      withDirection,
                                  task_t           withTask,
                                  bool             asReference = false );

    virtual void * getVirtualSegment( IOByteCount   offset,  /* not supported */
                                      IOByteCount * length );

    IOMemoryDescriptor::withAddress;                         /* not supported */
    IOMemoryDescriptor::withPhysicalAddress;                 /* not supported */
    IOMemoryDescriptor::withPhysicalRanges;                  /* not supported */
    IOMemoryDescriptor::withRanges;                          /* not supported */
    IOMemoryDescriptor::withSubRange;                        /* not supported */

public:

    static IODeblocker * withBlockSize(
                                  UInt64               blockSize,
                                  UInt64               withRequestStart,
                                  IOMemoryDescriptor * withRequestBuffer,
                                  IOStorageCompletion  withRequestCompletion,
                                  void *               withRequestContext );

    virtual bool initWithBlockSize(
                                  UInt64               blockSize,
                                  UInt64               withRequestStart,
                                  IOMemoryDescriptor * withRequestBuffer,
                                  IOStorageCompletion  withRequestCompletion,
                                  void *               withRequestContext );

    virtual IOPhysicalAddress getPhysicalSegment( IOByteCount   offset,
                                                  IOByteCount * length );

    virtual IOReturn prepare(IODirection forDirection = kIODirectionNone);

    virtual IOReturn complete(IODirection forDirection = kIODirectionNone);

    virtual IOByteCount readBytes( IOByteCount offset,
                                   void *      bytes,
                                   IOByteCount withLength );

    virtual IOByteCount writeBytes( IOByteCount  offset,
                                    const void * bytes,
                                    IOByteCount  withLength );

    virtual bool getNextStage(UInt64 * byteStart);

    virtual void getRequestCompletion( IOStorageCompletion * completion,
                                       IOReturn *            status,
                                       UInt64 *              actualByteCount );

    virtual IOMemoryDescriptor * getRequestBuffer();

    virtual void * getRequestContext();
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#undef  super
#define super IOMemoryDescriptor
OSDefineMetaClassAndStructors(IODeblocker, IOMemoryDescriptor)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithAddress( void *      /* address       */ ,
                                   IOByteCount /* withLength    */ ,
                                   IODirection /* withDirection */ )
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithAddress( vm_address_t /* address       */ ,
                                   IOByteCount  /* withLength    */ ,
                                   IODirection  /* withDirection */ ,
                                   task_t       /* withTask      */ )
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithPhysicalAddress(
                                   IOPhysicalAddress /* address       */ ,
                                   IOByteCount       /* withLength    */ ,
                                   IODirection       /* withDirection */ )
{
    return false;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithPhysicalRanges(
                                   IOPhysicalRange * /* ranges        */ ,
                                   UInt32            /* withCount     */ ,
                                   IODirection       /* withDirection */ ,
                                   bool              /* asReference   */ )
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithRanges( IOVirtualRange * /* ranges        */ ,
                                  UInt32           /* withCount     */ ,
                                  IODirection      /* withDirection */ ,
                                  task_t           /* withTask      */ ,
                                  bool             /* asReference   */ )
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IODeblocker * IODeblocker::withBlockSize(
                                  UInt64               blockSize,
                                  UInt64               withRequestStart,
                                  IOMemoryDescriptor * withRequestBuffer,
                                  IOStorageCompletion  withRequestCompletion,
                                  void *               withRequestContext )
{
    //
    // Create a new IODeblocker.
    //

    IODeblocker * me = new IODeblocker;
    
    if ( me && me->initWithBlockSize(
                /* blockSize               */ blockSize,
                /* withRequestStart        */ withRequestStart,
                /* withRequestBuffer       */ withRequestBuffer,
                /* withRequestCompletion   */ withRequestCompletion,
                /* withRequestContext      */ withRequestContext ) == false )
    {
	    me->release();
	    me = 0;
    }

    return me;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::initWithBlockSize(
                                  UInt64               blockSize,
                                  UInt64               withRequestStart,
                                  IOMemoryDescriptor * withRequestBuffer,
                                  IOStorageCompletion  withRequestCompletion,
                                  void *               withRequestContext )
{
    //
    // Initialize an IODeblocker.
    //
    // _excessCountStart = byte count from media boundary to start of request
    // _excessCountFinal = byte count from end of request to a media boundary
    //

    UInt32 excessBufferSize = 0;

    // Ask our superclass' opinion.

    if ( super::init() == false )  return false;

    // Initialize our minimal state.

    _blockSize         = blockSize;
    _chunksCount       = 0;
    _direction         = kIODirectionNone;
    _length            = 0;

    _requestBuffer     = withRequestBuffer;
    _requestBuffer->retain();
    _requestCompletion = withRequestCompletion;
    _requestContext    = withRequestContext;
    _requestCount      = withRequestBuffer->getLength();
    _requestStart      = withRequestStart;

    _excessCountStart  = (withRequestStart                ) % blockSize;
    _excessCountFinal  = (withRequestStart + _requestCount) % blockSize;
    if ( _excessCountFinal )  _excessCountFinal = blockSize - _excessCountFinal;

    _requestIsOneBlock = (_excessCountStart + _requestCount <= blockSize);

    // Determine the necessary size for our scratch buffer.

    switch ( _requestBuffer->getDirection() )
    {
        case kIODirectionIn:                                           // (read)
        {
            excessBufferSize = max(_excessCountStart, _excessCountFinal);
        } break;

        case kIODirectionOut:                                         // (write)
        {
            if ( _excessCountStart )  excessBufferSize += blockSize;
            if ( _excessCountFinal )  excessBufferSize += blockSize;

            // If there is excess both ends of the original request, but both
            // ends reside within the same media block, then we could shorten
            // our buffer size to just one block.

            if ( _excessCountStart && _excessCountFinal && _requestIsOneBlock )
            {
                excessBufferSize -= blockSize;
            }
        } break;

        default:
        {
            assert(0);
        } break;
    }

    // Allocate our scratch buffer.

    if ( excessBufferSize )
    {
        _excessBuffer = IOBufferMemoryDescriptor::withCapacity(
                                         /* capacity      */ excessBufferSize,
                                         /* withDirection */ kIODirectionNone );
        if ( _excessBuffer == 0 )  return false;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IODeblocker::free()
{
    //
    // Free all of this object's outstanding resources.
    //

    if ( _requestBuffer )  _requestBuffer->release();
    if ( _excessBuffer )  _excessBuffer->release();

    super::free();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOReturn IODeblocker::prepare(IODirection forDirection)
{
    //
    // Prepare the memory for an I/O transfer.
    //
    // This involves paging in the memory and wiring it down for the duration
    // of the transfer.  The complete() method finishes the processing of the
    // memory after the I/O transfer finishes.
    //

    unsigned index;
    IOReturn status = kIOReturnInternalError;
    IOReturn statusUndo;

    if ( forDirection == kIODirectionNone )
    {
        forDirection = _direction;
    }

    for ( index = 0; index < _chunksCount; index++ ) 
    {
        status = _chunks[index].buffer->prepare(forDirection);
        if ( status != kIOReturnSuccess )  break;
    }

    if ( status != kIOReturnSuccess )
    {
        for ( unsigned indexUndo = 0; indexUndo <= index; indexUndo++ )
        {
            statusUndo = _chunks[index].buffer->complete(forDirection);
            assert(statusUndo == kIOReturnSuccess);
        }
    }

    return status;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOReturn IODeblocker::complete(IODirection forDirection)
{
    //
    // Complete processing of the memory after an I/O transfer finishes.
    //
    // This method shouldn't be called unless a prepare() was previously issued;
    // the prepare() and complete() must occur in pairs, before and after an I/O
    // transfer.
    //

    IOReturn status;
    IOReturn statusFinal = kIOReturnSuccess;

    if ( forDirection == kIODirectionNone )
    {
        forDirection = _direction;
    }

    for ( unsigned index = 0; index < _chunksCount; index++ ) 
    {
        status = _chunks[index].buffer->complete(forDirection);
        if ( status != kIOReturnSuccess )  statusFinal = status;
        assert(status == kIOReturnSuccess);
    }

    return statusFinal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOPhysicalAddress IODeblocker::getPhysicalSegment( IOByteCount   offset,
                                                   IOByteCount * length )
{
    //
    // This method returns the physical address of the byte at the given offset
    // into the memory,  and optionally the length of the physically contiguous
    // segment from that offset.
    //

    assert(offset <= _length);

    for ( unsigned index = 0; index < _chunksCount; index++ ) 
    {
        if ( offset < _chunks[index].length )
        {
            IOPhysicalAddress address;
            address = _chunks[index].buffer->getPhysicalSegment(
                                    /* offset */ offset + _chunks[index].offset,
                                    /* length */ length );
            if ( length )  *length = min(*length, _chunks[index].length);
            return address;
        }
        offset -= _chunks[index].length;
    }

    if ( length )  *length = 0;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void * IODeblocker::getVirtualSegment( IOByteCount   /* offset */ ,
                                       IOByteCount * /* length */ )
{
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOByteCount IODeblocker::readBytes( IOByteCount offset,
                                    void *      bytes,
                                    IOByteCount withLength )
{
    //
    // Copies data from the memory descriptor's buffer at the given offset, to
    // the specified buffer.  Returns the number of bytes copied.
    //

    IOByteCount bytesCopied = 0;
    unsigned    index;

    for ( index = 0; index < _chunksCount; index++ ) 
    {
        if ( offset < _chunks[index].length )  break;
        offset -= _chunks[index].length;
    }

    for ( ; index < _chunksCount && withLength; index++)
    {
        IOByteCount copy   = min(_chunks[index].length - offset, withLength);
        IOByteCount copied = _chunks[index].buffer->readBytes(
                                    /* offset */ offset + _chunks[index].offset,
                                    /* bytes  */ bytes,
                                    /* length */ copy );

        bytesCopied += copied;
        if ( copied != copy )  break;

        bytes = ((UInt8 *) bytes) + copied;
        withLength -= copied;
        offset = 0;
    }

    return bytesCopied;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOByteCount IODeblocker::writeBytes( IOByteCount  offset,
                                     const void * bytes,
                                     IOByteCount  withLength )
{
    //
    // Copies data to the memory descriptor's buffer at the given offset, from
    // the specified buffer.  Returns the number of bytes copied.
    //

    IOByteCount bytesCopied = 0;
    unsigned    index;

    for ( index = 0; index < _chunksCount; index++ ) 
    {
        if ( offset < _chunks[index].length )  break;
        offset -= _chunks[index].length;
    }

    for ( ; index < _chunksCount && withLength; index++)
    {
        IOByteCount copy   = min(_chunks[index].length - offset, withLength);
        IOByteCount copied = _chunks[index].buffer->writeBytes(
                                    /* offset */ offset + _chunks[index].offset,
                                    /* bytes  */ bytes,
                                    /* length */ copy );

        bytesCopied += copied;
        if ( copied != copy )  break;

        bytes = ((UInt8 *) bytes) + copied;
        withLength -= copied;
        offset = 0;
    }

    return bytesCopied;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IODeblocker::getNextStage(UInt64 * byteStart)
{
    //
    // Obtain the next stage of the transfer.   The transfer buffer will be the
    // deblocker object itself and the byte start will be returned in byteStart.
    //
    // This method must not be called if the current stage failed with an error
    // or a short byte count, but instead getRequestCompletion() must be called
    // to adjust the status and actual byte count (with respect to the original
    // request) and return the original request's completion routine.  The same
    // call to getRequestCompletion() should also be done if the getNextStage()
    // method returns false.
    //

    _chunksCount = 0;
    _direction   = kIODirectionNone;
    _length      = 0;

    switch ( _requestBuffer->getDirection() )
    {
        case kIODirectionIn:                                           // (read)
        {
            switch ( _stage )
            {
                case kStageInit:
                {
                    _stage     = kStageLast;
                    _excessBuffer->setDirection(kIODirectionIn);
                    _direction = kIODirectionIn;
                    *byteStart = _requestStart - _excessCountStart;

                    if ( _excessCountStart )
                    {
                        _chunks[_chunksCount].buffer = _excessBuffer;
                        _chunks[_chunksCount].offset = 0;
                        _chunks[_chunksCount].length = _excessCountStart;
                        _chunksCount++;
                    }

                    _chunks[_chunksCount].buffer = _requestBuffer;
                    _chunks[_chunksCount].offset = 0;
                    _chunks[_chunksCount].length = _requestBuffer->getLength();
                    _chunksCount++;

                    if ( _excessCountFinal )
                    {
                        _chunks[_chunksCount].buffer = _excessBuffer;
                        _chunks[_chunksCount].offset = 0;
                        _chunks[_chunksCount].length = _excessCountFinal;
                        _chunksCount++;
                    }
                } break;

                case kStageLast:
                {
                    _stage = kStageDone;
                } break;

                default:
                {
                    assert(0);
                } break;
            } // (switch)
        } break;

        case kIODirectionOut:                                         // (write)
        {
            switch ( _stage )
            {
                case kStageInit:
                {
                    if ( _excessCountStart )
                    {
                        _stage = kStagePrepareExcessStart;
                        _excessBuffer->setDirection(kIODirectionIn);
                        _direction = kIODirectionIn;
                        *byteStart = _requestStart - _excessCountStart;

                        _chunks[_chunksCount].buffer = _excessBuffer;
                        _chunks[_chunksCount].offset = 0;
                        _chunks[_chunksCount].length = _blockSize;
                        _chunksCount++;
                        break;
                    } 
                } // (fall thru)

                case kStagePrepareExcessStart:
                {
                    if ( _excessCountFinal )
                    {
                        // We do not issue this stage if the original transfer
                        // resides within one media block, and we already read
                        // that block into our buffer in the previous stage.

                        if ( !_excessCountStart || !_requestIsOneBlock )
                        {
                            _stage = kStagePrepareExcessFinal;
                            _excessBuffer->setDirection(kIODirectionIn);
                            _direction = kIODirectionIn;
                            *byteStart = _requestStart + _requestCount +
                                         _excessCountFinal - _blockSize;

                            _chunks[_chunksCount].buffer = _excessBuffer;
                            _chunks[_chunksCount].offset = (_requestIsOneBlock)
                                                           ? 0
                                                           : (_excessCountStart)
                                                             ? _blockSize
                                                             : 0;
                            _chunks[_chunksCount].length = _blockSize;
                            _chunksCount++;
                            break;
                        }
                    }
                } // (fall thru)

                case kStagePrepareExcessFinal:
                {
                    _stage     = kStageLast;
                    _excessBuffer->setDirection(kIODirectionOut);
                    _direction = kIODirectionOut;
                    *byteStart = _requestStart - _excessCountStart;

                    if ( _excessCountStart )
                    {
                        _chunks[_chunksCount].buffer = _excessBuffer;
                        _chunks[_chunksCount].offset = 0;
                        _chunks[_chunksCount].length = _excessCountStart;
                        _chunksCount++;
                    }

                    _chunks[_chunksCount].buffer = _requestBuffer;
                    _chunks[_chunksCount].offset = 0;
                    _chunks[_chunksCount].length = _requestBuffer->getLength();
                    _chunksCount++;

                    if ( _excessCountFinal )
                    {
                        _chunks[_chunksCount].buffer = _excessBuffer;
                        _chunks[_chunksCount].offset = (_requestIsOneBlock)
                                                       ? 0
                                                       : (_excessCountStart)
                                                         ? _blockSize
                                                         : 0;
                        _chunks[_chunksCount].offset += ( _blockSize -
                                                          _excessCountFinal );
                        _chunks[_chunksCount].length = _excessCountFinal;
                        _chunksCount++;
                    }
                } break;

                case kStageLast:
                {
                    _stage = kStageDone;
                } break;

                default:
                {
                    assert(0);
                } break;
            } // (switch)
        } break;

        default:
        {
            assert(0);
        } break;
    } // (switch)

    // Determine whether we have an abort or completion condition.

    if ( _chunksCount == 0 )  return false;

    // Compute the total length of the descriptor over all chunks.

    for ( unsigned index = 0; index < _chunksCount; index++ )
    {
        _length += _chunks[index].length;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IODeblocker::getRequestCompletion( IOStorageCompletion * completion,
                                        IOReturn *            status,
                                        UInt64 *              actualByteCount )
{
    //
    // Obtain the completion information for the original request, taking
    // into account the status and actual byte count of the current stage. 
    //

    *completion = _requestCompletion;

    switch ( _stage )
    {
        case kStageInit:                                       // (inital stage)
        {
            *status = kIOReturnInternalError;
            *actualByteCount = 0;
        } break;

        case kStagePrepareExcessStart:              // (write preparation stage)
        case kStagePrepareExcessFinal:
        {
            *actualByteCount = 0;
        } break;

        case kStageLast:                                         // (last stage)
        case kStageDone:
        {
            if ( *actualByteCount > _excessCountStart )
                *actualByteCount -= _excessCountStart;
            else
                *actualByteCount = 0;

            if ( *actualByteCount > _requestBuffer->getLength() )
                *actualByteCount = _requestBuffer->getLength();
        } break;

        default:
        {
            assert(0);
        } break;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOMemoryDescriptor * IODeblocker::getRequestBuffer()
{
    //
    // Obtain the buffer for the original request. 
    //

    return _requestBuffer;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void * IODeblocker::getRequestContext()
{
    //
    // Obtain the context for the original request. 
    //

    return _requestContext;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::deblockRequest(
                                     UInt64                          byteStart,
                                     IOMemoryDescriptor *            buffer,
                                     IOStorageCompletion             completion,
                                     IOBlockStorageDriver::Context * context )
{
    //
    // The deblockRequest method checks to see if the incoming request rests
    // on the media's block boundaries, and if not, deblocks it.  Deblocking
    // involves rounding out the request to the nearest block boundaries and
    // transferring the excess bytes into a scratch buffer.
    //
    // This method is part of a sequence of methods invoked for each read/write
    // request.  The first is prepareRequest, which allocates and prepares some
    // context for the transfer; the second is deblockRequest, which aligns the
    // transfer at the media's block boundaries; third is breakUpRequest, which
    // breaks up the transfer into multiple sub-transfers when certain hardware
    // constraints are exceeded; fourth is executeRequest, which implements the
    // actual transfer from the block storage device.
    //
    // The current implementation of deblockRequest is asynchronous.
    //

    IODeblocker * deblocker;

    // If the request is aligned with the media's block boundaries, we
    // do short-circuit the deblocker and call breakUpRequest directly.

    if ( (byteStart           % context->block.size) == 0 &&
         (buffer->getLength() % context->block.size) == 0 )
    {
        breakUpRequest(byteStart, buffer, completion, context);
        return;
    }

    // Build a deblocker object.

    deblocker = IODeblocker::withBlockSize(
                                /* blockSize             */ context->block.size,
                                /* withRequestStart      */ byteStart,
                                /* withRequestBuffer     */ buffer,
                                /* withRequestCompletion */ completion,
                                /* withRequestContext    */ context );

    if ( deblocker == 0 )
    {
        complete(completion, kIOReturnNoMemory);
        return;
    }

    // This implementation of the deblocker permits only one read-modify-write
    // at any given time.  Note that other write requests can, and do, proceed
    // simultaneously so long as they do not require the deblocker.

    if ( buffer->getDirection() == kIODirectionOut )
    {
        IOLockLock(_deblockRequestWriteLock);

        _deblockRequestWriteLockCount++;

        if ( _deblockRequestWriteLockCount > 1 )
        {
            IOLockSleep( /* lock          */ _deblockRequestWriteLock, 
                         /* event         */ _deblockRequestWriteLock,
                         /* interruptible */ THREAD_UNINT );
        }

        IOLockUnlock(_deblockRequestWriteLock);
    }

    // Execute the transfer (for the next stage).

    deblockRequestCompletion(this, deblocker, kIOReturnSuccess, 0);

    return;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::deblockRequestCompletion( void *   target,
                                                     void *   parameter,
                                                     IOReturn status,
                                                     UInt64   actualByteCount )
{
    //
    // This is the completion routine for the aligned deblocker subrequests.
    // It verifies the success of the just-completed stage,  transitions to
    // the next stage, then builds and issues a transfer for the next stage.
    //

    UInt64                 byteStart;
    IOStorageCompletion    completion;
    Context *              context;
    IODeblocker *          deblocker = (IODeblocker          *) parameter;
    IOBlockStorageDriver * driver    = (IOBlockStorageDriver *) target;

    // Determine whether an error occurred or whether there are no more stages.

    if ( actualByteCount                      < deblocker->getLength() ||
         status                              != kIOReturnSuccess       ||
         deblocker->getNextStage(&byteStart) == false                  )
    {
        // Unlock the write-lock in order to allow the next write to proceed.

        if ( deblocker->getRequestBuffer()->getDirection() == kIODirectionOut )
        {
            IOLockLock(driver->_deblockRequestWriteLock);

            driver->_deblockRequestWriteLockCount--;

            if ( driver->_deblockRequestWriteLockCount > 0 )
            {
                IOLockWakeup( /* lock  */ driver->_deblockRequestWriteLock,
                              /* event */ driver->_deblockRequestWriteLock,
                              /* one   */ true );
            }

            IOLockUnlock(driver->_deblockRequestWriteLock);
        }

        // Obtain the completion information for the original request, taking
        // into account the status and actual byte count of the current stage. 

        deblocker->getRequestCompletion(&completion, &status, &actualByteCount);

        // Complete the original request.

        IOStorage::complete(completion, status, actualByteCount);

        // Release our resources.

        deblocker->release();

        return;
    }

    // Execute the transfer (for the next stage).

    completion.target    = driver;
    completion.action    = deblockRequestCompletion;
    completion.parameter = deblocker;

    context = (Context *) deblocker->getRequestContext();

    driver->breakUpRequest(byteStart, deblocker, completion, context);

    return;
}

// -----------------------------------------------------------------------------
// Breaker Implementation

class IOBreaker : public IOSubMemoryDescriptor
{
    OSDeclareDefaultStructors(IOBreaker);

protected:

    UInt64                     _breakSize;

    UInt64                     _maximumBlockCount;
    UInt64                     _maximumByteCount;
    UInt64                     _maximumSegmentCount;
    UInt64                     _maximumSegmentByteCount;

    UInt64                     _requestBlockSize;
    IOMemoryDescriptor *       _requestBuffer;
    IOStorageCompletion        _requestCompletion;
    void *                     _requestContext;
    UInt64                     _requestCount;
    UInt64                     _requestStart;

    virtual void free();

public:

    static UInt64 getBreakSize(
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              IOMemoryDescriptor * withRequestBuffer,
                              UInt64               withRequestBufferOffset );

    static IOBreaker * withBreakSize(
                              UInt64               breakSize,
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              UInt64               withRequestStart,
                              IOMemoryDescriptor * withRequestBuffer,
                              IOStorageCompletion  withRequestCompletion,
                              void *               withRequestContext );

    virtual bool initWithBreakSize(
                              UInt64               breakSize,
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              UInt64               withRequestStart,
                              IOMemoryDescriptor * withRequestBuffer,
                              IOStorageCompletion  withRequestCompletion,
                              void *               withRequestContext );

    virtual bool getNextStage(UInt64 * byteStart);

    virtual void getRequestCompletion( IOStorageCompletion * completion,
                                       IOReturn *            status,
                                       UInt64 *              actualByteCount );

    virtual IOMemoryDescriptor * getRequestBuffer();

    virtual void * getRequestContext();
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#undef  super
#define super IOSubMemoryDescriptor
OSDefineMetaClassAndStructors(IOBreaker, IOSubMemoryDescriptor)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt64 IOBreaker::getBreakSize(
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              IOMemoryDescriptor * withRequestBuffer,
                              UInt64               withRequestBufferOffset )
{
    //
    // Determine where the next break point is given our constraints.
    //

    UInt64               breakSize    = 0;
    IOMemoryDescriptor * buffer       = withRequestBuffer;
    IOByteCount          bufferLength = withRequestBuffer->getLength();
    IOByteCount          bufferOffset = withRequestBufferOffset;
    IOPhysicalAddress    chunk        = 0;
    UInt32               chunkSize    = 0;
    IOPhysicalAddress    segment      = 0;
    UInt32               segmentCount = 0;
    UInt32               segmentSize  = 0;

    // Constrain block count.

    if ( withMaximumBlockCount )
    {
        UInt64 blockCountInBytes;

        blockCountInBytes = withMaximumBlockCount * withRequestBlockSize;

        if ( withMaximumByteCount )
        {
            withMaximumByteCount = min(blockCountInBytes, withMaximumByteCount);
        }
        else
        {
            withMaximumByteCount = blockCountInBytes;
        }
    }

    // Scan the buffer's segments.

    while ( segment || bufferOffset < bufferLength ) 
    {
        // Obtain an individual segment.

        if ( segment == 0 )
        {
            segment = buffer->getPhysicalSegment(bufferOffset, &segmentSize);

            assert(segment);
            assert(segmentSize);

            bufferOffset += segmentSize;
        }

        // Process an individual segment.

        if ( chunk == 0 )
        {
            breakSize  += segmentSize;

            chunk       = segment;
            chunkSize   = segmentSize;

            segment     = 0;
            segmentSize = 0;

            segmentCount++;
        }
        else if ( chunk + chunkSize == segment )
        {
            breakSize  += segmentSize;
            chunkSize  += segmentSize;

            segment     = 0;
            segmentSize = 0;
        }

        if ( segment == 0 )
        {
            // Constrain segment byte count.

            if ( withMaximumSegmentByteCount )
            {
                if ( chunkSize > withMaximumSegmentByteCount )
                {
                    segment     = chunk     + withMaximumSegmentByteCount;
                    segmentSize = chunkSize - withMaximumSegmentByteCount;

                    breakSize  -= segmentSize;
                    chunkSize  -= segmentSize;
                }
            }

            // Constrain byte count.

            if ( withMaximumByteCount )
            {
                if ( breakSize >= withMaximumByteCount )
                {
                    breakSize = withMaximumByteCount;
                    break;
                }
            }
        }

        // Process a coalesced segment.

        if ( segment )
        {
            // Constrain segment count.

            if ( withMaximumSegmentCount )
            {
                if ( segmentCount == withMaximumSegmentCount )
                {
                    break;
                }
            }

            chunk     = 0;
            chunkSize = 0;
        }
    }

    breakSize = IOTrunc(breakSize, withRequestBlockSize);

    return breakSize;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOBreaker * IOBreaker::withBreakSize(
                              UInt64               breakSize,
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              UInt64               withRequestStart,
                              IOMemoryDescriptor * withRequestBuffer,
                              IOStorageCompletion  withRequestCompletion,
                              void *               withRequestContext )
{
    //
    // Create a new IOBreaker.
    //

    IOBreaker * me = new IOBreaker;

    if ( me && me->initWithBreakSize(
              /* breakSize                   */ breakSize,
              /* withMaximumBlockCount       */ withMaximumBlockCount,
              /* withMaximumByteCount        */ withMaximumByteCount,
              /* withMaximumSegmentCount     */ withMaximumSegmentCount,
              /* withMaximumSegmentByteCount */ withMaximumSegmentByteCount,
              /* withRequestBlockSize        */ withRequestBlockSize,
              /* withRequestStart            */ withRequestStart,
              /* withRequestBuffer           */ withRequestBuffer,
              /* withRequestCompletion       */ withRequestCompletion,
              /* withRequestContext          */ withRequestContext ) == false )
    {
	    me->release();
	    me = 0;
    }

    return me;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBreaker::initWithBreakSize(
                              UInt64               breakSize,
                              UInt64               withMaximumBlockCount,
                              UInt64               withMaximumByteCount,
                              UInt64               withMaximumSegmentCount,
                              UInt64               withMaximumSegmentByteCount,
                              UInt64               withRequestBlockSize,
                              UInt64               withRequestStart,
                              IOMemoryDescriptor * withRequestBuffer,
                              IOStorageCompletion  withRequestCompletion,
                              void *               withRequestContext )
{
    //
    // Initialize an IOBreaker.
    //

    // Ask our superclass' opinion.

    if ( super::initSubRange( 
              /* parent        */ withRequestBuffer, 
              /* withOffset    */ 0,
              /* withLength    */ withRequestBuffer->getLength(),
              /* withDirection */ withRequestBuffer->getDirection() ) == false )
    {
        return false;
    }

    // Initialize our minimal state.

    _breakSize               = breakSize;
    _length                  = 0;

    _maximumBlockCount       = withMaximumBlockCount;
    _maximumByteCount        = withMaximumByteCount;
    _maximumSegmentCount     = withMaximumSegmentCount;
    _maximumSegmentByteCount = withMaximumSegmentByteCount;

    _requestBlockSize        = withRequestBlockSize;
    _requestBuffer           = withRequestBuffer;
    _requestBuffer->retain();
    _requestCompletion       = withRequestCompletion;
    _requestContext          = withRequestContext;
    _requestCount            = withRequestBuffer->getLength();
    _requestStart            = withRequestStart;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBreaker::free()
{
    //
    // Free all of this object's outstanding resources.
    //

    if ( _requestBuffer )  _requestBuffer->release();

    super::free();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOBreaker::getNextStage(UInt64 * byteStart)
{
    //
    // Obtain the next stage of the transfer.   The transfer buffer will be the
    // breaker object itself and the byte start will be returned in byteStart.
    //
    // This method must not be called if the current stage failed with an error
    // or a short byte count, but instead getRequestCompletion() must be called
    // to adjust the status and actual byte count (with respect to the original
    // request) and return the original request's completion routine.  The same
    // call to getRequestCompletion() should also be done if the getNextStage()
    // method returns false.
    //

    if ( _start + _length < _requestCount )
    {
        _start += _length;
        _length = min(_breakSize, _requestCount - _start);

        _breakSize = getBreakSize(
              /* withMaximumBlockCount       */ _maximumBlockCount,
              /* withMaximumByteCount        */ _maximumByteCount,
              /* withMaximumSegmentCount     */ _maximumSegmentCount,
              /* withMaximumSegmentByteCount */ _maximumSegmentByteCount,
              /* withRequestBlockSize        */ _requestBlockSize,
              /* withRequestBuffer           */ _requestBuffer,
              /* withRequestBufferOffset     */ _start + _length );
    }
    else
    {
        return false;
    }

    *byteStart = _requestStart + _start;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBreaker::getRequestCompletion( IOStorageCompletion * completion,
                                      IOReturn *            status,
                                      UInt64 *              actualByteCount )
{
    //
    // Obtain the completion information for the original request, taking
    // into account the status and actual byte count of the current stage. 
    //

    *actualByteCount += _start;
    *completion       = _requestCompletion;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOMemoryDescriptor * IOBreaker::getRequestBuffer()
{
    //
    // Obtain the buffer for the original request. 
    //

    return _requestBuffer;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void * IOBreaker::getRequestContext()
{
    //
    // Obtain the context for the original request. 
    //

    return _requestContext;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::breakUpRequest(
                                     UInt64                          byteStart,
                                     IOMemoryDescriptor *            buffer,
                                     IOStorageCompletion             completion,
                                     IOBlockStorageDriver::Context * context )
{
    //
    // The breakUpRequest method checks to see if the incoming request exceeds
    // our transfer constraints, and if so, breaks up the request into smaller
    // sub-requests.
    //
    // This method is part of a sequence of methods invoked for each read/write
    // request.  The first is prepareRequest, which allocates and prepares some
    // context for the transfer; the second is deblockRequest, which aligns the
    // transfer at the media's block boundaries; third is breakUpRequest, which
    // breaks up the transfer into multiple sub-transfers when certain hardware
    // constraints are exceeded; fourth is executeRequest, which implements the
    // actual transfer from the block storage device.
    //
    // The current implementation of breakUpRequest is asynchronous.
    //

    IOBreaker * breaker;
    UInt64      breakSize;

    // State our assumptions.

    assert((byteStart           % context->block.size) == 0);
    assert((buffer->getLength() % context->block.size) == 0);

    // Determine the transfer constraint, based on direction.

    if ( buffer->getDirection() == kIODirectionIn )
    {
        breakSize = IOBreaker::getBreakSize(
              /* withMaximumBlockCount       */ _maxReadBlockTransfer,
              /* withMaximumByteCount        */ _maxReadByteTransfer,
              /* withMaximumSegmentCount     */ _maxReadSegmentTransfer,
              /* withMaximumSegmentByteCount */ _maxReadSegmentByteTransfer,
              /* withRequestBlockSize        */ context->block.size,
              /* withRequestBuffer           */ buffer,
              /* withRequestBufferOffset     */ 0 );
    }
    else
    {
        breakSize = IOBreaker::getBreakSize(
              /* withMaximumBlockCount       */ _maxWriteBlockTransfer,
              /* withMaximumByteCount        */ _maxWriteByteTransfer,
              /* withMaximumSegmentCount     */ _maxWriteSegmentTransfer,
              /* withMaximumSegmentByteCount */ _maxWriteSegmentByteTransfer,
              /* withRequestBlockSize        */ context->block.size,
              /* withRequestBuffer           */ buffer,
              /* withRequestBufferOffset     */ 0 );
    }

    // If the request doesn't exceed our transfer constaints, we do
    // short-circuit the break-up and call executeRequest directly.

    if ( buffer->getLength() <= breakSize )
    {
        executeRequest(byteStart, buffer, completion, context);
        return;
    }

    // Round the sub-transfer size to a block boundary.

    breakSize = IOTrunc(breakSize, context->block.size);

    // Build a breaker object.

    if ( buffer->getDirection() == kIODirectionIn )
    {
        breaker = IOBreaker::withBreakSize(
              /* breakSize                   */ breakSize,
              /* withMaximumBlockCount       */ _maxReadBlockTransfer,
              /* withMaximumByteCount        */ _maxReadByteTransfer,
              /* withMaximumSegmentCount     */ _maxReadSegmentTransfer,
              /* withMaximumSegmentByteCount */ _maxReadSegmentByteTransfer,
              /* withRequestBlockSize        */ context->block.size,
              /* withRequestStart            */ byteStart,
              /* withRequestBuffer           */ buffer,
              /* withRequestCompletion       */ completion,
              /* withRequestContext          */ context );
    }
    else
    {
        breaker = IOBreaker::withBreakSize(
              /* breakSize                   */ breakSize,
              /* withMaximumBlockCount       */ _maxWriteBlockTransfer,
              /* withMaximumByteCount        */ _maxWriteByteTransfer,
              /* withMaximumSegmentCount     */ _maxWriteSegmentTransfer,
              /* withMaximumSegmentByteCount */ _maxWriteSegmentByteTransfer,
              /* withRequestBlockSize        */ context->block.size,
              /* withRequestStart            */ byteStart,
              /* withRequestBuffer           */ buffer,
              /* withRequestCompletion       */ completion,
              /* withRequestContext          */ context );
    }

    if ( breaker == 0 )
    {
        complete(completion, kIOReturnNoMemory);
        return;
    }

    // Execute the transfer (for the next stage).

    breakUpRequestCompletion(this, breaker, kIOReturnSuccess, 0);

    return;
}

OSMetaClassDefineReservedUsed(IOBlockStorageDriver, 0);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOBlockStorageDriver::breakUpRequestCompletion( void *   target,
                                                     void *   parameter,
                                                     IOReturn status,
                                                     UInt64   actualByteCount )
{
    //
    // This is the completion routine for the broken-up breaker subrequests.
    // It verifies the success of the just-completed stage,  transitions to
    // the next stage, then builds and issues a transfer for the next stage.
    //

    UInt64                 byteStart;
    IOStorageCompletion    completion;
    Context *              context;
    IOBreaker *            breaker = (IOBreaker            *) parameter;
    IOBlockStorageDriver * driver  = (IOBlockStorageDriver *) target;

    // Determine whether an error occurred or whether there are no more stages.

    if ( actualByteCount                    < breaker->getLength() ||
         status                            != kIOReturnSuccess     ||
         breaker->getNextStage(&byteStart) == false                )
    {
        // Obtain the completion information for the original request, taking
        // into account the status and actual byte count of the current stage. 

        breaker->getRequestCompletion(&completion, &status, &actualByteCount);

        // Complete the original request.

        IOStorage::complete(completion, status, actualByteCount);

        // Release our resources.

        breaker->release();

        return;
    }

    // Execute the transfer (for the next stage).

    completion.target    = driver;
    completion.action    = breakUpRequestCompletion;
    completion.parameter = breaker;

    context = (Context *) breaker->getRequestContext();

    driver->executeRequest(byteStart, breaker, completion, context);

    return;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  1);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  3);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  4);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  5);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  6);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  7);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  8);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver,  9);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 10);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 11);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 12);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 13);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 14);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 15);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 16);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 17);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 18);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 19);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 20);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 21);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 22);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 23);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 24);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 25);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 26);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 27);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 28);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 29);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 30);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOBlockStorageDriver, 31);

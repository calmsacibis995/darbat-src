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

/*!
 * @header IOPartitionScheme
 * @abstract
 * This header contains the IOPartitionScheme class definition.
 */

#ifndef _IOPARTITIONSCHEME_H
#define _IOPARTITIONSCHEME_H

/*!
 * @defined kIOPartitionSchemeClass
 * @abstract
 * The name of the IOPartitionScheme class.
 * @discussion
 * kIOPartitionSchemeClass is the name of the IOPartitionScheme class.
 */

#define kIOPartitionSchemeClass "IOPartitionScheme"

/*!
 * @defined kIOMediaPartitionIDKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaPartitionIDKey property has an OSNumber
 * value and is placed into each IOMedia instance
 * created via the partition scheme.  It is an ID that differentiates one 
 * partition from the other (within a given scheme).  It is typically an index
 * into the on-disk partition table.
 */

#define kIOMediaPartitionIDKey "Partition ID"

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/storage/IOMedia.h>
#include <IOKit/storage/IOStorage.h>

/*!
 * @class IOPartitionScheme
 * @abstract
 * The common base class for all partition scheme
 * objects.
 * @discussion
 * The IOPartitionScheme class is the common base class for all partition scheme
 * objects.  It extends the IOStorage class by implementing the appropriate open
 * and close semantics for partition objects (standard semantics are to act as a
 * multiplexor for incoming opens,  producing one outgoing open with the correct
 * access).  It also implements the default read and write semantics, which pass
 * all reads and writes through to the provider media unprocessed.    For simple
 * schemes, the default behavior is sufficient.   More complex partition schemes
 * such as RAID will want to do extra processing for reads and writes.
 */

class IOPartitionScheme : public IOStorage
{
    OSDeclareDefaultStructors(IOPartitionScheme);

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    IOStorageAccess _openLevel;
    OSSet *         _openReaders;
    OSSet *         _openReaderWriters;

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free();

    /*!
     * @function handleOpen
     * @discussion
     * The handleOpen method grants or denies permission to access this object
     * to an interested client.  The argument is an IOStorageAccess value that
     * specifies the level of access desired -- reader or reader-writer.
     *
     * This method can be invoked to upgrade or downgrade the access level for
     * an existing client as well.  The previous access level will prevail for
     * upgrades that fail, of course.   A downgrade should never fail.  If the
     * new access level should be the same as the old for a given client, this
     * method will do nothing and return success.  In all cases, one, singular
     * close-per-client is expected for all opens-per-client received.
     *
     * This implementation replaces the IOService definition of handleOpen().
     * @param client
     * Client requesting the open.
     * @param options
     * Options for the open.  Set to zero.
     * @param access
     * Access level for the open.  Set to kIOStorageAccessReader or
     * kIOStorageAccessReaderWriter.
     * @result
     * Returns true if the open was successful, false otherwise.
     */

    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       access);

    /*!
     * @function handleIsOpen
     * @discussion
     * The handleIsOpen method determines whether the specified client, or any
     * client if none is specified, presently has an open on this object.
     *
     * This implementation replaces the IOService definition of handleIsOpen().
     * @param client
     * Client to check the open state of.  Set to zero to check the open state
     * of all clients.
     * @result
     * Returns true if the client was (or clients were) open, false otherwise.
     */

    virtual bool handleIsOpen(const IOService * client) const;

    /*!
     * @function handleClose
     * @discussion
     * The handleClose method closes the client's access to this object.
     *
     * This implementation replaces the IOService definition of handleClose().
     * @param client
     * Client requesting the close.
     * @param options
     * Options for the close.  Set to zero.
     */

    virtual void handleClose(IOService * client, IOOptionBits options);

public:

    using IOStorage::read;
    using IOStorage::write;

    /*
     * Initialize this object's minimal state.
     */

    virtual bool init(OSDictionary * properties = 0);

    /*!
     * @function read
     * @discussion
     * Read data from the storage object at the specified byte offset into the
     * specified buffer, asynchronously.   When the read completes, the caller
     * will be notified via the specified completion action.
     *
     * The buffer will be retained for the duration of the read.
     *
     * For simple partition schemes, the default behavior is to simply pass the
     * read through to the provider media.  More complex partition schemes such
     * as RAID will need to do extra processing here.
     * @param client
     * Client requesting the read.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param completion
     * Completion routine to call once the data transfer is complete.
     */

    virtual void read(IOService *          client,
                      UInt64               byteStart,
                      IOMemoryDescriptor * buffer,
                      IOStorageCompletion  completion);

    /*!
     * @function write
     * @discussion
     * Write data into the storage object at the specified byte offset from the
     * specified buffer, asynchronously.   When the write completes, the caller
     * will be notified via the specified completion action.
     *
     * The buffer will be retained for the duration of the write.
     *
     * For simple partition schemes, the default behavior is to simply pass the
     * write through to the provider media. More complex partition schemes such
     * as RAID will need to do extra processing here.
     * @param client
     * Client requesting the write.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param completion
     * Completion routine to call once the data transfer is complete.
     */

    virtual void write(IOService *          client,
                       UInt64               byteStart,
                       IOMemoryDescriptor * buffer,
                       IOStorageCompletion  completion);

    /*!
     * @function synchronizeCache
     * @discussion
     * Flush the cached data in the storage object, if any, synchronously.
     * @param client
     * Client requesting the cache synchronization.
     * @result
     * Returns the status of the cache synchronization.
     */

    virtual IOReturn synchronizeCache(IOService * client);

    /*
     * Obtain this object's provider.  We override the superclass's method
     * to return a more specific subclass of OSObject -- an IOMedia.  This
     * method serves simply as a convenience to subclass developers.
     */

    virtual IOMedia * getProvider() const;

    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  0);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  1);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  2);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  3);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  4);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  5);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  6);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  7);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  8);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme,  9);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 10);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 11);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 12);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 13);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 14);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 15);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 16);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 17);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 18);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 19);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 20);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 21);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 22);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 23);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 24);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 25);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 26);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 27);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 28);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 29);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 30);
    OSMetaClassDeclareReservedUnused(IOPartitionScheme, 31);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOPARTITIONSCHEME_H */

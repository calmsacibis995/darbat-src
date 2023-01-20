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

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

#include <IOKit/IODeviceTreeSupport.h> // (gIODTPlane, ...)
#include <IOKit/IOLib.h>               // (IONew, ...)
#include <IOKit/IOMessage.h>           // (kIOMessageServicePropertyChange, ...)
#include <IOKit/storage/IOMedia.h>

#define super IOStorage
OSDefineMetaClassAndStructors(IOMedia, IOStorage)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum
{
    kIOStorageAccessWriter       = 0x00000002,
    kIOStorageAccessInvalid      = 0x0000000C,
    kIOStorageAccessReservedMask = 0xFFFFFFF0
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class IOMediaAccess
{
protected:

    IOStorageAccess _access;

public:

    inline void operator=( IOStorageAccess access )
    {
        _access = access;
    }

    inline void operator=( OSObject * access )
    {
        if ( access )
        {
            operator=( ( ( OSNumber * ) access )->unsigned32BitValue( ) );
        }
        else
        {
            operator=( kIOStorageAccessNone );
        }
    }

    inline void operator+=( IOStorageAccess access )
    {
        static UInt8 table[8][8] =
        {            /* Rea, Wri, R|S, W|S, R|E, W|E, Inv, Non */
            /* Rea */ { 000, 001, 002, 003, 006, 006, 006, 000 },
            /* Wri */ { 011, 006, 011, 006, 006, 006, 006, 011 },
            /* R|S */ { 002, 001, 002, 003, 006, 006, 006, 002 },
            /* W|S */ { 003, 006, 003, 003, 006, 006, 006, 003 },
            /* R|E */ { 006, 006, 006, 006, 006, 006, 006, 004 },
            /* W|E */ { 006, 006, 006, 006, 006, 006, 006, 015 },
            /* Inv */ { 006, 006, 006, 006, 006, 006, 006, 006 },
            /* Inv */ { 006, 006, 006, 006, 006, 006, 006, 006 }
        };

        _access = ( ( _access - 1 ) >> 1 ) & 7;
        _access = table[ ( ( access - 1 ) >> 1 ) & 7 ][ _access ];
        _access = ( ( _access & 7 ) << 1 ) + 1;
    }

    inline void operator+=( OSObject * access )
    {
        if ( access )
        {
            operator+=( ( ( OSNumber * ) access )->unsigned32BitValue( ) );
        }
    }

    inline operator IOStorageAccess( )
    {
        return _access;
    }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOStorage * IOMedia::getProvider() const
{
    //
    // Obtain this object's provider.  We override the superclass's method to
    // return a more specific subclass of OSObject -- IOStorage.  This method
    // serves simply as a convenience to subclass developers.
    //

    return (IOStorage *) IOService::getProvider();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::init(UInt64         base,
                   UInt64         size,
                   UInt64         preferredBlockSize,
                   bool           isEjectable,
                   bool           isWhole,
                   bool           isWritable,
                   const char *   contentHint,
                   OSDictionary * properties)
{
    //
    // Initialize this object's minimal state.
    //

    IOMediaAttributeMask attributes = 0;

    attributes |= isEjectable ? kIOMediaAttributeEjectableMask : 0;
    attributes |= isEjectable ? kIOMediaAttributeRemovableMask : 0;

    return init( /* base               */ base,
                 /* size               */ size,
                 /* preferredBlockSize */ preferredBlockSize,
                 /* attributes         */ attributes,
                 /* isWhole            */ isWhole,
                 /* isWritable         */ isWritable,
                 /* contentHint        */ contentHint,
                 /* properties         */ properties );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOMedia::free(void)
{
    //
    // Free all of this object's outstanding resources.
    //

    if (_openClients)  _openClients->release();

    super::free();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::attachToChild(IORegistryEntry *       client,
                            const IORegistryPlane * plane)
{
    //
    // This method is called for each client interested in the services we
    // provide.  The superclass links us as a parent to this client in the
    // I/O Kit registry on success.
    //

    OSString * s;

#ifdef L4IOKIT
    //IOLog("%s::%s attachToChild\n", getName(), __FUNCTION__);
#endif
    // Ask our superclass' opinion.

    if (super::attachToChild(client, plane) == false)  return false;

    //
    // Determine whether the client is a storage driver, which we consider
    // to be a consumer of this storage object's content and a producer of
    // new content. A storage driver need not be an IOStorage subclass, so
    // long as it identifies itself with a match category of "IOStorage".
    //
    // If the client is indeed a storage driver, we reset the media's Leaf
    // property to false and replace the media's Content property with the
    // client's Content Mask property, if any.
    //

    s = OSDynamicCast(OSString, client->getProperty(gIOMatchCategoryKey));

    if (s && !strcmp(s->getCStringNoCopy(), kIOStorageCategory))
    {
        setProperty(kIOMediaLeafKey, false);

        s = OSDynamicCast(OSString,client->getProperty(kIOMediaContentMaskKey));
        if (s)  setProperty(kIOMediaContentKey, s->getCStringNoCopy());
    }

#ifdef L4IOKIT
    //IOLog("%s::%s attachToChild done\n", getName(), __FUNCTION__);
#endif
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOMedia::detachFromChild(IORegistryEntry *       client,
                              const IORegistryPlane * plane)
{
    //
    // This method is called for each client that loses interest in the
    // services we provide.  The superclass unlinks us from this client
    // in the I/O Kit registry on success.
    //
    // Note that this method is called at a nondeterministic time after
    // our client is terminated, which means another client may already
    // have arrived and attached in the meantime.  This is not an issue
    // should the termination be issued synchrnously, however, which we
    // take advantage of when this media needs to  eliminate one of its
    // clients.  If the termination was issued on this media or farther
    // below in the hierarchy, we don't really care that the properties
    // would not  be consistent since this media object is going to die
    // anyway.
    //

    OSString * s;

    //
    // Determine whether the client is a storage driver, which we consider
    // to be a consumer of this storage object's content and a producer of
    // new content. A storage driver need not be an IOStorage subclass, so
    // long as it identifies itself with a match category of "IOStorage".
    //
    // If the client is indeed a storage driver, we reset the media's Leaf
    // property to true and reset the media's Content property to the hint
    // we obtained when this media was initialized.
    //

    s = OSDynamicCast(OSString, client->getProperty(gIOMatchCategoryKey));
 
    if (s && !strcmp(s->getCStringNoCopy(), kIOStorageCategory))
    {
        setProperty(kIOMediaContentKey, getContentHint());
        setProperty(kIOMediaLeafKey, true);
    }

    // Pass the call onto our superclass.

    super::detachFromChild(client, plane);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::handleOpen(IOService *  client,
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
    // This method will work even when the media is in the terminated state.
    //
    // We are guaranteed that no other opens or closes will be processed until
    // we make our decision, change our state, and return from this method.
    //

    IOMediaAccess   access;
    IOStorageAccess accessIn;
    IOService *     driver;
    IOMediaAccess   level;
    OSObject *      object;
    OSIterator *    objects;
    bool            rebuild;
    bool            teardown;

    //
    // State our assumptions.
    //

    assert( client );

    //
    // Initialize our minimal state.
    //

    access   = _openClients->getObject( ( OSSymbol * ) client );
    accessIn = ( IOStorageAccess ) argument;

    rebuild  = false;
    teardown = false;

    //
    // Determine whether one of our clients is a storage driver.
    //

    object = ( OSObject * ) OSSymbol::withCString( kIOStorageCategory );

    if ( object == 0 )
    {
        return false;
    }

    driver = getClientWithCategory( ( OSSymbol * ) object );

    object->release( );

    //
    // Reevaluate the open we have on the level below us.
    //

    objects = OSCollectionIterator::withCollection( _openClients );

    if ( objects == 0 )
    {
        return false;
    }

    level = kIOStorageAccessNone;

    while ( ( object = objects->getNextObject( ) ) )
    {
        if ( object != client )
        {
            level += _openClients->getObject( ( OSSymbol * ) object );
        }
    }

    objects->release( );

    //
    // Evaluate the open we have from the level above us.
    //

    level += accessIn;

    if ( level == kIOStorageAccessInvalid )
    {
        return false;
    }

    if ( ( accessIn & kIOStorageAccessWriter ) )
    {
        if ( _isWritable == false )
        {
            return false;
        }

        if ( ( accessIn & kIOStorageAccessSharedLock ) == false )
        {
            if ( driver )
            {
                if ( driver != client )
                {
                    teardown = true;
                }
            }
        }
    }
    else
    {
        if ( ( access & kIOStorageAccessWriter ) )
        {
            rebuild = true;
        }
    }

    //
    // If we are in the terminated state, we only accept downgrades.
    //

    if ( isInactive( ) )
    {
        if ( access == kIOStorageAccessNone )
        {
            return false;
        }

        if ( ( accessIn & kIOStorageAccessWriter ) )
        {
            return false;
        }
    }

    //
    // Determine whether the storage driver above us can be torn down, if
    // this is a new exclusive writer open, or an upgrade to an exclusive
    // writer open (and if the client issuing the open is not the storage
    // driver itself).
    //

    if ( teardown )
    {
        if ( _openClients->getObject( ( OSSymbol * ) driver ) )
        {
            return false;
        }

        if ( driver->terminate( kIOServiceSynchronous ) == false )
        {
            return false;
        }
    }

    //
    // Determine whether the storage object below us accepts the open at this
    // multiplexed level of access -- new opens, upgrades and downgrades (and
    // no changes in access) all enter through the same method.
    //

    level = ( level & kIOStorageAccessReaderWriter );

    if ( _openLevel != level )
    {
        IOStorage * provider;

        provider = OSDynamicCast( IOStorage, getProvider( ) );

        if ( provider )
        {
            bool success;

            success = provider->open( this, options, level );

            if ( success == false )
            {
                //
                // We were unable to open the storage object below us.  We
                // must recover from the terminate we invoked above before
                // bailing out, if applicable, by re-registering the media
                // object for matching.
                //

                if ( teardown )
                {
                    registerService( kIOServiceAsynchronous );
                }

                return false;
            }
        }
    }

    //
    // Process the open.
    //

    object = OSNumber::withNumber( level, 32 );

    assert( object );

    _openClients->setObject( ( OSSymbol * ) client, object );

    _openLevel = level;

    object->release( );

    //
    // If a writer just closed, re-register the media so that I/O Kit will
    // attempt to match storage drivers that may now be interested in this
    // media.
    //

    if ( rebuild )
    {
        if ( isInactive( ) == false )
        {
            if ( driver )
            {
                if ( driver != client )
                {
                    driver->requestProbe( 0 );
                }
            }
            else
            {
                registerService( kIOServiceAsynchronous );
            }
        }
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::handleIsOpen(const IOService * client) const
{
    //
    // The handleIsOpen method determines whether the specified client, or any
    // client if none is specificed, presently has an open on this object.
    //
    // This method will work even when the media is in the terminated state.
    //
    // We are guaranteed that no other opens or closes will be processed until
    // we return from this method.
    //

    if ( client )
    {
        return _openClients->getObject( ( OSSymbol * ) client ) ? true : false;
    }
    else
    {
        return _openClients->getCount( ) ? true : false;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOMedia::handleClose(IOService * client, IOOptionBits options)
{
    //
    // A client is informing us that it is giving up access to our contents.
    //
    // This method will work even when the media is in the terminated state.
    //
    // We are guaranteed that no other opens or closes will be processed until
    // we change our state and return from this method.
    //

    IOMediaAccess access;
    IOService *   driver;
    IOMediaAccess level;
    OSObject *    object;
    OSIterator *  objects;

    //
    // State our assumptions.
    //

    assert( client );

    assert( _openClients->getObject( ( OSSymbol * ) client ) );

    //
    // Initialize our minimal state.
    //

    access = _openClients->getObject( ( OSSymbol * ) client );

    //
    // Determine whether one of our clients is a storage driver.
    //

    object = ( OSObject * ) OSSymbol::withCString( kIOStorageCategory );

    if ( object == 0 )
    {
        return;
    }

    driver = getClientWithCategory( ( OSSymbol * ) object );

    object->release( );

    //
    // Reevaluate the open we have on the level below us.
    //

    objects = OSCollectionIterator::withCollection( _openClients );

    if ( objects == 0 )
    {
        return;
    }

    level = kIOStorageAccessNone;

    while ( ( object = objects->getNextObject( ) ) )
    {
        if ( object != client )
        {
            level += _openClients->getObject( ( OSSymbol * ) object );
        }
    }

    objects->release( );

    //
    // If no opens remain, we close, or if no writers remain, but readers do,
    // we downgrade.
    //

    level = ( level & kIOStorageAccessReaderWriter );

    if ( _openLevel != level )
    {
        IOStorage * provider;

        provider = OSDynamicCast( IOStorage, getProvider( ) );

        if ( provider )
        {
            if ( level == kIOStorageAccessNone )
            {
                provider->close( this, options );
            }
            else
            {
                bool success;

                success = provider->open( this, 0, level );

                assert( success );
            }
        }
    }

    //
    // Process the close.
    //

    _openClients->removeObject( ( OSSymbol * ) client );

    _openLevel = level;

    //
    // If a writer just closed, re-register the media so that I/O Kit will
    // attempt to match storage drivers that may now be interested in this
    // media.
    //

    if ( ( access & kIOStorageAccessWriter ) )
    {
        if ( isInactive( ) == false )
        {
            if ( driver )
            {
                if ( driver != client )
                {
                    driver->requestProbe( 0 );
                }
            }
            else
            {
                registerService( kIOServiceAsynchronous );
            }
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOMedia::read(IOService *          /* client */,
                   UInt64               byteStart,
                   IOMemoryDescriptor * buffer,
                   IOStorageCompletion  completion)
{
    //
    // Read data from the storage object at the specified byte offset into the
    // specified buffer, asynchronously.   When the read completes, the caller
    // will be notified via the specified completion action.
    //
    // The buffer will be retained for the duration of the read.
    //
    // This method will work even when the media is in the terminated state.
    //

    if (isInactive())
    {
#ifdef L4OKIT
	IOLog("IOMedia::%s isInactive\n", __FUNCTION__);
#endif
        complete(completion, kIOReturnNoMedia);
        return;
    }

    if (_openLevel == kIOStorageAccessNone)    // (instantaneous value, no lock)
    {
#ifdef L4IOKIT
	IOLog("IOMedia::%s kIOStorageAccessNone\n", __FUNCTION__);
#endif
        complete(completion, kIOReturnNotOpen);
        return;
    }

    if (_mediaSize == 0 || _preferredBlockSize == 0)
    {
#ifdef L4IOKIT
	IOLog("IOMedia::%s unformatted media\n", __FUNCTION__);
#endif
        complete(completion, kIOReturnUnformattedMedia);
        return;
    }

    if (buffer == 0)
    {
        complete(completion, kIOReturnBadArgument);
        return;
    }

    if (_mediaSize < byteStart + buffer->getLength())
    {
        complete(completion, kIOReturnBadArgument);
        return;
    }

    byteStart += _mediaBase;

    getProvider()->read(this, byteStart, buffer, completion);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOMedia::write(IOService *          client,
                    UInt64               byteStart,
                    IOMemoryDescriptor * buffer,
                    IOStorageCompletion  completion)
{
    //
    // Write data into the storage object at the specified byte offset from the
    // specified buffer, asynchronously.   When the write completes, the caller
    // will be notified via the specified completion action.
    //
    // The buffer will be retained for the duration of the write.
    //
    // This method will work even when the media is in the terminated state.
    //

    if (isInactive())
    {
        complete(completion, kIOReturnNoMedia);
        return;
    }

    if (_openLevel == kIOStorageAccessNone)    // (instantaneous value, no lock)
    {
        complete(completion, kIOReturnNotOpen);
        return;
    }

    if (_openLevel == kIOStorageAccessReader)  // (instantaneous value, no lock)
    {
///m:2425148:workaround:commented:start
//        complete(completion, kIOReturnNotPrivileged);
//        return;
///m:2425148:workaround:commented:stop
    }

    if (_isWritable == 0)
    {
        complete(completion, kIOReturnLockedWrite);
        return;
    }

    if (_mediaSize == 0 || _preferredBlockSize == 0)
    {
        complete(completion, kIOReturnUnformattedMedia);
        return;
    }

    if (buffer == 0)
    {
        complete(completion, kIOReturnBadArgument);
        return;
    }

    if (_mediaSize < byteStart + buffer->getLength())
    {
        complete(completion, kIOReturnBadArgument);
        return;
    }

    byteStart += _mediaBase;
    getProvider()->write(this, byteStart, buffer, completion);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOReturn IOMedia::synchronizeCache(IOService * client)
{
    //
    // Flush the cached data in the storage object, if any, synchronously.
    //

    if (isInactive())
    {
        return kIOReturnNoMedia;
    }

    if (_openLevel == kIOStorageAccessNone)    // (instantaneous value, no lock)
    {
        return kIOReturnNotOpen;
    }

    if (_openLevel == kIOStorageAccessReader)  // (instantaneous value, no lock)
    {
///m:2425148:workaround:commented:start
//        return kIOReturnNotPrivileged;
///m:2425148:workaround:commented:stop
    }

    if (_isWritable == 0)
    {
        return kIOReturnLockedWrite;
    }

    if (_mediaSize == 0 || _preferredBlockSize == 0)
    {
        return kIOReturnUnformattedMedia;
    }

    return getProvider()->synchronizeCache(this);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt64 IOMedia::getPreferredBlockSize() const
{
    //
    // Ask the media object for its natural block size.  This information
    // is useful to clients that want to optimize access to the media.
    //
#ifndef L4IOKIT
    return _preferredBlockSize;
#else
    // sigh, this returns garbage smetimes, no idea why 
    return 512;	/* for disk.  Likely to change for L4IOKit batching */
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt64 IOMedia::getSize() const
{
    //
    // Ask the media object for its total length in bytes.
    //

    return _mediaSize;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

UInt64 IOMedia::getBase() const
{
    //
    // Ask the media object for its byte offset relative to its provider media
    // object below it in the storage hierarchy.
    //

    return _mediaBase;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::isEjectable() const
{
    //
    // Ask the media object whether it is ejectable.
    //

    return (_attributes & kIOMediaAttributeEjectableMask) ? true : false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::isFormatted() const
{
    //
    // Ask the media object whether it is formatted.
    //

    return (_mediaSize && _preferredBlockSize);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::isWritable() const
{
    //
    // Ask the media object whether it is writable.
    //

    return _isWritable;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::isWhole() const
{
    //
    // Ask the media object whether it represents the whole disk.
    //

    return _isWhole;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const char * IOMedia::getContent() const
{
    //
    // Ask the media object for a description of its contents.  The description
    // is the same as the hint at the time of the object's creation,  but it is
    // possible that the description be overrided by a client (which has probed
    // the media and identified the content correctly) of the media object.  It
    // is more accurate than the hint for this reason.  The string is formed in
    // the likeness of Apple's "Apple_HFS" strings or in the likeness of a UUID.
    //
    // The content description can be overrided by any client that matches onto
    // this media object with a match category of kIOStorageCategory.  The media
    // object checks for a kIOMediaContentMaskKey property in the client, and if
    // it finds one, it copies it into kIOMediaContentKey property.
    //

    OSString * string;

    string = OSDynamicCast(OSString, getProperty(kIOMediaContentKey));
    if (string == 0)  return "";
    return string->getCStringNoCopy();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const char * IOMedia::getContentHint() const
{
    //
    // Ask the media object for a hint of its contents.  The hint is set at the
    // time of the object's creation, should the creator have a clue as to what
    // it may contain.  The hint string does not change for the lifetime of the
    // object and is also formed in the likeness of Apple's "Apple_HFS" strings
    // or in the likeness of a UUID.
    //

    OSString * string;

    string = OSDynamicCast(OSString, getProperty(kIOMediaContentHintKey));
    if (string == 0)  return "";
    return string->getCStringNoCopy();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::matchPropertyTable(OSDictionary * table, SInt32 * score)
{
    //
    // Compare the properties in the supplied table to this object's properties.
    //

    OSCollectionIterator * properties;
    bool                   success = true;

    // Ask our superclass' opinion.

    if (super::matchPropertyTable(table, score) == false)  return false;
#ifdef L4IOKIT
#if 0
    if (super::matchPropertyTable(table, score) == false)  {
	IOLog("%s::%s matchPropertyTable returned false.\n",
	    getName(), __FUNCTION__);

	return false;
    }
#endif
#endif
    // Compare properties.

    properties = OSCollectionIterator::withCollection(table);

    if (properties)
    {
        OSSymbol * property;

        while ((property = (OSSymbol *) properties->getNextObject()))
        {
///m:2922205:workaround:added:start
            extern const OSSymbol * gIOMatchCategoryKey;
            extern const OSSymbol * gIOProbeScoreKey;

#ifdef L4IOKIT
#if 0
	    OSString *__s = OSDynamicCast(OSString, property);
	    if (__s) {
	    IOLog("%s::%s prop is %s \n", 
		getName(),
		__FUNCTION__,
		__s->getCStringNoCopy());
	    } else {
		IOLog("%s::%s OSDynamicCast failed.\n", 
		getName(), __FUNCTION__);
	    }
#endif
#endif
            if ( property->isEqualTo(gIOMatchCategoryKey) ||
                 property->isEqualTo(gIOProbeScoreKey   ) )
            {
                continue;
            }
///m:2922205:workaround:added:stop
            OSObject * valueFromMedia = copyProperty(property);
            OSObject * valueFromTable = table->getObject(property);

#ifdef L4IOKIT
#if 0
	    if (!valueFromMedia)
		IOLog("%s::%s could not do valueFromMedia is NULL\n",
		    getName(), __FUNCTION__);
#endif
#endif
            if (valueFromMedia)
            {
#ifdef L4IOKIT
#if 0
		OSString *p, *q;

		p = OSDynamicCast(OSString, valueFromMedia);
		q = OSDynamicCast(OSString, valueFromTable);

		IOLog("%s::%s valueFromMedia %s valueFromTable %s\n",
		    getName(), __FUNCTION__,
		    p->getCStringNoCopy(), q->getCStringNoCopy());
#endif
#endif
                success = valueFromMedia->isEqualTo(valueFromTable);

                valueFromMedia->release();

                if (success == false)  break;
            }
        }

        properties->release();
    }

    return success;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOMedia::init(UInt64               base,
                   UInt64               size,
                   UInt64               preferredBlockSize,
                   IOMediaAttributeMask attributes,
                   bool                 isWhole,
                   bool                 isWritable,
                   const char *         contentHint,
                   OSDictionary *       properties)
{
    //
    // Initialize this object's minimal state.
    //

    bool isEjectable;
    bool isRemovable;

    // Ask our superclass' opinion.

    if (_openClients == 0)
    {
        if (super::init(properties) == false)  return false;
    }

    // Initialize our state.

    isEjectable = (attributes & kIOMediaAttributeEjectableMask) ? true : false;
    isRemovable = (attributes & kIOMediaAttributeRemovableMask) ? true : false;

    if (isEjectable)
    {
        attributes |= kIOMediaAttributeRemovableMask;
        isRemovable = true;
    }

    _attributes         = attributes;
    _mediaBase          = base;
    _isWhole            = isWhole;
    _isWritable         = isWritable;
    _preferredBlockSize = preferredBlockSize;

///m:3879984:workaround:added:start
    if (size > _mediaSize)
    {
#ifdef L4IOKIT	/* gcc4: cast to lvalue invalid */
        _mediaSize = (volatile UInt64)((size & (UINT64_MAX ^ UINT32_MAX)) | (_mediaSize & UINT32_MAX));
#else
        (volatile UInt64) _mediaSize = (size & (UINT64_MAX ^ UINT32_MAX)) | (_mediaSize & UINT32_MAX);
#endif
    }
    else
    {
#ifdef L4IOKIT	/* gcc4: cast to lvalue invalid */
        _mediaSize = (volatile UInt64)((size & UINT32_MAX) | (_mediaSize & (UINT64_MAX ^ UINT32_MAX)));
#else
        (volatile UInt64) _mediaSize = (size & UINT32_MAX) | (_mediaSize & (UINT64_MAX ^ UINT32_MAX));
#endif
    }
///m:3879984:workaround:added:stop
#ifdef L4IOKIT	/* gcc4: cast to lvalue invalid */
    _mediaSize = (volatile UInt64)size;
#else
    (volatile UInt64) _mediaSize = size;
#endif

    if (_openClients == 0)
    {
        _openClients = OSDictionary::withCapacity(2);
        _openLevel   = kIOStorageAccessNone;
    }

    if (_openClients == 0)  return false;

    // Create our registry properties.

    setProperty(kIOMediaContentKey,            contentHint ? contentHint : "");
    setProperty(kIOMediaContentHintKey,        contentHint ? contentHint : "");
    setProperty(kIOMediaEjectableKey,          isEjectable);
    setProperty(kIOMediaLeafKey,               true);
    setProperty(kIOMediaPreferredBlockSizeKey, preferredBlockSize, 64);
    setProperty(kIOMediaRemovableKey,          isRemovable);
    setProperty(kIOMediaSizeKey,               size, 64);
    setProperty(kIOMediaWholeKey,              isWhole);
    setProperty(kIOMediaWritableKey,           isWritable);

    messageClients(kIOMessageServicePropertyChange);

#ifdef L4IOKIT
    //IOLog("%s::init returning true.\n", getName());
#endif
    return true;
}

OSMetaClassDefineReservedUsed(IOMedia, 0);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOMediaAttributeMask IOMedia::getAttributes() const
{
    //
    // Ask the media object for its attributes.
    //

    return _attributes;
}

OSMetaClassDefineReservedUsed(IOMedia, 1);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 3);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 4);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 5);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 6);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 7);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 8);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 9);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 10);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 11);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 12);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 13);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 14);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOMedia, 15);

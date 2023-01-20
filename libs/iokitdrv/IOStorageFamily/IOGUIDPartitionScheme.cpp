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
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOLib.h>
#include <IOKit/storage/IOFDiskPartitionScheme.h>
#include <IOKit/storage/IOGUIDPartitionScheme.h>
#include <libkern/OSByteOrder.h>
#include <sys/utfconv.h>

#ifdef L4IOKIT
#include <l4/kdebug.h>
/* XXX HACK  */
extern "C" uint32_t        crc32(uint32_t crc, const void *bufp, size_t len);
#endif

#define super IOPartitionScheme
OSDefineMetaClassAndStructors(IOGUIDPartitionScheme, IOPartitionScheme);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define UCS_LITTLE_ENDIAN 0x00000001

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static size_t ucs2_to_utf8( const uint16_t * ucs2str,
                            size_t           ucs2strsiz,
                            char *           utf8str,
                            size_t           utf8strsiz,
                            uint32_t         flags )
{
    size_t ucs2strlen;
    size_t utf8strlen;

    for ( ucs2strlen = 0; ucs2strlen < ucs2strsiz; ucs2strlen++ )
    {
        if ( ucs2str[ucs2strlen] == 0 )  break;
    }

    utf8_encodestr( ucs2str,
                    ucs2strlen * sizeof(uint16_t),
                    (u_int8_t *) utf8str,
                    &utf8strlen,
                    utf8strsiz,
                    '/',
// L4IOKIT!!
#if __BIG_ENDIAN__
//#ifdef __BIG_ENDIAN__
                    (flags & UCS_LITTLE_ENDIAN) ? UTF_REVERSE_ENDIAN : 0 );
#else /* !__BIG_ENDIAN__ */
                    (flags & UCS_LITTLE_ENDIAN) ? 0 : UTF_REVERSE_ENDIAN );
#endif /* !__BIG_ENDIAN__ */

    return utf8strlen;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void uuid_unswap(uuid_t uu)
{
    uint8_t tmp;

    tmp = uu[0];  uu[0] = uu[3];  uu[3] = tmp;
    tmp = uu[2];  uu[2] = uu[1];  uu[1] = tmp;
    tmp = uu[4];  uu[4] = uu[5];  uu[5] = tmp;
    tmp = uu[6];  uu[6] = uu[7];  uu[7] = tmp;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::init(OSDictionary * properties)
{
    //
    // Initialize this object's minimal state.
    //
#ifdef L4IOKIT
    //IOLog("%s::%s called.\n", "IOGUIDPartitionscheme",  __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    // Ask our superclass' opinion.

    if ( super::init(properties) == false )  return false;

    // Initialize our state.

    _partitions = 0;

#ifdef L4IOKIT
    //IOLog("%s::%s returning true.\n", "IOGUIDPartitionScheme", __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOGUIDPartitionScheme::free()
{
    //
    // Free all of this object's outstanding resources.
    //

    if ( _partitions )  _partitions->release();

    super::free();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOService * IOGUIDPartitionScheme::probe(IOService * provider, SInt32 * score)
{
    //
    // Determine whether the provider media contains an GUID partition map.
    //

    // State our assumptions.

    assert(OSDynamicCast(IOMedia, provider));

    // Ask our superclass' opinion.

#ifdef L4IOKIT
    //IOLog("%s::%s calling super::probe.\n", 
//	"IOGUIDPartitionScheme", __FUNCTION__);
     //L4_KDB_Enter("");
#endif
    if ( super::probe(provider, score) == 0 )  return 0;

    // Scan the provider media for an GUID partition map.

    _partitions = scan(score);

#ifdef L4IOKIT
    //IOLog("%s::%s _partitions = %d\n", 
//	"IOGUIDPartitionScheme", __FUNCTION__, _partitions);
    //L4_KDB_Enter("");
#endif
    return ( _partitions ) ? this : 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::start(IOService * provider)
{
    //
    // Publish the new media objects which represent our partitions.
    //

    IOMedia *    partition;
    OSIterator * partitionIterator;

    // State our assumptions.

    assert(_partitions);

    // Ask our superclass' opinion.

#ifdef L4IOKIT
    //IOLog("%s::%s calling super::start.\n", 
//	"IOGUIDPartitionScheme", __FUNCTION__);
    //L4_KDB_Enter("");
#endif

    if ( super::start(provider) == false )  return false;

    // Attach and register the new media objects representing our partitions.

    partitionIterator = OSCollectionIterator::withCollection(_partitions);
    if ( partitionIterator == 0 )  return false;

    while ( (partition = (IOMedia *) partitionIterator->getNextObject()) )
    {
        if ( partition->attach(this) )
        {
            attachMediaObjectToDeviceTree(partition);

            partition->registerService();
        }
    }

    partitionIterator->release();

#ifdef L4IOKIT
    //IOLog("%s::%s returning true.\n", "IOGUIDPartitionScheme", __FUNCTION__);
    //L4_KDB_Enter("");
#endif
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOGUIDPartitionScheme::stop(IOService * provider)
{
    //
    // Clean up after the media objects we published before terminating.
    //

    IOMedia *    partition;
    OSIterator * partitionIterator;

    // State our assumptions.

    assert(_partitions);

    // Detach the media objects we previously attached to the device tree.

    partitionIterator = OSCollectionIterator::withCollection(_partitions);

    if ( partitionIterator )
    {
        while ( (partition = (IOMedia *) partitionIterator->getNextObject()) )
        {
            detachMediaObjectFromDeviceTree(partition);
        }

        partitionIterator->release();
    }

    super::stop(provider);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSSet * IOGUIDPartitionScheme::scan(SInt32 * score)
{
    //
    // Scan the provider media for a GUID partition map.    Returns the set
    // of media objects representing each of the partitions (the retain for
    // the set is passed to the caller), or null should no partition map be
    // found.  The default probe score can be adjusted up or down, based on
    // the confidence of the scan.
    //

    IOBufferMemoryDescriptor * buffer         = 0;
    UInt32                     bufferSize     = 0;
    UInt32                     fdiskID        = 0;
    disk_blk0 *                fdiskMap       = 0;
    UInt64                     gptBlock       = 0;
    UInt32                     gptCheck       = 0;
    UInt32                     gptCount       = 0;
    UInt32                     gptID          = 0;
    gpt_ent *                  gptMap         = 0;
    UInt32                     gptSize        = 0;
    UInt32                     headerCheck    = 0;
    gpt_hdr *                  headerMap      = 0;
    UInt32                     headerSize     = 0;
    IOMedia *                  media          = getProvider();
    UInt64                     mediaBlockSize = media->getPreferredBlockSize();
    bool                       mediaIsOpen    = false;
    OSSet *                    partitions     = 0;
    IOReturn                   status         = kIOReturnError;

    // Determine whether this media is formatted.

#ifdef L4IOKIT
    //IOLog("IOGUIDPartitionScheme::scan scanning.\n");
    //L4_KDB_Enter("XXX");
#endif
#ifdef L4IOKIT
    if ( media->isFormatted() == false )  {
	IOLog("IOGUIDPartitionScheme::scan media is not formatted.\n");
	goto scanErr;
    }
#else
    if ( media->isFormatted() == false )  goto scanErr;
#endif

    // Determine whether this media has an appropriate block size.

#ifdef L4IOKIT
    if ( (mediaBlockSize % sizeof(disk_blk0)) )  {
	IOLog("IOGUIDPartitionScheme::scan mediaBlockSize BADNESS\n");
	goto scanErr;
    }
#else
    if ( (mediaBlockSize % sizeof(disk_blk0)) )  goto scanErr;
#endif

    // Allocate a buffer large enough to hold one map, rounded to a media block.
    bufferSize = IORound(sizeof(disk_blk0), mediaBlockSize);
    buffer     = IOBufferMemoryDescriptor::withCapacity(
                                           /* capacity      */ bufferSize,
                                           /* withDirection */ kIODirectionIn );
    if ( buffer == 0 )  goto scanErr;

    // Allocate a set to hold the set of media objects representing partitions.

    partitions = OSSet::withCapacity(8);
    if ( partitions == 0 )  goto scanErr;

    // Open the media with read access.

#ifdef L4IOKIT
    //IOLog("IOGUIDPartitionScheme::scan opening media.\n");
    //L4_KDB_Enter("");
#endif
    mediaIsOpen = media->open(this, 0, kIOStorageAccessReader);
#ifdef L4IOKIT
    if ( mediaIsOpen == false )  {
	IOLog("IOGUIDPartitionScheme::scan mediaIsOpen is FALSE!\n");
	goto scanErr;
    }
#else
    if ( mediaIsOpen == false )  goto scanErr;
#endif

    // Read the protective map into our buffer.

#ifdef L4IOKIT
    //IOLog("IOGUIDPartitionScheme::scan trying to read.\n");
#endif
    status = media->read(this, 0, buffer);
#ifdef L4IOKIT
    //IOLog("IOGUIDPartitionScheme::scan DONE, got status %lu\n", status);
#endif
    if ( status != kIOReturnSuccess )  goto scanErr;

    fdiskMap = (disk_blk0 *) buffer->getBytesNoCopy();

    // Determine whether the protective map signature is present.

    if ( OSSwapLittleToHostInt16(fdiskMap->signature) != DISK_SIGNATURE )
    {
         goto scanErr;
    }

    // Scan for valid partition entries in the protective map.

    for ( unsigned index = 0; index < DISK_NPART; index++ )
    {
        if ( fdiskMap->parts[index].systid )
        {
            if ( fdiskMap->parts[index].systid == 0xEE )
            {
                if ( fdiskID )  goto scanErr;

                fdiskID = index + 1;
            }
        }
    }

    if ( fdiskID == 0 )  goto scanErr;

    // Read the partition header into our buffer.

#ifdef L4IOKIT
    //IOLog("IOGUIDPartitionScheme::%s trying to read in partition header.\n", 
//	__FUNCTION__);
#endif
    status = media->read(this, mediaBlockSize, buffer);
    if ( status != kIOReturnSuccess )  goto scanErr;

    headerMap = (gpt_hdr *) buffer->getBytesNoCopy();

    // Determine whether the partition header signature is present.

    if ( memcmp(headerMap->hdr_sig, GPT_HDR_SIG, strlen(GPT_HDR_SIG)) )
    {
        goto scanErr;
    }

    // Determine whether the partition header size is valid.

    headerCheck = OSSwapLittleToHostInt32(headerMap->hdr_crc_self);
    headerSize  = OSSwapLittleToHostInt32(headerMap->hdr_size);

    if ( headerSize < offsetof(gpt_hdr, padding) )
    {
        goto scanErr;
    }

    // Determine whether the partition header checksum is valid.

    headerMap->hdr_crc_self = 0;

    if ( crc32(0, headerMap, headerSize) != headerCheck )
    {
        goto scanErr;
    }

    // Determine whether the partition entry size is valid.

    gptBlock = OSSwapLittleToHostInt64(headerMap->hdr_lba_table);
    gptCheck = OSSwapLittleToHostInt32(headerMap->hdr_crc_table);
    gptCount = OSSwapLittleToHostInt32(headerMap->hdr_entries);
    gptSize  = OSSwapLittleToHostInt32(headerMap->hdr_entsz);

    if ( gptSize < sizeof(gpt_ent) )
    {
        goto scanErr;
    }

    // Allocate a buffer large enough to hold one map, rounded to a media block.

    buffer->release();

    bufferSize = IORound(gptCount * gptSize, mediaBlockSize);
    buffer     = IOBufferMemoryDescriptor::withCapacity(
                                           /* capacity      */ bufferSize,
                                           /* withDirection */ kIODirectionIn );
    if ( buffer == 0 )  goto scanErr;

    // Read the partition header into our buffer.

#ifdef L4IOKIT
    IOLog("IOGUIDPartitionScheme::%s trying to read in partition header.\n",
	__FUNCTION__);
#endif
    status = media->read(this, gptBlock * mediaBlockSize, buffer);
    if ( status != kIOReturnSuccess )  goto scanErr;

    gptMap = (gpt_ent *) buffer->getBytesNoCopy();

    // Determine whether the partition entry checksum is valid.

    if ( crc32(0, gptMap, gptCount * gptSize) != gptCheck )
    {
        goto scanErr;
    }

    // Scan for valid partition entries in the partition map.

    for ( gptID = 1; gptID <= gptCount; gptID++ )
    {
        gptMap = (gpt_ent *) ( ((UInt8 *) buffer->getBytesNoCopy()) +
                               (gptID * gptSize) - gptSize );

        uuid_unswap( gptMap->ent_type );
        uuid_unswap( gptMap->ent_uuid );
 
        if ( isPartitionUsed( gptMap ) )
        {
            // Determine whether the partition is corrupt (fatal).

            if ( isPartitionCorrupt( gptMap, gptID ) )
            {
                goto scanErr;
            }

            // Determine whether the partition is invalid (skipped).

            if ( isPartitionInvalid( gptMap, gptID ) )
            {
                continue;
            }

            // Create a media object to represent this partition.

            IOMedia * newMedia = instantiateMediaObject( gptMap, gptID );

            if ( newMedia )
            {
                partitions->setObject(newMedia);
                newMedia->release();
            }
        }
    }

    // Release our resources.

    media->close(this);
    buffer->release();

    return partitions;

scanErr:

    // Release our resources.

    if ( mediaIsOpen )  media->close(this);
    if ( partitions )  partitions->release();
    if ( buffer )  buffer->release();

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::isPartitionUsed(gpt_ent * partition)
{
    //
    // Ask whether the given partition is used.
    //

    return uuid_is_null(partition->ent_type) ? false : true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::isPartitionCorrupt( gpt_ent * /* partition   */ ,
                                                UInt32    /* partitionID */ )
{
    //
    // Ask whether the given partition appears to be corrupt. A partition that
    // is corrupt will cause the failure of the GUID partition map recognition
    // altogether.
    //

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::isPartitionInvalid( gpt_ent * partition,
                                                UInt32    partitionID )
{
    //
    // Ask whether the given partition appears to be invalid.  A partition that
    // is invalid will cause it to be skipped in the scan, but will not cause a
    // failure of the GUID partition map recognition.
    //

    IOMedia * media          = getProvider();
    UInt64    mediaBlockSize = media->getPreferredBlockSize();
    UInt64    partitionBase  = 0;
    UInt64    partitionSize  = 0;

    // Compute the relative byte position and size of the new partition.

    partitionBase  = OSSwapLittleToHostInt64(partition->ent_lba_start);
    partitionSize  = OSSwapLittleToHostInt64(partition->ent_lba_end);
    partitionBase *= mediaBlockSize;
    partitionSize *= mediaBlockSize;

    // Determine whether the partition is a placeholder.

    if ( partitionBase == partitionSize )  return true;

    // Compute the relative byte position and size of the new partition.

    partitionSize -= partitionBase - mediaBlockSize;

    // Determine whether the new partition leaves the confines of the container.

    if ( partitionBase + partitionSize > media->getSize() )  return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOMedia * IOGUIDPartitionScheme::instantiateMediaObject( gpt_ent * partition,
                                                         UInt32    partitionID )
{
    //
    // Instantiate a new media object to represent the given partition.
    //

    IOMedia * media          = getProvider();
    UInt64    mediaBlockSize = media->getPreferredBlockSize();
    UInt64    partitionBase  = 0;
    char      partitionHint[36 + 1];
    char      partitionName[36 * 3 + 1];
    UInt64    partitionSize  = 0;

    ucs2_to_utf8( partition->ent_name,
                  sizeof(partition->ent_name),
                  partitionName,
                  sizeof(partitionName),
                  UCS_LITTLE_ENDIAN );

    uuid_unparse( partition->ent_type,
                  partitionHint );

    // Compute the relative byte position and size of the new partition.

    partitionBase  = OSSwapLittleToHostInt64(partition->ent_lba_start);
    partitionSize  = OSSwapLittleToHostInt64(partition->ent_lba_end);
    partitionBase *= mediaBlockSize;
    partitionSize *= mediaBlockSize;
    partitionSize -= partitionBase - mediaBlockSize;

    // Create the new media object.

    IOMedia * newMedia = instantiateDesiredMediaObject(
                                   /* partition   */ partition,
                                   /* partitionID */ partitionID );

    if ( newMedia )
    {
         if ( newMedia->init(
                /* base               */ partitionBase,
                /* size               */ partitionSize,
                /* preferredBlockSize */ mediaBlockSize,
                /* attributes         */ media->getAttributes(),
                /* isWhole            */ false,
                /* isWritable         */ media->isWritable(),
                /* contentHint        */ partitionHint ) )
        {
            // Set a name for this partition.

            char name[24];
            sprintf(name, "Untitled %ld", partitionID);
            newMedia->setName(partitionName[0] ? partitionName : name);

            // Set a location value (the partition number) for this partition.

            char location[12];
            sprintf(location, "%ld", partitionID);
            newMedia->setLocation(location);

            // Set the "Partition ID" key for this partition.

            newMedia->setProperty(kIOMediaPartitionIDKey, partitionID, 32);

            // Set the "Universal Unique ID" key for this partition.

            char uuid[48];
            uuid_unparse(partition->ent_uuid, uuid);
            newMedia->setProperty(kIOMediaUUIDKey, uuid);
        }
        else
        {
            newMedia->release();
            newMedia = 0;
        }
    }

    return newMedia;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

IOMedia * IOGUIDPartitionScheme::instantiateDesiredMediaObject(
                                                         gpt_ent * partition,
                                                         UInt32    partitionID )
{
    //
    // Allocate a new media object (called from instantiateMediaObject).
    //

    return new IOMedia;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool IOGUIDPartitionScheme::attachMediaObjectToDeviceTree( IOMedia * media )
{
    //
    // Attach the given media object to the device tree plane.
    //

    IORegistryEntry * parent = this;

    while ( (parent = parent->getParentEntry(gIOServicePlane)) )
    {
        if ( parent->inPlane(gIODTPlane) )
        {
            char         location[ 32 ];
            const char * locationOfParent = parent->getLocation(gIODTPlane);
            const char * nameOfParent     = parent->getName(gIODTPlane);

            if ( locationOfParent == 0 )  break;

            if ( OSDynamicCast(IOMedia, parent) == 0 )  break;

            parent = parent->getParentEntry(gIODTPlane);

            if ( parent == 0 )  break;

            if ( media->attachToParent(parent, gIODTPlane) == false )  break;

            strcpy(location, locationOfParent);
            if ( strchr(location, ':') )  *(strchr(location, ':') + 1) = 0;
            strcat(location, media->getLocation());
            media->setLocation(location, gIODTPlane);
            media->setName(nameOfParent, gIODTPlane);

            return true;
        }
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void IOGUIDPartitionScheme::detachMediaObjectFromDeviceTree( IOMedia * media )
{
    //
    // Detach the given media object from the device tree plane.
    //

    IORegistryEntry * parent;

    if ( (parent = media->getParentEntry(gIODTPlane)) )
    {
        media->detachFromParent(parent, gIODTPlane);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 0);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 1);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 3);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 4);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 5);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 6);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 7);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 8);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 9);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 10);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 11);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 12);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 13);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 14);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

OSMetaClassDefineReservedUnused(IOGUIDPartitionScheme, 15);

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

/*
 * This header contains the IOGUIDPartitionScheme class definition.
 */

#ifndef _IOGUIDPARTITIONSCHEME_H
#define _IOGUIDPARTITIONSCHEME_H

#include <IOKit/IOTypes.h>

/*
 * kIOGUIDPartitionSchemeClass is the name of the IOGUIDPartitionScheme class.
 */

#define kIOGUIDPartitionSchemeClass "IOGUIDPartitionScheme"

/*
 * GUID Partition Map Definitions
 */

#include <uuid/uuid.h>

//#pragma pack(8)        /* (enable 64-bit struct packing for gpt_hdr, gpt_ent) */

/* Partition map. */

struct gpt_hdr
{
    uint8_t  hdr_sig[8];
    uint32_t hdr_revision;
    uint32_t hdr_size;
    uint32_t hdr_crc_self;
    uint32_t __reserved;
    uint64_t hdr_lba_self;
    uint64_t hdr_lba_alt;
    uint64_t hdr_lba_start;
    uint64_t hdr_lba_end;
    uuid_t   hdr_uuid;
    uint64_t hdr_lba_table;
    uint32_t hdr_entries;
    uint32_t hdr_entsz;
    uint32_t hdr_crc_table;
    uint32_t padding;
} __attribute__((aligned(8)));

/* Partition map entry. */

struct gpt_ent
{
    uuid_t   ent_type;
    uuid_t   ent_uuid;
    uint64_t ent_lba_start;
    uint64_t ent_lba_end;
    uint64_t ent_attr;
    uint16_t ent_name[36];
} __attribute__((aligned(8)));

/* Partition map signature (hdr_sig). */

#define GPT_HDR_SIG "EFI PART"

/* Partition map version (hdr_revision). */

#define GPT_HDR_REVISION 0x00010000

/* Partition map entry flags (ent_attr). */

#define GPT_ENT_ATTR_PLATFORM 0x00000001

//#pragma options align=reset              /* (reset to default struct packing) */

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/storage/IOPartitionScheme.h>

/*
 * Class
 */

class IOGUIDPartitionScheme : public IOPartitionScheme
{
    OSDeclareDefaultStructors(IOGUIDPartitionScheme);

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    OSSet * _partitions;    /* (set of media objects representing partitions) */

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free(void);

    /*
     * Scan the provider media for a GUID partition map.    Returns the set
     * of media objects representing each of the partitions (the retain for
     * the set is passed to the caller), or null should no partition map be
     * found.  The default probe score can be adjusted up or down, based on
     * the confidence of the scan.
     */

    virtual OSSet * scan(SInt32 * score);

    /*
     * Ask whether the given partition is used.
     */

    virtual bool isPartitionUsed(gpt_ent * partition);

    /*
     * Ask whether the given partition appears to be corrupt. A partition that
     * is corrupt will cause the failure of the GUID partition map recognition
     * altogether.
     */

    virtual bool isPartitionCorrupt( gpt_ent * partition,
                                     UInt32    partitionID );

    /*
     * Ask whether the given partition appears to be invalid.  A partition that
     * is invalid will cause it to be skipped in the scan, but will not cause a
     * failure of the GUID partition map recognition.
     */

    virtual bool isPartitionInvalid( gpt_ent * partition,
                                     UInt32    partitionID );

    /*
     * Instantiate a new media object to represent the given partition.
     */

    virtual IOMedia * instantiateMediaObject( gpt_ent * partition,
                                              UInt32    partitionID );

    /*
     * Allocate a new media object (called from instantiateMediaObject).
     */

    virtual IOMedia * instantiateDesiredMediaObject( gpt_ent * partition,
                                                     UInt32    partitionID );

    /*
     * Attach the given media object to the device tree plane.
     */

    virtual bool attachMediaObjectToDeviceTree(IOMedia * media);

    /*
     * Detach the given media object from the device tree plane.
     */

    virtual void detachMediaObjectFromDeviceTree(IOMedia * media);

public:

    /*
     * Initialize this object's minimal state.
     */

    virtual bool init(OSDictionary * properties = 0);

    /*
     * Determine whether the provider media contains a GUID partition map.
     */

    virtual IOService * probe(IOService * provider, SInt32 * score);

    /*
     * Publish the new media objects which represent our partitions.
     */

    virtual bool start(IOService * provider);

    /*
     * Clean up after the media objects we published before terminating.
     */

    virtual void stop(IOService * provider);

    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  0);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  1);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  2);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  3);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  4);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  5);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  6);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  7);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  8);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme,  9);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 10);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 11);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 12);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 13);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 14);
    OSMetaClassDeclareReservedUnused(IOGUIDPartitionScheme, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOGUIDPARTITIONSCHEME_H */

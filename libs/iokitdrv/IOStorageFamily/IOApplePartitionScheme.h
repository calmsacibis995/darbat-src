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
 * This header contains the IOApplePartitionScheme class definition.
 */

#ifndef _IOAPPLEPARTITIONSCHEME_H
#define _IOAPPLEPARTITIONSCHEME_H

#include <IOKit/IOTypes.h>

/*
 * kIOApplePartitionSchemeClass is the name of the IOApplePartitionScheme class.
 */

#define kIOApplePartitionSchemeClass "IOApplePartitionScheme"

/*
 * Apple Partition Map Definitions
 */

//#pragma pack(2)     /* (enable 16-bit struct packing for dpme, DDMap, Block0) */

/* Structure constants. */

#define DPISTRLEN 32

/* Partition map entry, as found in blocks 1 to dpme_map_entries of the disk. */

typedef struct dpme
{
    UInt16  dpme_signature;       /* (unique value for partition entry, 'PM') */
    UInt16  dpme_reserved_1;      /* (reserved for future use)                */
    UInt32  dpme_map_entries;     /* (number of partition entries)            */
    UInt32  dpme_pblock_start;    /* (physical block start of partition)      */
    UInt32  dpme_pblocks;         /* (physical block count of partition)      */
    char    dpme_name[DPISTRLEN]; /* (name of partition)                      */
    char    dpme_type[DPISTRLEN]; /* (type of partition, eg. Apple_HFS)       */
    UInt32  dpme_lblock_start;    /* (logical block start of partition)       */
    UInt32  dpme_lblocks;         /* (logical block count of partition)       */
    UInt32  dpme_flags;           /* (partition flags, see defines below)     */
    UInt32  dpme_boot_block;      /* (logical block start of boot code)       */
    UInt32  dpme_boot_bytes;      /* (byte count of boot code)                */
    UInt8 * dpme_load_addr;       /* (load address in memory of boot code)    */
    UInt8 * dpme_load_addr_2;     /* (reserved for future use)                */
    UInt8 * dpme_goto_addr;       /* (jump address in memory of boot code)    */
    UInt8 * dpme_goto_addr_2;     /* (reserved for future use)                */
    UInt32  dpme_checksum;        /* (checksum of boot code)                  */
    UInt8   dpme_process_id[16];  /* (processor type)                         */
    UInt32  dpme_reserved_2[32];  /* (reserved for future use)                */
    UInt32  dpme_reserved_3[62];  /* (reserved for future use)                */
} DPME __attribute__((aligned(2)));

/* Driver descriptor map entry. */

typedef struct DDMap
{
    UInt32  ddBlock;              /* (driver's block start, sbBlkSize-blocks) */
    UInt16  ddSize;               /* (driver's block count, 512-blocks)       */
    UInt16  ddType;               /* (driver's system type)                   */
} DDMap __attribute__((aligned(2)));

/* Driver descriptor map, as found in block zero of the disk. */

typedef struct Block0
{
    UInt16  sbSig;                     /* (unique value for block zero, 'ER') */
    UInt16  sbBlkSize;                 /* (block size for this device)        */
    UInt32  sbBlkCount;                /* (block count for this device)       */
    UInt16  sbDevType;                 /* (device type)                       */
    UInt16  sbDevId;                   /* (device id)                         */
    UInt32  sbDrvrData;                /* (driver data)                       */
    UInt16  sbDrvrCount;               /* (driver descriptor count)           */
    DDMap   sbDrvrMap[8];              /* (driver descriptor table)           */
    UInt8   sbReserved[430];           /* (reserved for future use)           */
} Block0 __attribute__((aligned(2)));

/* Partition map signature (sbSig). */

#define BLOCK0_SIGNATURE 0x4552

/* Partition map entry signature (dpme_signature). */

#define DPME_SIGNATURE 0x504D

/* Partition map entry flags (dpme_flags). */

#define DPME_FLAGS_VALID          0x00000001                   /* (bit 0)     */
#define DPME_FLAGS_ALLOCATED      0x00000002                   /* (bit 1)     */
#define DPME_FLAGS_IN_USE         0x00000004                   /* (bit 2)     */
#define DPME_FLAGS_BOOTABLE       0x00000008                   /* (bit 3)     */
#define DPME_FLAGS_READABLE       0x00000010                   /* (bit 4)     */
#define DPME_FLAGS_WRITABLE       0x00000020                   /* (bit 5)     */
#define DPME_FLAGS_OS_PIC_CODE    0x00000040                   /* (bit 6)     */
#define DPME_FLAGS_OS_SPECIFIC_2  0x00000080                   /* (bit 7)     */
#define DPME_FLAGS_OS_SPECIFIC_1  0x00000100                   /* (bit 8)     */
#define DPME_FLAGS_RESERVED_2     0xFFFFFE00                   /* (bit 9..31) */

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

class IOApplePartitionScheme : public IOPartitionScheme
{
    OSDeclareDefaultStructors(IOApplePartitionScheme);

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    OSSet * _partitions;    /* (set of media objects representing partitions) */

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free(void);

    /*
     * Scan the provider media for an Apple partition map.  Returns the set
     * of media objects representing each of the partitions (the retain for
     * the set is passed to the caller), or null should no partition map be
     * found.  The default probe score can be adjusted up or down, based on
     * the confidence of the scan.
     */

    virtual OSSet * scan(SInt32 * score);

    /*
     * Ask whether the given partition appears to be corrupt.  A partition that
     * is corrupt will cause the failure of the Apple partition map recognition
     * altogether.
     */

    virtual bool isPartitionCorrupt( dpme * partition,
                                     UInt32 partitionID,
                                     UInt32 partitionBlockSize );

    /*
     * Ask whether the given partition appears to be invalid.  A partition that
     * is invalid will cause it to be skipped in the scan, but will not cause a
     * failure of the Apple partition map recognition.
     */

    virtual bool isPartitionInvalid( dpme * partition,
                                     UInt32 partitionID,
                                     UInt32 partitionBlockSize );

    /*
     * Instantiate a new media object to represent the given partition.
     */

    virtual IOMedia * instantiateMediaObject( dpme * partition,
                                              UInt32 partitionID,
                                              UInt32 partitionBlockSize );

    /*
     * Allocate a new media object (called from instantiateMediaObject).
     */

    virtual IOMedia * instantiateDesiredMediaObject(
                                                    dpme * partition,
                                                    UInt32 partitionID,
                                                    UInt32 partitionBlockSize );

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
     * Determine whether the provider media contains an Apple partition map.
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

    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  0);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  1);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  2);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  3);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  4);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  5);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  6);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  7);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  8);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme,  9);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 10);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 11);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 12);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 13);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 14);
    OSMetaClassDeclareReservedUnused(IOApplePartitionScheme, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOAPPLEPARTITIONSCHEME_H */

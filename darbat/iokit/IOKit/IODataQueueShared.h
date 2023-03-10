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

#ifndef _IOKIT_IODATAQUEUESHARED_H
#define _IOKIT_IODATAQUEUESHARED_H

#include <libkern/OSTypes.h>

/*!
 * @typedef IODataQueueEntry
 * @abstract Represents an entry within the data queue
 * @discussion This is a variable sized struct.  The data field simply represents the start of the data region.  The size of the data region is stored in the size field.  The whole size of the specific entry is the size of a UInt32 plus the size of the data region.  
 * @field size The size of the following data region.
 * @field data Represents the beginning of the data region.  The address of the data field is a pointer to the start of the data region.
 */
typedef struct _IODataQueueEntry{
    UInt32  size;
    void *  data;
} IODataQueueEntry;

/*!
 * @typedef IODataQueueMemory
 * @abstract A struct mapping to the header region of a data queue.
 * @discussion This struct is variable sized.  The struct represents the data queue header information plus a pointer to the actual data queue itself.  The size of the struct is the combined size of the header fields (3 * sizeof(UInt32)) plus the actual size of the queue region.  This size is stored in the queueSize field.
 * @field queueSize The size of the queue region pointed to by the queue field.
 * @field head The location of the queue head.  This field is represented as a byte offset from the beginning of the queue memory region.
 * @field tail The location of the queue tail.  This field is represented as a byte offset from the beginning of the queue memory region.
 * @field queue Represents the beginning of the queue memory region.  The size of the region pointed to by queue is stored in the queueSize field.
 */
typedef struct _IODataQueueMemory {
    UInt32            queueSize;
    volatile UInt32   head;
    volatile UInt32   tail;
    IODataQueueEntry  queue[1];
} IODataQueueMemory;

/*!
 * @defined DATA_QUEUE_ENTRY_HEADER_SIZE Represents the size of the data queue entry header independent of the actual size of the data in the entry.  This is the overhead of each entry in the queue.  The total size of an entry is equal to this value plus the size stored in the entry's size field (in IODataQueueEntry).
 */
#define DATA_QUEUE_ENTRY_HEADER_SIZE (sizeof(IODataQueueEntry) - sizeof(void *))

/*!
 * @defined DATA_QUEUE_MEMORY_HEADER_SIZE Represents the size of the data queue memory header independent of the actual size of the queue data itself.  The total size of the queue memory is equal to this value plus the size of the queue data region which is stored in the queueSize field of IODataQueueMeory.
 */
#define DATA_QUEUE_MEMORY_HEADER_SIZE (sizeof(IODataQueueMemory) - sizeof(IODataQueueEntry))

#endif /* _IOKIT_IODATAQUEUESHARED_H */


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
#ifndef _IOMEMORYCURSOR_H
#define _IOMEMORYCURSOR_H

#include <libkern/c++/OSObject.h>
#include <IOKit/IOTypes.h>

class IOMemoryDescriptor;

/**************************** class IOMemoryCursor ***************************/

/*!
    @class IOMemoryCursor
    @abstract A mechanism to convert memory references to physical addresses.
    @discussion The IOMemoryCursor declares the super class that all
specific memory cursors must inherit from, but a memory cursor can be created without a specific format subclass by just providing a segment function to the initializers.  This class does the difficult stuff of dividing a memory descriptor into a physical scatter/gather list appropriate for the target hardware.
<br><br>
    A driver is expected to create a memory cursor and configure it to the limitations of its DMA hardware; for instance the memory cursor used by the FireWire SBP-2 protocol has a maximum physical segment size of 2^16 - 1 but the actual transfer size is unlimited.  Thus it would create a cursor with a maxSegmentSize of 65535 and a maxTransfer size of UINT_MAX.   It would also provide a SegmentFunction that can output a pagelist entry.
<br><br>
Below is the simplest example of a SegmentFunction:<br>
void IONaturalMemoryCursor::outputSegment(PhysicalSegment segment,<br>
					  void *	  outSegments,<br>
					  UInt32	  outSegmentIndex)<br>
{<br>
    ((PhysicalSegment *) outSegments)[outSegmentIndex] = segment;<br>
}

*/
class IOMemoryCursor : public OSObject
{
    OSDeclareDefaultStructors(IOMemoryCursor)

public:
/*!
    @typedef PhysicalSegment
    @discussion A physical address/length pair.
*/
    struct PhysicalSegment
    {
	IOPhysicalAddress location;
	IOPhysicalLength  length;
    };

/*! @defined IOPhysicalSegment
    @discussion Backward compatibility define for the old non-class scoped type definition.  See IOMemoryCursor::PhysicalSegment 
*/
#define IOPhysicalSegment IOMemoryCursor::PhysicalSegment

/*!
    @typedef SegmentFunction
    @discussion Pointer to a C function that outputs a single physical segment to an element in the array as defined by the segments and segmentIndex parameters.
    @param segment The physical address and length that is next to be output.
    @param segments Base of the output vector of DMA address length pairs.
    @param segmentIndex Index to output 'segment' in the 'segments' array.
*/
    typedef void (*SegmentFunction)(PhysicalSegment segment,
				    void *	    segments,
				    UInt32	    segmentIndex);

/*! @defined OutputSegmentFunc
    @discussion Backward compatibility define for the old non-class scoped type definition.  See IOMemoryCursor::SegmentFunction */
#define OutputSegmentFunc IOMemoryCursor::SegmentFunction

protected:
/*! @var outSeg The action method called when an event has been delivered */
    SegmentFunction outSeg;

/*! @var maxSegmentSize Maximum size of one segment in a scatter/gather list */
    IOPhysicalLength  maxSegmentSize;

/*! @var maxTransferSize
    Maximum size of a transfer that this memory cursor is allowed to generate */
    IOPhysicalLength  maxTransferSize;

/*! @var alignMask
    Currently unused.  Reserved for automated aligment restriction code. */
    IOPhysicalLength  alignMask;

public:
/*! @function withSpecification
    @abstract Creates and initializes an IOMemoryCursor in one operation.
    @discussion Factory function to create and initialize an IOMemoryCursor in one operation.  For more information, see IOMemoryCursor::initWithSpecification.
    @param outSegFunc SegmentFunction to call to output one physical segment.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns a new memory cursor if successfully created and initialized, 0 otherwise.
*/
    static IOMemoryCursor *
	withSpecification(SegmentFunction  outSegFunc,
			  IOPhysicalLength maxSegmentSize = 0,
			  IOPhysicalLength maxTransferSize = 0,
			  IOPhysicalLength alignment = 1);

/*! @function initWithSpecification
    @abstract Primary initializer for the IOMemoryCursor class.
    @param outSegFunc SegmentFunction to call to output one physical segment.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns true if the inherited classes and this instance initialize
successfully.
*/
    virtual bool initWithSpecification(SegmentFunction	outSegFunc,
				       IOPhysicalLength maxSegmentSize = 0,
				       IOPhysicalLength maxTransferSize = 0,
				       IOPhysicalLength alignment = 1);

/*! @function genPhysicalSegments
    @abstract Generates a physical scatter/gather list given a memory descriptor.
    @discussion Generates a list of physical segments from the given memory descriptor, relative to the current position of the descriptor.
    @param descriptor IOMemoryDescriptor that describes the data associated with an I/O request. 
    @param fromPosition Starting location of the I/O within a memory descriptor. 
    @param segments Void pointer to base of output physical scatter/gather list.  Always passed directly onto the SegmentFunction without interpretation by the cursor. 
    @param maxSegments Maximum number of segments that can be written to segments array.
    @param maxTransferSize Maximum transfer size is limited to that many bytes, otherwise it defaults to the maximum transfer size specified when the memory cursor was initialized.
    @param transferSize Pointer to an IOByteCount variable that can contain the total size of the transfer being described.  Defaults to 0 indicating that no transfer size need be returned. 
    @result If the descriptor is exhausted of memory, a zero is returned, otherwise the number of segments that were filled in is returned.
*/
    virtual UInt32 genPhysicalSegments(
				      IOMemoryDescriptor *descriptor,
				      IOByteCount	  fromPosition,
				      void *		  segments,
				      UInt32		  maxSegments,
				      UInt32		  maxTransferSize = 0,
				      IOByteCount	 *transferSize = 0);
};

/************************ class IONaturalMemoryCursor ************************/


/*!
    @class IONaturalMemoryCursor
    @abstract An IOMemoryCursor subclass that outputs a vector of PhysicalSegments in the natural byte orientation for the CPU.  
    @discussion The IONaturalMemoryCursor would be used when it is too difficult to safely describe a SegmentFunction that is more appropriate for your hardware.  This cursor just outputs an array of PhysicalSegments.
*/
class IONaturalMemoryCursor : public IOMemoryCursor
{
    OSDeclareDefaultStructors(IONaturalMemoryCursor)

public:
/*! @function outputSegment
    @abstract Outputs the given segment into the output segments array in natural byte order.
    @param segment The physical address and length that is next to be output.
    @param segments Base of the output vector of DMA address length pairs.
    @param segmentIndex Index to output 'segment' in the 'segments' array.
*/
    static void outputSegment(PhysicalSegment segment,
			      void *	      segments,
			      UInt32	      segmentIndex);

/*! @defined naturalOutputSegment
    @discussion Backward compatibility define for the old global function definition.  See IONaturalMemoryCursor::outputSegment.
*/
#define naturalOutputSegment IONaturalMemoryCursor::outputSegment

/*! @function withSpecification
    @abstract Creates and initializes an IONaturalMemoryCursor in one operation.
    @discussion Factory function to create and initialize an IONaturalMemoryCursor in one operation.  For more information, see IONaturalMemoryCursor::initWithSpecification.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns a new memory cursor if successfully created and initialized, 0 otherwise.
*/
    static IONaturalMemoryCursor * 
	withSpecification(IOPhysicalLength maxSegmentSize,
			  IOPhysicalLength maxTransferSize,
			  IOPhysicalLength alignment = 1);

/*! @function initWithSpecification
    @abstract Primary initializer for the IONaturalMemoryCursor class.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns true if the inherited classes and this instance initialize successfully.
*/
    virtual bool initWithSpecification(IOPhysicalLength	 maxSegmentSize,
				       IOPhysicalLength	 maxTransferSize,
				       IOPhysicalLength	 alignment = 1);


/*! @function getPhysicalSegments
    @abstract Generates a CPU natural physical scatter/gather list given a memory descriptor.
    @discussion Generates a list of physical segments from the given memory descriptor, relative to the current position of the descriptor.  Wraps IOMemoryCursor::genPhysicalSegments.
    @param descriptor IOMemoryDescriptor that describes the data associated with an I/O request. 
    @param fromPosition Starting location of the I/O within a memory descriptor. 
    @param segments Pointer to an array of IOMemoryCursor::PhysicalSegments for the output physical scatter/gather list.
    @param maxSegments Maximum number of segments that can be written to segments array.
    @param maxTransferSize Maximum transfer size is limited to that many bytes, otherwise it defaults to the maximum transfer size specified when the memory cursor was initialized.
    @param transferSize Pointer to an IOByteCount variable that can contain the total size of the transfer being described.  Defaults to 0 indicating that no transfer size need be returned. 
    @result If the descriptor is exhausted of memory, a zero is returned, otherwise the number of segments that were filled in is returned.
*/
    virtual UInt32 getPhysicalSegments(IOMemoryDescriptor *descriptor,
				       IOByteCount	   fromPosition,
				       PhysicalSegment	  *segments,
				       UInt32		   maxSegments,
				       UInt32		   maxTransferSize = 0,
				       IOByteCount	  *transferSize = 0)
    {
	return genPhysicalSegments(descriptor, fromPosition, segments,
				maxSegments, maxTransferSize, transferSize);
    }
};

/************************** class IOBigMemoryCursor **************************/

/*!
    @class IOBigMemoryCursor
    @abstract An IOMemoryCursor subclass that outputs a vector of PhysicalSegments in the big endian byte order.  
    @discussion The IOBigMemoryCursor would be used when the DMA hardware requires a big endian address and length pair.  This cursor outputs an array of PhysicalSegments that are encoded in big-endian format.
*/
class IOBigMemoryCursor : public IOMemoryCursor
{
    OSDeclareDefaultStructors(IOBigMemoryCursor)

public:
/*! @function outputSegment
    @abstract Outputs the given segment into the output segments array in big endian byte order.
    @param segment The physical address and length that is next to be output.
    @param segments Base of the output vector of DMA address length pairs.
    @param segmentIndex Index to output 'segment' in the 'segments' array.
*/
    static void outputSegment(PhysicalSegment segment,
			      void *	      segments,
			      UInt32	      segmentIndex);

/*! @defined bigOutputSegment
    @discussion Backward compatibility define for the old global function definition.  See IOBigMemoryCursor::outputSegment 
*/
#define bigOutputSegment IOBigMemoryCursor::outputSegment

/*! @function withSpecification
    @abstract Creates and initializes an IOBigMemoryCursor in one operation.
    @discussion Factory function to create and initialize an IOBigMemoryCursor in one operation.  See also IOBigMemoryCursor::initWithSpecification.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns a new memory cursor if successfully created and initialized, 0 otherwise.
*/
    static IOBigMemoryCursor *
	withSpecification(IOPhysicalLength maxSegmentSize,
			  IOPhysicalLength maxTransferSize,
			  IOPhysicalLength alignment = 1);

/*! @function initWithSpecification
    @abstract Primary initializer for the IOBigMemoryCursor class.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns true if the inherited classes and this instance initialize
successfully.
*/
    virtual bool initWithSpecification(IOPhysicalLength	 maxSegmentSize,
				       IOPhysicalLength	 maxTransferSize,
				       IOPhysicalLength	 alignment = 1);


/*! @function getPhysicalSegments
    @abstract Generates a big endian physical scatter/gather list given a memory descriptor.
    @discussion Generates a list of physical segments from the given memory descriptor, relative to the current position of the descriptor.  Wraps IOMemoryCursor::genPhysicalSegments.
    @param descriptor IOMemoryDescriptor that describes the data associated with an I/O request. 
    @param fromPosition Starting location of the I/O within a memory descriptor. 
    @param segments Pointer to an array of IOMemoryCursor::PhysicalSegments for the output physical scatter/gather list.
    @param maxSegments Maximum number of segments that can be written to segments array.
    @param maxTransferSize Maximum transfer size is limited to that many bytes, otherwise it defaults to the maximum transfer size specified when the memory cursor was initialized.
    @param transferSize Pointer to an IOByteCount variable that can contain the total size of the transfer being described.  Defaults to 0 indicating that no transfer size need be returned. 
    @result If the descriptor is exhausted of memory, a zero is returned, otherwise the number of segments that were filled in is returned.
*/
    virtual UInt32 getPhysicalSegments(IOMemoryDescriptor * descriptor,
				       IOByteCount	    fromPosition,
				       PhysicalSegment *    segments,
				       UInt32		    maxSegments,
				       UInt32		    maxTransferSize = 0,
				       IOByteCount	 *  transferSize = 0)
    {
	return genPhysicalSegments(descriptor, fromPosition, segments,
				maxSegments, maxTransferSize, transferSize);
    }
};

/************************* class IOLittleMemoryCursor ************************/

/*!
    @class IOLittleMemoryCursor
    @abstract An IOMemoryCursor subclass that outputs a vector of PhysicalSegments in the little endian byte order.  
    @discussion The IOLittleMemoryCursor would be used when the DMA hardware requires a little endian address and length pair.	This cursor outputs an array of PhysicalSegments that are encoded in little endian format.
*/
class IOLittleMemoryCursor : public IOMemoryCursor
{
    OSDeclareDefaultStructors(IOLittleMemoryCursor)

public:
/*! @function outputSegment
    @abstract Outputs the given segment into the output segments array in little endian byte order.
    @param segment The physical address and length that is next to be output.
    @param segments Base of the output vector of DMA address length pairs.
    @param segmentIndex Index to output 'segment' in the 'segments' array.
*/
    static void outputSegment(PhysicalSegment segment,
			      void *	      segments,
			      UInt32	      segmentIndex);

/*! @defined littleOutputSegment
    @discussion Backward compatibility define for the old global function definition.  See also IOLittleMemoryCursor::outputSegment. */
#define littleOutputSegment IOLittleMemoryCursor::outputSegment

/*! @function withSpecification
    @abstract Creates and initializes an IOLittleMemoryCursor in one operation.
    @discussion Factory function to create and initialize an IOLittleMemoryCursor in one operation.  See also IOLittleMemoryCursor::initWithSpecification.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns a new memory cursor if successfully created and initialized, 0 otherwise.
*/
    static IOLittleMemoryCursor *
	withSpecification(IOPhysicalLength maxSegmentSize,
			  IOPhysicalLength maxTransferSize,
			  IOPhysicalLength alignment = 1);

/*! @function initWithSpecification
    @abstract Primary initializer for the IOLittleMemoryCursor class.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns true if the inherited classes and this instance initialize successfully.
*/
    virtual bool initWithSpecification(IOPhysicalLength	 maxSegmentSize,
				       IOPhysicalLength	 maxTransferSize,
				       IOPhysicalLength	 alignment = 1);


/*! @function getPhysicalSegments
    @abstract Generates a little endian physical scatter/gather list given a memory descriptor.
    @discussion Generates a list of physical segments from the given memory descriptor, relative to the current position of the descriptor.  Wraps IOMemoryCursor::genPhysicalSegments.
    @param descriptor IOMemoryDescriptor that describes the data associated with an I/O request. 
    @param fromPosition Starting location of the I/O within a memory descriptor. 
    @param segments Pointer to an array of IOMemoryCursor::PhysicalSegments for the output physical scatter/gather list.
    @param maxSegments Maximum number of segments that can be written to segments array.
    @param maxTransferSize Maximum transfer size is limited to that many bytes, otherwise it defaults to the maximum transfer size specified when the memory cursor was initialized.
    @param transferSize Pointer to an IOByteCount variable that can contain the total size of the transfer being described.  Defaults to 0 indicating that no transfer size need be returned. 
    @result If the descriptor is exhausted of memory, a zero is returned, otherwise the number of segments that were filled in is returned.
*/
    virtual UInt32 getPhysicalSegments(IOMemoryDescriptor * descriptor,
				       IOByteCount	    fromPosition,
				       PhysicalSegment *    segments,
				       UInt32		    maxSegments,
				       UInt32		    maxTransferSize = 0,
				       IOByteCount	 *  transferSize = 0)
    {
	return genPhysicalSegments(descriptor, fromPosition, segments,
				maxSegments, maxTransferSize, transferSize);
    }
};

/************************* class IODBDMAMemoryCursor *************************/

#if defined(__ppc__)

struct IODBDMADescriptor;

/*!
    @class IODBDMAMemoryCursor
    @abstract An IOMemoryCursor subclass that outputs a vector of DBDMA descriptors where the address and length are filled in.  
    @discussion The IODBDMAMemoryCursor would be used when the DBDMA hardware is available for the device for that will use an instance of this cursor.
*/
class IODBDMAMemoryCursor : public IOMemoryCursor
{
    OSDeclareDefaultStructors(IODBDMAMemoryCursor)

public:
/*! @function outputSegment
    @abstract Outpust the given segment into the output segments array in address and length fields of an DBDMA descriptor.
    @param segment The physical address and length that is next to be output.
    @param segments Base of the output vector of DMA address length pairs.
    @param segmentIndex Index to output 'segment' in the 'segments' array.
*/
    static void outputSegment(PhysicalSegment segment,
			      void *	      segments,
			      UInt32	      segmentIndex);

/*! @defined dbdmaOutputSegment
    @discussion Backward compatibility define for the old global function definition.  See IODBDMAMemoryCursor::outputSegment. */
#define dbdmaOutputSegment IODBDMAMemoryCursor::outputSegment

/*! @function withSpecification
    @abstract Creates and initializes an IODBDMAMemoryCursor in one operation.
    @discussion Factory function to create and initialize an IODBDMAMemoryCursor in one operation.  See also IODBDMAMemoryCursor::initWithSpecification.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns a new memory cursor if successfully created and initialized, 0 otherwise.
*/
    static IODBDMAMemoryCursor * 
	withSpecification(IOPhysicalLength maxSegmentSize,
			  IOPhysicalLength maxTransferSize,
			  IOPhysicalLength alignment = 1);

/*! @function initWithSpecification
    @abstract Primary initializer for the IODBDMAMemoryCursor class.
    @param maxSegmentSize Maximum allowable size for one segment.  Defaults to 0.
    @param maxTransferSize Maximum size of an entire transfer.	Defaults to 0 indicating no maximum.
    @param alignment Alignment restrictions on output physical addresses.  Not currently implemented.  Defaults to single byte alignment.
    @result Returns true if the inherited classes and this instance initialize successfully.
*/
    virtual bool initWithSpecification(IOPhysicalLength	 maxSegmentSize,
				       IOPhysicalLength	 maxTransferSize,
				       IOPhysicalLength	 alignment = 1);


/*! @function getPhysicalSegments
    @abstract Generates a DBDMA physical scatter/gather list given a memory descriptor.
    @discussion Generates a list of DBDMA descriptors where the address and length fields are filled in appropriately.	But the client is expected to fill in the rest of the DBDMA descriptor as is appropriate for their particular hardware.  Wraps IOMemoryCursor::genPhysicalSegments.
    @param descriptor IOMemoryDescriptor that describes the data associated with an I/O request. 
    @param fromPosition Starting location of the I/O within a memory descriptor. 
    @param segments Pointer to an array of DBDMA descriptors for the output physical scatter/gather list.  Be warned no room is left for a preamble in the output array.  'segments' should point to the first memory description slot in a DBDMA command.
    @param maxSegments Maximum number of segments that can be written to the DBDMA descriptor table.
    @param maxTransferSize Maximum transfer size is limited to that many bytes, otherwise it defaults to the maximum transfer size specified when the memory cursor was initialized.
    @param transferSize Pointer to an IOByteCount variable that can contain the total size of the transfer being described.  Defaults to 0 indicating that no transfer size need be returned. 
    @result If the descriptor is exhausted of memory, a zero is returned, otherwise the number of segments that were filled in is returned.
*/
    virtual UInt32 getPhysicalSegments(IOMemoryDescriptor * descriptor,
				       IOByteCount	    fromPosition,
				       IODBDMADescriptor *  segments,
				       UInt32		    maxSegments,
				       UInt32		    maxTransferSize = 0,
				       IOByteCount	 *  transferSize = 0)
    {
	return genPhysicalSegments(descriptor, fromPosition, segments,
				maxSegments, maxTransferSize, transferSize);
    }
};

#endif /* defined(__ppc__) */

#endif /* !_IOMEMORYCURSOR_H */


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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
/* IOArray.m created by rsulack on Fri 12-Sep-1997 */
/* IOArray.cpp converted to C++ by gvdl on Fri 1998-10-30 */


#include <libkern/c++/OSArray.h>
#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSSerialize.h>
#include <libkern/c++/OSLib.h>

#define super OSCollection

OSDefineMetaClassAndStructors(OSArray, OSCollection)
OSMetaClassDefineReservedUnused(OSArray, 0);
OSMetaClassDefineReservedUnused(OSArray, 1);
OSMetaClassDefineReservedUnused(OSArray, 2);
OSMetaClassDefineReservedUnused(OSArray, 3);
OSMetaClassDefineReservedUnused(OSArray, 4);
OSMetaClassDefineReservedUnused(OSArray, 5);
OSMetaClassDefineReservedUnused(OSArray, 6);
OSMetaClassDefineReservedUnused(OSArray, 7);

#if OSALLOCDEBUG
extern "C" {
    extern int debug_container_malloc_size;
};
#define ACCUMSIZE(s) do { debug_container_malloc_size += (s); } while(0)
#else
#define ACCUMSIZE(s)
#endif

#define EXT_CAST(obj) \
    reinterpret_cast<OSObject *>(const_cast<OSMetaClassBase *>(obj))

bool OSArray::initWithCapacity(unsigned int inCapacity)
{
    int size;

    if (!super::init())
        return false;

    size = sizeof(const OSMetaClassBase *) * inCapacity;
    array = (const OSMetaClassBase **) kalloc(size);
    if (!array)
        return false;

    count = 0;
    capacity = inCapacity;
    capacityIncrement = (inCapacity)? inCapacity : 16;

    bzero(array, size);
    ACCUMSIZE(size);

    return true;
}

bool OSArray::initWithObjects(const OSObject *objects[],
                              unsigned int theCount,
                              unsigned int theCapacity)
{
    unsigned int initCapacity;

    if (!theCapacity)
        initCapacity = theCount;
    else if (theCount > theCapacity)
        return false;
    else
        initCapacity = theCapacity;

    if (!objects || !initWithCapacity(initCapacity))
        return false;

    for ( unsigned int i = 0; i < theCount; i++ ) {
        const OSMetaClassBase *newObject = *objects++;

        if (!newObject)
            return false;

        array[count++] = newObject;
        newObject->taggedRetain(OSTypeID(OSCollection));
    }

    return true;	
}

bool OSArray::initWithArray(const OSArray *anArray,
                            unsigned int theCapacity)
{
    if ( !anArray )
        return false;

    return initWithObjects((const OSObject **) anArray->array,
                           anArray->count, theCapacity);
}

OSArray *OSArray::withCapacity(unsigned int capacity)
{
    OSArray *me = new OSArray;

    if (me && !me->initWithCapacity(capacity)) {
        me->release();
        return 0;
    }

    return me;
}

OSArray *OSArray::withObjects(const OSObject *objects[],
                              unsigned int count,
                              unsigned int capacity)
{
    OSArray *me = new OSArray;

    if (me && !me->initWithObjects(objects, count, capacity)) {
        me->release();
        return 0;
    }

    return me;
}

OSArray *OSArray::withArray(const OSArray *array,
                            unsigned int capacity)
{
    OSArray *me = new OSArray;

    if (me && !me->initWithArray(array, capacity)) {
        me->release();
        return 0;
    }

    return me;
}

void OSArray::free()
{
    // Clear immutability - assumes the container is doing the right thing
    (void) super::setOptions(0, kImmutable);

    flushCollection();

    if (array) {
        kfree(array, sizeof(const OSMetaClassBase *) * capacity);
        ACCUMSIZE( -(sizeof(const OSMetaClassBase *) * capacity) );
    }

    super::free();
}


unsigned int OSArray::getCount() const { return count; }
unsigned int OSArray::getCapacity() const { return capacity; }
unsigned int OSArray::getCapacityIncrement() const { return capacityIncrement; }
unsigned int OSArray::setCapacityIncrement(unsigned int increment)
{
    capacityIncrement = (increment)? increment : 16;

    return capacityIncrement;
}

unsigned int OSArray::ensureCapacity(unsigned int newCapacity)
{
    const OSMetaClassBase **newArray;
    int oldSize, newSize;

    if (newCapacity <= capacity)
        return capacity;

    // round up
    newCapacity = (((newCapacity - 1) / capacityIncrement) + 1)
                * capacityIncrement;
    newSize = sizeof(const OSMetaClassBase *) * newCapacity;

    newArray = (const OSMetaClassBase **) kalloc(newSize);
    if (newArray) {
        oldSize = sizeof(const OSMetaClassBase *) * capacity;

        ACCUMSIZE(newSize - oldSize);

        bcopy(array, newArray, oldSize);
        bzero(&newArray[capacity], newSize - oldSize);
        kfree(array, oldSize);
        array = newArray;
        capacity = newCapacity;
    }

    return capacity;
}

void OSArray::flushCollection()
{
    unsigned int i;

    haveUpdated();
    for (i = 0; i < count; i++)
        array[i]->taggedRelease(OSTypeID(OSCollection));
    count = 0;
}

bool OSArray::setObject(const OSMetaClassBase *anObject)
{
    return setObject(count, anObject);
}

bool OSArray::setObject(unsigned int index, const OSMetaClassBase *anObject)
{
    unsigned int i;
    unsigned int newCount = count + 1;

    if ((index > count) || !anObject)
        return false;

    // do we need more space?
    if (newCount > capacity && newCount > ensureCapacity(newCount))
        return false;

    haveUpdated();
    if (index != count) {
        for (i = count; i > index; i--)
            array[i] = array[i-1];
    }
    array[index] = anObject;
    anObject->taggedRetain(OSTypeID(OSCollection));
    count++;

    return true;
}

bool OSArray::merge(const OSArray * otherArray)
{
    unsigned int otherCount = otherArray->getCount();
    unsigned int newCount = count + otherCount;

    if (!otherCount)
        return true;

    // do we need more space?
    if (newCount > capacity && newCount > ensureCapacity(newCount))
        return false;

    haveUpdated();
    for (unsigned int i = 0; i < otherCount; i++) {
        const OSMetaClassBase *newObject = otherArray->getObject(i);

        array[count++] = newObject;
        newObject->taggedRetain(OSTypeID(OSCollection));
    }

    return true;
}

void OSArray::
replaceObject(unsigned int index, const OSMetaClassBase *anObject)
{
    const OSMetaClassBase *oldObject;

    if ((index >= count) || !anObject)
        return;

    haveUpdated();
    oldObject = array[index];
    array[index] = anObject;
    anObject->taggedRetain(OSTypeID(OSCollection));

    oldObject->taggedRelease(OSTypeID(OSCollection));
}

void OSArray::removeObject(unsigned int index)
{
    unsigned int i;
    const OSMetaClassBase *oldObject;

    if (index >= count)
        return;

    haveUpdated();
    oldObject = array[index];

    count--;
    for (i = index; i < count; i++)
        array[i] = array[i+1];

    oldObject->taggedRelease(OSTypeID(OSCollection));
}

bool OSArray::isEqualTo(const OSArray *anArray) const
{
    unsigned int i;
    
    if ( this == anArray )
        return true;
    
    if ( count != anArray->getCount() )
        return false;

    for ( i = 0; i < count; i++ ) {
        if ( !array[i]->isEqualTo(anArray->getObject(i)) )
            return false;
    }

    return true;
}

bool OSArray::isEqualTo(const OSMetaClassBase *anObject) const
{
    OSArray *otherArray;

    otherArray = OSDynamicCast(OSArray, anObject);
    if ( otherArray )
        return isEqualTo(otherArray);
    else
        return false;
}

OSObject *OSArray::getObject(unsigned int index) const
{
    if (index >= count)
        return 0;
    else
        return (OSObject *) (const_cast<OSMetaClassBase *>(array[index]));
}

OSObject *OSArray::getLastObject() const
{
    if (count == 0)
        return 0;
    else
        return ( OSObject *) (const_cast<OSMetaClassBase *>(array[count - 1]));
}

unsigned int OSArray::getNextIndexOfObject(const OSMetaClassBase * anObject,
                                            unsigned int index) const
{
    while ((index < count) && (array[index] != anObject))
        index++;
    if (index >= count)
        index = (unsigned int)-1;
    return index;
}

unsigned int OSArray::iteratorSize() const
{
    return sizeof(unsigned int);
}

bool OSArray::initIterator(void *inIterator) const
{
    unsigned int *iteratorP = (unsigned int *) inIterator;

    *iteratorP = 0;
    return true;
}

bool OSArray::getNextObjectForIterator(void *inIterator, OSObject **ret) const
{
    unsigned int *iteratorP = (unsigned int *) inIterator;
    unsigned int index = (*iteratorP)++;

    if (index < count) {
        *ret = (OSObject *)(const_cast<OSMetaClassBase *> (array[index]));
        return true;
    }
    else {
        *ret = 0;
        return false;
    }
}

bool OSArray::serialize(OSSerialize *s) const
{
    if (s->previouslySerialized(this)) return true;
    
    if (!s->addXMLStartTag(this, "array")) return false;

    for (unsigned i = 0; i < count; i++) { 
        if (!array[i]->serialize(s)) return false;
    }

    return s->addXMLEndTag("array");
}

unsigned OSArray::setOptions(unsigned options, unsigned mask, void *)
{
    unsigned old = super::setOptions(options, mask);
    if ((old ^ options) & mask) {

	// Value changed need to recurse over all of the child collections
	for ( unsigned i = 0; i < count; i++ ) {
	    OSCollection *coll = OSDynamicCast(OSCollection, array[i]);
	    if (coll)
		coll->setOptions(options, mask);
	}
    }

    return old;
}

OSCollection * OSArray::copyCollection(OSDictionary *cycleDict)
{
    bool allocDict = !cycleDict;
    OSCollection *ret = 0;
    OSArray *newArray = 0;

    if (allocDict) {
	cycleDict = OSDictionary::withCapacity(16);
	if (!cycleDict)
	    return 0;
    }

    do {
	// Check for a cycle
	ret = super::copyCollection(cycleDict);
	if (ret)
	    continue;
	
	newArray = OSArray::withArray(this);
	if (!newArray)
	    continue;

	// Insert object into cycle Dictionary
	cycleDict->setObject((const OSSymbol *) this, newArray);

	for (unsigned int i = 0; i < count; i++) {
	    OSCollection *coll =
		OSDynamicCast(OSCollection, EXT_CAST(newArray->array[i]));

	    if (coll) {
		OSCollection *newColl = coll->copyCollection(cycleDict);
		if (!newColl)
		    goto abortCopy;

		newArray->replaceObject(i, newColl);
		newColl->release();
	    };
	};

	ret = newArray;
	newArray = 0;

    } while (false);

abortCopy:
    if (newArray)
	newArray->release();

    if (allocDict)
	cycleDict->release();

    return ret;
}


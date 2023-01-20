/*
 * Copyright (c) 1998-2004 Apple Computer, Inc. All rights reserved.
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
 * HISTORY
 *
 * 17-Apr-91   Portions from libIO.m, Doug Mitchell at NeXT.
 * 17-Nov-98   cpp
 *
 */

#include <IOKit/system.h>
#include <mach/sync_policy.h>
#include <machine/machine_routines.h>
#include <libkern/c++/OSCPPDebug.h>

#include <IOKit/assert.h>

#include <IOKit/IOReturn.h>
#include <IOKit/IOLib.h> 
#include <IOKit/IOLocks.h> 
#include <IOKit/IOMapper.h>
#include <IOKit/IOKitDebug.h> 

#include "IOKitKernelInternal.h"


#ifdef L4IOKIT
#include <iguana/hardware.h>
#include <iguana/memsection.h>
#endif

mach_timespec_t IOZeroTvalspec = { 0, 0 };

extern ppnum_t pmap_find_phys(pmap_t pmap, addr64_t va);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

lck_grp_t	*IOLockGroup;

/*
 * Global variables for use by iLogger
 * These symbols are for use only by Apple diagnostic code.
 * Binary compatibility is not guaranteed for kexts that reference these symbols.
 */

void *_giDebugLogInternal	= NULL;
void *_giDebugLogDataInternal	= NULL;
void *_giDebugReserved1		= NULL;
void *_giDebugReserved2		= NULL;


/*
 * Static variables for this module.
 */

static queue_head_t gIOMallocContiguousEntries;
static lck_mtx_t *  gIOMallocContiguousEntriesLock;

enum { kIOMaxPageableMaps = 16 };
enum { kIOPageableMapSize = 96 * 1024 * 1024 };
enum { kIOPageableMaxMapSize = 96 * 1024 * 1024 };

/* LP64todo - these need to expand */
typedef struct {
    vm_map_t	map;
    vm_offset_t	address;
    vm_offset_t	end;
} IOMapData;

static struct {
    UInt32	count;
    UInt32	hint;
    IOMapData	maps[ kIOMaxPageableMaps ];
    lck_mtx_t *	lock;
} gIOKitPageableSpace;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef L4IOKIT
struct physframe {
	vm_offset_t		addr;
	struct physframe	*next;
};

struct physframe *physhead;	/* 4K */
struct physframe *physhead64;	/* 64 K */

vm_offset_t
physalloc(size_t s)
{
	vm_offset_t	p;
	int		i;
	lck_spin_lock(xnulck);

	//printf("physalloc called, s = %lu\n", s);
	if (s > 0x1000 * 16) {
		printf("%s: warning: allocation larger than base size of "
		    "64K (caller asked for %d)\n", __func__, (int)s);
                s = round_page_32(s);
		memsection_create_direct(s, &p);
		if (!p)
			assert(!"could not allocate dodgy phys memory");
		goto out;
	}		
	p = (vm_offset_t)physhead;

	if (!physhead)
		assert(!"out of physalloc memory XXX FIXME XXX");

	physhead = physhead->next;
out:
	lck_spin_unlock(xnulck);

	assert(p);
	return p;
}

void
physfree(void *p, size_t s)
{
	struct physframe *f = p;

	assert(p);
	lck_spin_lock(xnulck);
	f->next = physhead;
	physhead = f;
	lck_spin_unlock(xnulck);

	return;
}
#endif


void IOLibInit(void)
{
    kern_return_t ret;

    static bool libInitialized;

    if(libInitialized)
        return;	

    gIOKitPageableSpace.maps[0].address = 0;
    ret = kmem_suballoc(kernel_map,
                    &gIOKitPageableSpace.maps[0].address,
                    kIOPageableMapSize,
                    TRUE,
                    VM_FLAGS_ANYWHERE,
                    &gIOKitPageableSpace.maps[0].map);
    if (ret != KERN_SUCCESS)
        panic("failed to allocate iokit pageable map\n");

#ifdef L4IOKIT
    //IOLog("IOLibInit: got address 0%lx map 0x%lx\n", 
//	gIOKitPageableSpace.maps[0].address, 
	//gIOKitPageableSpace.maps[0].map);

   // XXX L4IOKIT: We want some 1-1 pages in the low part of physical
   // memory.  If it's too high, apparently certain stuff won't work
   // like Ethernet, then it gives you bogus warnings about how
   // the checksum is incorrect on the ROM ... lalala.
   // so allocate some memory here.
   memsection_ref_t	ref;
   uintptr_t		physstrt, physend, chunk;
   /*
    * XXX yuck.
    */
   ref = memsection_create_direct(12 * 1024 * 1024, (uintptr_t)&physstrt);
   assert(ref && physstrt);

   physend = physstrt + (12 * 1024 * 1024);

   IOLog("IOLibInit: got phys 0x%lx - 0x%lx\n", physstrt, physend);

   physend -= 0x10000;
   while (physend >= physstrt) {
	struct physframe *tmp;

	tmp = (struct physframe *)physend;

	tmp->next = physhead;
	physhead = tmp;

	/*
	 * Set the boundary to 64K. Should be enough for anyone.
	 */
	physend -= (0x10000);
   }

   /*
    * 64K region, IDE for disk.
    */
#endif

    IOLockGroup = lck_grp_alloc_init("IOKit", LCK_GRP_ATTR_NULL);

    gIOKitPageableSpace.lock 		= lck_mtx_alloc_init(IOLockGroup, LCK_ATTR_NULL);
    gIOKitPageableSpace.maps[0].end	= gIOKitPageableSpace.maps[0].address + kIOPageableMapSize;
    gIOKitPageableSpace.hint		= 0;
    gIOKitPageableSpace.count		= 1;

    gIOMallocContiguousEntriesLock 	= lck_mtx_alloc_init(IOLockGroup, LCK_ATTR_NULL);
    queue_init( &gIOMallocContiguousEntries );

    libInitialized = true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef L4IOKIT
static IOThreadFunc threadArgFcn;
static void *threadArgArg;
lck_mtx_t *threadArgMutex;

#include <l4/thread.h>
#include <l4/ipc.h>

// note to self, we are doing this because thread_create_simple is broken!!

static void ioThreadStart( void )
{
    IOThreadFunc        fcn;
    void *              arg;

    fcn = threadArgFcn;
    arg = threadArgArg;
    //lock_done( threadArgLock);
    lck_mtx_unlock( threadArgMutex );

/*
 * XXX:
 *
 * note we have this crap here because thread_create_simple is broken
 * in Ig
 */
    //IOLog("ioThreadStart running func %p with arg %p, tid 0x%lx\n", 
//	fcn, arg, L4_Myself().raw);

    (*fcn)(arg);

    IOExitThread();
}

#endif

IOThread IOCreateThread(IOThreadFunc fcn, void *arg)
{
	kern_return_t	result;
	thread_t		thread;

	result = kernel_thread_start((thread_continue_t)fcn, arg, &thread);
	if (result != KERN_SUCCESS)
		return (NULL);

	thread_deallocate(thread);

	return (thread);
#if 0
	IOThread thread;

	lck_mtx_lock( threadArgMutex );
        //lock_write( threadArgLock);
        threadArgFcn = fcn;
        threadArgArg = arg;

        thread = kernel_thread( kernel_task, ioThreadStart);

        return(thread);
#endif
}


volatile void IOExitThread(void)
{

	(void) thread_terminate(current_thread());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void * IOMalloc(vm_size_t size)
{
    void * address;

    address = (void *)kalloc(size);
#if IOALLOCDEBUG
    if (address)
	debug_iomalloc_size += size;
#endif
#ifdef L4IOKIT
    assert(address);
#endif
    return address;
}

void IOFree(void * address, vm_size_t size)
{
#ifdef L4IOKIT
// XXX we should implement this, however, currently our malloc is done via 
// a host of memsection+_create() and kalloc, which means, that this isn't
// very nice when you don't have a matching kalloc for a kfree.
// so, we don't free for now.  Iny any case, our VM glue is non-existent
// so trying to work something out here, is pointless
// XXX - glee
// XXX maybe we can use this after all??
#endif
    if (address) {
	kfree(address, size);
#if IOALLOCDEBUG
	debug_iomalloc_size -= size;
#endif
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void * IOMallocAligned(vm_size_t size, vm_size_t alignment)
{
    kern_return_t	kr;
    vm_address_t	address;
    vm_address_t	allocationAddress;
    vm_size_t		adjustedSize;
    vm_offset_t		alignMask;

    if (size == 0)
        return 0;
    if (alignment == 0) 
        alignment = 1;

    alignMask = alignment - 1;
    adjustedSize = size + sizeof(vm_size_t) + sizeof(vm_address_t);

    if (adjustedSize >= page_size) {

        kr = kernel_memory_allocate(kernel_map, &address,
					size, alignMask, 0);
	if (KERN_SUCCESS != kr)
	    address = 0;

    } else {

	adjustedSize += alignMask;

	if (adjustedSize >= page_size) {

	    kr = kernel_memory_allocate(kernel_map, &allocationAddress,
					    adjustedSize, 0, 0);
	    if (KERN_SUCCESS != kr)
		allocationAddress = 0;

	} else
	    allocationAddress = (vm_address_t) kalloc(adjustedSize);

        if (allocationAddress) {
            address = (allocationAddress + alignMask
                    + (sizeof(vm_size_t) + sizeof(vm_address_t)))
                    & (~alignMask);

            *((vm_size_t *)(address - sizeof(vm_size_t)
                            - sizeof(vm_address_t))) = adjustedSize;
            *((vm_address_t *)(address - sizeof(vm_address_t)))
                            = allocationAddress;
	} else
	    address = 0;
    }

    assert(0 == (address & alignMask));

#if IOALLOCDEBUG
    if( address)
	debug_iomalloc_size += size;
#endif

#ifdef L4IOKIT
    assert(address);
#endif
    return (void *) address;
}

void IOFreeAligned(void * address, vm_size_t size)
{
    vm_address_t	allocationAddress;
    vm_size_t		adjustedSize;

    if( !address)
	return;

    assert(size);

    adjustedSize = size + sizeof(vm_size_t) + sizeof(vm_address_t);
    if (adjustedSize >= page_size) {

        kmem_free( kernel_map, (vm_address_t) address, size);

    } else {
        adjustedSize = *((vm_size_t *)( (vm_address_t) address
                                - sizeof(vm_address_t) - sizeof(vm_size_t)));
        allocationAddress = *((vm_address_t *)( (vm_address_t) address
				- sizeof(vm_address_t) ));

	if (adjustedSize >= page_size)
	    kmem_free( kernel_map, allocationAddress, adjustedSize);
	else
	  kfree((void *)allocationAddress, adjustedSize);
    }

#if IOALLOCDEBUG
    debug_iomalloc_size -= size;
#endif
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct _IOMallocContiguousEntry
{
    void *		virtual;
    ppnum_t		ioBase;
    queue_chain_t	link;
};
typedef struct _IOMallocContiguousEntry _IOMallocContiguousEntry;

void * IOMallocContiguous(vm_size_t size, vm_size_t alignment,
			   IOPhysicalAddress * physicalAddress)
{
#ifdef L4IOKIT
	memsection_ref_t	ref;
	uintptr_t		oldbase, base;
	vm_size_t		mysize;

	mysize = (alignment > size)? alignment : size;
	if (mysize < 0x1000/*pagesize*/)
		mysize = 0x1000;

	/*
	 * XXX THIS IS BAD
	 *
	 * This assumes that we always align on a PAGESIZE
	 *
	 * boundary.  Which is probably OK, but might be bad for
	 * other things.
	 */
#if 0
	ref = memsection_create_direct(size, &base);
	assert(ref);
#endif

	base = physalloc(mysize);

	assert(base);

	if (physicalAddress)
		*physicalAddress = (IOPhysicalAddress) base;
	// copied form L4Linux(Wombat)
	/*
	 * paranoia:
	 * make sure that we can write to everything
	 *
	 */
	memset(base, '\0', size);

	assert(base);
	return base;
#endif
#ifndef L4IOKIT 
    kern_return_t	kr;
    vm_address_t	address;
    vm_address_t	allocationAddress;
    vm_size_t		adjustedSize;
    vm_offset_t		alignMask;
    ppnum_t		pagenum;

    if (size == 0)
        return 0;
    if (alignment == 0) 
        alignment = 1;

    alignMask = alignment - 1;
    adjustedSize = (2 * size) + sizeof(vm_size_t) + sizeof(vm_address_t);

    if (adjustedSize >= page_size)
    {
	adjustedSize = size;
	if (adjustedSize > page_size)
	{
	    kr = kmem_alloc_contig(kernel_map, &address, size,
				    alignMask, 0);
	}
	else
	{
	    kr = kernel_memory_allocate(kernel_map, &address,
					size, alignMask, 0);
	}
	if (KERN_SUCCESS != kr)
	    address = 0;
    }
    else
    {
	adjustedSize += alignMask;
        allocationAddress = (vm_address_t) kalloc(adjustedSize);

        if (allocationAddress) {

            address = (allocationAddress + alignMask
                    + (sizeof(vm_size_t) + sizeof(vm_address_t)))
                    & (~alignMask);

            if (atop_32(address) != atop_32(address + size - 1))
                address = round_page_32(address);

            *((vm_size_t *)(address - sizeof(vm_size_t)
                            - sizeof(vm_address_t))) = adjustedSize;
            *((vm_address_t *)(address - sizeof(vm_address_t)))
                            = allocationAddress;
	} else
	    address = 0;
    }

    /* Do we want a physical address? */
    if (address && physicalAddress)
    {
#ifdef L4IOKIT
	//IOLog("IOMallocContiguous: want physical\n");
#endif
	do
	{
	    /* Get the physical page */
	    pagenum = pmap_find_phys(kernel_pmap, (addr64_t) address);
#ifdef L4IOKIT
	    //IOLog("IOMallocContiguous: got pagenum %d\n", pagenum);
#endif
	    if(pagenum)
	    {
		IOByteCount offset;
		ppnum_t base;
    
		base = IOMapperIOVMAlloc((size + PAGE_MASK) >> PAGE_SHIFT);
		if (base)
		{
#ifdef L4IOKIT
		//IOLog("IOMallocContiguous: got base 0x%lx addr 0x%lx\n",
		//    base, 
		 //   (base << PAGE_SHIFT) | (address & PAGE_MASK));
#endif
		    _IOMallocContiguousEntry *
		    entry = IONew(_IOMallocContiguousEntry, 1);
		    if (!entry)
		    {
			IOFreeContiguous((void *) address, size);
			address = 0;
			break;
		    }
		    entry->virtual = (void *) address;
		    entry->ioBase  = base;
		    lck_mtx_lock(gIOMallocContiguousEntriesLock);
		    queue_enter( &gIOMallocContiguousEntries, entry, 
				_IOMallocContiguousEntry *, link );
		    lck_mtx_unlock(gIOMallocContiguousEntriesLock);
    
		    *physicalAddress = (IOPhysicalAddress)((base << PAGE_SHIFT) | (address & PAGE_MASK));
		    for (offset = 0; offset < ((size + PAGE_MASK) >> PAGE_SHIFT); offset++, pagenum++)
			IOMapperInsertPage( base, offset, pagenum );
		}
		else
#ifdef L4IOKIT
                {
		    //IOLog("IOMallocContiguous: got base 0x%lx addr 0x%lx\n",
		    //base, 
		    //(base << PAGE_SHIFT) | (address & PAGE_MASK));
#endif
		    *physicalAddress = (IOPhysicalAddress)((pagenum << PAGE_SHIFT) | (address & PAGE_MASK));
#ifdef L4IOKIT
                }
#endif
	    } 
	    else
		/* Did not find, return 0 */
		*physicalAddress = (IOPhysicalAddress) 0;
	}
	while (false);
    }

    assert(0 == (address & alignMask));

#if IOALLOCDEBUG
    if( address)
	debug_iomalloc_size += size;
#endif

    return (void *) address;
#endif
}

void IOFreeContiguous(void * address, vm_size_t size)
{
#ifdef L4IOKIT
#if 0
	thread_ref_t	unused;
	memsection_ref_t	ref;
 
	ref = memsection_lookup((objref_t)address, &unused);
	assert(ref);

	memsection_delete(ref);
#endif

	physfree(address, size);

	return;
#endif
#ifndef	L4IOKIT		/* not implemented leak away! */
    vm_address_t	       allocationAddress;
    vm_size_t		       adjustedSize;
    _IOMallocContiguousEntry * entry;
    ppnum_t		       base = 0;

    if( !address)
	return;

    assert(size);

    lck_mtx_lock(gIOMallocContiguousEntriesLock);
    queue_iterate( &gIOMallocContiguousEntries, entry,
		    _IOMallocContiguousEntry *, link )
    {
	if( entry->virtual == address ) {
	    base = entry->ioBase;
	    queue_remove( &gIOMallocContiguousEntries, entry,
			    _IOMallocContiguousEntry *, link );
	    break;
	}
    }
    lck_mtx_unlock(gIOMallocContiguousEntriesLock);

    if (base)
    {
	IOMapperIOVMFree(base, (size + PAGE_MASK) >> PAGE_SHIFT);
	IODelete(entry, _IOMallocContiguousEntry, 1);
    }

    adjustedSize = (2 * size) + sizeof(vm_size_t) + sizeof(vm_address_t);
    if (adjustedSize >= page_size) {

        kmem_free( kernel_map, (vm_address_t) address, size);

    } else {
        adjustedSize = *((vm_size_t *)( (vm_address_t) address
                                - sizeof(vm_address_t) - sizeof(vm_size_t)));
        allocationAddress = *((vm_address_t *)( (vm_address_t) address
				- sizeof(vm_address_t) ));

        kfree((void *)allocationAddress, adjustedSize);
    }

#if IOALLOCDEBUG
    debug_iomalloc_size -= size;
#endif
#endif
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

kern_return_t IOIteratePageableMaps(vm_size_t size,
                    IOIteratePageableMapsCallback callback, void * ref)
{
    kern_return_t	kr = kIOReturnNotReady;
    vm_size_t		segSize;
    UInt32		attempts;
    UInt32		index;
    vm_offset_t		min;
    vm_map_t		map;

#ifdef L4IOKIT
    //IOLog("IOIteratePageableMaps size %d func %p ref %p\n", size, callback,
	//ref);
#endif
    if (size > kIOPageableMaxMapSize)
        return( kIOReturnBadArgument );

    do {
        index = gIOKitPageableSpace.hint;
        attempts = gIOKitPageableSpace.count;
        while( attempts--) {
            kr = (*callback)(gIOKitPageableSpace.maps[index].map, ref);
            if( KERN_SUCCESS == kr) {
                gIOKitPageableSpace.hint = index;
                break;
            }
            if( index)
                index--;
            else
                index = gIOKitPageableSpace.count - 1;
        }
        if( KERN_SUCCESS == kr)
            break;

        lck_mtx_lock( gIOKitPageableSpace.lock );

        index = gIOKitPageableSpace.count;
        if( index >= (kIOMaxPageableMaps - 1)) {
            lck_mtx_unlock( gIOKitPageableSpace.lock );
            break;
        }

        if( size < kIOPageableMapSize)
            segSize = kIOPageableMapSize;
        else
            segSize = size;

        min = 0;
        kr = kmem_suballoc(kernel_map,
                    &min,
                    segSize,
                    TRUE,
                    VM_FLAGS_ANYWHERE,
                    &map);
        if( KERN_SUCCESS != kr) {
            lck_mtx_unlock( gIOKitPageableSpace.lock );
            break;
        }

        gIOKitPageableSpace.maps[index].map 	= map;
        gIOKitPageableSpace.maps[index].address = min;
        gIOKitPageableSpace.maps[index].end 	= min + segSize;
        gIOKitPageableSpace.hint 		= index;
        gIOKitPageableSpace.count 		= index + 1;

        lck_mtx_unlock( gIOKitPageableSpace.lock );

    } while( true );

    return kr;
}

struct IOMallocPageableRef
{
    vm_address_t address;
    vm_size_t	 size;
};

static kern_return_t IOMallocPageableCallback(vm_map_t map, void * _ref)
{
    struct IOMallocPageableRef * ref = (struct IOMallocPageableRef *) _ref;
    kern_return_t	         kr;

    kr = kmem_alloc_pageable( map, &ref->address, ref->size );

    return( kr );
}

void * IOMallocPageable(vm_size_t size, vm_size_t alignment)
{
    kern_return_t	       kr = kIOReturnNotReady;
    struct IOMallocPageableRef ref;

    if (alignment > page_size)
        return( 0 );
    if (size > kIOPageableMaxMapSize)
        return( 0 );

    ref.size = size;
    kr = IOIteratePageableMaps( size, &IOMallocPageableCallback, &ref );
    if( kIOReturnSuccess != kr)
        ref.address = 0;

#if IOALLOCDEBUG
    if( ref.address)
       debug_iomallocpageable_size += round_page_32(size);
#endif

#ifdef L4IOKIT
    assert(ref.address);
#endif
    return( (void *) ref.address );
}

vm_map_t IOPageableMapForAddress( vm_address_t address )
{
    vm_map_t	map = 0;
    UInt32	index;
   
#ifdef L4IOKIT
    //IOLog("%s: trying to find a pageable map for addr 0x%lx\n", 
	//__FUNCTION__, address);
#endif 
    for( index = 0; index < gIOKitPageableSpace.count; index++) {
#ifdef L4IOKIT
//	IOLog("%s: index %d start 0x%lx end 0x%lx\n",
//		__FUNCTION__, index, gIOKitPageableSpace.maps[index].address,
//		gIOKitPageableSpace.maps[index].end);
#endif
        if( (address >= gIOKitPageableSpace.maps[index].address)
         && (address < gIOKitPageableSpace.maps[index].end) ) {
            map = gIOKitPageableSpace.maps[index].map;
            break;
        }
    }
#ifdef L4IOKIT
/*
 * XXX
 *
 * We don't have pageable maps in L4-IOKit for this moment since
 * we don't have a proper VM system.
 */
#endif
#ifndef L4IOKIT
    if( !map)
        IOPanic("IOPageableMapForAddress: null");
#endif

    return( map );
}

void IOFreePageable(void * address, vm_size_t size)
{
    vm_map_t map;
    
    map = IOPageableMapForAddress( (vm_address_t) address);
    if( map)
        kmem_free( map, (vm_offset_t) address, size);

#if IOALLOCDEBUG
    debug_iomallocpageable_size -= round_page_32(size);
#endif
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOReturn IOSetProcessorCacheMode( task_t task, IOVirtualAddress address,
				  IOByteCount length, IOOptionBits cacheMode )
{
    IOReturn	ret = kIOReturnSuccess;
    ppnum_t	pagenum;

    if( task != kernel_task)
	return( kIOReturnUnsupported );

    length = round_page_32(address + length) - trunc_page_32( address );
    address = trunc_page_32( address );

    // make map mode
    cacheMode = (cacheMode << kIOMapCacheShift) & kIOMapCacheMask;

    while( (kIOReturnSuccess == ret) && (length > 0) ) {

	// Get the physical page number
	pagenum = pmap_find_phys(kernel_pmap, (addr64_t)address);
	if( pagenum) {
            ret = IOUnmapPages( get_task_map(task), address, page_size );
	    ret = IOMapPages( get_task_map(task), address, pagenum << PAGE_SHIFT, page_size, cacheMode );
	} else
	    ret = kIOReturnVMError;

	address += page_size;
	length -= page_size;
    }

    return( ret );
}


IOReturn IOFlushProcessorCache( task_t task, IOVirtualAddress address,
				  IOByteCount length )
{
    if( task != kernel_task)
	return( kIOReturnUnsupported );

#ifdef __ppc__
    flush_dcache64( (addr64_t) address, (unsigned) length, false );
#endif

    return( kIOReturnSuccess );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

SInt32 OSKernelStackRemaining( void )
{
   SInt32 stack;

   stack = (((SInt32) &stack) & (KERNEL_STACK_SIZE - 1));

   return( stack );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void IOSleep(unsigned milliseconds)
{
    delay_for_interval(milliseconds, kMillisecondScale);
}

/*
 * Spin for indicated number of microseconds.
 */
void IODelay(unsigned microseconds)
{
    delay_for_interval(microseconds, kMicrosecondScale);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void IOLog(const char *format, ...)
{
	va_list ap;
	extern void conslog_putc(char);
	extern void logwakeup(void);

#ifdef L4IOKIT
#ifndef QUIETMODE
	va_start(ap, format);
	_doprnt(format, &ap, conslog_putc, 16);
	va_end(ap);
#endif	/*QUIETMODE*/
#endif	/*L4IOKIT*/
}

void IOPanic(const char *reason)
{
	panic(reason);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Convert a integer constant (typically a #define or enum) to a string.
 */
static char noValue[80];	// that's pretty

const char *IOFindNameForValue(int value, const IONamedValue *regValueArray)
{
	for( ; regValueArray->name; regValueArray++) {
		if(regValueArray->value == value)
			return(regValueArray->name);
	}
	sprintf(noValue, "0x%x (UNDEFINED)", value);
	return((const char *)noValue);
}

IOReturn IOFindValueForName(const char *string, 
	const IONamedValue *regValueArray,
	int *value)
{
	for( ; regValueArray->name; regValueArray++) {
		if(!strcmp(regValueArray->name, string)) {
			*value = regValueArray->value;
			return kIOReturnSuccess;
		}
	}
	return kIOReturnBadArgument;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOAlignment IOSizeToAlignment(unsigned int size)
{
    register int shift;
    const int intsize = sizeof(unsigned int) * 8;
    
    for (shift = 1; shift < intsize; shift++) {
	if (size & 0x80000000)
	    return (IOAlignment)(intsize - shift);
	size <<= 1;
    }
    return 0;
}

unsigned int IOAlignmentToSize(IOAlignment align)
{
    unsigned int size;
    
    for (size = 1; align; align--) {
	size <<= 1;
    }
    return size;
}

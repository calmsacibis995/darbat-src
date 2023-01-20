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
/*
 * Copyright (c) 1998 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 *
 */

#include <sys/sysctl.h>

#include <IOKit/IOKitDebug.h>
#include <IOKit/IOLib.h>
#include <IOKit/assert.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOService.h>

#include <libkern/c++/OSContainers.h>
#include <libkern/c++/OSCPPDebug.h>

#ifdef IOKITDEBUG
#define DEBUG_INIT_VALUE IOKITDEBUG
#else
#define DEBUG_INIT_VALUE 0
#endif

SInt64		gIOKitDebug = DEBUG_INIT_VALUE;
SYSCTL_QUAD(_debug, OID_AUTO, iokit, CTLFLAG_RW, &gIOKitDebug, "boot_arg io");


int 		debug_malloc_size;
int		debug_iomalloc_size;
vm_size_t	debug_iomallocpageable_size;
int 		debug_container_malloc_size;
// int 		debug_ivars_size; // in OSObject.cpp

extern "C" {


void IOPrintPlane( const IORegistryPlane * plane )
{
    IORegistryEntry *		next;
    IORegistryIterator * 	iter;
    OSOrderedSet *		all;
    char			format[] = "%xxxs";
    IOService *			service;

    iter = IORegistryIterator::iterateOver( plane );
    assert( iter );
    all = iter->iterateAll();
    if( all) {
        IOLog("Count %d\n", all->getCount() );
        all->release();
    } else
	IOLog("Empty\n");

    iter->reset();
    while( (next = iter->getNextObjectRecursive())) {
	sprintf( format + 1, "%ds", 2 * next->getDepth( plane ));
	IOLog( format, "");
	IOLog( "\033[33m%s", next->getName( plane ));
	if( (next->getLocation( plane )))
            IOLog("@%s", next->getLocation( plane ));
	IOLog("\033[0m <class %s", next->getMetaClass()->getClassName());
        if( (service = OSDynamicCast(IOService, next)))
            IOLog(", busy %ld", service->getBusyState());
	IOLog( ">\n");
	IOSleep(250);
    }
    iter->release();
}

void dbugprintf(char *fmt, ...);
void db_dumpiojunk( const IORegistryPlane * plane );

void db_piokjunk(void) {

	dbugprintf("\nDT plane:\n");
	db_dumpiojunk( gIODTPlane );
	dbugprintf("\n\nService plane:\n");
	db_dumpiojunk( gIOServicePlane );
    dbugprintf("\n\n"
	    "ivar kalloc()       0x%08x\n"
	    "malloc()            0x%08x\n"
            "containers kalloc() 0x%08x\n"
	    "IOMalloc()          0x%08x\n"
            "----------------------------------------\n",
	    debug_ivars_size,
            debug_malloc_size,
            debug_container_malloc_size,
            debug_iomalloc_size
            );

}


void db_dumpiojunk( const IORegistryPlane * plane )
{
    IORegistryEntry *		next;
    IORegistryIterator * 	iter;
    OSOrderedSet *		all;
    char			format[] = "%xxxs";
    IOService *			service;

    iter = IORegistryIterator::iterateOver( plane );

    all = iter->iterateAll();
    if( all) {
        dbugprintf("Count %d\n", all->getCount() );
        all->release();
    } else dbugprintf("Empty\n");

    iter->reset();
    while( (next = iter->getNextObjectRecursive())) {
		sprintf( format + 1, "%ds", 2 * next->getDepth( plane ));
		dbugprintf( format, "");
		dbugprintf( "%s", next->getName( plane ));
		if( (next->getLocation( plane )))
				dbugprintf("@%s", next->getLocation( plane ));
		dbugprintf(" <class %s", next->getMetaClass()->getClassName());
			if( (service = OSDynamicCast(IOService, next)))
				dbugprintf(", busy %ld", service->getBusyState());
		dbugprintf( ">\n");
    }
    iter->release();
}

void IOPrintMemory( void )
{

//    OSMetaClass::printInstanceCounts();

    IOLog("\n"
	    "ivar kalloc()       0x%08x\n"
	    "malloc()            0x%08x\n"
            "containers kalloc() 0x%08x\n"
	    "IOMalloc()          0x%08x\n"
            "----------------------------------------\n",
	    debug_ivars_size,
            debug_malloc_size,
            debug_container_malloc_size,
            debug_iomalloc_size
            );
}

} /* extern "C" */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define super OSObject
OSDefineMetaClassAndStructors(IOKitDiagnostics, OSObject)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSObject * IOKitDiagnostics::diagnostics( void )
{
    IOKitDiagnostics * diags;

    diags = new IOKitDiagnostics;
    if( diags && !diags->init()) {
	diags->release();
	diags = 0;
    }

    return( diags );
}

void IOKitDiagnostics::updateOffset( OSDictionary * dict,
			UInt32 value, const char * name )
{
    OSNumber * off;

    off = OSNumber::withNumber( value, 32 );
    if( !off)
	return;

    dict->setObject( name, off );
    off->release();
}


bool IOKitDiagnostics::serialize(OSSerialize *s) const
{
    OSDictionary * 	dict;
    bool		ok;

    dict = OSDictionary::withCapacity( 5 );
    if( !dict)
	return( false );

    updateOffset( dict, debug_ivars_size, "Instance allocation" );
    updateOffset( dict, debug_container_malloc_size, "Container allocation" );
    updateOffset( dict, debug_iomalloc_size, "IOMalloc allocation" );
    updateOffset( dict, debug_iomallocpageable_size, "Pageable allocation" );

    OSMetaClass::serializeClassDictionary(dict);

    ok = dict->serialize( s );

    dict->release();

    return( ok );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

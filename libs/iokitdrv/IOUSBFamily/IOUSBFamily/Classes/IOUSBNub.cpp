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

#include <libkern/OSByteOrder.h>

#include <libkern/c++/OSDictionary.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <libkern/c++/OSData.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/IOUSBController.h>
#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBPipe.h>

//#include "IOUSBUserClient.h"

#define DEBUGGING_LEVEL 0

#if DEBUGGING_LEVEL > 0
#define USBExpertStatusLevel(a, b, c, d) if (IOUSBController::_log) IOUSBController::_log->AddStatusLevel((UInt32)a, (UInt32)b, (char*)c, (UInt32)d)
#else
#define USBExpertStatusLevel(a, b, c, d)
#endif

#define super	IOService

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

#if 0
static const 
IOUSBDescriptorHeader *NextDescriptor(const void *desc)
{
    const UInt8 *next = (const UInt8 *)desc;
    UInt8 length = next[0];
    next = &next[length];
    return((const IOUSBDescriptorHeader *)next);
}



const IOUSBDescriptorHeader*
IOUSBNub::FindNextDescriptor(const void *cur, UInt8 descType)
{
    const IOUSBDescriptorHeader *hdr;
    hdr = (const IOUSBDescriptorHeader *)cur;
    do {
	hdr = NextDescriptor(hdr);
        if(hdr->length == 0)
            break;
        if(descType == 0)
            return hdr;	// type 0 is wildcard.
        else if(hdr->descriptorType == descType)
            return hdr;
    }
    while(true);

    return NULL;	// Fell off end of list
}
#endif
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSDefineMetaClass( IOUSBNub, IOService )
OSDefineAbstractStructors(IOUSBNub, IOService)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 ** Matching methods
 **/

#ifdef L4IOKIT
extern void printPlist(OSObject *o, UInt32 indent );
#endif

bool 
IOUSBNub::USBCompareProperty( OSDictionary   * matching, const char     * key )
{
    // We return success iff we match the key in the dictionary with the key in
    // the property table.
    //
    OSObject 	* value;
    bool		matches;

#ifdef L4IOKIT
#if 0
    IOLog("%s dictionary dump\n", __FUNCTION__);
    printPlist(matching, 1);
    L4_KDB_Enter("");
#endif
#endif
    value = matching->getObject( key );

    if( value)
        matches = value->isEqualTo( getProperty( key ));
    else
        matches = false;

#ifdef L4IOKIT
#if 0
    if (matches == true) {
	IOLog("%s: matches = t rue\n", __FUNCTION__);
	//L4_KDB_Enter("");
    }    
#endif
#endif
    return matches;
}

bool 
IOUSBNub::IsWildCardMatch( OSDictionary   * matching, const char     * key )
{
    // We return success iff the  key in the dictionary exists AND it is a OSString "*"
    // the property table.
    //
    OSString 	* theString;
    bool	matches;
    
    theString = OSDynamicCast(OSString, matching->getObject( key ));
#ifdef L4IOKIT
#if 0
    IOLog("%s dictionary dump\n", __FUNCTION__);
    printPlist(matching, 1);
    L4_KDB_Enter("");
#endif
#endif
    
    if( theString)
        matches = theString->isEqualTo("*");
    else
        matches = false;

#ifdef L4IOKIT
    if (matches == true) {
	IOLog("%s: matches = t rue\n", __FUNCTION__);
	//L4_KDB_Enter("");
    }    
#endif
    return matches;
}  

bool
IOUSBNub::USBComparePropertyWithMask( OSDictionary *matching, const char *key, const char * maskKey )
{
    // This routine will return success if the "key" in the dictionary  matches the key in the property table
    // while applying the "mask" value to both
    // First, check to see if we have both keys
    //
    OSNumber *	registryProperty = NULL;
    OSNumber *	dictionaryProperty = NULL;
    OSNumber *	dictionaryMask = NULL;
    
    registryProperty = OSDynamicCast(OSNumber,  getProperty(key));
    dictionaryProperty = OSDynamicCast(OSNumber, matching->getObject(key));
    dictionaryMask = OSDynamicCast(OSNumber, matching->getObject(maskKey));
    
    if ( registryProperty && dictionaryProperty && dictionaryMask )
    {
	// If all our values are OSNumbers, then get their actual value and do the masking
	// to see if they are equal
	//
	UInt32  registryValue = registryProperty->unsigned32BitValue();
	UInt32  dictionaryValue = dictionaryProperty->unsigned32BitValue();
	UInt32  mask = dictionaryMask->unsigned32BitValue();
	
	if ( (registryValue & mask) == (dictionaryValue & mask) )
	{
	    return true;
	}
    }
    
    return false;
}


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
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
 * Copyright (c) 1997 Apple Computer, Inc.
 *
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOHIDUSERCLIENT_H
#define _IOKIT_IOHIDUSERCLIENT_H

#include <IOKit/IOUserClient.h>
#include <IOKit/hidsystem/IOHIDSystem.h>


class IOHIDUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOHIDUserClient)

private:

    IOHIDSystem *	owner;

public:
    // IOUserClient methods
    virtual IOReturn clientClose( void );

    virtual IOService * getService( void );

    virtual IOReturn registerNotificationPort(
		mach_port_t port, UInt32 type, UInt32 refCon );

    virtual IOReturn connectClient( IOUserClient * client );

    virtual IOReturn clientMemoryForType( UInt32 type,
        UInt32 * flags, IOMemoryDescriptor ** memory );

    virtual IOExternalMethod * getTargetAndMethodForIndex(
                        IOService ** targetP, UInt32 index );

    // others

    virtual bool start( IOService * provider );
    virtual IOReturn setProperties( OSObject * properties );

};


class IOHIDParamUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(IOHIDParamUserClient)

private:

    IOHIDSystem *	owner;
    
public:

    // IOUserClient methods    
    virtual IOReturn clientClose( void );

    virtual IOService * getService( void );

    virtual IOExternalMethod * getTargetAndMethodForIndex(
                        IOService ** targetP, UInt32 index );

    // others

    virtual bool start( IOService * provider );
    virtual IOReturn setProperties( OSObject * properties );

};


#endif /* ! _IOKIT_IOHIDUSERCLIENT_H */

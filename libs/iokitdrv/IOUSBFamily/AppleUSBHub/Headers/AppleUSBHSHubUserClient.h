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


#include <IOKit/IOUserClient.h>
#include "AppleUSBHub.h"
#include "AppleUSBEHCI.h"

// Index for user client methods
//
enum
{
    kAppleUSBHSHubUserClientOpen = 0,
    kAppleUSBHSHubUserClientClose,
    kAppleUSBHSHubUserClientIsEHCIRootHub,
    kAppleUSBHSHubUserClientEnterTestMode,
    kAppleUSBHSHubUserClientLeaveTestMode,
    kAppleUSBHSHubUserClientGetNumberOfPorts,
    kAppleUSBHSHubUserClientPutPortIntoTestMode,
    kAppleUSBHSHubUserClientGetLocationID,
    kNumUSBHSHubMethods
};


class AppleUSBHSHubUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(AppleUSBHSHubUserClient)
    
private:

    AppleUSBHub *			fOwner;
    task_t				fTask;
    const IOExternalMethod *		fMethods;
    IOCommandGate *			fGate;
    UInt32				fNumMethods;
    mach_port_t 			fWakePort;
    bool				fDead;

    static const IOExternalMethod	sMethods[kNumUSBHSHubMethods];
    static const IOItemCount 		sMethodCount;

    virtual void 			SetExternalMethodVectors(void);

        //	IOService overrides
        //
    virtual IOReturn  			open(bool seize);
    virtual IOReturn  			close(void);
    virtual bool 			start( IOService * provider );
#ifndef L4IOKIT	// no virtual function here... blech
    virtual void 			stop( IOService * provider );
#endif

    //	IOUserClient overrides
    //
    virtual bool 			initWithTask( task_t owningTask, void * securityID, UInt32 type,  OSDictionary * properties );
    virtual IOExternalMethod * 		getTargetAndMethodForIndex(IOService **target, UInt32 index);
#ifndef L4IOKIT	// overrides?? yeh, right.
    virtual IOReturn 			clientClose( void );
#endif


    // Hub specific methods
    //
    IOReturn				IsEHCIRootHub(UInt32 *ret);
    IOReturn				EnterTestMode(void);
    IOReturn				LeaveTestMode(void);
    IOReturn				GetNumberOfPorts(UInt32 *numPorts);
    IOReturn				PutPortIntoTestMode(UInt32 port, UInt32 mode);
    IOReturn				GetLocationID(UInt32 *locID);
};

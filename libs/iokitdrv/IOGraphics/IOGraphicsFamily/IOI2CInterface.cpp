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

#include <IOKit/IOLib.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOLocks.h>
#include <IOKit/pwr_mgt/RootDomain.h>
#include <IOKit/ndrvsupport/IONDRVFramebuffer.h>
#include <IOKit/assert.h>
#include <libkern/c++/OSContainers.h>

#include <IOKit/i2c/IOI2CInterfacePrivate.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#undef super
#define super IOService

OSDefineMetaClassAndAbstractStructors(IOI2CInterface, IOService)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool IOI2CInterface::registerI2C( UInt64 id )
{
    bool result = true;

    fID = id;

    setProperty(kIOI2CInterfaceIDKey, id, 64);

    registerService();

    return (result);
}

IOReturn IOI2CInterface::newUserClient( task_t		owningTask,
                                        void * 		security_id,
                                        UInt32  	type,
                                        IOUserClient **	handler )

{
    IOReturn		err = kIOReturnSuccess;
    IOUserClient *	newConnect = 0;

    if (type)
        return (kIOReturnBadArgument);

    newConnect = IOI2CInterfaceUserClient::withTask(owningTask);

    if (newConnect)
    {
        if (!newConnect->attach(this)
                || !newConnect->start(this))
        {
            newConnect->detach( this );
            newConnect->release();
            newConnect = 0;
        }
    }

    *handler = newConnect;

    return (err);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#undef super
#define super IOUserClient

OSDefineMetaClassAndStructors(IOI2CInterfaceUserClient, IOUserClient)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

IOI2CInterfaceUserClient * IOI2CInterfaceUserClient::withTask( task_t owningTask )
{
    IOI2CInterfaceUserClient * inst;

    inst = new IOI2CInterfaceUserClient;
    if (inst && !inst->init())
    {
        inst->release();
        inst = 0;
    }
    if (inst)
        inst->fTask = owningTask;

    return (inst);
}

bool IOI2CInterfaceUserClient::start( IOService * provider )
{
    if (!super::start(provider))
        return (false);

    return (true);
}

IOReturn IOI2CInterfaceUserClient::clientClose( void )
{
    terminate();
    return (kIOReturnSuccess);
}

IOService * IOI2CInterfaceUserClient::getService( void )
{
    return (getProvider());
}

IOExternalMethod * IOI2CInterfaceUserClient::getTargetAndMethodForIndex(
    IOService ** targetP, UInt32 index )
{
    static const IOExternalMethod methodTemplate[] = {
                /* 0 */  { NULL, (IOMethod) &IOI2CInterfaceUserClient::extAcquireBus,
                           kIOUCScalarIScalarO, 0, 0 },
                /* 1 */  { NULL, (IOMethod) &IOI2CInterfaceUserClient::extReleaseBus,
                           kIOUCScalarIScalarO, 0, 0 },
                /* 3 */  { NULL, (IOMethod) &IOI2CInterfaceUserClient::extIO,
                           kIOUCStructIStructO, 0xffffffff, 0xffffffff },
            };

    if (index > (sizeof(methodTemplate) / sizeof(methodTemplate[0])))
        return (NULL);

    *targetP = this;
    return ((IOExternalMethod *)(methodTemplate + index));
}

IOReturn IOI2CInterfaceUserClient::setProperties( OSObject * properties )
{
    return (kIOReturnUnsupported);
}

IOReturn IOI2CInterfaceUserClient::extAcquireBus( void )
{
    IOReturn		ret = kIOReturnNotReady;
    IOI2CInterface *	provider;

    if ((provider = (IOI2CInterface *) copyParentEntry(gIOServicePlane)))
    {
        ret = provider->open( this ) ? kIOReturnSuccess : kIOReturnBusy;
        provider->release();
    }

    return (ret);
}

IOReturn IOI2CInterfaceUserClient::extReleaseBus( void )
{
    IOReturn		ret = kIOReturnNotReady;
    IOI2CInterface *	provider;

    if ((provider = (IOI2CInterface *) copyParentEntry(gIOServicePlane)))
    {
        provider->close( this );
        provider->release();
        ret = kIOReturnSuccess;
    }

    return (ret);
}

IOReturn IOI2CInterfaceUserClient::extIO(
    void * inStruct, void * outStruct,
    IOByteCount inSize, IOByteCount * outSize )
{
    IOReturn		err = kIOReturnNotReady;
    IOI2CInterface *	provider;
    IOI2CRequest *	request;
    IOI2CBuffer *	buffer;

    if (inSize < sizeof(IOI2CRequest))
        return (kIOReturnNoSpace);
    if (*outSize < inSize)
        return (kIOReturnNoSpace);

    if ((provider = (IOI2CInterface *) copyParentEntry(gIOServicePlane)))
        do
        {
            if (!provider->isOpen(this))
            {
                err = kIOReturnNotOpen;
                continue;
            }

            buffer = (IOI2CBuffer *) inStruct;
            request = &buffer->request;

            if (request->sendBytes)
            {
                if (!request->sendBuffer)
                    request->sendBuffer = (vm_address_t)  &buffer->inlineBuffer[0];
                else
                {
                    err = kIOReturnMessageTooLarge;
                    continue;
                }
            }
            if (request->replyBytes)
            {
                if (!request->replyBuffer)
                    request->replyBuffer = (vm_address_t) &buffer->inlineBuffer[0];
                else
                {
                    err = kIOReturnMessageTooLarge;
                    continue;
                }
            }

            err = provider->startIO( &buffer->request );
        }
        while (false);

    if (provider)
        provider->release();

    if (kIOReturnSuccess == err)
    {
        *outSize = inSize;
        bcopy(inStruct, outStruct, inSize);
    }
    else
        *outSize = 0;

    return (err);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



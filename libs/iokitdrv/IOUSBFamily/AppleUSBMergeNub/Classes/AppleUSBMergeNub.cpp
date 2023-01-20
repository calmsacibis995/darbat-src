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

#include "AppleUSBMergeNub.h"

#include <IOKit/usb/IOUSBController.h>
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/IOService.h>

#include <libkern/c++/OSNumber.h>

#define super IOService

OSDefineMetaClassAndStructors(AppleUSBMergeNub, IOService)

static bool haveCreatedRef = false;

//================================================================================================
//
//  probe()
//
//  This is a special IOUSBDevice driver which will always fail to probe. However, the probe
//  will have a side effect, which is that it merge a property dictionary into his provider's
//  parent NUB in the gIOUSBPlane
//
//================================================================================================
//
IOService *
AppleUSBMergeNub::probe(IOService *provider, SInt32 *score)
{
    const IORegistryPlane * usbPlane = getPlane(kIOUSBPlane);
    
    IOUSBDevice	*device = OSDynamicCast(IOUSBDevice, provider);
    if (device && usbPlane)
    {
        IOUSBNub *parentNub = OSDynamicCast(IOUSBNub, device->getParentEntry(usbPlane));

        if (parentNub)
        {
            OSDictionary *providerDict = (OSDictionary*)getProperty("IOProviderParentUSBNubMergeProperties");
            if (providerDict)
            {
                //    parentNub->getPropertyTable()->merge(providerDict);		// merge will verify that this really is a dictionary
                MergeDictionaryIntoProvider( parentNub, providerDict);
            }
        }
    }

    OSDictionary *providerDict = (OSDictionary*)getProperty("IOProviderMergeProperties");
    if (providerDict)
    {
          //   provider->getPropertyTable()->merge(providerDict);		// merge will verify that this really is a dictionary
        MergeDictionaryIntoProvider( provider, providerDict);
    }
    
    return NULL;								// always fail the probe!
}

//================================================================================================
//
//  MergeDictionaryIntoProvider
//
//  We will iterate through the dictionary that we want to merge into our provider.  If
//  the dictionary entry is not an OSDictionary, we will set that property into our provider.  If it is a
//  OSDictionary, we will get our provider's entry and merge our entry into it, recursively.
//
//================================================================================================
//
bool
AppleUSBMergeNub::MergeDictionaryIntoProvider(IOService * provider, OSDictionary * dictionaryToMerge)
{
    const OSSymbol * 		dictionaryEntry = NULL;
    OSCollectionIterator * 	iter = NULL;
    bool			result = false;

    USBLog(6,"+%s[%p]::MergeDictionary(%p)IntoProvider(%p)", getName(), this, dictionaryToMerge, provider);

    if (!provider || !dictionaryToMerge)
        return false;

	//
	// rdar://4041566 -- Trick the C++ run-time into keeping us loaded.
	//
	if (haveCreatedRef == false) 
	{
		haveCreatedRef = true;
		getMetaClass()->instanceConstructed();
	}
	
    // Get the dictionary whose entries we need to merge into our provider and get
    // an iterator to it.
    //
    iter = OSCollectionIterator::withCollection((OSDictionary *)dictionaryToMerge);
    if ( iter != NULL )
    {
        // Iterate through the dictionary until we run out of entries
        //
        while ( NULL != (dictionaryEntry = (const OSSymbol *)iter->getNextObject()) )
        {
            const char *	str = NULL;
            OSDictionary *	sourceDictionary = NULL;
            OSDictionary *	providerDictionary = NULL;
            OSObject *		providerProperty = NULL;

            // Get the symbol name for debugging
            //
            str = dictionaryEntry->getCStringNoCopy();
            USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  merging \"%s\"", getName(), this, str);

            // Check to see if our destination already has the same entry.  If it does
            // we assume that it is a dictionary.  Perhaps we should check that
            //
            providerProperty = provider->getProperty(dictionaryEntry);
            if ( providerProperty )
            {
                USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  provider already had property %s", getName(), this, str);
                providerDictionary = OSDynamicCast(OSDictionary, providerProperty);
                if ( providerDictionary )
                {
                    USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  provider's %s is also a dictionary (%p)", getName(), this, str, providerDictionary);
                }
            }

            // See if our source entry is also a dictionary
            //
            sourceDictionary = OSDynamicCast(OSDictionary, dictionaryToMerge->getObject(dictionaryEntry));
            if ( sourceDictionary )
            {
                USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  source dictionary had %s as a dictionary (%p)", getName(), this, str, sourceDictionary);
            }

            if ( providerDictionary &&  sourceDictionary )
            {
                // Need to merge our entry into the provider's dictionary.  However, we don't have a copy of our dictionary, just
                // a reference to it.  So, we need to make a copy of our provider's dictionary
                //
                OSDictionary *		localCopyOfProvidersDictionary;
                UInt32			providerSize;
                UInt32			providerSizeAfterMerge;

                localCopyOfProvidersDictionary = OSDictionary::withDictionary( providerDictionary, 0);
                if ( localCopyOfProvidersDictionary == NULL )
                {
                    USBError(1,"%s[%p]::MergeDictionaryIntoProvider  could not copy our provider's dictionary",getName(), this);
                    break;
                }

                // Get the size of our provider's dictionary so that we can check later whether it changed
                //
                providerSize = providerDictionary->getCapacity();
                USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  Created a local copy(%p) of dictionary (%p), size %d", getName(), this, localCopyOfProvidersDictionary, providerDictionary, providerSize);

                // Note that our providerDictionary *might* change
                // between the time we copied it and when we write it out again.  If so, we will obviously overwrite anychanges
                //
                USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  need to merge a dictionary (%s)", getName(), this, str);
                result = MergeDictionaryIntoDictionary(  sourceDictionary, localCopyOfProvidersDictionary);
                if ( result )
                {
                    // Get the size of our provider's dictionary so to see if it's changed  (Yes, the size could remain the same but the contents
                    // could have changed, but this gives us a first approximation.  We're not doing anything with this result, although we could
                    // remerge
                    //
                    providerSizeAfterMerge = providerDictionary->getCapacity();
                    if ( providerSizeAfterMerge != providerSize )
                    {
                        USBError(1,"%s[%p]::MergeDictionaryIntoProvider  our provider's dictionary size changed (%d,%d)",getName(), this, providerSize, providerSizeAfterMerge);
                    }

                    USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  setting  property %s from merged dictionary (%p)", getName(), this, str, providerDictionary);
                    result = provider->setProperty( dictionaryEntry, localCopyOfProvidersDictionary );
                    if ( !result )
                    {
                        USBLog(3,"%s[%p]::MergeDictionaryIntoProvider  setProperty %s , returned false", getName(), this, str);
                        break;
                    }
                }
                else
                {
                    // If we got an error merging dictionaries, then just bail out without doing anything
                    //
                    USBLog(3,"%s[%p]::MergeDictionaryIntoProvider  MergeDictionaryIntoDictionary(%p,%p) returned false", getName(), this, sourceDictionary, providerDictionary);
                    break;
                }
            }
            else
            {
                USBLog(5,"%s[%p]::MergeDictionaryIntoProvider  setting property %s", getName(), this, str);
                result = provider->setProperty(dictionaryEntry, dictionaryToMerge->getObject(dictionaryEntry));
                if ( !result )
                {
                    USBLog(3,"%s[%p]::MergeDictionaryIntoProvider  setProperty %s, returned false", getName(), this, str);
                    break;
                }
            }
        }
        iter->release();
    }
    USBLog(6,"-%s[%p]::MergeDictionaryIntoProvider(%p, %p)  result %d", getName(), this, provider, dictionaryToMerge, result);

    return result;
}


//================================================================================================
//
//  MergeDictionaryIntoDictionary( parentSourceDictionary, parentTargetDictionary)
//
//  This routine will merge the contents of parentSourceDictionary into the targetDictionary, recursively.
//  Note that we are only modifying copies of the parentTargetDictionary, so we don't expect anybody
//  else to be accessing them at the same time.
//
//================================================================================================
//
bool
AppleUSBMergeNub::MergeDictionaryIntoDictionary(OSDictionary * parentSourceDictionary,  OSDictionary * parentTargetDictionary)
{
    OSCollectionIterator*	srcIterator = NULL;
    OSSymbol*			keyObject = NULL ;
    OSObject*			targetObject = NULL ;
    bool			result = false;

    USBLog(3,"+%s[%p]::MergeDictionaryIntoDictionary(%p => %p)", getName(), this, parentSourceDictionary, parentTargetDictionary);

    if (!parentSourceDictionary || !parentTargetDictionary)
        return false ;

    // Get our source dictionary
    //
    srcIterator = OSCollectionIterator::withCollection(parentSourceDictionary) ;

    while (NULL != (keyObject = OSDynamicCast(OSSymbol, srcIterator->getNextObject())))
    {
        const char *	str;
        OSDictionary *	childSourceDictionary = NULL;
        OSDictionary *	childTargetDictionary = NULL;
        OSObject *	childTargetObject = NULL;

        // Get the symbol name for debugging
        //
        str = keyObject->getCStringNoCopy();
        USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  merging \"%s\"", getName(), this, str);

        // Check to see if our destination already has the same entry.
        //
        childTargetObject = parentTargetDictionary->getObject(keyObject);
        if ( childTargetObject )
        {
            childTargetDictionary = OSDynamicCast(OSDictionary, childTargetObject);
            if ( childTargetDictionary )
                USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  target object %s is a dictionary (%p)", getName(), this, str, childTargetDictionary);
        }

        // See if our source entry is also a dictionary
        //
        childSourceDictionary = OSDynamicCast(OSDictionary, parentSourceDictionary->getObject(keyObject));
        if ( childSourceDictionary )
        {
            USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  source dictionary had %s as a dictionary (%p)", getName(), this, str, childSourceDictionary);
        }

        if ( childTargetDictionary && childSourceDictionary)
        {
            // Our destination dictionary already has the entry for this same object AND our
            // source is also a dcitionary, so we need to recursively add it.
            //
            USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  recursing(%p,%p)", getName(), this, childSourceDictionary, childTargetDictionary);
            result = MergeDictionaryIntoDictionary(childSourceDictionary, childTargetDictionary) ;
            if ( !result )
            {
                USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  recursing (%p,%p) failed", getName(), this, childSourceDictionary, childTargetDictionary);
                break;
            }
        }
        else
        {
            // We have a property that we need to merge into our parent dictionary.
            //
            USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  setting object %s into dictionary %p", getName(), this, str, parentTargetDictionary);
            result = parentTargetDictionary->setObject(keyObject, parentSourceDictionary->getObject(keyObject)) ;
            if ( !result )
            {
                USBLog(3,"%s[%p]::MergeDictionaryIntoDictionary  setObject %s, returned false", getName(), this, str);
                break;
            }
        }

    }

    srcIterator->release();

    USBLog(3,"-%s[%p]::MergeDictionaryIntoDictionary(%p=>(%p)  result %d", getName(), this, parentSourceDictionary, parentTargetDictionary, result);
    return result;
}


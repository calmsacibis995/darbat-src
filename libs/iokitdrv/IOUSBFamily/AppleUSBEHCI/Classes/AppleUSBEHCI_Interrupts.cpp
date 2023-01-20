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
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/usb/IOUSBRootHubDevice.h>
#include "AppleUSBEHCI.h"

#define super IOUSBControllerV2
#define self this

#ifdef L4IOKIT
#include <l4/kdebug.h>
#endif

// Delete this later and clean up
//#define EndianSwap32Bit USBToHostLong




void 
AppleUSBEHCI::PollInterrupts(IOUSBCompletionAction safeAction)
{
    if (_hostErrorInterrupt & kEHCIHostErrorIntBit)
    {
        _hostErrorInterrupt = 0;
        
		// Host System Error - this is a serious error on the PCI bus
		// Only print it every power of 2 times
		//
#ifdef L4IOKIT
			IOLog("BAD!\n");
			L4_KDB_Enter("");
#endif
		if ( ++_errors.hostSystemError == (UInt32) (1L << _errors.displayed) )
		{
			USBLog(1, "%s[%p]::PollInterrupts - Host System Error Occurred - not restarted", getName(), this);
			_errors.displayed++;
		}

#if 0
		// We should only attempt this once...
		
		// Cardbus cards can generate spurious interrupts while ejecting, so don't try to recover on cardbus cards
		//
		if ( !_onCardBus )
		{
			if ( _rootHubDevice )
			{
				_rootHubDevice->terminate(kIOServiceRequired | kIOServiceSynchronous);
				_rootHubDevice->detachAll(gIOUSBPlane);
				_rootHubDevice->release();
				_rootHubDevice = NULL;
			}
			SuspendUSBBus();
			UIMFinalizeForPowerDown();
			ehciAvailable = false;					// tell the interrupt filter routine that we are off
			IOSleep(100);
			
			// Initialize our hardware
			//
			UIMInitializeForPowerUp();
			
			_ehciBusState = kEHCIBusStateRunning;
			_ehciAvailable = true;										// tell the interrupt filter routine that we are on
			if ( _rootHubDevice == NULL )
			{
				IOReturn err = CreateRootHubDevice( _device, &_rootHubDevice );
				if ( err != kIOReturnSuccess )
				{
					USBError(1,"%s[%p] Could not create root hub device upon wakeup (%x)!",getName(), this, err);
				}
				else
				{
					_rootHubDevice->registerService(kIOServiceRequired | kIOServiceSynchronous);
				}
			}
        }
#endif
    }
	
    if (_errorInterrupt & kEHCIErrorIntBit)
    {
        _errorInterrupt = 0;
        
        USBLog(7, "%s[%p]::PollInterrupts - completion (_errorInterrupt) interrupt", getName(), this);
        scavengeCompletedTransactions(safeAction);
    }
	
    if (_completeInterrupt & kEHCICompleteIntBit)
    {
        _completeInterrupt = 0;
        USBLog(7, "%s[%p]::PollInterrupts - completion (_completeInterrupt) interrupt", getName(), this);
        scavengeCompletedTransactions(safeAction);
    }
	
    /*
	 * RootHubStatusChange Interrupt
	 */
    if (_portChangeInterrupt & kEHCIPortChangeIntBit)
    {
        _portChangeInterrupt = 0;
        
		// Clear status change.
		_remote_wakeup_occurred = true; //needed by ::callPlatformFunction()
	
		USBLog(3, "%s[%p]::PollInterrupts - port change detect interrupt", getName(), this);
        if ( _idleSuspend )
		{
			USBLog(1, "%s[%p]::PollInterrupts - port change detect interrupt while in idlesuspend - restarting bus", getName(), this);
            setPowerState(kEHCISetPowerLevelRunning, self);
		}
	    
		UIMRootHubStatusChange();
    }
    /*
	 * OwnershipChange Interrupt
	 */
    if (_asyncAdvanceInterrupt & kEHCIAAEIntBit)
    {
        _asyncAdvanceInterrupt = 0;
		_errors.ownershipChange++;
		_pEHCIRegisters->USBSTS = USBToHostLong(kEHCIAAEIntBit);
		USBLog(3, "%s[%p]::PollInterrupts - async advance interrupt", getName(), this);
    }
}



void
AppleUSBEHCI::InterruptHandler(OSObject *owner, IOInterruptEventSource * /*source*/, int /*count*/)
{
    register 	AppleUSBEHCI		*controller = (AppleUSBEHCI *) owner;
    static 	Boolean 		emitted;
	
    if (!controller || controller->isInactive() || (controller->_onCardBus && controller->_pcCardEjected) || !controller->_ehciAvailable)
        return;
	
    if(!emitted)
    {
        emitted = true;
        // USBLog("EHCIUIM -- InterruptHandler Unimplimented not finishPending\n");
    }
	
    controller->PollInterrupts();
}



// This routine will get called at Primary interrupt time. 
//
// At primary interrupt time we are mainly concerned with updating the frStatus and frActCount fields of the frames
// in low latency isoch TD's. We also updated the master frame counter.
//
// Since this is a static method, the work is actually done by the FilterInterrupt, which is an instance method
//
bool 
AppleUSBEHCI::PrimaryInterruptFilter(OSObject *owner, IOFilterInterruptEventSource *source)
{
    register AppleUSBEHCI *controller = (AppleUSBEHCI *)owner;
    bool result = true;

    // If we our controller has gone away, or it's going away, or if we're on a PC Card and we have been ejected,
    // then don't process this interrupt.
    //
    if (!controller || controller->isInactive() || (controller->_onCardBus && controller->_pcCardEjected) || !controller->_ehciAvailable)
        return false;
	
    if (controller->_ehciBusState == kEHCIBusStateSuspended)
    {
		// Unexpected interrupt while bus is suspended.  What's up with that? 
		//
		return true;
    }
	
    // Process this interrupt
    //
    controller->_filterInterruptActive = true;
    result = controller->FilterInterrupt(0);
    controller->_filterInterruptActive = false;
    return result;
}



bool 
AppleUSBEHCI::FilterInterrupt(int index)
{
    
    register UInt32			activeInterrupts;
    register UInt32			enabledInterrupts;
    Boolean				needSignal = false;
    AbsoluteTime			timeStamp;
   
    enabledInterrupts = USBToHostLong(_pEHCIRegisters->USBIntr);
    activeInterrupts = enabledInterrupts & USBToHostLong(_pEHCIRegisters->USBSTS);
   
#ifdef L4IOKIT
#if 0	/*NODEBUG*/
    if (activeInterrupts != 0) { 
        if (activeInterrupts & kEHCIFrListRolloverIntBit)
		IOLog("usb: rollover\n");
        if (activeInterrupts & kEHCIAAEIntBit)
		IOLog("usb: aaeint\n");
        if (activeInterrupts & kEHCIHostErrorIntBit)
		IOLog("usb: hosterr\n");
        if (activeInterrupts & kEHCIPortChangeIntBit)
		IOLog("usb: portchangeint\n");
        if (activeInterrupts & kEHCIErrorIntBit)
		IOLog("usb: errorint\n");
        if (activeInterrupts & kEHCICompleteIntBit)
		IOLog("usb: completeint\n");
    }
#endif
#endif
 
    if (activeInterrupts != 0)
    {
        // One of our 6 interrupts fired.  Process the ones which need to be processed at primary int time
        //
		
        // Frame Number Rollover
        //
        if (activeInterrupts & kEHCIFrListRolloverIntBit)
        {
			UInt32		frindex;
			
			// NOTE: This code depends upon the fact that we do not change the Frame List Size
			// in the USBCMD register. If the frame list size changes, then this code needs to change
			frindex = USBToHostLong(_pEHCIRegisters->FRIndex);
			if (frindex < kEHCIFRIndexRolloverBit)
				_frameNumber += kEHCIFrameNumberIncrement;
			
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIFrListRolloverIntBit);			// clear the interrupt
            IOSync();
        }
		// at the moment, let the secondary interrupt handler get these by signaling
        if (activeInterrupts & kEHCIAAEIntBit)
		{
			_asyncAdvanceInterrupt = kEHCIAAEIntBit;
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIAAEIntBit);				// clear the interrupt
            IOSync();
			needSignal = true;
		}
        if (activeInterrupts & kEHCIHostErrorIntBit)
		{
			_hostErrorInterrupt = kEHCIHostErrorIntBit;
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIHostErrorIntBit);				// clear the interrupt
            IOSync();
			needSignal = true;
		}
        if (activeInterrupts & kEHCIPortChangeIntBit)
		{
			_portChangeInterrupt = kEHCIPortChangeIntBit;
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIPortChangeIntBit);				// clear the interrupt
            IOSync();
			if (_errataBits & kErrataNECIncompleteWrite)
			{
				UInt32		newValue = 0, count = 0;
				newValue = USBToHostLong(_pEHCIRegisters->USBSTS);						// this bit SHOULD now be cleared
				while ((count++ < 10) && (newValue & kEHCIPortChangeIntBit))
				{
					// can't log in the FilterInterrupt routine
					// USBError(1, "EHCI driver: FilterInterrupt - PCD bit not sticking. Retrying.");
					_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIPortChangeIntBit);				// clear the bit again
					IOSync();
					newValue = USBToHostLong(_pEHCIRegisters->USBSTS);
				}
			}
			needSignal = true;
		}
        if (activeInterrupts & kEHCIErrorIntBit)
		{
			_errorInterrupt = kEHCIErrorIntBit;
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCIErrorIntBit);				// clear the interrupt
            IOSync();
			needSignal = true;
		}
        if (activeInterrupts & kEHCICompleteIntBit)
		{
            // Now that we have the beginning of the queue, walk it looking for low latency isoch TD's
            // Use this time as the time stamp time for all the TD's that we processed.  
            //
            clock_get_uptime(&timeStamp);
			_completeInterrupt = kEHCICompleteIntBit;
			_pEHCIRegisters->USBSTS = HostToUSBLong(kEHCICompleteIntBit);			// clear the interrupt
            IOSync();
			needSignal = true;
			
			// we need to check the periodic list to see if there are any Isoch TDs which need to come off
			// and potentially have their frame lists updated (for Low Latency) we will place them in reverse
			// order on a "done queue" which will be looked at by the isoch scavanger
			// only do this if the periodic schedule is enabled
			if (!_inAbortIsochEP && (_pEHCIRegisters->USBCMD & HostToUSBLong(kEHCICMDPeriodicEnable)) && (_outSlot < kEHCIPeriodicListEntries))
			{
				AppleEHCIIsochListElement *		cachedHead;
				UInt32							cachedProducer;
				UInt32							frIndex;
				UInt16							curSlot, testSlot, nextSlot;
				UInt16							curMicroFrame;
				
				frIndex = USBToHostLong(_pEHCIRegisters->FRIndex);
				curSlot = (frIndex >> 3) & (kEHCIPeriodicListEntries-1);
				curMicroFrame = frIndex & 7;
				
				cachedHead = (AppleEHCIIsochListElement*)_savedDoneQueueHead;
				cachedProducer = _producerCount;
				testSlot = _outSlot;
				
				while (testSlot != curSlot)
				{
					AppleEHCIListElement					*thing, *prevThing, *nextThing;
					AppleEHCIIsochListElement				*isochEl;
					AppleEHCISplitIsochTransferDescriptor	*splitTD;
					bool									needToRescavenge = false;
					
					nextSlot = (testSlot+1) & (kEHCIPeriodicListEntries-1);
					thing = _logicalPeriodicList[testSlot];
					prevThing = NULL;
					while(thing != NULL)
					{
						nextThing = thing->_logicalNext;
						isochEl = OSDynamicCast(AppleEHCIIsochListElement, thing);

						if (!isochEl)
							break;						// only care about Isoch in this list - if we get here we are at the interrupt TDs

						splitTD = OSDynamicCast(AppleEHCISplitIsochTransferDescriptor, isochEl);
						
						// check to see if all of these conditions are met, if so, we can't retire this TD yes
						// 1 - this is a splitTD
						// 2 - the TD wraps around (useBackPtr == true)
						// 3 - the slot after this one is the curslot
						// 4 - we have not gotten to microframe 2 of the curSlot
						if (splitTD && (splitTD->_pEndpoint->useBackPtr) && (nextSlot == curSlot) && (curMicroFrame < 2))
						{
							prevThing = thing;
							thing = nextThing;
							needToRescavenge = true;
							continue;
						}
						
						// need to unlink this TD
						if (!prevThing)
						{
							_logicalPeriodicList[testSlot] = nextThing;
							_periodicList[testSlot] = thing->GetPhysicalLink();
						}
						else
						{
							prevThing->_logicalNext = nextThing;
							prevThing->SetPhysicalLink(thing->GetPhysicalLink());
						}
						
						if (isochEl->_lowLatency)
							isochEl->UpdateFrameList(timeStamp);
						// place this guy on the backward done queue
						// the reason that we do not use the _logicalNext link is that the done queue is not a null terminated list
						// and the element linked "last" in the list might not be a true link - trust me
						isochEl->_doneQueueLink = cachedHead;
						cachedHead = isochEl;
						cachedProducer++;
						if (isochEl->_pEndpoint)
						{
							isochEl->_pEndpoint->onProducerQ++;
							isochEl->_pEndpoint->scheduledTDs--;
						}
						
						thing = nextThing;
					}
					testSlot = nextSlot;
					if (!needToRescavenge)
						_outSlot = testSlot;
				}
				IOSimpleLockLock( _wdhLock );
				
				_savedDoneQueueHead = cachedHead;	// updates the shadow head
				_producerCount = cachedProducer;	// Validates _producerCount;
				
				IOSimpleLockUnlock( _wdhLock );
			}
		}
    }
	
    // We will return false from this filter routine, but will indicate that there the action routine should be called by calling _filterInterruptSource->signalInterrupt(). 
    // This is needed because IOKit will disable interrupts for a level interrupt after the filter interrupt is run, until the action interrupt is called.  We want to be
    // able to have our filter interrupt routine called before the action routine runs, if needed.  That is what will enable low latency isoch transfers to work, as when the
    // system is under heavy load, the action routine can be delayed for tens of ms.
    //
    if (needSignal)
		_filterInterruptSource->signalInterrupt();
    
    return false;
}


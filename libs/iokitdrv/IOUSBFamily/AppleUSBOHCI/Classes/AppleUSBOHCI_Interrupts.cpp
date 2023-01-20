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

#include <IOKit/IOService.h>
#include <IOKit/usb/IOUSBLog.h>
#include <IOKit/usb/IOUSBRootHubDevice.h>

#include "AppleUSBOHCIMemoryBlocks.h"
#include "AppleUSBOHCI.h"

#define nil (0)
#define DEBUGGING_LEVEL 0	// 1 = low; 2 = high; 3 = extreme

#define super IOUSBController
#define self this


void AppleUSBOHCI::PollInterrupts(IOUSBCompletionAction safeAction)
{
    UInt64				timeElapsed;
	AbsoluteTime		timeStop;
    IOReturn            err = kIOReturnSuccess;
    
	// Calculate the time between the filter interrupt and the workloop dispatching
	//
	/*
	 clock_get_uptime (&timeStop);
	 SUB_ABSOLUTETIME(&timeStop, &_filterTimeStamp); 
	 absolutetime_to_nanoseconds(timeStop, &timeElapsed); 
	 USBLog(5,"%s[%p]::PollInterrupts:  microsecs since filter interrupt:  %qd", getName(), this, timeElapsed / 1000);
	 */
	
    // WritebackDoneHead Interrupt
    //
    if (_writeDoneHeadInterrupt & kOHCIHcInterrupt_WDH)
    {
        _writeDoneHeadInterrupt = 0;
        UIMProcessDoneQueue(safeAction);
    }
	
    // ResumeDetected Interrupt
    //
    if (_resumeDetectedInterrupt & kOHCIHcInterrupt_RD)
    {
        _resumeDetectedInterrupt = 0;
		
        //setPowerState(1, self);
        _remote_wakeup_occurred = true; //needed by ::callPlatformFunction()
		
        USBLog(3,"%s[%p] ResumeDetected Interrupt on bus %d", getName(), this, _busNumber );
        if ( _idleSuspend )
            setPowerState(kOHCISetPowerLevelRunning, self);
    }
	
    // Unrecoverable Error Interrupt
    //
    if (_unrecoverableErrorInterrupt & kOHCIHcInterrupt_UE)
    {
        USBError(1,"USB Controller on bus %d received and unrecoverable error interrupt.  Attempting to recover (%d,%d,%d)", _busNumber,_onCardBus, _pcCardEjected, isInactive() );
        _unrecoverableErrorInterrupt = 0;
		
        _errors.unrecoverableError++;
        
		if ( _onCardBus )
		{
			USBError(1,"Ignoring unrecoverable error on PC Card" );
		}
		else
		{
			if ( !(_errataBits & kErrataNECOHCIIsochWraparound ) )
			{
				// Let's do a SW reset to recover from this condition.
				// We could make sure all OCHI registers and in-memory
				// data structures are valid, too.
				_pOHCIRegisters->hcCommandStatus = HostToUSBLong(kOHCIHcCommandStatus_HCR);
				delay(10 * MICROSECOND);
				_pOHCIRegisters->hcControl = HostToUSBLong((kOHCIFunctionalState_Operational << kOHCIHcControl_HCFSPhase) | kOHCIHcControl_PLE);
			}
			else
			{
				// For NEC controllers, we unload all drivers
				//
				if ( _rootHubDevice )
				{
					_rootHubDevice->terminate(kIOServiceRequired | kIOServiceSynchronous);
					_rootHubDevice->detachAll(gIOUSBPlane);
					_rootHubDevice->release();
					_rootHubDevice = NULL;
				}
				SuspendUSBBus();
				UIMFinalizeForPowerDown();
				_ohciAvailable = false;									// tell the interrupt filter routine that we are off
				
				IOSleep(100);
				UIMInitializeForPowerUp();
				
				_ohciAvailable = true;                          // tell the interrupt filter routine that we are on
				_ohciBusState = kOHCIBusStateRunning;
				if ( _rootHubDevice == NULL )
				{
					err = CreateRootHubDevice( _device, &_rootHubDevice );
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
		}
    }
	
    //	RootHubStatusChange Interrupt
    //
    if (_rootHubStatusChangeInterrupt & kOHCIHcInterrupt_RHSC)
    {
        
        _rootHubStatusChangeInterrupt = 0;
        _remote_wakeup_occurred = true;						//needed by ::callPlatformFunction()
		
        USBLog(3,"%s[%p] RootHub Status Change Interrupt on bus %d", getName(), this, _busNumber );
		
        UIMRootHubStatusChange( false );
        LastRootHubPortStatusChanged ( true );
		
        // We let the RootHub driver enable this interrupt once it gets another interrupt read
        //
    }
}



void 
AppleUSBOHCI::InterruptHandler(OSObject *owner, IOInterruptEventSource * /*source*/, int /*count*/)
{
    register AppleUSBOHCI		*controller = (AppleUSBOHCI *) owner;
	
    if (!controller || controller->isInactive() || (controller->_onCardBus && controller->_pcCardEjected) || !controller->_ohciAvailable)
        return;
	
    // Finish pending transactions first.
    //
    controller->finishPending();
    controller->PollInterrupts();
    controller->_filterInterruptCount = 0;
    
}



// This routine will get called at Primary interrupt time.  When we are interrupted the host controller
// has already written the HCDoneHead register to the HCCADoneHeadRegister.  Furthermore, the host controller
// will NOT update the HCCADoneHeadRegister again until we clear the WDH (WritebackDoneHead) bit of the 
// HCInterruptStatus register.  At Filter Interrupt time (hardware interrupt) we will NOT clear that bit so that
// the Action Interrupt ( secondary interrupt) can fire and it will then clear the bit.
//
// At primary interrupt time we are only concerned with updating the frStatus and frActCount fields of the frames
// in low latency isoch TD's.  We will traverse the done queue (pointed by the HCCADoneHeadRegister) and look for those 
// TD and update the frStatus and frActCount fields just like is done in the ProcessCompletedITD routine.
//
// The Done Queue has physical addresses.  We need to traverse the queue using logical addresses, so we need to do
// a lookup of the logical address from the physical address. 
//
bool 
AppleUSBOHCI::PrimaryInterruptFilter(OSObject *owner, IOFilterInterruptEventSource *source)
{
	register AppleUSBOHCI *controller = (AppleUSBOHCI *)owner;
	bool result = true;
	
	// If we our controller has gone away, or it's going away, or if we're on a PC Card and we have been ejected,
	// then don't process this interrupt.
	//
	if (!controller || controller->isInactive() || (controller->_onCardBus && controller->_pcCardEjected) || !controller->_ohciAvailable)
		return false;
	
	// Process this interrupt
	//
	result = controller->FilterInterrupt(0);
	return result;
}


//================================================================================================
//
//  IsValidPhysicalAddress()
//
//  This routine will search for the incoming physical address in our GTD and ITD Memory Blocks.  This
//  is used to verify that the address is one that we "know" about before we actually try to read from
//  it to get the logical address (that is stored at the beginning of the memory blocks).
//
//  Note that the comparison is making use of the fact that we allocate our memory blocks in kOHCIPageSize
//  chunks, so we only need to compare the page #'s to see if they are equal.  We are assuming that the
//  incoming address is the address of an OHCI page (lower 12 bits are 0).
//
//================================================================================================
//
bool
AppleUSBOHCI::IsValidPhysicalAddress(IOPhysicalAddress pageAddr)
{
	AppleUSBOHCIitdMemoryBlock 	*itdMemBlock = _itdMBHead;
	AppleUSBOHCIgtdMemoryBlock 	*gtdMemBlock = _gtdMBHead;
	
	while (gtdMemBlock)
	{
		if ( pageAddr == (gtdMemBlock->GetSharedPhysicalPtr(0) & kOHCIPageMask) )
												return true;
		gtdMemBlock = gtdMemBlock->GetNextBlock();
	}
	
	while (itdMemBlock)
	{
		if ( pageAddr == (itdMemBlock->GetSharedPhysicalPtr(0) & kOHCIPageMask) )
												return true;
		itdMemBlock = itdMemBlock->GetNextBlock();
	}
	return false;
}


bool 
AppleUSBOHCI::FilterInterrupt(int index)
{
	
	register UInt32				activeInterrupts;
	register UInt32				enabledInterrupts;
	IOPhysicalAddress				physicalAddress;
	AppleOHCIGeneralTransferDescriptorPtr 	pHCDoneTD = NULL;
	AppleOHCIGeneralTransferDescriptorPtr	nextTD = NULL, prevTD = NULL;
	AbsoluteTime				timeStamp;
	UInt32					numberOfTDs = 0;
	IOPhysicalAddress				oldHead;
	IOPhysicalAddress				cachedHead;
	UInt32					cachedProducer;
	Boolean					needSecondary = false;
	
	
	// Check if the OHCI has written the DoneHead yet.  First we get the list of
	// active enabled interrupts and we make sure that the master interrupts bit
	// is enabled and that we do have an interrupt to process. 
	//
	enabledInterrupts = USBToHostLong(_pOHCIRegisters->hcInterruptEnable);
	activeInterrupts = enabledInterrupts & USBToHostLong(_pOHCIRegisters->hcInterruptStatus);
	
	if ((enabledInterrupts & kOHCIHcInterrupt_MIE) && (activeInterrupts != 0))
	{
		
		// One of our 8 interrupts fired.  Need to see which one it is
		//
		
		// Frame Number Overflow
		//
		if (activeInterrupts & kOHCIHcInterrupt_FNO)
		{
			// not really an error, but close enough
			//
			_errors.frameNumberOverflow++;
			
			if ( (USBToHostWord(*(UInt16*)(_pHCCA + kHCCAFrameNumberOffset)) & kOHCIFmNumberMask) < kOHCIBit15 )
				_frameNumber += kOHCIFrameOverflowBit;
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_FNO);
			IOSync();
			if (_errataBits & kErrataNECIncompleteWrite)
			{
				UInt32		newValue = 0, count = 0;
				newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);			// this bit SHOULD now be cleared
				while ((count++ < 10) && (newValue & kOHCIHcInterrupt_FNO))
				{
					// can't log in the FilterInterrupt routine
					// USBError(1, "OHCI driver: UIMInitializeForPowerUp - DRWE bit not sticking. Retrying.");
					_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_FNO);
					IOSync();
					newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);
				}
			}
		}
		
		// SchedulingOverrun Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_SO)
		{
			_errors.scheduleOverrun++;
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_SO);
			IOSync();
		}
		
		// StartofFrame Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_SF)
		{
			// Clear the interrrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_SF);
			IOSync();
			
			// and mask it off so it doesn't happen again.
			// will have to be turned on manually to happen again.
			//
			_pOHCIRegisters->hcInterruptDisable = HostToUSBLong(kOHCIHcInterrupt_SF);
			IOSync();
												
		}
		
		// OwnershipChange Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_OC)
		{
			// well, we certainly weren't expecting this!
			_errors.ownershipChange++;
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_OC);
			IOSync();
												
		}
		
		// RootHub Status Change Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_RHSC)
		{
			// Set the shadow field that will tell the secondary interrput that we had an RHSC
			// Interrupt event
			//
			_rootHubStatusChangeInterrupt = kOHCIHcInterrupt_RHSC;
			
			// disable the RHSC interrupt until we process it at secondary interrupt
			// time. some controllers do not respond to the clear bit
			_pOHCIRegisters->hcInterruptDisable = HostToUSBLong(kOHCIHcInterrupt_RHSC);
			IOSync();
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_RHSC);
			IOSync();
			if (_errataBits & kErrataNECIncompleteWrite)
			{
				UInt32		newValue = 0, count = 0;
				newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);			// this bit SHOULD now be cleared
				while ((count++ < 10) && (newValue & kOHCIHcInterrupt_RHSC))
				{
					// can't log in the FilterInterrupt routine
					// USBError(1, "OHCI driver: UIMInitializeForPowerUp - DRWE bit not sticking. Retrying.");
					_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_RHSC);
					IOSync();
					newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);
				}
			}
			needSecondary = true;
		}
		
		// Unrecoverable Error Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_UE)
		{
			_errors.unrecoverableError++;
			
			// Set the shadow field that will tell the secondary interrput that we had an RHSC
			// Interrupt event
			//
			_unrecoverableErrorInterrupt = kOHCIHcInterrupt_UE;
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_UE);
			IOSync();
			needSecondary = true;
		}
		
		// Resume Detected Interrupt
		//
		if (activeInterrupts & kOHCIHcInterrupt_RD)
		{
			// Set the shadow field that will tell the secondary interrput that we had an RD
			// Interrupt event
			//
			_resumeDetectedInterrupt = kOHCIHcInterrupt_RD;
			
			// Clear the interrupt
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_RD);
			IOSync();
			if (_errataBits & kErrataNECIncompleteWrite)
			{
				UInt32		newValue = 0, count = 0;
				newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);			// this bit SHOULD now be cleared
				while ((count++ < 10) && (newValue & kOHCIHcInterrupt_RD))
				{
					// can't log in the FilterInterrupt routine
					_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_RD);
					IOSync();
					newValue = USBToHostLong(_pOHCIRegisters->hcInterruptStatus);
				}
			}
			needSecondary = true;
		}
		
		// Check to see if the WriteDoneHead interrupt fired.  If so, then we can look at the queue
		//
		if (activeInterrupts & kOHCIHcInterrupt_WDH)
		{
			// Now that we have the beginning of the queue, walk it looking for low latency isoch TD's
			// Use this time as the time stamp time for all the TD's that we processed.  
			//
			clock_get_uptime(&timeStamp);
			
			// Debugging aid to keep track of how long we take in between calls to the filter routine
			//
			/*
			 _filterInterruptCount++;
			 _filterTimeStamp2 = timeStamp;
			 SUB_ABSOLUTETIME(&_filterTimeStamp2, &_filterTimeStamp); 
			 _filterTimeStamp = timeStamp;
			 */
			
			// Get the pointer to the list (physical address)
			//
			physicalAddress = (UInt32) USBToHostLong(*(UInt32 *)(_pHCCA + kHCCADoneHeadOffset));
			
			// Mask off interrupt bits
			//
			physicalAddress &= kOHCIHeadPMask;
			
			// Save the current value of the shadow queue head so that we can link our new head
			// to it later on.
			//
			oldHead = _savedDoneQueueHead; 
			
			// And save the current head
			//
			cachedHead = physicalAddress;
		
#ifndef L4IOKIT
			if ( physicalAddress == NULL )
#else
			if ( physicalAddress )
#endif
				pHCDoneTD = NULL;
			else
			{
				if ( _onCardBus )
				{
					if (!IsValidPhysicalAddress( physicalAddress & kOHCIPageMask) )
					{
						USBLog(1, "Bad phys addr #1 %p", physicalAddress);
						pHCDoneTD = NULL;
					}
					else
					{
						pHCDoneTD = AppleUSBOHCIgtdMemoryBlock::GetGTDFromPhysical(physicalAddress);
					}
				}
				else
				{
					// Now get the logical address from the physical one
					//
					pHCDoneTD = AppleUSBOHCIgtdMemoryBlock::GetGTDFromPhysical(physicalAddress);
				}
			}
			
			
			// write to 0 to the HCCA DoneHead ptr so we won't look at it anymore.
			//
			*(UInt32 *)(_pHCCA + kHCCADoneHeadOffset) = 0L;
			
			// Since we have a copy of the queue to process, we can let the host update it again.  We 
			// do this by writing one to the bit in the register.
			//
			_pOHCIRegisters->hcInterruptStatus = HostToUSBLong(kOHCIHcInterrupt_WDH);
			IOSync();
			
			_writeDoneHeadInterrupt = kOHCIHcInterrupt_WDH;
			
			prevTD = NULL;
			
			while (pHCDoneTD != NULL)
			{
				AppleOHCIIsochTransferDescriptorPtr	pITD;
				IOUSBLowLatencyIsocFrame *		pFrames;
				IOReturn 				errStatus;
				UInt32					control;
				UInt32					transferStatus;
				UInt32					frameCount;
				UInt32					i;
				
				// Increment our count of the number of TDs that this queue head is pointing to
				//
				numberOfTDs++;
				
				// Find the next one
				//
				physicalAddress = USBToHostLong(pHCDoneTD->pShared->nextTD) & kOHCIHeadPMask;
			
#ifndef L4IOKIT	
				if ( physicalAddress == NULL )
#else
				if ( physicalAddress )
#endif
					nextTD = NULL;
				else
				{
					if ( _onCardBus )
					{
						if (!IsValidPhysicalAddress( physicalAddress & kOHCIPageMask) )
						{
							nextTD = NULL;
						}
						else
							nextTD = AppleUSBOHCIgtdMemoryBlock::GetGTDFromPhysical(physicalAddress);
					}
					else
						nextTD = AppleUSBOHCIgtdMemoryBlock::GetGTDFromPhysical(physicalAddress);
				}
				
				if ( (pHCDoneTD->pType == kOHCIIsochronousInLowLatencyType) || 
					 (pHCDoneTD->pType == kOHCIIsochronousOutLowLatencyType) )
				{
					// We have a low latency isoch TD.  Update debugging stamps
					//
					_lowLatencyIsochTDsProcessed++;
					
					// Since we know it's an ITD, cast it into one and get a pointer to the Low Latency ITD's frames
					//
					pITD = (AppleOHCIIsochTransferDescriptorPtr) pHCDoneTD;
					pFrames = (IOUSBLowLatencyIsocFrame *) pITD->pIsocFrame;
					
					// Get any errors from the TD
					//
					control = USBToHostLong(pHCDoneTD->pShared->ohciFlags);
					transferStatus = (control & kOHCIGTDControl_CC) >> kOHCIGTDControl_CCPhase;
					errStatus = TranslateStatusToUSBError(transferStatus);
					
					// Process the frames in the low latency isochTDs
					//
					frameCount = (USBToHostLong(pITD->pShared->flags) & kOHCIITDControl_FC) >> kOHCIITDControl_FCPhase;
					for (i = 0; i <= frameCount; i++)
					{
						// Debugging stamps
						//
						_framesUpdated++;
						if ( pFrames[pITD->frameNum + i].frStatus != (IOReturn) kUSBLowLatencyIsochTransferKey )
							_framesError++;
						
						// Set the time stamp
						//
						pFrames[pITD->frameNum + i].frTimeStamp = timeStamp;
						
						// Get information on whether there was an error in the frame
						//
						UInt16 offset = USBToHostWord(pITD->pShared->offset[i]);
						
						if ( ((offset & kOHCIITDOffset_CC) >> kOHCIITDOffset_CCPhase) == kOHCIITDOffsetConditionNotAccessed)
						{
							// If the condition code is not accessed, set the frActCount to 0 and the status accordingly
							//
							pFrames[pITD->frameNum + i].frActCount = 0;
							pFrames[pITD->frameNum + i].frStatus = TranslateStatusToUSBError(kOHCIITDConditionNotAccessedReturn);
						}
						else
						{
							// Set the frStatus to the OHCI Condition code translated to the correct USB Error
							//
							pFrames[pITD->frameNum + i].frStatus = TranslateStatusToUSBError( (offset & kOHCIITDPSW_CC) >> kOHCIITDPSW_CCPhase);
							
							// Successful isoch transmit sets the size field to requested count,
							// successful receive sets size to actual packet size received
							//
							if((kIOReturnSuccess == pFrames[pITD->frameNum + i].frStatus) && (pITD->pType == kOHCIIsochronousOutLowLatencyType))
								pFrames[pITD->frameNum + i].frActCount = pFrames[pITD->frameNum + i].frReqCount;
							else
								pFrames[pITD->frameNum + i].frActCount = offset & kOHCIITDPSW_Size;
						}
						
					}
				} 
				else
				{
					if ( (pHCDoneTD->pType != kOHCIIsochronousInType) && 
						 (pHCDoneTD->pType != kOHCIIsochronousOutType) )
					{
						// Time stamp this TD (non isoch  TD)
						//
						pHCDoneTD->command->SetTimeStamp( timeStamp );
					}
				}
				
				prevTD = pHCDoneTD;
				
				// Look at the next TD
				pHCDoneTD = nextTD;	/* New qHead */
			}
			
			// We have now processed all the TD's in this queue.  We need to update our producer count
			//
			cachedProducer = _producerCount;
			cachedProducer += numberOfTDs;
			
			// Now link in to the old queue head.  Note that we have to write this in bus order as the
			// secondary interrupt routine will do the opposite when it reverses the list
			//
			if ( prevTD != NULL )
				prevTD->pShared->nextTD = HostToUSBLong(oldHead);
			
			// Now, update the producer and head. We need to take a lock so that the consumer (the action routine) does not read them
			// while they are in transition.
			//
			IOSimpleLockLock( _wdhLock );
			
			_savedDoneQueueHead = cachedHead;	// updates the shadow head
			_producerCount = cachedProducer;	// Validates _producerCount;
			
			IOSimpleLockUnlock( _wdhLock );
			needSecondary = true;
		}
	}
	
	
	// We will return false from this filter routine, but will indicate that there the action routine should be called by calling _filterInterruptSource->signalInterrupt(). 
	// This is needed because IOKit will disable interrupts for a level interrupt after the filter interrupt is run, until the action interrupt is called.  We want to be
	// able to have our filter interrupt routine called before the action routine runs, if needed.  That is what will enable low latency isoch transfers to work, as when the
	// system is under heavy load, the action routine can be delayed for tens of ms.
	//
	if (needSecondary)
		_filterInterruptSource->signalInterrupt();
	
	return false;
	
}

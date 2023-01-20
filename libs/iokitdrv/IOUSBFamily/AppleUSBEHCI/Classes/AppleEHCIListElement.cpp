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

#include <IOKit/usb/IOUSBLog.h>

#include "AppleEHCIListElement.h"

#define super OSObject
// -----------------------------------------------------------------
//		AppleEHCIListElement
// -----------------------------------------------------------------
OSDefineMetaClass( AppleEHCIListElement, OSObject )
OSDefineAbstractStructors(AppleEHCIListElement, OSObject)

void
AppleEHCIListElement::print(int level)
{
    USBLog(level, "AppleEHCIListElement[%p]::print - _sharedPhysical[%x]", this, (unsigned int)_sharedPhysical);
    USBLog(level, "AppleEHCIListElement::print - _sharedLogical[%x]", (unsigned int)_sharedLogical);
    USBLog(level, "AppleEHCIListElement::print - _logicalNext[%x]", (unsigned int)_logicalNext);
}


#undef super
#define super AppleEHCIListElement
// -----------------------------------------------------------------
//		AppleEHCIQueueHead
// -----------------------------------------------------------------
OSDefineMetaClassAndStructors(AppleEHCIQueueHead, AppleEHCIListElement);

AppleEHCIQueueHead *
AppleEHCIQueueHead::WithSharedMemory(EHCIQueueHeadSharedPtr sharedLogical, IOPhysicalAddress sharedPhysical)
{
    AppleEHCIQueueHead *me = new AppleEHCIQueueHead;
    if (!me || !me->init())
		return NULL;
    me->_sharedLogical = sharedLogical;
    me->_sharedPhysical = sharedPhysical;
    return me;
}


EHCIQueueHeadSharedPtr		
AppleEHCIQueueHead::GetSharedLogical(void)
{
    return (EHCIQueueHeadSharedPtr)_sharedLogical;
}


void 
AppleEHCIQueueHead::SetPhysicalLink(IOPhysicalAddress next)
{
    GetSharedLogical()->nextQH = next;
}


IOPhysicalAddress
AppleEHCIQueueHead::GetPhysicalLink(void)
{
    return GetSharedLogical()->nextQH;
}


IOPhysicalAddress 
AppleEHCIQueueHead::GetPhysicalAddrWithType(void)
{
    return _sharedPhysical | (kEHCITyp_QH << kEHCIEDNextED_TypPhase);
}

void
AppleEHCIQueueHead::print(int level)
{
    EHCIQueueHeadSharedPtr shared = GetSharedLogical();
	
    super::print(level);
    USBLog(level, "AppleEHCIQueueHead::print - shared.nextQH[%p]", (void*)USBToHostLong(shared->nextQH));
    USBLog(level, "AppleEHCIQueueHead::print - shared.flags[%p]", (void*)USBToHostLong(shared->flags));
    USBLog(level, "AppleEHCIQueueHead::print - shared.splitFlags[%p]", (void*)USBToHostLong(shared->splitFlags));
    USBLog(level, "AppleEHCIQueueHead::print - shared.CurrqTDPtr[%p]", (void*)USBToHostLong(shared->CurrqTDPtr));
    USBLog(level, "AppleEHCIQueueHead::print - shared.NextqTDPtr[%p]", (void*)USBToHostLong(shared->NextqTDPtr));
    USBLog(level, "AppleEHCIQueueHead::print - shared.AltqTDPtr[%p]", (void*)USBToHostLong(shared->AltqTDPtr));
    USBLog(level, "AppleEHCIQueueHead::print - shared.qTDFlags[%p]", (void*)USBToHostLong(shared->qTDFlags));
    USBLog(level, "AppleEHCIQueueHead::print - shared.BuffPtr[0][%p]", (void*)USBToHostLong(shared->BuffPtr[0]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.BuffPtr[1][%p]", (void*)USBToHostLong(shared->BuffPtr[1]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.BuffPtr[2][%p]", (void*)USBToHostLong(shared->BuffPtr[2]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.BuffPtr[3][%p]", (void*)USBToHostLong(shared->BuffPtr[3]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.BuffPtr[4][%p]", (void*)USBToHostLong(shared->BuffPtr[4]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.extBuffPtr[0][%p]", (void*)USBToHostLong(shared->extBuffPtr[0]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.extBuffPtr[1][%p]", (void*)USBToHostLong(shared->extBuffPtr[1]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.extBuffPtr[2][%p]", (void*)USBToHostLong(shared->extBuffPtr[2]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.extBuffPtr[3][%p]", (void*)USBToHostLong(shared->extBuffPtr[3]));
    USBLog(level, "AppleEHCIQueueHead::print - shared.extBuffPtr[4][%p]", (void*)USBToHostLong(shared->extBuffPtr[4]));
}


// -----------------------------------------------------------------
//		AppleEHCIIsochListElement
// -----------------------------------------------------------------
OSDefineMetaClass( AppleEHCIIsochListElement, AppleEHCIListElement )
OSDefineAbstractStructors(AppleEHCIIsochListElement, AppleEHCIListElement)

void
AppleEHCIIsochListElement::print(int level)
{
    super::print(level);
    USBLog(level, "AppleEHCIIsochListElement::print - _pEndpoint[%p]", _pEndpoint);
    USBLog(level, "AppleEHCIIsochListElement::print - _pFrames[%p]", _pFrames);
    USBLog(level, "AppleEHCIIsochListElement::print - completion[%p, %p, %p]", _completion.action, _completion.target, _completion.parameter);
    USBLog(level, "AppleEHCIIsochListElement::print - _lowLatency[%x]", _lowLatency);
    USBLog(level, "AppleEHCIIsochListElement::print - frameNumber[0x%x]", _frameNumber);
}


#undef super
#define super AppleEHCIIsochListElement
// -----------------------------------------------------------------
//		AppleEHCIIsochTransferDescriptor
// -----------------------------------------------------------------
OSDefineMetaClassAndStructors(AppleEHCIIsochTransferDescriptor, AppleEHCIIsochListElement);

AppleEHCIIsochTransferDescriptor *
AppleEHCIIsochTransferDescriptor::WithSharedMemory(EHCIIsochTransferDescriptorSharedPtr sharedLogical, IOPhysicalAddress sharedPhysical)
{
    AppleEHCIIsochTransferDescriptor *me = new AppleEHCIIsochTransferDescriptor;
    if (!me || !me->init())
		return NULL;
    me->_sharedLogical = sharedLogical;
    me->_sharedPhysical = sharedPhysical;
    return me;
}


EHCIIsochTransferDescriptorSharedPtr		
AppleEHCIIsochTransferDescriptor::GetSharedLogical(void)
{
    return (EHCIIsochTransferDescriptorSharedPtr)_sharedLogical;
}


void 
AppleEHCIIsochTransferDescriptor::SetPhysicalLink(IOPhysicalAddress next)
{
    GetSharedLogical()->nextiTD = next;
}


IOPhysicalAddress
AppleEHCIIsochTransferDescriptor::GetPhysicalLink(void)
{
    return GetSharedLogical()->nextiTD;
}


IOPhysicalAddress 
AppleEHCIIsochTransferDescriptor::GetPhysicalAddrWithType(void)
{
    return _sharedPhysical | (kEHCITyp_iTD << kEHCIEDNextED_TypPhase);
}


IOReturn 
AppleEHCIIsochTransferDescriptor::mungeEHCIStatus(UInt32 status, UInt16 *transferLen, UInt32 maxPacketSize, UInt8 direction)
{
	/*  This is how I'm unmangling the EHCI error status 
	
	iTD has these possible status bits:
	
	31 Active.							- If Active, then not accessed.
	30 Data Buffer Error.				- Host data buffer under (out) over (in) run error
	29 Babble Detected.                 - Recevied data overrun
	28 Transaction Error (XactErr).	    - Everything else. Use not responding.
	
	if(active) kIOUSBNotSent1Err
	else if(DBE) if(out)kIOUSBBufferUnderrunErr else kIOUSBBufferOverrunErr
	else if(babble) kIOReturnOverrun
	else if(Xacterr) kIOReturnNotResponding
	else if(in) if(length < maxpacketsize) kIOReturnUnderrun
	else
	kIOReturnSuccess
	*/
	if((status & (kEHCI_ITDStatus_Active | kEHCI_ITDStatus_BuffErr | kEHCI_ITDStatus_Babble)) == 0)
	{
		if (((status & kEHCI_ITDStatus_XactErr) == 0) || (direction == kUSBIn))
		{
			// Isoch IN transactions can set the Xact_Err bit when the device sent the wrong PID (DATA2/1/0)
			// for the amount of data sent. For example, a device based on the Cypress EZ-USB FX2 chip set can send up 
			// to 3072 bytes per microframe (DATA2=1024, DATA1=1024, DATA0=1024). But if the device only has 1024 bytes
			// on a particular microframe, it sends it with a DATA2 PID. It then ignores the subsequent
			// IN PID - which it should not do, and which is a XactERR in the controller. However
			// the first 1024 bytes was transferred correctly, so we need to count that as an Underrun instead
			// of the XActErr. So this works around a bug in that Cypress chip set. (3915817)
			*transferLen = (status & kEHCI_ITDTr_Len) >> kEHCI_ITDTr_LenPhase;
			if( (direction == kUSBIn) && (maxPacketSize != *transferLen) )
			{
				return(kIOReturnUnderrun);
			}
			return(kIOReturnSuccess);
		}
	}
	*transferLen = 0;
	
	if( (status & kEHCI_ITDStatus_Active) != 0)
	{
		return(kIOUSBNotSent1Err);
	}
	else if( (status & kEHCI_ITDStatus_BuffErr) != 0)
	{
		if(direction == kUSBOut)
		{
			return(kIOUSBBufferUnderrunErr);
		}
		else
		{
			return(kIOUSBBufferOverrunErr);
		}
	}
	else if( (status & kEHCI_ITDStatus_Babble) != 0)
	{
		return(kIOReturnOverrun);
	}
	else // if( (status & kEHCI_ITDStatus_XactErr) != 0)
	{
		return(kIOReturnNotResponding);
	}
}


IOReturn
AppleEHCIIsochTransferDescriptor::UpdateFrameList(AbsoluteTime timeStamp)
{
	// Do not use any USBLogs in this routine, as it's called from Filter Interrupt time
	//
    UInt32							*TransactionP, statusWord;
    IOUSBIsocFrame					*pFrames;    
    IOUSBLowLatencyIsocFrame		*pLLFrames;    
    IOReturn						ret, frStatus;
    int								i;
	UInt16							*pActCount;
	UInt8							framesInTD;
	
    ret = _pEndpoint->accumulatedStatus;
	
    TransactionP = &GetSharedLogical()->Transaction0;
    pFrames = _pFrames;
	framesInTD = _framesInTD;
	if (!pFrames || !framesInTD)							// this will be the case for the dummy TD
		return kIOReturnSuccess;
	
    pLLFrames = (IOUSBLowLatencyIsocFrame*)_pFrames;
    for(i=0; i < 8; i+= _pEndpoint->interval)
    {
		if (!framesInTD)
			break;
		
	    statusWord = USBToHostLong(*(TransactionP++));
		if (_lowLatency)
			pActCount = &(pLLFrames[i].frActCount);
		else
			pActCount = &(pFrames[i].frActCount);
		
	    frStatus = mungeEHCIStatus(statusWord, pActCount,  _pEndpoint->maxPacketSize,  _pEndpoint->direction);

	    if(frStatus != kIOReturnSuccess)
	    {
		    if(frStatus != kIOReturnUnderrun)
		    {
			    ret = frStatus;
		    }
		    else if(ret == kIOReturnSuccess)
		    {
			    ret = kIOReturnUnderrun;
		    }
	    }
	    if(_lowLatency)
	    {
		    pLLFrames[i].frStatus = frStatus;
			pLLFrames[i].frTimeStamp = timeStamp;
	    }
	    else
	    {
		    pFrames[i].frStatus = frStatus;
	    }
		framesInTD--;
    }
    _pEndpoint->accumulatedStatus = ret;
    return ret;
}



IOReturn
AppleEHCIIsochTransferDescriptor::Deallocate(AppleUSBEHCI *uim)
{
    return uim->DeallocateITD(this);
}


void
AppleEHCIIsochTransferDescriptor::print(int level)
{
    EHCIIsochTransferDescriptorSharedPtr shared = GetSharedLogical();
    
    super::print(level);
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.nextiTD[%x]", USBToHostLong(shared->nextiTD));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction0[%x]", USBToHostLong(shared->Transaction0));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction1[%x]", USBToHostLong(shared->Transaction1));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction2[%x]", USBToHostLong(shared->Transaction2));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction3[%x]", USBToHostLong(shared->Transaction3));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction4[%x]", USBToHostLong(shared->Transaction4));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction5[%x]", USBToHostLong(shared->Transaction5));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction6[%x]", USBToHostLong(shared->Transaction6));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.Transaction7[%x]", USBToHostLong(shared->Transaction7));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage0[%x]", USBToHostLong(shared->bufferPage0));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage1[%x]", USBToHostLong(shared->bufferPage1));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage2[%x]", USBToHostLong(shared->bufferPage2));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage3[%x]", USBToHostLong(shared->bufferPage3));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage4[%x]", USBToHostLong(shared->bufferPage4));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage5[%x]", USBToHostLong(shared->bufferPage5));
    USBLog(level, "AppleEHCIIsochTransferDescriptor::print - shared.bufferPage6[%x]", USBToHostLong(shared->bufferPage6));
}


// -----------------------------------------------------------------
//		AppleEHCISplitIsochTransferDescriptor
// -----------------------------------------------------------------
OSDefineMetaClassAndStructors(AppleEHCISplitIsochTransferDescriptor, AppleEHCIIsochListElement);
AppleEHCISplitIsochTransferDescriptor *
AppleEHCISplitIsochTransferDescriptor::WithSharedMemory(EHCISplitIsochTransferDescriptorSharedPtr sharedLogical, IOPhysicalAddress sharedPhysical)
{
    AppleEHCISplitIsochTransferDescriptor *me = new AppleEHCISplitIsochTransferDescriptor;
    if (!me || !me->init())
		return NULL;
    me->_sharedLogical = sharedLogical;
    me->_sharedPhysical = sharedPhysical;
    return me;
}

EHCISplitIsochTransferDescriptorSharedPtr		
AppleEHCISplitIsochTransferDescriptor::GetSharedLogical(void)
{
    return (EHCISplitIsochTransferDescriptorSharedPtr)_sharedLogical;
}


void 
AppleEHCISplitIsochTransferDescriptor::SetPhysicalLink(IOPhysicalAddress next)
{
    GetSharedLogical()->nextSITD = next;
}


IOPhysicalAddress
AppleEHCISplitIsochTransferDescriptor::GetPhysicalLink(void)
{
    return GetSharedLogical()->nextSITD;
}


IOPhysicalAddress 
AppleEHCISplitIsochTransferDescriptor::GetPhysicalAddrWithType(void)
{
    return _sharedPhysical | (kEHCITyp_siTD << kEHCIEDNextED_TypPhase);
}


IOReturn
AppleEHCISplitIsochTransferDescriptor::UpdateFrameList(AbsoluteTime timeStamp)
{
    UInt32						statFlags;
    IOUSBIsocFrame 				*pFrames;    
    IOUSBLowLatencyIsocFrame 	*pLLFrames;    
    IOReturn					frStatus = kIOReturnSuccess;
    UInt16						frActualCount = 0;
    UInt16						frReqCount;
    
    statFlags = USBToHostLong(GetSharedLogical()->statFlags);
    // warning - this method can run at primary interrupt time, which can cause a panic if it logs too much
    // USBLog(7, "AppleEHCISplitIsochTransferDescriptor[%p]::UpdateFrameList statFlags (%x)", this, statFlags);
    pFrames = _pFrames;
	if (!pFrames)							// this will be the case for the dummy TD
		return kIOReturnSuccess;
	
    pLLFrames = (IOUSBLowLatencyIsocFrame*)_pFrames;
    if (_lowLatency)
    {
		frReqCount = pLLFrames[_frameIndex].frReqCount;
    }
    else
    {
		frReqCount = pFrames[_frameIndex].frReqCount;
    }
	
    if ((statFlags & kEHCIsiTDStatStatusActive) && !_isDummySITD)
    {
		frStatus = kIOUSBNotSent2Err;
    }
    else if (statFlags & kEHCIsiTDStatStatusERR)
    {
		frStatus = kIOReturnNotResponding;
    }
    else if (statFlags & kEHCIsiTDStatStatusDBE)
    {
		if (_pEndpoint->direction == kUSBOut)
			frStatus = kIOReturnUnderrun;
		else
			frStatus = kIOReturnOverrun;
    }
    else if (statFlags & kEHCIsiTDStatStatusBabble)
    {
		frStatus = kIOReturnNotResponding;
    }
    else if (statFlags & kEHCIsiTDStatStatusXActErr)
    {
		frStatus = kIOUSBWrongPIDErr;
    }
    else if (statFlags & kEHCIsiTDStatStatusMMF)
    {
		frStatus = kIOUSBNotSent1Err;
    }
    else
    {
		frActualCount = frReqCount - ((statFlags & kEHCIsiTDStatLength) >> kEHCIsiTDStatLengthPhase);
		if (frActualCount != frReqCount)
		{
			if (_pEndpoint->direction == kUSBOut)
			{
				// warning - this method can run at primary interrupt time, which can cause a panic if it logs too much
				// USBLog(7, "AppleEHCISplitIsochTransferDescriptor[%p]::UpdateFrameList - (OUT) reqCount (%d) actCount (%d)", this, frReqCount, frActualCount);
				frStatus = kIOReturnUnderrun;
			}
			else if (_pEndpoint->direction == kUSBIn)
			{
				// warning - this method can run at primary interrupt time, which can cause a panic if it logs too much
				// USBLog(7, "AppleEHCISplitIsochTransferDescriptor[%p]::UpdateFrameList - (IN) reqCount (%d) actCount (%d)", this, frReqCount, frActualCount);
				frStatus = kIOReturnUnderrun;
			}
		}
    }
    if (_lowLatency)
    {
		pLLFrames[_frameIndex].frActCount = frActualCount;
		pLLFrames[_frameIndex].frStatus = frStatus;
		pLLFrames[_frameIndex].frTimeStamp = timeStamp;
    }
    else
    {
		pFrames[_frameIndex].frActCount = frActualCount;
		pFrames[_frameIndex].frStatus = frStatus;
    }
	
    if(frStatus != kIOReturnSuccess)
    {
		if(frStatus != kIOReturnUnderrun)
		{
			_pEndpoint->accumulatedStatus = frStatus;
		}
		else if(_pEndpoint->accumulatedStatus == kIOReturnSuccess)
		{
			_pEndpoint->accumulatedStatus = kIOReturnUnderrun;
		}
    }
	
    return frStatus;
}


IOReturn
AppleEHCISplitIsochTransferDescriptor::Deallocate(AppleUSBEHCI *uim)
{
    return uim->DeallocateSITD(this);
}


void
AppleEHCISplitIsochTransferDescriptor::print(int level)
{
    EHCISplitIsochTransferDescriptorSharedPtr shared = GetSharedLogical();
    
    super::print(level);
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.nextSITD[%x]", USBToHostLong(shared->nextSITD));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.routeFlags[%x]", USBToHostLong(shared->routeFlags));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.timeFlags[%x]", USBToHostLong(shared->timeFlags));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.statFlags[%x]", USBToHostLong(shared->statFlags));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.buffPtr0[%x]", USBToHostLong(shared->buffPtr0));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.buffPtr1[%x]", USBToHostLong(shared->buffPtr1));
    USBLog(level, "AppleEHCISplitIsochTransferDescriptor::print - shared.backPtr[%x]", USBToHostLong(shared->backPtr));
}


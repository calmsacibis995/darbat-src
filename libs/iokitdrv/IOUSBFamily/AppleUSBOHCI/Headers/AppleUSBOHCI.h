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

#ifndef _IOKIT_AppleUSBOHCI_H
#define _IOKIT_AppleUSBOHCI_H

#include <libkern/c++/OSData.h>

#include <IOKit/IOService.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOFilterInterruptEventSource.h>
#include <IOKit/pci/IOPCIBridge.h>
#include <IOKit/pci/IOPCIDevice.h>

#include <IOKit/usb/IOUSBControllerV2.h>
#include <IOKit/usb/USB.h>
#include <IOKit/usb/USBHub.h>

#include "USBOHCI.h"
#include "USBOHCIRootHub.h"

#define USB_CONSTANT16(x)	(OSSwapHostToLittleConstInt16(x))
#define MICROSECOND		(1)
#define MILLISECOND		(1000)

#ifdef __ppc__
#define IOSync eieio
#else
#define IOSync()
#endif

extern "C" {
    extern void delay(int);
};

struct InterruptTransaction {
    IOMemoryDescriptor *	buf;
    UInt32 			bufLen;
    IOUSBCompletion		completion;
};
#define kMaxOutstandingTrans 4

typedef struct AppleOHCIIntHeadStruct
                    AppleOHCIIntHead,
                    *AppleOHCIIntHeadPtr;

typedef struct AppleOHCIEndpointDescriptorStruct
		AppleOHCIEndpointDescriptor,
		*AppleOHCIEndpointDescriptorPtr;
		
typedef struct AppleOHCIGeneralTransferDescriptorStruct
		AppleOHCIGeneralTransferDescriptor,
		*AppleOHCIGeneralTransferDescriptorPtr;

typedef struct AppleOHCIIsochTransferDescriptorStruct
		AppleOHCIIsochTransferDescriptor,
		*AppleOHCIIsochTransferDescriptorPtr;

// Interrupt head struct
struct AppleOHCIIntHeadStruct
{
    AppleOHCIEndpointDescriptorPtr	pHead;
    AppleOHCIEndpointDescriptorPtr	pTail;
    IOPhysicalAddress			pHeadPhysical;
    int					nodeBandwidth;
};

struct AppleOHCIEndpointDescriptorStruct
{
    OHCIEndpointDescriptorSharedPtr	pShared;
    AppleOHCIEndpointDescriptorPtr	pLogicalNext;	
    IOPhysicalAddress			pPhysical;		
    void*				pLogicalTailP;		
    void*				pLogicalHeadP;
};

struct AppleOHCIGeneralTransferDescriptorStruct
{
    UInt16					pType;			// Note this must appear at the same offset in GTD & ITD structs
    UInt16					uimFlags;		// Note this must appear at the same offset in GTD & ITD structs
    IOPhysicalAddress				pPhysical;		// Note this must appear at the same offset in GTD & ITD structs
    AppleOHCIGeneralTransferDescriptorPtr	pLogicalNext;		// Note this must appear at the same offset in GTD & ITD structs
    OHCIGeneralTransferDescriptorSharedPtr	pShared;		// pointer to the GTD shared with the controller
    IOUSBCommand	    	  		*command;		// the command associated with this TD
    UInt32					lastFrame;		// the lower 32 bits the last time we checked this TD
    UInt32					lastRemaining;		// the "remaining" count the last time we checked
    AppleOHCIEndpointDescriptorPtr		pEndpoint;		// pointer to TD's Endpoint
    UInt32					bufferSize;		// used only by control transfers to keep track of data buffers size leftover
};

struct AppleOHCIIsochTransferDescriptorStruct
{
    UInt16					pType;		// Note this must appear at the same offset in GTD & ITD structs
    UInt16					uimFlags;	// Note this must appear at the same offset in GTD & ITD structs
    UInt32					pPhysical;	// Note this must appear at the same offset in GTD & ITD structs
    AppleOHCIIsochTransferDescriptorPtr		pLogicalNext;	// Note this must appear at the same offset in GTD & ITD structs
    OHCIIsochTransferDescriptorSharedPtr	pShared;	// pointer to the ITD shared with the controller
    IOUSBIsocCompletion  			completion;	// callback for Isoch transactions
    IOUSBIsocFrame *				pIsocFrame;	// ptr to USLs status and length array
    UInt32					frameNum;	// index to pIsocFrame array
};								// 0x40 total length



class IONaturalMemoryCursor;
class AppleUSBOHCIedMemoryBlock;
class AppleUSBOHCIitdMemoryBlock;
class AppleUSBOHCIgtdMemoryBlock;

class AppleUSBOHCI : public IOUSBControllerV2
{
    OSDeclareDefaultStructors(AppleUSBOHCI)

private:
    virtual IOReturn 		setPowerState( unsigned long, IOService* );
    virtual void 		initForPM (IOPCIDevice *provider);
    unsigned long 		maxCapabilityForDomainState ( IOPMPowerFlags domainState );
    unsigned long 		initialPowerStateForDomainState ( IOPMPowerFlags domainState );
    void			ResumeUSBBus();
    void			SuspendUSBBus();
    void print_td(AppleOHCIGeneralTransferDescriptorPtr x);
    void print_itd(AppleOHCIIsochTransferDescriptorPtr x);
    void print_ed(AppleOHCIEndpointDescriptorPtr x);
    void print_isoc_ed(AppleOHCIEndpointDescriptorPtr x);
    void					print_list(AppleOHCIEndpointDescriptorPtr pListHead, AppleOHCIEndpointDescriptorPtr pListTail);
    void print_control_list(void);
    void print_bulk_list(void);
    void print_int_list(void);
    bool IsValidPhysicalAddress(IOPhysicalAddress pageAddr);

protected:

    IOPCIDevice *      					_device;
    IOMemoryMap *					_deviceBase;
    IONaturalMemoryCursor * 				_genCursor;
    IONaturalMemoryCursor * 				_isoCursor;
    AppleOHCIGeneralTransferDescriptorPtr 		_pendingHead;
    AppleOHCIGeneralTransferDescriptorPtr		_pendingTail;
    UInt16						_vendorID;
    UInt16						_deviceID;
    UInt16						_revisionID;
    UInt32						_errataBits;		// various bits for chip erratas
    OHCIRegistersPtr					_pOHCIRegisters;	// Pointer to base address of OHCI registers.
    Ptr							_pHCCA;			// Pointer to HCCA.
    AppleOHCIIntHead					_pInterruptHead[63];	// ptr to private list of all interrupts heads 			
    volatile AppleOHCIEndpointDescriptorPtr		_pIsochHead;		// ptr to Isochronous list head
    volatile AppleOHCIEndpointDescriptorPtr		_pIsochTail;		// ptr to Isochronous list tail
    volatile AppleOHCIEndpointDescriptorPtr		_pBulkHead;		// ptr to Bulk list
    volatile AppleOHCIEndpointDescriptorPtr		_pControlHead;		// ptr to Control list
    volatile AppleOHCIEndpointDescriptorPtr		_pBulkTail;		// ptr to Bulk list
    volatile AppleOHCIEndpointDescriptorPtr		_pControlTail;		// ptr to Control list
    volatile AppleOHCIGeneralTransferDescriptorPtr	_pFreeTD;		// list of availabble Trasfer Descriptors
    volatile AppleOHCIIsochTransferDescriptorPtr		_pFreeITD;		// list of availabble Trasfer Descriptors
    volatile AppleOHCIEndpointDescriptorPtr		_pFreeED;		// list of available Endpoint Descriptors
    volatile AppleOHCIGeneralTransferDescriptorPtr	_pLastFreeTD;		// last of availabble Trasfer Descriptors
    volatile AppleOHCIIsochTransferDescriptorPtr		_pLastFreeITD;		// last of availabble Trasfer Descriptors
    volatile AppleOHCIEndpointDescriptorPtr		_pLastFreeED;		// last of available Endpoint Descriptors
    volatile AppleOHCIGeneralTransferDescriptorPtr	_pPendingTD;		// list of non processed Trasfer Descriptors
    AppleUSBOHCIedMemoryBlock*				_edMBHead;		// head of a linked list of ED memory blocks				
    AppleUSBOHCIgtdMemoryBlock*				_gtdMBHead;		// head of a linked list of GTD memory blocks				
    AppleUSBOHCIitdMemoryBlock*				_itdMBHead;		// head of a linked list of ITD memory blocks				
    UInt32						_pageSize;		// OS Logical page size
    struct  {
        volatile UInt32	scheduleOverrun;				// updated by the interrupt handler
        volatile UInt32	unrecoverableError;				// updated by the interrupt handler
        volatile UInt32	frameNumberOverflow;				// updated by the interrupt handler
        volatile UInt32	ownershipChange;				// updated by the interrupt handler
        } _errors;
    volatile UInt64					_frameNumber;
    UInt16						_rootHubFuncAddress;	// Function Address for the root hub
    int							_OptiOn;
    UInt32						_isochBandwidthAvail;	// amount of available bandwidth for Isochronous transfers
    UInt32		 				_disablePortsBitmap;	// Bitmaps of ports that support port suspend even if they have an errata
    UInt32						_dataAllocationSize;	// # of bytes allocated in for TD's
    IOFilterInterruptEventSource *			_filterInterruptSource;
    IOLock *						_intLock;
    struct InterruptTransaction				_outstandingTrans[kMaxOutstandingTrans];
    bool						_uimInitialized;
    bool						_unloadUIMAcrossSleep;
    bool						_onCardBus;
    bool						_idleSuspend;
    bool						_hasPCIPwrMgmt;
    bool						_ohciAvailable;
    IOPhysicalAddress 					_hccaPhysAddr;
    UInt8						_ohciBusState;
    AbsoluteTime					_lastCheckedTime;		// Last time we checked the Root Hub for inactivity
    AbsoluteTime					_lastRootHubStatusChanged;	// Last time we had activity on the root hub
    AbsoluteTime					_filterTimeStamp;
    AbsoluteTime					_filterTimeStamp2;
    UInt32						_lowLatencyIsochTDsProcessed;	// Number of low latency isoch TD's processed at primary interrupt time
    UInt32						_filterInterruptCount;
    UInt32						_framesUpdated;
    UInt32						_framesError;
    
    // Interrupt related fields
    //
    UInt32						_resumeDetectedInterrupt;	// Set at primary interrupt time if we get that interrupt, cleared at secondary interrupt time
    UInt32						_unrecoverableErrorInterrupt;	// Set at primary interrupt time if we get that interrupt, cleared at secondary interrupt time
    UInt32						_rootHubStatusChangeInterrupt;	// Set at primary interrupt time if we get that interrupt, cleared at secondary interrupt time
    UInt32						_writeDoneHeadInterrupt;	// Set at primary interrupt time if we get that interrupt, cleared at secondary interrupt time
    volatile IOPhysicalAddress				_savedDoneQueueHead;		// Physical address read from the done queue;
    volatile UInt32					_producerCount;			// Counter used to synchronize reading of the done queue between filter (producer) and action (consumer)
    volatile UInt32					_consumerCount;			// Counter used to synchronize reading of the done queue between filter (producer) and action (consumer)
    IOSimpleLock *					_wdhLock;
    UInt64						_timeElapsed;
	bool									_needToCreateRootHub;					// True if we need to create the root hub post wake

    static void 				InterruptHandler(OSObject *owner,  IOInterruptEventSource * source, int count);
    static bool 				PrimaryInterruptFilter(OSObject *owner, IOFilterInterruptEventSource *source);
    bool 					FilterInterrupt(int index);

    void					SetVendorInfo(void);
    void					finishPending();
    IOReturn 					ControlInitialize(void);
    IOReturn 					BulkInitialize (void);
    IOReturn 					IsochronousInitialize(void);
    IOReturn 					InterruptInitialize (void);

    // callPlatformFunction symbols
    //
    const OSSymbol *				_usb_remote_wakeup;
    bool  					_remote_wakeup_occurred;
    
    // Memory routines
    void										doCallback(AppleOHCIGeneralTransferDescriptorPtr nextTD, UInt32 transferStatus, UInt32 bufferSizeRemaining);
    UInt32 findBufferRemaining (AppleOHCIGeneralTransferDescriptorPtr pCurrentTD);
    AppleOHCIIsochTransferDescriptorPtr AllocateITD(void);
    AppleOHCIGeneralTransferDescriptorPtr AllocateTD(void);
    AppleOHCIEndpointDescriptorPtr AllocateED(void);
    IOReturn 	TranslateStatusToUSBError(UInt32 status);
    
    void ProcessCompletedITD (AppleOHCIIsochTransferDescriptorPtr pITD, IOReturn status);
    IOReturn DeallocateITD (AppleOHCIIsochTransferDescriptorPtr pTD);
    IOReturn DeallocateTD (AppleOHCIGeneralTransferDescriptorPtr pTD);
    IOReturn DeallocateED (AppleOHCIEndpointDescriptorPtr pED);
    IOReturn RemoveAllTDs(AppleOHCIEndpointDescriptorPtr pED);
    IOReturn RemoveTDs(AppleOHCIEndpointDescriptorPtr pED);
    // IOReturn DoDoneQueueProcessing(AppleOHCIGeneralTransferDescriptorPtr pHCDoneTD, IOUSBCompletionAction safeAction);
    IOReturn DoDoneQueueProcessing(IOPhysicalAddress cachedWritedoneQueueHead, UInt32 cachedProducer, IOUSBCompletionAction safeAction);
                                   
                                   
    void UIMProcessDoneQueue(IOUSBCompletionAction safeAction=0);
    void UIMRootHubStatusChange( void );
    void UIMRootHubStatusChange(bool abort);
    void SimulateRootHubInt(
            UInt8					endpoint,
            IOMemoryDescriptor * 			buf,
            UInt32 					bufLen,
            IOUSBCompletion				completion);
    IOReturn SimulateInterruptEDCreate(UInt16 maxPacketSize, short pollingRate);
    IOReturn SimulateControlEDCreate (UInt16 maxPacketSize);
    IOReturn SimulateEDAbort (short endpointNumber, short direction);
    IOReturn SimulateEDDelete (short endpointNumber, short direction);
    IOReturn SimulateEDClearStall (short endpointNumber, short direction);
    
    AppleOHCIEndpointDescriptorPtr AddEmptyEndPoint(
            UInt8 					functionAddress,
            UInt8					endpointNumber,
            UInt16					maxPacketSize,
            UInt8					speed,
            UInt8					direction,
            AppleOHCIEndpointDescriptorPtr			pED,
            OHCIEDFormat				format);

    AppleOHCIEndpointDescriptorPtr FindEndpoint (
            short 					functionNumber,
            short 					endpointNumber,
            short 					direction,
            AppleOHCIEndpointDescriptorPtr 			*pEDQueueBack,
            UInt32 					*controlMask);

    AppleOHCIEndpointDescriptorPtr FindControlEndpoint (
            short 					functionNumber,
            short					endpointNumber,
            AppleOHCIEndpointDescriptorPtr   		*pEDBack);

    AppleOHCIEndpointDescriptorPtr FindBulkEndpoint (
            short 					functionNumber,
            short					endpointNumber,
            short					direction,
            AppleOHCIEndpointDescriptorPtr			*pEDBack);

    AppleOHCIEndpointDescriptorPtr FindIsochronousEndpoint(
            short 					functionNumber,
            short					endpointNumber,
            short 					direction,
            AppleOHCIEndpointDescriptorPtr			*pEDBack);
            
    AppleOHCIEndpointDescriptorPtr FindInterruptEndpoint(
            short 					functionNumber,
            short					endpointNumber,
            short					direction,
            AppleOHCIEndpointDescriptorPtr			*pEDBack);

    
    void DoOptiFix(AppleOHCIEndpointDescriptorPtr pIsochHead);
    void OptiLSHSFix(void);
    void dumpRegs(void);
    bool DetermineInterruptOffset(UInt32          pollingRate,
                            UInt32          reserveBandwidth,
                            int             *offset);
    void ReturnTransactions(
                AppleOHCIGeneralTransferDescriptorPtr 	transaction,
                UInt32					tail);

    void ReturnOneTransaction(
                AppleOHCIGeneralTransferDescriptorPtr 	transaction,
		AppleOHCIEndpointDescriptorPtr		pED,
		IOReturn				err);

    void CheckEDListForTimeouts(
                                AppleOHCIEndpointDescriptorPtr 	head,
                                AppleOHCIEndpointDescriptorPtr 	tail);
    void ReturnAllTransactionsInEndpoint(
                                AppleOHCIEndpointDescriptorPtr 	head,
                                AppleOHCIEndpointDescriptorPtr 	tail);
        
public:
    virtual bool 	init(OSDictionary * propTable);
    virtual bool 	start( IOService * provider );
    virtual void 	stop( IOService * provider );
    virtual bool 	finalize(IOOptionBits options);
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );
    virtual void 	free();

    /*
     * UIM methods
     */
    IOReturn UIMInitialize(IOService * provider);
    IOReturn UIMFinalize();
    IOReturn UIMInitializeForPowerUp();
    IOReturn UIMFinalizeForPowerDown();
    
    // Control
    virtual IOReturn UIMCreateControlEndpoint(
            UInt8				functionNumber,
            UInt8				endpointNumber,
            UInt16				maxPacketSize,
            UInt8				speed);

    virtual IOReturn UIMCreateControlEndpoint(
                                              UInt8				functionNumber,
                                              UInt8				endpointNumber,
                                              UInt16				maxPacketSize,
                                              UInt8				speed,
                                              USBDeviceAddress    		highSpeedHub,
                                              int			                highSpeedPort);

    // method in 1.8 and 1.8.1
   virtual IOReturn UIMCreateControlTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCompletion			completion,
            void *				CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);
    //same method in 1.8.2
   virtual IOReturn UIMCreateControlTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCommand*			command,
            void *				CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);

    // method in 1.8 and 1.8.1
    virtual IOReturn UIMCreateControlTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCompletion			completion,
            IOMemoryDescriptor *		CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);

    //same method in 1.8.2
    virtual IOReturn UIMCreateControlTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCommand*			command,
            IOMemoryDescriptor *		CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);

    // Bulk
    virtual IOReturn UIMCreateBulkEndpoint(
            UInt8				functionNumber,
            UInt8				endpointNumber,
            UInt8				direction,
            UInt8				speed,
            UInt8				maxPacketSize);

    virtual IOReturn UIMCreateBulkEndpoint(
                                           UInt8				functionNumber,
                                           UInt8				endpointNumber,
                                           UInt8				direction,
                                           UInt8				speed,
                                           UInt16				maxPacketSize,
                                           USBDeviceAddress    		highSpeedHub,
                                           int			                highSpeedPort);

    // method in 1.8 and 1.8.1
    virtual IOReturn UIMCreateBulkTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCompletion			completion,
            IOMemoryDescriptor *		CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);

    // same method in 1.8.2
    virtual IOReturn UIMCreateBulkTransfer(IOUSBCommand* command);

    // general purpose method to handle all of the other transfers - not in the controller class
    virtual IOReturn CreateGeneralTransfer(
            AppleOHCIEndpointDescriptorPtr		queue,
            IOUSBCommand*			command,
            IOMemoryDescriptor*			CBP,
            UInt32				bufferSize,
            UInt32				flags,
            UInt32				type,
            UInt32				kickBits);

    // Interrupt
    virtual IOReturn UIMCreateInterruptEndpoint(
            short				functionAddress,
            short				endpointNumber,
            UInt8				direction,
            short				speed,
            UInt16				maxPacketSize,
            short				pollingRate);

    virtual IOReturn UIMCreateInterruptEndpoint(
                                                short				functionAddress,
                                                short				endpointNumber,
                                                UInt8				direction,
                                                short				speed,
                                                UInt16				maxPacketSize,
                                                short				pollingRate,
                                                USBDeviceAddress    		highSpeedHub,
                                                int                 		highSpeedPort);

    // method in 1.8 and 1.8.1
    virtual IOReturn UIMCreateInterruptTransfer(
            short				functionNumber,
            short				endpointNumber,
            IOUSBCompletion			completion,
            IOMemoryDescriptor *		CBP,
            bool				bufferRounding,
            UInt32				bufferSize,
            short				direction);

    // method in 1.8.2
    virtual IOReturn UIMCreateInterruptTransfer(IOUSBCommand* command);

    // Isoch
    virtual IOReturn UIMCreateIsochEndpoint(
            short				functionAddress,
            short				endpointNumber,
            UInt32				maxPacketSize,
            UInt8				direction);

    virtual IOReturn 		UIMCreateIsochEndpoint(
                                              short		functionAddress,
                                              short		endpointNumber,
                                              UInt32		maxPacketSize,
                                              UInt8		direction,
                                              USBDeviceAddress highSpeedHub,
                                              int      highSpeedPort);
    
    virtual IOReturn UIMCreateIsochTransfer(
	short				functionAddress,
	short				endpointNumber,
	IOUSBIsocCompletion		completion,
	UInt8				direction,
	UInt64				frameStart,
	IOMemoryDescriptor *		pBuffer,
	UInt32				frameCount,
	IOUSBIsocFrame			*pFrames);

    virtual IOReturn UIMCreateIsochTransfer(
	short				functionAddress,
	short				endpointNumber,
	IOUSBIsocCompletion		completion,
	UInt8				direction,
	UInt64				frameStart,
	IOMemoryDescriptor *		pBuffer,
	UInt32				frameCount,
	IOUSBLowLatencyIsocFrame	*pFrames,
        UInt32				updateFrequency);

    virtual IOReturn UIMAbortEndpoint(
            short				functionNumber,
            short				endpointNumber,
            short				direction);
    virtual IOReturn UIMDeleteEndpoint(
            short				functionNumber,
            short				endpointNumber,
            short				direction);
    virtual IOReturn UIMClearEndpointStall(
            short				functionNumber,
            short				endpointNumber,
            short				direction);
    /*
     * Root hub methods
     */
    IOReturn 		GetRootHubDeviceDescriptor(IOUSBDeviceDescriptor *desc);
    IOReturn 		GetRootHubDescriptor(IOUSBHubDescriptor *desc);
    IOReturn 		SetRootHubDescriptor(OSData *buffer);
    IOReturn 		GetRootHubConfDescriptor(OSData *desc);
    IOReturn 		GetRootHubStatus(IOUSBHubStatus *status);
    IOReturn		GetRootHubStringDescriptor(UInt8 index, OSData *desc);
    IOReturn 		SetRootHubFeature(UInt16 wValue);
    IOReturn 		ClearRootHubFeature(UInt16 wValue);
    IOReturn 		GetRootHubPortStatus(IOUSBHubPortStatus *status, UInt16 port);
    IOReturn 		SetRootHubPortFeature(UInt16 wValue, UInt16 port);
    IOReturn 		ClearRootHubPortFeature(UInt16 wValue, UInt16 port);
    IOReturn 		GetRootHubPortState(UInt8 *state, UInt16 port);
    IOReturn 		SetHubAddress(UInt16 wValue);
    AbsoluteTime	LastRootHubPortStatusChanged( bool reset );
    bool		RootHubAreAllPortsDisconnected( void );
    void		OHCIGetNumberOfPorts(UInt8 *numPorts);
    
    void OHCIRootHubPower(bool on);
    void OHCIRootHubResetChangeConnection(UInt16 port);
    void OHCIRootHubResetResetChange(UInt16 port);
    void OHCIRootHubResetSuspendChange(UInt16 port);
    void OHCIRootHubResetEnableChange(UInt16 port);
    void OHCIRootHubResetOverCurrentChange(UInt16 port);
    void OHCIRootHubResetPort (UInt16 port);
    void OHCIRootHubPortEnable(UInt16 port, bool on);
    void OHCIRootHubPortSuspend(UInt16 port, bool on);
    void OHCIRootHubPortPower(UInt16 port, bool on);

    virtual UInt32 GetBandwidthAvailable();
    virtual UInt64 GetFrameNumber();
    virtual UInt32 GetFrameNumber32();

    virtual void PollInterrupts(IOUSBCompletionAction safeAction=0);
    virtual IOReturn callPlatformFunction(const OSSymbol *functionName,
					bool waitForFunction,
                                        void *param1, void *param2,
                                        void *param3, void *param4);
    virtual void UIMCheckForTimeouts(void);

};


// constants for the uimFlags field of the GTD structure
// may also be used in ITD one day if needed. plenty of bits to go around
enum
{
    kUIMFlagsCallbackTD			=		0x0001,				// this TD requires a callback
    kUIMFlagsMultiTDTransaction 	= 		0x0002,				// this TD is part of a multi-TD transaction (e.g. a control xaction)
    kUIMFlagsFinalTDinTransaction	=		0x0004				// this TD is the final TD in a multi-TD transaction (for finding the end)
};

enum
{
    kOHCIBusStateOff		= 0,
    kOHCIBusStateSuspended	= 1,
    kOHCIBusStateRunning	= 2
};

// Constants that define the different power states in the setPowerState call
enum
{
    kOHCISetPowerLevelSuspend		= 0,
    kOHCISetPowerLevelRunning		= 1,
    kOHCISetPowerLevelIdleSuspend	= 2
};

// constants to use to decide whether to idle suspend a bus
//
enum
{
    kOHCICheckForRootHubConnectionsPeriod = 30, 	// Check every x secs to see if root hub has connections
    kOHCICheckForRootHubInactivityPeriod = 30		// Wait for x secs after the last time the root hub was active
};    

#endif /* _IOKIT_AppleUSBOHCI_H */

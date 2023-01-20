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

#ifndef _IOKIT_APPLEUSBHUBPORT_H
#define _IOKIT_APPLEUSBHUBPORT_H

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/USBHub.h>
#include <IOKit/usb/IOUSBLog.h>

#include "AppleUSBHub.h"

#include <kern/thread_call.h>

class AppleUSBHubPort;
class AppleUSBHub;

typedef IOReturn (AppleUSBHubPort::*ChangeHandlerFuncPtr)(UInt16 changeFlags, UInt16 statusFlags);

typedef struct {
    ChangeHandlerFuncPtr handler;
    UInt32 bit;
    UInt32 clearFeature;
} portStatusChangeVector;

enum{
    kNumChangeHandlers = 5
};

typedef enum HubPortState
{
    hpsNormal = 0,
    hpsDead,
    hpsDeviceZero,
    hpsDeadDeviceZero,
    hpsSetAddress,
    hpsSetAddressFailed
} HubPortState;

class AppleUSBHubPort : public OSObject
{
    friend  class AppleUSBHub;
    
    OSDeclareDefaultStructors(AppleUSBHubPort)

	IOUSBDeviceDescriptor			_desc;
    UInt8							_speed;					// kUSBDeviceSpeedLow or kUSBDeviceSpeedFull
    UInt32							_portPowerAvailable;
    int								_portNum;
	
protected:
    IOUSBController *				_bus;
    AppleUSBHub *					_hub;
    IOUSBHubDescriptor *			_hubDesc;
    IOUSBDevice *					_portDevice;
    bool							_devZero;
    bool							_captive;
    bool							_retryPortStatus;
    bool							_statusChangedThreadActive;
    UInt8							_statusChangedState;
    UInt8							_connectionChangedState;
    bool							_initThreadActive;
    bool							_inCommandSleep;
    UInt32							_attachRetry;
	bool							_attachMessageDisplayed;
	bool							_overCurrentNoticeDisplayed;
    
    portStatusChangeVector	_changeHandler[kNumChangeHandlers];
    
    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

private:
		
    thread_call_t					_initThread;
    thread_call_t					_portStatusChangedHandlerThread;
    IOUSBHubPortStatus				_portStatus;
    HubPortState					_state;
    IOLock *						_runLock;											// Lock to synchronize accesses to our ProcessStatus thread
	IOLock *						_initLock;											// Lock to make sure we don't start processing changes until init is done
    bool							_getDeviceDescriptorFailed;
    UInt8							_setAddressFailed;
    UInt32							_devZeroCounter;
    bool							_extraResetDelay;
    
    static void						PortInitEntry(OSObject *target);					// this will run on its own thread
    static void						PortStatusChangedHandlerEntry(OSObject *target);	// this will run on its own thread
 
    IOReturn						DetachDevice();
    IOReturn						GetDevZeroDescriptorWithRetries();
    bool							AcquireDeviceZero();
    void							ReleaseDeviceZero();
    
protected:
		
    virtual IOReturn				init(AppleUSBHub *	parent, int portNum, UInt32 powerAvailable, bool captive);
    virtual void					PortInit(void);
    virtual void					PortStatusChangedHandler(void);

public:

	// IOService methods
    virtual IOReturn				start(void);
    virtual void					stop(void);
	virtual void					free(void);

    IOReturn						AddDevice(void);
    void							RemoveDevice(void);
    IOReturn						ResetPort();
    IOReturn						ClearTT(bool multiTTs, UInt32 options);
    bool							StatusChanged(void);

    void							InitPortVectors(void);
    void							SetPortVector(ChangeHandlerFuncPtr routine, UInt32 condition);
    IOReturn						DefaultOverCrntChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						DefaultResetChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						DefaultSuspendChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						DefaultEnableChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						DefaultConnectionChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						AddDeviceResetChangeHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						HandleResetPortHandler(UInt16 changeFlags, UInt16 statusFlags);
    IOReturn						HandleSuspendPortHandler(UInt16 changeFlags, UInt16 statusFlags);
    void							FatalError(IOReturn err, char *str);
    IOReturn						ReleaseDevZeroLock( void);
    IOReturn						SuspendPort(bool suspend);
    IOReturn						ReEnumeratePort(UInt32 options);
	
    void							DisplayOverCurrentNotice(bool individual);
	bool							willTerminate( IOService * provider, IOOptionBits options );

	
	// Accessors
    AppleUSBHub *					GetHub(void) { return _hub; }
    bool							IsCaptive(void) { return _captive; }
    bool							GetDevZeroLock(void) { return _devZero; }
    UInt32							GetPortTimeStamp(void) { return _devZeroCounter; }

};

#endif  _IOKIT_APPLEUSBHUBPORT_H

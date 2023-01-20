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


#import "BusProber.h"


@implementation BusProber

static void DeviceAdded(void *refCon, io_iterator_t iterator)
{
    io_service_t ioDeviceObj=nil;
    
    while( ioDeviceObj = IOIteratorNext( iterator) )
    {
        IOObjectRelease( ioDeviceObj );
    }
    [(BusProber *)refCon refreshData:false];
}

static void DeviceRemoved(void *refCon, io_iterator_t iterator)
{
    io_service_t ioDeviceObj=nil;
    
    while( (ioDeviceObj = IOIteratorNext( iterator)))
    {
        IOObjectRelease( ioDeviceObj );
    }
    [(BusProber *)refCon refreshData:false];
}

- initWithListener:(id)listener devicesArray:(NSMutableArray *)devices {
    if (self = [super init]) {
        _runLoopSource = NULL;
        _listener = listener;
        _devicesArray = [devices retain];
        
        if (listener == nil) {
            [NSException raise:@"BusProberBadListener" format:@"Listener must be non-nil"];
            [self dealloc];
            self = nil;
        } else if (! [self registerForUSBNotifications]) {
            NSLog(@"BusProber was unable to register for USB notifications");
            [self dealloc];
            self = nil;
        } else {
            // no problems
            [self refreshData:true];
        }
    }
    return self;
}

- (void)dealloc {
    [self unregisterForUSBNotifications];
    [_devicesArray release];
    [super dealloc];
}

- (BOOL)registerForUSBNotifications
{
    kern_return_t kr;
    mach_port_t masterPort;
    IONotificationPortRef gNotifyPort;
    io_iterator_t  gAddedIter,gRemovedIter;
    
    kr = IOMasterPort(MACH_PORT_NULL, &masterPort);
    if (kr != KERN_SUCCESS) return NO;
    
    gNotifyPort = IONotificationPortCreate(masterPort);
    _runLoopSource = IONotificationPortGetRunLoopSource(gNotifyPort);
    CFRunLoopAddSource([[NSRunLoop currentRunLoop] getCFRunLoop], _runLoopSource, kCFRunLoopDefaultMode);
    kr = IOServiceAddMatchingNotification(gNotifyPort,
                                          kIOFirstMatchNotification,
                                          IOServiceMatching(kIOUSBDeviceClassName),
                                          DeviceAdded,
                                          self,
                                          &gAddedIter);
    if (kr != KERN_SUCCESS) return NO;
    
    kr = IOServiceAddMatchingNotification(gNotifyPort,
                                          kIOTerminatedNotification,
                                          IOServiceMatching(kIOUSBDeviceClassName),
                                          DeviceRemoved,
                                          self,
                                          &gRemovedIter);
    if (kr != KERN_SUCCESS) return NO;
    
    DeviceAdded(self, gAddedIter);
    DeviceRemoved(self, gRemovedIter);
    mach_port_deallocate(mach_task_self(), masterPort);
    return YES;
}

- (void)unregisterForUSBNotifications {
    if (_runLoopSource != NULL)
    {
        CFRunLoopSourceInvalidate(_runLoopSource);
        CFRelease(_runLoopSource);
    }
}

- (void)refreshData:(BOOL)shouldForce {
    if (!shouldForce && [[NSUserDefaults standardUserDefaults] boolForKey:@"BusProbeDontAutoRefresh"] == YES) {
        return;
    }
    
    [_devicesArray removeAllObjects];
     
    CFDictionaryRef matchingDict = NULL;
    mach_port_t         mMasterDevicePort = nil;
    io_iterator_t       devIter = nil;
    io_service_t        ioDeviceObj	= nil;
    IOReturn            kr;
    int                 deviceNumber = 0; //used to iterate through devices
    
    kr = IOMasterPort(MACH_PORT_NULL, &mMasterDevicePort);
    if (kr != kIOReturnSuccess) {
        NSLog(@"BusProber: error in -refresh at IOMasterPort()");
        return;
    }
    
    matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (matchingDict == NULL) {
        NSLog(@"BusProber: error in -refresh at IOServiceMatching() - dictionary was NULL");
        mach_port_deallocate(mach_task_self(), mMasterDevicePort);
        return;
    }
    
    kr = IOServiceGetMatchingServices(mMasterDevicePort, matchingDict /*reference consumed*/, &devIter);
    if (kr != kIOReturnSuccess) {
        NSLog(@"BusProber: error in -refresh at IOServiceGetMatchingServices()");
        mach_port_deallocate(mach_task_self(), mMasterDevicePort);
        return;
    }
    
    while (ioDeviceObj = IOIteratorNext(devIter)) {
        IOCFPlugInInterface 	**ioPlugin;
        IOUSBDeviceRef			deviceIntf = NULL;
        SInt32                  score;
        
        kr = IOCreatePlugInInterfaceForService(ioDeviceObj, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &ioPlugin, &score);
        if (kr != kIOReturnSuccess) {
            IOObjectRelease(ioDeviceObj);
            continue;
        }
        
        kr = (*ioPlugin)->QueryInterface(ioPlugin, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID *)&deviceIntf);
		IODestroyPlugInInterface(ioPlugin);
        ioPlugin = NULL;

        if (kr != kIOReturnSuccess) {
            IOObjectRelease(ioDeviceObj);
            continue;
        }
        
        [self processDevice:deviceIntf deviceNumber:deviceNumber];
        deviceNumber++;
        
        
        (*deviceIntf)->Release(deviceIntf);
        IOObjectRelease(ioDeviceObj);
    }
    
    IOObjectRelease(devIter);
    mach_port_deallocate(mach_task_self(), mMasterDevicePort);
    
    [_listener busProberInformationDidChange:self];
}

- (void)processDevice:(IOUSBDeviceRef)deviceIntf deviceNumber:(int)deviceNumber {
    BusProbeDevice *        thisDevice;
    UInt32                  locationID = 0;
    UInt8                   speed = 0;
    USBDeviceAddress        address = 0;
    IOUSBDeviceDescriptor   dev;
    int                     len;
    IOReturn                error;
	BOOL					needToSuspend = FALSE;

    thisDevice = [[BusProbeDevice alloc] init];
    
    [_devicesArray addObject:thisDevice];
    
    // Get the locationID for this device
    if (GetDeviceLocationID( deviceIntf, &locationID ) == 0) {
        [thisDevice setLocationID:locationID];
    }
    
    // Get the connection speed for this device
    if (GetDeviceSpeed( deviceIntf, &speed ) == 0) {
        [thisDevice setSpeed:speed];
    }
    
    // Get the device address for this device
    if (GetDeviceAddress( deviceIntf, &address ) == 0) {
        [thisDevice setAddress:address];
    }
    
    // Set the name of the device (this is what will be shown in the UI)
    [thisDevice setDeviceName:
        [NSString stringWithFormat:@"%s Speed device @ %d (0x%08lX): .............................................",
            (speed == kUSBDeviceSpeedHigh ? "High" : (speed == kUSBDeviceSpeedLow ? "Low" : "Full")), 
            address, 
            locationID]];    

    error = GetDescriptor(deviceIntf, kUSBDeviceDesc, 0, &dev, sizeof(dev));
    if (error == kIOReturnNotResponding) 
	{
		// The device did not respond to a request for its device descriptor, probably because it was suspended.  Attempt to resume it and 
		// later on suspend it again.
		needToSuspend = TRUE;
		
		error = SuspendDevice(deviceIntf,false);
		if ( error == kIOReturnSuccess )
		{
			error = GetDescriptor(deviceIntf, kUSBDeviceDesc, 0, &dev, sizeof(dev));
		}
	} 
	
	if ( error == kIOReturnSuccess )
	{
        int iconfig;
        [DecodeDeviceDescriptor decodeBytes:&dev forDevice:thisDevice deviceInterface:deviceIntf wasSuspended:needToSuspend];
		
        for (iconfig = 0; iconfig < dev.bNumConfigurations; ++iconfig) {
            IOUSBConfigurationDescHeader cfgHeader;
            IOUSBConfigurationDescriptor config;
			
            // Get the Configuration descriptor.  We first get just the header and later we get the full
            // descriptor
            error = GetDescriptor(deviceIntf, kUSBConfDesc, iconfig, &cfgHeader, sizeof(cfgHeader));
            if (error != kIOReturnSuccess) {
                // Set a flag to the decodeBytes descriptor indicating that we didn't get the header
                //
                cfgHeader.bDescriptorType = sizeof(cfgHeader);
                cfgHeader.wTotalLength = 0;
                [DecodeConfigurationDescriptor decodeBytes:(IOUSBConfigurationDescHeader *)&cfgHeader forDevice:thisDevice deviceInterface:deviceIntf configNumber:iconfig isOtherSpeedDesc:NO];
                
                // Try to get the descriptor again, using the sizeof(IOUSBConfigurationDescriptor) 
                //
                bzero(&config,sizeof(config)-1);
                error = GetDescriptor(deviceIntf, kUSBConfDesc, iconfig, &config, sizeof(config)-1);
                if (error != kIOReturnSuccess) {
                    cfgHeader.bDescriptorType = sizeof(config)-1;
                    cfgHeader.wTotalLength = 0;
                }
                else
                {
                    cfgHeader.bLength = config.bLength;
                    cfgHeader.bDescriptorType = config.bDescriptorType;
                    cfgHeader.wTotalLength = config.wTotalLength;
                }
            }
            [DecodeConfigurationDescriptor decodeBytes:(IOUSBConfigurationDescHeader *)&cfgHeader forDevice:thisDevice deviceInterface:deviceIntf configNumber:iconfig isOtherSpeedDesc:NO];
        }
    }
	else 
	{
		// This description will be shown in the UI, to the right of the device's name
		[thisDevice setDeviceDescription: [NSString stringWithFormat:@"Unknown device (did not respond to inquiry - 0x%x)", error]];
	}
	
	
    // If the device is a hub, then dump the Hub descriptor
    //
    if ( dev.bDeviceClass == kUSBHubClass )
    {
        IOUSBHubDescriptor	cfg;
        
        len = GetClassDescriptor(deviceIntf, kUSBHUBDesc, 0, &cfg, sizeof(cfg));
        if (len > 0) {
            [DescriptorDecoder decodeBytes:(Byte *)&cfg forDevice:thisDevice deviceInterface:deviceIntf userInfo:NULL isOtherSpeedDesc:false];
        }
    }
    
    // Check to see if the device has the "Device Qualifier" descriptor
    //
    if ( dev.bcdUSB >= 0x0200 ) {
        IOUSBDeviceQualifierDescriptor	desc;

        error = GetDescriptor(deviceIntf, kUSBDeviceQualifierDesc, 0, &desc, sizeof(desc));
        if (error == kIOReturnSuccess) {
            [DescriptorDecoder decodeBytes:(Byte *)&desc forDevice:thisDevice deviceInterface:deviceIntf userInfo:NULL isOtherSpeedDesc:false];
            
            // Since we have a Device Qualifier Descriptor, we can get a "Other Speed Configuration Descriptor"
            // (It's the same as a regular configuration descriptor)
            //
            int iconfig;
            
            for (iconfig = 0; iconfig < desc.bNumConfigurations; ++iconfig)
            {
                IOUSBConfigurationDescHeader cfgHeader;
                IOUSBConfigurationDescriptor config;
                
                // Get the Configuration descriptor.  We first get just the header and later we get the full
                // descriptor
                error = GetDescriptor(deviceIntf, kUSBOtherSpeedConfDesc, iconfig, &cfgHeader, sizeof(cfgHeader));
                if (error != kIOReturnSuccess) {
                    // Set a flag to the decodeBytes descriptor indicating that we didn't get the header
                    //
                    cfgHeader.bDescriptorType = sizeof(cfgHeader);
                    cfgHeader.wTotalLength = 0;
                    [DecodeConfigurationDescriptor decodeBytes:(IOUSBConfigurationDescHeader *)&cfgHeader forDevice:thisDevice deviceInterface:deviceIntf configNumber:iconfig isOtherSpeedDesc:YES];
                    
                    // Try to get the descriptor again, using the sizeof(IOUSBConfigurationDescriptor) 
                    //
                    bzero(&config,sizeof(config)-1);
                    error = GetDescriptor(deviceIntf, kUSBOtherSpeedConfDesc, iconfig, &config, sizeof(config)-1);
                    if (error != kIOReturnSuccess) {
                        cfgHeader.bDescriptorType = sizeof(config)-1;
                        cfgHeader.wTotalLength = 0;
                    }
                    else
                    {
                        cfgHeader.bLength = config.bLength;
                        cfgHeader.bDescriptorType = config.bDescriptorType;
                        cfgHeader.wTotalLength = config.wTotalLength;
                    }
                }
                [DecodeConfigurationDescriptor decodeBytes:(IOUSBConfigurationDescHeader *)&cfgHeader forDevice:thisDevice deviceInterface:deviceIntf configNumber:iconfig isOtherSpeedDesc:YES];
            }
        }
    }
    
	if ( needToSuspend )
		error = SuspendDevice(deviceIntf,true);
	
    [thisDevice release];
}

@end

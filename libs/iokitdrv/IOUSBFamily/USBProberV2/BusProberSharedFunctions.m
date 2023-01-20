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


#import "BusProberSharedFunctions.h"

int GetDeviceLocationID( IOUSBDeviceRef deviceIntf, UInt32 * locationID ) {
     IOReturn err;
    
    err = (*deviceIntf)->GetLocationID(deviceIntf, locationID);
    if (err) {
        NSLog(@"BusProber: GetDeviceSpeed() failed");
        return -1;
    }
    return 0;
}

int GetDeviceSpeed( IOUSBDeviceRef deviceIntf, UInt8 * speed ) {
    IOReturn err;
    
    err = (*deviceIntf)->GetDeviceSpeed(deviceIntf, speed);
    if (err) {
        NSLog(@"BusProber: GetDeviceSpeed() failed");
        return -1;
    }
    return 0;
}

int GetDeviceAddress( IOUSBDeviceRef deviceIntf, USBDeviceAddress * address ) {
    IOReturn err;
    
    err = (*deviceIntf)->GetDeviceAddress(deviceIntf, address);
    if (err) {
        NSLog(@"BusProber: GetDeviceAddress() failed");
        return -1;
    }
    return 0;
}

int SuspendDevice( IOUSBDeviceRef deviceIntf, BOOL suspend ) {
    IOReturn err;
    
	// First, see if we can open the IOUSBDevice.  If so, then call suspend and then close
    err = (*deviceIntf)->USBDeviceOpen(deviceIntf);
    if (err) {
        NSLog(@"BusProber: USBDeviceOpen() failed");
        return -1;
    }
    err = (*deviceIntf)->USBDeviceSuspend(deviceIntf, suspend);
    if (err) {
        NSLog(@"BusProber: USBDeviceSuspend() failed");
        return -1;
    }
    err = (*deviceIntf)->USBDeviceClose(deviceIntf);
    if (err) {
        NSLog(@"BusProber: USBDeviceClose() failed");
        return -1;
    }
    return 0;
}

IOReturn GetDescriptor(IOUSBDeviceRef deviceIntf, UInt8 descType, UInt8 descIndex, void *buf, UInt16 len) {
    IOUSBDevRequest req;
    
    req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBDevice);
    req.bRequest = kUSBRqGetDescriptor;
    req.wValue = (descType << 8) | descIndex;
    req.wIndex = 0;
    req.wLength = len;
    req.pData = buf;
    
    return (*deviceIntf)->DeviceRequest(deviceIntf, &req);
}

int GetStringDescriptor(IOUSBDeviceRef deviceIntf, UInt8 descIndex, void *buf, UInt16 len, UInt16 lang) {
    IOUSBDevRequest req;
    UInt8 		desc[256]; // Max possible descriptor length
    int stringLen;
    IOReturn err;
    if (lang == nil) // set default langID
        lang=0x0409;
    
    req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBDevice);
    req.bRequest = kUSBRqGetDescriptor;
    req.wValue = (kUSBStringDesc << 8) | descIndex;
    req.wIndex = lang;	// English
    req.wLength = 2;
    req.pData = &desc;
    verify_noerr(err = (*deviceIntf)->DeviceRequest(deviceIntf, &req));
    if ( (err != kIOReturnSuccess) && (err != kIOReturnOverrun) )
        return -1;
    
    // If the string is 0 (it happens), then just return 0 as the length
    //
    stringLen = desc[0];
    if(stringLen == 0)
    {
        return 0;
    }
    
    // OK, now that we have the string length, make a request for the full length
    //
    req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBDevice);
    req.bRequest = kUSBRqGetDescriptor;
    req.wValue = (kUSBStringDesc << 8) | descIndex;
    req.wIndex = lang;	// English
    req.wLength = stringLen;
    req.pData = buf;
    
    verify_noerr(err = (*deviceIntf)->DeviceRequest(deviceIntf, &req));
    
    return req.wLenDone;
}

int GetClassDescriptor(IOUSBDeviceRef deviceIntf, UInt8 descType, UInt8 descIndex, void *buf, UInt16 len)
{
    IOUSBDevRequest req;
    IOReturn err;
    
    req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBClass, kUSBDevice);
    req.bRequest = kUSBRqGetDescriptor;
    req.wValue = (descType << 8) | descIndex;
    req.wIndex = 0;
    req.wLength = len;
    req.pData = buf;
    
    verify_noerr(err = (*deviceIntf)->DeviceRequest(deviceIntf, &req));
    if (err) return -1;
    return req.wLenDone;
}

int GetDescriptorFromInterface(IOUSBDeviceRef deviceIntf, UInt8 descType, UInt8 descIndex, UInt16 wIndex, void *buf, UInt16 len)
{
    IOUSBDevRequest req;
    IOReturn err;
    
    req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBInterface);
    req.bRequest = kUSBRqGetDescriptor;
    req.wValue = (descType << 8) | descIndex;
    req.wIndex = wIndex;
    req.wLength = len;
    req.pData = buf;
    
    verify_noerr(err = (*deviceIntf)->DeviceRequest(deviceIntf, &req));
    if (err) return -1;
    return req.wLenDone;
}

char * GetStringFromNumber(UInt32 value, int sizeInBytes, int style) {
    char *format = malloc(32 *sizeof(char));
    char *valstr = malloc(32 *sizeof(char));
    
    memset(format, '\0', 32 *sizeof(char));
    memset(valstr, '\0', 32 *sizeof(char));
    
    if (style == kIntegerOutputStyle) {
        sprintf(valstr, "%d",(int)value);
		free(format);
        return valstr;
    }
    else if (style == kHexOutputStyle) {
        sprintf(format, "0x%%0%dlX", sizeInBytes*2);
        sprintf(valstr, format, value);
		free(format);
        return valstr;
    } else {
		free(format);
		free(valstr);
        return NULL;
    }
}

char * GetStringFromIndex(UInt8 strIndex, IOUSBDeviceRef deviceIntf) {
    Byte buf[256];
    char *str2 =  malloc(500 * sizeof(char));
    memset(str2,'\0', 500 * sizeof(char));
    
    if (strIndex > 0) {
        int len;
        buf[0] = 0;
        len = GetStringDescriptor(deviceIntf, strIndex, buf, sizeof(buf), nil);
        
        if (len > 2) {
            Byte *p;
            CFStringRef str;
            for (p = buf + 2; p < buf + len; p += 2)
            {
                Swap16(p);
            }
            
            str = CFStringCreateWithCharacters(NULL, (const UniChar *)(buf+2), (len-2)/2);
            CFStringGetCString(str, (char *)buf, 256, kCFStringEncodingNonLossyASCII);
            CFRelease(str);
            sprintf(str2, "\"%s\"", buf);
            return str2;
        }
        else {
            strcat(str2,"0x00");
            return str2;
        }
    }
    else {
        strcat(str2,"0x00");
        return str2;
    }
}


BusProbeClass * GetDeviceClassAndSubClass(UInt8 * pcls) {
    BusProbeClass *bpClass = [[BusProbeClass alloc] init];
    NSString *cls = @"", *sub = @"", *protocol = @"";
    
    switch (pcls[0]) {
        case kUSBCompositeClass:
            cls = @"Composite";
            break;
        case kUSBCommClass:
            cls = @"Communication";
            break;
        case kUSBHubClass:
            cls = @"Hub";
            // Check the bDeviceProtocol.  If 0, then hub is operating at full/low Speed
            //
            switch (pcls[2]) {
                case 1:
                    protocol = @"High Speed Single Transaction Translator";
                    break;
                case 2:
                    protocol = @"High Speed Multiple Transaction Translators";
                    break;
                case 0:
                default:
                    protocol = @"Full/Low Speed";
                    break;
            }
            break;
        case kUSBDiagnosticClass:
            cls = @"Diagnostic Device";
            switch (pcls[1]) {
                case kUSBReprogrammableDiagnosticSubClass:
                    sub = @"Reprogrammable Diagnostic Device";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            switch (pcls[2]) {
                case kUSB2ComplianceDeviceProtocol:
                    protocol = @"USB2 Compliance Device";
                    break;
                default:
                    protocol = @"Unknown";
                    break;
            }
            break;
        case kUSBWirelessControllerClass:
            cls = @"Wireless Controller";
            switch (pcls[1]) {
                case kUSBRFControllerSubClass:
                    sub = @"RF Controller";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            switch (pcls[2]) {
                case kUSBBluetoothProgrammingInterfaceProtocol:
                    protocol = @"Bluetooth Programming Interface";
                    break;
                default:
                    protocol = @"Unknown";
                    break;
            }
            break;
        case kUSBMiscellaneousClass:
            cls = @"Miscellaneous";
            switch (pcls[1]) {
                case kUSBCommonClassSubClass:
                    sub = @"Common Class";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            switch (pcls[2]) {
                case KUSBInterfaceAssociationDescriptorProtocol:
                    protocol = @"Interface Association";
                    break;
                default:
                    protocol = @"Unknown";
                    break;
            }
            break;
        case kUSBVendorSpecificClass:
            cls = sub = @"Vendor-specific";
            break;            
        default:
            cls = @"Unknown";
            break;
    }
    
    [bpClass setClassNum:pcls[0]];
    [bpClass setSubclassNum:pcls[1]];
    [bpClass setProtocolNum:pcls[2]];
    
    [bpClass setClassName:cls];
    [bpClass setSubclassName:sub];
    [bpClass setProtocolName:protocol];
    
    return [bpClass autorelease];
}

BusProbeClass * GetInterfaceClassAndSubClass(UInt8 * pcls) {
    BusProbeClass *bpClass = [[BusProbeClass alloc] init];
    NSString *cls = @"", *sub = @"",  *protocol = @"";;
    
    switch (pcls[0]) {
        case kUSBAudioInterfaceClass:
            cls = @"Audio";
            switch (pcls[1]) {
                case kUSBAudioControlSubClass:
                    sub = @"Control";
                    break;
                case kUSBAudioStreamingSubClass:
                    sub = @"Streaming";
                    break;
                case kUSBMIDIStreamingSubClass:
                    sub = @"Streaming";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            break;
        case kUSBCommClass:
            cls = @"Communications-Control";
            break;
        case kUSBHIDClass:			
            cls = @"HID";
            switch (pcls[1])
            {
                case kUSBHIDBootInterfaceSubClass:
                    sub = @"Boot Interface";
                    break;
                default:
                    sub = @"";
                    break;
            }
            break;
        case kUSBPhysicalInterfaceClass:
            cls = @"Physical";
            break;
        case kUSBImageInterfaceClass:
            cls = @"Image";
            break;
        case kUSBPrintingInterfaceClass:
            cls = @"Printer";
            break;
        case kUSBMassStorageInterfaceClass:		
            cls = @"Mass Storage";
            switch (pcls[1])
            {
                case kUSBMassStorageRBCSubClass:        sub = @"Reduced Block Commands"; break;
                case kUSBMassStorageATAPISubClass:  	sub = @"ATAPI"; break;
                case kUSBMassStorageQIC157SubClass:  	sub = @"QIC-157"; break;
                case kUSBMassStorageUFISubClass:  	sub = @"UFI"; break;
                case kUSBMassStorageSFF8070iSubClass:  	sub = @"SFF-8070i"; break;
                case kUSBMassStorageSCSISubClass:  	sub = @"SCSI"; break;
                default:                        	sub = @"Unknown"; break;
            }
            break;
            
        case kUSBHubClass:
            cls = @"Hub";

            switch (pcls[2]) {
                case 1:
                    protocol = @"Multi TT Hub configured as a Single TT Hub";
                    break;
                case 2:
                    protocol = @"Multi TT Hub";
                    break;
                case 0:
                default:
                    protocol = @"";
                    break;
            }
                break;
        case kUSBCommunicationDataInterfaceClass:
            cls = @"Communications-Data";
            switch (pcls[1])
            {
                case kUSBCommDirectLineSubClass:	sub = @"Direct Line Model";  break;
                case kUSBCommAbstractSubClass:		sub = @"Abstract Model";   break;
                case kUSBCommTelephoneSubClass:		sub = @"Telephone Model"; break;
                case kUSBCommMultiChannelSubClass:	sub = @"Multi Channel Model"; break;
                case kUSBCommCAPISubClass:		sub = @"CAPI Model"; break;
                case kUSBCommEthernetNetworkingSubClass:sub = @"Ethernet Networking Model";  break;
                case kUSBATMNetworkingSubClass:		sub = @"ATM Networking Model";  break;
                default:				sub = @"Unknown Comm Class Model";  break;
            }
            break;
        case kUSBChipSmartCardInterfaceClass:
            cls = @"Chip/Smart-Card";
            break;
        case kUSBContentSecurityInterfaceClass:
            cls = @"Content-Security";
            break;
        case kUSBVideoInterfaceClass:
            cls = @"Video";
            switch (pcls[1]) {
                case kUSBVideoControlSubClass:
                    sub = @"Control";
                    break;
                case kUSBVideoStreamingSubClass:
                    sub = @"Streaming";
                    break;
                case kUSBVideoInterfaceCollectionSubClass:
                    sub = @"Interface Collection";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
                break;
            break;
        case kUSBDiagnosticDeviceInterfaceClass:
            cls = @"Diagnostic Device";
            switch (pcls[1]) {
                case kUSBReprogrammableDiagnosticSubClass:
                    sub = @"Reprogrammable Diagnostic Device";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            break;
        case kUSBWirelessControllerInterfaceClass:
            cls = @"Wireless Controller";
            switch (pcls[1]) {
                case kUSBRFControllerSubClass:
                    sub = @"RF Controller";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
                switch (pcls[2]) {
                    case kUSBBluetoothProgrammingInterfaceProtocol:
                        protocol = @"Bluetooth Programming Interface";
                        break;
                    default:
                        protocol = @"Unknown";
                        break;
                }
                break;
        case kUSBApplicationSpecificClass:
            cls = @"Application Specific";
            switch (pcls[1]) {
                case kUSBDFUSubClass:
                    sub = @"Device Firmware Update";
                    break;
                case kUSBIrDABridgeSubClass:
                    sub = @"IrDA Bridge";
                    break;
                case kUSBTestMeasurementSubClass:
                    sub = @"Test & Measurement Class";
                    break;
                default:
                    sub = @"Unknown";
                    break;
            }
            break;
        case kUSBVendorSpecificClass:
            cls = sub = @"Vendor-specific";
            break;
        default:
            cls = @"Unknown";
            break;
    }
    
    [bpClass setClassNum:pcls[0]];
    [bpClass setSubclassNum:pcls[1]];
    [bpClass setProtocolNum:pcls[2]];
   
    [bpClass setClassName:cls];
    [bpClass setSubclassName:sub];
    [bpClass setProtocolName:protocol];
    
    return [bpClass autorelease];
}

NSString * VendorNameFromVendorID(NSString * intValueAsString) {
    static NSMutableDictionary * gVendorNamesDictionary = nil;
    NSString *vendorName;
    
    if (gVendorNamesDictionary == nil) {
        gVendorNamesDictionary = [[NSMutableDictionary dictionary] retain];
        
        NSString *vendorListString = [NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"USBVendors" ofType:@"txt"]];
        
        if (vendorListString == nil) { 
            NSLog(@"Error reading USBVendors.txt from the Resources directory");
        } else {
            NSArray *vendorsAndIDs = [vendorListString componentsSeparatedByString:@"\n"];
            if (vendorsAndIDs == nil) { 
                NSLog(@"Error parsing USBVendors.txt");
            } else {
                NSEnumerator *enumerator = [vendorsAndIDs objectEnumerator];
                NSString *vendorIDCombo;
                NSArray *aVendor;
                while ((vendorIDCombo = [enumerator nextObject])) {
                    aVendor = [vendorIDCombo componentsSeparatedByString:@"|"];
                    if (aVendor == nil || [aVendor count] < 2) { 
                        continue;
                    }
                    [gVendorNamesDictionary setObject:[aVendor objectAtIndex:1] forKey:[aVendor objectAtIndex:0]];
                }
            }
        }
    }
    
    vendorName = [gVendorNamesDictionary objectForKey:intValueAsString];
    
    return (vendorName != nil ? vendorName : @"unknown vendor");
}

void FreeString(char * cstr) {
    if (cstr != NULL) {
        free(cstr);
        cstr = NULL;
    }
}

UInt16	Swap16(void *p) {
    * (UInt16 *) p = CFSwapInt16LittleToHost(*(UInt16 *)p);
    return * (UInt16 *) p;
}

UInt32	Swap32(void *p) {
    * (UInt32 *) p = CFSwapInt32LittleToHost(*(UInt32 *)p);
    return * (UInt32 *) p;
}

UInt64	Swap64(void *p) {
    * (UInt64 *) p = CFSwapInt64LittleToHost(*(UInt64 *)p);
    return * (UInt64 *) p;
    
}

//  This function will NOT swap the results in memory.  It will
//  take a pointer to a UInt32 that looks like 0xAABBCCDD and return
//  a UInt32 that has the first 3 bytes swapped:  0x00CCBBAA
//
UInt32 Swap24(void *p) {
    UInt32 temp = CFSwapInt32LittleToHost(*(UInt32 *)p);
    return ( temp & 0x00FFFFFF);
}

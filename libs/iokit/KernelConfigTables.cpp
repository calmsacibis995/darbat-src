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


/* This list is used in IOStartIOKit.cpp to declare fake kmod_info
 * structs for kext dependencies that are built into the kernel.
 * Empty version strings get replaced with osrelease at runtime.
 */
const char * gIOKernelKmods =
"{"
   "'com.apple.kernel'                         = '';"
   "'com.apple.kpi.bsd'                        = '';"
   "'com.apple.kpi.iokit'                      = '';"
   "'com.apple.kpi.libkern'                    = '';"
   "'com.apple.kpi.mach'                       = '';"
   "'com.apple.kpi.unsupported'                = '';"
   "'com.apple.iokit.IONVRAMFamily'            = '';"
   "'com.apple.driver.AppleNMI'                = '';"
   "'com.apple.iokit.IOSystemManagementFamily' = '';"
   "'com.apple.iokit.ApplePlatformFamily'      = '';"
#ifdef L4IOKIT
   "'com.apple.iokit.IOPCIFamily' = '';"
   "'com.apple.iokit.IOStorageFamily' = '';"
   "'com.apple.driver.AppleIntelPIIXATA' = '';"
   "'com.apple.iokit.IOATAPIProtocolTransport' = '';"
   "'com.apple.iokit.IODVDStorageFamily'	= '';"
   "'com.apple.iokit.IOCDStorageFamily'		= '';"
   "'com.apple.driver.AppleI386GenericPlatform' = '';"
   "'com.apple.driver.AppleI386PCI' = '';"
   "'com.apple.driver.ApplePS2Controller' = '';"
   "'com.apple.driver.ApplePS2Keyboard' = '';"
   "'com.apple.driver.ApplePS2Mouse' = '';"
   "'com.apple.driver.Apple16X50Serial' = '';"
   "'com.apple.iokit.IOSerialFamily'	= '';"
   "'com.apple.driver.AppleSMBIOS'	= '';"
   "'com.apple.driver.AppleIntelPIIXATA'	= '';"
   "'com.apple.driver.AppleAC97AudioIntelICH'	= '';"
   "'com.apple.iokit.IOAudioFamily'	= '';"
   "'com.apple.driver.AppleAC97Audio'	= '';"
   "'com.apple.driver.AppleAC97CodecAD198x' = '';"
   "'com.apple.driver.AppleGenericPCATA' = '';"
   "'com.apple.driver.AppleIntel8255x'	= '';"
#endif
   "'com.apple.kernel.6.0'                     = '7.9.9';"
   "'com.apple.kernel.bsd'                     = '7.9.9';"
   "'com.apple.kernel.iokit'                   = '7.9.9';"
   "'com.apple.kernel.libkern'                 = '7.9.9';"
   "'com.apple.kernel.mach'                    = '7.9.9';"
"}";

#ifdef L4IOKIT
/*
 * Note for the following: in XML, the &amp; stands for an ampersand.
 * Presumably, the OSUnserializeXML will convert this into a real ampersand.
 *
 * However, in this scheme, the ampersand is represented literally.  So what
 * is taken from the project file has been modified to reflect this.
 */
#endif

const char * gIOKernelConfigTables =
"("
"   {"
"     'IOClass'         = IOPanicPlatform;"
"     'IOProviderClass' = IOPlatformExpertDevice;"
"     'IOProbeScore'    = '-1';"
"   }"
#ifdef PPC
"   ,"
"   {"
"       'IOClass'               = AppleCPU;"
"       'IOProviderClass'       = IOPlatformDevice;"
"       'IONameMatch'           = 'cpu';"
"       'IOProbeScore'          = 100:32;"
"   },"
"   {"
"       'IOClass'              = AppleNMI;"
"       'IOProviderClass'      = AppleMacIODevice;"
"       'IONameMatch'          = 'programmer-switch';"
"   },"
"   {"
"       'IOClass'               = AppleNVRAM;"
"       'IOProviderClass'       = AppleMacIODevice;"
"       'IONameMatch'           = nvram;"
"   }"
#endif /* PPC */
#ifdef i386
"   ,"
"   {"
"       'IOClass'           = AppleIntelClock;"
"       'IOProviderClass'   = IOPlatformDevice;"
"       'IONameMatch'       = intel-clock;"
"   }"
#endif /* i386 */
#ifdef L4IOKIT	/* XXX i386 specific */
"   ,"
"   {"
"	'IOClass'		= 'AppleI386CPU';"
"	'IOProviderClass'	= 'IOPlatformDevice';"
"	'IONameMatch'		= 'cpu';"
"	'IOProbeScore'		= 1000:32 ;"
"   },"
"   {"
"	'IOClass'		= 'AppleI386PlatformExpert';"
"	'IOProviderClass'	= 'IOPlatformExpertDevice';"
"	'IOProbeScore'		= 1000:32 ;"
"	'InterruptControllerName' = '8259-pic';"
"	'top-level'	= (  "
"		{ 'IOName' = 'cpu';	},"
"		{ 'IOName' = '8259-pic';	"
"		   'InterruptControllerName' = '8259-pic'; },"
"		{ 'IOName' = 'intel-clock'; },"
#if 0 	/* glee: XXX I reckon it's a little broken. */
"		{ 'IOName' = 'ps2controller'; },"
#endif
"		{ 'IOName' = 'bios'; },"
"		{ 'IOName' = 'pci'; } "
"	);"
"   },"
"   {"
"	'IOClass'		= 'AppleI386PCI';"
"	'IONameMatch'		= pci;"
"	'IOProviderClass'	= IOPlatformDevice;"
"   },"
"   {"
"	'IOClass'		= 'ApplePS2Controller';"
"	'IONameMatch'		= 'ps2controller';"
"	'IOProviderClass'	= IOPlatformDevice;"
"   },"
"   {"
"	'IOClass'		= 'ApplePS2Keyboard';"
"	'IOProviderClass'	= 'ApplePS2KeyboardDevice';"
"	'Make capslock into control' = .false.;"
"	'Swap alt and windows key' = .true.;"
"   },"
"   {"
"	'IOClass'		= 'com_apple_driver_16X50PCI';"
"	'IOKitDebug'		= .true.;"	
"	'IOPCIClassMatch'	= '0x07000000&0xFFFF0000';"
"	'IOProbeScore'		= 900:32 ;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"   },"
"   {"
"	'IOClass'		= 'IOSerialBSDClient';"
"	'IOProbeScore'		= 1000:32 ;"
"	'IOProviderClass'	= 'IOSerialStreamSync';"
"	'IOResourceMatch'	= 'IOBSD';"
"   },"
"   {"
"	'IOClass'		= 'IOSerialBSDClient';"
"	'IOProbeScore'		= 1000:32 ;"
"	'IOProviderClass'	= 'IOSerialStream';"
"	'IOResourceMatch'	= 'IOBSD';"
"   },"
"   {"
"	'IOClass'		= 'ApplePS2Mouse';"
"	'IOProviderClass'	= 'ApplePS2MouseDevice';"
"   },"
"   {"
"	'IOClass'		= 'AppleSMBIOS';"
"	'IOMatchCategory'	= 'AppleSMBIOS';"
"	'IONameMatch'		= 'bios';"
"	'IOProviderClass'	= 'IOPlatformDevice';"
"   },"
"   {"	/* ok since one matches intel-pic and the other 8259-pic */
"	'IOClass'		= 'Apple8259PICInterruptController';"
"	'IONameMatch'		= 'io-apic';"
"	'IOProviderClass'	= 'IOPlatformDevice';"
"   },"
"   {"
"	'IOClass'		= 'Apple8259PICInterruptController';"
"	'IONameMatch'		= '8259-pic';"
"	'IOProviderClass'	= 'IOPlatformDevice';"
"   },"
"   {"
"	'Controller Name'	= 'PIIX3';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIPrimaryMatch'	= '0x70108086';"
"	'IOProbeScore'		= 2000:32 ;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Supported Transfer Modes' = '0x00061d';"
"   },"
"   {"
"	'Controller Name'	= 'ICH5 ATA/100';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIPrimaryMatch'	= '0x24DB8086';"
"	'IOProbeScore'		= 2000:32 ;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Supported Transfer Modes' = '0x3f061d';"
"   },"
"   {"
"	'Controller Name'	= 'ICH5 SATA';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIPrimaryMatch'	= '0x24D18086';"
"	'IOProbeScore'		= 2000:32 ;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Serial ATA'		= .true.;"
"	'Supported Transfer Modes' = '0x3f061d';"
"   },"
"   {"
"	'Controller Name'	= 'ICH6 SATA';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIClassMatch'	= '0x01010000&0xffff0000';"
"	'IOPCIPrimaryMatch'	= '0x26528086 0x26518086';"
"	'IOProbeScore'		= 2000:32;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Serial ATA'		= .true.;"
"	'Supported Transfer Modes'	= '0x3f061d';"
"   },"
"   {"
"	'Controller Name'	= 'ICH6-M SATA';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIClassMatch'	= '0x01010000&0xffff0000';"
"	'IOPCIPrimaryMatch'	= '0x26538086';"
"	'IOProbeScore'		= 2000:32;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Serial ATA'		= .true.;"
"	'Supported Transfer Modes'	= '0x3f061d';"
"   },"
"   {"
"	'Controller Name'	= 'ICH7-M SATA';"
"	'IOClass'		= 'AppleIntelPIIXATARoot';"
"	'IOPCIClassMatch'	= '0x01060100';"
"	'IOPCIPrimaryMatch'	= '0x27c58086';"
"	'IOProbeScore'		= 2000:32;"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Serial ATA'		= .true.;"
"	'Supported Transfer Modes'	= '0x3f061d';"
"   },"
"   {"
"	'IOClass'		= 'AppleIntelPIIXPATA';"
"	'IOProbeScore'		= 800:32 ;"
"	'IOProviderClass'	= 'AppleIntelPIIXATAChannel';"
"	'Serial ATA'		= .false.;"
"   },"
"   {"
"	'IOClass'		= 'AppleIntelICHxSATA';"
"	'IOProbeScore'		= 1000:32;"
"	'IOProviderClass'	= 'AppleIntelPIIXATAChannel';"
"	'Serial ATA'		= .true.;"
"   }"
#if 0	/* nope. */
"   {"	/* Clagged from the Info.plist in AppleYukon binary driver */
"	'DescriptorPollTimer'	= '250';"
"	'IOClass'		= 'yukonosx';"
"	'IOPCIPrimaryMatch'	= '0x436211AB';"
"	'IOProviderClass'	= 'IOPCIDevice';"
"	'Model'			= 'Yukon Gigabit Adapter 88E8053';"
"	'RxRingSize'		= 256:32;"
"	'TxRingSize'		= 256:32;"
"	'WaitToCheckDelay'	= 5000:32;"
"	'WaitForLinkUp'		= 6000:32;"
"	'InitialWaitForLinkUp'	= 60000:32;"
"	'EnableLowPwr'		= 1:32;"
"	'LowPwrD1'		= .true.;"
"	'LowPwrClockDivide'	= .true.;"
"	'LowPwrPeerMin'		= 60:32;"
"	'LowPwrPeerMax'		= 240:32;"
"	'Vendor'		= 'Marvell';"
"   }"
#endif	/* yukon */
#endif	/* L4IOKIT */
")";


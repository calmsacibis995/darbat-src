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


#import <Cocoa/Cocoa.h>
#import "BusProbeController.h"
#import "KernelExtensionsController.h"
#import "IORegistryController.h"
#import "USBLoggerController.h"

@interface MainApplicationController : NSObject
{
    IBOutlet id BPController;
    IBOutlet id BusProbeOutput;
    IBOutlet id IORegController;
    IBOutlet id IORegDetailedOutputDrawer;
    IBOutlet id IORegistryOutput;
    IBOutlet id KEController;
    IBOutlet id KernelExtensionsOutput;
    IBOutlet id MainTabView;
    IBOutlet id LoggerController;
    IBOutlet id USBLoggerOutput;
}

- (IBAction)ChooseTab:(id)sender;
- (IBAction)ClearOutput:(id)sender;
- (IBAction)MarkOutput:(id)sender;
- (IBAction)Refresh:(id)sender;
- (IBAction)SaveOutput:(id)sender;
- (IBAction)ToggleIORegDetaiLDrawer:(id)sender;

- (void)tabView:(NSTabView *)tabView didSelectTabViewItem:(NSTabViewItem *)tabViewItem;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
- (void)windowWillClose:(NSNotification *)aNotification;
- (void)applicationWillTerminate:(NSNotification *)aNotification;

@end

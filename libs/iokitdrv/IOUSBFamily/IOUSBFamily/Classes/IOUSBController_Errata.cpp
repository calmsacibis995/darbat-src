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

#include <IOKit/system.h>


#include <IOKit/usb/IOUSBController.h>

#define super IOUSBBus
#define self this

/*
 This table contains the list of errata that are necessary for known
 problems with particular silicon.  The format is vendorID, deviceID,
 lowest revisionID needing errata, highest rev needing errata, errataBits.
 The result of all matches is ORed together, so more than one entry may
 match.  Typically for a given errata a list of chips revisions that
 this applies to is supplied.
 */
static ErrataListEntry  errataList[] = {
    
    {0x1095, 0x0670, 0, 0x0004,	kErrataCMDDisableTestMode | kErrataOnlySinglePageTransfers | kErrataRetryBufferUnderruns},	// CMD 670 & 670a (revs 0-4)
    {0x1045, 0xc861, 0, 0x001f, kErrataLSHSOpti},																			// Opti 1045
    {0x11C1, 0x5801, 0, 0xffff, kErrataDisableOvercurrent | kErrataLucentSuspendResume | kErrataNeedsWatchdogTimer},		// Lucent USS 302
    {0x11C1, 0x5802, 0, 0xffff, kErrataDisableOvercurrent | kErrataLucentSuspendResume | kErrataNeedsWatchdogTimer},		// Lucent USS 312
    {0x106b, 0x0019, 0, 0xffff, kErrataDisableOvercurrent | kErrataNeedsWatchdogTimer},										// Apple KeyLargo - all revs
    {0x106b, 0x0019, 0, 0, 	kErrataLucentSuspendResume },																	// Apple KeyLargo - USB Rev 0 only
    {0x106b, 0x0026, 0, 0xffff, kErrataDisableOvercurrent | kErrataLucentSuspendResume | kErrataNeedsWatchdogTimer},		// Apple Pangea, all revs
    {0x106b, 0x003f, 0, 0xffff, kErrataDisableOvercurrent | kErrataNeedsWatchdogTimer},										// Apple Intrepid, all revs
    {0x1033, 0x0035, 0, 0xffff, kErrataDisableOvercurrent | kErrataNECOHCIIsochWraparound | kErrataNECIncompleteWrite },	// NEC OHCI
    {0x1033, 0x00e0, 0, 0xffff, kErrataDisableOvercurrent | kErrataNECIncompleteWrite},										// NEC EHCI
    {0x1131, 0x1561, 0x30, 0x30, kErrataNeedsPortPowerOff },																// Philips, USB 2
    {0x11C1, 0x5805, 0x11, 0x11, kErrataAgereEHCIAsyncSched },																// Agere, Async Schedule bug
	{0x8086, 0x2658, 0x03, 0x04, kErrataICH6PowerSequencing },																// ICH6 UHCI #1
	{0x8086, 0x2659, 0x03, 0x04, kErrataICH6PowerSequencing },																// ICH6 UHCI #2
	{0x8086, 0x265A, 0x03, 0x04, kErrataICH6PowerSequencing },																// ICH6 UHCI #3
	{0x8086, 0x265B, 0x03, 0x04, kErrataICH6PowerSequencing },																// ICH6 UHCI #4
	{0x8086, 0x265C, 0x03, 0x04, kErrataICH6PowerSequencing }																// ICH6 EHCI
};

#define errataListLength (sizeof(errataList)/sizeof(ErrataListEntry))

UInt32 IOUSBController::GetErrataBits(UInt16 vendorID, UInt16 deviceID, UInt16 revisionID)
{
    ErrataListEntry	*entryPtr;
    UInt32		i, errata = 0;
    
    for(i = 0, entryPtr = errataList; i < errataListLength; i++, entryPtr++)
    {
        if (vendorID == entryPtr->vendID &&
            deviceID == entryPtr->deviceID &&
            revisionID >= entryPtr->revisionLo &&
            revisionID <= entryPtr->revisionHi)
        {
            // we match, add this errata to our list
            errata |= entryPtr->errata;
        }
    }
    return(errata);
}       



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
#ifdef L4IOKIT
/*Compile with c++ due to fucking -Werror.  Spastic piece of shit!*/
extern "C" {
#endif
/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
/*
	File:		HIDGetNextButtonInfo.c

	Contains:	HIDGetNextButtonInfo call for HID Library

	Version:	1.0d1

	Copyright:	� 2000 by Apple Computer, Inc., all rights reserved.

	File Ownership:

		DRI:				David Ferguson

		Other Contact:		Keithen Hayenga

		Technology:			technologies, usb

	Writers:

		(KH)	Keithen Hayenga

	Change History (most recent first):

	  <USB1>	 2/14/00	KH		first checked in
*/

#include "HIDLib.h"

/*
 *------------------------------------------------------------------------------
 *
 * HIDGetNextButtonInfo - Get report id and collection for a button. In keeping
 *								with USBGetNextInterface, we find the usage in the
 *								next collection, so that you can find usages that
 *								have the same usage and usage page.
 *
 *	 Input:
 *			  reportType			- HIDP_Input, HIDP_Output, HIDP_Feature
 *			  usagePage				- Page Criteria or zero
 *			  usage					- The usage to get the information for
 *			  collection			- Starting Collection Criteria or zero
 *			  preparsedDataRef		- Pre-Parsed Data
 *	 Output:
 *			  collection			- Final Collection Criteria or no change
 *			  reportID				- Report ID or no change
 *	 Returns:
 *
 *------------------------------------------------------------------------------
*/
OSStatus HIDGetNextButtonInfo
					   (HIDReportType			reportType,
						HIDUsage				usagePage,
						HIDUsage				usage,
						UInt32 *				collection,
						UInt8 *					reportID,
						HIDPreparsedDataRef		preparsedDataRef)
{
	HIDPreparsedDataPtr ptPreparsedData = (HIDPreparsedDataPtr)preparsedDataRef;
	HIDReportItem *ptReportItem;
	UInt32 iCollection;
	UInt32 newCollection = 0xFFFFFFFF;
	int iR;
	UInt8 newReportID = 0;
	OSStatus iStatus = kHIDUsageNotFoundErr;

	//Disallow Null Pointers

	if ((ptPreparsedData == NULL) || (collection == NULL) || (reportID == NULL))
		return kHIDNullPointerErr;
	if (ptPreparsedData->hidTypeIfValid != kHIDOSType)
		return kHIDInvalidPreparsedDataErr;

	// The Collection must be in range

	iCollection = *collection;
	// Umm... an unsigned number can never be less than 0!
	if ((iCollection < 0) || (iCollection >= ptPreparsedData->collectionCount))
		return kHIDBadParameterErr;

	// HIDGetNextButtonInfo is different from HIDGetButton in how it treats
	// the collection parameter. HIDGetButton will only look at report items that
	// are within the collection and can therefore limit it's searches to starting at
	// ptPreparsedData->collections[iCollection]->firstReportItem and only check
	// ptPreparsedData->collections[iCollection]->reportItemCount. Since we want to 
	// find the NEXT collection as well, we need to cycle through all of the reports.

	for (iR = 0; iR < ptPreparsedData->reportItemCount; iR++)
	{
		SInt32 minUsage;
		SInt32 maxUsage;
		HIDP_UsageItem thisUsage;

		ptReportItem = &ptPreparsedData->reportItems[iR];
		
		thisUsage = ptPreparsedData->usageItems[ptReportItem->firstUsageItem];

		if (thisUsage.isRange)
		{
			minUsage = thisUsage.usageMinimum;
			maxUsage = thisUsage.usageMaximum;
		}
		else
		{
			minUsage = thisUsage.usage;
			maxUsage = thisUsage.usage;
		}

		if (ptReportItem->reportType == reportType &&
			(usagePage == 0 || ptReportItem->globals.usagePage == usagePage) &&
			(usage >= minUsage && usage <= maxUsage) &&
			ptReportItem->parent > iCollection &&
			HIDIsButton(ptReportItem, preparsedDataRef))
		{
			if (ptReportItem->parent < newCollection)
			{
				newCollection = ptReportItem->parent;
				newReportID = iR;
				iStatus = noErr;
			}
		}
	}
		
	if (iStatus == noErr)
	{
		*reportID = newReportID;
		*collection = newCollection;
	}

	return iStatus;
}
#ifdef L4IOKIT
};
#endif

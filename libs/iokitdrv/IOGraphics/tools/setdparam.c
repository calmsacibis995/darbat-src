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
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
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
/*
cc -g -o /tmp/setdparam setdparam.c -framework ApplicationServices -framework IOKit -Wall
*/

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char * argv[])
{
    io_service_t 	service;
    CGError		err;
    int			i;
    CGDisplayCount	max;
    CGDirectDisplayID	displayIDs[8];
    CFStringRef		key;
    float 		value;

    err = CGGetOnlineDisplayList(8, displayIDs, &max);
    if(err != kCGErrorSuccess)
        exit(1);
    if(max > 8)
        max = 8;

    if( argc < 2)
	key = CFSTR(kIODisplayBrightnessKey);
    else
	key = CFStringCreateWithCString( kCFAllocatorDefault, argv[1],
					kCFStringEncodingMacRoman );


    for(i = 0; i < max; i++ ) {

        service = CGDisplayIOServicePort(displayIDs[i]);

        err = IODisplayGetFloatParameter(service, kNilOptions, key, &value);
        printf("Display %x: IODisplayGetFloatParameter(%d), %f\n", displayIDs[i], err, value);
        if( kIOReturnSuccess != err)
            continue;

	if (argc < 3)
            continue;

	sscanf( argv[argc - 1], "%f", &value );
        err = IODisplaySetFloatParameter(service, kNilOptions, key, value);
        printf("IODisplaySetFloatParameter(%d, %f)\n", err, value);
        if( kIOReturnSuccess != err)
            continue;
    }
    
    exit(0);
    return(0);
}


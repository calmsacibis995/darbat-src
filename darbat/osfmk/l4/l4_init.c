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
#include <platforms.h>
#include <mach_kdb.h>

#include <string.h>
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <mach/machine.h>
#include <mach/time_value.h>
#include <kern/spl.h>
#include <kern/assert.h>
#include <kern/debug.h>
#include <kern/misc_protos.h>
#include <kern/startup.h>
#include <kern/clock.h>
#include <kern/cpu_data.h>
#include <kern/machine.h>
#include <kern/thread.h>

/* XXX: header */
void l4_init(void);

/* XXX */
extern void cpu_init(void);
extern void machine_startup(void);

/* default unknown - but let the build system set it */
#include <l4/kdebug.h>
#include "video_config.h"

#ifndef VID_DEFAULT
#define VID_DEFAULT VID_UNKNOWN
#endif

int darbat_video_mode = VID_DEFAULT;

/* order must match defines in video_config.h */
const char *vid_names[] = { 	"Mac Mini",
				"17\" iMac",
				"20\" iMac",
				"Macbook",
				"Macbook Pro 15\"",
				"Macbook Pro 17\"" };

void l4_pick_video(void);
void
l4_pick_video(void)
{
	/* XXX: set video mode */
	int c, i;
	while( darbat_video_mode < VID_MIN
	       || darbat_video_mode > VID_MAX )
	{
		printf( "\n\n\n**** Please select your video mode:\n" );
		for( i = 0; i < VID_MAX; i++ )
			printf( "%d) %s\n", i + 1, vid_names[i] );

		printf( "Number: " );
		c = L4_KDB_ReadChar_Blocked();
		printf( "%c\n", c );
		darbat_video_mode = c - '0';
	}
	printf( "Using video '%s'\n", vid_names[darbat_video_mode-VID_MIN] );
}

void
l4_init(void)
{
	master_cpu = 0;
	cpu_data_alloc(TRUE);
	cpu_init();
	// postcode(CPU_INIT_D);

	printf( "calling processor_bootstrap\n" );
	processor_bootstrap();
	printf( "called processor_bootstrap\n" );

	/*
	 * Set up initial thread so current_thread() works early on
	 */
	thread_bootstrap();
	// postcode(THREAD_BOOTSTRAP_D);

	machine_startup();
}


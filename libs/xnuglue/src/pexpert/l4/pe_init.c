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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
/*
 * file: pe_init.c
 *    i386 platform expert initialization.
 */
#ifdef L4IOKIT
/*
 * XXXglee: this doesn't belong here ... since this is arch-dependent
 *
 */

#include <kern/kalloc.h>	/* kalloc, kfree */
#include <stdio.h>
#include <string.h>

/*
 * XXX: hack
 */
extern void l4_init_bootargs(void *);

/*
 * should be in pexpert, protos.h but can't be bothered now XXX
 *
 */

extern int StartIOKit( void * p1, void * p2, void * p3, void * p4);

#endif

#include <sys/types.h>
#include <mach/vm_param.h>
#include <pexpert/protos.h>
#include <pexpert/pexpert.h>
#include <pexpert/boot.h>
#include <pexpert/device_tree.h>
#include <pexpert/pe_images.h>
#include <kern/sched_prim.h>

#ifdef L4IOKIT
#include <assert.h>		/* needed for assert .. */
#endif

#include "fakePPCStructs.h"
#include "fakePPCDeviceTree.h"
#ifndef L4IOKIT
#include "boot_images.h"

/* extern references */
extern void pe_identify_machine(void * args);
extern void initialize_screen(void *, unsigned int);

/* Local references */
static int         PE_fb_mode  = TEXT_MODE;
#endif

/* private globals */
PE_state_t  PE_state;
dt_data     gMemoryMapNode;
dt_data     gDriversProp;
dt_data     gRootpathProp;
dt_data     gCompatibleProp;

#ifndef L4IOKIT
/* Clock Frequency Info */
clock_frequency_info_t gPEClockFrequencyInfo;

int PE_initialize_console( PE_Video * info, int op )
{
    static int   last_console = -1;
    Boot_Video   bootInfo;
    Boot_Video * bInfo;

    /*
     * Refuse changes from outside pexpert.
     * The video mode setup by the booter cannot be changed.
     */
    if ( info )
    {
        bootInfo.v_baseAddr = info->v_baseAddr;
        bootInfo.v_rowBytes	 = info->v_rowBytes;
        bootInfo.v_width     = info->v_width;
        bootInfo.v_height    = info->v_height;
        bootInfo.v_depth     = info->v_depth;
        bInfo = &bootInfo;
        if (info == &PE_state.video) {
            bootInfo.v_display  = PE_fb_mode;
        } else {
            bootInfo.v_display  = GRAPHICS_MODE;
        }
    }
    else
        bInfo = 0;

    switch ( op ) {

        case kPEDisableScreen:
            initialize_screen((void *) bInfo, op);
#ifdef FIXME
            last_console = switch_to_serial_console();
#endif
            kprintf("kPEDisableScreen %d\n", last_console);
            break;

        case kPEEnableScreen:
            initialize_screen((void *) bInfo, op);
            kprintf("kPEEnableScreen %d\n", last_console);
#ifdef FIXME
            if( last_console != -1)
                switch_to_old_console( last_console);
#endif
            break;
	
        default:
            initialize_screen((void *) bInfo, op);
            break;
    }

    return 0;
}
#endif

void PE_init_iokit(void)
{
    long * dt;
    int    i;
    KernelBootArgs_t *kap = (KernelBootArgs_t *)PE_state.bootArgs;
    enum { kMaxBootVar = 128 };
    char *rdValue, *platformValue;
        
    typedef struct {
        char            name[32];
        unsigned long   length;
        unsigned long   value[2];
    } DriversPackageProp;

#ifndef L4IOKIT
    PE_init_kprintf(TRUE);
    PE_init_printf(TRUE);
#endif

    /*
     * Update the fake device tree with the driver information provided by
     * the booter.
     */

    gDriversProp.length   = kap->numBootDrivers * sizeof(DriversPackageProp);
    gMemoryMapNode.length = 2 * sizeof(long);

    rdValue = kalloc(kMaxBootVar);
#ifndef L4IOKIT	/* PE_parse_boot_arg not implemeted in xnu_glue */
    if ( PE_parse_boot_arg("rd", rdValue) ) {
        if (*rdValue == '*') {
            gRootpathProp.address = (rdValue + 1);
        } else {
            gRootpathProp.address = rdValue;
        }
        strcat(rdValue, ",");
    } else {
#endif
        gRootpathProp.address = rdValue;
	rdValue[0] = '\0';
#ifndef L4IOKIT
    }
    strcat(rdValue, kap->bootFile);
#else
    strcat(rdValue, "disk0s1,/Iguana");		/* hehe :) */
#endif
    gRootpathProp.length = strlen(rdValue) + 1;

    platformValue = kalloc(kMaxBootVar);
#ifndef L4IOKIT
    if ( ! PE_parse_boot_arg("platform", platformValue) ) {
        strcpy(platformValue, kDefaultPlatformName);
    }
#endif
#ifdef L4IOKIT
    strcpy(platformValue, kDefaultPlatformName);	// disgusting hack for now 
#endif
    gCompatibleProp.address = platformValue;
    gCompatibleProp.length = strlen(platformValue) + 1;

#ifdef L4IOKIT
    printf("before createdt(): drivers prop address %p\n",
	(void *)gDriversProp.address);
#endif
    dt = (long *) createdt( fakePPCDeviceTree,
#ifdef L4IOKIT
            (long *) &((boot_args*)PE_state.fakePPCBootArgs)->deviceTreeLength );
#else
            	  &((boot_args*)PE_state.fakePPCBootArgs)->deviceTreeLength );
#endif /* L4IOKIT*/

    kfree(rdValue, kMaxBootVar);
    kfree(platformValue, kMaxBootVar);


    if ( dt )
    {
        DriversPackageProp * prop = (DriversPackageProp *) gDriversProp.address;

#ifdef L4IOKIT
	/*
	 * this address seems seedy??  How the hell does it arrive at this?
	 * it initializes it as a macro and that's it???  What about memory
	 * allocation??  Or perhaps we should allocate some memory for this??
	 */
	printf("gDriversProp.address = %p\n", (void *)gDriversProp.address);
#endif
        /* Copy driver info in kernBootStruct to fake device tree */

        for ( i = 0; i < kap->numBootDrivers; i++, prop++ )
        {
            switch ( kap->driverConfig[i].type )
            {
                case kBootDriverTypeKEXT:
                    sprintf(prop->name, "Driver-%lx", kap->driverConfig[i].address);
                    break;
                
                 case kBootDriverTypeMKEXT:
                    sprintf(prop->name, "DriversPackage-%lx", kap->driverConfig[i].address);
                    break;

                default:
                    sprintf(prop->name, "DriverBogus-%lx", kap->driverConfig[i].address);
                    break;
            }
            prop->length   = sizeof(prop->value);
            prop->value[0] = kap->driverConfig[i].address;
            prop->value[1] = kap->driverConfig[i].size;
        }

        *((long *)gMemoryMapNode.address) = kap->numBootDrivers + 1;
    }

    /* Setup powermac_info and powermac_machine_info structures */

    ((boot_args*)PE_state.fakePPCBootArgs)->deviceTreeP	= (unsigned long *) dt;
    ((boot_args*)PE_state.fakePPCBootArgs)->topOfKernelData = (unsigned long) kalloc(0x2000);

    /* 
     * Setup the OpenFirmware Device Tree routines
     * so the console can be found and the right I/O space 
     * can be used..
     */
    DTInit(dt);

#ifndef L4IOKIT
    /*
     * Fetch the CLUT and the noroot image.
     */
    bcopy( (void *) (uintptr_t) bootClut, (void *) appleClut8, sizeof(appleClut8) );

    default_noroot.width  = kFailedBootWidth;
    default_noroot.height = kFailedBootHeight;
    default_noroot.dx     = 0;
    default_noroot.dy     = kFailedBootOffset;
    default_noroot_data   = failedBootPict;
    
    /*
     * Initialize the panic UI
     */
    panic_ui_initialize( (unsigned char *) appleClut8 );

    /*
     * Initialize the spinning wheel (progress indicator).
     */
    vc_progress_initialize( &default_progress, default_progress_data,
                            (unsigned char *) appleClut8 );
#endif

    (void) StartIOKit( (void*)dt, PE_state.bootArgs, 0, 0);
}

void PE_init_platform(boolean_t vm_initialized, void * args)
{
#ifndef L4IOKIT
	if (PE_state.initialized == FALSE)
	{
	    KernelBootArgs_t *kap = (KernelBootArgs_t *) args;
#else
	    KernelBootArgs_t *kap = kalloc(sizeof(KernelBootArgs_t));
	    assert(kap);
	    memset(kap, 0, sizeof(KernelBootArgs_t));
	    /* XXX: hack -gl */
	    l4_init_bootargs(kap);
	    args = (void *) kap;
#endif
	    PE_state.initialized        = TRUE;
	    PE_state.bootArgs           = args;
#ifndef L4IOKIT
	    PE_state.video.v_baseAddr   = kap->video.v_baseAddr;
	    PE_state.video.v_rowBytes   = kap->video.v_rowBytes;
	    PE_state.video.v_height     = kap->video.v_height;
	    PE_state.video.v_width      = kap->video.v_width;
	    PE_state.video.v_depth      = kap->video.v_depth;
	    PE_state.video.v_display    = kap->video.v_display;
	    PE_fb_mode                  = kap->graphicsMode;
#endif
	    PE_state.fakePPCBootArgs    = (boot_args *)&fakePPCBootArgs;
	    ((boot_args *)PE_state.fakePPCBootArgs)->machineType	= 386;

#ifndef L4IOKIT
        if (PE_fb_mode == TEXT_MODE)
        {
            /* Force a text display if the booter did not setup a
             * VESA frame buffer.
             */
            PE_state.video.v_display = 0;
        }
    }

    if (!vm_initialized)
    {
		/* Hack! FIXME.. */ 
        outb(0x21, 0xff);   /* Maskout all interrupts Pic1 */
        outb(0xa1, 0xff);   /* Maskout all interrupts Pic2 */
 
        pe_identify_machine(args);
    }
    else
    {
        pe_init_debug();
    }
#endif
}

#ifndef L4IOKIT
void PE_create_console( void )
{
    if ( PE_state.video.v_display )
        PE_initialize_console( &PE_state.video, kPEGraphicsMode );
    else
        PE_initialize_console( &PE_state.video, kPETextMode );
}

int PE_current_console( PE_Video * info )
{
    *info = PE_state.video;

    if ( PE_fb_mode == TEXT_MODE )
    {
        /*
         * FIXME: Prevent the IOBootFrameBuffer from starting up
         * when we are in Text mode.
         */
        info->v_baseAddr = 0;
        
        /*
         * Scale the size of the text screen from characters
         * to pixels.
         */
        info->v_width  *= 8;   // CHARWIDTH
        info->v_height *= 16;  // CHARHEIGHT
    }

    return (0);
}

void PE_display_icon( __unused unsigned int flags, __unused const char * name )
{
    if ( default_noroot_data )
        vc_display_icon( &default_noroot, default_noroot_data );
}

extern boolean_t PE_get_hotkey( __unused unsigned char key )
{
    return (FALSE);
}

static timebase_callback_func gTimebaseCallback;

void PE_register_timebase_callback(timebase_callback_func callback)
{
    gTimebaseCallback = callback;
  
    PE_call_timebase_callback();
}

void PE_call_timebase_callback(void)
{
  struct timebase_freq_t timebase_freq;
  unsigned long          num, den, cnt;
  
  num = gPEClockFrequencyInfo.bus_clock_rate_num * gPEClockFrequencyInfo.bus_to_dec_rate_num;
  den = gPEClockFrequencyInfo.bus_clock_rate_den * gPEClockFrequencyInfo.bus_to_dec_rate_den;
  
  cnt = 2;
  while (cnt <= den) {
    if ((num % cnt) || (den % cnt)) {
      cnt++;
      continue;
    }
    
    num /= cnt;
    den /= cnt;
  }
  
  timebase_freq.timebase_num = num;
  timebase_freq.timebase_den = den;
  
  if (gTimebaseCallback) gTimebaseCallback(&timebase_freq);
}

/*
 * The default (non-functional) PE_poll_input handler.
 */
static int
PE_stub_poll_input(__unused unsigned int options, char * c)
{
    *c = 0xff;
    return 1;  /* 0 for success, 1 for unsupported */
}

/*
 * Called by the kernel debugger to poll for keyboard input.
 * Keyboard drivers may replace the default stub function
 * with their polled-mode input function.
 */
int (*PE_poll_input)(unsigned int options, char * c)
	= PE_stub_poll_input;


#endif

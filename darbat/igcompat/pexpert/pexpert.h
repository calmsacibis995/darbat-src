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

#ifndef __IG_PEXPERT_H__
#define __IG_PEXPERT_H__

typedef void *cpu_id_t;


struct clock_frequency_info_t {
  unsigned long bus_clock_rate_hz;
  unsigned long cpu_clock_rate_hz;
  unsigned long dec_clock_rate_hz;
  unsigned long bus_clock_rate_num;
  unsigned long bus_clock_rate_den;
  unsigned long bus_to_cpu_rate_num;
  unsigned long bus_to_cpu_rate_den;
  unsigned long bus_to_dec_rate_num;
  unsigned long bus_to_dec_rate_den;
  unsigned long timebase_frequency_hz;
  unsigned long timebase_frequency_num;
  unsigned long timebase_frequency_den;
  unsigned long long bus_frequency_hz;
  unsigned long long bus_frequency_min_hz;
  unsigned long long bus_frequency_max_hz;
  unsigned long long cpu_frequency_hz;
  unsigned long long cpu_frequency_min_hz;
  unsigned long long cpu_frequency_max_hz;
};

typedef struct clock_frequency_info_t clock_frequency_info_t;

extern clock_frequency_info_t gPEClockFrequencyInfo;

struct PE_Video {
        unsigned long   v_baseAddr;     /* Base address of video memory */
        unsigned long   v_rowBytes;     /* Number of bytes per pixel row */
        unsigned long   v_width;        /* Width */
        unsigned long   v_height;       /* Height */
        unsigned long   v_depth;        /* Pixel Depth */
        unsigned long   v_display;      /* Text or Graphics */
	char		v_pixelFormat[64];
	long		v_resv[ 4 ];
};

typedef struct PE_Video       PE_Video;

char *PE_boot_args(void);


int PE_initialize_console( PE_Video * info, int op );

#define kPETextScreen		3

extern int PE_current_console(PE_Video *info);

extern boolean_t PE_parse_boot_arg(
	const char	*arg_string,
	void    	*arg_ptr);


#endif /* __IG_PEXPERT_H__ */

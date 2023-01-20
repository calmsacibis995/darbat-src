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
#include <stdio.h>
#include <igcompat/compat.h>
#include <l4/types.h>
#include <sys/param.h>

#include <igcompat/timer.h>

#define MAX_TGB_TIME_SAMPLES 4000
uint64_t mach_absolute_time(void);
int tgb_timer_index = 0;

uint64_t tgb_times[MAX_TGB_TIME_SAMPLES];
char *tgb_files[MAX_TGB_TIME_SAMPLES];
int tgb_lines[MAX_TGB_TIME_SAMPLES];

void tgb_time_start(void)
{
    tgb_timer_index = 0;
    tgb_time(__FILE__, __LINE__);
}

void tgb_time(char *file, int line)
{
    uint64_t c;
    __asm__ __volatile__(
    "rdtsc\n\t"
    "movl %%eax,0(%0)\n\t"
    "movl %%edx,4(%0)"
    : : "r" (&c) : "eax", "edx");

    if(tgb_timer_index >= MAX_TGB_TIME_SAMPLES)
    {
        printf("TOO MANY TIME SAMPLES\n");
        return;
    }
    tgb_times[tgb_timer_index] = c;
    tgb_files[tgb_timer_index] = file;
    tgb_lines[tgb_timer_index] = line;
    tgb_timer_index++;
    
}

void tgb_print_time(void)
{
    int i;
    for(i=0;i<tgb_timer_index;i++)
    {
        printf("times[%d] is %llu, delta is %llu\n",
                i, tgb_times[i], (i == 0) ? 0 : tgb_times[i] - tgb_times[i-1]);
        printf("@ %s: %d\n", tgb_files[i], tgb_lines[i]);
    }
    printf("total delta is %llu\n", tgb_times[tgb_timer_index-1] - tgb_times[0]);
}

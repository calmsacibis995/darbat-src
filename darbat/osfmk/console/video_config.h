/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-07-10.
 *
 * @NICTA_MODIFICATIONS_END@
 */

/* the video mode we want to run in */
extern int darbat_video_mode;

/* various options we support */
#define VID_UNKNOWN  0x0
#define VID_MAC_MINI 0x1
#define VID_IMAC_17  0x2
#define VID_IMAC_20  0x3
#define VID_MACBOOK  0x4
#define VID_MBP_15   0x5
#define VID_MBP_17   0x6

#define VID_MIN VID_MAC_MINI
#define VID_MAX VID_MBP_17


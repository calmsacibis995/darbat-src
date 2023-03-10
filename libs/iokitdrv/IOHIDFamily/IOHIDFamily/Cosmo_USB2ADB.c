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

/* Cosmo_USB2ADB.c
 *  	Copyright Apple Computers, Inc., 1998
 * Created hastily on 12/2/98 by Adam Wang
 * This file does a quick map of USB scan codes to ADB scan codes, based on 
 * the Cosmo USB Tables 1.0
 * I'm not sure what some of the Norsi key conflicts with standard ADB keyboards are.
 */
#define DEADKEY 0x80

unsigned char hid_usb_2_adb_keymap[] = 
{
	DEADKEY,	// 0
	DEADKEY,	// 1
	DEADKEY,	// 2
	DEADKEY,	// 3
	0x00,	// 4
	0x0b,	// 5
	0x08,	// 6
	0x02,	// 7
	0x0e,	// 8
	0x03,	// 9
	0x05,	// a
	0x04,	// b
	0x22,	// c
	0x26,	// d
	0x28,	// e
	0x25,	// f
	0x2e,	// 10
	0x2d,	// 11
	0x1f,	// 12
	0x23,	// 13
	0x0c,	// 14
	0x0f,	// 15
	0x01,	// 16
	0x11,	// 17
	0x20,	// 18
	0x09,	// 19
	0x0d,	// 1a
	0x07,	// 1b
	0x10,	// 1c
	0x06,	// 1d
	0x12,	// 1e
	0x13,	// 1f
	0x14,	// 20
	0x15,	// 21
	0x17,	// 22
	0x16,	// 23
	0x1a,	// 24
	0x1c,	// 25
	0x19,	// 26
	0x1d,	// 27
	0x24,	// 28
	0x35,	// 29
	0x33,	// 2a
	0x30,	// 2b
	0x31,	// 2c
	0x1b,	// 2d
	0x18,	// 2e
	0x21,	// 2f
	0x1e,	// 30
	0x2a,	// 31
	0x2a,	// 32
	0x29,	// 33
	0x27,	// 34
	0x32,	// 35
	0x2b,	// 36
	0x2f,	// 37
	0x2c,	// 38
	0x39,	// 39
	0x7a,	// 3a
	0x78,	// 3b
	0x63,	// 3c
	0x76,	// 3d
	0x60,	// 3e
	0x61,	// 3f
	0x62,	// 40
	0x64,	// 41
	0x65,	// 42
	0x6d,	// 43
	0x67,	// 44
	0x6f,	// 45
	0x69,	// 46
	0x6b,	// 47
	0x71,	// 48
	0x72,	// 49
	0x73,	// 4a
	0x74,	// 4b
	0x75,	// 4c
	0x77,	// 4d
	0x79,	// 4e
	0x7c,	// 4f Right arrow key, raw is 0x3c, virtual ADB is 0x7c
	0x7b,	// 50 Left arrow key, raw is 0x3b, virtual ADB is 0x7b
	0x7d,	// 51 Down arrow, raw is 0x3d, virtual is 0x7d
	0x7e,	// 52 Up arrow key, raw is 0x3e, virtual is 0x7e
	0x47,	// 53
	0x4b,	// 54
	0x43,	// 55
	0x4e,	// 56
	0x45,	// 57
	0x4c,	// 58 Not on Cosmo, but is 0x6A for JIS????
	0x53,	// 59
	0x54,	// 5a
	0x55,	// 5b
	0x56,	// 5c
	0x57,	// 5d
	0x58,	// 5e
	0x59,	// 5f
	0x5b,	// 60
	0x5c,	// 61
	0x52,	// 62
	0x41,	// 63
	0x0a,	// 64   ISO only
	0x6e,	// 65   Microsoft Winodows95 key
	0x7f,	// 66   This is the power key, scan code in ADB is 7f 7f, not 7f ff
	0x51,	// 67
	0x69,	// 68  F13 on Andy keyboards
	0x6b,	// 69  F14 on Andy keyboards
	0x71,	// 6a  F15 on Andy keyboards
	0x6a,	// 6b
	DEADKEY,	// 6c
	DEADKEY,	// 6d
	DEADKEY,	// 6e
	DEADKEY,	// 6f
	DEADKEY,	// 70
	DEADKEY,	// 71
	DEADKEY,	// 72
	DEADKEY,	// 73
	DEADKEY,	// 74
	0x72,		// 75
	DEADKEY,	// 76
	DEADKEY,	// 77
	DEADKEY,	// 78
	DEADKEY,	// 79
	DEADKEY,	// 7a
	DEADKEY,	// 7b
	DEADKEY,	// 7c
	DEADKEY,	// 7d
	DEADKEY,	// 7e
	0x4a,	// 7f Norsi Mute, or maybe 0x4a
	0x48,	// 80 Norsi volume up, otherwise is 0x48 in ADB
	0x49,	// 81 Norsi volume down
	DEADKEY,	// 82
	DEADKEY,	// 83
	DEADKEY,	// 84
	0x5f,	// 85  , JIS only
	DEADKEY,	// 86
	0x5e,	// 87  Ro (JIS)
	DEADKEY,	// 88
	0x5d,	// 89  Yen (JIS)
	DEADKEY,	// 8a
	DEADKEY,	// 8b
	DEADKEY,	// 8c
	DEADKEY,	// 8d
	DEADKEY,	// 8e
	DEADKEY,	// 8f
	0x68,	// 90  Kana
	0x66,	// 91  Eisu
	DEADKEY,	// 92
	DEADKEY,	// 93
	DEADKEY,	// 94
	DEADKEY,	// 95
	DEADKEY,	// 96
	DEADKEY,	// 97
	DEADKEY,	// 98
	DEADKEY,	// 99
	DEADKEY,	// 9a
	DEADKEY,	// 9b
	DEADKEY,	// 9c
	DEADKEY,	// 9d
	DEADKEY,	// 9e
	DEADKEY,	// 9f
	DEADKEY,	// a0
	DEADKEY,	// a1
	DEADKEY,	// a2
	DEADKEY,	// a3
	DEADKEY,	// a4
	DEADKEY,	// a5
	DEADKEY,	// a6
	DEADKEY,	// a7
	DEADKEY,	// a8
	DEADKEY,	// a9
	DEADKEY,	// aa
	DEADKEY,	// ab
	DEADKEY,	// ac
	DEADKEY,	// ad
	DEADKEY,	// ae
	DEADKEY,	// af
	DEADKEY,	// b0
	DEADKEY,	// b1
	DEADKEY,	// b2
	DEADKEY,	// b3
	DEADKEY,	// b4
	DEADKEY,	// b5
	DEADKEY,	// b6
	DEADKEY,	// b7
	DEADKEY,	// b8
	DEADKEY,	// b9
	DEADKEY,	// ba
	DEADKEY,	// bb
	DEADKEY,	// bc
	DEADKEY,	// bd
	DEADKEY,	// be
	DEADKEY,	// bf
	DEADKEY,	// c0
	DEADKEY,	// c1
	DEADKEY,	// c2
	DEADKEY,	// c3
	DEADKEY,	// c4
	DEADKEY,	// c5
	DEADKEY,	// c6
	DEADKEY,	// c7
	DEADKEY,	// c8
	DEADKEY,	// c9
	DEADKEY,	// ca
	DEADKEY,	// cb
	DEADKEY,	// cc
	DEADKEY,	// cd
	DEADKEY,	// ce
	DEADKEY,	// cf
	DEADKEY,	// d0
	DEADKEY,	// d1
	DEADKEY,	// d2
	DEADKEY,	// d3
	DEADKEY,	// d4
	DEADKEY,	// d5
	DEADKEY,	// d6
	DEADKEY,	// d7
	DEADKEY,	// d8
	DEADKEY,	// d9
	DEADKEY,	// da
	DEADKEY,	// db
	DEADKEY,	// dc
	DEADKEY,	// dd
	DEADKEY,	// de
	DEADKEY,	// df
	0x3b,	// e0 Left Control.  raw is 0x36, virtual is 0x3b
	0x38,	// e1 Left Shift
	0x3a,	// e2 Left option/alt key
	0x37,	// e3 Left command key
	0x3e,	// e4 Right Control, use 0x3e virtual 
	0x3c,	// e5 Right Shift, use 0x3c virtual
	0x3d,	// e6 Right Option, use 0x3d virtual
	0x36,	// e7 Right Command, use 0x36 virtual
	DEADKEY,	// e8
	DEADKEY,	// e9
	DEADKEY,	// ea
	DEADKEY,	// eb
	DEADKEY,	// ec
	DEADKEY,	// ed
	DEADKEY,	// ee
	DEADKEY,	// ef
	DEADKEY,	// f0
	DEADKEY,	// f1
	DEADKEY,	// f2
	DEADKEY,	// f3
	DEADKEY,	// f4
	DEADKEY,	// f5
	DEADKEY,	// f6
	DEADKEY,	// f7
	DEADKEY,	// f8
	DEADKEY,	// f9
	DEADKEY,	// fa
	DEADKEY,	// fb
	DEADKEY,	// fc
	DEADKEY,	// fd
	DEADKEY,	// fe
	DEADKEY,	// ff
	0	//Final one
};


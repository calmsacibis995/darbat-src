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
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
enum PMLogEnum {
    kPMLogSetParent = 1,		//  1	0x05100004
    kPMLogAddChild,			//  2	0x05100008
    kPMLogRemoveChild,			//  3	0x0510000c
    kPMLogControllingDriver,		//  4	0x05100010
    kPMLogControllingDriverErr1,	//  5	0x05100014 - bad power state array version
    kPMLogControllingDriverErr2,	//  6	0x05100018 - too many power states
    kPMLogControllingDriverErr3,	//  7	0x0510001c - not a real IOPMDriver
    kPMLogControllingDriverErr4,	//  8	0x05100020 - power state change in progress
    kPMLogInterestedDriver,		//  9	0x05100024
    kPMLogAcknowledgeErr1,		// 10	0x05100028 - unknown entity called acknowledgePowerChange
    kPMLogChildAcknowledge,		// 11	0x0510002c
    kPMLogDriverAcknowledge,		// 12	0x05100030 - interested driver acknowledges
    kPMLogAcknowledgeErr2,		// 13	0x05100034 - object has already acked
    kPMLogAcknowledgeErr3,		// 14	0x05100038 - not expecting any acks
    kPMLogAcknowledgeErr4,		// 15	0x0510003c - not expecting acknowledgeSetPowerState
    kPMLogDriverAcknowledgeSet,		// 16	0x05100040 - controlling driver acknowledges
    kPMLogWillChange,			// 17	0x05100044
    kPMLogDidChange,			// 18	0x05100048
    kPMLogRequestDomain,		// 19	0x0510004c
    kPMLogMakeUsable,			// 20	0x05100050
    kPMLogChangeStateTo,		// 21	0x05100054
    kPMLogChangeStateToPriv,		// 22	0x05100058
    kPMLogSetAggressiveness,		// 23	0x0510005c
    kPMLogCriticalTemp,			// 24	0x05100060
    kPMLogOverrideOn,			// 25	0x05100064
    kPMLogOverrideOff,			// 26	0x05100068
    kPMLogEnqueueErr,			// 27	0x0510006c - change queue overflow
    kPMLogCollapseQueue,		// 28	0x05100070
    kPMLogChangeDone,			// 29	0x05100074
    kPMLogCtrlDriverTardy,		// 30	0x05100078 - controlling driver didn't acknowledge
    kPMLogIntDriverTardy,		// 31	0x0510007c - interested driver didn't acknowledge
    kPMLogStartAckTimer,		// 32	0x05100080
    kPMLogStartParentChange,		// 33	0x05100084
    kPMLogAmendParentChange,		// 34	0x05100088
    kPMLogStartDeviceChange,		// 35	0x0510008c
    kPMLogRequestDenied,		// 36	0x05100090 - parent denied domain state change request
    kPMLogControllingDriverErr5,	// 37	0x05100094 - zero power states or we already have a driver with more power states
    kPMLogProgramHardware,		// 38	0x05100098
    kPMLogInformDriverPreChange,	// 39	0x0510009c
    kPMLogInformDriverPostChange,	// 40	0x051000a0
    kPMLogRemoveDriver,			// 41	0x051000a4
    kPMLogSetIdleTimerPeriod,		// 42	0x051000a8
    kPMLogSystemWake,			// 43	0x051000ac
    kPMLogAcknowledgeErr5,		// 44	0x051000b0
    kPMLogClientAcknowledge,		// 45	0x051000b4
    kPMLogClientTardy,			// 46	0x051000b8 - application didn't acknowledge
    kPMLogClientCancel,			// 47	0x051000bc
    kPMLogClientNotify,			// 48	0x051000c0 - client sent a notification
    kPMLogAppNotify,			// 49	0x051000c4 - application sent a notification
    kIOPMlogLastEvent
};

// Deprecated Power Management Logging Constants
#define PMlogSetParent			kPMLogSetParent
#define PMlogAddChild			kPMLogAddChild
#define PMlogRemoveChild		kPMLogRemoveChild
#define PMlogControllingDriver		kPMLogControllingDriver
#define PMlogControllingDriverErr1	kPMLogControllingDriverErr1
#define PMlogControllingDriverErr2	kPMLogControllingDriverErr2
#define PMlogControllingDriverErr3	kPMLogControllingDriverErr3
#define PMlogControllingDriverErr4	kPMLogControllingDriverErr4
#define PMlogInterestedDriver		kPMLogInterestedDriver
#define PMlogAcknowledgeErr1		kPMLogAcknowledgeErr1
#define PMlogChildAcknowledge		kPMLogChildAcknowledge
#define PMlogDriverAcknowledge		kPMLogDriverAcknowledge
#define PMlogAcknowledgeErr2		kPMLogAcknowledgeErr2
#define PMlogAcknowledgeErr3		kPMLogAcknowledgeErr3
#define PMlogAcknowledgeErr4		kPMLogAcknowledgeErr4
#define PMlogDriverAcknowledgeSet	kPMLogDriverAcknowledgeSet
#define PMlogWillChange			kPMLogWillChange
#define PMlogDidChange			kPMLogDidChange
#define PMlogRequestDomain		kPMLogRequestDomain
#define PMlogMakeUsable			kPMLogMakeUsable
#define PMlogChangeStateTo		kPMLogChangeStateTo
#define PMlogChangeStateToPriv		kPMLogChangeStateToPriv
#define PMlogSetAggressiveness		kPMLogSetAggressiveness
#define PMlogCriticalTemp		kPMLogCriticalTemp
#define PMlogOverrideOn			kPMLogOverrideOn
#define PMlogOverrideOff		kPMLogOverrideOff
#define PMlogEnqueueErr			kPMLogEnqueueErr
#define PMlogCollapseQueue		kPMLogCollapseQueue
#define PMlogChangeDone			kPMLogChangeDone
#define PMlogCtrlDriverTardy		kPMLogCtrlDriverTardy
#define PMlogIntDriverTardy		kPMLogIntDriverTardy
#define PMlogStartAckTimer		kPMLogStartAckTimer
#define PMlogStartParentChange		kPMLogStartParentChange
#define PMlogAmendParentChange		kPMLogAmendParentChange
#define PMlogStartDeviceChange		kPMLogStartDeviceChange
#define PMlogRequestDenied		kPMLogRequestDenied
#define PMlogControllingDriverErr5	kPMLogControllingDriverErr5
#define PMlogProgramHardware		kPMLogProgramHardware
#define PMlogInformDriverPreChange	kPMLogInformDriverPreChange
#define PMlogInformDriverPostChange	kPMLogInformDriverPostChange
#define PMlogRemoveDriver		kPMLogRemoveDriver
#define PMsetIdleTimerPeriod		kPMLogSetIdleTimerPeriod
#define PMlogSystemWake			kPMLogSystemWake
#define PMlogAcknowledgeErr5		kPMLogAcknowledgeErr5
#define PMlogClientAcknowledge		kPMLogClientAcknowledge
#define PMlogClientTardy		kPMLogClientTardy
#define PMlogClientCancel		kPMLogClientCancel


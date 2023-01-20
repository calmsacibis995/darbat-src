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
 	AltiAssist.s 

	Do the VMX assists

	Lovingly crafted by Bill Angell using traditional methods and only natural or recycled materials.
	No animal products are used other than rendered otter bile and deep fried pork lard.

*/

#include <ppc/asm.h>
#include <ppc/proc_reg.h>
#include <ppc/exception.h>
#include <mach/machine/vm_param.h>
#include <assym.s>

;
;
;			General stuff what happens here:
;				1)	All general context saved, interrupts off, translation off
;				2)	Vector and floating point disabled, but there may be live context.
;					This code is responsible for saving and restoring what is used. This
;					includes exception states, java mode, etc.
;				3)	No attempt is made to resolve page faults.  PTE misses are handled
;					automatically, but actual faults (ala copyin/copyout) are not. If 
;					a fault does occur, the exception that caused entry to the emulation
;					routine is remapped to either an instruction or data miss (depending
;					upon the stage detected) and redriven through the exception handler.
;					The only time that an instruction fault can happen is when a different
;					processor removes a mapping between our original fault and when we
;					fetch the assisted instruction. For an assisted instruction, data
;					faults should not occur (except in the MP case).  For a purely
;					emulated instruction, faults can occur.
;
;			Emulation algorithms cloned from MacOS 9 code.
;
;			Assumes that R2 = per_proc_area
;
;


			.align	5
			.globl	EXT(AltivecAssist)

LEXT(AltivecAssist)

			li			r10,emvr0					; Point to the vector savearea
			
			li			r11,emvr1					; Another savearea
			stvxl		v0,r10,r2					; Save V0
			stvxl		v1,r11,r2					; Save V1
			vspltisw	v0,1						; Set a 1 in V0			
			vspltisw	v1,8						; Get half of the shift
			vslw		v0,v0,v1					; Shift half way
			vslw		v0,v0,v1					; Shift the rest of the way (we now have 0x00010000)
			mfvscr		v1							; Get the VSCR
			vor			v1,v1,v0					; Turn off Java mode
			lvxl		v0,r10,r2					; Restore V0
			mtvscr		v1							; Set Java mode off
			lvxl		v1,r11,r2					; Restore V1
			
			li			r11,T_IN_VAIN				; We are all done
			b			EXT(EmulExit)				; We are done, no tracing on...





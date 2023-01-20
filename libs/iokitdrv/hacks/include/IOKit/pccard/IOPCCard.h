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

#ifndef _IOKIT_IOPCCARD_H
#define _IOKIT_IOPCCARD_H

#include <IOKit/IOService.h>

#include <sys/cdefs.h>

__BEGIN_DECLS
#include <IOKit/pccard/version.h>
#include <IOKit/pccard/config.h>
#define IOPCCARD_IN_IOKIT_CODE
#include <IOKit/pccard/k_compat.h>
#include <IOKit/pccard/cs_types.h>
#include <IOKit/pccard/cs.h>
#include <IOKit/pccard/cistpl.h>
#include <IOKit/pccard/cisreg.h>
__END_DECLS

#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/pccard/IOCardBusDevice.h>
#include <IOKit/pccard/IOPCCardBridge.h>
#include <IOKit/pccard/IOPCCard16Device.h>
#include <IOKit/pccard/IOPCCard16Enabler.h>
#include <IOKit/pccard/IOPCCardEjectController.h>

#endif /* ! _IOKIT_IOPCCARD_H */

/*********************************************************************
 *                
 * Copyright (C) 2002, 2003,  Karlsruhe University
 *                
 * File path:     kdb/platform/efi/reset.cc
 * Description:   Reset system using an EFI service call
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: reset.cc,v 1.7 2003/09/24 19:05:18 skoglund Exp $
 *                
 ********************************************************************/
#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <kdb/cmd.h>
#include <kdb/kdb.h>
#include INC_PLAT(system_table.h)
#include INC_PLAT(runtime_services.h)

#ifdef CONFIG_EFI
/**
 * cmd_reset: reset system
 */

#warning see kdb/platform/efi/reset.cc
DECLARE_CMD (cmd_reset, root, '6', "reset", "Reset system");

#if !defined(CONFIG_EFI)
CMD(cmd_reset, cg)
{
    asm volatile (
        "       movb    $0xFE, %al      \n"
        "       outb    %al, $0x64      \n");

    /* NOTREACHED */
    return CMD_NOQUIT;
}
#endif


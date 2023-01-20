/*********************************************************************
 *                
 * Copyright (C) 2002,  Karlsruhe University
 *                
 * File path:     kdb/generic/entry.cc
 * Description:   The kernel debugger entry point.
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
 * $Id: entry.cc,v 1.13 2003/09/24 19:05:11 skoglund Exp $
 *                
 ********************************************************************/
#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <kdb/kdb.h>
#include <kdb/cmd.h>
#include INC_API(tcb.h)

/*
 * Command group for root level kdb commands.
 */

DECLARE_CMD_GROUP (root);

/*
 * Generic architecture specific command group.
 */

DECLARE_CMD_GROUP (arch);

/*
 * Command group for kernel debuger configuration stuff.
 */

DECLARE_CMD_GROUP (config);

/*
 * Command group for kernel statistics.
 */

DECLARE_CMD_GROUP (statistics);


/* Wrapper to call KDB's entry method */
#ifdef __ELF__
void SECTION(SEC_KDEBUG) kdebug_entry (void * param) { kdb.entry(param); }
#elif defined(__APPLE_CC__)
void SECTION(SEG_KDEBUG,SEC_KDEBUG) kdebug_entry (void * param) { kdb.entry(param); }
#else
#error unknown compiler
#endif

/**
 * kdebug_entry: Entry point for the kernel debugger.
 */
#ifdef __ELF__
void SECTION(SEC_KDEBUG) kdb_t::entry (void * param)
#elif defined(__APPLE_CC__)
void SECTION(SEG_KDEBUG,SEC_KDEBUG) kdb_t::entry (void * param)
#else
#error unknown compiler
#endif
{
    static DEFINE_SPINLOCK(kdb_lock);
    kdb_lock.lock();

    cmd_ret_t r;

    kdb_param = param;

    /* XXX probably not generic enough */
    kdb_current = addr_to_tcb ((addr_t) param);

    if (pre())
	do {
	    r = root.interact (NULL, "");
	} while (r != CMD_QUIT);
    
    post();
    
    kdb_param = NULL;
    kdb_lock.unlock();
}


/**
 * Exit debugger and continue execution.
 */

DECLARE_CMD (cmd_go, root, 'g', "go", "continue execution");

CMD (cmd_go, cg)
{
    return CMD_QUIT;
}


/**
 * Enter architecture specific command group.
 */
DECLARE_CMD (cmd_arch, root, 'a', "arch", "architecture specifics");

CMD (cmd_arch, cg)
{
    return arch.interact (cg, "arch");
}


/**
 * Enter KDB configuration menu.
 */
DECLARE_CMD (cmd_config, root, 'c', "config", "KDB configuration");

CMD (cmd_config, cg)
{
    return config.interact (cg, "conf");
}

/**
 * Enter KDB statistics menu.
 */
DECLARE_CMD (cmd_statistics, root, '#', "stats", "statistics");

CMD (cmd_statistics, cg)
{
    return statistics.interact (cg, "stats");
}

/*********************************************************************
 *                
 * Copyright (C) 2002,  Karlsruhe University
 *                
 * File path:     kdb/generic/init.cc
 * Description:   Invoke all kernel debugger init functions
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
 * $Id: init.cc,v 1.6 2003/09/24 19:05:11 skoglund Exp $
 *                
 ********************************************************************/
#include <macros.h>
#include <types.h>
#include <config.h>
#include <kdb/kdb.h>
#include <kdb/linker_set.h>
#include <kdb/init.h>


/* THE kernel debugger instance */
kdb_t kdb;


/* From generic/linker_set.cc */
void init_sets (void);


/*
 * Set containing kdebug init functions.
 */

DECLARE_SET (kdb_initfuncs);



/* Wrapper to call KDB's init method */
#ifdef __ELF__
void SECTION (".init") kdebug_init (void) { kdb.init(); };
#elif defined(__APPLE_CC__)
void SECTION ("__INIT","__init") kdebug_init (void) { kdb.init(); };
#else
#error "unknown compiler"
#endif

/**
 * kdebug_init: Invoke all kernel debugger init functions.
 */
#ifdef __ELF__
void SECTION (".init")
#elif defined(__APPLE_CC__)
void SECTION ("__INIT","__init")
#else
#error "unknown compiler"
#endif
kdb_t::init (void)
{
    /* initialize state */
    kdb_cmd_mode = CMD_KEYMODE;
    kdb_param = NULL;
#ifndef __APPLE_CC__
    /*
     * Ensure that linker sets are initialized.
     */

    init_sets ();

    /*
     * Invoke all functions in the kdb_initfuncs set.
     */

    kdb_initfunc_t initfunc;
    kdb_initfuncs.reset ();
    while ((initfunc = (kdb_initfunc_t) kdb_initfuncs.next ()) != NULL)
	initfunc ();
#endif	/*__APPLE_CC__*/
}

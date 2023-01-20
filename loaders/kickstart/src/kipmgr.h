/****************************************************************************
 *
 * Copyright (C) 2002-2003, Karlsruhe University
 *
 * File path:	kipmgr.h
 * Description:
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
 * $Id: kipmgr.h,v 1.9 2004/06/03 01:01:00 stoess Exp $
 *
 ***************************************************************************/
#ifndef __KICKSTART__KIP_H__
#define __KICKSTART__KIP_H__

#include <l4/types.h>
#if defined(KICKSTART_AMD64)
#include "kcp-amd64.h"
#else
#include <l4/kcp.h>
#include <l4/kip.h>
#endif
#include <stdbool.h>

enum mem_bootloader_e {
	kip_mbi_mem_descriptor=0, 
	kip_module_mem_descriptor=1,
	kip_bootinfo_descriptor=2
};

typedef struct {
    L4_KernelConfigurationPage_t *kip;

    L4_Word_t mem_desc_cnt;
    L4_Word_t mem_desc_offset;
    L4_Word_t word_size;
} kip_manager_t;

void install_sigma0 (kip_manager_t *kip, L4_Word_t mod_start, L4_Word_t mod_end,
		     L4_Word_t entry);
void install_root_task (kip_manager_t *kip, L4_Word_t mod_start, L4_Word_t mod_end,
			L4_Word_t entry);
void update_kip (kip_manager_t *kip, L4_Word_t boot_info);

bool find_kip (kip_manager_t *kip, L4_Word_t kernel_start, L4_Word_t kernel_end);
L4_Word_t kip_get_min_pagesize (kip_manager_t *kip);
bool dedicate_memory(kip_manager_t *kip, L4_Word64_t start, L4_Word64_t end,
		     L4_Word64_t type, L4_Word64_t sub_type);
bool kip_is_mem_region_free(kip_manager_t *kip, L4_Word_t start, L4_Word_t size);
L4_Word64_t get_phys_mem_max(kip_manager_t *kip);

#endif	/* __KICKSTART__KIP_H__ */

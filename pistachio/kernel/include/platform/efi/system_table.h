/*********************************************************************
 *                
 * Copyright (C) 2002-2003,  Karlsruhe University
 *                
 * File path:     platform/efi/system_table.h
 * Description:   System table provided by EFI firmware
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
 * $Id: system_table.h,v 1.8 2003/09/24 19:04:55 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __PLATFORM__EFI__SYSTEM_TABLE_H__
#define __PLATFORM__EFI__SYSTEM_TABLE_H__

#include INC_PLAT(types.h)

class efi_runtime_services_t;
class efi_boot_services_t;


/**
 * Entry in the EFI configuration table.
 */
class efi_config_table_t
{
public:
    efi_guid_t		vendor_guid;
    void		*vendor_table;
};

/**
 * EFI configuration table pointer.
 */
class efi_config_table_ptr_t
{
public:
    word_t			number_of_table_entries;
    efi_config_table_t		*config_table;

    void * find_table (efi_guid_t guid);

    void dump(void)
    {
	    printf( "config table at %p\n", this );
	    printf( "nents: %d\n", number_of_table_entries );
	    printf( "ctptr: %p\n", config_table );
    }
};

/**
 * Search for indicated system table.
 * @param guid		unique id of table
 * @return point to table, or NULL if table is not found.
 */
INLINE void * efi_config_table_ptr_t::find_table (efi_guid_t guid)
{
	printf( "system_table.h: find_table, this %p\n", this );
	printf( "n_o_t_e: %d\n", number_of_table_entries );
	printf( "config_table: %p\n", config_table );
	for (word_t i = 0; i < number_of_table_entries; i++)
	{
		if (config_table[i].vendor_guid == guid)
			return config_table[i].vendor_table;
#if 0
		else
			printf( "\t!=, skipping ptr %p\n", 
				config_table[i].vendor_table );
#endif
	}

    return NULL;
} 


#define O(x) \
	((char*)&x) - ((char*)this) \
	, x

/**
 * System table provided by EFI firmware.
 */
class efi_system_table_t
{   
public:
    efi_table_header_t		hdr;

    char16			*firmware_vendor;
    u32_t			firmware_revision;

    efi_handle_t		console_in_handle;
    efi_interface_t		*console_in;
    efi_handle_t		console_out_handle;
    efi_interface_t		*console_out;
    efi_handle_t		standard_error_handle;
    efi_interface_t		*standard_error;

    efi_runtime_services_t	*runtime_services;
    efi_boot_services_t		*boot_services;
    
    efi_config_table_ptr_t	config_table;

    void dump_table(void)
    {
	    printf( "dumping EFI systab @ %p\n", this );
	    hdr.dump_header();
	    printf( "[@0x%x]firmware_vendor: %p\n", O(firmware_vendor) );
	    printf( "[@0x%x]firmware_revision: 0x%x\n", O(firmware_revision) );
	    printf( "[@0x%x]console_in: %p\n", O(console_in) );
	    printf( "[@0x%x]console_out: %p\n", O(console_out) );
	    printf( "[@0x%x]console_err: %p\n", O(standard_error) );
	    printf( "[@0x%x]runtime_svc: %p\n", O(runtime_services) );
	    printf( "[@0x%x]boot_servic: %p\n", O(boot_services) );
	    printf( "[@0x%x]config_tabl: %p\n", O(config_table) );
	    config_table.dump();
    }
};


/*
 * Location of the EFI system table.
 */

extern efi_system_table_t * efi_systab;


/*
 * Location of EFI runtime services table
 */

extern efi_runtime_services_t * efi_runtime_services;


/*
 * EFI configuration tables
 */

extern efi_config_table_ptr_t efi_config_table;


#endif /* !__PLATFORM__EFI__SYSTEM_TABLE_H__ */

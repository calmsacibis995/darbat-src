
#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include INC_GLUE(space.h)

#include INC_PLAT(runtime_services.h)
#include INC_PLAT(memory_map.h)
#include INC_PLAT(system_table.h)


/* EFI memory map - don't use this! */
efi_memory_map_t efi_memmap;

/*
 * Location of the EFI system table.
 */
static addr_t efi_systab_phys;
efi_system_table_t * efi_systab;


/*
 * Location of EFI runtime services table.
 */

efi_runtime_services_t * efi_runtime_services;


/*
 * EFI configuration tables
 */

efi_config_table_ptr_t efi_config_table;


void add_init_root_mapping( void *vaddr );

static addr_t
efi_phys_to_virt_fn( addr_t x )
{
	word_t offset;
	offset = ((word_t)x) - ((word_t)efi_systab_phys);

	return (addr_t)(EFI_MAPPINGS + offset);
}

#define efi_phys_to_virt(x) ((typeof(x)) efi_phys_to_virt_fn(x))

static void*
do_efi_map( addr_t phys, unsigned poff, unsigned pcount )
{
	unsigned i;
	word_t pptr, vptr, ovptr, offset;

	pptr = (word_t) phys;
	offset = pptr & (IA32_PAGE_SIZE-1);
	pptr &= ~(IA32_PAGE_SIZE-1);
	vptr = EFI_MAPPINGS + poff * IA32_PAGE_SIZE;
	ovptr = vptr;
	
	
	for( i = 0; i < pcount; i++ )
	{
		printf( "mapping vptr 0x%lx to pptr 0x%lx, offset %lx\n", 
			vptr, pptr, offset );
		
		get_kernel_space()->add_mapping( (addr_t) vptr, 
						 (addr_t) pptr, 
						 pgent_t::size_4k,
						 false, 
						 true, 
						 true );
		vptr += IA32_PAGE_SIZE;
		pptr += IA32_PAGE_SIZE;
	}

	return (void*) (ovptr + offset);
}



/**
 * init_efi: EFI specific initialization
 * @param systab_addr		Physical address of EFI system table
 */
#ifdef __ELF__
void SECTION (".init")
#elif defined(__APPLE_CC__)
void SECTION ("__INIT", "__init")
#else
#error "unknown compiler"
#endif
init_efi( addr_t systab_addr )
{
    /*
     * Map EFI system table.
     */

    /* map 2 pages for the systable */
    efi_systab_phys = systab_addr;
    efi_systab = (efi_system_table_t *) do_efi_map( efi_systab_phys, 0, 2 );

    /* dump it out */
    efi_systab->dump_table();

    /*
     * EFI Spec v1.10 says SetVirtualAddressMap translates all
     * pointers for us, but it seems that some old versions of EFI
     * don't.  So we take copies of the needed pointers before
     * SetVirtualAddressMap and translate ourselves.
     */
    
    printf( "looking at systab %p\n", efi_systab );


    efi_runtime_services = efi_phys_to_virt (efi_systab->runtime_services);
    printf( "runtime services %p\n", efi_runtime_services );
    efi_config_table = efi_systab->config_table;
    printf( "config table %p\n", efi_config_table.config_table );
    efi_config_table.config_table = (efi_config_table_t*) do_efi_map( efi_config_table.config_table, 2, 2 );
    printf( "config table now %p\n", efi_config_table.config_table );

#if 0
    {
	    int i;
	    unsigned char *c = (unsigned char*) efi_config_table.config_table;
	    printf( "memdump at %p\n", c );

	    for( i = 0; i < 0x200; i++ )
	    {
		    if( i % 16 == 0 )
			    printf( "%08x: ", &c[i] );

		    printf( "%02x", c[i] );

		    if( i % 8 == 7 )
			    if( i % 16 == 15 )
				    printf( "\n" );
			    else
				    printf( "-" );
		    else
			    printf( " " );
	    }

	    printf( "\n\n" );
    }
#endif    


    /*
     * Notify EFI firmware about virtual locations of memory regions
     * so that we can invoke EFI functions in virtual mode.
     */
#if 0
    word_t status = call_efi_physical
	((word_t) efi_runtime_services->set_virtual_address_map_f,
	 memmap_size, memdesc_size, memdesc_version,
	 virt_to_phys ((word_t) memmap_addr), 0);

    if (status != efi_runtime_services_t::success)
	ipanic ("efi_set_virtual_address_map() failed\n");
#endif
}

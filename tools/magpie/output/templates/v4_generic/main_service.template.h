/*-run(templates.get('preamble'))-*/
#define MAGPIE_BYTES_PER_WORD (sizeof(L4_Word_t))

/*-run(templates.get('basic_includes'))-*/

/*-run(templates.get('imports'))-*/

#if !defined(/*-?generator.get_ifdefable_filename()-*/)
#define /*-?generator.get_ifdefable_filename()-*/

/*LOOP constnamevalue = generator.get_constants()*/
#define /*-?constnamevalue[0]-*/ /*-?constnamevalue[1]-*/
/*ENDLOOP*/

/*LOOP interface = generator.get_interfaces()*/
/* Interface {*-?interface.get_name()-*} */
/*-run(templates.get('service_interface_wrapper'))-*/
/*ENDLOOP*/

#endif //{*-?generator.get_ifdefable_filename()-*}

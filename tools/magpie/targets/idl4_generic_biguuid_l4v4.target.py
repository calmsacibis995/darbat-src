Generator = 'v4'

#InheritFrom('idl4_generic_l4v4')
class Templates(OldTemplates):
	"""
	Biguuid templates share almost everything with generic.
	"""
	MAPPING = 'CORBA C'
	
	client_function_create_id = 'v4_generic_biguuid/client_function_create_id.template.c'
	client_function_marshal = 'v4_generic_biguuid/client_function_marshal.template.c'

	servicetemplate_create_getiid_func = 'v4_generic_biguuid/servicetemplate_getiid.template.c'

	basic_includes = 'v4_generic_biguuid/basic_includes.template.c'
	clientservice_function_params_maker = 'v4_generic_biguuid/function_params_maker.template.c'
	preamble = 'v4_generic_biguuid/preamble.template.c'

	public = ['client', 'service']

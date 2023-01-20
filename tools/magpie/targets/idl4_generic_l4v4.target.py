Generator = 'v4'

class Templates(OldTemplates):
	MAPPING = 'CORBA C'

	client_function_wrapper = 'v4_generic/client_function_wrapper.template.c'
	client_function_body = 'v4_generic/client_function_body.template.c'
	client_function_body_pre_ipc_defs = None # Used by v4nicta_modifier
	client_function_body_pre_ipc = None
	client_function_body_post_ipc = None
	client_function_create_id = 'v4_generic/client_function_create_id.template.c'
	client_function_marshal = 'v4_generic/client_function_marshal.template.c'
	client = 'v4_generic/main_client.template.h'

	service_interface_wrapper = 'v4_generic/service_interface_wrapper.template.c'
	service_function = 'v4_generic/service_function.template.c'
	service_function_reply = 'v4_generic/service_function_reply.template.c'
	service = 'v4_generic/main_service.template.h'

	servicetemplate_create_getiid_func = 'v4_generic/servicetemplate_getiid.template.c'
	servicetemplate = 'v4_generic/main_servicetemplate.template.h'

	types = 'v4_generic/main_types.template.h'

	basic_includes = 'v4_generic/basic_includes.template.c'
	clientservice_function_params_maker = 'v4_generic/function_params_maker.template.c'
	preamble = 'v4_generic/preamble.template.c'
	interface_wrapper = 'v4_generic/interface_wrapper.template.c'
	imports = 'v4_generic/import.template.c'

	language_specific_remapping = 'v4_generic/null_remapping.template.c'
	
	public = ['client', 'service', 'servicetemplate', 'types']


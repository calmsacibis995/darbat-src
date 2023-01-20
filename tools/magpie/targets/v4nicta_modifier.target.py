class Templates(OldTemplates):
	MAPPING = 'CORBA C'
	client_function_body_pre_ipc_defs = 'v4nicta_generic/client_function_body_asynchmask_defs.template.c'
	client_function_body_pre_ipc = 'v4nicta_generic/client_function_body_save_asynchmask.template.c'
	client_function_body_post_ipc = 'v4nicta_generic/client_function_body_restore_asynchmask.template.c'

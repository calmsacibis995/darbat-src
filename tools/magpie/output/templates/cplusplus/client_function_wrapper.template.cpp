/*-
function.rename_args({'fpage': 'idl4_fpage_t'})
# The C++ interface shares the service pointer and environment across all functions in the interface, so we don't have to add anything here. 
#call_param_list = ['%s _service' % (interface.get_name())]
call_param_list = []
for param in function.get_call_params():
	call_param_list.append('%s %s%s%s' % (param['typename'], param['c_impl_indirection'], param['indirection'], param['name']))
#call_param_list.append('CORBA_Environment *_env')
-*/
/*-run(templates.get('client_function_create_id'))-*/
inline /*-?function.get_return_type()-*/
/*-?function.get_name_raw()-*/ (/*-?', '.join (call_param_list)-*/)
{
/*-run(templates.get('client_function_body'))-*/
}

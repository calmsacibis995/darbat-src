/*-
msg_params_in = [(item['typename'], '%s%s' % (item['indirection'], item['name'])) for item in function.get_params_in()]

msg_params_out = [(item['typename'], '%s%s' % (item['indirection'], item['name'])) for item in function.get_params_out()]

if function.get_return_type() != 'void':
	msg_params_out.append( (function.get_return_type(), '__retval') )
-*/

/*-
printf_string = ', '.join(['%s: %%%s' % (desc, fmt) for desc, fmt in zip(function.iguana_debug_description_list, function.iguana_debug_format_string_list)])
printf_args = ', '.join(['_par->_in.%s' % acc for acc in function.iguana_debug_access_list])
if printf_string == '':
	printf_string = "<none>"
if printf_args != '':
	printf_args = ', ' + printf_args
-*/	/*Iguana debug -  PRINT INPUT PARAMS */\
	printf("Function /*-?function.func_name-*/: params /*-?printf_string-*/\n" /*-?printf_args-*/);\
	/*End Iguana debug */\

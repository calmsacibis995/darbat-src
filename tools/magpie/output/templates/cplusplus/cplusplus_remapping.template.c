/*-# Rename all function names that are C++ reserved words.
CXX_RESERVED = ('delete', 'new', 'operator', 'class')

for param in function.get_params():
	if param['name'] in CXX_RESERVED:
		param['name'] = '_' + param['name']

if function.get_name_raw() in CXX_RESERVED:
	function.set_name_raw('_' + function.get_name_raw())
-*/

"""
Helper functions for dealing with the parsed IDL syntax tree
"""

def get_idl_type_name(type_ast):
	""" Return the name of the type from a type_ast """
	if type_ast.leaf is None:
		subtype = type_ast.the(['existing_constr_type', 'primitive_type'])
		if subtype.type == 'existing_constr_type':
			return subtype.leaf
		elif subtype.type == 'primitive_type':
			return subtype.the('integer_type').the('g_signed_int_type').leaf
	else:
		return type_ast.leaf

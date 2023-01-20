#from idlparser.helper import get_idl_type_name

class SimpleParam(object):
	"""
	A SimpleParam is a list of parameter attributes. A list of them is passed to
	the template so it doesn't have to know about the structure of the AST.
	"""
	def __init__(self, attributes_dict):
		self.attributes_dict = attributes_dict
	
	def __getitem__(self, key):
		return self.attributes_dict[key]
	
	def __setitem__(self, key, value):
		self.attributes_dict[key] = value
	
	def get(self, key, default):
		return self.attributes_dict.get(key, default)

	def create(cls, parameter_decl):
		newparam = {}
		newparam['indirection'] = parameter_decl.get_single_attribute('indirection', '')
		assert newparam['indirection'] is not None
		newparam['direction'] = parameter_decl.get_attribute('direction')[0]
		assert newparam['direction'] in ('in', 'out', 'inout')
		newparam['name'] = parameter_decl.leaf
		newparam['typename'] = parameter_decl.the('type').leaf #get_idl_type_name(parameter_decl.the('parameter_type'))
		newparam['idltype'] = parameter_decl.get_annotation()
		if (newparam['direction'] in ('out', 'inout')) or (newparam['idltype'].is_value_type is False):
			newparam['c_impl_indirection'] = '*'
		else:
			newparam['c_impl_indirection'] = ''
		#FIXME: What about the case of byref and 'special_indirection' is not ''?
		#FIXME: What about the case of explicit byval and 'special_indirection' is not ''?
		#if parameter_decl['passtype'] is not None and parameter_decl['passtype'] == 'byref':
		#	newparam['special_indirection'] += '*'
		return cls(newparam)
	create = classmethod(create)

	def create_return(cls, op_return_type):
		# Special case: function return type counts as special parameter with
		# direction 'return'. 
		newparam = {'indirection': '',
				'c_impl_indirection': '',
				'name': '__return',
				'typename': op_return_type.the('type').leaf,
				'direction': 'return',
				'idltype': op_return_type.get_annotation()
				#'passtype' : op_return_type.get_attribute('passtype')
		}
		return cls(newparam)
	create_return = classmethod(create_return)

def make_simple_param_list(function_decl_ast):
	""" Return a list of SimpleParam objects to pass to the templates, so
	template code doesn't have to know how to walk the AST."""
	
	# Create the list of simplified params
	simple_param_list = []
	
	# ... create each positional parameter
	parameter_decl_list = function_decl_ast['parameter']
	for parameter_decl in parameter_decl_list:
		newparam = SimpleParam.create(parameter_decl)
		simple_param_list.append(newparam)
		
	# ... create the return type (special case)
	#op_return_type = function_decl_ast.get_attribute('return')
	newparam = SimpleParam.create_return(function_decl_ast)
	simple_param_list.append(newparam)
	# ... done.
	return simple_param_list

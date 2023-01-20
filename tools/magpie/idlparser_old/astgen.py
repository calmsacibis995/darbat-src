from parser_common import Node
# AST parts.
class ASTPart(Node):
	pass

class Declarator(ASTPart):
	def __init__(self, children = None):
		ASTPart.__init__(self, "declarator", children)
		
class Interface(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'interface', children, name)
class Inheritance(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'inherits', children, name)

class Function(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'function', children, name)
		
class Parameter(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'parameter', children, name)
		
class Definition(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'definition', children, name)

class Decorator(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'decorator', children, name)
	
class Annotation(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'annotation', children, name)

		
class Type(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'type', children, name)
	
	def add_instances(self, *instances):
		self.add_attribute('instances', instances)
	
class Error(ASTPart):
	def __init__(self):
		ASTPart.__init__(self, "ERROR")

class UnknownNode(ASTPart):
	def __init__(self, pt):
		ASTPart.__init__(self, "Unknown")
		self.children = [pt]
	
	# Dummy methods so we can use this class everywhere
	def add_instances(self, *args):
		pass 

class UnknownLeaf(object):
	def __init__(self, pt = None):
		self.pt = pt
	
	def __repr__(self):
		return '<Unknown leaf; PT is %s>' % (self.pt)

# AST helper functions


class ASTGen(object):
	def convert(self, pt):
		return self.translation_unit(pt)
		
	def translation_unit(self, pt):
		ast = Node("IDLFile")
		for node in pt.children:
			if node.type == 'decorated_definition':
				def_children = self.decorated_def(node)
				def_node = Definition(def_children)
				ast.add_child(def_node)
			else:
				#print 'node = ', node.type
				ast.add_child(UnknownNode(node))
		return ast
		
	def decorated_def(self, pt):
		ast = None
		def_children = []
		for child in pt.children:
			if child.type == 'decorator':
				dec_node = self.create_interface_decorator_node(child)
				def_children.append(dec_node)
				#print 'Decorator = ', dec_node
			elif child.type == 'interface_decl':
				#create a (sub)tree with the information of the interface
				ast = self.create_interface_node(child)
				def_children.append(ast)
			elif child.type == 'type_declaration':
				type_node = self.create_type_node(child)
				def_children.append(type_node)
			elif child.type == 'const_declaration':
				const_node = self.create_const_node(child)
				def_children.append(const_node)
			elif child.type == 'import':
				def_children.append(child)
			else:
				print 'Unknown child in decortated_definition: ', child
		return def_children
		
	def create_const_node(self, pt):
		node = Type(None)
		child = pt.the('const_type').children[0]
		if child.type == 'existing_constr_type':
			node.set_leaf(child.leaf)
		node.add_attribute('specifiers', 'const')
		decl = Declarator(None)
		decl.set_leaf(pt.leaf)			
		if pt.the('const_expr').result != None:
			decl.add_attribute('initialiser', pt.the('const_expr').result)
		node.add_child(decl)
		return node
		
		
	def create_type_node(self, pt):
		node = Type(None)
		if pt.the('constr_type').children[0].type == 'struct_type':
			str_node = pt.the('constr_type').the('struct_type')
			
			dec = Declarator(None)
			dec.set_leaf(str_node.leaf)
			node.add_child(dec)
			
			node.add_attribute('meta_type', 'struct')
			
			member_list = str_node.the('typed_member_list')['typed_member']
			for member in member_list:
				new_member = Type(None)
				#children[0] is a hack to avoid distinct nodes existing_constr_type ...
				mem_child = member.the('type_spec').children[0]
				if mem_child.type == 'existing_constr_typ':
					new_member.set_leaf(mem_child.leaf)
					for decl in member.the('declarator_list')['declarator']:
						new_decl = Declarator(None)
						new_decl.set_leaf(decl.leaf)
						if decl.the('allow_indirection').leaf != '':
							new_decl.add_attribute('indirection', decl.the('allow_indirection').leaf)
						new_member.add_child(new_decl)
				elif mem_child.type == 'constr_type':
					node.add_child(self.create_type_node(member.the('type_spec')))
				else:	#just template_type is left ... 
					#the code is just a copy of existing_constr_typ
					#FIXME: -> perhaps customize for template_type!!!
					new_member.set_leaf(mem_child.leaf)
					for decl in member.the('declarator_list')['declarator']:
						new_decl = Declarator(None)
						new_decl.set_leaf(decl.leaf)
						if decl.the('allow_indirection').leaf != '':
							new_decl.add_attribute('indirection', decl.the('allow_indirection').leaf)
						new_member.add_child(new_decl)
				node.add_child(new_member)
		return node
		
	
	def create_interface_decorator_node(self, pt):
		dec_node = Decorator(None)
		anno = Annotation(name=pt.leaf)
		args = []
		for child in pt.children:
			if child.type == 'const_expr':
				args.append(child.result)
		anno.add_attribute('arguments', args)
		dec_node.add_child(anno)
		return dec_node
		
	def create_function_decorator_node(self, pt):
		dec_node = Decorator(None)
		if pt.children == []:
			dec_node.add_child(Annotation(name=pt.leaf))
		for child in pt.children:
			if child.type == 'modifier_element':
				anno_node = Annotation()
				anno_node.set_leaf(child.leaf)
				for mod_child in child.children:
					if mod_child.type == 'modifier_arg':
						anno_node.add_attribute('arguments', mod_child.leaf)
				dec_node.add_child(anno_node)
			else: 
				pass

		return dec_node
		
	def create_interface_node(self, pt):
		if pt.my_children_are('interface_sig', 'interface_def'):
			sig = pt.the('interface_sig')
			intfc_def = pt.the('interface_def')
			ast = self.create_interface_head(sig)
			ast.add_children(self.create_interface_body(intfc_def))
			return ast
		else:
			return UnknownNode(pt)
			
	def create_interface_head(self, pt):
		node = Interface(None)
		node.set_leaf(pt.leaf)
		for child in pt['inherits_from']:
			node.add_child(Inheritance(name = child.leaf))
		return node
			
	def create_interface_body(self,pt):
		# I got the interface_def-node
		# -> walk down to "export" children
		body = pt.the('interface_body')
		
		ast_list = []
		
		#now process all 'export'-children
		for node in body.children:
			if node.type == 'export':
				fcn_node = self.create_function_node(node)
				ast_list.append(fcn_node)	
			else:
				pass #ast_list.append(node)
				
		return ast_list

	def create_function_node(self, pt):
		# create a new 'function'-node
		fcn_node = Function(None)
		op_decl_node = pt.the('op_declaration')
		
		# get function name as leaf-attribute
		fcn_node.set_leaf(op_decl_node.leaf)
		
		# process op_modifiers, op_return_type and parameter_list
		for node in op_decl_node.children:
			#print 'node = ', node.type
			if node.type == 'op_modifiers':
				if node.children != []:
					new_child = self.create_function_decorator_node(node)
					if new_child.children != []:
						fcn_node.add_child(new_child)
				
			elif node.type == 'op_return_type':
				if node.leaf == None:		
					fcn_node.add_attribute('return', self.get_type(node))
				else:
					fcn_node.add_attribute('return', node.leaf)
			elif node.type == 'parameter_list':
				# create a node for the inputargs and the result parameters
				parameter_nodes = self.create_parameter_nodes(node)
				
				#print parameter_nodes
				
				# add to the ast-tree
				fcn_node.add_children(parameter_nodes)
			else:
				pass 
		return fcn_node
		
	def get_type(self, pt):
		if pt.my_children_are('existing_constr_type'):
			return pt.the('existing_constr_type').leaf
		else:
			# FIXME: process user defined types
			return 'FIXME: unknown user-def-type'
			
	def create_parameter_annotation(self, pt, ast):
		an_list = []
		for anno in pt['modifier_element']:
			if anno.leaf == 'byval':
				if not ast.has_attribute('passtype'):
					ast.add_attribute('passtype', 'byval')
			elif anno.leaf == 'byref':
				if not ast.has_attribute('passtype'):
					ast.add_attribute('passtype', 'byref')
			else:
				an_list.append(anno.leaf)
			if an_list != []:
				anno = Annotation(None)
				anno.add_attribute('arguments', an_list)
				ast.add_child(anno)

	def create_parameter_nodes(self, pt):
		param_nodes_list = []
		for node in pt.children:
			if node.type == 'parameter_decl':
				new_param_node = Parameter(None)
				new_param_node.set_leaf(node.leaf)
				for param_node in node.children:
					if param_node.type == 'parameter_modifiers':
						self.create_parameter_annotation(param_node, new_param_node)
						#print new_param_node
						"""
						if anno != None:
						  new_param_node.add_child(anno)
						"""
						
					elif param_node.type == 'parameter_direction':
						new_param_node.add_attribute('direction', param_node.leaf)
					elif param_node.type == 'parameter_type':
						new_param_node.add_attribute('type', self.get_type(param_node))
					elif param_node.type == 'allow_indirection':
						#if param_node.leaf != '':
						new_param_node.add_attribute('indirection', param_node.leaf)
					else:
						pass
				param_nodes_list.append(new_param_node)
			else:
				pass
		return param_nodes_list
		

			 
			
def gen(pt):
	astgen = ASTGen()
	return astgen.convert(pt)
			
			
			
			
			
			
			

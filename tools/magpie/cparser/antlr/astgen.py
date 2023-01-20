"""
Transform the parse tree produced by parser.py to a higher-level tree using
recursive descent.
"""

from parser_common import Node
import operator


# AST parts.
class ASTPart(Node):
	pass

class Declarator(ASTPart):
	def __init__(self, children = None):
		ASTPart.__init__(self, "declarator", children)

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

def all_children(node, names):
	for child_name in node.get_child_names():
		if child_name not in names:
			return False
	return True

# AST generator

CLASS_SPECIFIERS = ('union', 'struct', 'class', 'enum')

class ASTGen(object):
	def convert(self, pt):
		return self.translation_unit(pt)

	def translation_unit(self, pt):
		#print 'PT'
		#pt.print_tree()
		#print 'PT done'
		ast = Node("translation_unit")
		for node in pt.children:
			if node.type == 'declaration':
				ast.add_child(self.declaration(node))
			elif node.type == 'function_definition':
				ast.add_child(Node('unfinished_function_definition'))
			else:
				ast.add_child(UnknownNode(node))
		return ast
	
	def declaration(self, pt):
		"""
		"""
		# There should be two parts to this declaration.
		if pt.my_children_are('declaration_specifiers', 'init_declarator_list'):
			decl_specifiers = pt.the('declaration_specifiers')
			init_decl_list = pt.the('init_declarator_list')

			decl_type, decl_node = self._declaration_specifiers(decl_specifiers)
			ast = decl_node
			# Add a bunch of attributes based on the specifiers.
			for decl_spec in decl_type:
				if decl_spec in ('extern', 'static'):
					ast.add_attribute('linkage', [decl_spec])
				elif decl_spec in ('const', 'restrict', 'volatile'):
					ast.add_attribute('type-qualifier', [decl_spec])
				elif decl_spec in ('typedef', 'extern', 'static', 'auto', 'register'):
					ast.add_attribute('storage-class', [decl_spec])
				elif decl_spec in ('inline',):
					ast.add_attribute('function-specifier', [decl_spec])
				else:
					print "DUNNO", decl_spec
					pt.print_tree()
					raise Exception()
					ast.add_attribute('specifiers_unknown', [decl_spec])
			# Handle init declarator list.
			ast.add_children(self._init_declarator_list(init_decl_list))
		else:
			ast = UnknownNode(pt)
		return ast
	
	def _declaration_specifiers(self, pt):
		"""
		Returns (decl_type, ast)
		decl_type can go in parent's leaf
		"""
		decl_type = pt.leaf
		if pt.my_children_are('simple_type_specifier'):
			type_name = ' '.join(pt.the('simple_type_specifier').leaf)
			return decl_type, Type(None, type_name)
		elif pt.my_children_are('enum_specifier'):
			type_name = 'unsigned int'
			return decl_type, Type(None, type_name)
		elif len(pt.children) == 1 and pt.children[0].type in CLASS_SPECIFIERS:
			# Create a new type right here right now!
			new_type = self.get_type(pt.children[0])
			return decl_type, new_type
		else:
			return decl_type, UnknownNode(pt)

	def get_type(self, pt):
		"""
		Create a new type from a list of member_declarations
		"""
		
		# Member declarations are now contained in a "members" node.
		# If this assert fails, we are declarating a forward reference instead...
		assert pt.my_children_are('members')
		members_pt = pt.the('members')

		if all_children(members_pt, ('member_declaration', 'declaration')):
			# For each member decl we have a
			# declaration_specifier and a member_declarator_list.
			assert pt.type in CLASS_SPECIFIERS
			ast = Type(None)
			ast.add_attribute('meta_type', pt.type)
			if pt.leaf is not None: # We are creating a new type here.
				ast.add_attribute('type_name', pt.leaf)
			for child in members_pt.children:
				decl_specifiers = None
				if child.type == 'member_declaration' \
						and child.my_children_are('declaration_specifiers', 'member_declarator_list'):
					decl_specifiers = child.the('declaration_specifiers')
					member_decls = self._member_declarator_list(
							child.the('member_declarator_list'))
					decl_type, decl_node = self._declaration_specifiers(decl_specifiers)
					decl_node.add_children(member_decls)
					ast.add_child(decl_node)
				elif child.type == 'declaration':
					decl_node = self.declaration(child)
					ast.add_child(decl_node)
				else:
					ast.add_child(UnknownNode(child))
			return ast
		else:
			return UnknownNode(pt)

	def _member_declarator_list(self, pt):
		"""
		Return a list of instance names.
		"""
		return self._some_declarator_list(pt)

	def _init_declarator_list(self, pt):
		return self._some_declarator_list(pt)
	
	def _some_declarator_list(self, pt):
		"""
		Init declarators are separated in source using commas.
		"""
		assert pt.type in ("init_declarator_list", "member_declarator_list")

		init_declarators = []
		for child in pt.children:
			init_declarators.append(self.init_declarator(child))
		return init_declarators
	
	def init_declarator(self, pt):
		"""
		Return a text string describing this declarator.
		"""
		ast = Declarator()
		if pt.type == 'member_declarator_bitfield':
			#print "This is what I'm Tolkien about:"
			#pt.print_tree()
			ast.set_leaf(pt.leaf)
			ast.add_attribute('bitfield', True)
			ast.add_child(pt.the('expression'))
		else:
			assert pt.type in ("init_declarator", "member_declarator")

			if pt.my_children_are('direct_declarator', 'expression', minkids = 1):
				ast.set_leaf(pt.the('direct_declarator').leaf)
				expr = pt.the('expression')
				if expr:
					# Initialiser.
					ast.add_attribute("initialiser", expr.result)
			else:
				ast.set_leaf(UnknownLeaf(pt))
		return ast
	
	def _init_declarator_get_value(self, pt):
		pass
	
	
def gen(pt):
	astgen = ASTGen()
	return astgen.convert(pt)


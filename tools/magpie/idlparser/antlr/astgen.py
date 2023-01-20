from parser_common import ParserLexerState, Node
from magpietypes.registry import new_registry
# AST parts.
class ASTPart(Node):
	pass

class Declarator(ASTPart):
	def __init__(self, children = None):
		ASTPart.__init__(self, "declarator", children)
		
class Interface(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'interface', children, name)
		
class Module(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'module', children, name)
		
class Inheritance(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'inherits', children, name)

class Support(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'supports', children, name)

class Function(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'function', children, name)

class Component(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'component', children, name)
		
class Home(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'home', children, name)
		
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

class Expression(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'expression', children, name)
		
class Attribute(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'attribute', children, name)

class CaseNode(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'case', children, name)

class Export(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'export', children, name)

class ExceptionNode(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'exception', children, name)

class Const(ASTPart):
	def __init__(self, children=None, name = None):
		ASTPart.__init__(self, 'const', children, name)

class Valuetype(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'valuetype', children, name)
		
class Type(ASTPart):
	def __init__(self, children, name = None):
		ASTPart.__init__(self, 'type', children, name)
	
	def add_instances(self, *instances):
		self.add_attribute('instances', instances)
	
class Error(ASTPart):
	def __init__(self):
		ASTPart.__init__(self, "ERROR")

class Event(ASTPart):
	def __init__(self, children = None, name = None):
		ASTPart.__init__(self, 'eventtype', children, name)

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
	def __init__(self, registry=None):
		self.registry = registry
		
	def convert(self, pt):
		return self.translation_unit(pt)
		
	def translation_unit(self, pt):
		ast = Node("IDLFile")
		for node in pt.children:
			if node.type == 'decorated_definition':
				def_children = self.decorated_def(node)
				def_node = Definition(def_children)
				ast.add_child(def_node)
			elif node.type == 'import_dcl':
				imp_node = self.import_dcl(node)
				ast.add_child(imp_node)
			else:
				#print 'node = ', node.type
				ast.add_child(UnknownNode(node))
		return ast
	def import_dcl(self, pt):
		ast = None
		#imported_scope
		child = pt.the('imported_scope').children[0]
		#print child
		if child.type == 'string_literal':
			ast = Node(None)
			ast.type = 'import'
			ast.leaf = child.leaf
		elif child.type == 'scoped_name':
			ast = Node(None)
			ast.type = 'import'
			ast.leaf = self.scoped_name(child)
		else:
			ast = Node(child)
			ast.type = 'import'
		return ast
		
	def decorated_def(self, pt):
		dec_def_children = []
		#child = pt.the('definition')
		
		
		for child in pt.children:
			if child.type == 'decorator':
				dec_children = self.decorator_elements(child)
				dec_node = Decorator(dec_children)
				dec_def_children.append(dec_node)
			elif child.type == 'definition':
				definition_node = self.definition(child)
				dec_def_children.append(definition_node)
			else:
				dec_def_children.append(UnknownNode(child))
		return dec_def_children

	def decorator_elements(self,pt):
		children = []
		for child in pt.children:
			if child.type == 'decorator_element':
				dec_el = self.decorator_element(child)
				children.append(dec_el)
			else:
				children.append(UnknownNode(child))
		#print '\n', children
		return children
				
	def decorator_element(self, pt):
		dec_node = Annotation(None)
		for child in pt.children:
			if child.type == 'identifier':
				dec_node.leaf = child.leaf
			elif child.type == 'expr_list':
				dec_node.add_children(self.expr_list(child, True))
			else:
				dec_node.add_child(UnknownNode(child))
		#print dec_node
		return dec_node
		
	def expr_list(self, pt, evaluate = False):
		ex_list = []
		for child in pt.children:
			if child.type == 'const_exp':
				exp_node = Expression()
				exp_node.leaf, exp_node.result = self.getExpression(child, evaluate)
				#print exp_node.leaf, exp_node.result
				ex_list.append(exp_node)
			else:
				ex_list.append(UnknownNode(child))
		return ex_list
		
	def getExpression(self, node, evaluate=False):
		str_exp = ''
		result = None
		if len(node.children) == 0:
			if node.type == 'scoped_name':
				str_exp = self.scoped_name(node)
				result = None
			elif node.type == 'identifier':
                                str_exp = node.leaf
                                result = None
		elif len(node.children) == 1:
                        if node.type == 'scoped_name':
				str_exp = self.scoped_name(node)
				result = None
			elif node.type == 'literal':
				str_exp = node.leaf
				if evaluate:
					result = self.getValue(node)
			elif node.type == 'const_exp':
				str_exp, result = self.getExpression(node.children[0], evaluate)
			elif node.type == 'primary_expr':
				str_exp, result = self.getExpression(node.children[0], evaluate)
			else:
				str_exp, result = self.getExpression(node.children[0], evaluate)
				#print node
				
		elif len(node.children) == 2:
			if node.type == 'unary_expr':
				substr2, res2 = self.getExpression(node.children[1], evaluate)
				str_exp = '('+ node.children[0].leaf + substr2 +')'
				if evaluate and res2 != None:
					if node.children[0].leaf == '-':
						result = -res2
					elif node.children[0].leaf == '~':
						result = ~res2
					else:
						result = res2
			else:
				substr1, res1 = self.getExpression(node.children[0], evaluate)
				substr2, res2 = self.getExpression(node.children[1], evaluate)
				str_exp = '('+substr1+'' + node.leaf + '' + substr2+')'
				if evaluate and res1 != None and res2 != None:
					if node.type == 'or_expr':
						#str_exp = '('+substr1+'|'+substr2+')'
						result = res1 | res2
					elif node.type == 'xor_expr':
						#str_exp = '('+substr1+'^'+substr2+')'
						result = res1 ^ res2
					elif node.type == 'and_expr':
						#str_exp = '('+substr1+'&'+substr2+')'
						result = res1 & res2
					
		elif len(node.children) == 3:
			substr1, res1 = self.getExpression(node.children[0], evaluate)
			substr2, res2 = self.getExpression(node.children[2], evaluate)
			
			str_exp = '('+substr1+node.children[1].leaf+substr2+')'
			if evaluate and res1 != None and res2 != None:	
				if node.type == 'shift_expr':
					if node.children[1].leaf == '<<':
						#str_exp = '('+substr1+'<<'+substr2+')'
						result = res1 << res2			
					else:
						#str_exp = '('+substr1+'>>'+substr2+')'
						result = res1 >> res2			
				elif node.type == 'add_expr':
					if node.children[1].leaf == '+':
						#str_exp = '('+substr1+'+'+substr2+')'
						result = res1 + res2			
					else:
						#str_exp = '('+substr1+'-'+substr2+')'
						result = res1 - res2
				elif node.type == 'mult_expr':
					if node.children[1].leaf == '*':
						#str_exp = '('+substr1+'*'+substr2+')'
						#print res1,'   ', res2 
						result = res1 * res2			
					elif node.children[1].leaf == '/':
						#str_exp = '('+substr1+'/'+substr2+')'
						result = res1 / res2			
					else:
						#str_exp = '('+substr1+'%'+substr2+')'
						result = res1 % res2

		else:
			str_exp += ' + ERROR'
			print node, '  ' , str_exp
		return str_exp, result
		
	def getValue(self, node):
		if node.children[0].type == 'integer_literal':
			return int(eval(node.children[0].leaf))
		elif node.children[0].type == 'floating_pt_literal':
			return float(eval(node.children[0].leaf))
		elif node.children[0].type == 'boolean_literal':
			return bool(eval(node.children[0].leaf))
		else:
			return None #node.leaf
	
		
	def definition(self, pt):
                child = UnknownNode(pt.children[0])
		if pt.children[0].type == 'type_dcl':
			child = self.type_dcl(pt.children[0])
		elif pt.children[0].type == 'const_dcl':
			child = self.const_dcl(pt.children[0])
		elif pt.children[0].type == 'except_dcl':
			child = self.except_dcl(pt.children[0])
		elif pt.children[0].type == 'interf':
			child = self.interf(pt.children[0])
		elif pt.children[0].type == 'module':
			child = self.module(pt.children[0])
		elif pt.children[0].type == 'value':
			child = self.value_def(pt.children[0])
		elif pt.children[0].type == 'type_id_dcl':
			child = self.type_id_dcl(pt.children[0])
		elif pt.children[0].type == 'type_prefix_dcl':
			child = self.type_prefix_dcl(pt.children[0])
		elif pt.children[0].type == 'event':
			child = self.event_def(pt.children[0])
		elif pt.children[0].type == 'component':
			child = self.component(pt.children[0])
		elif pt.children[0].type == 'home_dcl':
			child = self.home_dcl(pt.children[0])
		else:
			child = UnknownNode(pt.children[0])
		return child
	
	def type_dcl(self, pt):
		type_node = Type(None)
		
		if pt.children[0].type == 'type_declarator':
			type_node.add_attribute('specifier','typedef')
			typechild = self.type_spec(pt.the('type_declarator').the('type_spec'))
			type_node.add_child(typechild)
			decls = pt.the('type_declarator').the('declarators')
			decl_list = []
			for child in decls.children:
				decl_list.append(self.getDeclarator(child))
			dec_node = Declarator(None)
			dec_node.leaf = decl_list
			type_node.add_child(dec_node)
			
		elif pt.children[0].type == 'struct_type':
			struct_node = self.struct_type(pt.children[0])
			type_node.add_child(struct_node)
			type_node.add_attribute('specifier', 'constr_type')
		
		elif pt.children[0].type == 'enum_type':
			enum_node = self.enum_type(pt.children[0])
			type_node.add_child(enum_node)
			type_node.add_attribute('specifier', 'constr_type')
			
		elif pt.children[0].type == 'union_type':
			union_node = self.union_type(pt.children[0])
			type_node.add_child(union_node)
			type_node.add_attribute('specifier', 'constr_type')
		
		elif pt.children[0].type == 'simple_declarator':
			dec = Declarator(None)
			dec.leaf = pt.children[0].leaf
			dec.add_attribute('modifier', 'native')
			type_node.add_child(dec)
			
		elif pt.children[0].type == 'constr_forward_decl':
			dec = Declarator(None)
			dec.leaf = pt.the('constr_forward_decl').the('identifier').leaf
			#typetype = 'forward ' + pt.the('constr_forward_dcl').leaf
			dec.add_attribute('meta_type' , pt.the('constr_forward_decl').leaf)
			dec.add_attribute('modifier', 'forward')
			type_node.add_child(dec)
		else:
			type_node = UnknownNode(pt.children[0])
		return type_node

	def const_dcl(self, pt):
            const_node = Const()
            const_node.leaf = pt.the('identifier').leaf
	    const_node.add_child(self.const_type(pt.the('const_type')))
            str, res = self.getExpression(pt.the('const_exp'), True)
            if res != None:
                const_node.add_attribute('value', res)
            else:
                const_node.add_attribute('value', str)
	    
	    #type_inst = self.registry[const_node.the('type').leaf]
	    #self.registry.make_instance_add_instance(type_inst, const_node.leaf, const_node.get_attribute('value'))
            return const_node
	
	def const_type(self, pt):	
		child = pt.children[0]
		typenode = Type(None)
		if child.type == 'integer_type':
			typenode.leaf = self.integer_type(child)
		elif child.type == 'char_type':
			typenode.leaf = 'char'
		elif child.type == 'wide_char_type':
			typenode.leaf = 'wchar'
		elif child.type == 'boolean_type':
			typenode.leaf = 'boolean'
		elif child.type == 'floating_pt_type':
			typenode.leaf = self.floating_pt_type(child)
		elif child.type == 'string_type':
			typenode.leaf = self.string_type(child)
		elif child.type == 'wide_string_type':
			typenode.leaf = self.wide_string_type(child)
		elif child.type == '_type':
			typenode.leaf = 'fixed'
		elif child.type == 'scoped_name':
			typenode.leaf = self.scoped_name(child)
		elif child.type == 'octet_type':
			typenode.leaf = 'octet'
		else:
			typenode.leaf = 'UNKOWN'
		return typenode

        def except_dcl(self, pt):
            excep_node = ExceptionNode(None)
            excep_node.leaf = pt.the('identifier').leaf
            if pt.the('opt_member_list') != None:
                excep_node.add_children(self.member_list(pt.the('opt_member_list')))
            return excep_node

        def type_id_dcl(self, pt):
            type_id = Node(name='typeid')
            type_id.leaf = self.scoped_name(pt.the('scoped_name'))
            type_id.add_attribute('value', pt.the('string_literal').leaf)
            return type_id

        def type_prefix_dcl(self, pt):
            type_id = Node(name='typeid')
            type_id.leaf = self.scope_name(pt.the('scope_name'))
            type_id.add_attribute('value', pt.the('string_literal').leaf)
            return type_id
        
        def interf(self, pt):
            interface = Interface(None)
            if pt.leaf == 'abstract' or pt.leaf == 'local':
                interface.add_attribute('modifier', pt.leaf)
            for child in pt.children:
                if child.type == 'identifier':
                    interface.leaf = child.leaf
                elif child.type == 'interface_dcl':
                    #print child
                    if child.the('interface_header') != None:
                        scope_list = child.the('interface_header').the('interface_inheritance_spec').the('scoped_name_list')
                        for scope_name in scope_list['scoped_name']:
                            interface.add_child(Inheritance(name = self.scoped_name(scope_name)))
                    if child.the('interface_body') != None:
		    	exp_list = Export(None)
                        for export_child in child.the('interface_body').children:
				exp_node = self.export(export_child)
				exp_list.add_child(exp_node)
                                interface.add_child(exp_node)
            return interface
	
	def module(self, pt):
		mod = Module(None)
		for child in pt.children:
			if child.type == 'identifier':
				mod.leaf = child.leaf
			elif child.type == 'definition_list':
				for def_child in child.children:
					def_child = self.definition(def_child)
					mod.add_child(def_child)
			else:
				mod.add_child(UnknownNode(child))
		return mod
	
	def value_def(self, pt):
		if pt.children[0].type == 'value_dcl':
			return self.value_dcl(pt.children[0])
		elif pt.children[0].type == 'value_abs_dcl':
			return self.value_abs_dcl(pt.children[0])
		elif pt.children[0].type == 'value_box_dcl':
			val_node = Valuetype(None)
			val_node.leaf = pt.children[0].the('identifier').leaf
			val_node.add_child(self.type_spec(pt.children[0].the('type_spec')))
			return val_node
		elif pt.children[0].type == 'value_custom_dcl':
			val_node = self.value_dcl(pt.children[0].the('value_dcl'))
			val_node.add_attribute('modifier', 'custom')
			return val_node
		elif pt.children[0].type == 'value_forward_dcl':
			val_node = Valuetype(None)
			val_node.leaf = val_node.leaf = pt.children[0].the('identifier').leaf
			val_node.add_attribute('modifier', 'forward')
			return val_node
		else:
			return UnknownNode(pt.children[0].type)
			
	def event_def(self, pt):
		event_node = Event()
		child = pt.children[0]
		if child.type == 'event_abs':
			event_node.add_attribute('modifier', 'abstract')
			event_node.leaf = child.the('event_abs_dcl').the('event_header').the('identifier').leaf
			if child.the('event_abs_dcl') != None:
				event_node.add_child(self.value_inheritance_spec(child.the('event_abs_dcl').the('value_inheritance_spec')))
				exp_list = []
				for exp_child in child.the('event_abs_dcl')[export]:
					exp_list.append(self.export(exp_child))
				if exp_list != []:
					event_node.add_child(Export(exp_list))
		elif child.type == 'event_custom':
			event_node.add_attribute('modifier', 'custom')
			event_node.leaf = child.the('event_custom').the('event_header').the('identifier').leaf
			if child.the('event_elem_dcl') != None:
				event_node.add_child(self.value_inheritance_spec(child.the('event_elem_dcl').the('value_inheritance_spec')))
				exp_list = []
				for exp_child in child.the('event_elem_dcl')[export]:
					exp_list.append(self.export(exp_child))
				if exp_list != []:
					event_node.add_child(Export(exp_list))
		elif child.type == 'event_dcl':
			event_node.leaf = child.the('event_dcl').the('event_header').the('identifier').leaf
			if child.the('event_elem_dcl') != None:
				event_node.add_child(self.value_inheritance_spec(child.the('event_elem_dcl').the('value_inheritance_spec')))
				exp_list = []
				for exp_child in child.the('event_elem_dcl')[export]:
					exp_list.append(self.export(exp_child))
				if exp_list != []:
					event_node.add_child(Export(exp_list))
		
		else:
			return UnknownNode(child)
	
	def component(self, pt):
		compnode = Component(None)
		compnode.leaf = pt.the('identifier').leaf
		dcl = pt.the('component_dcl')
		if  dcl != None:
			inh = dcl.the('component_inheritance_spec')
			inhnode = Inheritance()
			inhnode.leaf = self.scoped_name(inh.the('soped_name'))
			component.add_child(inhnode)
			
			sup = dcl.the('supported_interface_spec')
			supnode = Support()
			name_list = []
			for name in sup['scoped_name']:
				name_list.append(self.scoped_name(name))
			supnode.leaf = name_list
			component.add_child(supnode)
			
			bod = dcl.the('component_body')
			if bod != None:
				exp_list = self.component_body(bod)
				if exp_list != []:
					component.add_children(exp_list)
		return component
	
	def home_dcl(self, pt):
		homenode = Home()
		#
		#	HEADER
		#
		homeheader = pt.the('home_header')
		homenode.leaf = homeheader.the('identifier').leaf
		if homeheader.the('home_inheritance_spec') != None:
			inhnode = Inheritance()
			inhnode.leaf = self.scoped_name(homeheader.the('home_inheritance_spec').the('scoped_name'))
			homenode.add_child(inhnode)
		if homeheader.the('supported_interface_spec') != None:
			supnode = Support()
			namelist = []
			for name in homeheader.the('supported_interface_spec')['scoped_name']:
				namelist.append(self.scoped_name(name))
			supnode.leaf = namelist
			homenode.add_child(supnode)
		mannode = Node(None, name='manages')
		mannode.leaf = self.scoped_name(homheader.the('scoped_name'))
		if homeheader.the('primary_key_spec') != None:
			mannode.add_attribute('primarykey', self.scoped_name(homeheader.the('primary_key_spec').the('scoped_name')))
		homenode.add_child(mannode)
		#
		#	BODY
		#
		homebody = pt.the('home_body')
		for child in homebody.children:
			if child.children[0].type == 'export':
				homenode.add_child(self.export(child.children[0]))
			elif child.children[0].type == 'factory_dcl':
				homenbode.add_child(self.factory_dcl(child.children[0]))
			elif child.children[0].type == 'finder_dcl':
				homenode.add_child(self.finder_dcl(child.children[0]))
			else:
				homenode.add_child(UnknownNode(child.children[0]))
		
		return homenode
	
	def factory_dcl(self, pt):
		fac_node = Node(None, name = 'factory')
		fac_node.leaf = pt.the('identifier').leaf
		fac_node.add_children(self.init_param_decls(pt.the('init_param_decls')))
		if pt.the('raises_expr') != None:
			raises = Node(name='raises')
			leaflist = []
			for node in child.the('scoped_name_list').children:
				if node.type == 'scoped_name':
					leaflist.append(self.scoped_name(node))
			raises.leaf = leaflist
			fac_node.add_child(raises)
		return fac_node
	
	def finder_dcl(self, pt):
		fac_node = Node(None, name = 'finder')
		fac_node.leaf = pt.the('identifier').leaf
		fac_node.add_children(self.init_param_decls(pt.the('init_param_decls')))
		if pt.the('raises_expr') != None:
			raises = Node(name='raises')
			leaflist = []
			for node in child.the('scoped_name_list').children:
				if node.type == 'scoped_name':
					leaflist.append(self.scoped_name(node))
			raises.leaf = leaflist
			fac_node.add_child(raises)
		return fac_node
		
	
	def component_body(self, pt):
		exp_list = []
		for exp in pt.children:
			exp_node = Export()
			if exp.children[0].type == 'provides_dcl':
				exp_node.add_attribute('type', 'provides')
				exp_node.leaf = exp.children[0].the('identifier').leaf
				if exp.children[0].the('interface_type').the('scoped_name') != None:
					scopedname = self.scoped_name(exp.children[0].the('interface_type').the('scoped_name'))
					exp_node.add_attribute('name', scopedname)
				else:
					exp_node.add_attribute('name', 'Object')
			elif exp.children[0].type == 'uses_dcl':
				typestr = ''
				for child in exp.children[0]['uses_dcl']:
					typestr += child.leaf
				exp_node.add_attribute('type', typestr)
				exp_node.leaf = exp.children[0].the('identifier').leaf
				if exp.children[0].the('interface_type').the('scoped_name') != None:
					scopedname = self.scoped_name(exp.children[0].the('interface_type').the('scoped_name'))
					exp_node.add_attribute('name', scopedname)
				else:
					exp_node.add_attribute('name', 'Object')						
			elif exp.children[0].type == 'emits_dcl':
				exp_node.add_attribute('type', 'emits')
				exp_node.leaf = exp.children[0].the('identifier').leaf
				scopedname = self.scoped_name(exp.children[0].the('scoped_name'))
				exp_node.add_attribute('name', scopedname)
			elif exp.children[0].type == 'publishes_dcl':
				exp_node.add_attribute('type', 'publishes')
				exp_node.leaf = exp.children[0].the('identifier').leaf
				scopedname = self.scoped_name(exp.children[0].the('scoped_name'))
				exp_node.add_attribute('name', scopedname)
			elif exp.children[0].type == 'consumes_dcl':
				exp_node.add_attribute('type', 'consumes')
				exp_node.leaf = exp.children[0].the('identifier').leaf
				scopedname = self.scoped_name(exp.children[0].the('scoped_name'))
				exp_node.add_attribute('name', scopedname)
			elif exp.children[0].type == 'attr_dcl':
				exp_node.add_child(self.attr_dcl(exp.children[0]))
			else:
				exp_list.append(UnknownChild(exp))
			exp_list.append(exp_node)
		return exp_list
		
	
	def value_dcl(self, pt):
		node = Valuetype(None)
		for child in pt.children:
			if child.type == 'identifier':
				node.leaf = child.leaf
			elif child.type == 'value_inheritance_spec': 
				val_inh_node = self.value_inheritance_spec(self, child)
				node.add_child(val_inh_node)
			else:
				node.add_child(UnknownNode(child))
                return node
	
	def value_abs_dcl(self, pt):
		node = Valuetype(None)
		node.add_attribute('modifier', 'abstract')
		for child in pt.children:
			if child.type == 'identifier':
				node.leaf = child.leaf
			elif child.type == 'value_abs_full_dcl':
				val_inh_node = self.value_inheritance_spec(self, child.the('value_inheritance_spec'))
				exp_list = []
				for exp_child in child[export]:
					exp_list.append(self.export(exp_child))
				if exp_list != []:
					val_inh_node.add_child(Export(exp_list))
			else:
				node.add_child(UnknownNode(child))
                return node
		
	def value_inheritance_spec(self, pt):
		if pt.children[0].type == 'value_value_inheritance_spec':
			inh_node = Inheritance(None)
			inh_node.add_attribute('relation', 'value')
			if pt.children[0].the('value_value_inheritance_spec') != None:
				inh_node.add_attribute('modifier', pt.children[0].the('value_value_inheritance_spec').leaf)
			name_list = []
			for name in pt.the('value_value_inheritance_spec')['value_name']:
				name_list.append(self.scoped_name(name.the('scoped_name')))
			inh_node.leaf = name_list
			return inh_node
		elif pt.children[0].type == 'value_interface_inheritance_spec':
			inh_node = Inheritance(None)
			inh_node.add_attribute('relation', 'interface')
			name_list = []
			for name in pt.the('value_interface_inheritance_spec')['interface_name']:
				name_list.append(self.scoped_name(name.the('scoped_name')))
			inh_node.leaf = name_list
			return inh_node
		else:
			return UnknownNode(pt)
	
	def value_element(self, pt):
		if pt.children[0].type == 'export':
			return self.export(pt.children[0])
		elif pt.children[0].type == 'state_member':
			return self.state_member(pt.children[0])
		elif pt.children[0].type == 'init_dcl':
			return self.init_dcl(pt.children[0])
		else:
			return UnknownNode(pt)
	
	def state_member(self, pt):
		type_node = Type(None)
		
		if pt.the('state_member') != None:
			type_node.leaf = child.leaf
		type_node.add_child(self.type_spec(pt.the('type_spec')))
		decls = pt.the('declarators')
		decl_list = []
		for child in decls.children:
			decl_list.append(self.getDeclarator(child))
		dec_node = Declarator(None)
		dec_node.leaf = decl_list
		type_node.add_child(dec_node)
		return type_node
	
	def init_dcl(self, pt):
		type_node = Node(None, name = 'factory')
		type_node.leaf = pt.the('identifier').leaf
		if pt.the('init_param_decls') != None:
			type_node.add_children(self.init_param_decls(pt.the('init_param_decls')))
		if pt.the('raises_expr') != None:
			raises = Node(name='raises')
			leaflist = []
			for node in child.the('scoped_name_list').children:
				if node.type == 'scoped_name':
					leaflist.append(self.scoped_name(node))
			raises.leaf = leaflist
			type_node.add_child(raises)
		return type_node
		
	def init_param_decls(self, pt):
		decl_list = []
		for child in pt['init_param_decl']:
			param_node = Parameter(None)
			param_node.add_child(self.param_type_spec(child.the('param_type_spec')))
			param_node.leaf = child.the('simple_declarator').leaf
			if child.the('init_param_attribute') != None:
				param_node.add_attribute('attribute', child.the('init_param_attribute').leaf)
			decl_list.append(param_node)
		return decl_list
		
			
		
        def export(self, pt):
            
            if pt.children[0].type == 'type_dcl':
                return self.type_dcl(pt.children[0])
            elif pt.children[0].type == 'const_dcl':
                return self.const_dcl(pt.children[0])
            elif pt.children[0].type == 'except_dcl':
                return self.except_dcl(pt.children[0])
            elif pt.children[0].type == 'attr_dcl':
                return self.attr_dcl(pt.children[0])
            elif pt.children[0].type == 'op_dcl':
                return self.op_dcl(pt.children[0])
            elif pt.children[0].type == 'type_id_dcl':
                return self.type_id_dcl(pt.children[0])
            elif pt.children[0].type == 'type_prefix_dcl':
                return self.type_prefix_dcl(pt.children[0])
            else:
                return UnknownNode(pt.children[0])
		
	def attr_dcl(self,pt):
		attr_node = Attribute(None)
		if pt.children[0].type == 'readonly_attr_spec':
			attr_node.add_attribute('mode', 'readonly')
			attr_node.add_child(self.attr_declarator(pt.children[0].the('readonly_attr_declarator')))
		elif pt.children[0].type == 'attr_spec':
			attr_node.add_attribute('mode', 'readwrite')
			attr_node.add_child(self.attr_declarator(pt.children[0].the('attr_declarator')))
		else:
			attr_node = UnknownNode(pt.children[0])
		attr_node.add_child(self.param_type_spec(pt.children[0].the('param_type_spec')))
		
		return attr_node
		
	def op_dcl(self, pt):
		fcn = Function(None)
		for child in pt.children:
			if child.type == 'decorator':
				#print child
				dec_children = self.decorator_elements(child)
				dec_node = Decorator(dec_children)
				fcn.add_child(dec_node)
			elif child.type == 'op_attribute':
				fcn.add_attribute('attribute', child.leaf)
			elif child.type == 'op_type_spec':
				if child.leaf == 'void':
					fcn.add_child(Type(None, name = 'void'))
				else:
					typenode = self.param_type_spec(child.the('param_type_spec'))
					fcn.add_child(typenode)
			elif child.type == 'op_dcl':
				fcn.leaf = child.leaf
			elif child.type == 'parameter_dcls':
				fcn.add_children(self.parameter_dcls(child))
			elif child.type == 'raises_expr':
				raises = Node(name='raises')
				leaflist = []
				for node in child.the('scoped_name_list').children:
					if node.type == 'scoped_name':
						leaflist.append(self.scoped_name(node))
				raises.leaf = leaflist
				fcn.add_child(raises)
			elif child.type == 'context_expr':
				context = Node(name='context')
				leaflist = []
				for node in child.the('string_literal_list').children:
					if node.type == 'string_literal':
						leaflist.append(node.leaf)
				context.leaf = leaflist
				fcn.add_child(context)
			else:
				fcn = UnknownNode(child)
		return fcn
		
	def parameter_dcls(self, pt):
		param_list = []
		if pt.the('param_dcl_list') != None:
			dec_node = None
			param_node = None
			for child in pt.the('param_dcl_list').children:
				if child.type == 'decorator':
					#print child
					dec_els = self.decorator_elements(child)
					dec_node = Decorator(dec_els)
					
					#print dec_node
				if child.type == 'param_dcl':
					param_node = self.param_dcl(child)
					if dec_node != None:
						param_node.add_child(dec_node)
						dec_node = None
					param_list.append(param_node)
		return param_list
	
	def param_dcl(self, pt):
		param_node = Parameter(None)
		param_node.add_attribute('direction', pt.leaf)
		for child in pt.children:
			if child.type == 'param_type_spec':
				param_node.add_child(self.param_type_spec(child))
			elif child.type == 'allow_indirection':
				param_node.add_attribute('indirection', child.leaf)
			elif child.type == 'simple_declarator':
				param_node.leaf = child.leaf
			else:
				param_node.add_child(UnkownNode(child))
		return param_node
			
			
					
	def attr_declarator(self, pt):
		decl = Declarator(None)
		
		for child in pt.children:
			if child.type == 'simple_declarator':
				#childnode = Node(None)
				#childnode.name = 'identifier'
				decl.leaf = child.leaf
				#decl.add_child(childnode)
			elif child.type == 'attr_raises_expr':
				decl.add_child(self.attr_raises_expr(child))
			else:
				decl.add_child(UnkownNode(child))
		return decl
		
		
	def param_type_spec(self, pt):
		
		param_type = Type(None)
		if pt.children[0].type == 'base_type_spec':
			param_type = self.base_type_spec(pt.children[0])
		elif pt.children[0].type == 'string_type':
			param_type = self.string_type(pt.children[0])
		elif pt.children[0].type == 'wide_string_type':
			param_type = self.wide_string_type(pt.children[0])
		elif pt.children[0].type == 'scoped_name':
			param_type.leaf = self.scoped_name(pt.children[0])
		else:
			param_type = UnknownNode(pt.children[0])
		return param_type
	
	def attr_raises_expr(self, pt):
		raisesnode = Node(None)
		for child in pt.children:
			if child.type == 'get_excep_expr':
				raisesnode.leaf = 'getraises'
				exception_list = self.exception_list(child.the('exception_list'))
				raisesnode.add_attribute('exception_list', exception_list)
			elif child.type == 'set_excep_expr':
				raisesnode.leaf = 'setraises'
				exception_list = self.exception_list(child.the('exception_list'))
				raisesnode.add_attribute('exception_list', exception_list)
			else:
				raisesnode = UnknownNode(child)
		return raisesnode
		
	def exception_list(self, pt):
		ex_list = []	
		for child in pt.children:
			if child.type == 'scoped_name':
				exlist.append(self.scoped_name(child))
		return ex_list
	
		
	def struct_type(self, pt):
		dec = Declarator(None)
		dec.add_attribute('meta_type', 'struct')
		dec.leaf = pt.the('identifier').leaf
		
		memberlist = self.member_list(pt.the('member_list'))
		dec.add_children(memberlist)
		
		return dec
	    
	def enum_type(self, pt):
		dec = Declarator(None)
		dec.add_attribute('meta_type', 'enum')
		for child in pt.children:
                    #print child.type
                    if child.type == 'identifier':
                        dec.leaf = child.leaf
                    elif child.type == 'enumerator_list':
                        enum_list = []
                        for enum in child['enumerator']:
                            enum_list.append(enum.leaf)
			dec.add_attribute('enumeration', enum_list)
		return dec

	def union_type(self,pt):
                dec = Declarator(None)
		dec.add_attribute('meta_type', 'union')
		for child in pt.children:
			if child.type == 'identifier':
                            dec.leaf = child.leaf
			elif child.type == 'switch_type_spec':
                            name = 'unknown'
                            if child.children[0].type == 'integer_type':
                                name = self.integer_type(child.children[0])
                            elif child.children[0].type == 'char_type':
                                name = 'char'
                            elif child.children[0].type == 'boolean_type':
                                name = 'boolean'
                            elif child.children[0].type == 'enum_type':
                                name = 'enum'
                            elif child.children[0].type == 'scoped_name':
                                name = self.scoped_name(child.children[0])
                            dec.add_attribute('switch_type',name)
                        elif child.type == 'switch_body':
                            pass
                            switch_body = self.case_stmt_list(child.the('case_stmt_list'))
                            dec.add_children(switch_body)
		return dec

	def case_stmt_list(self, pt):
            cases = []
            for case in pt.children:
                case_node = CaseNode(None)
                #case_node.leaf = case.leaf
                if case.the('const_exp') != None:
                    str, res = self.getExpression(case.the('const_exp'), False)
                    if res != None:
                        #case_node.add_attribute('value', res)
			case_node.leaf = res
                    else:
                        #case_node.add_attribute('value', str)
			case_node.leaf = str
                typenode = self.type_spec(case.the('element_spec').the('type_spec'))
		decl = case.the('element_spec').the('declarator')
		typenode.add_attribute('declarator', self.getDeclarator(decl))
		typenode.add_child(case_node)
                cases.append(typenode)
            return cases
        
	def member_list(self, pt):
		memberlist = []
		typememberlist = []
		for child in pt.children:
			if child.type == 'member':
				typenode = self.type_spec(child.the('type_spec'))
				for decl in child.the('declarators').children:
					typenode.add_attribute('declarator', self.getDeclarator(decl))
				memberlist.append(typenode)
			else:
				print 'memberlist_unknown' + child.type
				memberlist.append(UnknownNode(child))
		return memberlist

	def scoped_name(self, pt):
            name = pt.leaf
            if name == '::':
                name = ''
            for child in pt.children:
                name += '::' + child.leaf
            return name
	
	def type_spec(self, pt):
		typenode = None
		if pt.children[0].type == 'simple_type_spec':
			typenode = self.simple_type_spec(pt.children[0])
		else: #constr_type_spec
			typenode = self.constr_type_spec(pt.children[0])
		return typenode
		
	def simple_type_spec(self, pt):
		typenode = None
		#print pt
		if pt.children[0].type == 'base_type_spec':
			typenode = self.base_type_spec(pt.children[0])
		elif pt.children[0].type == 'template_type_spec':
			typenode = self.template_type_spec(pt.children[0])
		else: #scoped_name
			typenode = Type(None)
			typenode.leaf = self.scoped_name(pt.children[0])
		return typenode
		
	def base_type_spec(self, pt):
		typenode = Type(None)
		#print pt
		if pt.children[0].type == 'floating_pt_type':
			typenode.leaf = self.floating_pt_type(pt.children[0])
		elif pt.children[0].type == 'integer_type':
			typenode.leaf = self.integer_type(pt.children[0])
		else:
			typenode.leaf = pt.children[0].leaf
		return typenode
	    
	def integer_type(self,pt):
            name = '' 
            child = pt.children[0]
            while not (child.children == []):
                    name += ' ' + child.children[0].leaf
                    if len(child.children) == 2:
                            name += ' ' + child.children[1].leaf
                    child = child.children[0]
            return name[1:]

        def floating_pt_type(self,pt):
            name = pt.leaf
	    if pt.children != []:
	    	name += ' ' + pt.children[0].leaf
            return name
        
        
	def template_type_spec(self, pt):
                typenode = Type(None)
                if pt.children[0].type == 'sequence_type':
                    typenode = self.sequence_type(pt.children[0])
                elif pt.children[0].type == 'string_type':
		    typenode = self.string_type(pt.children[0])
                elif pt.children[0].type == 'wide_string_type':
                    typenode = self.wide_string_type(pt.children[0])                   
                elif pt.children[0].type == 'fixed_pt_type':
                    typenode.leaf = 'fixed'
                    fix_str = ''
                    pos_const_node = pt.the('fixed_pt_type')['positive_int_const'][0]
                    constant_str, result = self.getExpression(pos_const_node.the('const_exp'))
                    if result != None:
                        fix_str = str(result)
                    else:
                        fix_str = constant_str
                    pos_const_node = pt.the('fixed_pt_type')['positive_int_const'][1]
                    constant_str, result = self.getExpression(pos_const_node.the('const_exp'))
                    if result != None:
                        fix_str += ',' + str(result)
                    else:
                        fix_str += ',' + constant_str
                else:
                    typenode = UnknownNode(pt.children[0])
		return typenode
	def sequence_type(self, pt):
		typenode = Type(None)
		typenode.leaf = 'sequence'
                simple_type_node = self.simple_type_spec(pt.the('simple_type_spec'))
                typenode.add_child(simple_type_node)
                pos_const_node = pt.the('opt_pos_int')
		typenode.add_attribute('meta_type', 'sequence')
                if pos_const_node != None:
                	constant_str, result = self.getExpression(pos_const_node.the('positive_int_const').the('const_exp'))
                	typenode.add_attribute('length', constant_str)
		return typenode
		
	def string_type(self, pt):
		typenode = Type(None)
		typenode.leaf = 'string'
                pos_const_node = pt.the('positive_int_const')
                if pos_const_node != None:
                    constant_str, result = self.getExpression(pos_const_node.the('const_exp'))
		    #typenode.add_attribute('type', 'string')
              	    #name = ['char', constant_str, '['+constant_str + ']']
                    typenode.add_attribute('length', constant_str)
		    #typenode.leaf = name
		return typenode	    
		
	def wide_string_type(self, pt):
		typenode = Type(None)
		typenode.leaf = 'wstring'
                pos_const_node = pt.the('positive_int_const')
                if pos_const_node != None:
                    constant_str, result = self.getExpression(pos_const_node.the('const_exp'))
                    typenode.add_attribute('type', 'wstring')
                    if result != None:
		    	name = ['wchar_t', result, '['+constant_str + ']']
                        typenode.add_attribute('length', result)
                    else:
			name = ['wchar_t', constant_str, '['+constant_str + ']']
                        typenode.add_attribute('length', constant_str)
		    typenode.leaf = name
		return typenode	   
			   
	    
	def constr_type_spec(self, pt):
            constr_type_node = UnknownNode(pt.children[0])
            if pt.children[0].type == 'struct_type':
                constr_type_node = self.struct_type(pt.children[0])
            elif pt.children[0].type == 'union_type':
                constr_type_node = self.union_type(pt.children[0])
            elif pt.children[0].type == 'enum_type':
                constr_type_node = self.enum_type(pt.children[0])
	    return constr_type_node
	
	def getDeclarator(self, pt):
		decl_str = ''
		if pt.children[0].type == 'simple_declarator':
			decl_str = pt.children[0].leaf
		else: #complex_declarator
			array_dcl = pt.the('complex_declarator').the('array_declarator')
			leaf_str = array_dcl.leaf
			for child in array_dcl.children:
				exp_node = child.the('positive_int_const').the('const_exp')
				exp_str, res = self.getExpression(exp_node, True)
				array_dcl = []
				length_str = ''
				if res != None:
					array_dcl.append(res)
					length_str += '+(' + str(res) + ')'
				else:
					array_dcl.append(exp_str)
					length_str += '+(' + exp_str + ')'
			decl_str = [[leaf_str, length_str, array_dcl]]
		return decl_str
			 
			
def gen(pt):
	#registry = new_registry('Generic 32')
	#newtype = registry.make_type('alias','myName', 'int')
	#print newtype
	#registry.add_type(newtype)
	astgen = ASTGen()
	output = astgen.convert(pt)
	#registry.print_registry()
	return output
			
			
			
			
			
			
			

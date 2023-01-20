#
# Australian Public Licence B (OZPLB)
# 
# Version 1-0
# 
# Copyright (c) 2004 National ICT Australia
# 
# All rights reserved. 
# 
# Developed by: Embedded Real-time and Operating Systems Group (ERTOS)
#               National ICT Australia
#               http://www.ertos.nicta.com.au
# 
# Permission is granted by National ICT Australia, free of charge, to
# any person obtaining a copy of this software and any associated
# documentation files (the "Software") to deal with the Software without
# restriction, including (without limitation) the rights to use, copy,
# modify, adapt, merge, publish, distribute, communicate to the public,
# sublicense, and/or sell, lend or rent out copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject
# to the following conditions:
# 
#    # Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimers.
# 
#    # Redistributions in binary form must reproduce the above
#       copyright notice, this list of conditions and the following
#       disclaimers in the documentation and/or other materials provided
#       with the distribution.
# 
#    # Neither the name of National ICT Australia, nor the names of its
#       contributors, may be used to endorse or promote products derived
#       from this Software without specific prior written permission.
# 
# EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
# PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
# NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
# WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
# BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
# REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
# THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
# ERRORS, WHETHER OR NOT DISCOVERABLE.
# 
# TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
# NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
# THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
# LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
# OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
# OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
# OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
# CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
# CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
# DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
# CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
# DAMAGES OR OTHER LIABILITY.
# 
# If applicable legislation implies representations, warranties, or
# conditions, or imposes obligations or liability on National ICT
# Australia or one of its contributors in respect of the Software that
# cannot be wholly or partly excluded, restricted or modified, the
# liability of National ICT Australia or the contributor is limited, to
# the full extent permitted by the applicable legislation, at its
# option, to:
# a.  in the case of goods, any one or more of the following:
# i.  the replacement of the goods or the supply of equivalent goods;
# ii.  the repair of the goods;
# iii. the payment of the cost of replacing the goods or of acquiring
#  equivalent goods;
# iv.  the payment of the cost of having the goods repaired; or
# b.  in the case of services:
# i.  the supplying of the services again; or
# ii.  the payment of the cost of having the services supplied again.
# 
# The construction, validity and performance of this licence is governed
# by the laws in force in New South Wales, Australia.
#

"""IDL parser. Originally based on the Yacc grammar for the Mungi Component System by Antony Edwards, with modifications for IDL4 by Andreas Haeberlen."""

from dparser import Parser, Reject
import sys

if __name__ == '__main__':
	# Allows importing of parser_common if called from cmdline
	sys.path.insert(0, '.')

from parser_common import ParserLexerState, print_tree, Node, ExpressionNode, UnaryOperatorNode

from debugging import debug

from astgen import gen as ast_gen

def get_only(somelist, type_name_list):
	#print "get only", [item.type for item in somelist if hasattr(item, 'type')]
	return [item for item in somelist if hasattr(item, "type") and item.type in type_name_list]

def d_IDLFile(t):
	"IDLFile : definition_list"
	return Node('IDLFile', t[0].children)
	
def d_definition_list(t):
	"definition_list : (decorated_definition ';')+"
	# We get t[0] == [deco_defn, ';'] or [deco_defn, ';', deco_defn, ';'] or ...
	return Node('definition_list', get_only(t[0], ['decorated_definition', 'definition']))

def d_decorated_definition(t):
	""" decorated_definition : decorator* definition
	"""
	if t[0]:
		return Node('decorated_definition', t[0] + t[1].children)
	else:
		return Node('decorated_definition', t[1].children)

def d_decorator(t):
	""" decorator : '[' IDENTIFIER '(' const_expr? (',' const_expr)* ')' ']' """
	args = []
	if t[3]:
		args.append(t[3][0])
	if t[4]:
		args.extend(t[4][1::2])
	# As a convenience, the result of a single-parameter decorator is the reuslt
	# of its first child.
	if len(args) == 1:
		result = args[0].result
	else:
		result = None
	return Node('decorator', args, t[1], result = result)

def d_definition(t):
	""" definition : type_declaration
				| const_declaration
				| except_declaration
				| interface_decl
				| module
				
				| import
				| modifier
				| component_decl
	"""
	return Node('definition', [t[0]])
	

#
#  'import' grammar
#	
def d_import(t, parser):
	"""import : 'import' filename """
	parser.shared_state.import_handler(t[1])
	return Node('import', None, t[1])

def d_filename(t):
	'filename : STRING_LITERAL'
	return t[0]



#
#  'module' grammar
#	
def d_module(t):
	"""module : 'module' IDENTIFIER '{' module_def_list '}'"""
	return Node('module', [t[1], t[3]])
def d_module_def_list(t):
	'module_def_list : decorated_definition+'
	raise Exception("Broken")
	return Node('module_def_list', [t[0]])
	
#
#  'modifier' grammar
#	
def d_modifier(t):
	"modifier : 'modifier' IDENTIFIER '(' INTEGER_LITERAL ')'"
	# FIXME: Obsolete?
	t.parser.shared_state.addModifier (t[1])
	return Node('modifier', None, (t[1], t[3]))
#
#  'modifier_list' grammar
#	
	
def d_modifier_list(t):
	"""modifier_list : '[' _modifier_list ']'
	"""
	return Node('modifier_list', t[1].children)
def d__modifier_list(t):
	"""_modifier_list : modifier_element
					| _modifier_list ',' modifier_element
	"""
	if t[0].type=='modifier_element':
		return Node('_modifier_list', [t[0]])
	else:
		return Node('_modifier_list', t[0].children + [t[2]])
def d_modifier_element(t):
	'modifier_element : MOD_IDENTIFIER modifier_arg_list?'
	if t[1]:
		return Node('modifier_element', t[1][0].children, t[0])
	else:
		return Node('modifier_element', None, t[0])
def d_modifier_arg_list(t):
	"""modifier_arg_list : 
						| '(' ')'
						| '(' _modifier_arg_list ')'
	"""
	if t[0] == '(':
		if t[1] ==')':
			return Node('modifier_arg_list')
		else:
			return Node('modifier_arg_list', t[1].children)
	else:
		return Node('modifier_arg_list') # null list
def d__modifier_arg_list(t):
	"""_modifier_arg_list : modifier_arg
						| _modifier_arg_list ',' modifier_arg
	"""
	if t[0].type=='modifier_arg':
		return Node('_modifier_arg_list', [t[0]])
	else:
		return Node('_modifier_arg_list', [t[0], t[2]])
def d_modifier_arg(t):
	"""modifier_arg : INTEGER_LITERAL
		| namespaced_identifier"""
	# 'modifier_arg : INTEGER_LITERAL'
	if type(t[0]) is int:
		return Node('modifier_arg', None, t[0])
	else:
		return Node('modifier_arg', None, t[0].leaf)

def d_namespaced_identifier(t):
	"""namespaced_identifier : IDENTIFIER
		| IDENTIFIER '::' IDENTIFIER"""
	if len(t) == 3 and t[1] == '::':
		return Node('namespaced_identifier', None, [t[0], t[2]])
	else:
		return Node('namespaced_identifier', None, [None, t[0]])

def d_scoped_name(t):
	'scoped_name: ('::')? IDENTIFIER ('::' IDENTIFIER)*
	return Node('scoped_name', 

def d_interface_decl(t):
	'interface_decl : interface_sig interface_def'
	return Node('interface_decl', [t[0], t[1]])
def d_interface_sig(t):
	"""interface_sig : interface_modifiers 'interface' IDENTIFIER (':' inheritance)? (',' inheritance)*"""
	args = [t[0]]
	if t[3]:
		args.append(t[3][1])
	if t[4]:
		args.extend(t[4][1::2])
	return Node('interface_sig', args, t[2])
	
def d_interface_modifiers(t):
	"""interface_modifiers : modifier_list*"""
	return Node('interface_modifiers', t[0])
	
def d_inheritance(t):
	"""inheritance :  IDENTIFIER"""
	return Node('inherits_from', [], t[0])
		
def d_interface_def(t):
	"""interface_def : ('{' interface_body '}')?"""
	if t[0]:
		return Node('interface_def', [t[0][1]])
	else: # null defn
		return Node('interface_def')
def d_interface_body(t):
	"""interface_body : _interface_body?"""
	if not t[0]:
		return Node('interface_body')
	else:
		return Node('interface_body', t[0][0].children)
def d__interface_body(t):
	"""_interface_body : export
				| _interface_body export"""
	if t[0].type=='export':
		return Node('_interface_body', [t[0]])
	else:
		return Node('_interface_body', t[0].children +[t[1]])
def d_export(t):
	"""export : attr_declaration ';'
			| op_declaration ';'
	"""
	return Node('export', [t[0]])
def d_attr_declaration(t):
	"attr_declaration : attr_modifiers 'attribute' attr_type_spec attr_declarators"
	return Node('attr_declaration', [t[0], t[2], t[3]], t[1])
def d_attr_modifiers(t):
	"""attr_modifiers : modifier_list?"""
	if t[0]:
		return Node('attr_modifiers', t[0][0].children)
	else:
		return Node('attr_modifiers')
def d_attr_type_spec(t):
	"""attr_type_spec : existing_constr_type allow_indirection
	"""
	return Node('attr_type_spec', [t[0], t[1]])
def d_attr_declarators(t):
	""" attr_declarators : attr_identifier
						| attr_declarators ',' attr_identifier
	"""
	if t[1]==',': # attr_declarators, attr_identifier
		return Node('attr_declarators', t[0].children + [t[1]])
	else: # attr_identifier
		return Node('attr_declaratos', [t[0]])
def d_attr_identifier(t):
	'attr_identifier : IDENTIFIER'
	return Node('attr_identifier', None, t[0])
def d_op_declaration(t):
	"op_declaration : op_modifiers op_return_type IDENTIFIER '(' parameter_list ')' raises_expr context_expr"
	return Node('op_declaration', [t[0], t[1], t[4], t[6], t[7]], t[2])
def d_op_modifiers(t):
	"""op_modifiers : modifier_list?"""
	if t[0]:
		return Node ('op_modifiers', t[0][0].children)
	else:
		return Node('op_modifiers')
def d_op_return_type(t):
	"""op_return_type : existing_constr_type
				| template_type
				| 'void'"""
	if t[0] == 'void':
		return Node('op_return_type', None, t[0])  # No children: assume void
	else:
		return Node('op_return_type', [t[0]])
def d_parameter_list(t):
	"""parameter_list : _parameter_list?"""
	if t[0]:
		return Node('parameter_list', t[0][0].children)
	else:
		return Node('parameter_list')
def d__parameter_list(t):
	"""_parameter_list : parameter_decl
				| _parameter_list ',' parameter_decl"""
	if t[0].type == 'parameter_decl':
		return Node('_parameter_list', [t[0]])
	else:
		return Node('_parameter_list', t[0].children +[t[2]])
def d_parameter_decl(t):
	"parameter_decl : parameter_modifiers parameter_direction parameter_type allow_indirection IDENTIFIER"
	return Node('parameter_decl', [t[0], t[1], t[2], t[3]], t[4])

def d_parameter_direction(t):
	"""parameter_direction : 'in'
		| 'out'
		| 'inout'"""
	return Node('parameter_direction', None, t[0])

def d_parameter_modifiers(t):
	"""parameter_modifiers : modifier_list?"""
	if t[0]:
		return Node('parameter_modifiers', t[0][0].children)
	else:
		return Node('parameter_modifiers')
def d_parameter_type(t):
	"""parameter_type : existing_constr_type
				| template_type"""
	return Node('parameter_type', [t[0]])
def d_raises_expr(t):
	"""raises_expr : ('raises' '(' exception_list ')')?"""
	if not t[0]:
		return Node('raises_expr')
	else:
		return Node('raises_expr', [t[0][2]])
def d_exception_list(t):
	"""exception_list : exception_identifier
				| exception_list ',' exception_identifier"""
	if t[1] == ',':
		return Node ('exception_list', t[1].children+[t[3]])
	else:
		return Node ('exception_list', [t[0]])
def d_exception_identifier(t):
	"exception_identifier : IDENTIFIER"
	return Node('exception_identifier', None, t[0])
def d_context_expr(t):
	"""context_expr : ('context' '(' context_list ')')?"""
	if t[0]:
		return Node('context_expr', [t[0][2]])
	else: # null
		return Node('context_expr')
def d_context_list(t):
	"""context_list : context_string
				| context_list ',' context_string"""
	if t[1]==',':
		return Node('context_list', t[0].children+[t[2]])
	else:
		return Node('context_list', [t[0]])
def d_context_string(t):
	"context_string : STRING_LITERAL"
	return Node('context_string', None, t[0])
def d_component_decl(t):
	"component_decl : component_modifiers 'component' IDENTIFIER component_definition"
	return Node('component_decl', [t[0], t[3]], t[2])
def d_component_modifiers(t):
	"""component_modifiers : modifier_list?"""
	if t[0]:
		return Node('component_modifiers', t[0][0].children)
	else:
		return Node('component_modifiers')
def d_component_definition(t):
	"component_definition : '{' component_body '}'"
	return Node('component_definition', [t[1]])
def d_component_body(t):
	"""component_body : _component_body?"""
	if t[0]:
		return Node('component_body', t[0][0].children)
	else:
		return Node('component_body')
def d__component_body(t):
	"""_component_body : component_export ce_identity ';' """
	return Node('_component_body', [t[0],t[1]])
def d_component_export(t):
	"""component_export : _component_export ce_identity ';' """
	return Node ('component_export', [t[0],t[1]])
def d__component_export(t):
	"""_component_export : provides_decl
					| uses_decl
					| publishes_decl
					| emits_decl
					| consumes_decl"""
	return Node('_component_export', [t[0]])
def d_ce_identity(t):
	"ce_identity : IDENTIFIER"
	return Node('ce_identity', None, t[0])
def d_cmpt_export_modifiers(t):
	"""cmpt_export_modifiers : modifier_list?"""
	if t[0]:
		return Node('cmpt_export_modifiers', t[0][0].children)
	else:
		return Node('cmpt_export_modifiers')
def d_provides_decl(t):
	"provides_decl : cmpt_export_modifiers 'provides'"
	return Node('provides_decl', [t[0]])
def d_uses_decl(t):
	"uses_decl : cmpt_export_modifiers 'uses'"
	return Node('uses_decl', [t[0]])
def d_publishes_decl(t):
	"publishes_decl : cmpt_export_modifiers 'publishes'"
	return Node('publishes_decl', [t[0]])
def d_emits_decl(t):
	"emits_decl : cmpt_export_modifiers 'emits'"
	return Node('emits_decl', [t[0]])
def d_consumes_decl(t):
	"consumes_decl : cmpt_export_modifiers 'consumes'"
	return Node('consumes_decl', [t[0]])
def d_except_declaration(t):
	"except_declaration : 'exception' IDENTIFIER '{' typed_member_list '}'"
	return Node('except_declaration', [t[3]], t[1])
def d_const_declaration(t, parser):
	"const_declaration : 'const' const_type IDENTIFIER '=' const_expr"
	# Add a constant to the shared state list. 
	parser.shared_state.add_constant(t[2], t[1])
	return Node('const_declaration', [t[1], t[4]], t[2])
def d_const_type(t):
	"""const_type : existing_constr_type
					| template_type"""
	#"""const_type : primitive_type
	return Node('const_type', [t[0]])
def d_const_expr(t):
	"""const_expr : o_const_expr
				| ':' f_const_expr"""
	if t[0]==':':
		return Node('scoped_const_expr', None, result = t[1].result)
	else:
		return Node('const_expr', None, result = t[0].result)
def d_o_const_expr(t):
	"""o_const_expr : STRING_LITERAL
				| boolean_literal
				| CHAR_LITERAL
				| i_const_expr"""
	if isinstance (t[0], str):
		#FIXME: Should make raw strings into Nodes too. Cleaner.
		return Node('o_const_expr', None, result = t[0]) 
	else:
		return Node('o_const_expr', result = t[0].result)
def d_boolean_literal(t):
	"""boolean_literal : 'true'
				| 'false'"""
	result = {'true': True, 'false': False}[t[0]]
	return Node('boolean_literal', None, result = result)
def d_i_const_expr(t):
	"i_const_expr : i_or_expr"
	return ExpressionNode('i_const_expr', t)
def d_i_or_expr(t):
	"""i_or_expr : i_xor_expr 
			| i_or_expr '|' i_xor_expr"""
	return ExpressionNode('i_or_expr', t)
def d_i_xor_expr(t):
	"""i_xor_expr : i_and_expr
			| i_xor_expr '^' i_and_expr"""
	return ExpressionNode('i_xor_expr', t)
def d_i_and_expr(t):
	"""i_and_expr : i_shift_expr
				| i_and_expr '&' i_shift_expr"""
	return ExpressionNode('i_and_expr', t)
def d_i_shift_expr(t):
	"""i_shift_expr : i_add_expr
				| i_shift_expr '>>' i_add_expr 
				| i_shift_expr '<<' i_add_expr"""
	return ExpressionNode('i_shift_expr', t)
def d_i_add_expr(t):
	"""i_add_expr : i_mult_expr
				| i_add_expr '+' i_mult_expr
				| i_add_expr '-' i_mult_expr"""
	return ExpressionNode('i_add_expr', t)
def d_i_mult_expr(t):
	"""i_mult_expr : i_unary_expr
				| i_mult_expr '*' i_unary_expr
				| i_mult_expr '/' i_unary_expr
				| i_mult_expr '%' i_unary_expr"""
	return ExpressionNode('i_mult_expr', t)
def d_i_unary_expr(t):
	"""i_unary_expr : i_unary_operator i_primary_expr 
				| i_primary_expr"""
	return UnaryOperatorNode('i_unary_expr', t)
def d_i_unary_operator(t):
	"""i_unary_operator : '-'
				| '+'
				| '~'"""
	return Node('i_unary_operator', None, t[0])
def d_i_primary_expr(t):
	"""i_primary_expr : INTEGER_LITERAL
				| predefined_constant_identifier
				| ( i_const_expr ) """
#				| IDENTIFIER""" # nfd nov15
	if isinstance (t[0], int):
		return Node('i_primary_expr', None, result = t[0])
	elif t[0]=='(': # ( i_const_expr )
		return Node('i_primary_expr', None, result = t[1].result)
	else:
		return Node('i_primary_expr', None, result = t[0].result)
#	else: # IDENTIFIER
#		return Node('i_primary_expr', None, t[0])
	return Node('TODO')
def d_f_const_expr(t):
	"f_const_expr : f_add_expr"
	return Node('f_const_expr', None, result = t[0].result)
def d_f_add_expr(t):
	"""f_add_expr : f_mult_expr
				| f_add_expr '+' f_mult_expr
				| f_add_expr '-' f_mult_expr"""
	return ExpressionNode('f_add_expr', t)
def d_f_mult_expr(t):
	"""f_mult_expr : f_unary_expr
				| f_mult_expr '*' f_unary_expr
				| f_mult_expr '/' f_unary_expr"""
	return ExpressionNode('f_mult_expr', t)
def d_f_unary_expr(t):
	"""f_unary_expr : f_unary_operator f_primary_expr
				| f_primary_expr"""
	return UnaryOperatorNode(t)
def d_f_unary_operator(t):
	"""f_unary_operator : '-'
				| '+'"""
	return Node('f_unary_operator', None, leaf=t[0])
def d_f_primary_expr(t):
	"""f_primary_expr : FLOAT_LITERAL
				| ( f_const_expr )  """
#				| IDENTIFIER""" # nfd nov 15
	if t[0] == '(':
		return Node('f_primary_expr', result = t[1].result)
	else:
		return Node('f_primary_expr', result=t[0])
def d_allow_indirection(t):
	"""allow_indirection : _allow_indirection?"""
	if not t[0]:
		return Node('allow_indirection', None, '')
	else:
		return Node('allow_indirection', None, t[0][0].leaf)
def d__allow_indirection(t):
	"""_allow_indirection : '*'
				| _allow_indirection '*'"""
	if t[0] == '*':
		return Node('allow_indirection', None, '*')
	else:
		return Node('allow_indirection', None, t[0].leaf + '*')
def d_type_declaration(t):
	"""type_declaration : typedef_declaration
				| constr_type"""
	return Node('type_declaration', [t[0]])

def d_typedef_declaration(t, parser, spec):
	"""typedef_declaration : 'typedef' type_spec allow_indirection IDENTIFIER array_subscripts"""
	#t.parser.shared_state.addTypedef (t[3]) # Add IDENTIFIER to shared state.
	if spec:
		if t[3] is not None:
			parser.shared_state.addTypedef(t[3])
	else:
		return Node('typedef_declaration', [t[1], t[2], t[4]], t[3])
	
def d_type_spec(t):
	"""type_spec : constr_type
				| existing_constr_type
				| template_type"""
	return Node('type_spec', [t[0]])
def d_simple_type_spec(t):
	"""simple_type_spec : existing_constr_type
				| template_type"""
	return Node('simple_type_spec', [t[0]])
def d_existing_constr_type(t):
	"""existing_constr_type : 'struct' ECT_IDENTIFIER
				| 'enum' ECT_IDENTIFIER
				| 'union' ECT_IDENTIFIER
				| ECT_IDENTIFIER"""
	if t[0] in ('struct', 'enum', 'union'):
		return Node('existing_constr_type', [t[0], t[1]])
	else:
		return Node('existing_constr_type', None, t[0])
#def d_primitive_type(t):
#	"primitive_type : _primitive_type"
#	return Node('primitive_type', [t[0].children[0]])
#def d__primitive_type(t):
#	"""_primitive_type : integer_type
#				| floating_pt_type
#				| char_type
#				| boolean_type
#				| any_type
#				| octet_type
#				| object_type
#				| value_base_type"""
#	return Node('_primitive_type', [t[0]])
#def d_integer_type(t):
#	"""integer_type : g_signed_int_type
#				| g_unsigned_int_type"""
#	return Node('integer_type', [t[0]])
# The following are simplified from the original.
#def d_g_signed_int_type(t):struct_type
#	"""g_signed_int_type : SHORT
#				| INT
#				| LONG"""
#	return Node('g_signed_int_type', None, t[0])
#def d_g_unsigned_int_type(t):
#	"""g_unsigned_int_type : UNSIGNED SHORT
#				| UNSIGNED INT
#				| UNSIGNED LONG"""
#	return Node('g_unsigned_int_type', None, t[1])
#def d_floating_pt_type(t):
#	"""floating_pt_type : FLOAT
#				| DOUBLE"""
#	return Node('floating_pt_type', [t[0]])
#def d_char_type(t):
#	"char_type : CHAR"
#	return Node('char_type', None, t[0])
#def d_boolean_type(t):
#	"boolean_type : BOOLEAN"
#	return Node('boolean_type', None, t[0])
#def d_any_type(t):
#	"any_type : ANY"
#	return Node('any_type', None, t[0])
#def d_octet_type(t):
#	"octet_type : OCTET"
#	return Node('octet_type', None, t[0])
#def d_object_type(t):
#	"object_type : OBJECT"
#	return Node('object_type', None, t[0])
#def d_value_base_type(t):
#	"value_base_type : VALUEBASE"
#	return Node('value_base_type', None, t[0])
def d_constr_type(t):
	"constr_type : _constr_type"
	return Node('constr_type', t[0].children )
def d__constr_type(t):
	"""_constr_type : enum_type
				| struct_type"""
	return Node('_constr_type', [t[0]])
def d_struct_type(t, parser):
	"""struct_type : 'struct' IDENTIFIER '{' typed_member_list '}'
				| 'struct' '{' typed_member_list '}'"""

	if (t[1]=='{'): # Unnamed struct
		return Node('struct_type', [t[2]])
	else: # Named struct
		#print 'new registry entry with ', t[1]
		new_type = parser.shared_state.type_registry.make_type('struct', t[1])
		#print 'tree:'
		#t[3].print_tree()
		for child in t[3].children:
			if child.the('type_spec').the('existing_constr_type') != None:
				type_name = child.the('type_spec').the('existing_constr_type').leaf
				#print 'name', type_name
				type_inst = parser.shared_state.type_registry[type_name]
				type_label = child.the('declarator_list').the('declarator').leaf
				#print ' inst ', type_inst, ' label ', type_label
				new_type.add_member(type_inst, type_label)
			elif child.the('type_spec').the('constr_type') != None:
				#print 'child ', child.the('type_spec').the('constr_type')
				if child.the('type_spec').the('constr_type').the('struct_type').leaf != None:
					type_name = child.the('type_spec').the('constr_type').the('struct_type').leaf
					#print 'name', type_name
					type_inst = parser.shared_state.type_registry[type_name]
					type_label = child.the('declarator_list').the('declarator').leaf
					#print ' inst ', type_inst, ' label ', type_label
					new_type.add_member(type_inst, type_label)
			
		new_type.is_predefined = False
		parser.shared_state.type_registry.add_type(new_type)
		return Node('struct_type', [t[3]], t[1])
def d_typed_member_list(t):
	"""typed_member_list : _typed_member_list?"""
	#print 'tree:'
	#t[0][0].print_tree()
	if t[0]:
		return Node('typed_member_list', t[0][0].children)
	else:
		return Node('typed_member_list')
def d__typed_member_list(t):
	"""_typed_member_list : typed_member+"""
	if t[0].type in ('typed_member', 'struct_type'):
		return Node('_typed_member_list', [t[0]])
	else:
		return Node('_typed_member_list', t[0].children + [t[1]])
def d_typed_member(t):
	"""typed_member : type_spec declarator_list ';' """
	return Node('typed_member', [t[0], t[1]])
def d_declarator_list(t):
	"""declarator_list : declarator
				| declarator_list ',' declarator"""
	if t[0].type=='declarator':
		return Node('declarator_list', [t[0]])
	else:
		return Node('declarator_list', t[0].children + [t[2]])
def d_declarator(t):
	"declarator : allow_indirection IDENTIFIER array_subscripts"
	return Node('declarator', [t[0], t[2]], t[1])
def d_array_subscripts(t):
	"""array_subscripts : _array_subscripts?"""
	if t[0]:
		return Node('array_subscripts', t[0][0].children)
	else:
		return Node('array_subscripts')
def d__array_subscripts(t):
	"""_array_subscripts : '[' i_const_expr ']'
				| _array_subscripts '[' i_const_expr ']'"""
	if t[0]=='[':
		return Node('_array_subscripts', [t[1]])
	else:
		return Node('_array_subscripts', t[0].children + [t[2]])
def d_enum_type(t):
	"""enum_type : 'enum' IDENTIFIER '{' enum_member_list '}'
				| 'enum' '{' enum_member_list '}'"""
	if t[1]=='{': # unnamed enum
		return Node('enum_type', [t[2]])
	else:
		return Node('enum_type', [t[3]], t[1])
def d_enum_member_list(t):
	"""enum_member_list : _enum_member_list?"""
	if t[0]:
		return Node('enum_member_list', t[0][0].children)
	else:
		return Node('enum_member_list')
def d__enum_member_list(t):
	"""_enum_member_list : enum_identifier
				| _enum_member_list ',' enum_identifier"""
	if t[0].type=='enum_identifier':
		return Node ('_enum_member_list', [t[0]])
	else:
		return Node ('_enum_member_list', t[0].children + [t[2]])
def d_enum_identifier(t):
	"""enum_identifier : IDENTIFIER
				| IDENTIFIER '=' INTEGER_LITERAL"""
	if t[1]=='=':
		return Node ('enum_identifier', None, (t[0], t[2]))
	else:
		return Node('enum_identifier', None, t[0])
def d_template_type(t):
	"template_type : sequence_type"
	return Node('template_type', [t[0]])
def d_sequence_type(t):
	"""sequence_type : 'sequence' '<' sequence_type '>'
					| simple_type_spec"""
	if t[0] == 'sequence':
		return Node('sequence_type', t[2].children)
	else:
		return Node('sequence_type', [t[0]])
#def d_empty(t):
#	"empty : ' '* "
#	return Node('empty')

# Literals
def d_FLOAT_LITERAL(t):
	r"""FLOAT_LITERAL :  "(({\d}+\.{\d}+){[Ee][+-]?[0-9]+}?{(F|f|L|l)}?)|((\.{\d}+){[Ee][+-]?[0-9]+}?{(F|f|L|l)}?)|(({\d}+){[Ee][+-]?[0-9]+}{(F|f|L|l)}?)" """ # Delicious!
	return float(t[0])

def d_INTEGER_LITERAL(t):
	r'INTEGER_LITERAL : "(0x[0123456789abcdefABCDEF]+)|([0123456789]+)"'
	if t[0].startswith ('0x'):
		return int (t[0][2:], 16)
	elif t[0].startswith ('0'):
		return int (t[0], 8)
	else:
		return int (t[0])

def d_CHAR_LITERAL (t):
	r""" CHAR_LITERAL : "'[\x20-z]'" """
	return t[0]

def d_STRING_LITERAL (t):
	r""" STRING_LITERAL : "\"([\x20-z])*\"" """
	return t[0][1:-1] # Chop the " bits off string literals

# FIXME: id_surrounds may need a few more things in it.
RESERVED= ['any', 'attribute', 'case', 'component', 'const',
	'consumes', 'context', 'default', 'emits', 'enum', 'exception',
	'false', 'import', 'in', 'inout', 'interface',
	'modifier', 'module', 'native', 'object', 'out', 'provides',
	'publishes', 'raises', 'sequence', 'supports',
	'switch', 'true', 'truncatable', 'typedef', 'union', 'unsigned', 'uses',
	'void', 'struct']
id_surrounds = ' \t\n()[].>*~!%^&-+,<?:;'
def d_identifier(t, parser, spec_only, this):
	"""IDENTIFIER: "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	#print "potential_id", potential_id
	if potential_id in RESERVED or parser.shared_state.isTypedef(potential_id):
		#print "reject"
		return Reject
	# Hack: for some reason the parser wants to accept identifiers without
	# whitespace separation?!
	if this.buf[this.start_loc.s - 1] not in id_surrounds:
		# hell no!
		return Reject
	#print "accept"
	return t[0]

def d_ect_identifier(t, parser, spec_only, this):
	"""ECT_IDENTIFIER : "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	if not parser.shared_state.isTypedef(potential_id):
		return Reject
	return t[0]

def d_mod_identifier(t, parser, spec_only, this):
	"""MOD_IDENTIFIER : "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	return t[0]

def d_predefined_constant_identifier(t, parser, spec_only, this):
	"""predefined_constant_identifier : "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	if not parser.shared_state.is_constant(potential_id):
		return Reject
	#constant_result = parser.shared_state.get_constant_ast(potential_id).result
	# Note we don't return the value of the constant in "result": instead we return
	# the name, to force upper levels to insert that name in the code rather
	# than folding.
	return Node('predefined_constant_identifier', None, t[0], result=potential_id)

#def d_decorator_function(t):
#	"""DECORATOR_FUNCTION : 'uuid'"""
#	return t[0]

def syntax_error(loc):
	mn = max(loc.s - 30, 0)
	mx = min(loc.s + 30, len(loc.buf))
	begin = loc.buf[mn:loc.s]
	end = loc.buf[loc.s:mx]
	space = ' '*len(begin)
	print "Syntax error:"
	print begin + '\n' + space + '<--error' + '\n' + space + end

def ambiguity(sym_array):
	for node in sym_array:
		print "start", node.start_loc.s
		print "end", node.end
		print node.buf[node.start_loc.s:node.end], node.symbol
		for child in node.c:
			print "*", child.symbol
	#print sym_array[0].c
	raise Exception('Ambiguity: %s' % (sym_array))


def parse_to_ast(data, shared_state, parse_tables_prefix = None, debug=None):
	"""if parse_tables_prefix is None:
		parse_tables_prefix = './d_parser_mach_gen_idl'
	parser = Parser(file_prefix = parse_tables_prefix)
	parser.shared_state = shared_state
	if debug:
		pdi = 1
	else:
		pdi = 0
	pt = parser.parse(data, ambiguity_fn = ambiguity, syntax_error_fn = syntax_error, print_debug_info=pdi, start_symbol = 'IDLFile')
	if pt is None:
		raise Exception("Syntax error")
	"""
	
	pt = parse_to_pt(data, shared_state, parse_tables_prefix, debug)
	
	if debug:
		print_tree (pt)
		
	# Now generate a 'better' AST
	ast = ast_gen(pt)
	return ast
	
def parse_to_pt(data, shared_state, parse_tables_prefix = None, debug=None):
	if parse_tables_prefix is None:
		parse_tables_prefix = './d_parser_mach_gen_idl'
	parser = Parser(file_prefix = parse_tables_prefix)
	parser.shared_state = shared_state
	if debug:
		pdi = 1
	else:
		pdi = 0
	pt = parser.parse(data, ambiguity_fn = ambiguity, syntax_error_fn = syntax_error, print_debug_info=pdi, start_symbol = 'IDLFile')
	#parser.shared_state.type_registry.print_registry()
	if pt is None:
		raise Exception("Syntax error")
	return pt

def dummy_import_handler(filename):
	print "dummy import", filename

def main():
	state = ParserLexerState()
	state.import_handler = dummy_import_handler
	state.type_registry = {}

	data = file(sys.argv[1]).read()
	parse(data, state, debug=True)
	
if __name__ == '__main__':
	main()

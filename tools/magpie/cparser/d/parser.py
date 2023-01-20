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


"""C / C++ parser for Dparser
"""
import sys
#sys.path.append('tmp/d/python/build/lib.linux-i686-2.3/') # FIXME

from dparser import Parser, Reject
from parser_common import Node, UnfinishedNode, ExpressionNode, ParserLexerState

from debugging import debug_cpp, debug_flags

def debug_tree(node):
	if debug_flags['c++']:
		node.print_tree

def choose_nonempty(some_list):
	# Keep the "None"s to make it obvious when nodes aren't constructed.
	return [item for item in some_list if item is None or item.type != 'empty']

#1.3 basic concepts
def d_translation_unit(t):
	"""
	translation_unit : declaration_seq_opt
	"""
	return Node('translation_unit', [t[0]])

#1.1 keywords

#1.2 lexical conventions
def d_literal(t):
	"""literal : LIT_INT
			| LIT_CHR
			| LIT_REAL
			| LIT_STRING
			| 'true'
			| 'false'
	"""
	if t[0] in ['true', 'false']:
		return Node('literal', None, t[0], result={'true': 1, 'false': 0}[t[0]])
	else:
		return Node('literal', None, t[0].leaf, result=t[0].result)

#nfd: gcc 'compound literals' extension
def d_compound_literal(t):
	"""compound_literal : '(' type_specifier ')' declarator """
	return Node('compound_literal', [t[1], t[3]])

#1.4 expressions
def d_primary_expression(t):
	"""primary_expression : literal
			| 'this'
			| OPER_SCOPE identifier
			| OPER_SCOPE operator_function_id
			| OPER_SCOPE qualified_id
			| compound_literal
			| '(' expression ')'
			| id_expression
	"""
	# Propagate the leaf, if any.
	if t[0] == 'this':
		return Node('primary_expression', None, t[0])
	elif t[0] == '::':
		return Node('scoped_primary_expression', [t[1]], result = t[1].result)
	elif t[0] == '(':
		return Node('primary_expression', [t[1]], result = t[1].result)
	else:
		return Node('primary_expression', [t[0]], result = t[0].result)
	
def d_id_expression(t):
	"""id_expression : unqualified_id
			| qualified_id
	"""
	return Node('id_expression', [t[0]], result=t[0].result)
	
def d_unqualified_id(t):
	"""unqualified_id : identifier
			| operator_function_id
			| conversion_function_id
			| '~' class_name
			| template_id
	"""
	if t[0] == '~':
		return Node('unqualified_id', [t[1]], t[0])
	elif t[0].type == 'identifier':
		return Node('unqualified_id', None, t[0].leaf, result=t[0].leaf)
	else:
		return UnfinishedNode('unqualified_id')
	
def d_qualified_id(t):
	"""qualified_id : nested_name_specifier template_opt unqualified_id"""
	return Node('qualified_id', t)
	
def d_nested_name_specifier(t):
	"""nested_name_specifier : class_or_namespace_name OPER_SCOPE nested_name_specifier_opt"""
	return Node('nested_name_specifier', [t[0], t[2]])
	
def d_class_or_namespace_name(t):
	"""class_or_namespace_name : class_name
			| namespace_name
	"""
	return Node('class_or_namespace_name', [t[0]])
	
def d_postfix_expression(t):
	"""postfix_expression : primary_expression
			| postfix_expression '[' expression ']'
			| postfix_expression '(' expression_list_opt ')'
			| simple_type_specifier '(' expression_list_opt ')'
			| postfix_expression OPER_MEMBER_SELECT template_opt scope_opt id_expression
			| postfix_expression OPER_MEMBER_SELECT_PTR template_opt scope_opt id_expression
			| postfix_expression OPER_MEMBER_SELECT pseudo_destructor_name
			| postfix_expression OPER_MEMBER_SELECT_PTR pseudo_destructor_name
			| postfix_expression '++'
			| postfix_expression '--'
			| 'dynamic_cast' '<' type_id '>' '(' expression ')'
			| 'static_cast' '<' type_id '>' '(' expression ')'
			| 'reinterpret_cast' '<' type_id '>' '(' expression ')'
			| 'const_cast' '<' type_id '>' '(' expression ')'
			| 'typeid' '(' expression ')'
			| 'typeid' '(' type_id ')'
	"""
	# Propagate leaves
	if t[0] in ['dynamic_cast', 'static_cast', 'reinterpret_cast', 'const_cast']:
		return Node('postfix_expression'+t[0], [t[2], t[5]], result = t[5].result)
	elif t[0] == 'typeid':
		return Node('postfix_expression', [t[2]], result = t[2].result)
	elif t[0].type == 'primary_expression':
		return Node('postfix_expression', [t[0]], result = t[0].result)
	elif t[1] == '[':
		return Node('postfix_expression_array_access', [t[0], t[2]], result = t[2].result)
	elif t[1] == '(':
		return Node('postfix_expression_function_call', [t[0], t[2]])
	elif t[1] in ['.', '->']:
		if t[2].type == 'psuedo_destructor_name':
			return Node('postfix_expression_destructor', [t[2]], t[1])
		else:
			return Node('postfix_expression_reference', choose_nonempty(t[2:]))
	elif t[1] == '++':
		return Node('postfix_expression_postinc', [t[0]], result = t[0].result)
	elif t[1] == '--':
		return Node('postfix_expression_postdec', [t[0]], result = t[0].result)
	else:
		raise Exception()
	
def d_expression_list_opt(t):
	"""expression_list_opt : expression_list
			| empty
	"""
	return t[0]
	
def d_expression_list(t):
	"""expression_list : assignment_expression
			| expression_list ',' assignment_expression
	"""
	if len(t) == 3:
		return Node('expression_list', t[0].children + [t[2]])
	else:
		return Node('expression_list', [t[0]])
	
def d_pseudo_destructor_name(t):
	"""pseudo_destructor_name : scope_opt nested_name_specifier_opt identifier OPER_SCOPE '~' identifier 
			| scope_opt nested_name_specifier_opt '~' identifier
	"""
	return UnfinishedNode('pseudo_destructor_name')
	
def d_unary_expression(t, parser):
	"""unary_expression : postfix_expression
			| '++' cast_expression
			| '--' cast_expression
			| unary_operator cast_expression
			| 'sizeof' '(' type_id ')'
			| new_expression
			| delete_expression
	"""
			# FIXME
			#| 'sizeof' unary_expression
	# FIXME FIXME FIXME: We need proper size information here for sizeof.
	if t[0] == '++':
		return Node('unary_preinc_expression', [t[1]], result = t[1].result)
	elif t[0] == '--':
		return Node('unary_predec_expression', [t[1]], result = t[1].result)
	elif t[0] == 'sizeof':
		# This is a sizeof. We want to find the size here and store it.
		# By definition we *can* find the size at this point, so how hard
		# could it be?
		if t[1] == '(':
			subtree_size = parser.ast_walker.get_subtree_size(t[2])
			return Node('unary_expression_sizeof', [t[2]], result = subtree_size)
		else:
			assert 0 # This isn't supported here (ambiguous parser?)
			return Node('unary_expression_sizeof', [t[1]], '0') # FIXME: Here. :)
	else:
		return Node('unary_expression', t, result=t[0].result)
		
	
def d_unary_operator(t):
	"""unary_operator : '*'
			| '&'
			| '+'
			| '-'
			| '!' 
			| '~'
	"""
	return Node('unary_operator', None, t[0])
	
def d_new_expression(t):
	"""new_expression : scope_opt 'new' new_placement_opt new_type_id new_initialiser_opt
			| scope_opt 'new' new_placement_opt '(' type_id ')' new_initialiser_opt
	"""
	return UnfinishedNode('new_expression')
	
def d_new_placement_opt(t):
	"""new_placement_opt : new_placement
			| empty
	"""
	return t[0]

def d_new_placement(t):
	"""new_placement : '(' expression_list ')' """
	return Node('new_placement', [t[0]])
	
def d_new_type_id(t):
	"""new_type_id : type_specifier_seq new_declarator_opt"""
	return Node('new_type_id', [t[0], t[1]])
	
def d_new_declarator_opt(t):
	"""new_declarator_opt : new_declarator
			| empty
	"""
	return t[0]

def d_new_declarator(t):
	"""new_declarator : ptr_operator new_declarator_opt
			| direct_new_declarator
	"""
	return Node('new_declarator', t)
	
def d_direct_new_declarator(t):
	"""direct_new_declarator : '[' expression ']'
			| direct_new_declarator '[' constant_expression ']'
	"""
	if t[0] == '[':
		return Node('direct_new_declarator', [t[1]])
	else:
		return Node('direct_new_declarator', [t[0], t[2]])
	
def d_new_initialiser_opt(t):
	"""new_initialiser_opt : new_initialiser
			| empty
	"""
	return t[0]

def d_new_initialiser(t):
	"""new_initialiser : '(' expression_list_opt ')' """
	return t[1]
	
def d_delete_expression(t):
	"""delete_expression : scope_opt 'delete' cast_expression
			| scope_opt 'delete' '[' ']' cast_expression
	"""
	return UnfinishedNode('delete_expression')
	
def d_cast_expression(t):
	"""cast_expression : unary_expression
			| '(' type_id ')' cast_expression
	"""
	if t[0] == '(':
		return Node('cast_expression', [t[1], t[3]], result = t[3].result)
	else:
		return Node('cast_expression', [t[0]], result = t[0].result)
	
def d_pm_expression(t):
	"""pm_expression : cast_expression
			| pm_expression '.*' cast_expression
			| pm_expression '->*' cast_expression
	"""
	return ExpressionNode('pm_expression', t)
	
def d_multiplicative_expression(t):
	"""multiplicative_expression : pm_expression
			| multiplicative_expression '*' pm_expression
			| multiplicative_expression '/' pm_expression
			| multiplicative_expression '%' pm_expression
	"""
	return ExpressionNode('multiplicative_expression', t)

def d_additive_expression(t):
	"""additive_expression : multiplicative_expression
			| additive_expression '+' multiplicative_expression
			| additive_expression '-' multiplicative_expression
	"""
	return ExpressionNode('additive_expression', t)

def d_shift_expression(t):
	"""shift_expression : additive_expression
			| shift_expression '<<' additive_expression
			| shift_expression '>>' additive_expression
	"""
	return ExpressionNode('shift_expression', t)

def d_relational_expression(t):
	"""relational_expression : shift_expression
			| relational_expression '<' shift_expression
			| relational_expression '>' shift_expression
			| relational_expression '>=' shift_expression
			| relational_expression '<=' shift_expression
	"""
	return ExpressionNode('relational_expression', t)

def d_equality_expression(t):
	"""equality_expression : relational_expression
			| equality_expression '!=' relational_expression
			| equality_expression '==' relational_expression
	"""
	return ExpressionNode('equality_expression', t)

def d_and_expression(t):
	"""and_expression : equality_expression
			| and_expression '&' equality_expression
	"""
	return ExpressionNode('and_expression', t)

def d_exclusive_or_expression(t):
	"""exclusive_or_expression : and_expression
			| exclusive_or_expression '^' and_expression
	"""
	return ExpressionNode('exclusive_or_expression', t)

def d_inclusive_or_expression(t):
	"""inclusive_or_expression : exclusive_or_expression
			| inclusive_or_expression '|' exclusive_or_expression
	"""
	return ExpressionNode('inclusive_or_expression', t)

def d_logical_and_expression(t):
	"""logical_and_expression : inclusive_or_expression
			| logical_and_expression '&&' inclusive_or_expression
	"""
	return ExpressionNode('logical_and_expression', t)

def d_logical_or_expression(t):
	"""logical_or_expression : logical_and_expression
			| logical_or_expression '||' logical_and_expression
	"""
	return ExpressionNode('logical_or_expression', t)

def d_conditional_expression(t):
	"""conditional_expression : logical_or_expression
			| logical_or_expression '?' expression ':' assignment_expression
	"""
	if len(t) == 1:
		return t[0]
	else:
		return Node('conditional_expression', [t[0], t[2], t[4]], '?:')

def d_assignment_expression_opt(t):
	"""assignment_expression_opt : assignment_expression
			| empty
	"""
	return t[0]
	
def d_assignment_expression(t):
	"""assignment_expression : conditional_expression
			| logical_or_expression assignment_operator assignment_expression
			| throw_expression
	"""
	return ExpressionNode('assignment_expression', t)
	#return Node('assignment_expression', t)

def d_assignment_operator(t):
	r"""assignment_operator : OPER_ASSIGNMENT
			| '*='
			| '/='
			| '%='
			| '+='
			| '-='
			| '<<=' | '<?=' | '>=' | '>>=' | '&=' | '^=' | '|=' """
	return Node('assignment_operator', None, t[0])

def d_expression_opt(t):
	"""expression_opt : expression
			| empty
	"""
	return t[0]

def d_expression(t):
	"""expression : assignment_expression
			| expression ',' assignment_expression
	"""
	if len(t) == 3:
		return Node('expression', t[0].children + [t[2]], result=t[2].result)
	else:
		return Node('expression', [t[0]], result=t[0].result)

def d_constant_expression_opt(t):
	"""constant_expression_opt : constant_expression
			| empty
	"""
	return t[0]

def d_constant_expression(t):
	"""constant_expression : conditional_expression"""
	return Node('constant_expression', [t[0]], result=t[0].result)

#1.5 statements
def d_statement(t):
	"""statement : labeled_statement
			| selection_statement
			| expression_statement
			| compound_statement
			| iteration_statement
			| jump_statement
			| declaration_statement
			| try_block
	"""
	return t[0]

def d_labeled_statement(t):
	"""labeled_statement : identifier ':' statement
			| 'case' constant_expression ':' statement
			| 'default' ':' statement
	"""
	if t[0] == 'case':
		return Node('labeled_statement', [t[1], t[3]], 'case')
	elif t[0] == 'default':
		return Node('labeled_statement', [t[2]], 'default')
	else:
		return Node('labeled_statement', [t[2]], t[0].leaf)

def d_expression_statement(t):
	"""expression_statement : expression_opt ';'"""
	return Node('expression_statement', [t[0]])

def d_compound_statement(t):
	"""compound_statement : '{' statement* '}'"""
	return Node('compound_statement', choose_nonempty(t[1]))

def d_selection_statement(t):
	"""selection_statement : 'if' '(' condition ')' statement ('else' statement)?
			| 'switch' '(' condition ')' statement
	"""
	if t[0] == 'if':
		if t[5]:
			return Node('selection_statement', [t[2], t[4], t[5][1]], 'if')
		else:
			return Node('selection_statement', [t[2], t[4]], 'if')
	else:
		return Node('selection_statement', [t[2], t[4]], 'switch')

def d_condition_opt(t):
	"""condition_opt : condition
			| empty
	"""
	return t[0]

def d_condition(t):
	"""condition : expression
			| type_specifier_seq declarator OPER_ASSIGNMENT assignment_expression
	"""
	if len(t) == 1:
		return Node('condition', [t[0]])
	else:
		return Node('condition', [t[0], t[1], t[3]], 'l,l,=,r')

def d_iteration_statement(t):
	"""iteration_statement : 'while' '(' condition ')' statement
			| 'do' statement 'while' '(' expression ')' ';'
			| 'for' '(' for_init_statement condition_opt ';' expression_opt ')' statement
	"""
	if t[0] == 'while':
		return Node('iteration_statement', [t[2], t[4]], 'while') # and begin a while loop :)
	elif t[0] == 'do':
		return Node('iteration_statement', [t[1], t[4]], 'dowhile')
	elif t[0] == 'for':
		return Node('iteration_statement', [t[2], t[3], t[5], t[7]], 'for')
	else:
		raise Exception()

def d_for_init_statement(t):
	"""for_init_statement : expression_statement
			| simple_declaration
	"""
	return Node('for_init_statement', [t[0]])

def d_jump_statement(t):
	"""jump_statement : 'break' ';'
			| 'continue' ';'
			| 'return' expression_opt ';'
			| 'goto' identifier ';'
	"""
	if t[0] == 'break':
		return Node('jump_statement', None, 'break')
	elif t[0] == 'continue':
		return Node('jump_statement', None, 'continue')
	elif t[0] == 'return':
		return Node('jump_statement', [t[1]], 'return')
	elif t[0] == 'goto':
		return Node('jump_statement', [t[1]], 'goto')

def d_declaration_statement(t):
	"""declaration_statement : block_declaration"""
	return Node('declaration_statement', [t[0]])

#1.6 declarations

def d_declaration_seq_opt(t):
	"""declaration_seq_opt : declaration_seq
			| empty """
	return Node('declaration_seq', t[0].children)
	
def d_declaration_seq(t):
	"""declaration_seq : declaration 
			| declaration_seq declaration
	"""
	if len(t) == 2:
		return Node('declaration_seq', t[0].children + [t[1]])
	else:
		return Node('declaration_seq', [t[0]])

def d_declaration(t):
	"""declaration : block_declaration
			| function_definition
			| template_declaration
			| explicit_instantiation
			| explicit_specialisation
			| linkage_specification
			| namespace_definition
	"""
	return Node('declaration', [t[0]])

def d_block_declaration(t):
	"""block_declaration : simple_declaration
			| asm_definition
			| namespace_alias_definition
			| using_declaration
			| using_directive
	"""
	return Node('block_declaration', [t[0]])

def d_simple_declaration(t, parser, spec):
	"""simple_declaration : decl_specifier_seq_opt init_declarator_list_opt ';'"""
	if spec:
		if t[0] is not None and t[1] is not None:
			debug_cpp("SIMPLE DECL! Spec. %s" % (t))
			result = Node('simple_declaration', choose_nonempty([t[0], t[1]]))
			parser.symbols.maybe_add_typedef(result)
		debug_cpp("SIMPLE DECL! Some nodes null. %s" % (t))
	else:
		debug_cpp("SIMPLE DECL! Nonspec. %s" %(t))
		result = Node('simple_declaration', choose_nonempty([t[0], t[1]]))
		parser.ast_walker.maybe_add_type_from_simple_declaration(result)
		return result

def d_decl_specifier_seq_opt (t):
	"""decl_specifier_seq_opt : decl_specifier_seq 
			| empty
	"""
	return t[0]

def d_decl_specifier_seq(t):
	"""decl_specifier_seq : decl_specifier_seq decl_specifier
			| decl_specifier"""
	if len(t) == 2:
		return Node('decl_specifier_seq', t[0].children + [t[1]])
	else:
		return Node('decl_specifier_seq', [t[0]])

def d_decl_specifier(t):
	"""decl_specifier : storage_class_specifier
			| type_specifier
			| function_specifier
			| attribute_specifier
			| 'friend' 
			| 'typedef'
	"""
	if t[0] in ['friend', 'typedef']:
		return Node('decl_specifier', None, t[0])
	else:
		return Node('decl_specifier', [t[0]])

def d_storage_class_specifier(t):
	"""storage_class_specifier : 'auto'
			| 'register'
			| 'static'
			| 'extern'
			| 'mutable'
	"""
	return Node('storage_class_specifier', None, t[0])

def d_attribute_specifier_opt(t):
	"""attribute_specifier_opt : attribute_specifier
			| empty
	"""
	return t[0]

def d_attribute_specifier(t):
	"""attribute_specifier : '__attribute__' '((' attribute_specifier_list '))' """
	return Node('attribute_specifier', [t[2]])

def d_attribute_specifier_list(t):
	"""attribute_specifier_list : attribute_specifier_item ',' attribute_specifier_list
		| attribute_specifier_item
		| empty
	"""
	if len(t) == 3:
		return Node('attribute_specifier_list', [t[0]] + t[2].children)
	else:
		return Node('attribute_specifier_list', [t[0]])

def d_attribute_specifier_item(t):
	"""attribute_specifier_item : '__mode__' '(' identifier ')'
		| 'const'
	"""
	return Node('attribute_specifier_item', None, t)

def d_function_specifier(t):
	"""function_specifier : 'inline'
			| 'virtual'
			| 'explicit'
			| '__inline'
	"""
	return Node('function_specifier', None, t[0])

def d_type_specifier(t):
	"""type_specifier : simple_type_specifier
			| class_specifier
			| enum_specifier
			| elaborated_type_specifier
			| cv_qualifier
	"""
	return Node('type_specifier', [t[0]], result=t[0].result)

def d_simple_type_specifier(t):
	"""simple_type_specifier : scope_opt nested_name_specifier_opt TYPE_ID
			| 'char'
			| 'wchar_t'
			| 'bool'
			| 'short'
			| 'int'
			| 'long'
			| '__int64'
			| 'signed'
			| 'unsigned'
			| 'float'
			| 'double'
			| 'void'
	"""
	if len(t) == 1:
		return Node('simple_type_specifier', None, t[0])
	else:
		return Node('simple_type_specifier', [t[0], t[1], t[2]], t[2].leaf, result=t[2].result)

def d_elaborated_type_specifier(t):
	"""elaborated_type_specifier : class_key scope_opt nested_name_specifier_opt identifier
			| 'enum' scope_opt nested_name_specifier_opt TYPE_ID
			| identifier scope_opt nested_name_specifier TYPE_ID
			| identifier scope_opt nested_name_specifier TYPE_ID '<' template_argument_list '>'
	"""
	# NOTE: We use "identfier" rather than TYPE_ID in the first definition because
	# this may be 
	if t[0] == 'enum':
		return Node('elaborated_type_specifier_enum', choose_nonempty([t[1], t[2], t[3]]), None,
			result = t[3].result)
	elif t[-1] == '>':
		return Node('elaborated_type_specifier_template', [t[0], t[1], t[2], t[3], t[5]],
			result = t[3].result)
	else:
		return Node('elaborated_type_specifier', t)

def d_enum_specifier(t):
	"enum_specifier : 'enum' identifier_opt '{' enumerator_list_opt '}'"
	return Node('enum_specifier', t[3].children, t[1])

def d_enumerator_list_opt(t):
	"""enumerator_list_opt : enumerator_list
			| empty
	"""
	return t[0]

def d_enumerator_list(t):
	"""enumerator_list : enumerator_definition 
			| enumerator_list ',' enumerator_definition
	"""
	if len(t) == 3:
		return Node('enumerator_list', t[0].children + [t[2]])
	else:
		return Node('enumerator_list', [t[0]])

def d_enumerator_definition(t):
	"""enumerator_definition : enumerator
			| enumerator OPER_ASSIGNMENT constant_expression
	"""
	if len(t) == 3:
		return Node('enumerator_definition', [t[0], t[2]], None)
	else:
		return Node('enumerator_definition', [t[0]])

def d_enumerator(t):
	"enumerator : identifier"
	return t[0]

def d_namespace_name(t):
	"""namespace_name : original_namespace_name
			| namespace_alias
	"""
	return Node('namespace_name', [t[0]])

def d_original_namespace_name(t):
	"""original_namespace_name : identifier """
	return t[0]

def d_namespace_definition(t):
	"""namespace_definition : named_namespace_definition
			| unnamed_namespace_definition
	"""
	return t[0]

def d_named_namespace_definition(t):
	"""named_namespace_definition : original_namespace_definition
			| extension_namespace_definition
	"""
	return t[0]

def d_original_namespace_definition(t):
	"""original_namespace_definition : 'namespace' identifier '{' namespace_body '}'"""
	return Node('original_namespace_definition', [t[1], t[3]])

def d_extension_namespace_definition(t):
	"""extension_namespace_definition : 'namespace' original_namespace_name '{' namespace_body '}'"""
	return Node('extension_namespace_definition', [t[1], t[3]])

def d_unnamed_namespace_definition(t):
	"""unnamed_namespace_definition : 'namespace' '{' namespace_body '}' """
	return Node('unnamed_namespace_definition', [t[2]])

def d_namespace_body(t):
	"""namespace_body : declaration_seq_opt"""
	return t[0]

def d_namespace_alias(t):
	"""namespace_alias : identifier"""
	return t[0]

def d_namespace_alias_definition(t):
	"""namespace_alias_definition : 'namespace' identifier OPER_ASSIGNMENT qualified_namespace_specifier ';'"""
	return Node('namespace_alias_definition', [t[1], t[3]])

def d_qualified_namespace_specifier(t):
	"""qualified_namespace_specifier : scope_opt nested_name_specifier_opt namespace_name"""
	return Node('qualified_namespace_specifier', [t[0], t[1], t[2]])

def d_using_declaration(t):
	"""using_declaration : 'using' identifier_opt scope_opt nested_name_specifier unqualified_id ';'
			| 'using' OPER_SCOPE unqualified_id ';'
	"""
	if t[1] == '::':
		return Node('using_declaration', [t[2]])
	else:
		return Node('using_declaration', [t[1], t[2], t[3], t[4]])

def d_using_directive(t):
	"""using_directive : 'using' 'namespace' scope_opt nested_name_specifier_opt namespace_name ';' """
	return Node('using_directive', [t[2], t[3], t[4]])

def d_asm_definition(t):
	"""asm_definition : 'asm' asm_volatile_declaration '(' LIT_STRING gcc_asm_constraints ')' ';'
			| '__asm__' asm_volatile_declaration '(' LIT_STRING gcc_asm_constraints ')' ';'"""
	return UnfinishedNode("asm_definition")

def d_asm_volatile_declaration(t):
	"""asm_volatile_declaration : 'volatile' | '__volatile__'
			| empty
	"""

def d_gcc_asm_constraints(t):
	"""gcc_asm_constraints : ':' gcc_asm_constraint (':' gcc_asm_constraint (':' gcc_asm_constraint)?)?
			| empty
	"""

def d_gcc_asm_constraint(t):
	"""gcc_asm_constraint : LIT_STRING '(' identifier ')'
			| LIT_STRING '(' identifier ')' ',' gcc_asm_constraint
			| empty
	"""

def d_linkage_specification(t):
	"""linkage_specification : 'extern' LIT_STRING '{' declaration_seq_opt '}'
			| 'extern' LIT_STRING declaration
	"""

# 1.7 declarators
def d_init_declarator_list_opt(t):
	"""init_declarator_list_opt : init_declarator_list
			| empty
	"""
	return t[0]
	
def d_init_declarator_list(t):
	"""init_declarator_list : init_declarator
			| init_declarator_list ',' init_declarator
	"""
	if len(t) == 3:
		return Node('init_declarator_list', t[0].children + [t[2]])
	else:
		return Node('init_declarator_list', [t[0]])
	
def d_init_declarator(t):
	"""init_declarator : declarator initialiser_opt"""
	return Node('init_declarator', choose_nonempty(t))
	
def d_declarator(t):
	"""declarator : direct_declarator
			| ptr_operator declarator
	"""
	return Node('declarator', t)
	
def d_direct_declarator(t):
	"""direct_declarator : declarator_id
			| union_discriminator expression
			| expression
			| direct_declarator '(' parameter_declaration_clause ')' attribute_specifier_opt cv_qualifier_seq_opt exception_specification_opt
			| direct_declarator '[' constant_expression_opt ']'
			| '{' declarator '}'
	"""
	if t[0] == '{':
		return t[1]
	elif t[0].type == 'declarator_id':
		return Node('direct_declarator', [t[0]])
	elif t[0].type == 'union_discriminator':
		return Node('direct_declarator_union_discriminated', [t[0], t[1]])
	elif t[0].type == 'expression':
		return Node('direct_declarator_non_constant', [t[0]])
	elif t[1] == '(':
		return Node('direct_declarator', choose_nonempty([t[0], t[2], t[4], t[5]]))
	elif t[1] == '[':
		return Node('direct_declarator', choose_nonempty([t[0], t[2]]))
	
def d_ptr_operator(t):
	"""ptr_operator : '*' cv_qualifier_seq_opt
			| '&'
			| scope_opt nested_name_specifier '*' cv_qualifier_seq_opt
	"""
	if t[0] == '*':
		return Node('ptr_operator', choose_nonempty([t[1]]), t[0])
	elif t[0] == '&':
		return Node('ptr_operator', None, t[0])
	else:
		return Node('ptr_operator', choose_nonempty([t[0], t[1], t[3]]), t[2])
	
def d_cv_qualifier_seq_opt(t):
	"""cv_qualifier_seq_opt : cv_qualifier_seq
			| empty
	"""
	return t[0]
	
def d_cv_qualifier_seq(t):
	"""cv_qualifier_seq : cv_qualifier cv_qualifier_seq
			| cv_qualifier
	"""
	if len(t) == 2:
		return Node('cv_qualifier_seq', [t[0]] + t[1].children)
	else:
		return Node('cv_qualifier_seq', [t[0]])
	
def d_cv_qualifier(t):
	"""cv_qualifier : 'const'
			| 'volatile'
	"""
	return Node('cv_qualifier', None, t[0])
	
def d_declarator_id(t):
	"""declarator_id : scope_opt id_expression
			| scope_opt nested_name_specifier_opt identifier
	"""
	if len(t) == 2:
		return Node('declarator_id', choose_nonempty([t[0], t[1]]), result=t[1].result)
	else:
		return Node('declarator_id', choose_nonempty([t[0], t[1], t[2]]), result=t[2].result)

# nfd: gcc extension (I think) for determining which bit of a union you're setting
def d_union_discriminator(t):
	"""union_discriminator : identifier ':' """
	return UnfinishedNode('union_discriminator')

def d_type_id(t):
	"""type_id : type_specifier_seq abstract_declarator_opt
	"""
	# FIXME: 'result' may not be correct WRT pointers (take abstract_declarator_opt into account)
	return Node('type_id', t, result = t[0].result)

def d_type_specifier_seq(t):
	"""type_specifier_seq : type_specifier type_specifier_seq
			| type_specifier
	"""
	# FIXME: Is this correct?
	if len(t) == 1:
		return Node('type_specifier_seq', t, result=t[0].result)
	else:
		return Node('type_specifier_seq', t, result = None)

def d_abstract_declarator_opt(t):
	"""abstract_declarator_opt : abstract_declarator
			| empty"""
	return t[0]

def d_abstract_declarator(t):
	"""abstract_declarator : ptr_operator abstract_declarator_opt
			| direct_abstract_declarator
	"""
	return Node('abstract_declarator', t)

def d_direct_abstract_declarator(t):
	"""direct_abstract_declarator : direct_abstract_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
			| '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
			| direct_abstract_declarator '[' constant_expression_opt ']'
			| '[' constant_expression_opt ']'
			| '(' abstract_declarator ')'
	"""
	return UnfinishedNode('direct_abstract_declarator')

def d_parameter_declaration_clause(t):
	"""parameter_declaration_clause : parameter_declaration_list_opt ellipsis_opt
			| parameter_declaration_list ',' '...'
	"""
	if t[1] == ',':
		return Node('parameter_declaration_clause', t[0].children, '...')
	elif t[1] == '...':
		return Node('parameter_declaration_clause', t[0].children, t[1])
	else:
		return Node('parameter_declaration_clause', [t[0]])

def d_parameter_declaration_list_opt(t):
	"""parameter_declaration_list_opt : parameter_declaration_list
			| empty
	"""
	return t[0]

def d_parameter_declaration_list(t):
	"""parameter_declaration_list : parameter_declaration
			| parameter_declaration_list ',' parameter_declaration
	"""
	if len(t) == 3:
		return Node('parameter_declaration_list', t[0].children + [t[2]])
	else:
		return Node('parameter_declaration_list', [t[0]])

def d_parameter_declaration(t):
	"""parameter_declaration : decl_specifier_seq declarator
			| decl_specifier_seq declarator OPER_ASSIGNMENT assignment_expression
			| decl_specifier_seq abstract_declarator_opt
			| decl_specifier_seq abstract_declarator_opt OPER_ASSIGNMENT assignment_expression
	"""
	if '=' in t:
		return Node('parameter_declaration', choose_nonempty([t[0], t[1], t[3]]))
	else:
		return Node('parameter_declaration', choose_nonempty(t))

def d_function_definition(t):
	"""function_definition : decl_specifier_seq_opt declarator ctor_initialiser_opt compound_statement
			| decl_specifier_seq_opt declarator function_try_block
	"""
	return Node('function_definition', choose_nonempty(t))

def d_initialiser_opt(t):
	"""initialiser_opt : initialiser
			| empty
	"""
	return t[0]

def d_initialiser(t):
	"""initialiser : OPER_ASSIGNMENT initialiser_clause
			| '(' expression_list ')'
	"""
	if t[0] == '=':
		return Node('initialiser', [t[1]], '=', result=t[1].result)
	else:
		return Node('initialiser', [t[1]], result=t[1].result)

def d_initialiser_clause(t):
	"""initialiser_clause : assignment_expression
			| '{' initialiser_list comma_opt '}'
			| '{' '}'
	"""
	if t[0] == '{' and t[1] == '}':
		return Node('initialiser_clause')
	elif t[0] == '{':
		return Node('initialiser_clause', [t[1]], result=t[1].result)
	else:
		return Node('initialiser_clause', [t[0]], result=t[0].result)

def d_initialiser_list(t):
	"""initialiser_list : initialiser_clause
			| initialiser_list ',' initialiser_clause
	"""

#1.8 classes

def d_class_name(t):
	"""class_name : identifier 
			| template_id
	"""
	return UnfinishedNode('class_name')

def d_class_specifier(t):
	"""class_specifier : class_head '{' member_specification_opt '}' """
	return Node('class_specifier', [t[0], t[2]])

def d_class_head(t):
	"""class_head : class_key identifier_opt base_clause_opt
			| class_key nested_name_specifier identifier base_clause_opt
	"""
	return Node('class_head', t)

def d_class_key(t):
	"""class_key : 'class'
			| 'struct'
			| 'union'
	"""
	return Node('class_key', None, t[0])

def d_member_specification_opt(t):
	"""member_specification_opt : member_specification
			| empty
	"""
	return t[0]

def d_member_specification(t):
	"""member_specification : member_declaration member_specification_opt
			| access_specifier ':' member_specification_opt
	"""
	if t[1] == ':':
		return Node('member_specification', [t[0], t[2]])
	else:
		return Node('member_specification', [t[0]] + t[1].children)

def d_member_declaration(t):
	"""member_declaration : decl_specifier_seq_opt member_declarator_list_opt ';'
			| function_definition semi_opt
			| qualified_id ';'
			| using_declaration
			| template_declaration
	"""
	if t[0].type in ['template_declaration', 'using_declaration', 'qualified_id', 'function_definition']:
		return Node('member_declaration', [t[0]])
	else:
		return Node('member_declaration_decl_list', [t[0], t[1]])
				
	
def d_member_declarator_list_opt (t):
	"""member_declarator_list_opt : member_declarator_list 
			| empty
	"""
	return t[0]

def d_member_declarator_list(t):
	"""member_declarator_list : member_declarator
			| member_declarator_list ',' member_declarator
	"""
	if len(t) == 3:
		return Node('member_declarator_list', t[0].children + [t[2]])
	else:
		return Node('member_declarator_list', [t[0]])

def d_member_declarator(t):
	"""member_declarator : declarator
			| declarator OPER_ASSIGNMENT '0'
			| declarator constant_initialiser
			| identifier_opt ':' constant_expression
	"""
	if t[0].type == 'declarator':
		return t[0]
	elif t[1] == '=' and t[2] == '0':
		return Node('declarator', None, '=0')
	elif t[1] == ':':
		return Node('bitfield_declarator', [t[0], t[2]], 'bitfield')
	elif t[1].type == 'constant_initialiser':
		return Node('declarator', [t[1]], 'initialised declarator')
	else:
		raise Exception()

def d_constant_initialiser(t):
	"""constant_initialiser : OPER_ASSIGNMENT constant_expression"""
	return Node('constant_initialiser', [t[1]])

#1.9 derived classes

def d_base_clause_opt (t):
	"""base_clause_opt : base_clause
			| empty
	"""
	return t[0]

def d_base_clause(t):
	"""base_clause : ':' base_specifier_list"""

def d_base_specifier_list(t):
	"""base_specifier_list : base_specifier 
			| base_specifier_list ',' base_specifier
	"""

def d_base_specifier(t):
	"""base_specifier : scope_opt nested_name_specifier_opt class_name
			| 'virtual' access_specifier_opt scope_opt nested_name_specifier_opt class_name
			| access_specifier virtual_opt scope_opt nested_name_specifier_opt class_name
	"""

def d_access_specifier_opt(t):
	"""access_specifier_opt : access_specifier
			| empty
	"""

def d_access_specifier(t):
	"""access_specifier : 'private'
			| 'protected'
			| 'public'
	"""

#1.10 special member functions

def d_conversion_function_id(t):
	"""conversion_function_id : 'operator' conversion_type_id"""
	return Node('conversion_function_id', [t[1]], 'operator')

def d_conversion_type_id(t):
	"""conversion_type_id : type_specifier_seq conversion_declarator_opt"""

def d_conversion_declarator_opt(t):
	"""conversion_declarator_opt : conversion_declarator
			| empty
	"""

def d_conversion_declarator(t):
	"""conversion_declarator : ptr_operator conversion_declarator_opt"""
	
def d_ctor_initialiser_opt (t):
	"""ctor_initialiser_opt : ctor_initialiser
			| empty
	"""
	return t[0]

def d_ctor_initialiser(t):
	"""ctor_initialiser : ':' mem_initialiser_list"""

def d_mem_initialiser_list(t):
	"""mem_initialiser_list : mem_initialiser
			| mem_initialiser ',' mem_initialiser_list
	"""

def d_mem_initialiser(t):
	"""mem_initialiser : mem_initialiser_id '(' expression_list_opt ')'"""

def d_mem_initialiser_id(t):
	"""mem_initialiser_id : scope_opt nested_name_specifier_opt class_name
			| identifier
	"""

# 1.11 overloading

def d_operator_function_id(t):
	"""operator_function_id : 'operator' overloading_operator"""
	return Node('operator_function_id', [t[0]], 'operator')

def d_overloading_operator(t):
	r"""overloading_operator : 'new'
			| 'delete'
			| 'new[]'
			| 'delete[]'
			| '+'
			| '-'
			| '*'
			| '/'
			| '%'
			| '^'
			| '&'
			| '|'
			| '~'
			| '~'
			| OPER_ASSIGNMENT
			| '<'
			| '>'
			| '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '<?=' | '>?' | '>>=' | '&=' | '^=' | '|='
			| '<<'
			| '>>'
			| '&&'
			| '||'
			| '++'
			| '--'
			| ','
			| '->*'
			| '->'
			| '()'
			| '[]'
	"""
	return Node('overloading_operator', t[0])

# 1.12 Templates
def d_template_declaration(t):
	"""template_declaration : export_opt 'template' '<' template_parameter_list '>' declaration"""

def d_template_parameter_list(t):
	"""template_parameter_list : template_parameter
			| template_parameter_list ',' template_parameter
	"""

def d_template_parameter(t):
	"""template_parameter : type_parameter
			| parameter_declaration
	"""

def d_type_parameter(t):
	"""type_parameter : 'class' identifier_opt
			| 'class' identifier_opt OPER_ASSIGNMENT type_id
			| identifier identifier_opt
			| identifier identifier_opt OPER_ASSIGNMENT type_id
			| 'template' '<' template_parameter_list '>' 'class' identifier_opt
			| 'template' '<' template_parameter_list '>' 'class' identifier_opt OPER_ASSIGNMENT template_name
	"""

def d_template_id(t):
	"""template_id : template_name '<' template_argument_list '>' """
	return UnfinishedNode('template_id')

def d_template_name(t):
	"""template_name : identifier"""

def d_template_argument_list(t):
	"""template_argument_list : template_argument
			| template_argument_list ',' template_argument
	"""

def d_template_argument(t):
	"""template_argument : assignment_expression
			| type_id
			| template_name
	"""

def d_explicit_instantiation(t):
	"""explicit_instantiation : template_declaration """

def d_explicit_specialisation(t):
	"""explicit_specialisation : 'template' '<' '>' declaration """

# 1.13 exception handling

def d_try_block(t):
	"""try_block : 'try' compound_statement handler_seq"""

def d_function_try_block(t):
	"""function_try_block : 'try' ctor_initialiser_opt compound_statement handler_seq"""

def d_handler_seq_opt (t):
	"""handler_seq_opt : handler_seq
			| empty
	"""
	
def d_handler_seq(t):
	"""handler_seq : handler handler_seq_opt"""

def d_handler(t):
	"""handler : 'catch' '(' exception_declaration ')' compound_statement"""

def d_exception_declaration(t):
	"""exception_declaration : type_specifier_seq declarator
			| type_specifier_seq abstract_declarator
			| type_specifier_seq
			| '...'
	"""

def d_throw_expression(t):
	"""throw_expression : 'throw' assignment_expression_opt"""

def d_exception_specification_opt(t):
	"""exception_specification_opt : exception_specification
			| empty
	"""
	return t[0]

def d_exception_specification(t):
	"""exception_specification : 'throw' '(' type_id_list_opt ')'"""

def d_type_id_list_opt(t):
	"""type_id_list_opt : type_id_list
			| empty
	"""

def d_type_id_list(t):
	"""type_id_list : type_id
			| type_id_list ',' type_id
	"""

def d_nested_name_specifier_opt(t):
	"""nested_name_specifier_opt : nested_name_specifier
			| empty
	"""
	if t[0].type == 'empty':
		return Node('nested_name_specifier_opt', None)
	else:
		return Node('nested_name_specifier_opt', t[0].children)

# nfd - opts for tokens
def d_template_opt(t):
	"""template_opt : 'template'
			| empty
	"""
	if t[0] == 'template':
		return Node('template_opt', None, 'template')
	return t[0]
	
def d_scope_opt(t):
	"""scope_opt : OPER_SCOPE
			| empty
	"""
	if t[0] == '::':
		return Node('scope_opt', None, '::')
	else:
		return Node('scope_opt', None)

def d_semi_opt(t):
	"""semi_opt : ';' 
			| empty
	"""

def d_ellipsis_opt(t):
	"""ellipsis_opt : '...'
			| empty
	"""
	return t[0]

def d_comma_opt(t):
	"""comma_opt : ','
			| empty
	"""

def d_virtual_opt(t):
	"""virtual_opt : 'virtual'
			| empty
	"""

def d_export_opt(t):
	"""export_opt : 'export' 
			| empty
	"""

def d_identifier_opt(t):
	"""identifier_opt : identifier 
			| empty
	"""
	return t[0]

RESERVED = ['union', 'return', 'if', 'while', 'for', 'do', 'struct', 'typedef', '__asm__', 'asm', 'sizeof']
# FIXME: id_surrounds may need a few more things in it.
id_surrounds = ' \t\n()[].>*~!%^&-+,<?:;'

def d_identifier(t, parser, spec_only, this):
	"""identifier : "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	if potential_id in RESERVED or parser.symbols.is_typedef(potential_id):
		return Reject
	# Hack: for some reason the parser wants to accept identifiers without
	# whitespace separation?!
	if this.buf[this.start_loc.s - 1] not in id_surrounds:
		# Hell no!
		return Reject
	return Node('identifier', None, t[0])

def d_empty(t):
	"""empty : ' '* """
	return Node('empty')

def d_TYPE_ID(t, parser, spec_only, this):
	"""TYPE_ID : "[A-Za-z_][A-Za-z0-9_]*" """
	potential_id = this.buf[this.start_loc.s:this.end]
	if not parser.symbols.is_typedef(potential_id):
		return Reject
	type_name = t[0]
	# We can't use the type registry here. The registry only gets types
	# on a final pass, but we consider type IDs on a speculative parse.
	#size_in_bytes = parser.type_registry.size_in_bits_cls(type_name) / 8 
	#return Node('TYPE_ID', None, t[0], result = size_in_bytes)
	return Node('TYPE_ID', None, t[0])

# Identifiers
def strip_ul(token):
	while token[-1] in 'uUlL':
		token = token[:-1]
	return token

def d_DEC_INT(t):
	"""DEC_INT : "[1-9][0-9]*[uU]?[lL]?" """
	result = int(strip_ul(t[0]))
	return Node('DEC_INT', None, result, result)

def d_HEX_INT(t):
	"""HEX_INT : "(0x|0X)[0-9a-fA-F]+[uU]?[lL]?" """
	result = int(strip_ul(t[0]), 16)
	return Node('HEX_INT', None, result, result)

def d_OCT_INT(t):
	"""OCT_INT : "0[0-7]*[uU]?[lL]?" """
	result = int(strip_ul(t[0]), 8)
	return Node('OCT_INT', None, result, result)

def d_LIT_INT(t):
	'LIT_INT : DEC_INT | HEX_INT | OCT_INT'
	return Node('LIT_INT', None, t[0].leaf, result = t[0].result)

def d_LIT_CHR(t):
	"""LIT_CHR : "'[A-Za-z0-9]'" """

def d_LIT_REAL(t):
	r"""LIT_REAL : "(({\d}+\.{\d}+){[Ee][+-]?[0-9]+}?{(F|f|L|l)}?)|((\.{\d}+){[Ee][+-]?[0-9]+}?{(F|f|L|l)}?)|(({\d}+){[Ee][+-]?[0-9]+}{(F|f|L|l)}?)" """ # Delicious!

def d_one_string(t):
	r"""one_string: "\"([^\"\\]|\\[^])*\"" """
	return t[0][1:-1]

def d_LIT_STRING(t):
	r"""LIT_STRING : one_string+ """
	return Node('LIT_STRING', None, ''.join(t[0]))

# Operators
def d_oper_scope(t):
	r"""OPER_SCOPE : '::'"""
	return t[0]

def d_oper_member_select(t):
	r"""OPER_MEMBER_SELECT : '.'"""
	return '.'

def d_oper_member_select_ptr(t):
	r"""OPER_MEMBER_SELECT_PTR : '->'"""
	return t[0]

def d_oper_assignment(t):
	r"""OPER_ASSIGNMENT : '='"""
	return t[0]

def syntax_error(loc):
	mn = max(loc.s - 30, 0)
	mx = min(loc.s + 30, len(loc.buf))
	begin = loc.buf[mn:loc.s].replace('\n', '.')
	end = loc.buf[loc.s:mx].replace('\n', '.')
	space = ' '*len(begin)
	print "Syntax error:"
	print begin + end
	print space + "^-- error"

def ambiguity(sym_array):
	for node in sym_array:
		print "start", node.start_loc.s
		print "end", node.end
		print node.buf[node.start_loc.s:node.end], node.symbol
		for child in node.c:
			print "*", child.symbol
	#print sym_array[0].c
	raise Exception('Ambiguity: %s' % (sym_array))

class Symbols:
	def __init__(self):
		self.current_scope_identifiers = {} # FIXME: scoping
		
	def find_identifier(self, simple_decl):
		# FIXME: This might not be a good way to deal with indirection.
		current = simple_decl.the('init_declarator_list').the('init_declarator')
		while current.the('direct_declarator') is None:
			current = current.the('declarator')
		return current.the('direct_declarator').the('declarator_id').the('identifier').leaf
		
	def maybe_add_typedef(self, simple_decl):
		assert simple_decl.type == 'simple_declaration'
		debug_cpp("maybe add typedef for ...")
		debug_tree(simple_decl)
		declspecs = simple_decl.the('decl_specifier_seq')
		if not declspecs:
			#print "no declspecs"
			return False
		if len(declspecs.children) == 0 or declspecs.children[0].leaf != 'typedef':
			#print 'not a typedef'
			return False
		# FIXME: Scoping!
		#simple_decl.print_tree()
		identifier = self.find_identifier(simple_decl)#simple_decl.the('init_declarator_list').the('init_declarator').the('declarator').the('direct_declarator').the('declarator_id').the('identifier').leaf
		debug_cpp ("adding typedef '%s'" % (identifier))
		self.current_scope_identifiers[identifier] = 1

	def is_typedef(self, t):
		#print "nfd: is typedef?", t, t in self.current_scope_identifiers
		return t in self.current_scope_identifiers

def parse(data, ast_walker, type_registry, parse_tables_prefix = None):
	if parse_tables_prefix is None:
		parse_tables_prefix = './d_parser_mach_gen'
	parser = Parser(file_prefix = parse_tables_prefix, make_grammar_file=1)
	# FIXME: We should be using a proper type registry instead of this Symbols stuff.
	# FIXME: So Symbols should be obsoleted.
	parser.symbols = Symbols()
	parser.ast_walker = ast_walker
	parser.type_registry = type_registry
	ast = parser.parse(data, ambiguity_fn = ambiguity, syntax_error_fn = syntax_error, print_debug_info=0, start_symbol = 'translation_unit')
	if ast is None:
		raise Exception("Syntax error")
	debug_tree (ast)
	return ast

if __name__ == '__main__':
	data = file(argv[1]).read()
	parse(data)


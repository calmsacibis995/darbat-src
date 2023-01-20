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


from debugging import debug_castwalker, debug_flags
from magpietypes.magpietype import UnknownMembers
from evaluator import evaluate

def debug_tree(ast):
	if debug_flags['castwalker']:
		ast.print_tree()

class error(Exception):
	pass

class CASTWalker:
	"""
	Walk a C/C++ AST and produce appropriate types in the type registry.
	"""
	def __init__(self, type_registry):
		self.registry = type_registry
		
	def _create_constructed_type_internal(self, ast, meta_type):
		#ast.print_tree()
		members_astlist = ast['type']
		instance_name = ast.find_single_child('declarator').leaf
		type_name = ast.get_single_attribute('type_name', None)
		new_type = self.registry.make_type(meta_type, type_name)
		for member_ast in members_astlist:
			member_inst = self._get_type(member_ast)
			declarator_ast = member_ast.the('declarator')
			member_label = declarator_ast.leaf
			# if member_size_in_bits is None, the type factory will use the
			# default size for the type.
			member_is_bitfield = declarator_ast.get_single_attribute('bitfield', False)
			if member_is_bitfield is not False:
				member_size_in_bits = evaluate(declarator_ast.the('expression'), self.registry)
			else:
				member_size_in_bits = None
			new_type.add_member(member_inst, member_label, member_size_in_bits)
		# If the type isn't anonymous, create it here.
		if type_name is not None:
			self.registry.add_type(new_type)
		return new_type

	def _create_basic_type_internal(self, ast):
		assert ast.leaf is not None
		return self.registry[ast.leaf]

	def _create_union_type(self, ast):
		return self._create_constructed_type_internal(ast, 'union')
	
	def _create_struct_type(self, ast):
		return self._create_constructed_type_internal(ast, 'struct')

	def _get_type(self, ast):
		meta_type = ast.get_single_attribute('meta_type', None)
		if meta_type is None:
			c_type_constructor = self._create_basic_type_internal
		else:
			c_type_constructor = getattr(self, '_create_%s_type' % (meta_type))
		# If the following produces a TypeError then you need to implement this
		# type constructor!
		return c_type_constructor(ast)

	def _add_typedef(self, ast):
		assert ast.get_attribute('storage-class') == ['typedef']
		# the_declarator is the name of the alias.
		declarator_name = ast.the('declarator').leaf
		assert self._is_valid_name(declarator_name)

		type_inst = self._get_type(ast)
		alias_inst = self.registry.make_type('alias', declarator_name, type_inst)
		self.registry.add_type(alias_inst)

	def _add_constant(self, ast):
		#ast.print_tree()
		the_specifiers = ast.get_attribute('type-qualifier'); the_specifiers.sort()
		# FIXME: Take linkage into account here, because we don't want to create the same thing
		# twice.
		type_inst = self._get_type(ast)
		declarator_ast = ast.the('declarator')
		declarator_name = declarator_ast.leaf
		initialiser = declarator_ast.get_single_attribute('initialiser')
		self.registry.make_instance_add_instance(type_inst, declarator_name, initialiser)
	
	def _is_valid_name(self, declarator_name):
		assert len(declarator_name) > 1 and isinstance(declarator_name, basestring)
		return True

	def find_types(self, ast):
		"""
		The only public function.
		"""
		# go to root scope!
		for child in ast.children:
			if child.type == 'type':
				if child.get_attribute('storage-class', []) == ['typedef']:
					# This is a typedef! Hurrah! Add it!
					self._add_typedef(child)
				elif 'const' in child.get_attribute('type-qualifier', []):
					# This is a constant. Add that too.
					self._add_constant(child)
	
#def add_types_ast_to_registry(types_ast, registry):
#	""" Convenience function """
#	walker = CASTWalker(registry)
#	walker.find_types(types_ast)
	

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
	if debug_flags['idlastwalker']:
		ast.print_tree()

class IDLASTWalker:
	""" Walk the IDL AST and import types as appropriate. """
	def __init__(self, type_registry):
		self.registry = type_registry
		
	def _create_constructed_type_internal(self, ast, meta_type):
		pass
		
	def _add_typedef(self, ast):
		#assert ast.leaf == 'typedef'
		#assert ast.get_attribute('specifiers') == 'typedef'
		# the_declarator is the name of the alias.
		namelist = ast.the('declarator').leaf
		typename = ast.the('type').leaf
		print namelist, typename
		
		#if self.registry[typename] == None:
		#	return None
		assert typename != 'fixed'

		if typename == 'sequence':
			type_inst = self._add_constr_type(ast.the('type'))
		for declarator_name in namelist:
			#declarator_name = ast.the('declarator').leaf
			#assert self._is_valid_name(declarator_name)
			if typename == 'sequence':
				#print 'in alias generation'
				
				if type_inst.name == '_sequence' and typename == 'sequence':
					self.registry.rename_type(declarator_name, '_sequence')
					type_inst.name = declarator_name
				else:
					alias_inst = self.registry.make_type('alias', declarator_name, type_inst)
					#print alias_inst
					self.registry.add_type(alias_inst)
			
	def _get_type_list(ast):
		reglist = []
		for name in ast.the('declarator').leaf:

			reglist.append(self.registry[name])
		return reglist
		
		
	def _get_type(ast):
		return self.registry[ast.the('declarator').children[0]]
			
		
	def _add_constr_type(self, ast):
		meta_type = ast.get_attribute('meta_type')
		#print 'here:',ast, meta_type
		meta_type = meta_type[0]	
		if meta_type == 'enum':
			return None
			
		if meta_type == 'sequence':
			if ast.the('type').leaf == 'sequence':
				super_type = self._add_constr_type(ast.the('type'))
			else:
				super_type = self.registry[ast.the('type').leaf]
				
			if ast.has_attribute('length') != None:
				size = ast.get_attribute('length')[0]
			
			print super_type	
			new_type = self.registry.make_type('sequence', '_sequence', super_type, size)
			print new_type
		else:	
			declarator_name = ast.leaf
			new_type = self.registry.make_type(meta_type, declarator_name)
			if meta_type == 'struct':
				self._get_members(new_type, ast)
			elif meta_type == 'union':
				self._get_members(new_type, ast)
			else:
				pass
		#print new_type
		self.registry.add_type(new_type)
		#self.registry.print_registry()
		return new_type
		
	def _get_members(self, new_type, ast):
		for child in ast.children:
			bitfield = 0
			name = child.get_attribute('declarator')[0]
			if child.type == 'type':
				if child.get_attribute('specifiers') == ['typedef']:
					child_type = self._add_constr_type(self, ast)
				else:
					if isinstance(name, list):
						super_type = self.registry[child.leaf]
						#print child, super_type, self.registry.arch_size_in_bits(super_type.name)
						child_type = self.registry.make_type('array', None, super_type, name[2])
						name = name[0]
					else:
						child_type = self.registry[child.leaf]
						#name = child.get_attribute('declarator')[0]
			elif child.type == 'declarator':
				if child.has_attribute('meta_type'):
					child_type = self._add_constr_type(child)
			else:
				pass
			'''
			if bitfield != 0:
				new_type.add_member(child_type, name, bitfield)
			else:
			'''
			new_type.add_member(child_type, name)

	def _add_constant(self, ast):
                declarator_name = ast.leaf
                initialiser = ast.get_attribute('value')[0]
                type_name = ast.the('type').leaf
                type_inst = self.registry[ast.the('type').leaf]
                print type_inst, declarator_name, initialiser
                self.registry.make_instance_add_instance(type_inst, declarator_name, initialiser)
	
	
	
	def _get_type(self, ast):
		'''
		meta_type = ast.get_single_attribute('meta_type', None)
		if meta_type is None:
			c_type_constructor = self._create_basic_type_internal
		else:
			c_type_constructor = getattr(self, '_create_%s_type' % (meta_type))
		# If the following produces a TypeError then you need to implement this
		# type constructor!
		return c_type_constructor(ast)
		'''
		
	def add_types(self):
		pass
		
	def find_types_test(self, ast):
		for el in self.find_types_rec(ast):
			print '\n', el
			
	def find_types(self, ast):
		for child in ast.children:
			if child.type == 'definition':
				for def_child in child.children:
					if def_child.type == 'type':
						if def_child.get_attribute('specifier') == ['typedef']:
							self._add_typedef(def_child) 
							print 'FIXME: processing of typedef'
						elif def_child.get_attribute('specifier') == ['constr_type']:
							self._add_constr_type(def_child.the('declarator'))
						else:
							print 'FIXME: processing of node: ', def_child
					elif def_child.type == 'const':
                                                self._add_constant(def_child)
		
	def find_types_rec(self, ast):
		if ast.type == 'type':
			typelist =[ast]
		else:
			typelist = []
		for child in ast.children:
			typelist.append(self.find_types_rec(child))
		return typelist
		"""
		The only public function.
		
		for defchild in ast.the('IDLFile')['definition']
			if defchild.type == ''
		# go to root scope!
		for child in ast.children:
			if child.type == 'type':
				if child.get_attribute('specifiers', []) == ['typedef']:
					# This is a typedef! Hurrah! Add it!
					self._add_typedef(child)
				elif 'const' in child.get_attribute('specifiers', []):
					# This is a constant. Add that too.
					self._add_constant(child)
		"""

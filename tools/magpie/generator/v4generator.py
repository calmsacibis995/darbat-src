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

# V4 generator. 

# Laundry list: Things to remove from here - possibly move to templates, possibly
# specialise to V4-specific generator.
#  - ArchitectureInfo passed in.
#  - annotate_parameters_with_message_registers and the whole ArchitectureInfo
#    concept is very L4-specific. Perhaps another level.
#  - create_register_map_from_simplified_params
#  - annotate_parameters_with_function_modifiers
#  - get_ktable_functions
#  - get_untyped_words_*
#  - Things like output.gen_client_v4_function ...

import math

from debugging import debug_generator
from helper import c_friendly_string
from simple_params import make_simple_param_list
#from idlparser.helper import get_idl_type_name
from wordsize import ArchitectureInfo, WordSizeAnnotator
from generator import Generator
from targets.shared.options import options

def get_function_name(interface_name, function_ast):
	return '%s_%s' % (interface_name, function_ast.leaf)


class V4WordsizeMixIn(object):
        # OK
	def _get_untyped_bits(self, simplified_params, directions_list, unflagged_only = False):
		""" Private. Count the number of bits in a set of params which match "directions" """
		# Return the number of words in the output.
		# This includes "out" and "inout"(?), and the function return value.
		num_bits = 0
		for param in simplified_params:
			if unflagged_only and param['flags'] != []:
				continue
			if param['direction'] in directions_list:
				debug_generator("UNT: type is %s" % (param['typename']))
				num_bits += param['idltype'].size_in_bits()
		return num_bits

        # OK
	def _words_for_bits(self, num_bits):
		""" Private. Return the number of machine words a given bit size would
			occupy, rounded up to the nearest machine word."""
		# If num_bits is not a multiple of target_word_size, pad to word size
		return int(math.ceil(float(num_bits) / self.arch_info.word_size_in_bits))

class V4Interface(object):
	def __init__(self, interface_ast = None, decorators_list = None, arch_info = None, interface_map = None):
		self.ast = interface_ast
		self.decorators_list = decorators_list
		self.arch_info = arch_info
		self.exports_list = self.ast['function']
		self.inherits = self.create_inheritance_list(interface_map)
		
	# OK
	def create_inheritance_list(self, interface_map):
		inherits = []
		#print 'the() : ', self.ast['inherits']
		if self.ast['inherits'] == None:
			return []
		for name in self.ast['inherits']:
			if interface_map.has_key(name.leaf):
				inherits.append(interface_map[name.leaf])
			else:
				print 'Inheritance-Error! No Interface with name: ', name
				pass
		#print 'Interface inheritance = ', inherits
		return inherits
    
		
		
        # OK
	# public functions
	def get_functions(self, modifier = None):
		function_class = self._my_function_class()
		inher_exports = []
		for inher_num, inher_data in enumerate(self.inherits):
			inher_ast = inher_data[1]
			inher_exports.extend(inher_ast['function'])

		for function_num, export_ast in enumerate(inher_exports + self.exports_list):
			new_func = function_class(function_ast = export_ast,
					interface_name = self.get_name(),
					function_num = function_num,
					arch_info = self.arch_info)
			if modifier is not None and modifier not in new_func.get_modifiers():
				continue
			yield new_func
	
	def get_pagefault_functions(self):
		return self.get_functions(modifier = ('kernelmsg', 'idl4::pagefault'))
		
		
        # OK
	def get_ifdef_name(self):
		return '_objdef___%s' % (self.get_name())
        # OK
	def get_name(self):
		return self.ast.leaf
        # OK
	def get_uuid(self):
		uuid = self._get_uuid_ast()
		if uuid is not None:
			return uuid.the('expression').leaf
		return None
	# OK
	def get_annotations(self):
		decorators = {}
		for decorator in self.decorators_list:
			for arg in decorator.children:
				args = []
				#for exp in arg.children:	
				#args.append(arg.the('expression').leaf)
				if len(arg['expression']) != 0:
					#print 'get_annotations: ', arg['expression']
					for exp in arg['expression']:
						args.append(exp.leaf)
				decorators[arg.leaf] = args
		return decorators

	# OK
	# For service
	def get_function_names(self):
		return [get_function_name(self.get_name(), function_ast) \
				for function_ast in self.exports_list]

	# OK
	def get_fid_mask(self, num_functions):
        # We want to mask off the bits used to specify function ID.
		# So if we have 5 functions we want to mask off bits 0, 1 and 2 
		# so we return 0x7. If we have 15 functions we want to mask off bits
		# 0, 1, 2, and 3 so we return 0xf.
		return int(2 ** math.ceil(math.log(num_functions, 2))) - 1

	# OK
	def get_defined_constants(self):
                #print 'Dont use this!!'
                #assert false
		# FIXME: Why this AND get_constants in the generator?!?!?!?! -nfd 5/sep/05
		uuid_ast = self._get_uuid_ast()
		if uuid_ast is not None and uuid_ast.get_annotation() is not None:
			return [(uuid_ast.children[0].leaf, uuid_ast.get_annotation())]
		else:
			return []
        # OK
	def _get_uuid_ast(self):
		# FIXME: smart nodes instead. CF similarly-named function in the annotator.
		for decorator in self.decorators_list:
			if decorator.children[0].leaf == 'uuid':
				return decorator.children[0]
		return None # didn't find a UUID.

	# OK
	def _my_function_class(self):
		return V4Function

        # OK
	def __repr__(self):
		return '<%s named %s at %x>' % (self.__class__.__name__, 'ahar', id(self))

class V4Function(V4WordsizeMixIn):
	directions_in = ['in', 'inout']
	directions_out = ['out', 'inout', 'return']
	directions_all = ['in', 'inout', 'out', 'return']
	def __init__(self, function_ast = None, interface_name = None, function_num = None,
				arch_info = None):
		self.ast = function_ast
		self.decl_ast = self.ast
		self.interface_name = interface_name
		self.number = function_num
		self.arch_info = arch_info
		self.simplified_params = make_simple_param_list(self.decl_ast)
		self._annotate_parameters(self.simplified_params)
		word_annotator = WordSizeAnnotator(self.simplified_params, self.arch_info)
		word_annotator.annotate()

        # OK
	# For client
	def get_name(self):
		return get_function_name(self.interface_name, self.ast)

        # OK
	def get_name_raw(self):
		decl_ast = self.ast
		return decl_ast.leaf
	# OK
	def set_name_raw(self, new_name):
		self.ast.leaf = new_name

        # OK
	def get_return_type(self):
		#print 'gt_return_type: ', self.decl_ast.type
		return self.decl_ast.the('type').leaf

	# OK
	def get_params(self, direction_list = None, flag = None):
		result = []
		for param in self.simplified_params:
			if flag is not None and flag not in param['flags']:
				continue
			if direction_list is not None and param['direction'] not in direction_list:
				continue
			result.append(param)
		return result

	# OK
	def get_params_in(self):
		return self.get_params(direction_list = ['in', 'inout'], flag = 'call')

        # OK
	def get_params_out(self):
		return self.get_params(direction_list = ['out', 'inout'], flag = 'call')

	# OK -> passtyp in simple_params.py - create_return
	def get_param_return(self):
		result = self.get_params(direction_list = ['return'])
		if result:
			assert len(result) == 1
			return result[0]
		return None

        # OK
	def get_call_params(self):
		return self.get_params(flag = 'call')

	# OK
	def get_fpages_count(self):
		count = 0
		for item in self.simplified_params:
			if 'fpage' in item['flags']:
				count += 1
		return count
	    
        # OK
	def get_is_pagefault(self):
		modifiers = []
		#print 'get_is_pagefault(): decl.ast = ', self.decl_ast
		for deco_node in self.decl_ast['decorator']:
			for modifier_ast in deco_node['annotation']:
				if modifier_ast.leaf == 'kernelmsg':
                                    for exp_node in modifier_ast['expression']:
					if exp_node.leaf == 'idl4::pagefault':
						return True
		return False

	# OK
	def get_modifiers(self):
		modifiers = []
		for deco_node in self.decl_ast['decorator']:
			for modifier_ast in deco_node['annotation']:
			    	arg_ast = []
                            	for exp_node in modifier_ast['expression']:
					if exp_node.result != None:
						arg_ast.append(exp_node.result)
					else:
						arg_ast.append(exp_node.leaf)
				#print 'argAST = ', arg_ast
				
				
				if arg_ast == []:
					modifiers.append( (modifier_ast.leaf, ()) )
				elif len(arg_ast) == 1:
					modifiers.append( (modifier_ast.leaf, arg_ast[0]) )
				else:
					modifiers.append( (modifier_ast.leaf, arg_ast) )
		return modifiers

        # OK
	def get_num_untyped_output_words(self):
		""" Return the number of words in the output direction."""
		returntype_ast = self.decl_ast
		num_bits = self._get_untyped_bits(self.simplified_params, ['out', 'inout'])
		num_bits += returntype_ast.get_annotation().size_in_bits()
		return self._words_for_bits(num_bits)

	# OK
	def get_num_untyped_input_words(self):
		""" Return the number of words in the input direction."""
		num_bits = self._get_untyped_bits(self.simplified_params, ['in', 'inout'], unflagged_only = True)
		return self._words_for_bits(num_bits)

        # OK
	def get_number(self):
		return self.number

	# OK
	def get_defable_name(self):
		return '_MAGPIE_' + self.get_name().upper()

	# OK
	def get_ifdef_name(self):
		return '_funcdef___%s' % (c_friendly_string(self.get_name()))

	# OK
	def get_priv_param_name(self):
		for param in self.simplified_params:
			if 'priv' in param['flags']:
				return param['name']
		return None

	# OK
	def rename_args(self, type_remap):
		for param in self.simplified_params:
			for key in type_remap:
				if key in param['flags']:
					param['typename'] = type_remap[key]

	# OK
	def _annotate_parameters(self, params):
		# We only handle one sort of modifier right now
		is_pf = self.get_is_pagefault()
		# Count the number of fpages in the input; we use this later.
		# Now annotate the parameters
		for param in params:
			flags = []
			if is_pf and param['name'] == 'priv':
				flags.append('priv')
				flags.append('call')
			elif is_pf and param['typename'] == 'fpage':
				flags.append('fpage')
				flags.append('call')
			elif param['direction'] != 'return':
				# It's a regular parameter; add it to the list of call params.
				flags.append('call')
			param['flags'] = flags
	
class V4Generator(Generator, V4WordsizeMixIn):
	""" Code to generate V4 client stubs """
	def __init__(self, output, ast):
		# FIXME: Create architecture info somewhere better.
		self.arch_info = ArchitectureInfo()
		Generator.__init__(self, output, ast)
		self.interface_map = {}

	# OK
	def get_interfaces(self):
		# AST-walkin' time!
		interface_class = self._my_interface_class()
		for container, interface in self.astinfo.get_definitions('interface'):
			self.interface_map[interface.leaf] = [container, interface]
			#print self.interface_map
			#container.the('decorator').print_tree()
			#print 'uuid is', uuid
			yield interface_class(interface_ast = interface,
					decorators_list = container['decorator'],
					arch_info = self.arch_info,
					interface_map = self.interface_map)
			#self.goop_interface(decorated_definition_ast)

        # OK
	def get_constants(self):
		
		for container, defn in self.astinfo.get_definitions('const'):
				const_name = defn.leaf
				const_value = defn.get_attribute('value')[0]
				yield (const_name, const_value)

        # OK
	def get_imports(self):
		for impn in self.astinfo.ast.ast['import']:
			#print 'importing : ', defn
			yield impn.leaf

	# OK
	def get_idl_filename(self):
		return options.idl_filenames[0]

	# OK
	def get_output_filename(self):
		return options['output_filename']

	# OK
	def get_ifdefable_filename(self):
		return '__%s__' % (c_friendly_string (self.get_output_filename()))

	# OK
	def get_types(self):
		""" Return a list of type instances. Type instances are returned if:
		 * They appear as annotations to "op_return_type" or "parameter_decl"
		 * They have their is_predefined property set to False.
		"""
		appropriate_types = []
		for node in self.ast.ast.traverse():
			if node.type in ('function', 'parameter'):
				annotation = node.get_annotation()
				if annotation and annotation.is_predefined is False:
					appropriate_types.append(annotation)
		return appropriate_types

	# OK
	def _my_interface_class(self):
		return V4Interface

def construct(output, ast):
	return V4Generator(output, ast)

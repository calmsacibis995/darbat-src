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

from debugging import debug_annotate
"""
"""

class IDLASTTypeAnnotator:
	""" Walk the CORBA AST and annotate type definitions using the type registry. """
	# FIXME: We should be using a scoped type registry here.
	def __init__(self, type_registry):
		self.registry = type_registry
	
	def annotate(self, ast_info):
		""" Currently, we only annotate function arguments and function return values ---
			this is all the IDL generator needs.
		"""
		for definition in ast_info.ast['definition']:
			interface_decl_ast = definition.the('interface')
			if interface_decl_ast is None:
				# Not an interface declaration so no need to annotate
				continue
			
			for function_ast in interface_decl_ast['function']:
				self.annotate_function_params(function_ast)
				self.annotate_function_return(function_ast)
				
	def annotate_function_params(self, function_ast):
		#params_ast = function_ast.the('op_declaration').the('parameter_list')
		for param in function_ast['parameter']:
			var_name = param.leaf
			type_name = param.the('type').leaf #self.get_type(param.the('parameter_type'))
			# Create an instance of this type and store it in the annotation.
			debug_annotate ("var name is %s, type name is %s, registry says %s" % (var_name, type_name, self.registry[type_name]))
			type_ref = self.registry[type_name]
			param.annotate(type_ref)

	def annotate_function_return(self, function_ast):
		type_name = function_ast.the('type').leaf
		debug_annotate ("var name is return, type name is %s, registry says %s" % (type_name, self.registry[type_name]))
		# FIXME: Removed __return here 5/sep/05 - nfd
		function_ast.annotate(self.registry[type_name])
	
	
	def ___get_type(self, paramtype_ast): #NO LONGER OF USE!!!????!!!!
		if paramtype_ast.leaf == 'void':
			return 'void'
		if paramtype_ast.the('existing_constr_type') is not None:
			return paramtype_ast.the('existing_constr_type').leaf
		return None

class IDLASTConstantAnnotator:
	""" Walk the CORBA AST and annotate constant definitions using a list of constants. """
	# FIXME: This is hackish and will go away with CPP/IDL shared scopes.
	def __init__(self, type_registry):
		self.registry = type_registry
	
	def annotate(self, ast_info):
		for definition in ast_info.ast['definition']:
			for dec in definition['decorator']:
				uuid_ast = self._get_uuid_ast(dec)
				if uuid_ast is not None:
					uuid_name = uuid_ast.the('expression').leaf
					#print 'IDLASTConstAnnotator: uuidname = ', uuid_name
					if self.registry.has_key(uuid_name):
						type_inst = self.registry[uuid_name]
						uuid_ast.annotate(type_inst.initialiser)
		
	def _get_uuid_ast(self, decorators):
		# FIXME: this function is an argument for smarter nodes.
		for item in decorators.children:
			if item.leaf == 'uuid':
				return item

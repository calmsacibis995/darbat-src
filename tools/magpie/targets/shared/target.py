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

import glob
import sys
import os

import helper
from magpietypes.registry import new_registry
from magpietypes.annotator import IDLASTTypeAnnotator as TypeAnnotator
from inputparser import ASTImportError
from inputparser import construct as inputparser_construct
from output.generic import GenericOutput
from generator import Generators
from options import options

class CommandlineError(Exception):
	pass
class TargetReadError(Exception):
	pass

class Target(object):
	"""
	The target class:
		- Create a type registry
		- Create input, output, and generator classes
		- Generate ASTs
		- Generate output for ASTs.
		- Write the output somewhere
		- Pretty-print the output.
	
	Key instance variables:
		self.type_registry
		self.generator
		self.templates
		self.output
		self.inputparser
	"""
	def __init__(self):
		target_data = self.get_target_data(options['target'])
		
		# Create the type registry.
		self.type_registry = new_registry(options['hardware_arch'])

		self.templates = target_data['Templates']()
		self.output = GenericOutput()
		self.generator = Generators[target_data['Generator']]
		self.inputparser = inputparser_construct(self.type_registry)
	
	def run(self):
		# Meat of the generator.
		# By this stage options have been parsed; the task is simply to read 
		# the relevant files, generate an AST, and then walk that AST
		# to produce the correct output files according to the options.
		if options['print_help']:
			# Print help only
			self._print_help(options['print_help'])
			return False
		else:
			# Run Magpie proper.
			self._sanity_check_cmdline(options)
			try:
				self.generate_asts()
				self.generate_output()
			except ASTImportError, e:
				print >>sys.stderr, "Import error: %s" % (str(e))
				if e.show_traceback is True:
					raise
				return False
			except Exception, e:
				print >>sys.stderr, "Error encountered. Traceback follows."
				raise
			return True
	
	def generate_asts(self):
		# For each IDL filename, generate an AST.
		self.asts = []
		for idl_filename in options.idl_filenames:
			ast = self.inputparser.produce_ast(idl_filename)
			# FIXME: Should type annotation really go here?
			annotator = TypeAnnotator(self.type_registry)
			annotator.annotate(ast)
			self.asts.append(ast) # We should only have one...
			#ast.ast.print_tree()
	
	def generate_output(self):
		# Initialise the output context...
		self.output.context['templates'] = self.templates
		self.output.context.file.version_string = helper.VERSION_STRING
		for ast in self.asts:
			generator_inst = self.generator(self.output, ast)
			self.output.context['generator'] = generator_inst
			self.output.context.file.output_filename = options['output_filename']
			self.output.context.file.idl_filename = ast['filename']
			base_template = self.templates.get(options['output_type'])
			self.output.go(base_template)
		output_str = self.output.getvalue()
		self.write_output(output_str)

	def write_output(self, output_str):
		# FIXME: All of this (and generate_output?) should go somewhere generic
		if options['output_filename'] == '-':
			sys.stdout.write(output_str)
		else:
			self.outputfile = file(options['output_filename'], 'w')
			self.outputfile.write(output_str)
			self.outputfile.close()

	def get_target_data(self, target_name_list):
		""" We can have a bunch of targets, each inheriting from the last.
		"""
		# Pre-init the options with a very liberal set.
		class BaseTemplates:
			template_base = ''
			def get(self, name):
				template_name = getattr(self, name, None)
				if template_name:
					return os.path.join(self.template_base, template_name)
				else:
					return None
			public = []
		target_opts = {'Templates': BaseTemplates,
			'Generator': None}
		# We've initialised the options. Now add each target in sequence.
		for target_name in target_name_list:
			new_target_opts = {'OldTemplates': target_opts['Templates'],
					'Generator': target_opts['Generator']
			}
			target_pathname = self._get_target_data_produce_pathname(target_name)
			execfile(target_pathname, new_target_opts)
			target_opts = new_target_opts
		# Sanity-check the data
		if not issubclass(target_opts.get('Templates', None), BaseTemplates):
			raise TargetReadError("Target chain %s does not define a valid Templates class" %\
					(str(target_name_list)))
		if not isinstance(target_opts.get('Generator', None), basestring):
			raise TargetReadError("Target chain %s does not define a valid Generator" %\
					(str(target_name_list)))
		return target_opts

	def _get_target_path(self):
		return os.path.join(helper.get_module_base_path(), 'targets')

	def _get_target_data_produce_pathname(self, target_name):
		target_filename = '%s.target.py' % (target_name)
		target_pathname = os.path.join(self._get_target_path(), target_filename)
		return target_pathname
	
	def _sanity_check_cmdline(self, cmdline_options):
		if not isinstance(cmdline_options['output_type'], basestring):
			raise CommandlineError("Output type not specified.")
		if not cmdline_options.idl_filenames:
			raise CommandlineError("IDL filename not specified.")


	def _print_help(self, help):
		printed = False
		if 'list_targets' in help:
			targets = glob.glob(os.path.join(self._get_target_path(), '*.target.py'))
			targets.sort()
			print "Available targets:"
			for target in targets:
				pretty_name = os.path.basename(target)
				pretty_name = pretty_name.split('.target.py')[0]
				print ' * %s' %(pretty_name)
			printed = True
		if 'list_outputs' in help:
			pretty_target_list = ' : '.join(options['target'])
			print "Public outputs for target list %s:" % (pretty_target_list)
			if not hasattr(self.templates, 'public') or not self.templates.public:
				print " - None found."
			else:
				for public in self.templates.public:
					print " * %s" % (public)
			printed = True
		if not printed:
			print "No help to print (internal error?)"

	
#	def imp(self, name):
#		""" Import the module 'name'. This workaround for weird __import__ 
#		behaviour comes straight out of the Python built-in-functions documentation.
#		"""
#		package_end = name.rindex('.')
#		package, module = name[:package_end], name[package_end + 1:]
#		mod = __import__(package, globals(), locals(), module)
#		mod = getattr(mod, module)
#		return mod
	


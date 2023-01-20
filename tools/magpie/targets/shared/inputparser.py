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

import re
import popen2
import os.path
import debugging

from cparser import parse as cparse

from magpietypes.castwalker import CASTWalker #add_types_ast_to_registry
from idlparser import parse as idlparser
#from idlparser import parse_to_ast as parse_to_ast
from parser_common import ParserLexerState, print_tree
from debugging import debug_import
from magpietypes.annotator import IDLASTConstantAnnotator
from helper import usr_bin_which
from targets.shared.options import options

class ASTImportError(Exception):
	def __init__(self, *args, **kwargs):
		Exception.__init__(self, *args, **kwargs)
		self.show_traceback = True

class CImportError(ASTImportError):
	pass

class CPPNotFoundError(CImportError):
	def __init__(self, *args, **kwargs):
		CImportError.__init__(self, *args, **kwargs)
		self.show_traceback = False

class GenericASTInfo(object):
	def __init__(self, ast, **kwargs):
		self.ast = ast
		self.info = kwargs
	
	def __getitem__(self, key):
		return self.info[key]
	
# FIXME: This should be elsewhere probably
class CASTImporter(object):
	def __init__(self, filename_list, type_registry):
		self.filename_list = filename_list
		self.type_registry = type_registry

#	def find_real_filepath(self, filename):
#		"""Check list of include directories for the given file.
#		cpp accepts -I to supply include directories, but is apparently too stupid
#		to check them when supplied with a filename.
#		"""
#		for path in ['.'] + options['c_include_dirs']:
#			candidate = os.path.join(path, filename)
#			if os.path.exists(candidate):
#				return candidate
#		raise Exception("Can't find file %s in cwd or list of includes: %s" % \
#			(filename, ', '.join(options['c_include_dirs'])))

	def preprocess_and_grab_data(self, filename_list):
		# Make a tiny C file containing all the filenames as included.
		cpp_file = ['#include "%s"' % (filename) for filename in filename_list]
		cpp_file = '\n'.join(cpp_file) + '\n'
		# Run the C preprocessor over the file first.
		cpp = options['c_preprocessor']
		full_cpp_path = usr_bin_which(cpp)
		if full_cpp_path is None:
			raise CPPNotFoundError("C pre-processor '%s' not found" % cpp)
		cpp_command_line = ' '.join ([cpp] + options['cpp_options'] \
			+ ['-I%s' % (incdir) for incdir in options['c_include_dirs']])
		debug_import ("***** cpp: %s" % (cpp_command_line))
		child_out, child_in = popen2.popen4(cpp_command_line)
		child_in.write(cpp_file)
		child_in.close()
		return child_out.read()
		
	def run(self):
		debug_import ("***** Preprocessing %s" % (self.filename_list))
		data = self.preprocess_and_grab_data(self.filename_list)
		debug_import ("Data:\n%s" % (data))
		# Calculate the path to the parse tables.
		parse_tables_prefix = 'c_parser_gen'
		ast_walker = CASTWalker(self.type_registry)
		filename_for_parser = '_'.join(self.filename_list)
		try:
			ast = cparse(filename_for_parser, data) #, ast_walker = ast_walker,
				#type_registry = self.type_registry,
				#parse_tables_prefix = parse_tables_prefix)
			ast_walker.find_types(ast)
		except Exception, e:
			print "*** Exception encountered while processing %s" % (self.filename_list)
			file("inputparser.error.out", 'w').write(data)
			print "Preprocessed input written to inputparser.error.out"
			raise
		# Add all them thar types.
		# FIXME: This needs a cleanup; we now just pass the AST walker to the parser.
		# add_types_ast_to_registry(ast, self.type_registry)
		return ast

class ASTGeneratorCImportMixIn(object):
	# Import handing as of sep 2005:
	# - We now scan the whole file prior to handing it to the parser, and perform
	#   all imports in one go. This is handled a bit poorly.
	def __init__(self, type_registry):
		self.type_registry = type_registry
		#self.shared_state.import_handler = self.handle_import_statement
		self.shared_state.import_handler = self.handle_import_statement_dummy
		self.shared_state.set_registry(self.type_registry)

	def handle_import_statement(self, import_filename):
		# What to do when we get an import statement - basically
		# 1. Get the filename from the AST
		# 2. Run the C preprocessor over the AST, making sure to
		#    supply all the relevant include directories and flags
		# 3. Feed the result to the C parser and get an AST
		# 4. Run idltypes/castwalker over the ast to update the type
		#    registry.
		importer = CASTImporter(import_filename, self.type_registry)
		ast = importer.run()

	def handle_import_statement_dummy(self, import_filename):
		pass
	
	def perform_imports(self, data):
		import_re = re.compile(r'^import +"(.*?)";', re.MULTILINE)
		filenames = import_re.findall(data)
		if filenames:
			importer = CASTImporter(filenames, self.type_registry)
			ast = importer.run()
		
class GenericASTGenerator(object):
	def __init__(self):
		self.create_shared_state()

	def create_shared_state(self):
		self.shared_state = ParserLexerState()

	# AST generator interface
	def produce_ast(self, idl_filename):
		data = file(idl_filename, 'r').read()
		self.perform_imports(data) # FIXME
		# raw_ast = parse(data, shared_state = self.shared_state, parse_tables_prefix =\
		#	'idl_parser_gen', debug=debugging.debug_flags['idlparser'])
		#print 'producing ast ...'
		raw_ast = idlparser(idl_filename, data)
		#print '.. ast produced'
		return GenericASTInfo(raw_ast, filename=idl_filename)

class ImportingASTGenerator(GenericASTGenerator, ASTGeneratorCImportMixIn):
	def __init__(self, type_registry):
		GenericASTGenerator.__init__(self)
		ASTGeneratorCImportMixIn.__init__(self, type_registry)
	
	def produce_ast(self, *args):
		# FIXME: This must all go with CPP/AST unified scoping
		ast_info = GenericASTGenerator.produce_ast(self, *args)
		annotator = IDLASTConstantAnnotator(self.type_registry)
		annotator.annotate(ast_info)
		return ast_info

def construct(type_registry):
	return ImportingASTGenerator(type_registry)


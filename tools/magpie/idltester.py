"""
Specialised tester for IDL; we want:

- Display parse tree
- Display AST
"""

import re
from optparse import OptionParser
#from idlparser import parser as idlparser
#from idlparser import astgen
from parser_common import ParserLexerState
from idlparser import parse_to_pt_cached,parse_to_pt_noncached, parse_to_ast
from magpietypes.registry import new_registry
from magpietypes.idlastwalker import IDLASTWalker
#from cache import cache
#from targets.shared.inputparser import ASTGeneratorCImportMixIn, IDLASTImporter
from targets.shared.options import options

# "constants"
REGISTRY_MACHINE_TYPE = "Generic 32"

def gimme_a_registry():
	""" Provide a type registry with builtin types for ast and cpp """
	return new_registry(REGISTRY_MACHINE_TYPE)

def main():
	# Parse command-line arguments and dispatch to appropriate tester.
	parser = OptionParser()
	parser.add_option('--pt', dest = 'pt', action = 'store_true', default = False,
			help = 'Display the IDL parse tree')
	parser.add_option('--ast', dest = 'ast', action = 'store_true', default = False,
			help = 'Display the IDL AST')
	parser.add_option('--types', dest = 'types', action = 'store_true', default = False,
			help = 'Import types and display the type registry')
	
	my_options, args = parser.parse_args()

	filename = args[0]
	#Read the data from file
	data = file(filename).read()
	state = ParserLexerState()
	
	registry = gimme_a_registry()

	#import_re = re.compile(r'^import +"(.*?)";', re.MULTILINE)
	#filenames = import_re.findall(data)
	#if filenames:
	#	importer = CASTImporter(filenames, state.type_registry)
	#	ast = importer.run()
	
	pt = parse_to_pt_noncached(data)

	if my_options.pt:
		print "*** PT:"
		pt.print_tree()
		print "*** PT ends"
	
	if my_options.ast:
		ast = parse_to_ast(pt)
		print "*** AST:"
		ast.print_tree()
		print "*** AST ends"
		
	if my_options.types and ast:
		print "*** Types list:"
		walker = IDLASTWalker(registry)
		#registry.print_registry()
		walker.find_types(ast)
		walker.registry.print_registry()
		print "*** Types list ends"
		
	
	
if __name__ == '__main__':
	main()

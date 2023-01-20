"""
Specialised tester for C++ import; we want:

- Display parse tree
- Display AST
- Import types and display registry.
"""
from optparse import OptionParser
from cparser import parse_to_pt_cached, parse_to_ast
from magpietypes.registry import new_registry
from magpietypes.castwalker import CASTWalker
from cache import cache
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
			help = 'Display the C++ parse tree')
	parser.add_option('--ast', dest = 'ast', action = 'store_true', default = False,
			help = 'Display the C++ AST')
	parser.add_option('--types', dest = 'types', action = 'store_true', default = False,
			help = 'Import types and display the type registry')
	# Other options we might want...
	parser.add_option('--nocache', dest = 'nocache', action = 'store_true', default = False,
			help = "Don't used cached versions of the parse tree")
	my_options, args = parser.parse_args()

	filename = args[0]
	data = file(filename).read()

	options.cache_enabled = not my_options.nocache

	options.set_initialised()

	pt = parse_to_pt_cached(filename, data)

	if my_options.pt:
		print "*** Parse tree:"
		pt.print_tree()
		print "*** Parse tree ends"

	ast = parse_to_ast(pt)

	if my_options.ast:
		print "*** AST:"
		ast.print_tree()
		print "*** AST ends"

	registry = gimme_a_registry()
	walker = CASTWalker(registry)
	walker.find_types(ast)

	if my_options.types and ast:
		print "*** Types list:"
		registry.print_registry()
		print "*** Types list ends"
	
if __name__ == '__main__':
	main()

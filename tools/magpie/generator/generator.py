class ASTInfo(object):
	"""
	This is where we put all the convenience functions to walk the AST.
	This class is just for the namespace and instances do not store state
	apart from the AST itself.
	"""
	def __init__(self, ast):
		self.ast = ast
	
	def get_definitions(self, childname):
		for defn in self.ast.ast['definition']:
			result = defn.the(childname)
			if result is not None:
				yield defn, result


class Generator(object):
	"""
	Walks the IDL AST and calls relevant output functions.

	Writing a generator necessarily means deciding on the basic structure of
	the output.
	"""
	def __init__(self, output, ast):
		self.output = output
		self.ast = ast
		self.astinfo = ASTInfo(ast)
		self.output.set_hook_object(self)


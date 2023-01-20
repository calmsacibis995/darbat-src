# Errors
class EvaluationError(Exception):
	pass

# Helpers
class EvalUndefined(object):
	pass

class Evaluator(object):
	def __init__(self, type_registry):
		self.registry = type_registry
		self.OPERATOR_HANDLERS = {
			'+': self.evaluate_plus,
			'-': self.evaluate_minus,
			'*': self.evaluate_multiply,
			'/': self.evaluate_divide,
			'sizeof': self.evaluate_sizeof,
		}


	def evaluate_lit(self, pt):
		"""
		Evaluate a literal. This should recognise:
		 * The U, L, and UL modifiers
		 * Floats, ints, chars
		"""
		# Right now just try ints and barf otherwise. :)
		return int(pt.leaf)

	def evaluate_plus(self, lhs, rhs):
		return self.evaluate(lhs) + self.evaluate(rhs)

	def evaluate_minus(self, lhs, rhs = EvalUndefined):
		if rhs is EvalUndefined:
			# Unary minus
			return -(self.evaluate(lhs))
		else:
			return self.evaluate(lhs) - self.evaluate(rhs)

	def evaluate_multiply(self, lhs, rhs):
		return self.evaluate(lhs) * self.evaluate(rhs)

	def evaluate_divide(self, lhs, rhs):
		return self.evaluate(lhs) / self.evaluate(rhs)

	def evaluate_sizeof(self, pt):
		"""
		Return the size of a type given a type_name parse tree fragment.
		Doesn't handle everything yet.
		"""
		# Sanity checks:
		assert pt.my_children_are('declaration_specifiers', 'abstract_declarator')
		# ... we don't handle abstract decls here yet so panic if we get one.
		abstract_declarator_pt = pt.the('abstract_declarator')
		assert not abstract_declarator_pt.result and not abstract_declarator_pt.children
		# And find it in the registry.
		type_name = pt.the('declaration_specifiers').result
		type_size = self.registry[type_name].size_in_bits()
		assert type_size and type_size % 8 == 0
		return type_size / 8

	def unsafe_evaluate(self, pt):
		if not pt.children:
			# Just return the literal.
			return self.evaluate_lit(pt)
		else:
			return self.OPERATOR_HANDLERS[pt.leaf](*pt.children)

	def evaluate(self, pt):
		"""
		Evaluates expression nodes. Raises EvaluationError if the expression
		couldn't be evaluated. (This will happen if the expression is non-constant,
		or even (currently) if the expression is constant but is not composed of
		literals.)
		"""
		return self.unsafe_evaluate(pt)
		try:
			result = self.unsafe_evaluate(pt)
			print "would return from"
			pt.print_tree()
			print "..done"
			return result
		except Exception:
			raise EvaluationError(pt)

def evaluate(pt, registry):
	evaluator = Evaluator(registry)
	return evaluator.evaluate(pt)


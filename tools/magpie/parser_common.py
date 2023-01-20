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

import traceback

exception_if_incomplete = False # FIXME: Set to True for final.

class NoDefault(object):
	pass

class ParserLexerState:
	def __init__ (self):
		self.typedefs = []
		self.constants = {}
		self.in_typedef = False
	
	def set_registry(self, type_registry):
		self.type_registry = type_registry
	
	def addTypedef (self, identifier):
		raise NotImplementedError() # Obsolete
		self.typedefs.append (identifier)

	def addModifier (self, identifier):
		self.modifiers.append (identifier)
	
	def isModifier (self, identifier):
		return identifier in self.modifiers

	def isTypedef (self, identifier):
		if identifier in self.typedefs:
			return True # FIXME: deprecated
		if self.type_registry.has_key(identifier):
			return True
		return False
	
	def add_constant(self, name, const_type=None, const_value=None):
		self.constants[name] = {'type': const_type, 'value': const_value}
	
	def is_constant(self, name):
		# FIXME: Also check for constants declared in the type registry
		if name in self.constants:
			return True # FIXME: is this ever used?
		elif self.type_registry.has_key(name):
			# FIXME: This isn't necessarily a const...
			return True
		return False
	
	def get_constant_names(self):
		raise NotImplementedError('obsolete')
		return self.constants.keys()
	
	def get_constant_value(self, constant_name):
		return self.constants[constant_name]['value']
	
def print_tree (node, depth=None, parent_name=None):
	if depth is None: depth = 0
	if node is None:
		print ' ' * depth, '* NONE (Unfinished tree, parent is %s)' % (parent_name)
	else:
		print ' ' * depth, node.type,
		result = ''
		if node.result is not None:
			result = '= %s' % (node.result)
		if node.leaf is not None:
			print node.leaf, result,
		else:
			print result,
		annotation = node.get_annotation()
		if annotation is not None:
			print "[Ann: %s]" % (annotation),
		print '(%d)' % (depth)
		for attr_name in node.attributes:
			print ' ' * depth, '+- %s =' % (attr_name), node.attributes[attr_name]
		for child in node.children:
			print_tree (child, depth+1, parent_name=node.type)

class Node:
	def __init__ (self, name, children=None, leaf=None, result=None):
		self.type = name
		self.attributes = {}
		if children:
			self.children = children
		else:
			self.children = []
		try:
			for child in self.children:
				if not isinstance(child, Node):
					print "Node was trying to create itself but encountered a child of type", type(child)
					print "Node repr", repr(child)
					print "I am named %s with a leaf of leaf %s" % (name, leaf)
					print "RRRR"
					assert isinstance(child, Node)
		except:
			print type(self.children), self.children
			raise
		self.leaf = leaf
		if exception_if_incomplete is True:
			if children and None in children:
				print "Children up to this point:"
				print_tree(self)
				raise Exception("One of my children is missing! type is %s, children so far are %s" % (name, children) )
		self._annotation = None
		self.result = result
	
	def __str__ (self):
		return '%s (%s) = %s' % (self.type, self.leaf, self.children)
	__repr__ = __str__

	def add_child(self, child):
		"""if not isinstance(child, Node):
			print "hmm, node is a", type(child)
			print "it is", child
			print "named", name, "leaf", leaf
			print "RRRR"
			assert isinstance(child, Node)"""
		#print 'adding child', child
		self.children.append(child)

	def add_children(self, children):
		for child in children:
			self.add_child(child)

	def set_leaf(self, leaf):
		self.leaf = leaf
	
	def set_result(self, result):
		self.result = result

	def print_tree(self):
		print_tree(self)

	def my_children_are(self, *child_names, **kwargs):
		maxkids = kwargs.get('maxkids', len(child_names))
		minkids = kwargs.get('minkids', len(child_names))

		if len(self.children) < minkids or len(self.children) > maxkids:
			return False

		for child, wanted_name in zip(self.children, child_names):
			if child.type != wanted_name:
				return False
		return True
	
	def add_attribute(self, key, value):
		"""
		"""
		if not isinstance(value, list):
			value = [value]
		if self.attributes.has_key(key):
			self.attributes.extend(value)
		else:
			self.attributes[key] = value

	def has_attribute(self, key):
		return self.attributes.has_key(key)
	
	def get_attribute(self, key, default = NoDefault):
		if default is NoDefault:
			if self.has_attribute(key):
				return self.attributes[key]
			else:
				return None
		else:
			return self.attributes.get(key, default)
	
	def get_single_attribute(self, key, default = NoDefault):
		if default is NoDefault:
			attrs = self.attributes[key]
		else:
			attrs = self.attributes.get(key, [default])
		assert len(attrs) == 1
		return attrs[0]

	def get_child_names(self):
		return [child.type for child in self.children]

	def the(self, keylist):
		""" Return the only child with a type matching any in <keylist>
		Usage: somenode.the('childnode')
		Returns: a Node iff there is a single child
		Returns: None iff there are no children.
		Raises Exception iff there is more than one matching child."""
		if type(keylist) is not list:
			keylist = [keylist]
		suitableChildren = []
		for key in keylist:
			for child in self.children:
				if child.type == key:
					suitableChildren.append(child)
		if len(suitableChildren) > 1:
			raise Exception("Too many children for me. I am %s, wanted %s" % (self.type, keylist))
		if len(suitableChildren) == 0:
			return None
		return suitableChildren[0]
	
	def find_single_child(self, keylist):
		return self.the(keylist)
	
	def maybe_walk_to(self, *args):
		"""Return the descendant matching the list supplied in *args.
		Usage: somenode.maybe_walk_to('child', 'grandchild', ...)
		Returns: a Node if the descendants could be walked to a matching Node.
		Returns None, otherwise."""
		current = self
		for target in args:
			current = current.the(target)
			if current is None:
				return None
		return current

	def __getitem__ (self, key):
		""" Return a list of all children with a type matching <key> """
		suitableChildren = []
		for child in self.children:
			if child.type == key:
				suitableChildren.append (child)
		return suitableChildren
	
	def annotate(self, annotation):
		assert self._annotation is None # Don't - yet - allow multiple annotations
		self._annotation = annotation
	
	def get_annotation(self):
		return self._annotation
	
	def traverse(self):
		pos = [self]
		while pos:
			yield pos[-1]
			pos.extend(pos.pop().children)

def UnfinishedNode(type):
	return Node(type, None, 'UNFINISHED')

def ExpressionNode(type, children):
	if len(children) == 1:
		# Collapse long chains of "empty" expression nodes
		return children[0]
		#return Node(type, children)
	elif len(children) == 3:
		# In this case it actually is parsing an expression of this type.
		# We actually try to propagate constant expressions up the tree, so we 
		# try to eval, and if that fails we leave the expanded expression.
		result = None
		# FIXME: This is a bit hackish, but t[1] may be a Node but it may be a String or
		# something
		if isinstance(children[1], Node):
			operator = children[1].leaf
		else:
			operator = children[1]
		if children[0].result is not None and children[2].result is not None:
			try:
				expression = '%sL %s %sL' % (children[0].result, operator, children[2].result)
				result = eval(expression)
			except (NameError, SyntaxError):
				result = '(%s %s %s)' % (children[0].result, operator, children[2].result)
		return Node(type, [children[0], children[2]], children[1], result=result)
	else:
		raise Exception("Expression constructor too many args!")

def UnaryOperatorNode(type, children):
	assert len(children) in (1,2)
	if len(children) == 2:
		result = eval(children[0].leaf + str(children[1].result))
	else:
		result = children[0].result
	return Node(type, children, result=result)


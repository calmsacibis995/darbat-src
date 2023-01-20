
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
from helper import positive_id

"""
Type properties:
	- is_namespace : if True, the type can contain names.
	- is_marshallable : if True, the type can be sent across an interface.
		Right now, this just means the type has a "size_in_bits()" method.
	- is_value_type : Undefined if is_marshallable is False. 
		Otherwise, if True, the type can be passed by value.
		FIXME: This is pretty simplistic.
	- is_predefined : if True, the type is already defined in the target.
		if False, the type should be replicated in the target.
"""

class UnknownMembers:
	pass

class MagpieTypeInstance(object):
	"""
	Hi! I'm a generic type instance!
	"""
	def __init__(self, type_obj, label, initialiser):
		self.label = label
		self.type_obj = type_obj
		self.initialiser = initialiser
	
	def dump(self, level):
		print ' ' * level, '%s (instance of %s) = %s' % (self.label, self.type_obj.name, self.initialiser)

class MagpieType(object):
	"""Overload this to implement type classes."""

	def __init__(self, registry, name):
		"""
		arch: a TypeSizes instance (see arch_sizes.py)
		name: the type name
		"""
		self.is_namespace = False
		self.is_marshallable = False
		self.is_value_type = None # Doesn't make sense if not marhsallable
		self.is_predefined = True # Assume that we don't need to replicate anything.
		# Type-specific stuff...
		self.registry = registry
		self.name = name
	
	def __str__(self):
		return "<%s '%s' at 0x%x>" % (self.__class__.__name__, self.name, positive_id(self))
	
	def make_instance(self, label, initialiser):
		"""
		Create a generic type instance. Overload this if necessary for type-specific
		initialisation.
		"""
		return MagpieTypeInstance(self, label, initialiser)
	
class NamespaceMixIn(object):
	def __init__(self, parent = None):
		self.is_namespace = True
		self.is_marshallable = False
		# Namespace-specific stuff...
		self.parent = parent
		self.namespace_clear()

	def namespace_clear(self):
		self.names = {}
		
	def namespace_add(self, name, obj):
		if name in self.names:
			print "Adding duplicate name", name, id(obj), id(self.names[name])
		#print name, self.names
		#assert name not in self.names
		self.names[name] = obj
	
	def namespace_rename(self, newname, name):
		assert name in self.names
		assert newname not in self.names
		obj = self.names[name]
		del self.names[name]	
		self.names[newname] = obj	
		
		
	def namespace_lookup(self, name):
		return self.names[name]
	
	def namespace_set_parent(self, parent):
		self.parent = parent
	
	def namespace_has_key(self, key):
		if self.names.has_key(key):
			return True
		elif self.parent is not None:
			return self.parent.has_key(key)
		else:
			return False

	def namespace_items(self):
		return self.names.items()
	
	def __getitem__(self, key):
		return self.namespace_lookup(key)

class MagpieTypeNamespace(MagpieType, NamespaceMixIn):
	def __init__(self, registry, name):
		MagpieType.__init__(self,registry, name)
		NamespaceMixIn.__init__(self)

class MagpieTypeBasic(MagpieType):
	def __init__(self, registry, name):
		MagpieType.__init__(self, registry, name)
		self.is_marshallable = True
		self.is_value_type = True
	
	def size_in_bits(self):
		return self.registry.arch_size_in_bits(self.name)
	
	def dump(self, level):
		print ' ' * level, '%s (basic: size %d)' % (self.name, self.size_in_bits())



class MagpieTypeSequence(MagpieType):
	def __init__(self, registry, name, size):
		MagpieType.__init__(self, registry, name)
		self.is_marshallable = True
		self.is_value_type = True
		self.elementcount = size
		
	def size_in_bits(self):
		return self.registry.arch_size_in_bits(self.name) #* self.elementcount




class MagpieTypeConstructedMember(object):
	def __init__(self, inst, label = None, size_in_bits = None):
		self.type_inst = inst
		self.size_in_bits = size_in_bits
		self.label = label

class MagpieTypeConstructed(MagpieType, NamespaceMixIn):
	def __init__(self, registry, name):
		MagpieType.__init__(self, registry, name)
		NamespaceMixIn.__init__(self)
		# Properties peculiar to constructed types: we are a namespace, but one that
		# can be marshalled.
		self.is_marshallable = True
		#self.is_value_type = False
		# Semantics for "is_value_type" are set out in get_is_value_type, below.
		# self.members is a list of MagpieMemberType instances
		self.members = []
	
	def get_is_value_type(self):
		return False
	def set_is_value_type(self, new_val):
		# Ignore the new value - it's set up in parent constructors.
		pass
	is_value_type = property(get_is_value_type, set_is_value_type)
	
	def size_in_bits(self):
		size = self._calculate_size(self.members)
		return size

	def add_member(self, type_inst, label, size_in_bits = None):
		"""
		Add a member to the end of this type.
		"""
		member = MagpieTypeConstructedMember(type_inst, label, size_in_bits)
		self.members.append(member)

	def _calculate_size(self, member_list):
		"""
		member_list is a list of MagpieTypeConstructedMember instances
		"""
		# FIXME: This doesn't take alignment into account; it would need
		# to co-operate with the Architecture class for that.
		size_count = 0
		for member in member_list:
			if member.size_in_bits is None:
				size_count += member.type_inst.size_in_bits()
			else:
				size_count += member.size_in_bits
		return size_count

	def dump(self, level):
		print ' ' * level,
		if self.name is None:
			print "<anonymous type>", type(self),
		else:
			print '%s:' % (self.name), type(self),
		print "(size: %d bits)" % self.size_in_bits()
		for member in self.members:
			if member.size_in_bits is None:
				bits_string = ''
			else:
				bits_string = ' (%d bits)' % (member.size_in_bits)
			print ' ' * (level + 1), '%s%s: ' % (member.label, bits_string)
			member.type_inst.dump(level + 2)
			
class MagpieTypeArray(MagpieType):
	def __init__(self, registry, name, base_type_inst, dim_list):
		MagpieType.__init__(self, registry, name)
		self.is_marshallable = True
		self.is_value_type = True
		self.dim_list = dim_list
		self.elementcount = self._count_elements(dim_list)
		self.base_type_inst = base_type_inst
		#self.add_member(base_type_inst, 'type')
		
	def _count_elements(self, dim_list):
		el_count = 0
		for dim in dim_list:
			el_count += eval(str(dim))
		return el_count
	
	def size_in_bits(self):
		return self.registry.arch_size_in_bits(self.base_type_inst.name) * self.elementcount
		
	def dump(self, level):
		print ' ' * level,
		if self.name is None:
			#print 'name = ', self.base_type_inst.name, 'dim_list = ', self.dim_list
			print "<anonymous type> = %s%s" %(self.base_type_inst.name, str(self.dim_list)), type(self),
		else:
			print '%s = %s%s:' % ((self.name), (self.base_type_inst.name) , (self.dim_list)),type(self),
		print "(size: %d bits)" % self.size_in_bits()

class MagpieTypeSequence(MagpieType):
	def __init__(self, registry, name, base_type_inst, size):
		MagpieType.__init__(self, registry, name)
		self.is_marshallable = True
		self.is_value_type = True
		self.base_type_inst = base_type_inst
		self.size = size
		#self.add_member(base_type_inst, 'type')
	
	def size_as_string(self):
		return str(self.registry.arch_size_in_bits(self.base_type_inst.name)) + ' * ' + str(self.size) 
		
	def size_in_bits(self):
		return 0 #self.registry.arch_size_in_bits(self.base_type_inst.name) 
		
	def dump(self, level):
		print ' ' * level,
		if self.name is None:
			#print 'name = ', self.base_type_inst.name, 'dim_list = ', self.dim_list
			print "<anonymous type> = %s%s" %(self.base_type_inst.name, str(self.size)), type(self),
		else:
			print '%s = %s[%s]:' % ((self.name), (self.base_type_inst.name) , (self.size)),type(self),
		print "(max size: %s bits)" % self.size_as_string()

class MagpieTypeUnion(MagpieTypeConstructed):
	def size_in_bits(self):
		size = 0
		for member in self.members:
			member_size = member.type_inst.size_in_bits()
			if member_size > size:
				size = member_size
		return size

class MagpieTypeAlias(MagpieType):
	MY_ATTRIBUTES = ['target', 'dump', 'name', 'registry']
	def __init__(self, registry, name, other_type_inst):
		MagpieType.__init__(self, registry, name)
		self.target = other_type_inst
	
	def __getattribute__(self, key):
		if key in MagpieTypeAlias.MY_ATTRIBUTES:
			return MagpieType.__getattribute__(self, key)
		else:
			other_type = MagpieType.__getattribute__(self, 'target')
			return getattr(other_type, key)

	def dump(self, level):
		print ' ' * level, '%s -> %s' % (self.name, self.target.name)
		if self.target.name is None:
			# This is an anonymous type.
			self.target.dump(level + 1)

# Factories
# Special note for the constructed factories: you can either pass a list of 
# members to them here, or you can add them individuall using add_member.
# Using add_member is easier if you are walking a tree, but passing them
# here is easier if you are creating builtin types.
def namespace_factory(registry, type_name):
	"""
	registry: as per MagpieType
	type_name: as per MagpieType
	parent: the parent namespace of this one.
	"""
	return MagpieTypeNamespace(registry, type_name)

def basic_factory(registry, type_name):
	return MagpieTypeBasic(registry, type_name)

def constructed_factory(registry, type_name, members = None, type_class = None):
	"""
	if members is not None, expected is a list of (type_name, label, size_in_bits = None)
	"""
	if type_class is None:
		type_class = MagpieTypeConstructed
	new_type = type_class(registry, type_name)
	if members is not None:
		for member in members:
			type_inst = registry[member[0]]
			member_adder_args = (type_inst,) + member[1:]
			new_type.add_member(*member_adder_args)
	return new_type

def struct_factory(registry, type_name, members = None):
	return constructed_factory(registry, type_name, members)

def union_factory(registry, type_name, members = None):
	return constructed_factory(registry, type_name, members, type_class = MagpieTypeUnion)

def alias_factory(registry, type_name, real_type_name_or_inst):
	# This may fail. If so we actually need to construct the type.
	if isinstance(real_type_name_or_inst, basestring):
		real_type_inst = registry[real_type_name_or_inst]
	else:
		assert isinstance(real_type_name_or_inst, MagpieType)
		real_type_inst = real_type_name_or_inst
		
	return MagpieTypeAlias(registry, type_name, real_type_inst)
	
def array_factory(registry, type_name, base_type_inst, dim_list):
	return MagpieTypeArray(registry, type_name, base_type_inst, dim_list)
	
def sequence_factory(registry, type_name, base_type, size):
	return MagpieTypeSequence(registry, type_name, base_type, size)


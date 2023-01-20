import arch_sizes as arch_sizes_module
from magpietype import MagpieType, basic_factory, constructed_factory, struct_factory, \
	alias_factory, namespace_factory, union_factory, array_factory, sequence_factory
from builtin import create as create_builtin_types

class MagpieTypeRegistry:
	def __init__(self, architecture_name = None):
		"""
		Types are added using type factories. The preferred way to add types is
		to call the appropriate factory function through the registry (see the 
		manufacture_type() call). Therefore all factories must be registered
		with this registry (using add_factories()) before they are used.
		"""
		self.typefactories = {}
		#self.anonymous_type_prefix = '__magpie__anon'
		#self.anonymous_type_counter = 0 # Used to generate unique type names
		if architecture_name is not None:
			self.set_arch(architecture_name)
		self.add_factories(
				basic = basic_factory,
				constructed = constructed_factory,
				alias = alias_factory,
				struct = struct_factory,
				union = union_factory,
				array = array_factory,
				sequence = sequence_factory,
				namespace = namespace_factory,)
		# Now create the "root" scope: an unnamed namespace.
		self.base = self.make_type('namespace', None)
		self.current = self.base # The current namespace is the root.
	
	def set_arch(self, arch_name):
		self.arch_sizes = arch_sizes_module.construct_for_arch(arch_name)
	
	def add_type(self, type_object):
		assert type_object.name
		assert not self.current.namespace_has_key(type_object.name)
		self.current.namespace_add(type_object.name, type_object)
		if type_object.is_namespace:
			type_object.namespace_set_parent(self.current)
		#if not type_object.name:
		#	# Generate an anonymous type name.
		#	anon_name = self._generate_anon_name()
		#	self.current.namespace_add(anon_name, type_object)
		#else:
		#	self.current.namespace_add(type_object.name, type_object)
		
	def rename_type(self, newname, oldname):
		self.current.namespace_rename(newname, oldname)
	
	def add_types(self, *type_objects):
		for type_object in type_objects:
			self.add_type(type_object)

	def add_factories(self, **factories):
		self.typefactories.update(factories)
	
	def __getitem__(self, key):
		return self.current.namespace_lookup(key)
	
	def arch_size_in_bits(self, key):
		return self.arch_sizes.size_in_bits(key)
	
	def has_key(self, key):
		return self.current.namespace_has_key(key)
	
	def make_type(self, factory_name, type_name,
				*other_factory_args, **other_factory_kwargs):
		factory = self.typefactories[factory_name]
		result = factory(self, type_name, *other_factory_args, **other_factory_kwargs)
		assert isinstance(result, MagpieType)
		return result
	
	def make_type_add_type(self, factory_name, type_name, *other_factory_args,
				**other_factory_kwargs):
		new_type = self.make_type(factory_name, type_name, *other_factory_args,
				**other_factory_kwargs)
		self.add_type(new_type)
	
	def make_instance(self, type_obj, label, initialiser_string):
		return type_obj.make_instance(label, initialiser_string)
	
	def add_instance(self, type_instance):
		assert type_instance.label is not None
		self.current.namespace_add(type_instance.label, type_instance)
	
	def make_instance_add_instance(self, type_obj, label, initialiser_string):
		new_instance = self.make_instance(type_obj, label, initialiser_string)
		self.add_instance(new_instance)

	def get_types(self, name_re = None, label_re = None, attributes_dict = None,
			scope = None):
		"""
		A way to search for types:
		name_re: return types with a name matching name_re
		label_re: return types with a label matching label_re
		attributes_list: return types with appropriately-set attributes
		scope: return types in this scope only (None = base scope)
		"""
		assert scope is name_re is label_re is None
		if scope is None:
			scope = self.base
		matching_types = []
		for type_label, type_inst in scope.namespace_items():
			# Check attributes
			good_attributes = True
			for key in attributes_dict:
				inst_value = getattr(type_inst, key, None)
				if inst_value != attributes_dict[key]:
					good_attributes = False
					break
			# ... add it to the list if everything matches.
			if good_attributes:
				matching_types.append(type_inst)
		return matching_types

	def print_registry(self):
		scope = self.base
		for key, value in scope.namespace_items():
			value.dump(0)
	dump = print_registry
	
	def _generate_anon_name(self):
		name = '%s%s' % (self.anonymous_type_prefix, self.anonymous_type_counter)
		self.anonymous_type_counter += 1
		return name

def new_registry(architecture = None):
	registry = MagpieTypeRegistry(architecture)
	create_builtin_types(registry)
	return registry

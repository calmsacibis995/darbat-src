import os.path
from cStringIO import StringIO

from wsogmm import markup
from targets.shared.options import options

def reverse(data):
	for index in range(len(data)-1, -1, -1):
		yield data[index]

class DualAccess(object):
	def __getitem__(self, key):
		return getattr(self, key)
	
	def __setitem__(self, key, value):
		setattr(self, key, value)
	
	def fromdict(self, sourcedict):
		for key, value in sourcedict.items():
			self[key] = value

	def setup(self, *args, **kwargs):
		for key, value in kwargs.items():
			self[key] = value

class OutputContext(dict):
	""" Class that lets me call attributes as inst['attribute'] or
		inst.attribute freely.
	"""
	def __init__(self):
		base_scope = {'internal': DualAccess(),
			'file': DualAccess(),
			'interface': DualAccess(),
			'function': DualAccess(),
			'current': DualAccess(),
		}
		self._unlock()
		self.scopes = [base_scope]
		self._lock()

	def __setitem__(self, key, value):
		self._unlock()
		#print "setitem", key, value
		self.scopes[-1][key] = value
		self._lock()
	
	def __getitem__(self, key):
		self._unlock()
		for scope in reverse(self.scopes):
			if scope.has_key(key):
				self._lock()
				#print "getitem locked returning for key", key
				return scope[key]
		self._lock()
		#print "getitem keyerror for key", key
		raise KeyError(key)
	
	def scope_enter(self):
		self._unlock()
		self.scopes.append({})
		self._lock()
	
	def scope_exit(self):
		self._unlock()
		self.scopes.pop()
		self._lock()

	def get(self, key, default = None):
		try:
			return self.__getattr__(key)
		except KeyError:
			return default
	
	def __delitem__(self, key):
		del self.__dict__[key]
	
	def __setattr__(self, key, value):
		if self.__dict__['locked'] is True:
			raise AttributeError("setattr not allowed")
		else:
			#print "setattr", key, value
			self.__dict__[key] = value
	
	def __getattr__(self, key):
		if self.__dict__['locked'] is True:
			#print "getattr locked returning for key", key
			return self.__getitem__(key)
		else:
			#print "getattr unlocked returning for key", key
			return self.__dict__[key]
	
	def dump(self):
		self._unlock()
		print self.scopes[-1]
		self._lock()

	# execute and evaluate:
	# Ideally we would like to pass self as the "dict" argument, 
	# but eval() is evil and doesn't respect our attribute access
	# methods. So we pass the internal dictionaries here. This
	# also restricts code to two scopes. 
	def execute(self, code_str):
		self._unlock()
		local_scope = self.scopes[-1]
		global_scope = self.scopes[0]
		self._lock()
		#print 'code_str ', code_str, ' END'
		#print local_scope
		#print global_scope
		try:
			exec code_str in global_scope, local_scope
		except:
			print code_str
			raise
	
	def evaluate(self, code_str):
		self._unlock()
		local_scope = self.scopes[-1]
		global_scope = self.scopes[0]
		self._lock()
		return eval(code_str, global_scope, local_scope)
	
	def _lock(self):
		self.__dict__['locked'] = True

	def _unlock(self):
		self.__dict__['locked'] = False
	
	def __str__(self):
		return "<OutputContext obj. Scopes are %s>" % (self.__dict__['scopes'])
	
class BaseOutput(object):
	def __init__(self):
		# Calculate path to templates
		self.context = OutputContext()
		self.context['call_hook'] = self.call_hook
		self.context.internal.path_to_templates = options['template_base']
		self.hook_function = None
		self.output = StringIO()
	
	def fromtemplate(self, template_filename, **kwargs):
		template_fullname = os.path.join(
				self.context.internal.path_to_templates, template_filename)
		self.context.current.fromdict(kwargs)
		# Could cache these, but doubt it will become a problem.
		markup(template_fullname, self.output, self.context)
	
	def getvalue(self):
		return self.output.getvalue()
	
	def set_hook_object(self, hook_object):
		self.hook_object = hook_object
	
	def call_hook(self, func_name, *args, **kwargs):
		some_callable = getattr(self.hook_object, func_name)
		some_callable(*args, **kwargs)

class GenericOutput(BaseOutput):
	def __init__(self):
		BaseOutput.__init__(self)
	
	def go(self, template_filename):
		self.fromtemplate(template_filename)


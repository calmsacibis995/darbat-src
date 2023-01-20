"""
Basic cache.
"""
import os, sha, cPickle, errno, atexit
from targets.shared.options import options

import helper

class NotInCacheError(Exception):
	pass

class Cache(object):
	"""
	This is a cache.

	It works by storing pickled objects in a special directory, normally $HOME/.magpie/cache.

	Cache validity is assured through the use of SHA-1 hashes of files. 
	Hashes and cache keys are mapped to files through a "directory", which is a pickled 
	dictionary. 
	"""
	def __init__(self):
		# We use a lazy initialisation because we rely on helper.get_magpie_dir, which 
		# in turn relies on the global options setting, but that isn't setup until after
		# the cache singleton is created.
		self.directory_loaded = False
		self.initialised = False
	
	def _initialise(self):
		if options['cache_enabled'] and not self.initialised:
			self.cache_dir = helper.get_magpie_dir('cache_dir', options)
			self._setup_files()
			self._load_directory()
			self.initialised = True
		
	def clear(self):
		self.directory = {}

	def make_key(self, name, data):
		"""
		Return a cache key given name and data.
		
		"name" may be anything which identifies this data; if it is a filename
		then you should normalise it first using os.path.abspath().

		"data" is anything that can be passed to sha.new(), such as a Python
		string.

		Nothing besides this class should need to know the format of cache keys, 
		because they could change in the future. They are currently of the form
		(name, <hash-str>), where hash-str is the binary form of an SHA hash of
		the input data.
		"""
		datahash = sha.new(data).digest()
		return (name, datahash)

	def load(self, cache_key):
		"""
		Returns the cached object identified by cache_key. 

		Raises NotInCacheError if the object does not exist.
		"""
		self._initialise()
		name, data_hash = cache_key
		if options['cache_enabled'] is False:
			raise NotInCacheError(cache_key)
		# Assume the directory is up-to-date:
		try:
			pathname, in_hash = self.directory[name]
		except KeyError:
			raise NotInCacheError(name)
		if in_hash != data_hash:
			# Cache entry is invalid because input has changed.
			raise NotInCacheError(name)
		try:
			handle = file(pathname, 'rb')
		except IOError, e:
			if e.errno == errno.ENOENT:
				print "Magpie: Warning: Cache directory inconsistent."
				raise NotInCacheError(name)
			else:
				raise
		data_out = cPickle.load(handle)
		handle.close()
		return data_out
	
	def store(self, cache_key, data_out):
		"""
		Stores data_out in the cache.
		"""
		self._initialise()
		if options['cache_enabled'] is True:
			pathname = self._create_cache_filename(cache_key)
			# ... write the object to the cache
			handle = file(pathname, 'wb')
			cPickle.dump(data_out, handle)
			handle.close()

			# ... and update the directory.
			name, data_hash = cache_key
			self.directory[name] = (pathname, data_hash)

	def _setup_files(self):
		try:
			os.mkdir(self.cache_dir)
		except OSError, e:
			if e.errno != errno.EEXIST:
				raise
		self.directory_filename = os.path.join(self.cache_dir, "directory")
	
	def _load_directory(self):
		"""
		Attempt to load the cache directory. If the cache doesn't exist, create a
		new, empty cache.
		"""
		create_new = False
		try:
			handle = file(self.directory_filename, 'rb')
		except IOError, e:
			if e.errno == errno.ENOENT: # No such file or directory
				create_new = True
			else:
				raise
		if create_new:
			self.directory = {}
		else:
			try:
				self.directory = cPickle.load(handle)
			except:
				print "Magpie: Warning: Cache directory corrupt."
				self.directory = {}
			handle.close()
		self.directory_loaded = True

	def _save_directory(self):
		"""
		Save the cache directory.
		"""
		if self.directory_loaded:
			handle = file(self.directory_filename, "wb")
			cPickle.dump(self.directory, handle)
			handle.close()

	def _create_cache_filename(self, cache_key):
		"""
		Create a filename for storing cached data.
		"""
		# FIXME: This is UNIX-specific right now. A better
		# version would remove all non-alphanumeric characters
		name, data_hash = cache_key
		filename = name.replace(os.path.sep, '_')
		pathname = os.path.join(self.cache_dir, filename)

		return pathname

cache = Cache() # singleton cache
atexit.register(cache._save_directory)

class CachedTransformableFile(object):
	def __init__(self, filename, input_data):
		filename = os.path.abspath(filename)
		self.cache_key = cache.make_key(filename, input_data)

	def load(self):
		return cache.load(self.cache_key)

	def save(self, output_data):
		cache.store(self.cache_key, output_data)


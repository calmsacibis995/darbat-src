import os
import glob
from cStringIO import StringIO
from SCons.Environment import Environment

checklib_include = '#libs/check/src'

def make_abs_path(some_path):
	if not some_path.startswith('#'):
		return '#' + some_path
	return some_path

def markup(template, output, environment):
	"""
	This function reads a template. The template format is:
	{{python code:}} execute "python code"
	{{?python code}}: evaluate "python code" and replace the whole thing with the result.
	{{
	python code
	...
	}}: execute "python code". 
	"""		
	environment['out'] = output
	
	window_start = 0
	window_end = 0
	eof = len(template)

	STATE_NORMAL = 0
	STATE_EXECCODE = 1
	STATE_EVALCODE = 2
	STATE_LOOP = 3
	STATE_IF = 4

	state = STATE_NORMAL

	while window_start < eof:
		if state == STATE_NORMAL:
			window_end = template.find('{{', window_start)
			if window_end == -1:
				window_end = eof
			output.write(template[window_start:window_end])
			window_start = window_end
			if template[window_start:window_start + 9] == '{{ABORT}}':
				return False
			if template[window_start:window_start + 4] == '{{if':
				state = STATE_IF
				window_start += 4
			elif template[window_start:window_start + 3] == '{{?':
				state = STATE_EVALCODE
				window_start += 3
			elif template[window_start:window_start + 3] == '{{*':
				state = STATE_LOOP
				window_start += 3
			elif template[window_start:window_start + 2] == '{{':
				state = STATE_EXECCODE
				window_start += 2
		elif state == STATE_EVALCODE:
			window_end = template.find('}}', window_start)
			if window_end != -1:
				code = template[window_start:window_end]
				output.write(str(eval(code, environment)))
				window_start = window_end + 2
			state = STATE_NORMAL
		elif state == STATE_EXECCODE:
			window_end = template.find('}}', window_start)
			if window_end != -1:
				code = template[window_start:window_end]
				exec code in environment
				window_start = window_end + 2
			state = STATE_NORMAL
		elif state == STATE_IF:
			window_end = template.find('fi}}', window_start)
			ifcode_end = template.find(':', window_start)
			code = template[window_start:ifcode_end]
			if eval(code, environment):
				result = markup(template[ifcode_end+1:window_end], output, environment)
				if result is False:
					return False
			window_start = window_end + 4
			state = STATE_NORMAL
		elif state == STATE_LOOP:
			window_end = template.find('*}}', window_start)
			loopcode = template[window_start:window_end]
			for item in environment['LOOP']:
				environment['LOOPITEM'] = item
				result = markup(loopcode, output, environment)
				if result is False:
					return False
			window_start = window_end + 3
			state = STATE_NORMAL
	return True
	
# The environment for individual tests.
class TestEnvironment(Environment):
	def __init__(self, *args, **kwargs):
		Environment.__init__(self, *args, **kwargs)
		# Our personal list of things to be tested.
		self.test_libs = []
		self.test_libs_includes = []
		self.test_libs_path = []
		self.check_lib = ['check']
		self.check_lib_includes = [checklib_include]
		self.check_lib_path = ['#build/test/check']
		self.current_build_dir = None
		# Custom builder for templating language
		def build_from_template(target, source, env, for_signature = None):
			assert len(target) == 1
			assert len(source) == 1
			target = str(target[0])
			source = str(source[0])
			#print "Build template target is", target, "source is", source, "env is", env
			template = file(source).read()
			output = StringIO()
			environment = {
				'include_files' : ['%s.h' % (libname) for libname in self.test_libs],
				'suite_build_functions': ['make_%s_suite' % (libname) for libname in self.test_libs],
			}
			result = markup(template, output, environment)
			assert result is True
			file(target, 'wb').write(output.getvalue())

		template_builder = self.Builder(action = build_from_template)
		self['BUILDERS']['Templated'] = template_builder

	def TestLibrary(self, test_lib_name, test_lib_dir, sources):
		# And now call StaticLibrary.
		# Find suitable includess...
		assert test_lib_dir.endswith(os.path.sep)
		if self.current_build_dir is None:
			# Haven't set up the test environment; assume we're not testing.
			return None
		include_dir = 'include'
		tester_include_dir = 'test'
		all_includes = [checklib_include, include_dir]
		# Collect include dirs here so we can use them in MainTestProgram below.
		self.test_libs_includes.extend([make_abs_path(os.path.join(test_lib_dir, include_dir)),
			make_abs_path(os.path.join(test_lib_dir, tester_include_dir))])
		# Find suitable source files...
		all_sources = []
		for source in sources:
			all_sources.extend(self.src_glob(source))
		#print "StaticLibrary", test_lib_name, all_sources, all_includes
		result = self.StaticLibrary(test_lib_name, all_sources, CPPPATH=all_includes)
		assert type(result) is list
		self.test_libs.append(test_lib_name)
		self.test_libs_path.append(os.path.join(self.current_build_dir))
		self.current_build_dir = None
	
	def TemplatedMainTestProgram(self, target, sources):
		# All the libraries
		#print "Program", target, sources, \
		#	self.test_libs, self.test_libs_includes, self.test_libs_path
		result = self.Templated(target, sources,
			LIBS = self.check_lib + self.test_libs,
			CPPPATH = self.check_lib_includes + self.test_libs_includes,
			LIBPATH = self.check_lib_path + self.test_libs_path)
		for lib in self.test_libs:
			self.Depends(result, self.Value(lib))
		#print "Program result is", result
		return result
	
	def MainTestProgram(self, target, sources):
		result = self.Program(target, sources,
			LIBS = self.check_lib + self.test_libs,
			CPPPATH = self.check_lib_includes + self.test_libs_includes,
			LIBPATH = self.check_lib_path + self.test_libs_path)
		return result

	def SConscript(self, *args, **kwargs):
		self.current_build_dir = kwargs.get('build_dir')
		return Environment.SConscript(self, *args, **kwargs)
		

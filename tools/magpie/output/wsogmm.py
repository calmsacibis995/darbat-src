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

"""wsogmm, used in python-on-mungi, tasks database, and regression tester
as well as here.
"""

import re, sys
import os.path
from cStringIO import StringIO
#NB: Dparser doesn't work with psyco for some reason. No doubt because dparser is unspeakably evil.
#try:
#	import psyco
#except ImportError:
#	pass
#else:
#	psyco.full()

def sstarts(s, pos, compare):
	return s[pos : pos + len(compare)] == compare

class Markup:
	"""
	This function reads a template. The template format is:
	/*-python code-*/: execute "python code"
	/*-?python code-*/: evaluate "python code" and replace the whole thing with the result.
	/*-
	python code
	...
	-*/: execute "python code". 
	/*LOOP <somelist>*/ ... /*ENDLOOP*/ For LOOPITEM in <somelist> evaluate ...
	/*-if condition*/ template /*fi-*/: Evaluate "template" if eval(condition)
	/*-ABORT-*/: return immediately.
	"""		
	def __init__(self, output, environment):
		# TEMPLATES_INDICATORS is a list of (starter, finisher, func) in whatever order
		# is most natural. There are no special requirements
		self.output = output
		self.environment = environment

		TEMPLATES_INDICATORS = [ ('/*-', '-*/', self.t_code),
			('{*-', '-*}', self.t_code),
			('/*-if', '/*fi-*/', self.t_if),
			('{*-if', '{*fi-*}', self.t_if),
			('/*-?', '-*/', self.t_eval),
			('{*-?', '-*}', self.t_eval),
			('/*LOOP', '/*ENDLOOP*/', self.t_loop),
			('{*LOOP', '{*ENDLOOP*}', self.t_loop),
		]
		# MAGIC_SEPARATORS separate antecedent and consequent in "if", and
		# separate iterator and body in "loop"
		self.MAGIC_SEPARATORS = ('*/', '*}')
		# TEMPLATE_STARTERS is a list of (starter, func) sorted by length of starter.
		self.TEMPLATE_STARTERS = [(ti[0], ti[2]) for ti in TEMPLATES_INDICATORS]
		self.TEMPLATE_STARTERS.sort(lambda x, y: cmp(len(x[0]), len(y[0])))
		self.TEMPLATE_STARTERS.reverse()
		# TEMPLATE_FINISHERS is a list of (finisher, func) sorted by length of finisher
		self.TEMPLATE_FINISHERS = [(ti[1], ti[2]) for ti in TEMPLATES_INDICATORS]
		self.TEMPLATE_FINISHERS.sort(lambda x, y: cmp(len(x[0]), len(y[0])))
		self.TEMPLATE_FINISHERS.reverse()

		self.code_gen = CodeGen()

	def t_code(self, tmpl_piece):
		self.code_gen.output_code(tmpl_piece)

	def t_if(self, tmpl_piece):
		antecedent, consequent = self.split_closest(tmpl_piece, self.MAGIC_SEPARATORS)
		self.code_gen.output_if(antecedent)
		self._compile(consequent)

	def t_eval(self, tmpl_piece):
		self.code_gen.output_eval(tmpl_piece)

	def t_loop(self, tmpl_piece):
		arguments, body = self.split_closest(tmpl_piece, self.MAGIC_SEPARATORS)
		try:
			iterator_name, iterable = arguments.split('=', 1)
		except ValueError: # No iterator names supplied
			iterator_name = 'LOOPITEM'
			iterable = arguments
		self.code_gen.output_loop(iterator_name, iterable)
		self._compile(body)
	
	def split_closest(self, haystack, needle_list):
		pos = 0
		while pos < len(haystack):
			for needle in needle_list:
				if sstarts(haystack, pos, needle):
					return haystack.split(needle, 1)
			pos += 1
		raise Exception("No closest to split!")

	def find_same_level(self, haystack, indicator_func, startpos):
		stack = 1 # We are called *after* the starter.
		pos = startpos
		#print "fsl, startpos is", startpos, 'indicator func is', indicator_func
		while pos < len(haystack):
			for candidate_starter, candidate_func in self.TEMPLATE_STARTERS:
				if sstarts(haystack, pos, candidate_starter):
					if candidate_func == indicator_func:
						# New level down.
						stack += 1
			for candidate_finisher, candidate_func in self.TEMPLATE_FINISHERS:
				if sstarts(haystack, pos, candidate_finisher):
					if candidate_func == indicator_func:
						stack -= 1
						if stack == 0:
							#print "returning new pos of", pos
							return pos, len(candidate_finisher)
			pos += 1
		raise Exception("No end found (start was %s, pos %d in template)" % (haystack[startpos:startpos+160], startpos))
	
	def position_starts_template(self, haystack, pos):
		# return function, length of starter
		for candidate_starter, candidate_func in self.TEMPLATE_STARTERS:
			if sstarts(haystack, pos, candidate_starter):
				# Found one...
				return candidate_func, len(candidate_starter)
		return None, 0
	
	def _compile(self, template):
		window_start = 0
		window_end = 0
		eof = len(template)

		self.code_gen.start()

		while window_start < eof:
			handler_func, skipstart = self.position_starts_template(template, window_end)
			while handler_func is None and window_end < eof:
				window_end += 1
				handler_func, skipstart = self.position_starts_template(template, window_end)
			# Now window_start points to just past the end of the previous template
			# and window_end points at the first character of the next template.
			#print "Test 1: window_start is", window_start, "window_end is", window_end
			if window_start != window_end:
				self.code_gen.output_literal(template[window_start:window_end])
			if window_end == eof:
				break # End of file
			window_start = window_end
			window_end, skipend = self.find_same_level(template, handler_func, window_end + 1)
			# Now window_start points to the beginning of the template and
			# window_end points to the first character marking the end of the template.
			#print "Test 2: window_start is", window_start, "window_end is", window_end
			handler_output = handler_func \
					(template[window_start + skipstart : window_end])
			window_start = window_end = window_end + skipend

		self.code_gen.stop()

		return True

	def _run_template(self, template):
		#print 'in  ', template
		self._compile(template)

		python_code = self.code_gen.get()
		self.environment.execute(python_code)

	def internal_write_fn(self, data):
		self.output.write(data)

	def internal_run_fn(self, template_filename):
		if template_filename is not None:
			full_filename = os.path.join(self.environment.internal.path_to_templates, template_filename)
			child_template = file(full_filename).read()
			#environment.scope_enter()
			try:
				self.go(child_template, self.output, self.environment)
			except:
				print "Inner template filename was", template_filename
				raise
			#environment.scope_exit()

	def internal_markup_fn(self, template_fragment):
		self.go(template_fragment, self.output, self.environment)

	def go(cls, template, output, environment):
		inst = cls(output, environment)
		for key, value in [
				('out', output),
				('_markup', inst.internal_markup_fn),
				('run', inst.internal_run_fn),
				('_write', inst.internal_write_fn)
			]:
			if key not in environment:
				environment[key] = value
		inst._run_template(template)
	go = classmethod(go)

class CodeGen:
	def __init__(self):
		self.clear()
	
	def clear(self):
		self.loc = []
		self.indent_level = None
	
	def start(self):
		if self.indent_level is None:
			self.indent_level = 0
		else:
			self.indent_level += 1
	
	def stop(self):
		self.indent_level -= 1
		if self.indent_level == -1:
			self.indent_level = None
	
	def get(self):
		return '\n'.join(self.loc)

	def output_code(self, code):
		code_lines = code.split('\n')
		self._add_code_lines(code_lines)
	
	def output_if(self, antecedent):
		self._add_code('if %s:' % (antecedent))
	
	def output_eval(self, code):
		self._add_code("_write(str(%s))" % (code))
	
	def output_loop(self, iter_name, iterable):
		self._add_code('for %s in %s:' % (iter_name, iterable))
	
	def output_literal(self, data):
		self._add_code("_write(%s)" % (repr(data)))
	
	def _add_code(self, code_line):
		self.loc.append('%s%s' % ('\t' * self.indent_level, code_line))
	
	def _add_code_lines(self, code_lines):
		for line in code_lines:
			self._add_code(line)

def safe_markup(template, output, environment):
	try:
		return Markup.go(template, output, environment)
		#return unsafe_markup_v2(template, output, environment)
	except:
		print "TEMPLATE ERROR"
		print "Template was:", template
		raise

def safe_markup_fromfile(template_filename, output, environment):
	template = file(template_filename, 'rb').read()
	try:
		return Markup.go(template, output, environment)
	except:
		print "TEMPLATE ERROR"
		print "Template filename was:", template_filename
		raise

markup = safe_markup_fromfile



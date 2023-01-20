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

import unittest
import optparse
import popen2
import shutil
import os
import sys
import re


PATH_TO_EXPECTED_OUTPUT = 'test/expected_output/'
FAILED_OUTPUT_PREFIX = 'test.fail.'

WORD_SIZES = ['32', '64']
PLATFORMS = ['generic', 'generic_biguuid', 'arm_biguuid']
OUTPUT_TYPES = ['c', 's', 't']  # Client, service, service template
STANDARD_CPP = 'arm-linux-cpp'

HACK_PREFIX = '../../'

CMD_PREFIX = "./magpidl4.py"
CMD_POSTFIX_TMPL = '-%(output_type)s %(input_filename)s -h - -i %(interface)s -fno-use-malloc -w %(word_size)s -p %(platform)s --with-cpp=%(selected_cpp)s'

INCLUDE_LIBS_IGUANA = """--nfdonly-ugly-includepath-hack=%s -I/usr/local/include -Ilibs/templates/include -Ilibs/l4/include -Ilibs/c/include -Ilibs/c/arch_include/arm -Ilibs/iguana/include -Ibuild/ig_server/libs/iguana/include -Ilibs/iguana/include -Ilibs/elf/include -Ilibs/hash/include -Ilibs/bit_fl/include -Ilibs/ll/include -Ilibs/circular_buffer/include -Ilibs/b_plus_tree/include -Ilibs/b_plus_tree/include -Ilibs/range_fl/include -Ilibs/l4e/include"""

INCLUDE_LIBS_TEST = "-Itest/input"

STANDARD_CONFORM_REGEXES = [
	(r'Generated by Magpie \d+, .*', 'Generated by Magpie VERSION_REMOVED'),
]

# Automatically update test results.
# Set to True if you are 100% CONFIDENT that your changes are correct
ALWAYS_UPDATE_NEW = False
# PS: 100% CONFIDENT

# Automatically update test results if the file is new.
ALWAYS_UPDATE_IF_NOT_EXISTS = False

if ALWAYS_UPDATE_NEW is True:
	print "WARNING! You are going to UPDATE all tests even if they fail."
	print "If you don't want this, set ALWAYS_UPDATE_NEW in test/test.py to False."
	print "Type 'yes' to continue."
	yes = raw_input()
	if yes != 'yes':
		sys.exit(0)

if ALWAYS_UPDATE_IF_NOT_EXISTS is True:
	print "WARNING! You are going to UPDATE all tests when the target does not exist.."
	print "Type 'yes' to continue."
	yes = raw_input()
	if yes != 'yes':
		sys.exit(0)

class FullTests:
	def popen_run(self, cmd):
		""" Run 'cmd', return the output. """
		child_stdout_stderr, child_stdin = popen2.popen4(cmd)
		child_stdin.close()
		result = child_stdout_stderr.read()
		return result
	
	def regex_process(self, regexlist, text):
		for matcher, replacement_string in regexlist:
			text = re.sub(matcher, replacement_string, text)
		return text
	
	def strip_blank_lines(self, line_list):
		if line_list is not None:
			return [line for line in line_list if line.strip() != '']
		else:
			return None

	def strip_whitespace(self, line_list):
		if line_list is None:
			return None
		else:
			return [re.sub('[ \t\n]', '', line) for line in line_list if line.strip() != '']

	def front_to_back(self, cmdline, expected_output_name,
			conform_regexes = STANDARD_CONFORM_REGEXES):
		#print "front to back", cmdline
		run_again = True
		while run_again:
			run_again = False
			sys.stdout.write('-')
			sys.stdout.flush()
			new_output = self.popen_run(cmdline)
			new_output = self.regex_process(conform_regexes, new_output)
			new_output = new_output.split('\n')
			
			full_expected_output_name = os.path.join(PATH_TO_EXPECTED_OUTPUT, expected_output_name)
			if os.path.exists(full_expected_output_name):
				expected_output = file(full_expected_output_name).read()
				expected_output = expected_output.split('\n')
			else:
				expected_output = None

			stripped_expected = self.strip_whitespace(expected_output)
			stripped_new = self.strip_whitespace(new_output)
			panic = False
			if stripped_expected != stripped_new:
				panic = True
				# Write this output somewhere.
				failed_output_name = FAILED_OUTPUT_PREFIX + expected_output_name
				file(failed_output_name, 'w').write('\n'.join(new_output))
				print "front to back", cmdline
				print '******'
				print "Files differ: %s and %s" % (full_expected_output_name, failed_output_name)
				print "To diff: diff -Bwu %s %s" % (full_expected_output_name, failed_output_name)
				print "To update new: cp %s %s" % (failed_output_name, full_expected_output_name)
				print '******'
				if TEST_NONINTERACTIVE is False:
					if not os.path.exists(full_expected_output_name):
						print "**** CREATED A NEW FILE ****"
						os.system('cat %s | less' % (failed_output_name))
					else:
						os.system('diff -Bwu %s %s | less' % (full_expected_output_name, failed_output_name))
					update = raw_input('Type y to auto-update, s to skip, r to run again >')
					if update == 'y':
						print 'Updating.'
						panic = False
						shutil.copyfile(failed_output_name, full_expected_output_name)
					elif update == 'r':
						panic = False
						run_again = True
					elif update == 's':
						pass
					else:
						print 'Not updating.'
				if ALWAYS_UPDATE_NEW is True and not run_again:
					panic = False
					print "* Copying as specified in hack."
					shutil.copyfile(failed_output_name, full_expected_output_name)
				if ALWAYS_UPDATE_IF_NOT_EXISTS is True and not os.path.exists(full_expected_output_name) and not run_again:
					panic = False
					print "* New file; updating it"
					shutil.copyfile(failed_output_name, full_expected_output_name)
		if panic is True:
			self.assertEqual(stripped_expected, stripped_new)
		
	def front_to_back_multiple(self, input_filename, include_libs_type = None,
			conform_regexes = STANDARD_CONFORM_REGEXES, selected_cpp = STANDARD_CPP,
			interface = 'v4'):
		cmd_head = CMD_PREFIX
		if include_libs_type is None or include_libs_type == 'TEST':
			include_libs = INCLUDE_LIBS_TEST
			include_libs_type = 'TEST'
		elif include_libs_type == 'IGUANA':
			include_libs = INCLUDE_LIBS_IGUANA % (TEST_IGUANA_PREFIX)
		cmd_head += ' %s' % (include_libs)
		use_include_libs_text = 'includes_%s' % (include_libs_type)
		for output_type in OUTPUT_TYPES:
			for word_size in WORD_SIZES:
				for platform in PLATFORMS:
					cmd_postfix = CMD_POSTFIX_TMPL % locals()
					cmd = '%s %s' % (cmd_head, cmd_postfix)
					output_filename = 'test_%s_%s_%s_%s_%s_%s_%s' % (os.path.basename(input_filename), output_type, interface, word_size, platform, use_include_libs_text, selected_cpp)
					self.front_to_back(cmd, output_filename, conform_regexes)

class KengeIguana(unittest.TestCase, FullTests):
	def test_full_iguana(self):
		self.front_to_back_multiple('test/input/iguana.idl4', include_libs_type = 'IGUANA',
				interface = 'v4nicta')

	def test_full_mips_cpp(self):
		self.front_to_back_multiple('test/input/iguana.idl4', include_libs_type = 'IGUANA',
				selected_cpp = 'mips64-elf-cpp', interface = 'v4nicta')
	
	def test_full_broken_cpp(self):
		self.front_to_back_multiple('test/input/iguana.idl4', include_libs_type = 'IGUANA', selected_cpp = 'nonexistent-cpp', interface = 'v4nicta')
	
class BlackboxGeneric(unittest.TestCase, FullTests):

	# Only use setUp() and tearDown() if necessary

	#def setUp(self):
	#	... code to execute in preparation for tests ...

	#def tearDown(self):
	#	... code to execute to clean up after tests ...
	
	
	#def test_structsimple(self):
	#	self.front_to_back_multiple('test/input/struct.idl')

	def test_inheritance(self):
		self.front_to_back_multiple('test/input/inheritance.idl4')

	def test_no_include_dirs(self):
		self.front_to_back_multiple('test/input/simple.idl4')

	def test_char_ptr_arg(self):
		self.front_to_back_multiple('test/input/char_ptr_arg.idl4')

	def test_char_ptr_arg_2(self):
		self.front_to_back_multiple('test/input/char_ptr_arg_2.idl4')

	def test_struct_params(self):
		self.front_to_back_multiple('test/input/struct_params.idl4')

	def test_diverse_types(self):
		self.front_to_back_multiple('test/input/diverse_types.idl4')

#	def test_diverse_types_2(self):
#		self.front_to_back_multiple('test/input/diverse_types_2.idl')

	def test_const_propagation(self):
		self.front_to_back_multiple('test/input/const_propagation.idl4')

	def test_const_propagation_fromheaders(self):
		self.front_to_back_multiple('test/input/const_propagation_fromheaders.idl4')
	
	def test_default_output(self):
		self.front_to_back('./magpidl4.py test/input/simple.idl4', 'test_default_output')
	
	def test_bitfields(self):
		self.front_to_back_multiple('test/input/bitfields.idl4')
	
	def test_ppc64asm(self):
		self.front_to_back('./magpidl4.py test/input/ppc64asm.idl4 -I test/input', 'test_ppc64_asm')
	
	def test_annotations(self):
		self.front_to_back('./magpie.py --target=corba_tester --output=annotations test/input/annotations.idl', 'test_function_annotations')
	
	def test_generic_iface(self):
		# Make sure all the command-line options work.
		self.front_to_back('./magpie.py --help', 'generic_iface_cmdline_help')
		self.front_to_back('./magpie.py --list-targets', 'generic_iface_cmdline_list_targets')
		self.front_to_back('./magpie.py --target=corba_tester --list-outputs', 'generic_iface_cmdline_list_outputs')
		self.front_to_back('./magpie.py --target=corba_tester --output=annotations --templates=test/test_templates test/input/annotations.idl', 'generic_iface_cmdline_templates_dir')

	
class MagpieTestResults(unittest.TestResult):
	def startTest(self, test):
		print test
	
	def stopTest(self, test):
		print " Finished."

def _hack_add_options(options):
	__builtins__.TEST_IGUANA_PREFIX = options.iguana_path # FIXME: giant hack
	__builtins__.TEST_NONINTERACTIVE = options.noninteractive

def add_all_tests(options, suite):
	print 'Adding test suite "BlackboxGeneric"'
	suite.addTest(unittest.makeSuite(BlackboxGeneric))
	if options.test_iguana:
		print 'Adding test suite "Iguana"'
		suite.addTest(unittest.makeSuite(KengeIguana))

def add_specified_test(options, suite):
	for testcase in (BlackboxGeneric, KengeIguana):
		func = getattr(testcase, options.testonly, None)
		if func:
			suite.addTest(testcase(options.testonly))
			break

def main():
	parser = optparse.OptionParser()
	parser.add_option('-i', '--test-iguana', dest = 'test_iguana', action = 'store_true', default = False)
	parser.add_option('--iguana-path', dest = 'iguana_path', action = 'store', default = HACK_PREFIX)
	parser.add_option('--test', dest = 'testonly', action = 'store', default = None)
	parser.add_option('--noninteractive', dest = 'noninteractive', action = 'store_true', default = False)
	options, args = parser.parse_args()
	
	suite = unittest.TestSuite()
	if options.testonly is None:
		add_all_tests(options, suite)
	else:
		add_specified_test(options, suite)
	_hack_add_options(options)

	results = MagpieTestResults()
	suite.run(results)
	for error in results.errors:
		print '\n'.join(error[1:])
	print "Errors:", len(results.errors)
	print "Failures:", len(results.failures)

if __name__ == '__main__':
	main()

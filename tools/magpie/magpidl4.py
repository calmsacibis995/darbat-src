#!/usr/bin/env python
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
import helper
helper.sanity_checks()

# And now for our feature attraction...
import os.path, sys, traceback

from optparse import OptionParser
from helper import VERSION_STRING
from targets.shared.target import Target
from targets.shared.options import options

# Basic IDL parser.
# Parse IDL4-style options and send them along in a native format.

class IDL4OptionParser(object):
	def setup(self):
		# Don't include -h in the parser object because IDL4 uses -h for something else
		parser = OptionParser(add_help_option=False,
				usage = "%s [flags] <idl file>" % (sys.argv[0]))
		parser.add_option('-p', '--platform', type="string", dest='platform',
			help="specify platform", default="generic")
		parser.add_option('-m', '--mapping', type="string", dest='mapping',
			help="specify mapping", default="c")
		parser.add_option('-i', '--interface', type="string", dest='interface',
			help="specify interface (v4, v4nicta)", default="v4nicta")
		parser.add_option('-s', '--service-stubs', action="store_const",
			dest="output_type", const='service', help="generate service stubs")
		parser.add_option('-c', '--client-stubs', action="store_const",
			dest="output_type", const='client', help="generate client stubs",
			default = 'client')
		parser.add_option('-t', '--service-template', action="store_const",
			dest="output_type", const='servicetemplate', help="generate service template")
		parser.add_option('-w', '--word-size', type="int", dest="word_size",
			help="specify word size in bits (32, 64)", default=32)
		parser.add_option('--with-cpp', type="string", dest="cpp",
			help="specify the location of the C preprocessor", default="cpp")
		parser.add_option('-I', type="string", action="append", dest="include_dirs",
			help="specify additional include directories", default=[])
		parser.add_option('-h', type="string", dest="dest",
			help="specify location of destination header file")
		#parser.add_option('-o', type="string", dest="dest",
		#	help="specify location of destination header file")
		parser.add_option('-f', type="string", action="append", dest="compilerflags",
			help="parameters to pass to the IDL compiler")
		parser.add_option('--nfdonly-ugly-includepath-hack', type="string",
			help="nfd's magic to convert relative to absolute paths; DO NOT USE",
			dest="ugly_includepath_hack")
		parser.add_option('-g', type="string", dest="generator",
			help="specify generator (idl4, igdebug)", default="idl4")
		parser.add_option('--version', action='store_true', dest='print_version',
				help = 'Display the current Magpie version ("%s") and exit' % (VERSION_STRING))
		parser.add_option('--help', action='help')
		parser.add_option('--magpie-use-cache', action="store_true", dest='cache_enabled',
				default = False, help = 'Determine whether Magpie should use its cache.')
		parser.add_option('--magpie-cache-dir', type='string', dest='cache_dir',
				help = "Specify the cache directory (default is $HOME/.magpie/cache on unix)")
		parser.add_option('--cpp-flags', type='string', dest='cpp_flags', default = '-P',
				help = "Specify flags to the C preprocessor")
		self.parser = parser

	def parse_options(self):
		self.options, self.args = self.parser.parse_args()
		return self.options, self.args
	
	def print_help(self):
		self.parser.print_help()

	def get_target(self):
		# Convert our platform and generator options into a "target" for the real 
		# Magpie options.
		# Magpie supports target inheritance, which is why the values here
		# are lists.
		TARGET_MAP = {
			('idl4', 'generic'): ['idl4_generic_l4v4'],
			('idl4', 'generic_biguuid'): ['idl4_generic_l4v4', 'idl4_generic_biguuid_l4v4'],
			('idl4', 'arm_biguuid'): ['idl4_generic_l4v4', 'idl4_generic_biguuid_l4v4', 'idl4_arm_biguuid_l4v4'],
		}
		target = TARGET_MAP[(self.options.generator, self.options.platform)]
		# Add interface modifier here.
		if self.options.interface == 'v4':
			pass
		elif self.options.interface == 'v4nicta':
			target.append('v4nicta_modifier')
		else:
			raise Exception("Unknown interface '%s'" % (self.options.interface))
		if self.options.mapping == 'c++':
			target.append('cplusplus_modifier')
		return target
	
	def set_options(self):
		options.set_uninitialised()
		#print idl4style_options
		if self.options.dest:
			options['output_filename'] = self.options.dest
		options['target'] = self.get_target()
		options['c_preprocessor'] = self.options.cpp


		# For ADS compiler, must use armcc to compile .h as a C file.
                # Also must use different cflags.  Temp fix.  L4LINUX_TODO.
                # Revisit after new IDL is merged in since that has changed
                # a bit.  Also, we might need to add a new param to accept cflag
                # options on the command line
		if (os.path.basename(self.options.cpp)) in ["armcpp", "tcpp"]:
			self['c_preprocessor'] = "armcc"
			self['cpp_options'] = ['-E -D__arm__ ' +
                                               '-DARM_LITTLE_ENDIAN -D__ARMEL__']

		if self.options.include_dirs is not None:
			options['c_include_dirs'] = self.options.include_dirs
		if self.options.compilerflags:
			options['compiler_flags'] = self.options.compilerflags
		if self.options.word_size:
			# FIXME: this looks alittle clunky...
			if self.options.word_size == '32':
				options['hardware_arch'] = 'Generic 32'
			elif self.options.word_size == '64':
				options['hardware_arch'] = 'Generic 64'
		options['cache_enabled'] = self.options.cache_enabled
		if self.options.cache_dir:
			options['cache_dir'] = self.options.cache_dir
		options['output_type'] = self.options.output_type
		options['cpp_options'] = self.options.cpp_flags.split(' ')

def main():
	parser_inst = IDL4OptionParser()
	parser_inst.setup()
	cmdlineoptions, cmdlineargs = parser_inst.parse_options()
	if cmdlineoptions.print_version:
		print VERSION_STRING
		sys.exit(0)
	if cmdlineargs == []: # No files, so exit
		parser_inst.print_help()
		print >>sys.stderr, "\nExiting because no IDL files were specified.\n"
		sys.exit(1)
	if cmdlineoptions.ugly_includepath_hack is not None:
		cmdlineoptions.include_dirs = [os.path.join(cmdlineoptions.ugly_includepath_hack, i)
			for i in cmdlineoptions.include_dirs]
	parser_inst.set_options()
	options.add_idl_files(cmdlineargs)
	options['target'] = parser_inst.get_target()
	options.set_initialised()

	target_inst = Target()
	try:
		result = False
		result = target_inst.run()
	except:
		traceback.print_exc()
	if result is False:
		sys.exit(1)
	else:
		sys.exit(0)

"""
<blog>

OMG! *blog* *blog* *blog*

DWIM!@!!!!!!1111one oneone

Hahfahrahrharahrhar

You would not belivee what l33t stuff th1s k0hd is going to do!!!

r = make_program_go_now( arguments )

</blog>
"""
	
if __name__ == '__main__':
	main()

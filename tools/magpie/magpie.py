#!/usr/bin/env python

import os, sys

from optparse import OptionParser

from targets.shared.target import Target
from targets.shared.options import options

import helper
helper.sanity_checks()

class MagpieOptionParser(object):
	class ParserError(Exception):
		pass
	def __init__(self):
		parser = OptionParser(usage = 'magpie.py [flags] <idl file>')
		parser.add_option('--target', type = 'string', dest = 'target',
				help = 'Specify a target.')
		parser.add_option('--list-targets', action = 'store_true', default = False,
				help = 'List all targets.', dest = 'list_targets')
		parser.add_option('--output', type = 'string', dest = 'output',
				help = 'Specify an output format.')
		parser.add_option('--list-outputs', action = 'store_true', default = False,
				help = 'List all outputs for a given target.', dest = 'list_outputs')
		parser.add_option('-I', type="string", action="append", dest="include_dirs",
				help="specify additional include directories", default=[])
		parser.add_option('--templates', type="string", dest = "templates_dir",
				help = "The base directory for templates")
		parser.add_option('--output-filename', type="string", dest="output_filename",
				help = "The output filename (or '-' for standard output)",
				default = '-')
		self.parser = parser
	
	def parse(self, cmdline):
		self.options, self.args = self.parser.parse_args(cmdline)

	def set_options(self):
		options.add_idl_files(self.args)
		if self.options.output:
			options['output_type'] = self.options.output
		if self.options.target:
			target_list = self.options.target.split(':')
			target_list.reverse()
			options['target'] = target_list
		options['hardware_arch'] = 'Generic 32' # FIXME
		options['c_include_dirs'] = self.options.include_dirs
		options['print_help'] = []
		options['output_filename'] = self.options.output_filename
		if self.options.templates_dir:
			options['template_base'] = self.options.templates_dir
		if self.options.list_targets:
			options['print_help'] = ['list_targets']
		if self.options.list_outputs:
			options['print_help'] = ['list_outputs']
	
	def must_display_help(self):
		return self._has_help_option()

	def _has_help_option(self):
		for key in self.help_options:
			if self.options[key] is True:
				return True
	
	def _help_list_targets(self):
		print "Current targets:"
	
	def _help_list_outputs(self):
		print "Outputs for target '%s':" % ('ahar')

class Magpie(object):
	def __init__(self, cmdline):
		self.cmdline_parser = MagpieOptionParser()
		self.cmdline_parser.parse(cmdline)
	
	def run(self):
		"""
		"""
		self.cmdline_parser.set_options()
		options.set_initialised()
		target = Target()
		target.run()

def main():
	magpie = Magpie(sys.argv[1:])
	magpie.run()

if __name__ == '__main__':
	main()

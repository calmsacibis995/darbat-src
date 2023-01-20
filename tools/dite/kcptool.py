#!/usr/bin/env python
"""
Modify parts of the KCP.

Syntax:
kcptool server sigma0 print_info
kcptool server sigma0 print_info=ip
kcptool server help
kcptool bootmem print_info
kcptool bootmem clean
kcptool bootmem set 
kcptool general print_info
kcptool general generate
"""
import sys
from optparse import OptionParser
from aistruct import AIStruct, BitPoker, GFile
from elf import ElfFile

class KCPException(Exception):
	pass

class InvalidUsage(KCPException):
	pass

class KIPNotFound(KCPException):
	pass

class KCPMeminfoStruct(AIStruct):
	def __init__(self, *args, **kwargs):
		super(KCPMeminfoStruct, self).__init__(*args, **kwargs)
		self.setup(
				('BITFIELD', 'word1', {'components':
						[('type', {AIStruct.SIZE32: 4, AIStruct.SIZE64: 4}),
						('t', {AIStruct.SIZE32: 4, AIStruct.SIZE64: 4}),
						('_padding1', {AIStruct.SIZE32: 1, AIStruct.SIZE64: 1}),
						('v', {AIStruct.SIZE32: 1, AIStruct.SIZE64: 1}),
						('low', {AIStruct.SIZE32: 22, AIStruct.SIZE64: 54})],
						'post_get': self.post_get_word1, 'pre_set': self.pre_set_word1} ),
				('BITFIELD', 'word2', {'components':
						[('_padding10', {AIStruct.SIZE32: 10, AIStruct.SIZE64: 10}),
						('high', {AIStruct.SIZE32: 22, AIStruct.SIZE64: 54})],
						'post_get': self.post_get_word2, 'pre_set': self.pre_set_word2} ),
		)
	
	def post_get_word1(self, key, value):
		if key == 'low':
			# Least 10 significant bits are set low.
			value <<= 10
		return value
	
	def post_get_word2(self, key, value):
		if key == 'high':
			# Least 10 significant bits are set high.
			value <<= 10
			value |= (0x400 - 1)
		return value
	
	def pre_set_word1(self, key, value):
		if key == 'low':
			value >>= 10
		return value
	
	def pre_set_word2(self, key, value):
		if key == 'high':
			value >>= 10
		return value

class KCP(AIStruct):
	MAGIC = [ord(x) for x in 'L4\xE6K']
	# If we have more than SANE_MEMINFO_SECTION_COUNT memoryinfo blocks,
	# assume something's broken.
	SANE_MEMINFO_SECTION_COUNT = 30

	class MeminfoList(object):
		def __init__(self, kcpstruct):
			self.kcp = kcpstruct
			self.items = {}

		def __len__(self):
			return self.kcp.ai.MemoryInfo['n']

		def __getitem__(self, key):
			if key == self.kcp.ai.MemoryInfo['n']:
				raise StopIteration()
			assert key >= 0 and key < self.kcp.ai.MemoryInfo['n']
			if key in self.items:
				return self.items[key] # Return the cached copy
			else:
				newitem = KCPMeminfoStruct(word_size_in_bits = self.kcp.word_size_in_bits)
				offset = (newitem.struct_size() * key) + self.kcp.ai.MemoryInfo['MemDescPtr']
				newpoker = BitPoker.new_with_poker(self.kcp.poker, offset)
				newitem.read_from_poker(newpoker)
				self.items[key] = newitem
				return newitem

		def append(self, infostruct):
			print "length of self is", len(self)
			newpos = len(self)
			offset = (infostruct.struct_size() * newpos) + self.kcp.ai.MemoryInfo['MemDescPtr']
			newpoker = BitPoker.new_with_poker(self.kcp.poker, offset)
			infostruct.set_poker(newpoker)
			self.items[newpos] = infostruct
			self.kcp.ai.MemoryInfo['n'] = newpos + 1

		def write(self):
			for counter in range(len(self)):
				if counter in self.items:
					self.items[counter].write()

	def __init__(self, *args, **kwargs):
		super(KCP, self).__init__(*args, **kwargs)
		self.setup(
			('INT8', 'magic', {'times': 4}),
			('WORD', '__padding04', {'times': 3}),
			('WORD', "Kdebug_init"),
			('WORD', "Kdebug_entry"),
			('WORD', "Kdebug_low"),
			('WORD', "Kdebug_high"),
			('WORD', "sigma0_sp"),
			('WORD', "sigma0_ip"),
			('WORD', "sigma0_low"),
			('WORD', "sigma0_high"),
			('WORD', "sigma1_sp"),
			('WORD', "sigma1_ip"),
			('WORD', "sigma1_low"),
			('WORD', "sigma1_high"),
			('WORD', "root_server_sp"),
			('WORD', "root_server_ip"),
			('WORD', "root_server_low"),
			('WORD', "root_server_high"),
			('WORD', "__padding50"),
			('BITFIELD', "MemoryInfo", {'components':
					[('n', {AIStruct.SIZE32: 16, AIStruct.SIZE64: 32}),
					('MemDescPtr', {AIStruct.SIZE32: 16, AIStruct.SIZE64: 32})]} ),
			('WORD', "Kdebug_config", {'times':2}),
			('WORD', "MainMem_low"),
			('WORD', "MainMem_high"),
			('WORD', "__padding68", {'times':4}),
			('WORD', "DedicatedMem", {'times':10}),
			('WORD', "__paddingA0", {'times':6}),
			('WORD', "BootInfo"),
			('WORD', "__paddingBC"),
		)
		self.mem_info = KCP.MeminfoList(self)
	
	def write(self, *args, **kwargs):
		super(KCP, self).write(*args, **kwargs)
		self.mem_info.write()
	
	def print_info(self):
		print "Kernel Configuration Page: "
		print "  Magic          %s" % (''.join([chr(x) for x in self.ai.magic]))
		print "  Boot info      0x%x" % (self.ai.BootInfo)
		print
		print "Root servers:"
		print "  sigma0         ip: 0x%x, sp: 0x%x, %x:0x%x"\
				% (self.ai.sigma0_ip, self.ai.sigma0_sp, self.ai.sigma0_low, self.ai.sigma0_high)
		print "  sigma1         ip: 0x%x, sp: 0x%x, %x:0x%x"\
				% (self.ai.sigma1_ip, self.ai.sigma1_sp, self.ai.sigma1_low, self.ai.sigma1_high)
		print "  root server    ip: 0x%x, sp: 0x%x, %x:0x%x"\
				% (self.ai.root_server_ip, self.ai.root_server_sp, self.ai.root_server_low, self.ai.root_server_high)
		print
		print "Memory regions (%d):" % (self.ai.MemoryInfo['n'])
		physregions = [i for i in self.mem_info if i.ai.word1['v'] == 0]
		if physregions:
			print "  Physical:"
			for info in physregions:
				print "                 0x%x - 0x%x  0x%x (0x%x)" \
						% (info.ai.word1['low'], info.ai.word2['high'], info.ai.word1['type'], 
						info.ai.word1['t'])
		virtregions = [i for i in self.mem_info if i.ai.word1['v'] == 1]
		if virtregions:
			print "  Virtual:"
			for info in virtregions:
				print "         0x%x - 0x%x  0x%x (0x%x)" \
						% (info.ai.word1['low'], info.ai.word2['high'], info.ai.word1['type'], 
						info.ai.word1['t'])
		print
		print "Memory regions (legacy):"
		print "  Main mem       0x%x - 0x%x" % (self.ai.MainMem_low, self.ai.MainMem_high)

class KCPHandler(object):
	def __init__(self):
		self.parser = OptionParser()
		self.opt_to_func = {}
		self.auto_kcp = {}

	def register_command(self, name, func, help=None, auto_kcp = False):
		opt_name = '--' + name
		self.parser.add_option(opt_name, help=help, action="store_true", default=False)
		self.opt_to_func[name] = func
		self.auto_kcp[name] = auto_kcp

	def main(self, cmdline_args):
		self.options, self.args = self.parser.parse_args(cmdline_args)
		# Find out which function we wanted, and call it.
		run_func = False
		self.changed = False
		for key in self.opt_to_func.keys():
			if getattr(self.options, key) is True:
				assert run_func is False
				if self.auto_kcp[key] is True:
					# Find the KCP from the first argument, and eat it.
					self.kcp = self.find_kcp_in_elf_file(self.args[0])
					self.args = self.args[1:]
				else:
					self.kcp = None
				self.opt_to_func[key]()
				run_func = True
				if self.changed is True and self.auto_kcp[key] is True:
					self.kcp.write()
		if run_func is False:
			self.parser.print_help()
			raise InvalidUsage("Unknown function. Supported functions are --%s" % \
				(', --'.join(self.opt_to_func.keys())))
		
	def atoi(self, numstr):
		if numstr.startswith('0x'):
			num = int(numstr, 16)
		else:
			num = int(numstr)
		return num
	
	def find_kcp_in_elf_file(self, filename):
		# Find the KCP in an ELF file by looking for the section named ".kip"
		# This is not foolproof. Another non-foolproof way is to look for the 
		# symbol named "kip". Other, even less foolproof methods are left
		# as an exercise.
		elf_file = ElfFile.from_file(filename)
		kip_section = None
		for s_header in elf_file.sheaders:
			section_header_name = elf_file.string_table.read(s_header.ai.sh_name)
			if section_header_name == '.kip':
				kip_section = s_header
				break
		if kip_section is None:
			raise KIPNotFound()
		# If this breaks our "offset" flag is wrong.
		assert kip_section.ai.sh_offset != 0
		poker = BitPoker.new_with_gfile(elf_file.gfile, kip_section.ai.sh_offset)
		kcp = KCP(word_size_in_bits = elf_file.word_size)
		kcp.read_from_poker(poker)
		if list(kcp.ai.magic) != list(kcp.MAGIC):
			return None # Not a KCP, despite what the section header says.
		return kcp
	

class KCPGeneral(KCPHandler):
	def __init__(self):
		super(KCPGeneral, self).__init__()
		self.register_command('print', self.print_info,
				help='Display information about a KCP',
				auto_kcp = True)
		self.register_command('generate', self.generate,
				help='Create a fresh KCP and write it to a new file',
				auto_kcp = False)
	
	def print_info(self):
		self.kcp.print_info()
	
	def generate(self):
		raise NotImplementedError("Broken right now")

class KCPServer(KCPHandler):
	SERVER_NAMES = ['Kdebug', 'sigma0', 'sigma1', 'root_server']
	def __init__(self):
		super(KCPServer, self).__init__()
		self.register_command('set', self.set,
				help='Set server parameters',
				auto_kcp = True)
		self.parser.add_option('--ip', dest='ip', default=None,
				help='Address of instruction pointer')
		self.parser.add_option('--sp', dest='sp', default=None,
				help='Address of stack pointer')
		self.parser.add_option('--low', dest='low', default=None,
				help='Address of lowest byte occupied by server')
		self.parser.add_option('--high', dest='high', default=None,
				help='Address of highest byte occupied by server')
		self.parser.add_option('--server', dest='server', default=None,
				help='Name of server to modify (one of %s)' %\
				(', '.join(self.SERVER_NAMES)))

	def set(self):
		for addr_name in ('ip', 'sp', 'low', 'high'):
			new_addr = getattr(self.options, addr_name)
			if new_addr is not None:
				attribute_name = '%s_%s' % (self.options.server, addr_name)
				address_int = self.atoi(new_addr)
				setattr(self.kcp.ai, attribute_name, address_int)
				self.changed = True
	
class KCPMeminfo(KCPHandler):
	def __init__(self):
		super(KCPMeminfo, self).__init__()
		self.register_command('clear', self.clear,
				help = 'Clear the Meminfo (set the number of sections to 0)',
				auto_kcp = True)
		self.register_command('add', self.add,
				help = 'Add a Meminfo section',
				auto_kcp = True)
		# Options for the above commands.
		self.parser.add_option('--low', dest='low', default='0x0',
				help = 'Address of first byte in region')
		self.parser.add_option('--high', dest='high', default='0x0',
				help = 'Address of final byte in region')
		self.parser.add_option('--is-virtual', dest='is_virtual', default=False,
				action = "store_true",
				help = 'Memory referenced is virtual, not physical')
		self.parser.add_option('--type', dest='type', default='0xe',
				help = 'Type of the memory block')
		self.parser.add_option('--sub-type', dest='sub_type', default='0x2',
				help = 'Sub-type of the memory block')
	
	def clear(self):
		"""Clear memory info region by setting the number of elements to zero"""
		self.kcp.ai.MemoryInfo['n'] = 0
		self.changed = True

	def add(self):
		new_item = KCPMeminfoStruct(word_size_in_bits = self.kcp.word_size_in_bits)
		new_item.ai.word1['type'] = self.atoi(self.options.type)
		new_item.ai.word1['t'] = self.atoi(self.options.sub_type)
		new_item.ai.word1['v'] = self.atoi(self.options.is_virtual)
		new_item.ai.word1['low'] = self.atoi(self.options.low)
		new_item.ai.word2['high'] = self.atoi(self.options.high)
		self.kcp.mem_info.append(new_item)
		self.changed = True

class Main(object):
	dispatch = {'server': KCPServer,
			'meminfo': KCPMeminfo,
			'general': KCPGeneral,
	}

	def print_functions_die(self):
		print "Usage: %s <function> [other args...]" % (sys.argv[0])
		print "<function> should be one of '%s'" % "', '".join(self.dispatch.keys())
		print "Call <function> with no arguments for help on individual commands."
		sys.exit(1)

	def parse_args(self):
		if len(sys.argv) < 2 or sys.argv[1] not in self.dispatch:
			self.print_functions_die()
		handler = self.dispatch[sys.argv[1]]()
		try:
			handler.main(sys.argv[2:])
		except InvalidUsage, e:
			print "Invalid usage: %s" % str(e)
			print "Exiting without making changes."
			sys.exit(1)

	def main(self):
		args = self.parse_args()
	
if __name__ == '__main__':
	Main().main() # so mainey, do wa


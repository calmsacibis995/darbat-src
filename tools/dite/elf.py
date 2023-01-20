from aistruct import GFile, BitPoker, AIStruct
import sys

class Elf32Header(AIStruct):
	EI_MAGIC = [0x7f, ord('E'), ord('L'), ord('F')]
	EI_CLASS_32 = 1
	EI_CLASS_64 = 2
	EI_DATA_LSB = 1
	EI_DATA_MSB = 2
	EI_TYPE_NONE = 0
	EI_TYPE_REL = 1
	EI_TYPE_EXEC = 2
	EI_TYPE_DYN = 3
	EI_TYPE_CORE = 4
	EI_TYPE_NUM = 5
	EI_TYPE_LOPROC = 0xff00
	EI_TYPE_HIPROC = 0xffff
	MACHINE_NONE = 0
	MACHINE_SPARC = 2
	MACHINE_386 = 3
	MACHINE_MIPS = 8
	MACHINE_MIPS_RS4_BE = 10
	MACHINE_SPARC32PLUS = 18
	MACHINE_ARM = 40
	MACHINE_FAKE_ALPHA = 41
	MACHINE_SPARCV9 = 43
	MACHINE_IA_64 = 50
	MACHINE_ALPHA = 0x9026
	VERSION_NONE = 0
	VERSION_CURRENT = 1

	def __init__(self):
		AIStruct.__init__(self, AIStruct.SIZE32)
		self.setup(
			('UINT8', 'ei_magic', {'times': 4}),
			('UINT8', 'ei_class'),
			('UINT8', 'ei_data'),
			('UINT8', 'ei_version'),
			('UINT8', 'ei_padding', {'times': 9}),
			('UINT16', 'e_type'),
			('UINT16', 'e_machine'),
			('UINT32', 'e_version'),
			('UINT32', 'e_entry'),
			('UINT32', 'e_phoff'),
			('UINT32', 'e_shoff'),
			('UINT32', 'e_flags'),
			('UINT16', 'e_ehsize'),
			('UINT16', 'e_phentsize'),
			('UINT16', 'e_phnum'),
			('UINT16', 'e_shentsize'),
			('UINT16', 'e_shnum'),
			('UINT16', 'e_shstrndx')
		)
	
	def print_info(self):
		print " * General"
		print "   Magic          : %s" % (self.ai.ei_magic)
		print "   Class          : %s" % (self.ai.ei_class)
		print "   Data           : %s" % (self.ai.ei_data)
		print "   Version (Info) : %s" % (self.ai.ei_version)
		print "   Type           : %s" % (self.ai.e_type)
		print "   Machine        : %s" % (self.ai.e_machine)
		print "   Version (File) : %s" % (self.ai.e_version)
		print "   Entry          : 0x%x" % (self.ai.e_entry)
		print "   Header size    : 0x%x" % (self.ai.e_ehsize)
		print "   String table start: 0x%x" % (self.ai.e_shstrndx)
		print " * Program headers"
		print "   Program headers begin      : 0x%x" % (self.ai.e_phoff)
		print "   Program header entity size : 0x%x" % (self.ai.e_phentsize)
		print "   Number of program headers  : %d" % (self.ai.e_phnum)
		print " * Section headers"
		print "   Section headers begin      : 0x%x" % (self.ai.e_shoff)
		print "   Section header entity size : 0x%x" % (self.ai.e_shentsize)
		print "   Number of section headers  : %d" % (self.ai.e_shnum)
	

class Elf64Header(Elf32Header):
	# Inherit from Elf32Header to get the constants.
	def __init__(self):
		AIStruct.__init__(self, AIStruct.SIZE64)
		self.setup(
			('UINT8', 'ei_magic', {'times': 4}),
			('UINT8', 'ei_class'),
			('UINT8', 'ei_data'),
			('UINT8', 'ei_version'),
			('UINT8', 'ei_padding', {'times': 9}),
			('UINT16', 'e_type'),
			('UINT16', 'e_machine'),
			('UINT32', 'e_version'),
			('UINT64', 'e_entry'),
			('UINT64', 'e_phoff'),
			('UINT64', 'e_shoff'),
			('UINT32', 'e_flags'),
			('UINT16', 'e_ehsize'),
			('UINT16', 'e_phentsize'),
			('UINT16', 'e_phnum'),
			('UINT16', 'e_shentsize'),
			('UINT16', 'e_shnum'),
			('UINT16', 'e_shstrndx')
		)

class Elf32SectionHeader(AIStruct):
	def __init__(self, *args, **kwargs):
		AIStruct.__init__(self, AIStruct.SIZE32)
		self.setup(
			('UINT32', 'sh_name'),
			('UINT32', 'sh_type'),
			('UINT32', 'sh_flags'),
			('UINT32', 'sh_addr'),
			('UINT32', 'sh_offset'),
			('UINT32', 'sh_size'),
			('UINT32', 'sh_link'),
			('UINT32', 'sh_info'),
			('UINT32', 'sh_addralign'),
			('UINT32', 'sh_entsize'),
		)

class Elf64SectionHeader(AIStruct):
	def __init__(self, *args, **kwargs):
		AIStruct.__init__(self, AIStruct.SIZE64)
		self.setup(
			('UINT32', 'sh_name'),
			('UINT32', 'sh_type'),
			('UINT64', 'sh_flags'),
			('UINT64', 'sh_addr'),
			('UINT64', 'sh_offset'),
			('UINT64', 'sh_size'),
			('UINT32', 'sh_link'),
			('UINT32', 'sh_info'),
			('UINT64', 'sh_addralign'),
			('UINT64', 'sh_entsize'),
		)

class Elf32ProgramHeader(AIStruct):
	PT_NULL = 0
	PT_NULL = 0
	PT_LOAD = 1
	PT_DYNAMIC = 2
	PT_INTERP = 3
	PT_NOTE = 4
	PT_SHLIB = 5
	PT_PHDR = 6
	PT_NUM = 7
	PT_LOOS = 0x60000000
	PT_HIOS = 0x6fffffff
	PT_LOPROC = 0x70000000
	PT_HIPROC = 0x7fffffff

	PF_X = 1 << 0
	PF_W = 1 << 1
	PF_R = 1 << 2
	PF_MASKPROC = 0xf0000000L

	def __init__(self, *args, **kwargs):
		AIStruct.__init__(self, AIStruct.SIZE32)
		self.setup(
			('UINT32', 'p_type'),
			('UINT32', 'p_offset'),
			('UINT32', 'p_vaddr'),
			('UINT32', 'p_paddr'),
			('UINT32', 'p_filesz'),
			('UINT32', 'p_memsz'),
			('UINT32', 'p_flags'),
			('UINT32', 'p_align'),
		)

class Elf64ProgramHeader(Elf32ProgramHeader):
	def __init__(self, *args, **kwargs):
		AIStruct.__init__(self, AIStruct.SIZE64)
		self.setup(
			('UINT32', 'p_type'),
			('UINT32', 'p_flags'),
			('UINT64', 'p_offset'),
			('UINT64', 'p_vaddr'),
			('UINT64', 'p_paddr'),
			('UINT64', 'p_filesz'),
			('UINT64', 'p_memsz'),
			('UINT64', 'p_align'),
		)

class ElfFileException(Exception):
	pass

class ElfFileNotElfException(ElfFileException):
	pass

class ElfFileContainer(object):
	def __init__(self, gfile, word_size, offset, entsize, number, cls):
		self.gfile = gfile
		self.word_size = word_size
		self.offset = offset
		self.entsize = entsize
		self.number = number
		self.cls = cls
	
	def __getitem__(self, num):
		assert num >= 0
		assert num < self.number
		inst = self.cls(self.word_size)
		poker = BitPoker.new_with_gfile(self.gfile, self.offset + (self.entsize * num))
		inst.read_from_poker(poker)
		return inst
	
	def __len__(self):
		return self.number
	
	def __iter__(self):
		class EFCIterator:
			def __init__(self, container):
				self.container = container
				self.current = 0

			def __iter__(self):
				return self

			def next(self):
				if self.current == len(self.container) - 1:
					raise StopIteration()
				self.current += 1
				return self.container[self.current]
		return EFCIterator(self)

class ElfFileStringTable(object):
	def __init__(self, gfile, section_header):
		file_offset = section_header.ai.sh_offset
		self.poker = BitPoker.new_with_gfile(gfile, file_offset)
	
	def read(self, offset):
		return self.poker.read_c_string(offset)

class ElfFile(object):
	WORD_SIZE_MAP = {Elf32Header.EI_CLASS_32: Elf32Header.SIZE32,
			Elf32Header.EI_CLASS_64: Elf32Header.SIZE64}
	BYTE_ORDER_MAP = {Elf32Header.EI_DATA_LSB: 'lsb',
			Elf32Header.EI_DATA_MSB: 'msb'}
	HEADER_MAP = {Elf32Header.SIZE32: Elf32Header, Elf64Header.SIZE64: Elf64Header}
	PROGRAM_HEADER_MAP = {Elf32Header.SIZE32: Elf32ProgramHeader, Elf64Header.SIZE64: Elf64ProgramHeader}
	SECTION_HEADER_MAP = {Elf32Header.SIZE32: Elf32SectionHeader, Elf64Header.SIZE64: Elf64SectionHeader}
	""" Python representation of an Elf file. """
	def __init__(self, gfile, byte_ordering, word_size):
		self.gfile = gfile
		self.gfile.set_byte_ordering(byte_ordering)
		self.byte_order = byte_ordering
		self.word_size = word_size

		self.header = ElfFile.HEADER_MAP[self.word_size]()
		self.header.read_from_poker(BitPoker.new_with_gfile(self.gfile, 0))
		# Setup the parts of the file
		# ... program headers
		self.pheaders = ElfFileContainer \
				(gfile, word_size, self.header.ai.e_phoff, self.header.ai.e_phentsize,
				self.header.ai.e_phnum, ElfFile.PROGRAM_HEADER_MAP[word_size])
		# ... section headers
		self.sheaders = ElfFileContainer \
				(gfile, word_size, self.header.ai.e_shoff, self.header.ai.e_shentsize,
				self.header.ai.e_shnum, ElfFile.SECTION_HEADER_MAP[word_size])
		# ... string table
		if self.header.ai.e_shstrndx != 0:
			self.string_table = ElfFileStringTable \
				(self.gfile, self.sheaders[self.header.ai.e_shstrndx])
	
	def set_source(self, poker):
		self.source_poker = poker
	
	def print_info(self):
		print "* Information for ELF file:"
		print "* Header info:"
		self.header.print_info()

	def from_file(filename):
		gfile = GFile.existing(filename)
		poker = BitPoker()
		poker.set_mmapfile(gfile.mapping, 0) # Offset of 0 from start of file.
		poker.set_byte_ordering('lsb') # Use default because we don't (yet) know
		header = Elf32Header() # Once again, use a default size.
		header.read_from_poker(poker)
		# Examine the header for info we need.
		# Check the magic first. If we don't and the file is non-ELF, chances are
		# class & data won't match which will result in a confusing error message
		if header.ai.ei_magic != Elf32Header.EI_MAGIC:
			raise ElfFileNotElfException("Wanted magic %r, got %r" \
					% (Elf32Header.EI_MAGIC, header.ai.ei_magic))
		word_size = ElfFile.WORD_SIZE_MAP[header.ai.ei_class]
		byte_order = ElfFile.BYTE_ORDER_MAP[header.ai.ei_data]
		return ElfFile(gfile, byte_order, word_size)
	from_file = staticmethod(from_file)

def main():
	filename = sys.argv[1] # Consider this a usage message :)
	elf_file = ElfFile.from_file(filename)
	elf_file.print_info()

if __name__ == '__main__':
	main()



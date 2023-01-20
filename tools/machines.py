from simulators import *

class Machine:
    virtual = True
    as_flags = []
    c_flags = []
    cpp_flags = []
    cxx_flags = []
    link_flags = []
    drivers = []
    wordsize = None
    timer_driver = None
    serial_driver = "drv_l4_kdb"
    elfloader = False
    macho = False
    endian = None

############################################################################
# ia32 based machines
############################################################################
class ia32(Machine):
    wordsize = 32
    arch = "ia32"
    endian = "little"
	# sigh
    as_flags = ["-m32"]
    c_flags = ["-m32"]
    link_flags = ["-melf_i386"]
    toolchain = ""
    #toolchain = "i686-linux-"
    qemu_args = []
    sim = staticmethod(qemu_sim)

class pc99(ia32):
    virtual = False
    cpu = "i686"
    l4conf = "ia32-qemu-serial"
    platform = "pc99"
    qemu_args = ia32.qemu_args + ["-nographic"]
    serial_console = True
    timer_driver = "drv_8254_timer"

class ia32efi(ia32):
    virtual = False
    cpu = "i686"
    l4conf = "ia32-qemu-serial"
    platform = "efi"
    qemu_args = ia32.qemu_args + ["-nographic"]
    serial_console = True
    timer_driver = "drv_8254_timer"

class ia32efiapple(ia32efi):
    toolchain = ""
    as_flags = ["-arch", "i386"]
    c_flags = ["-arch", "i386"]
    link_flags = ["-arch", "i386"]
    macho = True
############################################################################
# arm based machines
############################################################################
class arm(Machine):
    wordsize = 32
    arch = "arm"
    toolchain = "arm-linux-"
    endian = "little"
    sim = staticmethod(skyeye_sim)

class sa1100(arm):
    c_flags = arm.c_flags + ["-march=armv4", "-mtune=strongarm1100"]
    l4conf = "sa1100"
    cpu = "sa1100"
    timer_driver = "drv_sa1100_timer"

class pleb(sa1100):
    virtual = False
    serial_driver = "drv_sa1100_uart"
    skyeye = "pleb.skyeye"
    platform = "pleb"

class ipaq_h3800(sa1100):
    virtual = False
    skyeye = "pleb.skyeye"
    elfloader = True
    elf_entry = 0xC0008000L
    platform = "pleb"

class xscale(arm):
    c_flags = arm.c_flags + ["-march=armv5te", "-mtune=xscale"]

class pleb2(xscale):
    virtual = False
    c_flags = xscale.c_flags
    timer_driver = "drv_pxa250_timer"
    l4conf = "pleb2"
    skyeye = "pleb2.skyeye"
    elfloader = True
    elf_entry = 0xa0008000L
    platform = "pleb2"
    cpu = "xscale"

class pleb2_thumb(pleb2):
    cpp_flags = ["-mthumb", "-mthumb-interwork"]
    toolchain = "arm-elf-"

class ln2410sbc(arm):
    virtual = False
    l4conf = "ln2410sbc"
    skyeye = "ln2410sbc.skyeye"
    drivers = ["drv_ln2410sbc_lcd"]

############################################################################
# mips64 based machines
############################################################################
class mips64(Machine):
    wordsize = 64
    arch = "mips64"
    c_flags = ["-mlong64", "-mabi=64", "-G",  "0", "-Wa,-mabi=o64",
               "-EB", "-mno-abicalls", "-non_shared", "-msplit-addresses",
               "-mips3"]
    toolchain = "mips64-elf-"
    sim = staticmethod(sulima_sim)

class u4600(mips64):
    virtual = False
    platform = "u4600"
    cpu = "r4x00"
    l4conf = "u4600"
    endian = "big"
    timer_driver = "drv_gt64xxx_timer"

############################################################################
# Alpha based machines
############################################################################
class alpha(Machine):
    wordsize = 64
    arch = "alpha"
    endian = "little"
    c_flags = ["-mno-fp-regs"]
    toolchain = "alpha-unknown-linux-gnu-"
    elfloader = True
    elf_entry = 0x20000000 # Alpha console expects apps here.
    sim = staticmethod(m5_sim)
    
class ds20(alpha):
    virtual = False
    l4conf = "tsunami"
    # awiggins (2005-10-05): elf_entry override is for M5, needs cleaning up.
    elf_entry = 0xfffffc0000200000

# set a default install target

# First step is to include our real build tools
# tools/build.py includes the KengeEnvironment
try:
    execfile("tools/build.py")
except IOError:
    print 
    print "There was a problem finding the tools directory"
    print "This probably means you need to run:"
    print "  $ baz build-config packages"
    print
    import sys
    sys.exit()

# Now we go and construct all the different types of options
# that we have
add_config_help("Iguana options:\n")

examples = [eg for eg in os.listdir("example") if
            not eg.startswith(".")] + [None]

add_config_list("example", "Specify an example app to run.", None, examples)

# Wombat defaults to false if example is set
add_config_bool("wombat", "Do you want to include wombat in this image", False)
if wombat:
    add_config_list("linux_apps", "Which Linux apps do you want to compile?",
                    None, ["ltp", "lmbench", "strace", None])

# Darbat defaults to true
add_config_bool("darbat", "Do you want to include darbat in this image", True)

# L4IOKit defaults to true
add_config_bool("l4iokit", "L4-based I/O Kit", True)
add_config_bool("verbose_iokit", "Verbose IOKit printing", False)

# By default, query the video console to use
# see osfmk/console/video_config.h for appropriate values here
# add_config_arg("video_console", "Darbat video console", 0)
# video_console = globals().get( "video_console", 0 )
video_console = opts.get( "video_console", 0 )


# Mach-O components
# XXX for now, remove me
macho = False
add_config_bool("macho_hello", "Mach-O helloworld", False)


add_config_bool("caps", "Do you want to enable capability protection.", True)
add_config_bool("restrict_vm", "Do you want to restrict the size of virtual memory.", True)
add_config_bool("shell", "Do you want to enable the iguana shell?", False)

libraries = [lib for lib in os.listdir("libs") if
            not lib.startswith(".")] + [None]

add_config_list("test_lib", "Name of a library to test", None, libraries)

# Now we can setup the help screen
setup_help()

# Create of default environment for compiling everything in.
env = None
if machine.macho == True:
	env = KengeEnvironment(toolchain_name="apple")
else:
	env = KengeEnvironment(toolchain_name="gnuelf")

# Build the l4 kernel
kernel_env = env.Copy("pistachio")
if kernel_env.toolchain_name == "apple":
	kernel_env.AddLibrary("gcc")
#l4kernel = kernel_env.Pistachio()
l4kernel = kernel_env.Application("pistachio")

# Now we create a new environment in which to compile l4 rootserver.
# Again we build a C library, which is different here because we can use
# the L4 kernel debugger for doing printing, and can use the L4_KDB_Enter() call
# to implement abort().
sigma0_env = env.Copy("sigma0",
                      LINKFLAGS=["-r"])
if sigma0_env.toolchain_name == "apple":
	sigma0_env.AddLibrary("gcc")
sigma0_env.AddLibrary("l4")
sigma0_env.AddLibrary("c", system="l4_rootserver")

# Now we build a sigma0. This is different from L4s default sigma0 in that it
# doesn't support dynamic memory allocation. In most of our rootservers we find
# it much easier for the rootserver, rather than sigma0 to handle dynamic
# memory allocation. This allows use to have a sigma0 that has a small, and more
# importantly fixed, memory footprint.
iguana_sigma0 = sigma0_env.Application("iguana/sigma0")

# Now we setup the environment for compiling the iguana server in.
# Note that we have use a lot of other libraries, mostly for implementing
# data structures
ig_serv_env = env.Copy("ig_server", LINKFLAGS=["-r"])
if ig_serv_env.toolchain_name == "apple":
	ig_serv_env.AddLibrary("gcc")
ig_serv_env.AddLibrary("l4")
ig_serv_env.AddLibrary("mutex")
ig_serv_env.AddLibrary("c", system = "iguana_server")
ig_serv_env.AddLibrary("ll")
ig_serv_env.AddLibrary("range_fl")
ig_serv_env.AddLibrary("circular_buffer")
ig_serv_env.AddLibrary("elf")
ig_serv_env.AddLibrary("l4e")
ig_serv_env.AddLibrary("iguana", restrict_vm=restrict_vm)
ig_serv_env.AddLibrary("hash")
ig_serv_env.AddLibrary("bit_fl")
ig_serv_env.AddLibrary("util")
ig_serv_env.AddLibrary("obj_alloc")
ig_serv_env.AddLibrary("queue")
ig_serv_env.AddLibrary("b_plus_tree", buildname = "obj_btree", conf = "iguana/server/src/obj_btree.h")
ig_serv_env.AddLibrary("b_plus_tree", buildname = "cap_btree", conf = "iguana/server/src/cap_btree.h")

# Finally we are ready to build the iguana root task
iguana = ig_serv_env.Application("iguana/server", caps=caps, restrict_vm=restrict_vm)

# Now we create an environment in which to compile the user applications.
# All the applications share this environment, so eventually there may be
# a long list of libraries, although every app will only use a small number
# of these.

linux_toolchains = { "arm" : "/opt/tools/3.4/arm-linux/bin/arm-linux-",
                     "ia32" : None,
                     "mips64" : "mips-linux-",
                     "powerpc64" : None
                     }

linux_static = {"arm" : 0,
                "ia32" : 0,
                "mips64" : 1,
                "powerpc64" : 0 }

ig_env = env.Copy("iguana", LINKFLAGS=["-r"])
if ig_env.toolchain_name == "apple":
	ig_env.AddLibrary("gcc")
ig_env.AddLibrary("l4")
ig_env.AddLibrary("mutex")
ig_env.Append(CPPDEFINES=["THREAD_SAFE"])
ig_env.AddLibrary("c", system="iguana", filesystem="bootinfo")
ig_env.AddLibrary("util")
ig_env.AddLibrary("ll")
ig_env.AddLibrary("range_fl")
ig_env.AddLibrary("circular_buffer")
ig_env.AddLibrary("elf")
ig_env.AddLibrary("l4e")
ig_env.AddLibrary("iguana", restrict_vm=restrict_vm)
ig_env.AddLibrary("naming")
ig_env.AddLibrary("timer")
ig_env.AddLibrary("trace")
ig_env.AddLibrary("mach-o")
ig_env.AddLibrary("lkm")
ig_env.AddLibrary("iokitcli")
ig_env.AddLibrary("xnuglue")
ig_env.AddLibrary("libsa")
ig_env.AddLibrary("libkern")
ig_env.AddLibrary("iokit", verbose_iokit=verbose_iokit)
if( l4iokit ):
	ig_env.AddLibrary("iokitdrv")
	ig_env.AddLibrary("dynamic")
ig_env.AddLibrary("driver", system="iguana")

ig_env.AddLibrary(machine.serial_driver)
ig_env.AddLibrary(machine.timer_driver)
for lib in machine.drivers:
    ig_env.AddLibrary(lib)

ig_env.AddLibrary("lua")
ig_env.AddLibrary("binary_tree")

ig_test_env = ig_env.Copy("iguana_test", TESTENV=1)

#ig_macho_env = ig_env.Copy("iguana_macho", toolchain_name="apple", MACHO=True, _LIBFLAGSBEGIN="", _LIBFLAGSEND="", TOOLCHAIN=["", ""])
#ig_macho_env.AddLibrary("l4")
#ig_macho_env.AddLibrary("mutex")
#ig_macho_env.Append(CPPDEFINES=["THREAD_SAFE"])
#ig_macho_env.AddLibrary("c", system="iguana", filesystem="bootinfo")
##ig_macho_env.AddLibrary("gcc")
#ig_macho_env.AddLibrary("util")
#ig_macho_env.AddLibrary("ll")
#ig_macho_env.AddLibrary("range_fl")
#ig_macho_env.AddLibrary("circular_buffer")
#ig_macho_env.AddLibrary("elf")
#ig_macho_env.AddLibrary("l4e")
#ig_macho_env.AddLibrary("iguana", restrict_vm=restrict_vm)
#ig_macho_env.AddLibrary("naming")
#ig_macho_env.AddLibrary("timer")
#ig_macho_env.AddLibrary("trace")
#ig_macho_env.AddLibrary("mach-o")
#ig_macho_env.AddLibrary("lkm")
#ig_macho_env.AddLibrary("xnuglue")
#ig_macho_env.AddLibrary("libkern")
#ig_macho_env.AddLibrary("iokit")
#ig_macho_env.AddLibrary("iokitdrv")
#ig_macho_env.AddLibrary("libsa")
#ig_macho_env.AddLibrary("dynamic")
#ig_macho_env.AddLibrary("driver", system="iguana")
#
#ig_macho_env.AddLibrary(machine.serial_driver)
#ig_macho_env.AddLibrary(machine.timer_driver)
#for lib in machine.drivers:
#    ig_macho_env.AddLibrary(lib)
#
#ig_macho_env.AddLibrary("lua")
#ig_macho_env.AddLibrary("binary_tree")

# The first application we build is the iguana's init task -- This is started
# automatically by iguana, and is responsible for starting the rest of the
# applications.
if test_lib is not None:
    example="test"
    wombat = False
if shell:
    wombat = False # We don't compile wombat currently if we have a shell. This will change
if example is not None:
    wombat = False # We don't compile wombat if we compile examples

iguana_init = ig_env.Application("iguana/init", shell=shell, example=example, wombat=wombat,darbat=darbat, l4iokit=l4iokit, macho_hello=macho_hello)

if test_lib is not None:
    example=None

# Iguana serial is an example serial driver server. Because the serial
# driver server is generic and can be used with different serial device chipsets
# we specify which serial device to use

iguana_serial = ig_env.Application("iguana/serial", driver=machine.serial_driver)
iguana_naming = ig_env.Application("iguana/naming")
iguana_timer = ig_env.Application("iguana/timer", driver=machine.timer_driver)
iguana_trace = ig_env.Application("iguana/trace")

apps = []
# Example apps to compile
if example is not None:
    if example not in examples:
        raise UserError, "Example must be on of: %s " % examples
    example_app = ig_env.Application("example/%s" % example)
    apps.append(example_app)

if shell == True:
    apps.append(ig_env.Application("apps/iguana_shell"))

# print "def: %s" % ddefault_target

if darbat == True:
    apps.append(ig_env.Application("darbat",video_console=video_console))

if l4iokit == True:
    if macho == True:
        apps.append(ig_macho_env.Application("iguana/iokit", verbose_iokit=verbose_iokit))
    else:
        apps.append(ig_env.Application("iguana/iokit", verbose_iokit=verbose_iokit))

if test_lib is not None:
    test_app = ig_test_env.Application("test", lib=test_lib)
    wombat = False
    apps.append(test_app)
    # Append any files required by the test environment
    for raw_file in ig_test_env.get_files():
        apps.append((raw_file, "raw"))

if wombat:
    # Create an environment in which to build linux applications
    linux_env = KengeEnvironment(STATIC=linux_static[machine.arch],
                                 GCC_AS_LINK=1)
    the_linux_apps = []
    the_linux_apps.append(linux_env.build_busybox())
    if "ltp" == linux_apps:
        the_linux_apps.append(linux_env.build_linux_app("linux_apps/ltp", tests=ltp))
    if "lmbench" == linux_apps:
        the_linux_apps.append(linux_env.build_linux_app("linux_apps/lmbench"))
    if "strace" == linux_apps:
        the_linux_apps.append(linux_env.build_linux_app("linux_apps/strace"))

    ramdisk = linux_env.build_ramdisk(the_linux_apps)
    # This builds a copy of L4/Linux
    wombat = ig_env.build_linux()
    apps.append((wombat, "l"))
    apps.append((ramdisk, "raw"))


# Testing only. - gl
# Either you build it or it is already inside your directory
# in which case you just use apps.append.
#if macho == True and macho_hello == True:
#	apps.append(ig_macho_env.Application("iguana/macho_hello"))
# 
# Because we are appending this not as a standard ELF file, this must go
# last, because Benno hardcoded it to use readelf to relocate stuff.
# XXX coming soon -gl
if macho == True and macho_hello == True:
	apps.append(("macho_hello", "machohack"))

# Warning RAW files must be appended AFTER any binaries
# Append any files required by the ig_env environment
for raw_file in ig_env.get_files():
    apps.append((raw_file, "raw"))


env["EXPECT_TEST_DATA"] = ig_env["EXPECT_TEST_DATA"]

bootimage = env.Bootimage(l4kernel, iguana_sigma0, iguana,
                          iguana_init, iguana_serial,
                          iguana_naming, iguana_timer,
                          iguana_trace,
                          *apps)

# Default build target is the bootimage.
if( default_target is None ):
    print "Defaulting to env.Bootimage"
    # Default(bootimage)
    
else:
    print "Setting default target to '%s'" % default_target
    Default( default_target )

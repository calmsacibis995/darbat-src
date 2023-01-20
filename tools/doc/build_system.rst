===================================================
 Information on how the build system is structured
===================================================

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005

.. contents::

Overview
========

The build system is designed to allow you to easily generate a bootable
image for your target machine. The build system is based on the 
`SCons <http://www.scons.org>`_ build system, which in turn
is based on the `Python <http://www.python.org>`_ programming language.

It build on this by providing extra functions and enhanced classes
that handle much of the logic that you would otherwise need to handle
manually.

It also provides builders for generating end products such as filesystem
and bootable images.

The rest of this documents goes through how to use the build system from
various points of view.

Using a Kenge based build system
=================================

Simply using the SCons based build system doesn't require any special
knowledge of SCons or Python. At its most simplest building a project
is simply::

 $ scons machine=<yourmachine>

You will need to know what `machine <machines.pml>`_ you want to compile
the project for. `pc99_serial` is perhaps the simplest example. So
you would do::

 $ scons machine=pc99_serial

This will compile and L4, sigma0, rootserver and any other bits of code
required to get you a bootable system.

Configuration Options
---------------------

The build system allows individual projects to specify command line arguments
that change the behaviour of the project. For example the `hello-project` allows
you to specify which language you want by setting the `lang` option::

 $ scons machine=pc99_serial lang=french

Tool Suffixes
-------------

If you wish to set a version of gcc, g++ and cpp to use in the build system,
you can do so with a tool suffix. For example, to have gcc-3.3, g++-3.3 and
cpp-3.3 be the compilation commands used::

 $ scons toolsuffix=-3.3

User Configurations
-------------------

Specifying every option on the command line each time can become tedious. The
build system allows a user to create a `.conf` file, which contains options that
are that are read by default. For example to capture the above configuration
we can have a .conf like::

 machine="pc99_serial"
 lang="french"

The format for this file is::

 option_name="option"

Note the need to use quotation marks. This file is actually a python
file so you can write arbitrary python expressions, allowing for
powerful extension.

Note that options specified in the `.conf` file can be overridden on
the command line.

Multiple config files (advanced)
---------------------------------

If you are often building for multiple different platform and with
different configuration options you can create a `.conf` file for each
different configuration. These files are named `<configname>.conf` and
have the same format as the normal `.conf` file.

To use a specific config you use a command line like::

 $ scons conf=<configname>

Rather than these being built into the normal `build` directory, they
are built into a directory called `build.<configname>`. This makes it
very convenient to test for multiple platforms and configurations at
once.

Predefined config files (advanced)
----------------------------------

Project can distribute their own predefined configs for common cases.
These are found in the `configs` directory. When a user specifies 
`conf=` on the command line, it will also check the `configs` directory
for a valid configuration.

There is also a mechanism to build all targets at once. This the
script `build_all.py`. This will look for all user and predefined
configuration and build themm with `scons conf=<configname>`.

So to simply build everything::

 $ ./tools/build_all.py

This will also only print miniaml output. E.g::
 
 pleb_english: OK                                
 ipaq_english: OK
 pc99_english: FAILED, output in pc99_english.output.err


Simulate target
----------------

Simulators provide a very convenient way to run and test operating
systems code. To make this easy for you the Kenge build system
provides a `simulate` target, which will run your compiled image in a
simulator, with the relevant simulator configuration for your machine
choice.

Of course to simulate your desired platform you will need to have a simulator
installed. Our `simulators page <simulators.pml>`_
contains more information on obtaining and installing simulators.

Expect based automatic testing
------------------------------

Simulators also provide the opportunity to use expect based automatic testing.
By using the simulator_test target the build system will use the python 
pexpect library to run the simulator and look for expected output.

For more information on how to provide an the expected output read
the documentation on how to write a top-level SConstruct.

Install target
---------------

Some machines provide an install target which allows you to copy to
relevant files to a local or remote directory to allow a hardware
bootloader to load the boot image. More information can be found
in the `booting <booting.pml>`_ documentation.

Cleaning
---------

You can do a full clean by doing::

$ scons -c

or simply::

$ rm -r build

Writing a top-level SConstruct
===============================

Kenge is based around using existing libraries and applications to write
your design your own L4 based systems. If you are doing this then the main
thing you need to know from the build system point of view is how to write
a top level SConstruct which controls how the project is constructed.

A simplified version of the hello-world project SConstruct is used as
an example of a simple top-level SConstruct.

The first line in your top-level SConstruct loads the build system
which gives you access to the enhanced functions.::

 execfile("tools/build.py")

The first real step is to create a build *environment*. The build
environment describes all the parameters such as compilers, compile
flags used to compile the libraries and programs in the
environment. By default the environment will determine the compilers
and compile flags needed for the machine chosen by the the user. This
first environment created is known as the base environment.::

 env = KengeEnvironment()

In building an L4 based system you compile different parts of the system in different
environments, as they need different compile flags and use different libraries. The
first environment we need is one in which to build the kernel. We create that environment
by copying the base environment. In this case we don't need to make any special changes
to so we just go on and specify the kernel.

::

 l4kernel_env  = env.Copy("kernel")
 l4kernel = l4kernel_env.Pistachio()

L4 based systems have two special program know as *rootservers* that
are started by the kernel at boot time. This next step involves creating
an environment in which to build the rootservers.

In this case the call to the `Copy` method is passed a named argument
specifying extra **LINKFLAGS** to be used when linking programs in this
environment. Specifically we pass the `-r` flag which compiles the programs
as relocatable binaries.

We then go and add the libraries required by the programs being compiled
in this environment. In this case we add the `l4` and `c` libraries. The
`l4` library is used by any application running on top of L4 to access
the system calls. You can see that it is possible to pass arguments to the 
library specification. In this case we specify what type of system we should
compile the C library for. Specifically, we compile it for an *l4_rootserver*
system. This controls how the C library handles functions like `abort()` and
standard I/O.

::

 rootserver_env = env.Copy("rootserver", LINKFLAGS=["-r"])
 rootserver_env.AddLibrary("l4")
 rootserver_env.AddLibrary("c", system="l4_rootserver")


Now that the environment is configured we are able to build the applications
needed. Here we build `sigma0` and `hello`. Sigma0 is the initial root memory
manager and hello is our simple *Hello World* application.

::

 sigma0 = rootserver_env.Application("sigma0")
 hello = rootserver_env.Application("hello")

Finally specify how to construct the final bootimage. In this case it contains
three things: the kernel, `sigma0`, and our application `hello`.

::

 bootimage = env.Bootimage(l4kernel, sigma0, hello)

Finally we set the default build target to be our final boot

::

 Default(bootimage)


The rest of this section covers some of the more advanced topics in writing a 
top-level SConstruct.

Configuration options
---------------------

It is often the case that you will want to provide some configuration options to
your users. This is done by using the `add_config_*` functions.

The simplest is `add_config_bool` function. This allows for a True or False response 
from the user. `add_config_bool` takes three arguments, the name of the option, 
a description which will be presented to the user as help text, and a default value. 
An example from the Iguana project is::

  add_config_bool("caps", "Enable capability protection", True)

The other config function provided is `add_config_list`. This allows for the user
to provide one of a range of responses. It takes an extra argument, which is the
list of valid values. For example::

  add_config_list("lang", "Select a language", "english", ["english", "spanish", "french", "german"])

SConstruct file is a python file
---------------------------------

One thing to remember when writing a top-level SConstruct is that you
are able to use arbitrary Python language constructs, which can allow
you to create very powerful specification. Despite this power you should
be careful when writing the top-level construct to ensure that it is
readable and understandable by people who may not be Python experts.

Specifying test expect data
----------------------------

The build system provides a simulate_test target to allow you to automatically
test your build. This is done by setting the `EXPECT_TEST_DATA` variable
on your build environment.

The format of this data should be a list of tuples. Each tuple has an
expected input as the first field, and the output to provide when that
input is detected as the second field. If you don't need to provide
output simply supply `None`. The simple example from hello world consists
of::

 env["EXPECT_TEST_DATA"] = [("Hello, world. Press any key to continue", ""),
                       	  ("That's all folks", None)]

In the above example it waits for the hello, world string and then responds
with an empty string, which is equivilant to the user pressing enter. It
the waits until the That's all folks string at which stage the test is completed
successfully.

Writing package SConstruct files
=================================

If you are writing packages, usually an application or a library then you need to write
a package SConstruct file.

Data files
----------

Some libraries need to provide data files. E.g: as test input,
storing locale information etc.

These can be added by ``env.add_file()``. The ``.sconf`` file is responsible
for copying any files in an environment into the final image. An
example usage of this can be seen in ``libs/c/Sconstruct`` for copying
test data files for the filesystem test.

Overriding default flags
------------------------
Normally compiler flags, linker flags and the like are handled by the 
environment in which you are compiling, and therefore you will not need
to worry about them when writing an SConstruct file for a library, or
for a program. 

For the times when you don't need to changes things there are two options;
either appending to the existing list or totally replacing it. To replace
a given variable you do::

 env.KengeLibrary(FOO=["bar", "baz"])

To append to a variable add ``EXTRA_`` to the front of it. For example::

 env.KengeLibrary(EXTRA_FOO=["bar, "baz"])

In some cases you might want to change the list. Here you will need a couple of
steps involving some python programming to extract the relevant items you want. The 
following example extracts the environments FOO variable, but filters out any ``quz``
items in it.
 
 foo = env["FOO"]
 foo = [x for x in foo if x != "quz"]
 env.KengeLibrary(FOO=foo)

Finally, in some cases you may want to change the actual environment itself. Note
that this will change the compilation environment for all the other libraries and applications
as well, so use it with care. One example of this is a library wanting to add some preprocessor
defines that must be used by any library including its header files. To achieve this
you can use the environment's ``Prepend()`` and ``Append()`` methods. For example::

 env.Append(CPPDEFINES = ["FOO"])

Some of the more useful variables you may want to change are:

 * CPPDEFINES - These are a list of defines passed to the C preprocessor.
   The equivilant of ``#define FOO bar`` in a C program. It is likely that
   you would want to append to this list rather than replacing it, as the default
   include interesting defines, such as ``MACHINE_$machinename`` and ``ARCH_$arch``.
   CPPDEFINES are a list of strings, or tuples. Tuples are used when the defines have
   associated values.

 * CC_STD - This specifies the C standard you wish to compile code with. It defaults to
   ``gnu99``. (See the gcc man page for more information.)

 * CC_ARCH_FLAGS - These are architecture specific C compiler flags. It is unlikely that you 
    would need to change them. They are separate from normal ``CC_FLAGS`` to make it simpler
    to change one without the other.

 * CC_WARNINGS - This is a list of warnings that you want to compiler to use. By default the
    setup will warn on most things. By changing this variable you can reduce the number of 
    warning the compiler will generate.

 * CCFLAGS - This is a list of other general flags to pass to the compiler. By default it includes
   ``-O2``, ``-g``, ``-nostdlib``, ``-nostdinc``. It is unlikely that you would need to 
   change these, but you may wish to append to them.

 * LINKSCRIPTS - This is a list of linker script files that you wish the linker to use.

 * LINKFLAGS - A list of flags you want to pass to the linker.

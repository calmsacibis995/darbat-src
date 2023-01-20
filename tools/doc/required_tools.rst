===================================================
 External tools needed
===================================================

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005

.. contents::

Overview
========

The Kenge build system tries to provide known working
versions of most of the tools required to build a bootable
image, and these are compiled by the build system when
required. There are however some external dependencies
required.

This document describes which external tools you need
and how to get them.

Python
=======

The majority of the build scripts are written in the
excellent scripting language Python. Many operating
systems come with python installed. The minimum
version required is Python 2.3. We plan on supporting
this version going forward, although we will also ensure forward
compatability with new version of python.

Python can be downloaded from the `Python website <http://www.python.org/download>`_.

SCons
=====

We use the SCons build system. Unfortunately it is slightly
trickier to maintain compatability between different
version of SCons. The currenty minimum required is version
0.96.1. As with Python we will attempt to be forward compatible
with newer versions.

SCons can be downloaded from the `SCons website <http://www.scons.org/download.php>`_.

Toolchains
==========

We currently rely on the gcc toolchains.
To compile Kenge projects
such as Iguana natively on ia32, use a standard native compiler.
In this case, the compiler *must* be gcc-3.3. Later versions of
gcc will not accept the ia32 headers. Support for more compilers
is at a high priority for coming releases. If you have gcc-3.3
installed but running gcc defaults to another version (check with
gcc --version) then you will probably need to set tool suffixes,
see the `build system documentation <build_system.pml>`_ for
further details.

To compile for other architectures, such as ARM and MIPS,
a cross compiler is needed. Obtaining
cross compilers can be tricky, so we make available binary copies of
gcc-3.4.4 which run on linux-ia32 and compile for arm and mips64. See the
`prebuilt binaries page <http://www.ertos.nicta.com.au/software/prebuilt/binaries.pml>`_.

If you are building on Windows for ARM the Cygwin toolchains from
`GNUARM <http://www.gnuarm.com>`_ are recommended.

If you need or want to compile your own toolchain we
suggest that you use `crosstool <http://kegel.com/crosstool>`_.

The basic steps involved are:
 1. Download crosstool. Eg: wget http://kegel.com/crosstool/crosstool-0.28-rc32.tar.gz
 2. Extract. Eg: tar zxvf crosstool-0.28-rc32.tar.gz
 3. Edit demo-arm-softfloat.sh. Uncomment the gcc-3.3.3 line.
 4. Edit arm-softfloat.dat. Set TARGET=arm-linux.
 5. Create build directory. sudo mkdir /opt; sudo chown $USER /opt
 6. Run tool. sh demo-arm-softfloat.sh
 7. Get coffee, it takes a while to build...

Simulators
==========

If you want to run the built targets in a simulated environment
(which, as a first step, is strongly recommended!), then you will also need a 
simulator. See the
`supported simulators page  <simulators.pml>`_ for more information.


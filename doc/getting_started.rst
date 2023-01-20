=================
 Getting started 
=================

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005

Obtaining
=========

If you are reading this file from your disk, chances are you managed
to get the software already. However if you are reading this
on our webpages, it might still be unclear.

The easiest thing to do is simply download the latest tarball
from the
`project page <http://www.ertos.nicta.com.au/software/kenge/iguana-project/latest/>`_.

Alternately, you can get Iguana directly from our
`version control repository <http://www.ertos.nicta.com.au/software/baz-howto.pml>`_.

Making sure you have all the tools
==================================

Before you get started you will want to make sure you have all the tools you need.
This is described in detail on our 
`required tools <http://www.ertos.nicta.com.au/software/kenge/build-tools/latest/required_tools.pml>`_ page.
Basically you need Python, SCons, gcc and a simulator. You probably
need to use gcc-3.3 (see the required tools page for details).

Building
=========

For the impatient::

 $ scons machine=pc99

For a more extensive discussion of the scons based build system,
see the `build system pages <http://www.ertos.nicta.com.au/software/kenge/build-tools/latest/build_system.pml>`_.

Note that you always need to tell the build system what 
machine you want to compile for. We support a lot of IA32 (x86), MIPS and 
ARM targets, which are described in more detail on 
our `supported machines <http://www.ertos.nicta.com.au/software/kenge/build-tools/latest/machines.pml>`_
page.

At this point, either scons built Iguana 
successfully, or it all crashed in a big heap of error messages. In the latter 
case the problem might be something simple to diagnose, (maybe you 
didn't install your cross compiler correctly)
or it might be something a lot more complicated.
In any case, feel free to ask for help on our mailing list, 
`kenge-users@ertos.nicta.com.au <https://lists.ertos.nicta.com.au/mailman/listinfo/kenge-users>`_.

Assuming everything has ``just worked`` up to now,
you should have a bootable image that you can now run. Exactly
what kind of bootable image you have depends on what your target is. For example, on
ia32 it will be a FAT filesystem image with grub installed on it. If your
target is an ARM embedded board then you probably have an ELF file that
can be loaded by your bootloader.

Running
=======

Again for the impatient::

 $ scons machine=pc99 simulate

This requires you to have a supported simulator, see the
`supported simulators page <http://www.ertos.nicta.com.au/software/kenge/build-tools/latest/simulators.pml>`_
for more information on the supported simulators and their usage.

By specifying the simulate target you get the build system to start
up the simulator with all the appropriate flags and configurations for
the chosen platform.

The simulated system should boot up Pistachio, then Iguana, then
Wombat in sequence, and finally drop into a shell running in the
virtual system.

You can also build and run a number of other examples (see the examples
directory), for instance::

 $ scons machine=pc99 example=naming simulate

This example should load a simple test of the naming system, which
should hopefully print that a number of tests passed, and finally
conclude that the naming system works.

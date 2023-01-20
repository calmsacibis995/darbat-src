===================================================
Information about supported simulators
===================================================

:Author: Thomas Sewell <Thomas.Sewell@nicta.com.au>
:Copyright: National ICT Australia, 2005

.. contents::

Overview
========

The use of a simulator is invaluable when doing operating systems
development. We have information on a range of simulators that the
ERTOS program uses during development. Most of the information here
relates to getting L4, and L4 based systems to run on the simulator.

The Kenge build system can be instructed to run these simulators
automatically. Adding 'simulate' to a scons command, for instance,
'scons machine=pc99_serial example=naming simulate', will both build
the project with the given configuration and attempt to run an appropriate
simulator. The arguments passed to the simulators are detailed below.

QEMU
====

QEMU is a full-system simulator for ia32. It simulates peripherals
such as serial interfaces. It has been tested with L4/Iguana and
Wombat.

The source is available from the 
`QEMU website <http://fabrice.bellard.free.fr/qemu/>`_.
QEMU is also available in debian (apt-get install qemu), and
may be packaged for many other systems.

Useful options include:

-fda file_name: Specify a floppy disk image

-hda file_name: Specify a hard disk image

-nographic: Disable VGA simulation, and simulate a serial device
in the console. Highly recommended!

-nics n: Simulate n network cards. Defaults to 1.

-s n: Simulate n MB of memory. Defaults to 128.

The Kenge build system can build a disk image, and set it up
with grub etc, without any user intervention. Once 'scons' has
run, there should be a build/c.img hard disk image. The typical
usage, and the one used by 'scons simulate' when machine=pc99_serial,
is:

qemu -hda build/c.img -nics 0 -nographic

SkyEye
======

SkyEye is an ARM full-system
functional simulator. It has been tested with L4/Iguana and
Wombat.

SkyEye can be obtained from the
`SkyEye website <http://www.skyeye.org/>`_,
and we also have a version available on the
`prebuilt binaries page <http://www.ertos.nicta.com.au/software/prebuilt/binarie
s.pml>`_.

SkyEye is always invoked with a -c configuration argument
and a -e executable argument. Typical usage, and that used by
'scons simulate' when machine=pleb, is:

skyeye -c tools/pleb.skyeye -e build/bootimg.dite

Sulima
======

Sulima is an instruction set architecture simulator
developed locally. See the
`Sulima page <http://www.ertos.nicta.com.au/software/sulima/>`_ 
for further details.

Sulima is typically invoked through the 'u4600' script,
which launches sulima and configures it to simulate the
UNSW U4600 board. Typical usage of the script, and that
used by 'scons simulate' when machine=u4600, is:

u4600 build/bootimg.dite




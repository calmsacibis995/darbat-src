=======================================================
 Information on machines supported by the build system
=======================================================

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005

.. contents::

ARM
====

We support a range of different embedded ARM boards, using a
range of different processors.

Pleb
-----

.. image:: http://www.ertos.nicta.com.au/hardware/pleb/images/pleb.jpg


Pleb2
-----

.. image:: http://www.ertos.nicta.com.au/hardware/pleb/images/pleb2.jpg

PLEB 2 is a single board computer designed to provide a platform on
which both academic research and application implementation can be
accomplished. It has been based on PLEB. More information is
available on the `PLEB2 website <http://www.ertos.nicta.com.au/hardware/pleb/>`_.

The Pleb 2 uses U-boot bootloader, and is simulated using the skyeye
simulator. It is based on the XScale processor.

LN2410SBC
---------


IPAQ H3100, H3600, H3700, H3800 (SA1100-based IPAQs)
----------------------------------------------------

We currently support IPAQs with the StrongARM (sa1100) processor. To boot this machine you will need
the ARM bootloader version 2.21.12 installed on your IPAQ. See 
http://familiar.handhelds.org/releases/v0.8.2/install/bootldr.html for more information
on installing the bootloader::

 boot> load ram 0xc0008000
 (start ymodem)
 boot> jump 0xc0008000

Alternatively if you can boot from a cfcard::

 boot> vfat read 0xc0008000 boot/bootimage
 boot> jump 0xc0008000


MIPS64
=======

Currently just support U4600 out of the box.

u4600
-----

Home grown 64-bit mips machine.


IA32
=====

PC99
----

Support standard PC99 machiens using a variety of booting methods.
=========================================
 Information on how bootable images work
=========================================

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005

Different machines have different methods and requirements for how
they boot. It is often either impossible or impractical to change to
bootloader that is installed on a platform. As a result the build system
tries to accommodate different types of bootloaders and provides 
different bootable images as required.

There are essentially three different ways images are loaded
currently.  Firstly on system with bootloaders that can load an ELF
file we simple provide a packed ELF to load applications. On systems
that simply load a binary image and jump to the start we write our
own *ELF loader* to the start of the image which then unpacks an
ELF file, finally on systems using grub we take advntage of its
ability to load multiple files.

Whether a specific machine uses an ELF loader is defined in the
machine specification in machines.py. If the machine needs an 
ELF loader, specify "elfloader=True". You should also specify
an "elf_entry", which is the address at which the ELF loader should
be linked at. This differs on each machine as the physical memory
layout differs.
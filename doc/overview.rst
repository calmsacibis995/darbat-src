===========
 Overview
===========

:Author: Ben Leslie <ben.leslie@nicta.com.au>
:Copyright: National ICT Australia, 2005


Iguana is designed as a base for the provision of operating system
(OS) services for embedded systems. Among others, it provides
the underlying OS for Wombat, our version
of paravirtualised Linux designed
to provide legacy support for embedded systems.

Iguana runs on top of the L4
microkernel, presently the Version 4 API as implemented by 
L4Ka::Pistachio. It is designed to support a painless transition to the new
security-oriented API being developed for L4.

While it borrows many ideas from the Mungi operating system, Iguana's
target domain of embedded systems requires a different approach to a
number of issues.  The main characteristics of Iguana's design are:

- Iguana complements, rather than hides the underlying L4 API. It
  provides services virtually every OS environment requires, such as
  memory and protection management, and a device driver framework;

- the memory and cache footprints of Iguana are kept small;

- low-overhead sharing of data is supported;

- Iguana supports the separation of protection and translation, by
  encouraging a non-overlapping address-space layout. This means that
  Iguana-based systems can be readily deployed on processors without
  virtual memory, and can also obtain the best possible performance on
  the ARM7 and ARM9 cores widely used in embedded systems.


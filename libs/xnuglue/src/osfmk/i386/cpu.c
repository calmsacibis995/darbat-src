/*
 * cpu.c
 */

#include <kern/kalloc.h>
#include <kern/misc_protos.h>
//#include <kern/machine.h>
//#include <i386/machine_cpu.h>
#include <mach/machine.h>


cpu_type_t
cpu_type(void)
{
	return CPU_TYPE_I386;
}

cpu_subtype_t
cpu_subtype(void)
{
	return CPU_SUBTYPE_PENTPRO;
}

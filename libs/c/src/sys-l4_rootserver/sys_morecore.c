/*
 * sys_morecore.c
 *
 */

#include <stdio.h>	/* NULL */
#include <l4/kdebug.h>

#include "../k_r_malloc.h"

Header *
morecore(unsigned nu)
{
	L4_KDB_Enter("morecore called in sys-l4_roootserver");
	return (NULL);
}


/*
 * sys_tmpfile.c
 *
 */

#include <l4/kdebug.h>

#include <stdio.h>

extern FILE * sys_tmpfile(void);

FILE *
sys_tmpfile(void)
{
	L4_KDB_Enter("sys_tmpfile called in sys-l4_rootserver");
	return (NULL);
}

#include <stdio.h>
#include <l4/kdebug.h>

static size_t
l4kdb_write(void *data, long int position, size_t count, void *handle /*unused*/)
{
	size_t i;
	char *realdata = data;
	for (i = 0; i < count; i++)
		L4_KDB_PrintChar(realdata[i]);
	return count;
}


struct __file __stdin = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
#ifdef THREAD_SAFE
	{0, 0, 0}
#endif
};


struct __file __stdout = {
	NULL,
	NULL,
	l4kdb_write,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
#ifdef THREAD_SAFE
	{0, 0, 0}
#endif
};


struct __file __stderr = {
	NULL,
	NULL,
	l4kdb_write,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
#ifdef THREAD_SAFE
	{0, 0, 0}
#endif
};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

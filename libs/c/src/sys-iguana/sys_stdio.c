#include <stdio.h>
#include <l4/kdebug.h>
#include <l4/ipc.h>

static size_t
l4kdb_write(void *data, long int position, size_t count, void *handle /*unused*/)
{
	size_t i;
	char *real_data = data;
	for (i = 0; i < count; i++)
		L4_KDB_PrintChar(real_data[i]);
	return count;
}

static size_t
l4kdb_read(void *data, long int position, size_t count, void *handle /*unused*/)
{
	size_t i;
	char *real_data = data;
	for (i = 0; i < count; i++) {
		do {
			real_data[i] = L4_KDB_ReadChar();
			if (real_data[i] != 0) {
				break;
			}
			//L4_Sleep(L4_TimePeriod(1000));
		} while(1);
	}
	return count;
}


struct __file __stdin = {
	NULL,
	l4kdb_read,
	NULL,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0,
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
	0,
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
	0,
#ifdef THREAD_SAFE
	{0, 0, 0}
#endif
};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

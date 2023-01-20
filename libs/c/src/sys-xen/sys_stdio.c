#include <stdio.h>
#include <xen/calls.h>

static size_t
xen_write(void *data, long int position, size_t count, void *handle /*unused*/)
{
	char *realdata = data;
	xen_console_io(CONSOLEIO_write, count, realdata);
	return count;
}

static size_t
xen_read(void *data, long int position, size_t count, void *handle /*unused*/)
{
	char *realdata = data;
	xen_console_io(CONSOLEIO_read, count, realdata);
	return count;
}


struct __file __stdin = {
	NULL,
	xen_read,
	NULL,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
};


struct __file __stdout = {
	NULL,
	NULL,
	xen_write,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
};


struct __file __stderr = {
	NULL,
	NULL,
	xen_write,
	NULL,
	NULL,
	_IONBF,
	NULL,
	0,
	0
};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

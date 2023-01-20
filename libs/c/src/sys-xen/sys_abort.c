#include <stdlib.h>
#include <stdio.h>

void
abort(void)
{
	printf("ABORT!");
	while(1); /* We don't return after this */
}

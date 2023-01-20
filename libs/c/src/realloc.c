/*
 * K&R Malloc 
 *
 * System specifc code should implement `more_core'
 */

#include "k_r_malloc.h"
#include <stdlib.h>
#include <string.h>

#ifdef THREAD_SAFE
#include <mutex/mutex.h>
extern struct kenge_mutex malloc_mutex;
#define MALLOC_LOCK kenge_mutex_count_lock(&malloc_mutex)
#define MALLOC_UNLOCK kenge_mutex_count_unlock(&malloc_mutex)
#else
#define MALLOC_LOCK
#define MALLOC_UNLOCK
#endif

void *
realloc(void *ptr, size_t size)
{
	Header *bp;
	void *new_ptr;
	size_t old_size;

	if (ptr == NULL)
		return malloc(size);
	bp = (Header *) ptr - 1; /* point to block header */
	old_size = sizeof(Header) * bp->s.size;
	new_ptr = malloc(size);
	if (new_ptr == NULL) {
		return NULL;
	}
	if (old_size <= size) {
		memcpy(new_ptr, ptr, old_size);
	} else {
		memcpy(new_ptr, ptr, size);
	}
	free(ptr);
	return new_ptr;
}

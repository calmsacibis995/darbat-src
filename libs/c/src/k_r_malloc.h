#ifndef _LIBC_K_R_MALLOC_H_
#define _LIBC_K_R_MALLOC_H_

#define NALLOC  0x10000		/* minimum #units to request */

typedef long long Align;	/* for alignment to long long boundary */

union header {			/* block header */
	struct {
		union header   *ptr;	/* next block if on free list */
		unsigned        size;	/* size of this block */
	} s;
	Align           x;	/* force alignment of blocks */
};

typedef union header Header;

Header  *morecore(unsigned nu);
void __malloc_init(void*, void*);
#endif /* _LIBC_K_R_MALLOC_H_ */

/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * symhash.c
 *
 * Geoffrey Lee < glee at cse unsw edu au >
 */

/*
 * This file is meant to record down all of the symbols of what was loaded,
 * so that we do not have to parse things every time.
 *
 * It deliberately duplicates the information, as what was given to it
 * might actually have been part of a file (in which case, it could be
 * freed later on.  The contractual agreement between the caller and the callee
 * is the callee (us) will save whatever information we need.  
 *
 * It only does 32-bit right now ... it can easily be extended to do 
 * 64-bit too but it is simply not necessary.
 */

#include <lkm/lkm.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lkm_hash {
	char		*name;
	uint32_t	addr;
	struct lkm_hash	*next;
};

static int	lkm_hashsiz;

/*
 * XXX
 *
 * Localize?  We could pass this in as the first arg.
 */
static struct lkm_hash	**lkm_hashtab;

int
lkm_hashinit(siz)
	uint32_t	siz;
{
	int	i;

	lkm_hashtab = malloc(sizeof(struct lkm_hash *) * siz);
	if (!lkm_hashtab)
		return ELKMNOMEM;

	for (i = 0; i < siz; i++)
		lkm_hashtab[i] = NULL;

	lkm_hashsiz = siz;

	return ELKMSUCCESS;
}

/*
 * lkm_hashput
 *
 * Puts a symbol with corresponding address into the hash table.
 *
 * XXX We currently do not handle weak symbols XXX
 * XXX and other fancy things at this point    XXX
 */
int
lkm_hashput(sym, addr)
	const char	*sym;
	uint32_t	addr;
{
	struct lkm_hash	*hashent, *p;
	uint32_t	h;

	h = elf_hash(sym) % lkm_hashsiz;	/* XXX MISNAMED XXX */

	/*
	 * XXX How to best handle this?
	 *
	 * We should never add _start.  I am not quite sure if returning
	 * ELKMSUCCESS is the right thing to do here.
	 */
	if (strcmp(sym, "_start") == 0)
		return ELKMSUCCESS;

	/*
	 * Make sure that no such symbol exists in the hash.
	 *
	 * Hopefully, this is a short transversal.
	 */
	for (p = lkm_hashtab[h]; p != NULL; p = p->next) {
		if (strcmp(p->name, sym) == 0)
			return ELKMSYMEXISTS;
	}

	hashent = malloc(sizeof(struct lkm_hash));
	if (!hashent)
		return ELKMNOMEM;

	hashent->name = malloc(strlen(sym) + 1);
	strcpy(hashent->name, sym);
	hashent->addr = addr;

	hashent->next = lkm_hashtab[h];
	lkm_hashtab[h] = hashent;

	return ELKMSUCCESS;
}

/*
 * lkm_hashdelete
 *
 * Delete a symbol from the hash table.
 */
int
lkm_hashdelete(sym)
	const char	*sym;
{
	struct lkm_hash	*hashent, *prev;
	uint32_t	h;

	h = elf_hash(sym) % lkm_hashsiz;

	for (hashent = lkm_hashtab[h], prev = NULL; 
	    hashent != NULL; 
	    prev = hashent, hashent = hashent->next) {
		if (strcmp(hashent->name, sym) == 0) {
			if (!prev)
				lkm_hashtab[h] = hashent->next;
			else
				prev->next = hashent->next;
			free(hashent->name);
			free(hashent);
			return (ELKMSUCCESS);
		}
	}
	return (ELKMNOSYM);
}
	

/*
 * lkm_hashget
 *
 * Given the name of a certain symbol, lookup the address.
 * ELKMSUCCESS on success, ELKMNOSYM if it cannot find the sym.
 */
int
lkm_hashget(sym, addr)
	const char	*sym;
	uint32_t	*addr;
{
	uint32_t	h;
	struct lkm_hash	*hashent;

	h = elf_hash(sym) % lkm_hashsiz;

	for (hashent = lkm_hashtab[h]; 
	    hashent != NULL; 
	    hashent = hashent->next) {

		if (strcmp(hashent->name, sym) == 0) {
		
			if (addr)
				*addr = hashent->addr;

			return ELKMSUCCESS;
		}
	}

	return ELKMNOSYM;
}

/*
 * lkm_hashfini
 *
 * Destroy the hash table.
 * XXX NOT YET IMPLEMENTED XXX
 */
int
lkm_hashfini(void)
{

	assert(!"shit");
	return ELKMSUCCESS;
}


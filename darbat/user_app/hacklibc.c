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

#include <stdlib.h>

#include "hacklibc.h"

void *
memset(void *b, int c, size_t len)
{
	char *d;
	int i;

	d = b;

	for( i = 0; i < len; i++ )
		d[i] = c;

	return d;
}

int
strlen( const char *buf )
{
	int len = 0;

	while( buf[len] != '\0' )
		len++;

	return len;
}

char *
strcpy(char *d, char *s)
{
	size_t          i;

	for (i = 0; (d[i] = s[i]) != '\0'; i++);
	return d;
}


char *
strcat(char *s, char *t)
{
	strcpy(s + strlen(s), t);
	return s;
}

int
strcmp(const char *s1, const char *s2)
{
	size_t i;
	int diff;

	for (i = 0;; i++) {
		diff =
		    ((unsigned char *) s1)[i] - ((unsigned char *) s2)[i];
		if (diff != 0 || s1[i] == '\0')
			return diff;
	}
}

size_t
strspn(const char *s, const char *charset)
{
	size_t i;

	for (i = 0; strchr(charset, s[i]) != NULL && s[i] != '\0'; i++);
	return i;
}

size_t
strcspn(const char *s, const char *charset)
{
	size_t i;
	size_t len = strlen(s);

	for (i = 0; strchr(charset, s[i]) == NULL && i < len; i++);

	return i;
}

char *
strtok(char *s, const char *delim)
{
	static char *tok;

	if (s == NULL)
		s = tok;	/* recommence just after last token */
	s += strspn(s, delim);	/* skip leading delimeters */
	if (*s == '\0')
		return NULL;
	tok = s + strcspn(s, delim);	/* remember end of token string */
	if (*tok != '\0')
		*(tok)++ = '\0';	/* terminate token string */
	return s;
}

char *
strchr(const char *s, int c)
{
	for (; *s != '\0'; s++)
		if (*s == c)
			return (char *) s;
	if (c == '\0') 
		return (char *) s;
	return NULL;
}

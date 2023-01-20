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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef int boolean_t;

#define Ctod(c) ((c) - '0')
static char digs[] = "0123456789abcdef";
#define MAXBUF (sizeof(long long int) * 8)	/* enough for binary */

#define TRUE  1
#define FALSE 0

static int
printnum(
	register unsigned long long int	u,	/* number to print */
	register int		base,
	void			(*putc)(int, void *),
	void                    *arg)
{
	char	buf[MAXBUF];	/* build number here */
	register char *	p = &buf[MAXBUF-1];
	int nprinted = 0;

	do {
	    *p-- = digs[u % base];
	    u /= base;
	} while (u != 0);

	while (++p != &buf[MAXBUF]) {
	    (*putc)(*p, arg);
	    nprinted++;
	}

	return nprinted;
}


boolean_t	_doprnt_truncates = FALSE;

int
__doprnt(
	register const char	*fmt,
	va_list			*argp,
						/* character output routine */
	void			(*putc)(int, void *arg),
	void                    *arg,
	int			radix);		/* default radix - for '%r' */


int
__doprnt(
	register const char	*fmt,
	va_list			*argp,
						/* character output routine */
	void			(*putc)(int, void *arg),
	void                    *arg,
	int			radix)		/* default radix - for '%r' */
{
	int		length;
	int		prec;
	boolean_t	ladjust;
	char		padc;
	long long		n;
	unsigned long long	u;
	int		plus_sign;
	int		sign_char;
	boolean_t	altfmt, truncate;
	int		base;
	register char	c;
	int		capitals;
	int		long_long;
	int             nprinted = 0;

	while ((c = *fmt) != '\0') {
	    if (c != '%') {
		(*putc)(c, arg);
		nprinted++;
		fmt++;
		continue;
	    }

	    fmt++;

	    long_long = 0;
	    length = 0;
	    prec = -1;
	    ladjust = FALSE;
	    padc = ' ';
	    plus_sign = 0;
	    sign_char = 0;
	    altfmt = FALSE;

	    while (TRUE) {
		c = *fmt;
		if (c == '#') {
		    altfmt = TRUE;
		}
		else if (c == '-') {
		    ladjust = TRUE;
		}
		else if (c == '+') {
		    plus_sign = '+';
		}
		else if (c == ' ') {
		    if (plus_sign == 0)
			plus_sign = ' ';
		}
		else
		    break;
		fmt++;
	    }

	    if (c == '0') {
		padc = '0';
		c = *++fmt;
	    }

	    if (isdigit(c)) {
		while(isdigit(c)) {
		    length = 10 * length + Ctod(c);
		    c = *++fmt;
		}
	    }
	    else if (c == '*') {
		length = va_arg(*argp, int);
		c = *++fmt;
		if (length < 0) {
		    ladjust = !ladjust;
		    length = -length;
		}
	    }

	    if (c == '.') {
		c = *++fmt;
		if (isdigit(c)) {
		    prec = 0;
		    while(isdigit(c)) {
			prec = 10 * prec + Ctod(c);
			c = *++fmt;
		    }
		}
		else if (c == '*') {
		    prec = va_arg(*argp, int);
		    c = *++fmt;
		}
	    }

	    if (c == 'l') {
		c = *++fmt;	/* need it if sizeof(int) < sizeof(long) */
		if (c == 'l') {
		    long_long = 1;
		    c = *++fmt;
		}	
	    } else if (c == 'q' || c == 'L') {
	    	long_long = 1;
		c = *++fmt;
	    } 

	    truncate = FALSE;
	    capitals=0;		/* Assume lower case printing */

	    switch(c) {
		case 'b':
		case 'B':
		{
		    register char *p;
		    boolean_t	  any;
		    register int  i;

		    if (long_long) {
			u = va_arg(*argp, unsigned long long);
		    } else {
			u = va_arg(*argp, unsigned long);
		    }
		    p = va_arg(*argp, char *);
		    base = *p++;
		    nprinted += printnum(u, base, putc, arg);

		    if (u == 0)
			break;

		    any = FALSE;
		    while ((i = *p++) != '\0') {
			if (*fmt == 'B')
			    i = 33 - i;
			if (*p <= 32) {
			    /*
			     * Bit field
			     */
			    register int j;
			    if (any)
				(*putc)(',', arg);
			    else {
				(*putc)('<', arg);
				any = TRUE;
			    }
			    nprinted++;
			    j = *p++;
			    if (*fmt == 'B')
				j = 32 - j;
			    for (; (c = *p) > 32; p++) {
				(*putc)(c, arg);
				nprinted++;
			    }
			    nprinted += printnum((unsigned)( (u>>(j-1)) & ((2<<(i-j))-1)),
						 base, putc, arg);
			}
			else if (u & (1<<(i-1))) {
			    if (any)
				(*putc)(',', arg);
			    else {
				(*putc)('<', arg);
				any = TRUE;
			    }
			    nprinted++;
			    for (; (c = *p) > 32; p++) {
				(*putc)(c, arg);
				nprinted++;
			    }
			}
			else {
			    for (; *p > 32; p++)
				continue;
			}
		    }
		    if (any) {
			(*putc)('>', arg);
			nprinted++;
		    }
		    break;
		}

		case 'c':
		    c = va_arg(*argp, int);
		    (*putc)(c, arg);
		    nprinted++;
		    break;

		case 's':
		{
		    register char *p;
		    register char *p2;

		    if (prec == -1)
			prec = 0x7fffffff;	/* MAXINT */

		    p = va_arg(*argp, char *);

		    if (p == (char *)0)
			p = "";

		    if (length > 0 && !ladjust) {
			n = 0;
			p2 = p;

			for (; *p != '\0' && n < prec; p++)
			    n++;

			p = p2;

			while (n < length) {
			    (*putc)(' ', arg);
			    n++;
			    nprinted++;
			}
		    }

		    n = 0;

		    while (*p != '\0') {
			if (++n > prec || (length > 0 && n > length))
			    break;

			(*putc)(*p++, arg);
			nprinted++;
		    }

		    if (n < length && ladjust) {
			while (n < length) {
			    (*putc)(' ', arg);
			    n++;
			    nprinted++;
			}
		    }

		    break;
		}

		case 'o':
		    truncate = _doprnt_truncates;
		case 'O':
		    base = 8;
		    goto print_unsigned;

		case 'D': {
		    unsigned char *up;
		    char *q, *p;
		    
			up = (unsigned char *)va_arg(*argp, unsigned char *);
			p = (char *)va_arg(*argp, char *);
			if (length == -1)
				length = 16;
			while(length--) {
				(*putc)(digs[(*up >> 4)], arg);
				(*putc)(digs[(*up & 0x0f)], arg);
				nprinted += 2;
				up++;
				if (length) {
				    for (q=p;*q;q++) {
						(*putc)(*q, arg);
						nprinted++;
				    }
				}
			}
			break;
		}

		case 'd':
		    truncate = _doprnt_truncates;
		    base = 10;
		    goto print_signed;

		case 'u':
		    truncate = _doprnt_truncates;
		case 'U':
		    base = 10;
		    goto print_unsigned;

		case 'p':
		    altfmt = TRUE;
		case 'x':
		    truncate = _doprnt_truncates;
		    base = 16;
		    goto print_unsigned;

		case 'X':
		    base = 16;
		    capitals=16;	/* Print in upper case */
		    goto print_unsigned;

		case 'z':
		    truncate = _doprnt_truncates;
		    base = 16;
		    goto print_signed;
			
		case 'Z':
		    base = 16;
		    capitals=16;	/* Print in upper case */
		    goto print_signed;

		case 'r':
		    truncate = _doprnt_truncates;
		case 'R':
		    base = radix;
		    goto print_signed;

		case 'n':
		    truncate = _doprnt_truncates;
		case 'N':
		    base = radix;
		    goto print_unsigned;

		print_signed:
		    if (long_long) {
			n = va_arg(*argp, long long);
		    } else {
			n = va_arg(*argp, long);
		    }
		    if (n >= 0) {
			u = n;
			sign_char = plus_sign;
		    }
		    else {
			u = -n;
			sign_char = '-';
		    }
		    goto print_num;

		print_unsigned:
		    if (long_long) {
			u = va_arg(*argp, unsigned long long);
		    } else { 
			u = va_arg(*argp, unsigned long);
		    }
		    goto print_num;

		print_num:
		{
		    char	buf[MAXBUF];	/* build number here */
		    register char *	p = &buf[MAXBUF-1];
		    static char digits[] = "0123456789abcdef0123456789ABCDEF";
		    char *prefix = 0;

		    if (truncate) u = (long long)((int)(u));

		    if (u != 0 && altfmt) {
			if (base == 8)
			    prefix = "0";
			else if (base == 16)
			    prefix = "0x";
		    }

		    do {
			/* Print in the correct case */
			*p-- = digits[(u % base)+capitals];
			u /= base;
		    } while (u != 0);

		    length -= (&buf[MAXBUF-1] - p);
		    if (sign_char)
			length--;
		    if (prefix)
			length -= strlen((const char *) prefix);

		    if (padc == ' ' && !ladjust) {
			/* blank padding goes before prefix */
			while (--length >= 0) {
			    (*putc)(' ', arg);
			    nprinted++;
			}			    
		    }
		    if (sign_char) {
			(*putc)(sign_char, arg);
			nprinted++;
		    }
		    if (prefix) {
			while (*prefix) {
			    (*putc)(*prefix++, arg);
			    nprinted++;
			}
		    }
		    if (padc == '0') {
			/* zero padding goes after sign and prefix */
			while (--length >= 0) {
			    (*putc)('0', arg);
			    nprinted++;
			}			    
		    }
		    while (++p != &buf[MAXBUF]) {
			(*putc)(*p, arg);
			nprinted++;
		    }
		    
		    if (ladjust) {
			while (--length >= 0) {
			    (*putc)(' ', arg);
			    nprinted++;
			}
		    }
		    break;
		}

		case '\0':
		    fmt--;
		    break;

		default:
		    (*putc)(c, arg);
		    nprinted++;
	    }
	fmt++;
	}

	return nprinted;
}

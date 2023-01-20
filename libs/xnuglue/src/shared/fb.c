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
 * fb.c
 *
 * Many thanks to Michael Steil of the Darwin/x86 Xbox project.
 */

#include <assert.h>
#include <string.h>

#include <iguana/memsection.h>	/* Iguana */
#include <iguana/hardware.h>	/* Iguana */

#include <fb.h>

static COLOR		*framebuffer;
static int		screen_width;
static int		screen_height;
static int		bytes_per_pixel;
static unsigned		cur_x;
static unsigned		cur_y;
static unsigned		cur_attr;

/* XXX */
extern unsigned char	iso_font[256 * 16];

/*
 * XXX
 * 
 * Extra information that should be set up during fb_init()
 *
 * Mac Mini: fb @ 0x80000000 (???x800/2048)
 * iMac 17: 0x80010000 (1440x900/1472 or 1680x1050/1728 for 20inch.)
 */
void
fb_clrscrn(void)
{

	memset(framebuffer, 0, screen_width * screen_height * bytes_per_pixel);
}


#define IMAC_FB		(0x80010000)
#define MACMINI_FB	(0x80000000)

#if 0
#define FBADDR IMAC_FB
#else
#define FBADDR MACMINI_FB
#endif

void *
fb_init( int clr )
{
	memsection_ref_t	ref;
	uintptr_t		fbaddr;

	ref = memsection_create_user(64 * 1024 * 1024, &fbaddr);
	assert(fbaddr);
	hardware_back_memsection(ref, FBADDR, MEM_NORMAL);
	framebuffer = (void *)fbaddr;

//	screen_width = 1472;
	screen_width = 2048;
//	screen_height = 900;
//	screen_height = 1000;
	screen_height = 800;
	bytes_per_pixel = 4;
	cur_x = 0;
	cur_y = 0;
	cur_attr = 0x0f;
	if( clr )
		fb_clrscrn();

	return (void*) fbaddr;
}

COLOR
fb_vgaattr_to_color(attr)
	unsigned char		attr;
{
	unsigned char		intensity = (attr & 8) ? 255 : 127;

	return ((attr & 4) ? intensity << 16 : 0) | 
	    ((attr & 2) ? intensity << 8 : 0) | 
	    ((attr & 1) ? intensity : 0);
}

void
fb_putchar(c, attr, px, py)
	char		c;
	unsigned char	attr;
	unsigned int	px, py;
{
	unsigned int	x, y;
	COLOR		fgcolor, bgcolor;

	fgcolor = fb_vgaattr_to_color(attr);
	bgcolor = fb_vgaattr_to_color(attr >> 4);

	for (y = 0; y < CHAR_HEIGHT; y++) {
		for (x = 0; x < CHAR_WIDTH; x++) {
			framebuffer[(py * CHAR_HEIGHT + y) * (screen_width) +
			    px * CHAR_WIDTH + x] = 
			    (iso_font[c * 16 + y] & (1 << x)) ? fgcolor : 
			    bgcolor;
		}
	}
}

void
fb_scroll(void)
{
	/*DISABLED*/
}

void
fb_putchar_interp(c)
	unsigned char	c;
{

	switch (c) {
		case '\n':	/* LF */
			if (cur_y < screen_height / CHAR_HEIGHT - 1)
				cur_y++;
			else
				fb_scroll();
			/*FALLTHROUGH*/
		case '\r':	/* CR */
			cur_x = 0;
			break;
		case 8:		/* BS */
			if (cur_x == 0) {
				if (cur_y != 0) {
					cur_y--;
					cur_x = screen_width / CHAR_WIDTH - 1;
				}
			} else
				cur_x--;
			break;
		default:
			fb_putchar(c, cur_attr, cur_x, cur_y);
			cur_x++;
			if (cur_x >= (screen_width / CHAR_WIDTH))
				fb_putchar_interp('\n');
	}
}

void
fb_puts(s)
	const char	*s;
{

	for (; *s; s++)
		fb_putchar_interp(*s);

	fb_putchar_interp('\n');
}

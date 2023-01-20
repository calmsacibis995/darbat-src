/*********************************************************************
 *                
 * Copyright (C) 2001, 2004-2003,  Karlsruhe University
 *                
 * File path:     kdb/platform/pc99/io.cc
 * Description:   PC99 specific I/O functions
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: io.cc,v 1.24 2004/04/27 22:59:37 stoess Exp $
 *                
 ********************************************************************/
#include <macros.h>
#include <types.h>
#include <config.h>
#include INC_ARCH(cpu.h)
#include INC_ARCH(ioport.h)
#include INC_API(tcb.h)
#include <kdb/kdb.h>
#include <kdb/init.h>
#include <kdb/input.h>
#include <kdb/cmd.h>
#include <kdb/console.h>
#include <init.h>
#include <debug.h>
#include <linear_ptab.h>

#if !defined(CONFIG_KDB_COMPORT)
#define CONFIG_KDB_COMPORT 0x3f8
#endif

#if !defined(CONFIG_KDB_COMSPEED)
#define CONFIG_KDB_COMSPEED 115200
#endif

#define KERNEL_VIDEO		(KERNEL_OFFSET + 0xb8000)
#define KERNEL_VIDEO_HERC	(0xF00b0000)

#ifdef __ELF__
#define SEC_PC99_IO		".kdebug"
#elif defined(__APPLE_CC__)
#define SEG_PC99_IO		"__KDEBUG"
#define SEC_PC99_IO		"__kdebug"
#else
#error "unknown compiler"
#endif


/* Section assignements */
#ifdef __ELF__
static void putc_screen (char) SECTION (SEC_PC99_IO);
static char getc_screen (bool) SECTION (SEC_PC99_IO);
static void putc_serial (char) SECTION (SEC_PC99_IO);
static char getc_serial (bool) SECTION (SEC_PC99_IO);
static void init_serial (void) SECTION (SEC_PC99_IO);
#elif defined(__APPLE_CC__)
static void putc_screen (char) SECTION (SEG_PC99_IO,SEC_PC99_IO);
static char getc_screen (bool) SECTION (SEG_PC99_IO,SEC_PC99_IO);
static void putc_serial (char) SECTION (SEG_PC99_IO,SEC_PC99_IO);
static char getc_serial (bool) SECTION (SEG_PC99_IO,SEC_PC99_IO);
static void init_serial (void) SECTION (SEG_PC99_IO,SEC_PC99_IO);
#else
#error "unknown compiler"
#endif


/* XXX */
#ifdef __ELF__
#define SEC_EFI_IO		".kdebug"
void init_dbg1394(void) SECTION (SEC_EFI_IO);
void putc_dbg1394(char) SECTION (SEC_EFI_IO);
char getc_dbg1394(bool) SECTION (SEC_EFI_IO);
#elif defined(__APPLE_CC__)
#define SEC_EFI_IO		"__kdebug"
#define SEG_EFI_IO		"__KDEBUG"
void init_dbg1394(void) SECTION (SEG_EFI_IO,SEC_EFI_IO);
void putc_dbg1394(char) SECTION (SEG_EFI_IO,SEC_EFI_IO);
char getc_dbg1394(bool) SECTION (SEG_EFI_IO, SEC_EFI_IO);
#else
#error "unknown compiler"
#endif

kdb_console_t kdb_consoles[] = {
    { "screen", NULL, &putc_screen, &getc_screen },
    { "serial", &init_serial, &putc_serial, &getc_serial },
#ifdef CONFIG_EFI
    { "firewire", &init_dbg1394, &putc_dbg1394, &getc_dbg1394 },
#endif
    KDB_NULL_CONSOLE
};
    
#if defined(CONFIG_KDB_CONS_COM)
word_t kdb_current_console = 1;
#elif defined(CONFIG_EFI)
word_t kdb_current_console = 2; /* XXX */
#endif



/*
**
** Console I/O functions.
**
*/
#if defined(CONFIG_DEBUGGER_IO_SCREEN_HERC)
# define DISPLAY ((char *) KERNEL_VIDEO_HERC)
# define NUM_LINES (25)
# define NUM_COLS (80)
#else
# define DISPLAY ((char *) KERNEL_VIDEO)
# define NUM_LINES (25)
# define NUM_COLS  (80)
#endif

static void putc_screen (char c)
{
    static unsigned cursor = 160 * (NUM_LINES - 1) ;
    static unsigned color = 7;
    static unsigned new_color = 0;
    static unsigned esc = 0;
    static unsigned esc2 = 0;
    static const unsigned col[] = { 0, 4, 2, 14, 1, 5, 3, 15 };

    if (esc == 1)
    {
	if (c == '[')
	{
	    esc++;
	    return;
	}
    }
    else if (esc == 2)
    {
	switch (c)
	{
	case '0': case '1': case '2':
	case '3': case '4': case '7':
	    esc++;
	    esc2 = c;
	    return;
	}
    }
    else if (esc == 3)
    {
	switch (c)
	{
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
	    if (esc2 == '3' || esc2 == '4')
	    {
		// New foreground or background color
		new_color = col[c - '0'];
		esc++;
		return;
	    }
	    break;
	case 'J':
	    if (esc2 == '2')
	    {
		// Clear screen
		for (int i = 0; i < 80*NUM_LINES; i++)
		    ((u16_t *) DISPLAY)[i] = (color << 8) + ' ';
		cursor = 0;
		esc = 0;
		return;
	    }
	    break;
	case 'm':
	    switch (esc2)
	    {
	    case '0':
		// Normal text
		color = 7;
		esc = 0;
		return;
	    case '1':
		// Bright text
		color = 15;
		esc = 0;
		return;
	    case  '7':
		// Reversed
		color = (7 << 4);
		esc = 0;
		return;
	    }
	}
    }
    else if (esc == 4)
    {
	if (c == 'm' && esc2 == '3')
	{
	    // Foreground color
	    color = (color & 0xf0) | new_color;
	    esc = 0;
	    return;
	}
	else if (c == 'm' && esc2 == '4')
	{
	    // Background color
	    color = (color & 0x0f) | (new_color << 4);
	    esc = 0;
	    return;
	}
    }


    switch(c) {
    case '\e':
	esc = 1;
	return;
    case '\r':
        cursor -= (cursor % cursor % (NUM_COLS * 2));
	break;
    case '\n':
	cursor += ((NUM_COLS * 2) - (cursor % (NUM_COLS * 2)));
	break;
    case '\t':
	cursor += (8 - (cursor % 8));
	break;
    case '\b':
	cursor -= 2;
	break;
    default:
	DISPLAY[cursor++] = c;
	DISPLAY[cursor++] = color;
    }

    esc = 0;

    if ((cursor /  (NUM_COLS * 2)) == NUM_LINES)
	{
	    for (int i = NUM_COLS; i < NUM_COLS*NUM_LINES; i++)
		((u16_t *) DISPLAY)[i - NUM_COLS] = ((u16_t *) DISPLAY)[i];
	    for (int i = 0; i < NUM_COLS; i++)
		((u16_t * )DISPLAY)[NUM_COLS * (NUM_LINES-1) + i] = 0;
	    cursor -= (NUM_COLS*2);
    }
}

#define KBD_STATUS_REG		0x64	
#define KBD_CNTL_REG		0x64	
#define KBD_DATA_REG		0x60	

#define KBD_STAT_OBF 		0x01	/* Keyboard output buffer full */

#define kbd_read_input() in_u8(KBD_DATA_REG)
#define kbd_read_status() in_u8(KBD_STATUS_REG)

static unsigned char keyb_layout[2][128] =
{
    "\000\0331234567890-=\010\t"			/* 0x00 - 0x0f */
    "qwertyuiop[]\r\000as"				/* 0x10 - 0x1f */
    "dfghjkl;'`\000\\zxcv"				/* 0x20 - 0x2f */
    "bnm,./\000*\000 \000\201\202\203\204\205"		/* 0x30 - 0x3f */
    "\206\207\210\211\212\000\000789-456+1"		/* 0x40 - 0x4f */
    "230\177\000\000\213\214\000\000\000\000\000\000\000\000\000\000"
    "\r\000/"						/* 0x60 - 0x6f */
    ,
    "\000\033!@#$%^&*()_+\010\t"			/* 0x00 - 0x0f */
    "QWERTYUIOP{}\r\000AS"				/* 0x10 - 0x1f */
    "DFGHJKL:\"`\000\\ZXCV"				/* 0x20 - 0x2f */
    "BNM<>?\000*\000 \000\201\202\203\204\205"		/* 0x30 - 0x3f */
    "\206\207\210\211\212\000\000789-456+1"		/* 0x40 - 0x4f */
    "230\177\000\000\213\214\000\000\000\000\000\000\000\000\000\000"
    "\r\000/"						/* 0x60 - 0x6f */
};

static char getc_screen (bool block)
{
    static u8_t last_key = 0;
    static u8_t shift = 0;
    char c;
    while(1) {
	unsigned char status = kbd_read_status();
	while (status & KBD_STAT_OBF) {
	    u8_t scancode;
	    scancode = kbd_read_input();
	    /* check for SHIFT-keys */
	    if (((scancode & 0x7F) == 42) || ((scancode & 0x7F) == 54))
	    {
		shift = !(scancode & 0x80);
		continue;
	    }
	    /* ignore all other RELEASED-codes */
	    if (scancode & 0x80)
		last_key = 0;
	    else if (last_key != scancode)
	    {
		last_key = scancode;
		c = keyb_layout[shift][scancode];
		if (c > 0) return c;
	    }
	}
    }
}



/*
**
** Serial port I/O functions.
**
*/

#define COMPORT		CONFIG_KDB_COMPORT
#define RATE		CONFIG_KDB_COMSPEED

static void init_serial (void)
{
#define IER	(COMPORT+1)
#define EIR	(COMPORT+2)
#define LCR	(COMPORT+3)
#define MCR	(COMPORT+4)
#define LSR	(COMPORT+5)
#define MSR	(COMPORT+6)
#define DLLO	(COMPORT+0)
#define DLHI	(COMPORT+1)

    out_u8(LCR, 0x80);		/* select bank 1	*/
    for (volatile int i = 10000000; i--; );
    out_u8(DLLO, (((115200/RATE) >> 0) & 0x00FF));
    out_u8(DLHI, (((115200/RATE) >> 8) & 0x00FF));
    out_u8(LCR, 0x03);		/* set 8,N,1		*/
    out_u8(IER, 0x00);		/* disable interrupts	*/
    out_u8(EIR, 0x07);		/* enable FIFOs	*/
    out_u8(IER, 0x01);		/* enable RX interrupts	*/
    in_u8(IER);
    in_u8(EIR);
    in_u8(LCR);
    in_u8(MCR);
    in_u8(LSR);
    in_u8(MSR);
}


static void putc_serial (const char c)
{
    while ((in_u8(COMPORT+5) & 0x60) == 0);
    out_u8(COMPORT,c);
    if (c == '\n')
	putc_serial('\r');

}

static char getc_serial (bool block)
{
    if ((in_u8(COMPORT+5) & 0x01) == 0)
    {
	if (!block)
	    return -1;
	while ((in_u8(COMPORT+5) & 0x01) == 0);
    }
    return in_u8(COMPORT);
}

#if defined(CONFIG_KDB_BREAKIN) && !defined(CONFIG_EFI)
void SECTION (SEC_PC99_IO) kdebug_check_breakin (void)
{
    if ((in_u8(COMPORT+5) & 0x01))
	if (in_u8(COMPORT) == 0x1b)
	    enter_kdebug("breakin");
}
#endif


DECLARE_CMD (cmd_dumpvga, arch, 'V', "screendump", "dump VGA screen contents");

CMD(cmd_dumpvga, cg)
{
    addr_t display = (addr_t) get_hex ("VGA base:", KERNEL_VIDEO, "VGA screen");
    space_t *space = get_space ("Space");
    space = space ? space : get_kernel_space();

    printf("VGA screen dump %p\n"
	   "========================================"
	   "========================================", display);

    do {
	for (unsigned y = 0; y < 25; y++)           // rows
	{
	    printf("\n");
	    for (unsigned x = 0; x < 80; x++)       // columns
	    {
	    
		unsigned char v;
		readmem(space, addr_offset(display, y*160 + 2*x), &v);
		printf ("%c", ((v >= 32 && v < 127) ||
			       (v >= 161 && v <= 191) ||
			       (v >= 224)) ? v : (v == 0) ? ' ' : '.');
	    }
	}
	printf("\n"
	       "========================================"
	       "========================================\n");
    
	display = addr_offset (display, 80 * 25 * 2);
    } while (get_choice ("Continue?", "Continue/Quit", 'c') != 'q');
    
    return CMD_NOQUIT;
}

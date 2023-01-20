/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2004 National ICT Australia
 * 
 * All rights reserved. 
 * 
 * Developed by: Embedded, Real-time and Operating Systems Program (ERTOS)
 *               National ICT Australia
 *               http://www.ertos.nicta.com.au
 * 
 * Permission is granted by National ICT Australia, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of National ICT Australia, nor the names of its
 *       contributors, may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
 * PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
 * NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
 * WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
 * REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
 * THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
 * ERRORS, WHETHER OR NOT DISCOVERABLE.
 * 
 * TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
 * NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
 * THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
 * LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
 * OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
 * OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
 * OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
 * CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
 * CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
 * CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
 * DAMAGES OR OTHER LIABILITY.
 * 
 * If applicable legislation implies representations, warranties, or
 * conditions, or imposes obligations or liability on National ICT
 * Australia or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of National ICT Australia or the contributor is limited, to
 * the full extent permitted by the applicable legislation, at its
 * option, to:
 * a.  in the case of goods, any one or more of the following:
 * i.  the replacement of the goods or the supply of equivalent goods;
 * ii.  the repair of the goods;
 * iii. the payment of the cost of replacing the goods or of acquiring
 *  equivalent goods;
 * iv.  the payment of the cost of having the goods repaired; or
 * b.  in the case of services:
 * i.  the supplying of the services again; or
 * ii.  the payment of the cost of having the services supplied again.
 * 
 * The construction, validity and performance of this licence is governed
 * by the laws in force in New South Wales, Australia.
 */
/*
  Author: Ben Leslie
  Created: Thu Jun  2 2005 
*/

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <naming/naming.h>
#include <l4/thread.h>
#include <l4/kdebug.h>
#include <iguana/debug.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>

//#ifdef ARCH_IA32
//#include <pci.h>
//#endif

#define MAX_COMMAND 100
static char command[MAX_COMMAND];

enum mode { SHELL, LUA };

static const luaL_reg lualibs[] = {
        { "base",       luaopen_base },
        { "table",      luaopen_table },
        { "io",         luaopen_io },
        { "string",     luaopen_string },
        { "debug",      luaopen_debug },
        { "loadlib",    luaopen_loadlib },
	//#ifdef ARCH_IA32
	//        { "pci",        luaopen_pci },
	//#endif
        { NULL,         NULL }
};

static void
openlualibs(lua_State *l)
{
        const luaL_reg *lib;

        for (lib = lualibs; lib->func != NULL; lib++) {
                lib->func(l);           /* Open the library */
                /* 
                 * Flush the stack, by setting the top to 0, in order to
                 * ignore any result given by the library load function.
                 */
                lua_settop(l, 0);
        }
}

/* Get a character and provide and translation fixups */
static char 
sh_getchar(void)
{
	char c = getchar();

	/* Fixup \r -> \n */
	if (c == '\r')
		c = '\n';

	if (c == 127) 
		c = '\b';

	return c;
}

/* Get a line of text, handling line editting functionality */
static void
getline(void)
{
	int len = 0;
	bool got_cmd = false;

	do {
		command[len] = sh_getchar();

		if (command[len] == '\b') {
			if (len > 0) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
				len--;
			}
			command[len] = '\0';
			len--;
		} else if (isprint(command[len]) || command[len] == '\n') {
			putchar(command[len]);
		} else {
			len--;
		}

		/* Newline detection */
		if (command[len] == '\n') {
			command[len] = '\0';
			got_cmd = true;
		}

	} while (len++ < (MAX_COMMAND - 1) && got_cmd == false);

	if (got_cmd == false) {
		while(sh_getchar() != '\n');
	}

	/* Need to wait for a newline if we haven't got a full
	   string */
	return;
}

static enum mode mode = LUA;

/* Change to shell mode */
static int
shellL(lua_State *l)
{
	mode = SHELL;
	return 0;
}

/* Enter KDB */
static int
kdbL(lua_State *l)
{
	L4_KDB_Enter("<from lua>");
	return 0;
}

static int
debug_dump_infoL(lua_State *l)
{
	debug_dump_info();
	return 0;
}


#ifdef MACHINE_LN2410SBC
/* FIXME: This is short term demo code for the 
   evas library. It will be moved somewhere more appropriate
   in the near future
*/
#include <ln2410sbc_lcd.h>

#include <Evas.h>
#include <Evas_Engine_Buffer.h>

static void
evas_run(void)
{
   int win_w = 640;
   int win_h = 480;
   int tw, th;
   Evas *evas;
   Evas_Object *ob, *panel_clip;

   evas = evas_new();
   evas_output_method_set(evas, evas_render_method_lookup("buffer"));
   evas_output_size_set(evas, win_w, win_h);
   evas_output_viewport_set(evas, 0, 0, win_w, win_h);
   {
      Evas_Engine_Info_Buffer *einfo;

      einfo = (Evas_Engine_Info_Buffer *) evas_engine_info_get(evas);
      /* the following is specific to the engine */
      einfo->info.depth_type = EVAS_ENGINE_BUFFER_DEPTH_RGB16;
      einfo->info.dest_buffer = (void*) ln2410sbc_lcd_fb;
      einfo->info.dest_buffer_row_bytes = win_w * 2;
      einfo->info.use_color_key = 0;
      einfo->info.alpha_threshold = 128;
      evas_engine_info_set(evas, (Evas_Engine_Info *) einfo);
   }

   ob = evas_object_rectangle_add(evas);
   evas_object_move(ob, 10, 10);
   evas_object_resize(ob, 400, 100);
   evas_object_color_set(ob, 255, 255, 255, 100);
   evas_object_show(ob);
   panel_clip = ob;

   ob = evas_object_rectangle_add(evas);
   evas_object_color_set(ob, 128, 255, 255, 100);
   evas_object_move(ob, win_w - 50, win_h - 50);
   evas_object_resize(ob, 20, 20);
   evas_object_show(ob);

   ob = evas_object_text_add(evas);
   evas_object_move(ob, 50, 50);
   evas_object_color_set(ob, 0, 100, 0, 125);
   evas_object_text_font_set(ob, "Vera.ttf", 30);
   evas_object_geometry_get(ob, NULL, NULL, &tw, &th);
   evas_object_text_text_set(ob, "Welcome to Iguana!");
   evas_object_geometry_get(ob, NULL, NULL, &tw, &th);
   evas_object_show(ob);

   evas_render(evas);
   return;
}

static int
graphics_demoL(lua_State *l)
{
	ln2410sbc_lcd_init();
	evas_run();
	return 0;
}
#endif


#define BUFSIZE 100
char buf[BUFSIZE];

static int
cpL(lua_State *L)
{
	const char *from = lua_tostring(L, 1);
	const char *to = lua_tostring(L, 2);
	if (from == NULL || to == NULL) {
		printf("Must specify to and from file\n");
		return 0;
	}
	FILE *ff = fopen(from, "r");
	FILE *ft = fopen(to, "w");
	printf("Copy from: %s -> %s\n", from, to);
	int n;
	
	do {
		n = fread(buf, 1, BUFSIZE, ff);
		fwrite(buf, 1, n, ft);
	} while(n == BUFSIZE);
	
	fclose(ff);
	fclose(ft);
	return 0;
}

static int
catL(lua_State *l)
{
	const char *name = lua_tostring(l, 1);
	char *s;
	FILE *f;
	if (name == NULL) {
		printf("Need to pass filename argument");
		return 0;
	}
	f = fopen(name, "r");
	if (f == NULL) {
		printf("No file called: %s\n", name);
		return 0;
	}
	while (1) {
		s = fgets(buf, BUFSIZE, f);
		if (s == NULL) {
			break;
		}
		fputs(buf, stdout);
	}
	fclose(f);
	return 0;
}

static int
helpL(lua_State *l)
{
	printf("The Iguana shell is a \"lua\" interpreter. So you need to type lua syntax.\n");
	printf("Commands:\n");
	printf("\tkdb():              Enter the kernel debugger\n");
	printf("\tdebug_dump_info():  Dump Iguan internal data structures\n");
	printf("\thelp():             This help information\n");
	printf("\tpci.ls():           List PCI devices\n");
	printf("\tfat.test():         Test the FAT library\n");
	printf("\tfat.*():            Run a FAT filesystem command\n");
 	return 0;
}

int
main(int argc, char **argv)
{
	lua_State *l;
	int x;
	printf("Iguana shell 0.1\n\n");

        l = lua_open();

        openlualibs(l); /* Load Lua libraries */

	lua_register(l, "shell", shellL);
	lua_register(l, "kdb", kdbL);
	lua_register(l, "debug_dump_info", debug_dump_infoL);
	lua_register(l, "cp", cpL);
	lua_register(l, "cat", catL);
 	lua_register(l, "help", helpL);

#ifdef MACHINE_LN2410SBC
	lua_register(l, "graphics_demo", graphics_demoL);
#endif

	while (1) {
		switch (mode) {
		case LUA:
			printf("iguana> ");
			break;
		case SHELL:
			printf("iguana$ ");
			break;
		}

		getline();
		/* Process command */
		switch (mode) {
		case LUA:
			x = lua_dostring(l, command);
			if (x != 0) {
				printf("Type \"help()\" for help.\n");
			}
			break;
		case SHELL:
			if (strcmp(command, "lua") == 0) {
				mode = LUA;
			}
			break;
		}
	}
}

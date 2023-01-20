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
  Authors: Ben Leslie
  Date: Tue Jul  6 2004 
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <l4/bootinfo.h>
#include <l4/kip.h>
#include <l4/ipc.h>
#include <l4/kdebug.h>

#include <l4e/misc.h>

#include <iguana/thread.h>
#include <iguana/memsection.h>
#include <iguana/session.h>
#include <iguana/object.h>
#include <iguana/cap.h>
#include <iguana/pd.h>

#include <driver.h>
#include <driver/driver_ops.h>

#include <naming/naming.h>

#include <interfaces/serial_client.h>
#include <interfaces/naming_client.h>
//#include <interfaces/timer_client.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef VERBOSE
#define VERBOSE_INIT printf
#else
#define VERBOSE_INIT(...) 
#endif

#if 1	/* -gl: shared memory section for now */
#include <iguana/iokit_disk.h>	/* in xnu_glue */
memsection_ref_t	iokit_memsection;
uintptr_t		iokit_base;
#endif

static void * start_server(const char *name, int priority, objref_t naming, 
			   objref_t stdin_p, objref_t stdout_p, pd_ref_t *newpd, 
			   ...);
static void insert_files(void);
/* These shoudl be directly generated by the IDL compiler */
static object_t *
_device_create(object_t * driver, CORBA_Environment *env)
{
	objref_t obj;
	VERBOSE_INIT("Calling device_create\n");
	obj = device_create(driver->server, driver->obj, env);
	VERBOSE_INIT("Called device_create\n");
	if (obj == 0) {
		return NULL;
	}
	return object_get_interface(obj);
}

static void
_stream_set_sink(object_t *stream_obj, const objref_t sink, 
		 CORBA_Environment *env)
{
	/* Find the session */
	stream_set_sink(stream_obj->server, stream_obj->obj, sink, env);
}

/* End hand crafted IDL stubs */

int naming_server_started = 0;

static const luaL_reg lualibs[] = {
        { "base",       luaopen_base },
        { "table",      luaopen_table },
        { "io",         luaopen_io },
        { "string",     luaopen_string },
        { "debug",      luaopen_debug },
        { "loadlib",    luaopen_loadlib },
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

static objref_t naming_obj;
static object_t *naming_iface;
static object_t *serial_device;

static int
initialise_naming(void)
{
	void  *naming;
	pd_ref_t newpd;
	
	naming_server_started = 0;

	naming = start_server("ig_naming", 200, 0, 0, 0, &newpd, NULL);
	naming_obj = (objref_t) naming;
	naming_iface = object_get_interface((objref_t) naming);
	__naming_init(naming_obj);
	__naming_thread_init(malloc(naming_init_buf_size()));
	assert(naming != NULL);

	naming_server_started = 1;

	insert_files();

	/*
	 * -gl: XXX hack
	 *
	 * OK insert the IOKit memsection in there.
	 */
	naming_insert("iokit_memsection", iokit_base);

	return 1;
}

static int
initialise_namingL(lua_State *L)
{
	lua_pushnumber(L, initialise_naming());
	return 1;
}

static int
initialise_timer(void)
{
	pd_ref_t newpd;
	void *timer_obj; /* Ahr! This would be called "timer" but IDL4 makes a type
			    called timer. This is bad, and we will replace it! */
	object_t *timer_dev, *timer_iface;

	/* Startup timer server */
	timer_obj = start_server("ig_timer", 240, naming_obj, 0, 0, &newpd, NULL);
	/* Add TIMER */

	VERBOSE_INIT("Adding timer to name server\n");
	
	assert(timer_obj != NULL);
	timer_iface = object_get_interface((objref_t) timer_obj);
	assert(timer_iface != NULL);
	timer_dev = _device_create(timer_iface, NULL);
	assert(timer_dev != NULL);
	naming_insert("timer", timer_dev->obj);

	return 1;
}

static int
initialise_timerL(lua_State *L)
{
	lua_pushnumber(L, initialise_timer());
	return 1;
}


static int
initialise_trace(void)
{
	void *trace_svr;
	pd_ref_t newpd;

	/* Setup trace_server program */
	trace_svr = start_server("ig_trace", -1, naming_obj, 0, 0, &newpd, NULL);
	VERBOSE_INIT("started iguana trace server\n");

	return 1;
}

static int
initialise_traceL(lua_State *L)
{
	lua_pushnumber(L, initialise_trace());
	return 1;
}


static int
initialise_serial(void)
{
	void *serial;
	pd_ref_t newpd;
	object_t *serial_iface;
	
	/* Startup example cap applications */

	VERBOSE_INIT("starting ig serial\n");

	/* Setup serial driver */
	serial = start_server("ig_serial", -1, naming_obj, 0, 0, &newpd, NULL);
	VERBOSE_INIT("started iguana serial\n");

	assert(serial != NULL);
	serial_iface = object_get_interface((objref_t) serial);
	VERBOSE_INIT("serial_iface: %p\n", serial_iface);
	serial_device = _device_create(serial_iface, NULL);
	VERBOSE_INIT("starting examples\n");
	return 1;
}

static int
initialise_serialL(lua_State *L)
{
	lua_pushnumber(L, initialise_serial());
	return 1;
}

static int
initialise_block(void)
{
	pd_ref_t newpd;
	void *block;
	object_t *block_iface;

	/* Startup example cap applications */
	printf("starting iguana block\n");

	/* Setup serial driver */
	block = start_server("iguana_block", -1, naming_obj, 0, 0, &newpd, NULL);
	printf("started iguana serial\n");

	block_iface = object_get_interface((objref_t) block);

	naming_insert("block", block_iface->obj);

	assert(block != NULL);
#if 0
	VERBOSE_INIT("serial_iface: %p\n", serial_iface);
	serial_device = _device_create(serial_iface, NULL);
	VERBOSE_INIT("starting examples\n");
#endif
	return 1;
}

static int
initialise_blockL(lua_State *L)
{
	lua_pushnumber(L, initialise_block());
	return 1;
}

static int
start_serverL(lua_State *L)
{
	//int n = lua_gettop(L);
	const char *name = lua_tostring(L, 1);
	pd_ref_t newpd;
	start_server(name, -1, naming_obj, 0, 0, &newpd, NULL);

	return 0;
}

static memsection_ref_t
setup_vmalloc_area(memsection_ref_t wombat, pd_ref_t pd, uintptr_t size)
{
	uintptr_t addr;
	memsection_ref_t ms;

	printf("wombat is at <%p:%p>\n", memsection_base(wombat),
			(void *)((uintptr_t)memsection_base(wombat) + memsection_size(wombat)));
#ifdef ARCH_ARM
	/* Search below wombat image */
	addr = (uintptr_t)memsection_base(wombat) - size;
	printf("starting at %p\n", (void *)addr);
	while ((ms = pd_create_memsection_fixed_user(pd, size, addr)) == 0)
		addr -= l4e_min_pagesize();
#else
	addr = (uintptr_t)memsection_base(wombat);
	printf("starting at %p\n", (void *)addr);
	while ((ms = pd_create_memsection_fixed_user(pd, size, addr)) == 0)
		addr += l4e_min_pagesize();
#endif
	printf("vmalloc area at %p\n", memsection_base(ms));
	naming_insert("vmalloc_area", (uintptr_t)memsection_base(ms));
	return ms;
}

static int
start_linuxL(lua_State *L)
{
	void *vmlinux;
	pd_ref_t newpd;
	/* Start L4 Linux */
	vmlinux = start_server("vmlinux", -1, naming_obj, serial_device->obj, serial_device->obj, &newpd, 
			       "vmlinux igms_name=ramdisk root=/dev/igms0", NULL);
	/* Set the sink to Linux */
	_stream_set_sink(serial_device, (objref_t) vmlinux, NULL);
	lua_pushnumber(L, 1);
	return 1;
}

static int
cap_exampleL(lua_State *L)
{
	int i;
	L4_MsgTag_t tag;
	L4_ThreadId_t cap_thread;
	void *cap_server;
	L4_Msg_t msg;
	struct session * session;
	char *another_string;
	uintptr_t another_string_address;
	static char *hello_string = "Hello World!";
	pd_ref_t newpd;
	
	/* Create the example server */
	cap_server = start_server("cap_example", -1, naming_obj, 0, 0, &newpd, NULL);
	
	memsection_create(1024, &another_string_address);
	another_string = (char*) another_string_address;
	strcpy(another_string, "Goodbye cruel world");
	
	/* Create a session so that we can interact with it */
	session = session_create((objref_t) cap_server, &cap_thread);
	
	/* Now we provide it with access to the hello_string */
	/* Note that we provide it with access to everything
	   in the same memory section as the hello string, in
	   this case init's data section. Depending on
	   security dependancies you may want to create and
	   explicit buffer and only provide access to it */
	{
		uintptr_t ignore;
		
		session_provide_access(session, memsection_lookup((uintptr_t) another_string, &ignore),
				       MASTER_IID);
		
		session_provide_access(session, 
				       /* We find the memory section that hello_string resides
					  in and provide access to it */
				       memsection_lookup((uintptr_t) hello_string, &ignore), 
				       /* Currently we provide it with the master cap. This will
					  be changed once fine grained caps are fully implemented */
				       MASTER_IID);
	}
	
	/* Print out what our string looks like now */
	printf("String before: %s\n", hello_string);
	
	/* Call the example server */
	/* Setup an IPC -- we usually hide this with the IDL compiler */
	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, 0); /* toupper operation */
	L4_MsgAppendWord(&msg, (uintptr_t) hello_string);
	L4_Set_Label(&msg.tag, 0);
	L4_MsgLoad(&msg);
	tag = L4_Call(cap_thread);
	
	/* Print out the string after being changed by the server */
	printf("String upper : %s\n", hello_string);
	
	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, 1); /* tolower operation */
	L4_MsgAppendWord(&msg, (uintptr_t) hello_string);
	L4_Set_Label(&msg.tag, 0);
	L4_MsgLoad(&msg);
	tag = L4_Call(cap_thread);
	
	/* Print out the string again now that the server has "tolowered" it */
	printf("String lower : %s\n", hello_string);
	
	/* Print out what our string looks like now */
	printf("String before: %s\n", another_string);
	
	/* Call the example server */
	/* Setup an IPC -- we usually hide this with the IDL compiler */
	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, 0); /* toupper operation */
	L4_MsgAppendWord(&msg, (uintptr_t) another_string);
	L4_Set_Label(&msg.tag, 0);
	L4_MsgLoad(&msg);
	tag = L4_Call(cap_thread);
	
	/* Print out the string after being changed by the server */
	printf("String upper : %s\n", another_string);
	
	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, 1); /* tolower operation */
	L4_MsgAppendWord(&msg, (uintptr_t) another_string);
	L4_Set_Label(&msg.tag, 0);
	L4_MsgLoad(&msg);
	tag = L4_Call(cap_thread);
	
	/* Print out the string again now that the server has "tolowered" it */
	printf("String lower : %s\n", another_string);
	
	printf("Now we go into a loop creating and deleting sessions. This \n"
	       "should go on indefinately\n");
	i = 0;
	while(1) {
		i++;
		if (i % 1000 == 0) 
			printf("Done: %d\n", i);
		session_delete(session);
		/* Create a session so that we can interact with it */
		session = session_create_full_share((objref_t) cap_server, &cap_thread);
	}
}


int
main(int argc, char **argv)
{
	lua_State *l;
	int status, result;

	/*
	 * Setup the I/O Kit shared memory segment, now.
	 *
	 * Make it big for network packets, too.
	 */
	// iokit_memsection = memsection_create_direct(DISKBUFSIZ, &iokit_base);
	iokit_memsection = memsection_create_direct((1<<20), &iokit_base);
	assert(iokit_base);
	
        /*
         * All Lua contexts are held in this structure, we work with it almost
         * all the time.
         */
        l = lua_open();

        openlualibs(l); /* Load Lua libraries */

	/* Setup functions */
	lua_register(l, "initialise_naming", initialise_namingL);
	lua_register(l, "initialise_timer", initialise_timerL);
	lua_register(l, "initialise_serial", initialise_serialL);
	lua_register(l, "initialise_trace", initialise_traceL);
	lua_register(l, "initialise_block", initialise_blockL);
	lua_register(l, "start_server", start_serverL);
	lua_register(l, "start_linux", start_linuxL);
	lua_register(l, "cap_example", cap_exampleL);

        /* Load the file containing the script we are going to run */
        status = luaL_loadfile(l, "startup.lua");
        if (status) {
                (void)fprintf(stderr, "bad, bad file\n");
                exit(1);
        }
       /* Ask Lua to run our little script */
        result = lua_pcall(l, 0, LUA_MULTRET, 0);
        if (result) {
                (void)fprintf(stdout, "bad, bad script\n");
                exit(1);
        }

        /* Get the returned value at the top of the stack */
        result = lua_tonumber(l, lua_gettop(l));

        fprintf(stdout, "Script returned: %d\n", result);

        lua_pop(l, 1);  /* Take  the returned value out of the stack */
        lua_close(l);   /* Cya, Lua */

	L4_WaitForever();

	return 0;
}

static void
insert_files(void)
{
	L4_KernelInterfacePage_t *kip;
	L4_BootRec_t *rec;
	int bootentries, i;
	void *bootinfo;
	kip = L4_GetKernelInterface();
	bootinfo = (void*) L4_BootInfo(kip);
	assert(L4_BootInfo_Valid(bootinfo));

	bootentries = L4_BootInfo_Entries(bootinfo);

	/* Find name */
	rec = L4_BootInfo_FirstEntry(bootinfo);

	for (i=0; i < bootentries; i++) {
		if (L4_BootRec_Type(rec) == L4_BootInfo_Module) {
			naming_insert(L4_Module_Cmdline(rec), L4_Module_Start(rec));
			naming_insert("ramdisk_end", L4_Module_Start(rec) + L4_Module_Size(rec));
		}
		rec = L4_BootRec_Next(rec);
	}
}

#include "mbi.h"

static void *
start_server(const char *name, int priority, objref_t naming, objref_t stdin_p, objref_t stdout_p, pd_ref_t *newpd, ...)
{
	L4_KernelInterfacePage_t *kip;
	void *bootinfo;
	int bootentries, i;
	L4_BootRec_t *rec;
	struct cap_slot myslot;
	int x;
	mbi_t	*mbi;
	va_list argp;
	
	kip = L4_GetKernelInterface();
	bootinfo = (void*) L4_BootInfo(kip);
	assert(L4_BootInfo_Valid(bootinfo));

	bootentries = L4_BootInfo_Entries(bootinfo);

	/* Find name */
	rec = L4_BootInfo_FirstEntry(bootinfo);


	for (i=0; i < bootentries; i++) {
		if (L4_BootRec_Type(rec) == L4_BootInfo_SimpleExec) {
			if (strcmp(L4_SimpleExec_Cmdline(rec), name) == 0) {
 				thread_ref_t thread;
  				L4_ThreadId_t l4tid;
 				uintptr_t stack_base, heap_base, callback_base, clist_base, ignore;
  				uintptr_t *stack, *string_base, *init_vars;
 				memsection_ref_t callback, heap, stack_memsect, clist_memsect, text, data;
 				cap_t *clist;
 				int caps = 0;
				char *arg;
				char **argv;
				int argc = 0;
				int stacksize = 0x4000;
				int heapsize = 16 * 1024 * 1024;
				uintptr_t clist_pos;

  				/* Create pd */
  				*newpd = pd_create();
  
  				/* Create stack */
 				stack_memsect = pd_create_memsection(*newpd, stacksize, &stack_base);
  
  				/* Create callback */
 				callback = pd_create_memsection(*newpd, 0x1000, &callback_base);
  				pd_set_callback(*newpd, callback);
  
 				/* Create a heap */
				if (strcmp(name, "vmlinux") == 0) {
					heap = pd_create_memsection(*newpd, heapsize, &heap_base);
				} else {
					uintptr_t phys_base;
					uintptr_t phys_size = 0x10000; // 64k

					heap = pd_create_memsection_user(*newpd, heapsize, &heap_base);
					/* Back the first 64k of the heap, to help the app get started */
					pd_create_memsection(*newpd, phys_size, &phys_base);
					memsection_page_map(heap, 
							L4_Fpage(phys_base, phys_size), 
							L4_Fpage((uintptr_t)memsection_base(heap), phys_size));
				}
 
 				/* Create clist */
 				clist_memsect = pd_create_memsection(*newpd, l4e_min_pagesize(), &clist_base);
				clist_pos = pd_add_clist(*newpd, clist_memsect);
				assert(clist_pos != -1);
 				clist = (cap_t*) clist_base;
  
  				/* Create thread */
  				thread = pd_create_thread_with_priority(*newpd, priority, &l4tid);
  				L4_KDB_SetThreadName(l4tid, name);
  				//printf("Created tid: %lx\n", l4tid.raw);
 
 				/* Find text section */
 				text = memsection_lookup(L4_SimpleExec_InitialIP(rec),
 							       &ignore);
 
 				data = memsection_lookup(L4_SimpleExec_DataVstart(rec),
 							       &ignore);
  				memsection_register_server(data, thread);
 
 				clist[caps++] = iguana_get_cap(stack_memsect, MASTER_IID);
 				clist[caps++] = iguana_get_cap(callback, MASTER_IID);
 				clist[caps++] = iguana_get_cap(heap, MASTER_IID);
				/* XXX: reserve a slot for morecore to use */
 				clist[caps++] = iguana_get_cap(heap, MASTER_IID);
 				clist[caps++] = iguana_get_cap(clist_memsect, MASTER_IID);
 				clist[caps++] = iguana_get_cap(text, MASTER_IID);
 				clist[caps++] = iguana_get_cap(data, MASTER_IID);

 				/* Provide caps for the bootinfo */
 				{
 					L4_BootRec_t *rec2;
					unsigned num_recs, objs;
 					
 					/* Iterate through bootinfo */
 					num_recs = L4_BootInfo_Entries(bootinfo);
 					rec2 = L4_BootInfo_FirstEntry(bootinfo);
 					
 					clist[caps++] = iguana_get_cap(memsection_lookup((uintptr_t)bootinfo,
 											 &ignore), MASTER_IID);
 					while(num_recs > 0) {
 						L4_Word_t type;
 						/* find what type it is */
 						type = L4_BootRec_Type(rec2);
 						objs = 0;
 						if (type == L4_BootInfo_Module) {
 							clist[caps++] = iguana_get_cap(memsection_lookup(L4_Module_Start(rec2),
 													 &ignore), MASTER_IID);
 						}
				/*
				 * We want the MBI module + the 
				 * the binaries.
				 *
				 * XXX this may be a security risk,
				 * but hey, ...
				 */

						if (type == L4_BootInfo_Multiboot) {
							clist[caps++] = iguana_get_cap(memsection_lookup(L4_MBI_Address(rec2), &ignore), MASTER_IID);
							myslot = iguana_cap_get_slot();
							iguana_cap_set(iguana_get_cap(memsection_lookup(L4_MBI_Address(rec2), &ignore), MASTER_IID), myslot);

							/*
							 * Ok, got cap,
							 * Iterate
							 */

							mbi = (mbi_t *)L4_MBI_Address(rec2);

							for (x = 3; x < mbi->modcount; x++) {
								clist[caps++] = iguana_get_cap(memsection_lookup(mbi->mods[x].start, &ignore), MASTER_IID);

							}
						}
 						rec2 = L4_BootRec_Next(rec2);
 						num_recs--;
 					}
 				}
				/*
				   Setup vmalloc area for wombat
				   FIXME: this really belongs in start_linux
				*/
				if (strcmp(name, "vmlinux") == 0) {
					memsection_ref_t vma_ms = setup_vmalloc_area(text, *newpd, 4 * 1024 * 1024);
					clist[caps++] = iguana_get_cap(vma_ms, MASTER_IID);
				}

				/*
				 * XXX
				 *
				 * darbat/iokit
				 * Whatever.  Free for all!
				 */
				clist[caps++] = iguana_get_cap(
				    iokit_memsection,
				    MASTER_IID);
				/* 
				   Provide access to the ramdisk -- this should obviously
				   be done is a much better way 
				*/
				if (naming_server_started) {
					if (memsection_lookup(naming_lookup("ramdisk"), &ignore)) {
						clist[caps++] = iguana_get_cap(memsection_lookup(naming_lookup("ramdisk"), &ignore), MASTER_IID);
					}
				}

 				/* Setup stack -- FIXME: benjl, this could be done in a much
 				 nicer way */

 				string_base = stack = (uintptr_t *) (stack_base + stacksize);
				init_vars = stack - 0x100;

				/* First copy the strings in */
				va_start(argp, newpd);
				arg = va_arg(argp, char*);
				while (arg != NULL) {
					stack-= (strlen(arg) - 1) / sizeof(uintptr_t) + 1;
					strcpy((char*)stack, arg);
					argc++;
					arg = va_arg(argp, char*);
				}
				va_end(argp);

				/* Now setup argv[] */
 				stack-= (argc + 1); argv = (char **) stack;

				va_start(argp, newpd);
				for (i=0; i < argc; i++) {
					arg = va_arg(argp, char*);
					string_base -= (strlen(arg) - 1) / sizeof(uintptr_t) + 1;
					argv[i] = (char *) string_base; 
				}

				/* Copy all the initialisation arguments to a buffer on the stack */
				/* arguements for __libc_setup */
				*(init_vars +  0) = callback_base; /* Callback ptr */
				*(init_vars +  1) = stdin_p; /* stdin */
				*(init_vars +  2) = stdout_p; /* stdout */
				*(init_vars +  3) = 0; /* stderr */
				*(init_vars +  4) = heap_base;
				*(init_vars +  5) = heap_base + heapsize;
				/* arguements for __cap_init */
				*(init_vars +  6) = clist_pos; /* cap_slot */
				*(init_vars +  7) = caps - 1; /* cap_used */
				*(init_vars +  8) = l4e_min_pagesize() / sizeof(cap_t); /* cap_size */
				*(init_vars +  9) = clist_base; /* cap_addr */
				/* arguements for __naming_init */
				*(init_vars + 10) = (uintptr_t)naming; /* naming_server */	

				/* Initialise the stack */
 				stack--; *stack = argc; /* argc */
				stack--; *stack = (uintptr_t)init_vars; /* ptr to init args for __lib_init */

				/* Start thread */
				thread_start(thread, 
					     L4_SimpleExec_InitialIP(rec),
					     (uintptr_t) stack);
				return (void*) L4_SimpleExec_DataVstart(rec);
			}
		}
		rec = L4_BootRec_Next(rec);
	}
	printf("Couldn't find: %s\n", name);
	return NULL;
}

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
#include <stdlib.h>
#include <assert.h>

#include "clockthread.h"

int main(void);
extern void bsd_init(void);
extern void _kthread_init( void );
extern void _ktask_init( void );

extern void userprog(void);

void panic(const char *str, ...);

/* XXX: Mach VM */
typedef unsigned int vm_offset_t;
extern void kmem_init( vm_offset_t, vm_offset_t );
extern void vm_object_bootstrap(void);
extern void memory_object_control_bootstrap(void);
extern void vm_page_bootstrap( vm_offset_t *startp, vm_offset_t *endp );
extern void db_phys_bootstrap(void);
extern void db_virt_bootstrap(void);
extern void vm_page_module_init(void);
extern void vm_map_init(void);
extern void kpmap_init(void);
extern void pmap_bootstrap(void);

extern void do_hack_test(void);

extern void l4_init(void);

extern void syscall_loop(void);

extern void l4serial_init(void);

void l4_pick_video(void);


int
main(void) 
{
	/* XXX: setup the video first thing */
	l4_pick_video();

	/* startup the clock thread */
	clockthread_init();
	
	/* setup phys mem */
	db_phys_bootstrap();

	/* and virtual */
	db_virt_bootstrap();

	/* bootstrap the pmap system */
	pmap_bootstrap();

	/* setup the kernel pmap */
	kpmap_init();

	/* call the L4 arch init */
	l4_init();

	assert(!"what now?");

	return 0;
}

void
panic(const char *str, ...)
{
	char buf[1024];
	va_list ap;

	buf[0] = '\0';

	va_start( ap, str );
	vsprintf( buf, str, ap );
	va_end( ap );

	puts( buf );

	/* die now */
	assert( 0 );
}

extern void log(int level, char *fmt, ...);
void
log(int level, char *fmt, ...)
{
	char buf[1024];
	va_list ap;

	buf[0] = '\0';

	va_start( ap, fmt );
	vsprintf( buf, fmt, ap );
	va_end( ap );

	printf( "LOG [%d]: %s", level, buf );
}

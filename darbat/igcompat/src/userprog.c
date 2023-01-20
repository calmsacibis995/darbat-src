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
/* a dummy 'user' program */

// #include <stdio.h>
#include <assert.h>
// #include <stdlib.h>

extern void *malloc( int );
extern void free(void*);

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/file_internal.h>
#include <sys/stat.h>
#include <sys/vnode_internal.h>
#include <sys/mount_internal.h>
#include <sys/proc_internal.h>
#include <sys/kauth.h>
#include <sys/uio_internal.h>
#include <sys/malloc.h>
#include <sys/mman.h>
#include <sys/dirent.h>
#include <sys/attr.h>
#include <sys/sysctl.h>
#include <sys/ubc.h>
#include <sys/quota.h>
#include <sys/kdebug.h>
#include <sys/fsevents.h>
#include <sys/sysproto.h>
#include <sys/xattr.h>
#include <sys/ubc_internal.h>
#include <machine/cons.h>
#include <machine/limits.h>
#include <miscfs/specfs/specdev.h>

#include <igcompat/compat.h>

#define FILENAME "/foo.txt"

#if 0
void check_malloc( char *msg );

void
check_malloc( char *msg )
{
	void *s[20];
	int i, j;

	printf( "testing malloc - %s\n", msg );

	for( j = 0; j < 3; j++ )
	{
		for( i = 0; i < 20; i++ )
			s[i] = malloc( 1 << i );

		for( i = 0; i < 20; i++ )
			bzero( s[i], 1 << i );

		for( i = 0; i < 20; i++ )
			free(s[i]);
	}

	printf( "tested malloc\n" );
}
#endif

/* also initproc */
// extern struct proc *kernproc;

// Dodgey implementation of open
// 5	PRE 	NONE	ALL	{ int open(user_addr_t path, int flags, int mode); } 
static int
user_open( const char *pathname, int flags )
{
	int ret;
	struct open_args uap;
	register_t retval;

	uap.path = (user_addr_t) pathname;
	uap.flags = flags;
	uap.mode = 0644;

	ret = open( kernproc, &uap, &retval );

	if( ret != 0 )
		return -ret;

	return retval;
}

static ssize_t
user_write( int fd, const void *buf, size_t count )
{
	int r;
	register_t retval;
	struct write_args uap;

	uap.fd = fd;
	uap.cbuf = (user_addr_t) buf;
	uap.nbyte = count;

	r = write( kernproc, &uap, &retval );

	if( r != 0 )
		return -r;

	return retval;
}

static ssize_t
user_read( int fd, const void *buf, size_t count )
{
	int r;
	register_t retval;
	struct read_args uap;

	uap.fd = fd;
	uap.cbuf = (user_addr_t) buf;
	uap.nbyte = count;

	r = read( kernproc, &uap, &retval );

	if( r != 0 )
		return -r;
	
	return retval;
}

static int
user_close( int fd )
{
	int r;
	register_t retval;
	struct close_args uap;

	uap.fd = fd;

	r = close( kernproc, &uap, &retval );

	if( r != 0 )
		return -r;
	
	return retval;
}

static int
user_getdirentries( int fd, char *buf, int nbytes, long *basep )
{
	int r;
	register_t retval;
	struct getdirentries_args uap;

	uap.fd = fd;
	uap.buf = (user_addr_t) buf;
	uap.count = nbytes;
	uap.basep = (user_addr_t) basep;

	r = getdirentries( kernproc, &uap, &retval );

	if( r != 0 )
		return -r;

	return retval;
}


static pid_t
user_getpid(void)
{
	pid_t ret;
	int r;

	r = getpid( kernproc, NULL, &ret);
	assert( r == 0 );

	return ret;
}


void ls( char *dirname );

void
ls( char *dirname )
{
	char buf[8192];
	int fd, r, off;
	long basep = 0;
	struct dirent *de;

	/* first open the dir */
	fd = user_open( dirname, O_RDONLY );

	if( fd < 0 )
		printf( "failed to open '%s', err = %d\n", dirname, fd );

	printf( "opened dir, fd = %d\n", fd );

	/* now read stuff */
	r = user_getdirentries( fd, buf, 8192, &basep );

	printf( "did getdirentries, r = %d\n", r );

	if( r < 0 )
	{
		printf( "getdirentries failed, bailing!\n" );
		return;
	}

	off = 0;
	while( off < r )
	{
		de = (struct dirent *) &buf[off];
	
		printf( "%s - %d - %d\n", 
			de->d_name, de->d_reclen, de->d_type );

		off += de->d_reclen;
	}	

	r = user_close( fd );
	printf( "user_close returned %d\n", r );

}

static void
test_console( void )
{
	int fd, r;

	fd = user_open( "/dev/console", O_RDWR );

	r = user_write( fd, "This is some write() text!\n", 27 );

	if( r <= 0 )
		printf( "write() failed: err %d\n", r );

	user_close( fd );
}

static void
test_file( void )
{
	char buf[100];
	int fd, r;

	printf( "opening '" FILENAME "'\n" );

	fd = user_open( FILENAME, O_RDONLY );

	if( fd < 0 )
	{
		printf("failed to open file: err %d\n", fd);
		return;
	}

	printf( "opened, fd is %d\n", fd );

	r = user_read( fd, buf, 100 );

	printf( "read %d bytes\n", r );

	if( r > 0 )
		printf( "file is '%s'\n", buf );

	user_close( fd );
}



/* the user program */
void userprog(void);

void
userprog(void)
{
	int r;
	pid_t pid;

	printf( "Welcome to userprog\n" );

	/* trivial system call */
	pid = user_getpid();
	printf( "My pid is %d\n", pid );

	/* try and write something */
	printf( "about to write to stdout\n" );
	r = user_write( 1, "This is a write() message\n", 26 );
	printf( "done write to stdout, r = %d\n", r );

	/* what's in /dev? */
	ls("/dev/");

	/* test the console */
	test_console();

	/* test if files work */
	test_file();

	printf( "userprog done\n" );
}

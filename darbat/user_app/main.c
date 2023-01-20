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

#include <l4/kdebug.h>

#include "hacklibc.h"
#include "libsystem.h"


static int
put(const char *s)
{
	int len;

	len = strlen( s );

	write( 1, s, len );

	return 0;
}

int
puts(const char *s)
{
	char *nl = "\n";

	put(s);
	put(nl);

	return 0;
}

static void
stop(void)
{
	char *foo = NULL;

	puts( "user-land stopping!!!\n\n" );

	/* die die die */
	*foo = 0x37;

	while(1);
}

static int
cmd_mount(int argc, char** argv)
{
	struct hfs_mount_args args;
	int r;

	puts( "doing mount" );
	
	if( argc != 3 )
	{
		puts("usage: mount /dev/ikd0 /mnt");
		return 1;
	}

	memset( &args, 0, sizeof( args ) );
	args.fspec = argv[1];
	
	r = mount( "hfs", argv[2], 1, (void*) &args );

	return 1;
}

static int
cmd_ls(int argc, char** argv)
{
	char buf[8192];
	int fd, r, off;
	long basep = 0;
	struct dirent *de;
	char *dirname;

	if( argc == 1 )
		dirname = ".";
	else
		dirname = argv[1];

	if( argc > 2 )
	{
		puts( "usage: ls [dir]   (duh!)" );
		return 1;
	}

	/* first open the dir */
	fd = open( dirname, O_RDONLY );

	if( fd < 0 )
		puts( "could not open dir :(" );

	/* now read stuff */
	r = getdirentries( fd, buf, 8192, &basep );

	if( r < 0 )
	{
		puts( "getdirentries failed\n" );
		close( fd );
		return 1;
	}

	off = 0;
	while( off < r )
	{
		de = (struct dirent *) &buf[off];
	
		puts( de->d_name );

		off += de->d_reclen;
	}	

	r = close( fd );

	return 1;
}

static int
cmd_cd(int argc, char** argv)
{
	char *dirname;
	int r;

	if( argc == 2 )
		dirname = argv[1];
	else
	{
		puts("usage: cd <dir>");
		return 1;
	}
		
	r = chdir( dirname );

	if( r != 0 )
		puts( "error on chdir()" );

	return 1;
}

static int
cmd_cat(int argc, char** argv)
{
	char *fname;
	char buf[1024];
	int r, fd;

	if( argc == 2 )
		fname = argv[1];
	else
	{
		puts("usage: cat <file>" );
		return 1;
	}

	fd = open( fname, O_RDONLY );

	if( fd < 0 )
	{
		puts("error opening file");
		return 1;
	}

	while((r = read( fd, buf, 1024 ))>0)
		write( 1, buf, r );

	if( r == -1 )
		puts("error during cat\n");

	close(fd);

	return 1;
}

static int
cmd_uname(int argc, char** argv)
{
	puts( "L4 Darbat/IOKit" );
	return 1;
}

static int
cmd_kdb(int argc, char** argv)
{
	enter_kdebug("enter kdebug");

	return 0;
}

static int
cmd_fork(int argc, char** argv)
{
	int r;

	puts( "fork cmd" );

	if( argc != 1 )
		goto usage;

	r = fork();

	stop();

usage:
	// printf( "%s: takes no arguments\n" );
	stop();

	return 1;
}


struct
{
        char *cmd;
        int (*fn)(int argc ,char** argv);
        char *cmd_help; /* Actually unused here, coudl be useful
                           in the future though */
}  commands[] = {
	{ "ls", cmd_ls, "list directory" },
	{ "cd", cmd_cd, "change directory" },
	{ "uname", cmd_uname, "system information" },
	{ "mount", cmd_mount, "mount a filesystem" },
	{ "cat", cmd_cat, "display a file" },
	{ "kdb", cmd_kdb, "enter L4 Kernel bebugger" },
	{ "fork", cmd_fork, "fork test" },
};


#define WHITESPACE " \t\v\n"


static void
do_cmd( char *cmd )
{
        int j, cmd_exist = 0, argc;
        char * argv[20];

        /* Parse String */
        argc = 0;
        argv[argc] = strtok( cmd, WHITESPACE );

        while( argv[argc] != NULL )
	{
                argc++;
                argv[argc] = strtok( NULL, WHITESPACE );
        }

        if( argv[0] != NULL )
	{
                for (j = 0; commands[j].cmd != NULL ; j++)
		{
                        if (strcmp( argv[0], commands[j].cmd) == 0 )
			{
                                commands[j].fn( argc, argv );
				cmd_exist = 1;
			}
		}

                if (! cmd_exist) 
		{
                        // printf("No such command: %s\n", argv[0]);
			puts("no such command!");
		}
        }
}



#define PROMPT "darbat prompt>>> "

int
main( int argc, char *argv[] )
{
	int r;
	int fd;
	char cs[100];

	/* open stdin, stdout and stderr */
	fd = open( "/dev/console", O_RDONLY );
	if( fd != 0 )
		stop();
	fd = open( "/dev/console", O_WRONLY );
	if( fd != 1 )
		stop();
	fd = open( "/dev/console", O_RDWR );
	if( fd != 2 )
		stop();

	while( 1 )
	{
		/* print a prompt */
		put( PROMPT );

		/* try to read from stdwhatever */
		r = read( 0, cs, 100 );
		if( r > 0 )
		{
			/* terminate the string */
			cs[r] = '\0';
			
			do_cmd( cs );
		}
		else
		{
			write( 2, "error reading char\n", 19 );
			stop();
		}
	}

	stop();
}

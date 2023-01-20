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


typedef int ssize_t;
typedef int pid_t;

#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */

int open(const char *pathname, int flags);
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
pid_t fork(void);

int close(int d);
int getdirentries(int fd, char *buf, int nbytes, long *basep);
int chdir(const char *path);



int mount(const char *type, const char *dir, int flags, void *data);


struct hfs_mount_args 
{
        char    *fspec;    /* block special device to mount */
        int    hfs_uid;    /* uid that owns hfs files (standard HFS only) */
        int    hfs_gid;    /* gid that owns hfs files (standard HFS only) */
        short  hfs_mask;   /* mask to be applied for hfs perms  (standard HFS only) */
        int hfs_encoding;   /* encoding for this volume (standard HFS only) */
        int hfs_timezone;  /* user time zone info (standard HFS only) */
        int   flags;                  /* mounting flags, see below */
        int   journal_tbuffer_size;   /* size in bytes of the journal transaction buffer */
        int   journal_flags;          /* flags to pass to journal_open/create */
        int   ournal_disable;        /* don't use journaling (potentially dangerous) */
	int buffer[10];
};


struct dirent 
{
        unsigned int   d_ino;                    /* file number of entry */
        unsigned short d_reclen;            /* length of this record */
        unsigned char  d_type;              /* file type, see below */
        unsigned char  d_namlen;            /* length of string in d_name */
        char d_name[255 + 1];    /* name must be no longer than this */
};

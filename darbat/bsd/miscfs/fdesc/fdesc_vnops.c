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
 * Copyright (c) 2000-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
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
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)fdesc_vnops.c	8.17 (Berkeley) 5/22/95
 *
 */

/*
 * /dev/fd Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/proc_internal.h>
#include <sys/kernel.h>	/* boottime */
#include <sys/resourcevar.h>
#include <sys/filedesc.h>
#include <sys/kauth.h>
#include <sys/vnode_internal.h>
#include <sys/malloc.h>
#include <sys/file_internal.h>
#include <sys/stat.h>
#include <sys/mount_internal.h>
#include <sys/namei.h>
#include <sys/dirent.h>
#include <sys/ubc.h>
#include <sys/socketvar.h>
#include <sys/pipe.h>
#include <sys/uio_internal.h>
#include <miscfs/fdesc/fdesc.h>
#include <vfs/vfs_support.h>
#include <pexpert/pexpert.h>

#include <igcompat/compat.h>	/* bcopy */
#define FDL_WANT	0x01
#define FDL_LOCKED	0x02
static int fdcache_lock;


#if (FD_STDIN != FD_STDOUT-1) || (FD_STDOUT != FD_STDERR-1)
FD_STDIN, FD_STDOUT, FD_STDERR must be a sequence n, n+1, n+2
#endif

#define	NFDCACHE 3

#define FD_NHASH(ix) \
	(&fdhashtbl[(ix) & fdhash])
LIST_HEAD(fdhashhead, fdescnode) *fdhashtbl;
u_long fdhash;

static int fdesc_attr(int fd, struct vnode_attr *vap, vfs_context_t a_context);


/*
 * Initialise cache headers
 */
int
fdesc_init(__unused struct vfsconf *vfsp)
{

	fdhashtbl = hashinit(NFDCACHE, M_CACHE, &fdhash);

	return( 0 );
}

int
fdesc_allocvp(ftype, ix, mp, vpp, vtype)
	fdntype ftype;
	int ix;
	struct mount *mp;
	struct vnode **vpp;
	enum vtype vtype;
{
	struct fdhashhead *fc;
	struct fdescnode *fd;
	int error = 0;
	int vid = 0;
	struct vnode_fsparam vfsp;

	fc = FD_NHASH(ix);
loop:
	for (fd = fc->lh_first; fd != 0; fd = fd->fd_hash.le_next) {
		if (fd->fd_ix == ix && vnode_mount(fd->fd_vnode) == mp) {
		        /*
			 * doing a vnode_getwithvid isn't technically 
			 * necessary since fdesc is an unsafe filesystem
			 * and we're running behind a funnel at this point
			 * however, vnode_get always succeeds, which isn't
			 * what we want if this vnode is in the process of
			 * being terminated
			 */
		        vid = vnode_vid(fd->fd_vnode);

			if (vnode_getwithvid(fd->fd_vnode, vid))
				goto loop;
			*vpp = fd->fd_vnode;
			(*vpp)->v_type = vtype;

			return (error);
		}
	}

	/*
	 * otherwise lock the array while we call getnewvnode
	 * since that can block.
	 */ 
	if (fdcache_lock & FDL_LOCKED) {
		fdcache_lock |= FDL_WANT;
		sleep((caddr_t) &fdcache_lock, PINOD);
		goto loop;
	}
	fdcache_lock |= FDL_LOCKED;

	MALLOC(fd, void *, sizeof(struct fdescnode), M_TEMP, M_WAITOK);

	vfsp.vnfs_mp = mp;
	vfsp.vnfs_vtype = vtype;
	vfsp.vnfs_str = "fdesc";
	vfsp.vnfs_dvp = 0;
	vfsp.vnfs_fsnode = fd;
	vfsp.vnfs_cnp = 0;
	vfsp.vnfs_vops = fdesc_vnodeop_p;
	vfsp.vnfs_rdev = 0;
	vfsp.vnfs_filesize = 0;
	vfsp.vnfs_flags = VNFS_NOCACHE | VNFS_CANTCACHE;
	vfsp.vnfs_marksystem = 0;
	if (ftype == Froot)
		vfsp.vnfs_markroot = 1;
	else
		vfsp.vnfs_markroot = 0;

	error = vnode_create(VNCREATE_FLAVOR, VCREATESIZE, &vfsp, vpp);
	if (error) {
		FREE(fd, M_TEMP);
		goto out;
	}
	(*vpp)->v_tag = VT_FDESC;
	fd->fd_vnode = *vpp;
	fd->fd_type = ftype;
	fd->fd_fd = -1;
	fd->fd_link = 0;
	fd->fd_ix = ix;
	LIST_INSERT_HEAD(fc, fd, fd_hash);

out:
	fdcache_lock &= ~FDL_LOCKED;

	if (fdcache_lock & FDL_WANT) {
		fdcache_lock &= ~FDL_WANT;
		wakeup((caddr_t) &fdcache_lock);
	}

	return (error);
}

/*
 * vp is the current namei directory
 * ndp is the name to locate in that directory...
 */
int
fdesc_lookup(ap)
	struct vnop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	char *pname = cnp->cn_nameptr;
	struct proc *p = vfs_context_proc(ap->a_context);
	int numfiles = p->p_fd->fd_nfiles;
	int fd;
	int error;
	struct vnode *fvp;
	char *ln;

	if (cnp->cn_namelen == 1 && *pname == '.') {
		*vpp = dvp;
		
		if ( (error = vnode_get(dvp)) ) {
			return(error);
		}
		return (0);
	}

	switch (VTOFDESC(dvp)->fd_type) {
	default:
	case Flink:
	case Fdesc:
		/* should never happen */
		error = ENOTDIR;
		goto bad;

	case Froot:
		if (cnp->cn_namelen == 2 && bcmp(pname, "fd", 2) == 0) {
			error = fdesc_allocvp(Fdevfd, FD_DEVFD, dvp->v_mount, &fvp, VDIR);
			if (error)
				goto bad;
			*vpp = fvp;
			return (0);
		}

		ln = NULL;
		switch (cnp->cn_namelen) {
		case 5:
			if (bcmp(pname, "stdin", 5) == 0) {
				ln = "fd/0";
				fd = FD_STDIN;
			}
			break;
		case 6:
			if (bcmp(pname, "stdout", 6) == 0) {
				ln = "fd/1";
				fd = FD_STDOUT;
			} else
			if (bcmp(pname, "stderr", 6) == 0) {
				ln = "fd/2";
				fd = FD_STDERR;
			}
			break;
		}

		if (ln) {
			error = fdesc_allocvp(Flink, fd, dvp->v_mount, &fvp, VLNK);
			if (error)
				goto bad;
			VTOFDESC(fvp)->fd_link = ln;
			*vpp = fvp;
			return (0);
		} else {
			error = ENOENT;
			goto bad;
		}

		/* FALL THROUGH */

	case Fdevfd:
		if (cnp->cn_namelen == 2 && bcmp(pname, "..", 2) == 0) {
			if ((error = fdesc_root(dvp->v_mount, vpp, ap->a_context)))
				goto bad;
			return (0);
		}

		fd = 0;
		while (*pname >= '0' && *pname <= '9') {
			fd = 10 * fd + *pname++ - '0';
			if (fd >= numfiles)
				break;
		}

		if (*pname != '\0') {
			error = ENOENT;
			goto bad;
		}

		if (fd < 0 || fd >= numfiles ||
				*fdfile(p, fd) == NULL ||
				(*fdflags(p, fd) & UF_RESERVED)) {
			error = EBADF;
			goto bad;
		}

		error = fdesc_allocvp(Fdesc, FD_DESC+fd, dvp->v_mount, &fvp, VNON);
		if (error)
			goto bad;
		VTOFDESC(fvp)->fd_fd = fd;
		*vpp = fvp;
		return (0);
	}

bad:;
	*vpp = NULL;
	return (error);
}

int
fdesc_open(ap)
	struct vnop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct proc *p = vfs_context_proc(ap->a_context);
	int error = 0;

	switch ((int)(VTOFDESC(vp)->fd_type)) {
	case Fdesc:
		/*
		 * XXX Kludge: set p->p_dupfd to contain the value of the
		 * the file descriptor being sought for duplication. The error 
		 * return ensures that the vnode for this device will be
		 * released by vn_open. Open will detect this special error and
		 * take the actions in dupfdopen.  Other callers of vn_open or
		 * vnop_open will simply report the error.
		 */
		p->p_dupfd = VTOFDESC(vp)->fd_fd;	/* XXX */
		error = ENODEV;
		break;

	}

	return (error);
}

/*XXX*/
extern int soo_stat(struct socket *, struct stat *);

static int
fdesc_attr(int fd, struct vnode_attr *vap, vfs_context_t a_context)
{
	struct fileproc *fp;
	struct proc *p = vfs_context_proc(a_context);
	struct stat stb;
	int error;

	if ((error = fp_lookup(p, fd, &fp, 0)))
		return (error);
	switch (fp->f_fglob->fg_type) {
	case DTYPE_VNODE:
		if((error = vnode_getwithref((struct vnode *) fp->f_fglob->fg_data))) {
			break;
		}
		if ((error = vnode_authorize((struct vnode *)fp->f_fglob->fg_data,
			 NULL,
			 KAUTH_VNODE_READ_ATTRIBUTES | KAUTH_VNODE_READ_SECURITY,
			 a_context)) == 0)
			error = vnode_getattr((struct vnode *)fp->f_fglob->fg_data, vap, a_context);
		if (error == 0 && vap->va_type == VDIR) {
			/*
			 * directories can cause loops in the namespace,
			 * so turn off the 'x' bits to avoid trouble.
			 *
			 * XXX ACLs break this, of course
			 */
			vap->va_mode &= ~((VEXEC)|(VEXEC>>3)|(VEXEC>>6));
		}
		(void)vnode_put((struct vnode *) fp->f_fglob->fg_data);
		break;

	case DTYPE_SOCKET:
	case DTYPE_PIPE:
	        if (fp->f_fglob->fg_type == DTYPE_SOCKET)
		        error = soo_stat((struct socket *)fp->f_fglob->fg_data, &stb);
		else
		        error = pipe_stat((struct pipe *)fp->f_fglob->fg_data, &stb);

		if (error == 0) {
			if (fp->f_fglob->fg_type == DTYPE_SOCKET)
			        VATTR_RETURN(vap, va_type, VSOCK);
                        else
			        VATTR_RETURN(vap, va_type, VFIFO);

			VATTR_RETURN(vap, va_mode, stb.st_mode);
			VATTR_RETURN(vap, va_nlink, stb.st_nlink);
			VATTR_RETURN(vap, va_uid, stb.st_uid);
			VATTR_RETURN(vap, va_gid, stb.st_gid);
			VATTR_RETURN(vap, va_fsid, stb.st_dev);
			VATTR_RETURN(vap, va_fileid, stb.st_ino);
			VATTR_RETURN(vap, va_data_size, stb.st_size);
			VATTR_RETURN(vap, va_access_time, stb.st_atimespec);
			VATTR_RETURN(vap, va_modify_time, stb.st_mtimespec);
			VATTR_RETURN(vap, va_change_time, stb.st_ctimespec);
			VATTR_RETURN(vap, va_gen, stb.st_gen);
			VATTR_RETURN(vap, va_flags, stb.st_flags);
			VATTR_RETURN(vap, va_rdev, stb.st_rdev);
			VATTR_RETURN(vap, va_total_alloc, stb.st_blocks * stb.st_blksize);
			VATTR_RETURN(vap, va_acl, NULL);
		}
		break;

	default:
		error = EBADF;
	}

	fp_drop(p, fd, fp, 0);
	return (error);
}

int
fdesc_getattr(ap)
	struct vnop_getattr_args /* {
		struct vnode *a_vp;
		struct vnode_attr *a_vap;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct vnode_attr *vap = ap->a_vap;
	unsigned fd;
	int error = 0;
	struct timespec ts;

	switch (VTOFDESC(vp)->fd_type) {
	case Froot:
	case Fdevfd:
	case Flink:
		VATTR_RETURN(vap, va_fileid, VTOFDESC(vp)->fd_ix);
		VATTR_RETURN(vap, va_uid, 0);
		VATTR_RETURN(vap, va_gid, 0);
		VATTR_RETURN(vap, va_fsid, vp->v_mount->mnt_vfsstat.f_fsid.val[0]);
		VATTR_RETURN(vap, va_iosize, DEV_BSIZE);
		ts.tv_sec = boottime_sec();
		ts.tv_nsec = 0;
		VATTR_RETURN(vap, va_access_time, ts);
		VATTR_RETURN(vap, va_modify_time, ts);
		VATTR_RETURN(vap, va_change_time, ts);
		VATTR_RETURN(vap, va_gen, 0);
		VATTR_RETURN(vap, va_flags, 0);
		VATTR_RETURN(vap, va_rdev, 0);
		VATTR_RETURN(vap, va_acl, NULL);

		switch (VTOFDESC(vp)->fd_type) {
		case Flink:
			VATTR_RETURN(vap, va_mode, S_IRUSR|S_IRGRP|S_IROTH);
			VATTR_RETURN(vap, va_type, VLNK);	/* not strictly required */
			VATTR_RETURN(vap, va_nlink, 1);
			VATTR_RETURN(vap, va_data_size, strlen(VTOFDESC(vp)->fd_link));
			break;

		default:
			VATTR_RETURN(vap, va_mode, S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
			VATTR_RETURN(vap, va_type, VDIR);
			VATTR_RETURN(vap, va_nlink, 2);
			VATTR_RETURN(vap, va_data_size, DEV_BSIZE);
			break;
		}
		break;

	case Fdesc:
		fd = VTOFDESC(vp)->fd_fd;
		error = fdesc_attr(fd, vap, ap->a_context);
		break;

	default:
		return (EBADF);
		break;	
	}
	
	if (error == 0) {
		vp->v_type = vap->va_type;
	}

	return (error);
}

int
fdesc_setattr(ap)
	struct vnop_setattr_args /* {
		struct vnode *a_vp;
		struct vnode_attr *a_vap;
		vfs_context_t a_context;
	} */ *ap;
{
	struct fileproc *fp;
	unsigned fd;
	int error;
	struct proc * p = vfs_context_proc(ap->a_context);

	/*
	 * Can't mess with the root vnode
	 */
	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fdesc:
		break;

	default:
		return (EACCES);
	}

	fd = VTOFDESC(ap->a_vp)->fd_fd;
	if ((error = fp_lookup(vfs_context_proc(ap->a_context), fd, &fp, 0)))
		return (error);

	/*
	 * Can setattr the underlying vnode, but not sockets!
	 */
	switch (fp->f_fglob->fg_type) {
	case DTYPE_VNODE:
	{
		if ((error = vnode_getwithref((struct vnode *) fp->f_fglob->fg_data)) != 0)
			break;
		error = vnode_setattr((struct vnode *) fp->f_fglob->fg_data, ap->a_vap, ap->a_context);
		(void)vnode_put((struct vnode *) fp->f_fglob->fg_data);
		break;
	}

	case DTYPE_SOCKET:
	case DTYPE_PIPE:
		error = 0;
		break;

	default:
		kprintf("fp->f_fglob->fg_type = %d\n", fp->f_fglob->fg_type);
        error = EBADF;
		break;
	}

	fp_drop(p, fd, fp, 0);
	return (error);
}

#define UIO_MX 16

static struct dirtmp {
	u_long d_fileno;
	u_short d_reclen;
	u_short d_namlen;
	char d_name[8];
} rootent[] = {
	{ FD_DEVFD, UIO_MX, 2, "fd" },
	{ FD_STDIN, UIO_MX, 5, "stdin" },
	{ FD_STDOUT, UIO_MX, 6, "stdout" },
	{ FD_STDERR, UIO_MX, 6, "stderr" },
	{ 0, 0, 0, "" }
};

int
fdesc_readdir(ap)
	struct vnop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_flags;
		int *a_eofflag;
		int *a_numdirent;
		vfs_context_t a_context;
	} */ *ap;
{
	struct uio *uio = ap->a_uio;
	struct proc *p = current_proc();
	int i, error;

	/*
	 * We don't allow exporting fdesc mounts, and currently local
	 * requests do not need cookies.
	 */
	if (ap->a_flags & (VNODE_READDIR_EXTENDED | VNODE_READDIR_REQSEEKOFF))
		return (EINVAL);

	switch (VTOFDESC(ap->a_vp)->fd_type) {
	case Fdesc:
		return (ENOTDIR);

	default:
		break;
	}

	if (VTOFDESC(ap->a_vp)->fd_type == Froot) {
		struct dirent d;
		struct dirent *dp = &d;
		struct dirtmp *dt;
		int fd;

		i = uio->uio_offset / UIO_MX;
		error = 0;

		while (uio_resid(uio) > 0) {
			dt = &rootent[i];
			if (dt->d_fileno == 0) {
				/**eofflagp = 1;*/
				break;
			}
			i++;
			
			switch (dt->d_fileno) {
			case FD_STDIN:
			case FD_STDOUT:
			case FD_STDERR:
				fd = dt->d_fileno - FD_STDIN;
				if (fd >= p->p_fd->fd_nfiles)
					continue;
				if (*fdfile(p, fd) == NULL &&
						!(*fdflags(p, fd) &
							UF_RESERVED))
					continue;
				break;
			}
			bzero((caddr_t) dp, UIO_MX);
			dp->d_fileno = dt->d_fileno;
			dp->d_namlen = dt->d_namlen;
			dp->d_type = DT_UNKNOWN;
			dp->d_reclen = dt->d_reclen;
			bcopy(dt->d_name, dp->d_name, dp->d_namlen+1);
			error = uiomove((caddr_t) dp, UIO_MX, uio);
			if (error)
				break;
		}
		uio->uio_offset = i * UIO_MX;
		return (error);
	}

	i = uio->uio_offset / UIO_MX;
	error = 0;
	while (uio_resid(uio) > 0) {
		if (i >= p->p_fd->fd_nfiles)
			break;

		if (*fdfile(p, i) != NULL && !(*fdflags(p, i) & UF_RESERVED)) {
			struct dirent d;
			struct dirent *dp = &d;

			bzero((caddr_t) dp, UIO_MX);

			dp->d_namlen = sprintf(dp->d_name, "%d", i);
			dp->d_reclen = UIO_MX;
			dp->d_type = DT_UNKNOWN;
			dp->d_fileno = i + FD_STDIN;
			/*
			 * And ship to userland
			 */
			error = uiomove((caddr_t) dp, UIO_MX, uio);
			if (error)
				break;
		}
		i++;
	}

	uio->uio_offset = i * UIO_MX;
	return (error);
}

int
fdesc_readlink(ap)
	struct vnop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	int error;

	if (vp->v_type != VLNK)
		return (EPERM);

	if (VTOFDESC(vp)->fd_type == Flink) {
		char *ln = VTOFDESC(vp)->fd_link;
		error = uiomove(ln, strlen(ln), ap->a_uio);
	} else {
		error = ENOTSUP;
	}

	return (error);
}

int
fdesc_read(__unused struct vnop_read_args *ap)
{

	return (ENOTSUP);
}

int
fdesc_write(__unused struct vnop_write_args *ap)
{
	return (ENOTSUP);
}

int
fdesc_ioctl(__unused struct vnop_ioctl_args *ap)
{
	return (ENOTSUP);
}

int
fdesc_select(__unused struct vnop_select_args *ap)
{
	return (ENOTSUP);
}

int
fdesc_inactive(ap)
	struct vnop_inactive_args /* {
		struct vnode *a_vp;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;

	/*
	 * Clear out the v_type field to avoid
	 * nasty things happening in vgone().
	 */
	vp->v_type = VNON;
	return (0);
}

int
fdesc_reclaim(ap)
	struct vnop_reclaim_args /* {
		struct vnode *a_vp;
		vfs_context_t a_context;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct fdescnode *fd = VTOFDESC(vp);

	LIST_REMOVE(fd, fd_hash);
	FREE(vp->v_data, M_TEMP);
	vp->v_data = 0;

	return (0);
}

/*
 * Return POSIX pathconf information applicable to special devices.
 */
int
fdesc_pathconf(ap)
	struct vnop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
		vfs_context_t a_context;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}

int fdesc_vfree(__unused int *);

/*void*/
int
#if 0	/*stupid gcc*/
fdesc_vfree(__unused struct vnop_vfree_args *ap)
#else
fdesc_vfree(__unused int/*blah!*/ *ap)
#endif
{

	return (0);
}

/*
 * /dev/fd "should never get here" operation
 */
int
fdesc_badop(void)
{

	return (ENOTSUP);
	/* NOTREACHED */
}

#define VOPFUNC int (*)(void *)

#define fdesc_create (int (*) (struct  vnop_create_args *))eopnotsupp
#define fdesc_mknod (int (*) (struct  vnop_mknod_args *))eopnotsupp
#define fdesc_close (int (*) (struct  vnop_close_args *))nullop
#define fdesc_access (int (*) (struct  vnop_access_args *))nullop
#define fdesc_mmap (int (*) (struct  vnop_mmap_args *))eopnotsupp
#define	fdesc_revoke nop_revoke
#define fdesc_fsync (int (*) (struct  vnop_fsync_args *))nullop
#define fdesc_remove (int (*) (struct  vnop_remove_args *))eopnotsupp
#define fdesc_link (int (*) (struct  vnop_link_args *))eopnotsupp
#define fdesc_rename (int (*) (struct  vnop_rename_args *))eopnotsupp
#define fdesc_mkdir (int (*) (struct  vnop_mkdir_args *))eopnotsupp
#define fdesc_rmdir (int (*) (struct  vnop_rmdir_args *))eopnotsupp
#define fdesc_symlink (int (*) (struct vnop_symlink_args *))eopnotsupp
#define fdesc_strategy (int (*) (struct  vnop_strategy_args *))fdesc_badop
#define fdesc_advlock (int (*) (struct vnop_advlock_args *))eopnotsupp
#define fdesc_bwrite (int (*) (struct  vnop_bwrite_args *))eopnotsupp
#define fdesc_blktooff (int (*) (struct  vnop_blktooff_args *))eopnotsupp
#define fdesc_offtoblk (int (*) (struct  vnop_offtoblk_args *))eopnotsupp
#define fdesc_blockmap (int (*) (struct  vnop_blockmap_args *))eopnotsupp

int (**fdesc_vnodeop_p)(void *);
struct vnodeopv_entry_desc fdesc_vnodeop_entries[] = {
	{ &vnop_default_desc, (VOPFUNC)vn_default_error },
	{ &vnop_lookup_desc, (VOPFUNC)fdesc_lookup },	/* lookup */
	{ &vnop_create_desc, (VOPFUNC)fdesc_create },	/* create */
	{ &vnop_mknod_desc, (VOPFUNC)fdesc_mknod },	/* mknod */
	{ &vnop_open_desc, (VOPFUNC)fdesc_open },	/* open */
	{ &vnop_close_desc, (VOPFUNC)fdesc_close },	/* close */
	{ &vnop_access_desc, (VOPFUNC)fdesc_access },	/* access */
	{ &vnop_getattr_desc, (VOPFUNC)fdesc_getattr },	/* getattr */
	{ &vnop_setattr_desc, (VOPFUNC)fdesc_setattr },	/* setattr */
	{ &vnop_read_desc, (VOPFUNC)fdesc_read },	/* read */
	{ &vnop_write_desc, (VOPFUNC)fdesc_write },	/* write */
	{ &vnop_ioctl_desc, (VOPFUNC)fdesc_ioctl },	/* ioctl */
	{ &vnop_select_desc, (VOPFUNC)fdesc_select },	/* select */
	{ &vnop_revoke_desc, (VOPFUNC)fdesc_revoke },	/* revoke */
	{ &vnop_mmap_desc, (VOPFUNC)fdesc_mmap },	/* mmap */
	{ &vnop_fsync_desc, (VOPFUNC)fdesc_fsync },	/* fsync */
	{ &vnop_remove_desc, (VOPFUNC)fdesc_remove },	/* remove */
	{ &vnop_link_desc, (VOPFUNC)fdesc_link },	/* link */
	{ &vnop_rename_desc, (VOPFUNC)fdesc_rename },	/* rename */
	{ &vnop_mkdir_desc, (VOPFUNC)fdesc_mkdir },	/* mkdir */
	{ &vnop_rmdir_desc, (VOPFUNC)fdesc_rmdir },	/* rmdir */
	{ &vnop_symlink_desc, (VOPFUNC)fdesc_symlink },	/* symlink */
	{ &vnop_readdir_desc, (VOPFUNC)fdesc_readdir },	/* readdir */
	{ &vnop_readlink_desc, (VOPFUNC)fdesc_readlink },/* readlink */
	{ &vnop_inactive_desc, (VOPFUNC)fdesc_inactive },/* inactive */
	{ &vnop_reclaim_desc, (VOPFUNC)fdesc_reclaim },	/* reclaim */
	{ &vnop_strategy_desc, (VOPFUNC)fdesc_strategy },	/* strategy */
	{ &vnop_pathconf_desc, (VOPFUNC)fdesc_pathconf },	/* pathconf */
	{ &vnop_advlock_desc, (VOPFUNC)fdesc_advlock },	/* advlock */
	{ &vnop_bwrite_desc, (VOPFUNC)fdesc_bwrite },	/* bwrite */
	{ &vnop_pagein_desc, (VOPFUNC)err_pagein },	/* pagein */
	{ &vnop_pageout_desc, (VOPFUNC)err_pageout },	/* pageout */
        { &vnop_copyfile_desc, (VOPFUNC)err_copyfile },	/* Copyfile */
	{ &vnop_blktooff_desc, (VOPFUNC)fdesc_blktooff },	/* blktooff */
	{ &vnop_blktooff_desc, (VOPFUNC)fdesc_offtoblk },	/* offtoblk */
	{ &vnop_blockmap_desc, (VOPFUNC)fdesc_blockmap },	/* blockmap */
	{ (struct vnodeop_desc*)NULL, (VOPFUNC)NULL }
};
struct vnodeopv_desc fdesc_vnodeop_opv_desc =
	{ &fdesc_vnodeop_p, fdesc_vnodeop_entries };

Summary: mtools, read/write/list/format DOS disks under Unix
Name: mtools
Version: 3.9.9
Release: 2
#Icon: mtools-icon.gif
Copyright: GPL/Lilux
Group: Utilities/System
Source: mtools-3.9.9.tar.gz
%description
Mtools is a collection of utilities to access MS-DOS disks
from Unix without mounting them. It supports Win'95 style
long file names, OS/2 Xdf disks, ZIP/JAZ disks and 2m
disks (store up to 1992k on a high density 3 1/2 disk).


%prep
%setup
./configure --prefix=/usr --infodir=/usr/share/info

%build
make

%install
make install
make install-info
/usr/bin/strip /usr/bin/mtools /usr/bin/mkmanifest /usr/bin/floppyd

%files
/usr/share/info/mtools.info.gz
/usr/man/man1/floppyd.1
/usr/man/man1/mattrib.1
/usr/man/man1/mbadblocks.1
/usr/man/man1/mcat.1
/usr/man/man1/mcd.1
/usr/man/man1/mcopy.1
/usr/man/man1/mdel.1
/usr/man/man1/mdeltree.1
/usr/man/man1/mdir.1
/usr/man/man1/mdu.1
/usr/man/man1/mformat.1
/usr/man/man1/mkmanifest.1
/usr/man/man1/mlabel.1
/usr/man/man1/mmd.1
/usr/man/man1/mmount.1
/usr/man/man1/mmove.1
/usr/man/man1/mpartition.1
/usr/man/man1/mrd.1
/usr/man/man1/mren.1
/usr/man/man1/mshowfat.1
/usr/man/man1/mtools.1
/usr/man/man5/mtools.5
/usr/man/man1/mtoolstest.1
/usr/man/man1/mtype.1
/usr/man/man1/mzip.1
/usr/bin/mattrib
/usr/bin/mbadblocks
/usr/bin/mcat
/usr/bin/mcd
/usr/bin/mcopy
/usr/bin/mdel
/usr/bin/mdeltree
/usr/bin/mdir
/usr/bin/mdu
/usr/bin/mformat
/usr/bin/minfo
/usr/bin/mkmanifest
/usr/bin/mlabel
/usr/bin/mmd
/usr/bin/mmount
/usr/bin/mmove
/usr/bin/mpartition
/usr/bin/mrd
/usr/bin/mren
/usr/bin/mshowfat
/usr/bin/mtools
/usr/bin/mtoolstest
/usr/bin/mtype
/usr/bin/mzip
/usr/bin/floppyd
/usr/bin/mcheck
/usr/bin/mcomp
/usr/bin/mxtar
/usr/bin/tgz
/usr/bin/uz

%pre
groupadd floppy 2>/dev/null || echo -n ""

%post
if [ -f /usr/bin/install-info ] ; then
	if [ -f /usr/info/dir ] ; then
		/usr/bin/install-info /usr/info/mtools.info /usr/info/dir
	fi
	if [ -f /usr/info/dir.info ] ; then
		/usr/bin/install-info /usr/info/mtools.info /usr/info/dir.info
	fi
fi


%preun
install-info --delete /usr/info/mtools.info /usr/info/dir.info
if [ -f /usr/bin/install-info ] ; then
	if [ -f /usr/info/dir ] ; then
		/usr/bin/install-info --delete /usr/info/mtools.info /usr/info/dir
	fi
	if [ -f /usr/info/dir.info ] ; then
		/usr/bin/install-info --delete /usr/info/mtools.info /usr/info/dir.info
	fi
fi

#
# rudimentary makefile for building mtools 3.1 on the BeOS
#

CC=mwcc -O7

OBJS=buffer.o codepage.o codepages.o config.o copyfile.o devices.o \
directory.o expand.o fat.o fat_free.o file.o file_name.o file_read.o \
filter.o force_io.o hash.o init.o match.o mainloop.o mattrib.o mbadblocks.o \
mcd.o mcopy.o mdel.o mdir.o mformat.o minfo.o misc.o missFuncs.o \
mk_direntry.o mlabel.o mmd.o mmount.o mmove.o mpartition.o mzip.o mtools.o \
parse.o plain_io.o precmd.o privileges.o scsi.o signal.o stream.o \
streamcache.o subdir.o toupper.o tty.o vfat.o xdf_io.o

all: mtools mkmanifest

$(OBJS): config.h

config.h: config.h.Be
	cp config.h.Be config.h

mtools:	$(OBJS)
	$(CC) -o mtools $(OBJS)

mkmanifest: mkmanifest.o
	$(CC) -o mkmanifest mkmanifest.c

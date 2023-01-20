/*
 * streamcache.c
 * Managing a cache of open disks
 */

#include "sysincludes.h"
#include "msdos.h"
#include "mtools.h"
#include "vfat.h"
#include "fs.h"
#include "mainloop.h"
#include "plain_io.h"
#include "file.h"

static int is_initialized = 0;
static Stream_t *fss[256]; /* open drives */

static void finish_sc(void)
{
	int i;

	for(i=0; i<256; i++){
		if(fss[i] && fss[i]->refs != 1 )
			fprintf(stderr,"Streamcache allocation problem:%c %d\n",
				i, fss[i]->refs);
		FREE(&(fss[i]));
	}
}

static void init_streamcache(void)
{
	int i;

	if(is_initialized)
		return;
	is_initialized = 1;
	for(i=0; i<256; i++)
		fss[i]=0;
	atexit(finish_sc);
}

Stream_t *open_root_dir(unsigned char drive, int flags)
{
	Stream_t *Fs;

	init_streamcache();

	drive = toupper(drive);
	
	/* open the drive */
	if(fss[drive])
		Fs = fss[drive];
	else {
		Fs = fs_init(drive, flags);
		if (!Fs){
			fprintf(stderr, "Cannot initialize '%c:'\n", drive);
			return NULL;
		}

		fss[drive] = Fs;
	}

	return OpenRoot(Fs);
}

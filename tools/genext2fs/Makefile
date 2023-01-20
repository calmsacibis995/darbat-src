all: genext2fs
INSTALL=install
CFLAGS=-Wall -O2

install:
	$(INSTALL) -d $(DESTDIR)/usr/bin/
	$(INSTALL) -m 755 genext2fs $(DESTDIR)/usr/bin/
	$(INSTALL) -d $(DESTDIR)/usr/share/man/man8/
	$(INSTALL) -m 644 genext2fs.8 $(DESTDIR)/usr/share/man/man8/

clean:
	-rm genext2fs
	rm -rf test ext2.img

check: all
	mkdir -p test
	dd if=/dev/zero of=test/zero count=1
	./genext2fs -b 4096 -d test ext2.img
	
	md5_correct=d048d86c381a4ad361c9652f86b1eba9; \
	md5_tested=`md5sum ext2.img 2>/dev/null | cut -f 1 -d " "`; \
	if [ "$$md5_tested" = "$$md5_correct" ] ; then \
		echo "test succeeded."; \
	else \
		md5_tested=`md5 ext2.img 2>/dev/null | cut -f 4 -d " "`; \
		if [ "$$md5_tested" = "$$md5_correct" ] ; then \
			echo "test succeeded."; \
		else \
			echo "test failed."; \
		fi \
	fi
	

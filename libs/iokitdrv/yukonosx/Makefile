CFLAGS = -O2 -Wall -I/home/glee/src/iguana/libs/xnuglue/xnu_include/include/osfmk -I/home/glee/src/iguana/libs/xnuglue/xnu_include/include/bsd -I/home/glee/src/iguana/libs/xnuglue/xnu_include/include/pexpert -I/home/glee/src/iguana/libs/xnuglue/include -I/home/glee/src/openbsd/sys
OBJ = yukonglue.o if_sk.o
CC = cc

all: yukon

yukon: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o yukon

clean:
	rm $(OBJ)

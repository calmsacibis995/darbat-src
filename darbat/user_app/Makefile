
# XXX: This is a makefile

CFLAGS = -ffreestanding -nostdlib -nostdinc -Wall -Werror -march=i386 -m32

SRC = main.c libsystem.c hacklibc.c crt0.S

DEPS = hacklibc.h libsystem.h Makefile ../igcompat/syscallnums.h

INCLUDES = -I../igcompat -I../../libs/c/include -I../../libs/l4/include -I../../libs/c/arch_include/ia32 

TARGET = launchd

LIBS = -L../../build/iguana/libs/l4 -ll4

all: $(TARGET)

$(TARGET): $(SRC) ../igcompat/syscallnums.h # $(LIBS)
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(TARGET)
TARGET = init
CC = gcc
LD = ld 
CFLAGS = -c -I../include -fno-builtin
#LDFLAGS= ../../lib/libc/libc.a ../../lib/csu/csu.a
LDFLAGS= ../../lib/libc/*.o ../../lib/csu/*.o

CSOUCE_FILES = $(wildcard *.c)
SSOUCE_FILES = $(wildcard *.S)
OBJS  = $(patsubst %.c,%.o,$(CSOUCE_FILES))
OBJS += $(patsubst %.S,%.S.o,$(SSOUCE_FILES))

%.o : %.c ../include/*.h
	$(CC) $(CFLAGS) $< -o $@
%.S.o : %.S  ../include/*.h
	$(CC) $(CFLAGS) $< -o $@


all:$(OBJS)
	$(LD) -Tlink.ld $(LDFLAGS) $< -o $(TARGET)
.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
.PHONY:c
c:
	make clean

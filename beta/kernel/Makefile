CC = gcc
CFLAGS = -m32 -c -I../include -fno-builtin 

CSOUCE_FILES = $(wildcard *.c)
SSOUCE_FILES = $(wildcard *.S)
OBJS  = $(patsubst %.c,%.o,$(CSOUCE_FILES))
OBJS += $(patsubst %.S,%.S.o,$(SSOUCE_FILES))

%.o : %.c ../include/*.h
	$(CC) $(CFLAGS) $< -o $@
%.S.o : %.S  ../include/*.h
	$(CC) $(CFLAGS) $< -o $@


all:$(OBJS)

.PHONY:clean
clean:
	$(RM) $(OBJS)
.PHONY:c
c:
	make clean

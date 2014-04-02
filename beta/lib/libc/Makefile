CC = gcc
INCLUDE = ../../include
CFLAGS = -c -I$(INCLUDE) -fno-builtin
TARGET = libc.a

CSOUCE_FILES = $(wildcard *.c)
SSOUCE_FILES = $(wildcard *.S)
OBJS  = $(patsubst %.c,%.o,$(CSOUCE_FILES))
OBJS += $(patsubst %.S,%.S.o,$(SSOUCE_FILES))

%.o : %.c $(INCLUDE)/*.h
	$(CC) $(CFLAGS) $< -o $@
%.S.o : %.S  $(INCLUDE)/*.h
	$(CC) $(CFLAGS) $< -o $@


all:$(OBJS)
	ar cru $(TARGET) $(OBJS)
.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
.PHONY:c
c:
	make clean

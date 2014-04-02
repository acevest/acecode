CC = gcc
CFLAGS = -O -g -w -fpermissive
INCLUDE = 
LFLAGS =

TARGET = netpeeper

SOUCE_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SOUCE_FILES))

%.o : %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	gcc -o $@ $^ -lnids -lnet -lpcap  -lgthread-2.0

.PHONY:clean
clean:
	$(RM) $(TARGET) $(OBJS)

CC	= gcc
CPP	= g++
BINS	= countc htc
SCRIPTS = cls cs
DST	= /usr/local/bin/

%.o : %.c
	$(CC) $< -o $@
%.o : %.cc
	$(CC) $< -o $@

.PHONY:every
every: $(BINS)
	cp $(BINS) $(DST)
	cp $(SCRIPTS) $(DST)
.PHONY:clean
clean:
	rm $(BINS) -f


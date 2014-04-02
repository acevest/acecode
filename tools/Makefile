CC	= gcc
CPP	= g++
BINS	= countc cpuid htc
SCRIPTS = cls cs
DST	= /usr/local/bin/

%.o : %.c
	$(CC) $< -o $@
%.o : %.cc
	$(CC) $< -o $@

.PHONY:every
every: $(BINS)
	sudo cp $(BINS) $(DST)
	sudo cp $(SCRIPTS) $(DST)
.PHONY:clean
clean:
	rm $(BINS) -f


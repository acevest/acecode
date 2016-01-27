CC	= gcc
CPP	= g++
BINS	= countc htc cpuid
SCRIPTS = cls cs
DST	= $(HOME)/.local/bin/ 

%.o : %.c
	$(CC) $< -o $@
%.o : %.cc
	$(CC) $< -o $@

.PHONY:every
every: $(BINS)
	cp $(BINS) $(DST)
	cp $(SCRIPTS) $(DST)
	rm -f $(BINS)
.PHONY:clean
clean:
	rm -f $(BINS)


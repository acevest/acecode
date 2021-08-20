CC	= gcc
CPP	= g++
BINS	= countc htc
SCRIPTS = cls cs int2ip
DST	= $(HOME)/.local/bin/ 

%.o : %.c
	$(CC) $< -o $@
%.o : %.cc
	$(CC) $< -o $@

.PHONY:every
every: $(BINS)
	mkdir -p $(DST)
	cp $(BINS) $(DST)
	cp $(SCRIPTS) $(DST)
	rm -f $(BINS)
.PHONY:clean
clean:
	rm -f $(BINS)


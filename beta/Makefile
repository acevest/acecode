############################################################################
CF		= -c -I include -fno-builtin
CC		= $(_CC) $(CF) -o
MAKE	= make
LD		= ld
SYSTEMMAP	= System.map
KERNELBIN	= Beta
LINKSCRIPT	= scripts/link.ld
OBJS		= boot/*.o kernel/*.o lib/libc/libc.a
#BINS#######################################################################
$(KERNELBIN):
	$(MAKE) -C boot		all
	$(MAKE) -C lib		all
	$(MAKE) -C kernel	all
	$(MAKE) -C servers	all
	$(LD) -M -T$(LINKSCRIPT) -o $@ $(OBJS) > $(SYSTEMMAP)
	$(LD) -T$(LINKSCRIPT) -o $@ $(OBJS)
	./scripts/debug.sh
.PHONY:real
real:

.PHONY:clean
clean:
	$(MAKE) -C boot		clean
	$(MAKE) -C lib		clean
	$(MAKE) -C kernel	clean
	$(MAKE) -C servers	clean
	rm -f $(KERNELBIN) System.map snapshot.txt log.txt
.PHONY:c
c:
	$(MAKE) clean

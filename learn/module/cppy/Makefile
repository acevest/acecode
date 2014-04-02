#cppy-objs := main.o
#obj-m	:= cppy.o
obj-m := main.o
module-objs := cppy.o main.o
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf *.order
	rm -rf .tmp_versions
	rm -rf Module.symvers

obj-m := pps-gpio-poll.o
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) HOSTCFLAGS=$(HOSTCFLAGS) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) KBUILD_HAVE_NLS=$(KBUILD_HAVE_NLS) CC=$(CC) SUBDIRS=$(PWD) modules

SRCS := test_add.c
obj-m := my_module.o

SYSCALL_ADDRESS = 0x$(subst R sys_call_table,,$(shell grep sys_call_table /boot/System.map-$(shell uname -r)))
CFLAGS_my_module.o += -DSYSCALL_TABLE=$(SYSCALL_ADDRESS)

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc test_add.c -o test_add

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	$(RM) -rf test_add.o test_add


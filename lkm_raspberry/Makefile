TARGET_MODULE:=lkm_raspberry
obj-m += $(TARGET_MODULE).o
all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
load:
	sudo insmod ./$(TARGET_MODULE).ko
unload:
	sudo rmmod ./$(TARGET_MODULE).ko
info:
	modinfo $(TARGET_MODULE).ko
test:
	sudo dmesg -C
	lsmod | grep -q $(TARGET_MODULE) && sudo rmmod $(TARGET_MODULE).ko || :
	sudo insmod $(TARGET_MODULE).ko
	sleep 2
	sudo rmmod $(TARGET_MODULE).ko
	dmesg

TARGET_MODULE:=lkm_device
obj-m += $(TARGET_MODULE).o
all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
load:
	sudo insmod ./$(TARGET_MODULE).ko
unload:
	sudo rmmod ./$(TARGET_MODULE).ko
test:
	sudo dmesg -C
	lsmod | grep -q $(TARGET_MODULE) && sudo rmmod $(TARGET_MODULE).ko || :
	sudo insmod $(TARGET_MODULE).ko
	sudo mknod /dev/test-device c `sudo dmesg | grep 'lkm' | grep -o '[0-9]\+' | tail -1` 0
	timeout 2 cat /dev/test-device > test || :
	sudo rm /dev/test-device
	cat test
	sudo rmmod $(TARGET_MODULE).ko
	dmesg
	rm test

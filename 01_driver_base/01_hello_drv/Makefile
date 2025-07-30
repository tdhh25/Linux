KERNEL_DIR = /home/book/100ask_imx6ull-sdk/Linux-4.9.88

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
	$(CROSS_COMPILE)gcc -o hello_test hello_drv_test.c

clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
	rm -rf hello_test
	rm -rf modules.order  Module.symvers

obj-m += hello_drv.o


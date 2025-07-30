KERNEL_DIR = /home/book/100ask_imx6ull-sdk/Linux-4.9.88

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
	$(CROSS_COMPILE)gcc -o led_test led_drv_test.c

clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
	rm -rf led_test
	rm -rf modules.order  Module.symvers

obj-m += led_drv.o


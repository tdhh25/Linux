KERNEL_DIR = /home/book/100ask_imx6ull-sdk/Linux-4.9.88

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
	$(CROSS_COMPILE)gcc -o stepper_test stepper_test.c

clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
	rm -rf stepper_test
	rm -rf modules.order  Module.symvers

obj-m += stepper_drv.o


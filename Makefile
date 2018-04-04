obj-m+=LKM_input_device_driver.o
obj-m+=LKM_output_device_driver.o

export KROOT = /lib/modules/$(shell uname -r)/build

allofit: modules
modules:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean
clean: kernel_clean
	rm -rf Module.symvers modules.order

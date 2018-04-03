obj-m+=LKM_input_device_driver.o
obj-m+=LKM_output_device_driver.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules 


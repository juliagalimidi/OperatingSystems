obj-m+=LKMChar.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules 


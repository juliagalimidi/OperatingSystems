# OperatingSystems
Navigate to the directory where the files are in terminal and type "make" and hit enter. This will run the make file.  Note that this time there are two .c files that are being compiled and produced.  LKM_input_device_driver.c and LKM_output_device_driver.c
                                
sudo insmod ./LKM_input_device_driver.ko		Load the kernel module into the kernel itself so that we can run it

sudo insmod ./LKM_output_device_driver.ko		Load the output kernel module into the kernel.  

You have to run these in this order otherwise it will throw an error

cat /proc/modules	Double check the module is loaded, you should see "LKM_input_device_driver" and "LKM_output_device_driver" at the top

gcc -o test	LKM_tester.c		Compile the test program

sudo ./test						Run the test program, it will ask you for input

sudo rmmod LKM_input_device_driver 				::  remove the kernel module

sudo rmmod LKM_output_device_driver 				::  remove the kernel module

dmesg			:: View what's happening in the Kernel, this where we should see all the printk statements in the kernel modules
lsmod		:: See the list of kernel modules that are loaded

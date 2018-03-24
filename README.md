# OperatingSystems

make 							Navigate to the directory where the files are in terminal and type "make" and hit enter. 
								This will run the make file.
                                
sudo insmod ./LKMChar.ko		Load the kernel module into the kernel itself so that we can run it

cat /proc/modules				Double check the module is loaded, you should see "LKMChar" at the top

gcc -o test	LKMChartest.c		Compile

sudo ./test						Run

sudo rmmod LKMChar 				remove the kernel module

dmesg							View what's happening in the Kernel
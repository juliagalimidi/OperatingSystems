/* 
* @file   LKMChartest.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH 1024              //Store bytes written to it up to a constant buffer size (at least 1KB)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
int currentBuffSize = 0;
int main(){
   int ret, fd, i, j = 0;
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");
   fd = open("/dev/LKMChar", O_RDWR);             // Open the device with read/write access
   if (fd < 0)
   {
      perror("Failed to open the device...");
      return errno;
   }
	while(currentBuffSize + strlen(stringToSend) < BUFFER_LENGTH)
   {
		printf("Type in a short string to send to the kernel module:\n");
		scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
		printf("Writing message to the device [%s].\n", stringToSend);
		ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
		currentBuffSize += strlen(stringToSend);
		if (ret < 0)
		{
			perror("Failed to write the message to the device.");
			return errno;
		}
   } 
	if(currentBuffSize < BUFFER_LENGTH)
	{
		int spaceRemaining = (currentBuffSize + strlen(stringToSend)) - BUFFER_LENGTH;
		char modStringToSend[spaceRemaining];
		
		for(i = currentBuffSize; i < BUFFER_LENGTH; i++)
		{
			modStringToSend[j] = stringToSend[j];
		}
		ret = write(fd, modStringToSend, strlen(stringToSend));
		currentBuffSize += strlen(modStringToSend);
	}
   
 
   printf("Press ENTER to read back from the device...\n");
   getchar();
 
   printf("Reading from the device...\n");
   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
   if (ret < 0){
      perror("Failed to read the message from the device.");
      return errno;
   }
   printf("The received message is: [%s]\n", receive);
   printf("End of the program\n");
   return 0;
}

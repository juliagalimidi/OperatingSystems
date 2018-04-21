#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

 
#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
 
int main(){
   int ret, fd1, fd2;
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");

   //we need to define our two modules, fd1 will be our input module, fd2 will be the output module
   fd1 = open("/dev/LKM_input_device_driver", O_RDWR);
   fd2 = open("/dev/LKM_output_device_driver", O_RDWR);             // Open the device with read/write access
   if (fd1 < 0){
      perror("Failed to open the device...");
      return errno;
   }
   printf("Type in a short string to send to the kernel module:\n");
   scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
  
    // check for UCF
   char *temp = strstr(stringToSend, "UCF");
	printf("UCF found? : %s \n", temp);    
    int position;  
    char *result = "";
     // If UCF is in the string
     if(temp != NULL)
     {
        // Caluclate where UCF begins
        position = temp - stringToSend; 
	// Index where first string ends
        int  posStart = position; 
        // Index where last string starts
        int  posEnd = posStart + 3;
 
        // INSERT TEST TO MAKE SURE POSEND ISNT PAST END
        printf("posStart = %d, postEnd = %d\n", posStart, posEnd);
        printf("past position, pos = %d \n", position);
	fflush(stdout);

        // Get string before UCF
        char startStr[strlen(stringToSend) + 38];
        memset(startStr, '\0', sizeof(startStr));
        strncpy(startStr, stringToSend + 0, posStart);
         printf(" PRINTING START HERE : %s\n", startStr);
        char* endTest = stringToSend + posEnd; 
printf("END STRING: %s\n", endTest);
       strcat(result, "Undefeated 2018 National Campions UCF");
       strcat(result, endTest);
       printf("RESULT : %s\n", result);


}
//      strncpy(end, stringToSend + posEnd, strlen(stringToSend) - 1);
//      printf("first half: %s\n", start);
//     printf("last half : %s\n", end);
/*	 int i;
       printf("AT FOR LOOP\n");
       for(i = 0; i < position; i++)
       {
	 printf("IN FIRST LOOP i = %d\n", i);
fflush(stdout);          
strcat(result, stringToSend[i]);
printf("strcat completed\n");
fflush(stdout);
       }

      strcat(result, "Undefeated 2018 National Champions UCF");

      for(i = position + 3; i  < strlen(stringToSend); i++)
      {
          strcat(result, stringToSend[i]);
      }
       strcpy(stringToSend,result);
*/  
     // strcpy(stringToSend, "Undefeated 2017 National Campions UCF");
    // char* test = strncpy(stringToSend, stringToSend + 0, position  - 0);
//strcpy(stringToSend, test); 
    // }

 



  printf("Writing message to the device [%s].\n", stringToSend);
  
  ret = write(fd1, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }
 
   printf("Press ENTER to read back from the device...\n");
   getchar();
 
   printf("Reading from the device...\n");
   ret = read(fd2, receive, BUFFER_LENGTH);        // Read the response from the LKM
   if (ret < 0){
      perror("Failed to read the message from the device.");
      return errno;
   }

   printf("RET: %d\n", ret);
   printf("The received message is: [%s]\n", receive);
   printf("End of the program\n");
   return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

 
#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
#define replaceStrLen 40  // length of string to replace UCF with  
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
  
   // Check for UCF
   char *temp = strstr(stringToSend, "UCF");
   printf("checked for UCF\n");
   int position;  
   // Get amount of times ucf occurs
   char* endTest;
   char countStr[strlen(stringToSend)];
   strcpy(countStr, stringToSend);
   printf("string copied correctly\n");
   int count = 0;
   printf("Temp is %s\n", temp);
   fflush(stdout);
   while(temp != NULL)
   {
         printf("in loop! Getting count!\n");
        fflush(stdout);
	// Caluclate where UCF begins
        position = temp - countStr; 
        // Index where first string ends
        int  posStart = position; 
        // Index where last string starts
        int  posEnd = posStart + 3;
 
        // Get remaining string after UCF
        endTest = countStr + posEnd; 

        // Set string to send to be end string
        strcpy(countStr, endTest);

        // See if remaining string has string UCF in it
        temp = strstr(countStr, "UCF");

     count++;
   }
    printf("count string is %s\n", countStr);
   printf("string to send is %s\n", stringToSend);

   temp = strstr(stringToSend, "UCF");
   printf("string to send is current %s\n", stringToSend);
   // set result to be correct size
   char result[strlen(stringToSend) + (replaceStrLen * count)];
   int resultFound = 0;
   if(count > 0)
      resultFound = 1;
   printf("time to format string: temp is %s\n", temp);
fflush(stdout);
 // If UCF is in the string
     while(temp != NULL)
     {
        // Caluclate where UCF begins
        position = temp - stringToSend; 
	// Index where first string ends
        int  posStart = position; 
        // Index where last string starts
        int  posEnd = posStart + 3;
 
        // Get string before UCF
        char startStr[strlen(stringToSend) + 38];
        memset(startStr, '\0', sizeof(startStr));
        strncpy(startStr, stringToSend + 0, posStart);
        printf("start string: %s \n", startStr);
        // Get remaining string
        endTest = stringToSend + posEnd; 
       
	// Copy start of string and UCF replacement
     	strcat(result, startStr);
        strcat(result, "Undefeated 2018 National Campions UCF");
        
        // Print what result currently is
        printf("RESULT : %s\n", result);
              
        // Set string to send to be end string
        strcpy(stringToSend, endTest);

        // See if remaining string has string UCF in it
        temp = strstr(stringToSend, "UCF");
    }
    
    // Put remaining string after all UCF have been replaced
  if(resultFound == 1)
  {
     printf("UCF WAS FOUND : RETURNING RESULT AS STRINGTOSEND FOR WRITE\n");
     strcat(result, endTest);
    printf("result is %s\n", result);
   // Copy final result to strng to send
       strcpy(stringToSend, result);
  }
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

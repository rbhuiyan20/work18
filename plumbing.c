#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main() {
    printf("This program take in input and returns it in all caps! \n");

    //makes two pipes

    //parents pipe 
    int parentP[2];
    pipe(parentP);

    //child pipe 
    int childP[2];
    pipe(childP);

   
    int f; 
    f= fork();

    if (f) { 
        
        //parent pipe stuff
        // prompts user for input, sends input to child, waits for response, displays response to the user

        close(childP[READ]);
        close(parentP[WRITE]);

       
        while (1) {
            char userIn[100];
            printf("Input please 0_0: ");
            fgets(userIn, 100, stdin);
            // writes in the user input
            write(childP[WRITE], userIn, sizeof(userIn)); 

            // child pipe feeds parents pipe its response
            read(parentP[READ], userIn, sizeof(userIn)); 
            // wait 2 seconds before displaying response
             sleep(2);
            printf("Input in all UPPERCASE: %s\n", userIn); 
        }
    }

    else { 
        
        //child pipe stuff
        // gets input, processes, sends response

        close(childP[WRITE]);
        close(parentP[READ]);
        
        // store user input
        char userIn[100];

        while (1) {
            read(childP[READ], userIn, sizeof(userIn)); 

            // simple for loop to iterate through the character ray containing the input and turns the characters into uppercase
            for(int i=0; i<strlen(userIn); i++) {
                userIn[i] = toupper(userIn[i]);
            }
            // sends the response to parent
            
            write(parentP[WRITE], userIn, sizeof(userIn));  
        }
    }

    return 0;
}
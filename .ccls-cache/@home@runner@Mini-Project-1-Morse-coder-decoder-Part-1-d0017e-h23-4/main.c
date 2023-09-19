#include <stdio.h>
#include <string.h>
#include "morse.h"

int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
    char command[32];
    char fname[MAX_CHAR_FNAME];


  //It is necessary to fill in the vocabulary initially
   initializeDictionary();

    while(!exit) {
        printf("What would like to do? Enter 'help' for list of commands\n>> ");
        scanf("%s", command);
        
        if(strcmp(command, "help") == 0) {
            displayHelp();
        }
        else if(strcmp(command, "exit") == 0) {
            exit = TRUE;
        }
        else {
            printf("Please enter a valid input\n\n");
        }
    }
    return 0;
}
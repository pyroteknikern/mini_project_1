#include <stdio.h>
#include <string.h>
#include "morse.h"

#define CMD_SIZE 32

int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
    char command[CMD_SIZE];
    char fname[MAX_CHAR_FNAME];
    char lname[MAX_CHAR_LNAME];

    char junk[100];

  //It is necessary to fill in the vocabulary initially
   initializeDictionary();
   initializeCoderDecoder();

    while(!exit) {
        printf("What would like to do? Enter 'help' for list of commands\n>> ");
       // scanf("%s", command);
         //   fgets(junk, 2, stdin);
        fgets(command, CMD_SIZE, stdin);
        command[strlen(command) - 1] = '\0';
        if(strcmp(command, "help") == 0) {
            displayHelp();
        }
        else if(strcmp(command, "exit") == 0) {
            exit = TRUE;
        }
        else if(strcmp(command, "code input text") == 0) {
            printf("Enter text you want to encode\n(encoder) >> ");
            char encodedString[MAX_CHAR_FNAME*(MAX_MORSE_LENGTH+1)];
            //fgets(junk, 2, stdin);
            fgets(fname, MAX_CHAR_FNAME, stdin);
            fname[strlen(fname) - 1] = '\0';
            if(strcmp(fname, "exit") == 0) {
                printf("Exiting encoder mode...");
            }
            else {
                encodeToMorse(fname, encodedString);
                printf("\nMorse: %s\n\n\n", encodedString);
            }
        }
        else if(strcmp(command, "show") == 0) {
            printDictionary();
        }
        else if(strcmp(command, "case_sensitive") == 0) {
            setMode(TRUE);
        }
        else if(strcmp(command, "case_insensitive") == 0) {
            setMode(FALSE);
        }
        else if(strcmp(command, "decode input text") == 0) {
            printf("Enter text you want to decode\n(decoder) >> ");
            char decodedString[MAX_CHAR_FNAME*(MAX_MORSE_LENGTH+1)];
            //fgets(junk, 2, stdin);
            fgets(lname, MAX_CHAR_LNAME, stdin);
            if(!strcmp(lname, "exit")) {
                printf("Exiting decoder mode...\n");
            }
            else {
                decodeFromMorse(lname, decodedString);
                printf("\nDecoded: %s\n\n\n", decodedString);
            }
            fgets(junk, 100, stdin);
        }
        else {
            printf("Please enter a valid input\n\n");
        }
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "morse.h"


int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
   
    char command[CMD_SIZE];

    char input_text[INPUT_TEXT_LENGTH];
    char input_morse[INPUT_MORSE_LENGTH];
    
    char junk[100];

  //It is necessary to fill in the vocabulary initially
   initializeDictionary();
   initializeCoderDecoder();

    while(!exit) {
        printf("What would like to do? Enter 'help' for list of commands\n>> ");
        fgets(command, CMD_SIZE, stdin);
        command[strlen(command) - 1] = '\0';
        if(strcmp(command, "help") == 0) {
            displayHelp();
        }
        else if(strcmp(command, "exit") == 0) {
            exit = TRUE;
        }
        else if(strcmp(command, "code input text") == 0 || strcmp(command, "encode") == 0) {
            printf("Enter text you want to encode\n(encoder) >> ");
            char encodedString[INPUT_MORSE_LENGTH];
            fgets(input_text, INPUT_TEXT_LENGTH, stdin);
            input_text[strlen(input_text) - 1] = '\0';
            if(strcmp(input_text, "exit") == 0) {
                printf("Exiting encoder mode...\n");
            }
            else {
                encodeToMorse(input_text, encodedString);
                printf("\nMorse: %s\n\n\n", encodedString);
            }
        }
        else if(strcmp(command, "show") == 0) {
            printDictionary();
        }
        else if(strcmp(command, "case_sensitive") == 0 || strcmp(command, "cs") == 0) {
            setMode(TRUE);
        }
        else if(strcmp(command, "case_insensitive") == 0 || strcmp(command, "ci") == 0) {
            setMode(FALSE);
        }
        else if(strcmp(command, "decode input text") == 0 || strcmp(command, "decode") == 0) {
            printf("Enter code you want to decode\n(decoder) >> ");
            char decodedString[INPUT_TEXT_LENGTH];
            //fgets(junk, 2, stdin);
            fgets(input_morse, INPUT_MORSE_LENGTH, stdin);
            if(!strcmp(input_morse, "exit")) {
                printf("Exiting decoder mode...\n");
            }
            else {
                decodeFromMorse(input_morse, decodedString);
                printf("\nDecoded: %s\n\n\n", decodedString);
            }
        }
        else {
            printf("Please enter a valid input\n\n");
        }
    }
    return 0;
}

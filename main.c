#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "String.h"
#include "morse.h"


int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
   
    char command[CMD_SIZE];

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
            String input_str = new_str();
            file_to_string(&input_str, stdin);
            char* encodedString = malloc(input_str.length * MAX_MORSE_LENGTH * sizeof(char));
            encodedString[0] = '\0';
            if(strcmp(input_str.str, "exit") == 0) {
                printf("Exiting encoder mode...\n");
            }
            else {
                encodeToMorse(input_str.str, encodedString);
                printf("\nMorse: %s\n\n\n", encodedString);
            }
            free(encodedString);
            destroy_string(&input_str);
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
            printf("Enter text you want to decode\n(decoder) >> ");
            String input_str = new_str();
            file_to_string(&input_str, stdin);
            char* decodedString = malloc((nr_of_seg(input_str.str, ' ') + 1) * sizeof(char));
            decodedString[0] = '\0';
            if(strcmp(input_str.str, "exit") == 0) {
                printf("Exiting decoder mode...\n");
            }
            else {
                decodeFromMorse(input_str.str, decodedString);
                printf("\nDecoded: %s\n\n\n", decodedString);
            }
            free(decodedString);
            destroy_string(&input_str);
        }
        else if(strcmp(command, "search") == 0) {
            printf("Enter character you want to translate\n(search) >> ");
            char input_char = getc(stdin);
            char morseCode[MAX_MORSE_LENGTH];
            getMorseCode(input_char, morseCode);
            printf("\nMorse: %s\n\n\n", morseCode);
        }
        else if(strcmp(command, "test") == 0) {
            printf("\n>> ");
            String test = new_str();
            String test2 = new_str();
            file_to_string(&test, stdin);
            file_to_string(&test2, stdin);
            printf("\n%d\n", char_append_string(&test, 'K'));
            print_string(&test);
            printf("\n%d\n", cat_string(&test, &test2));
            print_string(&test);
            destroy_string(&test);
            destroy_string(&test2);
        }
        else {
            printf("Please enter a valid input\n\n");
        }
    }
    return 0;
}

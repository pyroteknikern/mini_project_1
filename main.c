#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "String.h"
#include "morse.h"


int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
  //It is necessary to fill in the vocabulary initially
    initializeDictionary();
    initializeCoderDecoder();
    
    String cmd = new_str();
    while(!exit) {
        printf("\n\nWhat would like to do? Enter 'help' for list of commands\n>> ");
        file_to_string(&cmd, stdin);
        trunk_trailing_spaces(cmd.str);
        if(strcmp(cmd.str, "help") == 0)
            displayHelp();
        else if(strcmp(cmd.str, "code input text") == 0 || strcmp(cmd.str, "encode") == 0)
            encode();
        else if(strcmp(cmd.str, "show") == 0)
            printDictionary();
        else if(strcmp(cmd.str, "case_sensitive") == 0 || strcmp(cmd.str, "cs") == 0)
            setMode(TRUE);
        else if(strcmp(cmd.str, "case_insensitive") == 0 || strcmp(cmd.str, "ci") == 0)
            setMode(FALSE);
        else if(strcmp(cmd.str, "decode input text") == 0 || strcmp(cmd.str, "decode") == 0)
            decode();
        else if(strcmp(cmd.str, "search") == 0)
            search();
        else if(strcmp(cmd.str, "exit") == 0)
            exit = TRUE;
        else if(strcmp(cmd.str, "test") == 0)
            test();
        else 
            printf("Please enter a valid input\n\n");
    }
    destroy_string(&cmd);
    return 0;
}

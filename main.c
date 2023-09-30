#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "String.h"
#include "morse.h"


int main(void) {
    printf("-----------The Morse coder-------------\n");

    int exit = FALSE;
  //It is necessary to fill in the vocabulary initially
    Dictionary dict = initialize_dictionary();
    CoderDecoder coderDecoder = initialize_coder_decoder(&dict);
    
    String cmd = string_new();

    while(!exit) {
        printf("\n\nWhat would like to do? Enter 'help' for list of commands\n(main) >> ");
        string_read_file(&cmd, stdin);
        str_trunk_trailing_spaces(cmd.str);
        if(strcmp(cmd.str, "help") == 0)
            display_help();
        else if(strcmp(cmd.str, "code input text") == 0 || strcmp(cmd.str, "encode") == 0)
            encode(&coderDecoder);
        else if(strcmp(cmd.str, "show") == 0)
            print_dictionary(&coderDecoder);
        else if(strcmp(cmd.str, "case_sensitive") == 0 || strcmp(cmd.str, "cs") == 0) {
            set_mode(&coderDecoder, TRUE);
            printf("\nDecoder is now case sensitive\n");
        }
        else if(strcmp(cmd.str, "case_insensitive") == 0 || strcmp(cmd.str, "ci") == 0) {
            set_mode(&coderDecoder, FALSE);
            printf("\nDecoder is now insensitive to case\n");
        }
        else if(strcmp(cmd.str, "decode input text") == 0 || strcmp(cmd.str, "decode") == 0)
            decode(&coderDecoder);
        else if(strcmp(cmd.str, "search") == 0)
            search(&coderDecoder);
        else if(strcmp(cmd.str, "caesar") == 0)
            caesar(&coderDecoder);
        else if(strcmp(cmd.str, "status") == 0)
            status(&coderDecoder);
        else if(strcmp(cmd.str, "exit") == 0)
            exit = TRUE;
        else if(strcmp(cmd.str, "test") == 0)
            continue;
        else 
            printf("Please enter a valid input\n\n");
    }
    string_destroy(&cmd);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "morse.h"
#include "String.h"


void buffer_clear() {
    while (fgetc(stdin) != '\n');
}

void display_help() {
    printf("- `help`, shows the list of commands and what they do.\n");
    printf("- `code input text`, - code the input text in Morse code.\n");
    printf("- `decode input text`, - decode the entered Morse code.\n");
    printf("- `search`, shows Morse code for the specified symbol.\n");
    printf("- `show`, Shows a table with Morse code.\n");
    printf("- `case_sensitive`- enable case-sensitive processing.\n");
    printf("- `case_insensitive` - enable case-insensitive processing.\n");
    printf("- `exit`, to exit\n\n");
}

// Implement the functions here

/*
 * initialize Dictionary struct
 */
Dictionary initialize_dictionary() {
    Dictionary dictionary;
    dictionary.id = 0;
    dictionary.size = MAX_DICTIONARY_SIZE;
    char alph[] = "abcdefghijklmnopqrstuvwxyz";
    strcpy(dictionary.alphabet, alph);
    char nums[] = "1234567890";
    strcpy(dictionary.numbers, nums);
    char chars[MAX_DICTIONARY_SIZE];
    strcpy(dictionary.characters, nums);
    strcat(dictionary.characters, alph);


    char* morse_numbers[] = {".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};
    char* morse_alphabet[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    for(size_t i = 0; i < NR_OF_NUMBERS; i++) {
        dictionary.morse_codes[i] = morse_numbers[i];
        dictionary.morse_numbers[i] = morse_numbers[i];
    }
    for(size_t i = 0; i < NR_OF_CHARACTERS; i++) {
        dictionary.morse_codes[i + NR_OF_NUMBERS] = morse_alphabet[i];
        dictionary.morse_alphabet[i] = morse_alphabet[i];
    }
    return dictionary;
}

/*
 * initializses the global CoderDecoder struct
*/
CoderDecoder initialize_coder_decoder(Dictionary* dictionary){
    CoderDecoder coderDecoder;
    coderDecoder.dictionary = *dictionary;
    coderDecoder.case_sensitive = true;
    coderDecoder.current_dictionary_id = dictionary->id;
    return coderDecoder;
}

/*
 * translates an ASCII character to morse code
 * param1: character you want to translate into morse
 * param2: pointer to a string that will be populated with morse
*/
int get_morse_code(CoderDecoder* coderDecoder, const char character, char *morseChar){
    strcpy(morseChar, "");
    char ch = character;
    for(int i = 0; i < coderDecoder->dictionary.size; i++) {
        if(!coderDecoder->case_sensitive)
            ch = tolower(ch);
        if(ch == coderDecoder->dictionary.characters[i]) {
            strcpy(morseChar, coderDecoder->dictionary.morse_codes[i]);
            return 1;
        }
    }
    return -1;
}


/*
 * encodes an ASCII string to morse code
 * param1: string you want to translate
 * param2: pointer to the string you want to populate with morse code
 * note: param2 not having enough memory can lead to undefined behaviour
*/
int encode_to_morse(CoderDecoder* coderDecoder, const char *text, char *encodedText) {
    encodedText[0] = '\0';
    char morseChar[MAX_MORSE_CHAR_LENGTH + 1] = "";
    int return_status = 1;
    int temp_status = 1;
    for(int i = 0; i < strlen(text); i++) {
        temp_status = get_morse_code(coderDecoder, text[i], morseChar);
        if(temp_status == -1)
            return_status = -1;
        else {
            strcat(encodedText, morseChar);
            strcat(encodedText, " ");
        }
    }
    return return_status;
}

/*
 * translate morse code to ASCII character
 * param1: string that contains morse code
 * param2: pointer to character that will be populated by the translated morse code
 */

int get_char_from_morse(CoderDecoder* coderDecoder, const char* morseChar, char* character) {
    for(int i = 0; i < coderDecoder->dictionary.size; i++) {
        if(strcmp(coderDecoder->dictionary.morse_codes[i], morseChar) == 0) {
            *character = coderDecoder->dictionary.characters[i];
            return 1;
        }
    }
    return -1;
}

/*
 * translates morse code to ASCII string
 * param1: string of the morse code, characters are separated by space
 * param2: pointer to string that will be populated by the decoded morse code
 * note: param2 not having enough memory can lead to undefined behaviour
 */
int decode_from_morse(CoderDecoder* coderDecoder, const char *morseCode, char *decodedText) {
    char morseChar[MAX_MORSE_CHAR_LENGTH + 1] = "";
    uint morse_len_tracker = 0;
    char placeholderChar;
    int return_status = 1;
    for(int i = 0; i < strlen(morseCode) + 1; i++) {
        if(morseCode[i] == ' ' || morseCode[i] == '\0') {
            if(get_char_from_morse(coderDecoder, morseChar, &placeholderChar) == -1) return_status = -1;
            strncat(decodedText, &placeholderChar, 1);
            morseChar[0] = '\0';
            morse_len_tracker = 0;
            placeholderChar = '\0';
            continue;
        }
        strncat(morseChar, &morseCode[i], 1);
        morse_len_tracker++;
        if(morse_len_tracker > MAX_MORSE_CHAR_LENGTH) {
            return_status = -1;
            morseChar[0] = '\0';
            morse_len_tracker = 0;
        }
    }

    return return_status;
}

    
/*
 * prints Dictionary in two columns
 */
void print_dictionary(CoderDecoder* coderDecoder) {
    printf("\t Morse Alphabet\n\n");
    for(int i = 0; i < NR_OF_CHARACTERS; i++) {
        printf("%s\t%c", coderDecoder->dictionary.morse_alphabet[i], coderDecoder->dictionary.alphabet[i]);
        printf("\t|\t");
        if(i < NR_OF_NUMBERS) printf("%s\t%c", coderDecoder->dictionary.morse_numbers[i], coderDecoder->dictionary.numbers[i]);
        printf("\n");
    }
}

/*
 * changes decoder sensitivity
 * param1: true for case sensitive false for insensitive
 */
void set_mode(CoderDecoder* coderDecoder, bool case_sensitive) {
    coderDecoder->case_sensitive = case_sensitive;
}

/*
 * get number of segments of a string seperated by a character
 * param1: string you want to count the segments of
 * param2: seperator character
 * return: number of segments seperated by param2
 */
size_t nr_of_seg(char* morseCode, char ch) {
    size_t char_counter = 0;
    int i = 0;
    while(1) {
        if(morseCode[i] == '\0') break;
        if(morseCode[i] == ch) {
            char_counter++;
        }
        i++;
    }
    return char_counter++;
}

/*
 * get shifted character from alphabet
 * param1: character to shift
 * param2: integer shift
 * return: returns shifted character, if character is not found function will return space
 */
int caesar_get_char(CoderDecoder* coderDecoder, char ch, char* dest, unsigned int shift_nr) {
    unsigned int adjusted_nr;
    size_t len = strlen(coderDecoder->dictionary.alphabet);
    shift_nr = shift_nr % len;
    for(size_t i = 0; i < len; i++) {
        if(ch == coderDecoder->dictionary.alphabet[i]) {
            adjusted_nr = i + shift_nr;
            if(adjusted_nr >= len)
                adjusted_nr -= len;
            *dest = coderDecoder->dictionary.alphabet[adjusted_nr];
            return 1;
        }
    }
    return -1;
}

int caesar_encrypt(CoderDecoder* coderDecoder, String* input, String* dest, unsigned int shift_nr) {
    string_clear(dest);
    char shifted_char;
    int return_status = 1;
    for(size_t i = 0; i < input->length; i++) {
        if(caesar_get_char(coderDecoder, input->str[i], &shifted_char, shift_nr) != 1)
            return_status = -1;

        string_append_char(dest, shifted_char);
    }
    return return_status;
}

/*
 * command caesar
 */
void caesar(CoderDecoder* coderDecoder) {
    String input_str = string_new();
    String encrypted_input = string_new();
    bool run = true;
    while(run) {
        printf("\nEnter text you want to caesar shift (options -o)\n(caesar) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-o") == 0) {
            printf("\n- '-exit' exit caesar mode\n");
        }
        else if(strcmp(input_str.str, "-exit") == 0) {
            run = false;
        }
        else {
            printf("\nEnter shift number\n(caesar) >> ");
            unsigned int shift_nr;
            int result = scanf("%d", &shift_nr);
            if(result == EOF) {
                printf("No Entry\n");
                continue;
            }
            if(result == 0) {
                buffer_clear();
                printf("Could not read\n");
                continue;
            }
            if(caesar_encrypt(coderDecoder, &input_str, &encrypted_input, shift_nr) != 1)
                printf("Some characters could not be found and will be ignored\n");
            buffer_clear();
            printf("Encryted input: %s\n", encrypted_input.str);
        }
    }
    string_destroy(&encrypted_input);
    string_destroy(&input_str);
}

int decode_check_valid_input_chars(String* input) {
    char ch;
    for(size_t i = 0; i < input->length; i++) {
        ch = input->str[i];
        if(ch != '-' && ch != '.' && ch != ' ')
            return 0;
    }
    return 1;
}

/*
 * command decode
 */
void decode(CoderDecoder* coderDecoder) {
    String input_str = string_new();
    bool run = true;

    while(run) {
        printf("\nEnter text you want to decode\n(decoder) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("Exiting decoder mode...\n");
            break;
        }
        else if(strcmp(input_str.str, "-o") == 0) {
            printf("- '-exit' exit decoder mode\n");
            continue;
        }
        else if(!decode_check_valid_input_chars(&input_str)) {
            printf("\nYou can only enter '.' and '-' and ' ' to separate characters\n\n");
            continue;
        }
        char* decodedString = malloc((nr_of_seg(input_str.str, ' ') + 1) * sizeof(char));
        decodedString[0] = '\0';
        if(decode_from_morse(coderDecoder, input_str.str, decodedString) != 1)
            printf("\nSome characters were not found, they will be ignored\n");
        printf("\nDecoded: %s\n\n\n", decodedString);
        free(decodedString);
    }

    string_destroy(&input_str);
}
/*
 * encode text from file and print to another file
 * param1: source file
 * param2: destination file
 */
int encode_stream_file_to_file(CoderDecoder* coderDecoder, FILE* source, FILE* dest) {
    char ch;
    char morseChar[MAX_MORSE_CHAR_LENGTH + 1] = ""; 
    int res = 1;
    while((ch = getc(source)) != EOF) {
        if(get_morse_code(coderDecoder, ch, morseChar) != 1)
            res = -1;
        fprintf(dest, "%s ", morseChar);
    }
    fflush(dest);
    return res;
}

/*
 * encode text file to morse code alternative print file
 */
void encode_from_file(CoderDecoder* coderDecoder) {
    printf("Enter name of file to encode\n>> "); 
    String input_str = string_new();
    string_read_file(&input_str, stdin);
    string_trunk_trailing_spaces(&input_str);
    FILE* source = fopen(input_str.str, "r");
    if(source == NULL) {
        printf("\nFile was not found\n");
        string_destroy(&input_str);
        return;
    }
    FILE* destination;
    
    bool y_n = true;
    char y_n_char;
    while(y_n) {
        printf("Would you like to print result to a file? (y/n)\n>> ");
        int result = scanf("%c", &y_n_char);
        if(result == 0) {
            printf("Could not read\n");
            continue;
        }
        if(result == EOF) {
            printf("No entry\n");
            continue;
        }
        buffer_clear();
        if(y_n_char == 'n') {
            destination = stdout;
            break;
        }
        if(y_n_char == 'y') {
            printf("Enter filename to print encoded result\n>>");
            string_read_file(&input_str, stdin);
            string_trunk_trailing_spaces(&input_str);
            destination = fopen(input_str.str, "w+");
            break;
        }
        printf("Enter 'y' or 'n' to continue\n");
    }
    if(encode_stream_file_to_file(coderDecoder, source, destination) != 1)
        printf("\nUnrecognizable characters are ignored\n\n");
    if(destination != stdout) fclose(destination);
    fclose(source);
    string_destroy(&input_str);
}
/*
 * command encode
 */
void encode(CoderDecoder* coderDecoder) {
    String input_str = string_new();
    bool run = true;
    while(run) {
        printf("\nEnter text you want to encode (options '-o')\n(encoder) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("\nExiting encoder mode...\n");
            break;
        }
        else if(strcmp(input_str.str, "-o") == 0) {
            printf("\n- '-f' encode text from file\n");
            printf("- '-exit' exit\n");
        }
        else if(strcmp(input_str.str, "-f") == 0)
            encode_from_file(coderDecoder);
        else {
            char* encodedString = malloc((input_str.length * MAX_MORSE_CHAR_LENGTH + 1) * sizeof(char));
            encodedString[0] = '\0';
            if(encode_to_morse(coderDecoder, input_str.str, encodedString) == -1) 
                printf("\nUnrecognizable characters will be ignored\n");
            printf("\nMorse: %s\n\n\n", encodedString);
            free(encodedString);
        }
    }
    string_destroy(&input_str);
}

/*
 * command search
 */
void search(CoderDecoder* coderDecoder) {
    String input_str = string_new();
    bool run = true;
    while(run) {
        printf("\nEnter character you want to translate (options '-o')\n(search) >> ");
        string_read_file(&input_str, stdin);
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("\nExiting search mode...\n");
            break;
        }
        else if(strcmp(input_str.str, "-o") == 0)
            printf("\n- '-exit' exit search mode\n");
        else {    
            char input_char = input_str.str[0];
            char morseCode[MAX_MORSE_CHAR_LENGTH];
            if(get_morse_code(coderDecoder, input_char, morseCode) != 1)
                printf("\nThis character was not found\n");
            else
                printf("\nMorse: %s\n\n\n", morseCode);
        }
    }
}

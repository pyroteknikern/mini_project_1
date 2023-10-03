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
    printf("- 'help'\t\t\tshows the list of commands and what they do.\n");
    printf("- 'code input text' 'encode'\tcode the input text in Morse code.\n");
    printf("- 'decode input text' 'decode'\tdecode the entered Morse code.\n");
    printf("- 'search'\t\t\ttranslate specified character to morse code.\n");
    printf("- 'show'\t\t\tshow available characters.\n");
    printf("- 'case_sensitive' 'cs'\t\tenable case-sensitive processing.\n");
    printf("- 'case_insensitive' 'ci'\tenable case-insensitive processing.\n");
    printf("- 'status'\t\t\tsee status of decoder.\n");
    printf("- 'caesar'\t\t\tuse the caesar encoder.\n");
    printf("- 'exit'\t\t\texit\n\n");
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
    strcat(dictionary.characters, " ");


    char* morse_numbers[] = {".---- ", "..--- ", "...-- ", "....- ", "..... ", "-.... ", "--... ", "---.. ", "----. ", "----- "};
    char* morse_alphabet[] = {".- ", "-... ", "-.-. ", "-.. ", ". ", "..-. ", "--. ", ".... ", ".. ", ".--- ", "-.- ", ".-.. ", "-- ", "-. ", "--- ", ".--. ", "--.- ", ".-. ", "... ", "- ", "..- ", "...- ", ".-- ", "-..- ", "-.-- ", "--.. "};

    
    for(size_t i = 0; i < NR_OF_NUMBERS; i++) {
        strcpy(dictionary.morse_codes[i], morse_numbers[i]);
        strcpy(dictionary.morse_numbers[i], morse_numbers[i]);
    }
    for(size_t i = 0; i < NR_OF_CHARACTERS; i++) {
        strcpy(dictionary.morse_codes[i + NR_OF_NUMBERS], morse_alphabet[i]);
        strcpy(dictionary.morse_alphabet[i], morse_alphabet[i]);
    }
    strcpy(dictionary.morse_codes[MAX_DICTIONARY_SIZE - 1], " ");
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

void status(CoderDecoder* coderDecoder) {
    if(coderDecoder->case_sensitive)
        printf("\nDecoder is case sensitive\n");
    else
        printf("\nDecoder is not case sensitive\n");
}




    
/*
 * prints Dictionary
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
 * param1: CoderDecoder obj
 * param2: true for case sensitive false for insensitive
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
size_t nr_of_seg(char* morse_code, char ch) {
    size_t char_counter = 0;
    int i = 0;
    while(1) {
        if(morse_code[i] == '\0') break;
        if(morse_code[i] == ch) {
            char_counter++;
        }
        i++;
    }
    return char_counter++;
}

/*
 * get shifted character from alphabet
 * param1: CoderDecoder obj 
 * param2: character to shift
 * param3: pointer to character that will be changed to shifted character
 * param2: integer shift
 * return: returns 1 if success, if character is not found function will return -1 
 * note param3 will not be changed if character is not found
 */
int caesar_get_char(CoderDecoder* coderDecoder, char ch, char* dest, uint shift_nr) {
    uint adjusted_nr;
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


/*
 * encrypts input String
 * param1: CoderDecoder obj
 * param2: dynamic String input
 * param3: dynamic String output
 * param4: shift number
 * return: returns 1 if success and -1 if atleast 1 character was not translated
 */
int caesar_encrypt(CoderDecoder* coderDecoder, String* input, String* dest, uint shift_nr) {
    string_clear(dest);
    char shifted_char;
    int return_status = 1;
    char ch;
    for(size_t i = 0; i < input->length; i++) {
        ch = input->str[i];
        if(!coderDecoder->case_sensitive)
            ch = tolower(ch);
        if(caesar_get_char(coderDecoder, ch, &shifted_char, shift_nr) != 1)
            return_status = -1;

        if(string_append_char(dest, shifted_char) == -1) return -1;
    }
    return return_status;
}

/*
 * command caesar
 */
void caesar(CoderDecoder *coderDecoder) {
    String input_str = string_new();
    bool run = true;
    while(run) {
        printf("\nEnter text you want to encrypt (help '-h')\n(caesar) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-h") == 0) {
            printf("\n- '-back' exit caesar mode\n");
            continue;
        }
        else if(strcmp(input_str.str, "-back") == 0) {
            run = false;
            continue;
        }
        printf("\nEnter shift number\n(caesar) >> ");
        uint shift_nr;
        int result = scanf("%d", &shift_nr);
        if(result == EOF) {
            printf("\nNo Entry\n");
            continue;
        }
        if(result == 0) {
            buffer_clear();
            printf("\nCould not read\n");
            continue;
        }
        String encrypted_string = string_new();
        if(caesar_encrypt(coderDecoder, &input_str, &encrypted_string, shift_nr) != 1)
            printf("\nSome characters could not be found and will be ignored\n");
        buffer_clear();
        printf("\nEncryted: %s\n\n", encrypted_string.str);
        string_destroy(&encrypted_string);
    }
    string_destroy(&input_str);
    printf("\nExiting caesar encoder...\n");
}

/*
 * translate morse code to ASCII character
 * param1: CoderDecoder obj
 * param2: string that contains morse code
 * param3: pointer to character that will be populated by the translated morse code
 * return: returns 1 if character was found and -1 if not found
 * note function does not change value of param3 if it was not found
 */

int decode_get_char_from_morse(CoderDecoder* coderDecoder, const char* morseChar, char* character) {
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
 * param1: CoderDecoder obj
 * param2: string of the morse code, characters are separated by space
 * param3: pointer to string that will be populated by the decoded morse code
 * return: returns 1 if every morse character was successfuly translated and -1 if one or more characters were not found
 * note: param3 not having enough memory can lead to undefined behaviour
 */
int decode_from_morse(CoderDecoder* coderDecoder, const char *morse_code, char *decoded_text) {
    decoded_text[0] = '\0';
    String morse_char = string_new();
    char tmp_char;
    int return_status = 1;
    int tmp_status;
    for(int i = 0; i < strlen(morse_code) + 1; i++) {
        if(morse_code[i] == ' ' || morse_code[i] == '\0') {
            string_append_char(&morse_char, ' ');
            if(decode_get_char_from_morse(coderDecoder, morse_char.str, &tmp_char) == -1)
                return_status = -1;
            strncat(decoded_text, &tmp_char, 1);
            string_clear(&morse_char);
            if(morse_code[i] == '\0') break;
            continue;
        } 
        string_append_char(&morse_char, morse_code[i]);
    }
    string_destroy(&morse_char);
    return return_status;
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
        string_clear(&input_str);
        printf("\nEnter text you want to decode (help '-h')\n(decoder) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-back") == 0) {
            run = false;
            continue;
        }
        else if(strcmp(input_str.str, "-h") == 0) {
            printf("- '-back' exit decoder mode\n");
            continue;
        }
        else if(!decode_check_valid_input_chars(&input_str)) {
            printf("\nYou can only enter '.' and '-' with spaces to separate characters and double spaces to seperate words\n\n");
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
    printf("\nExiting decoder mode...\n");
}


/*
 * translates an ASCII character to morse code
 * param1: CoderDecoder obj
 * param2: character you want to translate into morse
 * param3: pointer to a string that will be populated with morse
 * return: return 1 if character is found and -1 if character is not found
*/
int encode_get_morse_code(CoderDecoder* coderDecoder, const char character, char *morse_char){
    strcpy(morse_char, "");
    char ch = character;
    for(int i = 0; i < coderDecoder->dictionary.size; i++) {
        if(!coderDecoder->case_sensitive)
            ch = tolower(ch);
        if(ch == coderDecoder->dictionary.characters[i]) {
            strcpy(morse_char, coderDecoder->dictionary.morse_codes[i]);
            return 1;
        }
    }
    return -1;
}


/*
 * encodes an ASCII string to morse code
 * param1: CoderDecoder obj
 * param2: string you want to translate
 * param3: pointer to the string you want to populate with morse code
 * return: returns 1 if all characters were translated and -1 if 1 or more characters were not found
 * note: param3 not having enough memory can lead to undefined behaviour
*/
int encode_to_morse(CoderDecoder* coderDecoder, const char *text, char *encoded_text) {
    encoded_text[0] = '\0';
    char morse_char[MAX_MORSE_CHAR_LENGTH + 1] = "";
    int return_status = 1;
    int temp_status = 1;
    for(int i = 0; i < strlen(text); i++) {
        temp_status = encode_get_morse_code(coderDecoder, text[i], morse_char);
        if(temp_status == -1)
            return_status = -1;
        else {
            strcat(encoded_text, morse_char);
        }
    }
    return return_status;
}
/*
 * encode text from file and print to another file
 * param1: CoderDecoder obj
 * param2: source file
 * param3: destination file
 * return: returns 1 if success and -1 if atleast 1 character is not translated
 */
int encode_stream_file_to_file(CoderDecoder* coderDecoder, FILE* source, FILE* dest) {
    char ch;
    char morse_char[MAX_MORSE_CHAR_LENGTH + 1] = ""; 
    int res = 1;
    while((ch = getc(source)) != EOF) {
        if(encode_get_morse_code(coderDecoder, ch, morse_char) != 1)
            res = -1;
        fprintf(dest, "%s", morse_char);
    }
    fflush(dest);
    return res;
}

/*
 * encode text file to morse code alternative print file
 */
void encode_from_file(CoderDecoder* coderDecoder) {
    printf("Enter name of file to read\n(select file) >> "); 
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
            printf("Enter filename to print encoded result\n(select file) >>");
            string_read_file(&input_str, stdin);
            string_trunk_trailing_spaces(&input_str);
            destination = fopen(input_str.str, "w+");
            break;
        }
        printf("Enter 'y' or 'n' to continue\n");
    }
    if(encode_stream_file_to_file(coderDecoder, source, destination) != 1)
        printf("\n\nSome characters were not found, they will be ignored\n\n");
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
        printf("\nEnter text you want to encode (help '-h')\n(encoder) >> ");
        string_read_file(&input_str, stdin);
        string_trunk_trailing_spaces(&input_str);
        if(strcmp(input_str.str, "-back") == 0) {
            run = false;
            continue;
        }
        else if(strcmp(input_str.str, "-h") == 0) {
            printf("\n- '-f' encode text from file\n");
            printf("- '-back' exit\n");
            continue;
        }
        else if(strcmp(input_str.str, "-f") == 0) {
            encode_from_file(coderDecoder);
            continue;
        }
        char* encodedString = malloc((input_str.length * MAX_MORSE_CHAR_LENGTH + 2) * sizeof(char));
        encodedString[0] = '\0';
        if(encode_to_morse(coderDecoder, input_str.str, encodedString) == -1) 
            printf("\nSome characters were not found, they will be ignored\n");
        printf("\nMorse: %s\n\n\n", encodedString);
        free(encodedString);
    }
    string_destroy(&input_str);
    printf("\nExiting encoder mode...\n");
}

/*
 * command search
 */
void search(CoderDecoder* coderDecoder) {
    String input_str = string_new();
    bool run = true;
    while(run) {
        printf("\nEnter character you want to translate (help '-h')\n(search) >> ");
        string_read_file(&input_str, stdin);
            
        if(strcmp(input_str.str, "-back") == 0) {
            run = false;
            continue;
        }

        else if(strcmp(input_str.str, "-h") == 0) {
            printf("\n- '-back' exit search mode\n");   
            continue;
        }

        if(input_str.length != 1) {
            printf("\nEnter only 1 character\n");
            continue;
        }
        char input_char = input_str.str[0];
        char morseCode[MAX_MORSE_CHAR_LENGTH];
        if(encode_get_morse_code(coderDecoder, input_char, morseCode) != 1)
            printf("\nThis character was not found\n");
        else
            printf("\nMorse: %s\n\n\n", morseCode);
    }
    string_destroy(&input_str);
    printf("\nExiting search mode...\n");
}

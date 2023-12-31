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
    printf("- 'help'\t\t\t\tshows the list of commands and what they do.\n");
    printf("- 'encode <input text>'\t\t\tcode the input text in Morse code.\n");
    printf("- 'decode <input text>'\t\t\tdecode the entered Morse code.\n");
    printf("- 'search <input character>'\t\ttranslate specified character to morse code.\n");
    printf("- 'show'\t\t\t\tshow available characters.\n");
    printf("- 'case_sensitive' 'cs'\t\t\tenable case-sensitive processing.\n");
    printf("- 'case_insensitive' 'ci'\t\tenable case-insensitive processing.\n");
    printf("- 'status'\t\t\t\tsee status of decoder.\n");
    printf("- 'caesar <key> <input text>'\t\tuse the caesar encoder.\n");
    printf("- 'encode_file <input.txt> <output.txt>\tencodes file and outputs to file.\n");
    printf("- 'exit'\t\t\t\texit\n\n");
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

void status(const CoderDecoder* coderDecoder) {
    if(coderDecoder->case_sensitive)
        printf("\nDecoder is case sensitive\n");
    else
        printf("\nDecoder is not case sensitive\n");
}




    
/*
 * prints Dictionary
 */
void print_dictionary(const CoderDecoder* coderDecoder) {
    printf("\t Morse Alphabet\n\n");
    for(int i = 0; i < NR_OF_CHARACTERS; i++) {
        printf("%\t\t%c", coderDecoder->dictionary.morse_alphabet[i], coderDecoder->dictionary.alphabet[i]);
        printf("\t\t|\t\t");
        if(i < NR_OF_NUMBERS) printf("%s\t%c", coderDecoder->dictionary.morse_numbers[i], coderDecoder->dictionary.numbers[i]);
        printf("\n");
    }
}

/*
 * changes decoder sensitivity
 * param1: const CoderDecoder obj
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
 * param1: const CoderDecoder obj 
 * param2: character to shift
 * param3: pointer to character that will be changed to shifted character
 * param2: integer shift
 * return: returns 1 if success, if character is not found function will return -1 
 * note param3 will not be changed if character is not found
 */
int caesar_get_char(const CoderDecoder* coderDecoder, char ch, char* dest, uint shift_nr) {
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
 * param1: const CoderDecoder obj
 * param2: dynamic String input
 * param3: dynamic String output
 * param4: shift number
 * return: returns 1 if success and -1 if atleast 1 character was not translated
 */
int caesar_encrypt(const CoderDecoder* coderDecoder, String* input, String* dest, uint shift_nr) {
    string_clear(dest);
    char shifted_char;
    int return_status = 1;
    char ch;
    for(size_t i = 0; i < input->length; i++) {
        ch = input->str[i];
        if(ch == ' ') {
            string_append_char(dest, ' ');
            continue;
        }
        if(!coderDecoder->case_sensitive)
            ch = tolower(ch);
        if(caesar_get_char(coderDecoder, ch, &shifted_char, shift_nr) != 1)
            return_status = -1;
        else {
            string_append_char(dest, shifted_char);
        }
    }
    return return_status;
}

/*
 * command caesar
 */
void caesar(const CoderDecoder *coderDecoder) {
    uint shift_nr;
    int result = scanf("%d", &shift_nr);

    if(result == EOF) {
        printf("\nNo Entry\n");
        return;
    }
    if(result == 0) {
        buffer_clear();
        printf("\nCould not read\n");
        return;
    }
    getchar();
    String input_str = string_new();
    string_read_file(&input_str, stdin);
    string_trunk_trailing_spaces(&input_str);
    String encrypted_string = string_new();
    if(caesar_encrypt(coderDecoder, &input_str, &encrypted_string, shift_nr) != 1)
        printf("\nSome characters could not be found and will be ignored\n");
    printf("\nEncryted: %s\n\n", encrypted_string.str);
    string_destroy(&encrypted_string);
    string_destroy(&input_str);
}

/*
 * translate morse code to ASCII character
 * param1: const CoderDecoder obj
 * param2: string that contains morse code
 * param3: pointer to character that will be populated by the translated morse code
 * return: returns 1 if character was found and -1 if not found
 * note function does not change value of param3 if it was not found
 */

int decode_get_char_from_morse(const CoderDecoder* coderDecoder, const char* morseChar, char* character) {
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
 * param1: const CoderDecoder obj
 * param2: string of the morse code, characters are separated by space
 * param3: pointer to string that will be populated by the decoded morse code
 * return: returns 1 if every morse character was successfuly translated and -1 if one or more characters were not found
 * note: param3 not having enough memory can lead to undefined behaviour
 */
int decode_from_morse(const CoderDecoder* coderDecoder, const String *morse_code, String *decoded_text) {
    string_clear(decoded_text);
    String morse_char = string_new();
    char tmp_char;
    int return_status = 1;
    int tmp_status;
    for(int i = 0; i < morse_code->length + 1; i++) {
        if(morse_code->str[i] != ' ' && morse_code->str[i] != '\0') {
            string_append_char(&morse_char, morse_code->str[i]);
            continue;
        }

        string_append_char(&morse_char, ' ');
        if(decode_get_char_from_morse(coderDecoder, morse_char.str, &tmp_char) == -1) {
            return_status = -1;
            string_clear(&morse_char);
            continue;
        }
        string_append_char(decoded_text, tmp_char);
        string_clear(&morse_char);
    }
    string_destroy(&morse_char);
    return return_status;
}


int decode_check_valid_input_chars(const String* input) {
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
void decode(const CoderDecoder* coderDecoder) {
    String input_str = string_new();
    string_read_file(&input_str, stdin);
    string_trunk_trailing_spaces(&input_str);
    if(!decode_check_valid_input_chars(&input_str)) {
        printf("\nYou can only enter '.' and '-' with spaces to separate characters and double spaces to seperate words\n\n");
        string_destroy(&input_str);
        return;
    }
    String decoded_input = string_new();
    if(decode_from_morse(coderDecoder, &input_str, &decoded_input) != 1)
        printf("\nSome characters were not found, they will be ignored\n");
    printf("\nDecoded: %s\n\n\n", decoded_input.str);
    string_destroy(&decoded_input);
    string_destroy(&input_str);
}


/*
 * translates an ASCII character to morse code
 * param1: const CoderDecoder obj
 * param2: character you want to translate into morse
 * param3: pointer to a string that will be populated with morse
 * return: return 1 if character is found and -1 if character is not found
*/
int encode_get_morse_code(const CoderDecoder* coderDecoder, const char character, char *morse_char){
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
 * param1: const CoderDecoder obj
 * param2: string you want to translate
 * param3: pointer to the string you want to populate with morse code
 * return: returns 1 if all characters were translated and -1 if 1 or more characters were not found
 * note: param3 not having enough memory can lead to undefined behaviour
*/
int encode_to_morse(const CoderDecoder* coderDecoder, const char *text, char *encoded_text) {
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
 * param1: const CoderDecoder obj
 * param2: source file
 * param3: destination file
 * return: returns 1 if success and -1 if atleast 1 character is not translated
 */
int encode_stream_file_to_file(const CoderDecoder* coderDecoder, FILE* source, FILE* dest) {
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
void encode_file(const CoderDecoder* coderDecoder) {
    String file1_string = string_new();
    string_input(&file1_string);
    string_trunk_trailing_spaces(&file1_string);
    FILE* source = fopen(file1_string.str, "r");
    string_destroy(&file1_string);
    if(source == NULL) {
        printf("\nSource file was not found\n");
        return;
    }
    String file2_string = string_new();
    string_input(&file2_string);
    string_trunk_trailing_spaces(&file2_string);
    FILE* destination = fopen(file2_string.str, "w+");
    string_destroy(&file2_string);
    if(source == NULL) {
        printf("\nDestination file was not found\n");
        return;
    }
    if(encode_stream_file_to_file(coderDecoder, source, destination) != 1)
        printf("\n\nSome characters were not found, they will be ignored\n\n");
    if(destination != stdout) fclose(destination);
    fclose(source);
}
/*
 * command encode
 */
void encode(const CoderDecoder* coderDecoder) {
    String input_str = string_new();
    string_read_file(&input_str, stdin);
    string_trunk_trailing_spaces(&input_str);
    
    char* encodedString = malloc((input_str.length * MAX_MORSE_CHAR_LENGTH + 2) * sizeof(char));
    encodedString[0] = '\0';
    if(encode_to_morse(coderDecoder, input_str.str, encodedString) == -1) 
        printf("\nSome characters were not found, they will be ignored\n");
    printf("\nMorse: %s\n\n\n", encodedString);
    free(encodedString);
    string_destroy(&input_str);
}

/*
 * command search
 */
void search(const CoderDecoder* coderDecoder) {
    String input_str = string_new();
    string_read_file(&input_str, stdin);
        
    if(input_str.length != 1) {
        printf("\nEnter only 1 character\n");
        string_destroy(&input_str);
        return;
    }
    char input_char = input_str.str[0];
    char morseCode[MAX_MORSE_CHAR_LENGTH];
    if(encode_get_morse_code(coderDecoder, input_char, morseCode) != 1)
        printf("\nThis character was not found\n");
    else
        printf("\nMorse: %s\n\n\n", morseCode);
    string_destroy(&input_str);
}
